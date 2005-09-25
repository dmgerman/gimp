begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*********************************************************/
end_comment

begin_comment
comment|/* Image manipulation routines. Calls mapobject_shade.c  */
end_comment

begin_comment
comment|/* functions to compute the shading of the image at each */
end_comment

begin_comment
comment|/* pixel. These routines are used by the functions in    */
end_comment

begin_comment
comment|/* mapobject_preview.c and mapobject_apply.c             */
end_comment

begin_comment
comment|/*********************************************************/
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
file|<sys/types.h>
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
file|"mapobject_preview.h"
end_include

begin_include
include|#
directive|include
file|"mapobject_shade.h"
end_include

begin_include
include|#
directive|include
file|"mapobject_ui.h"
end_include

begin_include
include|#
directive|include
file|"mapobject_image.h"
end_include

begin_decl_stmt
DECL|variable|input_drawable
DECL|variable|output_drawable
name|GimpDrawable
modifier|*
name|input_drawable
decl_stmt|,
modifier|*
name|output_drawable
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|source_region
DECL|variable|dest_region
name|GimpPixelRgn
name|source_region
decl_stmt|,
name|dest_region
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|box_drawables
name|GimpDrawable
modifier|*
name|box_drawables
index|[
literal|6
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|box_regions
name|GimpPixelRgn
name|box_regions
index|[
literal|6
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cylinder_drawables
name|GimpDrawable
modifier|*
name|cylinder_drawables
index|[
literal|2
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cylinder_regions
name|GimpPixelRgn
name|cylinder_regions
index|[
literal|2
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|preview_rgb_data
name|guchar
modifier|*
name|preview_rgb_data
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|maxcounter
DECL|variable|old_depth
DECL|variable|max_depth
name|glong
name|maxcounter
decl_stmt|,
name|old_depth
decl_stmt|,
name|max_depth
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|imgtype
DECL|variable|width
DECL|variable|height
DECL|variable|in_channels
DECL|variable|out_channels
name|gint
name|imgtype
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|,
name|in_channels
decl_stmt|,
name|out_channels
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|background
name|GimpRGB
name|background
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|oldtreshold
name|gdouble
name|oldtreshold
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|border_x1
DECL|variable|border_y1
DECL|variable|border_x2
DECL|variable|border_y2
name|gint
name|border_x1
decl_stmt|,
name|border_y1
decl_stmt|,
name|border_x2
decl_stmt|,
name|border_y2
decl_stmt|;
end_decl_stmt

begin_comment
comment|/******************/
end_comment

begin_comment
comment|/* Implementation */
end_comment

begin_comment
comment|/******************/
end_comment

begin_function
name|GimpRGB
DECL|function|peek (gint x,gint y)
name|peek
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
specifier|static
name|guchar
name|data
index|[
literal|4
index|]
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gimp_pixel_rgn_get_pixel
argument_list|(
operator|&
name|source_region
argument_list|,
name|data
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|color
operator|.
name|r
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|data
index|[
literal|0
index|]
argument_list|)
operator|/
literal|255.0
expr_stmt|;
name|color
operator|.
name|g
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|data
index|[
literal|1
index|]
argument_list|)
operator|/
literal|255.0
expr_stmt|;
name|color
operator|.
name|b
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|data
index|[
literal|2
index|]
argument_list|)
operator|/
literal|255.0
expr_stmt|;
if|if
condition|(
name|input_drawable
operator|->
name|bpp
operator|==
literal|4
condition|)
block|{
if|if
condition|(
name|in_channels
operator|==
literal|4
condition|)
name|color
operator|.
name|a
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|data
index|[
literal|3
index|]
argument_list|)
operator|/
literal|255.0
expr_stmt|;
else|else
name|color
operator|.
name|a
operator|=
literal|1.0
expr_stmt|;
block|}
else|else
block|{
name|color
operator|.
name|a
operator|=
literal|1.0
expr_stmt|;
block|}
return|return
name|color
return|;
block|}
end_function

