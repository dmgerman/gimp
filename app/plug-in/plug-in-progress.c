begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * plug-in-progress.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppdbprogress.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"plug-in.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-progress.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|plug_in_progress_cancel_callback
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|plug_in_progress_start (PlugIn * plug_in,const gchar * message,gint display_ID)
name|plug_in_progress_start
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gint
name|display_ID
parameter_list|)
block|{
name|PlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|plug_in
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in
operator|->
name|temp_proc_frames
condition|)
name|proc_frame
operator|=
name|plug_in
operator|->
name|temp_proc_frames
operator|->
name|data
expr_stmt|;
else|else
name|proc_frame
operator|=
operator|&
name|plug_in
operator|->
name|main_proc_frame
expr_stmt|;
if|if
condition|(
operator|!
name|message
condition|)
name|message
operator|=
name|plug_in
operator|->
name|prog
expr_stmt|;
if|if
condition|(
operator|!
name|proc_frame
operator|->
name|progress
condition|)
block|{
name|proc_frame
operator|->
name|progress
operator|=
name|gimp_new_progress
argument_list|(
name|plug_in
operator|->
name|gimp
argument_list|,
name|display_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_frame
operator|->
name|progress
condition|)
block|{
name|proc_frame
operator|->
name|progress_created
operator|=
name|TRUE
expr_stmt|;
name|g_object_ref
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|proc_frame
operator|->
name|progress
condition|)
block|{
if|if
condition|(
operator|!
name|proc_frame
operator|->
name|progress_cancel_id
condition|)
name|proc_frame
operator|->
name|progress_cancel_id
operator|=
name|g_signal_connect
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|,
literal|"cancel"
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_progress_cancel_callback
argument_list|)
argument_list|,
name|plug_in
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_progress_is_active
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
condition|)
block|{
name|gimp_progress_set_text
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|gimp_progress_set_value
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_progress_start
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|,
name|message
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|plug_in_progress_update (PlugIn * plug_in,gdouble percentage)
name|plug_in_progress_update
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
name|PlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|plug_in
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in
operator|->
name|temp_proc_frames
condition|)
name|proc_frame
operator|=
name|plug_in
operator|->
name|temp_proc_frames
operator|->
name|data
expr_stmt|;
else|else
name|proc_frame
operator|=
operator|&
name|plug_in
operator|->
name|main_proc_frame
expr_stmt|;
if|if
condition|(
operator|!
name|proc_frame
operator|->
name|progress
operator|||
operator|!
name|gimp_progress_is_active
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
operator|||
operator|!
name|proc_frame
operator|->
name|progress_cancel_id
condition|)
block|{
name|plug_in_progress_start
argument_list|(
name|plug_in
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|proc_frame
operator|->
name|progress
operator|&&
name|gimp_progress_is_active
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
condition|)
name|gimp_progress_set_value
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|plug_in_progress_end (PlugIn * plug_in)
name|plug_in_progress_end
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|PlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|plug_in
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in
operator|->
name|temp_proc_frames
condition|)
name|proc_frame
operator|=
name|plug_in
operator|->
name|temp_proc_frames
operator|->
name|data
expr_stmt|;
else|else
name|proc_frame
operator|=
operator|&
name|plug_in
operator|->
name|main_proc_frame
expr_stmt|;
if|if
condition|(
name|proc_frame
operator|->
name|progress
condition|)
block|{
if|if
condition|(
name|proc_frame
operator|->
name|progress_cancel_id
condition|)
block|{
name|g_signal_handler_disconnect
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|,
name|proc_frame
operator|->
name|progress_cancel_id
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|progress_cancel_id
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|gimp_progress_is_active
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
condition|)
name|gimp_progress_end
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_frame
operator|->
name|progress_created
condition|)
block|{
name|gimp_free_progress
argument_list|(
name|plug_in
operator|->
name|gimp
argument_list|,
name|proc_frame
operator|->
name|progress
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|progress
operator|=
name|NULL
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|plug_in_progress_install (PlugIn * plug_in,const gchar * progress_callback)
name|plug_in_progress_install
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|progress_callback
parameter_list|)
block|{
name|PlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|ProcRecord
modifier|*
name|proc_rec
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|plug_in
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress_callback
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc_rec
operator|=
name|procedural_db_lookup
argument_list|(
name|plug_in
operator|->
name|gimp
argument_list|,
name|progress_callback
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc_rec
operator|||
name|proc_rec
operator|->
name|num_args
operator|!=
literal|3
operator|||
name|proc_rec
operator|->
name|args
index|[
literal|0
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_INT32
operator|||
name|proc_rec
operator|->
name|args
index|[
literal|1
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_STRING
operator|||
name|proc_rec
operator|->
name|args
index|[
literal|2
index|]
operator|.
name|arg_type
operator|!=
name|GIMP_PDB_FLOAT
operator|||
name|proc_rec
operator|->
name|proc_type
operator|!=
name|GIMP_TEMPORARY
operator|||
name|proc_rec
operator|->
name|exec_method
operator|.
name|temporary
operator|.
name|plug_in
operator|!=
name|plug_in
condition|)
block|{
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|plug_in
operator|->
name|temp_proc_frames
condition|)
name|proc_frame
operator|=
name|plug_in
operator|->
name|temp_proc_frames
operator|->
name|data
expr_stmt|;
else|else
name|proc_frame
operator|=
operator|&
name|plug_in
operator|->
name|main_proc_frame
expr_stmt|;
if|if
condition|(
name|proc_frame
operator|->
name|progress
condition|)
block|{
name|plug_in_progress_end
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_frame
operator|->
name|progress
condition|)
block|{
name|g_object_unref
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|progress
operator|=
name|NULL
expr_stmt|;
block|}
block|}
name|proc_frame
operator|->
name|progress
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PDB_PROGRESS
argument_list|,
literal|"context"
argument_list|,
name|proc_frame
operator|->
name|context
argument_list|,
literal|"callback-name"
argument_list|,
name|progress_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|plug_in_progress_uninstall (PlugIn * plug_in,const gchar * progress_callback)
name|plug_in_progress_uninstall
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|progress_callback
parameter_list|)
block|{
name|PlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|plug_in
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress_callback
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in
operator|->
name|temp_proc_frames
condition|)
name|proc_frame
operator|=
name|plug_in
operator|->
name|temp_proc_frames
operator|->
name|data
expr_stmt|;
else|else
name|proc_frame
operator|=
operator|&
name|plug_in
operator|->
name|main_proc_frame
expr_stmt|;
if|if
condition|(
name|GIMP_IS_PDB_PROGRESS
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
condition|)
block|{
name|plug_in_progress_end
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|progress
operator|=
name|NULL
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
name|gboolean
DECL|function|plug_in_progress_cancel (PlugIn * plug_in,const gchar * progress_callback)
name|plug_in_progress_cancel
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|progress_callback
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|plug_in
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress_callback
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|plug_in_progress_cancel_callback (GimpProgress * progress,PlugIn * plug_in)
name|plug_in_progress_cancel_callback
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|PlugInProcFrame
modifier|*
name|proc_frame
init|=
operator|&
name|plug_in
operator|->
name|main_proc_frame
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
name|proc_frame
operator|->
name|main_loop
condition|)
block|{
name|proc_frame
operator|->
name|return_vals
operator|=
name|g_new
argument_list|(
name|Argument
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|n_return_vals
operator|=
literal|1
expr_stmt|;
name|proc_frame
operator|->
name|return_vals
operator|->
name|arg_type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|proc_frame
operator|->
name|return_vals
operator|->
name|value
operator|.
name|pdb_int
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
block|}
for|for
control|(
name|list
operator|=
name|plug_in
operator|->
name|temp_proc_frames
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|proc_frame
operator|=
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|proc_frame
operator|->
name|main_loop
condition|)
block|{
name|proc_frame
operator|->
name|return_vals
operator|=
name|g_new
argument_list|(
name|Argument
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|n_return_vals
operator|=
literal|1
expr_stmt|;
name|proc_frame
operator|->
name|return_vals
operator|->
name|arg_type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|proc_frame
operator|->
name|return_vals
operator|->
name|value
operator|.
name|pdb_int
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
block|}
block|}
name|plug_in_close
argument_list|(
name|plug_in
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|plug_in_unref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

