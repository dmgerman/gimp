begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdialog.c  * Copyright (C) 2000-2003 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialog.h"
end_include

begin_include
include|#
directive|include
file|"gimphelpui.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_dialog_class_init
parameter_list|(
name|GimpDialogClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dialog_init
parameter_list|(
name|GimpDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dialog_delete_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventAny
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dialog_close
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkDialogClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_dialog_get_type (void)
name|gimp_dialog_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|dialog_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|dialog_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|dialog_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpDialogClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_dialog_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpDialog
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_dialog_init
block|,       }
decl_stmt|;
name|dialog_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_DIALOG
argument_list|,
literal|"GimpDialog"
argument_list|,
operator|&
name|dialog_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|dialog_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dialog_class_init (GimpDialogClass * klass)
name|gimp_dialog_class_init
parameter_list|(
name|GimpDialogClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|GtkDialogClass
modifier|*
name|dialog_class
decl_stmt|;
name|widget_class
operator|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|dialog_class
operator|=
name|GTK_DIALOG_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|widget_class
operator|->
name|delete_event
operator|=
name|gimp_dialog_delete_event
expr_stmt|;
name|dialog_class
operator|->
name|close
operator|=
name|gimp_dialog_close
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dialog_init (GimpDialog * dialog)
name|gimp_dialog_init
parameter_list|(
name|GimpDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|gtk_dialog_set_has_separator
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dialog_delete_event (GtkWidget * widget,GdkEventAny * event)
name|gimp_dialog_delete_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventAny
modifier|*
name|event
parameter_list|)
block|{
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dialog_close (GtkDialog * dialog)
name|gimp_dialog_close
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|)
block|{
comment|/* Synthesize delete_event to close dialog. */
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
if|if
condition|(
name|widget
operator|->
name|window
condition|)
block|{
name|GdkEvent
modifier|*
name|event
decl_stmt|;
name|event
operator|=
name|gdk_event_new
argument_list|(
name|GDK_DELETE
argument_list|)
expr_stmt|;
name|event
operator|->
name|any
operator|.
name|window
operator|=
name|g_object_ref
argument_list|(
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
name|event
operator|->
name|any
operator|.
name|send_event
operator|=
name|TRUE
expr_stmt|;
name|gtk_main_do_event
argument_list|(
name|event
argument_list|)
expr_stmt|;
name|gdk_event_free
argument_list|(
name|event
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_dialog_new:  * @title:        The dialog's title which will be set with  *                gtk_window_set_title().  * @role:         The dialog's @role which will be set with  *                gtk_window_set_role().  * @parent:       The @parent widget of this dialog.  * @flags:        The @flags (see the #GtkDialog documentation).  * @help_func:    The function which will be called if the user presses "F1".  * @help_id:      The help_id which will be passed to @help_func.  * @...:          A %NULL-terminated @va_list destribing the  *                action_area buttons.  *  * Creates a new @GimpDialog widget.  *  * This function simply packs the action_area arguments passed in "..."  * into a @va_list variable and passes everything to gimp_dialog_new_valist().  *  * For a description of the format of the @va_list describing the  * action_area buttons see gtk_dialog_new_with_buttons().  *  * Returns: A #GimpDialog.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dialog_new (const gchar * title,const gchar * role,GtkWidget * parent,GtkDialogFlags flags,GimpHelpFunc help_func,const gchar * help_id,...)
name|gimp_dialog_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GtkDialogFlags
name|flags
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parent
operator|==
name|NULL
operator|||
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|role
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new_valist
argument_list|(
name|title
argument_list|,
name|role
argument_list|,
name|parent
argument_list|,
name|flags
argument_list|,
name|help_func
argument_list|,
name|help_id
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_dialog_new_valist:  * @title:        The dialog's title which will be set with  *                gtk_window_set_title().  * @role:         The dialog's @role which will be set with  *                gtk_window_set_role().  * @parent:       The @parent widget of this dialog.  * @flags:        The @flags (see the #GtkDialog documentation).  * @help_func:    The function which will be called if the user presses "F1".  * @help_id:      The help_id which will be passed to @help_func.  * @va_list:      A @va_list destribing the action_area buttons.  *  * Creates a new @GimpDialog widget.  *  * For a description of the format of the @va_list describing the  * action_area buttons see gtk_dialog_new_with_buttons().  *  * Returns: A #GimpDialog.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dialog_new_valist (const gchar * title,const gchar * role,GtkWidget * parent,GtkDialogFlags flags,GimpHelpFunc help_func,const gchar * help_id,va_list args)
name|gimp_dialog_new_valist
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GtkDialogFlags
name|flags
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parent
operator|==
name|NULL
operator|||
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|role
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DIALOG
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|role
argument_list|)
expr_stmt|;
if|if
condition|(
name|parent
condition|)
block|{
if|if
condition|(
name|GTK_IS_WINDOW
argument_list|(
name|parent
argument_list|)
condition|)
block|{
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* TODO */
block|}
block|}
if|if
condition|(
name|flags
operator|&
name|GTK_DIALOG_MODAL
condition|)
name|gtk_window_set_modal
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|flags
operator|&
name|GTK_DIALOG_DESTROY_WITH_PARENT
condition|)
name|gtk_window_set_destroy_with_parent
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|help_func
condition|)
name|gimp_help_connect
argument_list|(
name|dialog
argument_list|,
name|help_func
argument_list|,
name|help_id
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gimp_dialog_add_buttons_valist
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|args
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dialog_add_buttons_valist (GimpDialog * dialog,va_list args)
name|gimp_dialog_add_buttons_valist
parameter_list|(
name|GimpDialog
modifier|*
name|dialog
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|button_text
decl_stmt|;
name|gint
name|response_id
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|button_text
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
operator|)
condition|)
block|{
name|response_id
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gint
argument_list|)
expr_stmt|;
name|gtk_dialog_add_button
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|button_text
argument_list|,
name|response_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

