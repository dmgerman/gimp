begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextEditor  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_EDITOR_H__
define|#
directive|define
name|__GIMP_TEXT_EDITOR_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_TEXT_EDITOR
define|#
directive|define
name|GIMP_TYPE_TEXT_EDITOR
value|(gimp_text_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_TEXT_EDITOR (obj)
define|#
directive|define
name|GIMP_TEXT_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TEXT_EDITOR, GimpTextEditor))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_TEXT_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TEXT_EDITOR))
end_define

begin_typedef
DECL|typedef|GimpTextEditorClass
typedef|typedef
name|struct
name|_GimpTextEditorClass
name|GimpTextEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTextEditor
struct|struct
name|_GimpTextEditor
block|{
DECL|member|parent_instance
name|GimpDialog
name|parent_instance
decl_stmt|;
DECL|member|base_dir
name|GimpTextDirection
name|base_dir
decl_stmt|;
comment|/*<  private>*/
DECL|member|buffer
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
DECL|member|group
name|GtkWidget
modifier|*
name|group
decl_stmt|;
DECL|member|view
name|GtkWidget
modifier|*
name|view
decl_stmt|;
DECL|member|filesel
name|GtkWidget
modifier|*
name|filesel
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTextEditorClass
struct|struct
name|_GimpTextEditorClass
block|{
DECL|member|parent_class
name|GimpDialogClass
name|parent_class
decl_stmt|;
DECL|member|dir_changed
name|void
function_decl|(
modifier|*
name|dir_changed
function_decl|)
parameter_list|(
name|GimpTextEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_text_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_text_editor_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|GtkTextBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_editor_set_direction
parameter_list|(
name|GimpTextEditor
modifier|*
name|editor
parameter_list|,
name|GimpTextDirection
name|base_dir
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TEXT_EDITOR_H__ */
end_comment

end_unit

