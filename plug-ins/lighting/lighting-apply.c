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
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"lighting-main.h"
end_include

begin_include
include|#
directive|include
file|"lighting-image.h"
end_include

begin_include
include|#
directive|include
file|"lighting-shade.h"
end_include

begin_include
include|#
directive|include
file|"lighting-apply.h"
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
name|GimpImage
modifier|*
name|new_image
init|=
name|NULL
decl_stmt|;
name|GimpLayer
modifier|*
name|new_layer
init|=
name|NULL
decl_stmt|;
name|gint32
name|index
decl_stmt|;
name|guchar
modifier|*
name|row
init|=
name|NULL
decl_stmt|;
name|guchar
name|obpp
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|get_ray_func
name|ray_func
decl_stmt|;
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
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|input_drawable
argument_list|)
operator|)
condition|)
block|{
comment|/* Create a new image */
comment|/* ================== */
name|new_image
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
name|new_layer
operator|=
name|gimp_layer_new
argument_list|(
name|new_image
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
name|gimp_image_get_default_new_layer_mode
argument_list|(
name|new_image
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Create a "normal" layer */
comment|/* ======================= */
name|new_layer
operator|=
name|gimp_layer_new
argument_list|(
name|new_image
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
name|gimp_image_get_default_new_layer_mode
argument_list|(
name|new_image
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_image_insert_layer
argument_list|(
name|new_image
argument_list|,
name|new_layer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|output_drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|new_layer
argument_list|)
expr_stmt|;
block|}
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
name|bumpmap_setup
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|gimp_item_get_by_id
argument_list|(
name|mapvals
operator|.
name|bumpmap_id
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|precompute_init
argument_list|(
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|mapvals
operator|.
name|env_mapped
operator|||
name|mapvals
operator|.
name|envmap_id
operator|==
operator|-
literal|1
condition|)
block|{
name|ray_func
operator|=
name|get_ray_color
expr_stmt|;
block|}
else|else
block|{
name|envmap_setup
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|gimp_item_get_by_id
argument_list|(
name|mapvals
operator|.
name|envmap_id
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|ray_func
operator|=
name|get_ray_color_ref
expr_stmt|;
block|}
name|dest_buffer
operator|=
name|gimp_drawable_get_shadow_buffer
argument_list|(
name|output_drawable
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|output_drawable
argument_list|)
expr_stmt|;
comment|/* FIXME */
name|obpp
operator|=
name|has_alpha
condition|?
literal|4
else|:
literal|3
expr_stmt|;
comment|//gimp_drawable_bpp (output_drawable);
name|row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|obpp
operator|*
name|width
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Lighting Effects"
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Init the first row */
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
name|height
operator|>=
literal|2
condition|)
name|interpol_row
argument_list|(
literal|0
argument_list|,
name|width
argument_list|,
literal|0
argument_list|)
expr_stmt|;
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
name|precompute_normals
argument_list|(
literal|0
argument_list|,
name|width
argument_list|,
name|ycount
argument_list|)
expr_stmt|;
name|index
operator|=
literal|0
expr_stmt|;
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
name|ray_func
call|)
argument_list|(
operator|&
name|p
argument_list|)
expr_stmt|;
name|row
index|[
name|index
operator|++
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|color
operator|.
name|r
operator|*
literal|255.0
argument_list|)
expr_stmt|;
name|row
index|[
name|index
operator|++
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|color
operator|.
name|g
operator|*
literal|255.0
argument_list|)
expr_stmt|;
name|row
index|[
name|index
operator|++
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|color
operator|.
name|b
operator|*
literal|255.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|row
index|[
name|index
operator|++
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|color
operator|.
name|a
operator|*
literal|255.0
argument_list|)
expr_stmt|;
name|progress_counter
operator|++
expr_stmt|;
block|}
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
name|gegl_buffer_set
argument_list|(
name|dest_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
name|ycount
argument_list|,
name|width
argument_list|,
literal|1
argument_list|)
argument_list|,
literal|0
argument_list|,
name|has_alpha
condition|?
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
else|:
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
argument_list|,
name|row
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
block|}
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|row
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|output_drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|output_drawable
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
name|new_image
condition|)
block|{
name|gimp_display_new
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
block|}
end_function

end_unit

