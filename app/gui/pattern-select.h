begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PATTERN_SELECT_H__
end_ifndef

begin_define
DECL|macro|__PATTERN_SELECT_H__
define|#
directive|define
name|__PATTERN_SELECT_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"patterns.h"
end_include

begin_typedef
DECL|typedef|PatternSelect
typedef|typedef
name|struct
name|_PatternSelect
name|PatternSelect
typedef|;
end_typedef

begin_struct
DECL|struct|_PatternSelect
struct|struct
name|_PatternSelect
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
comment|/*  The preview and it's vscale data  */
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|gc
name|GdkGC
modifier|*
name|gc
decl_stmt|;
DECL|member|sbar_data
name|GtkAdjustment
modifier|*
name|sbar_data
decl_stmt|;
DECL|member|options_box
name|GtkWidget
modifier|*
name|options_box
decl_stmt|;
DECL|member|pattern_name
name|GtkWidget
modifier|*
name|pattern_name
decl_stmt|;
DECL|member|pattern_size
name|GtkWidget
modifier|*
name|pattern_size
decl_stmt|;
comment|/*  Pattern popup  */
DECL|member|pattern_popup
name|GtkWidget
modifier|*
name|pattern_popup
decl_stmt|;
DECL|member|pattern_preview
name|GtkWidget
modifier|*
name|pattern_preview
decl_stmt|;
DECL|member|popup_timeout_tag
name|guint
name|popup_timeout_tag
decl_stmt|;
comment|/*  Callback function name  */
DECL|member|callback_name
name|gchar
modifier|*
name|callback_name
decl_stmt|;
comment|/*  Context to store the current pattern  */
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|dnd_pattern
name|GPattern
modifier|*
name|dnd_pattern
decl_stmt|;
comment|/*  Some variables to keep the GUI consistent  */
DECL|member|cell_width
name|gint
name|cell_width
decl_stmt|;
DECL|member|cell_height
name|gint
name|cell_height
decl_stmt|;
DECL|member|scroll_offset
name|gint
name|scroll_offset
decl_stmt|;
DECL|member|old_row
name|gint
name|old_row
decl_stmt|;
DECL|member|old_col
name|gint
name|old_col
decl_stmt|;
DECL|member|NUM_PATTERN_COLUMNS
name|gint
name|NUM_PATTERN_COLUMNS
decl_stmt|;
DECL|member|NUM_PATTERN_ROWS
name|gint
name|NUM_PATTERN_ROWS
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  list of active dialogs  */
end_comment

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|pattern_active_dialogs
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  the main pattern dialog  */
end_comment

begin_decl_stmt
specifier|extern
name|PatternSelect
modifier|*
name|pattern_select_dialog
decl_stmt|;
end_decl_stmt

begin_function_decl
name|PatternSelect
modifier|*
name|pattern_select_new
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|gchar
modifier|*
name|initial_pattern
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pattern_select_free
parameter_list|(
name|PatternSelect
modifier|*
name|psp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|patterns_check_dialogs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  the main pattern selection  */
end_comment

begin_function_decl
name|void
name|pattern_dialog_create
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pattern_dialog_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PATTERN_SELECT_H__  */
end_comment

end_unit

