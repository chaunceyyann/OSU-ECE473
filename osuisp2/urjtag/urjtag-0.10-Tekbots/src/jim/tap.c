/*
 * $Id: tap.c $
 *
 * Copyright (C) 2008 Kolja Waschk <kawk>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <jim.h>

#include <jim/some_cpu.h>

#undef VERBOSE

const tap_state_t next_tap_state[16][2] =
{
  /* RESET       */ { IDLE,       RESET },
  /* SELECT_DR   */ { CAPTURE_DR, SELECT_IR },
  /* CAPTURE_DR  */ { SHIFT_DR,   EXIT1_DR },
  /* SHIFT_DR    */ { SHIFT_DR,   EXIT1_DR },
  /* EXIT1_DR    */ { PAUSE_DR,   UPDATE_DR },
  /* PAUSE_DR    */ { PAUSE_DR,   EXIT2_DR },
  /* EXIT2_DR    */ { SHIFT_DR,   UPDATE_DR },
  /* UPDATE_DR   */ { IDLE,       SELECT_DR },
  /* IDLE        */ { IDLE,       SELECT_DR },
  /* SELECT_IR   */ { CAPTURE_IR, RESET },
  /* CAPTURE_IR  */ { SHIFT_IR,   EXIT1_IR },
  /* SHIFT_IR    */ { SHIFT_IR,   EXIT1_IR },
  /* EXIT1_IR    */ { PAUSE_IR,   UPDATE_IR },
  /* PAUSE_IR    */ { EXIT2_IR,   EXIT2_IR },
  /* EXIT2_IR    */ { SHIFT_IR,   UPDATE_IR },
  /* UPDATE_IR   */ { IDLE,       SELECT_DR }
};

void jim_print_sreg(shift_reg_t *r)
{
  int i;
  for(i=(r->len+31)/32; i>=0; i--) printf(" %08X", r->reg[i]);
}

void jim_print_tap_state(char *rof, jim_device_t *dev)
{
  printf(" tck %s, state=", rof);
  switch(dev->tap_state & 7)
  {
    case 0:  printf((dev->tap_state==RESET) ? "RESET":"IDLE" ); break;
    case 1:  printf("SELECT"); break;
    case 2:  printf("CAPTURE"); break;
    case 3:  printf("SHIFT"); break;
    case 4:  printf("EXIT1"); break;
    case 5:  printf("PAUSE"); break;
    case 6:  printf("EXIT2"); break;
    default: printf("UPDATE"); break;
  }
  if(dev->tap_state & 7)
  {
    if(dev->tap_state & 8)
    {
      printf("_IR="); jim_print_sreg(&dev->sreg[0]);
    }
    else
    {
      printf("_DR");
      if(dev->current_dr != 0)
      {
        printf("(%d)=", dev->current_dr);
        jim_print_sreg(&dev->sreg[dev->current_dr]);
      }
    }
  }
  printf("\n");
}


void jim_set_trst(jim_state_t *s, int trst)
{
  s->trst = trst;
}

int jim_get_trst(jim_state_t *s)
{
  return s->trst;
}

int jim_get_tdo(jim_state_t *s)
{
  if(s->last_device_in_chain == NULL) return 0;
  return s->last_device_in_chain -> tdo;
}
 
void jim_tck_rise(jim_state_t *s, int tms, int tdi)
{
  jim_device_t *dev;


  for(dev = s->last_device_in_chain; dev; dev = dev->prev)
  {
    int dev_tdi;
    int i, n;
    shift_reg_t *sr;
    uint32_t *reg;

#ifdef VERBOSE
    jim_print_tap_state("rise", dev);
#endif

    dev_tdi = (dev->prev != NULL) ? dev->prev->tdo : tdi;

    if(dev->tck_rise != NULL) dev->tck_rise(dev, tms, dev_tdi, s->shmem, s->shmem_size);

    if(dev->tap_state & 8)
    {
      sr =  &(dev->sreg[0]);
    }
    else
    {
      if(dev->current_dr == 0)
      {
        sr = NULL; /* BYPASS */
      }
      else
      {
        sr = &(dev->sreg[dev->current_dr]);
      }
    }

    if(sr == NULL) /* BYPASS */
    {
      dev->tdo_buffer = dev_tdi;
    }
    else 
    {
      reg = sr->reg;

      if(dev->tap_state == SHIFT_IR || dev->tap_state == SHIFT_DR)
      {
        /* Start with LSW of shift register at index 0 */
    
        n = (sr->len-1) / 32;
        for(i=0; i < (sr->len-1)/32; i++)
        {
          reg[i] >>= 1;
          if(reg[i+1] & 1) reg[i] |= 0x80000000;
        }
    
        /* End with MSW at index i */
    
        reg[i] >>=1;
        if(dev_tdi != 0)
        {
          n = (sr->len & 31);
          if(n == 0) n = 32;
          reg[i] |= (1 << (n-1));
        }
      }

      dev->tdo_buffer = reg[0] & 1;
    }

    dev->tap_state = next_tap_state[dev->tap_state][tms];
  }
}

