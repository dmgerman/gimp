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
name|plug_in_progress_cancel
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
name|g_return_if_fail
argument_list|(
name|plug_in
operator|!=
name|NULL
argument_list|)
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
name|plug_in
operator|->
name|progress
condition|)
block|{
name|plug_in
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
name|plug_in
operator|->
name|progress
condition|)
name|plug_in
operator|->
name|progress_created
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
name|plug_in
operator|->
name|progress
condition|)
block|{
if|if
condition|(
name|plug_in
operator|->
name|progress_active
condition|)
block|{
name|gimp_progress_set_text
argument_list|(
name|plug_in
operator|->
name|progress
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|gimp_progress_set_value
argument_list|(
name|plug_in
operator|->
name|progress
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|gimp_progress_start
argument_list|(
name|plug_in
operator|->
name|progress
argument_list|,
name|message
argument_list|,
name|TRUE
argument_list|)
condition|)
block|{
name|gimp_progress_set_text
argument_list|(
name|plug_in
operator|->
name|progress
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|gimp_progress_set_value
argument_list|(
name|plug_in
operator|->
name|progress
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
name|g_signal_connect
argument_list|(
name|plug_in
operator|->
name|progress
argument_list|,
literal|"cancel"
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_progress_cancel
argument_list|)
argument_list|,
name|plug_in
argument_list|)
expr_stmt|;
name|plug_in
operator|->
name|progress_active
operator|=
name|TRUE
expr_stmt|;
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
name|g_return_if_fail
argument_list|(
name|plug_in
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|plug_in
operator|->
name|progress
operator|&&
name|plug_in
operator|->
name|progress_active
operator|)
condition|)
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
if|if
condition|(
name|plug_in
operator|->
name|progress
operator|&&
name|plug_in
operator|->
name|progress_active
condition|)
name|gimp_progress_set_value
argument_list|(
name|plug_in
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
name|progress
condition|)
block|{
if|if
condition|(
name|plug_in
operator|->
name|progress_active
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|plug_in
operator|->
name|progress
argument_list|,
name|plug_in_progress_cancel
argument_list|,
name|plug_in
argument_list|)
expr_stmt|;
name|gimp_progress_end
argument_list|(
name|plug_in
operator|->
name|progress
argument_list|)
expr_stmt|;
name|plug_in
operator|->
name|progress_active
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|plug_in
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
name|plug_in
operator|->
name|progress
argument_list|)
expr_stmt|;
name|plug_in
operator|->
name|progress
operator|=
name|NULL
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|plug_in_progress_cancel (GimpProgress * progress,PlugIn * plug_in)
name|plug_in_progress_cancel
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
if|if
condition|(
name|plug_in
operator|->
name|recurse_main_loop
operator|||
name|plug_in
operator|->
name|temp_main_loops
condition|)
block|{
name|plug_in
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
name|plug_in
operator|->
name|n_return_vals
operator|=
literal|1
expr_stmt|;
name|plug_in
operator|->
name|return_vals
operator|->
name|arg_type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|plug_in
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

