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
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppenciloptions.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimppenciltool.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_macro
DECL|function|G_DEFINE_TYPE (GimpPencilTool,gimp_pencil_tool,GIMP_TYPE_PAINTBRUSH_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPencilTool
argument_list|,
argument|gimp_pencil_tool
argument_list|,
argument|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|)
end_macro

begin_function
name|void
name|gimp_pencil_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_PENCIL_TOOL
argument_list|,
name|GIMP_TYPE_PENCIL_OPTIONS
argument_list|,
name|gimp_paint_options_gui
argument_list|,
name|GIMP_PAINT_OPTIONS_CONTEXT_MASK
operator||
name|GIMP_CONTEXT_GRADIENT_MASK
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
literal|"Pe_ncil"
argument_list|)
argument_list|,
literal|"N"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_PENCIL
argument_list|,
name|GIMP_STOCK_TOOL_PENCIL
argument_list|,
name|data
argument_list|)
expr_stmt|;
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
block|{ }
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
init|=
name|GIMP_TOOL
argument_list|(
name|pencil
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_PENCIL
argument_list|)
expr_stmt|;
name|gimp_paint_tool_enable_color_picker
argument_list|(
name|GIMP_PAINT_TOOL
argument_list|(
name|pencil
argument_list|)
argument_list|,
name|GIMP_COLOR_PICK_MODE_FOREGROUND
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

