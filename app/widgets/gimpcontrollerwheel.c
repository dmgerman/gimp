begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcontrollerwheel.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontrollerwheel.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|WheelEvent
typedef|typedef
name|struct
name|_WheelEvent
name|WheelEvent
typedef|;
end_typedef

begin_struct
DECL|struct|_WheelEvent
struct|struct
name|_WheelEvent
block|{
DECL|member|direction
name|GdkScrollDirection
name|direction
decl_stmt|;
DECL|member|modifiers
name|GdkModifierType
name|modifiers
decl_stmt|;
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|blurb
name|gchar
modifier|*
name|blurb
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_controller_wheel_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_controller_wheel_get_n_events
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|gimp_controller_wheel_get_event_name
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
name|gint
name|event_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|gimp_controller_wheel_get_event_blurb
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
name|gint
name|event_id
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpControllerWheel
argument_list|,
name|gimp_controller_wheel
argument_list|,
name|GIMP_TYPE_CONTROLLER
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_controller_wheel_parent_class
end_define

begin_decl_stmt
DECL|variable|wheel_events
specifier|static
name|WheelEvent
name|wheel_events
index|[]
init|=
block|{
block|{
name|GDK_SCROLL_UP
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"scroll-up-shift-control-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Up"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_UP
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
block|,
literal|"scroll-up-control-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Up"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_UP
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"scroll-up-shift-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Up"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_UP
block|,
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"scroll-up-shift-control"
block|,
name|N_
argument_list|(
literal|"Scroll Up"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_UP
block|,
name|GDK_MOD1_MASK
block|,
literal|"scroll-up-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Up"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_UP
block|,
name|GDK_CONTROL_MASK
block|,
literal|"scroll-up-control"
block|,
name|N_
argument_list|(
literal|"Scroll Up"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_UP
block|,
name|GDK_SHIFT_MASK
block|,
literal|"scroll-up-shift"
block|,
name|N_
argument_list|(
literal|"Scroll Up"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_UP
block|,
literal|0
block|,
literal|"scroll-up"
block|,
name|N_
argument_list|(
literal|"Scroll Up"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_DOWN
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"scroll-down-shift-control-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Down"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_DOWN
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
block|,
literal|"scroll-down-control-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Down"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_DOWN
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"scroll-down-shift-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Down"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_DOWN
block|,
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"scroll-down-shift-control"
block|,
name|N_
argument_list|(
literal|"Scroll Down"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_DOWN
block|,
name|GDK_MOD1_MASK
block|,
literal|"scroll-down-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Down"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_DOWN
block|,
name|GDK_CONTROL_MASK
block|,
literal|"scroll-down-control"
block|,
name|N_
argument_list|(
literal|"Scroll Down"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_DOWN
block|,
name|GDK_SHIFT_MASK
block|,
literal|"scroll-down-shift"
block|,
name|N_
argument_list|(
literal|"Scroll Down"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_DOWN
block|,
literal|0
block|,
literal|"scroll-down"
block|,
name|N_
argument_list|(
literal|"Scroll Down"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_LEFT
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"scroll-left-shift-control-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Left"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_LEFT
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
block|,
literal|"scroll-left-control-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Left"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_LEFT
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"scroll-left-shift-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Left"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_LEFT
block|,
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"scroll-left-shift-control"
block|,
name|N_
argument_list|(
literal|"Scroll Left"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_LEFT
block|,
name|GDK_MOD1_MASK
block|,
literal|"scroll-left-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Left"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_LEFT
block|,
name|GDK_CONTROL_MASK
block|,
literal|"scroll-left-control"
block|,
name|N_
argument_list|(
literal|"Scroll Left"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_LEFT
block|,
name|GDK_SHIFT_MASK
block|,
literal|"scroll-left-shift"
block|,
name|N_
argument_list|(
literal|"Scroll Left"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_LEFT
block|,
literal|0
block|,
literal|"scroll-left"
block|,
name|N_
argument_list|(
literal|"Scroll Left"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_RIGHT
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"scroll-right-shift-control-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Right"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_RIGHT
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
block|,
literal|"scroll-right-control-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Right"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_RIGHT
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"scroll-right-shift-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Right"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_RIGHT
block|,
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"scroll-right-shift-control"
block|,
name|N_
argument_list|(
literal|"Scroll Right"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_RIGHT
block|,
name|GDK_MOD1_MASK
block|,
literal|"scroll-right-alt"
block|,
name|N_
argument_list|(
literal|"Scroll Right"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_RIGHT
block|,
name|GDK_CONTROL_MASK
block|,
literal|"scroll-right-control"
block|,
name|N_
argument_list|(
literal|"Scroll Right"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_RIGHT
block|,
name|GDK_SHIFT_MASK
block|,
literal|"scroll-right-shift"
block|,
name|N_
argument_list|(
literal|"Scroll Right"
argument_list|)
block|}
block|,
block|{
name|GDK_SCROLL_RIGHT
block|,
literal|0
block|,
literal|"scroll-right"
block|,
name|N_
argument_list|(
literal|"Scroll Right"
argument_list|)
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_controller_wheel_class_init (GimpControllerWheelClass * klass)
name|gimp_controller_wheel_class_init
parameter_list|(
name|GimpControllerWheelClass
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
name|GimpControllerClass
modifier|*
name|controller_class
init|=
name|GIMP_CONTROLLER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_controller_wheel_constructor
expr_stmt|;
name|controller_class
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Mouse Wheel"
argument_list|)
expr_stmt|;
name|controller_class
operator|->
name|help_id
operator|=
name|GIMP_HELP_CONTROLLER_WHEEL
expr_stmt|;
name|controller_class
operator|->
name|get_n_events
operator|=
name|gimp_controller_wheel_get_n_events
expr_stmt|;
name|controller_class
operator|->
name|get_event_name
operator|=
name|gimp_controller_wheel_get_event_name
expr_stmt|;
name|controller_class
operator|->
name|get_event_blurb
operator|=
name|gimp_controller_wheel_get_event_blurb
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_controller_wheel_init (GimpControllerWheel * wheel)
name|gimp_controller_wheel_init
parameter_list|(
name|GimpControllerWheel
modifier|*
name|wheel
parameter_list|)
block|{
specifier|static
name|gboolean
name|event_names_initialized
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
operator|!
name|event_names_initialized
condition|)
block|{
name|gint
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
name|G_N_ELEMENTS
argument_list|(
name|wheel_events
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|WheelEvent
modifier|*
name|wevent
init|=
operator|&
name|wheel_events
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
name|wevent
operator|->
name|modifiers
operator|!=
literal|0
condition|)
block|{
name|wevent
operator|->
name|blurb
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s (%s)"
argument_list|,
name|gettext
argument_list|(
name|wevent
operator|->
name|blurb
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|wevent
operator|->
name|modifiers
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|event_names_initialized
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_controller_wheel_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_controller_wheel_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|object
argument_list|,
literal|"name"
argument_list|,
name|_
argument_list|(
literal|"Mouse Wheel Events"
argument_list|)
argument_list|,
literal|"state"
argument_list|,
name|_
argument_list|(
literal|"Ready"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_controller_wheel_get_n_events (GimpController * controller)
name|gimp_controller_wheel_get_n_events
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|)
block|{
return|return
name|G_N_ELEMENTS
argument_list|(
name|wheel_events
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_controller_wheel_get_event_name (GimpController * controller,gint event_id)
name|gimp_controller_wheel_get_event_name
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
name|gint
name|event_id
parameter_list|)
block|{
if|if
condition|(
name|event_id
operator|<
literal|0
operator|||
name|event_id
operator|>=
name|G_N_ELEMENTS
argument_list|(
name|wheel_events
argument_list|)
condition|)
return|return
name|NULL
return|;
return|return
name|wheel_events
index|[
name|event_id
index|]
operator|.
name|name
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_controller_wheel_get_event_blurb (GimpController * controller,gint event_id)
name|gimp_controller_wheel_get_event_blurb
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|,
name|gint
name|event_id
parameter_list|)
block|{
if|if
condition|(
name|event_id
operator|<
literal|0
operator|||
name|event_id
operator|>=
name|G_N_ELEMENTS
argument_list|(
name|wheel_events
argument_list|)
condition|)
return|return
name|NULL
return|;
return|return
name|wheel_events
index|[
name|event_id
index|]
operator|.
name|blurb
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_controller_wheel_scroll (GimpControllerWheel * wheel,const GdkEventScroll * sevent)
name|gimp_controller_wheel_scroll
parameter_list|(
name|GimpControllerWheel
modifier|*
name|wheel
parameter_list|,
specifier|const
name|GdkEventScroll
modifier|*
name|sevent
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTROLLER_WHEEL
argument_list|(
name|wheel
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|sevent
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|wheel_events
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|wheel_events
index|[
name|i
index|]
operator|.
name|direction
operator|==
name|sevent
operator|->
name|direction
condition|)
block|{
if|if
condition|(
operator|(
name|wheel_events
index|[
name|i
index|]
operator|.
name|modifiers
operator|&
name|sevent
operator|->
name|state
operator|)
operator|==
name|wheel_events
index|[
name|i
index|]
operator|.
name|modifiers
condition|)
block|{
name|GimpControllerEvent
name|controller_event
decl_stmt|;
name|GimpControllerEventTrigger
modifier|*
name|trigger
decl_stmt|;
name|trigger
operator|=
operator|(
name|GimpControllerEventTrigger
operator|*
operator|)
operator|&
name|controller_event
expr_stmt|;
name|trigger
operator|->
name|type
operator|=
name|GIMP_CONTROLLER_EVENT_TRIGGER
expr_stmt|;
name|trigger
operator|->
name|source
operator|=
name|GIMP_CONTROLLER
argument_list|(
name|wheel
argument_list|)
expr_stmt|;
name|trigger
operator|->
name|event_id
operator|=
name|i
expr_stmt|;
if|if
condition|(
name|gimp_controller_event
argument_list|(
name|GIMP_CONTROLLER
argument_list|(
name|wheel
argument_list|)
argument_list|,
operator|&
name|controller_event
argument_list|)
condition|)
block|{
return|return
name|TRUE
return|;
block|}
block|}
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

