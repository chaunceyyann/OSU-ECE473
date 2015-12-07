/*
 * $Id: bsdl_msg.h 1345 2008-08-27 20:40:16Z arniml $
 *
 * Copyright (C) 2008, Arnim Laeuger
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
 * Written by Arnim Laeuger <arniml@users.sourceforge.net>, 2007.
 *
 */

#ifndef BSDL_MSG_H
#define BSDL_MSG_H

#include "bsdl_types.h"

/* message types for bsdl_msg() */
#define BSDL_MSG_NOTE  0
#define BSDL_MSG_WARN  1
#define BSDL_MSG_ERR   2
#define BSDL_MSG_FATAL 3

void bsdl_msg( int, int, const char *, ... );

#endif /* BSDL_MSG_H */
