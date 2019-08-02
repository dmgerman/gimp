begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2008 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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

begin_comment
comment|/*  strlen  */
end_comment

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_define
DECL|macro|GIMP_DISABLE_COMPAT_CRUFT
define|#
directive|define
name|GIMP_DISABLE_COMPAT_CRUFT
end_define

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/*  defines  */
end_comment

begin_define
DECL|macro|GIMP_HELP_EXT_PROC
define|#
directive|define
name|GIMP_HELP_EXT_PROC
value|"extension-gimp-help"
end_define

begin_define
DECL|macro|GIMP_HELP_TEMP_EXT_PROC
define|#
directive|define
name|GIMP_HELP_TEMP_EXT_PROC
value|"extension-gimp-help-temp"
end_define

begin_typedef
DECL|typedef|Help
typedef|typedef
name|struct
name|_Help
name|Help
typedef|;
end_typedef

begin_typedef
DECL|typedef|HelpClass
typedef|typedef
name|struct
name|_HelpClass
name|HelpClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Help
struct|struct
name|_Help
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_HelpClass
struct|struct
name|_HelpClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2ac6e02d0108
block|{
DECL|member|procedure
name|gchar
modifier|*
name|procedure
decl_stmt|;
DECL|member|help_domain
name|gchar
modifier|*
name|help_domain
decl_stmt|;
DECL|member|help_locales
name|gchar
modifier|*
name|help_locales
decl_stmt|;
DECL|member|help_id
name|gchar
modifier|*
name|help_id
decl_stmt|;
DECL|typedef|IdleHelp
block|}
name|IdleHelp
typedef|;
end_typedef

begin_comment
comment|/*  forward declarations  */
end_comment

begin_define
DECL|macro|HELP_TYPE
define|#
directive|define
name|HELP_TYPE
value|(help_get_type ())
end_define

begin_define
DECL|macro|HELP
define|#
directive|define
name|HELP
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), HELP_TYPE, Help))
end_define

