begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BRUSH_SELECT_H__
end_ifndef

begin_define
DECL|macro|__BRUSH_SELECT_H__
define|#
directive|define
name|__BRUSH_SELECT_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_typedef
DECL|typedef|_BrushSelect
DECL|typedef|BrushSelectP
typedef|typedef
name|struct
name|_BrushSelect
name|_BrushSelect
typedef|,
modifier|*
name|BrushSelectP
typedef|;
end_typedef

begin_struct
DECL|struct|_BrushSelect
struct|struct
name|_BrushSelect
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
comment|/* Place holders which enable global<->per-tool paint options switching */
DECL|member|left_box
name|GtkWidget
modifier|*
name|left_box
decl_stmt|;
DECL|member|right_box
name|GtkWidget
modifier|*
name|right_box
decl_stmt|;
DECL|member|brush_selection_box
name|GtkWidget
modifier|*
name|brush_selection_box
decl_stmt|;
DECL|member|paint_options_box
name|GtkWidget
modifier|*
name|paint_options_box
decl_stmt|;
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|brush_name
name|GtkWidget
modifier|*
name|brush_name
decl_stmt|;
DECL|member|brush_size
name|GtkWidget
modifier|*
name|brush_size
decl_stmt|;
DECL|member|options_box
name|GtkWidget
modifier|*
name|options_box
decl_stmt|;
DECL|member|opacity_data
name|GtkAdjustment
modifier|*
name|opacity_data
decl_stmt|;
DECL|member|spacing_data
name|GtkAdjustment
modifier|*
name|spacing_data
decl_stmt|;
DECL|member|sbar_data
name|GtkAdjustment
modifier|*
name|sbar_data
decl_stmt|;
DECL|member|edit_button
name|GtkWidget
modifier|*
name|edit_button
decl_stmt|;
DECL|member|option_menu
name|GtkWidget
modifier|*
name|option_menu
decl_stmt|;
comment|/* Brush preview */
DECL|member|brush_popup
name|GtkWidget
modifier|*
name|brush_popup
decl_stmt|;
DECL|member|brush_preview
name|GtkWidget
modifier|*
name|brush_preview
decl_stmt|;
comment|/* Call back function name */
DECL|member|callback_name
name|gchar
modifier|*
name|callback_name
decl_stmt|;
comment|/* Current brush */
DECL|member|brush
name|GimpBrushP
name|brush
decl_stmt|;
DECL|member|spacing_value
name|gint
name|spacing_value
decl_stmt|;
comment|/* Current paint options */
DECL|member|opacity_value
name|gdouble
name|opacity_value
decl_stmt|;
DECL|member|paint_mode
name|gint
name|paint_mode
decl_stmt|;
comment|/* Some variables to keep the GUI consistent */
DECL|member|width
DECL|member|height
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
DECL|member|cell_width
DECL|member|cell_height
name|int
name|cell_width
decl_stmt|,
name|cell_height
decl_stmt|;
DECL|member|scroll_offset
name|int
name|scroll_offset
decl_stmt|;
DECL|member|redraw
name|int
name|redraw
decl_stmt|;
DECL|member|old_row
name|int
name|old_row
decl_stmt|;
DECL|member|old_col
name|int
name|old_col
decl_stmt|;
DECL|member|NUM_BRUSH_COLUMNS
name|gint
name|NUM_BRUSH_COLUMNS
decl_stmt|;
DECL|member|NUM_BRUSH_ROWS
name|gint
name|NUM_BRUSH_ROWS
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|BrushSelectP
name|brush_select_new
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
comment|/*  These are the required initial vals 				 *  If init_name == NULL then use current brush 				 */
name|gchar
modifier|*
name|init_name
parameter_list|,
name|gdouble
name|init_opacity
parameter_list|,
name|gint
name|init_spacing
parameter_list|,
name|gint
name|init_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|brush_select_free
parameter_list|(
name|BrushSelectP
name|bsp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|brush_select_select
parameter_list|(
name|BrushSelectP
name|bsp
parameter_list|,
name|int
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|brush_change_callbacks
parameter_list|(
name|BrushSelectP
name|bsp
parameter_list|,
name|gint
name|closing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|brushes_check_dialogs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  show/hide paint options (main brush dialog if bsp == NULL)  */
end_comment

begin_function_decl
name|void
name|brush_select_show_paint_options
parameter_list|(
name|BrushSelectP
name|bsp
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* PDB entry */
end_comment

begin_decl_stmt
specifier|extern
name|ProcRecord
name|brushes_popup_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|brushes_close_popup_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|brushes_set_popup_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|brushes_get_brush_data_proc
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __BRUSH_SELECT_H__  */
end_comment

end_unit

