/*
 * $Id: signal.c 733 2007-11-07 22:21:33Z arniml $
 *
 * Copyright (C) 2002 ETC s.r.o.
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
 * Written by Marcel Telka <marcel@telka.sk>, 2002.
 *
 */

#include <stdlib.h>
#include <string.h>

#include "bssignal.h"

signal_t *
signal_alloc( const char *name )
{
	signal_t *s = malloc( sizeof *s );
	if (!s)
		return NULL;

	s->name = strdup( name );
	if (!s->name) {
		free( s );
		return NULL;
	}
	s->pin = NULL; /* djf hack pin number */
	s->next = NULL;
	s->input = NULL;
	s->output = NULL;

	return s;
}

void
signal_free( signal_t *s )
{
	if (!s)
		return;
	free( s->name );
	free( s );
}

salias_t *
salias_alloc( const char *name, const signal_t *signal )
{
	salias_t *sa = malloc( sizeof *sa );
	if (sa == NULL)
		return NULL;

	sa->name = strdup( name );
	if (sa->name == NULL) {
		free( sa );
		return NULL;
	}
	sa->next = NULL;
	sa->signal = (signal_t *)signal;

	return sa;
}

void salias_free( salias_t *salias )
{
	if (salias == NULL)
		return;
	free( salias->name );
	free( salias );
}
