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
file|<string.h>
end_include

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
file|"tinyscheme/scheme.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-types.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-console.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-eval.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-interface.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-scripts.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-server.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-text-console.h"
end_include

begin_include
include|#
directive|include
file|"scheme-wrapper.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-intl.h"
end_include

begin_typedef
DECL|typedef|ScriptFu
typedef|typedef
name|struct
name|_ScriptFu
name|ScriptFu
typedef|;
end_typedef

begin_typedef
DECL|typedef|ScriptFuClass
typedef|typedef
name|struct
name|_ScriptFuClass
name|ScriptFuClass
typedef|;
end_typedef

begin_struct
DECL|struct|_ScriptFu
struct|struct
name|_ScriptFu
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_ScriptFuClass
struct|struct
name|_ScriptFuClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|SCRIPT_FU_TYPE
define|#
directive|define
name|SCRIPT_FU_TYPE
value|(script_fu_get_type ())
end_define

begin_define
DECL|macro|SCRIPT_FU
define|#
directive|define
name|SCRIPT_FU
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SCRIPT_FU_TYPE, ScriptFu))
end_define

begin_decl_stmt
name|GType
name|script_fu_get_type
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
name|script_fu_query_procedures
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
name|script_fu_create_procedure
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
name|script_fu_run
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
name|GList
modifier|*
name|script_fu_search_path
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|script_fu_extension_init
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
name|script_fu_refresh_proc
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

