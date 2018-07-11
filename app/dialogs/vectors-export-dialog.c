begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"vectors-export-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|VectorsExportDialog
typedef|typedef
name|struct
name|_VectorsExportDialog
name|VectorsExportDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_VectorsExportDialog
struct|struct
name|_VectorsExportDialog
block|{
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|active_only
name|gboolean
name|active_only
decl_stmt|;
DECL|member|callback
name|GimpVectorsExportCallback
name|callback
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|vectors_export_dialog_free
parameter_list|(
name|VectorsExportDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|vectors_export_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|VectorsExportDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public function  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|vectors_export_dialog_new (GimpImage * image,GtkWidget * parent,GFile * export_folder,gboolean active_only,GimpVectorsExportCallback callback,gpointer user_data)
name|vectors_export_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GFile
modifier|*
name|export_folder
parameter_list|,
name|gboolean
name|active_only
parameter_list|,
name|GimpVectorsExportCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|VectorsExportDialog
modifier|*
name|private
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
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
name|export_folder
operator|==
name|NULL
operator|||
name|G_IS_FILE
argument_list|(
name|export_folder
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|callback
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_slice_new0
argument_list|(
name|VectorsExportDialog
argument_list|)
expr_stmt|;
name|private
operator|->
name|image
operator|=
name|image
expr_stmt|;
name|private
operator|->
name|active_only
operator|=
name|active_only
expr_stmt|;
name|private
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|private
operator|->
name|user_data
operator|=
name|user_data
expr_stmt|;
name|dialog
operator|=
name|gtk_file_chooser_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Export Path to SVG"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GTK_FILE_CHOOSER_ACTION_SAVE
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
literal|"_Save"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
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
name|GTK_RESPONSE_OK
argument_list|)
expr_stmt|;
name|gimp_dialog_set_alternative_button_order
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
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-vectors-export"
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
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
name|gtk_file_chooser_set_do_overwrite_confirmation
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|export_folder
condition|)
name|gtk_file_chooser_set_current_folder_file
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|export_folder
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|vectors_export_dialog_free
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|image
argument_list|,
literal|"disconnect"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|dialog
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"delete-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_true
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|vectors_export_dialog_response
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_int_combo_box_new
argument_list|(
name|_
argument_list|(
literal|"Export the active path"
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Export all paths from this image"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|private
operator|->
name|active_only
argument_list|)
expr_stmt|;
name|gtk_file_chooser_set_extra_widget
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|combo
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_combo_box_get_active
argument_list|)
argument_list|,
operator|&
name|private
operator|->
name|active_only
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|vectors_export_dialog_free (VectorsExportDialog * private)
name|vectors_export_dialog_free
parameter_list|(
name|VectorsExportDialog
modifier|*
name|private
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|VectorsExportDialog
argument_list|,
name|private
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|vectors_export_dialog_response (GtkWidget * dialog,gint response_id,VectorsExportDialog * private)
name|vectors_export_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|VectorsExportDialog
modifier|*
name|private
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GtkFileChooser
modifier|*
name|chooser
init|=
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|file
operator|=
name|gtk_file_chooser_get_file
argument_list|(
name|chooser
argument_list|)
expr_stmt|;
if|if
condition|(
name|file
condition|)
block|{
name|GFile
modifier|*
name|folder
decl_stmt|;
name|folder
operator|=
name|gtk_file_chooser_get_current_folder_file
argument_list|(
name|chooser
argument_list|)
expr_stmt|;
name|private
operator|->
name|callback
argument_list|(
name|dialog
argument_list|,
name|private
operator|->
name|image
argument_list|,
name|file
argument_list|,
name|folder
argument_list|,
name|private
operator|->
name|active_only
argument_list|,
name|private
operator|->
name|user_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|folder
condition|)
name|g_object_unref
argument_list|(
name|folder
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

