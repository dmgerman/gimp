begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimperrordialog.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
name|gimp_error_dialog_class_init
parameter_list|(
name|GimpErrorDialogClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_error_dialog_init
parameter_list|(
name|GimpErrorDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDialogClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_error_dialog_get_type (void)
name|gimp_error_dialog_get_type
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
name|GimpErrorDialogClass
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
name|gimp_error_dialog_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpErrorDialog
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_error_dialog_init
block|}
decl_stmt|;
name|dialog_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DIALOG
argument_list|,
literal|"GimpErrorDialog"
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
DECL|function|gimp_error_dialog_class_init (GimpErrorDialogClass * klass)
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
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

begin_function
specifier|static
name|void
DECL|function|gimp_error_dialog_set_icon (GtkWidget * dialog,const gchar * stock_id)
name|gimp_error_dialog_set_icon
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
block|{
name|GtkIconSet
modifier|*
name|icon_set
decl_stmt|;
name|gtk_widget_ensure_style
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|icon_set
operator|=
name|gtk_style_lookup_icon_set
argument_list|(
name|dialog
operator|->
name|style
argument_list|,
name|stock_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|icon_set
condition|)
block|{
name|GtkIconSize
modifier|*
name|sizes
decl_stmt|;
name|GList
modifier|*
name|icons
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|n_sizes
decl_stmt|;
name|gtk_icon_set_get_sizes
argument_list|(
name|icon_set
argument_list|,
operator|&
name|sizes
argument_list|,
operator|&
name|n_sizes
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
name|n_sizes
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|sizes
index|[
name|i
index|]
operator|<
name|GTK_ICON_SIZE_DIALOG
condition|)
comment|/* skip the large version */
name|icons
operator|=
name|g_list_prepend
argument_list|(
name|icons
argument_list|,
name|gtk_widget_render_icon
argument_list|(
name|dialog
argument_list|,
name|stock_id
argument_list|,
name|sizes
index|[
name|i
index|]
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|sizes
argument_list|)
expr_stmt|;
if|if
condition|(
name|icons
condition|)
block|{
name|gtk_window_set_icon_list
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|icons
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|icons
argument_list|,
operator|(
name|GFunc
operator|)
name|g_object_unref
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|icons
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_error_dialog_new (const gchar * title,const gchar * stock_id)
name|gimp_error_dialog_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
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
name|dialog
operator|=
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
expr_stmt|;
if|if
condition|(
name|stock_id
condition|)
name|gimp_error_dialog_set_icon
argument_list|(
name|dialog
argument_list|,
name|stock_id
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_error_dialog_add (GimpErrorDialog * dialog,const gchar * stock_id,const gchar * domain,const gchar * message)
name|gimp_error_dialog_add
parameter_list|(
name|GimpErrorDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
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
name|stock_id
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
block|}
comment|/*  yes, these lines are repeated here for a reason  */
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
name|box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_MESSAGE_BOX
argument_list|,
literal|"stock_id"
argument_list|,
name|stock_id
argument_list|,
literal|"border_width"
argument_list|,
literal|12
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
name|message
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dialog
operator|->
name|vbox
argument_list|)
argument_list|,
name|box
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

