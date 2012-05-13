begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
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
file|"gimpbezierdesc.h"
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
DECL|member|clip
name|gboolean
name|clip
decl_stmt|;
DECL|member|clip_x
name|gint
name|clip_x
decl_stmt|;
DECL|member|clip_y
name|gint
name|clip_y
decl_stmt|;
DECL|member|clip_w
name|gint
name|clip_w
decl_stmt|;
DECL|member|clip_h
name|gint
name|clip_h
decl_stmt|;
comment|/* stroking options */
DECL|member|do_stroke
name|gboolean
name|do_stroke
decl_stmt|;
DECL|member|width
name|gdouble
name|width
decl_stmt|;
DECL|member|join
name|GimpJoinStyle
name|join
decl_stmt|;
DECL|member|cap
name|GimpCapStyle
name|cap
decl_stmt|;
DECL|member|miter
name|gdouble
name|miter
decl_stmt|;
DECL|member|dash_offset
name|gdouble
name|dash_offset
decl_stmt|;
DECL|member|dash_info
name|GArray
modifier|*
name|dash_info
decl_stmt|;
DECL|member|path_data
name|GArray
modifier|*
name|path_data
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_scan_convert_new:  *  * Create a new scan conversion context.  *  * Return value: a newly allocated #GimpScanConvert context.  */
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
init|=
name|g_slice_new0
argument_list|(
name|GimpScanConvert
argument_list|)
decl_stmt|;
name|sc
operator|->
name|path_data
operator|=
name|g_array_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|cairo_path_data_t
argument_list|)
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

