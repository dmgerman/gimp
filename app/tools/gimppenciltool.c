begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"libgimptool/gimptooltypes.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppencil.h"
end_include

begin_include
include|#
directive|include
file|"gimppenciltool.h"
end_include

begin_include
include|#
directive|include
file|"paint_options.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_pencil_tool_class_init
parameter_list|(
name|GimpPencilToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pencil_tool_init
parameter_list|(
name|GimpPencilTool
modifier|*
name|pancil
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpPaintToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  functions  */
end_comment

begin_function
name|void
DECL|function|gimp_pencil_tool_register (GimpToolRegisterCallback callback,Gimp * gimp)
name|gimp_pencil_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_PENCIL_TOOL
argument_list|,
name|paint_options_new
argument_list|,
name|TRUE
argument_list|,
literal|"gimp-pencil-tool"
argument_list|,
name|_
argument_list|(
literal|"Pencil"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Paint hard edged pixels"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Paint Tools/Pencil"
argument_list|)
argument_list|,
literal|"P"
argument_list|,
name|NULL
argument_list|,
literal|"tools/pencil.html"
argument_list|,
name|GIMP_STOCK_TOOL_PENCIL
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_pencil_tool_get_type (void)
name|gimp_pencil_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tool_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpPencilToolClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_pencil_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpPencilTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_pencil_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PAINT_TOOL
argument_list|,
literal|"GimpPencilTool"
argument_list|,
operator|&
name|tool_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pencil_tool_class_init (GimpPencilToolClass * klass)
name|gimp_pencil_tool_class_init
parameter_list|(
name|GimpPencilToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPaintToolClass
modifier|*
name|paint_tool_class
decl_stmt|;
name|paint_tool_class
operator|=
name|GIMP_PAINT_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pencil_tool_init (GimpPencilTool * pencil)
name|gimp_pencil_tool_init
parameter_list|(
name|GimpPencilTool
modifier|*
name|pencil
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpPaintTool
modifier|*
name|paint_tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|pencil
argument_list|)
expr_stmt|;
name|paint_tool
operator|=
name|GIMP_PAINT_TOOL
argument_list|(
name|pencil
argument_list|)
expr_stmt|;
name|tool
operator|->
name|control
operator|=
name|gimp_tool_control_new
argument_list|(
name|FALSE
argument_list|,
comment|/* scroll_lock */
name|TRUE
argument_list|,
comment|/* auto_snap_to */
name|TRUE
argument_list|,
comment|/* preserve */
name|FALSE
argument_list|,
comment|/* handle_empty_image */
name|GIMP_MOTION_MODE_EXACT
argument_list|,
comment|/* motion_mode */
name|GIMP_MOUSE_CURSOR
argument_list|,
comment|/* cursor */
name|GIMP_PENCIL_TOOL_CURSOR
argument_list|,
comment|/* tool_cursor */
name|GIMP_CURSOR_MODIFIER_NONE
argument_list|,
comment|/* cursor_modifier */
name|GIMP_MOUSE_CURSOR
argument_list|,
comment|/* toggle_cursor */
name|GIMP_TOOL_CURSOR_NONE
argument_list|,
comment|/* toggle_tool_cursor */
name|GIMP_CURSOR_MODIFIER_NONE
comment|/* toggle_cursor_modifier */
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|pick_colors
operator|=
name|TRUE
expr_stmt|;
name|paint_tool
operator|->
name|core
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PENCIL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

