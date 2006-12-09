begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpundo.h"
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
file|"gimptransformtool-undo.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/********************/
end_comment

begin_comment
comment|/*  Transform Undo  */
end_comment

begin_comment
comment|/********************/
end_comment

begin_typedef
DECL|typedef|TransformUndo
typedef|typedef
name|struct
name|_TransformUndo
name|TransformUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_TransformUndo
struct|struct
name|_TransformUndo
block|{
DECL|member|tool_ID
name|gint
name|tool_ID
decl_stmt|;
DECL|member|tool_type
name|GType
name|tool_type
decl_stmt|;
DECL|member|trans_info
name|TransInfo
name|trans_info
decl_stmt|;
DECL|member|original
name|TileManager
modifier|*
name|original
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|gboolean
name|undo_pop_transform
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
name|undo_free_transform
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

begin_function
name|gboolean
DECL|function|gimp_transform_tool_push_undo (GimpImage * image,const gchar * undo_desc,gint tool_ID,GType tool_type,gdouble * trans_info,TileManager * original)
name|gimp_transform_tool_push_undo
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|gint
name|tool_ID
parameter_list|,
name|GType
name|tool_type
parameter_list|,
name|gdouble
modifier|*
name|trans_info
parameter_list|,
name|TileManager
modifier|*
name|original
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|new
decl_stmt|;
if|if
condition|(
operator|(
name|new
operator|=
name|gimp_image_undo_push
argument_list|(
name|image
argument_list|,
name|GIMP_TYPE_UNDO
argument_list|,
sizeof|sizeof
argument_list|(
name|TransformUndo
argument_list|)
argument_list|,
sizeof|sizeof
argument_list|(
name|TransformUndo
argument_list|)
argument_list|,
name|GIMP_UNDO_TRANSFORM
argument_list|,
name|undo_desc
argument_list|,
name|FALSE
argument_list|,
name|undo_pop_transform
argument_list|,
name|undo_free_transform
argument_list|,
name|NULL
argument_list|)
operator|)
condition|)
block|{
name|TransformUndo
modifier|*
name|tu
init|=
name|new
operator|->
name|data
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|tu
operator|->
name|tool_ID
operator|=
name|tool_ID
expr_stmt|;
name|tu
operator|->
name|tool_type
operator|=
name|tool_type
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
name|tu
operator|->
name|trans_info
index|[
name|i
index|]
operator|=
name|trans_info
index|[
name|i
index|]
expr_stmt|;
if|if
condition|(
name|original
condition|)
name|tu
operator|->
name|original
operator|=
name|tile_manager_ref
argument_list|(
name|original
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|undo_pop_transform (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|undo_pop_transform
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
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|undo
operator|->
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_TRANSFORM_TOOL
argument_list|(
name|active_tool
argument_list|)
condition|)
block|{
name|GimpTransformTool
modifier|*
name|tt
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|active_tool
argument_list|)
decl_stmt|;
name|TransformUndo
modifier|*
name|tu
init|=
name|undo
operator|->
name|data
decl_stmt|;
comment|/*  only pop if the active tool is the tool that pushed this undo  */
if|if
condition|(
name|tu
operator|->
name|tool_ID
operator|==
name|active_tool
operator|->
name|ID
condition|)
block|{
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
name|tu
operator|->
name|trans_info
index|[
name|i
index|]
expr_stmt|;
name|tu
operator|->
name|trans_info
index|[
name|i
index|]
operator|=
name|tt
operator|->
name|trans_info
index|[
name|i
index|]
expr_stmt|;
name|tt
operator|->
name|trans_info
index|[
name|i
index|]
operator|=
name|d
expr_stmt|;
block|}
comment|/*  swap the original buffer--the source buffer for repeated transforms            */
name|temp
operator|=
name|tu
operator|->
name|original
expr_stmt|;
name|tu
operator|->
name|original
operator|=
name|tt
operator|->
name|original
expr_stmt|;
name|tt
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
name|tt
operator|->
name|original
condition|)
block|{
name|gimp_tool_control_activate
argument_list|(
name|active_tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tt
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|undo_free_transform (GimpUndo * undo,GimpUndoMode undo_mode)
name|undo_free_transform
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|TransformUndo
modifier|*
name|tu
init|=
name|undo
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|tu
operator|->
name|original
condition|)
name|tile_manager_unref
argument_list|(
name|tu
operator|->
name|original
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tu
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

