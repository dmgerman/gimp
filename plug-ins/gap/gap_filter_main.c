begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_filter_main.c  * 1997.12.18 hof (Wolfgang Hofer)  *  * GAP ... Gimp Animation Plugins  *  * This Module contains:  * - MAIN of GAP_filter  foreach: call any Filter (==Plugin Proc)  *                                with varying settings for all  *                                layers within one Image.  * - query   registration of gap_foreach Procedure  *                        and for all Iterator_ALT Procedures  * - run     invoke the gap_foreach procedure by its PDB name  *   *  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

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
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
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
file|"gap_filter.h"
end_include

begin_decl_stmt
DECL|variable|gap_filter_version
specifier|static
name|char
modifier|*
name|gap_filter_version
init|=
literal|"0.92.01; 2000/11/30"
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* revision history:  * 2000/11/30 v1.1.29b:  hof: new e-mail adress  * version 0.92.00              hof: set gap_debug from environment   * version 0.91.01; Tue Dec 23  hof: 1.st (pre) release  */
end_comment

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
DECL|variable|gap_debug
name|int
name|gap_debug
init|=
literal|0
decl_stmt|;
end_decl_stmt

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
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparam
parameter_list|,
name|GimpParam
modifier|*
name|param
parameter_list|,
name|int
modifier|*
name|nretvals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|retvals
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
comment|/* init_proc */
name|NULL
block|,
comment|/* quit_proc */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc */
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
parameter_list|()
block|{
specifier|static
name|GimpParamDef
name|args_foreach
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable (unused)"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"proc_name"
block|,
literal|"name of plugin procedure to run for each layer)"
block|}
block|,   }
decl_stmt|;
specifier|static
name|GimpParamDef
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
specifier|static
name|int
name|nreturn_vals
init|=
literal|0
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_gap_layers_run_animfilter"
argument_list|,
literal|"This plugin calls another plugin for each layer of an image, varying its settings (to produce animated effects). The called plugin must work on a single drawable and must be able to GIMP_RUN_WITH_LAST_VALS"
argument_list|,
literal|""
argument_list|,
literal|"Wolfgang Hofer (hof@gimp.org)"
argument_list|,
literal|"Wolfgang Hofer"
argument_list|,
name|gap_filter_version
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Filter all Layers..."
argument_list|)
argument_list|,
literal|"RGB*, INDEXED*, GRAY*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args_foreach
argument_list|)
argument_list|,
name|nreturn_vals
argument_list|,
name|args_foreach
argument_list|,
name|return_vals
argument_list|)
expr_stmt|;
comment|/* ------------------ ALTernative Iterators ------------------------------ */
name|gap_query_iterators_ALT
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/* end query */
end_comment

begin_function
specifier|static
name|void
DECL|function|run (char * name,int n_params,GimpParam * param,int * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|int
name|n_params
parameter_list|,
name|GimpParam
modifier|*
name|param
parameter_list|,
name|int
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
DECL|macro|MAX_PLUGIN_NAME_LEN
define|#
directive|define
name|MAX_PLUGIN_NAME_LEN
value|256
name|char
name|l_plugin_name
index|[
name|MAX_PLUGIN_NAME_LEN
index|]
decl_stmt|;
specifier|static
name|GimpParam
name|values
index|[
literal|1
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
name|gint32
name|image_id
decl_stmt|;
name|gint32
name|len_struct
decl_stmt|;
name|gint32
name|total_steps
decl_stmt|;
name|gdouble
name|current_step
decl_stmt|;
name|gint32
name|l_rc
decl_stmt|;
specifier|const
name|char
modifier|*
name|l_env
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
name|l_rc
operator|=
literal|0
expr_stmt|;
name|l_env
operator|=
name|g_getenv
argument_list|(
literal|"GAP_DEBUG"
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_env
operator|!=
name|NULL
condition|)
block|{
if|if
condition|(
operator|(
operator|*
name|l_env
operator|!=
literal|'n'
operator|)
operator|&&
operator|(
operator|*
name|l_env
operator|!=
literal|'N'
operator|)
condition|)
name|gap_debug
operator|=
literal|1
expr_stmt|;
block|}
name|run_mode
operator|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
if|if
condition|(
name|gap_debug
condition|)
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"\n\ngap_filter_main: debug name = %s\n"
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug_in_gap_layers_run_animfilter"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_NONINTERACTIVE
condition|)
block|{
if|if
condition|(
name|n_params
operator|!=
literal|4
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|strncpy
argument_list|(
name|l_plugin_name
argument_list|,
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|MAX_PLUGIN_NAME_LEN
operator|-
literal|1
argument_list|)
expr_stmt|;
name|l_plugin_name
index|[
name|MAX_PLUGIN_NAME_LEN
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
block|}
name|INIT_I18N
argument_list|()
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_WITH_LAST_VALS
condition|)
block|{
comment|/* probably get last values (name of last plugin) */
name|gimp_get_data
argument_list|(
literal|"plug_in_gap_layers_run_animfilter"
argument_list|,
name|l_plugin_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|image_id
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
expr_stmt|;
name|l_rc
operator|=
name|gap_proc_anim_apply
argument_list|(
name|run_mode
argument_list|,
name|image_id
argument_list|,
name|l_plugin_name
argument_list|)
expr_stmt|;
name|gimp_set_data
argument_list|(
literal|"plug_in_gap_layers_run_animfilter"
argument_list|,
name|l_plugin_name
argument_list|,
sizeof|sizeof
argument_list|(
name|l_plugin_name
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
operator|(
name|run_mode
operator|==
name|GIMP_RUN_NONINTERACTIVE
operator|)
operator|&&
operator|(
name|n_params
operator|==
literal|4
operator|)
condition|)
block|{
name|total_steps
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|current_step
operator|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|len_struct
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|l_rc
operator|=
name|gap_run_iterators_ALT
argument_list|(
name|name
argument_list|,
name|run_mode
argument_list|,
name|total_steps
argument_list|,
name|current_step
argument_list|,
name|len_struct
argument_list|)
expr_stmt|;
block|}
else|else
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
if|if
condition|(
name|l_rc
operator|<
literal|0
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
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

