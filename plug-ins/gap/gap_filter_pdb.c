begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_filter_pdb.c  * 1998.10.14 hof (Wolfgang Hofer)  *  * GAP ... Gimp Animation Plugins  *  * This Module contains:  * - GAP_filter  pdb: functions for calling any Filter (==Plugin Proc)  *                    that operates on a drawable  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * version gimp 1.1.17b  2000.02.22  hof: - removed limit PLUGIN_DATA_SIZE  *                                        - removed support for old gimp 1.0.x PDB-interface.  * version 0.97.00                   hof: - created module (as extract gap_filter_foreach)  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_comment
comment|/* SYTEM (UNIX) includes */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
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

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_SYS_WAIT_H
end_ifdef

begin_include
include|#
directive|include
file|<sys/wait.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP includes */
end_comment

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_comment
comment|/* GAP includes */
end_comment

begin_include
include|#
directive|include
file|"gap_arr_dialog.h"
end_include

begin_include
include|#
directive|include
file|"gap_filter.h"
end_include

begin_include
include|#
directive|include
file|"gap_filter_pdb.h"
end_include

begin_include
include|#
directive|include
file|"gap_lib.h"
end_include

begin_comment
comment|/* ------------------------  * global gap DEBUG switch  * ------------------------  */
end_comment

begin_comment
comment|/* int gap_debug = 1; */
end_comment

begin_comment
comment|/* print debug infos */
end_comment

begin_comment
comment|/* int gap_debug = 0; */
end_comment

begin_comment
comment|/* 0: dont print debug infos */
end_comment

