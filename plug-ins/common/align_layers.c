begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* align_layers.c  * Author: Shuji Narazaki<narazaki@InetQ.or.jp>  * Version:  0.26  *  * Copyright (C) 1997-1998 Shuji Narazaki<narazaki@InetQ.or.jp>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-align-layers"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"align_layers"
end_define

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|150
end_define

begin_enum
enum|enum
DECL|enum|__anon2b76337d0103
block|{
DECL|enumerator|H_NONE
name|H_NONE
block|,
DECL|enumerator|H_COLLECT
name|H_COLLECT
block|,
DECL|enumerator|LEFT2RIGHT
name|LEFT2RIGHT
block|,
DECL|enumerator|RIGHT2LEFT
name|RIGHT2LEFT
block|,
DECL|enumerator|SNAP2HGRID
name|SNAP2HGRID
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b76337d0203
block|{
DECL|enumerator|H_BASE_LEFT
name|H_BASE_LEFT
block|,
DECL|enumerator|H_BASE_CENTER
name|H_BASE_CENTER
block|,
DECL|enumerator|H_BASE_RIGHT
name|H_BASE_RIGHT
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b76337d0303
block|{
DECL|enumerator|V_NONE
name|V_NONE
block|,
DECL|enumerator|V_COLLECT
name|V_COLLECT
block|,
DECL|enumerator|TOP2BOTTOM
name|TOP2BOTTOM
block|,
DECL|enumerator|BOTTOM2TOP
name|BOTTOM2TOP
block|,
DECL|enumerator|SNAP2VGRID
name|SNAP2VGRID
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b76337d0403
block|{
DECL|enumerator|V_BASE_TOP
name|V_BASE_TOP
block|,
DECL|enumerator|V_BASE_CENTER
name|V_BASE_CENTER
block|,
DECL|enumerator|V_BASE_BOTTOM
name|V_BASE_BOTTOM
block|}
enum|;
end_enum

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
name|GimpPDBStatusType
name|align_layers
parameter_list|(
name|gint32
name|image_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|align_layers_get_align_offsets
parameter_list|(
name|gint32
name|drawable_id
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|align_layers_dialog
parameter_list|(
name|void
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
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* dialog variables */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b76337d0508
block|{
DECL|member|h_style
name|gint
name|h_style
decl_stmt|;
DECL|member|h_base
name|gint
name|h_base
decl_stmt|;
DECL|member|v_style
name|gint
name|v_style
decl_stmt|;
DECL|member|v_base
name|gint
name|v_base
decl_stmt|;
DECL|member|ignore_bottom
name|gboolean
name|ignore_bottom
decl_stmt|;
DECL|member|base_is_bottom_layer
name|gboolean
name|base_is_bottom_layer
decl_stmt|;
DECL|member|grid_size
name|gint
name|grid_size
decl_stmt|;
DECL|typedef|ValueType
block|}
name|ValueType
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|VALS
specifier|static
name|ValueType
name|VALS
init|=
block|{
name|H_NONE
block|,
name|H_BASE_LEFT
block|,
name|V_NONE
block|,
name|V_BASE_TOP
block|,
name|TRUE
block|,
name|FALSE
block|,
literal|10
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
literal|"Input drawable (not used)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"link-after-alignment"
block|,
literal|"Link the visible layers after alignment"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"use-bottom"
block|,
literal|"use the bottom layer as the base of alignment"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
literal|"Align visible layers"
argument_list|,
literal|"Align visible layers"
argument_list|,
literal|"Shuji Narazaki<narazaki@InetQ.or.jp>"
argument_list|,
literal|"Shuji Narazaki"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"Align _Visible Layers..."
argument_list|)
argument_list|,
literal|"RGB*,GRAY*,INDEXED*"
argument_list|,
name|GIMP_PLUGIN
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
name|gimp_plugin_menu_register
argument_list|(
name|PLUG_IN_PROC
argument_list|,
literal|"<Image>/Image/Arrange"
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
name|GIMP_PDB_EXECUTION_ERROR
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|gint
name|image_id
decl_stmt|,
name|layer_num
decl_stmt|;
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
name|image_id
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
name|INIT_I18N
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
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
name|gimp_image_get_layers
argument_list|(
name|image_id
argument_list|,
operator|&
name|layer_num
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer_num
operator|<
literal|2
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"There are not enough layers to align."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|VALS
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|align_layers_dialog
argument_list|()
condition|)
return|return;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|VALS
argument_list|)
expr_stmt|;
break|break;
block|}
name|status
operator|=
name|align_layers
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
operator|&&
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|gimp_set_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|VALS
argument_list|,
sizeof|sizeof
argument_list|(
name|ValueType
argument_list|)
argument_list|)
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

begin_function
specifier|static
name|GimpPDBStatusType
DECL|function|align_layers (gint32 image_id)
name|align_layers
parameter_list|(
name|gint32
name|image_id
parameter_list|)
block|{
name|gint
name|layer_num
init|=
literal|0
decl_stmt|;
name|gint
name|visible_layer_num
init|=
literal|0
decl_stmt|;
name|gint
modifier|*
name|layers
init|=
name|NULL
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|gint
name|vindex
decl_stmt|;
name|gint
name|step_x
init|=
literal|0
decl_stmt|;
name|gint
name|step_y
init|=
literal|0
decl_stmt|;
name|gint
name|x
init|=
literal|0
decl_stmt|;
name|gint
name|y
init|=
literal|0
decl_stmt|;
name|gint
name|orig_x
init|=
literal|0
decl_stmt|;
name|gint
name|orig_y
init|=
literal|0
decl_stmt|;
name|gint
name|offset_x
init|=
literal|0
decl_stmt|;
name|gint
name|offset_y
init|=
literal|0
decl_stmt|;
name|gint
name|base_x
init|=
literal|0
decl_stmt|;
name|gint
name|base_y
init|=
literal|0
decl_stmt|;
name|gint
name|bg_index
init|=
literal|0
decl_stmt|;
name|layers
operator|=
name|gimp_image_get_layers
argument_list|(
name|image_id
argument_list|,
operator|&
name|layer_num
argument_list|)
expr_stmt|;
name|bg_index
operator|=
name|layer_num
operator|-
literal|1
expr_stmt|;
for|for
control|(
name|index
operator|=
literal|0
init|;
name|index
operator|<
name|layer_num
condition|;
name|index
operator|++
control|)
block|{
if|if
condition|(
name|gimp_drawable_get_visible
argument_list|(
name|layers
index|[
name|index
index|]
argument_list|)
condition|)
name|visible_layer_num
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|VALS
operator|.
name|ignore_bottom
condition|)
block|{
name|layer_num
operator|--
expr_stmt|;
if|if
condition|(
name|gimp_drawable_get_visible
argument_list|(
name|layers
index|[
name|bg_index
index|]
argument_list|)
condition|)
name|visible_layer_num
operator|--
expr_stmt|;
block|}
if|if
condition|(
literal|0
operator|<
name|visible_layer_num
condition|)
block|{
name|gint
name|min_x
init|=
name|G_MAXINT
decl_stmt|;
name|gint
name|min_y
init|=
name|G_MAXINT
decl_stmt|;
name|gint
name|max_x
init|=
name|G_MININT
decl_stmt|;
name|gint
name|max_y
init|=
name|G_MININT
decl_stmt|;
comment|/* 0 is the top layer */
for|for
control|(
name|index
operator|=
literal|0
init|;
name|index
operator|<
name|layer_num
condition|;
name|index
operator|++
control|)
block|{
if|if
condition|(
name|gimp_drawable_get_visible
argument_list|(
name|layers
index|[
name|index
index|]
argument_list|)
condition|)
block|{
name|gimp_drawable_offsets
argument_list|(
name|layers
index|[
name|index
index|]
argument_list|,
operator|&
name|orig_x
argument_list|,
operator|&
name|orig_y
argument_list|)
expr_stmt|;
name|align_layers_get_align_offsets
argument_list|(
name|layers
index|[
name|index
index|]
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
name|orig_x
operator|+=
name|offset_x
expr_stmt|;
name|orig_y
operator|+=
name|offset_y
expr_stmt|;
if|if
condition|(
name|orig_x
operator|<
name|min_x
condition|)
name|min_x
operator|=
name|orig_x
expr_stmt|;
if|if
condition|(
name|max_x
operator|<
name|orig_x
condition|)
name|max_x
operator|=
name|orig_x
expr_stmt|;
if|if
condition|(
name|orig_y
operator|<
name|min_y
condition|)
name|min_y
operator|=
name|orig_y
expr_stmt|;
if|if
condition|(
name|max_y
operator|<
name|orig_y
condition|)
name|max_y
operator|=
name|orig_y
expr_stmt|;
block|}
block|}
if|if
condition|(
name|VALS
operator|.
name|base_is_bottom_layer
condition|)
block|{
name|gimp_drawable_offsets
argument_list|(
name|layers
index|[
name|bg_index
index|]
argument_list|,
operator|&
name|orig_x
argument_list|,
operator|&
name|orig_y
argument_list|)
expr_stmt|;
name|align_layers_get_align_offsets
argument_list|(
name|layers
index|[
name|bg_index
index|]
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
name|orig_x
operator|+=
name|offset_x
expr_stmt|;
name|orig_y
operator|+=
name|offset_y
expr_stmt|;
name|base_x
operator|=
name|min_x
operator|=
name|orig_x
expr_stmt|;
name|base_y
operator|=
name|min_y
operator|=
name|orig_y
expr_stmt|;
block|}
if|if
condition|(
name|visible_layer_num
operator|>
literal|1
condition|)
block|{
name|step_x
operator|=
operator|(
name|max_x
operator|-
name|min_x
operator|)
operator|/
operator|(
name|visible_layer_num
operator|-
literal|1
operator|)
expr_stmt|;
name|step_y
operator|=
operator|(
name|max_y
operator|-
name|min_y
operator|)
operator|/
operator|(
name|visible_layer_num
operator|-
literal|1
operator|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|VALS
operator|.
name|h_style
operator|==
name|LEFT2RIGHT
operator|)
operator|||
operator|(
name|VALS
operator|.
name|h_style
operator|==
name|RIGHT2LEFT
operator|)
condition|)
name|base_x
operator|=
name|min_x
expr_stmt|;
if|if
condition|(
operator|(
name|VALS
operator|.
name|v_style
operator|==
name|TOP2BOTTOM
operator|)
operator|||
operator|(
name|VALS
operator|.
name|v_style
operator|==
name|BOTTOM2TOP
operator|)
condition|)
name|base_y
operator|=
name|min_y
expr_stmt|;
block|}
name|gimp_image_undo_group_start
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
for|for
control|(
name|vindex
operator|=
operator|-
literal|1
operator|,
name|index
operator|=
literal|0
init|;
name|index
operator|<
name|layer_num
condition|;
name|index
operator|++
control|)
block|{
if|if
condition|(
name|gimp_drawable_get_visible
argument_list|(
name|layers
index|[
name|index
index|]
argument_list|)
condition|)
name|vindex
operator|++
expr_stmt|;
else|else
continue|continue;
name|gimp_drawable_offsets
argument_list|(
name|layers
index|[
name|index
index|]
argument_list|,
operator|&
name|orig_x
argument_list|,
operator|&
name|orig_y
argument_list|)
expr_stmt|;
name|align_layers_get_align_offsets
argument_list|(
name|layers
index|[
name|index
index|]
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|VALS
operator|.
name|h_style
condition|)
block|{
case|case
name|H_NONE
case|:
name|x
operator|=
name|orig_x
expr_stmt|;
break|break;
case|case
name|H_COLLECT
case|:
name|x
operator|=
name|base_x
operator|-
name|offset_x
expr_stmt|;
break|break;
case|case
name|LEFT2RIGHT
case|:
name|x
operator|=
operator|(
name|base_x
operator|+
name|vindex
operator|*
name|step_x
operator|)
operator|-
name|offset_x
expr_stmt|;
break|break;
case|case
name|RIGHT2LEFT
case|:
name|x
operator|=
operator|(
name|base_x
operator|+
operator|(
name|visible_layer_num
operator|-
name|vindex
operator|-
literal|1
operator|)
operator|*
name|step_x
operator|)
operator|-
name|offset_x
expr_stmt|;
break|break;
case|case
name|SNAP2HGRID
case|:
name|x
operator|=
name|VALS
operator|.
name|grid_size
operator|*
call|(
name|int
call|)
argument_list|(
operator|(
name|orig_x
operator|+
name|offset_x
operator|+
name|VALS
operator|.
name|grid_size
operator|/
literal|2
operator|)
operator|/
name|VALS
operator|.
name|grid_size
argument_list|)
operator|-
name|offset_x
expr_stmt|;
break|break;
block|}
switch|switch
condition|(
name|VALS
operator|.
name|v_style
condition|)
block|{
case|case
name|V_NONE
case|:
name|y
operator|=
name|orig_y
expr_stmt|;
break|break;
case|case
name|V_COLLECT
case|:
name|y
operator|=
name|base_y
operator|-
name|offset_y
expr_stmt|;
break|break;
case|case
name|TOP2BOTTOM
case|:
name|y
operator|=
operator|(
name|base_y
operator|+
name|vindex
operator|*
name|step_y
operator|)
operator|-
name|offset_y
expr_stmt|;
break|break;
case|case
name|BOTTOM2TOP
case|:
name|y
operator|=
operator|(
name|base_y
operator|+
operator|(
name|visible_layer_num
operator|-
name|vindex
operator|-
literal|1
operator|)
operator|*
name|step_y
operator|)
operator|-
name|offset_y
expr_stmt|;
break|break;
case|case
name|SNAP2VGRID
case|:
name|y
operator|=
name|VALS
operator|.
name|grid_size
operator|*
call|(
name|int
call|)
argument_list|(
operator|(
name|orig_y
operator|+
name|offset_y
operator|+
name|VALS
operator|.
name|grid_size
operator|/
literal|2
operator|)
operator|/
name|VALS
operator|.
name|grid_size
argument_list|)
operator|-
name|offset_y
expr_stmt|;
break|break;
block|}
name|gimp_layer_set_offsets
argument_list|(
name|layers
index|[
name|index
index|]
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
name|gimp_image_undo_group_end
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
return|return
name|GIMP_PDB_SUCCESS
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|align_layers_get_align_offsets (gint32 drawable_id,gint * x,gint * y)
name|align_layers_get_align_offsets
parameter_list|(
name|gint32
name|drawable_id
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|layer
init|=
name|gimp_drawable_get
argument_list|(
name|drawable_id
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|VALS
operator|.
name|h_base
condition|)
block|{
case|case
name|H_BASE_LEFT
case|:
operator|*
name|x
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|H_BASE_CENTER
case|:
operator|*
name|x
operator|=
name|layer
operator|->
name|width
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|H_BASE_RIGHT
case|:
operator|*
name|x
operator|=
name|layer
operator|->
name|width
expr_stmt|;
break|break;
default|default:
operator|*
name|x
operator|=
literal|0
expr_stmt|;
break|break;
block|}
switch|switch
condition|(
name|VALS
operator|.
name|v_base
condition|)
block|{
case|case
name|V_BASE_TOP
case|:
operator|*
name|y
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|V_BASE_CENTER
case|:
operator|*
name|y
operator|=
name|layer
operator|->
name|height
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|V_BASE_BOTTOM
case|:
operator|*
name|y
operator|=
name|layer
operator|->
name|height
expr_stmt|;
break|break;
default|default:
operator|*
name|y
operator|=
literal|0
expr_stmt|;
break|break;
block|}
name|gimp_drawable_detach
argument_list|(
name|layer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|align_layers_dialog (void)
name|align_layers_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Align Visible Layers"
argument_list|)
argument_list|,
name|PLUG_IN_BINARY
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|PLUG_IN_PROC
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_window_set_transient
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|7
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_int_combo_box_new
argument_list|(
name|_
argument_list|(
literal|"None"
argument_list|)
argument_list|,
name|H_NONE
argument_list|,
name|_
argument_list|(
literal|"Collect"
argument_list|)
argument_list|,
name|H_COLLECT
argument_list|,
name|_
argument_list|(
literal|"Fill (left to right)"
argument_list|)
argument_list|,
name|LEFT2RIGHT
argument_list|,
name|_
argument_list|(
literal|"Fill (right to left)"
argument_list|)
argument_list|,
name|RIGHT2LEFT
argument_list|,
name|_
argument_list|(
literal|"Snap to grid"
argument_list|)
argument_list|,
name|SNAP2HGRID
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|VALS
operator|.
name|h_style
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_combo_box_get_active
argument_list|)
argument_list|,
operator|&
name|VALS
operator|.
name|h_style
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Horizontal style:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|combo
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_int_combo_box_new
argument_list|(
name|_
argument_list|(
literal|"Left edge"
argument_list|)
argument_list|,
name|H_BASE_LEFT
argument_list|,
name|_
argument_list|(
literal|"Center"
argument_list|)
argument_list|,
name|H_BASE_CENTER
argument_list|,
name|_
argument_list|(
literal|"Right edge"
argument_list|)
argument_list|,
name|H_BASE_RIGHT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|VALS
operator|.
name|h_base
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_combo_box_get_active
argument_list|)
argument_list|,
operator|&
name|VALS
operator|.
name|h_base
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Ho_rizontal base:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|combo
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_int_combo_box_new
argument_list|(
name|_
argument_list|(
literal|"None"
argument_list|)
argument_list|,
name|V_NONE
argument_list|,
name|_
argument_list|(
literal|"Collect"
argument_list|)
argument_list|,
name|V_COLLECT
argument_list|,
name|_
argument_list|(
literal|"Fill (top to bottom)"
argument_list|)
argument_list|,
name|TOP2BOTTOM
argument_list|,
name|_
argument_list|(
literal|"Fill (bottom to top)"
argument_list|)
argument_list|,
name|BOTTOM2TOP
argument_list|,
name|_
argument_list|(
literal|"Snap to grid"
argument_list|)
argument_list|,
name|SNAP2VGRID
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|VALS
operator|.
name|v_style
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_combo_box_get_active
argument_list|)
argument_list|,
operator|&
name|VALS
operator|.
name|v_style
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"_Vertical style:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|combo
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_int_combo_box_new
argument_list|(
name|_
argument_list|(
literal|"Top edge"
argument_list|)
argument_list|,
name|V_BASE_TOP
argument_list|,
name|_
argument_list|(
literal|"Center"
argument_list|)
argument_list|,
name|V_BASE_CENTER
argument_list|,
name|_
argument_list|(
literal|"Bottom edge"
argument_list|)
argument_list|,
name|V_BASE_BOTTOM
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|VALS
operator|.
name|v_base
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_combo_box_get_active
argument_list|)
argument_list|,
operator|&
name|VALS
operator|.
name|v_base
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|3
argument_list|,
name|_
argument_list|(
literal|"Ver_tical base:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|combo
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|4
argument_list|,
name|_
argument_list|(
literal|"_Grid size:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|VALS
operator|.
name|grid_size
argument_list|,
literal|0
argument_list|,
literal|200
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|,
name|TRUE
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
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|VALS
operator|.
name|grid_size
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Ignore the bottom layer even if visible"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|VALS
operator|.
name|ignore_bottom
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|toggle
argument_list|,
literal|0
argument_list|,
literal|3
argument_list|,
literal|5
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|VALS
operator|.
name|ignore_bottom
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Use the (invisible) bottom layer as the base"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|VALS
operator|.
name|base_is_bottom_layer
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|toggle
argument_list|,
literal|0
argument_list|,
literal|3
argument_list|,
literal|6
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|VALS
operator|.
name|base_is_bottom_layer
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

end_unit

