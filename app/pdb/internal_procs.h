begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__INTERNAL_PROCS_H__
end_ifndef

begin_define
DECL|macro|__INTERNAL_PROCS_H__
define|#
directive|define
name|__INTERNAL_PROCS_H__
end_define

begin_function_decl
name|void
name|internal_procs_init
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Forward declarations for registering PDB procs */
end_comment

begin_function_decl
name|void
name|register_brush_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_brush_select_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_brushes_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_buffer_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_channel_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_color_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_context_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_convert_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_display_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_drawable_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_drawable_transform_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_edit_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_fileops_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_floating_sel_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_font_select_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_fonts_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_gimprc_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_gradient_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_gradient_select_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_gradients_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_grid_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_guides_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_help_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_image_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_layer_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_message_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_misc_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_paint_tools_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_palette_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_palette_select_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_palettes_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_parasite_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_paths_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_pattern_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_pattern_select_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_patterns_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_plug_in_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_procedural_db_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_progress_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_selection_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_selection_tools_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_text_tool_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_transform_tools_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_undo_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_unit_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_vectors_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __INTERNAL_PROCS_H__ */
end_comment

end_unit

