begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HUE_SATURATION_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HUE_SATURATION_TOOL_H__
define|#
directive|define
name|__GIMP_HUE_SATURATION_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpimagemaptool.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a4847ac0103
block|{
DECL|enumerator|ALL_HUES
name|ALL_HUES
block|,
DECL|enumerator|RED_HUES
name|RED_HUES
block|,
DECL|enumerator|YELLOW_HUES
name|YELLOW_HUES
block|,
DECL|enumerator|GREEN_HUES
name|GREEN_HUES
block|,
DECL|enumerator|CYAN_HUES
name|CYAN_HUES
block|,
DECL|enumerator|BLUE_HUES
name|BLUE_HUES
block|,
DECL|enumerator|MAGENTA_HUES
name|MAGENTA_HUES
DECL|typedef|HueRange
block|}
name|HueRange
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_HUE_SATURATION_TOOL
define|#
directive|define
name|GIMP_TYPE_HUE_SATURATION_TOOL
value|(gimp_hue_saturation_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_HUE_SATURATION_TOOL (obj)
define|#
directive|define
name|GIMP_HUE_SATURATION_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_HUE_SATURATION_TOOL, GimpHueSaturationTool))
end_define

begin_define
DECL|macro|GIMP_HUE_SATURATION_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_HUE_SATURATION_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_HUE_SATURATION_TOOL, GimpHueSaturationToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_HUE_SATURATION_TOOL (obj)
define|#
directive|define
name|GIMP_IS_HUE_SATURATION_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_HUE_SATURATION_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_HUE_SATURATION_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_HUE_SATURATION_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_HUE_SATURATION_TOOL))
end_define

begin_define
DECL|macro|GIMP_HUE_SATURATION_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_HUE_SATURATION_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_HUE_SATURATION_TOOL, GimpHueSaturationToolClass))
end_define

begin_typedef
DECL|typedef|GimpHueSaturationTool
typedef|typedef
name|struct
name|_GimpHueSaturationTool
name|GimpHueSaturationTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHueSaturationToolClass
typedef|typedef
name|struct
name|_GimpHueSaturationToolClass
name|GimpHueSaturationToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpHueSaturationTool
struct|struct
name|_GimpHueSaturationTool
block|{
DECL|member|parent_instance
name|GimpImageMapTool
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpHueSaturationToolClass
struct|struct
name|_GimpHueSaturationToolClass
block|{
DECL|member|parent_class
name|GimpImageMapToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|HueSaturationDialog
typedef|typedef
name|struct
name|_HueSaturationDialog
name|HueSaturationDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_HueSaturationDialog
struct|struct
name|_HueSaturationDialog
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|hue_partition_da
name|GtkWidget
modifier|*
name|hue_partition_da
index|[
literal|6
index|]
decl_stmt|;
DECL|member|hue_data
name|GtkAdjustment
modifier|*
name|hue_data
decl_stmt|;
DECL|member|lightness_data
name|GtkAdjustment
modifier|*
name|lightness_data
decl_stmt|;
DECL|member|saturation_data
name|GtkAdjustment
modifier|*
name|saturation_data
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|image_map
name|ImageMap
modifier|*
name|image_map
decl_stmt|;
DECL|member|hue
name|gdouble
name|hue
index|[
literal|7
index|]
decl_stmt|;
DECL|member|lightness
name|gdouble
name|lightness
index|[
literal|7
index|]
decl_stmt|;
DECL|member|saturation
name|gdouble
name|saturation
index|[
literal|7
index|]
decl_stmt|;
DECL|member|hue_partition
name|HueRange
name|hue_partition
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_hue_saturation_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_hue_saturation_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|hue_saturation_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|hue_saturation
parameter_list|(
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|hue_saturation_calculate_transfers
parameter_list|(
name|HueSaturationDialog
modifier|*
name|hsd
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __HUE_SATURATION_H__  */
end_comment

end_unit