begin_function
specifier|static
name|GimpRGB
DECL|function|peek_box_image (gint image,gint x,gint y)
name|peek_box_image
parameter_list|(
name|gint
name|image
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
specifier|static
name|guchar
name|data
index|[
literal|4
index|]
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gimp_pixel_rgn_get_pixel
argument_list|(
operator|&
name|box_regions
index|[
name|image
index|]
argument_list|,
name|data
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|color
operator|.
name|r
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|data
index|[
literal|0
index|]
argument_list|)
operator|/
literal|255.0
expr_stmt|;
name|color
operator|.
name|g
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|data
index|[
literal|1
index|]
argument_list|)
operator|/
literal|255.0
expr_stmt|;
name|color
operator|.
name|b
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|data
index|[
literal|2
index|]
argument_list|)
operator|/
literal|255.0
expr_stmt|;
if|if
condition|(
name|box_drawables
index|[
name|image
index|]
operator|->
name|bpp
operator|==
literal|4
condition|)
block|{
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|box_drawables
index|[
name|image
index|]
operator|->
name|drawable_id
argument_list|)
condition|)
name|color
operator|.
name|a
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|data
index|[
literal|3
index|]
argument_list|)
operator|/
literal|255.0
expr_stmt|;
else|else
name|color
operator|.
name|a
operator|=
literal|1.0
expr_stmt|;
block|}
else|else
block|{
name|color
operator|.
name|a
operator|=
literal|1.0
expr_stmt|;
block|}
return|return
name|color
return|;
block|}
end_function

begin_function
specifier|static
name|GimpRGB
DECL|function|peek_cylinder_image (gint image,gint x,gint y)
name|peek_cylinder_image
parameter_list|(
name|gint
name|image
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
specifier|static
name|guchar
name|data
index|[
literal|4
index|]
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gimp_pixel_rgn_get_pixel
argument_list|(
operator|&
name|cylinder_regions
index|[
name|image
index|]
argument_list|,
name|data
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|color
operator|.
name|r
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|data
index|[
literal|0
index|]
argument_list|)
operator|/
literal|255.0
expr_stmt|;
name|color
operator|.
name|g
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|data
index|[
literal|1
index|]
argument_list|)
operator|/
literal|255.0
expr_stmt|;
name|color
operator|.
name|b
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|data
index|[
literal|2
index|]
argument_list|)
operator|/
literal|255.0
expr_stmt|;
if|if
condition|(
name|cylinder_drawables
index|[
name|image
index|]
operator|->
name|bpp
operator|==
literal|4
condition|)
block|{
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|cylinder_drawables
index|[
name|image
index|]
operator|->
name|drawable_id
argument_list|)
condition|)
name|color
operator|.
name|a
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|data
index|[
literal|3
index|]
argument_list|)
operator|/
literal|255.0
expr_stmt|;
else|else
name|color
operator|.
name|a
operator|=
literal|1.0
expr_stmt|;
block|}
else|else
block|{
name|color
operator|.
name|a
operator|=
literal|1.0
expr_stmt|;
block|}
return|return
name|color
return|;
block|}
end_function

