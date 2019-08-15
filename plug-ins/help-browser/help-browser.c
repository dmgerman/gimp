begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help Browser  * Copyright (C) 1999-2008 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * Some code& ideas taken from the GNOME help browser.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
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

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-help-browser"
end_define

begin_typedef
DECL|typedef|HelpBrowser
typedef|typedef
name|struct
name|_HelpBrowser
name|HelpBrowser
typedef|;
end_typedef

begin_typedef
DECL|typedef|HelpBrowserClass
typedef|typedef
name|struct
name|_HelpBrowserClass
name|HelpBrowserClass
typedef|;
end_typedef

begin_struct
DECL|struct|_HelpBrowser
struct|struct
name|_HelpBrowser
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_HelpBrowserClass
struct|struct
name|_HelpBrowserClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|HELP_BROWSER_TYPE
define|#
directive|define
name|HELP_BROWSER_TYPE
value|(help_browser_get_type ())
end_define

begin_define
DECL|macro|HELP_BROWSER
define|#
directive|define
name|HELP_BROWSER
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), HELP_BROWSER_TYPE, HelpBrowser))
end_define

begin_decl_stmt
name|GType
name|help_browser_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|GList
modifier|*
name|help_browser_query_procedures
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
name|help_browser_create_procedure
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
name|help_browser_run
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
name|temp_proc_install
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|temp_proc_run
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

begin_macro
DECL|function|G_DEFINE_TYPE (HelpBrowser,help_browser,GIMP_TYPE_PLUG_IN)
name|G_DEFINE_TYPE
argument_list|(
argument|HelpBrowser
argument_list|,
argument|help_browser
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|HELP_BROWSER_TYPE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|help_browser_class_init
parameter_list|(
name|HelpBrowserClass
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
name|help_browser_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|help_browser_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|help_browser_init (HelpBrowser * help_browser)
name|help_browser_init
parameter_list|(
name|HelpBrowser
modifier|*
name|help_browser
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|help_browser_query_procedures (GimpPlugIn * plug_in)
name|help_browser_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
return|return
name|g_list_append
argument_list|(
name|NULL
argument_list|,
name|g_strdup
argument_list|(
name|GIMP_HELP_BROWSER_EXT_PROC
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProcedure
modifier|*
DECL|function|help_browser_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|help_browser_create_procedure
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
name|GIMP_HELP_BROWSER_EXT_PROC
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
name|help_browser_run
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Browse the GIMP user manual"
argument_list|,
literal|"A small and simple HTML browser "
literal|"optimized for browsing the GIMP "
literal|"user manual."
argument_list|,
name|GIMP_HELP_BROWSER_EXT_PROC
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Sven Neumann<sven@gimp.org>, "
literal|"Michael Natterer<mitch@gimp.org>"
literal|"Henrik Brix Andersen<brix@gimp.org>"
argument_list|,
literal|"Sven Neumann, Michael Natterer& "
literal|"Henrik Brix Andersen"
argument_list|,
literal|"1999-2008"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"run-mode"
argument_list|,
literal|"Run mode"
argument_list|,
literal|"The run mode"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"num-domain-names"
argument_list|,
literal|"Num domain names"
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
literal|"Domain names"
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
name|g_param_spec_int
argument_list|(
literal|"num-domain-uris"
argument_list|,
literal|"Num domain URIs"
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
DECL|function|help_browser_run (GimpProcedure * procedure,const GimpValueArray * args,gpointer run_data)
name|help_browser_run
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
name|INIT_I18N
argument_list|()
expr_stmt|;
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
literal|1
argument_list|)
argument_list|)
argument_list|,
name|gimp_value_get_string_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|)
argument_list|,
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
argument_list|,
name|gimp_value_get_string_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|4
argument_list|)
argument_list|)
argument_list|)
condition|)
block|{
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|NULL
argument_list|)
return|;
block|}
name|browser_dialog_open
argument_list|(
name|PLUG_IN_BINARY
argument_list|)
expr_stmt|;
name|temp_proc_install
argument_list|(
name|gimp_procedure_get_plug_in
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_extension_ready
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|gimp_plug_in_extension_enable
argument_list|(
name|gimp_procedure_get_plug_in
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_SUCCESS
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|temp_proc_install (GimpPlugIn * plug_in)
name|temp_proc_install
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
name|GIMP_HELP_BROWSER_TEMP_EXT_PROC
argument_list|,
name|GIMP_TEMPORARY
argument_list|,
name|temp_proc_run
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"DON'T USE THIS ONE"
argument_list|,
literal|"(Temporary procedure)"
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
literal|"Henrik Brix Andersen<brix@gimp.org>"
argument_list|,
literal|"Sven Neumann, Michael Natterer& "
literal|"Henrik Brix Andersen"
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
literal|"help-domain"
argument_list|,
literal|"Help domain"
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
literal|"Help locales"
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
literal|"Help ID"
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
DECL|function|temp_proc_run (GimpProcedure * procedure,const GimpValueArray * args,gpointer run_data)
name|temp_proc_run
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
specifier|const
name|gchar
modifier|*
name|string
decl_stmt|;
name|string
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
name|string
operator|&&
name|strlen
argument_list|(
name|string
argument_list|)
condition|)
name|help_domain
operator|=
name|string
expr_stmt|;
name|string
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
name|string
operator|&&
name|strlen
argument_list|(
name|string
argument_list|)
condition|)
name|help_locales
operator|=
name|string
expr_stmt|;
name|string
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
name|string
operator|&&
name|strlen
argument_list|(
name|string
argument_list|)
condition|)
name|help_id
operator|=
name|string
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
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_SUCCESS
argument_list|,
name|NULL
argument_list|)
return|;
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

