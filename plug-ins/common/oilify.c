begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1996 Torsten Martinsen  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * $Id$  */
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

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|125
end_define

begin_define
DECL|macro|HISTSIZE
define|#
directive|define
name|HISTSIZE
value|256
end_define

begin_define
DECL|macro|MODE_RGB
define|#
directive|define
name|MODE_RGB
value|0
end_define

begin_define
DECL|macro|MODE_INTEN
define|#
directive|define
name|MODE_INTEN
value|1
end_define

begin_define
DECL|macro|INTENSITY (p)
define|#
directive|define
name|INTENSITY
parameter_list|(
name|p
parameter_list|)
value|((guint) (p[0]*77+p[1]*150+p[2]*29)>> 8)
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27d667910108
block|{
DECL|member|mask_size
name|gdouble
name|mask_size
decl_stmt|;
DECL|member|mode
name|gint
name|mode
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|typedef|OilifyVals
block|}
name|OilifyVals
typedef|;
end_typedef

begin_comment
comment|/* Declare local functions.  */
end_comment

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
name|void
name|oilify
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|oilify_rgb
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|oilify_intensity
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|oilify_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
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

begin_decl_stmt
DECL|variable|ovals
specifier|static
name|OilifyVals
name|ovals
init|=
block|{
literal|7.0
block|,
comment|/* mask size */
literal|0
block|,
comment|/* mode      */
name|TRUE
comment|/* preview   */
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
literal|"Input image (unused)"
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
literal|"mask_size"
block|,
literal|"Oil paint mask size"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"mode"
block|,
literal|"Algorithm {RGB (0), INTENSITY (1)}"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_oilify"
argument_list|,
literal|"Modify the specified drawable to resemble an oil "
literal|"painting"
argument_list|,
literal|"This function performs the well-known oil-paint "
literal|"effect on the specified drawable.  The size of the "
literal|"input mask is specified by 'mask_size'."
argument_list|,
literal|"Torsten Martinsen"
argument_list|,
literal|"Torsten Martinsen"
argument_list|,
literal|"1996"
argument_list|,
name|N_
argument_list|(
literal|"Oili_fy..."
argument_list|)
argument_list|,
literal|"RGB*, GRAY*"
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
literal|"plug_in_oilify"
argument_list|,
literal|"<Image>/Filters/Artistic"
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
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
comment|/*  Get the specified drawable  */
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
literal|2
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
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_oilify"
argument_list|,
operator|&
name|ovals
argument_list|)
expr_stmt|;
comment|/*  First acquire information with a dialog  */
if|if
condition|(
operator|!
name|oilify_dialog
argument_list|(
name|drawable
argument_list|)
condition|)
return|return;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|!=
literal|5
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|ovals
operator|.
name|mask_size
operator|=
operator|(
name|gdouble
operator|)
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|ovals
operator|.
name|mode
operator|=
operator|(
name|gint
operator|)
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
if|if
condition|(
operator|(
name|ovals
operator|.
name|mask_size
operator|<
literal|1.0
operator|)
operator|||
operator|(
operator|(
name|ovals
operator|.
name|mode
operator|!=
name|MODE_INTEN
operator|)
operator|&&
operator|(
name|ovals
operator|.
name|mode
operator|!=
name|MODE_RGB
operator|)
operator|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_oilify"
argument_list|,
operator|&
name|ovals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
comment|/*  Make sure that the drawable is gray or RGB color  */
if|if
condition|(
operator|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
operator|)
operator|&&
operator|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
operator|||
name|gimp_drawable_is_gray
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
operator|)
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Oil Painting..."
argument_list|)
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
name|oilify
argument_list|(
name|drawable
argument_list|,
name|NULL
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
comment|/*  Store data  */
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
name|gimp_set_data
argument_list|(
literal|"plug_in_oilify"
argument_list|,
operator|&
name|ovals
argument_list|,
sizeof|sizeof
argument_list|(
name|OilifyVals
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* gimp_message ("oilify: cannot operate on indexed color images"); */
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * For each RGB channel, replace the pixel at (x,y) with the  * value that occurs most often in the n x n chunk centered  * at (x,y).  */
end_comment

begin_function
specifier|static
name|void
DECL|function|oilify_rgb (GimpDrawable * drawable,GimpPreview * preview)
name|oilify_rgb
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpPixelRgn
name|src_rgn
decl_stmt|,
name|dest_rgn
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|guchar
modifier|*
name|src_row
decl_stmt|,
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|dest_row
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|c
decl_stmt|,
name|b
decl_stmt|,
name|xx
decl_stmt|,
name|yy
decl_stmt|,
name|n
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|x3
decl_stmt|,
name|y3
decl_stmt|,
name|x4
decl_stmt|,
name|y4
decl_stmt|;
name|gint
name|Cnt
index|[
literal|4
index|]
decl_stmt|;
name|gint
name|Hist
index|[
literal|4
index|]
index|[
name|HISTSIZE
index|]
decl_stmt|;
name|gpointer
name|pr1
decl_stmt|;
name|gint
name|progress
decl_stmt|,
name|max_progress
decl_stmt|;
name|guchar
modifier|*
name|src_buf
decl_stmt|;
comment|/*  get the selection bounds  */
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_preview_get_position
argument_list|(
name|preview
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|gimp_preview_get_size
argument_list|(
name|preview
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|x2
operator|=
name|x1
operator|+
name|width
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
name|height
expr_stmt|;
block|}
else|else
block|{
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
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
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
block|}
name|progress
operator|=
literal|0
expr_stmt|;
name|max_progress
operator|=
name|width
operator|*
name|height
expr_stmt|;
name|bytes
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|n
operator|=
operator|(
name|int
operator|)
name|ovals
operator|.
name|mask_size
operator|/
literal|2
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
name|width
argument_list|,
name|height
argument_list|,
operator|(
name|preview
operator|==
name|NULL
operator|)
argument_list|,
name|TRUE
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
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|src_buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|height
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|src_buf
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
for|for
control|(
name|pr1
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
argument_list|,
operator|&
name|dest_rgn
argument_list|)
init|;
name|pr1
operator|!=
name|NULL
condition|;
name|pr1
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr1
argument_list|)
control|)
block|{
name|dest_row
operator|=
name|dest_rgn
operator|.
name|data
expr_stmt|;
for|for
control|(
name|y
operator|=
name|dest_rgn
operator|.
name|y
init|;
name|y
operator|<
operator|(
name|dest_rgn
operator|.
name|y
operator|+
name|dest_rgn
operator|.
name|h
operator|)
condition|;
name|y
operator|++
control|)
block|{
name|dest
operator|=
name|dest_row
expr_stmt|;
for|for
control|(
name|x
operator|=
name|dest_rgn
operator|.
name|x
init|;
name|x
operator|<
operator|(
name|dest_rgn
operator|.
name|x
operator|+
name|dest_rgn
operator|.
name|w
operator|)
condition|;
name|x
operator|++
control|)
block|{
name|x3
operator|=
name|CLAMP
argument_list|(
operator|(
name|x
operator|-
name|n
operator|)
argument_list|,
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|y3
operator|=
name|CLAMP
argument_list|(
operator|(
name|y
operator|-
name|n
operator|)
argument_list|,
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|x4
operator|=
name|CLAMP
argument_list|(
operator|(
name|x
operator|+
name|n
operator|+
literal|1
operator|)
argument_list|,
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|y4
operator|=
name|CLAMP
argument_list|(
operator|(
name|y
operator|+
name|n
operator|+
literal|1
operator|)
argument_list|,
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|Cnt
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|Cnt
argument_list|)
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|Hist
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|Hist
argument_list|)
argument_list|)
expr_stmt|;
name|src_row
operator|=
name|src_buf
operator|+
operator|(
operator|(
name|y3
operator|-
name|y1
operator|)
operator|*
name|width
operator|+
operator|(
name|x3
operator|-
name|x1
operator|)
operator|)
operator|*
name|bytes
expr_stmt|;
for|for
control|(
name|yy
operator|=
name|y3
init|;
name|yy
operator|<
name|y4
condition|;
name|yy
operator|++
control|)
block|{
name|src
operator|=
name|src_row
expr_stmt|;
for|for
control|(
name|xx
operator|=
name|x3
init|;
name|xx
operator|<
name|x4
condition|;
name|xx
operator|++
control|)
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bytes
condition|;
name|b
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|c
operator|=
operator|++
name|Hist
index|[
name|b
index|]
index|[
name|src
index|[
name|b
index|]
index|]
operator|)
operator|>
name|Cnt
index|[
name|b
index|]
condition|)
block|{
name|dest
index|[
name|b
index|]
operator|=
name|src
index|[
name|b
index|]
expr_stmt|;
name|Cnt
index|[
name|b
index|]
operator|=
name|c
expr_stmt|;
block|}
block|}
name|src
operator|+=
name|bytes
expr_stmt|;
block|}
name|src_row
operator|+=
name|width
operator|*
name|bytes
expr_stmt|;
block|}
name|dest
operator|+=
name|bytes
expr_stmt|;
block|}
name|dest_row
operator|+=
name|dest_rgn
operator|.
name|rowstride
expr_stmt|;
block|}
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_drawable_preview_draw_region
argument_list|(
name|GIMP_DRAWABLE_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
operator|&
name|dest_rgn
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|progress
operator|+=
name|dest_rgn
operator|.
name|w
operator|*
name|dest_rgn
operator|.
name|h
expr_stmt|;
if|if
condition|(
operator|(
name|progress
operator|%
literal|5
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|progress
operator|/
operator|(
name|double
operator|)
name|max_progress
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|preview
condition|)
block|{
comment|/*  update the oil-painted region  */
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  * For each RGB channel, replace the pixel at (x,y) with the  * value that occurs most often in the n x n chunk centered  * at (x,y). Histogram is based on intensity.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|oilify_intensity (GimpDrawable * drawable,GimpPreview * preview)
name|oilify_intensity
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpPixelRgn
name|src_rgn
decl_stmt|,
name|dest_rgn
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|guchar
modifier|*
name|src_row
decl_stmt|,
modifier|*
name|src
decl_stmt|,
modifier|*
name|selected_src
init|=
name|NULL
decl_stmt|;
name|guchar
modifier|*
name|dest_row
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|c
decl_stmt|,
name|xx
decl_stmt|,
name|yy
decl_stmt|,
name|n
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|x3
decl_stmt|,
name|y3
decl_stmt|,
name|x4
decl_stmt|,
name|y4
decl_stmt|;
name|gint
name|Cnt
decl_stmt|;
name|gint
name|Hist
index|[
name|HISTSIZE
index|]
decl_stmt|;
name|gpointer
name|pr1
decl_stmt|;
name|gint
name|progress
decl_stmt|,
name|max_progress
decl_stmt|;
name|guchar
modifier|*
name|src_buf
decl_stmt|;
comment|/*  get the selection bounds  */
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_preview_get_position
argument_list|(
name|preview
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|gimp_preview_get_size
argument_list|(
name|preview
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|x2
operator|=
name|x1
operator|+
name|width
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
name|height
expr_stmt|;
block|}
else|else
block|{
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
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
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
block|}
name|bytes
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|progress
operator|=
literal|0
expr_stmt|;
name|max_progress
operator|=
name|width
operator|*
name|height
expr_stmt|;
name|n
operator|=
operator|(
name|int
operator|)
name|ovals
operator|.
name|mask_size
operator|/
literal|2
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
name|width
argument_list|,
name|height
argument_list|,
operator|(
name|preview
operator|==
name|NULL
operator|)
argument_list|,
name|TRUE
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
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|src_buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|height
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|src_buf
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
for|for
control|(
name|pr1
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
argument_list|,
operator|&
name|dest_rgn
argument_list|)
init|;
name|pr1
operator|!=
name|NULL
condition|;
name|pr1
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr1
argument_list|)
control|)
block|{
name|dest_row
operator|=
name|dest_rgn
operator|.
name|data
expr_stmt|;
for|for
control|(
name|y
operator|=
name|dest_rgn
operator|.
name|y
init|;
name|y
operator|<
operator|(
name|dest_rgn
operator|.
name|y
operator|+
name|dest_rgn
operator|.
name|h
operator|)
condition|;
name|y
operator|++
control|)
block|{
name|dest
operator|=
name|dest_row
expr_stmt|;
for|for
control|(
name|x
operator|=
name|dest_rgn
operator|.
name|x
init|;
name|x
operator|<
operator|(
name|dest_rgn
operator|.
name|x
operator|+
name|dest_rgn
operator|.
name|w
operator|)
condition|;
name|x
operator|++
control|)
block|{
name|Cnt
operator|=
literal|0
expr_stmt|;
name|memset
argument_list|(
name|Hist
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|Hist
argument_list|)
argument_list|)
expr_stmt|;
name|x3
operator|=
name|CLAMP
argument_list|(
operator|(
name|x
operator|-
name|n
operator|)
argument_list|,
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|y3
operator|=
name|CLAMP
argument_list|(
operator|(
name|y
operator|-
name|n
operator|)
argument_list|,
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|x4
operator|=
name|CLAMP
argument_list|(
operator|(
name|x
operator|+
name|n
operator|+
literal|1
operator|)
argument_list|,
name|x1
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|y4
operator|=
name|CLAMP
argument_list|(
operator|(
name|y
operator|+
name|n
operator|+
literal|1
operator|)
argument_list|,
name|y1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|src_row
operator|=
name|src_buf
operator|+
operator|(
operator|(
name|y3
operator|-
name|y1
operator|)
operator|*
name|width
operator|+
operator|(
name|x3
operator|-
name|x1
operator|)
operator|)
operator|*
name|bytes
expr_stmt|;
for|for
control|(
name|yy
operator|=
name|y3
init|;
name|yy
operator|<
name|y4
condition|;
name|yy
operator|++
control|)
block|{
name|src
operator|=
name|src_row
expr_stmt|;
for|for
control|(
name|xx
operator|=
name|x3
init|;
name|xx
operator|<
name|x4
condition|;
name|xx
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|c
operator|=
operator|++
name|Hist
index|[
name|INTENSITY
argument_list|(
name|src
argument_list|)
index|]
operator|)
operator|>
name|Cnt
condition|)
block|{
name|Cnt
operator|=
name|c
expr_stmt|;
name|selected_src
operator|=
name|src
expr_stmt|;
block|}
name|src
operator|+=
name|bytes
expr_stmt|;
block|}
name|src_row
operator|+=
name|width
operator|*
name|bytes
expr_stmt|;
block|}
name|memcpy
argument_list|(
name|dest
argument_list|,
name|selected_src
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
name|dest
operator|+=
name|bytes
expr_stmt|;
block|}
name|dest_row
operator|+=
name|dest_rgn
operator|.
name|rowstride
expr_stmt|;
block|}
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_drawable_preview_draw_region
argument_list|(
name|GIMP_DRAWABLE_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
operator|&
name|dest_rgn
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|progress
operator|+=
name|dest_rgn
operator|.
name|w
operator|*
name|dest_rgn
operator|.
name|h
expr_stmt|;
if|if
condition|(
operator|(
name|progress
operator|%
literal|5
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|progress
operator|/
operator|(
name|double
operator|)
name|max_progress
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|preview
condition|)
block|{
comment|/*  update the oil-painted region  */
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|oilify (GimpDrawable * drawable,GimpPreview * preview)
name|oilify
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
operator|&&
operator|(
name|ovals
operator|.
name|mode
operator|==
name|MODE_INTEN
operator|)
condition|)
name|oilify_intensity
argument_list|(
name|drawable
argument_list|,
name|preview
argument_list|)
expr_stmt|;
else|else
name|oilify_rgb
argument_list|(
name|drawable
argument_list|,
name|preview
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|oilify_dialog (GimpDrawable * drawable)
name|oilify_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|table
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
literal|"oilify"
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
literal|"Oilify"
argument_list|)
argument_list|,
literal|"oilify"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"plug-in-oilify"
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
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_drawable_preview_new
argument_list|(
name|drawable
argument_list|,
operator|&
name|ovals
operator|.
name|preview
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|preview
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
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|preview
argument_list|,
literal|"invalidated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|oilify
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Mask size:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|ovals
operator|.
name|mask_size
argument_list|,
literal|3.0
argument_list|,
literal|50.0
argument_list|,
literal|1.0
argument_list|,
literal|5.0
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
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|ovals
operator|.
name|mask_size
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Use intensity algorithm"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach
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
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|ovals
operator|.
name|mode
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
name|ovals
operator|.
name|mode
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
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

