begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpwindow.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"display/display-types.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpcanvas.h"
end_include

begin_include
include|#
directive|include
file|"gimpwindow.h"
end_include

begin_include
include|#
directive|include
file|"gimp-log.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_window_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_window_key_press_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpWindow,gimp_window,GTK_TYPE_WINDOW)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpWindow
argument_list|,
argument|gimp_window
argument_list|,
argument|GTK_TYPE_WINDOW
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_window_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_window_class_init
parameter_list|(
name|GimpWindowClass
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
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_window_dispose
expr_stmt|;
name|widget_class
operator|->
name|key_press_event
operator|=
name|gimp_window_key_press_event
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_window_init (GimpWindow * window)
name|gimp_window_init
parameter_list|(
name|GimpWindow
modifier|*
name|window
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_window_dispose (GObject * object)
name|gimp_window_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|gimp_window_set_primary_focus_widget
argument_list|(
name|GIMP_WINDOW
argument_list|(
name|object
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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

begin_expr_stmt
name|fnord
argument_list|(
name|le
argument_list|)
expr_stmt|;
end_expr_stmt

begin_function
specifier|static
name|gboolean
DECL|function|gimp_window_key_press_event (GtkWidget * widget,GdkEventKey * event)
name|gimp_window_key_press_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|event
parameter_list|)
block|{
name|GimpWindow
modifier|*
name|gimp_window
init|=
name|GIMP_WINDOW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkWindow
modifier|*
name|window
init|=
name|GTK_WINDOW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|focus
init|=
name|gtk_window_get_focus
argument_list|(
name|window
argument_list|)
decl_stmt|;
name|GdkModifierType
name|accel_mods
decl_stmt|;
name|gboolean
name|enable_mnemonics
decl_stmt|;
name|gboolean
name|handled
init|=
name|FALSE
decl_stmt|;
comment|/* we're overriding the GtkWindow implementation here to give    * the focus widget precedence over unmodified accelerators    * before the accelerator activation scheme.    */
comment|/* text widgets get all key events first */
if|if
condition|(
name|focus
operator|&&
operator|(
name|GTK_IS_EDITABLE
argument_list|(
name|focus
argument_list|)
operator|||
name|GTK_IS_TEXT_VIEW
argument_list|(
name|focus
argument_list|)
operator|||
name|GIMP_IS_CANVAS
argument_list|(
name|focus
argument_list|)
operator|||
name|gtk_widget_get_ancestor
argument_list|(
name|focus
argument_list|,
name|GIMP_TYPE_CANVAS
argument_list|)
operator|)
condition|)
block|{
name|handled
operator|=
name|gtk_window_propagate_key_event
argument_list|(
name|window
argument_list|,
name|event
argument_list|)
expr_stmt|;
if|if
condition|(
name|handled
condition|)
name|GIMP_LOG
argument_list|(
name|KEY_EVENTS
argument_list|,
literal|"handled by gtk_window_propagate_key_event(text_widget)"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
specifier|static
name|guint32
name|val
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|(
name|val
operator|=
operator|(
name|val
operator|<<
literal|8
operator|)
operator||
operator|(
operator|(
operator|(
name|int
operator|)
name|event
operator|->
name|keyval
operator|)
operator|&
literal|0xff
operator|)
operator|)
operator|%
literal|141650939
operator|==
literal|62515060
condition|)
name|geimnum
argument_list|(
name|eb
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|handled
operator|&&
name|event
operator|->
name|keyval
operator|==
name|GDK_KEY_Escape
operator|&&
name|gimp_window
operator|->
name|primary_focus_widget
condition|)
block|{
if|if
condition|(
name|focus
operator|!=
name|gimp_window
operator|->
name|primary_focus_widget
condition|)
name|gtk_widget_grab_focus
argument_list|(
name|gimp_window
operator|->
name|primary_focus_widget
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_error_bell
argument_list|(
name|widget
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
name|accel_mods
operator|=
name|gtk_widget_get_modifier_mask
argument_list|(
name|widget
argument_list|,
name|GDK_MODIFIER_INTENT_PRIMARY_ACCELERATOR
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|gtk_widget_get_settings
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gtk-enable-mnemonics"
argument_list|,
operator|&
name|enable_mnemonics
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|enable_mnemonics
condition|)
name|accel_mods
operator||=
name|gtk_window_get_mnemonic_modifier
argument_list|(
name|window
argument_list|)
expr_stmt|;
comment|/* invoke modified accelerators */
if|if
condition|(
operator|!
name|handled
operator|&&
operator|(
name|event
operator|->
name|state
operator|&
name|accel_mods
operator|)
condition|)
block|{
name|handled
operator|=
name|gtk_window_activate_key
argument_list|(
name|window
argument_list|,
name|event
argument_list|)
expr_stmt|;
if|if
condition|(
name|handled
condition|)
name|GIMP_LOG
argument_list|(
name|KEY_EVENTS
argument_list|,
literal|"handled by gtk_window_activate_key(modified)"
argument_list|)
expr_stmt|;
block|}
comment|/* invoke focus widget handlers */
if|if
condition|(
operator|!
name|handled
condition|)
block|{
name|handled
operator|=
name|gtk_window_propagate_key_event
argument_list|(
name|window
argument_list|,
name|event
argument_list|)
expr_stmt|;
if|if
condition|(
name|handled
condition|)
name|GIMP_LOG
argument_list|(
name|KEY_EVENTS
argument_list|,
literal|"handled by gtk_window_propagate_key_event(other_widget)"
argument_list|)
expr_stmt|;
block|}
comment|/* invoke non-modified accelerators */
if|if
condition|(
operator|!
name|handled
operator|&&
operator|!
operator|(
name|event
operator|->
name|state
operator|&
name|accel_mods
operator|)
condition|)
block|{
name|handled
operator|=
name|gtk_window_activate_key
argument_list|(
name|window
argument_list|,
name|event
argument_list|)
expr_stmt|;
if|if
condition|(
name|handled
condition|)
name|GIMP_LOG
argument_list|(
name|KEY_EVENTS
argument_list|,
literal|"handled by gtk_window_activate_key(unmodified)"
argument_list|)
expr_stmt|;
block|}
comment|/* chain up, bypassing gtk_window_key_press(), to invoke binding set */
if|if
condition|(
operator|!
name|handled
condition|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|widget_class
operator|=
name|g_type_class_peek_static
argument_list|(
name|g_type_parent
argument_list|(
name|GTK_TYPE_WINDOW
argument_list|)
argument_list|)
expr_stmt|;
name|handled
operator|=
name|widget_class
operator|->
name|key_press_event
argument_list|(
name|widget
argument_list|,
name|event
argument_list|)
expr_stmt|;
if|if
condition|(
name|handled
condition|)
name|GIMP_LOG
argument_list|(
name|KEY_EVENTS
argument_list|,
literal|"handled by widget_class->key_press_event()"
argument_list|)
expr_stmt|;
block|}
return|return
name|handled
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_window_set_primary_focus_widget (GimpWindow * window,GtkWidget * primary_focus)
name|gimp_window_set_primary_focus_widget
parameter_list|(
name|GimpWindow
modifier|*
name|window
parameter_list|,
name|GtkWidget
modifier|*
name|primary_focus
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|primary_focus
operator|==
name|NULL
operator|||
name|GTK_IS_WIDGET
argument_list|(
name|primary_focus
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|primary_focus
operator|==
name|NULL
operator|||
name|gtk_widget_get_toplevel
argument_list|(
name|primary_focus
argument_list|)
operator|==
name|GTK_WIDGET
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|window
operator|->
name|primary_focus_widget
condition|)
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|window
operator|->
name|primary_focus_widget
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|window
operator|->
name|primary_focus_widget
argument_list|)
expr_stmt|;
name|window
operator|->
name|primary_focus_widget
operator|=
name|primary_focus
expr_stmt|;
if|if
condition|(
name|window
operator|->
name|primary_focus_widget
condition|)
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|window
operator|->
name|primary_focus_widget
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|window
operator|->
name|primary_focus_widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_window_get_primary_focus_widget (GimpWindow * window)
name|gimp_window_get_primary_focus_widget
parameter_list|(
name|GimpWindow
modifier|*
name|window
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|window
operator|->
name|primary_focus_widget
return|;
block|}
end_function

end_unit

