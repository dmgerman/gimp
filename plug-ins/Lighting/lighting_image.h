begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|LIGHTINGIMAGEH
end_ifndef

begin_define
DECL|macro|LIGHTINGIMAGEH
define|#
directive|define
name|LIGHTINGIMAGEH
end_define

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdk.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<gck/gck.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"lighting_main.h"
end_include

begin_decl_stmt
specifier|extern
name|GDrawable
modifier|*
name|input_drawable
decl_stmt|,
modifier|*
name|output_drawable
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GPixelRgn
name|source_region
decl_stmt|,
name|dest_region
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GDrawable
modifier|*
name|bump_drawable
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GPixelRgn
name|bump_region
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GDrawable
modifier|*
name|env_drawable
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GPixelRgn
name|env_region
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
name|GdkImage
modifier|*
name|image
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|glong
name|maxcounter
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
name|env_width
decl_stmt|,
name|env_height
decl_stmt|,
name|in_channels
decl_stmt|,
name|out_channels
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GckRGB
name|background
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
name|guchar
name|sinemap
index|[
literal|256
index|]
decl_stmt|,
name|spheremap
index|[
literal|256
index|]
decl_stmt|,
name|logmap
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_function_decl
name|guchar
name|peek_map
parameter_list|(
name|GPixelRgn
modifier|*
name|region
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GckRGB
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
name|GckRGB
name|peek_env_map
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
name|void
name|poke
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GckRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|check_bounds
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
name|GckVector3
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
name|GckVector3
name|int_to_posf
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
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
name|void
name|pos_to_float
parameter_list|(
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
specifier|extern
name|GckRGB
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
name|gdouble
name|get_map_value
parameter_list|(
name|GPixelRgn
modifier|*
name|region
parameter_list|,
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
name|gint
name|image_setup
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|interactive
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

