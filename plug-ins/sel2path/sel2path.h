begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for the GIMP.  *  * Plugin to convert a selection to a path.  *  * Copyright (C) 1999 Andy Thomas  alt@gimp.org  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *   */
end_comment

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_function_decl
name|guchar
name|sel_pixel_value
parameter_list|(
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|sel_pixel_is_white
parameter_list|(
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|sel_get_width
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|sel_get_height
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|sel_valid_pixel
parameter_list|(
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|reset_adv_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|dialog_create_selection_area
parameter_list|(
name|SELVALS
modifier|*
parameter_list|)
function_decl|;
end_function_decl

end_unit