void jim_tck_fall(jim_state_t *s)
{
  jim_device_t *dev;

  for(dev = s->last_device_in_chain; dev; dev = dev->prev)
  {
    dev->tdo = dev->tdo_buffer;

#ifdef VERBOSE
    jim_print_tap_state("fall", dev);
#endif

    if(dev->tck_fall != NULL) dev->tck_fall(dev, s->shmem, s->shmem_size);
  }
}

jim_device_t *jim_alloc_device(int num_sregs, const int reg_size[])
{
  int i, r;

  jim_device_t *dev = (jim_device_t *)malloc(sizeof(jim_device_t));

  if(dev == NULL)
  {
    printf("Out of memory\n");
    return NULL;
  }

  dev->sreg =
    (shift_reg_t *)malloc(num_sregs * sizeof(shift_reg_t));

  if(dev->sreg == NULL)
  {
    free(dev);
    printf("Out of memory\n");
    return NULL;
  }

  for(r=0,i=0;i<num_sregs;i++)
  {
    dev->sreg[i].len = reg_size[i];
    dev->sreg[i].reg = 
        (uint32_t*)calloc(((reg_size[i]+31)/32), sizeof(uint32_t));
    if(dev->sreg[i].reg == NULL) r++;
  }

  if(r>0)
  {
    printf("Out of memory\n");
    for(i=0;i<num_sregs;i++) if(dev->sreg[i].reg!=NULL) free(dev->sreg[i].reg);
    free(dev->sreg);
    free(dev);
    return NULL;
  }

  dev->num_sregs  = num_sregs;
  dev->current_dr = 0;
  dev->tck_rise   = NULL;
  dev->tck_fall   = NULL;
  dev->dev_free   = NULL;
  dev->tap_state  = RESET;
  dev->tdo = dev->tdo_buffer = 1;

  return dev;
}

jim_state_t *jim_init(void)
{
  jim_state_t *s;

  s = (jim_state_t *)malloc(sizeof(jim_state_t));
  if(s == NULL)
  {
    printf("Out of memory!\n");
    return NULL;
  }

  s->shmem_size = (1<<20)*16; /* 16 MByte */
  s->shmem = malloc(s->shmem_size);

  if(s->shmem != NULL)
  {
    memset(s->shmem, 0xFF, s->shmem_size);
    printf("Allocated %zd bytes for device memory simulation.\n", s->shmem_size);
  }
  else
  {
    free(s);
    printf("Out of memory!\n");
    return NULL;
  }

  s->trst = 0;
  s->last_device_in_chain = some_cpu();

  if(s->last_device_in_chain != NULL)
  {
    s->last_device_in_chain->prev = NULL;
  }
  else
  {
    printf("Out of memory!\n");
    free(s->shmem);
    free(s);
    return NULL;
  }
  return s;
}

void jim_free(jim_state_t *s)
{
  jim_device_t *dev, *pre;

  if(s == NULL) return;

  for(dev = s->last_device_in_chain; dev; dev=pre)
  {
    int i;

    if(dev->dev_free != NULL) dev->dev_free(dev);
    for(i=0;i<dev->num_sregs;i++)
    {
      free(dev->sreg[i].reg);
    }
    free(dev->sreg);
    pre = dev->prev;
    free(dev);
  }

  s->last_device_in_chain = NULL;
  free(s->shmem);
  free(s);
}


