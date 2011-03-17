begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpdnd-xds.c  * Copyright (C) 2005  Sven Neumann<sven@gimp.org>  *  * Saving Files via Drag-and-Drop:  * The Direct Save Protocol for the X Window System  *  *   http://www.newplanetsoftware.com/xds/  *   http://rox.sourceforge.net/xds.html  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager-file.h"
end_include

begin_include
include|#
directive|include
file|"file/file-save.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd-xds.h"
end_include

begin_include
include|#
directive|include
file|"gimpfiledialog.h"
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

begin_include
include|#
directive|include
file|"gimp-log.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|MAX_URI_LEN
define|#
directive|define
name|MAX_URI_LEN
value|4096
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|gimp_file_overwrite_dialog
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_dnd_xds_source_set (GdkDragContext * context,GimpImage * image)
name|gimp_dnd_xds_source_set
parameter_list|(
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GdkAtom
name|property
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GDK_IS_DRAG_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|image
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|property
operator|=
name|gdk_atom_intern_static_string
argument_list|(
literal|"XdndDirectSave0"
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|GdkAtom
name|type
init|=
name|gdk_atom_intern_static_string
argument_list|(
literal|"text/plain"
argument_list|)
decl_stmt|;
name|GFile
modifier|*
name|untitled
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|basename
operator|=
name|g_strconcat
argument_list|(
name|_
argument_list|(
literal|"Untitled"
argument_list|)
argument_list|,
literal|".xcf"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|untitled
operator|=
name|g_file_new_for_path
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|file
operator|=
name|gimp_image_get_any_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|file
condition|)
block|{
name|GFile
modifier|*
name|xcf_file
init|=
name|gimp_file_with_new_extension
argument_list|(
name|file
argument_list|,
name|untitled
argument_list|)
decl_stmt|;
name|basename
operator|=
name|g_file_get_basename
argument_list|(
name|xcf_file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|xcf_file
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|basename
operator|=
name|g_file_get_path
argument_list|(
name|untitled
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|untitled
argument_list|)
expr_stmt|;
name|gdk_property_change
argument_list|(
name|gdk_drag_context_get_source_window
argument_list|(
name|context
argument_list|)
argument_list|,
name|property
argument_list|,
name|type
argument_list|,
literal|8
argument_list|,
name|GDK_PROP_MODE_REPLACE
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|basename
argument_list|,
name|basename
condition|?
name|strlen
argument_list|(
name|basename
argument_list|)
else|:
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdk_property_delete
argument_list|(
name|gdk_drag_context_get_source_window
argument_list|(
name|context
argument_list|)
argument_list|,
name|property
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_dnd_xds_save_image (GdkDragContext * context,GimpImage * image,GtkSelectionData * selection)
name|gimp_dnd_xds_save_image
parameter_list|(
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|GdkAtom
name|property
decl_stmt|;
name|GdkAtom
name|type
decl_stmt|;
name|gint
name|length
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|gboolean
name|export
init|=
name|FALSE
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GDK_IS_DRAG_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|property
operator|=
name|gdk_atom_intern_static_string
argument_list|(
literal|"XdndDirectSave0"
argument_list|)
expr_stmt|;
name|type
operator|=
name|gdk_atom_intern_static_string
argument_list|(
literal|"text/plain"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gdk_property_get
argument_list|(
name|gdk_drag_context_get_source_window
argument_list|(
name|context
argument_list|)
argument_list|,
name|property
argument_list|,
name|type
argument_list|,
literal|0
argument_list|,
name|MAX_URI_LEN
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|length
argument_list|,
operator|&
name|data
argument_list|)
condition|)
return|return;
name|uri
operator|=
name|g_strndup
argument_list|(
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|data
argument_list|,
name|length
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_file_new_for_uri
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|proc
operator|=
name|gimp_plug_in_manager_file_procedure_find
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|GIMP_FILE_PROCEDURE_GROUP_SAVE
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
block|{
name|proc
operator|=
name|gimp_plug_in_manager_file_procedure_find
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|GIMP_FILE_PROCEDURE_GROUP_EXPORT
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|export
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
name|proc
condition|)
block|{
if|if
condition|(
operator|!
name|g_file_query_exists
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|)
operator|||
name|gimp_file_overwrite_dialog
argument_list|(
name|NULL
argument_list|,
name|file
argument_list|)
condition|)
block|{
if|if
condition|(
name|file_save
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|image
argument_list|,
name|NULL
argument_list|,
name|file
argument_list|,
name|proc
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
operator|!
name|export
argument_list|,
name|FALSE
argument_list|,
name|export
argument_list|,
operator|&
name|error
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|gtk_selection_data_set
argument_list|(
name|selection
argument_list|,
name|gtk_selection_data_get_target
argument_list|(
name|selection
argument_list|)
argument_list|,
literal|8
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
literal|"S"
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_selection_data_set
argument_list|(
name|selection
argument_list|,
name|gtk_selection_data_get_target
argument_list|(
name|selection
argument_list|)
argument_list|,
literal|8
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
literal|"E"
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|gimp_message
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Saving '%s' failed:\n\n%s"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
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
block|}
block|}
block|}
block|}
else|else
block|{
name|gtk_selection_data_set
argument_list|(
name|selection
argument_list|,
name|gtk_selection_data_get_target
argument_list|(
name|selection
argument_list|)
argument_list|,
literal|8
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
literal|"E"
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_message_literal
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"The given filename does not have any known "
literal|"file extension."
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_file_overwrite_dialog (GtkWidget * parent,GFile * file)
name|gimp_file_overwrite_dialog
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|gboolean
name|overwrite
init|=
name|FALSE
decl_stmt|;
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
name|_
argument_list|(
literal|"File Exists"
argument_list|)
argument_list|,
name|GIMP_ICON_DIALOG_WARNING
argument_list|,
name|parent
argument_list|,
name|GTK_DIALOG_DESTROY_WITH_PARENT
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"_Cancel"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|_
argument_list|(
literal|"_Replace"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_message_box_set_primary_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"A file named '%s' already exists."
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_message_box_set_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"Do you want to replace it with the image "
literal|"you are saving?"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_DIALOG
argument_list|(
name|parent
argument_list|)
condition|)
name|gtk_dialog_set_response_sensitive
argument_list|(
name|GTK_DIALOG
argument_list|(
name|parent
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|overwrite
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_DIALOG
argument_list|(
name|parent
argument_list|)
condition|)
name|gtk_dialog_set_response_sensitive
argument_list|(
name|GTK_DIALOG
argument_list|(
name|parent
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|overwrite
return|;
block|}
end_function

end_unit

