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

#include <libintl.h>
#include "dlg_setup.h"

#define _(string) gettext(string)

#define WIDGET_MARGINS 12

GtkWidget *
ibus_libthai_setup_dialog_new ()
{
  GtkWidget *main_dlg;
  GtkWidget *main_vbox;
  GtkWidget *widget;
  GtkWidget *vbox;
  char      *markup;
  GtkRadioButton *last_radio;

  /* Create main window */
  main_dlg = gtk_dialog_new_with_buttons (_("IBus LibThai Preferences"),
                                          NULL, GTK_DIALOG_MODAL,
                                          _("_Cancel"), GTK_RESPONSE_CANCEL,
                                          _("_OK"), GTK_RESPONSE_OK,
                                          NULL);
  /* Get the top level content vbox */
  main_vbox = gtk_dialog_get_content_area (GTK_DIALOG (main_dlg));
  gtk_widget_set_margin_top (GTK_WIDGET (main_vbox), WIDGET_MARGINS);
  gtk_widget_set_margin_start (GTK_WIDGET (main_vbox), WIDGET_MARGINS);

  /* Keyboard Layout section label */
  widget = gtk_label_new (NULL);
  markup = g_markup_printf_escaped ("<b>%s</b>", _("Keyboard layout:"));
  gtk_label_set_markup (GTK_LABEL (widget), markup);
  g_free (markup);
  gtk_label_set_xalign (GTK_LABEL (widget), 0);
  gtk_label_set_yalign (GTK_LABEL (widget), 0.5);
  gtk_widget_set_margin_end (widget, WIDGET_MARGINS);
  gtk_widget_show (widget);
  gtk_box_pack_start (GTK_BOX (main_vbox), widget, TRUE, FALSE, 0);

  /* Keyboard layout vbox for radio buttons */
  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_margin_start (vbox, WIDGET_MARGINS);
  gtk_widget_set_margin_end (vbox, WIDGET_MARGINS);
  gtk_widget_show (vbox);
  gtk_box_pack_start (GTK_BOX (main_vbox), vbox, TRUE, TRUE, 0);

  /* - Ketmanee keyboard layout */
  widget = gtk_radio_button_new_with_mnemonic (NULL, _("_Ketmanee"));
  gtk_widget_set_tooltip_text (
      widget,
      _("The traditional typewriter layout, the most "
      "popular one in the market.")
  );
  gtk_widget_show (widget);
  gtk_box_pack_start (GTK_BOX (vbox), widget, TRUE, FALSE, 0);
  last_radio = GTK_RADIO_BUTTON (widget);

  g_object_set_data (G_OBJECT (main_dlg), "ketmanee_radio", widget);

  /* - TIS-820.2538 keyboard layout */
  widget = gtk_radio_button_new_with_mnemonic_from_widget (last_radio,
                                                           _("_TIS-820.2538"));
  gtk_widget_set_tooltip_text (
    widget,
    _("National standard layout derived from Ketmanee, "
    "with some extra characters.")
  );
  gtk_widget_show (widget);
  gtk_box_pack_start (GTK_BOX (vbox), widget, TRUE, FALSE, 0);
  last_radio = GTK_RADIO_BUTTON (widget);

  g_object_set_data (G_OBJECT (main_dlg), "tis_radio", widget);

  /* - Pattachote keyboard layout */
  widget = gtk_radio_button_new_with_mnemonic_from_widget (last_radio,
                                                           _("_Pattachote"));
  gtk_widget_set_tooltip_text (
      widget,
      _("Keyboard layout designed by Sarit Pattachote "
      "from a statistical research.")
  );
  gtk_widget_show (widget);
  gtk_box_pack_start (GTK_BOX (vbox), widget, TRUE, FALSE, 0);

  g_object_set_data (G_OBJECT (main_dlg), "pattachote_radio", widget);

  /* - Manoonchai keyboard layout */
  widget = gtk_radio_button_new_with_mnemonic_from_widget (last_radio,
                                                           _("_Manoonchai"));
  gtk_widget_set_tooltip_text (
      widget,
      _("Keyboard layout designed by Manassarn Manoonchai "
      "using AI optimization based on contemporary documents.")
  );
  gtk_widget_show (widget);
  gtk_box_pack_start (GTK_BOX (vbox), widget, TRUE, FALSE, 0);

  g_object_set_data (G_OBJECT (main_dlg), "manoonchai_radio", widget);

  /* Input Sequence Check section label */
  widget = gtk_label_new (NULL);
  markup = g_markup_printf_escaped ("<b>%s</b>",
                                    _("Input sequence check mode:"));
  gtk_label_set_markup (GTK_LABEL (widget), markup);
  g_free (markup);
  gtk_label_set_xalign (GTK_LABEL (widget), 0);
  gtk_label_set_yalign (GTK_LABEL (widget), 0.5);
  gtk_widget_set_margin_end (widget, WIDGET_MARGINS);
  gtk_widget_show (widget);
  gtk_box_pack_start (GTK_BOX (main_vbox), widget, TRUE, FALSE, 0);

  /* Input Sequence Check vbox for radio buttons */
  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_margin_start (vbox, WIDGET_MARGINS);
  gtk_widget_set_margin_end (vbox, WIDGET_MARGINS);
  gtk_widget_show (vbox);
  gtk_box_pack_start (GTK_BOX (main_vbox), vbox, TRUE, TRUE, 0);

  /* - "No Check" choice */
  widget = gtk_radio_button_new_with_mnemonic (NULL, _("_No Check"));
  gtk_widget_set_tooltip_text (
    widget,
    _("Let all key sequences pass through.")
  );
  gtk_widget_show (widget);
  gtk_box_pack_start (GTK_BOX (vbox), widget, TRUE, FALSE, 0);
  last_radio = GTK_RADIO_BUTTON (widget);

  g_object_set_data (G_OBJECT (main_dlg), "no_check_radio", widget);

  /* - "Basic Check" choice */
  widget = gtk_radio_button_new_with_mnemonic_from_widget (last_radio,
                                                           _("_Basic Check"));
  gtk_widget_set_tooltip_text (
    widget,
    _("Check using basic rule, just to guarantee "
    "character order to be suitable for display.")
  );
  gtk_widget_show (widget);
  gtk_box_pack_start (GTK_BOX (vbox), widget, TRUE, FALSE, 0);
  last_radio = GTK_RADIO_BUTTON (widget);

  g_object_set_data (G_OBJECT (main_dlg), "basic_check_radio", widget);

  /* - "Strict Check" choice */
  widget = gtk_radio_button_new_with_mnemonic_from_widget (last_radio,
                                                           _("_Strict Check"));
  gtk_widget_set_tooltip_text (
    widget,
    _("Check using more strict orthographical rules.")
  );
  gtk_widget_show (widget);
  gtk_box_pack_start (GTK_BOX (vbox), widget, TRUE, FALSE, 0);

  g_object_set_data (G_OBJECT (main_dlg), "strict_check_radio", widget);

  /* "Correct input sequences" check box */
  widget = gtk_check_button_new_with_mnemonic (_("_Correct input sequences"));
  gtk_widget_set_tooltip_text (
    widget,
    _("Also try to correct wrong input sequences.")
  );
  gtk_widget_show (widget);
  gtk_widget_set_margin_end (widget, WIDGET_MARGINS);
  gtk_box_pack_end (GTK_BOX (main_vbox), widget, TRUE, FALSE, 0);

  g_object_set_data (G_OBJECT (main_dlg), "correct_input_checkbox", widget);

  return main_dlg;
}

