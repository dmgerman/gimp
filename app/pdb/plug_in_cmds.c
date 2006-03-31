begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
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
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-def.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-params.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc-def.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-ins-query.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-ins.h"
end_include

begin_decl_stmt
DECL|variable|plugins_query_proc
specifier|static
name|ProcRecord
name|plugins_query_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_domain_register_proc
specifier|static
name|ProcRecord
name|plugin_domain_register_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_help_register_proc
specifier|static
name|ProcRecord
name|plugin_help_register_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_menu_register_proc
specifier|static
name|ProcRecord
name|plugin_menu_register_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_menu_branch_register_proc
specifier|static
name|ProcRecord
name|plugin_menu_branch_register_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plugin_icon_register_proc
specifier|static
name|ProcRecord
name|plugin_icon_register_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_plug_in_procs (Gimp * gimp)
name|register_plug_in_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|ProcRecord
modifier|*
name|procedure
decl_stmt|;
comment|/*    * plugins_query    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|plugins_query_proc
argument_list|,
literal|1
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"search-string"
argument_list|,
literal|"search string"
argument_list|,
literal|"If not an empty string then use this as a search pattern"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|GIMP_PARAM_NO_VALIDATE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"num-plugins"
argument_list|,
literal|"num plugins"
argument_list|,
literal|"The number of plugins"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRINGARRAY
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"menu-path"
argument_list|,
literal|"menu path"
argument_list|,
literal|"The menu path of the plugin"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"num-plugins"
argument_list|,
literal|"num plugins"
argument_list|,
literal|"The number of plugins"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRINGARRAY
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"plugin-accelerator"
argument_list|,
literal|"plugin accelerator"
argument_list|,
literal|"String representing keyboard accelerator (could be empty string)"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"num-plugins"
argument_list|,
literal|"num plugins"
argument_list|,
literal|"The number of plugins"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRINGARRAY
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"plugin-location"
argument_list|,
literal|"plugin location"
argument_list|,
literal|"Location of the plugin program"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"num-plugins"
argument_list|,
literal|"num plugins"
argument_list|,
literal|"The number of plugins"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRINGARRAY
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"plugin-image-type"
argument_list|,
literal|"plugin image type"
argument_list|,
literal|"Type of image that this plugin will work on"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"num-plugins"
argument_list|,
literal|"num plugins"
argument_list|,
literal|"The number of plugins"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32ARRAY
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"plugin-install-time"
argument_list|,
literal|"plugin install time"
argument_list|,
literal|"Time that the plugin was installed"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"num-plugins"
argument_list|,
literal|"num plugins"
argument_list|,
literal|"The number of plugins"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRINGARRAY
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"plugin-real-name"
argument_list|,
literal|"plugin real name"
argument_list|,
literal|"The internal name of the plugin"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * plugin_domain_register    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|plugin_domain_register_proc
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"domain-name"
argument_list|,
literal|"domain name"
argument_list|,
literal|"The name of the textdomain (must be unique)"
argument_list|,
name|FALSE
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
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"domain-path"
argument_list|,
literal|"domain path"
argument_list|,
literal|"The absolute path to the compiled message catalog (may be NULL)"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|GIMP_PARAM_NO_VALIDATE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * plugin_help_register    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|plugin_help_register_proc
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"domain-name"
argument_list|,
literal|"domain name"
argument_list|,
literal|"The XML namespace of the plug-in's help pages"
argument_list|,
name|FALSE
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
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"domain-uri"
argument_list|,
literal|"domain uri"
argument_list|,
literal|"The root URI of the plug-in's help pages"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * plugin_menu_register    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|plugin_menu_register_proc
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"procedure-name"
argument_list|,
literal|"procedure name"
argument_list|,
literal|"The procedure for which to install the menu path"
argument_list|,
name|FALSE
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
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"menu-path"
argument_list|,
literal|"menu path"
argument_list|,
literal|"The procedure's additional menu path"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * plugin_menu_branch_register    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|plugin_menu_branch_register_proc
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"menu-path"
argument_list|,
literal|"menu path"
argument_list|,
literal|"The sub-menu's menu path"
argument_list|,
name|FALSE
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
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"menu-name"
argument_list|,
literal|"menu name"
argument_list|,
literal|"The name of the sub-menu"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * plugin_icon_register    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|plugin_icon_register_proc
argument_list|,
literal|4
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"procedure-name"
argument_list|,
literal|"procedure name"
argument_list|,
literal|"The procedure for which to install the icon"
argument_list|,
name|FALSE
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
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"icon-type"
argument_list|,
literal|"icon type"
argument_list|,
literal|"The type of the icon: { GIMP_ICON_TYPE_STOCK_ID (0), GIMP_ICON_TYPE_INLINE_PIXBUF (1), GIMP_ICON_TYPE_IMAGE_FILE (2) }"
argument_list|,
name|GIMP_TYPE_ICON_TYPE
argument_list|,
name|GIMP_ICON_TYPE_STOCK_ID
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"icon-data-length"
argument_list|,
literal|"icon data length"
argument_list|,
literal|"The length of 'icon-data' (1<= icon_data_length)"
argument_list|,
literal|1
argument_list|,
name|G_MAXINT32
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT8ARRAY
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"icon-data"
argument_list|,
literal|"icon data"
argument_list|,
literal|"The procedure's icon. The format depends on the 'icon_type' parameter"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plugins_query_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|plugins_query_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|search_string
decl_stmt|;
name|gint32
name|num_plugins
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|menu_path
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|plugin_accelerator
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|plugin_location
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|plugin_image_type
init|=
name|NULL
decl_stmt|;
name|gint32
modifier|*
name|plugin_install_time
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|plugin_real_name
init|=
name|NULL
decl_stmt|;
name|search_string
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|num_plugins
operator|=
name|plug_ins_query
argument_list|(
name|gimp
argument_list|,
name|search_string
argument_list|,
operator|&
name|menu_path
argument_list|,
operator|&
name|plugin_accelerator
argument_list|,
operator|&
name|plugin_location
argument_list|,
operator|&
name|plugin_image_type
argument_list|,
operator|&
name|plugin_real_name
argument_list|,
operator|&
name|plugin_install_time
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|g_value_set_pointer
argument_list|(
operator|&
name|return_vals
index|[
literal|2
index|]
operator|.
name|value
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|3
index|]
operator|.
name|value
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|g_value_set_pointer
argument_list|(
operator|&
name|return_vals
index|[
literal|4
index|]
operator|.
name|value
argument_list|,
name|plugin_accelerator
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|5
index|]
operator|.
name|value
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|g_value_set_pointer
argument_list|(
operator|&
name|return_vals
index|[
literal|6
index|]
operator|.
name|value
argument_list|,
name|plugin_location
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|7
index|]
operator|.
name|value
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|g_value_set_pointer
argument_list|(
operator|&
name|return_vals
index|[
literal|8
index|]
operator|.
name|value
argument_list|,
name|plugin_image_type
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|9
index|]
operator|.
name|value
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|g_value_set_pointer
argument_list|(
operator|&
name|return_vals
index|[
literal|10
index|]
operator|.
name|value
argument_list|,
name|plugin_install_time
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|11
index|]
operator|.
name|value
argument_list|,
name|num_plugins
argument_list|)
expr_stmt|;
name|g_value_set_pointer
argument_list|(
operator|&
name|return_vals
index|[
literal|12
index|]
operator|.
name|value
argument_list|,
name|plugin_real_name
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|plugins_query_proc
specifier|static
name|ProcRecord
name|plugins_query_proc
init|=
block|{
name|TRUE
block|,
literal|"gimp-plugins-query"
block|,
literal|"gimp-plugins-query"
block|,
literal|"Queries the plugin database for its contents."
block|,
literal|"This procedure queries the contents of the plugin database."
block|,
literal|"Andy Thomas"
block|,
literal|"Andy Thomas"
block|,
literal|"1998"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|plugins_query_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plugin_domain_register_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|plugin_domain_register_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|domain_name
decl_stmt|;
name|gchar
modifier|*
name|domain_path
decl_stmt|;
name|domain_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|domain_path
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
operator|&&
name|gimp
operator|->
name|current_plug_in
operator|->
name|query
condition|)
block|{
name|plug_in_def_set_locale_domain_name
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|plug_in_def
argument_list|,
name|domain_name
argument_list|)
expr_stmt|;
name|plug_in_def_set_locale_domain_path
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|plug_in_def
argument_list|,
name|domain_path
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
name|proc_record
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|plugin_domain_register_proc
specifier|static
name|ProcRecord
name|plugin_domain_register_proc
init|=
block|{
name|TRUE
block|,
literal|"gimp-plugin-domain-register"
block|,
literal|"gimp-plugin-domain-register"
block|,
literal|"Registers a textdomain for localisation."
block|,
literal|"This procedure adds a textdomain to the list of domains Gimp searches for strings when translating its menu entries. There is no need to call this function for plug-ins that have their strings included in the gimp-std-plugins domain as that is used by default. If the compiled message catalog is not in the standard location, you may specify an absolute path to another location. This procedure can only be called in the query function of a plug-in and it has to be called before any procedure is installed."
block|,
literal|"Sven Neumann<sven@gimp.org>"
block|,
literal|"Sven Neumann"
block|,
literal|"2000"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|plugin_domain_register_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plugin_help_register_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|plugin_help_register_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|domain_name
decl_stmt|;
name|gchar
modifier|*
name|domain_uri
decl_stmt|;
name|domain_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|domain_uri
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
operator|&&
name|gimp
operator|->
name|current_plug_in
operator|->
name|query
condition|)
block|{
name|plug_in_def_set_help_domain_name
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|plug_in_def
argument_list|,
name|domain_name
argument_list|)
expr_stmt|;
name|plug_in_def_set_help_domain_uri
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|plug_in_def
argument_list|,
name|domain_uri
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
name|proc_record
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|plugin_help_register_proc
specifier|static
name|ProcRecord
name|plugin_help_register_proc
init|=
block|{
name|TRUE
block|,
literal|"gimp-plugin-help-register"
block|,
literal|"gimp-plugin-help-register"
block|,
literal|"Register a help path for a plug-in."
block|,
literal|"This procedure changes the help rootdir for the plug-in which calls it. All subsequent calls of gimp_help from this plug-in will be interpreted relative to this rootdir."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer"
block|,
literal|"2000"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|plugin_help_register_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plugin_menu_register_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|plugin_menu_register_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|procedure_name
decl_stmt|;
name|gchar
modifier|*
name|menu_path
decl_stmt|;
name|procedure_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|menu_path
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
condition|)
block|{
name|gchar
modifier|*
name|canonical
init|=
name|gimp_canonicalize_identifier
argument_list|(
name|procedure_name
argument_list|)
decl_stmt|;
name|success
operator|=
name|plug_in_menu_register
argument_list|(
name|gimp
operator|->
name|current_plug_in
argument_list|,
name|canonical
argument_list|,
name|menu_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|canonical
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|plugin_menu_register_proc
specifier|static
name|ProcRecord
name|plugin_menu_register_proc
init|=
block|{
name|TRUE
block|,
literal|"gimp-plugin-menu-register"
block|,
literal|"gimp-plugin-menu-register"
block|,
literal|"Register an additional menu path for a plug-in procedure."
block|,
literal|"This procedure installs an additional menu entry for the given procedure."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer"
block|,
literal|"2004"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|plugin_menu_register_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plugin_menu_branch_register_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|plugin_menu_branch_register_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|menu_path
decl_stmt|;
name|gchar
modifier|*
name|menu_name
decl_stmt|;
name|menu_path
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|menu_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
condition|)
block|{
name|plug_ins_menu_branch_add
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|current_plug_in
operator|->
name|prog
argument_list|,
name|menu_path
argument_list|,
name|menu_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp
operator|->
name|no_interface
condition|)
block|{
name|gimp_menus_create_branch
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|current_plug_in
operator|->
name|prog
argument_list|,
name|menu_path
argument_list|,
name|menu_name
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
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
name|proc_record
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|plugin_menu_branch_register_proc
specifier|static
name|ProcRecord
name|plugin_menu_branch_register_proc
init|=
block|{
name|TRUE
block|,
literal|"gimp-plugin-menu-branch-register"
block|,
literal|"gimp-plugin-menu-branch-register"
block|,
literal|"Register a sub-menu."
block|,
literal|"This procedure installs an sub-menu which does not belong to any procedure."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|plugin_menu_branch_register_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|plugin_icon_register_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|plugin_icon_register_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|procedure_name
decl_stmt|;
name|gint32
name|icon_type
decl_stmt|;
name|gint32
name|icon_data_length
decl_stmt|;
name|guint8
modifier|*
name|icon_data
decl_stmt|;
name|procedure_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|icon_type
operator|=
name|g_value_get_enum
argument_list|(
operator|&
name|args
index|[
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|icon_data_length
operator|=
name|g_value_get_int
argument_list|(
operator|&
name|args
index|[
literal|2
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|icon_data
operator|=
name|g_value_get_pointer
argument_list|(
operator|&
name|args
index|[
literal|3
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
operator|&&
name|gimp
operator|->
name|current_plug_in
operator|->
name|query
condition|)
block|{
name|PlugInProcDef
modifier|*
name|proc_def
decl_stmt|;
name|gchar
modifier|*
name|canonical
decl_stmt|;
name|canonical
operator|=
name|gimp_canonicalize_identifier
argument_list|(
name|procedure_name
argument_list|)
expr_stmt|;
name|proc_def
operator|=
name|plug_in_proc_def_find
argument_list|(
name|gimp
operator|->
name|current_plug_in
operator|->
name|plug_in_def
operator|->
name|proc_defs
argument_list|,
name|canonical
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|canonical
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_def
condition|)
name|plug_in_proc_def_set_icon
argument_list|(
name|proc_def
argument_list|,
name|icon_type
argument_list|,
name|icon_data
argument_list|,
name|icon_data_length
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
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
name|proc_record
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|plugin_icon_register_proc
specifier|static
name|ProcRecord
name|plugin_icon_register_proc
init|=
block|{
name|TRUE
block|,
literal|"gimp-plugin-icon-register"
block|,
literal|"gimp-plugin-icon-register"
block|,
literal|"Register an icon for a plug-in procedure."
block|,
literal|"This procedure installs an icon for the given procedure."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer"
block|,
literal|"2004"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|plugin_icon_register_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

