begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
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
file|"airbrush.h"
end_include

begin_include
include|#
directive|include
file|"bezier_select.h"
end_include

begin_include
include|#
directive|include
file|"blend.h"
end_include

begin_include
include|#
directive|include
file|"brightness_contrast.h"
end_include

begin_include
include|#
directive|include
file|"bucket_fill.h"
end_include

begin_include
include|#
directive|include
file|"by_color_select.h"
end_include

begin_include
include|#
directive|include
file|"clone.h"
end_include

begin_include
include|#
directive|include
file|"color_balance.h"
end_include

begin_include
include|#
directive|include
file|"color_picker.h"
end_include

begin_include
include|#
directive|include
file|"convolve.h"
end_include

begin_include
include|#
directive|include
file|"crop.h"
end_include

begin_include
include|#
directive|include
file|"cursorutil.h"
end_include

begin_include
include|#
directive|include
file|"curves.h"
end_include

begin_include
include|#
directive|include
file|"eraser.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"hue_saturation.h"
end_include

begin_include
include|#
directive|include
file|"ellipse_select.h"
end_include

begin_include
include|#
directive|include
file|"flip_tool.h"
end_include

begin_include
include|#
directive|include
file|"free_select.h"
end_include

begin_include
include|#
directive|include
file|"fuzzy_select.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"histogram_tool.h"
end_include

begin_include
include|#
directive|include
file|"interface.h"
end_include

begin_include
include|#
directive|include
file|"iscissors.h"
end_include

begin_include
include|#
directive|include
file|"levels.h"
end_include

begin_include
include|#
directive|include
file|"magnify.h"
end_include

begin_include
include|#
directive|include
file|"move.h"
end_include

begin_include
include|#
directive|include
file|"paintbrush.h"
end_include

begin_include
include|#
directive|include
file|"pencil.h"
end_include

begin_include
include|#
directive|include
file|"posterize.h"
end_include

begin_include
include|#
directive|include
file|"rect_select.h"
end_include

begin_include
include|#
directive|include
file|"text_tool.h"
end_include

begin_include
include|#
directive|include
file|"threshold.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"transform_tool.h"
end_include

begin_comment
comment|/* Global Data */
end_comment

begin_decl_stmt
DECL|variable|active_tool
name|Tool
modifier|*
name|active_tool
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|active_tool_layer
name|Layer
modifier|*
name|active_tool_layer
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Local Data */
end_comment

