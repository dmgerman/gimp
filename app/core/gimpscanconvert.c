begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<libart_lgpl/libart.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpscanconvert.h"
end_include

begin_struct
DECL|struct|_GimpScanConvert
struct|struct
name|_GimpScanConvert
block|{
DECL|member|width
name|guint
name|width
decl_stmt|;
DECL|member|height
name|guint
name|height
decl_stmt|;
DECL|member|antialias
name|gboolean
name|antialias
decl_stmt|;
comment|/* do we want antialiasing? */
comment|/* stuff necessary for the _add_polygons API...  :-/  */
DECL|member|got_first
name|gboolean
name|got_first
decl_stmt|;
DECL|member|need_closing
name|gboolean
name|need_closing
decl_stmt|;
DECL|member|first
name|GimpVector2
name|first
decl_stmt|;
DECL|member|prev
name|GimpVector2
name|prev
decl_stmt|;
DECL|member|have_open
name|gboolean
name|have_open
decl_stmt|;
DECL|member|num_nodes
name|guint
name|num_nodes
decl_stmt|;
DECL|member|vpath
name|ArtVpath
modifier|*
name|vpath
decl_stmt|;
DECL|member|svp
name|ArtSVP
modifier|*
name|svp
decl_stmt|;
comment|/* Sorted vector path                                (extension no longer possible)          */
block|}
struct|;
end_struct

