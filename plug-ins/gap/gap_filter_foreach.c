begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_filter_foreach.c  * 1997.12.23 hof (Wolfgang Hofer)  *  * GAP ... Gimp Animation Plugins  *  * This Module contains:  * - GAP_filter  foreach: call any Filter (==Plugin Proc)  *                        with varying settings for all  *                        layers within one Image.  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * version 0.97.00              hof: - modul splitted (2.nd part is now gap_filter_pdb.c)  * version 0.96.03              hof: - pitstop dialog provides optional backup on each step  *                                     (and skip option)  * version 0.96.00              hof: - now using gap_arr_dialog.h  * version 0.92.00              hof: - pitstop dialog   *                                     give user a chance to stop after interactive plugin calls  *                                     if you dont want the dialog export GAP_FILTER_PITSTOP="N"  *                                   - fixed bug in restore of layervisibility  *                                   - codegen via explicite button (in gap_debug mode)  * version 0.91.01; Tue Dec 23  hof: 1.st (pre) release  */
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
DECL|variable|g_current_image_id
specifier|static
name|gint32
name|g_current_image_id
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|p_gdisplays_update_full (gint32 image_id)
name|void
name|p_gdisplays_update_full
parameter_list|(
name|gint32
name|image_id
parameter_list|)
block|{
name|GimpParam
modifier|*
name|l_params
decl_stmt|;
name|gint
name|l_retvals
decl_stmt|;
if|if
condition|(
name|p_procedure_available
argument_list|(
literal|"gimp_image_update_full"
argument_list|,
name|PTYP_ANY
argument_list|)
operator|>=
literal|0
condition|)
block|{
name|l_params
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_image_update_full"
argument_list|,
operator|&
name|l_retvals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_id
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
comment|/* Note: gimp_displays_update_full is not available in the official release gimp 0.99.16       *       (dont care if procedure is not there,       *        --> the user may not see the current layer, because       *            gimp_displays_flush() does not update on changes       *            of the visibility.       */
name|g_free
argument_list|(
name|l_params
argument_list|)
expr_stmt|;
block|}
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/* pitstop dialog  *   return -1 on cancel, 0 .. on continue, 1 .. on skip  */
end_comment

begin_function
DECL|function|p_pitstop (GimpRunModeType run_mode,char * plugin_name,gint text_flag,char * step_backup_file,gint len_step_backup_file,gint32 layer_idx)
specifier|static
name|gint
name|p_pitstop
parameter_list|(
name|GimpRunModeType
name|run_mode
parameter_list|,
name|char
modifier|*
name|plugin_name
parameter_list|,
name|gint
name|text_flag
parameter_list|,
name|char
modifier|*
name|step_backup_file
parameter_list|,
name|gint
name|len_step_backup_file
parameter_list|,
name|gint32
name|layer_idx
parameter_list|)
block|{
name|gchar
modifier|*
name|l_env
decl_stmt|;
name|gchar
modifier|*
name|l_msg
decl_stmt|;
specifier|static
name|t_but_arg
name|l_but_argv
index|[
literal|3
index|]
decl_stmt|;
name|gint
name|l_but_argc
decl_stmt|;
name|gint
name|l_argc
decl_stmt|;
specifier|static
name|t_arr_arg
name|l_argv
index|[
literal|1
index|]
decl_stmt|;
name|int
name|l_continue
decl_stmt|;
name|char
name|l_skip_txt
index|[
literal|20
index|]
decl_stmt|;
name|p_init_arr_arg
argument_list|(
operator|&
name|l_argv
index|[
literal|0
index|]
argument_list|,
name|WGT_FILESEL
argument_list|)
expr_stmt|;
name|l_argv
index|[
literal|0
index|]
operator|.
name|label_txt
operator|=
name|_
argument_list|(
literal|"backup to file"
argument_list|)
expr_stmt|;
name|l_argv
index|[
literal|0
index|]
operator|.
name|entry_width
operator|=
literal|140
expr_stmt|;
comment|/* pixel */
name|l_argv
index|[
literal|0
index|]
operator|.
name|help_txt
operator|=
name|_
argument_list|(
literal|"Make backup of the image after each step"
argument_list|)
expr_stmt|;
name|l_argv
index|[
literal|0
index|]
operator|.
name|text_buf_len
operator|=
name|len_step_backup_file
expr_stmt|;
name|l_argv
index|[
literal|0
index|]
operator|.
name|text_buf_ret
operator|=
name|step_backup_file
expr_stmt|;
name|l_but_argv
index|[
literal|0
index|]
operator|.
name|but_txt
operator|=
name|_
argument_list|(
literal|"Continue"
argument_list|)
expr_stmt|;
name|l_but_argv
index|[
literal|0
index|]
operator|.
name|but_val
operator|=
literal|0
expr_stmt|;
name|l_but_argv
index|[
literal|1
index|]
operator|.
name|but_txt
operator|=
name|_
argument_list|(
literal|"Cancel"
argument_list|)
expr_stmt|;
name|l_but_argv
index|[
literal|1
index|]
operator|.
name|but_val
operator|=
operator|-
literal|1
expr_stmt|;
name|sprintf
argument_list|(
name|l_skip_txt
argument_list|,
literal|"Skip %d"
argument_list|,
operator|(
name|int
operator|)
name|layer_idx
argument_list|)
expr_stmt|;
name|l_but_argv
index|[
literal|2
index|]
operator|.
name|but_txt
operator|=
name|l_skip_txt
expr_stmt|;
name|l_but_argv
index|[
literal|2
index|]
operator|.
name|but_val
operator|=
literal|1
expr_stmt|;
name|l_but_argc
operator|=
literal|2
expr_stmt|;
name|l_argc
operator|=
literal|0
expr_stmt|;
comment|/* optional dialog between both calls (to see the effect of 1.call) */
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|l_env
operator|=
name|g_getenv
argument_list|(
literal|"GAP_FILTER_PITSTOP"
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
operator|==
literal|'N'
operator|)
operator|||
operator|(
operator|*
name|l_env
operator|==
literal|'n'
operator|)
condition|)
block|{
return|return
literal|0
return|;
comment|/* continue without question */
block|}
block|}
if|if
condition|(
name|text_flag
operator|==
literal|0
condition|)
block|{
name|l_msg
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"2nd call of %s\n(define end-settings)"
argument_list|)
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|l_msg
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Non-Interactive call of %s\n(for all layers in between)"
argument_list|)
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
name|l_but_argc
operator|=
literal|3
expr_stmt|;
name|l_argc
operator|=
literal|1
expr_stmt|;
block|}
name|l_continue
operator|=
name|p_array_std_dialog
argument_list|(
name|_
argument_list|(
literal|"Animated Filter apply"
argument_list|)
argument_list|,
name|l_msg
argument_list|,
name|l_argc
argument_list|,
name|l_argv
argument_list|,
name|l_but_argc
argument_list|,
name|l_but_argv
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_msg
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_continue
operator|<
literal|0
condition|)
return|return
operator|-
literal|1
return|;
else|else
return|return
name|l_continue
return|;
block|}
return|return
literal|0
return|;
comment|/* continue without question */
block|}
end_function

