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

static void
set_default_config (IBusLibThaiSetupOptions *opt)
{
  opt->thai_kb_map = THAI_KB_KETMANEE;
  opt->isc_mode = ISC_BASICCHECK;
  opt->do_correct = TRUE;
}

void
ibus_libthai_read_config (IBusConfig *config,
                          IBusLibThaiSetupOptions *opt)
{
  GVariant *val;

  set_default_config (opt);

  /* Get keyboard layout */
  val = ibus_config_get_value (config, CONFIG_SECTION, CONFIG_KB_LAYOUT);
  if (val)
    {
      gint32    v;
      g_variant_get (val, "i", &v);
      opt->thai_kb_map = v;
      g_variant_unref (val);
    }

  /* Get input sequence check mode */
  val = ibus_config_get_value (config, CONFIG_SECTION, CONFIG_ISC_MODE);
  if (val)
    {
      gint32    v;
      g_variant_get (val, "i", &v);
      opt->isc_mode = v;
      g_variant_unref (val);
    }

  /* Get input sequence correction flag */
  val = ibus_config_get_value (config, CONFIG_SECTION, CONFIG_DO_CORRECT);
  if (val)
    {
      gboolean  b;
      g_variant_get (val, "b", &b);
      opt->do_correct = b;
      g_variant_unref (val);
    }
}

void
ibus_libthai_write_config (IBusConfig *config,
                           const IBusLibThaiSetupOptions *opt)
{
  GVariant *val;

  /* Set keyboard layout */
  val = g_variant_new_int32 (opt->thai_kb_map);
  ibus_config_set_value (config, CONFIG_SECTION, CONFIG_KB_LAYOUT, val);

  /* Set input sequence check mode */
  val = g_variant_new_int32 (opt->isc_mode);
  ibus_config_set_value (config, CONFIG_SECTION, CONFIG_ISC_MODE, val);

  /* Set input sequence correction flag */
  val = g_variant_new_boolean (opt->do_correct);
  ibus_config_set_value (config, CONFIG_SECTION, CONFIG_DO_CORRECT, val);
}

gboolean
force_engine_to_reload_config ()
{
  return system ("ibus-daemon -xrd") == 0;
}


/*
vi:ts=2:nowrap:ai:expandtab
*/
