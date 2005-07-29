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
file|<libart_lgpl/art_svp_intersect.h>
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
file|"gimpscanconvert.h"
end_include

begin_struct
DECL|struct|_GimpScanConvert
struct|struct
name|_GimpScanConvert
block|{
DECL|member|ratio_xy
name|gdouble
name|ratio_xy
decl_stmt|;
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
comment|/* stuff necessary for the rendering callback */
DECL|member|buf
name|guchar
modifier|*
name|buf
decl_stmt|;
DECL|member|rowstride
name|gint
name|rowstride
decl_stmt|;
DECL|member|x0
DECL|member|x1
name|gint
name|x0
decl_stmt|,
name|x1
decl_stmt|;
DECL|member|antialias
name|gboolean
name|antialias
decl_stmt|;
DECL|member|value
name|gboolean
name|value
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* private functions */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_scan_convert_render_internal
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|TileManager
modifier|*
name|tile_manager
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|guchar
name|value
parameter_list|)
function_decl|;
end_function_decl

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

begin_function_decl
specifier|static
name|void
name|gimp_scan_convert_render_callback
parameter_list|(
name|gpointer
name|user_data
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|start_value
parameter_list|,
name|ArtSVPRenderAAStep
modifier|*
name|steps
parameter_list|,
name|gint
name|n_steps
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpScanConvert
modifier|*
DECL|function|gimp_scan_convert_new (void)
name|gimp_scan_convert_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpScanConvert
modifier|*
name|sc
decl_stmt|;
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
name|ratio_xy
operator|=
literal|1.0
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
comment|/* set the Pixel-Ratio (width / height) for the pixels.  */
end_comment

begin_function
name|void
DECL|function|gimp_scan_convert_set_pixel_ratio (GimpScanConvert * sc,gdouble ratio_xy)
name|gimp_scan_convert_set_pixel_ratio
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|gdouble
name|ratio_xy
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|sc
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/* we only need the relative resolution */
name|sc
operator|->
name|ratio_xy
operator|=
name|ratio_xy
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
literal|0.0
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
literal|0.0
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
literal|0.0
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
literal|0.0
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
init|=
block|{
literal|0.0
block|,
literal|0.0
block|, }
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
comment|/* make sure that we have enough space for the nodes */
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
comment|/* close the polyline when needed */
if|if
condition|(
name|closed
operator|&&
operator|(
name|prev
operator|.
name|x
operator|!=
name|points
index|[
literal|0
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
literal|0
index|]
operator|.
name|y
operator|)
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
name|x
operator|=
name|points
index|[
literal|0
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
literal|0
index|]
operator|.
name|y
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
name|num_nodes
operator|++
expr_stmt|;
block|}
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
literal|0.0
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
literal|0.0
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
comment|/* Stroke the content of a GimpScanConvert. The next  * gimp_scan_convert_render() will result in the outline of the polygon  * defined with the commands above.  *  * You cannot add additional polygons after this command.  */
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
name|sc
operator|->
name|ratio_xy
operator|!=
literal|1.0
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
name|sc
operator|->
name|vpath
index|[
name|i
index|]
operator|.
name|x
operator|*=
name|sc
operator|->
name|ratio_xy
expr_stmt|;
block|}
if|if
condition|(
name|dash_info
operator|&&
name|dash_info
operator|->
name|len
operator|>=
literal|2
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
name|dash
operator|.
name|offset
operator|=
name|dash_offset
operator|*
name|MAX
argument_list|(
name|width
argument_list|,
literal|1.0
argument_list|)
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
name|MAX
argument_list|(
name|width
argument_list|,
literal|1.0
argument_list|)
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
comment|/* correct 0.0 in the first element (starts with a gap) */
if|if
condition|(
name|dash
operator|.
name|dash
index|[
literal|0
index|]
operator|==
literal|0.0
condition|)
block|{
name|gdouble
name|first
decl_stmt|;
name|first
operator|=
name|dash
operator|.
name|dash
index|[
literal|1
index|]
expr_stmt|;
comment|/* shift the pattern to really starts with a dash and            * use the offset to skip into it.            */
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
operator|-
literal|2
condition|;
name|i
operator|++
control|)
block|{
name|dash
operator|.
name|dash
index|[
name|i
index|]
operator|=
name|dash
operator|.
name|dash
index|[
name|i
operator|+
literal|2
index|]
expr_stmt|;
name|dash
operator|.
name|offset
operator|+=
name|dash
operator|.
name|dash
index|[
name|i
index|]
expr_stmt|;
block|}
if|if
condition|(
name|dash_info
operator|->
name|len
operator|%
literal|2
operator|==
literal|1
condition|)
block|{
name|dash
operator|.
name|dash
index|[
name|dash_info
operator|->
name|len
operator|-
literal|2
index|]
operator|=
name|first
expr_stmt|;
name|dash
operator|.
name|n_dash
operator|--
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|dash_info
operator|->
name|len
operator|<
literal|3
condition|)
block|{
comment|/* empty stroke */
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
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|dash
operator|.
name|dash
index|[
name|dash_info
operator|->
name|len
operator|-
literal|3
index|]
operator|+=
name|first
expr_stmt|;
name|dash
operator|.
name|n_dash
operator|-=
literal|2
expr_stmt|;
block|}
block|}
block|}
comment|/* correct odd number of dash specifiers */
if|if
condition|(
name|dash
operator|.
name|n_dash
operator|%
literal|2
operator|==
literal|1
condition|)
block|{
name|gdouble
name|last
decl_stmt|;
name|last
operator|=
name|dash
operator|.
name|dash
index|[
name|dash
operator|.
name|n_dash
operator|-
literal|1
index|]
expr_stmt|;
name|dash
operator|.
name|dash
index|[
literal|0
index|]
operator|+=
name|last
expr_stmt|;
name|dash
operator|.
name|offset
operator|+=
name|last
expr_stmt|;
name|dash
operator|.
name|n_dash
operator|--
expr_stmt|;
block|}
if|if
condition|(
name|sc
operator|->
name|vpath
condition|)
block|{
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
block|}
name|g_free
argument_list|(
name|dashes
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|sc
operator|->
name|vpath
condition|)
block|{
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
if|if
condition|(
name|sc
operator|->
name|ratio_xy
operator|!=
literal|1.0
condition|)
block|{
name|ArtSVPSeg
modifier|*
name|segment
decl_stmt|;
name|ArtPoint
modifier|*
name|point
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|stroke
operator|->
name|n_segs
condition|;
name|i
operator|++
control|)
block|{
name|segment
operator|=
name|stroke
operator|->
name|segs
operator|+
name|i
expr_stmt|;
name|segment
operator|->
name|bbox
operator|.
name|x0
operator|/=
name|sc
operator|->
name|ratio_xy
expr_stmt|;
name|segment
operator|->
name|bbox
operator|.
name|x1
operator|/=
name|sc
operator|->
name|ratio_xy
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|segment
operator|->
name|n_points
condition|;
name|j
operator|++
control|)
block|{
name|point
operator|=
name|segment
operator|->
name|points
operator|+
name|j
expr_stmt|;
name|point
operator|->
name|x
operator|/=
name|sc
operator|->
name|ratio_xy
expr_stmt|;
block|}
block|}
block|}
name|sc
operator|->
name|svp
operator|=
name|stroke
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* This is a more low level version. Expects a tile manager of depth 1.  *  * You cannot add additional polygons after this command.  */
end_comment

