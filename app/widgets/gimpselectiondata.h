begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SELECTION_DATA_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SELECTION_DATA_H__
define|#
directive|define
name|__GIMP_SELECTION_DATA_H__
end_define

begin_comment
comment|/*  uri list  */
end_comment

begin_function_decl
name|void
name|gimp_selection_data_set_uris
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|GdkAtom
name|atom
parameter_list|,
name|GList
modifier|*
name|uris
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_selection_data_get_uris
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  color  */
end_comment

begin_function_decl
name|void
name|gimp_selection_data_set_color
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|GdkAtom
name|atom
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_data_get_color
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  svg  */
end_comment

begin_function_decl
name|void
name|gimp_selection_data_set_svg
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|GdkAtom
name|atom
parameter_list|,
specifier|const
name|gchar
modifier|*
name|data
parameter_list|,
name|gint
name|data_length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_selection_data_get_svg
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|gint
modifier|*
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  image  */
end_comment

begin_function_decl
name|void
name|gimp_selection_data_set_image
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|GdkAtom
name|atom
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_selection_data_get_image
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  item  */
end_comment

begin_function_decl
name|void
name|gimp_selection_data_set_item
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|GdkAtom
name|atom
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|gimp_selection_data_get_item
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  various data  */
end_comment

begin_function_decl
name|void
name|gimp_selection_data_set_viewable
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|GdkAtom
name|atom
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrush
modifier|*
name|gimp_selection_data_get_brush
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPattern
modifier|*
name|gimp_selection_data_get_pattern
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpGradient
modifier|*
name|gimp_selection_data_get_gradient
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPalette
modifier|*
name|gimp_selection_data_get_palette
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpFont
modifier|*
name|gimp_selection_data_get_font
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBuffer
modifier|*
name|gimp_selection_data_get_buffer
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImagefile
modifier|*
name|gimp_selection_data_get_imagefile
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpTemplate
modifier|*
name|gimp_selection_data_get_template
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpToolInfo
modifier|*
name|gimp_selection_data_get_tool
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SELECTION_DATA_H__ */
end_comment

end_unit

