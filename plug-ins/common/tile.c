begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * This filter tiles an image to arbitrary width and height  */
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27854bd70108
block|{
DECL|member|new_width
name|gint
name|new_width
decl_stmt|;
DECL|member|new_height
name|gint
name|new_height
decl_stmt|;
DECL|member|constrain
name|gint
name|constrain
decl_stmt|;
DECL|member|new_image
name|gint
name|new_image
decl_stmt|;
DECL|typedef|TileVals
block|}
name|TileVals
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27854bd70208
block|{
DECL|member|sizeentry
name|GtkWidget
modifier|*
name|sizeentry
decl_stmt|;
DECL|member|chainbutton
name|GtkWidget
modifier|*
name|chainbutton
decl_stmt|;
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|TileInterface
block|}
name|TileInterface
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
name|gint32
name|tile
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint32
name|drawable_id
parameter_list|,
name|gint32
modifier|*
name|layer_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|tile_dialog
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tile_ok_callback
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

begin_decl_stmt
DECL|variable|tvals
specifier|static
name|TileVals
name|tvals
init|=
block|{
literal|1
block|,
comment|/* new_width  */
literal|1
block|,
comment|/* new_height */
name|TRUE
block|,
comment|/* constrain  */
name|TRUE
comment|/* new_image  */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tint
specifier|static
name|TileInterface
name|tint
init|=
block|{
name|NULL
block|,
comment|/* sizeentry */
name|FALSE
comment|/* run       */
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
literal|"new_width"
block|,
literal|"New (tiled) image width"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"new_height"
block|,
literal|"New (tiled) image height"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"new_image"
block|,
literal|"Create a new image?"
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
literal|"Output image (N/A if new_image == FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_LAYER
block|,
literal|"new_layer"
block|,
literal|"Output layer (N/A if new_image == FALSE)"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_tile"
argument_list|,
literal|"Create a new image which is a tiled version of the "
literal|"input drawable"
argument_list|,
literal|"This function creates a new image with a single "
literal|"layer sized to the specified 'new_width' and "
literal|"'new_height' parameters.  The specified drawable "
literal|"is tiled into this layer.  The new layer will have "
literal|"the same type as the specified drawable and the "
literal|"new image will have a corresponding base type."
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1996-1997"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Map/Tile..."
argument_list|)
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
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
name|gint32
name|new_layer
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
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
name|width
operator|=
name|gimp_drawable_width
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
name|height
operator|=
name|gimp_drawable_height
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
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_tile"
argument_list|,
operator|&
name|tvals
argument_list|)
expr_stmt|;
comment|/*  First acquire information with a dialog  */
if|if
condition|(
operator|!
name|tile_dialog
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
argument_list|,
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_drawable
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
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|!=
literal|6
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|tvals
operator|.
name|new_width
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
name|tvals
operator|.
name|new_height
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
name|tvals
operator|.
name|new_image
operator|=
name|param
index|[
literal|5
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
if|if
condition|(
name|tvals
operator|.
name|new_width
operator|<
literal|0
operator|||
name|tvals
operator|.
name|new_height
operator|<
literal|0
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
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_tile"
argument_list|,
operator|&
name|tvals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
comment|/*  Make sure that the drawable is gray or RGB color  */
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Tiling..."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
literal|2
operator|*
operator|(
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
name|tile
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
argument_list|,
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_drawable
argument_list|,
operator|&
name|new_layer
argument_list|)
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_layer
operator|=
name|new_layer
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
literal|"plug_in_tile"
argument_list|,
operator|&
name|tvals
argument_list|,
sizeof|sizeof
argument_list|(
name|TileVals
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
block|{
if|if
condition|(
name|tvals
operator|.
name|new_image
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
else|else
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
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
name|gint32
DECL|function|tile (gint32 image_id,gint32 drawable_id,gint32 * layer_id)
name|tile
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint32
name|drawable_id
parameter_list|,
name|gint32
modifier|*
name|layer_id
parameter_list|)
block|{
name|GimpPixelRgn
name|src_rgn
decl_stmt|;
name|GimpPixelRgn
name|dest_rgn
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpDrawable
modifier|*
name|new_layer
decl_stmt|;
name|GimpImageBaseType
name|image_type
decl_stmt|;
name|gint32
name|new_image_id
decl_stmt|;
name|gint
name|old_width
decl_stmt|,
name|old_height
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|gint
name|progress
decl_stmt|,
name|max_progress
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
comment|/* sanity check parameters */
if|if
condition|(
name|tvals
operator|.
name|new_width
operator|<
literal|1
operator|||
name|tvals
operator|.
name|new_height
operator|<
literal|1
condition|)
block|{
operator|*
name|layer_id
operator|=
operator|-
literal|1
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/* initialize */
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|new_image_id
operator|=
literal|0
expr_stmt|;
name|old_width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
name|old_height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|tvals
operator|.
name|new_image
condition|)
block|{
comment|/*  create  a new image  */
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable_id
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB_IMAGE
case|:
case|case
name|GIMP_RGBA_IMAGE
case|:
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY_IMAGE
case|:
case|case
name|GIMP_GRAYA_IMAGE
case|:
name|image_type
operator|=
name|GIMP_GRAY
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED_IMAGE
case|:
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
name|image_type
operator|=
name|GIMP_INDEXED
expr_stmt|;
break|break;
block|}
name|new_image_id
operator|=
name|gimp_image_new
argument_list|(
name|tvals
operator|.
name|new_width
argument_list|,
name|tvals
operator|.
name|new_height
argument_list|,
name|image_type
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
name|tvals
operator|.
name|new_width
argument_list|,
name|tvals
operator|.
name|new_height
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable_id
argument_list|)
argument_list|,
literal|100
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|layer_id
operator|==
operator|-
literal|1
condition|)
return|return
operator|-
literal|1
return|;
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
comment|/*  Get the specified drawable  */
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_undo_push_group_start
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
name|gimp_image_resize
argument_list|(
name|image_id
argument_list|,
name|tvals
operator|.
name|new_width
argument_list|,
name|tvals
operator|.
name|new_height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_layer
argument_list|(
name|drawable_id
argument_list|)
condition|)
name|gimp_layer_resize
argument_list|(
name|drawable_id
argument_list|,
name|tvals
operator|.
name|new_width
argument_list|,
name|tvals
operator|.
name|new_height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  Get the specified drawable  */
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
name|new_layer
operator|=
name|drawable
expr_stmt|;
block|}
comment|/*  progress  */
name|progress
operator|=
literal|0
expr_stmt|;
name|max_progress
operator|=
name|tvals
operator|.
name|new_width
operator|*
name|tvals
operator|.
name|new_height
expr_stmt|;
comment|/*  tile...  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|tvals
operator|.
name|new_height
condition|;
name|i
operator|+=
name|old_height
control|)
block|{
name|height
operator|=
name|old_height
expr_stmt|;
if|if
condition|(
name|height
operator|+
name|i
operator|>
name|tvals
operator|.
name|new_height
condition|)
name|height
operator|=
name|tvals
operator|.
name|new_height
operator|-
name|i
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|tvals
operator|.
name|new_width
condition|;
name|j
operator|+=
name|old_width
control|)
block|{
name|width
operator|=
name|old_width
expr_stmt|;
if|if
condition|(
name|width
operator|+
name|j
operator|>
name|tvals
operator|.
name|new_width
condition|)
name|width
operator|=
name|tvals
operator|.
name|new_width
operator|-
name|j
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
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
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|new_layer
argument_list|,
name|j
argument_list|,
name|i
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
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
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|src_rgn
operator|.
name|h
condition|;
name|k
operator|++
control|)
name|memcpy
argument_list|(
name|dest_rgn
operator|.
name|data
operator|+
name|k
operator|*
name|dest_rgn
operator|.
name|rowstride
argument_list|,
name|src_rgn
operator|.
name|data
operator|+
name|k
operator|*
name|src_rgn
operator|.
name|rowstride
argument_list|,
name|src_rgn
operator|.
name|w
operator|*
name|src_rgn
operator|.
name|bpp
argument_list|)
expr_stmt|;
name|progress
operator|+=
name|src_rgn
operator|.
name|w
operator|*
name|src_rgn
operator|.
name|h
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|progress
operator|/
operator|(
name|gdouble
operator|)
name|max_progress
argument_list|)
expr_stmt|;
block|}
block|}
block|}
comment|/*  copy the colormap, if necessary  */
if|if
condition|(
name|image_type
operator|==
name|GIMP_INDEXED
operator|&&
name|tvals
operator|.
name|new_image
condition|)
block|{
name|gint
name|ncols
decl_stmt|;
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|cmap
operator|=
name|gimp_image_get_cmap
argument_list|(
name|image_id
argument_list|,
operator|&
name|ncols
argument_list|)
expr_stmt|;
name|gimp_image_set_cmap
argument_list|(
name|new_image_id
argument_list|,
name|cmap
argument_list|,
name|ncols
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|cmap
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|tvals
operator|.
name|new_image
condition|)
block|{
name|gimp_drawable_flush
argument_list|(
name|new_layer
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|new_layer
argument_list|)
expr_stmt|;
block|}
else|else
name|gimp_undo_push_group_end
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return
name|new_image_id
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|tile_dialog (gint32 image_ID,gint32 drawable_ID)
name|tile_dialog
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|sizeentry
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"tile"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|unit
operator|=
name|gimp_image_get_unit
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image_ID
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|tvals
operator|.
name|new_width
operator|=
name|width
expr_stmt|;
name|tvals
operator|.
name|new_height
operator|=
name|height
expr_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Tile"
argument_list|)
argument_list|,
literal|"tile"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/tile.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
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
name|GTK_STOCK_OK
argument_list|,
name|tile_ok_callback
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
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dlg
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_main_quit
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  parameter settings  */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Tile to New Size"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_ETCHED_IN
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
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
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
name|TRUE
argument_list|,
literal|8
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|,
name|tvals
operator|.
name|constrain
argument_list|,
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"_Width:"
argument_list|)
argument_list|,
name|width
argument_list|,
name|xres
argument_list|,
literal|1
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|_
argument_list|(
literal|"_Height:"
argument_list|)
argument_list|,
name|height
argument_list|,
name|yres
argument_list|,
literal|1
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|sizeentry
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
name|sizeentry
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|sizeentry
argument_list|)
expr_stmt|;
name|tint
operator|.
name|sizeentry
operator|=
name|sizeentry
expr_stmt|;
name|tint
operator|.
name|chainbutton
operator|=
name|GTK_WIDGET
argument_list|(
name|GIMP_COORDINATES_CHAINBUTTON
argument_list|(
name|sizeentry
argument_list|)
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"C_reate New Image"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|toggle
argument_list|,
literal|0
argument_list|,
literal|4
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_FILL
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
name|tvals
operator|.
name|new_image
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
name|tvals
operator|.
name|new_image
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
name|tint
operator|.
name|run
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_ok_callback (GtkWidget * widget,gpointer data)
name|tile_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|tvals
operator|.
name|new_width
operator|=
name|RINT
argument_list|(
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|tint
operator|.
name|sizeentry
argument_list|)
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|tvals
operator|.
name|new_height
operator|=
name|RINT
argument_list|(
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|tint
operator|.
name|sizeentry
argument_list|)
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|tvals
operator|.
name|constrain
operator|=
name|gimp_chain_button_get_active
argument_list|(
name|GIMP_CHAIN_BUTTON
argument_list|(
name|tint
operator|.
name|chainbutton
argument_list|)
argument_list|)
expr_stmt|;
name|tint
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

end_unit

