/*
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * c-candy/include/constants.h
 *
 * (C) Copyright 2021 Akash Nag
 *
 * This program is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; version 2.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this
 * program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

/* start of include guard */
#ifndef CONSTANTS_H

#define CONSTANTS_H

/* Version */
#define C_CANDY_VERSION					"0.1.0-alpha"

/* Error constants */
#define ERR_MEM_ALLOC				 	-2
#define ERR_NULL_OBJECT					-3
#define ERR_INDEX_OUT_OF_BOUNDS			-4
#define ERR_BAD_REGEX					-5
#define ERR_TYPE_MISMATCH				-6

/* definition of BOOL (boolean) */
typedef enum {
	FALSE = 0, TRUE = 1
} BOOL;

/* definition of item type */
typedef enum {
	TYPE_CHAR, TYPE_STR, 
	TYPE_SHORT, TYPE_INT, TYPE_LONG, TYPE_LONG_LONG,
	TYPE_FLOAT, TYPE_DOUBLE, TYPE_LONG_DOUBLE, TYPE_OBJECT
} ITEM_TYPE;

/* end of include guard */
#endif
