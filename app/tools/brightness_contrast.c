begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"brightness_contrast.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"gimplut.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"image_map.h"
end_include

begin_include
include|#
directive|include
file|"lut_funcs.h"
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|SLIDER_WIDTH
define|#
directive|define
name|SLIDER_WIDTH
value|200
end_define

begin_define
DECL|macro|BRIGHTNESS
define|#
directive|define
name|BRIGHTNESS
value|0x1
end_define

begin_define
DECL|macro|CONTRAST
define|#
directive|define
name|CONTRAST
value|0x2
end_define

begin_define
DECL|macro|ALL
define|#
directive|define
name|ALL
value|(BRIGHTNESS | CONTRAST)
end_define

begin_comment
comment|/*  the brightness-contrast structures  */
end_comment

begin_typedef
DECL|typedef|BrightnessContrast
typedef|typedef
name|struct
name|_BrightnessContrast
name|BrightnessContrast
typedef|;
end_typedef

begin_struct
DECL|struct|_BrightnessContrast
struct|struct
name|_BrightnessContrast
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

begin_typedef
DECL|typedef|BrightnessContrastDialog
typedef|typedef
name|struct
name|_BrightnessContrastDialog
name|BrightnessContrastDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_BrightnessContrastDialog
struct|struct
name|_BrightnessContrastDialog
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|gimage_name
name|GtkWidget
modifier|*
name|gimage_name
decl_stmt|;
DECL|member|brightness_data
name|GtkAdjustment
modifier|*
name|brightness_data
decl_stmt|;
DECL|member|contrast_data
name|GtkAdjustment
modifier|*
name|contrast_data
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|image_map
name|ImageMap
name|image_map
decl_stmt|;
DECL|member|brightness
name|gdouble
name|brightness
decl_stmt|;
DECL|member|contrast
name|gdouble
name|contrast
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|member|lut
name|GimpLut
modifier|*
name|lut
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  the brightness-contrast tool options  */
end_comment

begin_decl_stmt
DECL|variable|brightness_contrast_options
specifier|static
name|ToolOptions
modifier|*
name|brightness_contrast_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  the brightness-contrast dialog  */
end_comment