void
ibus_libthai_setup_set_values (const GtkDialog *dlg,
                               const IBusLibThaiSetupOptions *opt)
{
  GtkWidget *widget;

  /* Set current keyboard layout value */
  switch (opt->thai_kb_map)
    {
      case THAI_KB_MANOONCHAI:
        widget = g_object_get_data (G_OBJECT (dlg), "manoonchai_radio");
        break;
      case THAI_KB_PATTACHOTE:
        widget = g_object_get_data (G_OBJECT (dlg), "pattachote_radio");
        break;
      case THAI_KB_TIS820_2538:
        widget = g_object_get_data (G_OBJECT (dlg), "tis_radio");
        break;
      case THAI_KB_KETMANEE:
      default:
        widget = g_object_get_data (G_OBJECT (dlg), "ketmanee_radio");
        break;
    }
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);

  /* Set input sequence check value */
  switch (opt->isc_mode)
    {
      case ISC_PASSTHROUGH:
        widget = g_object_get_data (G_OBJECT (dlg), "no_check_radio");
        break;
      case ISC_STRICT:
        widget = g_object_get_data (G_OBJECT (dlg), "strict_check_radio");
        break;
      case ISC_BASICCHECK:
      default:
        widget = g_object_get_data (G_OBJECT (dlg), "basic_check_radio");
        break;
    }
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);

  /* Set input sequence correction flag */
  widget = g_object_get_data (G_OBJECT (dlg), "correct_input_checkbox");
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), opt->do_correct);
}

void
ibus_libthai_setup_get_values (const GtkDialog *dlg,
                               IBusLibThaiSetupOptions *opt)
{
  GtkWidget *widget;

  /* Check for current keyboard layout value */
  widget = g_object_get_data (G_OBJECT (dlg), "manoonchai_radio");
  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
    {
      opt->thai_kb_map = THAI_KB_MANOONCHAI;
      goto kb_map_done;
    }
  widget = g_object_get_data (G_OBJECT (dlg), "pattachote_radio");
  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
    {
      opt->thai_kb_map = THAI_KB_PATTACHOTE;
      goto kb_map_done;
    }
  widget = g_object_get_data (G_OBJECT (dlg), "tis_radio");
  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
    {
      opt->thai_kb_map = THAI_KB_TIS820_2538;
      goto kb_map_done;
    }
  opt->thai_kb_map = THAI_KB_KETMANEE;

kb_map_done:
  /* Check for input sequence check value */
  widget = g_object_get_data (G_OBJECT (dlg), "no_check_radio");
  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
    {
      opt->isc_mode = ISC_PASSTHROUGH;
      goto isc_mode_done;
    }
  widget = g_object_get_data (G_OBJECT (dlg), "strict_check_radio");
  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
    {
      opt->isc_mode = ISC_STRICT;
      goto isc_mode_done;
    }
  opt->isc_mode = ISC_BASICCHECK;

isc_mode_done:
  /* Check for input sequence correction flag */
  widget = g_object_get_data (G_OBJECT (dlg), "correct_input_checkbox");
  opt->do_correct = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget));
}

/*
vi:ts=2:nowrap:ai:expandtab
*/
