begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptooldialog.c  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimptooldialog.h"
end_include

begin_typedef
DECL|typedef|GimpToolDialogPrivate
typedef|typedef
name|struct
name|_GimpToolDialogPrivate
name|GimpToolDialogPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolDialogPrivate
struct|struct
name|_GimpToolDialogPrivate
block|{
DECL|member|shell
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (dialog)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|dialog
parameter_list|)
value|G_TYPE_INSTANCE_GET_PRIVATE (dialog, \                                                          GIMP_TYPE_TOOL_DIALOG, \                                                          GimpToolDialogPrivate)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_tool_dialog_dispose
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
name|gimp_tool_dialog_shell_unmap
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpToolDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpToolDialog,gimp_tool_dialog,GIMP_TYPE_VIEWABLE_DIALOG)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpToolDialog
argument_list|,
argument|gimp_tool_dialog
argument_list|,
argument|GIMP_TYPE_VIEWABLE_DIALOG
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_tool_dialog_class_init
parameter_list|(
name|GimpToolDialogClass
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
name|object_class
operator|->
name|dispose
operator|=
name|gimp_tool_dialog_dispose
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpToolDialogPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_dialog_init (GimpToolDialog * dialog)
name|gimp_tool_dialog_init
parameter_list|(
name|GimpToolDialog
modifier|*
name|dialog
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_dialog_dispose (GObject * object)
name|gimp_tool_dialog_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolDialogPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|shell
condition|)
block|{
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|private
operator|->
name|shell
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|private
operator|->
name|shell
argument_list|)
expr_stmt|;
name|private
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|gimp_tool_dialog_parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_tool_dialog_new:  * @tool_info: a #GimpToolInfo  * @shell:     the parent display shell this dialog  * @desc:      a string to use in the dialog header or %NULL to use the help  *             field from #GimpToolInfo  * @...:       a %NULL-terminated valist of button parameters as described in  *             gtk_dialog_new_with_buttons().  *  * This function conveniently creates a #GimpViewableDialog using the  * information stored in @tool_info. It also registers the tool with  * the "toplevel" dialog factory.  *  * Return value: a new #GimpViewableDialog  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_tool_dialog_new (GimpToolInfo * tool_info,GimpDisplayShell * shell,const gchar * desc,...)
name|gimp_tool_dialog_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
name|gchar
modifier|*
name|identifier
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_INFO
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|stock_id
operator|=
name|gimp_viewable_get_stock_id
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_DIALOG
argument_list|,
literal|"title"
argument_list|,
name|tool_info
operator|->
name|blurb
argument_list|,
literal|"role"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|tool_info
argument_list|)
argument_list|,
literal|"help-func"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"help-id"
argument_list|,
name|tool_info
operator|->
name|help_id
argument_list|,
literal|"stock-id"
argument_list|,
name|stock_id
argument_list|,
literal|"description"
argument_list|,
name|desc
condition|?
name|desc
else|:
name|tool_info
operator|->
name|help
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_tool_dialog_set_shell
argument_list|(
name|GIMP_TOOL_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|desc
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
name|identifier
operator|=
name|g_strconcat
argument_list|(
name|gimp_object_get_name
argument_list|(
name|tool_info
argument_list|)
argument_list|,
literal|"-dialog"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_add_foreign
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|identifier
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_dialog_set_shell (GimpToolDialog * tool_dialog,GimpDisplayShell * shell)
name|gimp_tool_dialog_set_shell
parameter_list|(
name|GimpToolDialog
modifier|*
name|tool_dialog
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpToolDialogPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|tool_dialog
argument_list|)
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_DIALOG
argument_list|(
name|tool_dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|==
name|private
operator|->
name|shell
condition|)
return|return;
if|if
condition|(
name|private
operator|->
name|shell
condition|)
block|{
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|private
operator|->
name|shell
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|private
operator|->
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|private
operator|->
name|shell
argument_list|,
name|gimp_tool_dialog_shell_unmap
argument_list|,
name|tool_dialog
argument_list|)
expr_stmt|;
name|private
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
block|}
name|private
operator|->
name|shell
operator|=
name|shell
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|shell
condition|)
block|{
name|GtkWidget
modifier|*
name|toplevel
decl_stmt|;
name|g_signal_connect_object
argument_list|(
name|private
operator|->
name|shell
argument_list|,
literal|"unmap"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_dialog_shell_unmap
argument_list|)
argument_list|,
name|tool_dialog
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|private
operator|->
name|shell
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|private
operator|->
name|shell
argument_list|)
expr_stmt|;
name|toplevel
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|tool_dialog
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|toplevel
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_tool_dialog_shell_unmap (GimpDisplayShell * shell,GimpToolDialog * dialog)
name|gimp_tool_dialog_shell_unmap
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpToolDialog
modifier|*
name|dialog
parameter_list|)
block|{
comment|/*  the dialog being mapped while the shell is being unmapped    *  happens when switching images in GimpImageWindow    */
if|if
condition|(
name|gtk_widget_get_mapped
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|)
condition|)
name|g_signal_emit_by_name
argument_list|(
name|dialog
argument_list|,
literal|"close"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

