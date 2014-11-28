PRG            =hd44780

OBJS            = $(PRG).o  lcd_test1_8bit.o hd44780.o
#OBJS            = $(PRG).o  lcd1.o

MCU_TARGET     = atmega8

F_CPU          = 8000000UL

#OPTIMIZE       = -O0    # options are 1, 2, 3, s
#OPTIMIZE       = -O1    # options are 1, 2, 3, s
OPTIMIZE        = -O2    # options are 1, 2, 3, s
#OPTIMIZE       = -Os    # options are 1, 2, 3, s

DEFS           =
LIBS           =

CC             = avr-gcc

# Override is only needed by avr-lib build system.

override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS) -DF_CPU=$(F_CPU)
override LDFLAGS       = -Wl,-Map,$(PRG).map

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

all: $(PRG).elf lst text eeprom

$(PRG).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean: 
	rm -rf *.o $(PRG).elf *.lst *.map *.srec *.hex *.bin 

program: $(PRG).hex
	avrdude -p m8 -c usbasp  -e -U flash:w:$(PRG).hex 
#	avrdude -p m128 -c ousisp2 -e -U flash:w:$(PRG).hex 

lst:  $(PRG).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: hex bin srec

hex:  $(PRG).hex
bin:  $(PRG).bin
srec: $(PRG).srec

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images

eeprom: ehex ebin esrec

ehex:  $(PRG)_eeprom.hex
ebin:  $(PRG)_eeprom.bin
esrec: $(PRG)_eeprom.srec

%_eeprom.hex: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@

%_eeprom.srec: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@

%_eeprom.bin: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@

