begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpdebug_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * SECTION: gimpdebug_pdb  * @title: gimpdebug  * @short_description: Debug utility functions  *  * Miscellaneous debug utility functions. Not part of the stable  * library interface.  **/
end_comment

begin_comment
comment|/**  * gimp_debug_timer_start:  *  * Starts measuring elapsed time.  *  * This procedure starts a timer, measuring the elapsed time since the  * call. Each call to this procedure should be matched by a call to  * gimp_debug_timer_end(), which returns the elapsed time.  * If there is already an active timer, it is not affected by the call,  * however, a matching gimp_debug_timer_end() call is still required.  *  * This is a debug utility procedure. It is subject to change at any  * point, and should not be used in production.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_debug_timer_start (void)
name|gimp_debug_timer_start
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-debug-timer-start"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_debug_timer_end:  *  * Finishes measuring elapsed time.  *  * This procedure stops the timer started by a previous  * gimp_debug_timer_start() call, and prints and returns the elapsed  * time.  * If there was already an active timer at the time of corresponding  * call to gimp_debug_timer_start(), a dummy value is returned.  *  * This is a debug utility procedure. It is subject to change at any  * point, and should not be used in production.  *  * Returns: The elapsed time, in seconds.  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_debug_timer_end (void)
name|gimp_debug_timer_end
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
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
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-debug-timer-end"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|elapsed
operator|=
name|g_value_get_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|elapsed
return|;
block|}
end_function

end_unit

