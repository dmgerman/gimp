begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__INTERFACE_H__
end_ifndef

begin_define
DECL|macro|__INTERFACE_H__
define|#
directive|define
name|__INTERFACE_H__
end_define

begin_include
include|#
directive|include
file|"toolsF.h"
end_include

begin_include
include|#
directive|include
file|"gdisplayF.h"
end_include

begin_comment
comment|/*  function declarations  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|create_pixmap_widget
parameter_list|(
name|GdkWindow
modifier|*
name|parent
parameter_list|,
name|gchar
modifier|*
modifier|*
name|data
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|create_toolbox
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|toolbox_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|toolbox_raise_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|create_display_shell
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|gint
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __INTERFACE_H__ */
end_comment

end_unit

