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
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"gdk/gdkkeysyms.h"
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
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"convolve.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"paint_funcs.h"
end_include

begin_include
include|#
directive|include
file|"paint_core.h"
end_include

begin_include
include|#
directive|include
file|"paint_options.h"
end_include

begin_include
include|#
directive|include
file|"selection.h"
end_include

begin_include
include|#
directive|include
file|"tool_options_ui.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|FIELD_COLS
define|#
directive|define
name|FIELD_COLS
value|4
end_define

begin_define
DECL|macro|MIN_BLUR
define|#
directive|define
name|MIN_BLUR
value|64
end_define

begin_comment
DECL|macro|MIN_BLUR
comment|/*  (8/9 original pixel)   */
end_comment

begin_define
DECL|macro|MAX_BLUR
define|#
directive|define
name|MAX_BLUR
value|0.25
end_define

begin_comment
DECL|macro|MAX_BLUR
comment|/*  (1/33 original pixel)  */
end_comment

begin_define
DECL|macro|MIN_SHARPEN
define|#
directive|define
name|MIN_SHARPEN
value|-512
end_define

begin_define
DECL|macro|MAX_SHARPEN
define|#
directive|define
name|MAX_SHARPEN
value|-64
end_define

begin_comment
comment|/* defaults */
end_comment

begin_define
DECL|macro|DEFAULT_CONVOLVE_PRESSURE
define|#
directive|define
name|DEFAULT_CONVOLVE_PRESSURE
value|50.0
end_define

begin_define
DECL|macro|DEFAULT_CONVOLVE_TYPE
define|#
directive|define
name|DEFAULT_CONVOLVE_TYPE
value|BLUR_CONVOLVE
end_define

begin_comment
comment|/*  the convolve structures  */
end_comment

