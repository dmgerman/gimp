begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl. */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
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
file|"plug-in/gimpplugin-progress.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimpplugin.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"internal-procs.h"
end_include

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|progress_init_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|progress_init_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|message
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisplay
decl_stmt|;
name|message
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|gdisplay
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp
operator|->
name|plug_in_manager
operator|->
name|current_plug_in
decl_stmt|;
if|if
condition|(
name|plug_in
operator|&&
name|plug_in
operator|->
name|open
condition|)
block|{
if|if
condition|(
operator|!
name|gimp
operator|->
name|no_interface
condition|)
name|gimp_plug_in_progress_start
argument_list|(
name|plug_in
argument_list|,
name|message
argument_list|,
name|gdisplay
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|progress_update_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|progress_update_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gdouble
name|percentage
decl_stmt|;
name|percentage
operator|=
name|g_value_get_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp
operator|->
name|plug_in_manager
operator|->
name|current_plug_in
decl_stmt|;
if|if
condition|(
name|plug_in
operator|&&
name|plug_in
operator|->
name|open
condition|)
block|{
if|if
condition|(
operator|!
name|gimp
operator|->
name|no_interface
condition|)
name|gimp_plug_in_progress_set_value
argument_list|(
name|plug_in
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|progress_pulse_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|progress_pulse_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp
operator|->
name|plug_in_manager
operator|->
name|current_plug_in
decl_stmt|;
if|if
condition|(
name|plug_in
operator|&&
name|plug_in
operator|->
name|open
condition|)
block|{
if|if
condition|(
operator|!
name|gimp
operator|->
name|no_interface
condition|)
name|gimp_plug_in_progress_pulse
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|progress_set_text_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|progress_set_text_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|message
decl_stmt|;
name|message
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp
operator|->
name|plug_in_manager
operator|->
name|current_plug_in
decl_stmt|;
if|if
condition|(
name|plug_in
operator|&&
name|plug_in
operator|->
name|open
condition|)
block|{
if|if
condition|(
operator|!
name|gimp
operator|->
name|no_interface
condition|)
name|gimp_plug_in_progress_set_text
argument_list|(
name|plug_in
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|progress_end_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|progress_end_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp
operator|->
name|plug_in_manager
operator|->
name|current_plug_in
decl_stmt|;
if|if
condition|(
name|plug_in
operator|&&
name|plug_in
operator|->
name|open
condition|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
init|=
name|gimp_plug_in_get_proc_frame
argument_list|(
name|plug_in
argument_list|)
decl_stmt|;
name|gimp_plug_in_progress_end
argument_list|(
name|plug_in
argument_list|,
name|proc_frame
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|progress_get_window_handle_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|progress_get_window_handle_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|window
init|=
literal|0
decl_stmt|;
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp
operator|->
name|plug_in_manager
operator|->
name|current_plug_in
decl_stmt|;
if|if
condition|(
name|plug_in
operator|&&
name|plug_in
operator|->
name|open
condition|)
block|{
if|if
condition|(
operator|!
name|gimp
operator|->
name|no_interface
condition|)
name|window
operator|=
name|gimp_plug_in_progress_get_window_id
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|progress_install_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|progress_install_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|progress_callback
decl_stmt|;
name|progress_callback
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp
operator|->
name|plug_in_manager
operator|->
name|current_plug_in
decl_stmt|;
if|if
condition|(
name|plug_in
operator|&&
name|plug_in
operator|->
name|open
condition|)
name|success
operator|=
name|gimp_plug_in_progress_install
argument_list|(
name|plug_in
argument_list|,
name|progress_callback
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|progress_uninstall_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|progress_uninstall_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|progress_callback
decl_stmt|;
name|progress_callback
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp
operator|->
name|plug_in_manager
operator|->
name|current_plug_in
decl_stmt|;
if|if
condition|(
name|plug_in
operator|&&
name|plug_in
operator|->
name|open
condition|)
name|success
operator|=
name|gimp_plug_in_progress_uninstall
argument_list|(
name|plug_in
argument_list|,
name|progress_callback
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|progress_cancel_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|progress_cancel_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|progress_callback
decl_stmt|;
name|progress_callback
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp
operator|->
name|plug_in_manager
operator|->
name|current_plug_in
decl_stmt|;
if|if
condition|(
name|plug_in
operator|&&
name|plug_in
operator|->
name|open
condition|)
name|success
operator|=
name|gimp_plug_in_progress_cancel
argument_list|(
name|plug_in
argument_list|,
name|progress_callback
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|register_progress_procs (GimpPDB * pdb)
name|register_progress_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
comment|/*    * gimp-progress-init    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|progress_init_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-progress-init"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Initializes the progress bar for the current plug-in."
argument_list|,
literal|"Initializes the progress bar for the current plug-in. It is only valid to call this procedure from a plug-in."
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1995-1996"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"message"
argument_list|,
literal|"message"
argument_list|,
literal|"Message to use in the progress dialog"
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_display
argument_list|(
literal|"gdisplay"
argument_list|,
literal|"gdisplay"
argument_list|,
literal|"GimpDisplay to update progressbar in, or %NULL for a separate window"
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-progress-update    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|progress_update_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-progress-update"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Updates the progress bar for the current plug-in."
argument_list|,
literal|"Updates the progress bar for the current plug-in. It is only valid to call this procedure from a plug-in."
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1995-1996"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"percentage"
argument_list|,
literal|"percentage"
argument_list|,
literal|"Percentage of progress completed which must be between 0.0 and 1.0"
argument_list|,
operator|-
name|G_MAXDOUBLE
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-progress-pulse    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|progress_pulse_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-progress-pulse"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Pulses the progress bar for the current plug-in."
argument_list|,
literal|"Updates the progress bar for the current plug-in. It is only valid to call this procedure from a plug-in. Use this function instead of 'gimp-progress-update' if you cannot tell how much progress has been made. This usually causes the the progress bar to enter \"activity mode\", where a block bounces back and forth."
argument_list|,
literal|"Sven Neumann<sven@gimp.org>"
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-progress-set-text    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|progress_set_text_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-progress-set-text"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Changes the text in the progress bar for the current plug-in."
argument_list|,
literal|"This function changes the text in the progress bar for the current plug-in. Unlike 'gimp-progress-init' it does not change the displayed value."
argument_list|,
literal|"Sven Neumann<sven@gimp.org>"
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"message"
argument_list|,
literal|"message"
argument_list|,
literal|"Message to use in the progress dialog"
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-progress-end    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|progress_end_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-progress-end"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Ends the progress bar for the current plug-in."
argument_list|,
literal|"Ends the progress display for the current plug-in. Most plug-ins don't need to call this, they just exit when the work is done. It is only valid to call this procedure from a plug-in."
argument_list|,
literal|"Sven Neumann<sven@gimp.org>"
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"2007"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-progress-get-window-handle    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|progress_get_window_handle_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-progress-get-window-handle"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Returns the native window ID of the toplevel window this plug-in's progress is displayed in."
argument_list|,
literal|"This function returns the native window ID of the toplevel window this plug-in\'s progress is displayed in."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2004"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"window"
argument_list|,
literal|"window"
argument_list|,
literal|"The progress bar's toplevel window"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-progress-install    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|progress_install_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-progress-install"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Installs a progress callback for the current plug-in."
argument_list|,
literal|"This function installs a temporary PDB procedure which will handle all progress calls made by this plug-in and any procedure it calls. Calling this function multiple times simply replaces the old progress callbacks."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2004"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"progress-callback"
argument_list|,
literal|"progress callback"
argument_list|,
literal|"The callback PDB proc to call"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-progress-uninstall    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|progress_uninstall_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-progress-uninstall"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Uninstalls the progress callback for the current plug-in."
argument_list|,
literal|"This function uninstalls any progress callback installed with 'gimp-progress-install' before."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2004"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"progress-callback"
argument_list|,
literal|"progress callback"
argument_list|,
literal|"The name of the callback registered for this progress"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-progress-cancel    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|progress_cancel_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-progress-cancel"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Cancels a running progress."
argument_list|,
literal|"This function cancels the currently running progress."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2004"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"progress-callback"
argument_list|,
literal|"progress callback"
argument_list|,
literal|"The name of the callback registered for this progress"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

