begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginprocframe.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin-cleanup.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin-progress.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginprocedure.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpPlugInProcFrame
modifier|*
DECL|function|gimp_plug_in_proc_frame_new (GimpContext * context,GimpProgress * progress,GimpPlugInProcedure * procedure)
name|gimp_plug_in_proc_frame_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|proc_frame
operator|=
name|g_new0
argument_list|(
name|GimpPlugInProcFrame
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|ref_count
operator|=
literal|1
expr_stmt|;
name|gimp_plug_in_proc_frame_init
argument_list|(
name|proc_frame
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
return|return
name|proc_frame
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_proc_frame_init (GimpPlugInProcFrame * proc_frame,GimpContext * context,GimpProgress * progress,GimpPlugInProcedure * procedure)
name|gimp_plug_in_proc_frame_init
parameter_list|(
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|proc_frame
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|procedure
operator|==
name|NULL
operator|||
name|GIMP_IS_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|main_context
operator|=
name|g_object_ref
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|context_stack
operator|=
name|NULL
expr_stmt|;
name|proc_frame
operator|->
name|procedure
operator|=
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|main_loop
operator|=
name|NULL
expr_stmt|;
name|proc_frame
operator|->
name|return_vals
operator|=
name|NULL
expr_stmt|;
name|proc_frame
operator|->
name|progress
operator|=
name|progress
condition|?
name|g_object_ref
argument_list|(
name|progress
argument_list|)
else|:
name|NULL
expr_stmt|;
name|proc_frame
operator|->
name|progress_created
operator|=
name|FALSE
expr_stmt|;
name|proc_frame
operator|->
name|progress_cancel_id
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_plug_in_progress_attach
argument_list|(
name|progress
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_proc_frame_dispose (GimpPlugInProcFrame * proc_frame,GimpPlugIn * plug_in)
name|gimp_plug_in_proc_frame_dispose
parameter_list|(
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
parameter_list|,
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|proc_frame
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_frame
operator|->
name|progress
condition|)
block|{
name|gimp_plug_in_progress_end
argument_list|(
name|plug_in
argument_list|,
name|proc_frame
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
if|if
condition|(
name|proc_frame
operator|->
name|context_stack
condition|)
block|{
name|g_list_foreach
argument_list|(
name|proc_frame
operator|->
name|context_stack
argument_list|,
operator|(
name|GFunc
operator|)
name|g_object_unref
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|proc_frame
operator|->
name|context_stack
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|context_stack
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|proc_frame
operator|->
name|main_context
condition|)
block|{
name|g_object_unref
argument_list|(
name|proc_frame
operator|->
name|main_context
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|main_context
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|proc_frame
operator|->
name|return_vals
condition|)
block|{
name|g_value_array_free
argument_list|(
name|proc_frame
operator|->
name|return_vals
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|return_vals
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|proc_frame
operator|->
name|main_loop
condition|)
block|{
name|g_main_loop_unref
argument_list|(
name|proc_frame
operator|->
name|main_loop
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|main_loop
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|proc_frame
operator|->
name|cleanups
condition|)
name|gimp_plug_in_cleanup
argument_list|(
name|plug_in
argument_list|,
name|proc_frame
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpPlugInProcFrame
modifier|*
DECL|function|gimp_plug_in_proc_frame_ref (GimpPlugInProcFrame * proc_frame)
name|gimp_plug_in_proc_frame_ref
parameter_list|(
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|proc_frame
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|ref_count
operator|++
expr_stmt|;
return|return
name|proc_frame
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_proc_frame_unref (GimpPlugInProcFrame * proc_frame,GimpPlugIn * plug_in)
name|gimp_plug_in_proc_frame_unref
parameter_list|(
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
parameter_list|,
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|proc_frame
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|ref_count
operator|--
expr_stmt|;
if|if
condition|(
name|proc_frame
operator|->
name|ref_count
operator|<
literal|1
condition|)
block|{
name|gimp_plug_in_proc_frame_dispose
argument_list|(
name|proc_frame
argument_list|,
name|plug_in
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_frame
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GValueArray
modifier|*
DECL|function|gimp_plug_in_proc_frame_get_return_vals (GimpPlugInProcFrame * proc_frame)
name|gimp_plug_in_proc_frame_get_return_vals
parameter_list|(
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
parameter_list|)
block|{
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|proc_frame
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_frame
operator|->
name|return_vals
condition|)
block|{
if|if
condition|(
name|proc_frame
operator|->
name|return_vals
operator|->
name|n_values
operator|>=
name|proc_frame
operator|->
name|procedure
operator|->
name|num_values
operator|+
literal|1
condition|)
block|{
name|return_vals
operator|=
name|proc_frame
operator|->
name|return_vals
expr_stmt|;
block|}
else|else
block|{
comment|/* Allocate new return values of the correct size. */
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|proc_frame
operator|->
name|procedure
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* Copy all of the arguments we can. */
name|memcpy
argument_list|(
name|return_vals
operator|->
name|values
argument_list|,
name|proc_frame
operator|->
name|return_vals
operator|->
name|values
argument_list|,
sizeof|sizeof
argument_list|(
name|GValue
argument_list|)
operator|*
name|proc_frame
operator|->
name|return_vals
operator|->
name|n_values
argument_list|)
expr_stmt|;
comment|/* Free the old arguments. */
name|g_free
argument_list|(
name|proc_frame
operator|->
name|return_vals
operator|->
name|values
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|return_vals
operator|->
name|values
operator|=
literal|0
expr_stmt|;
name|proc_frame
operator|->
name|return_vals
operator|->
name|n_values
operator|=
literal|0
expr_stmt|;
name|g_value_array_free
argument_list|(
name|proc_frame
operator|->
name|return_vals
argument_list|)
expr_stmt|;
block|}
comment|/* We have consumed any saved values, so clear them. */
name|proc_frame
operator|->
name|return_vals
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
comment|/* Just return a dummy set of values. */
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|proc_frame
operator|->
name|procedure
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

end_unit

