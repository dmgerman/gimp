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
file|"gimpforegroundselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpforegroundselecttool-undo.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28ecd1c30108
block|{
DECL|member|tool_ID
name|gint
name|tool_ID
decl_stmt|;
DECL|typedef|FgSelectUndo
block|}
name|FgSelectUndo
typedef|;
end_typedef

begin_function_decl
specifier|static
name|gboolean
name|undo_pop_foreground_select
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
name|undo_free_foreground_select
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
DECL|function|gimp_foreground_select_tool_push_undo (GimpImage * gimage,const gchar * undo_desc,gint tool_ID)
name|gimp_foreground_select_tool_push_undo
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|gint
name|tool_ID
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
name|gimage
argument_list|,
name|GIMP_TYPE_UNDO
argument_list|,
sizeof|sizeof
argument_list|(
name|FgSelectUndo
argument_list|)
argument_list|,
sizeof|sizeof
argument_list|(
name|FgSelectUndo
argument_list|)
argument_list|,
name|GIMP_UNDO_FOREGROUND_SELECT
argument_list|,
name|undo_desc
argument_list|,
name|FALSE
argument_list|,
name|undo_pop_foreground_select
argument_list|,
name|undo_free_foreground_select
argument_list|,
name|NULL
argument_list|)
operator|)
condition|)
block|{
name|FgSelectUndo
modifier|*
name|undo
init|=
name|new
operator|->
name|data
decl_stmt|;
name|undo
operator|->
name|tool_ID
operator|=
name|tool_ID
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
DECL|function|undo_pop_foreground_select (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|undo_pop_foreground_select
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
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_FOREGROUND_SELECT_TOOL
argument_list|(
name|active_tool
argument_list|)
condition|)
block|{
name|FgSelectUndo
modifier|*
name|fg_undo
init|=
name|undo
operator|->
name|data
decl_stmt|;
comment|/*  only pop if the active tool is the tool that pushed this undo  */
if|if
condition|(
name|fg_undo
operator|->
name|tool_ID
operator|==
name|active_tool
operator|->
name|ID
condition|)
block|{          }
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|undo_free_foreground_select (GimpUndo * undo,GimpUndoMode undo_mode)
name|undo_free_foreground_select
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|FgSelectUndo
modifier|*
name|fg_undo
init|=
name|undo
operator|->
name|data
decl_stmt|;
name|g_free
argument_list|(
name|fg_undo
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

