begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"tool.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"airbrush.h"
end_include

begin_include
include|#
directive|include
file|"blend.h"
end_include

begin_include
include|#
directive|include
file|"bucket_fill.h"
end_include

begin_include
include|#
directive|include
file|"by_color_select.h"
end_include

begin_include
include|#
directive|include
file|"clone.h"
end_include

begin_include
include|#
directive|include
file|"color_picker.h"
end_include

begin_include
include|#
directive|include
file|"convolve.h"
end_include

begin_include
include|#
directive|include
file|"crop.h"
end_include

begin_include
include|#
directive|include
file|"dodgeburn.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"ellipse_select.h"
end_include

begin_include
include|#
directive|include
file|"eraser.h"
end_include

begin_include
include|#
directive|include
file|"flip_tool.h"
end_include

begin_include
include|#
directive|include
file|"free_select.h"
end_include

begin_include
include|#
directive|include
file|"fuzzy_select.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"measure.h"
end_include

begin_include
include|#
directive|include
file|"move.h"
end_include

begin_include
include|#
directive|include
file|"paintbrush.h"
end_include

begin_include
include|#
directive|include
file|"pencil.h"
end_include

begin_include
include|#
directive|include
file|"perspective_tool.h"
end_include

begin_include
include|#
directive|include
file|"rect_select.h"
end_include

begin_include
include|#
directive|include
file|"rotate_tool.h"
end_include

begin_include
include|#
directive|include
file|"scale_tool.h"
end_include

begin_include
include|#
directive|include
file|"shear_tool.h"
end_include

begin_include
include|#
directive|include
file|"smudge.h"
end_include

begin_function
name|void
DECL|function|register_tools (void)
name|register_tools
parameter_list|(
name|void
parameter_list|)
block|{
name|gimp_color_picker_register
argument_list|()
expr_stmt|;
name|gimp_measure_tool_register
argument_list|()
expr_stmt|;
name|gimp_move_tool_register
argument_list|()
expr_stmt|;
comment|/*   procedural_db_register (&airbrush_proc);   procedural_db_register (&airbrush_default_proc);   procedural_db_register (&blend_proc);   procedural_db_register (&bucket_fill_proc);   procedural_db_register (&by_color_select_proc);   procedural_db_register (&clone_proc);   procedural_db_register (&clone_default_proc);   procedural_db_register (&color_picker_proc);   procedural_db_register (&convolve_proc);   procedural_db_register (&convolve_default_proc);   procedural_db_register (&crop_proc);   procedural_db_register (&dodgeburn_proc);   procedural_db_register (&dodgeburn_default_proc);   procedural_db_register (&ellipse_select_proc);   procedural_db_register (&eraser_proc);   procedural_db_register (&eraser_default_proc);   procedural_db_register (&flip_proc);   procedural_db_register (&free_select_proc);   procedural_db_register (&fuzzy_select_proc);   procedural_db_register (&paintbrush_proc);   procedural_db_register (&paintbrush_default_proc);   procedural_db_register (&pencil_proc);   procedural_db_register (&perspective_proc);   procedural_db_register (&rect_select_proc);   procedural_db_register (&rotate_proc);   procedural_db_register (&scale_proc);   procedural_db_register (&shear_proc);   procedural_db_register (&smudge_proc);   procedural_db_register (&smudge_default_proc);   procedural_db_register (&transform_2d_proc); */
block|}
end_function

end_unit