begin_function
name|void
DECL|function|gimp_scan_convert_render (GimpScanConvert * sc,TileManager * tile_manager,gint off_x,gint off_y,gboolean antialias)
name|gimp_scan_convert_render
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|TileManager
modifier|*
name|tile_manager
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|gboolean
name|antialias
parameter_list|)
block|{
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
name|gimp_scan_convert_render_internal
argument_list|(
name|sc
argument_list|,
name|tile_manager
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|antialias
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_scan_convert_render_value (GimpScanConvert * sc,TileManager * tile_manager,gint off_x,gint off_y,guchar value)
name|gimp_scan_convert_render_value
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|TileManager
modifier|*
name|tile_manager
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|guchar
name|value
parameter_list|)
block|{
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
name|gimp_scan_convert_render_internal
argument_list|(
name|sc
argument_list|,
name|tile_manager
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|FALSE
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scan_convert_render_internal (GimpScanConvert * sc,TileManager * tile_manager,gint off_x,gint off_y,gboolean antialias,guchar value)
name|gimp_scan_convert_render_internal
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|TileManager
modifier|*
name|tile_manager
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|guchar
name|value
parameter_list|)
block|{
name|PixelRegion
name|maskPR
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|gimp_scan_convert_finish
argument_list|(
name|sc
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sc
operator|->
name|svp
condition|)
return|return;
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
name|sc
operator|->
name|antialias
operator|=
name|antialias
expr_stmt|;
name|sc
operator|->
name|value
operator|=
name|value
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
name|sc
operator|->
name|buf
operator|=
name|maskPR
operator|.
name|data
expr_stmt|;
name|sc
operator|->
name|rowstride
operator|=
name|maskPR
operator|.
name|rowstride
expr_stmt|;
name|sc
operator|->
name|x0
operator|=
name|off_x
operator|+
name|maskPR
operator|.
name|x
expr_stmt|;
name|sc
operator|->
name|x1
operator|=
name|off_x
operator|+
name|maskPR
operator|.
name|x
operator|+
name|maskPR
operator|.
name|w
expr_stmt|;
name|art_svp_render_aa
argument_list|(
name|sc
operator|->
name|svp
argument_list|,
name|sc
operator|->
name|x0
argument_list|,
name|off_y
operator|+
name|maskPR
operator|.
name|y
argument_list|,
name|sc
operator|->
name|x1
argument_list|,
name|off_y
operator|+
name|maskPR
operator|.
name|y
operator|+
name|maskPR
operator|.
name|h
argument_list|,
name|gimp_scan_convert_render_callback
argument_list|,
name|sc
argument_list|)
expr_stmt|;
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
name|ArtSVP
modifier|*
name|svp
decl_stmt|,
modifier|*
name|svp2
decl_stmt|;
name|ArtSvpWriter
modifier|*
name|swr
decl_stmt|;
comment|/* return gracefully on empty path */
if|if
condition|(
operator|!
name|sc
operator|->
name|vpath
condition|)
return|return;
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
name|svp
operator|=
name|art_svp_from_vpath
argument_list|(
name|sc
operator|->
name|vpath
argument_list|)
expr_stmt|;
name|swr
operator|=
name|art_svp_writer_rewind_new
argument_list|(
name|ART_WIND_RULE_ODDEVEN
argument_list|)
expr_stmt|;
name|art_svp_intersector
argument_list|(
name|svp
argument_list|,
name|swr
argument_list|)
expr_stmt|;
name|svp2
operator|=
name|art_svp_writer_rewind_reap
argument_list|(
name|swr
argument_list|)
expr_stmt|;
comment|/* this also frees swr */
name|art_svp_free
argument_list|(
name|svp
argument_list|)
expr_stmt|;
name|sc
operator|->
name|svp
operator|=
name|svp2
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * private function to render libart SVPRenderAASteps into the pixel region  *  * A function pretty similiar to this could be used to implement a  * lookup table for the values (just change VALUE_TO_PIXEL).  *  * from the libart documentation:  *  * The value 0x8000 represents 0% coverage by the polygon, while  * 0xff8000 represents 100% coverage. This format is designed so that  *>> 16 results in a standard 0x00..0xff value range, with nice  * rounding.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_scan_convert_render_callback (gpointer user_data,gint y,gint start_value,ArtSVPRenderAAStep * steps,gint n_steps)
name|gimp_scan_convert_render_callback
parameter_list|(
name|gpointer
name|user_data
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|start_value
parameter_list|,
name|ArtSVPRenderAAStep
modifier|*
name|steps
parameter_list|,
name|gint
name|n_steps
parameter_list|)
block|{
name|GimpScanConvert
modifier|*
name|sc
init|=
name|user_data
decl_stmt|;
name|gint
name|cur_value
init|=
name|start_value
decl_stmt|;
name|gint
name|k
decl_stmt|,
name|run_x0
decl_stmt|,
name|run_x1
decl_stmt|;
DECL|macro|VALUE_TO_PIXEL (x)
define|#
directive|define
name|VALUE_TO_PIXEL
parameter_list|(
name|x
parameter_list|)
value|(sc->antialias ? \                            ((x)>> 16)   : \                            (((x)& (1<< 23) ? sc->value : 0)))
if|if
condition|(
name|n_steps
operator|>
literal|0
condition|)
block|{
name|run_x1
operator|=
name|steps
index|[
literal|0
index|]
operator|.
name|x
expr_stmt|;
if|if
condition|(
name|run_x1
operator|>
name|sc
operator|->
name|x0
condition|)
name|memset
argument_list|(
name|sc
operator|->
name|buf
argument_list|,
name|VALUE_TO_PIXEL
argument_list|(
name|cur_value
argument_list|)
argument_list|,
name|run_x1
operator|-
name|sc
operator|->
name|x0
argument_list|)
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|n_steps
operator|-
literal|1
condition|;
name|k
operator|++
control|)
block|{
name|cur_value
operator|+=
name|steps
index|[
name|k
index|]
operator|.
name|delta
expr_stmt|;
name|run_x0
operator|=
name|run_x1
expr_stmt|;
name|run_x1
operator|=
name|steps
index|[
name|k
operator|+
literal|1
index|]
operator|.
name|x
expr_stmt|;
if|if
condition|(
name|run_x1
operator|>
name|run_x0
condition|)
name|memset
argument_list|(
name|sc
operator|->
name|buf
operator|+
name|run_x0
operator|-
name|sc
operator|->
name|x0
argument_list|,
name|VALUE_TO_PIXEL
argument_list|(
name|cur_value
argument_list|)
argument_list|,
name|run_x1
operator|-
name|run_x0
argument_list|)
expr_stmt|;
block|}
name|cur_value
operator|+=
name|steps
index|[
name|k
index|]
operator|.
name|delta
expr_stmt|;
if|if
condition|(
name|sc
operator|->
name|x1
operator|>
name|run_x1
condition|)
name|memset
argument_list|(
name|sc
operator|->
name|buf
operator|+
name|run_x1
operator|-
name|sc
operator|->
name|x0
argument_list|,
name|VALUE_TO_PIXEL
argument_list|(
name|cur_value
argument_list|)
argument_list|,
name|sc
operator|->
name|x1
operator|-
name|run_x1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|memset
argument_list|(
name|sc
operator|->
name|buf
argument_list|,
name|VALUE_TO_PIXEL
argument_list|(
name|cur_value
argument_list|)
argument_list|,
name|sc
operator|->
name|x1
operator|-
name|sc
operator|->
name|x0
argument_list|)
expr_stmt|;
block|}
name|sc
operator|->
name|buf
operator|+=
name|sc
operator|->
name|rowstride
expr_stmt|;
undef|#
directive|undef
name|VALUE_TO_PIXEL
block|}
end_function

end_unit

