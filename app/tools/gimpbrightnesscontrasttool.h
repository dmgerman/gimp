begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRIGHTNESS_CONTRAST_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRIGHTNESS_CONTRAST_TOOL_H__
define|#
directive|define
name|__GIMP_BRIGHTNESS_CONTRAST_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpimagemaptool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_BRIGHTNESS_CONTRAST_TOOL
define|#
directive|define
name|GIMP_TYPE_BRIGHTNESS_CONTRAST_TOOL
value|(gimp_brightness_contrast_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_BRIGHTNESS_CONTRAST_TOOL (obj)
define|#
directive|define
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_BRIGHTNESS_CONTRAST_TOOL, GimpBrightnessContrastTool))
end_define

begin_define
DECL|macro|GIMP_IS_BRIGHTNESS_CONTRAST_TOOL (obj)
define|#
directive|define
name|GIMP_IS_BRIGHTNESS_CONTRAST_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_BRIGHTNESS_CONTRAST_TOOL))
end_define

begin_define
DECL|macro|GIMP_BRIGHTNESS_CONTRAST_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_BRIGHTNESS_CONTRAST_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BRIGHTNESS_CONTRAST_TOOL, GimpBrightnessContrastToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_BRIGHTNESS_CONTRAST_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BRIGHTNESS_CONTRAST_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BRIGHTNESS_CONTRAST_TOOL))
end_define

begin_typedef
DECL|typedef|GimpBrightnessContrastTool
typedef|typedef
name|struct
name|_GimpBrightnessContrastTool
name|GimpBrightnessContrastTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBrightnessContrastToolClass
typedef|typedef
name|struct
name|_GimpBrightnessContrastToolClass
name|GimpBrightnessContrastToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBrightnessContrastTool
struct|struct
name|_GimpBrightnessContrastTool
block|{
DECL|member|parent_instance
name|GimpImageMapTool
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBrightnessContrastToolClass
struct|struct
name|_GimpBrightnessContrastToolClass
block|{
DECL|member|parent_class
name|GimpImageMapToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_brightness_contrast_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_brightness_contrast_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|brightness_contrast_dialog_hide
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BRIGHTNESS_CONTRAST_TOOL_H__  */
end_comment

end_unit

