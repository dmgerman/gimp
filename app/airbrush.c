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
file|"airbrush.h"
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
file|"gimpbrushpipe.h"
end_include

begin_include
include|#
directive|include
file|"gradient.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
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
file|"libgimp/gimpintl.h"
end_include

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

begin_comment
comment|/* Default pressure setting */
end_comment

begin_define
DECL|macro|AIRBRUSH_PRESSURE_DEFAULT
define|#
directive|define
name|AIRBRUSH_PRESSURE_DEFAULT
value|10.0
end_define

begin_define
DECL|macro|AIRBRUSH_INCREMENTAL_DEFAULT
define|#
directive|define
name|AIRBRUSH_INCREMENTAL_DEFAULT
value|FALSE
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

begin_comment
comment|/*  the airbrush structures  */
end_comment

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
DECL|member|paint_options
name|PaintOptions
name|paint_options
decl_stmt|;
DECL|member|rate
name|gdouble
name|rate
decl_stmt|;
DECL|member|rate_d
name|gdouble
name|rate_d
decl_stmt|;
DECL|member|rate_w
name|GtkObject
modifier|*
name|rate_w
decl_stmt|;
DECL|member|pressure
name|gdouble
name|pressure
decl_stmt|;
DECL|member|pressure_d
name|gdouble
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
comment|/*  the airbrush tool options  */
end_comment

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
name|gint
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
DECL|variable|non_gui_pressure
specifier|static
name|gdouble
name|non_gui_pressure
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|non_gui_incremental
specifier|static
name|gboolean
name|non_gui_incremental
decl_stmt|;
end_decl_stmt

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
name|PaintPressureOptions
modifier|*
parameter_list|,
name|gdouble
parameter_list|,
name|PaintApplicationMode
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

