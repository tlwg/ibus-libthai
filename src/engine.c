/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 *  Copyright (C) 2011 Theppitak Karoonboonyanan <thep@linux.thai.net>
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

#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include "engine.h"
#include "ibus_config.h"
#include "thaikb.h"
#include <thai/thcell.h>
#include <thai/thinp.h>
#include <glib.h>
#include <string.h>

typedef guchar tischar_t;

typedef struct _IBusLibThaiEngine IBusLibThaiEngine;
typedef struct _IBusLibThaiEngineClass IBusLibThaiEngineClass;

#define FALLBACK_BUFF_SIZE 4

struct _IBusLibThaiEngine
{
  IBusEngine parent;

  /* members */
  tischar_t  char_buff[FALLBACK_BUFF_SIZE];
  short      buff_tail;
  ThaiKBMap  kb_map;
  thstrict_t isc_mode;
  gboolean   do_correct;
};

struct _IBusLibThaiEngineClass
{
  IBusEngineClass parent;
};

static void ibus_libthai_engine_class_init (IBusLibThaiEngineClass *klass);
static void ibus_libthai_engine_init (IBusLibThaiEngine *libthai_engine);
static gboolean ibus_libthai_engine_process_key_event (IBusEngine *engine,
                                                       guint       keyval,
                                                       guint       keycode,
                                                       guint       modifiers);

/* Fallback functions */
static void
ibus_libthai_engine_forget_prev_chars (IBusLibThaiEngine *libthai_engine);
static void
ibus_libthai_engine_remember_prev_chars (IBusLibThaiEngine *libthai_engine,
                                         tischar_t new_char);

static thchar_t
ibus_libthai_engine_get_prev_char (IBusLibThaiEngine *libthai_engine);
static void
ibus_libthai_engine_get_prev_cell (IBusLibThaiEngine *libthai_engine,
                                   struct thcell_t *res);


/* Utility functions */
static gboolean
is_client_support_surrounding (IBusEngine *engine);

/* Global variables */
static IBusConfig *ibus_config = NULL;

void
ibus_libthai_init (IBusBus *bus)
{
  ibus_config = ibus_bus_get_config (bus);
}


GType
ibus_libthai_engine_get_type ()
{
  static GType type = 0;

  static const GTypeInfo type_info =
    {
      sizeof (IBusLibThaiEngineClass),
      (GBaseInitFunc)         NULL,
      (GBaseFinalizeFunc)     NULL,
      (GClassInitFunc)        ibus_libthai_engine_class_init,
      (GClassFinalizeFunc)    NULL,
      NULL,
      sizeof (IBusLibThaiEngine),
      0,
      (GInstanceInitFunc)     ibus_libthai_engine_init,
    };

  if (!type)
    {
      type = g_type_register_static (IBUS_TYPE_ENGINE,
                                     "IBusLibThaiEngine",
                                     &type_info,
                                     (GTypeFlags)0);
    }

  return type;
}

static void
ibus_libthai_engine_class_init (IBusLibThaiEngineClass *klass)
{
  IBusEngineClass *engine_class = IBUS_ENGINE_CLASS (klass);

  engine_class->process_key_event = ibus_libthai_engine_process_key_event;
}

static void
ibus_libthai_engine_init (IBusLibThaiEngine *libthai_engine)
{
  IBusLibThaiSetupOptions opt;

  ibus_libthai_engine_forget_prev_chars (libthai_engine);

  /* Read config */
  ibus_libthai_read_config (ibus_config, &opt);
  libthai_engine->kb_map = opt.thai_kb_map;
  libthai_engine->isc_mode = opt.isc_mode;
  libthai_engine->do_correct = opt.do_correct;
}

static gboolean
is_client_support_surrounding (IBusEngine *engine)
{
  return engine->client_capabilities & IBUS_CAP_SURROUNDING_TEXT;
}

static void
ibus_libthai_engine_forget_prev_chars (IBusLibThaiEngine *libthai_engine)
{
  memset (libthai_engine->char_buff, 0, FALLBACK_BUFF_SIZE);
  libthai_engine->buff_tail = 0;
}

