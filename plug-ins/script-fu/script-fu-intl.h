begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * script-fu-intl.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SCRIPT_FU_INTL_H__
end_ifndef

begin_define
DECL|macro|__SCRIPT_FU_INTL_H__
define|#
directive|define
name|__SCRIPT_FU_INTL_H__
end_define

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_LC_MESSAGES
end_ifdef

begin_define
DECL|macro|INIT_I18N ()
define|#
directive|define
name|INIT_I18N
parameter_list|()
value|G_STMT_START{			\   setlocale(LC_MESSAGES, ""); 				\   bindtextdomain("gimp-libgimp", LOCALEDIR);            \   bindtextdomain("gimp-script-fu", LOCALEDIR);	        \   textdomain("gimp-script-fu");			        \   			}G_STMT_END
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|INIT_I18N ()
define|#
directive|define
name|INIT_I18N
parameter_list|()
value|G_STMT_START{			\   bindtextdomain("gimp-libgimp", LOCALEDIR);            \   bindtextdomain("gimp-script-fu", LOCALEDIR);	        \   textdomain("gimp-script-fu");                         \   			}G_STMT_END
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|INIT_I18N_UI ()
define|#
directive|define
name|INIT_I18N_UI
parameter_list|()
value|G_STMT_START{	\   gtk_set_locale();			\   setlocale (LC_NUMERIC, "C");		\   INIT_I18N();				\ 			}G_STMT_END
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __SCRIPT_FU_INTL_H__ */
end_comment

end_unit

