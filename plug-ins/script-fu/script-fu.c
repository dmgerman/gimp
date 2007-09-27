begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_comment
comment|/* Declare local functions. */
end_comment

begin_function_decl
specifier|static
name|void
name|script_fu_query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|script_fu_run
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
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
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|script_fu_refresh_proc
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
function_decl|;
end_function_decl

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
name|script_fu_query
block|,
comment|/* query_proc */
name|script_fu_run
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
name|script_fu_query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpParamDef
name|console_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"Interactive, [non-interactive]"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|textconsole_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"Interactive, [non-interactive]"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|eval_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"[Interactive], non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"code"
block|,
literal|"The code to evaluate"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|server_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"[Interactive], non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"port"
block|,
literal|"The port on which to listen for requests"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"logfile"
block|,
literal|"The file to log server activity to"
block|}
block|}
decl_stmt|;
name|gimp_plugin_domain_register
argument_list|(
name|GETTEXT_PACKAGE
literal|"-script-fu"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"extension-script-fu"
argument_list|,
literal|"A scheme interpreter for scripting GIMP operations"
argument_list|,
literal|"More help here later"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1997"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_EXTENSION
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug-in-script-fu-console"
argument_list|,
name|N_
argument_list|(
literal|"Interactive console for Script-Fu development"
argument_list|)
argument_list|,
literal|"Provides an interface which allows interactive "
literal|"scheme development."
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"Script-Fu _Console"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|console_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|console_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
literal|"plug-in-script-fu-console"
argument_list|,
literal|"<Toolbox>/Xtns/Languages/Script-Fu"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug-in-script-fu-text-console"
argument_list|,
literal|"Provides a text console mode for script-fu "
literal|"development"
argument_list|,
literal|"Provides an interface which allows interactive "
literal|"scheme development."
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1997"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|textconsole_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|textconsole_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug-in-script-fu-server"
argument_list|,
name|N_
argument_list|(
literal|"Server for remote Script-Fu operation"
argument_list|)
argument_list|,
literal|"Provides a server for remote script-fu operation"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"_Start Server..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|server_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|server_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
literal|"plug-in-script-fu-server"
argument_list|,
literal|"<Toolbox>/Xtns/Languages/Script-Fu"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug-in-script-fu-eval"
argument_list|,
literal|"Evaluate scheme code"
argument_list|,
literal|"Evaluate the code under the scheme interpreter "
literal|"(primarily for batch mode)"
argument_list|,
literal|"Manish Singh"
argument_list|,
literal|"Manish Singh"
argument_list|,
literal|"1998"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|eval_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|eval_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|script_fu_run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|script_fu_run
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
name|gchar
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
comment|/*  Setup auxillary temporary procedures for the base extension  */
name|script_fu_extension_init
argument_list|()
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
name|param
operator|!=
name|NULL
condition|)
name|set_run_mode_constant
argument_list|(
operator|(
name|GimpRunMode
operator|)
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
comment|/*  Load all of the available scripts  */
name|script_fu_find_scripts
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
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
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
comment|/*  Acknowledge that the extension is properly initialized  */
name|gimp_extension_ack
argument_list|()
expr_stmt|;
comment|/*  Go into an endless loop  */
while|while
condition|(
name|TRUE
condition|)
name|gimp_extension_process
argument_list|(
literal|0
argument_list|)
expr_stmt|;
comment|/*  Set return values; pointless because we never get out of the loop  */
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
name|script_fu_text_console_run
argument_list|(
name|name
argument_list|,
name|nparams
argument_list|,
name|param
argument_list|,
name|nreturn_vals
argument_list|,
name|return_vals
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
name|script_fu_console_run
argument_list|(
name|name
argument_list|,
name|nparams
argument_list|,
name|param
argument_list|,
name|nreturn_vals
argument_list|,
name|return_vals
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
name|script_fu_server_run
argument_list|(
name|name
argument_list|,
name|nparams
argument_list|,
name|param
argument_list|,
name|nreturn_vals
argument_list|,
name|return_vals
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
name|script_fu_eval_run
argument_list|(
name|name
argument_list|,
name|nparams
argument_list|,
name|param
argument_list|,
name|nreturn_vals
argument_list|,
name|return_vals
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gchar
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
name|gchar
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
name|g_filename_from_utf8
argument_list|(
name|path_str
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
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
name|g_error_free
argument_list|(
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
DECL|function|script_fu_extension_init (void)
name|script_fu_extension_init
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
literal|"[Interactive], non-interactive"
block|}
block|}
decl_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Toolbox>/Help"
argument_list|,
name|N_
argument_list|(
literal|"_GIMP Online"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Toolbox>/Help"
argument_list|,
name|N_
argument_list|(
literal|"_User Manual"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Toolbox>/Xtns/Languages"
argument_list|,
name|N_
argument_list|(
literal|"_Script-Fu"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Toolbox>/Xtns"
argument_list|,
name|N_
argument_list|(
literal|"_Buttons"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Toolbox>/Xtns"
argument_list|,
name|N_
argument_list|(
literal|"_Logos"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Toolbox>/Xtns"
argument_list|,
name|N_
argument_list|(
literal|"_Misc"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Toolbox>/Xtns"
argument_list|,
name|N_
argument_list|(
literal|"_Patterns"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Toolbox>/Xtns/Languages/Script-Fu"
argument_list|,
name|N_
argument_list|(
literal|"_Test"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Toolbox>/Xtns"
argument_list|,
name|N_
argument_list|(
literal|"_Utilities"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Toolbox>/Xtns"
argument_list|,
name|N_
argument_list|(
literal|"_Web Page Themes"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Toolbox>/Xtns/Web Page Themes"
argument_list|,
name|N_
argument_list|(
literal|"_Alien Glow"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Toolbox>/Xtns/Web Page Themes"
argument_list|,
name|N_
argument_list|(
literal|"_Beveled Pattern"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Toolbox>/Xtns/Web Page Themes"
argument_list|,
name|N_
argument_list|(
literal|"_Classic.Gimp.Org"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Image>/Filters"
argument_list|,
name|N_
argument_list|(
literal|"Alpha to _Logo"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Image>/Filters"
argument_list|,
name|N_
argument_list|(
literal|"An_imation"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Image>/Filters/Animation"
argument_list|,
name|N_
argument_list|(
literal|"_Animators"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Image>/Filters"
argument_list|,
name|N_
argument_list|(
literal|"_Artistic"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Image>/Filters"
argument_list|,
name|N_
argument_list|(
literal|"_Blur"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Image>/Filters"
argument_list|,
name|N_
argument_list|(
literal|"_Decor"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Image>/Filters"
argument_list|,
name|N_
argument_list|(
literal|"_Effects"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Image>/Filters"
argument_list|,
name|N_
argument_list|(
literal|"En_hance"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Image>/Filters"
argument_list|,
name|N_
argument_list|(
literal|"_Light and Shadow"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Image>/Filters/Light and Shadow"
argument_list|,
name|N_
argument_list|(
literal|"S_hadow"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Image>/Filters"
argument_list|,
name|N_
argument_list|(
literal|"_Render"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_branch_register
argument_list|(
literal|"<Image>/Filters/Effects"
argument_list|,
name|N_
argument_list|(
literal|"_Alchemy"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_install_temp_proc
argument_list|(
literal|"script-fu-refresh"
argument_list|,
name|N_
argument_list|(
literal|"Re-read all available Script-Fu scripts"
argument_list|)
argument_list|,
literal|"Re-read all available Script-Fu scripts"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"_Refresh Scripts"
argument_list|)
argument_list|,
name|NULL
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
name|script_fu_refresh_proc
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
literal|"script-fu-refresh"
argument_list|,
literal|"<Toolbox>/Xtns/Languages/Script-Fu"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|script_fu_refresh_proc (const gchar * name,gint nparams,const GimpParam * params,gint * nreturn_vals,GimpParam ** return_vals)
name|script_fu_refresh_proc
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
name|GimpPDBStatusType
name|status
decl_stmt|;
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
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
else|else
block|{
comment|/*  Reload all of the available scripts  */
name|gchar
modifier|*
name|path
init|=
name|script_fu_search_path
argument_list|()
decl_stmt|;
name|script_fu_find_scripts
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
block|}
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

end_unit

