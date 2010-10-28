begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
DECL|member|view
name|GtkWidget
modifier|*
name|view
decl_stmt|;
DECL|member|col_index
name|gint
name|col_index
decl_stmt|;
DECL|member|layout
name|PangoLayout
modifier|*
name|layout
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
DECL|member|color_dialog
name|GtkWidget
modifier|*
name|color_dialog
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
parameter_list|,
name|GdkModifierType
name|state
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
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_colormap_editor_get_index
parameter_list|(
name|GimpColormapEditor
modifier|*
name|editor
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|search
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_colormap_editor_set_index
parameter_list|(
name|GimpColormapEditor
modifier|*
name|editor
parameter_list|,
name|gint
name|index
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_colormap_editor_max_index
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

