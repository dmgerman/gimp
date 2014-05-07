begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimperrordialog.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimperrordialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpmessagebox.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|GIMP_ERROR_DIALOG_MAX_MESSAGES
define|#
directive|define
name|GIMP_ERROR_DIALOG_MAX_MESSAGES
value|3
end_define

begin_function_decl
specifier|static
name|void
name|gimp_error_dialog_finalize
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
name|gimp_error_dialog_response
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpErrorDialog,gimp_error_dialog,GIMP_TYPE_DIALOG)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpErrorDialog
argument_list|,
argument|gimp_error_dialog
argument_list|,
argument|GIMP_TYPE_DIALOG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_error_dialog_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_error_dialog_class_init
parameter_list|(
name|GimpErrorDialogClass
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
name|GtkDialogClass
modifier|*
name|dialog_class
init|=
name|GTK_DIALOG_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_error_dialog_finalize
expr_stmt|;
name|dialog_class
operator|->
name|response
operator|=
name|gimp_error_dialog_response
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_error_dialog_init (GimpErrorDialog * dialog)
name|gimp_error_dialog_init
parameter_list|(
name|GimpErrorDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-message"
argument_list|)
expr_stmt|;
name|gtk_dialog_add_buttons
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|dialog
operator|->
name|vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|vbox
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|last_box
operator|=
name|NULL
expr_stmt|;
name|dialog
operator|->
name|last_domain
operator|=
name|NULL
expr_stmt|;
name|dialog
operator|->
name|last_message
operator|=
name|NULL
expr_stmt|;
name|dialog
operator|->
name|num_messages
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_error_dialog_finalize (GObject * object)
name|gimp_error_dialog_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpErrorDialog
modifier|*
name|dialog
init|=
name|GIMP_ERROR_DIALOG
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|dialog
operator|->
name|last_domain
condition|)
block|{
name|g_free
argument_list|(
name|dialog
operator|->
name|last_domain
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|last_domain
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|dialog
operator|->
name|last_message
condition|)
block|{
name|g_free
argument_list|(
name|dialog
operator|->
name|last_message
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|last_message
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
DECL|function|gimp_error_dialog_response (GtkDialog * dialog,gint response_id)
name|gimp_error_dialog_response
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_error_dialog_new (const gchar * title)
name|gimp_error_dialog_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_ERROR_DIALOG
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_error_dialog_add (GimpErrorDialog * dialog,const gchar * icon_name,const gchar * domain,const gchar * message)
name|gimp_error_dialog_add
parameter_list|(
name|GimpErrorDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|box
decl_stmt|;
name|gboolean
name|overflow
init|=
name|FALSE
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ERROR_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|domain
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|message
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
operator|->
name|last_box
operator|&&
name|dialog
operator|->
name|last_domain
operator|&&
name|strcmp
argument_list|(
name|dialog
operator|->
name|last_domain
argument_list|,
name|domain
argument_list|)
operator|==
literal|0
operator|&&
name|dialog
operator|->
name|last_message
operator|&&
name|strcmp
argument_list|(
name|dialog
operator|->
name|last_message
argument_list|,
name|message
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|gimp_message_box_repeat
argument_list|(
name|GIMP_MESSAGE_BOX
argument_list|(
name|dialog
operator|->
name|last_box
argument_list|)
argument_list|)
condition|)
return|return;
block|}
if|if
condition|(
name|dialog
operator|->
name|num_messages
operator|>=
name|GIMP_ERROR_DIALOG_MAX_MESSAGES
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: %s\n\n"
argument_list|,
name|domain
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|overflow
operator|=
name|TRUE
expr_stmt|;
name|icon_name
operator|=
name|GIMP_STOCK_WILBER_EEK
expr_stmt|;
name|domain
operator|=
name|_
argument_list|(
literal|"Too many error messages!"
argument_list|)
expr_stmt|;
name|message
operator|=
name|_
argument_list|(
literal|"Messages are redirected to stderr."
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
operator|->
name|last_domain
operator|&&
name|strcmp
argument_list|(
name|dialog
operator|->
name|last_domain
argument_list|,
name|domain
argument_list|)
operator|==
literal|0
operator|&&
name|dialog
operator|->
name|last_message
operator|&&
name|strcmp
argument_list|(
name|dialog
operator|->
name|last_message
argument_list|,
name|message
argument_list|)
operator|==
literal|0
condition|)
block|{
return|return;
block|}
block|}
name|box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_MESSAGE_BOX
argument_list|,
literal|"icon-name"
argument_list|,
name|icon_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|num_messages
operator|++
expr_stmt|;
if|if
condition|(
name|overflow
condition|)
name|gimp_message_box_set_primary_text
argument_list|(
name|GIMP_MESSAGE_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
literal|"%s"
argument_list|,
name|domain
argument_list|)
expr_stmt|;
else|else
name|gimp_message_box_set_primary_text
argument_list|(
name|GIMP_MESSAGE_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
comment|/* %s is a message domain,                                         * like "GIMP Message" or                                         * "PNG Message"                                         */
name|_
argument_list|(
literal|"%s Message"
argument_list|)
argument_list|,
name|domain
argument_list|)
expr_stmt|;
name|gimp_message_box_set_text
argument_list|(
name|GIMP_MESSAGE_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
literal|"%s"
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dialog
operator|->
name|vbox
argument_list|)
argument_list|,
name|box
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|last_box
operator|=
name|box
expr_stmt|;
name|g_free
argument_list|(
name|dialog
operator|->
name|last_domain
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|last_domain
operator|=
name|g_strdup
argument_list|(
name|domain
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dialog
operator|->
name|last_message
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|last_message
operator|=
name|g_strdup
argument_list|(
name|message
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

