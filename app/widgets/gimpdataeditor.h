begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdataeditor.h  * Copyright (C) 2002-2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DATA_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DATA_EDITOR_H__
define|#
directive|define
name|__GIMP_DATA_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|"gimpeditor.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DATA_EDITOR
define|#
directive|define
name|GIMP_TYPE_DATA_EDITOR
value|(gimp_data_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_DATA_EDITOR (obj)
define|#
directive|define
name|GIMP_DATA_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DATA_EDITOR, GimpDataEditor))
end_define

begin_define
DECL|macro|GIMP_DATA_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_DATA_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DATA_EDITOR, GimpDataEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_DATA_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_DATA_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DATA_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_DATA_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DATA_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DATA_EDITOR))
end_define

begin_define
DECL|macro|GIMP_DATA_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DATA_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DATA_EDITOR, GimpDataEditorClass))
end_define

begin_typedef
DECL|typedef|GimpDataEditorClass
typedef|typedef
name|struct
name|_GimpDataEditorClass
name|GimpDataEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDataEditor
struct|struct
name|_GimpDataEditor
block|{
DECL|member|parent_instance
name|GimpEditor
name|parent_instance
decl_stmt|;
DECL|member|data_factory
name|GimpDataFactory
modifier|*
name|data_factory
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|edit_active
name|gboolean
name|edit_active
decl_stmt|;
DECL|member|data
name|GimpData
modifier|*
name|data
decl_stmt|;
DECL|member|data_editable
name|gboolean
name|data_editable
decl_stmt|;
DECL|member|name_entry
name|GtkWidget
modifier|*
name|name_entry
decl_stmt|;
DECL|member|save_button
name|GtkWidget
modifier|*
name|save_button
decl_stmt|;
DECL|member|revert_button
name|GtkWidget
modifier|*
name|revert_button
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDataEditorClass
struct|struct
name|_GimpDataEditorClass
block|{
DECL|member|parent_class
name|GimpEditorClass
name|parent_class
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|set_data
name|void
function_decl|(
modifier|*
name|set_data
function_decl|)
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
DECL|member|title
specifier|const
name|gchar
modifier|*
name|title
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_data_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_data_editor_set_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpData
modifier|*
name|gimp_data_editor_get_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_data_editor_set_edit_active
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|gboolean
name|edit_active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_data_editor_get_edit_active
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DATA_EDITOR_H__  */
end_comment

end_unit

