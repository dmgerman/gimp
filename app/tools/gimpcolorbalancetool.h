begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_BALANCE_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_BALANCE_DIALOG_H__
define|#
directive|define
name|__GIMP_COLOR_BALANCE_DIALOG_H__
end_define

begin_include
include|#
directive|include
file|"gimpimagemaptool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_COLOR_BALANCE_TOOL
define|#
directive|define
name|GIMP_TYPE_COLOR_BALANCE_TOOL
value|(gimp_color_balance_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_BALANCE_TOOL (obj)
define|#
directive|define
name|GIMP_COLOR_BALANCE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_BALANCE_TOOL, GimpColorBalanceTool))
end_define

begin_define
DECL|macro|GIMP_COLOR_BALANCE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_BALANCE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_BALANCE_TOOL, GimpColorBalanceToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_BALANCE_TOOL (obj)
define|#
directive|define
name|GIMP_IS_COLOR_BALANCE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_BALANCE_TOOL))
end_define

begin_define
DECL|macro|GIMP_COLOR_BALANCE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_BALANCE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_BALANCE_TOOL, GimpColorBalanceToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_BALANCE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_BALANCE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_BALANCE_TOOL))
end_define

begin_define
DECL|macro|GIMP_COLOR_BALANCE_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_BALANCE_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_BALANCE_TOOL, GimpColorBalanceToolClass))
end_define

begin_typedef
DECL|typedef|GimpColorBalanceTool
typedef|typedef
name|struct
name|_GimpColorBalanceTool
name|GimpColorBalanceTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorBalanceToolClass
typedef|typedef
name|struct
name|_GimpColorBalanceToolClass
name|GimpColorBalanceToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorBalanceTool
struct|struct
name|_GimpColorBalanceTool
block|{
DECL|member|parent_instance
name|GimpImageMapTool
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorBalanceToolClass
struct|struct
name|_GimpColorBalanceToolClass
block|{
DECL|member|parent_class
name|GimpImageMapToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|ColorBalanceDialog
typedef|typedef
name|struct
name|_ColorBalanceDialog
name|ColorBalanceDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_ColorBalanceDialog
struct|struct
name|_ColorBalanceDialog
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|cyan_red_data
name|GtkAdjustment
modifier|*
name|cyan_red_data
decl_stmt|;
DECL|member|magenta_green_data
name|GtkAdjustment
modifier|*
name|magenta_green_data
decl_stmt|;
DECL|member|yellow_blue_data
name|GtkAdjustment
modifier|*
name|yellow_blue_data
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
DECL|member|cyan_red
name|gdouble
name|cyan_red
index|[
literal|3
index|]
decl_stmt|;
DECL|member|magenta_green
name|gdouble
name|magenta_green
index|[
literal|3
index|]
decl_stmt|;
DECL|member|yellow_blue
name|gdouble
name|yellow_blue
index|[
literal|3
index|]
decl_stmt|;
DECL|member|r_lookup
name|guchar
name|r_lookup
index|[
literal|256
index|]
decl_stmt|;
DECL|member|g_lookup
name|guchar
name|g_lookup
index|[
literal|256
index|]
decl_stmt|;
DECL|member|b_lookup
name|guchar
name|b_lookup
index|[
literal|256
index|]
decl_stmt|;
DECL|member|preserve_luminosity
name|gboolean
name|preserve_luminosity
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|member|application_mode
name|GimpTransferMode
name|application_mode
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_color_balance_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GType
name|gimp_color_balance_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_balance_dialog_hide
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_balance
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
name|color_balance_create_lookup_tables
parameter_list|(
name|ColorBalanceDialog
modifier|*
name|cbd
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_COLOR_BALANCE_GIMP_H__  */
end_comment

end_unit

