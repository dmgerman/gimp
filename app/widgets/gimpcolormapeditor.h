begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLORMAP_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLORMAP_EDITOR_H__
define|#
directive|define
name|__GIMP_COLORMAP_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|"gimpimageeditor.h"
end_include

begin_include
include|#
directive|include
file|"gui/gui-types.h"
end_include

begin_comment
comment|/* temp hack */
end_comment

begin_define
DECL|macro|GIMP_TYPE_COLORMAP_EDITOR
define|#
directive|define
name|GIMP_TYPE_COLORMAP_EDITOR
value|(gimp_colormap_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLORMAP_EDITOR (obj)
define|#
directive|define
name|GIMP_COLORMAP_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLORMAP_EDITOR, GimpColormapEditor))
end_define

begin_define
DECL|macro|GIMP_COLORMAP_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_COLORMAP_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLORMAP_EDITOR, GimpColormapEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLORMAP_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_COLORMAP_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLORMAP_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_COLORMAP_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLORMAP_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLORMAP_EDITOR))
end_define

begin_define
DECL|macro|GIMP_COLORMAP_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLORMAP_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLORMAP_EDITOR, GimpColormapEditorClass))
end_define

begin_typedef
DECL|typedef|GimpColormapEditorClass
typedef|typedef
name|struct
name|_GimpColormapEditorClass
name|GimpColormapEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColormapEditor
struct|struct
name|_GimpColormapEditor
block|{
DECL|member|parent_instance
name|GimpImageEditor
name|parent_instance
decl_stmt|;
DECL|member|col_index
name|gint
name|col_index
decl_stmt|;
DECL|member|dnd_col_index
name|gint
name|dnd_col_index
decl_stmt|;
DECL|member|palette
name|GtkWidget
modifier|*
name|palette
decl_stmt|;
DECL|member|xn
name|gint
name|xn
decl_stmt|;
DECL|member|yn
name|gint
name|yn
decl_stmt|;
DECL|member|cellsize
name|gint
name|cellsize
decl_stmt|;
DECL|member|edit_button
name|GtkWidget
modifier|*
name|edit_button
decl_stmt|;
DECL|member|add_button
name|GtkWidget
modifier|*
name|add_button
decl_stmt|;
DECL|member|index_adjustment
name|GtkAdjustment
modifier|*
name|index_adjustment
decl_stmt|;
DECL|member|index_spinbutton
name|GtkWidget
modifier|*
name|index_spinbutton
decl_stmt|;
DECL|member|color_entry
name|GtkWidget
modifier|*
name|color_entry
decl_stmt|;
DECL|member|color_notebook
name|ColorNotebook
modifier|*
name|color_notebook
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColormapEditorClass
struct|struct
name|_GimpColormapEditorClass
block|{
DECL|member|parent_class
name|GimpImageEditorClass
name|parent_class
decl_stmt|;
DECL|member|selected
name|void
function_decl|(
modifier|*
name|selected
function_decl|)
parameter_list|(
name|GimpColormapEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_colormap_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_colormap_editor_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_colormap_editor_selected
parameter_list|(
name|GimpColormapEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_colormap_editor_col_index
parameter_list|(
name|GimpColormapEditor
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
comment|/* __GIMP_COLORMAP_EDITOR_H__ */
end_comment

end_unit

