begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcontrollerkeyboard.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<gdk/gdkkeysyms.h>
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
file|"gimpcontrollerkeyboard.h"
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
DECL|typedef|KeyboardEvent
typedef|typedef
name|struct
name|_KeyboardEvent
name|KeyboardEvent
typedef|;
end_typedef

begin_struct
DECL|struct|_KeyboardEvent
struct|struct
name|_KeyboardEvent
block|{
DECL|member|keyval
name|guint
name|keyval
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
name|gimp_controller_keyboard_constructor
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
name|gimp_controller_keyboard_get_n_events
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
name|gimp_controller_keyboard_get_event_name
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
name|gimp_controller_keyboard_get_event_blurb
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
name|GimpControllerKeyboard
argument_list|,
name|gimp_controller_keyboard
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
value|gimp_controller_keyboard_parent_class
end_define

begin_decl_stmt
DECL|variable|keyboard_events
specifier|static
name|KeyboardEvent
name|keyboard_events
index|[]
init|=
block|{
block|{
name|GDK_Up
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"key-up-shift-control-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Up"
argument_list|)
block|}
block|,
block|{
name|GDK_Up
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
block|,
literal|"key-up-control-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Up"
argument_list|)
block|}
block|,
block|{
name|GDK_Up
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"key-up-shift-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Up"
argument_list|)
block|}
block|,
block|{
name|GDK_Up
block|,
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"key-up-shift-control"
block|,
name|N_
argument_list|(
literal|"Cursor Up"
argument_list|)
block|}
block|,
block|{
name|GDK_Up
block|,
name|GDK_MOD1_MASK
block|,
literal|"key-up-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Up"
argument_list|)
block|}
block|,
block|{
name|GDK_Up
block|,
name|GDK_CONTROL_MASK
block|,
literal|"key-up-control"
block|,
name|N_
argument_list|(
literal|"Cursor Up"
argument_list|)
block|}
block|,
block|{
name|GDK_Up
block|,
name|GDK_SHIFT_MASK
block|,
literal|"key-up-shift"
block|,
name|N_
argument_list|(
literal|"Cursor Up"
argument_list|)
block|}
block|,
block|{
name|GDK_Up
block|,
literal|0
block|,
literal|"key-up"
block|,
name|N_
argument_list|(
literal|"Cursor Up"
argument_list|)
block|}
block|,
block|{
name|GDK_Down
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"key-down-shift-control-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Down"
argument_list|)
block|}
block|,
block|{
name|GDK_Down
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
block|,
literal|"key-down-control-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Down"
argument_list|)
block|}
block|,
block|{
name|GDK_Down
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"key-down-shift-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Down"
argument_list|)
block|}
block|,
block|{
name|GDK_Down
block|,
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"key-down-shift-control"
block|,
name|N_
argument_list|(
literal|"Cursor Down"
argument_list|)
block|}
block|,
block|{
name|GDK_Down
block|,
name|GDK_MOD1_MASK
block|,
literal|"key-down-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Down"
argument_list|)
block|}
block|,
block|{
name|GDK_Down
block|,
name|GDK_CONTROL_MASK
block|,
literal|"key-down-control"
block|,
name|N_
argument_list|(
literal|"Cursor Down"
argument_list|)
block|}
block|,
block|{
name|GDK_Down
block|,
name|GDK_SHIFT_MASK
block|,
literal|"key-down-shift"
block|,
name|N_
argument_list|(
literal|"Cursor Down"
argument_list|)
block|}
block|,
block|{
name|GDK_Down
block|,
literal|0
block|,
literal|"key-down"
block|,
name|N_
argument_list|(
literal|"Cursor Down"
argument_list|)
block|}
block|,
block|{
name|GDK_Left
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"key-left-shift-control-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Left"
argument_list|)
block|}
block|,
block|{
name|GDK_Left
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
block|,
literal|"key-left-control-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Left"
argument_list|)
block|}
block|,
block|{
name|GDK_Left
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"key-left-shift-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Left"
argument_list|)
block|}
block|,
block|{
name|GDK_Left
block|,
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"key-left-shift-control"
block|,
name|N_
argument_list|(
literal|"Cursor Left"
argument_list|)
block|}
block|,
block|{
name|GDK_Left
block|,
name|GDK_MOD1_MASK
block|,
literal|"key-left-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Left"
argument_list|)
block|}
block|,
block|{
name|GDK_Left
block|,
name|GDK_CONTROL_MASK
block|,
literal|"key-left-control"
block|,
name|N_
argument_list|(
literal|"Cursor Left"
argument_list|)
block|}
block|,
block|{
name|GDK_Left
block|,
name|GDK_SHIFT_MASK
block|,
literal|"key-left-shift"
block|,
name|N_
argument_list|(
literal|"Cursor Left"
argument_list|)
block|}
block|,
block|{
name|GDK_Left
block|,
literal|0
block|,
literal|"key-left"
block|,
name|N_
argument_list|(
literal|"Cursor Left"
argument_list|)
block|}
block|,
block|{
name|GDK_Right
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"key-right-shift-control-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Right"
argument_list|)
block|}
block|,
block|{
name|GDK_Right
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_CONTROL_MASK
block|,
literal|"key-right-control-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Right"
argument_list|)
block|}
block|,
block|{
name|GDK_Right
block|,
name|GDK_MOD1_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"key-right-shift-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Right"
argument_list|)
block|}
block|,
block|{
name|GDK_Right
block|,
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
block|,
literal|"key-right-shift-control"
block|,
name|N_
argument_list|(
literal|"Cursor Right"
argument_list|)
block|}
block|,
block|{
name|GDK_Right
block|,
name|GDK_MOD1_MASK
block|,
literal|"key-right-alt"
block|,
name|N_
argument_list|(
literal|"Cursor Right"
argument_list|)
block|}
block|,
block|{
name|GDK_Right
block|,
name|GDK_CONTROL_MASK
block|,
literal|"key-right-control"
block|,
name|N_
argument_list|(
literal|"Cursor Right"
argument_list|)
block|}
block|,
block|{
name|GDK_Right
block|,
name|GDK_SHIFT_MASK
block|,
literal|"key-right-shift"
block|,
name|N_
argument_list|(
literal|"Cursor Right"
argument_list|)
block|}
block|,
block|{
name|GDK_Right
block|,
literal|0
block|,
literal|"key-right"
block|,
name|N_
argument_list|(
literal|"Cursor Right"
argument_list|)
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_controller_keyboard_class_init (GimpControllerKeyboardClass * klass)
name|gimp_controller_keyboard_class_init
parameter_list|(
name|GimpControllerKeyboardClass
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
name|gimp_controller_keyboard_constructor
expr_stmt|;
name|controller_class
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Keyboard"
argument_list|)
expr_stmt|;
name|controller_class
operator|->
name|help_id
operator|=
name|GIMP_HELP_CONTROLLER_KEYBOARD
expr_stmt|;
name|controller_class
operator|->
name|get_n_events
operator|=
name|gimp_controller_keyboard_get_n_events
expr_stmt|;
name|controller_class
operator|->
name|get_event_name
operator|=
name|gimp_controller_keyboard_get_event_name
expr_stmt|;
name|controller_class
operator|->
name|get_event_blurb
operator|=
name|gimp_controller_keyboard_get_event_blurb
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_controller_keyboard_init (GimpControllerKeyboard * keyboard)
name|gimp_controller_keyboard_init
parameter_list|(
name|GimpControllerKeyboard
modifier|*
name|keyboard
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
name|keyboard_events
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|KeyboardEvent
modifier|*
name|kevent
init|=
operator|&
name|keyboard_events
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
name|kevent
operator|->
name|modifiers
operator|!=
literal|0
condition|)
block|{
name|kevent
operator|->
name|blurb
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s (%s)"
argument_list|,
name|gettext
argument_list|(
name|kevent
operator|->
name|blurb
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|kevent
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
DECL|function|gimp_controller_keyboard_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_controller_keyboard_constructor
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
literal|"Keyboard Events"
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
DECL|function|gimp_controller_keyboard_get_n_events (GimpController * controller)
name|gimp_controller_keyboard_get_n_events
parameter_list|(
name|GimpController
modifier|*
name|controller
parameter_list|)
block|{
return|return
name|G_N_ELEMENTS
argument_list|(
name|keyboard_events
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_controller_keyboard_get_event_name (GimpController * controller,gint event_id)
name|gimp_controller_keyboard_get_event_name
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
name|keyboard_events
argument_list|)
condition|)
return|return
name|NULL
return|;
return|return
name|keyboard_events
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
DECL|function|gimp_controller_keyboard_get_event_blurb (GimpController * controller,gint event_id)
name|gimp_controller_keyboard_get_event_blurb
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
name|keyboard_events
argument_list|)
condition|)
return|return
name|NULL
return|;
return|return
name|keyboard_events
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
DECL|function|gimp_controller_keyboard_key_press (GimpControllerKeyboard * keyboard,const GdkEventKey * kevent)
name|gimp_controller_keyboard_key_press
parameter_list|(
name|GimpControllerKeyboard
modifier|*
name|keyboard
parameter_list|,
specifier|const
name|GdkEventKey
modifier|*
name|kevent
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTROLLER_KEYBOARD
argument_list|(
name|keyboard
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|kevent
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
name|keyboard_events
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|keyboard_events
index|[
name|i
index|]
operator|.
name|keyval
operator|==
name|kevent
operator|->
name|keyval
condition|)
block|{
if|if
condition|(
operator|(
name|keyboard_events
index|[
name|i
index|]
operator|.
name|modifiers
operator|&
name|kevent
operator|->
name|state
operator|)
operator|==
name|keyboard_events
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
name|keyboard
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
name|keyboard
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

