begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptemplate.h"
end_include

begin_include
include|#
directive|include
file|"file/file-open.h"
end_include

begin_include
include|#
directive|include
file|"file/file-save.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"dialogs.h"
end_include

begin_include
include|#
directive|include
file|"file-commands.h"
end_include

begin_include
include|#
directive|include
file|"file-new-dialog.h"
end_include

begin_include
include|#
directive|include
file|"file-open-dialog.h"
end_include

begin_include
include|#
directive|include
file|"file-save-dialog.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|REVERT_DATA_KEY
define|#
directive|define
name|REVERT_DATA_KEY
value|"revert-confirm-dialog"
end_define

begin_define
DECL|macro|return_if_no_gimp (gimp,data)
define|#
directive|define
name|return_if_no_gimp
parameter_list|(
name|gimp
parameter_list|,
name|data
parameter_list|)
define|\
value|if (GIMP_IS_DISPLAY (data)) \     gimp = ((GimpDisplay *) data)->gimage->gimp; \   else if (GIMP_IS_GIMP (data)) \     gimp = data; \   else \     gimp = NULL; \   if (! gimp) \     return
end_define

begin_define
DECL|macro|return_if_no_display (gdisp,data)
define|#
directive|define
name|return_if_no_display
parameter_list|(
name|gdisp
parameter_list|,
name|data
parameter_list|)
define|\
value|if (GIMP_IS_DISPLAY (data)) \     gdisp = data; \   else if (GIMP_IS_GIMP (data)) \     gdisp = gimp_context_get_display (gimp_get_user_context (GIMP (data))); \   else \     gdisp = NULL; \   if (! gdisp) \     return
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|file_new_template_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_revert_confirm_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|revert
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|file_new_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|file_new_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
comment|/*  if called from the image menu  */
if|if
condition|(
name|action
condition|)
name|gimage
operator|=
name|gimp_context_get_image
argument_list|(
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimage
operator|=
name|NULL
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-file-new-dialog"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
condition|)
name|file_new_dialog_set
argument_list|(
name|dialog
argument_list|,
name|gimage
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_open_by_extension_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|file_open_by_extension_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|file_open_dialog_set_type
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_open_type_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|file_open_type_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|file_open_dialog_set_type
argument_list|(
operator|(
name|PlugInProcDef
operator|*
operator|)
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_open_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|file_open_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
comment|/*  if called from the image menu  */
if|if
condition|(
name|action
condition|)
name|gimage
operator|=
name|gimp_context_get_image
argument_list|(
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimage
operator|=
name|NULL
expr_stmt|;
name|file_open_dialog_show
argument_list|(
name|gimp
argument_list|,
name|gimage
argument_list|,
name|NULL
argument_list|,
name|global_menu_factory
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_last_opened_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|file_last_opened_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
name|guint
name|num_entries
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|num_entries
operator|=
name|gimp_container_num_children
argument_list|(
name|gimp
operator|->
name|documents
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
operator|>=
name|num_entries
condition|)
return|return;
name|imagefile
operator|=
operator|(
name|GimpImagefile
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|gimp
operator|->
name|documents
argument_list|,
name|action
argument_list|)
expr_stmt|;
if|if
condition|(
name|imagefile
condition|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gimage
operator|=
name|file_open_with_display
argument_list|(
name|gimp
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
operator|->
name|name
argument_list|,
operator|&
name|status
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimage
operator|&&
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Opening '%s' failed:\n\n%s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|file_save_by_extension_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|file_save_by_extension_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|file_save_dialog_set_type
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_save_type_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|file_save_type_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|file_save_dialog_set_type
argument_list|(
operator|(
name|PlugInProcDef
operator|*
operator|)
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_save_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|file_save_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Only save if the gimage has been modified  */
if|if
condition|(
name|gdisp
operator|->
name|gimage
operator|->
name|dirty
operator|||
operator|!
name|GIMP_GUI_CONFIG
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|trust_dirty_flag
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|uri
condition|)
block|{
name|file_save_as_cmd_callback
argument_list|(
name|widget
argument_list|,
name|data
argument_list|,
name|action
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpPDBStatusType
name|status
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|status
operator|=
name|file_save
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|GIMP_RUN_WITH_LAST_VALS
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|!=
name|GIMP_PDB_SUCCESS
operator|&&
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Saving '%s' failed:\n\n%s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|file_save_as_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|file_save_as_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|file_save_dialog_show
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|global_menu_factory
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_save_a_copy_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|file_save_a_copy_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|file_save_a_copy_dialog_show
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|global_menu_factory
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_save_template_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|file_save_template_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GtkWidget
modifier|*
name|qbox
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|qbox
operator|=
name|gimp_query_string_box
argument_list|(
name|_
argument_list|(
literal|"Create New Template"
argument_list|)
argument_list|,
name|gdisp
operator|->
name|shell
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_FILE_SAVE_AS_TEMPLATE
argument_list|,
name|_
argument_list|(
literal|"Enter a name for this template"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|file_new_template_callback
argument_list|,
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|qbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_revert_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|file_revert_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GtkWidget
modifier|*
name|query_box
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|query_box
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|REVERT_DATA_KEY
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|uri
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Revert failed.\n"
literal|"No file name associated with this image."
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|query_box
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|query_box
operator|->
name|window
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|text
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Revert '%s' to\n"
literal|"'%s'?\n\n"
literal|"You will lose all your changes, "
literal|"including all undo information."
argument_list|)
argument_list|,
name|basename
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|query_box
operator|=
name|gimp_query_boolean_box
argument_list|(
name|_
argument_list|(
literal|"Revert Image"
argument_list|)
argument_list|,
name|gdisp
operator|->
name|shell
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_FILE_REVERT
argument_list|,
name|GIMP_STOCK_QUESTION
argument_list|,
name|text
argument_list|,
name|GTK_STOCK_YES
argument_list|,
name|GTK_STOCK_NO
argument_list|,
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|file_revert_confirm_callback
argument_list|,
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|REVERT_DATA_KEY
argument_list|,
name|query_box
argument_list|)
expr_stmt|;
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|query_box
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|query_box
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|file_close_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|file_close_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_display_shell_close
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_quit_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|file_quit_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_exit
argument_list|(
name|gimp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_file_open_dialog (Gimp * gimp,const gchar * uri)
name|file_file_open_dialog
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|file_open_dialog_show
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|uri
argument_list|,
name|global_menu_factory
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|file_new_template_callback (GtkWidget * widget,const gchar * name,gpointer data)
name|file_new_template_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gimage
operator|=
operator|(
name|GimpImage
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|name
operator|&&
name|strlen
argument_list|(
name|name
argument_list|)
operator|)
condition|)
name|name
operator|=
name|_
argument_list|(
literal|"(Unnamed Template)"
argument_list|)
expr_stmt|;
name|template
operator|=
name|gimp_template_new
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|gimp_template_set_from_image
argument_list|(
name|template
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|gimp_list_uniquefy_name
argument_list|(
name|GIMP_LIST
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|templates
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|template
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|templates
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|template
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_revert_confirm_callback (GtkWidget * widget,gboolean revert,gpointer data)
name|file_revert_confirm_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|revert
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|old_gimage
decl_stmt|;
name|old_gimage
operator|=
operator|(
name|GimpImage
operator|*
operator|)
name|data
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|old_gimage
argument_list|)
argument_list|,
name|REVERT_DATA_KEY
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|revert
condition|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpImage
modifier|*
name|new_gimage
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gimp
operator|=
name|old_gimage
operator|->
name|gimp
expr_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|old_gimage
argument_list|)
argument_list|)
expr_stmt|;
name|new_gimage
operator|=
name|file_open_image
argument_list|(
name|gimp
argument_list|,
name|uri
argument_list|,
name|uri
argument_list|,
name|NULL
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
operator|&
name|status
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_gimage
condition|)
block|{
name|GList
modifier|*
name|contexts
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
comment|/*  remember which contexts refer to old_gimage  */
for|for
control|(
name|list
operator|=
name|gimp
operator|->
name|context_list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_context_get_image
argument_list|(
name|context
argument_list|)
operator|==
name|old_gimage
condition|)
name|contexts
operator|=
name|g_list_prepend
argument_list|(
name|contexts
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|gimp_image_undo_free
argument_list|(
name|new_gimage
argument_list|)
expr_stmt|;
name|gimp_displays_reconnect
argument_list|(
name|gimp
argument_list|,
name|old_gimage
argument_list|,
name|new_gimage
argument_list|)
expr_stmt|;
name|gimp_image_clean_all
argument_list|(
name|new_gimage
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|new_gimage
argument_list|)
expr_stmt|;
comment|/*  set the new_gimage on the remembered contexts (in reverse            *  order, since older contexts are usually the parents of            *  newer ones)            */
name|g_list_foreach
argument_list|(
name|contexts
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_context_set_image
argument_list|,
name|new_gimage
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|contexts
argument_list|)
expr_stmt|;
comment|/*  the displays own the image now  */
name|g_object_unref
argument_list|(
name|new_gimage
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Reverting to '%s' failed:\n\n%s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

