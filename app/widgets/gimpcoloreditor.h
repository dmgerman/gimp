begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcoloreditor.h  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_EDITOR_H__
define|#
directive|define
name|__GIMP_COLOR_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|"gimpeditor.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_COLOR_EDITOR
define|#
directive|define
name|GIMP_TYPE_COLOR_EDITOR
value|(gimp_color_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_EDITOR (obj)
define|#
directive|define
name|GIMP_COLOR_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_EDITOR, GimpColorEditor))
end_define

begin_define
DECL|macro|GIMP_COLOR_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_EDITOR, GimpColorEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_COLOR_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_EDITOR))
end_define

begin_define
DECL|macro|GIMP_COLOR_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_EDITOR, GimpColorEditorClass))
end_define

begin_typedef
DECL|typedef|GimpColorEditorClass
typedef|typedef
name|struct
name|_GimpColorEditorClass
name|GimpColorEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorEditor
struct|struct
name|_GimpColorEditor
block|{
DECL|member|parent_instance
name|GimpEditor
name|parent_instance
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|edit_bg
name|gboolean
name|edit_bg
decl_stmt|;
DECL|member|hbox
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
DECL|member|notebook
name|GtkWidget
modifier|*
name|notebook
decl_stmt|;
DECL|member|fg_bg
name|GtkWidget
modifier|*
name|fg_bg
decl_stmt|;
DECL|member|hex_entry
name|GtkWidget
modifier|*
name|hex_entry
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorEditorClass
struct|struct
name|_GimpColorEditorClass
block|{
DECL|member|parent_class
name|GimpEditorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_color_editor_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COLOR_EDITOR_H__ */
end_comment

end_unit

