begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * libgimp-intl.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__LIBGIMP_INTL_H__
end_ifndef

begin_define
DECL|macro|__LIBGIMP_INTL_H__
define|#
directive|define
name|__LIBGIMP_INTL_H__
end_define

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
value|dgettext ("gimp-libgimp", String)
end_define

begin_undef
undef|#
directive|undef
name|gettext
end_undef

begin_define
DECL|macro|gettext (String)
define|#
directive|define
name|gettext
parameter_list|(
name|String
parameter_list|)
value|dgettext ("gimp-libgimp", String)
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
value|dgettext_noop ("gimp-libgimp", String)
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __LIBGIMP_INTL_H__ */
end_comment

end_unit

