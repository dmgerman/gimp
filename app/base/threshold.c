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
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"threshold.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|HISTOGRAM_WIDTH
define|#
directive|define
name|HISTOGRAM_WIDTH
value|256
end_define

begin_define
DECL|macro|HISTOGRAM_HEIGHT
define|#
directive|define
name|HISTOGRAM_HEIGHT
value|150
end_define

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
DECL|macro|HISTORGAM
define|#
directive|define
name|HISTORGAM
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
comment|/*  the threshold structures  */
end_comment

begin_typedef
DECL|typedef|Threshold
typedef|typedef
name|struct
name|_Threshold
name|Threshold
typedef|;
end_typedef

begin_struct
DECL|struct|_Threshold
struct|struct
name|_Threshold
block|{
DECL|member|x
DECL|member|y
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  coords for last mouse click  */
block|}
struct|;
end_struct

begin_comment
comment|/*  the threshold tool options  */
end_comment

begin_decl_stmt
DECL|variable|threshold_options
specifier|static
name|ToolOptions
modifier|*
name|threshold_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  the threshold tool dialog  */
end_comment

begin_decl_stmt
DECL|variable|threshold_dialog
specifier|static
name|ThresholdDialog
modifier|*
name|threshold_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  threshold action functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|threshold_control
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
name|ThresholdDialog
modifier|*
name|threshold_dialog_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|threshold_update
parameter_list|(
name|ThresholdDialog
modifier|*
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|threshold_preview
parameter_list|(
name|ThresholdDialog
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|threshold_reset_callback
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
name|threshold_ok_callback
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
name|threshold_cancel_callback
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
name|threshold_preview_update
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
name|threshold_low_threshold_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|threshold_high_threshold_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|threshold
parameter_list|(
name|PixelRegion
modifier|*
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|threshold_histogram_range
parameter_list|(
name|HistogramWidget
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  threshold machinery  */
end_comment

begin_function
name|void
DECL|function|threshold_2 (void * data,PixelRegion * srcPR,PixelRegion * destPR)
name|threshold_2
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
block|{
comment|/*  this function just re-orders the arguments so we can use     *  pixel_regions_process_paralell    */
name|threshold
argument_list|(
name|srcPR
argument_list|,
name|destPR
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|threshold (PixelRegion * srcPR,PixelRegion * destPR,void * data)
name|threshold
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
block|{
name|ThresholdDialog
modifier|*
name|td
decl_stmt|;
name|unsigned
name|char
modifier|*
name|src
decl_stmt|,
modifier|*
name|s
decl_stmt|;
name|unsigned
name|char
modifier|*
name|dest
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|int
name|has_alpha
decl_stmt|,
name|alpha
decl_stmt|;
name|int
name|w
decl_stmt|,
name|h
decl_stmt|,
name|b
decl_stmt|;
name|int
name|value
decl_stmt|;
name|td
operator|=
operator|(
name|ThresholdDialog
operator|*
operator|)
name|data
expr_stmt|;
name|h
operator|=
name|srcPR
operator|->
name|h
expr_stmt|;
name|src
operator|=
name|srcPR
operator|->
name|data
expr_stmt|;
name|dest
operator|=
name|destPR
operator|->
name|data
expr_stmt|;
name|has_alpha
operator|=
operator|(
name|srcPR
operator|->
name|bytes
operator|==
literal|2
operator|||
name|srcPR
operator|->
name|bytes
operator|==
literal|4
operator|)
expr_stmt|;
name|alpha
operator|=
name|has_alpha
condition|?
name|srcPR
operator|->
name|bytes
operator|-
literal|1
else|:
name|srcPR
operator|->
name|bytes
expr_stmt|;
while|while
condition|(
name|h
operator|--
condition|)
block|{
name|w
operator|=
name|srcPR
operator|->
name|w
expr_stmt|;
name|s
operator|=
name|src
expr_stmt|;
name|d
operator|=
name|dest
expr_stmt|;
while|while
condition|(
name|w
operator|--
condition|)
block|{
if|if
condition|(
name|td
operator|->
name|color
condition|)
block|{
name|value
operator|=
name|MAX
argument_list|(
name|s
index|[
name|RED_PIX
index|]
argument_list|,
name|s
index|[
name|GREEN_PIX
index|]
argument_list|)
expr_stmt|;
name|value
operator|=
name|MAX
argument_list|(
name|value
argument_list|,
name|s
index|[
name|BLUE_PIX
index|]
argument_list|)
expr_stmt|;
name|value
operator|=
operator|(
name|value
operator|>=
name|td
operator|->
name|low_threshold
operator|&&
name|value
operator|<=
name|td
operator|->
name|high_threshold
operator|)
condition|?
literal|255
else|:
literal|0
expr_stmt|;
block|}
else|else
name|value
operator|=
operator|(
name|s
index|[
name|GRAY_PIX
index|]
operator|>=
name|td
operator|->
name|low_threshold
operator|&&
name|s
index|[
name|GRAY_PIX
index|]
operator|<=
name|td
operator|->
name|high_threshold
operator|)
condition|?
literal|255
else|:
literal|0
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|alpha
condition|;
name|b
operator|++
control|)
name|d
index|[
name|b
index|]
operator|=
name|value
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|d
index|[
name|alpha
index|]
operator|=
name|s
index|[
name|alpha
index|]
expr_stmt|;
name|s
operator|+=
name|srcPR
operator|->
name|bytes
expr_stmt|;
name|d
operator|+=
name|destPR
operator|->
name|bytes
expr_stmt|;
block|}
name|src
operator|+=
name|srcPR
operator|->
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|destPR
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  threshold action functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|threshold_control (Tool * tool,ToolAction action,gpointer gdisp_ptr)
name|threshold_control
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
name|threshold_dialog_hide
argument_list|()
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
DECL|function|tools_new_threshold (void)
name|tools_new_threshold
parameter_list|(
name|void
parameter_list|)
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|Threshold
modifier|*
name|private
decl_stmt|;
comment|/*  The tool options  */
if|if
condition|(
operator|!
name|threshold_options
condition|)
block|{
name|threshold_options
operator|=
name|tool_options_new
argument_list|(
name|_
argument_list|(
literal|"Threshold"
argument_list|)
argument_list|)
expr_stmt|;
name|tools_register
argument_list|(
name|THRESHOLD
argument_list|,
name|threshold_options
argument_list|)
expr_stmt|;
block|}
name|tool
operator|=
name|tools_new_tool
argument_list|(
name|THRESHOLD
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_new0
argument_list|(
name|Threshold
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
name|TRUE
expr_stmt|;
comment|/*  Disallow scrolling  */
name|tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
comment|/*  Don't preserve on drawable change  */
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
name|control_func
operator|=
name|threshold_control
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|threshold_dialog_hide (void)
name|threshold_dialog_hide
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|threshold_dialog
condition|)
name|threshold_cancel_callback
argument_list|(
name|NULL
argument_list|,
operator|(
name|gpointer
operator|)
name|threshold_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_threshold (Tool * tool)
name|tools_free_threshold
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|Threshold
modifier|*
name|thresh
decl_stmt|;
name|thresh
operator|=
operator|(
name|Threshold
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
comment|/*  Close the threshold dialog  */
name|threshold_dialog_hide
argument_list|()
expr_stmt|;
name|g_free
argument_list|(
name|thresh
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|threshold_initialize (GDisplay * gdisp)
name|threshold_initialize
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
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
literal|"Threshold does not operate on indexed drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  The threshold dialog  */
if|if
condition|(
operator|!
name|threshold_dialog
condition|)
name|threshold_dialog
operator|=
name|threshold_dialog_new
argument_list|()
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|threshold_dialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|threshold_dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
name|threshold_dialog
operator|->
name|low_threshold
operator|=
literal|127
expr_stmt|;
name|threshold_dialog
operator|->
name|high_threshold
operator|=
literal|255
expr_stmt|;
name|threshold_dialog
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
name|threshold_dialog
operator|->
name|color
operator|=
name|drawable_color
argument_list|(
name|threshold_dialog
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|threshold_dialog
operator|->
name|image_map
operator|=
name|image_map_create
argument_list|(
name|gdisp
argument_list|,
name|threshold_dialog
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|gimp_histogram_calculate_drawable
argument_list|(
name|threshold_dialog
operator|->
name|hist
argument_list|,
name|threshold_dialog
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|threshold_dialog
operator|->
name|histogram
argument_list|)
argument_list|,
name|threshold_dialog
argument_list|)
expr_stmt|;
name|histogram_widget_update
argument_list|(
name|threshold_dialog
operator|->
name|histogram
argument_list|,
name|threshold_dialog
operator|->
name|hist
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|threshold_dialog
operator|->
name|histogram
argument_list|)
argument_list|,
name|threshold_dialog
argument_list|)
expr_stmt|;
name|threshold_update
argument_list|(
name|threshold_dialog
argument_list|,
name|ALL
argument_list|)
expr_stmt|;
if|if
condition|(
name|threshold_dialog
operator|->
name|preview
condition|)
name|threshold_preview
argument_list|(
name|threshold_dialog
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
name|ThresholdDialog
modifier|*
DECL|function|threshold_dialog_new (void)
name|threshold_dialog_new
parameter_list|(
name|void
parameter_list|)
block|{
name|ThresholdDialog
modifier|*
name|td
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkObject
modifier|*
name|data
decl_stmt|;
name|td
operator|=
name|g_new
argument_list|(
name|ThresholdDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|td
operator|->
name|preview
operator|=
name|TRUE
expr_stmt|;
name|td
operator|->
name|low_threshold
operator|=
literal|127
expr_stmt|;
name|td
operator|->
name|high_threshold
operator|=
literal|255
expr_stmt|;
name|td
operator|->
name|hist
operator|=
name|gimp_histogram_new
argument_list|()
expr_stmt|;
comment|/*  The shell and main vbox  */
name|td
operator|->
name|shell
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Threshold"
argument_list|)
argument_list|,
literal|"threshold"
argument_list|,
name|tools_help_func
argument_list|,
name|NULL
argument_list|,
name|GTK_WIN_POS_NONE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"OK"
argument_list|)
argument_list|,
name|threshold_ok_callback
argument_list|,
name|td
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Reset"
argument_list|)
argument_list|,
name|threshold_reset_callback
argument_list|,
name|td
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Cancel"
argument_list|)
argument_list|,
name|threshold_cancel_callback
argument_list|,
name|td
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
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
name|td
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
comment|/*  Horizontal box for threshold text widget  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
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
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Threshold Range:"
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
comment|/*  low threshold spinbutton  */
name|data
operator|=
name|gtk_adjustment_new
argument_list|(
name|td
operator|->
name|low_threshold
argument_list|,
literal|0.0
argument_list|,
literal|255.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|td
operator|->
name|low_threshold_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gtk_spin_button_new
argument_list|(
name|td
operator|->
name|low_threshold_data
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|spinbutton
argument_list|,
literal|75
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|spinbutton
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|td
operator|->
name|low_threshold_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|threshold_low_threshold_adjustment_update
argument_list|)
argument_list|,
name|td
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
comment|/* high threshold spinbutton  */
name|data
operator|=
name|gtk_adjustment_new
argument_list|(
name|td
operator|->
name|high_threshold
argument_list|,
literal|0.0
argument_list|,
literal|255.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|td
operator|->
name|high_threshold_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gtk_spin_button_new
argument_list|(
name|td
operator|->
name|high_threshold_data
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|spinbutton
argument_list|,
literal|75
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|spinbutton
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|td
operator|->
name|high_threshold_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|threshold_high_threshold_adjustment_update
argument_list|)
argument_list|,
name|td
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
comment|/*  The threshold histogram  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
literal|0
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
name|hbox
argument_list|)
argument_list|,
name|frame
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|td
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|td
operator|->
name|histogram
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|td
operator|->
name|histogram
argument_list|)
argument_list|,
literal|"rangechanged"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|threshold_histogram_range
argument_list|)
argument_list|,
name|td
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|td
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
name|hbox
argument_list|)
expr_stmt|;
comment|/*  Horizontal box for preview  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
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
comment|/*  The preview toggle  */
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Preview"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|td
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|threshold_preview_update
argument_list|)
argument_list|,
name|td
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|td
operator|->
name|shell
argument_list|)
expr_stmt|;
return|return
name|td
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|threshold_update (ThresholdDialog * td,gint update)
name|threshold_update
parameter_list|(
name|ThresholdDialog
modifier|*
name|td
parameter_list|,
name|gint
name|update
parameter_list|)
block|{
if|if
condition|(
name|update
operator|&
name|LOW
condition|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|td
operator|->
name|low_threshold_data
argument_list|,
name|td
operator|->
name|low_threshold
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|update
operator|&
name|HIGH
condition|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|td
operator|->
name|high_threshold_data
argument_list|,
name|td
operator|->
name|high_threshold
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|update
operator|&
name|HISTOGRAM
condition|)
block|{
name|histogram_widget_range
argument_list|(
name|td
operator|->
name|histogram
argument_list|,
name|td
operator|->
name|low_threshold
argument_list|,
name|td
operator|->
name|high_threshold
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|threshold_preview (ThresholdDialog * td)
name|threshold_preview
parameter_list|(
name|ThresholdDialog
modifier|*
name|td
parameter_list|)
block|{
if|if
condition|(
operator|!
name|td
operator|->
name|image_map
condition|)
block|{
name|g_warning
argument_list|(
literal|"threshold_preview(): No image map"
argument_list|)
expr_stmt|;
return|return;
block|}
name|active_tool
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
name|image_map_apply
argument_list|(
name|td
operator|->
name|image_map
argument_list|,
name|threshold
argument_list|,
name|td
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|threshold_reset_callback (GtkWidget * widget,gpointer data)
name|threshold_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ThresholdDialog
modifier|*
name|td
decl_stmt|;
name|td
operator|=
operator|(
name|ThresholdDialog
operator|*
operator|)
name|data
expr_stmt|;
name|td
operator|->
name|low_threshold
operator|=
literal|127.0
expr_stmt|;
name|td
operator|->
name|high_threshold
operator|=
literal|255.0
expr_stmt|;
name|threshold_update
argument_list|(
name|td
argument_list|,
name|ALL
argument_list|)
expr_stmt|;
if|if
condition|(
name|td
operator|->
name|preview
condition|)
name|threshold_preview
argument_list|(
name|td
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|threshold_ok_callback (GtkWidget * widget,gpointer data)
name|threshold_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ThresholdDialog
modifier|*
name|td
decl_stmt|;
name|td
operator|=
operator|(
name|ThresholdDialog
operator|*
operator|)
name|data
expr_stmt|;
name|gimp_dialog_hide
argument_list|(
name|td
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|!
name|td
operator|->
name|preview
condition|)
name|image_map_apply
argument_list|(
name|td
operator|->
name|image_map
argument_list|,
name|threshold
argument_list|,
operator|(
name|void
operator|*
operator|)
name|td
argument_list|)
expr_stmt|;
if|if
condition|(
name|td
operator|->
name|image_map
condition|)
name|image_map_commit
argument_list|(
name|td
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
name|td
operator|->
name|image_map
operator|=
name|NULL
expr_stmt|;
name|active_tool
operator|->
name|gdisp_ptr
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
name|void
DECL|function|threshold_cancel_callback (GtkWidget * widget,gpointer data)
name|threshold_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ThresholdDialog
modifier|*
name|td
decl_stmt|;
name|td
operator|=
operator|(
name|ThresholdDialog
operator|*
operator|)
name|data
expr_stmt|;
name|gimp_dialog_hide
argument_list|(
name|td
operator|->
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|td
operator|->
name|image_map
condition|)
block|{
name|active_tool
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
name|image_map_abort
argument_list|(
name|td
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
name|td
operator|->
name|image_map
operator|=
name|NULL
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
name|active_tool
operator|->
name|gdisp_ptr
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
name|void
DECL|function|threshold_preview_update (GtkWidget * widget,gpointer data)
name|threshold_preview_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ThresholdDialog
modifier|*
name|td
decl_stmt|;
name|td
operator|=
operator|(
name|ThresholdDialog
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
block|{
name|td
operator|->
name|preview
operator|=
name|TRUE
expr_stmt|;
name|threshold_preview
argument_list|(
name|td
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|td
operator|->
name|preview
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|td
operator|->
name|image_map
condition|)
block|{
name|active_tool
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
name|image_map_clear
argument_list|(
name|td
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|threshold_low_threshold_adjustment_update (GtkAdjustment * adjustment,gpointer data)
name|threshold_low_threshold_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ThresholdDialog
modifier|*
name|td
decl_stmt|;
name|td
operator|=
operator|(
name|ThresholdDialog
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|td
operator|->
name|low_threshold
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|td
operator|->
name|low_threshold
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|threshold_update
argument_list|(
name|td
argument_list|,
name|HISTOGRAM
argument_list|)
expr_stmt|;
if|if
condition|(
name|td
operator|->
name|preview
condition|)
name|threshold_preview
argument_list|(
name|td
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|threshold_high_threshold_adjustment_update (GtkAdjustment * adjustment,gpointer data)
name|threshold_high_threshold_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ThresholdDialog
modifier|*
name|td
decl_stmt|;
name|td
operator|=
operator|(
name|ThresholdDialog
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|td
operator|->
name|high_threshold
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|td
operator|->
name|high_threshold
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|threshold_update
argument_list|(
name|td
argument_list|,
name|HISTOGRAM
argument_list|)
expr_stmt|;
if|if
condition|(
name|td
operator|->
name|preview
condition|)
name|threshold_preview
argument_list|(
name|td
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|threshold_histogram_range (HistogramWidget * widget,gint start,gint end,gpointer data)
name|threshold_histogram_range
parameter_list|(
name|HistogramWidget
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
name|ThresholdDialog
modifier|*
name|td
decl_stmt|;
name|td
operator|=
operator|(
name|ThresholdDialog
operator|*
operator|)
name|data
expr_stmt|;
name|td
operator|->
name|low_threshold
operator|=
name|start
expr_stmt|;
name|td
operator|->
name|high_threshold
operator|=
name|end
expr_stmt|;
name|threshold_update
argument_list|(
name|td
argument_list|,
name|LOW
operator||
name|HIGH
argument_list|)
expr_stmt|;
if|if
condition|(
name|td
operator|->
name|preview
condition|)
name|threshold_preview
argument_list|(
name|td
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

