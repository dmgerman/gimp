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
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-coords.h"
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
value|(1.5 / MAX (shell->scale_x, shell->scale_y))
end_define

begin_define
DECL|macro|SMOOTH_FACTOR
define|#
directive|define
name|SMOOTH_FACTOR
value|0.3
end_define

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_interpolate_stroke
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

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

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_display_shell_eval_event:  * @shell:  * @coords:  * @inertia_factor:  * @time:  *  * This function evaluates the event to decide if the change is  * big enough to need handling and returns FALSE, if change is less  * than set filter level taking a whole lot of load off any draw tools  * that have no use for these events anyway. If the event is  * seen fit at first look, it is evaluated for speed and smoothed.  * Due to lousy time resolution of events pretty strong smoothing is  * applied to timestamps for sensible speed result. This function is  * also ideal for other event adjustment like pressure curve or  * calculating other derived dynamics factors like angular velocity  * calculation from tilt values, to allow for even more dynamic  * brushes. Calculated distance to last event is stored in GimpCoords  * because its a sideproduct of velocity calculation and is currently  * calculated in each tool. If they were to use this distance, more  * resouces on recalculating the same value would be saved.  *  * Return value:  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_display_shell_eval_event (GimpDisplayShell * shell,GimpCoords * coords,gdouble inertia_factor,guint32 time)
name|gimp_display_shell_eval_event
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gdouble
name|inertia_factor
parameter_list|,
name|guint32
name|time
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
name|dir_delta_x
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|dir_delta_y
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|distance
init|=
literal|1.0
decl_stmt|;
name|gboolean
name|event_fill
init|=
operator|(
name|inertia_factor
operator|>
literal|0
operator|)
decl_stmt|;
name|gdouble
name|delta_pressure
init|=
literal|0.0
decl_stmt|;
comment|/* Smoothing causes problems with cursor tracking    * when zoomed above screen resolution so we need to supress it.    */
if|if
condition|(
name|shell
operator|->
name|scale_x
operator|>
literal|1.0
operator|||
name|shell
operator|->
name|scale_y
operator|>
literal|1.0
condition|)
block|{
name|inertia_factor
operator|=
literal|0.0
expr_stmt|;
block|}
name|delta_time
operator|=
operator|(
name|shell
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
name|shell
operator|->
name|last_motion_time
operator|)
operator|*
name|SMOOTH_FACTOR
operator|)
expr_stmt|;
name|delta_pressure
operator|=
name|coords
operator|->
name|pressure
operator|-
name|shell
operator|->
name|last_coords
operator|.
name|pressure
expr_stmt|;
comment|/* Try to detect a pen lift */
if|if
condition|(
operator|(
name|delta_time
operator|<
literal|50
operator|)
operator|&&
operator|(
name|fabs
argument_list|(
name|delta_pressure
argument_list|)
operator|>
literal|0.04
operator|)
operator|&&
operator|(
name|delta_pressure
operator|<
literal|0.0
operator|)
condition|)
block|{
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|shell
operator|->
name|last_motion_time
operator|==
literal|0
condition|)
block|{
comment|/* First pair is invalid to do any velocity calculation,        * so we apply a constant value.        */
name|coords
operator|->
name|velocity
operator|=
literal|1.0
expr_stmt|;
block|}
else|else
block|{
name|gdouble
name|filter
decl_stmt|;
name|gdouble
name|dist
decl_stmt|;
name|gdouble
name|delta_dir
decl_stmt|;
name|GimpCoords
name|last_dir_event
init|=
name|shell
operator|->
name|last_coords
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
comment|/* Events with distances less than the screen resolution are not        * worth handling.        */
name|filter
operator|=
name|MIN
argument_list|(
literal|1
operator|/
name|shell
operator|->
name|scale_x
argument_list|,
literal|1
operator|/
name|shell
operator|->
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
return|return
name|FALSE
return|;
name|delta_time
operator|=
operator|(
name|shell
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
name|shell
operator|->
name|last_motion_time
operator|)
operator|*
name|SMOOTH_FACTOR
operator|)
expr_stmt|;
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
comment|/* If even smoothed time resolution does not allow to guess for speed,        * use last velocity.        */
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
name|shell
operator|->
name|last_coords
operator|.
name|velocity
expr_stmt|;
block|}
else|else
block|{
comment|/* We need to calculate the velocity in screen coordinates            * for human interaction            */
name|gdouble
name|screen_distance
init|=
operator|(
name|distance
operator|*
name|MIN
argument_list|(
name|shell
operator|->
name|scale_x
argument_list|,
name|shell
operator|->
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
name|shell
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
name|shell
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
name|shell
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
name|shell
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
name|shell
operator|->
name|last_coords
operator|.
name|direction
expr_stmt|;
if|if
condition|(
operator|(
name|fabs
argument_list|(
name|delta_dir
argument_list|)
operator|>
literal|0.5
operator|)
operator|&&
operator|(
name|delta_dir
operator|<
literal|0.0
operator|)
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
name|shell
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
operator|(
name|fabs
argument_list|(
name|delta_dir
argument_list|)
operator|>
literal|0.5
operator|)
operator|&&
operator|(
name|delta_dir
operator|>
literal|0.0
operator|)
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
name|shell
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
name|shell
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
comment|/* High speed -> less smooth*/
name|inertia_factor
operator|*=
operator|(
literal|1
operator|-
name|coords
operator|->
name|velocity
operator|)
expr_stmt|;
if|if
condition|(
name|inertia_factor
operator|>
literal|0
operator|&&
name|distance
operator|>
literal|0
condition|)
block|{
comment|/* Apply smoothing to X and Y. */
comment|/* This tells how far from the pointer can stray from the line */
name|gdouble
name|max_deviation
init|=
name|SQR
argument_list|(
literal|20
operator|*
name|inertia_factor
argument_list|)
decl_stmt|;
name|gdouble
name|cur_deviation
init|=
name|max_deviation
decl_stmt|;
name|gdouble
name|sin_avg
decl_stmt|;
name|gdouble
name|sin_old
decl_stmt|;
name|gdouble
name|sin_new
decl_stmt|;
name|gdouble
name|cos_avg
decl_stmt|;
name|gdouble
name|cos_old
decl_stmt|;
name|gdouble
name|cos_new
decl_stmt|;
name|gdouble
name|new_x
decl_stmt|;
name|gdouble
name|new_y
decl_stmt|;
name|sin_new
operator|=
name|delta_x
operator|/
name|distance
expr_stmt|;
name|sin_old
operator|=
name|shell
operator|->
name|last_motion_delta_x
operator|/
name|shell
operator|->
name|last_motion_distance
expr_stmt|;
name|sin_avg
operator|=
name|sin
argument_list|(
name|asin
argument_list|(
name|sin_old
argument_list|)
operator|*
name|inertia_factor
operator|+
name|asin
argument_list|(
name|sin_new
argument_list|)
operator|*
operator|(
literal|1
operator|-
name|inertia_factor
operator|)
argument_list|)
expr_stmt|;
name|cos_new
operator|=
name|delta_y
operator|/
name|distance
expr_stmt|;
name|cos_old
operator|=
name|shell
operator|->
name|last_motion_delta_y
operator|/
name|shell
operator|->
name|last_motion_distance
expr_stmt|;
name|cos_avg
operator|=
name|cos
argument_list|(
name|acos
argument_list|(
name|cos_old
argument_list|)
operator|*
name|inertia_factor
operator|+
name|acos
argument_list|(
name|cos_new
argument_list|)
operator|*
operator|(
literal|1
operator|-
name|inertia_factor
operator|)
argument_list|)
expr_stmt|;
name|delta_x
operator|=
name|sin_avg
operator|*
name|distance
expr_stmt|;
name|delta_y
operator|=
name|cos_avg
operator|*
name|distance
expr_stmt|;
name|new_x
operator|=
operator|(
name|shell
operator|->
name|last_coords
operator|.
name|x
operator|-
name|delta_x
operator|)
operator|*
literal|0.5
operator|+
name|coords
operator|->
name|x
operator|*
literal|0.5
expr_stmt|;
name|new_y
operator|=
operator|(
name|shell
operator|->
name|last_coords
operator|.
name|y
operator|-
name|delta_y
operator|)
operator|*
literal|0.5
operator|+
name|coords
operator|->
name|y
operator|*
literal|0.5
expr_stmt|;
name|cur_deviation
operator|=
name|SQR
argument_list|(
name|coords
operator|->
name|x
operator|-
name|new_x
argument_list|)
operator|+
name|SQR
argument_list|(
name|coords
operator|->
name|y
operator|-
name|new_y
argument_list|)
expr_stmt|;
while|while
condition|(
name|cur_deviation
operator|>=
name|max_deviation
condition|)
block|{
name|new_x
operator|=
name|new_x
operator|*
literal|0.8
operator|+
name|coords
operator|->
name|x
operator|*
literal|0.2
expr_stmt|;
name|new_y
operator|=
name|new_y
operator|*
literal|0.8
operator|+
name|coords
operator|->
name|y
operator|*
literal|0.2
expr_stmt|;
name|cur_deviation
operator|=
operator|(
name|SQR
argument_list|(
name|coords
operator|->
name|x
operator|-
name|new_x
argument_list|)
operator|+
name|SQR
argument_list|(
name|coords
operator|->
name|y
operator|-
name|new_y
argument_list|)
operator|)
expr_stmt|;
block|}
name|coords
operator|->
name|x
operator|=
name|new_x
expr_stmt|;
name|coords
operator|->
name|y
operator|=
name|new_y
expr_stmt|;
name|delta_x
operator|=
name|shell
operator|->
name|last_coords
operator|.
name|x
operator|-
name|coords
operator|->
name|x
expr_stmt|;
name|delta_y
operator|=
name|shell
operator|->
name|last_coords
operator|.
name|y
operator|-
name|coords
operator|->
name|y
expr_stmt|;
comment|/* Recalculate distance */
name|distance
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
block|}
comment|/* do event fill for devices that do not provide enough events*/
if|if
condition|(
name|distance
operator|>=
name|EVENT_FILL_PRECISION
operator|&&
name|event_fill
operator|&&
name|shell
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
name|shell
operator|->
name|event_delay
condition|)
block|{
name|gimp_display_shell_interpolate_stroke
argument_list|(
name|shell
argument_list|,
name|coords
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|shell
operator|->
name|event_delay
operator|=
name|TRUE
expr_stmt|;
name|gimp_display_shell_push_event_history
argument_list|(
name|shell
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
name|shell
operator|->
name|event_delay
condition|)
block|{
name|shell
operator|->
name|event_delay
operator|=
name|FALSE
expr_stmt|;
block|}
name|gimp_display_shell_push_event_history
argument_list|(
name|shell
argument_list|,
name|coords
argument_list|)
expr_stmt|;
block|}
ifdef|#
directive|ifdef
name|VERBOSE
name|g_printerr
argument_list|(
literal|"DIST: %f, DT:%f, Vel:%f, Press:%f,smooth_dd:%f, sf %f\n"
argument_list|,
name|distance
argument_list|,
name|delta_time
argument_list|,
name|shell
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
name|inertia_factor
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
name|g_array_append_val
argument_list|(
name|shell
operator|->
name|event_queue
argument_list|,
operator|*
name|coords
argument_list|)
expr_stmt|;
name|shell
operator|->
name|last_coords
operator|=
operator|*
name|coords
expr_stmt|;
name|shell
operator|->
name|last_motion_time
operator|=
name|time
expr_stmt|;
name|shell
operator|->
name|last_motion_delta_time
operator|=
name|delta_time
expr_stmt|;
name|shell
operator|->
name|last_motion_delta_x
operator|=
name|delta_x
expr_stmt|;
name|shell
operator|->
name|last_motion_delta_y
operator|=
name|delta_y
expr_stmt|;
name|shell
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

begin_comment
comment|/* Helper function fo managing event history */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_push_event_history (GimpDisplayShell * shell,GimpCoords * coords)
name|gimp_display_shell_push_event_history
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
if|if
condition|(
name|shell
operator|->
name|event_history
operator|->
name|len
operator|==
literal|4
condition|)
name|g_array_remove_index
argument_list|(
name|shell
operator|->
name|event_history
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_array_append_val
argument_list|(
name|shell
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
DECL|function|gimp_display_shell_interpolate_stroke (GimpDisplayShell * shell,GimpCoords * coords)
name|gimp_display_shell_interpolate_stroke
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
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
name|shell
operator|->
name|event_history
operator|->
name|len
operator|-
literal|1
decl_stmt|;
comment|/* Note that there must be exactly one event in buffer or bad things    * can happen. This should never get called under other circumstances.    */
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
name|shell
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
name|shell
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
name|shell
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
name|gimp_display_shell_push_event_history
argument_list|(
name|shell
argument_list|,
operator|&
name|g_array_index
argument_list|(
name|shell
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
name|shell
operator|->
name|event_queue
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_array_append_vals
argument_list|(
name|shell
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

end_unit

