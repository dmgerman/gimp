begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * IfsCompose is a interface for creating IFS fractals by  * direct manipulation.  * Copyright (C) 1997 Owen Taylor  *  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_typedef
DECL|struct|__anon292481780108
typedef|typedef
struct|struct
block|{
DECL|member|a11
DECL|member|a12
DECL|member|a21
DECL|member|a22
DECL|member|b1
DECL|member|b2
name|gdouble
name|a11
decl_stmt|,
name|a12
decl_stmt|,
name|a21
decl_stmt|,
name|a22
decl_stmt|,
name|b1
decl_stmt|,
name|b2
decl_stmt|;
DECL|typedef|Aff2
block|}
name|Aff2
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon292481780208
typedef|typedef
struct|struct
block|{
DECL|member|vals
name|gdouble
name|vals
index|[
literal|3
index|]
index|[
literal|4
index|]
decl_stmt|;
DECL|typedef|Aff3
block|}
name|Aff3
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon292481780308
typedef|typedef
struct|struct
block|{
DECL|member|points
name|GdkPoint
modifier|*
name|points
decl_stmt|;
DECL|member|npoints
name|gint
name|npoints
decl_stmt|;
DECL|typedef|IPolygon
block|}
name|IPolygon
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon292481780408
typedef|typedef
struct|struct
block|{
DECL|member|x
DECL|member|y
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
DECL|member|theta
name|gdouble
name|theta
decl_stmt|;
DECL|member|scale
name|gdouble
name|scale
decl_stmt|;
DECL|member|asym
name|gdouble
name|asym
decl_stmt|;
DECL|member|shear
name|gdouble
name|shear
decl_stmt|;
DECL|member|flip
name|gint
name|flip
decl_stmt|;
DECL|member|red_color
name|GimpRGB
name|red_color
decl_stmt|;
DECL|member|green_color
name|GimpRGB
name|green_color
decl_stmt|;
DECL|member|blue_color
name|GimpRGB
name|blue_color
decl_stmt|;
DECL|member|black_color
name|GimpRGB
name|black_color
decl_stmt|;
DECL|member|target_color
name|GimpRGB
name|target_color
decl_stmt|;
DECL|member|hue_scale
name|gdouble
name|hue_scale
decl_stmt|;
DECL|member|value_scale
name|gdouble
name|value_scale
decl_stmt|;
DECL|member|simple_color
name|gint
name|simple_color
decl_stmt|;
DECL|member|prob
name|gdouble
name|prob
decl_stmt|;
DECL|typedef|AffElementVals
block|}
name|AffElementVals
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon292481780508
block|{
DECL|member|num_elements
name|gint
name|num_elements
decl_stmt|;
DECL|member|iterations
name|gint
name|iterations
decl_stmt|;
DECL|member|max_memory
name|gint
name|max_memory
decl_stmt|;
DECL|member|subdivide
name|gint
name|subdivide
decl_stmt|;
DECL|member|radius
name|gdouble
name|radius
decl_stmt|;
DECL|member|aspect_ratio
name|gdouble
name|aspect_ratio
decl_stmt|;
DECL|member|center_x
name|gdouble
name|center_x
decl_stmt|;
DECL|member|center_y
name|gdouble
name|center_y
decl_stmt|;
DECL|typedef|IfsComposeVals
block|}
name|IfsComposeVals
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon292481780608
typedef|typedef
struct|struct
block|{
DECL|member|v
name|AffElementVals
name|v
decl_stmt|;
DECL|member|trans
name|Aff2
name|trans
decl_stmt|;
DECL|member|color_trans
name|Aff3
name|color_trans
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|click_boundary
name|IPolygon
modifier|*
name|click_boundary
decl_stmt|;
DECL|member|draw_boundary
name|IPolygon
modifier|*
name|draw_boundary
decl_stmt|;
DECL|typedef|AffElement
block|}
name|AffElement
typedef|;
end_typedef

begin_comment
comment|/* manipulation of affine transforms */
end_comment