begin_function
name|void
DECL|function|poke (gint x,gint y,GimpRGB * color,gpointer data)
name|poke
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
specifier|static
name|guchar
name|col
index|[
literal|4
index|]
decl_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
name|color
argument_list|,
operator|&
name|col
index|[
literal|0
index|]
argument_list|,
operator|&
name|col
index|[
literal|1
index|]
argument_list|,
operator|&
name|col
index|[
literal|2
index|]
argument_list|,
operator|&
name|col
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_pixel
argument_list|(
operator|&
name|dest_region
argument_list|,
name|col
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|checkbounds (gint x,gint y)
name|checkbounds
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
if|if
condition|(
name|x
operator|<
name|border_x1
operator|||
name|y
operator|<
name|border_y1
operator|||
name|x
operator|>=
name|border_x2
operator|||
name|y
operator|>=
name|border_y2
condition|)
return|return
name|FALSE
return|;
else|else
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|checkbounds_box_image (gint image,gint x,gint y)
name|checkbounds_box_image
parameter_list|(
name|gint
name|image
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|w
operator|=
name|box_drawables
index|[
name|image
index|]
operator|->
name|width
expr_stmt|;
name|h
operator|=
name|box_drawables
index|[
name|image
index|]
operator|->
name|height
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0
operator|||
name|y
operator|<
literal|0
operator|||
name|x
operator|>=
name|w
operator|||
name|y
operator|>=
name|h
condition|)
return|return
name|FALSE
return|;
else|else
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|checkbounds_cylinder_image (gint image,gint x,gint y)
name|checkbounds_cylinder_image
parameter_list|(
name|gint
name|image
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|w
operator|=
name|cylinder_drawables
index|[
name|image
index|]
operator|->
name|width
expr_stmt|;
name|h
operator|=
name|cylinder_drawables
index|[
name|image
index|]
operator|->
name|height
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0
operator|||
name|y
operator|<
literal|0
operator|||
name|x
operator|>=
name|w
operator|||
name|y
operator|>=
name|h
condition|)
return|return
name|FALSE
return|;
else|else
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GimpVector3
DECL|function|int_to_pos (gint x,gint y)
name|int_to_pos
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|GimpVector3
name|pos
decl_stmt|;
name|pos
operator|.
name|x
operator|=
operator|(
name|gdouble
operator|)
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
operator|(
name|gdouble
operator|)
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
return|return
name|pos
return|;
block|}
end_function

begin_function
name|void
DECL|function|pos_to_int (gdouble x,gdouble y,gint * scr_x,gint * scr_y)
name|pos_to_int
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gint
modifier|*
name|scr_x
parameter_list|,
name|gint
modifier|*
name|scr_y
parameter_list|)
block|{
operator|*
name|scr_x
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|x
operator|*
operator|(
name|gdouble
operator|)
name|width
operator|)
argument_list|)
expr_stmt|;
operator|*
name|scr_y
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|y
operator|*
operator|(
name|gdouble
operator|)
name|height
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**********************************************/
end_comment

begin_comment
comment|/* Compute the image color at pos (u,v) using */
end_comment

begin_comment
comment|/* Quartics bilinear interpolation stuff.     */
end_comment

begin_comment
comment|/**********************************************/
end_comment