begin_comment
comment|/* Private functions */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_scan_convert_finish
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_scan_convert_close_add_points
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpScanConvert
modifier|*
DECL|function|gimp_scan_convert_new (guint width,guint height,gboolean antialias)
name|gimp_scan_convert_new
parameter_list|(
name|guint
name|width
parameter_list|,
name|guint
name|height
parameter_list|,
name|gboolean
name|antialias
parameter_list|)
block|{
name|GimpScanConvert
modifier|*
name|sc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|sc
operator|=
name|g_new0
argument_list|(
name|GimpScanConvert
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|sc
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|sc
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|sc
operator|->
name|antialias
operator|=
name|antialias
expr_stmt|;
return|return
name|sc
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_scan_convert_free (GimpScanConvert * sc)
name|gimp_scan_convert_free
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|sc
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|sc
operator|->
name|vpath
condition|)
name|art_free
argument_list|(
name|sc
operator|->
name|vpath
argument_list|)
expr_stmt|;
if|if
condition|(
name|sc
operator|->
name|svp
condition|)
name|art_svp_free
argument_list|(
name|sc
operator|->
name|svp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|sc
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Add "n_points" from "points" to the polygon currently being  * described by "scan_converter". DEPRECATED.  */
end_comment

begin_function
name|void
DECL|function|gimp_scan_convert_add_points (GimpScanConvert * sc,guint n_points,GimpVector2 * points,gboolean new_polygon)
name|gimp_scan_convert_add_points
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|guint
name|n_points
parameter_list|,
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|gboolean
name|new_polygon
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|sc
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|points
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|n_points
operator|>
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|sc
operator|->
name|svp
operator|==
name|NULL
argument_list|)
expr_stmt|;
comment|/* We need an extra nodes to end the path */
name|sc
operator|->
name|vpath
operator|=
name|art_renew
argument_list|(
name|sc
operator|->
name|vpath
argument_list|,
name|ArtVpath
argument_list|,
name|sc
operator|->
name|num_nodes
operator|+
name|n_points
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|sc
operator|->
name|num_nodes
operator|==
literal|0
operator|||
name|new_polygon
condition|)
block|{
if|if
condition|(
name|sc
operator|->
name|need_closing
condition|)
name|gimp_scan_convert_close_add_points
argument_list|(
name|sc
argument_list|)
expr_stmt|;
name|sc
operator|->
name|got_first
operator|=
name|FALSE
expr_stmt|;
block|}
comment|/* We have to compress multiple identical coordinates */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_points
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|sc
operator|->
name|got_first
operator|==
name|FALSE
operator|||
name|sc
operator|->
name|prev
operator|.
name|x
operator|!=
name|points
index|[
name|i
index|]
operator|.
name|x
operator|||
name|sc
operator|->
name|prev
operator|.
name|y
operator|!=
name|points
index|[
name|i
index|]
operator|.
name|y
condition|)
block|{
name|sc
operator|->
name|vpath
index|[
name|sc
operator|->
name|num_nodes
index|]
operator|.
name|code
operator|=
operator|(
operator|(
operator|!
name|sc
operator|->
name|got_first
operator|)
operator|||
name|new_polygon
operator|)
condition|?
name|ART_MOVETO
else|:
name|ART_LINETO
expr_stmt|;
name|sc
operator|->
name|vpath
index|[
name|sc
operator|->
name|num_nodes
index|]
operator|.
name|x
operator|=
name|points
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|sc
operator|->
name|vpath
index|[
name|sc
operator|->
name|num_nodes
index|]
operator|.
name|y
operator|=
name|points
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
name|sc
operator|->
name|num_nodes
operator|++
expr_stmt|;
name|sc
operator|->
name|prev
operator|=
name|points
index|[
name|i
index|]
expr_stmt|;
if|if
condition|(
operator|!
name|sc
operator|->
name|got_first
condition|)
block|{
name|sc
operator|->
name|got_first
operator|=
name|TRUE
expr_stmt|;
name|sc
operator|->
name|first
operator|=
name|points
index|[
name|i
index|]
expr_stmt|;
block|}
block|}
block|}
name|sc
operator|->
name|need_closing
operator|=
name|TRUE
expr_stmt|;
name|sc
operator|->
name|vpath
index|[
name|sc
operator|->
name|num_nodes
index|]
operator|.
name|code
operator|=
name|ART_END
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scan_convert_close_add_points (GimpScanConvert * sc)
name|gimp_scan_convert_close_add_points
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|)
block|{
if|if
condition|(
name|sc
operator|->
name|need_closing
operator|&&
operator|(
name|sc
operator|->
name|prev
operator|.
name|x
operator|!=
name|sc
operator|->
name|first
operator|.
name|x
operator|||
name|sc
operator|->
name|prev
operator|.
name|y
operator|!=
name|sc
operator|->
name|first
operator|.
name|y
operator|)
condition|)
block|{
name|sc
operator|->
name|vpath
operator|=
name|art_renew
argument_list|(
name|sc
operator|->
name|vpath
argument_list|,
name|ArtVpath
argument_list|,
name|sc
operator|->
name|num_nodes
operator|+
literal|2
argument_list|)
expr_stmt|;
name|sc
operator|->
name|vpath
index|[
name|sc
operator|->
name|num_nodes
index|]
operator|.
name|code
operator|=
name|ART_LINETO
expr_stmt|;
name|sc
operator|->
name|vpath
index|[
name|sc
operator|->
name|num_nodes
index|]
operator|.
name|x
operator|=
name|sc
operator|->
name|first
operator|.
name|x
expr_stmt|;
name|sc
operator|->
name|vpath
index|[
name|sc
operator|->
name|num_nodes
index|]
operator|.
name|y
operator|=
name|sc
operator|->
name|first
operator|.
name|y
expr_stmt|;
name|sc
operator|->
name|num_nodes
operator|++
expr_stmt|;
name|sc
operator|->
name|vpath
index|[
name|sc
operator|->
name|num_nodes
index|]
operator|.
name|code
operator|=
name|ART_END
expr_stmt|;
block|}
name|sc
operator|->
name|need_closing
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Add a polygon with "npoints" "points" that may be open or closed.  * It is not recommended to mix gimp_scan_convert_add_polyline with  * gimp_scan_convert_add_points.  *  * Please note that you should use gimp_scan_convert_stroke() if you  * specify open polygons.  */
end_comment

begin_function
name|void
DECL|function|gimp_scan_convert_add_polyline (GimpScanConvert * sc,guint n_points,GimpVector2 * points,gboolean closed)
name|gimp_scan_convert_add_polyline
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|guint
name|n_points
parameter_list|,
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|gboolean
name|closed
parameter_list|)
block|{
name|GimpVector2
name|prev
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|sc
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|points
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|n_points
operator|>
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|sc
operator|->
name|svp
operator|==
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|sc
operator|->
name|need_closing
condition|)
name|gimp_scan_convert_close_add_points
argument_list|(
name|sc
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|closed
condition|)
name|sc
operator|->
name|have_open
operator|=
name|TRUE
expr_stmt|;
comment|/* We need two extra nodes later to close the path. */
name|sc
operator|->
name|vpath
operator|=
name|art_renew
argument_list|(
name|sc
operator|->
name|vpath
argument_list|,
name|ArtVpath
argument_list|,
name|sc
operator|->
name|num_nodes
operator|+
name|n_points
operator|+
literal|2
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_points
condition|;
name|i
operator|++
control|)
block|{
comment|/* compress multiple identical coordinates */
if|if
condition|(
name|i
operator|==
literal|0
operator|||
name|prev
operator|.
name|x
operator|!=
name|points
index|[
name|i
index|]
operator|.
name|x
operator|||
name|prev
operator|.
name|y
operator|!=
name|points
index|[
name|i
index|]
operator|.
name|y
condition|)
block|{
name|sc
operator|->
name|vpath
index|[
name|sc
operator|->
name|num_nodes
index|]
operator|.
name|code
operator|=
operator|(
name|i
operator|==
literal|0
condition|?
operator|(
name|closed
condition|?
name|ART_MOVETO
else|:
name|ART_MOVETO_OPEN
operator|)
else|:
name|ART_LINETO
operator|)
expr_stmt|;
name|sc
operator|->
name|vpath
index|[
name|sc
operator|->
name|num_nodes
index|]
operator|.
name|x
operator|=
name|points
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|sc
operator|->
name|vpath
index|[
name|sc
operator|->
name|num_nodes
index|]
operator|.
name|y
operator|=
name|points
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
name|sc
operator|->
name|num_nodes
operator|++
expr_stmt|;
name|prev
operator|=
name|points
index|[
name|i
index|]
expr_stmt|;
block|}
block|}
comment|/* for some reason we need to duplicate the last node?? */
name|sc
operator|->
name|vpath
index|[
name|sc
operator|->
name|num_nodes
index|]
operator|=
name|sc
operator|->
name|vpath
index|[
name|sc
operator|->
name|num_nodes
operator|-
literal|1
index|]
expr_stmt|;
name|sc
operator|->
name|num_nodes
operator|++
expr_stmt|;
name|sc
operator|->
name|vpath
index|[
name|sc
operator|->
name|num_nodes
index|]
operator|.
name|code
operator|=
name|ART_END
expr_stmt|;
comment|/* If someone wants to mix this function with _add_points ()    * try to do something reasonable...    */
name|sc
operator|->
name|got_first
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Stroke the content of a GimpScanConvert. The next  * gimp_scan_convert_to_channel will result in the outline of the polygon  * defined with the commands above.  *  * You cannot add additional polygons after this command.  */
end_comment

