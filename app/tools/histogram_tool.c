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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"actionarea.h"
end_include

begin_include
include|#
directive|include
file|"buildmenu.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"histogram_tool.h"
end_include

begin_include
include|#
directive|include
file|"image_map.h"
end_include

begin_include
include|#
directive|include
file|"interface.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|TEXT_WIDTH
define|#
directive|define
name|TEXT_WIDTH
value|45
end_define

begin_comment
comment|/*  the histogram structures  */
end_comment

begin_typedef
DECL|typedef|HistogramTool
typedef|typedef
name|struct
name|_HistogramTool
name|HistogramTool
typedef|;
end_typedef

begin_struct
DECL|struct|_HistogramTool
struct|struct
name|_HistogramTool
block|{
DECL|member|x
DECL|member|y
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  coords for last mouse click  */
block|}
struct|;
end_struct

begin_comment
comment|/*  the histogram tool options  */
end_comment

begin_decl_stmt
DECL|variable|histogram_tool_options
specifier|static
name|ToolOptions
modifier|*
name|histogram_tool_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  the histogram tool dialog  */
end_comment

begin_decl_stmt
DECL|variable|histogram_tool_dialog
specifier|static
name|HistogramToolDialog
modifier|*
name|histogram_tool_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  histogram_tool action functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|histogram_tool_button_press
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventButton
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|histogram_tool_button_release
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventButton
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|histogram_tool_motion
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|histogram_tool_cursor_update
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|histogram_tool_control
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|ToolAction
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|HistogramToolDialog
modifier|*
name|histogram_tool_new_dialog
parameter_list|(
name|void
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
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|histogram_tool_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|GdkEvent
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|histogram_tool_value_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|histogram_tool_red_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|histogram_tool_green_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|histogram_tool_blue_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
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
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  histogram_tool machinery  */
end_comment

begin_function
name|void
DECL|function|histogram_tool_histogram_range (HistogramWidget * w,int start,int end,void * user_data)
name|histogram_tool_histogram_range
parameter_list|(
name|HistogramWidget
modifier|*
name|w
parameter_list|,
name|int
name|start
parameter_list|,
name|int
name|end
parameter_list|,
name|void
modifier|*
name|user_data
parameter_list|)
block|{
name|HistogramToolDialog
modifier|*
name|htd
decl_stmt|;
name|double
name|pixels
decl_stmt|;
name|double
name|count
decl_stmt|;
name|htd
operator|=
operator|(
name|HistogramToolDialog
operator|*
operator|)
name|user_data
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
name|htd
operator|->
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
name|htd
operator|->
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
name|htd
operator|->
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
DECL|function|histogram_tool_dialog_update (HistogramToolDialog * htd,int start,int end)
name|histogram_tool_dialog_update
parameter_list|(
name|HistogramToolDialog
modifier|*
name|htd
parameter_list|,
name|int
name|start
parameter_list|,
name|int
name|end
parameter_list|)
block|{
name|char
name|text
index|[
literal|12
index|]
decl_stmt|;
comment|/*  mean  */
name|sprintf
argument_list|(
name|text
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
name|sprintf
argument_list|(
name|text
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
name|sprintf
argument_list|(
name|text
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
name|sprintf
argument_list|(
name|text
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
comment|/*  intensity  */
if|if
condition|(
name|start
operator|==
name|end
condition|)
name|sprintf
argument_list|(
name|text
argument_list|,
literal|"%d"
argument_list|,
name|start
argument_list|)
expr_stmt|;
else|else
name|sprintf
argument_list|(
name|text
argument_list|,
literal|"%d..%d"
argument_list|,
name|start
argument_list|,
name|end
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
comment|/*  count  */
name|sprintf
argument_list|(
name|text
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
literal|5
index|]
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
comment|/*  percentile  */
name|sprintf
argument_list|(
name|text
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
literal|6
index|]
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  histogram_tool action functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|histogram_tool_button_press (Tool * tool,GdkEventButton * bevent,gpointer gdisp_ptr)
name|histogram_tool_button_press
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|gdisp_ptr
expr_stmt|;
name|tool
operator|->
name|drawable
operator|=
name|gimage_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|histogram_tool_button_release (Tool * tool,GdkEventButton * bevent,gpointer gdisp_ptr)
name|histogram_tool_button_release
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|histogram_tool_motion (Tool * tool,GdkEventMotion * mevent,gpointer gdisp_ptr)
name|histogram_tool_motion
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|histogram_tool_cursor_update (Tool * tool,GdkEventMotion * mevent,gpointer gdisp_ptr)
name|histogram_tool_cursor_update
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_TOP_LEFT_ARROW
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|histogram_tool_control (Tool * tool,ToolAction action,gpointer gdisp_ptr)
name|histogram_tool_control
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|ToolAction
name|action
parameter_list|,
name|gpointer
name|gdisp_ptr
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
name|histogram_tool_dialog
condition|)
name|histogram_tool_close_callback
argument_list|(
name|NULL
argument_list|,
operator|(
name|gpointer
operator|)
name|histogram_tool_dialog
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_histogram_tool ()
name|tools_new_histogram_tool
parameter_list|()
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|HistogramTool
modifier|*
name|private
decl_stmt|;
comment|/*  The tool options  */
if|if
condition|(
operator|!
name|histogram_tool_options
condition|)
block|{
name|histogram_tool_options
operator|=
name|tool_options_new
argument_list|(
name|_
argument_list|(
literal|"Histogram Options"
argument_list|)
argument_list|)
expr_stmt|;
name|tools_register
argument_list|(
name|HISTOGRAM
argument_list|,
name|histogram_tool_options
argument_list|)
expr_stmt|;
block|}
name|tool
operator|=
operator|(
name|Tool
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|Tool
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
operator|(
name|HistogramTool
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|HistogramTool
argument_list|)
argument_list|)
expr_stmt|;
name|tool
operator|->
name|type
operator|=
name|HISTOGRAM
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
literal|1
expr_stmt|;
comment|/*  Disallow scrolling  */
name|tool
operator|->
name|auto_snap_to
operator|=
name|TRUE
expr_stmt|;
name|tool
operator|->
name|private
operator|=
operator|(
name|void
operator|*
operator|)
name|private
expr_stmt|;
name|tool
operator|->
name|button_press_func
operator|=
name|histogram_tool_button_press
expr_stmt|;
name|tool
operator|->
name|button_release_func
operator|=
name|histogram_tool_button_release
expr_stmt|;
name|tool
operator|->
name|motion_func
operator|=
name|histogram_tool_motion
expr_stmt|;
name|tool
operator|->
name|arrow_keys_func
operator|=
name|standard_arrow_keys_func
expr_stmt|;
name|tool
operator|->
name|modifier_key_func
operator|=
name|standard_modifier_key_func
expr_stmt|;
name|tool
operator|->
name|cursor_update_func
operator|=
name|histogram_tool_cursor_update
expr_stmt|;
name|tool
operator|->
name|control_func
operator|=
name|histogram_tool_control
expr_stmt|;
name|tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_histogram_tool (Tool * tool)
name|tools_free_histogram_tool
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|HistogramTool
modifier|*
name|hist
decl_stmt|;
name|hist
operator|=
operator|(
name|HistogramTool
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
comment|/*  Close the histogram dialog  */
if|if
condition|(
name|histogram_tool_dialog
condition|)
name|histogram_tool_close_callback
argument_list|(
name|NULL
argument_list|,
operator|(
name|gpointer
operator|)
name|histogram_tool_dialog
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|hist
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|histogram_tool_initialize (GDisplay * gdisp)
name|histogram_tool_initialize
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|PixelRegion
name|PR
decl_stmt|;
if|if
condition|(
name|drawable_indexed
argument_list|(
name|gimage_active_drawable
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
name|histogram_tool_dialog
condition|)
name|histogram_tool_dialog
operator|=
name|histogram_tool_new_dialog
argument_list|()
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|histogram_tool_dialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|histogram_tool_dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
name|histogram_tool_dialog
operator|->
name|drawable
operator|=
name|gimage_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|histogram_tool_dialog
operator|->
name|color
operator|=
name|drawable_color
argument_list|(
name|histogram_tool_dialog
operator|->
name|drawable
argument_list|)
expr_stmt|;
comment|/*  hide or show the channel menu based on image type  */
if|if
condition|(
name|histogram_tool_dialog
operator|->
name|color
condition|)
name|gtk_widget_show
argument_list|(
name|histogram_tool_dialog
operator|->
name|channel_menu
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_hide
argument_list|(
name|histogram_tool_dialog
operator|->
name|channel_menu
argument_list|)
expr_stmt|;
comment|/* calculate the histogram */
name|pixel_region_init
argument_list|(
operator|&
name|PR
argument_list|,
name|drawable_data
argument_list|(
name|histogram_tool_dialog
operator|->
name|drawable
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|drawable_width
argument_list|(
name|histogram_tool_dialog
operator|->
name|drawable
argument_list|)
argument_list|,
name|drawable_height
argument_list|(
name|histogram_tool_dialog
operator|->
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_histogram_calculate
argument_list|(
name|histogram_tool_dialog
operator|->
name|hist
argument_list|,
operator|&
name|PR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|histogram_widget_update
argument_list|(
name|histogram_tool_dialog
operator|->
name|histogram
argument_list|,
name|histogram_tool_dialog
operator|->
name|hist
argument_list|)
expr_stmt|;
name|histogram_widget_range
argument_list|(
name|histogram_tool_dialog
operator|->
name|histogram
argument_list|,
literal|0
argument_list|,
literal|255
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
DECL|function|histogram_tool_new_dialog ()
name|histogram_tool_new_dialog
parameter_list|()
block|{
name|HistogramToolDialog
modifier|*
name|htd
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox2
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
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
name|option_menu
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|int
name|i
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
specifier|static
name|ActionAreaItem
name|action_items
index|[]
init|=
block|{
block|{
name|N_
argument_list|(
literal|"Close"
argument_list|)
block|,
name|histogram_tool_close_callback
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|char
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
literal|"Intensity:"
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
specifier|static
name|MenuItem
name|color_option_items
index|[]
init|=
block|{
block|{
name|N_
argument_list|(
literal|"Value"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|histogram_tool_value_callback
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Red"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|histogram_tool_red_callback
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Green"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|histogram_tool_green_callback
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Blue"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|histogram_tool_blue_callback
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
name|htd
operator|=
operator|(
name|HistogramToolDialog
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|HistogramToolDialog
argument_list|)
argument_list|)
expr_stmt|;
name|htd
operator|->
name|channel
operator|=
name|HISTOGRAM_VALUE
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
name|color_option_items
index|[
name|i
index|]
operator|.
name|user_data
operator|=
operator|(
name|gpointer
operator|)
name|htd
expr_stmt|;
name|htd
operator|->
name|hist
operator|=
name|gimp_histogram_new
argument_list|()
expr_stmt|;
comment|/*  The shell and main vbox  */
name|htd
operator|->
name|shell
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|htd
operator|->
name|shell
argument_list|)
argument_list|,
literal|"histogram"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|htd
operator|->
name|shell
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Histogram"
argument_list|)
argument_list|)
expr_stmt|;
comment|/* handle the wm close signal */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|htd
operator|->
name|shell
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|histogram_tool_delete_callback
argument_list|,
name|htd
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|2
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
comment|/*  The vbox for the menu and histogram  */
name|vbox2
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
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
name|vbox2
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  The option menu for selecting channels  */
name|htd
operator|->
name|channel_menu
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
name|vbox2
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
name|htd
operator|->
name|channel_menu
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
name|menu
operator|=
name|build_menu
argument_list|(
name|color_option_items
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|option_menu
operator|=
name|gtk_option_menu_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|htd
operator|->
name|channel_menu
argument_list|)
argument_list|,
name|option_menu
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
name|gtk_widget_show
argument_list|(
name|option_menu
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|htd
operator|->
name|channel_menu
argument_list|)
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|option_menu
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
comment|/*  The histogram tool histogram  */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_ETCHED_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
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
name|htd
operator|->
name|histogram
operator|=
name|histogram_widget_new
argument_list|(
name|HISTOGRAM_WIDTH
argument_list|,
name|HISTOGRAM_HEIGHT
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|htd
operator|->
name|histogram
argument_list|)
argument_list|,
literal|"rangechanged"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|histogram_tool_histogram_range
argument_list|,
operator|(
name|void
operator|*
operator|)
name|htd
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|htd
operator|->
name|histogram
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|htd
operator|->
name|histogram
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox2
argument_list|)
expr_stmt|;
comment|/*  The table containing histogram information  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|4
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
comment|/*  the labels for histogram information  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|7
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
literal|4
operator|)
expr_stmt|;
name|x
operator|=
operator|(
name|i
operator|/
literal|4
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
comment|/*  The action area  */
name|action_items
index|[
literal|0
index|]
operator|.
name|user_data
operator|=
name|htd
expr_stmt|;
name|build_action_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|htd
operator|->
name|shell
argument_list|)
argument_list|,
name|action_items
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
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
DECL|function|histogram_tool_close_callback (GtkWidget * widget,gpointer client_data)
name|histogram_tool_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|HistogramToolDialog
modifier|*
name|htd
decl_stmt|;
name|htd
operator|=
operator|(
name|HistogramToolDialog
operator|*
operator|)
name|client_data
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|htd
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|htd
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|histogram_tool_delete_callback (GtkWidget * widget,GdkEvent * event,gpointer client_data)
name|histogram_tool_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|histogram_tool_close_callback
argument_list|(
name|widget
argument_list|,
name|client_data
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|histogram_tool_value_callback (GtkWidget * w,gpointer client_data)
name|histogram_tool_value_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|HistogramToolDialog
modifier|*
name|htd
decl_stmt|;
name|htd
operator|=
operator|(
name|HistogramToolDialog
operator|*
operator|)
name|client_data
expr_stmt|;
if|if
condition|(
name|htd
operator|->
name|channel
operator|!=
name|HISTOGRAM_VALUE
condition|)
block|{
name|htd
operator|->
name|channel
operator|=
name|HISTOGRAM_VALUE
expr_stmt|;
name|histogram_widget_channel
argument_list|(
name|htd
operator|->
name|histogram
argument_list|,
name|htd
operator|->
name|channel
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|histogram_tool_red_callback (GtkWidget * w,gpointer client_data)
name|histogram_tool_red_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|HistogramToolDialog
modifier|*
name|htd
decl_stmt|;
name|htd
operator|=
operator|(
name|HistogramToolDialog
operator|*
operator|)
name|client_data
expr_stmt|;
if|if
condition|(
name|htd
operator|->
name|channel
operator|!=
name|HISTOGRAM_RED
condition|)
block|{
name|htd
operator|->
name|channel
operator|=
name|HISTOGRAM_RED
expr_stmt|;
name|histogram_widget_channel
argument_list|(
name|htd
operator|->
name|histogram
argument_list|,
name|htd
operator|->
name|channel
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|histogram_tool_green_callback (GtkWidget * w,gpointer client_data)
name|histogram_tool_green_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|HistogramToolDialog
modifier|*
name|htd
decl_stmt|;
name|htd
operator|=
operator|(
name|HistogramToolDialog
operator|*
operator|)
name|client_data
expr_stmt|;
if|if
condition|(
name|htd
operator|->
name|channel
operator|!=
name|HISTOGRAM_GREEN
condition|)
block|{
name|htd
operator|->
name|channel
operator|=
name|HISTOGRAM_GREEN
expr_stmt|;
name|histogram_widget_channel
argument_list|(
name|htd
operator|->
name|histogram
argument_list|,
name|htd
operator|->
name|channel
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|histogram_tool_blue_callback (GtkWidget * w,gpointer client_data)
name|histogram_tool_blue_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|HistogramToolDialog
modifier|*
name|htd
decl_stmt|;
name|htd
operator|=
operator|(
name|HistogramToolDialog
operator|*
operator|)
name|client_data
expr_stmt|;
if|if
condition|(
name|htd
operator|->
name|channel
operator|!=
name|HISTOGRAM_BLUE
condition|)
block|{
name|htd
operator|->
name|channel
operator|=
name|HISTOGRAM_BLUE
expr_stmt|;
name|histogram_widget_channel
argument_list|(
name|htd
operator|->
name|histogram
argument_list|,
name|htd
operator|->
name|channel
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