static void
ibus_libthai_engine_remember_prev_chars (IBusLibThaiEngine *libthai_engine,
                                         tischar_t new_char)
{
  if (libthai_engine->buff_tail == FALLBACK_BUFF_SIZE)
    {
      memmove (libthai_engine->char_buff, libthai_engine->char_buff + 1,
               FALLBACK_BUFF_SIZE - 1);
      --libthai_engine->buff_tail;
    }
  libthai_engine->char_buff[libthai_engine->buff_tail++] = new_char;
}

static thchar_t
ibus_libthai_engine_get_prev_char (IBusLibThaiEngine *libthai_engine)
{
  thchar_t c;

  if (is_client_support_surrounding (IBUS_ENGINE (libthai_engine)))
    {
      IBusText *surrounding;
      guint     cursor_pos;
      guint     anchor_pos;
      const gchar *s;
      gchar    *tis_text = NULL;

      ibus_engine_get_surrounding_text (IBUS_ENGINE (libthai_engine),
                                        &surrounding, &cursor_pos, &anchor_pos);
      s = ibus_text_get_text (surrounding);
      cursor_pos = g_utf8_offset_to_pointer (s, cursor_pos) - s;
      while (*s)
        {
          const gchar *t;

          tis_text = g_convert (s, cursor_pos, "TIS-620", "UTF-8",
                                NULL, NULL, NULL);
          if (tis_text)
            break;

          t = g_utf8_next_char (s);
          cursor_pos -= (t - s);
          s = t;
        }
      if (tis_text)
        {
          gint char_index;

          char_index = g_utf8_pointer_to_offset (s, s + cursor_pos);
          c = tis_text[char_index - 1];
          g_free (tis_text);
        }
    }
  else
    {
      /* retrieve from the fallback buffer */
      c = libthai_engine->char_buff[libthai_engine->buff_tail - 1];
    }

  return c;
}

static void
ibus_libthai_engine_get_prev_cell (IBusLibThaiEngine *libthai_engine,
                                   struct thcell_t *res)
{
  th_init_cell (res);

  if (is_client_support_surrounding (IBUS_ENGINE (libthai_engine)))
    {
      IBusText *surrounding;
      guint     cursor_pos;
      guint     anchor_pos;
      const gchar *s;
      gchar    *tis_text = NULL;

      ibus_engine_get_surrounding_text (IBUS_ENGINE (libthai_engine),
                                        &surrounding, &cursor_pos, &anchor_pos);
      s = ibus_text_get_text (surrounding);
      cursor_pos = g_utf8_offset_to_pointer (s, cursor_pos) - s;
      while (*s)
        {
          const gchar *t;

          tis_text = g_convert (s, cursor_pos, "TIS-620", "UTF-8",
                                NULL, NULL, NULL);
          if (tis_text)
            break;

          t = g_utf8_next_char (s);
          cursor_pos -= (t - s);
          s = t;
        }
      if (tis_text)
        {
          gint char_index;

          char_index = g_utf8_pointer_to_offset (s, s + cursor_pos);
          th_prev_cell ((thchar_t *) tis_text, char_index, res, TRUE);
          g_free (tis_text);
        }
    }
  else
    {
      /* retrieve from the fallback buffer */
      th_prev_cell (libthai_engine->char_buff, libthai_engine->buff_tail,
                    res, TRUE);
    }
}

static gboolean
is_context_lost_key (guint keyval)
{
  return ((keyval & 0xFF00) == 0xFF00) &&
         (keyval == IBUS_BackSpace ||
          keyval == IBUS_Tab ||
          keyval == IBUS_Linefeed ||
          keyval == IBUS_Clear ||
          keyval == IBUS_Return ||
          keyval == IBUS_Pause ||
          keyval == IBUS_Scroll_Lock ||
          keyval == IBUS_Sys_Req ||
          keyval == IBUS_Escape ||
          keyval == IBUS_Delete ||
          /* IsCursorkey */
          (IBUS_Home <= keyval && keyval <= IBUS_Begin) ||
          /* IsKeypadKey, non-chars only */
          (IBUS_KP_Space <= keyval && keyval <= IBUS_KP_Delete) ||
          /* IsMiscFunctionKey */
          (IBUS_Select <= keyval && keyval <= IBUS_Break) ||
          /* IsFunctionKey */
          (IBUS_F1 <= keyval && keyval <= IBUS_F35));
}

