/*
 * $Id: bssignal.h 732 2007-11-07 09:56:15Z kawk $
 *
 * Copyright (C) 2002 ETC s.r.o.
 * Copyright (C) 2003 Marcel Telka
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * Written by Marcel Telka <marcel@telka.sk>, 2002, 2003.
 *
 */

#ifndef SIGNAL_H
#define	SIGNAL_H

typedef struct signal signal_t;

#include "bsbit.h"

struct signal {
	char *name;
	char *pin;	/* djf hack pin number from bsdl */
	signal_t *next;
	bsbit_t *input;
	bsbit_t *output;
};

typedef struct salias salias_t;

struct salias {
	char *name;
	salias_t *next;
	signal_t *signal;
};

signal_t *signal_alloc( const char *name );
void signal_free( signal_t *s );

salias_t *salias_alloc( const char *name, const signal_t *signal );
void salias_free( salias_t *salias );

#endif /* SIGNAL_H */
