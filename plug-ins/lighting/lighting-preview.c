begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*************************************************/
end_comment

begin_comment
comment|/* Compute a preview image and preview wireframe */
end_comment

begin_comment
comment|/*************************************************/
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|<libgimpmath/gimpmath.h>
end_include

begin_include
include|#
directive|include
file|"lighting-main.h"
end_include

begin_include
include|#
directive|include
file|"lighting-ui.h"
end_include

begin_include
include|#
directive|include
file|"lighting-image.h"
end_include

begin_include
include|#
directive|include
file|"lighting-apply.h"
end_include

begin_include
include|#
directive|include
file|"lighting-shade.h"
end_include

begin_include
include|#
directive|include
file|"lighting-preview.h"
end_include

begin_define
DECL|macro|LIGHT_SYMBOL_SIZE
define|#
directive|define
name|LIGHT_SYMBOL_SIZE
value|8
end_define

begin_decl_stmt
DECL|variable|handle_xpos
DECL|variable|handle_ypos
specifier|static
name|gint
name|handle_xpos
init|=
literal|0
decl_stmt|,
name|handle_ypos
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* g_free()'ed on exit */
end_comment

begin_decl_stmt
DECL|variable|xpostab
name|gdouble
modifier|*
name|xpostab
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ypostab
name|gdouble
modifier|*
name|ypostab
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|xpostab_size
specifier|static
name|gint
name|xpostab_size
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|xpostab_size
comment|/* if preview size change, do realloc */
end_comment

begin_decl_stmt
DECL|variable|ypostab_size
specifier|static
name|gint
name|ypostab_size
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|light_hit
specifier|static
name|gboolean
name|light_hit
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|left_button_pressed
specifier|static
name|gboolean
name|left_button_pressed
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|preview_update_timer
specifier|static
name|guint
name|preview_update_timer
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Protos */
end_comment

