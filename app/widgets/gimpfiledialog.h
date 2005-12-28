begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfiledialog.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FILE_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FILE_DIALOG_H__
define|#
directive|define
name|__GIMP_FILE_DIALOG_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_FILE_DIALOG
define|#
directive|define
name|GIMP_TYPE_FILE_DIALOG
value|(gimp_file_dialog_get_type ())
end_define

begin_define
DECL|macro|GIMP_FILE_DIALOG (obj)
define|#
directive|define
name|GIMP_FILE_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FILE_DIALOG, GimpFileDialog))
end_define

begin_define
DECL|macro|GIMP_FILE_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_FILE_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FILE_DIALOG, GimpFileDialogClass))
end_define

begin_define
DECL|macro|GIMP_IS_FILE_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_FILE_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FILE_DIALOG))
end_define

begin_define
DECL|macro|GIMP_IS_FILE_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FILE_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FILE_DIALOG))
end_define

begin_define
DECL|macro|GIMP_FILE_DIALOG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_FILE_DIALOG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FILE_DIALOG, GimpFileDialogClass))
end_define

begin_typedef
DECL|typedef|GimpFileDialogClass
typedef|typedef
name|struct
name|_GimpFileDialogClass
name|GimpFileDialogClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFileDialog
struct|struct
name|_GimpFileDialog
block|{
DECL|member|parent_instance
name|GtkFileChooserDialog
name|parent_instance
decl_stmt|;
DECL|member|file_proc
name|PlugInProcDef
modifier|*
name|file_proc
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
DECL|member|save_a_copy
name|gboolean
name|save_a_copy
decl_stmt|;
DECL|member|thumb_box
name|GtkWidget
modifier|*
name|thumb_box
decl_stmt|;
DECL|member|proc_expander
name|GtkWidget
modifier|*
name|proc_expander
decl_stmt|;
DECL|member|proc_view
name|GtkWidget
modifier|*
name|proc_view
decl_stmt|;
DECL|member|progress
name|GtkWidget
modifier|*
name|progress
decl_stmt|;
DECL|member|busy
name|gboolean
name|busy
decl_stmt|;
DECL|member|canceled
name|gboolean
name|canceled
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFileDialogClass
struct|struct
name|_GimpFileDialogClass
block|{
DECL|member|parent_class
name|GtkFileChooserDialogClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_file_dialog_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_file_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GtkFileChooserAction
name|action
parameter_list|,
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
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_file_dialog_set_sensitive
parameter_list|(
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_file_dialog_set_file_proc
parameter_list|(
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|,
name|PlugInProcDef
modifier|*
name|file_proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_file_dialog_set_image
parameter_list|(
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gboolean
name|save_a_copy
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_FILE_DIALOG_H__ */
end_comment

end_unit

