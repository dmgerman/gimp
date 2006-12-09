begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * pygimp-intl.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PYGIMP_INTL_H__
end_ifndef

begin_define
DECL|macro|__PYGIMP_INTL_H__
define|#
directive|define
name|__PYGIMP_INTL_H__
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|GETTEXT_PACKAGE
end_ifndef

begin_error
error|#
directive|error
literal|"config.h must be included prior to pygimp-intl.h"
end_error

begin_endif
endif|#
directive|endif
end_endif

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
value|dgettext (GETTEXT_PACKAGE "-python", String)
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
value|dgettext (GETTEXT_PACKAGE "-python", String)
end_define

begin_undef
undef|#
directive|undef
name|ngettext
end_undef

begin_define
DECL|macro|ngettext (String1,String2,number)
define|#
directive|define
name|ngettext
parameter_list|(
name|String1
parameter_list|,
name|String2
parameter_list|,
name|number
parameter_list|)
value|dngettext (GETTEXT_PACKAGE "-python", String1, String2, number)
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PYGIMP_INTL_H__ */
end_comment

end_unit