static gboolean
is_context_intact_key (guint keyval)
{
  return (((keyval & 0xFF00) == 0xFF00) &&
          ( /* IsModifierKey */
           (IBUS_Shift_L <= keyval && keyval <= IBUS_Hyper_R) ||
           (keyval == IBUS_Mode_switch) ||
           (keyval == IBUS_Num_Lock))) ||
         (((keyval & 0xFE00) == 0xFE00) &&
          (IBUS_ISO_Lock <= keyval && keyval <= IBUS_ISO_Last_Group_Lock));
}

static tischar_t
keyval_to_tis (ThaiKBMap thai_kb_map, guint keyval)
{
  if (IBUS_space <= keyval && keyval <= IBUS_asciitilde)
    return thai_map_qwerty (thai_kb_map, keyval);

  if (IBUS_Thai_kokai <= keyval && keyval <= IBUS_Thai_lekkao)
    return (tischar_t)(keyval - IBUS_Thai_kokai) + 0xa1;

  if (0x01000e01 <= keyval && keyval <= 0x01000e5f)
    return (tischar_t)(keyval - 0x01000e01) + 0xa1;

  return 0;
}

static gboolean
ibus_libthai_engine_commit_chars (IBusLibThaiEngine *libthai_engine,
                                  tischar_t *s, gsize len)
{
  gchar    *utf8;
  IBusText *text;

  utf8 = g_convert ((gchar *) s, len, "UTF-8", "TIS-620", NULL, NULL, NULL);
  if (!utf8)
    return FALSE;

  text = ibus_text_new_from_string (utf8);
  g_free (utf8);

  ibus_engine_commit_text (IBUS_ENGINE (libthai_engine), text);

  return TRUE;
}

static gboolean
ibus_libthai_engine_process_key_event (IBusEngine *engine,
                                       guint       keyval,
                                       guint       keycode,
                                       guint       modifiers)
{
  IBusLibThaiEngine *libthai_engine = IBUS_LIBTHAI_ENGINE (engine);
  struct thcell_t context_cell;
  struct thinpconv_t conv;
  tischar_t new_char;

  if (modifiers & IBUS_RELEASE_MASK)
    return FALSE;

  if (modifiers & (IBUS_CONTROL_MASK | IBUS_MOD1_MASK)
      || is_context_lost_key (keyval))
    {
      ibus_libthai_engine_forget_prev_chars (libthai_engine);
      return FALSE;
    }
  if (0 == keyval || is_context_intact_key (keyval))
    {
      return FALSE;
    }

  new_char = keyval_to_tis (libthai_engine->kb_map, keyval);
  if (0 == new_char)
    return FALSE;

  /* No correction -> just reject or commit */
  if (!libthai_engine->do_correct)
    {
      thchar_t prev_char = ibus_libthai_engine_get_prev_char (libthai_engine);

      if (!th_isaccept (prev_char, new_char, libthai_engine->isc_mode))
        goto reject_char;

      return ibus_libthai_engine_commit_chars (libthai_engine, &new_char, 1);
    }

  ibus_libthai_engine_get_prev_cell (libthai_engine, &context_cell);
  if (!th_validate_leveled (context_cell, new_char, &conv,
                            libthai_engine->isc_mode))
    {
      goto reject_char;
    }

  if (conv.offset < 0)
    {
      /* Can't correct context, just fall back to rejection */
      if (!is_client_support_surrounding (engine))
        goto reject_char;

      ibus_engine_delete_surrounding_text (engine, conv.offset, -conv.offset);
    }
  ibus_libthai_engine_forget_prev_chars (libthai_engine);
  ibus_libthai_engine_remember_prev_chars (libthai_engine, new_char);

  return ibus_libthai_engine_commit_chars (libthai_engine,
                                           conv.conv,
                                           strlen((char *) conv.conv));

reject_char:
  /* gdk_beep (); */
  return TRUE;
}

/*
vi:ts=2:nowrap:ai:expandtab
*/