begin_function
name|GimpRGB
DECL|function|get_image_color (gdouble u,gdouble v,gint * inside)
name|get_image_color
parameter_list|(
name|gdouble
name|u
parameter_list|,
name|gdouble
name|v
parameter_list|,
name|gint
modifier|*
name|inside
parameter_list|)
block|{
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|GimpRGB
name|p
index|[
literal|4
index|]
decl_stmt|;
name|pos_to_int
argument_list|(
name|u
argument_list|,
name|v
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
if|if
condition|(
name|mapvals
operator|.
name|tiled
operator|==
name|TRUE
condition|)
block|{
operator|*
name|inside
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|x1
operator|<
literal|0
condition|)
name|x1
operator|=
operator|(
name|width
operator|-
literal|1
operator|)
operator|-
operator|(
operator|-
name|x1
operator|%
name|width
operator|)
expr_stmt|;
else|else
name|x1
operator|=
name|x1
operator|%
name|width
expr_stmt|;
if|if
condition|(
name|y1
operator|<
literal|0
condition|)
name|y1
operator|=
operator|(
name|height
operator|-
literal|1
operator|)
operator|-
operator|(
operator|-
name|y1
operator|%
name|height
operator|)
expr_stmt|;
else|else
name|y1
operator|=
name|y1
operator|%
name|height
expr_stmt|;
name|x2
operator|=
operator|(
name|x1
operator|+
literal|1
operator|)
operator|%
name|width
expr_stmt|;
name|y2
operator|=
operator|(
name|y1
operator|+
literal|1
operator|)
operator|%
name|height
expr_stmt|;
name|p
index|[
literal|0
index|]
operator|=
name|peek
argument_list|(
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|p
index|[
literal|1
index|]
operator|=
name|peek
argument_list|(
name|x2
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|p
index|[
literal|2
index|]
operator|=
name|peek
argument_list|(
name|x1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|p
index|[
literal|3
index|]
operator|=
name|peek
argument_list|(
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
return|return
name|gimp_bilinear_rgba
argument_list|(
name|u
operator|*
name|width
argument_list|,
name|v
operator|*
name|height
argument_list|,
name|p
argument_list|)
return|;
block|}
if|if
condition|(
name|checkbounds
argument_list|(
name|x1
argument_list|,
name|y1
argument_list|)
operator|==
name|FALSE
condition|)
block|{
operator|*
name|inside
operator|=
name|FALSE
expr_stmt|;
return|return
name|background
return|;
block|}
name|x2
operator|=
operator|(
name|x1
operator|+
literal|1
operator|)
expr_stmt|;
name|y2
operator|=
operator|(
name|y1
operator|+
literal|1
operator|)
expr_stmt|;
if|if
condition|(
name|checkbounds
argument_list|(
name|x2
argument_list|,
name|y2
argument_list|)
operator|==
name|FALSE
condition|)
block|{
operator|*
name|inside
operator|=
name|TRUE
expr_stmt|;
return|return
name|peek
argument_list|(
name|x1
argument_list|,
name|y1
argument_list|)
return|;
block|}
operator|*
name|inside
operator|=
name|TRUE
expr_stmt|;
name|p
index|[
literal|0
index|]
operator|=
name|peek
argument_list|(
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|p
index|[
literal|1
index|]
operator|=
name|peek
argument_list|(
name|x2
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|p
index|[
literal|2
index|]
operator|=
name|peek
argument_list|(
name|x1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|p
index|[
literal|3
index|]
operator|=
name|peek
argument_list|(
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
return|return
name|gimp_bilinear_rgba
argument_list|(
name|u
operator|*
name|width
argument_list|,
name|v
operator|*
name|height
argument_list|,
name|p
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpRGB
DECL|function|get_box_image_color (gint image,gdouble u,gdouble v)
name|get_box_image_color
parameter_list|(
name|gint
name|image
parameter_list|,
name|gdouble
name|u
parameter_list|,
name|gdouble
name|v
parameter_list|)
block|{
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|GimpRGB
name|p
index|[
literal|4
index|]
decl_stmt|;
name|w
operator|=
name|box_drawables
index|[
name|image
index|]
operator|->
name|width
expr_stmt|;
name|h
operator|=
name|box_drawables
index|[
name|image
index|]
operator|->
name|height
expr_stmt|;
name|x1
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|u
operator|*
operator|(
name|gdouble
operator|)
name|w
operator|)
argument_list|)
expr_stmt|;
name|y1
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|v
operator|*
operator|(
name|gdouble
operator|)
name|h
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|checkbounds_box_image
argument_list|(
name|image
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
operator|==
name|FALSE
condition|)
return|return
name|background
return|;
name|x2
operator|=
operator|(
name|x1
operator|+
literal|1
operator|)
expr_stmt|;
name|y2
operator|=
operator|(
name|y1
operator|+
literal|1
operator|)
expr_stmt|;
if|if
condition|(
name|checkbounds_box_image
argument_list|(
name|image
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
operator|==
name|FALSE
condition|)
return|return
name|peek_box_image
argument_list|(
name|image
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
return|;
name|p
index|[
literal|0
index|]
operator|=
name|peek_box_image
argument_list|(
name|image
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|p
index|[
literal|1
index|]
operator|=
name|peek_box_image
argument_list|(
name|image
argument_list|,
name|x2
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|p
index|[
literal|2
index|]
operator|=
name|peek_box_image
argument_list|(
name|image
argument_list|,
name|x1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|p
index|[
literal|3
index|]
operator|=
name|peek_box_image
argument_list|(
name|image
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
return|return
name|gimp_bilinear_rgba
argument_list|(
name|u
operator|*
name|w
argument_list|,
name|v
operator|*
name|h
argument_list|,
name|p
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpRGB
DECL|function|get_cylinder_image_color (gint image,gdouble u,gdouble v)
name|get_cylinder_image_color
parameter_list|(
name|gint
name|image
parameter_list|,
name|gdouble
name|u
parameter_list|,
name|gdouble
name|v
parameter_list|)
block|{
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|GimpRGB
name|p
index|[
literal|4
index|]
decl_stmt|;
name|w
operator|=
name|cylinder_drawables
index|[
name|image
index|]
operator|->
name|width
expr_stmt|;
name|h
operator|=
name|cylinder_drawables
index|[
name|image
index|]
operator|->
name|height
expr_stmt|;
name|x1
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|u
operator|*
operator|(
name|gdouble
operator|)
name|w
operator|)
argument_list|)
expr_stmt|;
name|y1
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|v
operator|*
operator|(
name|gdouble
operator|)
name|h
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|checkbounds_cylinder_image
argument_list|(
name|image
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
operator|==
name|FALSE
condition|)
return|return
name|background
return|;
name|x2
operator|=
operator|(
name|x1
operator|+
literal|1
operator|)
expr_stmt|;
name|y2
operator|=
operator|(
name|y1
operator|+
literal|1
operator|)
expr_stmt|;
if|if
condition|(
name|checkbounds_cylinder_image
argument_list|(
name|image
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
operator|==
name|FALSE
condition|)
return|return
name|peek_cylinder_image
argument_list|(
name|image
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
return|;
name|p
index|[
literal|0
index|]
operator|=
name|peek_cylinder_image
argument_list|(
name|image
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|p
index|[
literal|1
index|]
operator|=
name|peek_cylinder_image
argument_list|(
name|image
argument_list|,
name|x2
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|p
index|[
literal|2
index|]
operator|=
name|peek_cylinder_image
argument_list|(
name|image
argument_list|,
name|x1
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|p
index|[
literal|3
index|]
operator|=
name|peek_cylinder_image
argument_list|(
name|image
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
return|return
name|gimp_bilinear_rgba
argument_list|(
name|u
operator|*
name|w
argument_list|,
name|v
operator|*
name|h
argument_list|,
name|p
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/****************************************/
end_comment

begin_comment
comment|/* Allocate memory for temporary images */
end_comment

begin_comment
comment|/****************************************/
end_comment

begin_function
name|gint
DECL|function|image_setup (GimpDrawable * drawable,gint interactive)
name|image_setup
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|interactive
parameter_list|)
block|{
comment|/* Set the tile cache size */
comment|/* ======================= */
name|gimp_tile_cache_ntiles
argument_list|(
operator|(
name|drawable
operator|->
name|width
operator|+
name|gimp_tile_width
argument_list|()
operator|-
literal|1
operator|)
operator|/
name|gimp_tile_width
argument_list|()
argument_list|)
expr_stmt|;
comment|/* Get some useful info on the input drawable */
comment|/* ========================================== */
name|input_drawable
operator|=
name|drawable
expr_stmt|;
name|output_drawable
operator|=
name|drawable
expr_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|border_x1
argument_list|,
operator|&
name|border_y1
argument_list|,
operator|&
name|border_x2
argument_list|,
operator|&
name|border_y2
argument_list|)
expr_stmt|;
name|width
operator|=
name|input_drawable
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|input_drawable
operator|->
name|height
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|source_region
argument_list|,
name|input_drawable
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
name|maxcounter
operator|=
operator|(
name|glong
operator|)
name|width
operator|*
operator|(
name|glong
operator|)
name|height
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
name|gimp_rgba_set
argument_list|(
operator|&
name|background
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_context_get_background
argument_list|(
operator|&
name|background
argument_list|)
expr_stmt|;
name|gimp_rgb_set_alpha
argument_list|(
operator|&
name|background
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
comment|/* Assume at least RGB */
comment|/* =================== */
name|in_channels
operator|=
literal|3
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|input_drawable
operator|->
name|drawable_id
argument_list|)
operator|==
name|TRUE
condition|)
name|in_channels
operator|++
expr_stmt|;
if|if
condition|(
name|interactive
operator|==
name|TRUE
condition|)
block|{
name|preview_rgb_data
operator|=
name|g_new0
argument_list|(
name|guchar
argument_list|,
name|PREVIEW_HEIGHT
operator|*
name|PREVIEW_WIDTH
operator|*
literal|3
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

