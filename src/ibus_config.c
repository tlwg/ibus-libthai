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

#include "ibus_config.h"
#include "engine_const.h"

#include <stdlib.h>

void
ibus_libthai_read_config (GSettings *settings,
                          IBusLibThaiSetupOptions *opt)
{
  opt->thai_kb_map = g_settings_get_enum (settings, CONFIG_KB_LAYOUT);
  opt->isc_mode = g_settings_get_enum (settings, CONFIG_ISC_MODE);
  opt->do_correct = g_settings_get_boolean (settings, CONFIG_DO_CORRECT);
}

static int
n_option_diffs (const IBusLibThaiSetupOptions *opt1,
                const IBusLibThaiSetupOptions *opt2)
{
  int n_diffs = 0;

  if (opt1->thai_kb_map != opt2->thai_kb_map)
    ++n_diffs;
  if (opt1->isc_mode != opt2->isc_mode)
    ++n_diffs;
  if (opt1->do_correct != opt2->do_correct)
    ++n_diffs;

  return n_diffs;
}

void
ibus_libthai_write_config (GSettings *settings,
                           const IBusLibThaiSetupOptions *opt,
                           const IBusLibThaiSetupOptions *prev_opt)
{
  int n_diffs = n_option_diffs (opt, prev_opt);

  if (n_diffs > 1)
    g_settings_delay (settings);

  if (opt->thai_kb_map != prev_opt->thai_kb_map)
    g_settings_set_enum (settings, CONFIG_KB_LAYOUT, opt->thai_kb_map);
  if (opt->isc_mode != prev_opt->isc_mode)
    g_settings_set_enum (settings, CONFIG_ISC_MODE, opt->isc_mode);
  if (opt->do_correct != prev_opt->do_correct)
    g_settings_set_boolean (settings, CONFIG_DO_CORRECT, opt->do_correct);

  if (n_diffs > 1)
    g_settings_apply (settings);
}

/*
vi:ts=2:nowrap:ai:expandtab
*/
