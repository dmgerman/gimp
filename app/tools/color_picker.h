begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__COLOR_PICKER_H__
end_ifndef

begin_define
DECL|macro|__COLOR_PICKER_H__
define|#
directive|define
name|__COLOR_PICKER_H__
end_define

begin_include
include|#
directive|include
file|"tool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_COLOR_PICKER
define|#
directive|define
name|GIMP_TYPE_COLOR_PICKER
value|(gimp_color_picker_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_PICKER (obj)
define|#
directive|define
name|GIMP_COLOR_PICKER
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_COLOR_PICKER, GimpColorPicker))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_PICKER (obj)
define|#
directive|define
name|GIMP_IS_COLOR_PICKER
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_COLOR_PICKER))
end_define

begin_define
DECL|macro|GIMP_COLOR_PICKER_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_PICKER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_PICKER, GimpColorPickerClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_PICKER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_PICKER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_PICKER))
end_define

begin_typedef
DECL|typedef|GimpColorPicker
typedef|typedef
name|struct
name|_GimpColorPicker
name|GimpColorPicker
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorPickerClass
typedef|typedef
name|struct
name|_GimpColorPickerClass
name|GimpColorPickerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorPicker
struct|struct
name|_GimpColorPicker
block|{
DECL|member|parent_instance
name|GimpTool
name|parent_instance
decl_stmt|;
DECL|member|core
name|DrawCore
modifier|*
name|core
decl_stmt|;
comment|/*  Core select object  */
DECL|member|centerx
name|gint
name|centerx
decl_stmt|;
comment|/*  starting x coord    */
DECL|member|centery
name|gint
name|centery
decl_stmt|;
comment|/*  starting y coord    */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorPickerClass
struct|struct
name|_GimpColorPickerClass
block|{
DECL|member|parent_class
name|GimpToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
specifier|extern
name|gint
name|col_value
index|[
literal|5
index|]
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkType
name|gimp_color_picker_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpTool
modifier|*
name|gimp_color_picker_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|pick_color
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gboolean
name|sample_average
parameter_list|,
name|double
name|average_radius
parameter_list|,
name|gint
name|final
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __COLOR_PICKER_H__  */
end_comment

end_unit