begin_comment
comment|/**  * gimp_scan_convert_free:  * @sc: a #GimpScanConvert context  *  * Frees the resources allocated for @sc.  */
end_comment

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
name|path_data
condition|)
name|g_array_free
argument_list|(
name|sc
operator|->
name|path_data
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|sc
operator|->
name|dash_info
condition|)
name|g_array_free
argument_list|(
name|sc
operator|->
name|dash_info
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpScanConvert
argument_list|,
name|sc
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_scan_convert_set_pixel_ratio:  * @sc:       a #GimpScanConvert context  * @ratio_xy: the aspect ratio of the major coordinate axes  *  * Sets the pixel aspect ratio.  */
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
comment|/**  * gimp_scan_convert_set_clip_rectangle  * @sc:     a #GimpScanConvert context  * @x:      horizontal offset of clip rectangle  * @y:      vertical offset of clip rectangle  * @width:  width of clip rectangle  * @height: height of clip rectangle  *  * Sets a clip rectangle on @sc. Subsequent render operations will be  * restricted to this area.  */
end_comment

begin_function
name|void
DECL|function|gimp_scan_convert_set_clip_rectangle (GimpScanConvert * sc,gint x,gint y,gint width,gint height)
name|gimp_scan_convert_set_clip_rectangle
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|sc
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|sc
operator|->
name|clip
operator|=
name|TRUE
expr_stmt|;
name|sc
operator|->
name|clip_x
operator|=
name|x
expr_stmt|;
name|sc
operator|->
name|clip_y
operator|=
name|y
expr_stmt|;
name|sc
operator|->
name|clip_w
operator|=
name|width
expr_stmt|;
name|sc
operator|->
name|clip_h
operator|=
name|height
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_scan_convert_add_polyline:  * @sc:       a #GimpScanConvert context  * @n_points: number of points to add  * @points:   array of points to add  * @closed:   whether to close the polyline and make it a polygon  *  * Add a polyline with @n_points @points that may be open or closed.  *  * Please note that you should use gimp_scan_convert_stroke() if you  * specify open polygons.  */
end_comment

begin_function
name|void
DECL|function|gimp_scan_convert_add_polyline (GimpScanConvert * sc,guint n_points,const GimpVector2 * points,gboolean closed)
name|gimp_scan_convert_add_polyline
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|guint
name|n_points
parameter_list|,
specifier|const
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
name|cairo_path_data_t
name|pd
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
name|pd
operator|.
name|header
operator|.
name|type
operator|=
operator|(
name|i
operator|==
literal|0
operator|)
condition|?
name|CAIRO_PATH_MOVE_TO
else|:
name|CAIRO_PATH_LINE_TO
expr_stmt|;
name|pd
operator|.
name|header
operator|.
name|length
operator|=
literal|2
expr_stmt|;
name|sc
operator|->
name|path_data
operator|=
name|g_array_append_val
argument_list|(
name|sc
operator|->
name|path_data
argument_list|,
name|pd
argument_list|)
expr_stmt|;
name|pd
operator|.
name|point
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
name|pd
operator|.
name|point
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
name|path_data
operator|=
name|g_array_append_val
argument_list|(
name|sc
operator|->
name|path_data
argument_list|,
name|pd
argument_list|)
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
condition|)
block|{
name|pd
operator|.
name|header
operator|.
name|type
operator|=
name|CAIRO_PATH_CLOSE_PATH
expr_stmt|;
name|pd
operator|.
name|header
operator|.
name|length
operator|=
literal|1
expr_stmt|;
name|sc
operator|->
name|path_data
operator|=
name|g_array_append_val
argument_list|(
name|sc
operator|->
name|path_data
argument_list|,
name|pd
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_scan_convert_add_polyline:  * @sc:     a #GimpScanConvert context  * @bezier: a #GimpBezierDesc  *  * Adds a @bezier path to @sc.  *  * Please note that you should use gimp_scan_convert_stroke() if you  * specify open paths.  **/
end_comment

begin_function
name|void
DECL|function|gimp_scan_convert_add_bezier (GimpScanConvert * sc,const GimpBezierDesc * bezier)
name|gimp_scan_convert_add_bezier
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
specifier|const
name|GimpBezierDesc
modifier|*
name|bezier
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
name|bezier
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|sc
operator|->
name|path_data
operator|=
name|g_array_append_vals
argument_list|(
name|sc
operator|->
name|path_data
argument_list|,
name|bezier
operator|->
name|data
argument_list|,
name|bezier
operator|->
name|num_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_scan_convert_stroke:  * @sc:          a #GimpScanConvert context  * @width:       line width in pixels  * @join:        how lines should be joined  * @cap:         how to render the end of lines  * @miter:       convert a mitered join to a bevelled join if the miter would  *               extend to a distance of more than @miter times @width from  *               the actual join point  * @dash_offset: offset to apply on the dash pattern  * @dash_info:   dash pattern or %NULL for a solid line  *  * Stroke the content of a GimpScanConvert. The next  * gimp_scan_convert_render() will result in the outline of the  * polygon defined with the commands above.  *  * You cannot add additional polygons after this command.  *  * Note that if you have nonstandard resolution, "width" gives the  * width (in pixels) for a vertical stroke, i.e. use the X resolution  * to calculate the width of a stroke when operating with real world  * units.  */
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
name|sc
operator|->
name|do_stroke
operator|=
name|TRUE
expr_stmt|;
name|sc
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|sc
operator|->
name|join
operator|=
name|join
expr_stmt|;
name|sc
operator|->
name|cap
operator|=
name|cap
expr_stmt|;
name|sc
operator|->
name|miter
operator|=
name|miter
expr_stmt|;
if|if
condition|(
name|sc
operator|->
name|dash_info
condition|)
block|{
name|g_array_free
argument_list|(
name|sc
operator|->
name|dash_info
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|sc
operator|->
name|dash_info
operator|=
name|NULL
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
name|gint
name|n_dashes
decl_stmt|;
name|gdouble
modifier|*
name|dashes
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|dash_offset
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
name|n_dashes
operator|=
name|dash_info
operator|->
name|len
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
comment|/* correct 0.0 in the first element (starts with a gap) */
if|if
condition|(
name|dashes
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
name|dashes
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
name|dashes
index|[
name|i
index|]
operator|=
name|dashes
index|[
name|i
operator|+
literal|2
index|]
expr_stmt|;
name|dash_offset
operator|+=
name|dashes
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
name|dashes
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
name|n_dashes
operator|--
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|dash_info
operator|->
name|len
operator|>
literal|2
condition|)
block|{
name|dashes
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
name|n_dashes
operator|-=
literal|2
expr_stmt|;
block|}
block|}
comment|/* correct odd number of dash specifiers */
if|if
condition|(
name|n_dashes
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
name|dashes
index|[
name|n_dashes
operator|-
literal|1
index|]
expr_stmt|;
name|dashes
index|[
literal|0
index|]
operator|+=
name|last
expr_stmt|;
name|dash_offset
operator|+=
name|last
expr_stmt|;
name|n_dashes
operator|--
expr_stmt|;
block|}
if|if
condition|(
name|n_dashes
operator|>=
literal|2
condition|)
block|{
name|sc
operator|->
name|dash_info
operator|=
name|g_array_sized_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|,
name|n_dashes
argument_list|)
expr_stmt|;
name|sc
operator|->
name|dash_info
operator|=
name|g_array_append_vals
argument_list|(
name|sc
operator|->
name|dash_info
argument_list|,
name|dashes
argument_list|,
name|n_dashes
argument_list|)
expr_stmt|;
name|sc
operator|->
name|dash_offset
operator|=
name|dash_offset
expr_stmt|;
block|}
name|g_free
argument_list|(
name|dashes
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_scan_convert_render:  * @sc:        a #GimpScanConvert context  * @bufferr:   the #GeglBuffer to render to  * @off_x:     horizontal offset into the @buffer  * @off_y:     vertical offset into the @buffer  * @antialias: whether to apply antialiasiing  *  * This is a wrapper around gimp_scan_convert_render_full() that replaces the  * content of the @buffer with a rendered form of the path passed in.  *  * You cannot add additional polygons after this command.  */
end_comment

begin_function
name|void
DECL|function|gimp_scan_convert_render (GimpScanConvert * sc,GeglBuffer * buffer,gint off_x,gint off_y,gboolean antialias)
name|gimp_scan_convert_render
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
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
name|gimp_scan_convert_render_full
argument_list|(
name|sc
argument_list|,
name|buffer
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|TRUE
argument_list|,
name|antialias
argument_list|,
literal|255
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_scan_convert_render_value:  * @sc:     a #GimpScanConvert context  * @buffer: the #GeglBuffer to render to  * @off_x:  horizontal offset into the @buffer  * @off_y:  vertical offset into the @buffer  * @value:  value to use for covered pixels  *  * This is a wrapper around gimp_scan_convert_render_full() that  * doesn't do antialiasing but gives control over the value that  * should be used for pixels covered by the scan conversion. Uncovered  * pixels are set to zero.  *  * You cannot add additional polygons after this command.  */
end_comment

begin_function
name|void
DECL|function|gimp_scan_convert_render_value (GimpScanConvert * sc,GeglBuffer * buffer,gint off_x,gint off_y,guchar value)
name|gimp_scan_convert_render_value
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
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
name|gimp_scan_convert_render_full
argument_list|(
name|sc
argument_list|,
name|buffer
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_scan_convert_compose:  * @sc:     a #GimpScanConvert context  * @buffer: the #GeglBuffer to render to  * @off_x:  horizontal offset into the @buffer  * @off_y:  vertical offset into the @buffer  *  * This is a wrapper around of gimp_scan_convert_render_full() that composes  * the (aliased) scan conversion on top of the content of the @buffer.  *  * You cannot add additional polygons after this command.  */
end_comment

begin_function
name|void
DECL|function|gimp_scan_convert_compose (GimpScanConvert * sc,GeglBuffer * buffer,gint off_x,gint off_y)
name|gimp_scan_convert_compose
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
block|{
name|gimp_scan_convert_render_full
argument_list|(
name|sc
argument_list|,
name|buffer
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|255
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_scan_convert_compose_value:  * @sc:     a #GimpScanConvert context  * @buffer: the #GeglBuffer to render to  * @off_x:  horizontal offset into the @buffer  * @off_y:  vertical offset into the @buffer  * @value:  value to use for covered pixels  *  * This is a wrapper around gimp_scan_convert_render_full() that  * composes the (aliased) scan conversion with value @value on top of the  * content of the @buffer.  *  * You cannot add additional polygons after this command.  */
end_comment

begin_function
name|void
DECL|function|gimp_scan_convert_compose_value (GimpScanConvert * sc,GeglBuffer * buffer,gint off_x,gint off_y,gint value)
name|gimp_scan_convert_compose_value
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|gint
name|value
parameter_list|)
block|{
name|gimp_scan_convert_render_full
argument_list|(
name|sc
argument_list|,
name|buffer
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_scan_convert_render_full:  * @sc:        a #GimpScanConvert context  * @buffer:    the #GeglBuffer to render to  * @off_x:     horizontal offset into the @buffer  * @off_y:     vertical offset into the @buffer  * @replace:   if true the original content of the @buffer gets estroyed  * @antialias: if true the rendering happens antialiased  * @value:     value to use for covered pixels  *  * This function renders the area described by the path to the  * @buffer, taking the offset @off_x and @off_y in the buffer into  * account.  The rendering can happen antialiased and be rendered on  * top of existing content or replacing it completely. The @value  * specifies the opacity value to be used for the objects in the @sc.  *  * You cannot add additional polygons after this command.  */
end_comment

begin_function
name|void
DECL|function|gimp_scan_convert_render_full (GimpScanConvert * sc,GeglBuffer * buffer,gint off_x,gint off_y,gboolean replace,gboolean antialias,guchar value)
name|gimp_scan_convert_render_full
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|gboolean
name|replace
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|guchar
name|value
parameter_list|)
block|{
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|GeglRectangle
modifier|*
name|roi
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
name|cairo_path_t
name|path
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
decl_stmt|,
name|height
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
name|GEGL_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|x
operator|=
literal|0
expr_stmt|;
name|y
operator|=
literal|0
expr_stmt|;
name|width
operator|=
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|height
operator|=
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|sc
operator|->
name|clip
operator|&&
operator|!
name|gimp_rectangle_intersect
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|sc
operator|->
name|clip_x
argument_list|,
name|sc
operator|->
name|clip_y
argument_list|,
name|sc
operator|->
name|clip_w
argument_list|,
name|sc
operator|->
name|clip_h
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
return|return;
name|path
operator|.
name|status
operator|=
name|CAIRO_STATUS_SUCCESS
expr_stmt|;
name|path
operator|.
name|data
operator|=
operator|(
name|cairo_path_data_t
operator|*
operator|)
name|sc
operator|->
name|path_data
operator|->
name|data
expr_stmt|;
name|path
operator|.
name|num_data
operator|=
name|sc
operator|->
name|path_data
operator|->
name|len
expr_stmt|;
name|format
operator|=
name|babl_format
argument_list|(
literal|"Y u8"
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|format
argument_list|,
name|GEGL_BUFFER_WRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|roi
operator|=
operator|&
name|iter
operator|->
name|roi
index|[
literal|0
index|]
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|guchar
modifier|*
name|data
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|guchar
modifier|*
name|tmp_buf
init|=
name|NULL
decl_stmt|;
specifier|const
name|gint
name|stride
init|=
name|cairo_format_stride_for_width
argument_list|(
name|CAIRO_FORMAT_A8
argument_list|,
name|roi
operator|->
name|width
argument_list|)
decl_stmt|;
comment|/*  cairo rowstrides are always multiples of 4, whereas        *  maskPR.rowstride can be anything, so to be able to create an        *  image surface, we maybe have to create our own temporary        *  buffer        */
if|if
condition|(
name|roi
operator|->
name|width
operator|*
name|bpp
operator|!=
name|stride
condition|)
block|{
specifier|const
name|guchar
modifier|*
name|src
init|=
name|data
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|dest
operator|=
name|tmp_buf
operator|=
name|g_alloca
argument_list|(
name|stride
operator|*
name|roi
operator|->
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|replace
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
name|roi
operator|->
name|height
condition|;
name|i
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|dest
argument_list|,
name|src
argument_list|,
name|roi
operator|->
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|src
operator|+=
name|roi
operator|->
name|width
operator|*
name|bpp
expr_stmt|;
name|dest
operator|+=
name|stride
expr_stmt|;
block|}
block|}
block|}
name|surface
operator|=
name|cairo_image_surface_create_for_data
argument_list|(
name|tmp_buf
condition|?
name|tmp_buf
else|:
name|data
argument_list|,
name|CAIRO_FORMAT_A8
argument_list|,
name|roi
operator|->
name|width
argument_list|,
name|roi
operator|->
name|height
argument_list|,
name|stride
argument_list|)
expr_stmt|;
name|cairo_surface_set_device_offset
argument_list|(
name|surface
argument_list|,
operator|-
name|off_x
operator|-
name|roi
operator|->
name|x
argument_list|,
operator|-
name|off_y
operator|-
name|roi
operator|->
name|y
argument_list|)
expr_stmt|;
name|cr
operator|=
name|cairo_create
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|cairo_set_operator
argument_list|(
name|cr
argument_list|,
name|CAIRO_OPERATOR_SOURCE
argument_list|)
expr_stmt|;
if|if
condition|(
name|replace
condition|)
block|{
name|cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
name|cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|value
operator|/
literal|255.0
argument_list|)
expr_stmt|;
name|cairo_append_path
argument_list|(
name|cr
argument_list|,
operator|&
name|path
argument_list|)
expr_stmt|;
name|cairo_set_antialias
argument_list|(
name|cr
argument_list|,
name|antialias
condition|?
name|CAIRO_ANTIALIAS_GRAY
else|:
name|CAIRO_ANTIALIAS_NONE
argument_list|)
expr_stmt|;
name|cairo_set_miter_limit
argument_list|(
name|cr
argument_list|,
name|sc
operator|->
name|miter
argument_list|)
expr_stmt|;
if|if
condition|(
name|sc
operator|->
name|do_stroke
condition|)
block|{
name|cairo_set_line_cap
argument_list|(
name|cr
argument_list|,
name|sc
operator|->
name|cap
operator|==
name|GIMP_CAP_BUTT
condition|?
name|CAIRO_LINE_CAP_BUTT
else|:
name|sc
operator|->
name|cap
operator|==
name|GIMP_CAP_ROUND
condition|?
name|CAIRO_LINE_CAP_ROUND
else|:
name|CAIRO_LINE_CAP_SQUARE
argument_list|)
expr_stmt|;
name|cairo_set_line_join
argument_list|(
name|cr
argument_list|,
name|sc
operator|->
name|join
operator|==
name|GIMP_JOIN_MITER
condition|?
name|CAIRO_LINE_JOIN_MITER
else|:
name|sc
operator|->
name|join
operator|==
name|GIMP_JOIN_ROUND
condition|?
name|CAIRO_LINE_JOIN_ROUND
else|:
name|CAIRO_LINE_JOIN_BEVEL
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
name|sc
operator|->
name|width
argument_list|)
expr_stmt|;
if|if
condition|(
name|sc
operator|->
name|dash_info
condition|)
name|cairo_set_dash
argument_list|(
name|cr
argument_list|,
operator|(
name|double
operator|*
operator|)
name|sc
operator|->
name|dash_info
operator|->
name|data
argument_list|,
name|sc
operator|->
name|dash_info
operator|->
name|len
argument_list|,
name|sc
operator|->
name|dash_offset
argument_list|)
expr_stmt|;
name|cairo_scale
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|,
name|sc
operator|->
name|ratio_xy
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|cairo_set_fill_rule
argument_list|(
name|cr
argument_list|,
name|CAIRO_FILL_RULE_EVEN_ODD
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|surface
argument_list|)
expr_stmt|;
if|if
condition|(
name|tmp_buf
condition|)
block|{
name|guchar
modifier|*
name|dest
init|=
name|data
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src
init|=
name|tmp_buf
decl_stmt|;
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
name|roi
operator|->
name|height
condition|;
name|i
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|dest
argument_list|,
name|src
argument_list|,
name|roi
operator|->
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|src
operator|+=
name|stride
expr_stmt|;
name|dest
operator|+=
name|roi
operator|->
name|width
operator|*
name|bpp
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

end_unit

