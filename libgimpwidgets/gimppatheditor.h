begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppatheditor.h  * Copyright (C) 1999 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

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
DECL|member|file_selection
name|GtkWidget
modifier|*
name|file_selection
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
name|gpe
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
name|filesel_title
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
name|gpe
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_path_editor_set_path
parameter_list|(
name|GimpPathEditor
modifier|*
name|gpe
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
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

