begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  *  * plugin-helper -- support plugin for dynamically loaded plugin modules  * Copyright (C) 2000 Nathan Summers  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_include
include|#
directive|include
file|<gmodule.h>
end_include

begin_comment
comment|/* why aren't these functions defined in gimp.h? */
end_comment

begin_function_decl
specifier|extern
name|void
name|gimp_extension_ack
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_extension_process
parameter_list|(
name|int
name|timeout
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Declare local functions */
end_comment

begin_function_decl
specifier|static
name|void
name|helper_query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|helper_run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
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
name|query_module
parameter_list|(
name|gchar
modifier|*
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
name|NULL
block|,
comment|/* quit_proc  */
name|helper_query
block|,
comment|/* query_proc */
name|helper_run
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
name|helper_query
parameter_list|(
name|void
parameter_list|)
block|{
name|g_message
argument_list|(
literal|"query called"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"extension_plugin_helper"
argument_list|,
literal|"Proxy process for dynamically loaded plugin modules"
argument_list|,
literal|"Automagically called by the Gimp at startup"
argument_list|,
literal|"Nathan Summers"
argument_list|,
literal|"Nathan Summers"
argument_list|,
literal|"2000"
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
name|g_message
argument_list|(
literal|"query done"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|helper_run (gchar * name,gint nparams,GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|helper_run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
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
literal|2
index|]
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|g_message
argument_list|(
literal|"run called %s"
argument_list|,
name|name
argument_list|)
expr_stmt|;
comment|/* No parameters have been defined: asking for one */
comment|/* seg-faults, since param[0] == NULL              */
comment|/* See helper_query                       -garo-   */
comment|/* run_mode = param[0].data.d_int32; */
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
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"extension_plugin_helper"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_SUCCESS
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
name|query_module
argument_list|(
literal|"/usr/local/lib/gimp/1.3/plugin-modules/libiwarp.so"
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
literal|"time for the evil loop"
argument_list|)
expr_stmt|;
name|gimp_extension_ack
argument_list|()
expr_stmt|;
while|while
condition|(
name|TRUE
condition|)
comment|/* this construction bothers me deeply */
name|gimp_extension_process
argument_list|(
literal|0
argument_list|)
expr_stmt|;
comment|/* doubtful that execution ever passes this point. */
name|g_message
argument_list|(
literal|"Brigadoon!"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
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
DECL|function|query_module (gchar * module)
name|void
name|query_module
parameter_list|(
name|gchar
modifier|*
name|module
parameter_list|)
block|{
name|GModule
modifier|*
name|mod
decl_stmt|;
name|GimpQueryProc
name|query_proc
init|=
name|NULL
decl_stmt|;
name|mod
operator|=
name|g_module_open
argument_list|(
name|module
argument_list|,
name|G_MODULE_BIND_LAZY
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|mod
condition|)
block|{
name|g_message
argument_list|(
literal|"Could not open module %s!"
argument_list|,
name|module
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|g_module_symbol
argument_list|(
name|mod
argument_list|,
literal|"query"
argument_list|,
operator|(
name|gpointer
operator|*
operator|)
operator|&
name|query_proc
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"alright!"
argument_list|)
expr_stmt|;
call|(
modifier|*
name|query_proc
call|)
argument_list|()
expr_stmt|;
block|}
else|else
block|{
name|g_message
argument_list|(
literal|"doh!"
argument_list|)
expr_stmt|;
name|g_error
argument_list|(
name|g_module_error
argument_list|()
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|plugin_module_install_procedure (gchar * name,gchar * blurb,gchar * help,gchar * author,gchar * copyright,gchar * date,gchar * menu_path,gchar * image_types,gint nparams,gint nreturn_vals,GimpParamDef * params,GimpParamDef * return_vals,GimpRunProc run_proc)
name|void
name|plugin_module_install_procedure
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
name|date
parameter_list|,
name|gchar
modifier|*
name|menu_path
parameter_list|,
name|gchar
modifier|*
name|image_types
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|gint
name|nreturn_vals
parameter_list|,
name|GimpParamDef
modifier|*
name|params
parameter_list|,
name|GimpParamDef
modifier|*
name|return_vals
parameter_list|,
name|GimpRunProc
name|run_proc
parameter_list|)
block|{
name|g_message
argument_list|(
literal|"Installing plug-in procedure %s (%p)"
argument_list|,
name|name
argument_list|,
name|run_proc
argument_list|)
expr_stmt|;
name|gimp_install_temp_proc
argument_list|(
name|name
argument_list|,
name|blurb
argument_list|,
name|help
argument_list|,
name|author
argument_list|,
name|copyright
argument_list|,
name|date
argument_list|,
name|menu_path
argument_list|,
name|image_types
argument_list|,
name|GIMP_TEMPORARY
argument_list|,
name|nparams
argument_list|,
name|nreturn_vals
argument_list|,
name|params
argument_list|,
name|return_vals
argument_list|,
name|run_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_empty_stmt
empty_stmt|;
end_empty_stmt

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* search for binaries in the plug-in directory path */
end_comment

begin_comment
unit|find_modules (plug_in_path, plug_in_init_file, 				  MODE_EXECUTABLE);
comment|/* read the pluginrc file for cached data */
end_comment

begin_comment
unit|filename = NULL;       if (pluginrc_path) 	{ 	  if (g_path_is_absolute (pluginrc_path)) 	    filename = g_strdup (pluginrc_path); 	  else 	    filename = g_strdup_printf ("%s" G_DIR_SEPARATOR_S "%s", 					gimp_directory (), pluginrc_path); 	}       else 	filename = gimp_personal_rc_file ("pluginrc");        app_init_update_status (_("Resource configuration"), filename, -1);       parse_gimprc_file (filename);
comment|/* query any plug-ins that have changed since we last wrote out          *  the pluginrc file.        */
end_comment

begin_comment
unit|tmp = plug_in_defs;       app_init_update_status (_("Plug-ins"), "", 0);       nplugins = g_slist_length (tmp);       nth = 0;       while (tmp) 	{ 	  plug_in_def = tmp->data; 	  tmp = tmp->next;  	  if (plug_in_def->query) 	    { 	      write_pluginrc = TRUE;  	      if (be_verbose) 		g_print (_("query plug-in: \"%s\"\n"), plug_in_def->prog);  	      plug_in_query (plug_in_def); 	    }  	  app_init_update_status (NULL, plug_in_def->prog, nth / nplugins); 	  nth++; 	}
comment|/* insert the proc defs */
end_comment

begin_comment
unit|for (tmp = gimprc_proc_defs; tmp; tmp = g_slist_next (tmp)) 	{ 	  proc_def = g_new (PlugInProcDef, 1); 	  *proc_def = *((PlugInProcDef *) tmp->data); 	  plug_in_proc_def_insert (proc_def, NULL); 	}        tmp = plug_in_defs;       while (tmp) 	{ 	  plug_in_def = tmp->data; 	  tmp = tmp->next;  	  tmp = tmp->next;  	  tmp2 = plug_in_def->proc_defs; 	  while (tmp2) 	    { 	      proc_def = tmp2->data; 	      tmp2 = tmp2->next;  	      proc_def->mtime = plug_in_def->mtime; 	      plug_in_proc_def_insert (proc_def, plug_in_proc_def_dead); 	    } 	}
comment|/* write the pluginrc file if necessary */
end_comment

begin_comment
unit|if (write_pluginrc) 	{ 	  if (be_verbose) 	    g_print (_("writing \"%s\"\n"), filename);  	  plug_in_write_rc (filename); 	}        g_free (filename);
comment|/* add the plug-in procs to the procedure database */
end_comment

begin_endif
unit|plug_in_add_to_db ();
endif|#
directive|endif
end_endif

end_unit

