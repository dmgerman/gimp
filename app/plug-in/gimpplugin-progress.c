begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpplugin-progress.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpparamspecs.h"
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
file|"pdb/gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimppdberror.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin-progress.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"gimptemporaryprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_plug_in_progress_cancel_callback
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gint
DECL|function|gimp_plug_in_progress_attach (GimpProgress * progress)
name|gimp_plug_in_progress_attach
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|gint
name|attach_count
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|attach_count
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|progress
argument_list|)
argument_list|,
literal|"plug-in-progress-attach-count"
argument_list|)
argument_list|)
expr_stmt|;
name|attach_count
operator|++
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|progress
argument_list|)
argument_list|,
literal|"plug-in-progress-attach-count"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|attach_count
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|attach_count
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_plug_in_progress_detach (GimpProgress * progress)
name|gimp_plug_in_progress_detach
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|gint
name|attach_count
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|attach_count
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|progress
argument_list|)
argument_list|,
literal|"plug-in-progress-attach-count"
argument_list|)
argument_list|)
expr_stmt|;
name|attach_count
operator|--
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|progress
argument_list|)
argument_list|,
literal|"plug-in-progress-attach-count"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|attach_count
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|attach_count
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_progress_start (GimpPlugIn * plug_in,const gchar * message,GimpObject * display)
name|gimp_plug_in_progress_start
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|display
operator|==
name|NULL
operator|||
name|GIMP_IS_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|proc_frame
operator|=
name|gimp_plug_in_get_proc_frame
argument_list|(
name|plug_in
argument_list|)
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
name|manager
operator|->
name|gimp
argument_list|,
name|display
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
name|gimp_plug_in_progress_attach
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
name|gimp_plug_in_progress_cancel_callback
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
if|if
condition|(
name|message
condition|)
name|gimp_progress_set_text
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|,
name|message
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_progress_get_value
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
operator|>
literal|0.0
condition|)
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
condition|?
name|message
else|:
literal|""
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
DECL|function|gimp_plug_in_progress_end (GimpPlugIn * plug_in,GimpPlugInProcFrame * proc_frame)
name|gimp_plug_in_progress_end
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|proc_frame
operator|!=
name|NULL
argument_list|)
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
name|gimp_plug_in_progress_detach
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
operator|<
literal|1
operator|&&
name|gimp_progress_is_active
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
condition|)
block|{
name|gimp_progress_end
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
expr_stmt|;
block|}
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
name|manager
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
name|void
DECL|function|gimp_plug_in_progress_set_text (GimpPlugIn * plug_in,const gchar * message)
name|gimp_plug_in_progress_set_text
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
name|proc_frame
operator|=
name|gimp_plug_in_get_proc_frame
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
name|gimp_progress_set_text
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_progress_set_value (GimpPlugIn * plug_in,gdouble percentage)
name|gimp_plug_in_progress_set_value
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
name|proc_frame
operator|=
name|gimp_plug_in_get_proc_frame
argument_list|(
name|plug_in
argument_list|)
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
name|gimp_plug_in_progress_start
argument_list|(
name|plug_in
argument_list|,
name|NULL
argument_list|,
name|NULL
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
DECL|function|gimp_plug_in_progress_pulse (GimpPlugIn * plug_in)
name|gimp_plug_in_progress_pulse
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
name|proc_frame
operator|=
name|gimp_plug_in_get_proc_frame
argument_list|(
name|plug_in
argument_list|)
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
name|gimp_plug_in_progress_start
argument_list|(
name|plug_in
argument_list|,
name|NULL
argument_list|,
name|NULL
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
name|gimp_progress_pulse
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|guint32
DECL|function|gimp_plug_in_progress_get_window_id (GimpPlugIn * plug_in)
name|gimp_plug_in_progress_get_window_id
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|proc_frame
operator|=
name|gimp_plug_in_get_proc_frame
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
return|return
name|gimp_progress_get_window_id
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
return|;
return|return
literal|0
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_progress_install (GimpPlugIn * plug_in,const gchar * progress_callback)
name|gimp_plug_in_progress_install
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|progress_callback
parameter_list|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
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
name|procedure
operator|=
name|gimp_pdb_lookup_procedure
argument_list|(
name|plug_in
operator|->
name|manager
operator|->
name|gimp
operator|->
name|pdb
argument_list|,
name|progress_callback
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GIMP_IS_TEMPORARY_PROCEDURE
argument_list|(
name|procedure
argument_list|)
operator|||
name|GIMP_TEMPORARY_PROCEDURE
argument_list|(
name|procedure
argument_list|)
operator|->
name|plug_in
operator|!=
name|plug_in
operator|||
name|procedure
operator|->
name|num_args
operator|!=
literal|3
operator|||
operator|!
name|GIMP_IS_PARAM_SPEC_INT32
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|0
index|]
argument_list|)
operator|||
operator|!
name|G_IS_PARAM_SPEC_STRING
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|1
index|]
argument_list|)
operator|||
operator|!
name|G_IS_PARAM_SPEC_DOUBLE
argument_list|(
name|procedure
operator|->
name|args
index|[
literal|2
index|]
argument_list|)
condition|)
block|{
return|return
name|FALSE
return|;
block|}
name|proc_frame
operator|=
name|gimp_plug_in_get_proc_frame
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
name|proc_frame
operator|->
name|progress
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PDB_PROGRESS
argument_list|,
literal|"pdb"
argument_list|,
name|plug_in
operator|->
name|manager
operator|->
name|gimp
operator|->
name|pdb
argument_list|,
literal|"context"
argument_list|,
name|proc_frame
operator|->
name|main_context
argument_list|,
literal|"callback-name"
argument_list|,
name|progress_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plug_in_progress_attach
argument_list|(
name|proc_frame
operator|->
name|progress
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_progress_uninstall (GimpPlugIn * plug_in,const gchar * progress_callback)
name|gimp_plug_in_progress_uninstall
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|progress_callback
parameter_list|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
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
name|proc_frame
operator|=
name|gimp_plug_in_get_proc_frame
argument_list|(
name|plug_in
argument_list|)
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
name|gimp_plug_in_progress_end
argument_list|(
name|plug_in
argument_list|,
name|proc_frame
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
DECL|function|gimp_plug_in_progress_cancel (GimpPlugIn * plug_in,const gchar * progress_callback)
name|gimp_plug_in_progress_cancel
parameter_list|(
name|GimpPlugIn
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
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
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
name|GimpValueArray
modifier|*
DECL|function|get_cancel_return_values (GimpProcedure * procedure)
name|get_cancel_return_values
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GError
modifier|*
name|error
decl_stmt|;
name|error
operator|=
name|g_error_new_literal
argument_list|(
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_CANCELLED
argument_list|,
name|_
argument_list|(
literal|"Cancelled"
argument_list|)
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_progress_cancel_callback (GimpProgress * progress,GimpPlugIn * plug_in)
name|gimp_plug_in_progress_cancel_callback
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|GimpPlugInProcFrame
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
name|get_cancel_return_values
argument_list|(
name|proc_frame
operator|->
name|procedure
argument_list|)
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
name|get_cancel_return_values
argument_list|(
name|proc_frame
operator|->
name|procedure
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_plug_in_close
argument_list|(
name|plug_in
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

