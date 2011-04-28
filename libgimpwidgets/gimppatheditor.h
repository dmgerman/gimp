begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppatheditor.h  * Copyright (C) 1999-2004 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_WIDGETS_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_WIDGETS_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpwidgets/gimpwidgets.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PATH_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PATH_EDITOR_H__
define|#
directive|define
name|__GIMP_PATH_EDITOR_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PATH_EDITOR
define|#
directive|define
name|GIMP_TYPE_PATH_EDITOR
value|(gimp_path_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_PATH_EDITOR (obj)
define|#
directive|define
name|GIMP_PATH_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PATH_EDITOR, GimpPathEditor))
end_define

begin_define
DECL|macro|GIMP_PATH_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_PATH_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PATH_EDITOR, GimpPathEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_PATH_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_PATH_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_PATH_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_PATH_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PATH_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PATH_EDITOR))
end_define

begin_define
DECL|macro|GIMP_PATH_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PATH_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PATH_EDITOR, GimpPathEditorClass))
end_define

begin_typedef
DECL|typedef|GimpPathEditorClass
typedef|typedef
name|struct
name|_GimpPathEditorClass
name|GimpPathEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPathEditor
struct|struct
name|_GimpPathEditor
block|{
DECL|member|parent_instance
name|GtkVBox
name|parent_instance
decl_stmt|;
DECL|member|upper_hbox
name|GtkWidget
modifier|*
name|upper_hbox
decl_stmt|;
DECL|member|new_button
name|GtkWidget
modifier|*
name|new_button
decl_stmt|;
DECL|member|up_button
name|GtkWidget
modifier|*
name|up_button
decl_stmt|;
DECL|member|down_button
name|GtkWidget
modifier|*
name|down_button
decl_stmt|;
DECL|member|delete_button
name|GtkWidget
modifier|*
name|delete_button
decl_stmt|;
DECL|member|file_entry
name|GtkWidget
modifier|*
name|file_entry
decl_stmt|;
DECL|member|dir_list
name|GtkListStore
modifier|*
name|dir_list
decl_stmt|;
DECL|member|sel
name|GtkTreeSelection
modifier|*
name|sel
decl_stmt|;
DECL|member|sel_path
name|GtkTreePath
modifier|*
name|sel_path
decl_stmt|;
DECL|member|writable_column
name|GtkTreeViewColumn
modifier|*
name|writable_column
decl_stmt|;
DECL|member|num_items
name|gint
name|num_items
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPathEditorClass
struct|struct
name|_GimpPathEditorClass
block|{
DECL|member|parent_class
name|GtkVBoxClass
name|parent_class
decl_stmt|;
DECL|member|path_changed
name|void
function_decl|(
modifier|*
name|path_changed
function_decl|)
parameter_list|(
name|GimpPathEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
DECL|member|writable_changed
name|void
function_decl|(
modifier|*
name|writable_changed
function_decl|)
parameter_list|(
name|GimpPathEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_decl_stmt
name|GType
name|gimp_path_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_path_editor_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_path_editor_get_path
parameter_list|(
name|GimpPathEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_path_editor_set_path
parameter_list|(
name|GimpPathEditor
modifier|*
name|editor
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_path_editor_get_writable_path
parameter_list|(
name|GimpPathEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_path_editor_set_writable_path
parameter_list|(
name|GimpPathEditor
modifier|*
name|editor
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_path_editor_get_dir_writable
parameter_list|(
name|GimpPathEditor
modifier|*
name|editor
parameter_list|,
specifier|const
name|gchar
modifier|*
name|directory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_path_editor_set_dir_writable
parameter_list|(
name|GimpPathEditor
modifier|*
name|editor
parameter_list|,
specifier|const
name|gchar
modifier|*
name|directory
parameter_list|,
name|gboolean
name|writable
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
comment|/* __GIMP_PATH_EDITOR_H__ */
end_comment

end_unit

