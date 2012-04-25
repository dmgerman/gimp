begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl. */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"internal-procs.h"
end_include

begin_comment
comment|/* 673 procedures registered total */
end_comment

begin_function
name|void
DECL|function|internal_procs_init (GimpPDB * pdb)
name|internal_procs_init
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
argument_list|)
argument_list|)
expr_stmt|;
name|register_brush_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_brush_select_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_brushes_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_buffer_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_channel_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_color_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_context_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_convert_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_display_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_drawable_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_drawable_transform_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_dynamics_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_edit_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_fileops_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_floating_sel_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_font_select_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_fonts_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_gimp_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_gimprc_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_gradient_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_gradient_select_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_gradients_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_grid_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_guides_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_help_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_image_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_image_select_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_item_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_item_transform_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_layer_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_message_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_paint_tools_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_palette_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_palette_select_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_palettes_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_paths_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_pattern_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_pattern_select_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_patterns_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_plug_in_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_plug_in_compat_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_procedural_db_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_progress_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_selection_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_selection_tools_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_text_layer_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_text_tool_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_transform_tools_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_undo_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_unit_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
name|register_vectors_procs
argument_list|(
name|pdb
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

