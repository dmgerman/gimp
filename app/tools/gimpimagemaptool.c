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
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagemaptool.h"
end_include

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_class_init
parameter_list|(
name|GimpImageMapToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_init
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  functions  */
end_comment

begin_function
name|GtkType
DECL|function|gimp_image_map_tool_get_type (void)
name|gimp_image_map_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
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
name|GtkTypeInfo
name|tool_info
init|=
block|{
literal|"GimpImageMapTool"
block|,
sizeof|sizeof
argument_list|(
name|GimpImageMapTool
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpImageMapToolClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_image_map_tool_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_image_map_tool_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_TOOL
argument_list|,
operator|&
name|tool_info
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
DECL|function|gimp_image_map_tool_class_init (GimpImageMapToolClass * klass)
name|gimp_image_map_tool_class_init
parameter_list|(
name|GimpImageMapToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|tool_class
operator|=
operator|(
name|GimpToolClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_TOOL
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_image_map_tool_destroy
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_init (GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_init
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
name|TRUE
expr_stmt|;
comment|/*  Disallow scrolling  */
name|tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
comment|/*  Don't preserve on drawable change  */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_destroy (GtkObject * object)
name|gimp_image_map_tool_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

