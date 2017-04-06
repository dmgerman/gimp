begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpparamspecs.h"
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

begin_decl_stmt
DECL|variable|gimp_debug_timer
specifier|static
name|GTimer
modifier|*
name|gimp_debug_timer
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_debug_timer_counter
specifier|static
name|gint
name|gimp_debug_timer_counter
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|debug_timer_start_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|debug_timer_start_invoker
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
if|if
condition|(
name|gimp_debug_timer_counter
operator|++
operator|==
literal|0
condition|)
name|gimp_debug_timer
operator|=
name|g_timer_new
argument_list|()
expr_stmt|;
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|debug_timer_end_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|debug_timer_end_invoker
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
name|gdouble
name|elapsed
init|=
literal|0.0
decl_stmt|;
name|elapsed
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|gimp_debug_timer_counter
operator|==
literal|0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
elseif|else
if|if
condition|(
operator|--
name|gimp_debug_timer_counter
operator|==
literal|0
condition|)
block|{
name|elapsed
operator|=
name|g_timer_elapsed
argument_list|(
name|gimp_debug_timer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"GIMP debug timer: %g seconds\n"
argument_list|,
name|elapsed
argument_list|)
expr_stmt|;
name|g_timer_destroy
argument_list|(
name|gimp_debug_timer
argument_list|)
expr_stmt|;
name|gimp_debug_timer
operator|=
name|NULL
expr_stmt|;
block|}
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
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|elapsed
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|void
DECL|function|register_debug_procs (GimpPDB * pdb)
name|register_debug_procs
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
comment|/*    * gimp-debug-timer-start    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|debug_timer_start_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-debug-timer-start"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-debug-timer-start"
argument_list|,
literal|"Starts measuring elapsed time."
argument_list|,
literal|"This procedure starts a timer, measuring the elapsed time since the call. Each call to this procedure should be matched by a call to 'gimp-debug-timer-end', which returns the elapsed time.\n"
literal|"If there is already an active timer, it is not affected by the call, however, a matching 'gimp-debug-timer-end' call is still required.\n"
literal|"\n"
literal|"This is a debug utility procedure. It is subject to change at any point, and should not be used in production."
argument_list|,
literal|"Ell"
argument_list|,
literal|"Ell"
argument_list|,
literal|"2017"
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
comment|/*    * gimp-debug-timer-end    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|debug_timer_end_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-debug-timer-end"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-debug-timer-end"
argument_list|,
literal|"Finishes measuring elapsed time."
argument_list|,
literal|"This procedure stops the timer started by a previous 'gimp-debug-timer-start' call, and prints and returns the elapsed time.\n"
literal|"If there was already an active timer at the time of corresponding call to 'gimp-debug-timer-start', a dummy value is returned.\n"
literal|"\n"
literal|"This is a debug utility procedure. It is subject to change at any point, and should not be used in production."
argument_list|,
literal|"Ell"
argument_list|,
literal|"Ell"
argument_list|,
literal|"2017"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"elapsed"
argument_list|,
literal|"elapsed"
argument_list|,
literal|"The elapsed time, in seconds"
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
block|}
end_function

end_unit

