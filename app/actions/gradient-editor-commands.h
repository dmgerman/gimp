begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GRADIENT_EDITOR_COMMANDS_H__
end_ifndef

begin_define
DECL|macro|__GRADIENT_EDITOR_COMMANDS_H__
define|#
directive|define
name|__GRADIENT_EDITOR_COMMANDS_H__
end_define

begin_enum
enum|enum
DECL|enum|__anon2ad890aa0103
block|{
DECL|enumerator|GRADIENT_EDITOR_COLOR_NEIGHBOR_ENDPOINT
name|GRADIENT_EDITOR_COLOR_NEIGHBOR_ENDPOINT
block|,
DECL|enumerator|GRADIENT_EDITOR_COLOR_OTHER_ENDPOINT
name|GRADIENT_EDITOR_COLOR_OTHER_ENDPOINT
block|,
DECL|enumerator|GRADIENT_EDITOR_COLOR_FOREGROUND
name|GRADIENT_EDITOR_COLOR_FOREGROUND
block|,
DECL|enumerator|GRADIENT_EDITOR_COLOR_BACKGROUND
name|GRADIENT_EDITOR_COLOR_BACKGROUND
block|,
DECL|enumerator|GRADIENT_EDITOR_COLOR_FIRST_CUSTOM
name|GRADIENT_EDITOR_COLOR_FIRST_CUSTOM
block|}
enum|;
end_enum

begin_function_decl
name|void
name|gradient_editor_left_color_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_left_color_type_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GtkAction
modifier|*
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_load_left_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_save_left_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_right_color_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_right_color_type_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GtkAction
modifier|*
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_load_right_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_save_right_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_blending_func_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GtkAction
modifier|*
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_coloring_type_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GtkAction
modifier|*
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_flip_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_replicate_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_split_midpoint_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_split_uniformly_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_delete_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_recenter_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_redistribute_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_blend_color_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_blend_opacity_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_zoom_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GRADIENT_EDITOR_COMMANDS_H__ */
end_comment

end_unit

