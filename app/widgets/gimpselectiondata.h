begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
name|gimp_selection_data_set_uri_list
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
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
name|gimp_selection_data_get_uri_list
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
comment|/*  stream (svg/png)  */
end_comment

begin_function_decl
name|void
name|gimp_selection_data_set_stream
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
specifier|const
name|guchar
modifier|*
name|stream
parameter_list|,
name|gsize
name|stream_length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|guchar
modifier|*
name|gimp_selection_data_get_stream
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|gsize
modifier|*
name|stream_length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  curve  */
end_comment

begin_function_decl
name|void
name|gimp_selection_data_set_curve
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|GimpCurve
modifier|*
name|curve
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCurve
modifier|*
name|gimp_selection_data_get_curve
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
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
name|GimpImage
modifier|*
name|image
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
comment|/*  component  */
end_comment

begin_function_decl
name|void
name|gimp_selection_data_set_component
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_selection_data_get_component
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpChannelType
modifier|*
name|channel
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
name|gimp_selection_data_set_object
parameter_list|(
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|GimpObject
modifier|*
name|object
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
name|gimp_selection_data_get_tool_info
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

