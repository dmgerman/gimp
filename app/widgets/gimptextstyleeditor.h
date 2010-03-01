begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextStyleEditor  * Copyright (C) 2010  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_STYLE_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_STYLE_EDITOR_H__
define|#
directive|define
name|__GIMP_TEXT_STYLE_EDITOR_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_TEXT_STYLE_EDITOR
define|#
directive|define
name|GIMP_TYPE_TEXT_STYLE_EDITOR
value|(gimp_text_style_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_TEXT_STYLE_EDITOR (obj)
define|#
directive|define
name|GIMP_TEXT_STYLE_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TEXT_STYLE_EDITOR, GimpTextStyleEditor))
end_define

begin_define
DECL|macro|GIMP_TEXT_STYLE_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_TEXT_STYLE_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TEXT_STYLE_EDITOR, GimpTextStyleEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_STYLE_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_TEXT_STYLE_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TEXT_STYLE_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_STYLE_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TEXT_STYLE_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TEXT_STYLE_EDITOR))
end_define

begin_define
DECL|macro|GIMP_TEXT_STYLE_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TEXT_STYLE_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TEXT_STYLE_EDITOR, GimpTextStyleEditorClass))
end_define

begin_typedef
DECL|typedef|GimpTextStyleEditorClass
typedef|typedef
name|struct
name|_GimpTextStyleEditorClass
name|GimpTextStyleEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTextStyleEditor
struct|struct
name|_GimpTextStyleEditor
block|{
DECL|member|parent_instance
name|GtkHBox
name|parent_instance
decl_stmt|;
DECL|member|buffer
name|GimpTextBuffer
modifier|*
name|buffer
decl_stmt|;
DECL|member|resolution_x
name|gdouble
name|resolution_x
decl_stmt|;
DECL|member|resolution_y
name|gdouble
name|resolution_y
decl_stmt|;
DECL|member|clear_button
name|GtkWidget
modifier|*
name|clear_button
decl_stmt|;
DECL|member|bold_toggle
name|GtkWidget
modifier|*
name|bold_toggle
decl_stmt|;
DECL|member|italic_toggle
name|GtkWidget
modifier|*
name|italic_toggle
decl_stmt|;
DECL|member|underline_toggle
name|GtkWidget
modifier|*
name|underline_toggle
decl_stmt|;
DECL|member|strikethrough_toggle
name|GtkWidget
modifier|*
name|strikethrough_toggle
decl_stmt|;
DECL|member|size_label
name|GtkWidget
modifier|*
name|size_label
decl_stmt|;
DECL|member|toggles
name|GList
modifier|*
name|toggles
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTextStyleEditorClass
struct|struct
name|_GimpTextStyleEditorClass
block|{
DECL|member|parent_class
name|GtkHBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_text_style_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_text_style_editor_new
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|,
name|gdouble
name|resolution_x
parameter_list|,
name|gdouble
name|resolution_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_text_style_editor_list_tags
parameter_list|(
name|GimpTextStyleEditor
modifier|*
name|editor
parameter_list|,
name|GList
modifier|*
modifier|*
name|remove_tags
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TEXT_STYLE_EDITOR_H__  */
end_comment

end_unit

