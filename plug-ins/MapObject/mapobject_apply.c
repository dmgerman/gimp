begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/******************************************************/
end_comment

begin_comment
comment|/* Apply mapping and shading on the whole input image */
end_comment

begin_comment
comment|/******************************************************/
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
file|"mapobject_main.h"
end_include

begin_include
include|#
directive|include
file|"mapobject_image.h"
end_include

begin_include
include|#
directive|include
file|"mapobject_shade.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/*************/
end_comment

begin_comment
comment|/* Main loop */
end_comment

begin_comment
comment|/*************/
end_comment

begin_decl_stmt
DECL|variable|imat
name|gdouble
name|imat
index|[
literal|4
index|]
index|[
literal|4
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rotmat
DECL|variable|a
DECL|variable|b
name|gfloat
name|rotmat
index|[
literal|16
index|]
decl_stmt|,
name|a
index|[
literal|16
index|]
decl_stmt|,
name|b
index|[
literal|16
index|]
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|init_compute (void)
name|init_compute
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
switch|switch
condition|(
name|mapvals
operator|.
name|maptype
condition|)
block|{
case|case
name|MAP_SPHERE
case|:
comment|/* Rotate the equator/northpole axis */
comment|/* ================================= */
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|firstaxis
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|secondaxis
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_vector3_rotate
argument_list|(
operator|&
name|mapvals
operator|.
name|firstaxis
argument_list|,
name|gimp_deg_to_rad
argument_list|(
name|mapvals
operator|.
name|alpha
argument_list|)
argument_list|,
name|gimp_deg_to_rad
argument_list|(
name|mapvals
operator|.
name|beta
argument_list|)
argument_list|,
name|gimp_deg_to_rad
argument_list|(
name|mapvals
operator|.
name|gamma
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_vector3_rotate
argument_list|(
operator|&
name|mapvals
operator|.
name|secondaxis
argument_list|,
name|gimp_deg_to_rad
argument_list|(
name|mapvals
operator|.
name|alpha
argument_list|)
argument_list|,
name|gimp_deg_to_rad
argument_list|(
name|mapvals
operator|.
name|beta
argument_list|)
argument_list|,
name|gimp_deg_to_rad
argument_list|(
name|mapvals
operator|.
name|gamma
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Compute the 2D bounding box of the sphere spanned by the axis */
comment|/* ============================================================= */
name|compute_bounding_box
argument_list|()
expr_stmt|;
name|get_ray_color
operator|=
name|get_ray_color_sphere
expr_stmt|;
break|break;
case|case
name|MAP_PLANE
case|:
comment|/* Rotate the plane axis */
comment|/* ===================== */
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|firstaxis
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|secondaxis
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|normal
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_vector3_rotate
argument_list|(
operator|&
name|mapvals
operator|.
name|firstaxis
argument_list|,
name|gimp_deg_to_rad
argument_list|(
name|mapvals
operator|.
name|alpha
argument_list|)
argument_list|,
name|gimp_deg_to_rad
argument_list|(
name|mapvals
operator|.
name|beta
argument_list|)
argument_list|,
name|gimp_deg_to_rad
argument_list|(
name|mapvals
operator|.
name|gamma
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_vector3_rotate
argument_list|(
operator|&
name|mapvals
operator|.
name|secondaxis
argument_list|,
name|gimp_deg_to_rad
argument_list|(
name|mapvals
operator|.
name|alpha
argument_list|)
argument_list|,
name|gimp_deg_to_rad
argument_list|(
name|mapvals
operator|.
name|beta
argument_list|)
argument_list|,
name|gimp_deg_to_rad
argument_list|(
name|mapvals
operator|.
name|gamma
argument_list|)
argument_list|)
expr_stmt|;
name|mapvals
operator|.
name|normal
operator|=
name|gimp_vector3_cross_product
argument_list|(
operator|&
name|mapvals
operator|.
name|firstaxis
argument_list|,
operator|&
name|mapvals
operator|.
name|secondaxis
argument_list|)
expr_stmt|;
if|if
condition|(
name|mapvals
operator|.
name|normal
operator|.
name|z
operator|<
literal|0.0
condition|)
name|gimp_vector3_mul
argument_list|(
operator|&
name|mapvals
operator|.
name|normal
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
comment|/* Initialize intersection matrix */
comment|/* ============================== */
name|imat
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|=
operator|-
name|mapvals
operator|.
name|firstaxis
operator|.
name|x
expr_stmt|;
name|imat
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|=
operator|-
name|mapvals
operator|.
name|firstaxis
operator|.
name|y
expr_stmt|;
name|imat
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|=
operator|-
name|mapvals
operator|.
name|firstaxis
operator|.
name|z
expr_stmt|;
name|imat
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|=
operator|-
name|mapvals
operator|.
name|secondaxis
operator|.
name|x
expr_stmt|;
name|imat
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|=
operator|-
name|mapvals
operator|.
name|secondaxis
operator|.
name|y
expr_stmt|;
name|imat
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|=
operator|-
name|mapvals
operator|.
name|secondaxis
operator|.
name|z
expr_stmt|;
name|imat
index|[
literal|0
index|]
index|[
literal|3
index|]
operator|=
name|mapvals
operator|.
name|position
operator|.
name|x
operator|-
name|mapvals
operator|.
name|viewpoint
operator|.
name|x
expr_stmt|;
name|imat
index|[
literal|1
index|]
index|[
literal|3
index|]
operator|=
name|mapvals
operator|.
name|position
operator|.
name|y
operator|-
name|mapvals
operator|.
name|viewpoint
operator|.
name|y
expr_stmt|;
name|imat
index|[
literal|2
index|]
index|[
literal|3
index|]
operator|=
name|mapvals
operator|.
name|position
operator|.
name|z
operator|-
name|mapvals
operator|.
name|viewpoint
operator|.
name|z
expr_stmt|;
name|get_ray_color
operator|=
name|get_ray_color_plane
expr_stmt|;
break|break;
case|case
name|MAP_BOX
case|:
name|get_ray_color
operator|=
name|get_ray_color_box
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|firstaxis
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|secondaxis
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|normal
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|ident_mat
argument_list|(
name|rotmat
argument_list|)
expr_stmt|;
name|rotatemat
argument_list|(
name|mapvals
operator|.
name|alpha
argument_list|,
operator|&
name|mapvals
operator|.
name|firstaxis
argument_list|,
name|a
argument_list|)
expr_stmt|;
name|matmul
argument_list|(
name|a
argument_list|,
name|rotmat
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|rotmat
argument_list|,
name|b
argument_list|,
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
operator|*
literal|16
argument_list|)
expr_stmt|;
name|rotatemat
argument_list|(
name|mapvals
operator|.
name|beta
argument_list|,
operator|&
name|mapvals
operator|.
name|secondaxis
argument_list|,
name|a
argument_list|)
expr_stmt|;
name|matmul
argument_list|(
name|a
argument_list|,
name|rotmat
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|rotmat
argument_list|,
name|b
argument_list|,
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
operator|*
literal|16
argument_list|)
expr_stmt|;
name|rotatemat
argument_list|(
name|mapvals
operator|.
name|gamma
argument_list|,
operator|&
name|mapvals
operator|.
name|normal
argument_list|,
name|a
argument_list|)
expr_stmt|;
name|matmul
argument_list|(
name|a
argument_list|,
name|rotmat
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|rotmat
argument_list|,
name|b
argument_list|,
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
operator|*
literal|16
argument_list|)
expr_stmt|;
comment|/* Set up pixel regions for the box face images */
comment|/* ============================================ */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|6
condition|;
name|i
operator|++
control|)
block|{
name|box_drawables
index|[
name|i
index|]
operator|=
name|gimp_drawable_get
argument_list|(
name|mapvals
operator|.
name|boxmap_id
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|box_regions
index|[
name|i
index|]
argument_list|,
name|box_drawables
index|[
name|i
index|]
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|box_drawables
index|[
name|i
index|]
operator|->
name|width
argument_list|,
name|box_drawables
index|[
name|i
index|]
operator|->
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|MAP_CYLINDER
case|:
name|get_ray_color
operator|=
name|get_ray_color_cylinder
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|firstaxis
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|secondaxis
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|normal
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|ident_mat
argument_list|(
name|rotmat
argument_list|)
expr_stmt|;
name|rotatemat
argument_list|(
name|mapvals
operator|.
name|alpha
argument_list|,
operator|&
name|mapvals
operator|.
name|firstaxis
argument_list|,
name|a
argument_list|)
expr_stmt|;
name|matmul
argument_list|(
name|a
argument_list|,
name|rotmat
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|rotmat
argument_list|,
name|b
argument_list|,
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
operator|*
literal|16
argument_list|)
expr_stmt|;
name|rotatemat
argument_list|(
name|mapvals
operator|.
name|beta
argument_list|,
operator|&
name|mapvals
operator|.
name|secondaxis
argument_list|,
name|a
argument_list|)
expr_stmt|;
name|matmul
argument_list|(
name|a
argument_list|,
name|rotmat
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|rotmat
argument_list|,
name|b
argument_list|,
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
operator|*
literal|16
argument_list|)
expr_stmt|;
name|rotatemat
argument_list|(
name|mapvals
operator|.
name|gamma
argument_list|,
operator|&
name|mapvals
operator|.
name|normal
argument_list|,
name|a
argument_list|)
expr_stmt|;
name|matmul
argument_list|(
name|a
argument_list|,
name|rotmat
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|rotmat
argument_list|,
name|b
argument_list|,
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
operator|*
literal|16
argument_list|)
expr_stmt|;
comment|/* Set up pixel regions for the cylinder cap images */
comment|/* ================================================ */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|2
condition|;
name|i
operator|++
control|)
block|{
name|cylinder_drawables
index|[
name|i
index|]
operator|=
name|gimp_drawable_get
argument_list|(
name|mapvals
operator|.
name|cylindermap_id
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|cylinder_regions
index|[
name|i
index|]
argument_list|,
name|cylinder_drawables
index|[
name|i
index|]
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|cylinder_drawables
index|[
name|i
index|]
operator|->
name|width
argument_list|,
name|cylinder_drawables
index|[
name|i
index|]
operator|->
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
name|max_depth
operator|=
operator|(
name|gint
operator|)
name|mapvals
operator|.
name|maxdepth
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|render (gdouble x,gdouble y,GimpRGB * col,gpointer data)
name|render
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GimpRGB
modifier|*
name|col
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpVector3
name|pos
decl_stmt|;
name|pos
operator|.
name|x
operator|=
name|x
operator|/
operator|(
name|gdouble
operator|)
name|width
expr_stmt|;
name|pos
operator|.
name|y
operator|=
name|y
operator|/
operator|(
name|gdouble
operator|)
name|height
expr_stmt|;
name|pos
operator|.
name|z
operator|=
literal|0.0
expr_stmt|;
operator|*
name|col
operator|=
name|get_ray_color
argument_list|(
operator|&
name|pos
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|show_progress (gint min,gint max,gint curr,gpointer data)
name|show_progress
parameter_list|(
name|gint
name|min
parameter_list|,
name|gint
name|max
parameter_list|,
name|gint
name|curr
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|curr
operator|/
operator|(
name|gdouble
operator|)
name|max
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**************************************************/
end_comment

begin_comment
comment|/* Performs map-to-sphere on the whole input image */
end_comment

begin_comment
comment|/* and updates or creates a new GIMP image.       */
end_comment

begin_comment
comment|/**************************************************/
end_comment

begin_function
name|void
DECL|function|compute_image (void)
name|compute_image
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|xcount
decl_stmt|,
name|ycount
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|glong
name|progress_counter
init|=
literal|0
decl_stmt|;
name|GimpVector3
name|p
decl_stmt|;
name|gint32
name|new_image_id
init|=
operator|-
literal|1
decl_stmt|;
name|gint32
name|new_layer_id
init|=
operator|-
literal|1
decl_stmt|;
name|init_compute
argument_list|()
expr_stmt|;
if|if
condition|(
name|mapvals
operator|.
name|create_new_image
operator|==
name|TRUE
operator|||
operator|(
name|mapvals
operator|.
name|transparent_background
operator|==
name|TRUE
operator|&&
name|input_drawable
operator|->
name|bpp
operator|!=
literal|4
operator|)
condition|)
block|{
comment|/* Create a new image */
comment|/* ================== */
name|new_image_id
operator|=
name|gimp_image_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_RGB
argument_list|)
expr_stmt|;
if|if
condition|(
name|mapvals
operator|.
name|transparent_background
operator|==
name|TRUE
condition|)
block|{
comment|/* Add a layer with an alpha channel */
comment|/* ================================= */
name|new_layer_id
operator|=
name|gimp_layer_new
argument_list|(
name|new_image_id
argument_list|,
literal|"Background"
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_RGBA_IMAGE
argument_list|,
literal|100.0
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Create a "normal" layer */
comment|/* ======================= */
name|new_layer_id
operator|=
name|gimp_layer_new
argument_list|(
name|new_image_id
argument_list|,
literal|"Background"
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_RGB_IMAGE
argument_list|,
literal|100.0
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
block|}
name|gimp_image_add_layer
argument_list|(
name|new_image_id
argument_list|,
name|new_layer_id
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|output_drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|new_layer_id
argument_list|)
expr_stmt|;
block|}
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dest_region
argument_list|,
name|output_drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|mapvals
operator|.
name|maptype
condition|)
block|{
case|case
name|MAP_PLANE
case|:
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Map to plane"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|MAP_SPHERE
case|:
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Map to sphere"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|MAP_BOX
case|:
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Map to box"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|MAP_CYLINDER
case|:
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Map to cylinder"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|mapvals
operator|.
name|antialiasing
operator|==
name|FALSE
condition|)
block|{
for|for
control|(
name|ycount
operator|=
literal|0
init|;
name|ycount
operator|<
name|height
condition|;
name|ycount
operator|++
control|)
block|{
for|for
control|(
name|xcount
operator|=
literal|0
init|;
name|xcount
operator|<
name|width
condition|;
name|xcount
operator|++
control|)
block|{
name|p
operator|=
name|int_to_pos
argument_list|(
name|xcount
argument_list|,
name|ycount
argument_list|)
expr_stmt|;
name|color
operator|=
call|(
modifier|*
name|get_ray_color
call|)
argument_list|(
operator|&
name|p
argument_list|)
expr_stmt|;
name|poke
argument_list|(
name|xcount
argument_list|,
name|ycount
argument_list|,
operator|&
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|progress_counter
operator|++
operator|%
name|width
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|progress_counter
operator|/
operator|(
name|gdouble
operator|)
name|maxcounter
argument_list|)
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|gimp_adaptive_supersample_area
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
operator|-
literal|1
argument_list|,
name|height
operator|-
literal|1
argument_list|,
name|max_depth
argument_list|,
name|mapvals
operator|.
name|pixeltreshold
argument_list|,
name|render
argument_list|,
name|NULL
argument_list|,
name|poke
argument_list|,
name|NULL
argument_list|,
name|show_progress
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
comment|/* Update the region */
comment|/* ================= */
name|gimp_drawable_flush
argument_list|(
name|output_drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|output_drawable
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|output_drawable
operator|->
name|drawable_id
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_image_id
operator|!=
operator|-
literal|1
condition|)
block|{
name|gimp_display_new
argument_list|(
name|new_image_id
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|output_drawable
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