begin_decl_stmt
name|GType
name|help_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|gchar
modifier|*
modifier|*
name|help_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpProcedure
modifier|*
name|help_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|help_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|help_temp_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|help_temp_proc_install
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|help_load
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_locales
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|help_load_idle
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpHelpProgress
modifier|*
name|help_load_progress_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|main_loop
specifier|static
name|GMainLoop
modifier|*
name|main_loop
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|G_DEFINE_TYPE (Help,help,GIMP_TYPE_PLUG_IN)
name|G_DEFINE_TYPE
argument_list|(
argument|Help
argument_list|,
argument|help
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|HELP_TYPE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|help_class_init
parameter_list|(
name|HelpClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPlugInClass
modifier|*
name|plug_in_class
init|=
name|GIMP_PLUG_IN_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|plug_in_class
operator|->
name|query_procedures
operator|=
name|help_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|help_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|help_init (Help * help)
name|help_init
parameter_list|(
name|Help
modifier|*
name|help
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gchar
modifier|*
modifier|*
DECL|function|help_query_procedures (GimpPlugIn * plug_in)
name|help_query_procedures
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
init|=
name|g_new0
argument_list|(
name|gchar
operator|*
argument_list|,
literal|2
argument_list|)
decl_stmt|;
name|procedures
index|[
literal|0
index|]
operator|=
name|g_strdup
argument_list|(
name|GIMP_HELP_EXT_PROC
argument_list|)
expr_stmt|;
return|return
name|procedures
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProcedure
modifier|*
DECL|function|help_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|help_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|GIMP_HELP_EXT_PROC
argument_list|)
condition|)
block|{
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|name
argument_list|,
name|GIMP_EXTENSION
argument_list|,
name|help_run
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Sven Neumann<sven@gimp.org>, "
literal|"Michael Natterer<mitch@gimp.org>, "
literal|"Henrik Brix Andersen<brix@gimp.org>"
argument_list|,
literal|"Sven Neumann, Michael Natterer& Henrik Brix Andersen"
argument_list|,
literal|"1999-2008"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-domain-names"
argument_list|,
literal|"Num Domain Names"
argument_list|,
literal|"Num domain names"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string_array
argument_list|(
literal|"domain-names"
argument_list|,
literal|"Domain Names"
argument_list|,
literal|"Domain names"
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-domain-uris"
argument_list|,
literal|"Num Domain URIs"
argument_list|,
literal|"Num domain URIs"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string_array
argument_list|(
literal|"domain-uris"
argument_list|,
literal|"Domain URIs"
argument_list|,
literal|"Domain URIs"
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|procedure
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|help_run (GimpProcedure * procedure,const GimpValueArray * args,gpointer run_data)
name|help_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
block|{
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*  make sure all the arguments are there  */
if|if
condition|(
name|gimp_value_array_length
argument_list|(
name|args
argument_list|)
operator|==
literal|4
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_help_init
argument_list|(
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
argument_list|,
name|gimp_value_get_string_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
argument_list|,
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|)
argument_list|,
name|gimp_value_get_string_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
argument_list|)
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"help: wrong number of arguments in procedure call.\n"
argument_list|)
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp_procedure_get_plug_in
argument_list|(
name|procedure
argument_list|)
decl_stmt|;
name|main_loop
operator|=
name|g_main_loop_new
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|help_temp_proc_install
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|gimp_procedure_extension_ready
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|gimp_plug_in_extension_enable
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|g_main_loop_run
argument_list|(
name|main_loop
argument_list|)
expr_stmt|;
name|g_main_loop_unref
argument_list|(
name|main_loop
argument_list|)
expr_stmt|;
name|main_loop
operator|=
name|NULL
expr_stmt|;
name|gimp_plug_in_remove_temp_procedure
argument_list|(
name|plug_in
argument_list|,
name|GIMP_HELP_TEMP_EXT_PROC
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|status
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|help_temp_proc_install (GimpPlugIn * plug_in)
name|help_temp_proc_install
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|GIMP_HELP_TEMP_EXT_PROC
argument_list|,
name|GIMP_TEMPORARY
argument_list|,
name|help_temp_run
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Sven Neumann<sven@gimp.org>, "
literal|"Michael Natterer<mitch@gimp.org>"
literal|"Henrik Brix Andersen<brix@gimp.org"
argument_list|,
literal|"Sven Neumann, Michael Natterer& Henrik Brix Andersen"
argument_list|,
literal|"1999-2008"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"help-proc"
argument_list|,
literal|"The procedure of the browser to use"
argument_list|,
literal|"The procedure of the browser to use"
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"help-domain"
argument_list|,
literal|"Help domain to use"
argument_list|,
literal|"Help domain to use"
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"help-locales"
argument_list|,
literal|"Language to use"
argument_list|,
literal|"Language to use"
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"help-id"
argument_list|,
literal|"Help ID to open"
argument_list|,
literal|"Help ID to open"
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_add_temp_procedure
argument_list|(
name|plug_in
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

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|help_temp_run (GimpProcedure * procedure,const GimpValueArray * args,gpointer run_data)
name|help_temp_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
block|{
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|help_proc
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|help_domain
init|=
name|GIMP_HELP_DEFAULT_DOMAIN
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|help_locales
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|help_id
init|=
name|GIMP_HELP_DEFAULT_ID
decl_stmt|;
comment|/*  make sure all the arguments are there  */
if|if
condition|(
name|gimp_value_array_length
argument_list|(
name|args
argument_list|)
operator|==
literal|4
condition|)
block|{
if|if
condition|(
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
condition|)
name|help_proc
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
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
condition|)
name|help_domain
operator|=
name|g_value_get_string
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
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|)
condition|)
name|help_locales
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
condition|)
name|help_id
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|help_proc
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|help_load
argument_list|(
name|help_proc
argument_list|,
name|help_domain
argument_list|,
name|help_locales
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|status
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|help_load (const gchar * procedure,const gchar * help_domain,const gchar * help_locales,const gchar * help_id)
name|help_load
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_locales
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|IdleHelp
modifier|*
name|idle_help
init|=
name|g_slice_new
argument_list|(
name|IdleHelp
argument_list|)
decl_stmt|;
name|idle_help
operator|->
name|procedure
operator|=
name|g_strdup
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|idle_help
operator|->
name|help_domain
operator|=
name|g_strdup
argument_list|(
name|help_domain
argument_list|)
expr_stmt|;
name|idle_help
operator|->
name|help_locales
operator|=
name|g_strdup
argument_list|(
name|help_locales
argument_list|)
expr_stmt|;
name|idle_help
operator|->
name|help_id
operator|=
name|g_strdup
argument_list|(
name|help_id
argument_list|)
expr_stmt|;
name|g_idle_add
argument_list|(
name|help_load_idle
argument_list|,
name|idle_help
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|help_load_idle (gpointer data)
name|help_load_idle
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|IdleHelp
modifier|*
name|idle_help
init|=
name|data
decl_stmt|;
name|GimpHelpDomain
modifier|*
name|domain
decl_stmt|;
name|domain
operator|=
name|gimp_help_lookup_domain
argument_list|(
name|idle_help
operator|->
name|help_domain
argument_list|)
expr_stmt|;
if|if
condition|(
name|domain
condition|)
block|{
name|GimpHelpProgress
modifier|*
name|progress
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|locales
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gboolean
name|fatal_error
decl_stmt|;
name|locales
operator|=
name|gimp_help_parse_locales
argument_list|(
name|idle_help
operator|->
name|help_locales
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_str_has_prefix
argument_list|(
name|domain
operator|->
name|help_uri
argument_list|,
literal|"file:"
argument_list|)
condition|)
name|progress
operator|=
name|help_load_progress_new
argument_list|()
expr_stmt|;
name|uri
operator|=
name|gimp_help_domain_map
argument_list|(
name|domain
argument_list|,
name|locales
argument_list|,
name|idle_help
operator|->
name|help_id
argument_list|,
name|progress
argument_list|,
name|NULL
argument_list|,
operator|&
name|fatal_error
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_help_progress_free
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|g_list_free_full
argument_list|(
name|locales
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
ifdef|#
directive|ifdef
name|GIMP_HELP_DEBUG
name|g_printerr
argument_list|(
literal|"help: calling '%s' for '%s'\n"
argument_list|,
name|idle_help
operator|->
name|procedure
argument_list|,
name|uri
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
name|idle_help
operator|->
name|procedure
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|fatal_error
condition|)
block|{
name|g_main_loop_quit
argument_list|(
name|main_loop
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|idle_help
operator|->
name|procedure
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|idle_help
operator|->
name|help_domain
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|idle_help
operator|->
name|help_locales
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|idle_help
operator|->
name|help_id
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|IdleHelp
argument_list|,
name|idle_help
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|help_load_progress_start (const gchar * message,gboolean cancelable,gpointer user_data)
name|help_load_progress_start
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|gimp_progress_init
argument_list|(
name|message
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|help_load_progress_update (gdouble value,gpointer user_data)
name|help_load_progress_update
parameter_list|(
name|gdouble
name|value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|gimp_progress_update
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|help_load_progress_end (gpointer user_data)
name|help_load_progress_end
parameter_list|(
name|gpointer
name|user_data
parameter_list|)
block|{
name|gimp_progress_end
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpHelpProgress
modifier|*
DECL|function|help_load_progress_new (void)
name|help_load_progress_new
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpHelpProgressVTable
name|vtable
init|=
block|{
name|help_load_progress_start
block|,
name|help_load_progress_end
block|,
name|help_load_progress_update
block|}
decl_stmt|;
return|return
name|gimp_help_progress_new
argument_list|(
operator|&
name|vtable
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

