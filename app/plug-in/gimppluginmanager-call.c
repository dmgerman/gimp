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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpprotocol.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpwire.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"base/tile.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
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
file|"plug-in-params.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-run.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-shm.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|Argument
modifier|*
name|plug_in_temp_run
parameter_list|(
name|ProcRecord
modifier|*
name|proc_rec
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|,
name|gint
name|argc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|Argument
modifier|*
name|plug_in_get_return_vals
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
name|ProcRecord
modifier|*
name|proc_rec
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|Argument
modifier|*
DECL|function|plug_in_run (Gimp * gimp,ProcRecord * proc_rec,Argument * args,gint argc,gboolean synchronous,gboolean destroy_return_vals,gint gdisp_ID)
name|plug_in_run
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|ProcRecord
modifier|*
name|proc_rec
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|,
name|gint
name|argc
parameter_list|,
name|gboolean
name|synchronous
parameter_list|,
name|gboolean
name|destroy_return_vals
parameter_list|,
name|gint
name|gdisp_ID
parameter_list|)
block|{
name|Argument
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
name|PlugIn
modifier|*
name|plug_in
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_rec
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|argc
operator|==
literal|0
operator|||
name|args
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_rec
operator|->
name|proc_type
operator|==
name|GIMP_TEMPORARY
condition|)
block|{
name|return_vals
operator|=
name|plug_in_temp_run
argument_list|(
name|proc_rec
argument_list|,
name|args
argument_list|,
name|argc
argument_list|)
expr_stmt|;
goto|goto
name|done
goto|;
block|}
name|plug_in
operator|=
name|plug_in_new
argument_list|(
name|gimp
argument_list|,
name|proc_rec
argument_list|,
name|proc_rec
operator|->
name|exec_method
operator|.
name|plug_in
operator|.
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in
condition|)
block|{
name|GPConfig
name|config
decl_stmt|;
name|GPProcRun
name|proc_run
decl_stmt|;
if|if
condition|(
operator|!
name|plug_in_open
argument_list|(
name|plug_in
argument_list|)
condition|)
block|{
name|plug_in_unref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
goto|goto
name|done
goto|;
block|}
name|plug_in
operator|->
name|recurse
operator|=
name|synchronous
expr_stmt|;
name|config
operator|.
name|version
operator|=
name|GP_VERSION
expr_stmt|;
name|config
operator|.
name|tile_width
operator|=
name|TILE_WIDTH
expr_stmt|;
name|config
operator|.
name|tile_height
operator|=
name|TILE_HEIGHT
expr_stmt|;
name|config
operator|.
name|shm_ID
operator|=
name|plug_in_shm_get_ID
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|config
operator|.
name|gamma
operator|=
name|gimp
operator|->
name|config
operator|->
name|gamma_val
expr_stmt|;
name|config
operator|.
name|install_cmap
operator|=
name|gimp
operator|->
name|config
operator|->
name|install_cmap
expr_stmt|;
name|config
operator|.
name|show_tool_tips
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|show_tool_tips
expr_stmt|;
name|config
operator|.
name|min_colors
operator|=
name|CLAMP
argument_list|(
name|gimp
operator|->
name|config
operator|->
name|min_colors
argument_list|,
literal|27
argument_list|,
literal|256
argument_list|)
expr_stmt|;
name|config
operator|.
name|gdisp_ID
operator|=
name|gdisp_ID
expr_stmt|;
name|proc_run
operator|.
name|name
operator|=
name|proc_rec
operator|->
name|name
expr_stmt|;
name|proc_run
operator|.
name|nparams
operator|=
name|argc
expr_stmt|;
name|proc_run
operator|.
name|params
operator|=
name|plug_in_args_to_params
argument_list|(
name|args
argument_list|,
name|argc
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gp_config_write
argument_list|(
name|plug_in
operator|->
name|my_write
argument_list|,
operator|&
name|config
argument_list|,
name|plug_in
argument_list|)
operator|||
operator|!
name|gp_proc_run_write
argument_list|(
name|plug_in
operator|->
name|my_write
argument_list|,
operator|&
name|proc_run
argument_list|,
name|plug_in
argument_list|)
operator|||
operator|!
name|wire_flush
argument_list|(
name|plug_in
operator|->
name|my_write
argument_list|,
name|plug_in
argument_list|)
condition|)
block|{
name|return_vals
operator|=
name|procedural_db_return_args
argument_list|(
name|proc_rec
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
goto|goto
name|done
goto|;
block|}
name|plug_in_params_destroy
argument_list|(
name|proc_run
operator|.
name|params
argument_list|,
name|proc_run
operator|.
name|nparams
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|plug_in_ref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
comment|/* If this is an automatically installed extension, wait for an        * installation-confirmation message        */
if|if
condition|(
operator|(
name|proc_rec
operator|->
name|proc_type
operator|==
name|GIMP_EXTENSION
operator|)
operator|&&
operator|(
name|proc_rec
operator|->
name|num_args
operator|==
literal|0
operator|)
condition|)
block|{
name|plug_in
operator|->
name|starting_ext
operator|=
name|TRUE
expr_stmt|;
name|plug_in_main_loop
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|plug_in
operator|->
name|starting_ext
operator|=
name|FALSE
expr_stmt|;
block|}
comment|/* If this plug-in is requested to run synchronously, wait for        * it's return values        */
if|if
condition|(
name|plug_in
operator|->
name|recurse
condition|)
block|{
name|plug_in_main_loop
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|plug_in_get_return_vals
argument_list|(
name|plug_in
argument_list|,
name|proc_rec
argument_list|)
expr_stmt|;
block|}
name|plug_in_unref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
name|done
label|:
if|if
condition|(
name|return_vals
operator|&&
name|destroy_return_vals
condition|)
block|{
name|procedural_db_destroy_args
argument_list|(
name|return_vals
argument_list|,
name|proc_rec
operator|->
name|num_values
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|NULL
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|void
DECL|function|plug_in_repeat (Gimp * gimp,gint display_ID,gint image_ID,gint drawable_ID,gboolean with_interface)
name|plug_in_repeat
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|display_ID
parameter_list|,
name|gint
name|image_ID
parameter_list|,
name|gint
name|drawable_ID
parameter_list|,
name|gboolean
name|with_interface
parameter_list|)
block|{
name|Argument
modifier|*
name|args
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|last_plug_in
condition|)
block|{
comment|/* construct the procedures arguments */
name|args
operator|=
name|g_new
argument_list|(
name|Argument
argument_list|,
literal|3
argument_list|)
expr_stmt|;
comment|/* initialize the first three argument types */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
name|args
index|[
name|i
index|]
operator|.
name|arg_type
operator|=
name|gimp
operator|->
name|last_plug_in
operator|->
name|args
index|[
name|i
index|]
operator|.
name|arg_type
expr_stmt|;
comment|/* initialize the first three plug-in arguments  */
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
operator|(
name|with_interface
condition|?
name|GIMP_RUN_INTERACTIVE
else|:
name|GIMP_RUN_WITH_LAST_VALS
operator|)
expr_stmt|;
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|image_ID
expr_stmt|;
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|drawable_ID
expr_stmt|;
comment|/* run the plug-in procedure */
name|plug_in_run
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|last_plug_in
argument_list|,
name|args
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|display_ID
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plug_in_temp_run (ProcRecord * proc_rec,Argument * args,gint argc)
name|plug_in_temp_run
parameter_list|(
name|ProcRecord
modifier|*
name|proc_rec
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|,
name|gint
name|argc
parameter_list|)
block|{
name|Argument
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
name|PlugIn
modifier|*
name|plug_in
decl_stmt|;
name|plug_in
operator|=
operator|(
name|PlugIn
operator|*
operator|)
name|proc_rec
operator|->
name|exec_method
operator|.
name|temporary
operator|.
name|plug_in
expr_stmt|;
if|if
condition|(
name|plug_in
condition|)
block|{
name|GPProcRun
name|proc_run
decl_stmt|;
name|gboolean
name|old_recurse
decl_stmt|;
if|if
condition|(
name|plug_in
operator|->
name|current_temp_proc
condition|)
block|{
name|return_vals
operator|=
name|procedural_db_return_args
argument_list|(
name|proc_rec
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
goto|goto
name|done
goto|;
block|}
name|plug_in
operator|->
name|current_temp_proc
operator|=
name|proc_rec
expr_stmt|;
name|proc_run
operator|.
name|name
operator|=
name|proc_rec
operator|->
name|name
expr_stmt|;
name|proc_run
operator|.
name|nparams
operator|=
name|argc
expr_stmt|;
name|proc_run
operator|.
name|params
operator|=
name|plug_in_args_to_params
argument_list|(
name|args
argument_list|,
name|argc
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gp_temp_proc_run_write
argument_list|(
name|plug_in
operator|->
name|my_write
argument_list|,
operator|&
name|proc_run
argument_list|,
name|plug_in
argument_list|)
operator|||
operator|!
name|wire_flush
argument_list|(
name|plug_in
operator|->
name|my_write
argument_list|,
name|plug_in
argument_list|)
condition|)
block|{
name|return_vals
operator|=
name|procedural_db_return_args
argument_list|(
name|proc_rec
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
goto|goto
name|done
goto|;
block|}
name|plug_in_params_destroy
argument_list|(
name|proc_run
operator|.
name|params
argument_list|,
name|proc_run
operator|.
name|nparams
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|old_recurse
operator|=
name|plug_in
operator|->
name|recurse
expr_stmt|;
name|plug_in
operator|->
name|recurse
operator|=
name|TRUE
expr_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_TEMP_RETURN
name|plug_in_ref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|plug_in_main_loop
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|plug_in_get_return_vals
argument_list|(
name|proc_rec
argument_list|)
expr_stmt|;
else|#
directive|else
name|return_vals
operator|=
name|procedural_db_return_args
argument_list|(
name|proc_rec
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|plug_in
operator|->
name|recurse
operator|=
name|old_recurse
expr_stmt|;
name|plug_in
operator|->
name|current_temp_proc
operator|=
name|NULL
expr_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_TEMP_RETURN
name|plug_in_unref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
name|done
label|:
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plug_in_get_return_vals (PlugIn * plug_in,ProcRecord * proc_rec)
name|plug_in_get_return_vals
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
name|ProcRecord
modifier|*
name|proc_rec
parameter_list|)
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nargs
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|plug_in
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_rec
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Return the status code plus the current return values. */
name|nargs
operator|=
name|proc_rec
operator|->
name|num_values
operator|+
literal|1
expr_stmt|;
if|if
condition|(
name|plug_in
operator|->
name|return_vals
operator|&&
name|plug_in
operator|->
name|n_return_vals
operator|==
name|nargs
condition|)
block|{
name|return_vals
operator|=
name|plug_in
operator|->
name|return_vals
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|plug_in
operator|->
name|return_vals
condition|)
block|{
comment|/* Allocate new return values of the correct size. */
name|return_vals
operator|=
name|procedural_db_return_args
argument_list|(
name|proc_rec
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* Copy all of the arguments we can. */
name|memcpy
argument_list|(
name|return_vals
argument_list|,
name|plug_in
operator|->
name|return_vals
argument_list|,
sizeof|sizeof
argument_list|(
name|Argument
argument_list|)
operator|*
name|MIN
argument_list|(
name|plug_in
operator|->
name|n_return_vals
argument_list|,
name|nargs
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Free the old argument pointer.  This will cause a memory leak        * only if there were more values returned than we need (which        * shouldn't ever happen).        */
name|g_free
argument_list|(
name|plug_in
operator|->
name|return_vals
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Just return a dummy set of values. */
name|return_vals
operator|=
name|procedural_db_return_args
argument_list|(
name|proc_rec
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
comment|/* We have consumed any saved values, so clear them. */
name|plug_in
operator|->
name|return_vals
operator|=
name|NULL
expr_stmt|;
name|plug_in
operator|->
name|n_return_vals
operator|=
literal|0
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

end_unit

