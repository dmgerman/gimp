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

begin_enum
enum|enum
DECL|enum|__anon2b4b7cb30103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_HELP_FUNC
name|PROP_HELP_FUNC
block|,
DECL|enumerator|PROP_HELP_ID
name|PROP_HELP_ID
block|}
enum|;
end_enum

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
name|GObject
modifier|*
name|gimp_dialog_constructor
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
name|void
name|gimp_dialog_dispose
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
name|gimp_dialog_set_property
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
name|gimp_dialog_get_property
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

begin_function_decl
specifier|static
name|void
name|gimp_dialog_help
parameter_list|(
name|GObject
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

begin_decl_stmt
DECL|variable|show_help_button
specifier|static
name|gboolean
name|show_help_button
init|=
name|TRUE
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
name|GtkDialogClass
modifier|*
name|dialog_class
init|=
name|GTK_DIALOG_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_dialog_constructor
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_dialog_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_dialog_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_dialog_get_property
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
comment|/**    * GimpDialog::help-func:    *    * Since: GIMP 2.2    **/
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_HELP_FUNC
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"help-func"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
comment|/**    * GimpDialog::help-id:    *    * Since: GIMP 2.2    **/
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_HELP_ID
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"help-id"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_dialog_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_dialog_constructor
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
name|GimpHelpFunc
name|help_func
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|help_id
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
name|help_func
operator|=
name|g_object_get_data
argument_list|(
name|object
argument_list|,
literal|"gimp-dialog-help-func"
argument_list|)
expr_stmt|;
name|help_id
operator|=
name|g_object_get_data
argument_list|(
name|object
argument_list|,
literal|"gimp-dialog-help-id"
argument_list|)
expr_stmt|;
if|if
condition|(
name|help_func
condition|)
name|gimp_help_connect
argument_list|(
name|GTK_WIDGET
argument_list|(
name|object
argument_list|)
argument_list|,
name|help_func
argument_list|,
name|help_id
argument_list|,
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|show_help_button
operator|&&
name|help_func
operator|&&
name|help_id
condition|)
block|{
name|GtkDialog
modifier|*
name|dialog
init|=
name|GTK_DIALOG
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|button
init|=
name|gtk_button_new_from_stock
argument_list|(
name|GTK_STOCK_HELP
argument_list|)
decl_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_button_box_set_child_secondary
argument_list|(
name|GTK_BUTTON_BOX
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dialog_help
argument_list|)
argument_list|,
name|dialog
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|object
argument_list|,
literal|"gimp-dialog-help-button"
argument_list|,
name|button
argument_list|)
expr_stmt|;
block|}
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dialog_dispose (GObject * object)
name|gimp_dialog_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GdkDisplay
modifier|*
name|display
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|g_main_depth
argument_list|()
operator|==
literal|0
condition|)
block|{
name|display
operator|=
name|gtk_widget_get_display
argument_list|(
name|GTK_WIDGET
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|display
argument_list|)
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
if|if
condition|(
name|display
condition|)
block|{
name|gdk_display_flush
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dialog_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_dialog_set_property
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
case|case
name|PROP_HELP_FUNC
case|:
name|g_object_set_data
argument_list|(
name|object
argument_list|,
literal|"gimp-dialog-help-func"
argument_list|,
name|g_value_get_pointer
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HELP_ID
case|:
name|g_object_set_data_full
argument_list|(
name|object
argument_list|,
literal|"gimp-dialog-help-id"
argument_list|,
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
break|break;
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
DECL|function|gimp_dialog_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_dialog_get_property
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
case|case
name|PROP_HELP_FUNC
case|:
name|g_value_set_pointer
argument_list|(
name|value
argument_list|,
name|g_object_get_data
argument_list|(
name|object
argument_list|,
literal|"gimp-dialog-help-func"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HELP_ID
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|g_object_get_data
argument_list|(
name|object
argument_list|,
literal|"gimp-dialog-help-id"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
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
init|=
name|gdk_event_new
argument_list|(
name|GDK_DELETE
argument_list|)
decl_stmt|;
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

begin_function
specifier|static
name|void
DECL|function|gimp_dialog_help (GObject * dialog)
name|gimp_dialog_help
parameter_list|(
name|GObject
modifier|*
name|dialog
parameter_list|)
block|{
name|GimpHelpFunc
name|help_func
init|=
name|g_object_get_data
argument_list|(
name|dialog
argument_list|,
literal|"gimp-dialog-help-func"
argument_list|)
decl_stmt|;
if|if
condition|(
name|help_func
condition|)
name|help_func
argument_list|(
name|g_object_get_data
argument_list|(
name|dialog
argument_list|,
literal|"gimp-dialog-help-id"
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
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
comment|/**  * gimp_dialog_new_valist:  * @title:        The dialog's title which will be set with  *                gtk_window_set_title().  * @role:         The dialog's @role which will be set with  *                gtk_window_set_role().  * @parent:       The @parent widget of this dialog or %NULL.  * @flags:        The @flags (see the #GtkDialog documentation).  * @help_func:    The function which will be called if the user presses "F1".  * @help_id:      The help_id which will be passed to @help_func.  * @args:         A @va_list destribing the action_area buttons.  *  * Creates a new @GimpDialog widget. If a GtkWindow is specified as  * @parent then the dialog will be made transient for this window.  *  * For a description of the format of the @va_list describing the  * action_area buttons see gtk_dialog_new_with_buttons().  *  * Returns: A #GimpDialog.  **/
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
literal|"role"
argument_list|,
name|role
argument_list|,
literal|"modal"
argument_list|,
operator|(
name|flags
operator|&
name|GTK_DIALOG_MODAL
operator|)
argument_list|,
literal|"help-func"
argument_list|,
name|help_func
argument_list|,
literal|"help-id"
argument_list|,
name|help_id
argument_list|,
name|NULL
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
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|flags
operator|&
name|GTK_DIALOG_DESTROY_WITH_PARENT
condition|)
name|g_signal_connect_object
argument_list|(
name|parent
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dialog_close
argument_list|)
argument_list|,
name|dialog
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
block|}
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

begin_comment
comment|/**  * gimp_dialog_add_buttons_valist:  * @dialog: The @dialog to add buttons to.  * @args:   The buttons as va_list.  *  * This function is essentially the same as gtk_dialog_add_buttons()  * except it takes a va_list instead of '...'  **/
end_comment

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
comment|/*  hide the automatically added help button if another one is added  */
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_HELP
condition|)
block|{
name|GtkWidget
modifier|*
name|button
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-dialog-help-button"
argument_list|)
decl_stmt|;
name|gtk_widget_hide
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
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
block|{
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
block|}
end_function

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b4b7cb30208
block|{
DECL|member|dialog
name|GtkDialog
modifier|*
name|dialog
decl_stmt|;
DECL|member|response_id
name|gint
name|response_id
decl_stmt|;
DECL|member|loop
name|GMainLoop
modifier|*
name|loop
decl_stmt|;
DECL|member|destroyed
name|gboolean
name|destroyed
decl_stmt|;
DECL|typedef|RunInfo
block|}
name|RunInfo
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|run_shutdown_loop (RunInfo * ri)
name|run_shutdown_loop
parameter_list|(
name|RunInfo
modifier|*
name|ri
parameter_list|)
block|{
if|if
condition|(
name|g_main_loop_is_running
argument_list|(
name|ri
operator|->
name|loop
argument_list|)
condition|)
name|g_main_loop_quit
argument_list|(
name|ri
operator|->
name|loop
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run_unmap_handler (GtkDialog * dialog,RunInfo * ri)
name|run_unmap_handler
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|RunInfo
modifier|*
name|ri
parameter_list|)
block|{
name|run_shutdown_loop
argument_list|(
name|ri
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run_response_handler (GtkDialog * dialog,gint response_id,RunInfo * ri)
name|run_response_handler
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|RunInfo
modifier|*
name|ri
parameter_list|)
block|{
name|ri
operator|->
name|response_id
operator|=
name|response_id
expr_stmt|;
name|run_shutdown_loop
argument_list|(
name|ri
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|run_delete_handler (GtkDialog * dialog,GdkEventAny * event,RunInfo * ri)
name|run_delete_handler
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|GdkEventAny
modifier|*
name|event
parameter_list|,
name|RunInfo
modifier|*
name|ri
parameter_list|)
block|{
name|run_shutdown_loop
argument_list|(
name|ri
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
comment|/* Do not destroy */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run_destroy_handler (GtkDialog * dialog,RunInfo * ri)
name|run_destroy_handler
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|RunInfo
modifier|*
name|ri
parameter_list|)
block|{
comment|/* shutdown_loop will be called by run_unmap_handler */
name|ri
operator|->
name|destroyed
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_dialog_run:  * @dialog: a #GimpDialog  *  * This function does exactly the same as gtk_dialog_run() except it  * does not make the dialog modal while the #GMainLoop is running.  *  * Return value: response ID  **/
end_comment

begin_function
name|gint
DECL|function|gimp_dialog_run (GimpDialog * dialog)
name|gimp_dialog_run
parameter_list|(
name|GimpDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|RunInfo
name|ri
init|=
block|{
name|NULL
block|,
name|GTK_RESPONSE_NONE
block|,
name|NULL
block|}
decl_stmt|;
name|gulong
name|response_handler
decl_stmt|;
name|gulong
name|unmap_handler
decl_stmt|;
name|gulong
name|destroy_handler
decl_stmt|;
name|gulong
name|delete_handler
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|response_handler
operator|=
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|run_response_handler
argument_list|)
argument_list|,
operator|&
name|ri
argument_list|)
expr_stmt|;
name|unmap_handler
operator|=
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"unmap"
argument_list|,
name|G_CALLBACK
argument_list|(
name|run_unmap_handler
argument_list|)
argument_list|,
operator|&
name|ri
argument_list|)
expr_stmt|;
name|delete_handler
operator|=
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"delete_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|run_delete_handler
argument_list|)
argument_list|,
operator|&
name|ri
argument_list|)
expr_stmt|;
name|destroy_handler
operator|=
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|run_destroy_handler
argument_list|)
argument_list|,
operator|&
name|ri
argument_list|)
expr_stmt|;
name|ri
operator|.
name|loop
operator|=
name|g_main_loop_new
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|GDK_THREADS_LEAVE
argument_list|()
expr_stmt|;
name|g_main_loop_run
argument_list|(
name|ri
operator|.
name|loop
argument_list|)
expr_stmt|;
name|GDK_THREADS_ENTER
argument_list|()
expr_stmt|;
name|g_main_loop_unref
argument_list|(
name|ri
operator|.
name|loop
argument_list|)
expr_stmt|;
name|ri
operator|.
name|loop
operator|=
name|NULL
expr_stmt|;
name|ri
operator|.
name|destroyed
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|ri
operator|.
name|destroyed
condition|)
block|{
name|g_signal_handler_disconnect
argument_list|(
name|dialog
argument_list|,
name|response_handler
argument_list|)
expr_stmt|;
name|g_signal_handler_disconnect
argument_list|(
name|dialog
argument_list|,
name|unmap_handler
argument_list|)
expr_stmt|;
name|g_signal_handler_disconnect
argument_list|(
name|dialog
argument_list|,
name|delete_handler
argument_list|)
expr_stmt|;
name|g_signal_handler_disconnect
argument_list|(
name|dialog
argument_list|,
name|destroy_handler
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|ri
operator|.
name|response_id
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_dialogs_show_help_button:  * @show: whether a help button should be added when creating a GimpDialog  *  * This function is for internal use only.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_dialogs_show_help_button (gboolean show)
name|gimp_dialogs_show_help_button
parameter_list|(
name|gboolean
name|show
parameter_list|)
block|{
name|show_help_button
operator|=
name|show
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

