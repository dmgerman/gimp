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
file|<math.h>
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
file|"dodgeburn.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimplut.h"
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
DECL|macro|ROUND (x)
define|#
directive|define
name|ROUND
parameter_list|(
name|x
parameter_list|)
value|(int)((x) + .5)
end_define

begin_comment
comment|/*  the dodgeburn structures  */
end_comment

begin_typedef
DECL|typedef|DodgeBurnOptions
typedef|typedef
name|struct
name|_DodgeBurnOptions
name|DodgeBurnOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_DodgeBurnOptions
struct|struct
name|_DodgeBurnOptions
block|{
DECL|member|paint_options
name|PaintOptions
name|paint_options
decl_stmt|;
DECL|member|type
name|DodgeBurnType
name|type
decl_stmt|;
DECL|member|type_d
name|DodgeBurnType
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
DECL|member|mode
name|DodgeBurnMode
name|mode
decl_stmt|;
comment|/*highlights,midtones,shadows*/
DECL|member|mode_d
name|DodgeBurnMode
name|mode_d
decl_stmt|;
DECL|member|mode_w
name|GtkWidget
modifier|*
name|mode_w
index|[
literal|3
index|]
decl_stmt|;
DECL|member|exposure
name|double
name|exposure
decl_stmt|;
DECL|member|exposure_d
name|double
name|exposure_d
decl_stmt|;
DECL|member|exposure_w
name|GtkObject
modifier|*
name|exposure_w
decl_stmt|;
DECL|member|lut
name|GimpLut
modifier|*
name|lut
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|dodgeburn_make_luts
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gfloat
name|dodgeburn_highlights_lut_func
parameter_list|(
name|void
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|gfloat
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gfloat
name|dodgeburn_midtones_lut_func
parameter_list|(
name|void
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|gfloat
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gfloat
name|dodgeburn_shadows_lut_func
parameter_list|(
name|void
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|gfloat
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* The dodge burn lookup tables */
end_comment

begin_function_decl
name|gfloat
name|dodgeburn_highlights
parameter_list|(
name|void
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|gfloat
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gfloat
name|dodgeburn_midtones
parameter_list|(
name|void
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|gfloat
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gfloat
name|dodgeburn_shadows
parameter_list|(
name|void
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|gfloat
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  the dodgeburn tool options  */
end_comment

begin_decl_stmt
DECL|variable|dodgeburn_options
specifier|static
name|DodgeBurnOptions
modifier|*
name|dodgeburn_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|dodgeburn_motion
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dodgeburn_init
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dodgeburn_finish
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|dodgeburn_options_reset (void)
name|dodgeburn_options_reset
parameter_list|(
name|void
parameter_list|)
block|{
name|DodgeBurnOptions
modifier|*
name|options
init|=
name|dodgeburn_options
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
name|exposure_w
argument_list|)
argument_list|,
name|options
operator|->
name|exposure_d
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
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|mode_w
index|[
name|options
operator|->
name|mode_d
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
name|DodgeBurnOptions
modifier|*
DECL|function|dodgeburn_options_new (void)
name|dodgeburn_options_new
parameter_list|(
name|void
parameter_list|)
block|{
name|DodgeBurnOptions
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
literal|"Dodge"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Burn"
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
name|DODGE
block|,
name|BURN
block|}
decl_stmt|;
name|gchar
modifier|*
name|mode_label
index|[
literal|3
index|]
init|=
block|{
name|N_
argument_list|(
literal|"Highlights"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Midtones"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Shadows"
argument_list|)
block|}
decl_stmt|;
name|gint
name|mode_value
index|[
literal|3
index|]
init|=
block|{
name|DODGEBURN_HIGHLIGHTS
block|,
name|DODGEBURN_MIDTONES
block|,
name|DODGEBURN_SHADOWS
block|}
decl_stmt|;
comment|/*  the new dodgeburn tool options structure  */
name|options
operator|=
operator|(
name|DodgeBurnOptions
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|DodgeBurnOptions
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
name|DODGEBURN
argument_list|,
name|dodgeburn_options_reset
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
name|DODGE
expr_stmt|;
name|options
operator|->
name|exposure
operator|=
name|options
operator|->
name|exposure_d
operator|=
literal|50.0
expr_stmt|;
name|options
operator|->
name|mode
operator|=
name|options
operator|->
name|mode_d
operator|=
name|DODGEBURN_HIGHLIGHTS
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
comment|/*  the exposure scale  */
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
literal|"Exposure:"
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
name|exposure_w
operator|=
name|gtk_adjustment_new
argument_list|(
name|options
operator|->
name|exposure_d
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
name|exposure_w
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
name|exposure_w
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
name|exposure
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
comment|/* the type (dodge or burn) */
name|frame
operator|=
name|tool_options_radio_buttons_new
argument_list|(
name|_
argument_list|(
literal|"Type"
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
comment|/*  mode (highlights, midtones, or shadows)  */
name|frame
operator|=
name|tool_options_radio_buttons_new
argument_list|(
name|_
argument_list|(
literal|"Mode"
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|mode
argument_list|,
name|options
operator|->
name|mode_w
argument_list|,
name|mode_label
argument_list|,
name|mode_value
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|mode_w
index|[
name|options
operator|->
name|mode_d
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
DECL|function|dodgeburn_paint_func (PaintCore * paint_core,GimpDrawable * drawable,int state)
name|dodgeburn_paint_func
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
name|INIT_PAINT
case|:
name|dodgeburn_init
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
break|break;
case|case
name|MOTION_PAINT
case|:
name|dodgeburn_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
break|break;
case|case
name|FINISH_PAINT
case|:
name|dodgeburn_finish
argument_list|(
name|paint_core
argument_list|,
name|drawable
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
DECL|function|dodgeburn_finish (PaintCore * paint_core,GimpDrawable * drawable)
name|dodgeburn_finish
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
comment|/* Here we destroy the luts to do the painting with.*/
if|if
condition|(
name|dodgeburn_options
operator|->
name|lut
condition|)
block|{
name|gimp_lut_free
argument_list|(
name|dodgeburn_options
operator|->
name|lut
argument_list|)
expr_stmt|;
name|dodgeburn_options
operator|->
name|lut
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dodgeburn_init (PaintCore * paint_core,GimpDrawable * drawable)
name|dodgeburn_init
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
comment|/* Here we create the luts to do the painting with.*/
name|dodgeburn_make_luts
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dodgeburn_make_luts (PaintCore * paint_core,GimpDrawable * drawable)
name|dodgeburn_make_luts
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpLutFunc
name|lut_func
decl_stmt|;
name|int
name|nchannels
init|=
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|gfloat
name|exposure
init|=
operator|(
name|dodgeburn_options
operator|->
name|exposure
operator|)
operator|/
literal|100.0
decl_stmt|;
comment|/* make the exposure negative if burn for luts*/
if|if
condition|(
name|dodgeburn_options
operator|->
name|type
operator|==
name|BURN
condition|)
name|exposure
operator|=
operator|-
name|exposure
expr_stmt|;
name|dodgeburn_options
operator|->
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
switch|switch
condition|(
name|dodgeburn_options
operator|->
name|mode
condition|)
block|{
case|case
name|DODGEBURN_HIGHLIGHTS
case|:
name|lut_func
operator|=
name|dodgeburn_highlights_lut_func
expr_stmt|;
break|break;
case|case
name|DODGEBURN_MIDTONES
case|:
name|lut_func
operator|=
name|dodgeburn_midtones_lut_func
expr_stmt|;
break|break;
case|case
name|DODGEBURN_SHADOWS
case|:
name|lut_func
operator|=
name|dodgeburn_shadows_lut_func
expr_stmt|;
break|break;
default|default:
name|lut_func
operator|=
name|NULL
expr_stmt|;
break|break;
block|}
name|gimp_lut_setup_exact
argument_list|(
name|dodgeburn_options
operator|->
name|lut
argument_list|,
name|lut_func
argument_list|,
operator|(
name|void
operator|*
operator|)
operator|&
name|exposure
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dodgeburn_modifier_key_func (Tool * tool,GdkEventKey * kevent,gpointer gdisp_ptr)
name|dodgeburn_modifier_key_func
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
switch|switch
condition|(
name|dodgeburn_options
operator|->
name|type
condition|)
block|{
case|case
name|BURN
case|:
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|dodgeburn_options
operator|->
name|type_w
index|[
name|BURN
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|DODGE
case|:
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|dodgeburn_options
operator|->
name|type_w
index|[
name|DODGE
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
case|case
name|GDK_Control_L
case|:
case|case
name|GDK_Control_R
case|:
break|break;
block|}
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_dodgeburn ()
name|tools_new_dodgeburn
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
name|dodgeburn_options
condition|)
block|{
name|dodgeburn_options
operator|=
name|dodgeburn_options_new
argument_list|()
expr_stmt|;
name|tools_register
argument_list|(
name|DODGEBURN
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|dodgeburn_options
argument_list|)
expr_stmt|;
comment|/*  press all default buttons  */
name|dodgeburn_options_reset
argument_list|()
expr_stmt|;
block|}
name|tool
operator|=
name|paint_core_new
argument_list|(
name|DODGEBURN
argument_list|)
expr_stmt|;
name|tool
operator|->
name|modifier_key_func
operator|=
name|dodgeburn_modifier_key_func
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
name|dodgeburn_paint_func
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_dodgeburn (Tool * tool)
name|tools_free_dodgeburn
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
comment|/* delete any luts here */
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
DECL|function|dodgeburn_motion (PaintCore * paint_core,GimpDrawable * drawable)
name|dodgeburn_motion
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
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
name|TempBuf
modifier|*
name|orig
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|,
name|tempPR
decl_stmt|;
name|guchar
modifier|*
name|temp_data
decl_stmt|;
name|gfloat
name|exposure
decl_stmt|;
name|gfloat
name|brush_opacity
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
comment|/*  If the image type is indexed, don't dodgeburn  */
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
comment|/* Constant painting --get a copy of the orig drawable (with      no paint from this stroke yet) */
block|{
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|x1
operator|=
name|BOUNDS
argument_list|(
name|area
operator|->
name|x
argument_list|,
literal|0
argument_list|,
name|drawable_width
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|y1
operator|=
name|BOUNDS
argument_list|(
name|area
operator|->
name|y
argument_list|,
literal|0
argument_list|,
name|drawable_height
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|x2
operator|=
name|BOUNDS
argument_list|(
name|area
operator|->
name|x
operator|+
name|area
operator|->
name|width
argument_list|,
literal|0
argument_list|,
name|drawable_width
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|BOUNDS
argument_list|(
name|area
operator|->
name|y
operator|+
name|area
operator|->
name|height
argument_list|,
literal|0
argument_list|,
name|drawable_height
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|x2
operator|-
name|x1
operator|)
operator|||
operator|!
operator|(
name|y2
operator|-
name|y1
operator|)
condition|)
return|return;
comment|/*  get the original untouched image  */
name|orig
operator|=
name|paint_core_get_orig_image
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|srcPR
operator|.
name|bytes
operator|=
name|orig
operator|->
name|bytes
expr_stmt|;
name|srcPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|srcPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|srcPR
operator|.
name|w
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|srcPR
operator|.
name|h
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
name|srcPR
operator|.
name|rowstride
operator|=
name|srcPR
operator|.
name|bytes
operator|*
name|orig
operator|->
name|width
expr_stmt|;
name|srcPR
operator|.
name|data
operator|=
name|temp_buf_data
argument_list|(
name|orig
argument_list|)
expr_stmt|;
block|}
comment|/* tempPR will hold the dodgeburned region*/
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
name|srcPR
operator|.
name|x
expr_stmt|;
name|tempPR
operator|.
name|y
operator|=
name|srcPR
operator|.
name|y
expr_stmt|;
name|tempPR
operator|.
name|w
operator|=
name|srcPR
operator|.
name|w
expr_stmt|;
name|tempPR
operator|.
name|h
operator|=
name|srcPR
operator|.
name|h
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
name|brush_opacity
operator|=
name|PAINT_OPTIONS_GET_OPACITY
argument_list|(
name|dodgeburn_options
argument_list|)
expr_stmt|;
name|exposure
operator|=
operator|(
name|dodgeburn_options
operator|->
name|exposure
operator|)
operator|/
literal|100.0
expr_stmt|;
comment|/*  DodgeBurn the region  */
name|gimp_lut_process
argument_list|(
name|dodgeburn_options
operator|->
name|lut
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|tempPR
argument_list|)
expr_stmt|;
comment|/* The dest is the paint area we got above (= canvas_buf) */
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
comment|/* Now add an alpha to the dodgeburned region       and put this in area = canvas_buf */
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
name|tempPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
else|else
name|copy_region
argument_list|(
operator|&
name|tempPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
comment|/*Replace the newly dodgedburned area (canvas_buf) to the gimage*/
name|paint_core_replace_canvas
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|ROUND
argument_list|(
name|brush_opacity
operator|*
literal|255.0
argument_list|)
argument_list|,
name|OPAQUE_OPACITY
argument_list|,
name|PRESSURE
argument_list|,
name|CONSTANT
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|dodgeburn_non_gui_paint_func (PaintCore * paint_core,GimpDrawable * drawable,int state)
name|dodgeburn_non_gui_paint_func
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
name|dodgeburn_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|dodgeburn_non_gui (GimpDrawable * drawable,double pressure,int num_strokes,double * stroke_array)
name|dodgeburn_non_gui
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|double
name|pressure
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
name|dodgeburn_non_gui_paint_func
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
if|if
condition|(
name|num_strokes
operator|==
literal|1
condition|)
name|dodgeburn_non_gui_paint_func
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

begin_function
specifier|static
name|gfloat
DECL|function|dodgeburn_highlights_lut_func (void * user_data,int nchannels,int channel,gfloat value)
name|dodgeburn_highlights_lut_func
parameter_list|(
name|void
modifier|*
name|user_data
parameter_list|,
name|int
name|nchannels
parameter_list|,
name|int
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
block|{
name|gfloat
modifier|*
name|exposure_ptr
init|=
operator|(
name|gfloat
operator|*
operator|)
name|user_data
decl_stmt|;
name|gfloat
name|exposure
init|=
operator|*
name|exposure_ptr
decl_stmt|;
name|gfloat
name|factor
init|=
literal|1.0
operator|+
name|exposure
operator|*
operator|(
literal|.333333
operator|)
decl_stmt|;
if|if
condition|(
operator|(
name|nchannels
operator|==
literal|2
operator|&&
name|channel
operator|==
literal|1
operator|)
operator|||
operator|(
name|nchannels
operator|==
literal|4
operator|&&
name|channel
operator|==
literal|3
operator|)
condition|)
return|return
name|value
return|;
return|return
name|factor
operator|*
name|value
return|;
block|}
end_function

begin_function
specifier|static
name|gfloat
DECL|function|dodgeburn_midtones_lut_func (void * user_data,int nchannels,int channel,gfloat value)
name|dodgeburn_midtones_lut_func
parameter_list|(
name|void
modifier|*
name|user_data
parameter_list|,
name|int
name|nchannels
parameter_list|,
name|int
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
block|{
name|gfloat
modifier|*
name|exposure_ptr
init|=
operator|(
name|gfloat
operator|*
operator|)
name|user_data
decl_stmt|;
name|gfloat
name|exposure
init|=
operator|*
name|exposure_ptr
decl_stmt|;
name|gfloat
name|factor
decl_stmt|;
if|if
condition|(
operator|(
name|nchannels
operator|==
literal|2
operator|&&
name|channel
operator|==
literal|1
operator|)
operator|||
operator|(
name|nchannels
operator|==
literal|4
operator|&&
name|channel
operator|==
literal|3
operator|)
condition|)
return|return
name|value
return|;
if|if
condition|(
name|exposure
operator|<
literal|0
condition|)
name|factor
operator|=
literal|1.0
operator|-
name|exposure
operator|*
operator|(
literal|.333333
operator|)
expr_stmt|;
else|else
name|factor
operator|=
literal|1
operator|/
operator|(
literal|1.0
operator|+
name|exposure
operator|)
expr_stmt|;
return|return
name|pow
argument_list|(
name|value
argument_list|,
name|factor
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gfloat
DECL|function|dodgeburn_shadows_lut_func (void * user_data,int nchannels,int channel,gfloat value)
name|dodgeburn_shadows_lut_func
parameter_list|(
name|void
modifier|*
name|user_data
parameter_list|,
name|int
name|nchannels
parameter_list|,
name|int
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
block|{
name|gfloat
modifier|*
name|exposure_ptr
init|=
operator|(
name|gfloat
operator|*
operator|)
name|user_data
decl_stmt|;
name|gfloat
name|exposure
init|=
operator|*
name|exposure_ptr
decl_stmt|;
name|gfloat
name|new_value
decl_stmt|;
name|gfloat
name|factor
decl_stmt|;
if|if
condition|(
operator|(
name|nchannels
operator|==
literal|2
operator|&&
name|channel
operator|==
literal|1
operator|)
operator|||
operator|(
name|nchannels
operator|==
literal|4
operator|&&
name|channel
operator|==
literal|3
operator|)
condition|)
return|return
name|value
return|;
if|if
condition|(
name|exposure
operator|>=
literal|0
condition|)
block|{
name|factor
operator|=
literal|.333333
operator|*
name|exposure
expr_stmt|;
name|new_value
operator|=
name|factor
operator|+
name|value
operator|-
name|factor
operator|*
name|value
expr_stmt|;
block|}
else|else
comment|/* exposure< 0 */
block|{
name|factor
operator|=
operator|-
literal|.333333
operator|*
name|exposure
expr_stmt|;
if|if
condition|(
name|value
operator|<
name|factor
condition|)
name|new_value
operator|=
literal|0
expr_stmt|;
else|else
comment|/*factor<= value<=1*/
name|new_value
operator|=
operator|(
name|value
operator|-
name|factor
operator|)
operator|/
operator|(
literal|1
operator|-
name|factor
operator|)
expr_stmt|;
block|}
return|return
name|new_value
return|;
block|}
end_function

end_unit