begin_comment
comment|/*  functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|airbrush_options_reset (void)
name|airbrush_options_reset
parameter_list|(
name|void
parameter_list|)
block|{
name|AirbrushOptions
modifier|*
name|options
init|=
name|airbrush_options
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
name|rate_w
argument_list|)
argument_list|,
name|options
operator|->
name|rate_d
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
block|}
end_function

begin_function
specifier|static
name|AirbrushOptions
modifier|*
DECL|function|airbrush_options_new (void)
name|airbrush_options_new
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
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
comment|/*  the new airbrush tool options structure  */
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
name|paint_options_init
argument_list|(
operator|(
name|PaintOptions
operator|*
operator|)
name|options
argument_list|,
name|AIRBRUSH
argument_list|,
name|airbrush_options_reset
argument_list|)
expr_stmt|;
name|options
operator|->
name|rate
operator|=
name|options
operator|->
name|rate_d
operator|=
literal|80.0
expr_stmt|;
name|options
operator|->
name|pressure
operator|=
name|options
operator|->
name|pressure_d
operator|=
name|AIRBRUSH_PRESSURE_DEFAULT
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
comment|/*  the rate scale  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
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
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|options
operator|->
name|rate_w
operator|=
name|gtk_adjustment_new
argument_list|(
name|options
operator|->
name|rate_d
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
name|scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|rate_w
argument_list|)
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
name|rate_w
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
name|rate
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Rate:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|scale
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  the pressure scale  */
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
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Pressure:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|scale
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
return|return
name|options
return|;
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_airbrush (void)
name|tools_new_airbrush
parameter_list|(
name|void
parameter_list|)
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
name|airbrush_options
condition|)
block|{
name|airbrush_options
operator|=
name|airbrush_options_new
argument_list|()
expr_stmt|;
name|tools_register
argument_list|(
name|AIRBRUSH
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|airbrush_options
argument_list|)
expr_stmt|;
block|}
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
name|private
operator|->
name|pick_colors
operator|=
name|TRUE
expr_stmt|;
name|private
operator|->
name|flags
operator||=
name|TOOL_CAN_HANDLE_CHANGING_BRUSH
expr_stmt|;
return|return
name|tool
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
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|gdouble
name|rate
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
name|gimp_context_get_brush
argument_list|(
name|NULL
argument_list|)
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
name|paint_options
operator|.
name|pressure_options
argument_list|,
name|airbrush_options
operator|->
name|pressure
argument_list|,
name|airbrush_options
operator|->
name|paint_options
operator|.
name|incremental
condition|?
name|INCREMENTAL
else|:
name|CONSTANT
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
name|rate
operator|=
name|airbrush_options
operator|->
name|paint_options
operator|.
name|pressure_options
operator|->
name|rate
condition|?
operator|(
literal|10000
operator|/
operator|(
name|airbrush_options
operator|->
name|rate
operator|*
literal|2.0
operator|*
name|paint_core
operator|->
name|curpressure
operator|)
operator|)
else|:
operator|(
literal|10000
operator|/
name|airbrush_options
operator|->
name|rate
operator|)
expr_stmt|;
name|timer
operator|=
name|gtk_timeout_add
argument_list|(
name|rate
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
name|paint_options
operator|.
name|pressure_options
argument_list|,
name|airbrush_options
operator|->
name|pressure
argument_list|,
name|airbrush_options
operator|->
name|paint_options
operator|.
name|incremental
condition|?
name|INCREMENTAL
else|:
name|CONSTANT
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
block|{
if|if
condition|(
name|airbrush_options
operator|->
name|paint_options
operator|.
name|pressure_options
operator|->
name|rate
condition|)
block|{
comment|/* set a new timer */
name|timer
operator|=
name|gtk_timeout_add
argument_list|(
operator|(
literal|10000
operator|/
operator|(
name|airbrush_options
operator|->
name|rate
operator|*
literal|2.0
operator|*
name|airbrush_timeout
operator|.
name|paint_core
operator|->
name|curpressure
operator|)
operator|)
argument_list|,
name|airbrush_time_out
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
else|else
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
name|void
DECL|function|airbrush_motion (PaintCore * paint_core,GimpDrawable * drawable,PaintPressureOptions * pressure_options,double pressure,PaintApplicationMode mode)
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
name|PaintPressureOptions
modifier|*
name|pressure_options
parameter_list|,
name|double
name|pressure
parameter_list|,
name|PaintApplicationMode
name|mode
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
name|col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|gdouble
name|scale
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
if|if
condition|(
name|pressure_options
operator|->
name|size
condition|)
name|scale
operator|=
name|paint_core
operator|->
name|curpressure
expr_stmt|;
else|else
name|scale
operator|=
literal|1.0
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
argument_list|,
name|scale
argument_list|)
operator|)
condition|)
return|return;
comment|/*  color the pixels  */
if|if
condition|(
name|pressure_options
operator|->
name|color
condition|)
block|{
name|gdouble
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
name|gradient_get_color_at
argument_list|(
name|gimp_context_get_gradient
argument_list|(
name|NULL
argument_list|)
argument_list|,
name|paint_core
operator|->
name|curpressure
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|,
operator|&
name|a
argument_list|)
expr_stmt|;
name|col
index|[
literal|0
index|]
operator|=
name|r
operator|*
literal|255.0
expr_stmt|;
name|col
index|[
literal|1
index|]
operator|=
name|g
operator|*
literal|255.0
expr_stmt|;
name|col
index|[
literal|2
index|]
operator|=
name|b
operator|*
literal|255.0
expr_stmt|;
name|col
index|[
literal|3
index|]
operator|=
name|a
operator|*
literal|255.0
expr_stmt|;
name|mode
operator|=
name|INCREMENTAL
expr_stmt|;
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
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_BRUSH_PIXMAP
argument_list|(
name|paint_core
operator|->
name|brush
argument_list|)
condition|)
block|{
name|mode
operator|=
name|INCREMENTAL
expr_stmt|;
name|paint_core_color_area_with_pixmap
argument_list|(
name|paint_core
argument_list|,
name|gimage
argument_list|,
name|drawable
argument_list|,
name|area
argument_list|,
name|scale
argument_list|,
name|SOFT
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimage_get_foreground
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|col
argument_list|)
expr_stmt|;
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
block|}
if|if
condition|(
name|pressure_options
operator|->
name|pressure
condition|)
name|pressure
operator|=
name|pressure
operator|*
literal|2.0
operator|*
name|paint_core
operator|->
name|curpressure
expr_stmt|;
comment|/*  paste the newly painted area to the image  */
name|paint_core_paste_canvas
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|MIN
argument_list|(
name|pressure
argument_list|,
literal|255
argument_list|)
argument_list|,
call|(
name|gint
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
name|gimp_context_get_paint_mode
argument_list|(
name|NULL
argument_list|)
argument_list|,
name|SOFT
argument_list|,
name|scale
argument_list|,
name|mode
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
operator|&
name|non_gui_pressure_options
argument_list|,
name|non_gui_pressure
argument_list|,
name|non_gui_incremental
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|airbrush_non_gui_default (GimpDrawable * drawable,int num_strokes,double * stroke_array)
name|airbrush_non_gui_default
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
name|AirbrushOptions
modifier|*
name|options
init|=
name|airbrush_options
decl_stmt|;
name|gdouble
name|pressure
init|=
name|AIRBRUSH_PRESSURE_DEFAULT
decl_stmt|;
if|if
condition|(
name|options
condition|)
name|pressure
operator|=
name|options
operator|->
name|pressure
expr_stmt|;
return|return
name|airbrush_non_gui
argument_list|(
name|drawable
argument_list|,
name|pressure
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
DECL|function|airbrush_non_gui (GimpDrawable * drawable,double pressure,int num_strokes,double * stroke_array)
name|airbrush_non_gui
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
name|airbrush_non_gui_paint_func
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

