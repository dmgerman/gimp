begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmessagedialog.c  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpmessagebox.h"
end_include

begin_include
include|#
directive|include
file|"gimpmessagedialog.h"
end_include

begin_function
name|GType
DECL|function|gimp_message_dialog_get_type (void)
name|gimp_message_dialog_get_type
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
name|GimpMessageDialogClass
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
name|NULL
block|,
comment|/* class_init     */
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpMessageDialog
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
name|dialog_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DIALOG
argument_list|,
literal|"GimpMessageDialog"
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_message_dialog_new (const gchar * title,const gchar * stock_id,GtkWidget * parent,GtkDialogFlags flags,GimpHelpFunc help_func,const gchar * help_id,...)
name|gimp_message_dialog_new
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
name|GimpMessageDialog
modifier|*
name|dialog
decl_stmt|;
name|va_list
name|args
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
if|if
condition|(
name|parent
condition|)
block|{
if|if
condition|(
operator|!
name|GTK_IS_WINDOW
argument_list|(
name|parent
argument_list|)
condition|)
name|parent
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|parent
argument_list|)
expr_stmt|;
block|}
name|dialog
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_MESSAGE_DIALOG
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
literal|"role"
argument_list|,
literal|"gimp-message-dialog"
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
block|}
name|va_start
argument_list|(
name|args
argument_list|,
name|help_id
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
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|dialog
operator|->
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
name|NULL
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
name|GTK_WIDGET
argument_list|(
name|dialog
operator|->
name|box
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
operator|->
name|box
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
return|;
block|}
end_function

end_unit

