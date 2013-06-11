begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"operations/gimpthresholdconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-histogram.h"
end_include

begin_include
include|#
directive|include
file|"core/gimperror.h"
end_include

begin_include
include|#
directive|include
file|"core/gimphistogram.h"
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
file|"widgets/gimphistogrambox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphistogramview.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogramoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpthresholdtool.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_threshold_tool_finalize
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
name|gimp_threshold_tool_initialize
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
name|gimp_threshold_tool_get_operation
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|,
name|GObject
modifier|*
modifier|*
name|config
parameter_list|,
name|gchar
modifier|*
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_threshold_tool_dialog
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
name|gimp_threshold_tool_config_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpThresholdTool
modifier|*
name|t_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_threshold_tool_histogram_range
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|end
parameter_list|,
name|GimpThresholdTool
modifier|*
name|t_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_threshold_tool_auto_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpThresholdTool
modifier|*
name|t_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpThresholdTool,gimp_threshold_tool,GIMP_TYPE_IMAGE_MAP_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpThresholdTool
argument_list|,
argument|gimp_threshold_tool
argument_list|,
argument|GIMP_TYPE_IMAGE_MAP_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_threshold_tool_parent_class
end_define

begin_function
name|void
name|gimp_threshold_tool_register
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
name|GIMP_TYPE_THRESHOLD_TOOL
argument_list|,
name|GIMP_TYPE_HISTOGRAM_OPTIONS
argument_list|,
name|gimp_histogram_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-threshold-tool"
argument_list|,
name|_
argument_list|(
literal|"Threshold"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Threshold Tool: Reduce image to two colors using a threshold"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Threshold..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_THRESHOLD
argument_list|,
name|GIMP_STOCK_TOOL_THRESHOLD
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_threshold_tool_class_init (GimpThresholdToolClass * klass)
name|gimp_threshold_tool_class_init
parameter_list|(
name|GimpThresholdToolClass
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
name|gimp_threshold_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_threshold_tool_initialize
expr_stmt|;
name|im_tool_class
operator|->
name|dialog_desc
operator|=
name|_
argument_list|(
literal|"Apply Threshold"
argument_list|)
expr_stmt|;
name|im_tool_class
operator|->
name|settings_name
operator|=
literal|"threshold"
expr_stmt|;
name|im_tool_class
operator|->
name|import_dialog_title
operator|=
name|_
argument_list|(
literal|"Import Threshold Settings"
argument_list|)
expr_stmt|;
name|im_tool_class
operator|->
name|export_dialog_title
operator|=
name|_
argument_list|(
literal|"Export Threshold Settings"
argument_list|)
expr_stmt|;
name|im_tool_class
operator|->
name|get_operation
operator|=
name|gimp_threshold_tool_get_operation
expr_stmt|;
name|im_tool_class
operator|->
name|dialog
operator|=
name|gimp_threshold_tool_dialog
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_threshold_tool_init (GimpThresholdTool * t_tool)
name|gimp_threshold_tool_init
parameter_list|(
name|GimpThresholdTool
modifier|*
name|t_tool
parameter_list|)
block|{
name|t_tool
operator|->
name|histogram
operator|=
name|gimp_histogram_new
argument_list|(
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_threshold_tool_finalize (GObject * object)
name|gimp_threshold_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpThresholdTool
modifier|*
name|t_tool
init|=
name|GIMP_THRESHOLD_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|t_tool
operator|->
name|histogram
condition|)
block|{
name|g_object_unref
argument_list|(
name|t_tool
operator|->
name|histogram
argument_list|)
expr_stmt|;
name|t_tool
operator|->
name|histogram
operator|=
name|NULL
expr_stmt|;
block|}
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
DECL|function|gimp_threshold_tool_initialize (GimpTool * tool,GimpDisplay * display,GError ** error)
name|gimp_threshold_tool_initialize
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
name|GimpThresholdTool
modifier|*
name|t_tool
init|=
name|GIMP_THRESHOLD_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
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
condition|)
block|{
return|return
name|FALSE
return|;
block|}
name|gimp_drawable_calculate_histogram
argument_list|(
name|drawable
argument_list|,
name|t_tool
operator|->
name|histogram
argument_list|)
expr_stmt|;
name|gimp_histogram_view_set_histogram
argument_list|(
name|t_tool
operator|->
name|histogram_box
operator|->
name|view
argument_list|,
name|t_tool
operator|->
name|histogram
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
DECL|function|gimp_threshold_tool_get_operation (GimpImageMapTool * image_map_tool,GObject ** config,gchar ** undo_desc)
name|gimp_threshold_tool_get_operation
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|,
name|GObject
modifier|*
modifier|*
name|config
parameter_list|,
name|gchar
modifier|*
modifier|*
name|undo_desc
parameter_list|)
block|{
name|GimpThresholdTool
modifier|*
name|t_tool
init|=
name|GIMP_THRESHOLD_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|t_tool
operator|->
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_THRESHOLD_CONFIG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|t_tool
operator|->
name|config
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_threshold_tool_config_notify
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|t_tool
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
operator|*
name|config
operator|=
name|G_OBJECT
argument_list|(
name|t_tool
operator|->
name|config
argument_list|)
expr_stmt|;
return|return
name|gegl_node_new_child
argument_list|(
name|NULL
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:threshold"
argument_list|,
literal|"config"
argument_list|,
name|t_tool
operator|->
name|config
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**********************/
end_comment

begin_comment
comment|/*  Threshold dialog  */
end_comment

begin_comment
comment|/**********************/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_threshold_tool_dialog (GimpImageMapTool * image_map_tool)
name|gimp_threshold_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpThresholdTool
modifier|*
name|t_tool
init|=
name|GIMP_THRESHOLD_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|GimpToolOptions
modifier|*
name|tool_options
init|=
name|GIMP_TOOL_GET_OPTIONS
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|GimpThresholdConfig
modifier|*
name|config
init|=
name|t_tool
operator|->
name|config
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|GtkWidget
modifier|*
name|box
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|main_vbox
operator|=
name|gimp_image_map_tool_dialog_get_vbox
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|menu
operator|=
name|gimp_prop_enum_stock_box_new
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
argument_list|,
literal|"histogram-scale"
argument_list|,
literal|"gimp-histogram"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|menu
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
name|menu
argument_list|)
expr_stmt|;
name|box
operator|=
name|gimp_histogram_box_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|box
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|t_tool
operator|->
name|histogram_box
operator|=
name|GIMP_HISTOGRAM_BOX
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|gimp_histogram_view_set_range
argument_list|(
name|t_tool
operator|->
name|histogram_box
operator|->
name|view
argument_list|,
name|config
operator|->
name|low
operator|*
literal|255.999
argument_list|,
name|config
operator|->
name|high
operator|*
literal|255.999
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|t_tool
operator|->
name|histogram_box
operator|->
name|view
argument_list|,
literal|"range-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_threshold_tool_histogram_range
argument_list|)
argument_list|,
name|t_tool
argument_list|)
expr_stmt|;
name|gimp_histogram_options_connect_view
argument_list|(
name|GIMP_HISTOGRAM_OPTIONS
argument_list|(
name|tool_options
argument_list|)
argument_list|,
name|t_tool
operator|->
name|histogram_box
operator|->
name|view
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Auto"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|_
argument_list|(
literal|"Automatically adjust to optimal "
literal|"binarization threshold"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_threshold_tool_auto_clicked
argument_list|)
argument_list|,
name|t_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_threshold_tool_config_notify (GObject * object,GParamSpec * pspec,GimpThresholdTool * t_tool)
name|gimp_threshold_tool_config_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpThresholdTool
modifier|*
name|t_tool
parameter_list|)
block|{
name|GimpThresholdConfig
modifier|*
name|config
init|=
name|GIMP_THRESHOLD_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|t_tool
operator|->
name|histogram_box
condition|)
return|return;
name|gimp_histogram_view_set_range
argument_list|(
name|t_tool
operator|->
name|histogram_box
operator|->
name|view
argument_list|,
name|config
operator|->
name|low
operator|*
literal|255.999
argument_list|,
name|config
operator|->
name|high
operator|*
literal|255.999
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_threshold_tool_histogram_range (GimpHistogramView * widget,gint start,gint end,GimpThresholdTool * t_tool)
name|gimp_threshold_tool_histogram_range
parameter_list|(
name|GimpHistogramView
modifier|*
name|widget
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|end
parameter_list|,
name|GimpThresholdTool
modifier|*
name|t_tool
parameter_list|)
block|{
name|gdouble
name|low
init|=
name|start
operator|/
literal|255.0
decl_stmt|;
name|gdouble
name|high
init|=
name|end
operator|/
literal|255.0
decl_stmt|;
if|if
condition|(
name|low
operator|!=
name|t_tool
operator|->
name|config
operator|->
name|low
operator|||
name|high
operator|!=
name|t_tool
operator|->
name|config
operator|->
name|high
condition|)
block|{
name|g_object_set
argument_list|(
name|t_tool
operator|->
name|config
argument_list|,
literal|"low"
argument_list|,
name|low
argument_list|,
literal|"high"
argument_list|,
name|high
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
DECL|function|gimp_threshold_tool_auto_clicked (GtkWidget * button,GimpThresholdTool * t_tool)
name|gimp_threshold_tool_auto_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpThresholdTool
modifier|*
name|t_tool
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|t_tool
argument_list|)
operator|->
name|drawable
decl_stmt|;
name|gdouble
name|low
decl_stmt|;
name|low
operator|=
name|gimp_histogram_get_threshold
argument_list|(
name|t_tool
operator|->
name|histogram
argument_list|,
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
condition|?
name|GIMP_HISTOGRAM_RGB
else|:
name|GIMP_HISTOGRAM_VALUE
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|gimp_histogram_view_set_range
argument_list|(
name|t_tool
operator|->
name|histogram_box
operator|->
name|view
argument_list|,
name|low
argument_list|,
literal|255.0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