begin_comment
comment|/* end p_pitstop */
end_comment

begin_function
DECL|function|p_visibilty_restore (gint32 image_id,gint nlayers,int * visible_tab,char * plugin_name)
specifier|static
name|void
name|p_visibilty_restore
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint
name|nlayers
parameter_list|,
name|int
modifier|*
name|visible_tab
parameter_list|,
name|char
modifier|*
name|plugin_name
parameter_list|)
block|{
name|gint32
modifier|*
name|l_layers_list
decl_stmt|;
name|gint
name|l_nlayers2
decl_stmt|;
name|gint32
name|l_idx
decl_stmt|;
name|l_layers_list
operator|=
name|gimp_image_get_layers
argument_list|(
name|image_id
argument_list|,
operator|&
name|l_nlayers2
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_nlayers2
operator|==
name|nlayers
condition|)
block|{
for|for
control|(
name|l_idx
operator|=
literal|0
init|;
name|l_idx
operator|<
name|nlayers
condition|;
name|l_idx
operator|++
control|)
block|{
name|gimp_layer_set_visible
argument_list|(
name|l_layers_list
index|[
name|l_idx
index|]
argument_list|,
name|visible_tab
index|[
name|l_idx
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|gap_debug
condition|)
name|printf
argument_list|(
literal|"visibilty restore [%d] %d\n"
argument_list|,
operator|(
name|int
operator|)
name|l_idx
argument_list|,
operator|(
name|int
operator|)
name|visible_tab
index|[
name|l_idx
index|]
argument_list|)
expr_stmt|;
block|}
name|p_gdisplays_update_full
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|printf
argument_list|(
literal|"Error: Plugin %s has changed Nr. of layers from %d to %d\ncould not restore Layer visibilty.\n"
argument_list|,
name|plugin_name
argument_list|,
operator|(
name|int
operator|)
name|nlayers
argument_list|,
operator|(
name|int
operator|)
name|l_nlayers2
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|l_layers_list
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|p_get_indexed_layerid (gint32 image_id,gint * nlayers,gint32 idx,char * plugin_name)
specifier|static
name|gint32
name|p_get_indexed_layerid
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint
modifier|*
name|nlayers
parameter_list|,
name|gint32
name|idx
parameter_list|,
name|char
modifier|*
name|plugin_name
parameter_list|)
block|{
name|gint32
modifier|*
name|l_layers_list
decl_stmt|;
name|gint32
name|l_layer_id
decl_stmt|;
name|gint
name|l_nlayers2
decl_stmt|;
name|l_layers_list
operator|=
name|gimp_image_get_layers
argument_list|(
name|image_id
argument_list|,
operator|&
name|l_nlayers2
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_layers_list
operator|==
name|NULL
condition|)
block|{
name|printf
argument_list|(
literal|"Warning: cant get layers (maybe the image was closed)\n"
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
if|if
condition|(
operator|(
name|l_nlayers2
operator|!=
operator|*
name|nlayers
operator|)
operator|&&
operator|(
operator|*
name|nlayers
operator|>
literal|0
operator|)
condition|)
block|{
name|printf
argument_list|(
literal|"Error: Plugin %s has changed Nr. of layers from %d to %d\nAnim Filter apply stopped.\n"
argument_list|,
name|plugin_name
argument_list|,
operator|(
name|int
operator|)
operator|*
name|nlayers
argument_list|,
operator|(
name|int
operator|)
name|l_nlayers2
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
operator|*
name|nlayers
operator|=
name|l_nlayers2
expr_stmt|;
name|l_layer_id
operator|=
name|l_layers_list
index|[
name|idx
index|]
expr_stmt|;
name|g_free
argument_list|(
name|l_layers_list
argument_list|)
expr_stmt|;
return|return
operator|(
name|l_layer_id
operator|)
return|;
block|}
end_function

begin_comment
comment|/* ============================================================================  * p_foreach_multilayer  *    apply the given plugin to each layer of the  image.  * returns   image_id of the new created multilayer image  *           (or -1 on error)  * ============================================================================  */
end_comment

begin_function
DECL|function|p_foreach_multilayer (GimpRunModeType run_mode,gint32 image_id,char * plugin_name,t_apply_mode apply_mode)
name|int
name|p_foreach_multilayer
parameter_list|(
name|GimpRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|char
modifier|*
name|plugin_name
parameter_list|,
name|t_apply_mode
name|apply_mode
parameter_list|)
block|{
specifier|static
name|char
name|l_key_from
index|[
literal|512
index|]
decl_stmt|;
specifier|static
name|char
name|l_key_to
index|[
literal|512
index|]
decl_stmt|;
name|char
modifier|*
name|l_plugin_iterator
decl_stmt|;
name|gint32
name|l_layer_id
decl_stmt|;
name|gint32
name|l_top_layer
decl_stmt|;
name|gint32
name|l_idx
decl_stmt|;
name|gint
name|l_nlayers
decl_stmt|;
name|gdouble
name|l_percentage
decl_stmt|,
name|l_percentage_step
decl_stmt|;
name|GimpParam
modifier|*
name|l_params
decl_stmt|;
name|gint
name|l_retvals
decl_stmt|;
name|int
name|l_rc
decl_stmt|;
name|gint
name|l_plugin_data_len
decl_stmt|;
name|long
name|l_child_pid
decl_stmt|;
comment|/* int         l_status; */
name|int
modifier|*
name|l_visible_tab
decl_stmt|;
name|char
name|l_step_backup_file
index|[
literal|120
index|]
decl_stmt|;
name|gint
name|l_pit_rc
decl_stmt|;
name|l_rc
operator|=
literal|0
expr_stmt|;
name|l_plugin_data_len
operator|=
literal|0
expr_stmt|;
name|l_nlayers
operator|=
literal|0
expr_stmt|;
name|l_visible_tab
operator|=
name|NULL
expr_stmt|;
name|l_step_backup_file
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
comment|/* check for the Plugin */
name|l_rc
operator|=
name|p_procedure_available
argument_list|(
name|plugin_name
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
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"ERROR: Plugin not available or wrong type %s\n"
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/* check for matching Iterator PluginProcedures */
name|l_plugin_iterator
operator|=
name|p_get_iterator_proc
argument_list|(
name|plugin_name
argument_list|)
expr_stmt|;
name|l_percentage
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Applying Filter to all Layers..."
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|l_layer_id
operator|=
name|p_get_indexed_layerid
argument_list|(
name|image_id
argument_list|,
operator|&
name|l_nlayers
argument_list|,
literal|0
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_layer_id
operator|>=
literal|0
condition|)
block|{
if|if
condition|(
name|l_nlayers
operator|<
literal|1
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"ERROR: need at least 1 Layers to apply plugin !\n"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* allocate a table to store the visibility attributes for each layer */
name|l_visible_tab
operator|=
operator|(
name|gint
operator|*
operator|)
name|g_malloc
argument_list|(
operator|(
name|l_nlayers
operator|+
literal|1
operator|)
operator|*
sizeof|sizeof
argument_list|(
name|gint
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_visible_tab
operator|==
name|NULL
condition|)
return|return
operator|-
literal|1
return|;
comment|/* save the visibility of all layers */
for|for
control|(
name|l_idx
operator|=
literal|0
init|;
name|l_idx
operator|<
name|l_nlayers
condition|;
name|l_idx
operator|++
control|)
block|{
name|l_layer_id
operator|=
name|p_get_indexed_layerid
argument_list|(
name|image_id
argument_list|,
operator|&
name|l_nlayers
argument_list|,
name|l_idx
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
name|l_visible_tab
index|[
name|l_idx
index|]
operator|=
name|gimp_layer_get_visible
argument_list|(
name|l_layer_id
argument_list|)
expr_stmt|;
comment|/* make the backround visible, all others invisible           * (so the user can see the effect of the 1.st applied _FROM filter)          */
if|if
condition|(
name|l_idx
operator|==
operator|(
name|l_nlayers
operator|-
literal|1
operator|)
condition|)
name|gimp_layer_set_visible
argument_list|(
name|l_layer_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
else|else
name|gimp_layer_set_visible
argument_list|(
name|l_layer_id
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|p_gdisplays_update_full
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
name|l_percentage_step
operator|=
literal|1.0
operator|/
name|l_nlayers
expr_stmt|;
if|if
condition|(
operator|(
name|l_plugin_iterator
operator|!=
name|NULL
operator|)
operator|&&
operator|(
name|l_nlayers
operator|>
literal|1
operator|)
operator|&&
operator|(
name|apply_mode
operator|==
name|PTYP_VARYING_LINEAR
operator|)
condition|)
block|{
name|l_child_pid
operator|=
literal|0
expr_stmt|;
comment|/* fork(); */
if|if
condition|(
name|l_child_pid
operator|<
literal|0
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"ERROR: fork failed !\n"
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/* if(l_child_pid != 0) */
block|{
comment|/* parent process: call plugin Interactive for background layer[n] */
comment|/* if(gap_debug) fprintf(stderr, "forked child process pid=%ld\n", l_child_pid); */
if|if
condition|(
name|gap_debug
condition|)
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"DEBUG start 1.st Interactive call (_FROM values)\n"
argument_list|)
expr_stmt|;
name|l_idx
operator|=
name|l_nlayers
operator|-
literal|1
expr_stmt|;
name|l_layer_id
operator|=
name|p_get_indexed_layerid
argument_list|(
name|image_id
argument_list|,
operator|&
name|l_nlayers
argument_list|,
name|l_idx
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_layer_id
operator|<
literal|0
condition|)
block|{
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
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
literal|"DEBUG: apllying %s on Layerstack %d id=%d\n"
argument_list|,
name|plugin_name
argument_list|,
operator|(
name|int
operator|)
name|l_idx
argument_list|,
operator|(
name|int
operator|)
name|l_layer_id
argument_list|)
expr_stmt|;
name|l_rc
operator|=
name|p_call_plugin
argument_list|(
name|plugin_name
argument_list|,
name|image_id
argument_list|,
name|l_layer_id
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|)
expr_stmt|;
comment|/* get values, then store with suffix "_ITER_FROM" */
name|l_plugin_data_len
operator|=
name|p_get_data
argument_list|(
name|plugin_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_plugin_data_len
operator|>
literal|0
condition|)
block|{
name|sprintf
argument_list|(
name|l_key_from
argument_list|,
literal|"%s_ITER_FROM"
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
name|p_set_data
argument_list|(
name|l_key_from
argument_list|,
name|l_plugin_data_len
argument_list|)
expr_stmt|;
block|}
else|else
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|l_percentage
operator|+=
name|l_percentage_step
expr_stmt|;
name|gimp_progress_update
argument_list|(
name|l_percentage
argument_list|)
expr_stmt|;
block|}
block|}
block|}
comment|/* else */
if|if
condition|(
operator|(
name|l_rc
operator|>=
literal|0
operator|)
operator|&&
operator|(
name|l_nlayers
operator|>
literal|1
operator|)
condition|)
block|{
comment|/* child process: call plugin Interactive for top layer [0] */
if|if
condition|(
name|gap_debug
condition|)
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"DEBUG start 2.nd Interactive call (_TO values)\n"
argument_list|)
expr_stmt|;
comment|/* optional dialog between both calls (to see the effect of 1.call) */
if|if
condition|(
name|p_pitstop
argument_list|(
name|run_mode
argument_list|,
name|plugin_name
argument_list|,
literal|0
argument_list|,
name|l_step_backup_file
argument_list|,
sizeof|sizeof
argument_list|(
name|l_step_backup_file
argument_list|)
argument_list|,
literal|0
argument_list|)
operator|<
literal|0
condition|)
block|{
if|if
condition|(
name|gap_debug
condition|)
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"TERMINATED: by pitstop dialog\n"
argument_list|)
expr_stmt|;
comment|/* restore the visibility of all layers */
name|p_visibilty_restore
argument_list|(
name|image_id
argument_list|,
name|l_nlayers
argument_list|,
name|l_visible_tab
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_visible_tab
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
else|else
block|{
name|l_layer_id
operator|=
name|p_get_indexed_layerid
argument_list|(
name|image_id
argument_list|,
operator|&
name|l_nlayers
argument_list|,
literal|0
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_layer_id
operator|<
literal|0
condition|)
block|{
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
block|}
else|else
block|{
comment|/* make _TO layer visible */
name|gimp_layer_set_visible
argument_list|(
name|l_layer_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|p_gdisplays_update_full
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|gap_debug
condition|)
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"DEBUG: apllying %s on Layerstack 0  id=%d\n"
argument_list|,
name|plugin_name
argument_list|,
operator|(
name|int
operator|)
name|l_layer_id
argument_list|)
expr_stmt|;
name|l_rc
operator|=
name|p_call_plugin
argument_list|(
name|plugin_name
argument_list|,
name|image_id
argument_list|,
name|l_layer_id
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|)
expr_stmt|;
comment|/* get values, then store with suffix "_ITER_TO" */
name|l_plugin_data_len
operator|=
name|p_get_data
argument_list|(
name|plugin_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_plugin_data_len
operator|>
literal|0
condition|)
block|{
name|sprintf
argument_list|(
name|l_key_to
argument_list|,
literal|"%s_ITER_TO"
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
name|p_set_data
argument_list|(
name|l_key_to
argument_list|,
name|l_plugin_data_len
argument_list|)
expr_stmt|;
block|}
else|else
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|l_percentage
operator|+=
name|l_percentage_step
expr_stmt|;
name|gimp_progress_update
argument_list|(
name|l_percentage
argument_list|)
expr_stmt|;
block|}
comment|/* if(gap_debug) fprintf(stderr, "DEBUG child process exit %d\n", (int)l_rc); */
comment|/* exit(l_rc); */
comment|/* end of childprocess */
block|}
block|}
block|}
name|l_top_layer
operator|=
literal|1
expr_stmt|;
comment|/* wait until exit of childprocess */
comment|/* waitpid(l_child_pid,&l_status, 0); */
block|}
else|else
block|{
comment|/* no iterator available, call plugin with constant values            * for each layer            */
comment|/* call plugin only ONCE Interactive for background layer[n] */
name|l_layer_id
operator|=
name|p_get_indexed_layerid
argument_list|(
name|image_id
argument_list|,
operator|&
name|l_nlayers
argument_list|,
name|l_nlayers
operator|-
literal|1
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_layer_id
operator|<
literal|0
condition|)
block|{
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
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
literal|"DEBUG: NO Varying, apllying %s on Layer id=%d\n"
argument_list|,
name|plugin_name
argument_list|,
operator|(
name|int
operator|)
name|l_layer_id
argument_list|)
expr_stmt|;
name|l_rc
operator|=
name|p_call_plugin
argument_list|(
name|plugin_name
argument_list|,
name|image_id
argument_list|,
name|l_layer_id
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|)
expr_stmt|;
name|l_top_layer
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|l_percentage
operator|+=
name|l_percentage_step
expr_stmt|;
name|gimp_progress_update
argument_list|(
name|l_percentage
argument_list|)
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
operator|(
name|l_rc
operator|>=
literal|0
operator|)
operator|&&
operator|(
name|l_nlayers
operator|>
literal|2
operator|)
condition|)
block|{
comment|/* call plugin foreach layer inbetween           * with runmode GIMP_RUN_WITH_LAST_VALS          * and modify the last values          */
name|l_pit_rc
operator|=
literal|1
expr_stmt|;
for|for
control|(
name|l_idx
operator|=
name|l_nlayers
operator|-
literal|2
init|;
name|l_idx
operator|>=
name|l_top_layer
condition|;
name|l_idx
operator|--
control|)
block|{
if|if
condition|(
name|l_rc
operator|<
literal|0
condition|)
break|break;
if|if
condition|(
name|l_pit_rc
operator|>
literal|0
condition|)
comment|/* last pit_rc was a skip, so ask again for the next layer */
block|{
name|l_pit_rc
operator|=
name|p_pitstop
argument_list|(
name|run_mode
argument_list|,
name|plugin_name
argument_list|,
literal|1
argument_list|,
name|l_step_backup_file
argument_list|,
sizeof|sizeof
argument_list|(
name|l_step_backup_file
argument_list|)
argument_list|,
name|l_idx
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|l_pit_rc
operator|<
literal|0
condition|)
block|{
if|if
condition|(
name|gap_debug
condition|)
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"TERMINATED: by pitstop dialog\n"
argument_list|)
expr_stmt|;
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
block|}
name|l_layer_id
operator|=
name|p_get_indexed_layerid
argument_list|(
name|image_id
argument_list|,
operator|&
name|l_nlayers
argument_list|,
name|l_idx
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_layer_id
operator|<
literal|0
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
name|gap_debug
condition|)
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"DEBUG: apllying %s on Layerstack %d id=%d\n"
argument_list|,
name|plugin_name
argument_list|,
operator|(
name|int
operator|)
name|l_idx
argument_list|,
operator|(
name|int
operator|)
name|l_layer_id
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|l_plugin_iterator
operator|!=
name|NULL
operator|)
operator|&&
operator|(
name|apply_mode
operator|==
name|PTYP_VARYING_LINEAR
operator|)
condition|)
block|{
comment|/* call plugin-specific iterator, to modify                * the plugin's last_values                */
if|if
condition|(
name|gap_debug
condition|)
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"DEBUG: calling iterator %s  current step:%d\n"
argument_list|,
name|l_plugin_iterator
argument_list|,
operator|(
name|int
operator|)
name|l_idx
argument_list|)
expr_stmt|;
name|l_params
operator|=
name|gimp_run_procedure
argument_list|(
name|l_plugin_iterator
argument_list|,
operator|&
name|l_retvals
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|l_nlayers
operator|-
literal|1
argument_list|,
comment|/* total steps  */
name|GIMP_PDB_FLOAT
argument_list|,
operator|(
name|gdouble
operator|)
name|l_idx
argument_list|,
comment|/* current step */
name|GIMP_PDB_INT32
argument_list|,
name|l_plugin_data_len
argument_list|,
comment|/* length of stored data struct */
name|GIMP_PDB_END
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
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"ERROR: iterator %s  failed\n"
argument_list|,
name|l_plugin_iterator
argument_list|)
expr_stmt|;
name|l_rc
operator|=
operator|-
literal|1
expr_stmt|;
block|}
name|g_free
argument_list|(
name|l_params
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|l_rc
operator|<
literal|0
condition|)
break|break;
if|if
condition|(
name|l_pit_rc
operator|==
literal|0
condition|)
comment|/* 0 == continue without further dialogs */
block|{
comment|/* call the plugin itself with runmode RUN_WITH_LAST_VALUES */
name|l_rc
operator|=
name|p_call_plugin
argument_list|(
name|plugin_name
argument_list|,
name|image_id
argument_list|,
name|l_layer_id
argument_list|,
name|GIMP_RUN_WITH_LAST_VALS
argument_list|)
expr_stmt|;
comment|/* check if to save each step to backup file */
if|if
condition|(
operator|(
name|l_step_backup_file
index|[
literal|0
index|]
operator|!=
literal|'\0'
operator|)
operator|&&
operator|(
name|l_step_backup_file
index|[
literal|0
index|]
operator|!=
literal|' '
operator|)
condition|)
block|{
name|printf
argument_list|(
literal|"Saving image to backupfile:%s step = %d\n"
argument_list|,
name|l_step_backup_file
argument_list|,
operator|(
name|int
operator|)
name|l_idx
argument_list|)
expr_stmt|;
name|p_save_xcf
argument_list|(
name|image_id
argument_list|,
name|l_step_backup_file
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|l_percentage
operator|+=
name|l_percentage_step
expr_stmt|;
name|gimp_progress_update
argument_list|(
name|l_percentage
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* end for */
block|}
comment|/* restore the visibility of all layers */
name|p_visibilty_restore
argument_list|(
name|image_id
argument_list|,
name|l_nlayers
argument_list|,
name|l_visible_tab
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|l_visible_tab
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|l_plugin_iterator
operator|!=
name|NULL
condition|)
name|g_free
argument_list|(
name|l_plugin_iterator
argument_list|)
expr_stmt|;
return|return
name|l_rc
return|;
block|}
end_function

begin_comment
comment|/* end p_foreach_multilayer */
end_comment

begin_comment
comment|/* ============================================================================  * gap_proc_anim_apply  * ============================================================================  */
end_comment

begin_function
DECL|function|gap_proc_anim_apply (GimpRunModeType run_mode,gint32 image_id,char * plugin_name)
name|gint
name|gap_proc_anim_apply
parameter_list|(
name|GimpRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|char
modifier|*
name|plugin_name
parameter_list|)
block|{
name|t_gap_db_browse_result
name|l_browser_result
decl_stmt|;
name|t_apply_mode
name|l_apply_mode
decl_stmt|;
name|l_apply_mode
operator|=
name|PAPP_CONSTANT
expr_stmt|;
name|g_current_image_id
operator|=
name|image_id
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
if|if
condition|(
name|gap_db_browser_dialog
argument_list|(
name|_
argument_list|(
literal|"Select Filter for Animated apply"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Apply Constant"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Apply Varying"
argument_list|)
argument_list|,
name|p_constraint_proc
argument_list|,
name|p_constraint_proc_sel1
argument_list|,
name|p_constraint_proc_sel2
argument_list|,
operator|&
name|l_browser_result
argument_list|,
name|TRUE
comment|/* call gtk_init */
argument_list|)
operator|<
literal|0
condition|)
block|{
if|if
condition|(
name|gap_debug
condition|)
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"DEBUG: gap_db_browser_dialog cancelled\n"
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|p_arr_gtk_init
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
comment|/* disable the initial gtk_init in gap_arr_dialog's                             * (gtk_init was done by the browser dialog) 			    */
name|strcpy
argument_list|(
name|plugin_name
argument_list|,
name|l_browser_result
operator|.
name|selected_proc_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|l_browser_result
operator|.
name|button_nr
operator|==
literal|1
condition|)
name|l_apply_mode
operator|=
name|PTYP_VARYING_LINEAR
expr_stmt|;
if|if
condition|(
name|gap_debug
condition|)
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"DEBUG: gap_db_browser_dialog SELECTED:%s\n"
argument_list|,
name|plugin_name
argument_list|)
expr_stmt|;
block|}
return|return
operator|(
name|p_foreach_multilayer
argument_list|(
name|run_mode
argument_list|,
name|image_id
argument_list|,
name|plugin_name
argument_list|,
name|l_apply_mode
argument_list|)
operator|)
return|;
block|}
end_function

end_unit

