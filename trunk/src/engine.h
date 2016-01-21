/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 *  Copyright (C) 2011 Theppitak Karoonboonyanan <theppitak@gmail.com>
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

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <ibus.h>

#define IBUS_TYPE_LIBTHAI_ENGINE  (ibus_libthai_engine_get_type())
#define IBUS_LIBTHAI_ENGINE(obj) \
          (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
                                       IBUS_TYPE_LIBTHAI_ENGINE, \
                                       IBusLibThaiEngine))
#define IBUS_LIBTHAI_ENGINE_CLASS(klass) \
          (G_TYPE_CHECK_CLASS_CAST ((klass), \
                                    IBUS_TYPE_LIBTHAI_ENGINE, \
                                    IBusLibThaiEngineClass))
#define IBUS_IS_LIBTHAI_ENGINE(obj) \
          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
                                       IBUS_TYPE_LIBTHAI_ENGINE))
#define IBUS_IS_LIBTHAI_ENGINE_CLASS(klass) \
          (G_TYPE_CHECK_CLASS_TYPE ((klass), \
                                    IBUS_TYPE_LIBTHAI_ENGINE))
#define IBUS_LIBTHAI_ENGINE_GET_CLASS(obj) \
          (G_TYPE_INSTANCE_GET_CLASS ((obj), \
                                      IBUS_TYPE_LIBTHAI_ENGINE, \
                                      IBusLibThaiEngineClass))

GType   ibus_libthai_engine_get_type ();

void ibus_libthai_init (IBusBus *bus);

#endif /* __ENGINE_H__ */

/*
vi:ts=2:nowrap:ai:expandtab
*/
