begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
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
file|"base/gimphistogram.h"
end_include

begin_include
include|#
directive|include
file|"base/threshold.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpbaseconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimagemap.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
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
file|"gimpthresholdtool.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|LOW
define|#
directive|define
name|LOW
value|0x1
end_define

begin_define
DECL|macro|HIGH
define|#
directive|define
name|HIGH
value|0x2
end_define

begin_define
DECL|macro|HISTOGRAM
define|#
directive|define
name|HISTOGRAM
value|0x4
end_define

begin_define
DECL|macro|ALL
define|#
directive|define
name|ALL
value|(LOW | HIGH | HISTOGRAM)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_threshold_tool_class_init
parameter_list|(
name|GimpThresholdToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_threshold_tool_init
parameter_list|(
name|GimpThresholdTool
modifier|*
name|threshold_tool
parameter_list|)
function_decl|;
end_function_decl

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
name|void
name|gimp_threshold_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_threshold_tool_map
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
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
name|image_map_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_threshold_tool_reset
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpImageMapToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_threshold_tool_register (GimpToolRegisterCallback callback,gpointer data)
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
name|G_TYPE_NONE
argument_list|,
name|NULL
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
literal|"Reduce image to two colors using a threshold"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Color Tools/_Threshold..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"tools/threshold.html"
argument_list|,
name|GIMP_STOCK_TOOL_THRESHOLD
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_threshold_tool_get_type (void)
name|gimp_threshold_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tool_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpThresholdToolClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_threshold_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpThresholdTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_threshold_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_IMAGE_MAP_TOOL
argument_list|,
literal|"GimpThresholdTool"
argument_list|,
operator|&
name|tool_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_type
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

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
decl_stmt|;
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|GimpImageMapToolClass
modifier|*
name|image_map_tool_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|image_map_tool_class
operator|=
name|GIMP_IMAGE_MAP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
name|image_map_tool_class
operator|->
name|map
operator|=
name|gimp_threshold_tool_map
expr_stmt|;
name|image_map_tool_class
operator|->
name|dialog
operator|=
name|gimp_threshold_tool_dialog
expr_stmt|;
name|image_map_tool_class
operator|->
name|reset
operator|=
name|gimp_threshold_tool_reset
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
name|GimpImageMapTool
modifier|*
name|image_map_tool
decl_stmt|;
name|image_map_tool
operator|=
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|t_tool
argument_list|)
expr_stmt|;
name|image_map_tool
operator|->
name|shell_identifier
operator|=
literal|"gimp-threshold-tool-dialog"
expr_stmt|;
name|image_map_tool
operator|->
name|shell_desc
operator|=
name|_
argument_list|(
literal|"Apply Threshold"
argument_list|)
expr_stmt|;
name|t_tool
operator|->
name|threshold
operator|=
name|g_new0
argument_list|(
name|Threshold
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|t_tool
operator|->
name|hist
operator|=
name|NULL
expr_stmt|;
name|t_tool
operator|->
name|threshold
operator|->
name|low_threshold
operator|=
literal|127
expr_stmt|;
name|t_tool
operator|->
name|threshold
operator|->
name|high_threshold
operator|=
literal|255
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
decl_stmt|;
name|t_tool
operator|=
name|GIMP_THRESHOLD_TOOL
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|t_tool
operator|->
name|threshold
condition|)
block|{
name|g_free
argument_list|(
name|t_tool
operator|->
name|threshold
argument_list|)
expr_stmt|;
name|t_tool
operator|->
name|threshold
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|t_tool
operator|->
name|hist
condition|)
block|{
name|gimp_histogram_free
argument_list|(
name|t_tool
operator|->
name|hist
argument_list|)
expr_stmt|;
name|t_tool
operator|->
name|hist
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
name|void
DECL|function|gimp_threshold_tool_initialize (GimpTool * tool,GimpDisplay * gdisp)
name|gimp_threshold_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpThresholdTool
modifier|*
name|t_tool
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|t_tool
operator|=
name|GIMP_THRESHOLD_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Threshold does not operate on indexed drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|t_tool
operator|->
name|hist
condition|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|GIMP_TOOL
argument_list|(
name|t_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|gimp
decl_stmt|;
name|t_tool
operator|->
name|hist
operator|=
name|gimp_histogram_new
argument_list|(
name|GIMP_BASE_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|t_tool
operator|->
name|threshold
operator|->
name|color
operator|=
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|t_tool
operator|->
name|threshold
operator|->
name|low_threshold
operator|=
literal|127
expr_stmt|;
name|t_tool
operator|->
name|threshold
operator|->
name|high_threshold
operator|=
literal|255
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
name|gdisp
argument_list|)
expr_stmt|;
name|gimp_drawable_calculate_histogram
argument_list|(
name|drawable
argument_list|,
name|t_tool
operator|->
name|hist
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|t_tool
operator|->
name|histogram_box
operator|->
name|histogram
argument_list|,
name|gimp_threshold_tool_histogram_range
argument_list|,
name|t_tool
argument_list|)
expr_stmt|;
name|gimp_histogram_view_set_histogram
argument_list|(
name|t_tool
operator|->
name|histogram_box
operator|->
name|histogram
argument_list|,
name|t_tool
operator|->
name|hist
argument_list|)
expr_stmt|;
name|gimp_histogram_view_set_range
argument_list|(
name|t_tool
operator|->
name|histogram_box
operator|->
name|histogram
argument_list|,
name|t_tool
operator|->
name|threshold
operator|->
name|low_threshold
argument_list|,
name|t_tool
operator|->
name|threshold
operator|->
name|high_threshold
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|t_tool
operator|->
name|histogram_box
operator|->
name|histogram
argument_list|,
name|gimp_threshold_tool_histogram_range
argument_list|,
name|t_tool
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|t_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_threshold_tool_map (GimpImageMapTool * image_map_tool)
name|gimp_threshold_tool_map
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpThresholdTool
modifier|*
name|t_tool
decl_stmt|;
name|t_tool
operator|=
name|GIMP_THRESHOLD_TOOL
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|gimp_image_map_apply
argument_list|(
name|image_map_tool
operator|->
name|image_map
argument_list|,
name|threshold
argument_list|,
name|t_tool
operator|->
name|threshold
argument_list|)
expr_stmt|;
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
decl_stmt|;
name|GtkWidget
modifier|*
name|box
decl_stmt|;
name|t_tool
operator|=
name|GIMP_THRESHOLD_TOOL
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|box
operator|=
name|gimp_histogram_box_new
argument_list|(
name|_
argument_list|(
literal|"Threshold Range:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|image_map_tool
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|box
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
name|g_signal_connect
argument_list|(
name|t_tool
operator|->
name|histogram_box
operator|->
name|histogram
argument_list|,
literal|"range_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_threshold_tool_histogram_range
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
DECL|function|gimp_threshold_tool_reset (GimpImageMapTool * image_map_tool)
name|gimp_threshold_tool_reset
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpThresholdTool
modifier|*
name|t_tool
decl_stmt|;
name|t_tool
operator|=
name|GIMP_THRESHOLD_TOOL
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|t_tool
operator|->
name|threshold
operator|->
name|low_threshold
operator|=
literal|127.0
expr_stmt|;
name|t_tool
operator|->
name|threshold
operator|->
name|high_threshold
operator|=
literal|255.0
expr_stmt|;
name|gimp_histogram_view_set_range
argument_list|(
name|t_tool
operator|->
name|histogram_box
operator|->
name|histogram
argument_list|,
name|t_tool
operator|->
name|threshold
operator|->
name|low_threshold
argument_list|,
name|t_tool
operator|->
name|threshold
operator|->
name|high_threshold
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
if|if
condition|(
name|start
operator|!=
name|t_tool
operator|->
name|threshold
operator|->
name|low_threshold
operator|||
name|end
operator|!=
name|t_tool
operator|->
name|threshold
operator|->
name|high_threshold
condition|)
block|{
name|t_tool
operator|->
name|threshold
operator|->
name|low_threshold
operator|=
name|start
expr_stmt|;
name|t_tool
operator|->
name|threshold
operator|->
name|high_threshold
operator|=
name|end
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|t_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

