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
file|"libgimpmath/gimpmath.h"
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
file|"base/pixel-region.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpenummenu.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
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
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogramtool.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|HistogramToolDialog
typedef|typedef
name|struct
name|_HistogramToolDialog
name|HistogramToolDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_HistogramToolDialog
struct|struct
name|_HistogramToolDialog
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|info_labels
name|GtkWidget
modifier|*
name|info_labels
index|[
literal|6
index|]
decl_stmt|;
DECL|member|channel_menu
name|GtkWidget
modifier|*
name|channel_menu
decl_stmt|;
DECL|member|histogram_box
name|GimpHistogramBox
modifier|*
name|histogram_box
decl_stmt|;
DECL|member|hist
name|GimpHistogram
modifier|*
name|hist
decl_stmt|;
DECL|member|gradient
name|GtkWidget
modifier|*
name|gradient
decl_stmt|;
DECL|member|mean
name|gdouble
name|mean
decl_stmt|;
DECL|member|std_dev
name|gdouble
name|std_dev
decl_stmt|;
DECL|member|median
name|gdouble
name|median
decl_stmt|;
DECL|member|pixels
name|gdouble
name|pixels
decl_stmt|;
DECL|member|count
name|gdouble
name|count
decl_stmt|;
DECL|member|percentile
name|gdouble
name|percentile
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_histogram_tool_class_init
parameter_list|(
name|GimpHistogramToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_tool_init
parameter_list|(
name|GimpHistogramTool
modifier|*
name|hist_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_tool_initialize
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
name|gimp_histogram_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|HistogramToolDialog
modifier|*
name|histogram_tool_dialog_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|histogram_tool_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|histogram_set_sensitive_callback
parameter_list|(
name|gpointer
name|item_data
parameter_list|,
name|HistogramToolDialog
modifier|*
name|htd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|histogram_tool_dialog_update
parameter_list|(
name|HistogramToolDialog
modifier|*
name|htd
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|end
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|histogram_tool_histogram_range
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
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|histogram_dialog
specifier|static
name|HistogramToolDialog
modifier|*
name|histogram_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

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
DECL|function|gimp_histogram_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_histogram_tool_register
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
name|GIMP_TYPE_HISTOGRAM_TOOL
argument_list|,
name|G_TYPE_NONE
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|"gimp-histogram-tool"
argument_list|,
name|_
argument_list|(
literal|"Histogram"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"View image histogram"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Color Tools/Histogram..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"tools/histogram.html"
argument_list|,
name|GIMP_STOCK_TOOL_HISTOGRAM
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_histogram_tool_get_type (void)
name|gimp_histogram_tool_get_type
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
name|GimpHistogramToolClass
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
name|gimp_histogram_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpHistogramTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_histogram_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_IMAGE_MAP_TOOL
argument_list|,
literal|"GimpHistogramTool"
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

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_tool_class_init (GimpHistogramToolClass * klass)
name|gimp_histogram_tool_class_init
parameter_list|(
name|GimpHistogramToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
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
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_histogram_tool_initialize
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_histogram_tool_control
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_tool_init (GimpHistogramTool * hist_tool)
name|gimp_histogram_tool_init
parameter_list|(
name|GimpHistogramTool
modifier|*
name|hist_tool
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_tool_initialize (GimpTool * tool,GimpDisplay * gdisp)
name|gimp_histogram_tool_initialize
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|PixelRegion
name|PR
decl_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Histogram does not operate on indexed drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  The histogram_tool dialog  */
if|if
condition|(
operator|!
name|histogram_dialog
condition|)
name|histogram_dialog
operator|=
name|histogram_tool_dialog_new
argument_list|(
name|tool
operator|->
name|tool_info
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
name|gimp_viewable_dialog_set_viewable
argument_list|(
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|histogram_dialog
operator|->
name|shell
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|histogram_dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
name|histogram_dialog
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|gimp_option_menu_set_sensitive
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|histogram_dialog
operator|->
name|channel_menu
argument_list|)
argument_list|,
operator|(
name|GimpOptionMenuSensitivityCallback
operator|)
name|histogram_set_sensitive_callback
argument_list|,
name|histogram_dialog
argument_list|)
expr_stmt|;
comment|/* calculate the histogram */
name|pixel_region_init
argument_list|(
operator|&
name|PR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|drawable
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_histogram_calculate
argument_list|(
name|histogram_dialog
operator|->
name|hist
argument_list|,
operator|&
name|PR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_histogram_view_set_histogram
argument_list|(
name|GIMP_HISTOGRAM_VIEW
argument_list|(
name|histogram_dialog
operator|->
name|histogram_box
operator|->
name|histogram
argument_list|)
argument_list|,
name|histogram_dialog
operator|->
name|hist
argument_list|)
expr_stmt|;
name|gimp_histogram_view_set_range
argument_list|(
name|GIMP_HISTOGRAM_VIEW
argument_list|(
name|histogram_dialog
operator|->
name|histogram_box
operator|->
name|histogram
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * gdisp)
name|gimp_histogram_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|PAUSE
case|:
break|break;
case|case
name|RESUME
case|:
break|break;
case|case
name|HALT
case|:
if|if
condition|(
name|histogram_dialog
condition|)
name|histogram_tool_close_callback
argument_list|(
name|NULL
argument_list|,
name|histogram_dialog
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|control
argument_list|(
name|tool
argument_list|,
name|action
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  histogram_tool machinery  */
end_comment

begin_function
specifier|static
name|void
DECL|function|histogram_tool_histogram_range (GimpHistogramView * widget,gint start,gint end,gpointer data)
name|histogram_tool_histogram_range
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
name|gpointer
name|data
parameter_list|)
block|{
name|HistogramToolDialog
modifier|*
name|htd
decl_stmt|;
name|GimpHistogramChannel
name|channel
decl_stmt|;
name|gdouble
name|pixels
decl_stmt|;
name|gdouble
name|count
decl_stmt|;
name|htd
operator|=
operator|(
name|HistogramToolDialog
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|htd
operator|==
name|NULL
operator|||
name|htd
operator|->
name|hist
operator|==
name|NULL
operator|||
name|gimp_histogram_nchannels
argument_list|(
name|htd
operator|->
name|hist
argument_list|)
operator|<=
literal|0
condition|)
return|return;
name|channel
operator|=
name|gimp_histogram_view_get_channel
argument_list|(
name|htd
operator|->
name|histogram_box
operator|->
name|histogram
argument_list|)
expr_stmt|;
name|pixels
operator|=
name|gimp_histogram_get_count
argument_list|(
name|htd
operator|->
name|hist
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|count
operator|=
name|gimp_histogram_get_count
argument_list|(
name|htd
operator|->
name|hist
argument_list|,
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
name|htd
operator|->
name|mean
operator|=
name|gimp_histogram_get_mean
argument_list|(
name|htd
operator|->
name|hist
argument_list|,
name|channel
argument_list|,
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
name|htd
operator|->
name|std_dev
operator|=
name|gimp_histogram_get_std_dev
argument_list|(
name|htd
operator|->
name|hist
argument_list|,
name|channel
argument_list|,
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
name|htd
operator|->
name|median
operator|=
name|gimp_histogram_get_median
argument_list|(
name|htd
operator|->
name|hist
argument_list|,
name|channel
argument_list|,
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
name|htd
operator|->
name|pixels
operator|=
name|pixels
expr_stmt|;
name|htd
operator|->
name|count
operator|=
name|count
expr_stmt|;
name|htd
operator|->
name|percentile
operator|=
name|count
operator|/
name|pixels
expr_stmt|;
if|if
condition|(
name|htd
operator|->
name|shell
condition|)
name|histogram_tool_dialog_update
argument_list|(
name|htd
argument_list|,
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|histogram_tool_dialog_update (HistogramToolDialog * htd,gint start,gint end)
name|histogram_tool_dialog_update
parameter_list|(
name|HistogramToolDialog
modifier|*
name|htd
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|end
parameter_list|)
block|{
name|gchar
name|text
index|[
literal|12
index|]
decl_stmt|;
comment|/*  mean  */
name|g_snprintf
argument_list|(
name|text
argument_list|,
sizeof|sizeof
argument_list|(
name|text
argument_list|)
argument_list|,
literal|"%3.1f"
argument_list|,
name|htd
operator|->
name|mean
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|htd
operator|->
name|info_labels
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
comment|/*  std dev  */
name|g_snprintf
argument_list|(
name|text
argument_list|,
sizeof|sizeof
argument_list|(
name|text
argument_list|)
argument_list|,
literal|"%3.1f"
argument_list|,
name|htd
operator|->
name|std_dev
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|htd
operator|->
name|info_labels
index|[
literal|1
index|]
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
comment|/*  median  */
name|g_snprintf
argument_list|(
name|text
argument_list|,
sizeof|sizeof
argument_list|(
name|text
argument_list|)
argument_list|,
literal|"%3.1f"
argument_list|,
name|htd
operator|->
name|median
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|htd
operator|->
name|info_labels
index|[
literal|2
index|]
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
comment|/*  pixels  */
name|g_snprintf
argument_list|(
name|text
argument_list|,
sizeof|sizeof
argument_list|(
name|text
argument_list|)
argument_list|,
literal|"%8.1f"
argument_list|,
name|htd
operator|->
name|pixels
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|htd
operator|->
name|info_labels
index|[
literal|3
index|]
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
comment|/*  count  */
name|g_snprintf
argument_list|(
name|text
argument_list|,
sizeof|sizeof
argument_list|(
name|text
argument_list|)
argument_list|,
literal|"%8.1f"
argument_list|,
name|htd
operator|->
name|count
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|htd
operator|->
name|info_labels
index|[
literal|4
index|]
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
comment|/*  percentile  */
name|g_snprintf
argument_list|(
name|text
argument_list|,
sizeof|sizeof
argument_list|(
name|text
argument_list|)
argument_list|,
literal|"%2.2f"
argument_list|,
name|htd
operator|->
name|percentile
operator|*
literal|100
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|htd
operator|->
name|info_labels
index|[
literal|5
index|]
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/***************************/
end_comment

begin_comment
comment|/*  Histogram Tool dialog  */
end_comment

begin_comment
comment|/***************************/
end_comment

begin_function
specifier|static
name|HistogramToolDialog
modifier|*
DECL|function|histogram_tool_dialog_new (GimpToolInfo * tool_info)
name|histogram_tool_dialog_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
block|{
name|HistogramToolDialog
modifier|*
name|htd
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
specifier|static
specifier|const
name|gchar
modifier|*
name|histogram_info_names
index|[]
init|=
block|{
name|N_
argument_list|(
literal|"Mean:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Std Dev:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Median:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Pixels:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Count:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Percentile:"
argument_list|)
block|}
decl_stmt|;
name|htd
operator|=
name|g_new0
argument_list|(
name|HistogramToolDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|htd
operator|->
name|hist
operator|=
name|gimp_histogram_new
argument_list|(
name|GIMP_BASE_CONFIG
argument_list|(
name|tool_info
operator|->
name|gimp
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|stock_id
operator|=
name|gimp_viewable_get_stock_id
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  The shell and main vbox  */
name|htd
operator|->
name|shell
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|NULL
argument_list|,
name|tool_info
operator|->
name|blurb
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
operator|->
name|name
argument_list|,
name|stock_id
argument_list|,
name|_
argument_list|(
literal|"View Image Histogram"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|tool_info
operator|->
name|help_data
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|histogram_tool_close_callback
argument_list|,
name|htd
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|htd
operator|->
name|shell
argument_list|)
operator|->
name|vbox
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
comment|/*  Create the histogram view first  */
name|htd
operator|->
name|histogram_box
operator|=
name|GIMP_HISTOGRAM_BOX
argument_list|(
name|gimp_histogram_box_new
argument_list|(
name|_
argument_list|(
literal|"Intensity Range:"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  The option menu for selecting channels  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Information on Channel:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|htd
operator|->
name|channel_menu
operator|=
name|gimp_prop_enum_option_menu_new
argument_list|(
name|G_OBJECT
argument_list|(
name|htd
operator|->
name|histogram_box
operator|->
name|histogram
argument_list|)
argument_list|,
literal|"channel"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_enum_option_menu_set_stock_prefix
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|htd
operator|->
name|channel_menu
argument_list|)
argument_list|,
literal|"gimp-channel"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|htd
operator|->
name|channel_menu
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
name|htd
operator|->
name|channel_menu
argument_list|)
expr_stmt|;
comment|/*  The histogram tool histogram  */
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|htd
operator|->
name|histogram_box
argument_list|)
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
name|GTK_WIDGET
argument_list|(
name|htd
operator|->
name|histogram_box
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|htd
operator|->
name|histogram_box
operator|->
name|histogram
argument_list|,
literal|"range_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|histogram_tool_histogram_range
argument_list|)
argument_list|,
name|htd
argument_list|)
expr_stmt|;
comment|/*  The option menu for selecting the histogram scale  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Histogram Scale:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|menu
operator|=
name|gimp_prop_enum_option_menu_new
argument_list|(
name|G_OBJECT
argument_list|(
name|htd
operator|->
name|histogram_box
operator|->
name|histogram
argument_list|)
argument_list|,
literal|"scale"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
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
comment|/*  The table containing histogram information  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|4
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
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
comment|/*  the labels for histogram information  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|6
condition|;
name|i
operator|++
control|)
block|{
name|y
operator|=
operator|(
name|i
operator|%
literal|3
operator|)
expr_stmt|;
name|x
operator|=
operator|(
name|i
operator|/
literal|3
operator|)
operator|*
literal|2
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|gettext
argument_list|(
name|histogram_info_names
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
name|x
argument_list|,
name|x
operator|+
literal|1
argument_list|,
name|y
argument_list|,
name|y
operator|+
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|htd
operator|->
name|info_labels
index|[
name|i
index|]
operator|=
name|gtk_label_new
argument_list|(
literal|"0"
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|htd
operator|->
name|info_labels
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|htd
operator|->
name|info_labels
index|[
name|i
index|]
argument_list|,
name|x
operator|+
literal|1
argument_list|,
name|x
operator|+
literal|2
argument_list|,
name|y
argument_list|,
name|y
operator|+
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|htd
operator|->
name|info_labels
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|gimp_dialog_factory_add_foreign
argument_list|(
name|gimp_dialog_factory_from_name
argument_list|(
literal|"toplevel"
argument_list|)
argument_list|,
literal|"gimp-histogram-tool-dialog"
argument_list|,
name|htd
operator|->
name|shell
argument_list|)
expr_stmt|;
return|return
name|htd
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|histogram_tool_close_callback (GtkWidget * widget,gpointer data)
name|histogram_tool_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|HistogramToolDialog
modifier|*
name|htd
decl_stmt|;
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
name|htd
operator|=
operator|(
name|HistogramToolDialog
operator|*
operator|)
name|data
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|htd
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|gdisp
operator|=
name|NULL
expr_stmt|;
name|active_tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|histogram_set_sensitive_callback (gpointer item_data,HistogramToolDialog * htd)
name|histogram_set_sensitive_callback
parameter_list|(
name|gpointer
name|item_data
parameter_list|,
name|HistogramToolDialog
modifier|*
name|htd
parameter_list|)
block|{
name|GimpHistogramChannel
name|channel
init|=
name|GPOINTER_TO_INT
argument_list|(
name|item_data
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|channel
condition|)
block|{
case|case
name|GIMP_HISTOGRAM_VALUE
case|:
return|return
name|TRUE
return|;
case|case
name|GIMP_HISTOGRAM_RED
case|:
case|case
name|GIMP_HISTOGRAM_GREEN
case|:
case|case
name|GIMP_HISTOGRAM_BLUE
case|:
return|return
name|gimp_drawable_is_rgb
argument_list|(
name|htd
operator|->
name|drawable
argument_list|)
return|;
case|case
name|GIMP_HISTOGRAM_ALPHA
case|:
return|return
name|gimp_drawable_has_alpha
argument_list|(
name|htd
operator|->
name|drawable
argument_list|)
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

