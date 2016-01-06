begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsavedialog.h  * Copyright (C) 2015 Jehan<jehan@girinstud.io>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SAVE_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SAVE_DIALOG_H__
define|#
directive|define
name|__GIMP_SAVE_DIALOG_H__
end_define

begin_include
include|#
directive|include
file|"gimpfiledialog.h"
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_SAVE_DIALOG
define|#
directive|define
name|GIMP_TYPE_SAVE_DIALOG
value|(gimp_save_dialog_get_type ())
end_define

begin_define
DECL|macro|GIMP_SAVE_DIALOG (obj)
define|#
directive|define
name|GIMP_SAVE_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SAVE_DIALOG, GimpSaveDialog))
end_define

begin_define
DECL|macro|GIMP_SAVE_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_SAVE_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SAVE_DIALOG, GimpSaveDialogClass))
end_define

begin_define
DECL|macro|GIMP_IS_SAVE_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_SAVE_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SAVE_DIALOG))
end_define

begin_define
DECL|macro|GIMP_IS_SAVE_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SAVE_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SAVE_DIALOG))
end_define

begin_define
DECL|macro|GIMP_SAVE_DIALOG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SAVE_DIALOG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SAVE_DIALOG, GimpSaveDialogClass))
end_define

begin_typedef
DECL|typedef|GimpSaveDialogClass
typedef|typedef
name|struct
name|_GimpSaveDialogClass
name|GimpSaveDialogClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSaveDialog
struct|struct
name|_GimpSaveDialog
block|{
DECL|member|parent_instance
name|GimpFileDialog
name|parent_instance
decl_stmt|;
DECL|member|save_a_copy
name|gboolean
name|save_a_copy
decl_stmt|;
DECL|member|close_after_saving
name|gboolean
name|close_after_saving
decl_stmt|;
DECL|member|display_to_close
name|GimpObject
modifier|*
name|display_to_close
decl_stmt|;
DECL|member|compat_toggle
name|GtkWidget
modifier|*
name|compat_toggle
decl_stmt|;
DECL|member|compat_info
name|GtkWidget
modifier|*
name|compat_info
decl_stmt|;
DECL|member|compat
name|gboolean
name|compat
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSaveDialogClass
struct|struct
name|_GimpSaveDialogClass
block|{
DECL|member|parent_class
name|GimpFileDialogClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_save_dialog_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_save_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_save_dialog_set_image
parameter_list|(
name|GimpSaveDialog
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|save_a_copy
parameter_list|,
name|gboolean
name|close_after_saving
parameter_list|,
name|GimpObject
modifier|*
name|display
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
comment|/* __GIMP_SAVE_DIALOG_H__ */
end_comment

end_unit

