begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_if
if|#
directive|if
name|HAVE_UNISTD_H
end_if

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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
file|"siod/siod.h"
end_include

begin_include
include|#
directive|include
file|"siod-wrapper.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-console.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-constants.h"
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
file|"script-fu-intl.h"
end_include

begin_comment
comment|/* Declare local functions. */
end_comment

begin_function_decl
specifier|static
name|void
name|script_fu_quit
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

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
name|void
name|script_fu_auxillary_init
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
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc  */
name|script_fu_quit
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
name|script_fu_quit
parameter_list|(
name|void
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|script_fu_query (void)
name|script_fu_query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpParamDef
name|console_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, [non-interactive]"
block|}
block|}
decl_stmt|;
specifier|static
name|GimpParamDef
name|textconsole_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, [non-interactive]"
block|}
block|}
decl_stmt|;
specifier|static
name|GimpParamDef
name|eval_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
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
name|GimpParamDef
name|server_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
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
literal|"extension_script_fu"
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
literal|"plug_in_script_fu_console"
argument_list|,
literal|"Provides a console mode for script-fu development"
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
literal|"plug_in_script_fu_console"
argument_list|,
name|N_
argument_list|(
literal|"<Toolbox>/Xtns/Script-Fu"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_script_fu_text_console"
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
literal|"plug_in_script_fu_server"
argument_list|,
literal|"Provides a server for remote script-fu operation"
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
literal|"plug_in_script_fu_server"
argument_list|,
name|N_
argument_list|(
literal|"<Toolbox>/Xtns/Script-Fu"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_script_fu_eval"
argument_list|,
literal|"Evaluate scheme code"
argument_list|,
literal|"Evaluate the code under the scheme interpeter "
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
name|INIT_I18N
argument_list|()
expr_stmt|;
name|siod_set_console_mode
argument_list|(
literal|0
argument_list|)
expr_stmt|;
name|siod_set_output_file
argument_list|(
name|stdout
argument_list|)
expr_stmt|;
comment|/*  Determine before we allow scripts to register themselves    *   whether this is the base, automatically installed script-fu extension    */
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"extension_script_fu"
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/*  Setup auxillary temporary procedures for the base extension  */
name|script_fu_auxillary_init
argument_list|()
expr_stmt|;
comment|/*  Init the interpreter  */
name|siod_init
argument_list|(
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  Init the interpreter  */
name|siod_init
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
block|}
comment|/*  Load all of the available scripts  */
name|script_fu_find_scripts
argument_list|()
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"extension_script_fu"
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/*        *  The main, automatically installed script fu extension.  For        *  things like logos and effects that are runnable from GIMP        *  menus.        */
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
comment|/*  Acknowledge that the extension is properly initialized  */
name|gimp_extension_ack
argument_list|()
expr_stmt|;
while|while
condition|(
name|TRUE
condition|)
name|gimp_extension_process
argument_list|(
literal|0
argument_list|)
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
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug_in_script_fu_text_console"
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/*        *  The script-fu text console for interactive SIOD development        */
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
literal|"plug_in_script_fu_console"
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/*        *  The script-fu console for interactive SIOD development        */
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
literal|"plug_in_script_fu_server"
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
literal|"plug_in_script_fu_eval"
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
name|void
DECL|function|script_fu_auxillary_init (void)
name|script_fu_auxillary_init
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"[Interactive], non-interactive"
block|}
block|}
decl_stmt|;
name|gimp_install_temp_proc
argument_list|(
literal|"script_fu_refresh"
argument_list|,
name|_
argument_list|(
literal|"Re-read all available scripts"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Re-read all available scripts"
argument_list|)
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"<Toolbox>/Xtns/Script-Fu/_Refresh Scripts"
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
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
comment|/*  Reload all of the available scripts  */
name|script_fu_find_scripts
argument_list|()
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