begin_decl_stmt
DECL|variable|brightness_contrast_dialog
specifier|static
name|BrightnessContrastDialog
modifier|*
name|brightness_contrast_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  brightness contrast action functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|brightness_contrast_control
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
name|BrightnessContrastDialog
modifier|*
name|brightness_contrast_dialog_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_update
parameter_list|(
name|BrightnessContrastDialog
modifier|*
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_preview
parameter_list|(
name|BrightnessContrastDialog
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_reset_callback
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
name|brightness_contrast_ok_callback
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
name|brightness_contrast_cancel_callback
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
name|brightness_contrast_preview_update
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
name|brightness_contrast_brightness_adjustment_update
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
name|brightness_contrast_contrast_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  brightness-contrast select action functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_control (Tool * tool,ToolAction action,gpointer gdisp_ptr)
name|brightness_contrast_control
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
name|brightness_contrast_dialog
condition|)
name|brightness_contrast_cancel_callback
argument_list|(
name|NULL
argument_list|,
operator|(
name|gpointer
operator|)
name|brightness_contrast_dialog
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
DECL|function|tools_new_brightness_contrast (void)
name|tools_new_brightness_contrast
parameter_list|(
name|void
parameter_list|)
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|BrightnessContrast
modifier|*
name|private
decl_stmt|;
comment|/*  The tool options  */
if|if
condition|(
operator|!
name|brightness_contrast_options
condition|)
block|{
name|brightness_contrast_options
operator|=
name|tool_options_new
argument_list|(
name|_
argument_list|(
literal|"Brightness-Contrast"
argument_list|)
argument_list|)
expr_stmt|;
name|tools_register
argument_list|(
name|BRIGHTNESS_CONTRAST
argument_list|,
name|brightness_contrast_options
argument_list|)
expr_stmt|;
block|}
name|tool
operator|=
name|tools_new_tool
argument_list|(
name|BRIGHTNESS_CONTRAST
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_new
argument_list|(
name|BrightnessContrast
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
name|brightness_contrast_control
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_brightness_contrast (Tool * tool)
name|tools_free_brightness_contrast
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|BrightnessContrast
modifier|*
name|bc
decl_stmt|;
name|bc
operator|=
operator|(
name|BrightnessContrast
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
comment|/*  Close the brightness-contrast dialog  */
if|if
condition|(
name|brightness_contrast_dialog
condition|)
name|brightness_contrast_cancel_callback
argument_list|(
name|NULL
argument_list|,
operator|(
name|gpointer
operator|)
name|brightness_contrast_dialog
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|brightness_contrast_initialize (GDisplay * gdisp)
name|brightness_contrast_initialize
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
literal|"Brightness-Contrast does not operate on indexed drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  The brightness-contrast dialog  */
if|if
condition|(
operator|!
name|brightness_contrast_dialog
condition|)
name|brightness_contrast_dialog
operator|=
name|brightness_contrast_dialog_new
argument_list|()
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|brightness_contrast_dialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|brightness_contrast_dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
name|brightness_contrast_dialog
operator|->
name|brightness
operator|=
literal|0.0
expr_stmt|;
name|brightness_contrast_dialog
operator|->
name|contrast
operator|=
literal|0.0
expr_stmt|;
name|brightness_contrast_dialog
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
name|brightness_contrast_dialog
operator|->
name|image_map
operator|=
name|image_map_create
argument_list|(
name|gdisp
argument_list|,
name|brightness_contrast_dialog
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|brightness_contrast_update
argument_list|(
name|brightness_contrast_dialog
argument_list|,
name|ALL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/********************************/
end_comment

begin_comment
comment|/*  Brightness Contrast dialog  */
end_comment

begin_comment
comment|/********************************/
end_comment

begin_function
specifier|static
name|BrightnessContrastDialog
modifier|*
DECL|function|brightness_contrast_dialog_new (void)
name|brightness_contrast_dialog_new
parameter_list|(
name|void
parameter_list|)
block|{
name|BrightnessContrastDialog
modifier|*
name|bcd
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
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|abox
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkWidget
modifier|*
name|slider
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkObject
modifier|*
name|data
decl_stmt|;
name|bcd
operator|=
name|g_new
argument_list|(
name|BrightnessContrastDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|bcd
operator|->
name|preview
operator|=
name|TRUE
expr_stmt|;
name|bcd
operator|->
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
comment|/*  The shell and main vbox  */
name|bcd
operator|->
name|shell
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Brightness-Contrast"
argument_list|)
argument_list|,
literal|"brightness_contrast"
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
name|brightness_contrast_ok_callback
argument_list|,
name|bcd
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
name|brightness_contrast_reset_callback
argument_list|,
name|bcd
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
name|brightness_contrast_cancel_callback
argument_list|,
name|bcd
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
name|bcd
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
comment|/*  The table containing sliders  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
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
comment|/*  Create the brightness scale widget  */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Brightness:"
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
literal|1.0
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
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|data
operator|=
name|gtk_adjustment_new
argument_list|(
literal|0
argument_list|,
operator|-
literal|127
argument_list|,
literal|127.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|bcd
operator|->
name|brightness_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|slider
argument_list|,
name|SLIDER_WIDTH
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_scale_set_digits
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|slider
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|abox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gtk_spin_button_new
argument_list|(
name|bcd
operator|->
name|brightness_data
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
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|abox
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
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|abox
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|brightness_contrast_brightness_adjustment_update
argument_list|)
argument_list|,
name|bcd
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|slider
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|abox
argument_list|)
expr_stmt|;
comment|/*  Create the contrast scale widget  */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Contrast:"
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
literal|1.0
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
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|data
operator|=
name|gtk_adjustment_new
argument_list|(
literal|0
argument_list|,
operator|-
literal|127.0
argument_list|,
literal|127.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|bcd
operator|->
name|contrast_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|slider
argument_list|,
name|SLIDER_WIDTH
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_scale_set_digits
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|slider
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|abox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gtk_spin_button_new
argument_list|(
name|bcd
operator|->
name|contrast_data
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
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|abox
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
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|abox
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|brightness_contrast_contrast_adjustment_update
argument_list|)
argument_list|,
name|bcd
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|slider
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|abox
argument_list|)
expr_stmt|;
comment|/*  Horizontal box for preview toggle button  */
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
name|bcd
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
name|brightness_contrast_preview_update
argument_list|)
argument_list|,
name|bcd
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
name|bcd
operator|->
name|shell
argument_list|)
expr_stmt|;
return|return
name|bcd
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_update (BrightnessContrastDialog * bcd,gint update)
name|brightness_contrast_update
parameter_list|(
name|BrightnessContrastDialog
modifier|*
name|bcd
parameter_list|,
name|gint
name|update
parameter_list|)
block|{
if|if
condition|(
name|update
operator|&
name|BRIGHTNESS
condition|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|bcd
operator|->
name|brightness_data
argument_list|,
name|bcd
operator|->
name|brightness
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|update
operator|&
name|CONTRAST
condition|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|bcd
operator|->
name|contrast_data
argument_list|,
name|bcd
operator|->
name|contrast
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_preview (BrightnessContrastDialog * bcd)
name|brightness_contrast_preview
parameter_list|(
name|BrightnessContrastDialog
modifier|*
name|bcd
parameter_list|)
block|{
if|if
condition|(
operator|!
name|bcd
operator|->
name|image_map
condition|)
block|{
name|g_message
argument_list|(
literal|"brightness_contrast_preview(): No image map"
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
name|brightness_contrast_lut_setup
argument_list|(
name|bcd
operator|->
name|lut
argument_list|,
name|bcd
operator|->
name|brightness
operator|/
literal|255.0
argument_list|,
name|bcd
operator|->
name|contrast
operator|/
literal|127.0
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|bcd
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|image_map_apply
argument_list|(
name|bcd
operator|->
name|image_map
argument_list|,
operator|(
name|ImageMapApplyFunc
operator|)
name|gimp_lut_process_2
argument_list|,
operator|(
name|void
operator|*
operator|)
name|bcd
operator|->
name|lut
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
DECL|function|brightness_contrast_reset_callback (GtkWidget * widget,gpointer data)
name|brightness_contrast_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrightnessContrastDialog
modifier|*
name|bcd
decl_stmt|;
name|bcd
operator|=
operator|(
name|BrightnessContrastDialog
operator|*
operator|)
name|data
expr_stmt|;
name|bcd
operator|->
name|brightness
operator|=
literal|0.0
expr_stmt|;
name|bcd
operator|->
name|contrast
operator|=
literal|0.0
expr_stmt|;
name|brightness_contrast_update
argument_list|(
name|bcd
argument_list|,
name|ALL
argument_list|)
expr_stmt|;
if|if
condition|(
name|bcd
operator|->
name|preview
condition|)
name|brightness_contrast_preview
argument_list|(
name|bcd
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_ok_callback (GtkWidget * widget,gpointer data)
name|brightness_contrast_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrightnessContrastDialog
modifier|*
name|bcd
decl_stmt|;
name|bcd
operator|=
operator|(
name|BrightnessContrastDialog
operator|*
operator|)
name|data
expr_stmt|;
name|gimp_dialog_hide
argument_list|(
name|bcd
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
name|bcd
operator|->
name|preview
condition|)
block|{
name|brightness_contrast_lut_setup
argument_list|(
name|bcd
operator|->
name|lut
argument_list|,
name|bcd
operator|->
name|brightness
operator|/
literal|255.0
argument_list|,
name|bcd
operator|->
name|contrast
operator|/
literal|127.0
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|bcd
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|image_map_apply
argument_list|(
name|bcd
operator|->
name|image_map
argument_list|,
operator|(
name|ImageMapApplyFunc
operator|)
name|gimp_lut_process_2
argument_list|,
operator|(
name|void
operator|*
operator|)
name|bcd
operator|->
name|lut
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|bcd
operator|->
name|image_map
condition|)
name|image_map_commit
argument_list|(
name|bcd
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
name|bcd
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
DECL|function|brightness_contrast_cancel_callback (GtkWidget * widget,gpointer data)
name|brightness_contrast_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrightnessContrastDialog
modifier|*
name|bcd
decl_stmt|;
name|bcd
operator|=
operator|(
name|BrightnessContrastDialog
operator|*
operator|)
name|data
expr_stmt|;
name|gimp_dialog_hide
argument_list|(
name|bcd
operator|->
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|bcd
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
name|bcd
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
name|bcd
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
DECL|function|brightness_contrast_preview_update (GtkWidget * widget,gpointer data)
name|brightness_contrast_preview_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrightnessContrastDialog
modifier|*
name|bcd
decl_stmt|;
name|bcd
operator|=
operator|(
name|BrightnessContrastDialog
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
name|bcd
operator|->
name|preview
operator|=
name|TRUE
expr_stmt|;
name|brightness_contrast_preview
argument_list|(
name|bcd
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|bcd
operator|->
name|preview
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|bcd
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
name|bcd
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
DECL|function|brightness_contrast_brightness_adjustment_update (GtkAdjustment * adjustment,gpointer data)
name|brightness_contrast_brightness_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrightnessContrastDialog
modifier|*
name|bcd
decl_stmt|;
name|bcd
operator|=
operator|(
name|BrightnessContrastDialog
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|bcd
operator|->
name|brightness
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|bcd
operator|->
name|brightness
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
if|if
condition|(
name|bcd
operator|->
name|preview
condition|)
name|brightness_contrast_preview
argument_list|(
name|bcd
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_contrast_adjustment_update (GtkAdjustment * adjustment,gpointer data)
name|brightness_contrast_contrast_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrightnessContrastDialog
modifier|*
name|bcd
decl_stmt|;
name|bcd
operator|=
operator|(
name|BrightnessContrastDialog
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|bcd
operator|->
name|contrast
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|bcd
operator|->
name|contrast
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
if|if
condition|(
name|bcd
operator|->
name|preview
condition|)
name|brightness_contrast_preview
argument_list|(
name|bcd
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

