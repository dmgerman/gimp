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
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdkimage.h>
end_include

begin_include
include|#
directive|include
file|<gck/gck.h>
end_include

begin_include
include|#
directive|include
file|<libgimpmath/gimpvector.h>
end_include

begin_include
include|#
directive|include
file|"lighting_main.h"
end_include

begin_include
include|#
directive|include
file|"lighting_ui.h"
end_include

begin_include
include|#
directive|include
file|"lighting_image.h"
end_include

begin_include
include|#
directive|include
file|"lighting_apply.h"
end_include

begin_include
include|#
directive|include
file|"lighting_shade.h"
end_include

begin_include
include|#
directive|include
file|"lighting_preview.h"
end_include

begin_define
DECL|macro|LIGHT_SYMBOL_SIZE
define|#
directive|define
name|LIGHT_SYMBOL_SIZE
value|8
end_define

begin_decl_stmt
DECL|variable|lightx
DECL|variable|lighty
name|gint
name|lightx
decl_stmt|,
name|lighty
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|backbuf
name|BackBuffer
name|backbuf
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
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
name|guint
name|light_hit
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|left_button_pressed
name|guint
name|left_button_pressed
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|spin_pos_x
name|GtkWidget
modifier|*
name|spin_pos_x
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|spin_pos_y
name|GtkWidget
modifier|*
name|spin_pos_y
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|spin_pos_z
name|GtkWidget
modifier|*
name|spin_pos_z
init|=
name|NULL
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
name|void
name|interactive_preview_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|interactive_preview_timer_callback
parameter_list|(
name|void
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
name|init_compute
argument_list|()
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
name|preview_rgb_data
operator|+
name|index
argument_list|,
name|preview_rgb_data
operator|+
name|index
operator|+
literal|1
argument_list|,
name|preview_rgb_data
operator|+
name|index
operator|+
literal|2
argument_list|)
expr_stmt|;
name|index
operator|+=
literal|3
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
block|}
block|}
block|}
name|gck_rgb_to_gdkimage
argument_list|(
name|visinfo
argument_list|,
name|preview_rgb_data
argument_list|,
name|image
argument_list|,
name|PREVIEW_WIDTH
argument_list|,
name|PREVIEW_HEIGHT
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
name|gboolean
DECL|function|check_marker_hit (gint xpos,gint ypos)
name|check_marker_hit
parameter_list|(
name|gint
name|xpos
parameter_list|,
name|gint
name|ypos
parameter_list|)
block|{
name|gdouble
name|dxpos
decl_stmt|,
name|dypos
decl_stmt|;
name|gint
name|lightx
decl_stmt|,
name|lighty
decl_stmt|;
name|gdouble
name|dx
decl_stmt|,
name|dy
decl_stmt|,
name|r
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
name|mapvals
operator|.
name|lightsource
operator|.
name|position
argument_list|)
expr_stmt|;
name|lightx
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
name|lighty
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
name|dx
operator|=
name|lightx
operator|-
name|xpos
expr_stmt|;
name|dy
operator|=
name|lighty
operator|-
name|ypos
expr_stmt|;
if|if
condition|(
name|mapvals
operator|.
name|lightsource
operator|.
name|type
operator|==
name|POINT_LIGHT
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
DECL|function|draw_lights ()
name|draw_lights
parameter_list|()
block|{
name|gdouble
name|dxpos
decl_stmt|,
name|dypos
decl_stmt|;
name|gint
name|xpos
decl_stmt|,
name|ypos
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
name|gfloat
name|length
decl_stmt|;
name|gfloat
name|delta_x
init|=
literal|0.0
decl_stmt|,
name|delta_y
init|=
literal|0.0
decl_stmt|;
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
if|if
condition|(
name|mapvals
operator|.
name|lightsource
operator|.
name|type
operator|==
name|DIRECTIONAL_LIGHT
condition|)
block|{
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
literal|0.0
expr_stmt|;
block|}
else|else
block|{
name|light_position
operator|=
name|mapvals
operator|.
name|lightsource
operator|.
name|position
expr_stmt|;
block|}
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
name|xpos
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
name|ypos
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
name|gdk_gc_set_function
argument_list|(
name|gc
argument_list|,
name|GDK_COPY
argument_list|)
expr_stmt|;
if|if
condition|(
name|mapvals
operator|.
name|lightsource
operator|.
name|type
operator|!=
name|NO_LIGHT
condition|)
block|{
comment|/* Restore background if it has been saved */
comment|/* ======================================= */
if|if
condition|(
name|backbuf
operator|.
name|image
operator|!=
name|NULL
condition|)
block|{
name|gdk_gc_set_function
argument_list|(
name|gc
argument_list|,
name|GDK_COPY
argument_list|)
expr_stmt|;
name|gdk_draw_image
argument_list|(
name|previewarea
operator|->
name|window
argument_list|,
name|gc
argument_list|,
name|backbuf
operator|.
name|image
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|backbuf
operator|.
name|x
argument_list|,
name|backbuf
operator|.
name|y
argument_list|,
name|backbuf
operator|.
name|w
argument_list|,
name|backbuf
operator|.
name|h
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|backbuf
operator|.
name|image
argument_list|)
expr_stmt|;
name|backbuf
operator|.
name|image
operator|=
name|NULL
expr_stmt|;
block|}
comment|/* calculate symbol size */
switch|switch
condition|(
name|mapvals
operator|.
name|lightsource
operator|.
name|type
condition|)
block|{
case|case
name|POINT_LIGHT
case|:
name|backbuf
operator|.
name|x
operator|=
name|xpos
operator|-
name|LIGHT_SYMBOL_SIZE
operator|/
literal|2
expr_stmt|;
name|backbuf
operator|.
name|y
operator|=
name|ypos
operator|-
name|LIGHT_SYMBOL_SIZE
operator|/
literal|2
expr_stmt|;
name|backbuf
operator|.
name|w
operator|=
name|LIGHT_SYMBOL_SIZE
expr_stmt|;
name|backbuf
operator|.
name|h
operator|=
name|LIGHT_SYMBOL_SIZE
expr_stmt|;
break|break;
case|case
name|DIRECTIONAL_LIGHT
case|:
name|length
operator|=
name|sqrt
argument_list|(
operator|(
name|mapvals
operator|.
name|lightsource
operator|.
name|direction
operator|.
name|x
operator|*
name|mapvals
operator|.
name|lightsource
operator|.
name|direction
operator|.
name|x
operator|)
operator|+
operator|(
name|mapvals
operator|.
name|lightsource
operator|.
name|direction
operator|.
name|y
operator|*
name|mapvals
operator|.
name|lightsource
operator|.
name|direction
operator|.
name|y
operator|)
argument_list|)
expr_stmt|;
name|length
operator|=
operator|(
literal|1.0
operator|/
name|length
operator|)
operator|*
operator|(
name|PREVIEW_HEIGHT
operator|/
literal|4.0
operator|)
expr_stmt|;
name|delta_x
operator|=
name|mapvals
operator|.
name|lightsource
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
operator|.
name|direction
operator|.
name|y
operator|*
name|length
expr_stmt|;
name|backbuf
operator|.
name|x
operator|=
name|xpos
operator|-
name|fabs
argument_list|(
name|delta_x
argument_list|)
expr_stmt|;
name|backbuf
operator|.
name|y
operator|=
name|ypos
operator|-
name|fabs
argument_list|(
name|delta_y
argument_list|)
expr_stmt|;
name|backbuf
operator|.
name|w
operator|=
name|fabs
argument_list|(
name|delta_x
operator|*
literal|2.0
argument_list|)
expr_stmt|;
name|backbuf
operator|.
name|h
operator|=
name|fabs
argument_list|(
name|delta_y
operator|*
literal|2.0
argument_list|)
expr_stmt|;
break|break;
case|case
name|SPOT_LIGHT
case|:
case|case
name|NO_LIGHT
case|:
name|backbuf
operator|.
name|x
operator|=
name|xpos
operator|-
name|LIGHT_SYMBOL_SIZE
operator|/
literal|2
expr_stmt|;
name|backbuf
operator|.
name|y
operator|=
name|ypos
operator|-
name|LIGHT_SYMBOL_SIZE
operator|/
literal|2
expr_stmt|;
name|backbuf
operator|.
name|w
operator|=
name|LIGHT_SYMBOL_SIZE
expr_stmt|;
name|backbuf
operator|.
name|h
operator|=
name|LIGHT_SYMBOL_SIZE
expr_stmt|;
break|break;
block|}
comment|/* Save background */
comment|/* =============== */
if|if
condition|(
operator|(
name|backbuf
operator|.
name|x
operator|>=
literal|0
operator|)
operator|&&
operator|(
name|backbuf
operator|.
name|x
operator|<=
name|PREVIEW_WIDTH
operator|)
operator|&&
operator|(
name|backbuf
operator|.
name|y
operator|>=
literal|0
operator|)
operator|&&
operator|(
name|backbuf
operator|.
name|y
operator|<=
name|PREVIEW_HEIGHT
operator|)
condition|)
block|{
comment|/* clip coordinates to preview widget sizes */
if|if
condition|(
operator|(
name|backbuf
operator|.
name|x
operator|+
name|backbuf
operator|.
name|w
operator|)
operator|>
name|PREVIEW_WIDTH
condition|)
name|backbuf
operator|.
name|w
operator|=
operator|(
name|PREVIEW_WIDTH
operator|-
name|backbuf
operator|.
name|x
operator|)
expr_stmt|;
if|if
condition|(
operator|(
name|backbuf
operator|.
name|y
operator|+
name|backbuf
operator|.
name|h
operator|)
operator|>
name|PREVIEW_HEIGHT
condition|)
name|backbuf
operator|.
name|h
operator|=
operator|(
name|PREVIEW_HEIGHT
operator|-
name|backbuf
operator|.
name|y
operator|)
expr_stmt|;
name|backbuf
operator|.
name|image
operator|=
name|gdk_drawable_get_image
argument_list|(
name|previewarea
operator|->
name|window
argument_list|,
name|backbuf
operator|.
name|x
argument_list|,
name|backbuf
operator|.
name|y
argument_list|,
name|backbuf
operator|.
name|w
argument_list|,
name|backbuf
operator|.
name|h
argument_list|)
expr_stmt|;
block|}
name|gck_gc_set_background
argument_list|(
name|visinfo
argument_list|,
name|gc
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gck_gc_set_foreground
argument_list|(
name|visinfo
argument_list|,
name|gc
argument_list|,
literal|0
argument_list|,
literal|50
argument_list|,
literal|255
argument_list|)
expr_stmt|;
comment|/* draw circle at light position */
switch|switch
condition|(
name|mapvals
operator|.
name|lightsource
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
name|gdk_draw_arc
argument_list|(
name|previewarea
operator|->
name|window
argument_list|,
name|gc
argument_list|,
name|TRUE
argument_list|,
name|xpos
operator|-
name|LIGHT_SYMBOL_SIZE
operator|/
literal|2
argument_list|,
name|ypos
operator|-
name|LIGHT_SYMBOL_SIZE
operator|/
literal|2
argument_list|,
name|LIGHT_SYMBOL_SIZE
argument_list|,
name|LIGHT_SYMBOL_SIZE
argument_list|,
literal|0
argument_list|,
literal|360
operator|*
literal|64
argument_list|)
expr_stmt|;
break|break;
case|case
name|DIRECTIONAL_LIGHT
case|:
name|gdk_draw_arc
argument_list|(
name|previewarea
operator|->
name|window
argument_list|,
name|gc
argument_list|,
name|TRUE
argument_list|,
name|xpos
operator|-
name|LIGHT_SYMBOL_SIZE
operator|/
literal|2
argument_list|,
name|ypos
operator|-
name|LIGHT_SYMBOL_SIZE
operator|/
literal|2
argument_list|,
name|LIGHT_SYMBOL_SIZE
argument_list|,
name|LIGHT_SYMBOL_SIZE
argument_list|,
literal|0
argument_list|,
literal|360
operator|*
literal|64
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|previewarea
operator|->
name|window
argument_list|,
name|gc
argument_list|,
name|xpos
argument_list|,
name|ypos
argument_list|,
name|xpos
operator|+
name|delta_x
argument_list|,
name|ypos
operator|+
name|delta_y
argument_list|)
expr_stmt|;
break|break;
case|case
name|NO_LIGHT
case|:
break|break;
block|}
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
operator|.
name|position
argument_list|)
expr_stmt|;
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
DECL|function|draw_preview_image (gint recompute)
name|draw_preview_image
parameter_list|(
name|gint
name|recompute
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
name|gck_gc_set_foreground
argument_list|(
name|visinfo
argument_list|,
name|gc
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|gck_gc_set_background
argument_list|(
name|visinfo
argument_list|,
name|gc
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gdk_gc_set_function
argument_list|(
name|gc
argument_list|,
name|GDK_COPY
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|recompute
operator|==
name|TRUE
condition|)
block|{
name|GdkCursor
modifier|*
name|newcursor
decl_stmt|;
name|newcursor
operator|=
name|gdk_cursor_new
argument_list|(
name|GDK_WATCH
argument_list|)
expr_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|previewarea
operator|->
name|window
argument_list|,
name|newcursor
argument_list|)
expr_stmt|;
name|gdk_cursor_unref
argument_list|(
name|newcursor
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
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
name|newcursor
operator|=
name|gdk_cursor_new
argument_list|(
name|GDK_HAND2
argument_list|)
expr_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|previewarea
operator|->
name|window
argument_list|,
name|newcursor
argument_list|)
expr_stmt|;
name|gdk_cursor_unref
argument_list|(
name|newcursor
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
comment|/* if we recompute, clear backbuf, so we don't  		 * restore the wrong bitmap */
if|if
condition|(
name|backbuf
operator|.
name|image
operator|!=
name|NULL
condition|)
block|{
name|g_object_unref
argument_list|(
name|backbuf
operator|.
name|image
argument_list|)
expr_stmt|;
name|backbuf
operator|.
name|image
operator|=
name|NULL
expr_stmt|;
block|}
block|}
name|gdk_draw_image
argument_list|(
name|previewarea
operator|->
name|window
argument_list|,
name|gc
argument_list|,
name|image
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|PREVIEW_WIDTH
argument_list|,
name|PREVIEW_HEIGHT
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
name|draw_lights
argument_list|()
expr_stmt|;
block|}
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
name|gint
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
name|GDK_EXPOSE
case|:
comment|/* Is this the first exposure? */
comment|/* =========================== */
if|if
condition|(
operator|!
name|gc
condition|)
block|{
name|gc
operator|=
name|gdk_gc_new
argument_list|(
name|area
operator|->
name|window
argument_list|)
expr_stmt|;
name|draw_preview_image
argument_list|(
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
name|draw_preview_image
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
break|break;
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
name|check_marker_hit
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
condition|)
block|{
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
operator|.
name|position
operator|.
name|z
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
specifier|static
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
name|gtk_timeout_remove
argument_list|(
name|preview_update_timer
argument_list|)
expr_stmt|;
block|}
comment|/* start new timer */
name|preview_update_timer
operator|=
name|gtk_timeout_add
argument_list|(
literal|100
argument_list|,
operator|(
name|GtkFunction
operator|)
name|interactive_preview_timer_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|interactive_preview_timer_callback (void)
name|interactive_preview_timer_callback
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_timeout_remove
argument_list|(
name|preview_update_timer
argument_list|)
expr_stmt|;
if|if
condition|(
name|mapvals
operator|.
name|interactive_preview
condition|)
block|{
name|draw_preview_image
argument_list|(
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|draw_preview_image
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|update_preview_image (void)
name|void
name|update_preview_image
parameter_list|(
name|void
parameter_list|)
block|{
name|interactive_preview_callback
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

