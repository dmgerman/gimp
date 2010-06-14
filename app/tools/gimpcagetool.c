begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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
file|"core/gimp-transform-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpcagetool.h"
end_include

begin_include
include|#
directive|include
file|"gimptransformoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCageTool,gimp_cage_tool,GIMP_TYPE_TRANSFORM_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCageTool
argument_list|,
argument|gimp_cage_tool
argument_list|,
argument|GIMP_TYPE_TRANSFORM_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_cage_tool_parent_class
end_define

begin_function
name|void
name|gimp_cage_tool_register
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
name|GIMP_TYPE_CAGE_TOOL
argument_list|,
name|GIMP_TYPE_TRANSFORM_OPTIONS
argument_list|,
name|gimp_transform_options_gui
argument_list|,
name|GIMP_CONTEXT_BACKGROUND_MASK
argument_list|,
literal|"gimp-cage-tool"
argument_list|,
name|_
argument_list|(
literal|"Rotate"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Rotate Tool: Rotate the layer, selection or path"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Rotate"
argument_list|)
argument_list|,
literal|"<shift>R"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_ROTATE
argument_list|,
name|GIMP_STOCK_TOOL_ROTATE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_class_init (GimpCageToolClass * klass)
name|gimp_cage_tool_class_init
parameter_list|(
name|GimpCageToolClass
modifier|*
name|klass
parameter_list|)
block|{  }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_init (GimpCageTool * self)
name|gimp_cage_tool_init
parameter_list|(
name|GimpCageTool
modifier|*
name|self
parameter_list|)
block|{  }
end_function

end_unit