begin_function
name|void
DECL|function|gimp_scan_convert_stroke (GimpScanConvert * sc,gdouble width,GimpJoinStyle join,GimpCapStyle cap,gdouble miter,gdouble dash_offset,GArray * dash_info)
name|gimp_scan_convert_stroke
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|GimpJoinStyle
name|join
parameter_list|,
name|GimpCapStyle
name|cap
parameter_list|,
name|gdouble
name|miter
parameter_list|,
name|gdouble
name|dash_offset
parameter_list|,
name|GArray
modifier|*
name|dash_info
parameter_list|)
block|{
name|ArtSVP
modifier|*
name|stroke
decl_stmt|;
name|ArtPathStrokeJoinType
name|artjoin
init|=
literal|0
decl_stmt|;
name|ArtPathStrokeCapType
name|artcap
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|sc
operator|->
name|svp
operator|==
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|sc
operator|->
name|need_closing
condition|)
name|gimp_scan_convert_close_add_points
argument_list|(
name|sc
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|join
condition|)
block|{
case|case
name|GIMP_JOIN_MITER
case|:
name|artjoin
operator|=
name|ART_PATH_STROKE_JOIN_MITER
expr_stmt|;
break|break;
case|case
name|GIMP_JOIN_ROUND
case|:
name|artjoin
operator|=
name|ART_PATH_STROKE_JOIN_ROUND
expr_stmt|;
break|break;
case|case
name|GIMP_JOIN_BEVEL
case|:
name|artjoin
operator|=
name|ART_PATH_STROKE_JOIN_BEVEL
expr_stmt|;
break|break;
block|}
switch|switch
condition|(
name|cap
condition|)
block|{
case|case
name|GIMP_CAP_BUTT
case|:
name|artcap
operator|=
name|ART_PATH_STROKE_CAP_BUTT
expr_stmt|;
break|break;
case|case
name|GIMP_CAP_ROUND
case|:
name|artcap
operator|=
name|ART_PATH_STROKE_CAP_ROUND
expr_stmt|;
break|break;
case|case
name|GIMP_CAP_SQUARE
case|:
name|artcap
operator|=
name|ART_PATH_STROKE_CAP_SQUARE
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|dash_info
condition|)
block|{
name|ArtVpath
modifier|*
name|dash_vpath
decl_stmt|;
name|ArtVpathDash
name|dash
decl_stmt|;
name|gdouble
modifier|*
name|dashes
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|width
operator|=
name|MAX
argument_list|(
name|width
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|dash
operator|.
name|offset
operator|=
name|dash_offset
operator|*
name|width
expr_stmt|;
name|dashes
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|dash_info
operator|->
name|len
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|dash_info
operator|->
name|len
condition|;
name|i
operator|++
control|)
name|dashes
index|[
name|i
index|]
operator|=
name|width
operator|*
name|g_array_index
argument_list|(
name|dash_info
argument_list|,
name|gdouble
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|dash
operator|.
name|n_dash
operator|=
name|dash_info
operator|->
name|len
expr_stmt|;
name|dash
operator|.
name|dash
operator|=
name|dashes
expr_stmt|;
name|dash_vpath
operator|=
name|art_vpath_dash
argument_list|(
name|sc
operator|->
name|vpath
argument_list|,
operator|&
name|dash
argument_list|)
expr_stmt|;
name|art_free
argument_list|(
name|sc
operator|->
name|vpath
argument_list|)
expr_stmt|;
name|sc
operator|->
name|vpath
operator|=
name|dash_vpath
expr_stmt|;
name|g_free
argument_list|(
name|dashes
argument_list|)
expr_stmt|;
block|}
name|stroke
operator|=
name|art_svp_vpath_stroke
argument_list|(
name|sc
operator|->
name|vpath
argument_list|,
name|artjoin
argument_list|,
name|artcap
argument_list|,
name|width
argument_list|,
name|miter
argument_list|,
literal|0.2
argument_list|)
expr_stmt|;
name|sc
operator|->
name|svp
operator|=
name|stroke
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Return a new Channel according to the polygonal shapes defined with  * the commands above.  *  * You cannot add additional polygons after this command.  */
end_comment

begin_function
name|GimpChannel
modifier|*
DECL|function|gimp_scan_convert_to_channel (GimpScanConvert * sc,GimpImage * gimage)
name|gimp_scan_convert_to_channel
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
name|mask
operator|=
name|gimp_channel_new_mask
argument_list|(
name|gimage
argument_list|,
name|sc
operator|->
name|width
argument_list|,
name|sc
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_scan_convert_render
argument_list|(
name|sc
argument_list|,
name|gimp_drawable_data
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|mask
operator|->
name|bounds_known
operator|=
name|FALSE
expr_stmt|;
return|return
name|mask
return|;
block|}
end_function

begin_comment
comment|/* This is a more low level version. Expects a tile manager of depth 1.  *  * You cannot add additional polygons after this command.  */
end_comment

begin_function
name|void
DECL|function|gimp_scan_convert_render (GimpScanConvert * sc,TileManager * tile_manager)
name|gimp_scan_convert_render
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|TileManager
modifier|*
name|tile_manager
parameter_list|)
block|{
name|PixelRegion
name|maskPR
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|x0
decl_stmt|,
name|y0
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|sc
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|tile_manager
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_scan_convert_finish
argument_list|(
name|sc
argument_list|)
expr_stmt|;
name|tile_manager_get_offsets
argument_list|(
name|tile_manager
argument_list|,
operator|&
name|x0
argument_list|,
operator|&
name|y0
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|tile_manager
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|tile_manager_width
argument_list|(
name|tile_manager
argument_list|)
argument_list|,
name|tile_manager_height
argument_list|(
name|tile_manager
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|maskPR
operator|.
name|bytes
operator|==
literal|1
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|1
argument_list|,
operator|&
name|maskPR
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|pixel_regions_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|art_gray_svp_aa
argument_list|(
name|sc
operator|->
name|svp
argument_list|,
name|x0
operator|+
name|maskPR
operator|.
name|x
argument_list|,
name|y0
operator|+
name|maskPR
operator|.
name|y
argument_list|,
name|x0
operator|+
name|maskPR
operator|.
name|x
operator|+
name|maskPR
operator|.
name|w
argument_list|,
name|y0
operator|+
name|maskPR
operator|.
name|y
operator|+
name|maskPR
operator|.
name|h
argument_list|,
name|maskPR
operator|.
name|data
argument_list|,
name|maskPR
operator|.
name|rowstride
argument_list|)
expr_stmt|;
if|if
condition|(
name|sc
operator|->
name|antialias
operator|==
name|FALSE
condition|)
block|{
comment|/*            * Ok, the user didn't want to have antialiasing, so just            * remove the results from lots of CPU-Power...            */
name|dest
operator|=
name|maskPR
operator|.
name|data
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|maskPR
operator|.
name|h
condition|;
name|j
operator|++
control|)
block|{
name|d
operator|=
name|dest
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|maskPR
operator|.
name|w
condition|;
name|i
operator|++
control|)
block|{
name|d
index|[
literal|0
index|]
operator|=
operator|(
name|d
index|[
literal|0
index|]
operator|>=
literal|127
operator|)
condition|?
literal|255
else|:
literal|0
expr_stmt|;
name|d
operator|+=
name|maskPR
operator|.
name|bytes
expr_stmt|;
block|}
name|dest
operator|+=
name|maskPR
operator|.
name|rowstride
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_comment
comment|/* private function to convert the vpath to a svp when not using  * gimp_scan_convert_stroke  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_scan_convert_finish (GimpScanConvert * sc)
name|gimp_scan_convert_finish
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|)
block|{
name|ArtVpath
modifier|*
name|pert_vpath
decl_stmt|;
name|ArtSVP
modifier|*
name|svp
decl_stmt|,
modifier|*
name|svp2
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|sc
operator|->
name|vpath
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|sc
operator|->
name|need_closing
condition|)
name|gimp_scan_convert_close_add_points
argument_list|(
name|sc
argument_list|)
expr_stmt|;
if|if
condition|(
name|sc
operator|->
name|svp
condition|)
return|return;
comment|/* We already have a valid SVP */
comment|/* Debug output of libart path */
comment|/* {    *   gint i;    *   for (i=0; i< sc->num_nodes + 1; i++)    *     {    *       g_printerr ("X: %f, Y: %f, Type: %d\n", sc->vpath[i].x,    *                                               sc->vpath[i].y,    *                                               sc->vpath[i].code );    *     }    * }    */
if|if
condition|(
name|sc
operator|->
name|have_open
condition|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|sc
operator|->
name|num_nodes
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|sc
operator|->
name|vpath
index|[
name|i
index|]
operator|.
name|code
operator|==
name|ART_MOVETO_OPEN
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Fixing ART_MOVETO_OPEN - result might be incorrect\n"
argument_list|)
expr_stmt|;
name|sc
operator|->
name|vpath
index|[
name|i
index|]
operator|.
name|code
operator|=
name|ART_MOVETO
expr_stmt|;
block|}
block|}
comment|/*    * Current Libart (2.3.8) recommends a slight random distorsion    * of the path, because art_svp_uncross and art_svp_rewind_uncrossed    * are not yet numerically stable. It is actually possible to construct    * worst case scenarios. The slight perturbation should not have any    * visible effect.    */
name|pert_vpath
operator|=
name|art_vpath_perturb
argument_list|(
name|sc
operator|->
name|vpath
argument_list|)
expr_stmt|;
name|svp
operator|=
name|art_svp_from_vpath
argument_list|(
name|pert_vpath
argument_list|)
expr_stmt|;
name|art_free
argument_list|(
name|pert_vpath
argument_list|)
expr_stmt|;
name|svp2
operator|=
name|art_svp_uncross
argument_list|(
name|svp
argument_list|)
expr_stmt|;
name|art_svp_free
argument_list|(
name|svp
argument_list|)
expr_stmt|;
name|svp
operator|=
name|art_svp_rewind_uncrossed
argument_list|(
name|svp2
argument_list|,
name|ART_WIND_RULE_ODDEVEN
argument_list|)
expr_stmt|;
name|art_svp_free
argument_list|(
name|svp2
argument_list|)
expr_stmt|;
name|sc
operator|->
name|svp
operator|=
name|svp
expr_stmt|;
block|}
end_function

end_unit

