begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpprocedure-private.c  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"gimp-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpgpparams.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure-private.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|_gimp_procedure_register (GimpProcedure * procedure)
name|_gimp_procedure_register
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|GParamSpec
modifier|*
modifier|*
name|args
decl_stmt|;
name|GParamSpec
modifier|*
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|n_args
decl_stmt|;
name|gint
name|n_return_vals
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpPlugIn
modifier|*
name|plug_in
decl_stmt|;
name|GPProcInstall
name|proc_install
decl_stmt|;
name|GimpIconType
name|icon_type
decl_stmt|;
specifier|const
name|guint8
modifier|*
name|icon_data
decl_stmt|;
name|gint
name|icon_data_length
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|args
operator|=
name|gimp_procedure_get_arguments
argument_list|(
name|procedure
argument_list|,
operator|&
name|n_args
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
operator|&
name|n_return_vals
argument_list|)
expr_stmt|;
name|proc_install
operator|.
name|name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gimp_procedure_get_name
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc_install
operator|.
name|blurb
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gimp_procedure_get_blurb
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc_install
operator|.
name|help
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gimp_procedure_get_help
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc_install
operator|.
name|authors
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gimp_procedure_get_authors
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc_install
operator|.
name|copyright
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gimp_procedure_get_copyright
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc_install
operator|.
name|date
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gimp_procedure_get_date
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc_install
operator|.
name|menu_label
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gimp_procedure_get_menu_label
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc_install
operator|.
name|image_types
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gimp_procedure_get_image_types
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc_install
operator|.
name|type
operator|=
name|gimp_procedure_get_proc_type
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc_install
operator|.
name|nparams
operator|=
name|n_args
expr_stmt|;
name|proc_install
operator|.
name|nreturn_vals
operator|=
name|n_return_vals
expr_stmt|;
name|proc_install
operator|.
name|params
operator|=
name|g_new0
argument_list|(
name|GPParamDef
argument_list|,
name|n_args
argument_list|)
expr_stmt|;
name|proc_install
operator|.
name|return_vals
operator|=
name|g_new0
argument_list|(
name|GPParamDef
argument_list|,
name|n_return_vals
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_args
condition|;
name|i
operator|++
control|)
block|{
name|_gimp_param_spec_to_gp_param_def
argument_list|(
name|args
index|[
name|i
index|]
argument_list|,
operator|&
name|proc_install
operator|.
name|params
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_return_vals
condition|;
name|i
operator|++
control|)
block|{
name|_gimp_param_spec_to_gp_param_def
argument_list|(
name|return_vals
index|[
name|i
index|]
argument_list|,
operator|&
name|proc_install
operator|.
name|return_vals
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|plug_in
operator|=
name|gimp_procedure_get_plug_in
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gp_proc_install_write
argument_list|(
name|_gimp_plug_in_get_write_channel
argument_list|(
name|plug_in
argument_list|)
argument_list|,
operator|&
name|proc_install
argument_list|,
name|plug_in
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
name|icon_type
operator|=
name|gimp_procedure_get_icon
argument_list|(
name|procedure
argument_list|,
operator|&
name|icon_data
argument_list|,
operator|&
name|icon_data_length
argument_list|)
expr_stmt|;
if|if
condition|(
name|icon_data
condition|)
name|_gimp_plugin_icon_register
argument_list|(
name|gimp_procedure_get_name
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|icon_type
argument_list|,
name|icon_data_length
argument_list|,
name|icon_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_install
operator|.
name|params
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_install
operator|.
name|return_vals
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_procedure_get_menu_paths
argument_list|(
name|procedure
argument_list|)
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
name|gimp_plugin_menu_register
argument_list|(
name|gimp_procedure_get_name
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|_gimp_procedure_unregister (GimpProcedure * procedure)
name|_gimp_procedure_unregister
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
decl_stmt|;
name|GPProcUninstall
name|proc_uninstall
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|proc_uninstall
operator|.
name|name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gimp_procedure_get_name
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|plug_in
operator|=
name|gimp_procedure_get_plug_in
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gp_proc_uninstall_write
argument_list|(
name|_gimp_plug_in_get_write_channel
argument_list|(
name|plug_in
argument_list|)
argument_list|,
operator|&
name|proc_uninstall
argument_list|,
name|plug_in
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_procedure_extension_ready (GimpProcedure * procedure)
name|_gimp_procedure_extension_ready
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|plug_in
operator|=
name|gimp_procedure_get_plug_in
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gp_extension_ack_write
argument_list|(
name|_gimp_plug_in_get_write_channel
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|plug_in
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
end_function

end_unit