begin_function_decl
name|void
name|aff2_translate
parameter_list|(
name|Aff2
modifier|*
name|naff
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff2_rotate
parameter_list|(
name|Aff2
modifier|*
name|naff
parameter_list|,
name|gdouble
name|theta
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff2_scale
parameter_list|(
name|Aff2
modifier|*
name|naff
parameter_list|,
name|gdouble
name|s
parameter_list|,
name|gint
name|flip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff2_distort
parameter_list|(
name|Aff2
modifier|*
name|naff
parameter_list|,
name|gdouble
name|asym
parameter_list|,
name|gdouble
name|shear
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff2_compute_stretch
parameter_list|(
name|Aff2
modifier|*
name|naff
parameter_list|,
name|gdouble
name|xo
parameter_list|,
name|gdouble
name|yo
parameter_list|,
name|gdouble
name|xn
parameter_list|,
name|gdouble
name|yn
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff2_compute_distort
parameter_list|(
name|Aff2
modifier|*
name|naff
parameter_list|,
name|gdouble
name|xo
parameter_list|,
name|gdouble
name|yo
parameter_list|,
name|gdouble
name|xn
parameter_list|,
name|gdouble
name|yn
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff2_compose
parameter_list|(
name|Aff2
modifier|*
name|naff
parameter_list|,
name|Aff2
modifier|*
name|aff1
parameter_list|,
name|Aff2
modifier|*
name|aff2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff2_invert
parameter_list|(
name|Aff2
modifier|*
name|naff
parameter_list|,
name|Aff2
modifier|*
name|aff
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff2_apply
parameter_list|(
name|Aff2
modifier|*
name|aff
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|xf
parameter_list|,
name|gdouble
modifier|*
name|yf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff2_fixed_point
parameter_list|(
name|Aff2
modifier|*
name|aff
parameter_list|,
name|gdouble
modifier|*
name|xf
parameter_list|,
name|gdouble
modifier|*
name|yf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff3_apply
parameter_list|(
name|Aff3
modifier|*
name|t
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|z
parameter_list|,
name|gdouble
modifier|*
name|xf
parameter_list|,
name|gdouble
modifier|*
name|yf
parameter_list|,
name|gdouble
modifier|*
name|zf
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* manipulation of polygons */
end_comment

begin_function_decl
name|IPolygon
modifier|*
name|ipolygon_convex_hull
parameter_list|(
name|IPolygon
modifier|*
name|poly
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|ipolygon_contains
parameter_list|(
name|IPolygon
modifier|*
name|poly
parameter_list|,
name|gint
name|xt
parameter_list|,
name|gint
name|yt
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* manipulation of composite transforms */
end_comment

begin_function_decl
name|AffElement
modifier|*
name|aff_element_new
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|count
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff_element_free
parameter_list|(
name|AffElement
modifier|*
name|elem
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff_element_compute_trans
parameter_list|(
name|AffElement
modifier|*
name|elem
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff_element_compute_color_trans
parameter_list|(
name|AffElement
modifier|*
name|elem
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff_element_decompose_trans
parameter_list|(
name|AffElement
modifier|*
name|elem
parameter_list|,
name|Aff2
modifier|*
name|aff
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff_element_compute_boundary
parameter_list|(
name|AffElement
modifier|*
name|elem
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|AffElement
modifier|*
modifier|*
name|elements
parameter_list|,
name|int
name|num_elements
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|aff_element_draw
parameter_list|(
name|AffElement
modifier|*
name|elem
parameter_list|,
name|gint
name|selected
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GdkDrawable
modifier|*
name|win
parameter_list|,
name|GdkGC
modifier|*
name|normal_gc
parameter_list|,
name|GdkGC
modifier|*
name|selected_gc
parameter_list|,
name|PangoLayout
modifier|*
name|layout
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ifs_render
parameter_list|(
name|AffElement
modifier|*
modifier|*
name|elements
parameter_list|,
name|gint
name|num_elements
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|nsteps
parameter_list|,
name|IfsComposeVals
modifier|*
name|vals
parameter_list|,
name|gint
name|band_y
parameter_list|,
name|gint
name|band_height
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|,
name|guchar
modifier|*
name|mask
parameter_list|,
name|guchar
modifier|*
name|nhits
parameter_list|,
name|gint
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|ifsvals_stringify
parameter_list|(
name|IfsComposeVals
modifier|*
name|vals
parameter_list|,
name|AffElement
modifier|*
modifier|*
name|elements
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|ifsvals_parse_string
parameter_list|(
specifier|const
name|gchar
modifier|*
name|str
parameter_list|,
name|IfsComposeVals
modifier|*
name|vals
parameter_list|,
name|AffElement
modifier|*
modifier|*
modifier|*
name|elements
parameter_list|)
function_decl|;
end_function_decl

end_unit

