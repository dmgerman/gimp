begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"base/colorize.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimpcolorizeconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorizetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagemapoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|SLIDER_WIDTH
define|#
directive|define
name|SLIDER_WIDTH
value|200
end_define

begin_define
DECL|macro|SPINNER_WIDTH
define|#
directive|define
name|SPINNER_WIDTH
value|4
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_colorize_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_colorize_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GeglNode
modifier|*
name|gimp_colorize_tool_get_operation
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|,
name|GObject
modifier|*
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_colorize_tool_map
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_colorize_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_colorize_tool_config_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorize_hue_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorize_saturation_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorize_lightness_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpColorizeTool,gimp_colorize_tool,GIMP_TYPE_IMAGE_MAP_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpColorizeTool
argument_list|,
argument|gimp_colorize_tool
argument_list|,
argument|GIMP_TYPE_IMAGE_MAP_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_colorize_tool_parent_class
end_define

begin_function
name|void
name|gimp_colorize_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_COLORIZE_TOOL
argument_list|,
name|GIMP_TYPE_IMAGE_MAP_OPTIONS
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|"gimp-colorize-tool"
argument_list|,
name|_
argument_list|(
literal|"Colorize"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Colorize Tool: Colorize the image"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Colori_ze..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_COLORIZE
argument_list|,
name|GIMP_STOCK_TOOL_COLORIZE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_class_init (GimpColorizeToolClass * klass)
name|gimp_colorize_tool_class_init
parameter_list|(
name|GimpColorizeToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpToolClass
modifier|*
name|tool_class
init|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpImageMapToolClass
modifier|*
name|im_tool_class
init|=
name|GIMP_IMAGE_MAP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_colorize_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_colorize_tool_initialize
expr_stmt|;
name|im_tool_class
operator|->
name|shell_desc
operator|=
name|_
argument_list|(
literal|"Colorize the Image"
argument_list|)
expr_stmt|;
name|im_tool_class
operator|->
name|settings_name
operator|=
literal|"colorize"
expr_stmt|;
name|im_tool_class
operator|->
name|import_dialog_title
operator|=
name|_
argument_list|(
literal|"Import Colorize Settings"
argument_list|)
expr_stmt|;
name|im_tool_class
operator|->
name|export_dialog_title
operator|=
name|_
argument_list|(
literal|"Export Colorize Settings"
argument_list|)
expr_stmt|;
name|im_tool_class
operator|->
name|get_operation
operator|=
name|gimp_colorize_tool_get_operation
expr_stmt|;
name|im_tool_class
operator|->
name|map
operator|=
name|gimp_colorize_tool_map
expr_stmt|;
name|im_tool_class
operator|->
name|dialog
operator|=
name|gimp_colorize_tool_dialog
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_init (GimpColorizeTool * col_tool)
name|gimp_colorize_tool_init
parameter_list|(
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
block|{
name|GimpImageMapTool
modifier|*
name|im_tool
init|=
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|col_tool
argument_list|)
decl_stmt|;
name|col_tool
operator|->
name|colorize
operator|=
name|g_slice_new0
argument_list|(
name|Colorize
argument_list|)
expr_stmt|;
name|colorize_init
argument_list|(
name|col_tool
operator|->
name|colorize
argument_list|)
expr_stmt|;
name|im_tool
operator|->
name|apply_func
operator|=
operator|(
name|GimpImageMapApplyFunc
operator|)
name|colorize
expr_stmt|;
name|im_tool
operator|->
name|apply_data
operator|=
name|col_tool
operator|->
name|colorize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_finalize (GObject * object)
name|gimp_colorize_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorizeTool
modifier|*
name|col_tool
init|=
name|GIMP_COLORIZE_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_slice_free
argument_list|(
name|Colorize
argument_list|,
name|col_tool
operator|->
name|colorize
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_colorize_tool_initialize (GimpTool * tool,GimpDisplay * display,GError ** error)
name|gimp_colorize_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpColorizeTool
modifier|*
name|col_tool
init|=
name|GIMP_COLORIZE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|display
operator|->
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Colorize operates only on RGB color layers."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_config_reset
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|col_tool
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|initialize
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|GeglNode
modifier|*
DECL|function|gimp_colorize_tool_get_operation (GimpImageMapTool * im_tool,GObject ** config)
name|gimp_colorize_tool_get_operation
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|,
name|GObject
modifier|*
modifier|*
name|config
parameter_list|)
block|{
name|GimpColorizeTool
modifier|*
name|col_tool
init|=
name|GIMP_COLORIZE_TOOL
argument_list|(
name|im_tool
argument_list|)
decl_stmt|;
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|node
operator|=
name|g_object_new
argument_list|(
name|GEGL_TYPE_NODE
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp-colorize"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|col_tool
operator|->
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLORIZE_CONFIG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|config
operator|=
name|G_OBJECT
argument_list|(
name|col_tool
operator|->
name|config
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|col_tool
operator|->
name|config
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_colorize_tool_config_notify
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|col_tool
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|node
argument_list|,
literal|"config"
argument_list|,
name|col_tool
operator|->
name|config
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|node
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_map (GimpImageMapTool * image_map_tool)
name|gimp_colorize_tool_map
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpColorizeTool
modifier|*
name|col_tool
init|=
name|GIMP_COLORIZE_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|gimp_colorize_config_to_cruft
argument_list|(
name|col_tool
operator|->
name|config
argument_list|,
name|col_tool
operator|->
name|colorize
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/***************************/
end_comment

begin_comment
comment|/*  Hue-Saturation dialog  */
end_comment

begin_comment
comment|/***************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_dialog (GimpImageMapTool * image_map_tool)
name|gimp_colorize_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpColorizeTool
modifier|*
name|col_tool
init|=
name|GIMP_COLORIZE_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|slider
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkObject
modifier|*
name|data
decl_stmt|;
name|main_vbox
operator|=
name|gimp_image_map_tool_dialog_get_vbox
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Select Color"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
comment|/*  The table containing sliders  */
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
comment|/*  Create the hue scale widget  */
name|data
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Hue:"
argument_list|)
argument_list|,
name|SLIDER_WIDTH
argument_list|,
name|SPINNER_WIDTH
argument_list|,
name|col_tool
operator|->
name|config
operator|->
name|hue
operator|*
literal|360.0
argument_list|,
literal|0.0
argument_list|,
literal|360.0
argument_list|,
literal|1.0
argument_list|,
literal|15.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|col_tool
operator|->
name|hue_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|slider
operator|=
name|GIMP_SCALE_ENTRY_SCALE
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_CONTINUOUS
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|colorize_hue_changed
argument_list|)
argument_list|,
name|col_tool
argument_list|)
expr_stmt|;
comment|/*  Create the saturation scale widget  */
name|data
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"_Saturation:"
argument_list|)
argument_list|,
name|SLIDER_WIDTH
argument_list|,
name|SPINNER_WIDTH
argument_list|,
name|col_tool
operator|->
name|config
operator|->
name|saturation
operator|*
literal|100.0
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|col_tool
operator|->
name|saturation_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|slider
operator|=
name|GIMP_SCALE_ENTRY_SCALE
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_CONTINUOUS
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|colorize_saturation_changed
argument_list|)
argument_list|,
name|col_tool
argument_list|)
expr_stmt|;
comment|/*  Create the lightness scale widget  */
name|data
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"_Lightness:"
argument_list|)
argument_list|,
name|SLIDER_WIDTH
argument_list|,
name|SPINNER_WIDTH
argument_list|,
name|col_tool
operator|->
name|config
operator|->
name|lightness
operator|*
literal|100.0
argument_list|,
operator|-
literal|100.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|col_tool
operator|->
name|lightness_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|slider
operator|=
name|GIMP_SCALE_ENTRY_SCALE
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_CONTINUOUS
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|colorize_lightness_changed
argument_list|)
argument_list|,
name|col_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_config_notify (GObject * object,GParamSpec * pspec,GimpColorizeTool * col_tool)
name|gimp_colorize_tool_config_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
block|{
name|GimpColorizeConfig
modifier|*
name|config
init|=
name|GIMP_COLORIZE_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|col_tool
operator|->
name|hue_data
condition|)
return|return;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"hue"
argument_list|)
condition|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|col_tool
operator|->
name|hue_data
argument_list|,
name|config
operator|->
name|hue
operator|*
literal|360.0
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"saturation"
argument_list|)
condition|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|col_tool
operator|->
name|saturation_data
argument_list|,
name|config
operator|->
name|saturation
operator|*
literal|100.0
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"lightness"
argument_list|)
condition|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|col_tool
operator|->
name|lightness_data
argument_list|,
name|config
operator|->
name|lightness
operator|*
literal|100.0
argument_list|)
expr_stmt|;
block|}
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|col_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorize_hue_changed (GtkAdjustment * adjustment,GimpColorizeTool * col_tool)
name|colorize_hue_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
block|{
name|gdouble
name|value
init|=
name|gtk_adjustment_get_value
argument_list|(
name|adjustment
argument_list|)
operator|/
literal|360.0
decl_stmt|;
if|if
condition|(
name|col_tool
operator|->
name|config
operator|->
name|hue
operator|!=
name|value
condition|)
block|{
name|g_object_set
argument_list|(
name|col_tool
operator|->
name|config
argument_list|,
literal|"hue"
argument_list|,
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorize_saturation_changed (GtkAdjustment * adjustment,GimpColorizeTool * col_tool)
name|colorize_saturation_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
block|{
name|gdouble
name|value
init|=
name|gtk_adjustment_get_value
argument_list|(
name|adjustment
argument_list|)
operator|/
literal|100.0
decl_stmt|;
if|if
condition|(
name|col_tool
operator|->
name|config
operator|->
name|saturation
operator|!=
name|value
condition|)
block|{
name|g_object_set
argument_list|(
name|col_tool
operator|->
name|config
argument_list|,
literal|"saturation"
argument_list|,
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorize_lightness_changed (GtkAdjustment * adjustment,GimpColorizeTool * col_tool)
name|colorize_lightness_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
block|{
name|gdouble
name|value
init|=
name|gtk_adjustment_get_value
argument_list|(
name|adjustment
argument_list|)
operator|/
literal|100.0
decl_stmt|;
if|if
condition|(
name|col_tool
operator|->
name|config
operator|->
name|lightness
operator|!=
name|value
condition|)
block|{
name|g_object_set
argument_list|(
name|col_tool
operator|->
name|config
argument_list|,
literal|"lightness"
argument_list|,
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

