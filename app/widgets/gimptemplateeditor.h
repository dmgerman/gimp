begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptemplateeditor.h  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEMPLATE_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEMPLATE_EDITOR_H__
define|#
directive|define
name|__GIMP_TEMPLATE_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkvbox.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_TEMPLATE_EDITOR
define|#
directive|define
name|GIMP_TYPE_TEMPLATE_EDITOR
value|(gimp_template_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_TEMPLATE_EDITOR (obj)
define|#
directive|define
name|GIMP_TEMPLATE_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TEMPLATE_EDITOR, GimpTemplateEditor))
end_define

begin_define
DECL|macro|GIMP_TEMPLATE_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_TEMPLATE_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TEMPLATE_EDITOR, GimpTemplateEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_TEMPLATE_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_TEMPLATE_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TEMPLATE_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_TEMPLATE_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TEMPLATE_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TEMPLATE_EDITOR))
end_define

begin_define
DECL|macro|GIMP_TEMPLATE_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TEMPLATE_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TEMPLATE_EDITOR, GimpTemplateEditorClass))
end_define

begin_typedef
DECL|typedef|GimpTemplateEditorClass
typedef|typedef
name|struct
name|_GimpTemplateEditorClass
name|GimpTemplateEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTemplateEditor
struct|struct
name|_GimpTemplateEditor
block|{
DECL|member|parent_instance
name|GtkVBox
name|parent_instance
decl_stmt|;
DECL|member|template
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
DECL|member|memsize
name|gulong
name|memsize
decl_stmt|;
DECL|member|stock_id_container
name|GimpContainer
modifier|*
name|stock_id_container
decl_stmt|;
DECL|member|stock_id_context
name|GimpContext
modifier|*
name|stock_id_context
decl_stmt|;
DECL|member|aspect_button
name|GtkWidget
modifier|*
name|aspect_button
decl_stmt|;
DECL|member|block_aspect
name|gboolean
name|block_aspect
decl_stmt|;
DECL|member|size_se
name|GtkWidget
modifier|*
name|size_se
decl_stmt|;
DECL|member|memsize_label
name|GtkWidget
modifier|*
name|memsize_label
decl_stmt|;
DECL|member|resolution_se
name|GtkWidget
modifier|*
name|resolution_se
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTemplateEditorClass
struct|struct
name|_GimpTemplateEditorClass
block|{
DECL|member|parent_class
name|GtkVBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_template_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_template_editor_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|edit_template
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_template_editor_set_template
parameter_list|(
name|GimpTemplateEditor
modifier|*
name|editor
parameter_list|,
name|GimpTemplate
modifier|*
name|template
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpTemplate
modifier|*
name|gimp_template_editor_get_template
parameter_list|(
name|GimpTemplateEditor
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
comment|/*  __GIMP_TEMPLATE_EDITOR_H__  */
end_comment

end_unit