begin_typedef
DECL|typedef|ConvolveOptions
typedef|typedef
name|struct
name|_ConvolveOptions
name|ConvolveOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_ConvolveOptions
struct|struct
name|_ConvolveOptions
block|{
DECL|member|paint_options
name|PaintOptions
name|paint_options
decl_stmt|;
DECL|member|type
name|ConvolveType
name|type
decl_stmt|;
DECL|member|type_d
name|ConvolveType
name|type_d
decl_stmt|;
DECL|member|type_w
name|GtkWidget
modifier|*
name|type_w
index|[
literal|2
index|]
decl_stmt|;
DECL|member|pressure
name|double
name|pressure
decl_stmt|;
DECL|member|pressure_d
name|double
name|pressure_d
decl_stmt|;
DECL|member|pressure_w
name|GtkObject
modifier|*
name|pressure_w
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  the convolve tool options  */
end_comment

begin_decl_stmt
DECL|variable|convolve_options
specifier|static
name|ConvolveOptions
modifier|*
name|convolve_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|matrix
specifier|static
name|int
name|matrix
index|[
literal|25
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|matrix_size
specifier|static
name|int
name|matrix_size
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|matrix_divisor
specifier|static
name|int
name|matrix_divisor
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|non_gui_type
specifier|static
name|ConvolveType
name|non_gui_type
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|non_gui_pressure
specifier|static
name|double
name|non_gui_pressure
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|custom_matrix
specifier|static
name|float
name|custom_matrix
index|[
literal|25
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|blur_matrix
specifier|static
name|float
name|blur_matrix
index|[
literal|25
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
literal|1
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
name|MIN_BLUR
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
literal|1
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|sharpen_matrix
specifier|static
name|float
name|sharpen_matrix
index|[
literal|25
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
literal|1
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
name|MIN_SHARPEN
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
literal|1
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  forward function declarations  */
end_comment

begin_function_decl
specifier|static
name|void
name|calculate_matrix
parameter_list|(
name|ConvolveType
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|integer_matrix
parameter_list|(
name|float
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|copy_matrix
parameter_list|(
name|float
modifier|*
parameter_list|,
name|float
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|sum_matrix
parameter_list|(
name|int
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|convolve_motion
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|ConvolveType
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|convolve_options_reset (void)
name|convolve_options_reset
parameter_list|(
name|void
parameter_list|)
block|{
name|ConvolveOptions
modifier|*
name|options
init|=
name|convolve_options
decl_stmt|;
name|paint_options_reset
argument_list|(
operator|(
name|PaintOptions
operator|*
operator|)
name|options
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|pressure_w
argument_list|)
argument_list|,
name|options
operator|->
name|pressure_d
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|type_w
index|[
name|options
operator|->
name|type_d
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|ConvolveOptions
modifier|*
DECL|function|convolve_options_new (void)
name|convolve_options_new
parameter_list|(
name|void
parameter_list|)
block|{
name|ConvolveOptions
modifier|*
name|options
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
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|gchar
modifier|*
name|type_label
index|[
literal|2
index|]
init|=
block|{
name|N_
argument_list|(
literal|"Blur"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Sharpen"
argument_list|)
block|}
decl_stmt|;
name|gint
name|type_value
index|[
literal|2
index|]
init|=
block|{
name|BLUR_CONVOLVE
block|,
name|SHARPEN_CONVOLVE
block|}
decl_stmt|;
comment|/*  the new convolve tool options structure  */
name|options
operator|=
operator|(
name|ConvolveOptions
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|ConvolveOptions
argument_list|)
argument_list|)
expr_stmt|;
name|paint_options_init
argument_list|(
operator|(
name|PaintOptions
operator|*
operator|)
name|options
argument_list|,
name|CONVOLVE
argument_list|,
name|convolve_options_reset
argument_list|)
expr_stmt|;
name|options
operator|->
name|type
operator|=
name|options
operator|->
name|type_d
operator|=
name|DEFAULT_CONVOLVE_TYPE
expr_stmt|;
name|options
operator|->
name|pressure
operator|=
name|options
operator|->
name|pressure_d
operator|=
name|DEFAULT_CONVOLVE_PRESSURE
expr_stmt|;
comment|/*  the main vbox  */
name|vbox
operator|=
operator|(
operator|(
name|ToolOptions
operator|*
operator|)
name|options
operator|)
operator|->
name|main_vbox
expr_stmt|;
comment|/*  the pressure scale  */
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
literal|"Pressure:"
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
name|options
operator|->
name|pressure_w
operator|=
name|gtk_adjustment_new
argument_list|(
name|options
operator|->
name|pressure_d
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|pressure_w
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
name|scale
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|pressure_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|tool_options_double_adjustment_update
argument_list|,
operator|&
name|options
operator|->
name|pressure
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|tool_options_radio_buttons_new
argument_list|(
name|_
argument_list|(
literal|"Convolve Type"
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|type
argument_list|,
name|options
operator|->
name|type_w
argument_list|,
name|type_label
argument_list|,
name|type_value
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|type_w
index|[
name|options
operator|->
name|type_d
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
return|return
name|options
return|;
block|}
end_function

begin_function
name|void
modifier|*
DECL|function|convolve_paint_func (PaintCore * paint_core,GimpDrawable * drawable,int state)
name|convolve_paint_func
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|state
parameter_list|)
block|{
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|MOTION_PAINT
case|:
name|convolve_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|convolve_options
operator|->
name|type
argument_list|,
name|convolve_options
operator|->
name|pressure
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|convolve_modifier_key_func (Tool * tool,GdkEventKey * kevent,gpointer gdisp_ptr)
name|convolve_modifier_key_func
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
block|{
switch|switch
condition|(
name|kevent
operator|->
name|keyval
condition|)
block|{
case|case
name|GDK_Alt_L
case|:
case|case
name|GDK_Alt_R
case|:
break|break;
case|case
name|GDK_Shift_L
case|:
case|case
name|GDK_Shift_R
case|:
break|break;
case|case
name|GDK_Control_L
case|:
case|case
name|GDK_Control_R
case|:
switch|switch
condition|(
name|convolve_options
operator|->
name|type
condition|)
block|{
case|case
name|BLUR_CONVOLVE
case|:
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|convolve_options
operator|->
name|type_w
index|[
name|SHARPEN_CONVOLVE
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|SHARPEN_CONVOLVE
case|:
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|convolve_options
operator|->
name|type_w
index|[
name|BLUR_CONVOLVE
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
break|break;
block|}
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_convolve ()
name|tools_new_convolve
parameter_list|()
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|PaintCore
modifier|*
name|private
decl_stmt|;
comment|/*  The tool options  */
if|if
condition|(
operator|!
name|convolve_options
condition|)
block|{
name|convolve_options
operator|=
name|convolve_options_new
argument_list|()
expr_stmt|;
name|tools_register
argument_list|(
name|CONVOLVE
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|convolve_options
argument_list|)
expr_stmt|;
comment|/*  press all default buttons  */
name|convolve_options_reset
argument_list|()
expr_stmt|;
block|}
name|tool
operator|=
name|paint_core_new
argument_list|(
name|CONVOLVE
argument_list|)
expr_stmt|;
name|tool
operator|->
name|modifier_key_func
operator|=
name|convolve_modifier_key_func
expr_stmt|;
name|private
operator|=
operator|(
name|PaintCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|private
operator|->
name|paint_func
operator|=
name|convolve_paint_func
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_convolve (Tool * tool)
name|tools_free_convolve
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|paint_core_free
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|convolve_motion (PaintCore * paint_core,GimpDrawable * drawable,ConvolveType type,double pressure)
name|convolve_motion
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|ConvolveType
name|type
parameter_list|,
name|double
name|pressure
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|unsigned
name|char
modifier|*
name|temp_data
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|,
name|tempPR
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return;
comment|/*  If the image type is indexed, don't convolve  */
if|if
condition|(
operator|(
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|INDEXED_GIMAGE
operator|)
operator|||
operator|(
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|INDEXEDA_GIMAGE
operator|)
condition|)
return|return;
comment|/*  Get a region which can be used to paint to  */
if|if
condition|(
operator|!
operator|(
name|area
operator|=
name|paint_core_get_paint_area
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|)
operator|)
condition|)
return|return;
comment|/*  configure the pixel regions correctly  */
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable_data
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|area
operator|->
name|x
argument_list|,
name|area
operator|->
name|y
argument_list|,
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|destPR
operator|.
name|bytes
operator|=
name|area
operator|->
name|bytes
expr_stmt|;
name|destPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|destPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|destPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|destPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|destPR
operator|.
name|rowstride
operator|=
name|area
operator|->
name|width
operator|*
name|destPR
operator|.
name|bytes
expr_stmt|;
name|destPR
operator|.
name|data
operator|=
name|temp_buf_data
argument_list|(
name|area
argument_list|)
expr_stmt|;
name|calculate_matrix
argument_list|(
name|type
argument_list|,
name|pressure
argument_list|,
name|paint_core
operator|->
name|curpressure
argument_list|)
expr_stmt|;
comment|/*  convolve the source image with the convolve mask  */
if|if
condition|(
name|srcPR
operator|.
name|w
operator|>=
name|matrix_size
operator|&&
name|srcPR
operator|.
name|h
operator|>=
name|matrix_size
condition|)
block|{
comment|/*  if the source has no alpha, then add alpha pixels  */
if|if
condition|(
operator|!
name|drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
comment|/* note: this architecture needlessly convolves the totally- 	     opaque alpha channel. A faster approach would be to keep 	     tempPR the same number of bytes as srcPR, and extend the 	     paint_core_replace_canvas API to handle non-alpha images. */
name|tempPR
operator|.
name|bytes
operator|=
name|srcPR
operator|.
name|bytes
operator|+
literal|1
expr_stmt|;
name|tempPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|tempPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|tempPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|tempPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|tempPR
operator|.
name|rowstride
operator|=
name|tempPR
operator|.
name|bytes
operator|*
name|tempPR
operator|.
name|w
expr_stmt|;
name|temp_data
operator|=
name|g_malloc
argument_list|(
name|tempPR
operator|.
name|h
operator|*
name|tempPR
operator|.
name|rowstride
argument_list|)
expr_stmt|;
name|tempPR
operator|.
name|data
operator|=
name|temp_data
expr_stmt|;
name|add_alpha_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|tempPR
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tempPR
operator|.
name|bytes
operator|=
name|srcPR
operator|.
name|bytes
expr_stmt|;
name|tempPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|tempPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|tempPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|tempPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|tempPR
operator|.
name|rowstride
operator|=
name|tempPR
operator|.
name|bytes
operator|*
name|tempPR
operator|.
name|w
expr_stmt|;
name|temp_data
operator|=
name|g_malloc
argument_list|(
name|tempPR
operator|.
name|h
operator|*
name|tempPR
operator|.
name|rowstride
argument_list|)
expr_stmt|;
name|tempPR
operator|.
name|data
operator|=
name|temp_data
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|tempPR
argument_list|)
expr_stmt|;
name|tempPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|tempPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|tempPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|tempPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|tempPR
operator|.
name|data
operator|=
name|temp_data
expr_stmt|;
name|multiply_alpha_region
argument_list|(
operator|&
name|tempPR
argument_list|)
expr_stmt|;
block|}
name|tempPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|tempPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|tempPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|tempPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|tempPR
operator|.
name|data
operator|=
name|temp_data
expr_stmt|;
comment|/*  Convolve the region  */
name|convolve_region
argument_list|(
operator|&
name|tempPR
argument_list|,
operator|&
name|destPR
argument_list|,
name|matrix
argument_list|,
name|matrix_size
argument_list|,
name|matrix_divisor
argument_list|,
name|NORMAL_CONVOL
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|separate_alpha_region
argument_list|(
operator|&
name|destPR
argument_list|)
expr_stmt|;
comment|/*  Free the allocated temp space  */
name|g_free
argument_list|(
name|temp_data
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  if the source has no alpha, then add alpha pixels, otherwise copy  */
if|if
condition|(
operator|!
name|drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|add_alpha_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
else|else
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
block|}
comment|/*  paste the newly painted canvas to the gimage which is being worked on  */
name|paint_core_replace_canvas
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|OPAQUE_OPACITY
argument_list|,
call|(
name|int
call|)
argument_list|(
name|gimp_context_get_opacity
argument_list|(
name|NULL
argument_list|)
operator|*
literal|255
argument_list|)
argument_list|,
name|SOFT
argument_list|,
name|INCREMENTAL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|calculate_matrix (ConvolveType type,double pressure,double curpressure)
name|calculate_matrix
parameter_list|(
name|ConvolveType
name|type
parameter_list|,
name|double
name|pressure
parameter_list|,
name|double
name|curpressure
parameter_list|)
block|{
name|float
name|percent
decl_stmt|;
comment|/*  find percent of tool pressure  */
name|percent
operator|=
operator|(
name|pressure
operator|/
literal|100.0
operator|)
operator|*
name|curpressure
expr_stmt|;
comment|/*  get the appropriate convolution matrix and size and divisor  */
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|BLUR_CONVOLVE
case|:
name|matrix_size
operator|=
literal|5
expr_stmt|;
name|blur_matrix
index|[
literal|12
index|]
operator|=
name|MIN_BLUR
operator|+
name|percent
operator|*
operator|(
name|MAX_BLUR
operator|-
name|MIN_BLUR
operator|)
expr_stmt|;
name|copy_matrix
argument_list|(
name|blur_matrix
argument_list|,
name|custom_matrix
argument_list|,
name|matrix_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|SHARPEN_CONVOLVE
case|:
name|matrix_size
operator|=
literal|5
expr_stmt|;
name|sharpen_matrix
index|[
literal|12
index|]
operator|=
name|MIN_SHARPEN
operator|+
name|percent
operator|*
operator|(
name|MAX_SHARPEN
operator|-
name|MIN_SHARPEN
operator|)
expr_stmt|;
name|copy_matrix
argument_list|(
name|sharpen_matrix
argument_list|,
name|custom_matrix
argument_list|,
name|matrix_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|CUSTOM_CONVOLVE
case|:
name|matrix_size
operator|=
literal|5
expr_stmt|;
break|break;
block|}
name|integer_matrix
argument_list|(
name|custom_matrix
argument_list|,
name|matrix
argument_list|,
name|matrix_size
argument_list|)
expr_stmt|;
name|matrix_divisor
operator|=
name|sum_matrix
argument_list|(
name|matrix
argument_list|,
name|matrix_size
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|matrix_divisor
condition|)
name|matrix_divisor
operator|=
literal|1
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|integer_matrix (float * source,int * dest,int size)
name|integer_matrix
parameter_list|(
name|float
modifier|*
name|source
parameter_list|,
name|int
modifier|*
name|dest
parameter_list|,
name|int
name|size
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
DECL|macro|PRECISION
define|#
directive|define
name|PRECISION
value|10000
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|size
operator|*
name|size
condition|;
name|i
operator|++
control|)
operator|*
name|dest
operator|++
operator|=
call|(
name|int
call|)
argument_list|(
operator|*
name|source
operator|++
operator|*
name|PRECISION
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|copy_matrix (float * src,float * dest,int size)
name|copy_matrix
parameter_list|(
name|float
modifier|*
name|src
parameter_list|,
name|float
modifier|*
name|dest
parameter_list|,
name|int
name|size
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|size
operator|*
name|size
condition|;
name|i
operator|++
control|)
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|sum_matrix (int * matrix,int size)
name|sum_matrix
parameter_list|(
name|int
modifier|*
name|matrix
parameter_list|,
name|int
name|size
parameter_list|)
block|{
name|int
name|sum
init|=
literal|0
decl_stmt|;
name|size
operator|*=
name|size
expr_stmt|;
while|while
condition|(
name|size
operator|--
condition|)
name|sum
operator|+=
operator|*
name|matrix
operator|++
expr_stmt|;
return|return
name|sum
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|convolve_non_gui_paint_func (PaintCore * paint_core,GimpDrawable * drawable,int state)
name|convolve_non_gui_paint_func
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|state
parameter_list|)
block|{
name|convolve_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|non_gui_type
argument_list|,
name|non_gui_pressure
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|convolve_non_gui_default (GimpDrawable * drawable,int num_strokes,double * stroke_array)
name|convolve_non_gui_default
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|num_strokes
parameter_list|,
name|double
modifier|*
name|stroke_array
parameter_list|)
block|{
name|double
name|pressure
init|=
name|DEFAULT_CONVOLVE_PRESSURE
decl_stmt|;
name|ConvolveType
name|type
init|=
name|DEFAULT_CONVOLVE_TYPE
decl_stmt|;
name|ConvolveOptions
modifier|*
name|options
init|=
name|convolve_options
decl_stmt|;
if|if
condition|(
name|options
condition|)
block|{
name|pressure
operator|=
name|options
operator|->
name|pressure
expr_stmt|;
name|type
operator|=
name|options
operator|->
name|type
expr_stmt|;
block|}
return|return
name|convolve_non_gui
argument_list|(
name|drawable
argument_list|,
name|pressure
argument_list|,
name|type
argument_list|,
name|num_strokes
argument_list|,
name|stroke_array
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|convolve_non_gui (GimpDrawable * drawable,double pressure,ConvolveType type,int num_strokes,double * stroke_array)
name|convolve_non_gui
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|double
name|pressure
parameter_list|,
name|ConvolveType
name|type
parameter_list|,
name|int
name|num_strokes
parameter_list|,
name|double
modifier|*
name|stroke_array
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
if|if
condition|(
name|paint_core_init
argument_list|(
operator|&
name|non_gui_paint_core
argument_list|,
name|drawable
argument_list|,
name|stroke_array
index|[
literal|0
index|]
argument_list|,
name|stroke_array
index|[
literal|1
index|]
argument_list|)
condition|)
block|{
comment|/* Set the paint core's paint func */
name|non_gui_paint_core
operator|.
name|paint_func
operator|=
name|convolve_non_gui_paint_func
expr_stmt|;
name|non_gui_type
operator|=
name|type
expr_stmt|;
name|non_gui_pressure
operator|=
name|pressure
expr_stmt|;
name|non_gui_paint_core
operator|.
name|startx
operator|=
name|non_gui_paint_core
operator|.
name|lastx
operator|=
name|stroke_array
index|[
literal|0
index|]
expr_stmt|;
name|non_gui_paint_core
operator|.
name|starty
operator|=
name|non_gui_paint_core
operator|.
name|lasty
operator|=
name|stroke_array
index|[
literal|1
index|]
expr_stmt|;
name|convolve_non_gui_paint_func
argument_list|(
operator|&
name|non_gui_paint_core
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|num_strokes
condition|;
name|i
operator|++
control|)
block|{
name|non_gui_paint_core
operator|.
name|curx
operator|=
name|stroke_array
index|[
name|i
operator|*
literal|2
operator|+
literal|0
index|]
expr_stmt|;
name|non_gui_paint_core
operator|.
name|cury
operator|=
name|stroke_array
index|[
name|i
operator|*
literal|2
operator|+
literal|1
index|]
expr_stmt|;
name|paint_core_interpolate
argument_list|(
operator|&
name|non_gui_paint_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|non_gui_paint_core
operator|.
name|lastx
operator|=
name|non_gui_paint_core
operator|.
name|curx
expr_stmt|;
name|non_gui_paint_core
operator|.
name|lasty
operator|=
name|non_gui_paint_core
operator|.
name|cury
expr_stmt|;
block|}
comment|/* Finish the painting */
name|paint_core_finish
argument_list|(
operator|&
name|non_gui_paint_core
argument_list|,
name|drawable
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/* Cleanup */
name|paint_core_cleanup
argument_list|()
expr_stmt|;
return|return
name|TRUE
return|;
block|}
else|else
return|return
name|FALSE
return|;
block|}
end_function

end_unit

