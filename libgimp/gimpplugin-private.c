begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpplugin-private.c  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"gimpplugin-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure-private.h"
end_include

begin_comment
comment|/*  local function prototpes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_plug_in_register
parameter_list|(
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
name|void
DECL|function|_gimp_plug_in_init (GimpPlugIn * plug_in)
name|_gimp_plug_in_init
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
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
if|if
condition|(
operator|!
name|GIMP_PLUG_IN_GET_CLASS
argument_list|(
name|plug_in
argument_list|)
operator|->
name|init_procedures
condition|)
return|return;
name|gimp_plug_in_register
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_plug_in_query (GimpPlugIn * plug_in)
name|_gimp_plug_in_query
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
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
if|if
condition|(
operator|!
name|GIMP_PLUG_IN_GET_CLASS
argument_list|(
name|plug_in
argument_list|)
operator|->
name|query_procedures
condition|)
return|return;
name|gimp_plug_in_register
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_plug_in_quit (GimpPlugIn * plug_in)
name|_gimp_plug_in_quit
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
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
if|if
condition|(
name|GIMP_PLUG_IN_GET_CLASS
argument_list|(
name|plug_in
argument_list|)
operator|->
name|quit
condition|)
name|GIMP_PLUG_IN_GET_CLASS
argument_list|(
name|plug_in
argument_list|)
operator|->
name|quit
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_register (GimpPlugIn * plug_in)
name|gimp_plug_in_register
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|gchar
modifier|*
modifier|*
name|procedures
decl_stmt|;
name|gint
name|n_procedures
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|procedures
operator|=
name|GIMP_PLUG_IN_GET_CLASS
argument_list|(
name|plug_in
argument_list|)
operator|->
name|query_procedures
argument_list|(
name|plug_in
argument_list|,
operator|&
name|n_procedures
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
name|n_procedures
condition|;
name|i
operator|++
control|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|procedure
operator|=
name|gimp_plug_in_create_procedure
argument_list|(
name|plug_in
argument_list|,
name|procedures
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|_gimp_procedure_register
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|plug_in
operator|->
name|priv
operator|->
name|translation_domain_name
condition|)
block|{
name|gchar
modifier|*
name|path
init|=
name|g_file_get_path
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|translation_domain_path
argument_list|)
decl_stmt|;
name|gimp_plugin_domain_register
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|translation_domain_name
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|plug_in
operator|->
name|priv
operator|->
name|help_domain_name
condition|)
block|{
name|gchar
modifier|*
name|uri
init|=
name|g_file_get_uri
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|help_domain_uri
argument_list|)
decl_stmt|;
name|gimp_plugin_domain_register
argument_list|(
name|plug_in
operator|->
name|priv
operator|->
name|help_domain_name
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|list
operator|=
name|plug_in
operator|->
name|priv
operator|->
name|menu_branches
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
name|GimpPlugInMenuBranch
modifier|*
name|branch
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
name|branch
operator|->
name|menu_path
argument_list|,
name|branch
operator|->
name|menu_label
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

