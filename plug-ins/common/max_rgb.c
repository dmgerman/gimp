begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* max_rgb.c -- This is a plug-in for the GIMP (1.0's API)  * Author: Shuji Narazaki<narazaki@InetQ.or.jp>  * Time-stamp:<2000-02-08 16:26:24 yasuhiro>  * Version: 0.35  *  * Copyright (C) 1997 Shuji Narazaki<narazaki@InetQ.or.jp>  *  * May 2000 - tim copperfield [timecop@japan.co.jp]  *  * Added a preview mode.  After adding preview mode realised just exactly  * how useless this plugin is :)  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

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

begin_comment
comment|/* Replace them with the right ones */
end_comment

begin_define
DECL|macro|PLUG_IN_NAME
define|#
directive|define
name|PLUG_IN_NAME
value|"plug_in_max_rgb"
end_define

begin_define
DECL|macro|SHORT_NAME
define|#
directive|define
name|SHORT_NAME
value|"max_rgb"
end_define

begin_define
DECL|macro|PROGRESS_UPDATE_NUM
define|#
directive|define
name|PROGRESS_UPDATE_NUM
value|100
end_define

begin_define
DECL|macro|PREVIEW_SIZE
define|#
directive|define
name|PREVIEW_SIZE
value|128
end_define

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
name|fill_preview_with_thumb
parameter_list|(
name|GtkWidget
modifier|*
name|preview_widget
parameter_list|,
name|gint32
name|drawable_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|preview_widget
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpPDBStatusType
name|main_function
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|preview_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|radio_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
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

begin_enum
enum|enum
DECL|enum|__anon2aa94d210103
block|{
DECL|enumerator|MIN_CHANNELS
name|MIN_CHANNELS
init|=
literal|0
block|,
DECL|enumerator|MAX_CHANNELS
name|MAX_CHANNELS
init|=
literal|1
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2aa94d210208
block|{
DECL|member|max_p
name|gint
name|max_p
decl_stmt|;
comment|/* gint, gdouble, and so on */
DECL|typedef|ValueType
block|}
name|ValueType
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2aa94d210308
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|Interface
block|}
name|Interface
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|pvals
specifier|static
name|ValueType
name|pvals
init|=
block|{
name|MAX_CHANNELS
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|interface
specifier|static
name|Interface
name|interface
init|=
block|{
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|preview_bits
specifier|static
name|guchar
modifier|*
name|preview_bits
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|preview
specifier|static
name|GtkWidget
modifier|*
name|preview
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
literal|"Input image (not used)"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"max_p"
block|,
literal|"1 for maximizing, 0 for minimizing"
block|}
block|}
decl_stmt|;
specifier|static
name|gint
name|nargs
init|=
sizeof|sizeof
argument_list|(
name|args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_NAME
argument_list|,
literal|"Return an image in which each pixel holds only "
literal|"the channel that has the maximum value in three "
literal|"(red, green, blue) channels, and other channels "
literal|"are zero-cleared"
argument_list|,
literal|"the help is not yet written for this plug-in since none is needed."
argument_list|,
literal|"Shuji Narazaki (narazaki@InetQ.or.jp)"
argument_list|,
literal|"Shuji Narazaki"
argument_list|,
literal|"May 2000"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Colors/Max RGB..."
argument_list|)
argument_list|,
literal|"RGB*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|nargs
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
DECL|function|run (gchar * name,gint nparams,GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
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
name|GimpRunModeType
name|run_mode
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
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_drawable
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
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
name|gimp_get_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|pvals
argument_list|)
expr_stmt|;
comment|/* Since a channel might be selected, we must check wheter RGB or not. */
if|if
condition|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Max RGB: Can only operate on RGB drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|dialog
argument_list|(
name|drawable
argument_list|)
condition|)
return|return;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/* You must copy the values of parameters to pvals or dialog variables. */
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gimp_get_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|pvals
argument_list|)
expr_stmt|;
break|break;
block|}
name|status
operator|=
name|main_function
argument_list|(
name|drawable
argument_list|,
name|FALSE
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
name|PLUG_IN_NAME
argument_list|,
operator|&
name|pvals
argument_list|,
sizeof|sizeof
argument_list|(
name|ValueType
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|preview_bits
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
DECL|function|main_function (GimpDrawable * drawable,gboolean preview_mode)
name|main_function
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|preview_mode
parameter_list|)
block|{
name|GimpPixelRgn
name|src_rgn
decl_stmt|,
name|dest_rgn
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|,
modifier|*
name|save_dest
decl_stmt|,
modifier|*
name|src_data
decl_stmt|,
modifier|*
name|dest_data
decl_stmt|;
name|gpointer
name|pr
init|=
name|NULL
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|y1
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|gap
decl_stmt|,
name|total
decl_stmt|,
name|processed
init|=
literal|0
decl_stmt|;
name|gint
name|init_value
decl_stmt|,
name|flag
decl_stmt|;
name|gint
name|bpp
init|=
literal|3
decl_stmt|;
name|init_value
operator|=
operator|(
name|pvals
operator|.
name|max_p
operator|>
literal|0
operator|)
condition|?
literal|0
else|:
literal|255
expr_stmt|;
name|flag
operator|=
operator|(
literal|0
operator|<
name|pvals
operator|.
name|max_p
operator|)
condition|?
literal|1
else|:
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|preview_mode
condition|)
block|{
name|x1
operator|=
name|y1
operator|=
literal|0
expr_stmt|;
name|x2
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|buffer_width
expr_stmt|;
name|y2
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|buffer_height
expr_stmt|;
name|gap
operator|=
literal|0
expr_stmt|;
comment|/* no alpha on preview */
name|bpp
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|bpp
expr_stmt|;
block|}
else|else
block|{
name|gap
operator|=
operator|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
operator|)
condition|?
literal|1
else|:
literal|0
expr_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
literal|2
operator|*
operator|(
name|drawable
operator|->
name|width
operator|/
name|gimp_tile_width
argument_list|()
operator|+
literal|1
operator|)
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|2
argument_list|,
operator|&
name|src_rgn
argument_list|,
operator|&
name|dest_rgn
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Max RGB: Scanning..."
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|total
operator|=
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
operator|(
name|y2
operator|-
name|y1
operator|)
expr_stmt|;
if|if
condition|(
name|total
operator|<
literal|1
condition|)
return|return
name|GIMP_PDB_EXECUTION_ERROR
return|;
if|if
condition|(
name|preview_mode
condition|)
block|{
comment|/* preview mode.  here we go again. see nova.c  	 I just don't want to write a prev_pixel_rgn_process 	 and then find out someone else coded a much cooler 	 preview widget / functions for GIMP */
name|src_data
operator|=
name|g_malloc
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|rowstride
operator|*
name|y2
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|src_data
argument_list|,
name|preview_bits
argument_list|,
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|rowstride
operator|*
name|y2
argument_list|)
expr_stmt|;
name|dest_data
operator|=
name|g_malloc
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|rowstride
operator|*
name|y2
argument_list|)
expr_stmt|;
name|save_dest
operator|=
name|dest_data
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|y2
condition|;
name|y
operator|++
control|)
block|{
name|src
operator|=
name|src_data
operator|+
name|y
operator|*
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|rowstride
expr_stmt|;
name|dest
operator|=
name|dest_data
operator|+
name|y
operator|*
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|rowstride
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|x2
condition|;
name|x
operator|++
control|)
block|{
name|gint
name|ch
decl_stmt|,
name|max_ch
init|=
literal|0
decl_stmt|;
name|guchar
name|max
decl_stmt|,
name|tmp_value
decl_stmt|;
name|max
operator|=
name|init_value
expr_stmt|;
for|for
control|(
name|ch
operator|=
literal|0
init|;
name|ch
operator|<
literal|3
condition|;
name|ch
operator|++
control|)
if|if
condition|(
name|flag
operator|*
name|max
operator|<=
name|flag
operator|*
operator|(
name|tmp_value
operator|=
operator|(
operator|*
name|src
operator|++
operator|)
operator|)
condition|)
block|{
if|if
condition|(
name|max
operator|==
name|tmp_value
condition|)
block|{
name|max_ch
operator|+=
literal|1
operator|<<
name|ch
expr_stmt|;
block|}
else|else
block|{
name|max_ch
operator|=
literal|1
operator|<<
name|ch
expr_stmt|;
comment|/* clear memories of old channels */
name|max
operator|=
name|tmp_value
expr_stmt|;
block|}
block|}
for|for
control|(
name|ch
operator|=
literal|0
init|;
name|ch
operator|<
literal|3
condition|;
name|ch
operator|++
control|)
operator|*
name|dest
operator|++
operator|=
call|(
name|guchar
call|)
argument_list|(
operator|(
operator|(
name|max_ch
operator|&
operator|(
literal|1
operator|<<
name|ch
operator|)
operator|)
operator|>
literal|0
operator|)
condition|?
name|max
else|:
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|gap
condition|)
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
block|}
block|}
name|memcpy
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|buffer
argument_list|,
name|save_dest
argument_list|,
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|rowstride
operator|*
name|y2
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|preview
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* normal mode */
for|for
control|(
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|src_rgn
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
name|src
operator|=
name|src_rgn
operator|.
name|data
operator|+
name|y
operator|*
name|src_rgn
operator|.
name|rowstride
expr_stmt|;
name|dest
operator|=
name|dest_rgn
operator|.
name|data
operator|+
name|y
operator|*
name|dest_rgn
operator|.
name|rowstride
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|src_rgn
operator|.
name|w
condition|;
name|x
operator|++
control|)
block|{
name|gint
name|ch
decl_stmt|,
name|max_ch
init|=
literal|0
decl_stmt|;
name|guchar
name|max
decl_stmt|,
name|tmp_value
decl_stmt|;
name|max
operator|=
name|init_value
expr_stmt|;
for|for
control|(
name|ch
operator|=
literal|0
init|;
name|ch
operator|<
literal|3
condition|;
name|ch
operator|++
control|)
if|if
condition|(
name|flag
operator|*
name|max
operator|<=
name|flag
operator|*
operator|(
name|tmp_value
operator|=
operator|(
operator|*
name|src
operator|++
operator|)
operator|)
condition|)
block|{
if|if
condition|(
name|max
operator|==
name|tmp_value
condition|)
block|{
name|max_ch
operator|+=
literal|1
operator|<<
name|ch
expr_stmt|;
block|}
else|else
block|{
name|max_ch
operator|=
literal|1
operator|<<
name|ch
expr_stmt|;
comment|/* clear memories of old channels */
name|max
operator|=
name|tmp_value
expr_stmt|;
block|}
block|}
for|for
control|(
name|ch
operator|=
literal|0
init|;
name|ch
operator|<
literal|3
condition|;
name|ch
operator|++
control|)
operator|*
name|dest
operator|++
operator|=
call|(
name|guchar
call|)
argument_list|(
operator|(
operator|(
name|max_ch
operator|&
operator|(
literal|1
operator|<<
name|ch
operator|)
operator|)
operator|>
literal|0
operator|)
condition|?
name|max
else|:
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|gap
condition|)
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
if|if
condition|(
operator|(
operator|++
name|processed
operator|%
operator|(
name|total
operator|/
name|PROGRESS_UPDATE_NUM
operator|+
literal|1
operator|)
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|processed
operator|/
operator|(
name|gdouble
operator|)
name|total
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
return|return
name|GIMP_PDB_SUCCESS
return|;
block|}
end_function

begin_comment
comment|/* dialog stuff */
end_comment

begin_function
specifier|static
name|gint
DECL|function|dialog (GimpDrawable * drawable)
name|dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|abox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|max
decl_stmt|;
name|GtkWidget
modifier|*
name|min
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"max_rgb"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Max RGB"
argument_list|)
argument_list|,
literal|"max_rgb"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/max_rgb.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"OK"
argument_list|)
argument_list|,
name|ok_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Cancel"
argument_list|)
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dlg
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_main_quit
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Preview"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|abox
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|abox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|abox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|abox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|abox
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|preview
operator|=
name|preview_widget
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|main_function
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_radio_group_new2
argument_list|(
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Parameter Settings"
argument_list|)
argument_list|,
name|radio_callback
argument_list|,
operator|&
name|pvals
operator|.
name|max_p
argument_list|,
operator|(
name|gpointer
operator|)
name|pvals
operator|.
name|max_p
argument_list|,
name|_
argument_list|(
literal|"Hold the Maximal Channels"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|MAX_CHANNELS
argument_list|,
operator|&
name|max
argument_list|,
name|_
argument_list|(
literal|"Hold the Minimal Channels"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|MIN_CHANNELS
argument_list|,
operator|&
name|min
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|max
argument_list|)
argument_list|,
literal|"drawable"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|min
argument_list|)
argument_list|,
literal|"drawable"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
return|return
name|interface
operator|.
name|run
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|radio_callback (GtkWidget * widget,gpointer data)
name|radio_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gimp_radio_button_update
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
block|{
name|drawable
operator|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"drawable"
argument_list|)
expr_stmt|;
name|main_function
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ok_callback (GtkWidget * widget,gpointer data)
name|ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|interface
operator|.
name|run
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|preview_widget (GimpDrawable * drawable)
name|preview_widget
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|gint
name|size
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|preview
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_COLOR
argument_list|)
expr_stmt|;
name|fill_preview_with_thumb
argument_list|(
name|preview
argument_list|,
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|size
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|rowstride
operator|*
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|buffer_height
expr_stmt|;
name|preview_bits
operator|=
name|g_malloc
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|preview_bits
argument_list|,
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|buffer
argument_list|,
name|size
argument_list|)
expr_stmt|;
return|return
name|preview
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|fill_preview_with_thumb (GtkWidget * widget,gint32 drawable_ID)
name|fill_preview_with_thumb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|guchar
modifier|*
name|drawable_data
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
init|=
name|PREVIEW_SIZE
decl_stmt|;
name|gint
name|height
init|=
name|PREVIEW_SIZE
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|;
name|gdouble
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
name|gdouble
name|c0
decl_stmt|,
name|c1
decl_stmt|;
name|guchar
modifier|*
name|p0
decl_stmt|,
modifier|*
name|p1
decl_stmt|;
name|guchar
modifier|*
name|even
decl_stmt|,
modifier|*
name|odd
decl_stmt|;
name|bpp
operator|=
literal|0
expr_stmt|;
comment|/* Only returned */
name|drawable_data
operator|=
name|gimp_drawable_get_thumbnail_data
argument_list|(
name|drawable_ID
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|bpp
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
operator|<
literal|1
operator|||
name|height
operator|<
literal|1
condition|)
return|return;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|widget
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|even
operator|=
name|g_malloc
argument_list|(
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|odd
operator|=
name|g_malloc
argument_list|(
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|src
operator|=
name|drawable_data
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
control|)
block|{
name|p0
operator|=
name|even
expr_stmt|;
name|p1
operator|=
name|odd
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
control|)
block|{
if|if
condition|(
name|bpp
operator|==
literal|4
condition|)
block|{
name|r
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|0
index|]
operator|)
operator|/
literal|255.0
expr_stmt|;
name|g
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|1
index|]
operator|)
operator|/
literal|255.0
expr_stmt|;
name|b
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|2
index|]
operator|)
operator|/
literal|255.0
expr_stmt|;
name|a
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|3
index|]
operator|)
operator|/
literal|255.0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|bpp
operator|==
literal|3
condition|)
block|{
name|r
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|src
index|[
name|x
operator|*
literal|3
operator|+
literal|0
index|]
operator|)
operator|/
literal|255.0
expr_stmt|;
name|g
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|src
index|[
name|x
operator|*
literal|3
operator|+
literal|1
index|]
operator|)
operator|/
literal|255.0
expr_stmt|;
name|b
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|src
index|[
name|x
operator|*
literal|3
operator|+
literal|2
index|]
operator|)
operator|/
literal|255.0
expr_stmt|;
name|a
operator|=
literal|1.0
expr_stmt|;
block|}
else|else
block|{
name|r
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|src
index|[
name|x
operator|*
name|bpp
operator|+
literal|0
index|]
operator|)
operator|/
literal|255.0
expr_stmt|;
name|g
operator|=
name|b
operator|=
name|r
expr_stmt|;
if|if
condition|(
name|bpp
operator|==
literal|2
condition|)
name|a
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|src
index|[
name|x
operator|*
name|bpp
operator|+
literal|1
index|]
operator|)
operator|/
literal|255.0
expr_stmt|;
else|else
name|a
operator|=
literal|1.0
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|x
operator|/
name|GIMP_CHECK_SIZE_SM
operator|)
operator|&
literal|1
condition|)
block|{
name|c0
operator|=
name|GIMP_CHECK_LIGHT
expr_stmt|;
name|c1
operator|=
name|GIMP_CHECK_DARK
expr_stmt|;
block|}
else|else
block|{
name|c0
operator|=
name|GIMP_CHECK_DARK
expr_stmt|;
name|c1
operator|=
name|GIMP_CHECK_LIGHT
expr_stmt|;
block|}
operator|*
name|p0
operator|++
operator|=
operator|(
name|c0
operator|+
operator|(
name|r
operator|-
name|c0
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p0
operator|++
operator|=
operator|(
name|c0
operator|+
operator|(
name|g
operator|-
name|c0
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p0
operator|++
operator|=
operator|(
name|c0
operator|+
operator|(
name|b
operator|-
name|c0
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p1
operator|++
operator|=
operator|(
name|c1
operator|+
operator|(
name|r
operator|-
name|c1
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p1
operator|++
operator|=
operator|(
name|c1
operator|+
operator|(
name|g
operator|-
name|c1
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p1
operator|++
operator|=
operator|(
name|c1
operator|+
operator|(
name|b
operator|-
name|c1
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
block|}
comment|/* for */
if|if
condition|(
operator|(
name|y
operator|/
name|GIMP_CHECK_SIZE_SM
operator|)
operator|&
literal|1
condition|)
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|(
name|guchar
operator|*
operator|)
name|odd
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|width
argument_list|)
expr_stmt|;
else|else
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|(
name|guchar
operator|*
operator|)
name|even
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|src
operator|+=
name|width
operator|*
name|bpp
expr_stmt|;
block|}
name|g_free
argument_list|(
name|even
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|odd
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|drawable_data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

