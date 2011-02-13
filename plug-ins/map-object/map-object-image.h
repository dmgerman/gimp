begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__MAPOBJECT_IMAGE_H__
end_ifndef

begin_define
DECL|macro|__MAPOBJECT_IMAGE_H__
define|#
directive|define
name|__MAPOBJECT_IMAGE_H__
end_define

begin_comment
comment|/* Externally visible variables */
end_comment

begin_comment
comment|/* ============================ */
end_comment

begin_decl_stmt
specifier|extern
name|GimpDrawable
modifier|*
name|input_drawable
decl_stmt|,
modifier|*
name|output_drawable
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpPixelRgn
name|source_region
decl_stmt|,
name|dest_region
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpDrawable
modifier|*
name|box_drawables
index|[
literal|6
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpPixelRgn
name|box_regions
index|[
literal|6
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpDrawable
modifier|*
name|cylinder_drawables
index|[
literal|2
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpPixelRgn
name|cylinder_regions
index|[
literal|2
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|preview_rgb_data
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|preview_rgb_stride
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|cairo_surface_t
modifier|*
name|preview_surface
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|glong
name|maxcounter
decl_stmt|,
name|old_depth
decl_stmt|,
name|max_depth
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
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
specifier|extern
name|GimpRGB
name|background
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gdouble
name|oldtreshold
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
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

begin_decl_stmt
specifier|extern
name|GimpTile
modifier|*
name|current_in_tile
decl_stmt|,
modifier|*
name|current_out_tile
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Externally visible functions */
end_comment

begin_comment
comment|/* ============================ */
end_comment

begin_function_decl
specifier|extern
name|gint
name|image_setup
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|interactive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|glong
name|in_xy_to_index
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|glong
name|out_xy_to_index
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|gint
name|checkbounds
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|GimpRGB
name|peek
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
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
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|GimpVector3
name|int_to_pos
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
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
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|GimpRGB
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
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|GimpRGB
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
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|GimpRGB
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
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __MAPOBJECT_IMAGE_H__ */
end_comment

end_unit