begin_decl_stmt
DECL|variable|options_shell
specifier|static
name|GtkWidget
modifier|*
name|options_shell
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|options_vbox
specifier|static
name|GtkWidget
modifier|*
name|options_vbox
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|active_tool_type
specifier|static
name|ToolType
name|active_tool_type
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|global_tool_ID
specifier|static
name|int
name|global_tool_ID
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tool_info
name|ToolInfo
name|tool_info
index|[]
init|=
block|{
block|{
name|NULL
block|,
literal|"Rect Select"
block|,
literal|0
block|}
block|,
block|{
name|NULL
block|,
literal|"Ellipse Select"
block|,
literal|1
block|}
block|,
block|{
name|NULL
block|,
literal|"Free Select"
block|,
literal|2
block|}
block|,
block|{
name|NULL
block|,
literal|"Fuzzy Select"
block|,
literal|3
block|}
block|,
block|{
name|NULL
block|,
literal|"Bezier Select"
block|,
literal|4
block|}
block|,
block|{
name|NULL
block|,
literal|"Intelligent Scissors"
block|,
literal|5
block|}
block|,
block|{
name|NULL
block|,
literal|"Move"
block|,
literal|6
block|}
block|,
block|{
name|NULL
block|,
literal|"Magnify"
block|,
literal|7
block|}
block|,
block|{
name|NULL
block|,
literal|"Crop"
block|,
literal|8
block|}
block|,
block|{
name|NULL
block|,
literal|"Transform"
block|,
literal|9
block|}
block|,
comment|/* rotate */
block|{
name|NULL
block|,
literal|"Transform"
block|,
literal|9
block|}
block|,
comment|/* scale */
block|{
name|NULL
block|,
literal|"Transform"
block|,
literal|9
block|}
block|,
comment|/* shear */
block|{
name|NULL
block|,
literal|"Transform"
block|,
literal|9
block|}
block|,
comment|/* perspective */
block|{
name|NULL
block|,
literal|"Flip"
block|,
literal|10
block|}
block|,
comment|/* horizontal */
block|{
name|NULL
block|,
literal|"Flip"
block|,
literal|10
block|}
block|,
comment|/* vertical */
block|{
name|NULL
block|,
literal|"Text"
block|,
literal|11
block|}
block|,
block|{
name|NULL
block|,
literal|"Color Picker"
block|,
literal|12
block|}
block|,
block|{
name|NULL
block|,
literal|"Bucket Fill"
block|,
literal|13
block|}
block|,
block|{
name|NULL
block|,
literal|"Blend"
block|,
literal|14
block|}
block|,
block|{
name|NULL
block|,
literal|"Pencil"
block|,
literal|15
block|}
block|,
block|{
name|NULL
block|,
literal|"Paintbrush"
block|,
literal|16
block|}
block|,
block|{
name|NULL
block|,
literal|"Eraser"
block|,
literal|17
block|}
block|,
block|{
name|NULL
block|,
literal|"Airbrush"
block|,
literal|18
block|}
block|,
block|{
name|NULL
block|,
literal|"Clone"
block|,
literal|19
block|}
block|,
block|{
name|NULL
block|,
literal|"Convolve"
block|,
literal|20
block|}
block|,
comment|/*  Non-toolbox tools  */
block|{
name|NULL
block|,
literal|"By Color Select"
block|,
literal|21
block|}
block|,
block|{
name|NULL
block|,
literal|"Color Balance"
block|,
literal|22
block|}
block|,
block|{
name|NULL
block|,
literal|"Brightness-Contrast"
block|,
literal|23
block|}
block|,
block|{
name|NULL
block|,
literal|"Hue-Saturation"
block|,
literal|24
block|}
block|,
block|{
name|NULL
block|,
literal|"Posterize"
block|,
literal|25
block|}
block|,
block|{
name|NULL
block|,
literal|"Threshold"
block|,
literal|26
block|}
block|,
block|{
name|NULL
block|,
literal|"Curves"
block|,
literal|27
block|}
block|,
block|{
name|NULL
block|,
literal|"Levels"
block|,
literal|28
block|}
block|,
block|{
name|NULL
block|,
literal|"Histogram"
block|,
literal|29
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Local function declarations  */
end_comment

begin_function_decl
specifier|static
name|void
name|tools_options_dialog_callback
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
name|tools_options_delete_callback
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

begin_comment
comment|/* Function definitions */
end_comment

begin_function
specifier|static
name|void
DECL|function|active_tool_free (void)
name|active_tool_free
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_container_disable_resize
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|options_shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
index|[
operator|(
name|int
operator|)
name|active_tool
operator|->
name|type
index|]
operator|.
name|tool_options
condition|)
name|gtk_widget_hide
argument_list|(
name|tool_info
index|[
operator|(
name|int
operator|)
name|active_tool
operator|->
name|type
index|]
operator|.
name|tool_options
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|active_tool
operator|->
name|type
condition|)
block|{
case|case
name|RECT_SELECT
case|:
name|tools_free_rect_select
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|ELLIPSE_SELECT
case|:
name|tools_free_ellipse_select
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|FREE_SELECT
case|:
name|tools_free_free_select
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|FUZZY_SELECT
case|:
name|tools_free_fuzzy_select
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|BEZIER_SELECT
case|:
name|tools_free_bezier_select
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|ISCISSORS
case|:
name|tools_free_iscissors
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|CROP
case|:
name|tools_free_crop
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|MOVE
case|:
name|tools_free_move_tool
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|MAGNIFY
case|:
name|tools_free_magnify
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|ROTATE
case|:
name|tools_free_transform_tool
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|SCALE
case|:
name|tools_free_transform_tool
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|SHEAR
case|:
name|tools_free_transform_tool
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|PERSPECTIVE
case|:
name|tools_free_transform_tool
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|FLIP_HORZ
case|:
name|tools_free_flip_tool
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|FLIP_VERT
case|:
name|tools_free_flip_tool
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|TEXT
case|:
name|tools_free_text
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|COLOR_PICKER
case|:
name|tools_free_color_picker
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|BUCKET_FILL
case|:
name|tools_free_bucket_fill
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|BLEND
case|:
name|tools_free_blend
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|PENCIL
case|:
name|tools_free_pencil
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|PAINTBRUSH
case|:
name|tools_free_paintbrush
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|ERASER
case|:
name|tools_free_eraser
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|AIRBRUSH
case|:
name|tools_free_airbrush
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|CLONE
case|:
name|tools_free_clone
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|CONVOLVE
case|:
name|tools_free_convolve
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|BY_COLOR_SELECT
case|:
name|tools_free_by_color_select
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|COLOR_BALANCE
case|:
name|tools_free_color_balance
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|BRIGHTNESS_CONTRAST
case|:
name|tools_free_brightness_contrast
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|HUE_SATURATION
case|:
name|tools_free_hue_saturation
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|POSTERIZE
case|:
name|tools_free_posterize
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|THRESHOLD
case|:
name|tools_free_threshold
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|CURVES
case|:
name|tools_free_curves
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|LEVELS
case|:
name|tools_free_levels
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|HISTOGRAM
case|:
name|tools_free_histogram_tool
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
break|break;
default|default:
return|return;
block|}
name|g_free
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
name|active_tool
operator|=
name|NULL
expr_stmt|;
name|active_tool_layer
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_select (ToolType type)
name|tools_select
parameter_list|(
name|ToolType
name|type
parameter_list|)
block|{
if|if
condition|(
name|active_tool
condition|)
name|active_tool_free
argument_list|()
expr_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|RECT_SELECT
case|:
name|active_tool
operator|=
name|tools_new_rect_select
argument_list|()
expr_stmt|;
break|break;
case|case
name|ELLIPSE_SELECT
case|:
name|active_tool
operator|=
name|tools_new_ellipse_select
argument_list|()
expr_stmt|;
break|break;
case|case
name|FREE_SELECT
case|:
name|active_tool
operator|=
name|tools_new_free_select
argument_list|()
expr_stmt|;
break|break;
case|case
name|FUZZY_SELECT
case|:
name|active_tool
operator|=
name|tools_new_fuzzy_select
argument_list|()
expr_stmt|;
break|break;
case|case
name|BEZIER_SELECT
case|:
name|active_tool
operator|=
name|tools_new_bezier_select
argument_list|()
expr_stmt|;
break|break;
case|case
name|ISCISSORS
case|:
name|active_tool
operator|=
name|tools_new_iscissors
argument_list|()
expr_stmt|;
break|break;
case|case
name|MOVE
case|:
name|active_tool
operator|=
name|tools_new_move_tool
argument_list|()
expr_stmt|;
break|break;
case|case
name|MAGNIFY
case|:
name|active_tool
operator|=
name|tools_new_magnify
argument_list|()
expr_stmt|;
break|break;
case|case
name|CROP
case|:
name|active_tool
operator|=
name|tools_new_crop
argument_list|()
expr_stmt|;
break|break;
case|case
name|ROTATE
case|:
name|active_tool
operator|=
name|tools_new_transform_tool
argument_list|()
expr_stmt|;
break|break;
case|case
name|SCALE
case|:
name|active_tool
operator|=
name|tools_new_transform_tool
argument_list|()
expr_stmt|;
break|break;
case|case
name|SHEAR
case|:
name|active_tool
operator|=
name|tools_new_transform_tool
argument_list|()
expr_stmt|;
break|break;
case|case
name|PERSPECTIVE
case|:
name|active_tool
operator|=
name|tools_new_transform_tool
argument_list|()
expr_stmt|;
break|break;
case|case
name|FLIP_HORZ
case|:
name|active_tool
operator|=
name|tools_new_flip
argument_list|()
expr_stmt|;
break|break;
case|case
name|FLIP_VERT
case|:
name|active_tool
operator|=
name|tools_new_flip
argument_list|()
expr_stmt|;
break|break;
case|case
name|TEXT
case|:
name|active_tool
operator|=
name|tools_new_text
argument_list|()
expr_stmt|;
break|break;
case|case
name|COLOR_PICKER
case|:
name|active_tool
operator|=
name|tools_new_color_picker
argument_list|()
expr_stmt|;
break|break;
case|case
name|BUCKET_FILL
case|:
name|active_tool
operator|=
name|tools_new_bucket_fill
argument_list|()
expr_stmt|;
break|break;
case|case
name|BLEND
case|:
name|active_tool
operator|=
name|tools_new_blend
argument_list|()
expr_stmt|;
break|break;
case|case
name|PENCIL
case|:
name|active_tool
operator|=
name|tools_new_pencil
argument_list|()
expr_stmt|;
break|break;
case|case
name|PAINTBRUSH
case|:
name|active_tool
operator|=
name|tools_new_paintbrush
argument_list|()
expr_stmt|;
break|break;
case|case
name|ERASER
case|:
name|active_tool
operator|=
name|tools_new_eraser
argument_list|()
expr_stmt|;
break|break;
case|case
name|AIRBRUSH
case|:
name|active_tool
operator|=
name|tools_new_airbrush
argument_list|()
expr_stmt|;
break|break;
case|case
name|CLONE
case|:
name|active_tool
operator|=
name|tools_new_clone
argument_list|()
expr_stmt|;
break|break;
case|case
name|CONVOLVE
case|:
name|active_tool
operator|=
name|tools_new_convolve
argument_list|()
expr_stmt|;
break|break;
case|case
name|BY_COLOR_SELECT
case|:
name|active_tool
operator|=
name|tools_new_by_color_select
argument_list|()
expr_stmt|;
break|break;
case|case
name|COLOR_BALANCE
case|:
name|active_tool
operator|=
name|tools_new_color_balance
argument_list|()
expr_stmt|;
break|break;
case|case
name|BRIGHTNESS_CONTRAST
case|:
name|active_tool
operator|=
name|tools_new_brightness_contrast
argument_list|()
expr_stmt|;
break|break;
case|case
name|HUE_SATURATION
case|:
name|active_tool
operator|=
name|tools_new_hue_saturation
argument_list|()
expr_stmt|;
break|break;
case|case
name|POSTERIZE
case|:
name|active_tool
operator|=
name|tools_new_posterize
argument_list|()
expr_stmt|;
break|break;
case|case
name|THRESHOLD
case|:
name|active_tool
operator|=
name|tools_new_threshold
argument_list|()
expr_stmt|;
break|break;
case|case
name|CURVES
case|:
name|active_tool
operator|=
name|tools_new_curves
argument_list|()
expr_stmt|;
break|break;
case|case
name|LEVELS
case|:
name|active_tool
operator|=
name|tools_new_levels
argument_list|()
expr_stmt|;
break|break;
case|case
name|HISTOGRAM
case|:
name|active_tool
operator|=
name|tools_new_histogram_tool
argument_list|()
expr_stmt|;
break|break;
default|default:
return|return;
block|}
comment|/*  Show the options for the active tool    */
if|if
condition|(
name|tool_info
index|[
operator|(
name|int
operator|)
name|active_tool
operator|->
name|type
index|]
operator|.
name|tool_options
condition|)
name|gtk_widget_show
argument_list|(
name|tool_info
index|[
operator|(
name|int
operator|)
name|active_tool
operator|->
name|type
index|]
operator|.
name|tool_options
argument_list|)
expr_stmt|;
name|gtk_container_enable_resize
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|options_shell
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Set the paused count variable to 0    */
name|active_tool
operator|->
name|paused_count
operator|=
literal|0
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
name|active_tool
operator|->
name|ID
operator|=
name|global_tool_ID
operator|++
expr_stmt|;
name|active_tool_type
operator|=
name|active_tool
operator|->
name|type
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_initialize (ToolType type,GDisplay * gdisp_ptr)
name|tools_initialize
parameter_list|(
name|ToolType
name|type
parameter_list|,
name|GDisplay
modifier|*
name|gdisp_ptr
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
comment|/* If you're wondering... only these dialog type tools have init functions */
name|gdisp
operator|=
name|gdisp_ptr
expr_stmt|;
if|if
condition|(
name|active_tool
condition|)
name|active_tool_free
argument_list|()
expr_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|RECT_SELECT
case|:
name|active_tool
operator|=
name|tools_new_rect_select
argument_list|()
expr_stmt|;
break|break;
case|case
name|ELLIPSE_SELECT
case|:
name|active_tool
operator|=
name|tools_new_ellipse_select
argument_list|()
expr_stmt|;
break|break;
case|case
name|FREE_SELECT
case|:
name|active_tool
operator|=
name|tools_new_free_select
argument_list|()
expr_stmt|;
break|break;
case|case
name|FUZZY_SELECT
case|:
name|active_tool
operator|=
name|tools_new_fuzzy_select
argument_list|()
expr_stmt|;
break|break;
case|case
name|BEZIER_SELECT
case|:
name|active_tool
operator|=
name|tools_new_bezier_select
argument_list|()
expr_stmt|;
break|break;
case|case
name|ISCISSORS
case|:
name|active_tool
operator|=
name|tools_new_iscissors
argument_list|()
expr_stmt|;
break|break;
case|case
name|MOVE
case|:
name|active_tool
operator|=
name|tools_new_move_tool
argument_list|()
expr_stmt|;
break|break;
case|case
name|MAGNIFY
case|:
name|active_tool
operator|=
name|tools_new_magnify
argument_list|()
expr_stmt|;
break|break;
case|case
name|CROP
case|:
name|active_tool
operator|=
name|tools_new_crop
argument_list|()
expr_stmt|;
break|break;
case|case
name|ROTATE
case|:
name|active_tool
operator|=
name|tools_new_transform_tool
argument_list|()
expr_stmt|;
break|break;
case|case
name|SCALE
case|:
name|active_tool
operator|=
name|tools_new_transform_tool
argument_list|()
expr_stmt|;
break|break;
case|case
name|SHEAR
case|:
name|active_tool
operator|=
name|tools_new_transform_tool
argument_list|()
expr_stmt|;
break|break;
case|case
name|PERSPECTIVE
case|:
name|active_tool
operator|=
name|tools_new_transform_tool
argument_list|()
expr_stmt|;
break|break;
case|case
name|FLIP_HORZ
case|:
name|active_tool
operator|=
name|tools_new_flip
argument_list|()
expr_stmt|;
break|break;
case|case
name|FLIP_VERT
case|:
name|active_tool
operator|=
name|tools_new_flip
argument_list|()
expr_stmt|;
break|break;
case|case
name|TEXT
case|:
name|active_tool
operator|=
name|tools_new_text
argument_list|()
expr_stmt|;
break|break;
case|case
name|COLOR_PICKER
case|:
name|active_tool
operator|=
name|tools_new_color_picker
argument_list|()
expr_stmt|;
break|break;
case|case
name|BUCKET_FILL
case|:
name|active_tool
operator|=
name|tools_new_bucket_fill
argument_list|()
expr_stmt|;
break|break;
case|case
name|BLEND
case|:
name|active_tool
operator|=
name|tools_new_blend
argument_list|()
expr_stmt|;
break|break;
case|case
name|PENCIL
case|:
name|active_tool
operator|=
name|tools_new_pencil
argument_list|()
expr_stmt|;
break|break;
case|case
name|PAINTBRUSH
case|:
name|active_tool
operator|=
name|tools_new_paintbrush
argument_list|()
expr_stmt|;
break|break;
case|case
name|ERASER
case|:
name|active_tool
operator|=
name|tools_new_eraser
argument_list|()
expr_stmt|;
break|break;
case|case
name|AIRBRUSH
case|:
name|active_tool
operator|=
name|tools_new_airbrush
argument_list|()
expr_stmt|;
break|break;
case|case
name|CLONE
case|:
name|active_tool
operator|=
name|tools_new_clone
argument_list|()
expr_stmt|;
break|break;
case|case
name|CONVOLVE
case|:
name|active_tool
operator|=
name|tools_new_convolve
argument_list|()
expr_stmt|;
break|break;
case|case
name|BY_COLOR_SELECT
case|:
if|if
condition|(
name|gdisp
condition|)
block|{
name|active_tool
operator|=
name|tools_new_by_color_select
argument_list|()
expr_stmt|;
name|by_color_select_initialize
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|active_tool_free
argument_list|()
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|COLOR_BALANCE
case|:
if|if
condition|(
name|gdisp
condition|)
block|{
name|active_tool
operator|=
name|tools_new_color_balance
argument_list|()
expr_stmt|;
name|color_balance_initialize
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|active_tool_free
argument_list|()
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|BRIGHTNESS_CONTRAST
case|:
if|if
condition|(
name|gdisp
condition|)
block|{
name|active_tool
operator|=
name|tools_new_brightness_contrast
argument_list|()
expr_stmt|;
name|brightness_contrast_initialize
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|active_tool_free
argument_list|()
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|HUE_SATURATION
case|:
if|if
condition|(
name|gdisp
condition|)
block|{
name|active_tool
operator|=
name|tools_new_hue_saturation
argument_list|()
expr_stmt|;
name|hue_saturation_initialize
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|active_tool_free
argument_list|()
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|POSTERIZE
case|:
if|if
condition|(
name|gdisp
condition|)
block|{
name|active_tool
operator|=
name|tools_new_posterize
argument_list|()
expr_stmt|;
name|posterize_initialize
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|active_tool_free
argument_list|()
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|THRESHOLD
case|:
if|if
condition|(
name|gdisp
condition|)
block|{
name|active_tool
operator|=
name|tools_new_threshold
argument_list|()
expr_stmt|;
name|threshold_initialize
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|active_tool_free
argument_list|()
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|CURVES
case|:
if|if
condition|(
name|gdisp
condition|)
block|{
name|active_tool
operator|=
name|tools_new_curves
argument_list|()
expr_stmt|;
name|curves_initialize
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|active_tool_free
argument_list|()
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|LEVELS
case|:
if|if
condition|(
name|gdisp
condition|)
block|{
name|active_tool
operator|=
name|tools_new_levels
argument_list|()
expr_stmt|;
name|levels_initialize
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|active_tool_free
argument_list|()
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|HISTOGRAM
case|:
if|if
condition|(
name|gdisp
condition|)
block|{
name|active_tool
operator|=
name|tools_new_histogram_tool
argument_list|()
expr_stmt|;
name|histogram_tool_initialize
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|active_tool_free
argument_list|()
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
return|return;
block|}
comment|/*  Show the options for the active tool    */
if|if
condition|(
name|tool_info
index|[
operator|(
name|int
operator|)
name|active_tool
operator|->
name|type
index|]
operator|.
name|tool_options
condition|)
name|gtk_widget_show
argument_list|(
name|tool_info
index|[
operator|(
name|int
operator|)
name|active_tool
operator|->
name|type
index|]
operator|.
name|tool_options
argument_list|)
expr_stmt|;
name|gtk_container_enable_resize
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|options_shell
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Set the paused count variable to 0    */
if|if
condition|(
name|gdisp
condition|)
name|active_tool
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
name|active_tool
operator|->
name|gdisp_ptr
operator|=
name|NULL
expr_stmt|;
name|active_tool
operator|->
name|ID
operator|=
name|global_tool_ID
operator|++
expr_stmt|;
name|active_tool_type
operator|=
name|active_tool
operator|->
name|type
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_options_dialog_new ()
name|tools_options_dialog_new
parameter_list|()
block|{
name|ActionAreaItem
name|action_items
index|[
literal|1
index|]
init|=
block|{
block|{
literal|"Close"
block|,
name|tools_options_dialog_callback
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
comment|/*  The shell and main vbox  */
name|options_shell
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|options_shell
argument_list|)
argument_list|,
literal|"tool_options"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|options_shell
argument_list|)
argument_list|,
literal|"Tool Options"
argument_list|)
expr_stmt|;
name|gtk_window_set_policy
argument_list|(
name|GTK_WINDOW
argument_list|(
name|options_shell
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_set_uposition
argument_list|(
name|options_shell
argument_list|,
name|tool_options_x
argument_list|,
name|tool_options_y
argument_list|)
expr_stmt|;
name|options_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|options_vbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|options_shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|options_vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* handle the window manager trying to close the window */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options_shell
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|tools_options_delete_callback
argument_list|)
argument_list|,
name|options_shell
argument_list|)
expr_stmt|;
name|action_items
index|[
literal|0
index|]
operator|.
name|user_data
operator|=
name|options_shell
expr_stmt|;
name|build_action_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|options_shell
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
name|options_vbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_options_dialog_show ()
name|tools_options_dialog_show
parameter_list|()
block|{
comment|/* menus_activate_callback() will destroy the active tool in many      cases.  if the user tries to bring up the options before      switching tools, the dialog will be empty.  recreate the active      tool here if necessary to avoid this behavior */
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|options_shell
argument_list|)
condition|)
block|{
name|gtk_widget_show
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdk_window_raise
argument_list|(
name|options_shell
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_options_dialog_free ()
name|tools_options_dialog_free
parameter_list|()
block|{
name|gtk_widget_destroy
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_register_options (ToolType type,GtkWidget * options)
name|tools_register_options
parameter_list|(
name|ToolType
name|type
parameter_list|,
name|GtkWidget
modifier|*
name|options
parameter_list|)
block|{
comment|/*  need to check whether the widget is visible...this can happen    *  because some tools share options such as the transformation tools    */
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|options
argument_list|)
condition|)
block|{
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|options_vbox
argument_list|)
argument_list|,
name|options
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
name|options
argument_list|)
expr_stmt|;
block|}
name|tool_info
index|[
operator|(
name|int
operator|)
name|type
index|]
operator|.
name|tool_options
operator|=
name|options
expr_stmt|;
block|}
end_function

begin_function
name|void
modifier|*
DECL|function|tools_register_no_options (ToolType tool_type,char * tool_title)
name|tools_register_no_options
parameter_list|(
name|ToolType
name|tool_type
parameter_list|,
name|char
modifier|*
name|tool_title
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
comment|/*  the main vbox  */
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
comment|/*  the main label  */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|tool_title
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
comment|/*  this tool has no special options  */
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"This tool has no options."
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
comment|/*  Register this selection options widget with the main tools options dialog  */
name|tools_register_options
argument_list|(
name|tool_type
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
return|return
operator|(
name|void
operator|*
operator|)
literal|1
return|;
block|}
end_function

begin_function
name|void
DECL|function|active_tool_control (int action,void * gdisp_ptr)
name|active_tool_control
parameter_list|(
name|int
name|action
parameter_list|,
name|void
modifier|*
name|gdisp_ptr
parameter_list|)
block|{
if|if
condition|(
name|active_tool
condition|)
block|{
if|if
condition|(
name|active_tool
operator|->
name|gdisp_ptr
operator|==
name|gdisp_ptr
condition|)
block|{
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|PAUSE
case|:
if|if
condition|(
name|active_tool
operator|->
name|state
operator|==
name|ACTIVE
condition|)
block|{
if|if
condition|(
operator|!
name|active_tool
operator|->
name|paused_count
condition|)
block|{
name|active_tool
operator|->
name|state
operator|=
name|PAUSED
expr_stmt|;
call|(
modifier|*
name|active_tool
operator|->
name|control_func
call|)
argument_list|(
name|active_tool
argument_list|,
name|action
argument_list|,
name|gdisp_ptr
argument_list|)
expr_stmt|;
block|}
block|}
name|active_tool
operator|->
name|paused_count
operator|++
expr_stmt|;
break|break;
case|case
name|RESUME
case|:
name|active_tool
operator|->
name|paused_count
operator|--
expr_stmt|;
if|if
condition|(
name|active_tool
operator|->
name|state
operator|==
name|PAUSED
condition|)
block|{
if|if
condition|(
operator|!
name|active_tool
operator|->
name|paused_count
condition|)
block|{
name|active_tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
call|(
modifier|*
name|active_tool
operator|->
name|control_func
call|)
argument_list|(
name|active_tool
argument_list|,
name|action
argument_list|,
name|gdisp_ptr
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
case|case
name|HALT
case|:
name|active_tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
call|(
modifier|*
name|active_tool
operator|->
name|control_func
call|)
argument_list|(
name|active_tool
argument_list|,
name|action
argument_list|,
name|gdisp_ptr
argument_list|)
expr_stmt|;
break|break;
case|case
name|DESTROY
case|:
name|active_tool_free
argument_list|()
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|options_shell
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
elseif|else
if|if
condition|(
name|action
operator|==
name|HALT
condition|)
name|active_tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|standard_arrow_keys_func (Tool * tool,GdkEventKey * kevent,gpointer gdisp_ptr)
name|standard_arrow_keys_func
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gint
DECL|function|tools_options_delete_callback (GtkWidget * w,GdkEvent * e,gpointer client_data)
name|tools_options_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|GdkEvent
modifier|*
name|e
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|tools_options_dialog_callback
argument_list|(
name|w
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
DECL|function|tools_options_dialog_callback (GtkWidget * w,gpointer client_data)
name|tools_options_dialog_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
operator|(
name|GtkWidget
operator|*
operator|)
name|client_data
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

