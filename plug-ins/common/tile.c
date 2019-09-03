begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<string.h>
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
value|"plug-in-tile"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"tile"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-tile"
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c8850e50108
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
name|tile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
modifier|*
name|new_image
parameter_list|,
name|GimpLayer
modifier|*
modifier|*
name|new_layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tile_gegl
parameter_list|(
name|GeglBuffer
modifier|*
name|src
parameter_list|,
name|gint
name|src_width
parameter_list|,
name|gint
name|src_height
parameter_list|,
name|GeglBuffer
modifier|*
name|dst
parameter_list|,
name|gint
name|dst_width
parameter_list|,
name|gint
name|dst_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|tile_dialog
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
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
specifier|const
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
literal|"The run mode { RUN-INTERACTIVE (0), RUN-NONINTERACTIVE (1) }"
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
literal|"new-width"
block|,
literal|"New (tiled) image width"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"new-height"
block|,
literal|"New (tiled) image height"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"new-image"
block|,
literal|"Create a new image?"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"new-image"
block|,
literal|"Output image (-1 if new-image == FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_LAYER
block|,
literal|"new-layer"
block|,
literal|"Output layer (-1 if new-image == FALSE)"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Create an array of copies of the image"
argument_list|)
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
literal|"_Tile..."
argument_list|)
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
argument_list|,
name|GIMP_PDB_PROC_TYPE_PLUGIN
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
name|PLUG_IN_PROC
argument_list|,
literal|"<Image>/Filters/Map"
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
name|gegl_init
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
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
name|PLUG_IN_PROC
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
name|gimp_image_get_by_id
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
argument_list|)
argument_list|,
name|gimp_drawable_get_by_id
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
literal|1
operator|||
name|tvals
operator|.
name|new_height
operator|<
literal|1
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
name|PLUG_IN_PROC
argument_list|,
operator|&
name|tvals
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
name|GimpLayer
modifier|*
name|new_layer
decl_stmt|;
name|GimpImage
modifier|*
name|new_image
decl_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Tiling"
argument_list|)
argument_list|)
expr_stmt|;
name|tile
argument_list|(
name|gimp_image_get_by_id
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
argument_list|)
argument_list|,
name|gimp_drawable_get_by_id
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
argument_list|,
operator|&
name|new_image
argument_list|,
operator|&
name|new_layer
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
name|gimp_image_get_id
argument_list|(
name|new_image
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
name|gimp_item_get_id
argument_list|(
name|GIMP_ITEM
argument_list|(
name|new_layer
argument_list|)
argument_list|)
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
name|PLUG_IN_PROC
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
name|new_image
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
name|gegl_exit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile_gegl (GeglBuffer * src,gint src_width,gint src_height,GeglBuffer * dst,gint dst_width,gint dst_height)
name|tile_gegl
parameter_list|(
name|GeglBuffer
modifier|*
name|src
parameter_list|,
name|gint
name|src_width
parameter_list|,
name|gint
name|src_height
parameter_list|,
name|GeglBuffer
modifier|*
name|dst
parameter_list|,
name|gint
name|dst_width
parameter_list|,
name|gint
name|dst_height
parameter_list|)
block|{
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|GeglNode
modifier|*
name|buffer_src_node
decl_stmt|;
name|GeglNode
modifier|*
name|tile_node
decl_stmt|;
name|GeglNode
modifier|*
name|crop_src_node
decl_stmt|;
name|GeglNode
modifier|*
name|crop_dst_node
decl_stmt|;
name|GeglNode
modifier|*
name|buffer_dst_node
decl_stmt|;
name|GeglProcessor
modifier|*
name|processor
decl_stmt|;
name|gdouble
name|progress
decl_stmt|;
name|node
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|buffer_src_node
operator|=
name|gegl_node_new_child
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-source"
argument_list|,
literal|"buffer"
argument_list|,
name|src
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|crop_src_node
operator|=
name|gegl_node_new_child
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:crop"
argument_list|,
literal|"width"
argument_list|,
operator|(
name|gdouble
operator|)
name|src_width
argument_list|,
literal|"height"
argument_list|,
operator|(
name|gdouble
operator|)
name|src_height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tile_node
operator|=
name|gegl_node_new_child
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:tile"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|crop_dst_node
operator|=
name|gegl_node_new_child
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:crop"
argument_list|,
literal|"width"
argument_list|,
operator|(
name|gdouble
operator|)
name|dst_width
argument_list|,
literal|"height"
argument_list|,
operator|(
name|gdouble
operator|)
name|dst_height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|buffer_dst_node
operator|=
name|gegl_node_new_child
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:write-buffer"
argument_list|,
literal|"buffer"
argument_list|,
name|dst
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_link_many
argument_list|(
name|buffer_src_node
argument_list|,
name|crop_src_node
argument_list|,
name|tile_node
argument_list|,
name|crop_dst_node
argument_list|,
name|buffer_dst_node
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|processor
operator|=
name|gegl_node_new_processor
argument_list|(
name|buffer_dst_node
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_processor_work
argument_list|(
name|processor
argument_list|,
operator|&
name|progress
argument_list|)
condition|)
if|if
condition|(
operator|!
operator|(
call|(
name|gint
call|)
argument_list|(
name|progress
operator|*
literal|100.0
argument_list|)
operator|%
literal|10
operator|)
condition|)
name|gimp_progress_update
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|processor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|node
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile (GimpImage * image,GimpDrawable * drawable,GimpImage ** new_image,GimpLayer ** new_layer)
name|tile
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
modifier|*
name|new_image
parameter_list|,
name|GimpLayer
modifier|*
modifier|*
name|new_layer
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|dst_drawable
decl_stmt|;
name|GeglBuffer
modifier|*
name|dst_buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|src_buffer
decl_stmt|;
name|gint
name|dst_width
init|=
name|tvals
operator|.
name|new_width
decl_stmt|;
name|gint
name|dst_height
init|=
name|tvals
operator|.
name|new_height
decl_stmt|;
name|gint
name|src_width
init|=
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|gint
name|src_height
init|=
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|GimpImageBaseType
name|image_type
init|=
name|GIMP_RGB
decl_stmt|;
comment|/* sanity check parameters */
if|if
condition|(
name|dst_width
operator|<
literal|1
operator|||
name|dst_height
operator|<
literal|1
condition|)
block|{
operator|*
name|new_image
operator|=
name|NULL
expr_stmt|;
operator|*
name|new_layer
operator|=
name|NULL
expr_stmt|;
empty_stmt|;
return|return;
block|}
if|if
condition|(
name|tvals
operator|.
name|new_image
condition|)
block|{
comment|/*  create  a new image  */
name|gint32
name|precision
init|=
name|gimp_image_get_precision
argument_list|(
name|image
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable
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
operator|*
name|new_image
operator|=
name|gimp_image_new_with_precision
argument_list|(
name|dst_width
argument_list|,
name|dst_height
argument_list|,
name|image_type
argument_list|,
name|precision
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
operator|*
name|new_image
argument_list|)
expr_stmt|;
comment|/*  copy the colormap, if necessary  */
if|if
condition|(
name|image_type
operator|==
name|GIMP_INDEXED
condition|)
block|{
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|gint
name|ncols
decl_stmt|;
name|cmap
operator|=
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|,
operator|&
name|ncols
argument_list|)
expr_stmt|;
name|gimp_image_set_colormap
argument_list|(
operator|*
name|new_image
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
operator|*
name|new_layer
operator|=
name|gimp_layer_new
argument_list|(
operator|*
name|new_image
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|dst_width
argument_list|,
name|dst_height
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
argument_list|,
literal|100
argument_list|,
name|gimp_image_get_default_new_layer_mode
argument_list|(
operator|*
name|new_image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|new_layer
operator|==
name|NULL
condition|)
return|return;
name|gimp_image_insert_layer
argument_list|(
operator|*
name|new_image
argument_list|,
operator|*
name|new_layer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|dst_drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
operator|*
name|new_layer
argument_list|)
expr_stmt|;
block|}
else|else
block|{
operator|*
name|new_image
operator|=
name|NULL
expr_stmt|;
operator|*
name|new_layer
operator|=
name|NULL
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_resize
argument_list|(
name|image
argument_list|,
name|dst_width
argument_list|,
name|dst_height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_item_is_layer
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_layer_resize
argument_list|(
name|GIMP_LAYER
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|dst_width
argument_list|,
name|dst_height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimp_item_is_layer_mask
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
name|GimpLayer
modifier|*
name|layer
init|=
name|gimp_layer_from_mask
argument_list|(
name|GIMP_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_layer_resize
argument_list|(
name|layer
argument_list|,
name|dst_width
argument_list|,
name|dst_height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|dst_drawable
operator|=
name|drawable
expr_stmt|;
block|}
name|src_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|dst_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|dst_drawable
argument_list|)
expr_stmt|;
name|tile_gegl
argument_list|(
name|src_buffer
argument_list|,
name|src_width
argument_list|,
name|src_height
argument_list|,
name|dst_buffer
argument_list|,
name|dst_width
argument_list|,
name|dst_height
argument_list|)
expr_stmt|;
name|gegl_buffer_flush
argument_list|(
name|dst_buffer
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|dst_drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|dst_width
argument_list|,
name|dst_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|tvals
operator|.
name|new_image
condition|)
block|{
name|gimp_image_undo_enable
argument_list|(
operator|*
name|new_image
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|src_buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dst_buffer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|tile_dialog (GimpImage * image,GimpDrawable * drawable)
name|tile_dialog
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
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
name|vbox
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
name|chainbutton
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
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|unit
operator|=
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
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
name|PLUG_IN_ROLE
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|PLUG_IN_PROC
argument_list|,
name|_
argument_list|(
literal|"_Cancel"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|_
argument_list|(
literal|"_OK"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
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
name|dlg
argument_list|)
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Tile to New Size"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|gtk_widget_show
argument_list|(
name|sizeentry
argument_list|)
expr_stmt|;
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
literal|"C_reate new image"
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
name|tvals
operator|.
name|new_image
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
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
name|chainbutton
argument_list|)
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

