begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpintl.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPINTL_H__
end_ifndef

begin_define
DECL|macro|__GIMPINTL_H__
define|#
directive|define
name|__GIMPINTL_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<locale.h>
end_include

begin_comment
comment|/* Copied from gnome-i18n.h by Tom Tromey<tromey@creche.cygnus.com>  * Heavily modified by Daniel Egger<Daniel.Egger@t-online.de>  * So be sure to hit me instead of him if something is wrong here  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|LOCALEDIR
end_ifndef

begin_define
DECL|macro|LOCALEDIR
define|#
directive|define
name|LOCALEDIR
value|g_strconcat (gimp_data_directory (), \ 			       G_DIR_SEPARATOR_S, \ 			       "locale", \ 			       NULL)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|ENABLE_NLS
end_ifdef

begin_include
include|#
directive|include
file|<libintl.h>
end_include

begin_define
DECL|macro|_ (String)
define|#
directive|define
name|_
parameter_list|(
name|String
parameter_list|)
value|gettext (String)
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|gettext_noop
end_ifdef

begin_define
DECL|macro|N_ (String)
define|#
directive|define
name|N_
parameter_list|(
name|String
parameter_list|)
value|gettext_noop (String)
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|N_ (String)
define|#
directive|define
name|N_
parameter_list|(
name|String
parameter_list|)
value|(String)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* Stubs that do something close enough.  */
end_comment

begin_define
DECL|macro|textdomain (String)
define|#
directive|define
name|textdomain
parameter_list|(
name|String
parameter_list|)
value|(String)
end_define

begin_define
DECL|macro|gettext (String)
define|#
directive|define
name|gettext
parameter_list|(
name|String
parameter_list|)
value|(String)
end_define

begin_define
DECL|macro|dgettext (Domain,Message)
define|#
directive|define
name|dgettext
parameter_list|(
name|Domain
parameter_list|,
name|Message
parameter_list|)
value|(Message)
end_define

begin_define
DECL|macro|dcgettext (Domain,Message,Type)
define|#
directive|define
name|dcgettext
parameter_list|(
name|Domain
parameter_list|,
name|Message
parameter_list|,
name|Type
parameter_list|)
value|(Message)
end_define

begin_define
DECL|macro|bindtextdomain (Domain,Directory)
define|#
directive|define
name|bindtextdomain
parameter_list|(
name|Domain
parameter_list|,
name|Directory
parameter_list|)
value|(Domain)
end_define

begin_define
DECL|macro|_ (String)
define|#
directive|define
name|_
parameter_list|(
name|String
parameter_list|)
value|(String)
end_define

begin_define
DECL|macro|N_ (String)
define|#
directive|define
name|N_
parameter_list|(
name|String
parameter_list|)
value|(String)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|INIT_LOCALE (domain)
define|#
directive|define
name|INIT_LOCALE
parameter_list|(
name|domain
parameter_list|)
value|G_STMT_START{	\ 	gtk_set_locale ();			\ 	setlocale (LC_NUMERIC, "C");		\ 	bindtextdomain (domain, LOCALEDIR);	\ 	textdomain (domain);			\ 				}G_STMT_END
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPINTL_H__ */
end_comment

end_unit

