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
file|"gimpbrushlist.h"
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
file|"palette.h"
end_include

begin_include
include|#
directive|include
file|"airbrush.h"
end_include

begin_include
include|#
directive|include
file|"selection.h"
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

begin_typedef
DECL|typedef|AirbrushTimeout
typedef|typedef
name|struct
name|_AirbrushTimeout
name|AirbrushTimeout
typedef|;
end_typedef

begin_struct
DECL|struct|_AirbrushTimeout
struct|struct
name|_AirbrushTimeout
block|{
DECL|member|paint_core
name|PaintCore
modifier|*
name|paint_core
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
comment|/*  forward function declarations  */
end_comment

begin_function_decl
specifier|static
name|void
name|airbrush_motion
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|airbrush_time_out
parameter_list|(
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|Argument
modifier|*
name|airbrush_invoker
parameter_list|(
name|Argument
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|non_gui_pressure
specifier|static
name|double
name|non_gui_pressure
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  The maximum amount of pressure that can be exerted  */
end_comment

begin_define
DECL|macro|MAX_PRESSURE
define|#
directive|define
name|MAX_PRESSURE
value|0.075
end_define

begin_define
DECL|macro|OFF
define|#
directive|define
name|OFF
value|0
end_define

begin_define
DECL|macro|ON
define|#
directive|define
name|ON
value|1
end_define

begin_typedef
DECL|typedef|AirbrushOptions
typedef|typedef
name|struct
name|_AirbrushOptions
name|AirbrushOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_AirbrushOptions
struct|struct
name|_AirbrushOptions
block|{
DECL|member|rate
name|double
name|rate
decl_stmt|;
DECL|member|pressure
name|double
name|pressure
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|timer
specifier|static
name|gint
name|timer
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|timer
comment|/*  timer for successive paint applications  */
end_comment

begin_decl_stmt
DECL|variable|timer_state
specifier|static
name|int
name|timer_state
init|=
name|OFF
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|timer_state
comment|/*  state of airbrush tool  */
end_comment

begin_decl_stmt
DECL|variable|airbrush_timeout
specifier|static
name|AirbrushTimeout
name|airbrush_timeout
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|airbrush_options
specifier|static
name|AirbrushOptions
modifier|*
name|airbrush_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|airbrush_scale_update (GtkAdjustment * adjustment,double * scale_val)
name|airbrush_scale_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|double
modifier|*
name|scale_val
parameter_list|)
block|{
operator|*
name|scale_val
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|AirbrushOptions
modifier|*
DECL|function|create_airbrush_options (void)
name|create_airbrush_options
parameter_list|(
name|void
parameter_list|)
block|{
name|AirbrushOptions
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
name|rate_scale
decl_stmt|;
name|GtkWidget
modifier|*
name|pressure_scale
decl_stmt|;
name|GtkObject
modifier|*
name|rate_scale_data
decl_stmt|;
name|GtkObject
modifier|*
name|pressure_scale_data
decl_stmt|;
comment|/*  the new options structure  */
name|options
operator|=
operator|(
name|AirbrushOptions
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|AirbrushOptions
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|->
name|rate
operator|=
literal|80.0
expr_stmt|;
name|options
operator|->
name|pressure
operator|=
literal|10.0
expr_stmt|;
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
name|_
argument_list|(
literal|"Airbrush Options"
argument_list|)
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
comment|/*  the rate scale  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
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
literal|"Rate: "
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
name|rate_scale_data
operator|=
name|gtk_adjustment_new
argument_list|(
literal|80.0
argument_list|,
literal|0.0
argument_list|,
literal|150.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|rate_scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|rate_scale_data
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
name|rate_scale
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
name|rate_scale
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|rate_scale
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|rate_scale_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|airbrush_scale_update
argument_list|,
operator|&
name|options
operator|->
name|rate
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|rate_scale
argument_list|)
expr_stmt|;
comment|/*  the pressure scale  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
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
literal|"Pressure: "
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
name|pressure_scale_data
operator|=
name|gtk_adjustment_new
argument_list|(
literal|10.0
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
name|pressure_scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|pressure_scale_data
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
name|pressure_scale
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
name|pressure_scale
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|pressure_scale
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|pressure_scale_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|airbrush_scale_update
argument_list|,
operator|&
name|options
operator|->
name|pressure
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pressure_scale
argument_list|)
expr_stmt|;
comment|/*  Register this selection options widget with the main tools options dialog  */
name|tools_register_options
argument_list|(
name|AIRBRUSH
argument_list|,
name|vbox
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
DECL|function|airbrush_paint_func (PaintCore * paint_core,GimpDrawable * drawable,int state)
name|airbrush_paint_func
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
name|GimpBrushP
name|brush
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return
name|NULL
return|;
name|brush
operator|=
name|get_active_brush
argument_list|()
expr_stmt|;
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|INIT_PAINT
case|:
comment|/* timer_state = OFF; */
if|if
condition|(
name|timer_state
operator|==
name|ON
condition|)
block|{
name|g_warning
argument_list|(
name|_
argument_list|(
literal|"killing stray timer, please report to lewing@gimp.org"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_timeout_remove
argument_list|(
name|timer
argument_list|)
expr_stmt|;
block|}
name|timer_state
operator|=
name|OFF
expr_stmt|;
break|break;
case|case
name|MOTION_PAINT
case|:
if|if
condition|(
name|timer_state
operator|==
name|ON
condition|)
name|gtk_timeout_remove
argument_list|(
name|timer
argument_list|)
expr_stmt|;
name|timer_state
operator|=
name|OFF
expr_stmt|;
name|airbrush_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|airbrush_options
operator|->
name|pressure
argument_list|)
expr_stmt|;
if|if
condition|(
name|airbrush_options
operator|->
name|rate
operator|!=
literal|0.0
condition|)
block|{
name|airbrush_timeout
operator|.
name|paint_core
operator|=
name|paint_core
expr_stmt|;
name|airbrush_timeout
operator|.
name|drawable
operator|=
name|drawable
expr_stmt|;
name|timer
operator|=
name|gtk_timeout_add
argument_list|(
operator|(
literal|10000
operator|/
name|airbrush_options
operator|->
name|rate
operator|)
argument_list|,
name|airbrush_time_out
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|timer_state
operator|=
name|ON
expr_stmt|;
block|}
break|break;
case|case
name|FINISH_PAINT
case|:
if|if
condition|(
name|timer_state
operator|==
name|ON
condition|)
name|gtk_timeout_remove
argument_list|(
name|timer
argument_list|)
expr_stmt|;
name|timer_state
operator|=
name|OFF
expr_stmt|;
break|break;
default|default :
break|break;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_airbrush ()
name|tools_new_airbrush
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
if|if
condition|(
operator|!
name|airbrush_options
condition|)
name|airbrush_options
operator|=
name|create_airbrush_options
argument_list|()
expr_stmt|;
name|tool
operator|=
name|paint_core_new
argument_list|(
name|AIRBRUSH
argument_list|)
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
name|airbrush_paint_func
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_airbrush (Tool * tool)
name|tools_free_airbrush
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
if|if
condition|(
name|timer_state
operator|==
name|ON
condition|)
name|gtk_timeout_remove
argument_list|(
name|timer
argument_list|)
expr_stmt|;
name|timer_state
operator|=
name|OFF
expr_stmt|;
name|paint_core_free
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|airbrush_time_out (gpointer client_data)
name|airbrush_time_out
parameter_list|(
name|gpointer
name|client_data
parameter_list|)
block|{
comment|/*  service the timer  */
name|airbrush_motion
argument_list|(
name|airbrush_timeout
operator|.
name|paint_core
argument_list|,
name|airbrush_timeout
operator|.
name|drawable
argument_list|,
name|airbrush_options
operator|->
name|pressure
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
comment|/*  restart the timer  */
if|if
condition|(
name|airbrush_options
operator|->
name|rate
operator|!=
literal|0.0
condition|)
return|return
name|TRUE
return|;
else|else
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|airbrush_motion (PaintCore * paint_core,GimpDrawable * drawable,double pressure)
name|airbrush_motion
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|double
name|pressure
parameter_list|)
block|{
name|gint
name|opacity
decl_stmt|;
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
name|col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
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
name|gimage_get_foreground
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|col
argument_list|)
expr_stmt|;
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
comment|/*  color the pixels  */
name|col
index|[
name|area
operator|->
name|bytes
operator|-
literal|1
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
comment|/*  color the pixels  */
name|color_pixels
argument_list|(
name|temp_buf_data
argument_list|(
name|area
argument_list|)
argument_list|,
name|col
argument_list|,
name|area
operator|->
name|width
operator|*
name|area
operator|->
name|height
argument_list|,
name|area
operator|->
name|bytes
argument_list|)
expr_stmt|;
name|opacity
operator|=
name|pressure
operator|*
operator|(
name|paint_core
operator|->
name|curpressure
operator|/
literal|0.5
operator|)
expr_stmt|;
if|if
condition|(
name|opacity
operator|>
literal|255
condition|)
name|opacity
operator|=
literal|255
expr_stmt|;
comment|/*  paste the newly painted area to the image  */
name|paint_core_paste_canvas
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|opacity
argument_list|,
call|(
name|int
call|)
argument_list|(
name|gimp_brush_get_opacity
argument_list|()
operator|*
literal|255
argument_list|)
argument_list|,
name|gimp_brush_get_paint_mode
argument_list|()
argument_list|,
name|SOFT
argument_list|,
name|CONSTANT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|airbrush_non_gui_paint_func (PaintCore * paint_core,GimpDrawable * drawable,int state)
name|airbrush_non_gui_paint_func
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
name|airbrush_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|non_gui_pressure
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*  The airbrush procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|airbrush_args
name|ProcArg
name|airbrush_args
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"the drawable"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"pressure"
block|,
literal|"The pressure of the airbrush strokes: 0<= pressure<= 100"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"num_strokes"
block|,
literal|"number of stroke control points (count each coordinate as 2 points)"
block|}
block|,
block|{
name|PDB_FLOATARRAY
block|,
literal|"strokes"
block|,
literal|"array of stroke coordinates: {s1.x, s1.y, s2.x, s2.y, ..., sn.x, sn.y}"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|airbrush_proc
name|ProcRecord
name|airbrush_proc
init|=
block|{
literal|"gimp_airbrush"
block|,
literal|"Paint in the current brush with varying pressure.  Paint application is time-dependent"
block|,
literal|"This tool simulates the use of an airbrush.  Paint pressure represents the relative intensity of the paint application.  High pressure results in a thicker layer of paint while low pressure results in a thinner layer."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|4
block|,
name|airbrush_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|airbrush_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|airbrush_invoker (Argument * args)
name|airbrush_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|success
init|=
name|TRUE
decl_stmt|;
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|int
name|num_strokes
decl_stmt|;
name|double
modifier|*
name|stroke_array
decl_stmt|;
name|int
name|int_value
decl_stmt|;
name|double
name|fp_value
decl_stmt|;
name|int
name|i
decl_stmt|;
name|drawable
operator|=
name|NULL
expr_stmt|;
name|num_strokes
operator|=
literal|0
expr_stmt|;
comment|/*  the drawable  */
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|drawable
operator|=
name|drawable_get_ID
argument_list|(
name|int_value
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
else|else
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
comment|/*  pressure  */
if|if
condition|(
name|success
condition|)
block|{
name|fp_value
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|fp_value
operator|>=
literal|0.0
operator|&&
name|fp_value
operator|<=
literal|100.0
condition|)
name|non_gui_pressure
operator|=
name|fp_value
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
comment|/*  num strokes  */
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|int_value
operator|>
literal|0
condition|)
name|num_strokes
operator|=
name|int_value
operator|/
literal|2
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
comment|/*  point array  */
if|if
condition|(
name|success
condition|)
name|stroke_array
operator|=
operator|(
name|double
operator|*
operator|)
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|success
condition|)
comment|/*  init the paint core  */
name|success
operator|=
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
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
comment|/*  set the paint core's paint func  */
name|non_gui_paint_core
operator|.
name|paint_func
operator|=
name|airbrush_non_gui_paint_func
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
name|airbrush_non_gui_paint_func
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
comment|/*  finish the painting  */
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
comment|/*  cleanup  */
name|paint_core_cleanup
argument_list|()
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|airbrush_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

end_unit

