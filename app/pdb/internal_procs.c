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
file|"core/gimp.h"
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
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_brushes_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_channel_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_color_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_convert_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_display_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_drawable_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_edit_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_fileops_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_floating_sel_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_gimprc_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_gradient_select_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_gradients_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_guides_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_help_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_image_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_layer_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_message_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_misc_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_misc_tools_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_paint_tools_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_palette_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_palette_select_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_palettes_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_parasite_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_paths_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_pattern_select_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_patterns_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_plug_in_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_procedural_db_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_selection_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_selection_tools_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_text_tool_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_transform_tools_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_undo_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|register_unit_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* 338 procedures registered total */
end_comment

begin_function
name|void
DECL|function|internal_procs_init (Gimp * gimp,GimpInitStatusFunc status_callback)
name|internal_procs_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|status_callback
operator|!=
name|NULL
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
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
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
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
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Channel"
argument_list|)
argument_list|,
literal|0.041
argument_list|)
expr_stmt|;
name|register_channel_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Color"
argument_list|)
argument_list|,
literal|0.089
argument_list|)
expr_stmt|;
name|register_color_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Convert"
argument_list|)
argument_list|,
literal|0.124
argument_list|)
expr_stmt|;
name|register_convert_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Display procedures"
argument_list|)
argument_list|,
literal|0.133
argument_list|)
expr_stmt|;
name|register_display_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Drawable procedures"
argument_list|)
argument_list|,
literal|0.145
argument_list|)
expr_stmt|;
name|register_drawable_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Edit procedures"
argument_list|)
argument_list|,
literal|0.213
argument_list|)
expr_stmt|;
name|register_edit_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"File Operations"
argument_list|)
argument_list|,
literal|0.231
argument_list|)
expr_stmt|;
name|register_fileops_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Floating selections"
argument_list|)
argument_list|,
literal|0.254
argument_list|)
expr_stmt|;
name|register_floating_sel_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Gimprc procedures"
argument_list|)
argument_list|,
literal|0.272
argument_list|)
expr_stmt|;
name|register_gimprc_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Gradient UI"
argument_list|)
argument_list|,
literal|0.284
argument_list|)
expr_stmt|;
name|register_gradient_select_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Gradients"
argument_list|)
argument_list|,
literal|0.293
argument_list|)
expr_stmt|;
name|register_gradients_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Guide procedures"
argument_list|)
argument_list|,
literal|0.314
argument_list|)
expr_stmt|;
name|register_guides_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Help procedures"
argument_list|)
argument_list|,
literal|0.331
argument_list|)
expr_stmt|;
name|register_help_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Image"
argument_list|)
argument_list|,
literal|0.334
argument_list|)
expr_stmt|;
name|register_image_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Layer"
argument_list|)
argument_list|,
literal|0.518
argument_list|)
expr_stmt|;
name|register_layer_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Message procedures"
argument_list|)
argument_list|,
literal|0.612
argument_list|)
expr_stmt|;
name|register_message_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Miscellaneous"
argument_list|)
argument_list|,
literal|0.621
argument_list|)
expr_stmt|;
name|register_misc_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Misc Tool procedures"
argument_list|)
argument_list|,
literal|0.627
argument_list|)
expr_stmt|;
name|register_misc_tools_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Paint Tool procedures"
argument_list|)
argument_list|,
literal|0.636
argument_list|)
expr_stmt|;
name|register_paint_tools_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Palette"
argument_list|)
argument_list|,
literal|0.68
argument_list|)
expr_stmt|;
name|register_palette_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Palette UI"
argument_list|)
argument_list|,
literal|0.698
argument_list|)
expr_stmt|;
name|register_palette_select_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Palettes"
argument_list|)
argument_list|,
literal|0.707
argument_list|)
expr_stmt|;
name|register_palettes_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Parasite procedures"
argument_list|)
argument_list|,
literal|0.722
argument_list|)
expr_stmt|;
name|register_parasite_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Paths"
argument_list|)
argument_list|,
literal|0.757
argument_list|)
expr_stmt|;
name|register_paths_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Pattern UI"
argument_list|)
argument_list|,
literal|0.796
argument_list|)
expr_stmt|;
name|register_pattern_select_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Patterns"
argument_list|)
argument_list|,
literal|0.805
argument_list|)
expr_stmt|;
name|register_patterns_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Plug-in"
argument_list|)
argument_list|,
literal|0.82
argument_list|)
expr_stmt|;
name|register_plug_in_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Procedural database"
argument_list|)
argument_list|,
literal|0.837
argument_list|)
expr_stmt|;
name|register_procedural_db_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Image mask"
argument_list|)
argument_list|,
literal|0.861
argument_list|)
expr_stmt|;
name|register_selection_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Selection Tool procedures"
argument_list|)
argument_list|,
literal|0.914
argument_list|)
expr_stmt|;
name|register_selection_tools_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Text procedures"
argument_list|)
argument_list|,
literal|0.929
argument_list|)
expr_stmt|;
name|register_text_tool_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Transform Tool procedures"
argument_list|)
argument_list|,
literal|0.941
argument_list|)
expr_stmt|;
name|register_transform_tools_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Undo"
argument_list|)
argument_list|,
literal|0.959
argument_list|)
expr_stmt|;
name|register_undo_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Units"
argument_list|)
argument_list|,
literal|0.964
argument_list|)
expr_stmt|;
name|register_unit_procs
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

