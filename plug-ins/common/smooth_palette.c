begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*    smooth palette - derive smooth palette from image    Copyright (C) 1997  Scott Draves<spot@cs.cmu.edu>     The GIMP -- an image manipulation program    Copyright (C) 1995 Spencer Kimball and Peter Mattis     This program is free software; you can redistribute it and/or modify    it under the terms of the GNU General Public License as published by    the Free Software Foundation; either version 2 of the License, or    (at your option) any later version.     This program is distributed in the hope that it will be useful,    but WITHOUT ANY WARRANTY; without even the implied warranty of    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    GNU General Public License for more details.     You should have received a copy of the GNU General Public License    along with this program; if not, write to the Free Software    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. */
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

begin_comment
comment|/* Declare local functions. */
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
name|gboolean
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
name|gint32
name|doit
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint32
modifier|*
name|layer_id
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
literal|"width"
block|,
literal|"Width"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"height"
block|,
literal|"Height"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"ntries"
block|,
literal|"Search Depth"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"show_image"
block|,
literal|"Show Image?"
block|}
block|}
decl_stmt|;
specifier|static
name|GimpParamDef
name|return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"new_image"
block|,
literal|"Output image"
block|}
block|,
block|{
name|GIMP_PDB_LAYER
block|,
literal|"new_layer"
block|,
literal|"Output layer"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_smooth_palette"
argument_list|,
literal|"derive smooth palette from image"
argument_list|,
literal|"help!"
argument_list|,
literal|"Scott Draves"
argument_list|,
literal|"Scott Draves"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"Smoo_th Palette..."
argument_list|)
argument_list|,
literal|"RGB*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|return_vals
argument_list|)
argument_list|,
name|args
argument_list|,
name|return_vals
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
literal|"plug_in_smooth_palette"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Colors"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_struct
specifier|static
struct|struct
DECL|struct|__anon2afb7fcc0108
block|{
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|ntries
name|gint
name|ntries
decl_stmt|;
DECL|member|try_size
name|gint
name|try_size
decl_stmt|;
DECL|member|show_image
name|gint
name|show_image
decl_stmt|;
DECL|variable|config
block|}
name|config
init|=
block|{
literal|256
block|,
literal|64
block|,
literal|50
block|,
literal|10000
block|,
literal|1
block|}
struct|;
end_struct

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
literal|3
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
name|GimpDrawable
modifier|*
name|drawable
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
name|INIT_I18N
argument_list|()
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|3
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
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_IMAGE
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_LAYER
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
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
name|gimp_get_data
argument_list|(
literal|"plug_in_smooth_palette"
argument_list|,
operator|&
name|config
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|nparams
operator|!=
literal|7
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|config
operator|.
name|width
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
name|config
operator|.
name|height
operator|=
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|config
operator|.
name|ntries
operator|=
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|config
operator|.
name|show_image
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
operator|&&
operator|(
operator|(
name|config
operator|.
name|width
operator|<=
literal|0
operator|)
operator|||
operator|(
name|config
operator|.
name|height
operator|<=
literal|0
operator|)
operator|||
name|config
operator|.
name|ntries
operator|<=
literal|0
operator|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_smooth_palette"
argument_list|,
operator|&
name|config
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Deriving Smooth Palette..."
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
operator|+
literal|1
operator|)
operator|/
name|gimp_tile_width
argument_list|()
argument_list|)
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
operator|=
name|doit
argument_list|(
name|drawable
argument_list|,
operator|&
name|values
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_layer
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
name|gimp_set_data
argument_list|(
literal|"plug_in_smooth_palette"
argument_list|,
operator|&
name|config
argument_list|,
sizeof|sizeof
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
operator|.
name|show_image
condition|)
name|gimp_display_new
argument_list|(
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
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
specifier|static
name|long
DECL|function|pix_diff (guchar * pal,guint bpp,gint i,gint j)
name|pix_diff
parameter_list|(
name|guchar
modifier|*
name|pal
parameter_list|,
name|guint
name|bpp
parameter_list|,
name|gint
name|i
parameter_list|,
name|gint
name|j
parameter_list|)
block|{
name|glong
name|r
init|=
literal|0
decl_stmt|;
name|guint
name|k
decl_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|bpp
condition|;
name|k
operator|++
control|)
block|{
name|gint
name|p1
init|=
name|pal
index|[
name|j
operator|*
name|bpp
operator|+
name|k
index|]
decl_stmt|;
name|gint
name|p2
init|=
name|pal
index|[
name|i
operator|*
name|bpp
operator|+
name|k
index|]
decl_stmt|;
name|r
operator|+=
operator|(
name|p1
operator|-
name|p2
operator|)
operator|*
operator|(
name|p1
operator|-
name|p2
operator|)
expr_stmt|;
block|}
return|return
name|r
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pix_swap (guchar * pal,guint bpp,gint i,gint j)
name|pix_swap
parameter_list|(
name|guchar
modifier|*
name|pal
parameter_list|,
name|guint
name|bpp
parameter_list|,
name|gint
name|i
parameter_list|,
name|gint
name|j
parameter_list|)
block|{
name|guint
name|k
decl_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|bpp
condition|;
name|k
operator|++
control|)
block|{
name|guchar
name|t
init|=
name|pal
index|[
name|j
operator|*
name|bpp
operator|+
name|k
index|]
decl_stmt|;
name|pal
index|[
name|j
operator|*
name|bpp
operator|+
name|k
index|]
operator|=
name|pal
index|[
name|i
operator|*
name|bpp
operator|+
name|k
index|]
expr_stmt|;
name|pal
index|[
name|i
operator|*
name|bpp
operator|+
name|k
index|]
operator|=
name|t
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|doit (GimpDrawable * drawable,gint32 * layer_id)
name|doit
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint32
modifier|*
name|layer_id
parameter_list|)
block|{
name|gint32
name|new_image_id
decl_stmt|;
name|GimpDrawable
modifier|*
name|new_layer
decl_stmt|;
name|gint
name|psize
decl_stmt|,
name|i
decl_stmt|,
name|j
decl_stmt|;
name|guchar
modifier|*
name|pal
decl_stmt|;
name|guint
name|bpp
init|=
name|drawable
operator|->
name|bpp
decl_stmt|;
name|gint
name|sel_x1
decl_stmt|,
name|sel_x2
decl_stmt|,
name|sel_y1
decl_stmt|,
name|sel_y2
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|GimpPixelRgn
name|pr
decl_stmt|;
name|GRand
modifier|*
name|gr
decl_stmt|;
name|gr
operator|=
name|g_rand_new
argument_list|()
expr_stmt|;
name|new_image_id
operator|=
name|gimp_image_new
argument_list|(
name|config
operator|.
name|width
argument_list|,
name|config
operator|.
name|height
argument_list|,
name|GIMP_RGB
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|new_image_id
argument_list|)
expr_stmt|;
operator|*
name|layer_id
operator|=
name|gimp_layer_new
argument_list|(
name|new_image_id
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|config
operator|.
name|width
argument_list|,
name|config
operator|.
name|height
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
argument_list|,
literal|100
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|new_image_id
argument_list|,
operator|*
name|layer_id
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|new_layer
operator|=
name|gimp_drawable_get
argument_list|(
operator|*
name|layer_id
argument_list|)
expr_stmt|;
name|psize
operator|=
name|config
operator|.
name|width
expr_stmt|;
name|pal
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|psize
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|sel_x1
argument_list|,
operator|&
name|sel_y1
argument_list|,
operator|&
name|sel_x2
argument_list|,
operator|&
name|sel_y2
argument_list|)
expr_stmt|;
name|width
operator|=
name|sel_x2
operator|-
name|sel_x1
expr_stmt|;
name|height
operator|=
name|sel_y2
operator|-
name|sel_y1
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|pr
argument_list|,
name|drawable
argument_list|,
name|sel_x1
argument_list|,
name|sel_y1
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
comment|/* get initial palette */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|psize
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|x
init|=
name|sel_x1
operator|+
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
literal|0
argument_list|,
name|width
argument_list|)
decl_stmt|;
name|gint
name|y
init|=
name|sel_y1
operator|+
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
literal|0
argument_list|,
name|height
argument_list|)
decl_stmt|;
name|gimp_pixel_rgn_get_pixel
argument_list|(
operator|&
name|pr
argument_list|,
name|pal
operator|+
name|bpp
operator|*
name|i
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
comment|/* reorder */
if|if
condition|(
literal|1
condition|)
block|{
name|guchar
modifier|*
name|pal_best
decl_stmt|;
name|guchar
modifier|*
name|original
decl_stmt|;
name|gdouble
name|len_best
init|=
literal|0
decl_stmt|;
name|gint
name|try
decl_stmt|;
name|pal_best
operator|=
name|g_memdup
argument_list|(
name|pal
argument_list|,
name|bpp
operator|*
name|psize
argument_list|)
expr_stmt|;
name|original
operator|=
name|g_memdup
argument_list|(
name|pal
argument_list|,
name|bpp
operator|*
name|psize
argument_list|)
expr_stmt|;
for|for
control|(
name|try
operator|=
literal|0
init|;
name|try
operator|<
name|config
operator|.
name|ntries
condition|;
name|try
operator|++
control|)
block|{
name|gdouble
name|len
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|try
operator|%
literal|5
operator|)
condition|)
name|gimp_progress_update
argument_list|(
name|try
operator|/
operator|(
name|double
operator|)
name|config
operator|.
name|ntries
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|pal
argument_list|,
name|original
argument_list|,
name|bpp
operator|*
name|psize
argument_list|)
expr_stmt|;
comment|/* scramble */
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|psize
condition|;
name|i
operator|++
control|)
name|pix_swap
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i
argument_list|,
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
literal|0
argument_list|,
name|psize
argument_list|)
argument_list|)
expr_stmt|;
comment|/* measure */
name|len
operator|=
literal|0.0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|psize
condition|;
name|i
operator|++
control|)
name|len
operator|+=
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i
argument_list|,
name|i
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/* improve */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|config
operator|.
name|try_size
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|i0
init|=
literal|1
operator|+
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
literal|0
argument_list|,
name|psize
operator|-
literal|2
argument_list|)
decl_stmt|;
name|gint
name|i1
init|=
literal|1
operator|+
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
literal|0
argument_list|,
name|psize
operator|-
literal|2
argument_list|)
decl_stmt|;
name|glong
name|as_is
decl_stmt|,
name|swapd
decl_stmt|;
if|if
condition|(
literal|1
operator|==
operator|(
name|i0
operator|-
name|i1
operator|)
condition|)
block|{
name|as_is
operator|=
operator|(
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i1
operator|-
literal|1
argument_list|,
name|i1
argument_list|)
operator|+
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i0
argument_list|,
name|i0
operator|+
literal|1
argument_list|)
operator|)
expr_stmt|;
name|swapd
operator|=
operator|(
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i1
operator|-
literal|1
argument_list|,
name|i0
argument_list|)
operator|+
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i1
argument_list|,
name|i0
operator|+
literal|1
argument_list|)
operator|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
literal|1
operator|==
operator|(
name|i1
operator|-
name|i0
operator|)
condition|)
block|{
name|as_is
operator|=
operator|(
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i0
operator|-
literal|1
argument_list|,
name|i0
argument_list|)
operator|+
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i1
argument_list|,
name|i1
operator|+
literal|1
argument_list|)
operator|)
expr_stmt|;
name|swapd
operator|=
operator|(
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i0
operator|-
literal|1
argument_list|,
name|i1
argument_list|)
operator|+
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i0
argument_list|,
name|i1
operator|+
literal|1
argument_list|)
operator|)
expr_stmt|;
block|}
else|else
block|{
name|as_is
operator|=
operator|(
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i0
argument_list|,
name|i0
operator|+
literal|1
argument_list|)
operator|+
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i0
argument_list|,
name|i0
operator|-
literal|1
argument_list|)
operator|+
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i1
argument_list|,
name|i1
operator|+
literal|1
argument_list|)
operator|+
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i1
argument_list|,
name|i1
operator|-
literal|1
argument_list|)
operator|)
expr_stmt|;
name|swapd
operator|=
operator|(
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i1
argument_list|,
name|i0
operator|+
literal|1
argument_list|)
operator|+
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i1
argument_list|,
name|i0
operator|-
literal|1
argument_list|)
operator|+
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i0
argument_list|,
name|i1
operator|+
literal|1
argument_list|)
operator|+
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i0
argument_list|,
name|i1
operator|-
literal|1
argument_list|)
operator|)
expr_stmt|;
block|}
if|if
condition|(
name|swapd
operator|<
name|as_is
condition|)
block|{
name|pix_swap
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i0
argument_list|,
name|i1
argument_list|)
expr_stmt|;
name|len
operator|+=
name|swapd
operator|-
name|as_is
expr_stmt|;
block|}
block|}
comment|/* best? */
if|if
condition|(
literal|0
operator|==
name|try
operator|||
name|len
operator|<
name|len_best
condition|)
block|{
name|memcpy
argument_list|(
name|pal_best
argument_list|,
name|pal
argument_list|,
name|bpp
operator|*
name|psize
argument_list|)
expr_stmt|;
name|len_best
operator|=
name|len
expr_stmt|;
block|}
block|}
name|memcpy
argument_list|(
name|pal
argument_list|,
name|pal_best
argument_list|,
name|bpp
operator|*
name|psize
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pal_best
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|original
argument_list|)
expr_stmt|;
comment|/* clean */
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
literal|4
operator|*
name|psize
condition|;
name|i
operator|++
control|)
block|{
name|glong
name|as_is
decl_stmt|,
name|swapd
decl_stmt|;
name|gint
name|i0
init|=
literal|1
operator|+
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
literal|0
argument_list|,
name|psize
operator|-
literal|2
argument_list|)
decl_stmt|;
name|gint
name|i1
init|=
name|i0
operator|+
literal|1
decl_stmt|;
name|as_is
operator|=
operator|(
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i0
operator|-
literal|1
argument_list|,
name|i0
argument_list|)
operator|+
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i1
argument_list|,
name|i1
operator|+
literal|1
argument_list|)
operator|)
expr_stmt|;
name|swapd
operator|=
operator|(
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i0
operator|-
literal|1
argument_list|,
name|i1
argument_list|)
operator|+
name|pix_diff
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i0
argument_list|,
name|i1
operator|+
literal|1
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|swapd
operator|<
name|as_is
condition|)
block|{
name|pix_swap
argument_list|(
name|pal
argument_list|,
name|bpp
argument_list|,
name|i0
argument_list|,
name|i1
argument_list|)
expr_stmt|;
name|len_best
operator|+=
name|swapd
operator|-
name|as_is
expr_stmt|;
block|}
block|}
block|}
comment|/* store smooth palette */
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|pr
argument_list|,
name|new_layer
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|config
operator|.
name|width
argument_list|,
name|config
operator|.
name|height
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|config
operator|.
name|height
condition|;
name|j
operator|++
control|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|config
operator|.
name|width
condition|;
name|i
operator|++
control|)
name|gimp_pixel_rgn_set_pixel
argument_list|(
operator|&
name|pr
argument_list|,
name|pal
operator|+
name|bpp
operator|*
name|i
argument_list|,
name|i
argument_list|,
name|j
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pal
argument_list|)
expr_stmt|;
name|g_rand_free
argument_list|(
name|gr
argument_list|)
expr_stmt|;
name|gimp_drawable_flush
argument_list|(
name|new_layer
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|new_layer
operator|->
name|drawable_id
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|config
operator|.
name|width
argument_list|,
name|config
operator|.
name|height
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|new_image_id
argument_list|)
expr_stmt|;
return|return
name|new_image_id
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
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
name|spinbutton
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|GtkWidget
modifier|*
name|sizeentry
decl_stmt|;
name|guint32
name|image_id
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"smooth_palette"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Smooth Palette"
argument_list|)
argument_list|,
literal|"smooth_palette"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"plug-in-smooth-palette"
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
name|image_id
operator|=
name|gimp_drawable_get_image
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|unit
operator|=
name|gimp_image_get_unit
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image_id
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|sizeentry
operator|=
name|gimp_coordinates_new
argument_list|(
name|unit
argument_list|,
literal|"%a"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|6
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"_Width:"
argument_list|)
argument_list|,
name|config
operator|.
name|width
argument_list|,
name|xres
argument_list|,
literal|2
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|2
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|_
argument_list|(
literal|"_Height:"
argument_list|)
argument_list|,
name|config
operator|.
name|height
argument_list|,
name|yres
argument_list|,
literal|1
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|1
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|sizeentry
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
name|dlg
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|sizeentry
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
name|sizeentry
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adj
argument_list|,
name|config
operator|.
name|ntries
argument_list|,
literal|1
argument_list|,
literal|1024
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"_Search depth:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|spinbutton
argument_list|,
literal|1
argument_list|,
name|FALSE
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
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|config
operator|.
name|ntries
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dlg
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
if|if
condition|(
name|run
condition|)
block|{
name|config
operator|.
name|width
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|config
operator|.
name|height
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

end_unit

