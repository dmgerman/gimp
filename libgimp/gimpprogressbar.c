begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpprogressbar.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<gdk/gdkwin32.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_X11
end_ifdef

begin_include
include|#
directive|include
file|<gdk/gdkx.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"gimpuitypes.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogressbar.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_progress_bar_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_progress_bar_start
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_progress_bar_end
parameter_list|(
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_progress_bar_set_text
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_progress_bar_set_value
parameter_list|(
name|gdouble
name|percentage
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_progress_bar_pulse
parameter_list|(
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|guint32
name|gimp_progress_bar_get_window
parameter_list|(
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpProgressBar,gimp_progress_bar,GTK_TYPE_PROGRESS_BAR)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpProgressBar
argument_list|,
argument|gimp_progress_bar
argument_list|,
argument|GTK_TYPE_PROGRESS_BAR
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_progress_bar_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_progress_bar_class_init
parameter_list|(
name|GimpProgressBarClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
init|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_progress_bar_destroy
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_bar_init (GimpProgressBar * bar)
name|gimp_progress_bar_init
parameter_list|(
name|GimpProgressBar
modifier|*
name|bar
parameter_list|)
block|{
name|GimpProgressVtable
name|vtable
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gtk_progress_bar_set_text
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|bar
argument_list|)
argument_list|,
literal|" "
argument_list|)
expr_stmt|;
name|gtk_progress_bar_set_ellipsize
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|bar
argument_list|)
argument_list|,
name|PANGO_ELLIPSIZE_END
argument_list|)
expr_stmt|;
name|vtable
operator|.
name|start
operator|=
name|gimp_progress_bar_start
expr_stmt|;
name|vtable
operator|.
name|end
operator|=
name|gimp_progress_bar_end
expr_stmt|;
name|vtable
operator|.
name|set_text
operator|=
name|gimp_progress_bar_set_text
expr_stmt|;
name|vtable
operator|.
name|set_value
operator|=
name|gimp_progress_bar_set_value
expr_stmt|;
name|vtable
operator|.
name|pulse
operator|=
name|gimp_progress_bar_pulse
expr_stmt|;
name|vtable
operator|.
name|get_window
operator|=
name|gimp_progress_bar_get_window
expr_stmt|;
name|bar
operator|->
name|progress_callback
operator|=
name|gimp_progress_install_vtable
argument_list|(
operator|&
name|vtable
argument_list|,
name|bar
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_bar_destroy (GtkObject * object)
name|gimp_progress_bar_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpProgressBar
modifier|*
name|bar
init|=
name|GIMP_PROGRESS_BAR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|bar
operator|->
name|progress_callback
condition|)
block|{
name|gimp_progress_uninstall
argument_list|(
name|bar
operator|->
name|progress_callback
argument_list|)
expr_stmt|;
name|bar
operator|->
name|progress_callback
operator|=
name|NULL
expr_stmt|;
block|}
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_bar_start (const gchar * message,gboolean cancelable,gpointer user_data)
name|gimp_progress_bar_start
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpProgressBar
modifier|*
name|bar
init|=
name|GIMP_PROGRESS_BAR
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|gtk_progress_bar_set_text
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|bar
argument_list|)
argument_list|,
name|message
condition|?
name|message
else|:
literal|" "
argument_list|)
expr_stmt|;
name|gtk_progress_bar_set_fraction
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|bar
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|bar
argument_list|)
condition|)
while|while
condition|(
name|g_main_context_pending
argument_list|(
name|NULL
argument_list|)
condition|)
name|g_main_context_iteration
argument_list|(
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_bar_end (gpointer user_data)
name|gimp_progress_bar_end
parameter_list|(
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpProgressBar
modifier|*
name|bar
init|=
name|GIMP_PROGRESS_BAR
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|gtk_progress_bar_set_text
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|bar
argument_list|)
argument_list|,
literal|" "
argument_list|)
expr_stmt|;
name|gtk_progress_bar_set_fraction
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|bar
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|bar
argument_list|)
condition|)
while|while
condition|(
name|g_main_context_pending
argument_list|(
name|NULL
argument_list|)
condition|)
name|g_main_context_iteration
argument_list|(
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_bar_set_text (const gchar * message,gpointer user_data)
name|gimp_progress_bar_set_text
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpProgressBar
modifier|*
name|bar
init|=
name|GIMP_PROGRESS_BAR
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|gtk_progress_bar_set_text
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|bar
argument_list|)
argument_list|,
name|message
condition|?
name|message
else|:
literal|" "
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|bar
argument_list|)
condition|)
while|while
condition|(
name|g_main_context_pending
argument_list|(
name|NULL
argument_list|)
condition|)
name|g_main_context_iteration
argument_list|(
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_bar_set_value (gdouble percentage,gpointer user_data)
name|gimp_progress_bar_set_value
parameter_list|(
name|gdouble
name|percentage
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpProgressBar
modifier|*
name|bar
init|=
name|GIMP_PROGRESS_BAR
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
if|if
condition|(
name|percentage
operator|>=
literal|0.0
condition|)
name|gtk_progress_bar_set_fraction
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|bar
argument_list|)
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
else|else
name|gtk_progress_bar_pulse
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|bar
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|bar
argument_list|)
condition|)
while|while
condition|(
name|g_main_context_pending
argument_list|(
name|NULL
argument_list|)
condition|)
name|g_main_context_iteration
argument_list|(
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_bar_pulse (gpointer user_data)
name|gimp_progress_bar_pulse
parameter_list|(
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpProgressBar
modifier|*
name|bar
init|=
name|GIMP_PROGRESS_BAR
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|gtk_progress_bar_pulse
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|bar
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|bar
argument_list|)
condition|)
while|while
condition|(
name|g_main_context_pending
argument_list|(
name|NULL
argument_list|)
condition|)
name|g_main_context_iteration
argument_list|(
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GdkNativeWindow
DECL|function|gimp_window_get_native (GtkWindow * window)
name|gimp_window_get_native
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GDK_NATIVE_WINDOW_POINTER
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|gimp_window_get_native() unimplementable for the target windowing system
endif|#
directive|endif
endif|#
directive|endif
ifdef|#
directive|ifdef
name|GDK_WINDOWING_WIN32
if|if
condition|(
name|window
operator|&&
name|GTK_WIDGET_REALIZED
argument_list|(
name|window
argument_list|)
condition|)
return|return
name|GDK_WINDOW_HWND
argument_list|(
name|GTK_WIDGET
argument_list|(
name|window
argument_list|)
operator|->
name|window
argument_list|)
return|;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|GDK_WINDOWING_X11
if|if
condition|(
name|window
operator|&&
name|GTK_WIDGET_REALIZED
argument_list|(
name|window
argument_list|)
condition|)
return|return
name|GDK_WINDOW_XID
argument_list|(
name|GTK_WIDGET
argument_list|(
name|window
argument_list|)
operator|->
name|window
argument_list|)
return|;
endif|#
directive|endif
return|return
literal|0
return|;
block|}
end_function

begin_function
specifier|static
name|guint32
DECL|function|gimp_progress_bar_get_window (gpointer user_data)
name|gimp_progress_bar_get_window
parameter_list|(
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpProgressBar
modifier|*
name|bar
init|=
name|GIMP_PROGRESS_BAR
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|toplevel
decl_stmt|;
name|toplevel
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|bar
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_WINDOW
argument_list|(
name|toplevel
argument_list|)
condition|)
return|return
operator|(
name|guint32
operator|)
name|gimp_window_get_native
argument_list|(
name|GTK_WINDOW
argument_list|(
name|toplevel
argument_list|)
argument_list|)
return|;
return|return
literal|0
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_progress_bar_new:  *  * Creates a new #GimpProgressBar widget.  *  * Return value: the new widget.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_progress_bar_new (void)
name|gimp_progress_bar_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_PROGRESS_BAR
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

