begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"devices.h"
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
file|"ink.h"
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
file|"session.h"
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

begin_include
include|#
directive|include
file|"pixmaps.h"
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

begin_decl_stmt
DECL|variable|active_tool_type
name|ToolType
name|active_tool_type
init|=
operator|-
literal|1
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
block|,
literal|"/Tools/Rect Select"
block|,
literal|"R"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|rect_bits
block|,
literal|"Select rectangular regions"
block|,
literal|"ContextHelp/rect-select"
block|,
name|RECT_SELECT
block|,
name|tools_new_rect_select
block|,
name|tools_free_rect_select
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Ellipse Select"
block|,
literal|1
block|,
literal|"/Tools/Ellipse Select"
block|,
literal|"E"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|circ_bits
block|,
literal|"Select elliptical regions"
block|,
literal|"ContextHelp/ellipse-select"
block|,
name|ELLIPSE_SELECT
block|,
name|tools_new_ellipse_select
block|,
name|tools_free_ellipse_select
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Free Select"
block|,
literal|2
block|,
literal|"/Tools/Free Select"
block|,
literal|"F"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|free_bits
block|,
literal|"Select hand-drawn regions"
block|,
literal|"ContextHelp/free-select"
block|,
name|FREE_SELECT
block|,
name|tools_new_free_select
block|,
name|tools_free_free_select
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Fuzzy Select"
block|,
literal|3
block|,
literal|"/Tools/Fuzzy Select"
block|,
literal|"Z"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|fuzzy_bits
block|,
literal|"Select contiguous regions"
block|,
literal|"ContextHelp/fuzzy-select"
block|,
name|FUZZY_SELECT
block|,
name|tools_new_fuzzy_select
block|,
name|tools_free_fuzzy_select
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Bezier Select"
block|,
literal|4
block|,
literal|"/Tools/Bezier Select"
block|,
literal|"B"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|bezier_bits
block|,
literal|"Select regions using Bezier curves"
block|,
literal|"ContextHelp/bezier-select"
block|,
name|BEZIER_SELECT
block|,
name|tools_new_bezier_select
block|,
name|tools_free_bezier_select
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Intelligent Scissors"
block|,
literal|5
block|,
literal|"/Tools/Intelligent Scissors"
block|,
literal|"I"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|iscissors_bits
block|,
literal|"Select shapes from image"
block|,
literal|"ContextHelp/iscissors"
block|,
name|ISCISSORS
block|,
name|tools_new_iscissors
block|,
name|tools_free_iscissors
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Move"
block|,
literal|6
block|,
literal|"/Tools/Move"
block|,
literal|"M"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|move_bits
block|,
literal|"Move layers& selections"
block|,
literal|"ContextHelp/move"
block|,
name|MOVE
block|,
name|tools_new_move_tool
block|,
name|tools_free_move_tool
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Magnify"
block|,
literal|7
block|,
literal|"/Tools/Magnify"
block|,
literal|"<shift>M"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|magnify_bits
block|,
literal|"Zoom in& out"
block|,
literal|"ContextHelp/magnify"
block|,
name|MAGNIFY
block|,
name|tools_new_magnify
block|,
name|tools_free_magnify
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Crop"
block|,
literal|8
block|,
literal|"/Tools/Crop"
block|,
literal|"<shift>C"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|crop_bits
block|,
literal|"Crop the image"
block|,
literal|"ContextHelp/crop"
block|,
name|CROP
block|,
name|tools_new_crop
block|,
name|tools_free_crop
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Transform"
block|,
literal|9
block|,
literal|"/Tools/Transform"
block|,
literal|"<shift>T"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|scale_bits
block|,
literal|"Transform the layer or selection"
block|,
literal|"ContextHelp/rotate"
block|,
name|ROTATE
block|,
name|tools_new_transform_tool
block|,
name|tools_free_transform_tool
block|,
name|NULL
block|}
block|,
comment|/* rotate */
block|{
name|NULL
block|,
literal|"Transform"
block|,
literal|9
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|SCALE
block|,
name|tools_new_transform_tool
block|,
name|tools_free_transform_tool
block|,
name|NULL
block|}
block|,
comment|/* scale */
block|{
name|NULL
block|,
literal|"Transform"
block|,
literal|9
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|SHEAR
block|,
name|tools_new_transform_tool
block|,
name|tools_free_transform_tool
block|,
name|NULL
block|}
block|,
comment|/* shear */
block|{
name|NULL
block|,
literal|"Transform"
block|,
literal|9
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|PERSPECTIVE
block|,
name|tools_new_transform_tool
block|,
name|tools_free_transform_tool
block|,
name|NULL
block|}
block|,
comment|/* perspective */
block|{
name|NULL
block|,
literal|"Flip"
block|,
literal|10
block|,
literal|"/Tools/Flip"
block|,
literal|"<shift>F"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|horizflip_bits
block|,
literal|"Flip the layer or selection"
block|,
literal|"ContextHelp/flip"
block|,
name|FLIP_HORZ
block|,
name|tools_new_flip
block|,
name|tools_free_flip_tool
block|,
name|NULL
block|}
block|,
comment|/* horizontal */
block|{
name|NULL
block|,
literal|"Flip"
block|,
literal|10
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|FLIP_VERT
block|,
name|tools_new_flip
block|,
name|tools_free_flip_tool
block|,
name|NULL
block|}
block|,
comment|/* vertical */
block|{
name|NULL
block|,
literal|"Text"
block|,
literal|11
block|,
literal|"/Tools/Text"
block|,
literal|"T"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|text_bits
block|,
literal|"Add text to the image"
block|,
literal|"ContextHelp/text"
block|,
name|TEXT
block|,
name|tools_new_text
block|,
name|tools_free_text
block|,
name|NULL
block|,   }
block|,
block|{
name|NULL
block|,
literal|"Color Picker"
block|,
literal|12
block|,
literal|"/Tools/Color Picker"
block|,
literal|"O"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|colorpicker_bits
block|,
literal|"Pick colors from the image"
block|,
literal|"ContextHelp/color-picker"
block|,
name|COLOR_PICKER
block|,
name|tools_new_color_picker
block|,
name|tools_free_color_picker
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Bucket Fill"
block|,
literal|13
block|,
literal|"/Tools/Bucket Fill"
block|,
literal|"<shift>B"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|fill_bits
block|,
literal|"Fill with a color or pattern"
block|,
literal|"ContextHelp/bucket-fill"
block|,
name|BUCKET_FILL
block|,
name|tools_new_bucket_fill
block|,
name|tools_free_bucket_fill
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Blend"
block|,
literal|14
block|,
literal|"/Tools/Blend"
block|,
literal|"L"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|gradient_bits
block|,
literal|"Fill with a color gradient"
block|,
literal|"ContextHelp/gradient"
block|,
name|BLEND
block|,
name|tools_new_blend
block|,
name|tools_free_blend
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Pencil"
block|,
literal|15
block|,
literal|"/Tools/Pencil"
block|,
literal|"<shift>P"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|pencil_bits
block|,
literal|"Draw sharp pencil strokes"
block|,
literal|"ContextHelp/pencil"
block|,
name|PENCIL
block|,
name|tools_new_pencil
block|,
name|tools_free_pencil
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Paintbrush"
block|,
literal|16
block|,
literal|"/Tools/Paintbrush"
block|,
literal|"P"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|paint_bits
block|,
literal|"Paint fuzzy brush strokes"
block|,
literal|"ContextHelp/paintbrush"
block|,
name|PAINTBRUSH
block|,
name|tools_new_paintbrush
block|,
name|tools_free_paintbrush
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Eraser"
block|,
literal|17
block|,
literal|"/Tools/Eraser"
block|,
literal|"<shift>E"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|erase_bits
block|,
literal|"Erase to background or transparency"
block|,
literal|"ContextHelp/eraser"
block|,
name|ERASER
block|,
name|tools_new_eraser
block|,
name|tools_free_eraser
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Airbrush"
block|,
literal|18
block|,
literal|"/Tools/Airbrush"
block|,
literal|"A"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|airbrush_bits
block|,
literal|"Airbrush with variable pressure"
block|,
literal|"ContextHelp/airbrush"
block|,
name|AIRBRUSH
block|,
name|tools_new_airbrush
block|,
name|tools_free_airbrush
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Clone"
block|,
literal|19
block|,
literal|"/Tools/Clone"
block|,
literal|"C"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|clone_bits
block|,
literal|"Paint using patterns or image regions"
block|,
literal|"ContextHelp/clone"
block|,
name|CLONE
block|,
name|tools_new_clone
block|,
name|tools_free_clone
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Convolve"
block|,
literal|20
block|,
literal|"/Tools/Convolve"
block|,
literal|"V"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|blur_bits
block|,
literal|"Blur or sharpen"
block|,
literal|"ContextHelp/convolve"
block|,
name|CONVOLVE
block|,
name|tools_new_convolve
block|,
name|tools_free_convolve
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|"Ink"
block|,
literal|21
block|,
literal|"/Tools/Ink"
block|,
literal|"K"
block|,
operator|(
name|char
operator|*
operator|*
operator|)
name|ink_bits
block|,
literal|"Draw in ink"
block|,
literal|"ContextHelp/ink"
block|,
name|INK
block|,
name|tools_new_ink
block|,
name|tools_free_ink
block|,
name|NULL
block|}
block|,
comment|/*  Non-toolbox tools  */
block|{
name|NULL
block|,
literal|"By Color Select"
block|,
literal|22
block|,
literal|"/Select/By Color"
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|BY_COLOR_SELECT
block|,
name|tools_new_by_color_select
block|,
name|tools_free_by_color_select
block|,
name|by_color_select_initialize
block|}
block|,
block|{
name|NULL
block|,
literal|"Color Balance"
block|,
literal|23
block|,
literal|"/Image/Colors/Color Balance"
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|COLOR_BALANCE
block|,
name|tools_new_color_balance
block|,
name|tools_free_color_balance
block|,
name|color_balance_initialize
block|}
block|,
block|{
name|NULL
block|,
literal|"Brightness-Contrast"
block|,
literal|24
block|,
literal|"/Image/Colors/Brightness-Contrast"
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|BRIGHTNESS_CONTRAST
block|,
name|tools_new_brightness_contrast
block|,
name|tools_free_brightness_contrast
block|,
name|brightness_contrast_initialize
block|}
block|,
block|{
name|NULL
block|,
literal|"Hue-Saturation"
block|,
literal|25
block|,
literal|"/Image/Colors/Hue-Saturation"
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|HUE_SATURATION
block|,
name|tools_new_hue_saturation
block|,
name|tools_free_hue_saturation
block|,
name|hue_saturation_initialize
block|}
block|,
block|{
name|NULL
block|,
literal|"Posterize"
block|,
literal|26
block|,
literal|"/Image/Colors/Posterize"
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|POSTERIZE
block|,
name|tools_new_posterize
block|,
name|tools_free_posterize
block|,
name|posterize_initialize
block|}
block|,
block|{
name|NULL
block|,
literal|"Threshold"
block|,
literal|27
block|,
literal|"/Image/Colors/Threshold"
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|THRESHOLD
block|,
name|tools_new_threshold
block|,
name|tools_free_threshold
block|,
name|threshold_initialize
block|}
block|,
block|{
name|NULL
block|,
literal|"Curves"
block|,
literal|28
block|,
literal|"/Image/Colors/Curves"
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|CURVES
block|,
name|tools_new_curves
block|,
name|tools_free_curves
block|,
name|curves_initialize
block|}
block|,
block|{
name|NULL
block|,
literal|"Levels"
block|,
literal|29
block|,
literal|"/Image/Colors/Levels"
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|LEVELS
block|,
name|tools_new_levels
block|,
name|tools_free_levels
block|,
name|levels_initialize
block|}
block|,
block|{
name|NULL
block|,
literal|"Histogram"
block|,
literal|30
block|,
literal|"/Image/Histogram"
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|HISTOGRAM
block|,
name|tools_new_histogram_tool
block|,
name|tools_free_histogram_tool
block|,
name|histogram_tool_initialize
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|num_tools
name|gint
name|num_tools
init|=
sizeof|sizeof
argument_list|(
name|tool_info
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|ToolInfo
argument_list|)
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
if|if
condition|(
operator|!
name|active_tool
condition|)
return|return;
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
operator|(
operator|*
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
name|free_func
operator|)
operator|(
name|active_tool
operator|)
expr_stmt|;
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
name|active_tool
operator|=
operator|(
operator|*
name|tool_info
index|[
operator|(
name|int
operator|)
name|type
index|]
operator|.
name|new_func
operator|)
operator|(
operator|)
expr_stmt|;
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
comment|/* Update the device-information dialog */
name|device_status_update
argument_list|(
name|current_device
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_initialize (ToolType type,GDisplay * gdisp)
name|tools_initialize
parameter_list|(
name|ToolType
name|type
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
comment|/* If you're wondering... only these dialog type tools have init functions */
if|if
condition|(
name|active_tool
condition|)
name|active_tool_free
argument_list|()
expr_stmt|;
if|if
condition|(
name|tool_info
index|[
operator|(
name|int
operator|)
name|type
index|]
operator|.
name|init_func
condition|)
block|{
if|if
condition|(
name|gdisp
condition|)
block|{
name|active_tool
operator|=
operator|(
operator|*
name|tool_info
index|[
operator|(
name|int
operator|)
name|type
index|]
operator|.
name|new_func
operator|)
operator|(
operator|)
expr_stmt|;
operator|(
operator|*
name|tool_info
index|[
operator|(
name|int
operator|)
name|type
index|]
operator|.
name|init_func
operator|)
operator|(
name|gdisp
operator|)
expr_stmt|;
block|}
else|else
block|{
name|active_tool
operator|=
name|tools_new_rect_select
argument_list|()
expr_stmt|;
block|}
block|}
else|else
name|active_tool
operator|=
operator|(
operator|*
name|tool_info
index|[
operator|(
name|int
operator|)
name|type
index|]
operator|.
name|new_func
operator|)
operator|(
operator|)
expr_stmt|;
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
else|else
name|active_tool
operator|->
name|drawable
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
name|session_set_window_geometry
argument_list|(
name|options_shell
argument_list|,
operator|&
name|tool_options_geometry
argument_list|,
name|FALSE
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
name|session_get_window_geometry
argument_list|(
name|options_shell
argument_list|,
operator|&
name|tool_options_geometry
argument_list|)
expr_stmt|;
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

