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
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"gimptransformtool.h"
end_include

begin_include
include|#
directive|include
file|"gimptransformtoolundo.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29c743330103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TRANSFORM_TOOL
name|PROP_TRANSFORM_TOOL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_transform_tool_undo_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_transform_tool_undo_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_transform_tool_undo_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_transform_tool_undo_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_transform_tool_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpTransformToolUndo,gimp_transform_tool_undo,GIMP_TYPE_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTransformToolUndo
argument_list|,
argument|gimp_transform_tool_undo
argument_list|,
argument|GIMP_TYPE_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_transform_tool_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_transform_tool_undo_class_init
parameter_list|(
name|GimpTransformToolUndoClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpUndoClass
modifier|*
name|undo_class
init|=
name|GIMP_UNDO_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_transform_tool_undo_constructed
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_transform_tool_undo_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_transform_tool_undo_get_property
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_transform_tool_undo_pop
expr_stmt|;
name|undo_class
operator|->
name|free
operator|=
name|gimp_transform_tool_undo_free
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_TRANSFORM_TOOL
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"transform-tool"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TRANSFORM_TOOL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_transform_tool_undo_init (GimpTransformToolUndo * undo)
name|gimp_transform_tool_undo_init
parameter_list|(
name|GimpTransformToolUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_transform_tool_undo_constructed (GObject * object)
name|gimp_transform_tool_undo_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTransformToolUndo
modifier|*
name|transform_tool_undo
init|=
name|GIMP_TRANSFORM_TOOL_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpTransformTool
modifier|*
name|transform_tool
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
condition|)
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_TRANSFORM_TOOL
argument_list|(
name|transform_tool_undo
operator|->
name|transform_tool
argument_list|)
argument_list|)
expr_stmt|;
name|transform_tool
operator|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|transform_tool_undo
operator|->
name|transform_tool
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|TRANS_INFO_SIZE
condition|;
name|i
operator|++
control|)
name|transform_tool_undo
operator|->
name|trans_info
index|[
name|i
index|]
operator|=
name|transform_tool
operator|->
name|old_trans_info
index|[
name|i
index|]
expr_stmt|;
if|#
directive|if
literal|0
block|if (transform_tool->original)     transform_tool_undo->original = tile_manager_ref (transform_tool->original);
endif|#
directive|endif
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|transform_tool_undo
operator|->
name|transform_tool
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|transform_tool_undo
operator|->
name|transform_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_transform_tool_undo_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_transform_tool_undo_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpTransformToolUndo
modifier|*
name|transform_tool_undo
init|=
name|GIMP_TRANSFORM_TOOL_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_TRANSFORM_TOOL
case|:
name|transform_tool_undo
operator|->
name|transform_tool
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_transform_tool_undo_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_transform_tool_undo_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpTransformToolUndo
modifier|*
name|transform_tool_undo
init|=
name|GIMP_TRANSFORM_TOOL_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_TRANSFORM_TOOL
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|transform_tool_undo
operator|->
name|transform_tool
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_transform_tool_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_transform_tool_undo_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
block|{
name|GimpTransformToolUndo
modifier|*
name|transform_tool_undo
init|=
name|GIMP_TRANSFORM_TOOL_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
name|GIMP_UNDO_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|pop
argument_list|(
name|undo
argument_list|,
name|undo_mode
argument_list|,
name|accum
argument_list|)
expr_stmt|;
if|if
condition|(
name|transform_tool_undo
operator|->
name|transform_tool
condition|)
block|{
name|GimpTransformTool
modifier|*
name|transform_tool
decl_stmt|;
name|TileManager
modifier|*
name|temp
decl_stmt|;
name|gdouble
name|d
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|transform_tool
operator|=
name|transform_tool_undo
operator|->
name|transform_tool
expr_stmt|;
comment|/*  swap the transformation information arrays  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|TRANS_INFO_SIZE
condition|;
name|i
operator|++
control|)
block|{
name|d
operator|=
name|transform_tool_undo
operator|->
name|trans_info
index|[
name|i
index|]
expr_stmt|;
name|transform_tool_undo
operator|->
name|trans_info
index|[
name|i
index|]
operator|=
name|transform_tool
operator|->
name|trans_info
index|[
name|i
index|]
expr_stmt|;
name|transform_tool
operator|->
name|trans_info
index|[
name|i
index|]
operator|=
name|d
expr_stmt|;
block|}
comment|/*  swap the original buffer--the source buffer for repeated transforms        */
name|temp
operator|=
name|transform_tool_undo
operator|->
name|original
expr_stmt|;
name|transform_tool_undo
operator|->
name|original
operator|=
name|transform_tool
operator|->
name|original
expr_stmt|;
name|transform_tool
operator|->
name|original
operator|=
name|temp
expr_stmt|;
comment|/*  If we're re-implementing the first transform, reactivate tool  */
if|if
condition|(
name|undo_mode
operator|==
name|GIMP_UNDO_MODE_REDO
operator|&&
name|transform_tool
operator|->
name|original
condition|)
block|{
name|gimp_tool_control_activate
argument_list|(
name|GIMP_TOOL
argument_list|(
name|transform_tool
argument_list|)
operator|->
name|control
argument_list|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|transform_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_transform_tool_undo_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_transform_tool_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpTransformToolUndo
modifier|*
name|transform_tool_undo
init|=
name|GIMP_TRANSFORM_TOOL_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
if|if
condition|(
name|transform_tool_undo
operator|->
name|transform_tool
condition|)
block|{
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|transform_tool_undo
operator|->
name|transform_tool
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|transform_tool_undo
operator|->
name|transform_tool
argument_list|)
expr_stmt|;
name|transform_tool_undo
operator|->
name|transform_tool
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|transform_tool_undo
operator|->
name|original
condition|)
block|{
name|tile_manager_unref
argument_list|(
name|transform_tool_undo
operator|->
name|original
argument_list|)
expr_stmt|;
name|transform_tool_undo
operator|->
name|original
operator|=
name|NULL
expr_stmt|;
block|}
name|GIMP_UNDO_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|free
argument_list|(
name|undo
argument_list|,
name|undo_mode
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

