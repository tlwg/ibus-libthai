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

#ifndef __IBUS_CONFIG_H__
#define __IBUS_CONFIG_H__

#include <thai/thinp.h>
#include "thaikb.h"
#include <gio/gio.h>

typedef struct _IBusLibThaiSetupOptions IBusLibThaiSetupOptions;

struct _IBusLibThaiSetupOptions
{
  ThaiKBMap  thai_kb_map;
  thstrict_t isc_mode;
  gboolean   do_correct;
};

void ibus_libthai_read_config (GSettings *settings,
                               IBusLibThaiSetupOptions *opt);
void ibus_libthai_write_config (GSettings *settings,
                                const IBusLibThaiSetupOptions *opt);

#endif /* __IBUS_CONFIG_H__ */

/*
vi:ts=2:nowrap:ai:expandtab
*/