begin_macro
DECL|function|G_DEFINE_TYPE (ScriptFu,script_fu,GIMP_TYPE_PLUG_IN)
name|G_DEFINE_TYPE
argument_list|(
argument|ScriptFu
argument_list|,
argument|script_fu
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|SCRIPT_FU_TYPE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|script_fu_class_init
parameter_list|(
name|ScriptFuClass
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
name|script_fu_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|script_fu_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|script_fu_init (ScriptFu * script_fu)
name|script_fu_init
parameter_list|(
name|ScriptFu
modifier|*
name|script_fu
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|script_fu_query_procedures (GimpPlugIn * plug_in)
name|script_fu_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|gimp_plug_in_set_translation_domain
argument_list|(
name|plug_in
argument_list|,
name|GETTEXT_PACKAGE
literal|"-script-fu"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|g_strdup
argument_list|(
literal|"extension-script-fu"
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|g_strdup
argument_list|(
literal|"plug-in-script-fu-console"
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|g_strdup
argument_list|(
literal|"plug-in-script-fu-text-console"
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|g_strdup
argument_list|(
literal|"plug-in-script-fu-server"
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|g_strdup
argument_list|(
literal|"plug-in-script-fu-eval"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProcedure
modifier|*
DECL|function|script_fu_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|script_fu_create_procedure
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
literal|"extension-script-fu"
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
name|script_fu_run
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
literal|"A scheme interpreter for scripting "
literal|"GIMP operations"
argument_list|,
literal|"More help here later"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1997"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug-in-script-fu-console"
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
name|GIMP_PLUGIN
argument_list|,
name|script_fu_run
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_menu_label
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"_Console"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_menu_path
argument_list|(
name|procedure
argument_list|,
literal|"<Image>/Filters/Development/Script-Fu"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Interactive console for Script-Fu "
literal|"development"
argument_list|)
argument_list|,
literal|"Provides an interface which allows "
literal|"interactive scheme development."
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1997"
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_ENUM
argument_list|(
name|procedure
argument_list|,
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
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug-in-script-fu-text-console"
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
name|GIMP_PLUGIN
argument_list|,
name|script_fu_run
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
literal|"Provides a text console mode for "
literal|"script-fu development"
argument_list|,
literal|"Provides an interface which allows "
literal|"interactive scheme development."
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1997"
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_ENUM
argument_list|(
name|procedure
argument_list|,
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
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug-in-script-fu-server"
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
name|GIMP_PLUGIN
argument_list|,
name|script_fu_run
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_menu_label
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"_Start Server..."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_menu_path
argument_list|(
name|procedure
argument_list|,
literal|"<Image>/Filters/Development/Script-Fu"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Server for remote Script-Fu "
literal|"operation"
argument_list|)
argument_list|,
literal|"Provides a server for remote "
literal|"script-fu operation. NOTE that for "
literal|"security reasons this procedure's "
literal|"API was changed in an incompatible "
literal|"way since GIMP 2.8.12. You now have "
literal|"to pass the IP to listen on as "
literal|"first parameter. Calling this "
literal|"procedure with the old API will "
literal|"fail on purpose."
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1997"
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_ENUM
argument_list|(
name|procedure
argument_list|,
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
expr_stmt|;
name|GIMP_PROC_ARG_STRING
argument_list|(
name|procedure
argument_list|,
literal|"ip"
argument_list|,
literal|"IP"
argument_list|,
literal|"The IP on which to listen for requests"
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"port"
argument_list|,
literal|"Port"
argument_list|,
literal|"The port on which to listen for requests"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_STRING
argument_list|(
name|procedure
argument_list|,
literal|"logfile"
argument_list|,
literal|"Log File"
argument_list|,
literal|"The file to log activity to"
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug-in-script-fu-eval"
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
name|GIMP_PLUGIN
argument_list|,
name|script_fu_run
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
literal|"Evaluate scheme code"
argument_list|,
literal|"Evaluate the code under the scheme "
literal|"interpreter (primarily for batch mode)"
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Manish Singh"
argument_list|,
literal|"Manish Singh"
argument_list|,
literal|"1998"
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_ENUM
argument_list|(
name|procedure
argument_list|,
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
expr_stmt|;
name|GIMP_PROC_ARG_STRING
argument_list|(
name|procedure
argument_list|,
literal|"code"
argument_list|,
literal|"Code"
argument_list|,
literal|"The code to run"
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
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
DECL|function|script_fu_run (GimpProcedure * procedure,const GimpValueArray * args,gpointer run_data)
name|script_fu_run
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
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp_procedure_get_plug_in
argument_list|(
name|procedure
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
init|=
name|gimp_procedure_get_name
argument_list|(
name|procedure
argument_list|)
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|path
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|path
operator|=
name|script_fu_search_path
argument_list|()
expr_stmt|;
comment|/*  Determine before we allow scripts to register themselves    *   whether this is the base, automatically installed script-fu extension    */
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"extension-script-fu"
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/*  Setup auxiliary temporary procedures for the base extension  */
name|script_fu_extension_init
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
comment|/*  Init the interpreter and register scripts */
name|tinyscheme_init
argument_list|(
name|path
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  Init the interpreter  */
name|tinyscheme_init
argument_list|(
name|path
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_value_array_length
argument_list|(
name|args
argument_list|)
operator|>
literal|0
condition|)
name|ts_set_run_mode
argument_list|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Load all of the available scripts  */
name|script_fu_find_scripts
argument_list|(
name|plug_in
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|g_list_free_full
argument_list|(
name|path
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"extension-script-fu"
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/*        *  The main script-fu extension.        */
comment|/*  Acknowledge that the extension is properly initialized  */
name|gimp_procedure_extension_ready
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*  Go into an endless loop  */
while|while
condition|(
name|TRUE
condition|)
name|gimp_plug_in_extension_process
argument_list|(
name|plug_in
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug-in-script-fu-text-console"
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/*        *  The script-fu text console for interactive Scheme development        */
name|return_vals
operator|=
name|script_fu_text_console_run
argument_list|(
name|procedure
argument_list|,
name|args
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug-in-script-fu-console"
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/*        *  The script-fu console for interactive Scheme development        */
name|return_vals
operator|=
name|script_fu_console_run
argument_list|(
name|procedure
argument_list|,
name|args
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug-in-script-fu-server"
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/*        *  The script-fu server for remote operation        */
name|return_vals
operator|=
name|script_fu_server_run
argument_list|(
name|procedure
argument_list|,
name|args
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug-in-script-fu-eval"
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/*        *  A non-interactive "console" (for batch mode)        */
name|return_vals
operator|=
name|script_fu_eval_run
argument_list|(
name|procedure
argument_list|,
name|args
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|return_vals
condition|)
name|return_vals
operator|=
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_SUCCESS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|script_fu_search_path (void)
name|script_fu_search_path
parameter_list|(
name|void
parameter_list|)
block|{
name|gchar
modifier|*
name|path_str
decl_stmt|;
name|GList
modifier|*
name|path
init|=
name|NULL
decl_stmt|;
name|path_str
operator|=
name|gimp_gimprc_query
argument_list|(
literal|"script-fu-path"
argument_list|)
expr_stmt|;
if|if
condition|(
name|path_str
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|path
operator|=
name|gimp_config_path_expand_to_files
argument_list|(
name|path_str
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path_str
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|path
condition|)
block|{
name|g_warning
argument_list|(
literal|"Can't convert script-fu-path to filesystem encoding: %s"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|path
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|script_fu_extension_init (GimpPlugIn * plug_in)
name|script_fu_extension_init
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
name|gimp_plug_in_add_menu_branch
argument_list|(
name|plug_in
argument_list|,
literal|"<Image>/Help"
argument_list|,
name|N_
argument_list|(
literal|"_GIMP Online"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_add_menu_branch
argument_list|(
name|plug_in
argument_list|,
literal|"<Image>/Help"
argument_list|,
name|N_
argument_list|(
literal|"_User Manual"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_add_menu_branch
argument_list|(
name|plug_in
argument_list|,
literal|"<Image>/Filters/Development"
argument_list|,
name|N_
argument_list|(
literal|"_Script-Fu"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_add_menu_branch
argument_list|(
name|plug_in
argument_list|,
literal|"<Image>/Filters/Development/Script-Fu"
argument_list|,
name|N_
argument_list|(
literal|"_Test"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_add_menu_branch
argument_list|(
name|plug_in
argument_list|,
literal|"<Image>/File/Create"
argument_list|,
name|N_
argument_list|(
literal|"_Buttons"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_add_menu_branch
argument_list|(
name|plug_in
argument_list|,
literal|"<Image>/File/Create"
argument_list|,
name|N_
argument_list|(
literal|"_Logos"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_add_menu_branch
argument_list|(
name|plug_in
argument_list|,
literal|"<Image>/File/Create"
argument_list|,
name|N_
argument_list|(
literal|"_Patterns"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_add_menu_branch
argument_list|(
name|plug_in
argument_list|,
literal|"<Image>/File/Create"
argument_list|,
name|N_
argument_list|(
literal|"_Web Page Themes"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_add_menu_branch
argument_list|(
name|plug_in
argument_list|,
literal|"<Image>/File/Create/Web Page Themes"
argument_list|,
name|N_
argument_list|(
literal|"_Alien Glow"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_add_menu_branch
argument_list|(
name|plug_in
argument_list|,
literal|"<Image>/File/Create/Web Page Themes"
argument_list|,
name|N_
argument_list|(
literal|"_Beveled Pattern"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_add_menu_branch
argument_list|(
name|plug_in
argument_list|,
literal|"<Image>/File/Create/Web Page Themes"
argument_list|,
name|N_
argument_list|(
literal|"_Classic.Gimp.Org"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_add_menu_branch
argument_list|(
name|plug_in
argument_list|,
literal|"<Image>/Filters"
argument_list|,
name|N_
argument_list|(
literal|"Alpha to _Logo"
argument_list|)
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plug_in
argument_list|,
literal|"script-fu-refresh"
argument_list|,
name|GIMP_TEMPORARY
argument_list|,
name|script_fu_refresh_proc
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_menu_label
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"_Refresh Scripts"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_menu_path
argument_list|(
name|procedure
argument_list|,
literal|"<Image>/Filters/Development/Script-Fu"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Re-read all available Script-Fu scripts"
argument_list|)
argument_list|,
literal|"Re-read all available Script-Fu scripts"
argument_list|,
literal|"script-fu-refresh"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1997"
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_ENUM
argument_list|(
name|procedure
argument_list|,
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
DECL|function|script_fu_refresh_proc (GimpProcedure * procedure,const GimpValueArray * args,gpointer run_data)
name|script_fu_refresh_proc
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
if|if
condition|(
name|script_fu_interface_is_active
argument_list|()
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"You can not use \"Refresh Scripts\" while a "
literal|"Script-Fu dialog box is open.  Please close "
literal|"all Script-Fu windows and try again."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_EXECUTION_ERROR
argument_list|,
name|NULL
argument_list|)
return|;
block|}
else|else
block|{
comment|/*  Reload all of the available scripts  */
name|GList
modifier|*
name|path
init|=
name|script_fu_search_path
argument_list|()
decl_stmt|;
name|script_fu_find_scripts
argument_list|(
name|gimp_procedure_get_plug_in
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|g_list_free_full
argument_list|(
name|path
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
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

end_unit

