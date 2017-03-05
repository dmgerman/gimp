begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"paint/gimpclone.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimpcloneoptions.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpclonetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpcloneoptions-gui.h"
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
DECL|function|G_DEFINE_TYPE (GimpCloneTool,gimp_clone_tool,GIMP_TYPE_SOURCE_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCloneTool
argument_list|,
argument|gimp_clone_tool
argument_list|,
argument|GIMP_TYPE_SOURCE_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_clone_tool_parent_class
end_define

begin_function
name|void
name|gimp_clone_tool_register
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
name|GIMP_TYPE_CLONE_TOOL
argument_list|,
name|GIMP_TYPE_CLONE_OPTIONS
argument_list|,
name|gimp_clone_options_gui
argument_list|,
name|GIMP_PAINT_OPTIONS_CONTEXT_MASK
operator||
name|GIMP_CONTEXT_PROP_MASK_PATTERN
argument_list|,
literal|"gimp-clone-tool"
argument_list|,
name|_
argument_list|(
literal|"Clone"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Clone Tool: Selectively copy from an image or pattern, using a brush"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Clone"
argument_list|)
argument_list|,
literal|"C"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_CLONE
argument_list|,
name|GIMP_ICON_TOOL_CLONE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_tool_class_init (GimpCloneToolClass * klass)
name|gimp_clone_tool_class_init
parameter_list|(
name|GimpCloneToolClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_tool_init (GimpCloneTool * clone)
name|gimp_clone_tool_init
parameter_list|(
name|GimpCloneTool
modifier|*
name|clone
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|clone
argument_list|)
decl_stmt|;
name|GimpPaintTool
modifier|*
name|paint_tool
init|=
name|GIMP_PAINT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpSourceTool
modifier|*
name|source_tool
init|=
name|GIMP_SOURCE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_CLONE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_action_object_2
argument_list|(
name|tool
operator|->
name|control
argument_list|,
literal|"context/context-pattern-select-set"
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|status
operator|=
name|_
argument_list|(
literal|"Click to clone"
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|status_ctrl
operator|=
name|_
argument_list|(
literal|"%s to set a new clone source"
argument_list|)
expr_stmt|;
name|source_tool
operator|->
name|status_paint
operator|=
name|_
argument_list|(
literal|"Click to clone"
argument_list|)
expr_stmt|;
comment|/* Translators: the translation of "Click" must be the first word */
name|source_tool
operator|->
name|status_set_source
operator|=
name|_
argument_list|(
literal|"Click to set a new clone source"
argument_list|)
expr_stmt|;
name|source_tool
operator|->
name|status_set_source_ctrl
operator|=
name|_
argument_list|(
literal|"%s to set a new clone source"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

