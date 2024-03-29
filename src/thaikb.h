/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 *  Copyright (C) 2012 Theppitak Karoonboonyanan <theppitak@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef __THAIKB_H__
#define __THAIKB_H__

typedef enum _ThaiKBMap ThaiKBMap;

enum _ThaiKBMap
{
  THAI_KB_KETMANEE,
  THAI_KB_PATTACHOTE,
  THAI_KB_TIS820_2538,
  THAI_KB_MANOONCHAI,
};

unsigned char thai_map_keycode (ThaiKBMap map, int keycode, int shift_lv);

#endif /* __THAIKB_H__ */
 
/*
vi:ts=2:nowrap:ai:expandtab
*/
