begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VIEWABLE_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VIEWABLE_BOX_H__
define|#
directive|define
name|__GIMP_VIEWABLE_BOX_H__
end_define

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_brush_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_pattern_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_gradient_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|reverse_prop
parameter_list|,
name|gint
name|scacing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_palette_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_font_box_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|spacing
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_VIEWABLE_BOX_H__ */
end_comment

end_unit

