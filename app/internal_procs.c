begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2000 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/* Forward declarations for registering PDB procs */
end_comment

begin_function_decl
name|void
name|register_brush_select_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_brushes_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_channel_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_channel_ops_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_color_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_convert_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_display_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_drawable_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_edit_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_fileops_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_floating_sel_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_gimprc_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_gradient_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_gradient_select_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_guides_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_help_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_image_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_layer_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_message_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_misc_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_palette_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_parasite_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_paths_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_pattern_select_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_patterns_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_plug_in_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_procedural_db_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_selection_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_text_tool_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_tools_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_undo_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_unit_procs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* 322 procedures registered total */
end_comment

begin_function
name|void
DECL|function|internal_procs_init (void)
name|internal_procs_init
parameter_list|(
name|void
parameter_list|)
block|{
name|app_init_update_status
argument_list|(
name|_
argument_list|(
literal|"Internal Procedures"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Brush UI"
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|register_brush_select_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Brushes"
argument_list|)
argument_list|,
literal|0.009
argument_list|)
expr_stmt|;
name|register_brushes_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Channel"
argument_list|)
argument_list|,
literal|0.043
argument_list|)
expr_stmt|;
name|register_channel_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Channel Ops"
argument_list|)
argument_list|,
literal|0.09
argument_list|)
expr_stmt|;
name|register_channel_ops_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Color"
argument_list|)
argument_list|,
literal|0.096
argument_list|)
expr_stmt|;
name|register_color_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Convert"
argument_list|)
argument_list|,
literal|0.134
argument_list|)
expr_stmt|;
name|register_convert_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"GDisplay procedures"
argument_list|)
argument_list|,
literal|0.143
argument_list|)
expr_stmt|;
name|register_display_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Drawable procedures"
argument_list|)
argument_list|,
literal|0.152
argument_list|)
expr_stmt|;
name|register_drawable_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Edit procedures"
argument_list|)
argument_list|,
literal|0.22
argument_list|)
expr_stmt|;
name|register_edit_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"File Operations"
argument_list|)
argument_list|,
literal|0.239
argument_list|)
expr_stmt|;
name|register_fileops_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Floating selections"
argument_list|)
argument_list|,
literal|0.264
argument_list|)
expr_stmt|;
name|register_floating_sel_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Gimprc procedures"
argument_list|)
argument_list|,
literal|0.283
argument_list|)
expr_stmt|;
name|register_gimprc_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Gradients"
argument_list|)
argument_list|,
literal|0.292
argument_list|)
expr_stmt|;
name|register_gradient_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Gradient UI"
argument_list|)
argument_list|,
literal|0.307
argument_list|)
expr_stmt|;
name|register_gradient_select_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Guide procedures"
argument_list|)
argument_list|,
literal|0.32
argument_list|)
expr_stmt|;
name|register_guides_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Help procedures"
argument_list|)
argument_list|,
literal|0.339
argument_list|)
expr_stmt|;
name|register_help_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Image"
argument_list|)
argument_list|,
literal|0.342
argument_list|)
expr_stmt|;
name|register_image_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Layer"
argument_list|)
argument_list|,
literal|0.525
argument_list|)
expr_stmt|;
name|register_layer_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Interface"
argument_list|)
argument_list|,
literal|0.621
argument_list|)
expr_stmt|;
name|register_message_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Miscellaneous"
argument_list|)
argument_list|,
literal|0.63
argument_list|)
expr_stmt|;
name|register_misc_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Palette"
argument_list|)
argument_list|,
literal|0.637
argument_list|)
expr_stmt|;
name|register_palette_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Parasite procedures"
argument_list|)
argument_list|,
literal|0.658
argument_list|)
expr_stmt|;
name|register_parasite_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Paths"
argument_list|)
argument_list|,
literal|0.696
argument_list|)
expr_stmt|;
name|register_paths_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Pattern UI"
argument_list|)
argument_list|,
literal|0.736
argument_list|)
expr_stmt|;
name|register_pattern_select_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Patterns"
argument_list|)
argument_list|,
literal|0.745
argument_list|)
expr_stmt|;
name|register_patterns_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Plug-in"
argument_list|)
argument_list|,
literal|0.758
argument_list|)
expr_stmt|;
name|register_plug_in_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Procedural database"
argument_list|)
argument_list|,
literal|0.776
argument_list|)
expr_stmt|;
name|register_procedural_db_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Image mask"
argument_list|)
argument_list|,
literal|0.801
argument_list|)
expr_stmt|;
name|register_selection_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Text procedures"
argument_list|)
argument_list|,
literal|0.854
argument_list|)
expr_stmt|;
name|register_text_tool_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Tool procedures"
argument_list|)
argument_list|,
literal|0.866
argument_list|)
expr_stmt|;
name|register_tools_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Undo"
argument_list|)
argument_list|,
literal|0.96
argument_list|)
expr_stmt|;
name|register_undo_procs
argument_list|()
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Units"
argument_list|)
argument_list|,
literal|0.966
argument_list|)
expr_stmt|;
name|register_unit_procs
argument_list|()
expr_stmt|;
block|}
end_function

end_unit

