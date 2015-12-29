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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpdeviceinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpdeviceinfo-coords.h"
end_include

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

begin_function
name|gboolean
DECL|function|gimp_device_info_get_event_coords (GimpDeviceInfo * info,GdkWindow * window,const GdkEvent * event,GimpCoords * coords)
name|gimp_device_info_get_event_coords
parameter_list|(
name|GimpDeviceInfo
modifier|*
name|info
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
specifier|const
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
name|gdouble
name|x
decl_stmt|;
if|if
condition|(
name|gdk_event_get_axis
argument_list|(
name|event
argument_list|,
name|GDK_AXIS_X
argument_list|,
operator|&
name|x
argument_list|)
condition|)
block|{
operator|*
name|coords
operator|=
name|default_coords
expr_stmt|;
name|coords
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|gdk_event_get_axis
argument_list|(
name|event
argument_list|,
name|GDK_AXIS_Y
argument_list|,
operator|&
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
comment|/* translate event coordinates to window coordinates, only        * happens if we drag a guide from a ruler        */
if|if
condition|(
name|event
operator|->
name|any
operator|.
name|window
operator|&&
name|event
operator|->
name|any
operator|.
name|window
operator|!=
name|window
condition|)
block|{
name|GtkWidget
modifier|*
name|src_widget
decl_stmt|;
name|GtkWidget
modifier|*
name|dest_widget
decl_stmt|;
name|src_widget
operator|=
name|gtk_get_event_widget
argument_list|(
operator|(
name|GdkEvent
operator|*
operator|)
name|event
argument_list|)
expr_stmt|;
name|gdk_window_get_user_data
argument_list|(
name|window
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|dest_widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_widget
operator|&&
name|dest_widget
condition|)
block|{
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
if|if
condition|(
name|gtk_widget_translate_coordinates
argument_list|(
name|src_widget
argument_list|,
name|dest_widget
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
condition|)
block|{
name|coords
operator|->
name|x
operator|+=
name|offset_x
expr_stmt|;
name|coords
operator|->
name|y
operator|+=
name|offset_y
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|gdk_event_get_axis
argument_list|(
name|event
argument_list|,
name|GDK_AXIS_PRESSURE
argument_list|,
operator|&
name|coords
operator|->
name|pressure
argument_list|)
condition|)
block|{
name|coords
operator|->
name|pressure
operator|=
name|gimp_device_info_map_axis
argument_list|(
name|info
argument_list|,
name|GDK_AXIS_PRESSURE
argument_list|,
name|coords
operator|->
name|pressure
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gdk_event_get_axis
argument_list|(
name|event
argument_list|,
name|GDK_AXIS_XTILT
argument_list|,
operator|&
name|coords
operator|->
name|xtilt
argument_list|)
condition|)
block|{
name|coords
operator|->
name|xtilt
operator|=
name|gimp_device_info_map_axis
argument_list|(
name|info
argument_list|,
name|GDK_AXIS_XTILT
argument_list|,
name|coords
operator|->
name|xtilt
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gdk_event_get_axis
argument_list|(
name|event
argument_list|,
name|GDK_AXIS_YTILT
argument_list|,
operator|&
name|coords
operator|->
name|ytilt
argument_list|)
condition|)
block|{
name|coords
operator|->
name|ytilt
operator|=
name|gimp_device_info_map_axis
argument_list|(
name|info
argument_list|,
name|GDK_AXIS_YTILT
argument_list|,
name|coords
operator|->
name|ytilt
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gdk_event_get_axis
argument_list|(
name|event
argument_list|,
name|GDK_AXIS_WHEEL
argument_list|,
operator|&
name|coords
operator|->
name|wheel
argument_list|)
condition|)
block|{
name|coords
operator|->
name|wheel
operator|=
name|gimp_device_info_map_axis
argument_list|(
name|info
argument_list|,
name|GDK_AXIS_WHEEL
argument_list|,
name|coords
operator|->
name|wheel
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_device_info_get_mode
argument_list|(
name|info
argument_list|)
operator|!=
name|GDK_MODE_DISABLED
operator|&&
name|gdk_device_get_source
argument_list|(
name|info
operator|->
name|device
argument_list|)
operator|!=
name|GDK_SOURCE_MOUSE
condition|)
block|{
comment|/* The event was generated by an enabled extended non-mouse device */
name|coords
operator|->
name|extended
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
comment|/* The event was generated by a not extended enabled device */
name|coords
operator|->
name|extended
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
name|gimp_device_info_get_device_coords
argument_list|(
name|info
argument_list|,
name|window
argument_list|,
name|coords
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_device_info_get_device_coords (GimpDeviceInfo * info,GdkWindow * window,GimpCoords * coords)
name|gimp_device_info_get_device_coords
parameter_list|(
name|GimpDeviceInfo
modifier|*
name|info
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
name|gdouble
name|axes
index|[
name|GDK_AXIS_LAST
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
operator|*
name|coords
operator|=
name|default_coords
expr_stmt|;
name|gdk_device_get_state
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|window
argument_list|,
name|axes
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_device_get_axis
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|axes
argument_list|,
name|GDK_AXIS_X
argument_list|,
operator|&
name|coords
operator|->
name|x
argument_list|)
expr_stmt|;
name|gdk_device_get_axis
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|axes
argument_list|,
name|GDK_AXIS_Y
argument_list|,
operator|&
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdk_device_get_axis
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|axes
argument_list|,
name|GDK_AXIS_PRESSURE
argument_list|,
operator|&
name|coords
operator|->
name|pressure
argument_list|)
condition|)
block|{
name|coords
operator|->
name|pressure
operator|=
name|gimp_device_info_map_axis
argument_list|(
name|info
argument_list|,
name|GDK_AXIS_PRESSURE
argument_list|,
name|coords
operator|->
name|pressure
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gdk_device_get_axis
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|axes
argument_list|,
name|GDK_AXIS_XTILT
argument_list|,
operator|&
name|coords
operator|->
name|xtilt
argument_list|)
condition|)
block|{
name|coords
operator|->
name|xtilt
operator|=
name|gimp_device_info_map_axis
argument_list|(
name|info
argument_list|,
name|GDK_AXIS_XTILT
argument_list|,
name|coords
operator|->
name|xtilt
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gdk_device_get_axis
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|axes
argument_list|,
name|GDK_AXIS_YTILT
argument_list|,
operator|&
name|coords
operator|->
name|ytilt
argument_list|)
condition|)
block|{
name|coords
operator|->
name|ytilt
operator|=
name|gimp_device_info_map_axis
argument_list|(
name|info
argument_list|,
name|GDK_AXIS_YTILT
argument_list|,
name|coords
operator|->
name|ytilt
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gdk_device_get_axis
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|axes
argument_list|,
name|GDK_AXIS_WHEEL
argument_list|,
operator|&
name|coords
operator|->
name|wheel
argument_list|)
condition|)
block|{
name|coords
operator|->
name|wheel
operator|=
name|gimp_device_info_map_axis
argument_list|(
name|info
argument_list|,
name|GDK_AXIS_WHEEL
argument_list|,
name|coords
operator|->
name|wheel
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_device_info_get_mode
argument_list|(
name|info
argument_list|)
operator|!=
name|GDK_MODE_DISABLED
operator|&&
name|gdk_device_get_source
argument_list|(
name|info
operator|->
name|device
argument_list|)
operator|!=
name|GDK_SOURCE_MOUSE
condition|)
block|{
comment|/* The event was generated by an enabled extended non-mouse device */
name|coords
operator|->
name|extended
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
comment|/* The event was generated by a not extended enabled device */
name|coords
operator|->
name|extended
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_device_info_get_time_coords (GimpDeviceInfo * info,GdkTimeCoord * event,GimpCoords * coords)
name|gimp_device_info_get_time_coords
parameter_list|(
name|GimpDeviceInfo
modifier|*
name|info
parameter_list|,
name|GdkTimeCoord
modifier|*
name|event
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
operator|*
name|coords
operator|=
name|default_coords
expr_stmt|;
name|gdk_device_get_axis
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|event
operator|->
name|axes
argument_list|,
name|GDK_AXIS_X
argument_list|,
operator|&
name|coords
operator|->
name|x
argument_list|)
expr_stmt|;
name|gdk_device_get_axis
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|event
operator|->
name|axes
argument_list|,
name|GDK_AXIS_Y
argument_list|,
operator|&
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
comment|/*  CLAMP() the return value of each *_get_axis() call to be safe    *  against buggy XInput drivers.    */
if|if
condition|(
name|gdk_device_get_axis
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|event
operator|->
name|axes
argument_list|,
name|GDK_AXIS_PRESSURE
argument_list|,
operator|&
name|coords
operator|->
name|pressure
argument_list|)
condition|)
block|{
name|coords
operator|->
name|pressure
operator|=
name|gimp_device_info_map_axis
argument_list|(
name|info
argument_list|,
name|GDK_AXIS_PRESSURE
argument_list|,
name|coords
operator|->
name|pressure
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gdk_device_get_axis
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|event
operator|->
name|axes
argument_list|,
name|GDK_AXIS_XTILT
argument_list|,
operator|&
name|coords
operator|->
name|xtilt
argument_list|)
condition|)
block|{
name|coords
operator|->
name|xtilt
operator|=
name|gimp_device_info_map_axis
argument_list|(
name|info
argument_list|,
name|GDK_AXIS_XTILT
argument_list|,
name|coords
operator|->
name|xtilt
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gdk_device_get_axis
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|event
operator|->
name|axes
argument_list|,
name|GDK_AXIS_YTILT
argument_list|,
operator|&
name|coords
operator|->
name|ytilt
argument_list|)
condition|)
block|{
name|coords
operator|->
name|ytilt
operator|=
name|gimp_device_info_map_axis
argument_list|(
name|info
argument_list|,
name|GDK_AXIS_YTILT
argument_list|,
name|coords
operator|->
name|ytilt
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gdk_device_get_axis
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|event
operator|->
name|axes
argument_list|,
name|GDK_AXIS_WHEEL
argument_list|,
operator|&
name|coords
operator|->
name|wheel
argument_list|)
condition|)
block|{
name|coords
operator|->
name|wheel
operator|=
name|gimp_device_info_map_axis
argument_list|(
name|info
argument_list|,
name|GDK_AXIS_WHEEL
argument_list|,
name|coords
operator|->
name|wheel
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_device_info_get_mode
argument_list|(
name|info
argument_list|)
operator|!=
name|GDK_MODE_DISABLED
operator|&&
name|gdk_device_get_source
argument_list|(
name|info
operator|->
name|device
argument_list|)
operator|!=
name|GDK_SOURCE_MOUSE
condition|)
block|{
comment|/* The event was generated by an enabled extended non-mouse device */
name|coords
operator|->
name|extended
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
comment|/* The event was generated by a not extended enabled device */
name|coords
operator|->
name|extended
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_device_info_get_event_state (GimpDeviceInfo * info,GdkWindow * window,const GdkEvent * event,GdkModifierType * state)
name|gimp_device_info_get_event_state
parameter_list|(
name|GimpDeviceInfo
modifier|*
name|info
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
specifier|const
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GdkModifierType
modifier|*
name|state
parameter_list|)
block|{
if|if
condition|(
name|gdk_event_get_state
argument_list|(
name|event
argument_list|,
name|state
argument_list|)
condition|)
return|return
name|TRUE
return|;
name|gimp_device_info_get_device_state
argument_list|(
name|info
argument_list|,
name|window
argument_list|,
name|state
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_device_info_get_device_state (GimpDeviceInfo * info,GdkWindow * window,GdkModifierType * state)
name|gimp_device_info_get_device_state
parameter_list|(
name|GimpDeviceInfo
modifier|*
name|info
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkModifierType
modifier|*
name|state
parameter_list|)
block|{
name|gdk_device_get_state
argument_list|(
name|info
operator|->
name|device
argument_list|,
name|window
argument_list|,
name|NULL
argument_list|,
name|state
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

