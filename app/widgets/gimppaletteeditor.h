begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PALETTE_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PALETTE_EDITOR_H__
define|#
directive|define
name|__GIMP_PALETTE_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|"gimpdataeditor.h"
end_include

begin_include
include|#
directive|include
file|"gui/gui-types.h"
end_include

begin_comment
comment|/* FIXME */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon276eb2490103
block|{
DECL|enumerator|GIMP_UPDATE_COLOR_STATE_NEW
name|GIMP_UPDATE_COLOR_STATE_NEW
block|,
DECL|enumerator|GIMP_UPDATE_COLOR_STATE_UPDATE_NEW
name|GIMP_UPDATE_COLOR_STATE_UPDATE_NEW
block|,
DECL|enumerator|GIMP_UPDATE_COLOR_STATE_UPDATE
name|GIMP_UPDATE_COLOR_STATE_UPDATE
DECL|typedef|GimpUpdateColorState
block|}
name|GimpUpdateColorState
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PALETTE_EDITOR
define|#
directive|define
name|GIMP_TYPE_PALETTE_EDITOR
value|(gimp_palette_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_PALETTE_EDITOR (obj)
define|#
directive|define
name|GIMP_PALETTE_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PALETTE_EDITOR, GimpPaletteEditor))
end_define

begin_define
DECL|macro|GIMP_PALETTE_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_PALETTE_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PALETTE_EDITOR, GimpPaletteEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_PALETTE_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_PALETTE_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PALETTE_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_PALETTE_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PALETTE_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PALETTE_EDITOR))
end_define

begin_define
DECL|macro|GIMP_PALETTE_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PALETTE_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PALETTE_EDITOR, GimpPaletteEditorClass))
end_define

begin_typedef
DECL|typedef|GimpPaletteEditorClass
typedef|typedef
name|struct
name|_GimpPaletteEditorClass
name|GimpPaletteEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPaletteEditor
struct|struct
name|_GimpPaletteEditor
block|{
DECL|member|parent_instance
name|GimpDataEditor
name|parent_instance
decl_stmt|;
DECL|member|color_area
name|GtkWidget
modifier|*
name|color_area
decl_stmt|;
DECL|member|scrolled_window
name|GtkWidget
modifier|*
name|scrolled_window
decl_stmt|;
DECL|member|color_name
name|GtkWidget
modifier|*
name|color_name
decl_stmt|;
DECL|member|popup_menu
name|GtkWidget
modifier|*
name|popup_menu
decl_stmt|;
DECL|member|delete_menu_item
name|GtkWidget
modifier|*
name|delete_menu_item
decl_stmt|;
DECL|member|edit_menu_item
name|GtkWidget
modifier|*
name|edit_menu_item
decl_stmt|;
DECL|member|color_notebook
name|ColorNotebook
modifier|*
name|color_notebook
decl_stmt|;
DECL|member|color_notebook_active
name|gboolean
name|color_notebook_active
decl_stmt|;
DECL|member|color
name|GimpPaletteEntry
modifier|*
name|color
decl_stmt|;
DECL|member|dnd_color
name|GimpPaletteEntry
modifier|*
name|dnd_color
decl_stmt|;
DECL|member|entry_sig_id
name|guint
name|entry_sig_id
decl_stmt|;
DECL|member|zoom_factor
name|gfloat
name|zoom_factor
decl_stmt|;
comment|/* range from 0.1 to 4.0 */
DECL|member|col_width
name|gint
name|col_width
decl_stmt|;
DECL|member|last_width
name|gint
name|last_width
decl_stmt|;
DECL|member|columns
name|gint
name|columns
decl_stmt|;
DECL|member|freeze_update
name|gboolean
name|freeze_update
decl_stmt|;
DECL|member|columns_valid
name|gboolean
name|columns_valid
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPaletteEditorClass
struct|struct
name|_GimpPaletteEditorClass
block|{
DECL|member|parent_class
name|GimpDataEditorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GimpDataEditor
modifier|*
name|gimp_palette_editor_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_palette_editor_update_color
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpUpdateColorState
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PALETTE_EDITOR_H__ */
end_comment

end_unit

