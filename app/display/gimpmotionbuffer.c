begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcoords.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcoords-interpolate.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpmotionbuffer.h"
end_include

begin_comment
comment|/* Velocity unit is screen pixels per millisecond we pass to tools as 1. */
end_comment

begin_define
DECL|macro|VELOCITY_UNIT
define|#
directive|define
name|VELOCITY_UNIT
value|3.0
end_define

begin_define
DECL|macro|EVENT_FILL_PRECISION
define|#
directive|define
name|EVENT_FILL_PRECISION
value|6.0
end_define

begin_define
DECL|macro|DIRECTION_RADIUS
define|#
directive|define
name|DIRECTION_RADIUS
value|(1.5 / MAX (scale_x, scale_y))
end_define

begin_define
DECL|macro|SMOOTH_FACTOR
define|#
directive|define
name|SMOOTH_FACTOR
value|0.3
end_define

begin_enum
enum|enum
DECL|enum|__anon2c6fe76d0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2c6fe76d0203
block|{
DECL|enumerator|STROKE
name|STROKE
block|,
DECL|enumerator|HOVER
name|HOVER
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_motion_buffer_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_motion_buffer_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_motion_buffer_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_motion_buffer_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_motion_buffer_push_event_history
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_motion_buffer_pop_event_queue
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_motion_buffer_interpolate_stroke
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_motion_buffer_event_queue_timeout
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpMotionBuffer
argument_list|,
argument|gimp_motion_buffer
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_motion_buffer_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|motion_buffer_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|default_coords
specifier|static
specifier|const
name|GimpCoords
name|default_coords
init|=
name|GIMP_COORDS_DEFAULT_VALUES
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_motion_buffer_class_init (GimpMotionBufferClass * klass)
name|gimp_motion_buffer_class_init
parameter_list|(
name|GimpMotionBufferClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|motion_buffer_signals
index|[
name|STROKE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"stroke"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpMotionBufferClass
argument_list|,
name|stroke
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__POINTER_UINT_FLAGS
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|3
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|G_TYPE_UINT
argument_list|,
name|GDK_TYPE_MODIFIER_TYPE
argument_list|)
expr_stmt|;
name|motion_buffer_signals
index|[
name|HOVER
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"hover"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpMotionBufferClass
argument_list|,
name|hover
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__POINTER_FLAGS_BOOLEAN
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|3
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|GDK_TYPE_MODIFIER_TYPE
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_motion_buffer_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_motion_buffer_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_motion_buffer_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_motion_buffer_get_property
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_motion_buffer_init (GimpMotionBuffer * buffer)
name|gimp_motion_buffer_init
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|buffer
operator|->
name|event_history
operator|=
name|g_array_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpCoords
argument_list|)
argument_list|)
expr_stmt|;
name|buffer
operator|->
name|event_queue
operator|=
name|g_array_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpCoords
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_motion_buffer_dispose (GObject * object)
name|gimp_motion_buffer_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpMotionBuffer
modifier|*
name|buffer
init|=
name|GIMP_MOTION_BUFFER
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|buffer
operator|->
name|event_delay_timeout
condition|)
block|{
name|g_source_remove
argument_list|(
name|buffer
operator|->
name|event_delay_timeout
argument_list|)
expr_stmt|;
name|buffer
operator|->
name|event_delay_timeout
operator|=
literal|0
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_motion_buffer_finalize (GObject * object)
name|gimp_motion_buffer_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpMotionBuffer
modifier|*
name|buffer
init|=
name|GIMP_MOTION_BUFFER
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|buffer
operator|->
name|event_history
condition|)
block|{
name|g_array_free
argument_list|(
name|buffer
operator|->
name|event_history
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|buffer
operator|->
name|event_history
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|buffer
operator|->
name|event_queue
condition|)
block|{
name|g_array_free
argument_list|(
name|buffer
operator|->
name|event_queue
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|buffer
operator|->
name|event_queue
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_motion_buffer_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_motion_buffer_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
switch|switch
condition|(
name|property_id
condition|)
block|{
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_motion_buffer_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_motion_buffer_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
switch|switch
condition|(
name|property_id
condition|)
block|{
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpMotionBuffer
modifier|*
DECL|function|gimp_motion_buffer_new (void)
name|gimp_motion_buffer_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_MOTION_BUFFER
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_motion_buffer_begin_stroke (GimpMotionBuffer * buffer,guint32 time,GimpCoords * last_motion)
name|gimp_motion_buffer_begin_stroke
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GimpCoords
modifier|*
name|last_motion
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MOTION_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|last_motion
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|buffer
operator|->
name|last_read_motion_time
operator|=
name|time
expr_stmt|;
operator|*
name|last_motion
operator|=
name|buffer
operator|->
name|last_coords
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_motion_buffer_end_stroke (GimpMotionBuffer * buffer)
name|gimp_motion_buffer_end_stroke
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MOTION_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
operator|->
name|event_delay_timeout
condition|)
block|{
name|g_source_remove
argument_list|(
name|buffer
operator|->
name|event_delay_timeout
argument_list|)
expr_stmt|;
name|buffer
operator|->
name|event_delay_timeout
operator|=
literal|0
expr_stmt|;
block|}
name|gimp_motion_buffer_event_queue_timeout
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_motion_buffer_motion_event:  * @buffer:  * @coords:  * @time:  * @event_fill:  *  * This function evaluates the event to decide if the change is big  * enough to need handling and returns FALSE, if change is less than  * set filter level taking a whole lot of load off any draw tools that  * have no use for these events anyway. If the event is seen fit at  * first look, it is evaluated for speed and smoothed.  Due to lousy  * time resolution of events pretty strong smoothing is applied to  * timestamps for sensible speed result. This function is also ideal  * for other event adjustment like pressure curve or calculating other  * derived dynamics factors like angular velocity calculation from  * tilt values, to allow for even more dynamic brushes. Calculated  * distance to last event is stored in GimpCoords because its a  * sideproduct of velocity calculation and is currently calculated in  * each tool. If they were to use this distance, more resouces on  * recalculating the same value would be saved.  *  * Return value: %TRUE if the motion was significant enough to be  *               processed, %FALSE otherwise.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_motion_buffer_motion_event (GimpMotionBuffer * buffer,GimpCoords * coords,guint32 time,gboolean event_fill)
name|gimp_motion_buffer_motion_event
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|gboolean
name|event_fill
parameter_list|)
block|{
name|gdouble
name|delta_time
init|=
literal|0.001
decl_stmt|;
name|gdouble
name|delta_x
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|delta_y
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|distance
init|=
literal|1.0
decl_stmt|;
name|gdouble
name|scale_x
init|=
name|coords
operator|->
name|xscale
decl_stmt|;
name|gdouble
name|scale_y
init|=
name|coords
operator|->
name|yscale
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MOTION_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|coords
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  the last_read_motion_time most be set unconditionally, so set    *  it early    */
name|buffer
operator|->
name|last_read_motion_time
operator|=
name|time
expr_stmt|;
name|delta_time
operator|=
operator|(
name|buffer
operator|->
name|last_motion_delta_time
operator|*
operator|(
literal|1
operator|-
name|SMOOTH_FACTOR
operator|)
operator|+
operator|(
name|time
operator|-
name|buffer
operator|->
name|last_motion_time
operator|)
operator|*
name|SMOOTH_FACTOR
operator|)
expr_stmt|;
if|if
condition|(
name|buffer
operator|->
name|last_motion_time
operator|==
literal|0
condition|)
block|{
comment|/*  First pair is invalid to do any velocity calculation, so we        *  apply a constant value.        */
name|coords
operator|->
name|velocity
operator|=
literal|1.0
expr_stmt|;
block|}
else|else
block|{
name|GimpCoords
name|last_dir_event
init|=
name|buffer
operator|->
name|last_coords
decl_stmt|;
name|gdouble
name|filter
decl_stmt|;
name|gdouble
name|dist
decl_stmt|;
name|gdouble
name|delta_dir
decl_stmt|;
name|gdouble
name|dir_delta_x
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|dir_delta_y
init|=
literal|0.0
decl_stmt|;
name|delta_x
operator|=
name|last_dir_event
operator|.
name|x
operator|-
name|coords
operator|->
name|x
expr_stmt|;
name|delta_y
operator|=
name|last_dir_event
operator|.
name|y
operator|-
name|coords
operator|->
name|y
expr_stmt|;
comment|/*  Events with distances less than the screen resolution are        *  not worth handling.        */
name|filter
operator|=
name|MIN
argument_list|(
literal|1.0
operator|/
name|scale_x
argument_list|,
literal|1.0
operator|/
name|scale_y
argument_list|)
operator|/
literal|2.0
expr_stmt|;
if|if
condition|(
name|fabs
argument_list|(
name|delta_x
argument_list|)
operator|<
name|filter
operator|&&
name|fabs
argument_list|(
name|delta_y
argument_list|)
operator|<
name|filter
condition|)
block|{
return|return
name|FALSE
return|;
block|}
name|distance
operator|=
name|dist
operator|=
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|delta_x
argument_list|)
operator|+
name|SQR
argument_list|(
name|delta_y
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  If even smoothed time resolution does not allow to guess for        *  speed, use last velocity.        */
if|if
condition|(
name|delta_time
operator|==
literal|0
condition|)
block|{
name|coords
operator|->
name|velocity
operator|=
name|buffer
operator|->
name|last_coords
operator|.
name|velocity
expr_stmt|;
block|}
else|else
block|{
comment|/*  We need to calculate the velocity in screen coordinates            *  for human interaction            */
name|gdouble
name|screen_distance
init|=
operator|(
name|distance
operator|*
name|MIN
argument_list|(
name|scale_x
argument_list|,
name|scale_y
argument_list|)
operator|)
decl_stmt|;
comment|/* Calculate raw valocity */
name|coords
operator|->
name|velocity
operator|=
operator|(
operator|(
name|screen_distance
operator|/
name|delta_time
operator|)
operator|/
name|VELOCITY_UNIT
operator|)
expr_stmt|;
comment|/* Adding velocity dependent smoothing, feels better in tools. */
name|coords
operator|->
name|velocity
operator|=
operator|(
name|buffer
operator|->
name|last_coords
operator|.
name|velocity
operator|*
operator|(
literal|1
operator|-
name|MIN
argument_list|(
name|SMOOTH_FACTOR
argument_list|,
name|coords
operator|->
name|velocity
argument_list|)
operator|)
operator|+
name|coords
operator|->
name|velocity
operator|*
name|MIN
argument_list|(
name|SMOOTH_FACTOR
argument_list|,
name|coords
operator|->
name|velocity
argument_list|)
operator|)
expr_stmt|;
comment|/* Speed needs upper limit */
name|coords
operator|->
name|velocity
operator|=
name|MIN
argument_list|(
name|coords
operator|->
name|velocity
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
operator|(
name|fabs
argument_list|(
name|delta_x
argument_list|)
operator|>
name|DIRECTION_RADIUS
operator|)
operator|&&
operator|(
name|fabs
argument_list|(
name|delta_y
argument_list|)
operator|>
name|DIRECTION_RADIUS
operator|)
operator|)
operator|||
operator|(
name|buffer
operator|->
name|event_history
operator|->
name|len
operator|<
literal|4
operator|)
condition|)
block|{
name|dir_delta_x
operator|=
name|delta_x
expr_stmt|;
name|dir_delta_y
operator|=
name|delta_y
expr_stmt|;
block|}
else|else
block|{
name|gint
name|x
init|=
literal|3
decl_stmt|;
while|while
condition|(
operator|(
operator|(
name|fabs
argument_list|(
name|dir_delta_x
argument_list|)
operator|<
name|DIRECTION_RADIUS
operator|)
operator|||
operator|(
name|fabs
argument_list|(
name|dir_delta_y
argument_list|)
operator|<
name|DIRECTION_RADIUS
operator|)
operator|)
operator|&&
operator|(
name|x
operator|>=
literal|0
operator|)
condition|)
block|{
name|last_dir_event
operator|=
name|g_array_index
argument_list|(
name|buffer
operator|->
name|event_history
argument_list|,
name|GimpCoords
argument_list|,
name|x
argument_list|)
expr_stmt|;
name|dir_delta_x
operator|=
name|last_dir_event
operator|.
name|x
operator|-
name|coords
operator|->
name|x
expr_stmt|;
name|dir_delta_y
operator|=
name|last_dir_event
operator|.
name|y
operator|-
name|coords
operator|->
name|y
expr_stmt|;
name|x
operator|--
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|(
name|fabs
argument_list|(
name|dir_delta_x
argument_list|)
operator|<
name|DIRECTION_RADIUS
operator|)
operator|||
operator|(
name|fabs
argument_list|(
name|dir_delta_y
argument_list|)
operator|<
name|DIRECTION_RADIUS
operator|)
condition|)
block|{
name|coords
operator|->
name|direction
operator|=
name|buffer
operator|->
name|last_coords
operator|.
name|direction
expr_stmt|;
block|}
else|else
block|{
name|coords
operator|->
name|direction
operator|=
name|gimp_coords_direction
argument_list|(
operator|&
name|last_dir_event
argument_list|,
name|coords
argument_list|)
expr_stmt|;
block|}
name|coords
operator|->
name|direction
operator|=
name|coords
operator|->
name|direction
operator|-
name|floor
argument_list|(
name|coords
operator|->
name|direction
argument_list|)
expr_stmt|;
name|delta_dir
operator|=
name|coords
operator|->
name|direction
operator|-
name|buffer
operator|->
name|last_coords
operator|.
name|direction
expr_stmt|;
if|if
condition|(
name|delta_dir
operator|<
operator|-
literal|0.5
condition|)
block|{
name|coords
operator|->
name|direction
operator|=
operator|(
literal|0.5
operator|*
name|coords
operator|->
name|direction
operator|+
literal|0.5
operator|*
operator|(
name|buffer
operator|->
name|last_coords
operator|.
name|direction
operator|-
literal|1.0
operator|)
operator|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|delta_dir
operator|>
literal|0.5
condition|)
block|{
name|coords
operator|->
name|direction
operator|=
operator|(
literal|0.5
operator|*
name|coords
operator|->
name|direction
operator|+
literal|0.5
operator|*
operator|(
name|buffer
operator|->
name|last_coords
operator|.
name|direction
operator|+
literal|1.0
operator|)
operator|)
expr_stmt|;
block|}
else|else
block|{
name|coords
operator|->
name|direction
operator|=
operator|(
literal|0.5
operator|*
name|coords
operator|->
name|direction
operator|+
literal|0.5
operator|*
name|buffer
operator|->
name|last_coords
operator|.
name|direction
operator|)
expr_stmt|;
block|}
name|coords
operator|->
name|direction
operator|=
name|coords
operator|->
name|direction
operator|-
name|floor
argument_list|(
name|coords
operator|->
name|direction
argument_list|)
expr_stmt|;
comment|/* do event fill for devices that do not provide enough events */
if|if
condition|(
name|distance
operator|>=
name|EVENT_FILL_PRECISION
operator|&&
name|event_fill
operator|&&
name|buffer
operator|->
name|event_history
operator|->
name|len
operator|>=
literal|2
condition|)
block|{
if|if
condition|(
name|buffer
operator|->
name|event_delay
condition|)
block|{
name|gimp_motion_buffer_interpolate_stroke
argument_list|(
name|buffer
argument_list|,
name|coords
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|buffer
operator|->
name|event_delay
operator|=
name|TRUE
expr_stmt|;
name|gimp_motion_buffer_push_event_history
argument_list|(
name|buffer
argument_list|,
name|coords
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|buffer
operator|->
name|event_delay
condition|)
name|buffer
operator|->
name|event_delay
operator|=
name|FALSE
expr_stmt|;
name|gimp_motion_buffer_push_event_history
argument_list|(
name|buffer
argument_list|,
name|coords
argument_list|)
expr_stmt|;
block|}
ifdef|#
directive|ifdef
name|EVENT_VERBOSE
name|g_printerr
argument_list|(
literal|"DIST: %f, DT:%f, Vel:%f, Press:%f,smooth_dd:%f, POS: (%f, %f)\n"
argument_list|,
name|distance
argument_list|,
name|delta_time
argument_list|,
name|buffer
operator|->
name|last_coords
operator|.
name|velocity
argument_list|,
name|coords
operator|->
name|pressure
argument_list|,
name|distance
operator|-
name|dist
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
name|g_array_append_val
argument_list|(
name|buffer
operator|->
name|event_queue
argument_list|,
operator|*
name|coords
argument_list|)
expr_stmt|;
name|buffer
operator|->
name|last_coords
operator|=
operator|*
name|coords
expr_stmt|;
name|buffer
operator|->
name|last_motion_time
operator|=
name|time
expr_stmt|;
name|buffer
operator|->
name|last_motion_delta_time
operator|=
name|delta_time
expr_stmt|;
name|buffer
operator|->
name|last_motion_delta_x
operator|=
name|delta_x
expr_stmt|;
name|buffer
operator|->
name|last_motion_delta_y
operator|=
name|delta_y
expr_stmt|;
name|buffer
operator|->
name|last_motion_distance
operator|=
name|distance
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|guint32
DECL|function|gimp_motion_buffer_get_last_motion_time (GimpMotionBuffer * buffer)
name|gimp_motion_buffer_get_last_motion_time
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MOTION_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|buffer
operator|->
name|last_read_motion_time
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_motion_buffer_request_stroke (GimpMotionBuffer * buffer,GdkModifierType state,guint32 time)
name|gimp_motion_buffer_request_stroke
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
name|GdkModifierType
name|event_state
decl_stmt|;
name|gint
name|keep
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MOTION_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
operator|->
name|event_delay
condition|)
block|{
comment|/* If we are in delay we use LAST state, not current */
name|event_state
operator|=
name|buffer
operator|->
name|last_active_state
expr_stmt|;
name|keep
operator|=
literal|1
expr_stmt|;
comment|/* Holding one event in buf */
block|}
else|else
block|{
comment|/* Save the state */
name|event_state
operator|=
name|state
expr_stmt|;
block|}
if|if
condition|(
name|buffer
operator|->
name|event_delay_timeout
condition|)
block|{
name|g_source_remove
argument_list|(
name|buffer
operator|->
name|event_delay_timeout
argument_list|)
expr_stmt|;
name|buffer
operator|->
name|event_delay_timeout
operator|=
literal|0
expr_stmt|;
block|}
name|buffer
operator|->
name|last_active_state
operator|=
name|state
expr_stmt|;
while|while
condition|(
name|buffer
operator|->
name|event_queue
operator|->
name|len
operator|>
name|keep
condition|)
block|{
name|GimpCoords
name|buf_coords
decl_stmt|;
name|gimp_motion_buffer_pop_event_queue
argument_list|(
name|buffer
argument_list|,
operator|&
name|buf_coords
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|buffer
argument_list|,
name|motion_buffer_signals
index|[
name|STROKE
index|]
argument_list|,
literal|0
argument_list|,
operator|&
name|buf_coords
argument_list|,
name|time
argument_list|,
name|event_state
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|buffer
operator|->
name|event_delay
condition|)
block|{
name|buffer
operator|->
name|event_delay_timeout
operator|=
name|g_timeout_add
argument_list|(
literal|50
argument_list|,
operator|(
name|GSourceFunc
operator|)
name|gimp_motion_buffer_event_queue_timeout
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_motion_buffer_request_hover (GimpMotionBuffer * buffer,GdkModifierType state,gboolean proximity)
name|gimp_motion_buffer_request_hover
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|gboolean
name|proximity
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MOTION_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
operator|->
name|event_queue
operator|->
name|len
operator|>
literal|0
condition|)
block|{
name|GimpCoords
name|buf_coords
init|=
name|g_array_index
argument_list|(
name|buffer
operator|->
name|event_queue
argument_list|,
name|GimpCoords
argument_list|,
name|buffer
operator|->
name|event_queue
operator|->
name|len
operator|-
literal|1
argument_list|)
decl_stmt|;
name|g_signal_emit
argument_list|(
name|buffer
argument_list|,
name|motion_buffer_signals
index|[
name|HOVER
index|]
argument_list|,
literal|0
argument_list|,
operator|&
name|buf_coords
argument_list|,
name|state
argument_list|,
name|proximity
argument_list|)
expr_stmt|;
name|g_array_set_size
argument_list|(
name|buffer
operator|->
name|event_queue
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_motion_buffer_push_event_history (GimpMotionBuffer * buffer,const GimpCoords * coords)
name|gimp_motion_buffer_push_event_history
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
if|if
condition|(
name|buffer
operator|->
name|event_history
operator|->
name|len
operator|==
literal|4
condition|)
name|g_array_remove_index
argument_list|(
name|buffer
operator|->
name|event_history
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_array_append_val
argument_list|(
name|buffer
operator|->
name|event_history
argument_list|,
operator|*
name|coords
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_motion_buffer_pop_event_queue (GimpMotionBuffer * buffer,GimpCoords * coords)
name|gimp_motion_buffer_pop_event_queue
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
operator|*
name|coords
operator|=
name|g_array_index
argument_list|(
name|buffer
operator|->
name|event_queue
argument_list|,
name|GimpCoords
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_array_remove_index
argument_list|(
name|buffer
operator|->
name|event_queue
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_motion_buffer_interpolate_stroke (GimpMotionBuffer * buffer,GimpCoords * coords)
name|gimp_motion_buffer_interpolate_stroke
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
name|GArray
modifier|*
name|ret_coords
decl_stmt|;
name|gint
name|i
init|=
name|buffer
operator|->
name|event_history
operator|->
name|len
operator|-
literal|1
decl_stmt|;
comment|/* Note that there must be exactly one event in buffer or bad things    * can happen. This must never get called under other circumstances.    */
name|ret_coords
operator|=
name|g_array_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpCoords
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_coords_interpolate_catmull
argument_list|(
name|g_array_index
argument_list|(
name|buffer
operator|->
name|event_history
argument_list|,
name|GimpCoords
argument_list|,
name|i
operator|-
literal|1
argument_list|)
argument_list|,
name|g_array_index
argument_list|(
name|buffer
operator|->
name|event_history
argument_list|,
name|GimpCoords
argument_list|,
name|i
argument_list|)
argument_list|,
name|g_array_index
argument_list|(
name|buffer
operator|->
name|event_queue
argument_list|,
name|GimpCoords
argument_list|,
literal|0
argument_list|)
argument_list|,
operator|*
name|coords
argument_list|,
name|EVENT_FILL_PRECISION
operator|/
literal|2
argument_list|,
operator|&
name|ret_coords
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Push the last actual event in history */
name|gimp_motion_buffer_push_event_history
argument_list|(
name|buffer
argument_list|,
operator|&
name|g_array_index
argument_list|(
name|buffer
operator|->
name|event_queue
argument_list|,
name|GimpCoords
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|g_array_set_size
argument_list|(
name|buffer
operator|->
name|event_queue
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_array_append_vals
argument_list|(
name|buffer
operator|->
name|event_queue
argument_list|,
operator|&
name|g_array_index
argument_list|(
name|ret_coords
argument_list|,
name|GimpCoords
argument_list|,
literal|0
argument_list|)
argument_list|,
name|ret_coords
operator|->
name|len
argument_list|)
expr_stmt|;
name|g_array_free
argument_list|(
name|ret_coords
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_motion_buffer_event_queue_timeout (GimpMotionBuffer * buffer)
name|gimp_motion_buffer_event_queue_timeout
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|buffer
operator|->
name|event_delay
operator|=
name|FALSE
expr_stmt|;
name|buffer
operator|->
name|event_delay_timeout
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|buffer
operator|->
name|event_queue
operator|->
name|len
operator|>
literal|0
condition|)
block|{
name|GimpCoords
name|last_coords
init|=
name|g_array_index
argument_list|(
name|buffer
operator|->
name|event_queue
argument_list|,
name|GimpCoords
argument_list|,
name|buffer
operator|->
name|event_queue
operator|->
name|len
operator|-
literal|1
argument_list|)
decl_stmt|;
name|gimp_motion_buffer_push_event_history
argument_list|(
name|buffer
argument_list|,
operator|&
name|last_coords
argument_list|)
expr_stmt|;
name|gimp_motion_buffer_request_stroke
argument_list|(
name|buffer
argument_list|,
name|buffer
operator|->
name|last_active_state
argument_list|,
name|buffer
operator|->
name|last_read_motion_time
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

