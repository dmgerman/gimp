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
file|"lighting_shade.h"
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
DECL|variable|ray_func
name|get_ray_func
name|ray_func
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|init_compute (void)
name|void
name|init_compute
parameter_list|(
name|void
parameter_list|)
block|{ }
end_function

begin_function
DECL|function|render (gdouble x,gdouble y,GckRGB * col)
name|void
name|render
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GckRGB
modifier|*
name|col
parameter_list|)
block|{
name|GimpVector3
name|pos
decl_stmt|;
name|pos
operator|=
name|int_to_pos
argument_list|(
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
operator|*
name|col
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
block|}
end_function

begin_function
DECL|function|show_progress (gint min,gint max,gint curr)
name|void
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

begin_function
DECL|function|compute_image (void)
name|void
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
name|GckRGB
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
decl_stmt|,
name|new_layer_id
init|=
operator|-
literal|1
decl_stmt|,
name|index
decl_stmt|;
name|guchar
modifier|*
name|row
init|=
name|NULL
decl_stmt|,
name|obpp
decl_stmt|;
name|gint
name|has_alpha
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
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|input_drawable
operator|->
name|id
argument_list|)
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
name|RGB
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
name|RGBA_IMAGE
argument_list|,
literal|100.0
argument_list|,
name|NORMAL_MODE
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
name|RGB_IMAGE
argument_list|,
literal|100.0
argument_list|,
name|NORMAL_MODE
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
name|precompute_init
argument_list|(
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
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
name|ray_func
operator|=
name|get_ray_color
expr_stmt|;
else|else
block|{
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
name|ray_func
operator|=
name|get_ray_color_ref
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
name|obpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|output_drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|output_drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|row
operator|=
operator|(
name|guchar
operator|*
operator|)
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|guchar
argument_list|)
operator|*
call|(
name|size_t
call|)
argument_list|(
name|obpp
argument_list|)
operator|*
call|(
name|size_t
call|)
argument_list|(
name|width
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
literal|"Lighting Effects"
argument_list|)
expr_stmt|;
comment|/*  if (mapvals.antialiasing==FALSE)     { */
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
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|dest_region
argument_list|,
name|row
argument_list|,
literal|0
argument_list|,
name|ycount
argument_list|,
name|width
argument_list|)
expr_stmt|;
block|}
comment|/*    }   else     gck_adaptive_supersample_area(0,0,width-1,height-1,(gint)mapvals.max_depth,       mapvals.pixel_treshold,render,poke,show_progress); */
if|if
condition|(
name|row
operator|!=
name|NULL
condition|)
name|free
argument_list|(
name|row
argument_list|)
expr_stmt|;
comment|/* Update image */
comment|/* ============ */
name|gimp_drawable_flush
argument_list|(
name|output_drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|output_drawable
operator|->
name|id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|output_drawable
operator|->
name|id
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