begin_decl_stmt
specifier|extern
name|int
name|gap_debug
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|global_plugin_data
specifier|static
name|char
modifier|*
name|global_plugin_data
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|g_current_image_id
specifier|static
name|gint32
name|g_current_image_id
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|p_call_plugin (char * plugin_name,gint32 image_id,gint32 layer_id,GRunModeType run_mode)
name|gint
name|p_call_plugin
parameter_list|(
name|char
modifier|*
name|plugin_name
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|gint32
name|layer_id
parameter_list|,
name|GRunModeType
name|run_mode
parameter_list|)
block|{
name|GDrawable
modifier|*
name|l_drawable
decl_stmt|;
name|GParam
modifier|*
name|l_ret_params
decl_stmt|;
name|GParam
modifier|*
name|l_argv
decl_stmt|;
name|gint
name|l_retvals
decl_stmt|;
name|int
name|l_idx
decl_stmt|;
name|int
name|l_nparams
decl_stmt|;
name|int
name|l_nreturn_vals
decl_stmt|;
name|int
name|l_proc_type
decl_stmt|;
name|char
modifier|*
name|l_proc_blurb
decl_stmt|;
name|char
modifier|*
name|l_proc_help
decl_stmt|;
name|char
modifier|*
name|l_proc_author
decl_stmt|;
name|char
modifier|*
name|l_proc_copyright
decl_stmt|;
name|char
modifier|*
name|l_proc_date
decl_stmt|;
name|GParamDef
modifier|*
name|l_params
decl_stmt|;
name|GParamDef
modifier|*
name|l_return_vals
decl_stmt|;
name|l_drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|layer_id
argument_list|)
expr_stmt|;
comment|/* use the background layer */
comment|/* query for plugin_name to get its argument types */
if|if
condition|(
name|FALSE
operator|==
name|gimp_query_procedure
argument_list|(
name|plugin_name
argument_list|,
operator|&
name|l_proc_blurb
argument_list|,
operator|&
name|l_proc_help
argument_list|,
operator|&
name|l_proc_author
argument_list|,
operator|&
name|l_proc_copyright
argument_list|,
operator|&
name|l_proc_date
argument_list|,
operator|&
name|l_proc_type
argument_list|,
operator|&
name|l_nparams
argument_list|,
operator|&
name|l_nreturn_vals
argument_list|,
operator|&
name|l_params
argument_list|,
operator|&
name|l_return_vals
argument_list|)
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"ERROR: Plugin not available, Name was %s\n"
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/* construct the procedures arguments */
name|l_argv
operator|=
name|g_new
argument_list|(
name|GParam
argument_list|,
name|l_nparams
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|l_argv
argument_list|,
literal|0
argument_list|,
operator|(
sizeof|sizeof
argument_list|(
name|GParam
argument_list|)
operator|*
name|l_nparams
operator|)
argument_list|)
expr_stmt|;
comment|/* initialize the argument types */
for|for
control|(
name|l_idx
operator|=
literal|0
init|;
name|l_idx
operator|<
name|l_nparams
condition|;
name|l_idx
operator|++
control|)
block|{
name|l_argv
index|[
name|l_idx
index|]
operator|.
name|type
operator|=
name|l_params
index|[
name|l_idx
index|]
operator|.
name|type
expr_stmt|;
switch|switch
condition|(
name|l_params
index|[
name|l_idx
index|]
operator|.
name|type
condition|)
block|{
case|case
name|PARAM_DISPLAY
case|:
name|l_argv
index|[
name|l_idx
index|]
operator|.
name|data
operator|.
name|d_display
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|PARAM_DRAWABLE
case|:
case|case
name|PARAM_LAYER
case|:
case|case
name|PARAM_CHANNEL
case|:
name|l_argv
index|[
name|l_idx
index|]
operator|.
name|data
operator|.
name|d_drawable
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|PARAM_IMAGE
case|:
name|l_argv
index|[
name|l_idx
index|]
operator|.
name|data
operator|.
name|d_image
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|PARAM_INT32
case|:
case|case
name|PARAM_INT16
case|:
case|case
name|PARAM_INT8
case|:
name|l_argv
index|[
name|l_idx
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|PARAM_FLOAT
case|:
name|l_argv
index|[
name|l_idx
index|]
operator|.
name|data
operator|.
name|d_float
operator|=
literal|0.0
expr_stmt|;
break|break;
case|case
name|PARAM_STRING
case|:
name|l_argv
index|[
name|l_idx
index|]
operator|.
name|data
operator|.
name|d_string
operator|=
name|NULL
expr_stmt|;
break|break;
default|default:
name|l_argv
index|[
name|l_idx
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
literal|0
expr_stmt|;
break|break;
block|}
block|}
comment|/* init the standard parameters, that should be common to all plugins */
name|l_argv
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
name|run_mode
expr_stmt|;
name|l_argv
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
operator|=
name|image_id
expr_stmt|;
name|l_argv
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_drawable
operator|=
name|l_drawable
operator|->
name|id
expr_stmt|;
comment|/* run the plug-in procedure */
name|l_ret_params
operator|=
name|gimp_run_procedure2
argument_list|(
name|plugin_name
argument_list|,
operator|&
name|l_retvals
argument_list|,
name|l_nparams
argument_list|,
name|l_argv
argument_list|)
expr_stmt|;
comment|/*  free up arguments and values  */
name|g_free
argument_list|(
name|l_argv
argument_list|)
expr_stmt|;
comment|/*  free the query information  */
name|g_free
argument_list|(
name|l_proc_blurb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_proc_help
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_proc_author
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_proc_copyright
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_proc_date
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_params
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_return_vals
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_ret_params
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|FALSE
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"ERROR: p_call_plugin %s failed.\n"
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_ret_params
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
else|else
block|{
if|if
condition|(
name|gap_debug
condition|)
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"DEBUG: p_call_plugin: %s successful.\n"
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_ret_params
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
block|}
end_function

begin_function
name|int
DECL|function|p_save_xcf (gint32 image_id,char * sav_name)
name|p_save_xcf
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|char
modifier|*
name|sav_name
parameter_list|)
block|{
name|GParam
modifier|*
name|l_params
decl_stmt|;
name|gint
name|l_retvals
decl_stmt|;
comment|/* save current image as xcf file      * xcf_save does operate on the complete image,      * the drawable is ignored. (we can supply a dummy value)      */
name|l_params
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_xcf_save"
argument_list|,
operator|&
name|l_retvals
argument_list|,
name|PARAM_INT32
argument_list|,
name|RUN_NONINTERACTIVE
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image_id
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
literal|0
argument_list|,
name|PARAM_STRING
argument_list|,
name|sav_name
argument_list|,
name|PARAM_STRING
argument_list|,
name|sav_name
argument_list|,
comment|/* raw name ? */
name|PARAM_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_params
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|FALSE
condition|)
return|return
operator|(
operator|-
literal|1
operator|)
return|;
return|return
literal|0
return|;
block|}
end_function

begin_comment
comment|/* ============================================================================  * p_get_data  *    try to get the plugin's data (key is usually the name of the plugin)  *    and check for the length of the retrieved data.  * if all done OK return the length of the retrieved data,  * return -1 in case of errors.  * ============================================================================  */
end_comment

begin_function
DECL|function|p_get_data (char * key)
name|gint
name|p_get_data
parameter_list|(
name|char
modifier|*
name|key
parameter_list|)
block|{
name|int
name|l_len
decl_stmt|;
name|l_len
operator|=
name|gimp_get_data_size
argument_list|(
name|key
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_len
operator|<
literal|1
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"ERROR: no stored data found for Key %s\n"
argument_list|,
name|key
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
if|if
condition|(
name|global_plugin_data
condition|)
block|{
name|g_free
argument_list|(
name|global_plugin_data
argument_list|)
expr_stmt|;
block|}
name|global_plugin_data
operator|=
name|g_malloc0
argument_list|(
name|l_len
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gimp_get_data
argument_list|(
name|key
argument_list|,
name|global_plugin_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gap_debug
condition|)
name|printf
argument_list|(
literal|"DEBUG p_get_data Key:%s  retrieved bytes %d\n"
argument_list|,
name|key
argument_list|,
operator|(
name|int
operator|)
name|l_len
argument_list|)
expr_stmt|;
return|return
operator|(
name|l_len
operator|)
return|;
block|}
end_function

begin_comment
comment|/* ============================================================================  * p_set_data  *  *    set global_plugin_data  * ============================================================================  */
end_comment

begin_function
DECL|function|p_set_data (char * key,gint plugin_data_len)
name|void
name|p_set_data
parameter_list|(
name|char
modifier|*
name|key
parameter_list|,
name|gint
name|plugin_data_len
parameter_list|)
block|{
if|if
condition|(
name|global_plugin_data
condition|)
block|{
name|gimp_set_data
argument_list|(
name|key
argument_list|,
name|global_plugin_data
argument_list|,
name|plugin_data_len
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* ============================================================================  * p_procedure_available  * ============================================================================  */
end_comment

begin_function
DECL|function|p_procedure_available (char * proc_name,t_proc_type ptype)
name|gint
name|p_procedure_available
parameter_list|(
name|char
modifier|*
name|proc_name
parameter_list|,
name|t_proc_type
name|ptype
parameter_list|)
block|{
name|int
name|l_nparams
decl_stmt|;
name|int
name|l_nreturn_vals
decl_stmt|;
name|int
name|l_proc_type
decl_stmt|;
name|char
modifier|*
name|l_proc_blurb
decl_stmt|;
name|char
modifier|*
name|l_proc_help
decl_stmt|;
name|char
modifier|*
name|l_proc_author
decl_stmt|;
name|char
modifier|*
name|l_proc_copyright
decl_stmt|;
name|char
modifier|*
name|l_proc_date
decl_stmt|;
name|GParamDef
modifier|*
name|l_params
decl_stmt|;
name|GParamDef
modifier|*
name|l_return_vals
decl_stmt|;
name|gint
name|l_rc
decl_stmt|;
name|l_rc
operator|=
literal|0
expr_stmt|;
comment|/* Query the gimp application's procedural database    *  regarding a particular procedure.    */
if|if
condition|(
name|gimp_query_procedure
argument_list|(
name|proc_name
argument_list|,
operator|&
name|l_proc_blurb
argument_list|,
operator|&
name|l_proc_help
argument_list|,
operator|&
name|l_proc_author
argument_list|,
operator|&
name|l_proc_copyright
argument_list|,
operator|&
name|l_proc_date
argument_list|,
operator|&
name|l_proc_type
argument_list|,
operator|&
name|l_nparams
argument_list|,
operator|&
name|l_nreturn_vals
argument_list|,
operator|&
name|l_params
argument_list|,
operator|&
name|l_return_vals
argument_list|)
condition|)
block|{
comment|/* procedure found in PDB */
if|if
condition|(
name|gap_debug
condition|)
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"DEBUG: found in PDB %s\n"
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|ptype
condition|)
block|{
case|case
name|PTYP_ITERATOR
case|:
comment|/* check exactly for Input Parametertypes (common to all Iterators) */
if|if
condition|(
name|l_proc_type
operator|!=
name|PROC_EXTENSION
condition|)
block|{
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|l_nparams
operator|!=
literal|4
condition|)
block|{
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|l_params
index|[
literal|0
index|]
operator|.
name|type
operator|!=
name|PARAM_INT32
condition|)
block|{
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|l_params
index|[
literal|1
index|]
operator|.
name|type
operator|!=
name|PARAM_INT32
condition|)
block|{
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|l_params
index|[
literal|2
index|]
operator|.
name|type
operator|!=
name|PARAM_FLOAT
condition|)
block|{
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|l_params
index|[
literal|3
index|]
operator|.
name|type
operator|!=
name|PARAM_INT32
condition|)
block|{
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
block|}
break|break;
case|case
name|PTYP_CAN_OPERATE_ON_DRAWABLE
case|:
comment|/* check if plugin can be a typical one, that works on one drawable */
if|if
condition|(
name|l_proc_type
operator|!=
name|PROC_PLUG_IN
condition|)
block|{
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|l_nparams
operator|<
literal|3
condition|)
block|{
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|l_params
index|[
literal|0
index|]
operator|.
name|type
operator|!=
name|PARAM_INT32
condition|)
block|{
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|l_params
index|[
literal|1
index|]
operator|.
name|type
operator|!=
name|PARAM_IMAGE
condition|)
block|{
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|l_params
index|[
literal|2
index|]
operator|.
name|type
operator|!=
name|PARAM_DRAWABLE
condition|)
block|{
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
block|}
break|break;
default|default:
break|break;
block|}
comment|/*  free the query information  */
name|g_free
argument_list|(
name|l_proc_blurb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_proc_help
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_proc_author
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_proc_copyright
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_proc_date
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_params
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_return_vals
argument_list|)
expr_stmt|;
block|}
else|else
block|{
return|return
operator|-
literal|1
return|;
block|}
return|return
name|l_rc
return|;
block|}
end_function

begin_comment
comment|/* end p_procedure_available */
end_comment

begin_comment
comment|/* ============================================================================  * p_get_iterator_proc  *   check the PDB for Iterator Procedures (suffix "_Iterator" or "_Iterator_ALT"  * return Pointer to the name of the Iterator Procedure  *        or NULL if not found  * ============================================================================  */
end_comment

begin_function
DECL|function|p_get_iterator_proc (char * plugin_name)
name|char
modifier|*
name|p_get_iterator_proc
parameter_list|(
name|char
modifier|*
name|plugin_name
parameter_list|)
block|{
name|char
modifier|*
name|l_plugin_iterator
decl_stmt|;
comment|/* check for matching Iterator PluginProcedures */
name|l_plugin_iterator
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s_Iterator"
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
comment|/* check if iterator is available in PDB */
if|if
condition|(
name|p_procedure_available
argument_list|(
name|l_plugin_iterator
argument_list|,
name|PTYP_ITERATOR
argument_list|)
operator|<
literal|0
condition|)
block|{
name|g_free
argument_list|(
name|l_plugin_iterator
argument_list|)
expr_stmt|;
name|l_plugin_iterator
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s_Iterator_ALT"
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
comment|/* check for alternative Iterator   _Iterator_ALT       * for now i made some Iterator Plugins using the ending _ALT,       * If New plugins were added or existing ones were updated       * the Authors should supply original _Iterator Procedures       * to be used instead of my Hacked versions without name conflicts.       */
if|if
condition|(
name|p_procedure_available
argument_list|(
name|l_plugin_iterator
argument_list|,
name|PTYP_ITERATOR
argument_list|)
operator|<
literal|0
condition|)
block|{
comment|/* both iterator names are not available */
name|g_free
argument_list|(
name|l_plugin_iterator
argument_list|)
expr_stmt|;
name|l_plugin_iterator
operator|=
name|NULL
expr_stmt|;
block|}
block|}
return|return
operator|(
name|l_plugin_iterator
operator|)
return|;
block|}
end_function

begin_comment
comment|/* end p_get_iterator_proc */
end_comment

begin_comment
comment|/* ============================================================================  * constraint procedures  *  * aer responsible for:  * - sensitivity of the dbbrowser's Apply Buttons  * - filter for dbbrowser's listbox  * ============================================================================  */
end_comment

begin_function
DECL|function|p_constraint_proc_sel1 (gchar * proc_name)
name|int
name|p_constraint_proc_sel1
parameter_list|(
name|gchar
modifier|*
name|proc_name
parameter_list|)
block|{
name|int
name|l_rc
decl_stmt|;
name|GImageType
name|l_base_type
decl_stmt|;
comment|/* here we should check, if proc_name    * can operate on the current Imagetype (RGB, INDEXED, GRAY)    * if not, 0 should be returned.    *    * I did not find a way to do this with the PDB Interface of gimp 0.99.16    */
return|return
literal|1
return|;
name|l_rc
operator|=
literal|0
expr_stmt|;
comment|/* 0 .. set Apply Button in_sensitive */
name|l_base_type
operator|=
name|gimp_image_base_type
argument_list|(
name|g_current_image_id
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|l_base_type
condition|)
block|{
case|case
name|RGB
case|:
case|case
name|GRAY
case|:
case|case
name|INDEXED
case|:
name|l_rc
operator|=
literal|1
expr_stmt|;
break|break;
block|}
return|return
name|l_rc
return|;
block|}
end_function

begin_function
DECL|function|p_constraint_proc_sel2 (gchar * proc_name)
name|int
name|p_constraint_proc_sel2
parameter_list|(
name|gchar
modifier|*
name|proc_name
parameter_list|)
block|{
name|char
modifier|*
name|l_plugin_iterator
decl_stmt|;
name|int
name|l_rc
decl_stmt|;
name|l_rc
operator|=
name|p_constraint_proc_sel1
argument_list|(
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_rc
operator|!=
literal|0
condition|)
block|{
name|l_plugin_iterator
operator|=
name|p_get_iterator_proc
argument_list|(
name|proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_plugin_iterator
operator|!=
name|NULL
condition|)
block|{
name|g_free
argument_list|(
name|l_plugin_iterator
argument_list|)
expr_stmt|;
return|return
literal|1
return|;
comment|/* 1 .. set "Apply Varying" Button sensitive */
block|}
block|}
return|return
literal|0
return|;
comment|/* 0 .. set "Apply Varying" Button in_sensitive */
block|}
end_function

begin_function
DECL|function|p_constraint_proc (gchar * proc_name)
name|int
name|p_constraint_proc
parameter_list|(
name|gchar
modifier|*
name|proc_name
parameter_list|)
block|{
name|int
name|l_rc
decl_stmt|;
if|if
condition|(
name|strncmp
argument_list|(
name|proc_name
argument_list|,
literal|"file"
argument_list|,
literal|4
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/* Do not add file Plugins (check if name starts with "file") */
return|return
literal|0
return|;
block|}
if|if
condition|(
name|strncmp
argument_list|(
name|proc_name
argument_list|,
literal|"plug_in_gap_"
argument_list|,
literal|12
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/* Do not add GAP Plugins (check if name starts with "plug_in_gap_") */
return|return
literal|0
return|;
block|}
name|l_rc
operator|=
name|p_procedure_available
argument_list|(
name|proc_name
argument_list|,
name|PTYP_CAN_OPERATE_ON_DRAWABLE
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_rc
operator|<
literal|0
condition|)
block|{
comment|/* Do not add, Plugin not available or wrong type */
return|return
literal|0
return|;
block|}
return|return
literal|1
return|;
comment|/* 1 add the plugin procedure */
block|}
end_function

end_unit