begin_comment
comment|/* ====== */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|interactive_preview_timer_callback
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|compute_preview (gint startx,gint starty,gint w,gint h)
name|compute_preview
parameter_list|(
name|gint
name|startx
parameter_list|,
name|gint
name|starty
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|gint
name|xcnt
decl_stmt|,
name|ycnt
decl_stmt|,
name|f1
decl_stmt|,
name|f2
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gdouble
name|imagex
decl_stmt|,
name|imagey
decl_stmt|;
name|gint32
name|index
init|=
literal|0
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|GimpRGB
name|lightcheck
decl_stmt|,
name|darkcheck
decl_stmt|;
name|GimpVector3
name|pos
decl_stmt|;
name|get_ray_func
name|ray_func
decl_stmt|;
if|if
condition|(
name|xpostab_size
operator|!=
name|w
condition|)
block|{
if|if
condition|(
name|xpostab
condition|)
block|{
name|g_free
argument_list|(
name|xpostab
argument_list|)
expr_stmt|;
name|xpostab
operator|=
name|NULL
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|xpostab
condition|)
block|{
name|xpostab
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|w
argument_list|)
expr_stmt|;
name|xpostab_size
operator|=
name|w
expr_stmt|;
block|}
if|if
condition|(
name|ypostab_size
operator|!=
name|h
condition|)
block|{
if|if
condition|(
name|ypostab
condition|)
block|{
name|g_free
argument_list|(
name|ypostab
argument_list|)
expr_stmt|;
name|ypostab
operator|=
name|NULL
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|ypostab
condition|)
block|{
name|ypostab
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|ypostab_size
operator|=
name|h
expr_stmt|;
block|}
for|for
control|(
name|xcnt
operator|=
literal|0
init|;
name|xcnt
operator|<
name|w
condition|;
name|xcnt
operator|++
control|)
name|xpostab
index|[
name|xcnt
index|]
operator|=
operator|(
name|gdouble
operator|)
name|width
operator|*
operator|(
operator|(
name|gdouble
operator|)
name|xcnt
operator|/
operator|(
name|gdouble
operator|)
name|w
operator|)
expr_stmt|;
for|for
control|(
name|ycnt
operator|=
literal|0
init|;
name|ycnt
operator|<
name|h
condition|;
name|ycnt
operator|++
control|)
name|ypostab
index|[
name|ycnt
index|]
operator|=
operator|(
name|gdouble
operator|)
name|height
operator|*
operator|(
operator|(
name|gdouble
operator|)
name|ycnt
operator|/
operator|(
name|gdouble
operator|)
name|h
operator|)
expr_stmt|;
name|precompute_init
argument_list|(
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|lightcheck
argument_list|,
name|GIMP_CHECK_LIGHT
argument_list|,
name|GIMP_CHECK_LIGHT
argument_list|,
name|GIMP_CHECK_LIGHT
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|darkcheck
argument_list|,
name|GIMP_CHECK_DARK
argument_list|,
name|GIMP_CHECK_DARK
argument_list|,
name|GIMP_CHECK_DARK
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|mapvals
operator|.
name|bump_mapped
operator|==
name|TRUE
operator|&&
name|mapvals
operator|.
name|bumpmap_id
operator|!=
operator|-
literal|1
condition|)
block|{
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|bump_region
argument_list|,
name|gimp_drawable_get
argument_list|(
name|mapvals
operator|.
name|bumpmap_id
argument_list|)
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
block|}
name|imagey
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|mapvals
operator|.
name|previewquality
condition|)
name|ray_func
operator|=
name|get_ray_color
expr_stmt|;
else|else
name|ray_func
operator|=
name|get_ray_color_no_bilinear
expr_stmt|;
if|if
condition|(
name|mapvals
operator|.
name|env_mapped
operator|==
name|TRUE
operator|&&
name|mapvals
operator|.
name|envmap_id
operator|!=
operator|-
literal|1
condition|)
block|{
name|env_width
operator|=
name|gimp_drawable_width
argument_list|(
name|mapvals
operator|.
name|envmap_id
argument_list|)
expr_stmt|;
name|env_height
operator|=
name|gimp_drawable_height
argument_list|(
name|mapvals
operator|.
name|envmap_id
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|env_region
argument_list|,
name|gimp_drawable_get
argument_list|(
name|mapvals
operator|.
name|envmap_id
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|env_width
argument_list|,
name|env_height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|mapvals
operator|.
name|previewquality
condition|)
name|ray_func
operator|=
name|get_ray_color_ref
expr_stmt|;
else|else
name|ray_func
operator|=
name|get_ray_color_no_bilinear_ref
expr_stmt|;
block|}
name|cairo_surface_flush
argument_list|(
name|preview_surface
argument_list|)
expr_stmt|;
for|for
control|(
name|ycnt
operator|=
literal|0
init|;
name|ycnt
operator|<
name|PREVIEW_HEIGHT
condition|;
name|ycnt
operator|++
control|)
block|{
name|index
operator|=
name|ycnt
operator|*
name|preview_rgb_stride
expr_stmt|;
for|for
control|(
name|xcnt
operator|=
literal|0
init|;
name|xcnt
operator|<
name|PREVIEW_WIDTH
condition|;
name|xcnt
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|ycnt
operator|>=
name|starty
operator|&&
name|ycnt
operator|<
operator|(
name|starty
operator|+
name|h
operator|)
operator|)
operator|&&
operator|(
name|xcnt
operator|>=
name|startx
operator|&&
name|xcnt
operator|<
operator|(
name|startx
operator|+
name|w
operator|)
operator|)
condition|)
block|{
name|imagex
operator|=
name|xpostab
index|[
name|xcnt
operator|-
name|startx
index|]
expr_stmt|;
name|imagey
operator|=
name|ypostab
index|[
name|ycnt
operator|-
name|starty
index|]
expr_stmt|;
name|pos
operator|=
name|int_to_posf
argument_list|(
name|imagex
argument_list|,
name|imagey
argument_list|)
expr_stmt|;
if|if
condition|(
name|mapvals
operator|.
name|bump_mapped
operator|==
name|TRUE
operator|&&
name|mapvals
operator|.
name|bumpmap_id
operator|!=
operator|-
literal|1
operator|&&
name|xcnt
operator|==
name|startx
condition|)
block|{
name|pos_to_float
argument_list|(
name|pos
operator|.
name|x
argument_list|,
name|pos
operator|.
name|y
argument_list|,
operator|&
name|imagex
argument_list|,
operator|&
name|imagey
argument_list|)
expr_stmt|;
name|precompute_normals
argument_list|(
literal|0
argument_list|,
name|width
argument_list|,
name|RINT
argument_list|(
name|imagey
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|color
operator|=
call|(
modifier|*
name|ray_func
call|)
argument_list|(
operator|&
name|pos
argument_list|)
expr_stmt|;
if|if
condition|(
name|color
operator|.
name|a
operator|<
literal|1.0
condition|)
block|{
name|f1
operator|=
operator|(
operator|(
name|xcnt
operator|%
literal|32
operator|)
operator|<
literal|16
operator|)
expr_stmt|;
name|f2
operator|=
operator|(
operator|(
name|ycnt
operator|%
literal|32
operator|)
operator|<
literal|16
operator|)
expr_stmt|;
name|f1
operator|=
name|f1
operator|^
name|f2
expr_stmt|;
if|if
condition|(
name|f1
condition|)
block|{
if|if
condition|(
name|color
operator|.
name|a
operator|==
literal|0.0
condition|)
name|color
operator|=
name|lightcheck
expr_stmt|;
else|else
name|gimp_rgb_composite
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|lightcheck
argument_list|,
name|GIMP_RGB_COMPOSITE_BEHIND
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|color
operator|.
name|a
operator|==
literal|0.0
condition|)
name|color
operator|=
name|darkcheck
expr_stmt|;
else|else
name|gimp_rgb_composite
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|darkcheck
argument_list|,
name|GIMP_RGB_COMPOSITE_BEHIND
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|GIMP_CAIRO_RGB24_SET_PIXEL
argument_list|(
operator|(
name|preview_rgb_data
operator|+
name|index
operator|)
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|index
operator|+=
literal|4
expr_stmt|;
name|imagex
operator|++
expr_stmt|;
block|}
else|else
block|{
name|preview_rgb_data
index|[
name|index
operator|++
index|]
operator|=
literal|200
expr_stmt|;
name|preview_rgb_data
index|[
name|index
operator|++
index|]
operator|=
literal|200
expr_stmt|;
name|preview_rgb_data
index|[
name|index
operator|++
index|]
operator|=
literal|200
expr_stmt|;
name|index
operator|++
expr_stmt|;
block|}
block|}
block|}
name|cairo_surface_mark_dirty
argument_list|(
name|preview_surface
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|compute_preview_rectangle (gint * xp,gint * yp,gint * wid,gint * heig)
name|compute_preview_rectangle
parameter_list|(
name|gint
modifier|*
name|xp
parameter_list|,
name|gint
modifier|*
name|yp
parameter_list|,
name|gint
modifier|*
name|wid
parameter_list|,
name|gint
modifier|*
name|heig
parameter_list|)
block|{
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
if|if
condition|(
name|width
operator|>=
name|height
condition|)
block|{
name|w
operator|=
operator|(
name|PREVIEW_WIDTH
operator|-
literal|50.0
operator|)
expr_stmt|;
name|h
operator|=
operator|(
name|gdouble
operator|)
name|height
operator|*
operator|(
name|w
operator|/
operator|(
name|gdouble
operator|)
name|width
operator|)
expr_stmt|;
name|x
operator|=
operator|(
name|PREVIEW_WIDTH
operator|-
name|w
operator|)
operator|/
literal|2.0
expr_stmt|;
name|y
operator|=
operator|(
name|PREVIEW_HEIGHT
operator|-
name|h
operator|)
operator|/
literal|2.0
expr_stmt|;
block|}
else|else
block|{
name|h
operator|=
operator|(
name|PREVIEW_HEIGHT
operator|-
literal|50.0
operator|)
expr_stmt|;
name|w
operator|=
operator|(
name|gdouble
operator|)
name|width
operator|*
operator|(
name|h
operator|/
operator|(
name|gdouble
operator|)
name|height
operator|)
expr_stmt|;
name|x
operator|=
operator|(
name|PREVIEW_WIDTH
operator|-
name|w
operator|)
operator|/
literal|2.0
expr_stmt|;
name|y
operator|=
operator|(
name|PREVIEW_HEIGHT
operator|-
name|h
operator|)
operator|/
literal|2.0
expr_stmt|;
block|}
operator|*
name|xp
operator|=
name|RINT
argument_list|(
name|x
argument_list|)
expr_stmt|;
operator|*
name|yp
operator|=
name|RINT
argument_list|(
name|y
argument_list|)
expr_stmt|;
operator|*
name|wid
operator|=
name|RINT
argument_list|(
name|w
argument_list|)
expr_stmt|;
operator|*
name|heig
operator|=
name|RINT
argument_list|(
name|h
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*************************************************/
end_comment

begin_comment
comment|/* Check if the given position is within the     */
end_comment

begin_comment
comment|/* light marker. Return TRUE if so, FALSE if not */
end_comment

begin_comment
comment|/*************************************************/
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|check_handle_hit (gint xpos,gint ypos)
name|check_handle_hit
parameter_list|(
name|gint
name|xpos
parameter_list|,
name|gint
name|ypos
parameter_list|)
block|{
name|gint
name|dx
decl_stmt|,
name|dy
decl_stmt|,
name|r
decl_stmt|;
name|gint
name|k
init|=
name|mapvals
operator|.
name|light_selected
decl_stmt|;
name|dx
operator|=
name|handle_xpos
operator|-
name|xpos
expr_stmt|;
name|dy
operator|=
name|handle_ypos
operator|-
name|ypos
expr_stmt|;
if|if
condition|(
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|type
operator|==
name|POINT_LIGHT
operator|||
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|type
operator|==
name|DIRECTIONAL_LIGHT
condition|)
block|{
name|r
operator|=
name|sqrt
argument_list|(
name|dx
operator|*
name|dx
operator|+
name|dy
operator|*
name|dy
argument_list|)
operator|+
literal|0.5
expr_stmt|;
if|if
condition|(
operator|(
name|gint
operator|)
name|r
operator|>
literal|7
condition|)
block|{
return|return
operator|(
name|FALSE
operator|)
return|;
block|}
else|else
block|{
return|return
operator|(
name|TRUE
operator|)
return|;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/****************************************/
end_comment

begin_comment
comment|/* Draw a light symbol                  */
end_comment

begin_comment
comment|/****************************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|draw_handles (void)
name|draw_handles
parameter_list|(
name|void
parameter_list|)
block|{
name|gdouble
name|dxpos
decl_stmt|,
name|dypos
decl_stmt|;
name|gint
name|startx
decl_stmt|,
name|starty
decl_stmt|,
name|pw
decl_stmt|,
name|ph
decl_stmt|;
name|GimpVector3
name|viewpoint
decl_stmt|;
name|GimpVector3
name|light_position
decl_stmt|;
name|gint
name|k
init|=
name|mapvals
operator|.
name|light_selected
decl_stmt|;
name|gfloat
name|length
decl_stmt|;
name|gfloat
name|delta_x
init|=
literal|0.0
decl_stmt|;
name|gfloat
name|delta_y
init|=
literal|0.0
decl_stmt|;
comment|/* calculate handle position */
name|compute_preview_rectangle
argument_list|(
operator|&
name|startx
argument_list|,
operator|&
name|starty
argument_list|,
operator|&
name|pw
argument_list|,
operator|&
name|ph
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|type
condition|)
block|{
case|case
name|NO_LIGHT
case|:
return|return;
case|case
name|POINT_LIGHT
case|:
case|case
name|SPOT_LIGHT
case|:
comment|/* swap z to reverse light position */
name|viewpoint
operator|=
name|mapvals
operator|.
name|viewpoint
expr_stmt|;
name|viewpoint
operator|.
name|z
operator|=
operator|-
name|viewpoint
operator|.
name|z
expr_stmt|;
name|light_position
operator|=
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|position
expr_stmt|;
name|gimp_vector_3d_to_2d
argument_list|(
name|startx
argument_list|,
name|starty
argument_list|,
name|pw
argument_list|,
name|ph
argument_list|,
operator|&
name|dxpos
argument_list|,
operator|&
name|dypos
argument_list|,
operator|&
name|viewpoint
argument_list|,
operator|&
name|light_position
argument_list|)
expr_stmt|;
name|handle_xpos
operator|=
call|(
name|gint
call|)
argument_list|(
name|dxpos
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|handle_ypos
operator|=
call|(
name|gint
call|)
argument_list|(
name|dypos
operator|+
literal|0.5
argument_list|)
expr_stmt|;
break|break;
case|case
name|DIRECTIONAL_LIGHT
case|:
name|light_position
operator|.
name|x
operator|=
name|light_position
operator|.
name|y
operator|=
literal|0.5
expr_stmt|;
name|light_position
operator|.
name|z
operator|=
literal|0
expr_stmt|;
name|viewpoint
operator|.
name|z
operator|=
operator|-
name|viewpoint
operator|.
name|z
expr_stmt|;
name|gimp_vector_3d_to_2d
argument_list|(
name|startx
argument_list|,
name|starty
argument_list|,
name|pw
argument_list|,
name|ph
argument_list|,
operator|&
name|dxpos
argument_list|,
operator|&
name|dypos
argument_list|,
operator|&
name|viewpoint
argument_list|,
operator|&
name|light_position
argument_list|)
expr_stmt|;
name|length
operator|=
name|PREVIEW_HEIGHT
operator|/
literal|4
expr_stmt|;
name|delta_x
operator|=
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|direction
operator|.
name|x
operator|*
name|length
expr_stmt|;
name|delta_y
operator|=
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|direction
operator|.
name|y
operator|*
name|length
expr_stmt|;
name|handle_xpos
operator|=
name|dxpos
operator|+
name|delta_x
expr_stmt|;
name|handle_ypos
operator|=
name|dypos
operator|+
name|delta_y
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|type
operator|!=
name|NO_LIGHT
condition|)
block|{
name|GdkColor
name|color
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|previewarea
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|color
operator|.
name|red
operator|=
literal|0x0
expr_stmt|;
name|color
operator|.
name|green
operator|=
literal|0x4000
expr_stmt|;
name|color
operator|.
name|blue
operator|=
literal|0xFFFF
expr_stmt|;
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
comment|/* draw circle at light position */
switch|switch
condition|(
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|type
condition|)
block|{
case|case
name|POINT_LIGHT
case|:
case|case
name|SPOT_LIGHT
case|:
name|cairo_arc
argument_list|(
name|cr
argument_list|,
name|handle_xpos
argument_list|,
name|handle_ypos
argument_list|,
name|LIGHT_SYMBOL_SIZE
operator|/
literal|2
argument_list|,
literal|0
argument_list|,
literal|2
operator|*
name|G_PI
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
break|break;
case|case
name|DIRECTIONAL_LIGHT
case|:
name|cairo_arc
argument_list|(
name|cr
argument_list|,
name|handle_xpos
argument_list|,
name|handle_ypos
argument_list|,
name|LIGHT_SYMBOL_SIZE
operator|/
literal|2
argument_list|,
literal|0
argument_list|,
literal|2
operator|*
name|G_PI
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|handle_xpos
argument_list|,
name|handle_ypos
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|startx
operator|+
name|pw
operator|/
literal|2
argument_list|,
name|starty
operator|+
name|ph
operator|/
literal|2
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
break|break;
case|case
name|NO_LIGHT
case|:
break|break;
block|}
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*************************************************/
end_comment

begin_comment
comment|/* Update light position given new screen coords */
end_comment

begin_comment
comment|/*************************************************/
end_comment

begin_function
name|void
DECL|function|update_light (gint xpos,gint ypos)
name|update_light
parameter_list|(
name|gint
name|xpos
parameter_list|,
name|gint
name|ypos
parameter_list|)
block|{
name|gint
name|startx
decl_stmt|,
name|starty
decl_stmt|,
name|pw
decl_stmt|,
name|ph
decl_stmt|;
name|GimpVector3
name|vp
decl_stmt|;
name|gint
name|k
init|=
name|mapvals
operator|.
name|light_selected
decl_stmt|;
name|compute_preview_rectangle
argument_list|(
operator|&
name|startx
argument_list|,
operator|&
name|starty
argument_list|,
operator|&
name|pw
argument_list|,
operator|&
name|ph
argument_list|)
expr_stmt|;
name|vp
operator|=
name|mapvals
operator|.
name|viewpoint
expr_stmt|;
name|vp
operator|.
name|z
operator|=
operator|-
name|vp
operator|.
name|z
expr_stmt|;
switch|switch
condition|(
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|type
condition|)
block|{
case|case
name|NO_LIGHT
case|:
break|break;
case|case
name|POINT_LIGHT
case|:
case|case
name|SPOT_LIGHT
case|:
name|gimp_vector_2d_to_3d
argument_list|(
name|startx
argument_list|,
name|starty
argument_list|,
name|pw
argument_list|,
name|ph
argument_list|,
name|xpos
argument_list|,
name|ypos
argument_list|,
operator|&
name|vp
argument_list|,
operator|&
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|position
argument_list|)
expr_stmt|;
break|break;
case|case
name|DIRECTIONAL_LIGHT
case|:
name|gimp_vector_2d_to_3d
argument_list|(
name|startx
argument_list|,
name|starty
argument_list|,
name|pw
argument_list|,
name|ph
argument_list|,
name|xpos
argument_list|,
name|ypos
argument_list|,
operator|&
name|vp
argument_list|,
operator|&
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|direction
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_comment
comment|/******************************************************************/
end_comment

begin_comment
comment|/* Draw preview image. if DoCompute is TRUE then recompute image. */
end_comment

begin_comment
comment|/******************************************************************/
end_comment

begin_function
name|void
DECL|function|preview_compute (void)
name|preview_compute
parameter_list|(
name|void
parameter_list|)
block|{
name|GdkDisplay
modifier|*
name|display
init|=
name|gtk_widget_get_display
argument_list|(
name|previewarea
argument_list|)
decl_stmt|;
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
name|gint
name|startx
decl_stmt|,
name|starty
decl_stmt|,
name|pw
decl_stmt|,
name|ph
decl_stmt|;
name|compute_preview_rectangle
argument_list|(
operator|&
name|startx
argument_list|,
operator|&
name|starty
argument_list|,
operator|&
name|pw
argument_list|,
operator|&
name|ph
argument_list|)
expr_stmt|;
name|cursor
operator|=
name|gdk_cursor_new_for_display
argument_list|(
name|display
argument_list|,
name|GDK_WATCH
argument_list|)
expr_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|previewarea
argument_list|)
argument_list|,
name|cursor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
name|compute_preview
argument_list|(
name|startx
argument_list|,
name|starty
argument_list|,
name|pw
argument_list|,
name|ph
argument_list|)
expr_stmt|;
name|cursor
operator|=
name|gdk_cursor_new_for_display
argument_list|(
name|display
argument_list|,
name|GDK_HAND2
argument_list|)
expr_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|previewarea
argument_list|)
argument_list|,
name|cursor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/******************************/
end_comment

begin_comment
comment|/* Preview area event handler */
end_comment

begin_comment
comment|/******************************/
end_comment

begin_function
name|gboolean
DECL|function|preview_events (GtkWidget * area,GdkEvent * event)
name|preview_events
parameter_list|(
name|GtkWidget
modifier|*
name|area
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
block|{
switch|switch
condition|(
name|event
operator|->
name|type
condition|)
block|{
case|case
name|GDK_ENTER_NOTIFY
case|:
break|break;
case|case
name|GDK_LEAVE_NOTIFY
case|:
break|break;
case|case
name|GDK_BUTTON_PRESS
case|:
name|light_hit
operator|=
name|check_handle_hit
argument_list|(
name|event
operator|->
name|button
operator|.
name|x
argument_list|,
name|event
operator|->
name|button
operator|.
name|y
argument_list|)
expr_stmt|;
name|left_button_pressed
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GDK_BUTTON_RELEASE
case|:
name|left_button_pressed
operator|=
name|FALSE
expr_stmt|;
break|break;
case|case
name|GDK_MOTION_NOTIFY
case|:
if|if
condition|(
name|left_button_pressed
operator|==
name|TRUE
operator|&&
name|light_hit
operator|==
name|TRUE
operator|&&
name|mapvals
operator|.
name|interactive_preview
operator|==
name|TRUE
condition|)
block|{
name|gtk_widget_queue_draw
argument_list|(
name|previewarea
argument_list|)
expr_stmt|;
name|interactive_preview_callback
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|update_light
argument_list|(
name|event
operator|->
name|motion
operator|.
name|x
argument_list|,
name|event
operator|->
name|motion
operator|.
name|y
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|preview_draw (GtkWidget * area,cairo_t * cr)
name|preview_draw
parameter_list|(
name|GtkWidget
modifier|*
name|area
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|cairo_set_source_surface
argument_list|(
name|cr
argument_list|,
name|preview_surface
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
comment|/* draw symbols if enabled in UI */
if|if
condition|(
name|mapvals
operator|.
name|interactive_preview
condition|)
block|{
name|draw_handles
argument_list|()
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|interactive_preview_callback (GtkWidget * widget)
name|interactive_preview_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
if|if
condition|(
name|preview_update_timer
operator|!=
literal|0
condition|)
block|{
name|g_source_remove
argument_list|(
name|preview_update_timer
argument_list|)
expr_stmt|;
block|}
comment|/* start new timer */
name|preview_update_timer
operator|=
name|g_timeout_add
argument_list|(
literal|100
argument_list|,
name|interactive_preview_timer_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|interactive_preview_timer_callback (gpointer data)
name|interactive_preview_timer_callback
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|gint
name|k
init|=
name|mapvals
operator|.
name|light_selected
decl_stmt|;
name|mapvals
operator|.
name|update_enabled
operator|=
name|FALSE
expr_stmt|;
comment|/* disable apply_settings() */
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spin_pos_x
argument_list|)
argument_list|,
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|position
operator|.
name|x
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spin_pos_y
argument_list|)
argument_list|,
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|position
operator|.
name|y
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spin_pos_z
argument_list|)
argument_list|,
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|position
operator|.
name|z
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spin_dir_x
argument_list|)
argument_list|,
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|direction
operator|.
name|x
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spin_dir_y
argument_list|)
argument_list|,
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|direction
operator|.
name|y
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spin_dir_z
argument_list|)
argument_list|,
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|direction
operator|.
name|z
argument_list|)
expr_stmt|;
name|mapvals
operator|.
name|update_enabled
operator|=
name|TRUE
expr_stmt|;
name|preview_compute
argument_list|()
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|previewarea
argument_list|)
expr_stmt|;
name|preview_update_timer
operator|=
literal|0
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit

