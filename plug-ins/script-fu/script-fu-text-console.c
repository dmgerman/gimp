begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_if
if|#
directive|if
name|HAVE_UNISTD_H
end_if

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"scheme-wrapper.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-text-console.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-intl.h"
end_include

begin_function
name|void
DECL|function|script_fu_text_console_run (const gchar * name,gint nparams,const GimpParam * params,gint * nreturn_vals,GimpParam ** return_vals)
name|script_fu_text_console_run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|params
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
comment|/*  Enable Script-Fu output  */
name|ts_register_output_func
argument_list|(
name|ts_stdout_output_func
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ts_print_welcome
argument_list|()
expr_stmt|;
name|gimp_plugin_set_pdb_error_handler
argument_list|(
name|GIMP_PDB_ERROR_HANDLER_PLUGIN
argument_list|)
expr_stmt|;
comment|/*  Run the interface  */
name|ts_interpret_stdin
argument_list|()
expr_stmt|;
name|gimp_plugin_set_pdb_error_handler
argument_list|(
name|GIMP_PDB_ERROR_HANDLER_INTERNAL
argument_list|)
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
block|}
end_function

end_unit

