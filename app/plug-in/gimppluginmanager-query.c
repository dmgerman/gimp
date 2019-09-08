begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * plug-ins-query.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager-query.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginprocedure.h"
end_include

begin_function
specifier|static
name|gboolean
DECL|function|match_string (GRegex * regex,gchar * string)
name|match_string
parameter_list|(
name|GRegex
modifier|*
name|regex
parameter_list|,
name|gchar
modifier|*
name|string
parameter_list|)
block|{
return|return
name|g_regex_match
argument_list|(
name|regex
argument_list|,
name|string
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_plug_in_manager_query (GimpPlugInManager * manager,const gchar * search_str,gchar *** procedure_strs,gchar *** accel_strs,gchar *** prog_strs,gint32 ** time_ints)
name|gimp_plug_in_manager_query
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|search_str
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|procedure_strs
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|accel_strs
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|prog_strs
parameter_list|,
name|gint32
modifier|*
modifier|*
name|time_ints
parameter_list|)
block|{
name|gint
name|num_plugins
init|=
literal|0
decl_stmt|;
name|GRegex
modifier|*
name|sregex
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|matched
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|procedure_strs
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|accel_strs
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|prog_strs
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|time_ints
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
operator|*
name|procedure_strs
operator|=
name|NULL
expr_stmt|;
operator|*
name|accel_strs
operator|=
name|NULL
expr_stmt|;
operator|*
name|prog_strs
operator|=
name|NULL
expr_stmt|;
operator|*
name|time_ints
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|search_str
operator|&&
operator|!
name|strlen
argument_list|(
name|search_str
argument_list|)
condition|)
name|search_str
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|search_str
condition|)
block|{
name|sregex
operator|=
name|g_regex_new
argument_list|(
name|search_str
argument_list|,
name|G_REGEX_CASELESS
operator||
name|G_REGEX_OPTIMIZE
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sregex
condition|)
return|return
literal|0
return|;
block|}
comment|/* count number of plugin entries, then allocate arrays of correct size    * where we can store the strings.    */
for|for
control|(
name|list
operator|=
name|manager
operator|->
name|plug_in_procedures
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|proc
operator|->
name|file
operator|&&
name|proc
operator|->
name|menu_paths
condition|)
block|{
name|gchar
modifier|*
name|name
init|=
name|proc
operator|->
name|menu_label
decl_stmt|;
name|name
operator|=
name|gimp_strip_uline
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|search_str
operator|||
name|match_string
argument_list|(
name|sregex
argument_list|,
name|name
argument_list|)
condition|)
block|{
name|num_plugins
operator|++
expr_stmt|;
name|matched
operator|=
name|g_slist_prepend
argument_list|(
name|matched
argument_list|,
name|proc
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
block|}
operator|*
name|procedure_strs
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
operator|*
name|accel_strs
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
operator|*
name|prog_strs
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
operator|*
name|time_ints
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|matched
operator|=
name|g_slist_reverse
argument_list|(
name|matched
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|matched
operator|,
name|i
operator|=
literal|0
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
operator|,
name|i
operator|++
control|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
init|=
name|list
operator|->
name|data
decl_stmt|;
operator|(
operator|*
name|procedure_strs
operator|)
index|[
name|i
index|]
operator|=
name|g_strdup
argument_list|(
name|gimp_object_get_name
argument_list|(
name|proc
argument_list|)
argument_list|)
expr_stmt|;
operator|(
operator|*
name|accel_strs
operator|)
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
operator|(
operator|*
name|prog_strs
operator|)
index|[
name|i
index|]
operator|=
name|g_file_get_path
argument_list|(
name|proc
operator|->
name|file
argument_list|)
expr_stmt|;
operator|(
operator|*
name|time_ints
operator|)
index|[
name|i
index|]
operator|=
name|proc
operator|->
name|mtime
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|matched
argument_list|)
expr_stmt|;
if|if
condition|(
name|sregex
condition|)
name|g_regex_unref
argument_list|(
name|sregex
argument_list|)
expr_stmt|;
return|return
name|num_plugins
return|;
block|}
end_function

end_unit

