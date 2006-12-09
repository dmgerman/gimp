begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2004 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
typedef|typedef
struct|struct
DECL|struct|__anon28b23b2d0108
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

begin_function_decl
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
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
name|param
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|temp_proc_install
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|temp_proc_run
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
name|param
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|load_help
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
name|load_help_idle
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  local variables  */
end_comment

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

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"num-domain-names"
block|,
literal|""
block|}
block|,
block|{
name|GIMP_PDB_STRINGARRAY
block|,
literal|"domain-names"
block|,
literal|""
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"num-domain-uris"
block|,
literal|""
block|}
block|,
block|{
name|GIMP_PDB_STRINGARRAY
block|,
literal|"domain-uris"
block|,
literal|""
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|GIMP_HELP_EXT_PROC
argument_list|,
literal|""
argument_list|,
comment|/* FIXME */
literal|""
argument_list|,
comment|/* FIXME */
literal|"Sven Neumann<sven@gimp.org>, "
literal|"Michael Natterer<mitch@gimp.org>, "
literal|"Henrik Brix Andersen<brix@gimp.org>"
argument_list|,
literal|"Sven Neumann, Michael Natterer& Henrik Brix Andersen"
argument_list|,
literal|"1999-2004"
argument_list|,
name|NULL
argument_list|,
literal|""
argument_list|,
name|GIMP_EXTENSION
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
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
name|param
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
name|nparams
operator|==
literal|4
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_help_init
argument_list|(
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_stringarray
argument_list|,
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_stringarray
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
name|main_loop
operator|=
name|g_main_loop_new
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|temp_proc_install
argument_list|()
expr_stmt|;
name|gimp_extension_ack
argument_list|()
expr_stmt|;
name|gimp_extension_enable
argument_list|()
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
name|gimp_uninstall_temp_proc
argument_list|(
name|GIMP_HELP_TEMP_EXT_PROC
argument_list|)
expr_stmt|;
block|}
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
name|status
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

begin_function
specifier|static
name|void
DECL|function|temp_proc_install (void)
name|temp_proc_install
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"procedure"
block|,
literal|"The procedure of the browser to use"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"help-domain"
block|,
literal|"Help domain to use"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"help-locales"
block|,
literal|"Language to use"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"help-id"
block|,
literal|"Help ID to open"
block|}
block|}
decl_stmt|;
name|gimp_install_temp_proc
argument_list|(
name|GIMP_HELP_TEMP_EXT_PROC
argument_list|,
literal|"DON'T USE THIS ONE"
argument_list|,
literal|"(Temporary procedure)"
argument_list|,
literal|"Sven Neumann<sven@gimp.org>, "
literal|"Michael Natterer<mitch@gimp.org>"
literal|"Henrik Brix Andersen<brix@gimp.org"
argument_list|,
literal|"Sven Neumann, Michael Natterer& Henrik Brix Andersen"
argument_list|,
literal|"1999-2004"
argument_list|,
name|NULL
argument_list|,
literal|""
argument_list|,
name|GIMP_TEMPORARY
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|,
name|temp_proc_run
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|temp_proc_run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|temp_proc_run
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
name|param
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
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|procedure
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
comment|/*  make sure all the arguments are there  */
if|if
condition|(
name|nparams
operator|==
literal|4
condition|)
block|{
if|if
condition|(
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_string
operator|&&
name|strlen
argument_list|(
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
condition|)
name|procedure
operator|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
if|if
condition|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
operator|&&
name|strlen
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
condition|)
name|help_domain
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
if|if
condition|(
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_string
operator|&&
name|strlen
argument_list|(
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
condition|)
name|help_locales
operator|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
if|if
condition|(
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
operator|&&
name|strlen
argument_list|(
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
condition|)
name|help_id
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|procedure
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
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
name|status
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|load_help
argument_list|(
name|procedure
argument_list|,
name|help_domain
argument_list|,
name|help_locales
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|load_help (const gchar * procedure,const gchar * help_domain,const gchar * help_locales,const gchar * help_id)
name|load_help
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
decl_stmt|;
name|idle_help
operator|=
name|g_new0
argument_list|(
name|IdleHelp
argument_list|,
literal|1
argument_list|)
expr_stmt|;
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
name|load_help_idle
argument_list|,
name|idle_help
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|load_help_idle (gpointer data)
name|load_help_idle
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
name|GList
modifier|*
name|locales
init|=
name|gimp_help_parse_locales
argument_list|(
name|idle_help
operator|->
name|help_locales
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|full_uri
decl_stmt|;
name|gboolean
name|fatal_error
decl_stmt|;
name|full_uri
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
name|NULL
argument_list|,
operator|&
name|fatal_error
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|locales
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|locales
argument_list|)
expr_stmt|;
if|if
condition|(
name|full_uri
condition|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|n_return_vals
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
name|full_uri
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
name|idle_help
operator|->
name|procedure
argument_list|,
operator|&
name|n_return_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|full_uri
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|n_return_vals
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|full_uri
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
name|g_free
argument_list|(
name|idle_help
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit

