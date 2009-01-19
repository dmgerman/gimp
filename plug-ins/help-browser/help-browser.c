begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help Browser  * Copyright (C) 1999-2008 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * Some code& ideas taken from the GNOME help browser.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
comment|/*  strlen, strcmp  */
end_comment

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"plug-ins/help/gimphelp.h"
end_include

begin_include
include|#
directive|include
file|"dialog.h"
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
DECL|macro|GIMP_HELP_BROWSER_EXT_PROC
define|#
directive|define
name|GIMP_HELP_BROWSER_EXT_PROC
value|"extension-gimp-help-browser"
end_define

begin_define
DECL|macro|GIMP_HELP_BROWSER_TEMP_EXT_PROC
define|#
directive|define
name|GIMP_HELP_BROWSER_TEMP_EXT_PROC
value|"extension-gimp-help-browser-temp"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"help-browser"
end_define

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
name|gboolean
name|help_browser_show_help
parameter_list|(
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
name|GimpHelpProgress
modifier|*
name|help_browser_progress_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  local variables  */
end_comment

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
literal|"run-mode"
block|,
literal|"The run mode { RUN-INTERACTIVE (0) }"
block|}
block|,
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
name|GIMP_HELP_BROWSER_EXT_PROC
argument_list|,
literal|"Browse the GIMP user manual"
argument_list|,
literal|"A small and simple HTML browser optimized for "
literal|"browsing the GIMP user manual."
argument_list|,
literal|"Sven Neumann<sven@gimp.org>, "
literal|"Michael Natterer<mitch@gimp.org>"
literal|"Henrik Brix Andersen<brix@gimp.org>"
argument_list|,
literal|"Sven Neumann, Michael Natterer& Henrik Brix Andersen"
argument_list|,
literal|"1999-2008"
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
name|GimpRunMode
name|run_mode
init|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
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
name|INIT_I18N
argument_list|()
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|>=
literal|1
condition|)
block|{
if|if
condition|(
name|nparams
operator|==
literal|5
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_help_init
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_stringarray
argument_list|,
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|param
index|[
literal|4
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
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|browser_dialog_open
argument_list|(
name|PLUG_IN_BINARY
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
name|gtk_main
argument_list|()
expr_stmt|;
block|}
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
break|break;
default|default:
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
block|}
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
name|GIMP_HELP_BROWSER_TEMP_EXT_PROC
argument_list|,
literal|"DON'T USE THIS ONE"
argument_list|,
literal|"(Temporary procedure)"
argument_list|,
literal|"Sven Neumann<sven@gimp.org>, "
literal|"Michael Natterer<mitch@gimp.org>"
literal|"Henrik Brix Andersen<brix@gimp.org>"
argument_list|,
literal|"Sven Neumann, Michael Natterer& Henrik Brix Andersen"
argument_list|,
literal|"1999-2008"
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
literal|3
condition|)
block|{
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
name|help_domain
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
name|help_locales
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
name|help_id
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
operator|!
name|help_browser_show_help
argument_list|(
name|help_domain
argument_list|,
name|help_locales
argument_list|,
name|help_id
argument_list|)
condition|)
block|{
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
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
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|help_browser_show_help (const gchar * help_domain,const gchar * help_locales,const gchar * help_id)
name|help_browser_show_help
parameter_list|(
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
name|GimpHelpDomain
modifier|*
name|domain
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|domain
operator|=
name|gimp_help_lookup_domain
argument_list|(
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
name|GimpHelpLocale
modifier|*
name|locale
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
name|help_browser_progress_new
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
name|help_id
argument_list|,
name|progress
argument_list|,
operator|&
name|locale
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
name|uri
condition|)
block|{
name|browser_dialog_make_index
argument_list|(
name|domain
argument_list|,
name|locale
argument_list|)
expr_stmt|;
name|browser_dialog_load
argument_list|(
name|uri
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
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
return|return
name|success
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|help_browser_progress_start (const gchar * message,gboolean cancelable,gpointer user_data)
name|help_browser_progress_start
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
DECL|function|help_browser_progress_update (gdouble value,gpointer user_data)
name|help_browser_progress_update
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
DECL|function|help_browser_progress_end (gpointer user_data)
name|help_browser_progress_end
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
DECL|function|help_browser_progress_new (void)
name|help_browser_progress_new
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
name|help_browser_progress_start
block|,
name|help_browser_progress_end
block|,
name|help_browser_progress_update
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

