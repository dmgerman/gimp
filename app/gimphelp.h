begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphelp.h  * Copyright (C) 1999-2000 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HELP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HELP_H__
define|#
directive|define
name|__GIMP_HELP_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimphelpui.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a0d49ef0103
block|{
DECL|enumerator|HELP_BROWSER_GIMP
name|HELP_BROWSER_GIMP
block|,
DECL|enumerator|HELP_BROWSER_NETSCAPE
name|HELP_BROWSER_NETSCAPE
block|}
enum|;
end_enum

begin_comment
comment|/*  the main help function  */
end_comment

begin_function_decl
name|void
name|gimp_help
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_HELP_H__ */
end_comment

end_unit

