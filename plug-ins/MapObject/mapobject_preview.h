begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|MAPOBJECTPREVIEWH
end_ifndef

begin_define
DECL|macro|MAPOBJECTPREVIEWH
define|#
directive|define
name|MAPOBJECTPREVIEWH
end_define

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
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
file|"arcball.h"
end_include

begin_include
include|#
directive|include
file|"mapobject_main.h"
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

begin_include
include|#
directive|include
file|"mapobject_apply.h"
end_include

begin_include
include|#
directive|include
file|"mapobject_shade.h"
end_include

begin_define
DECL|macro|PREVIEW_WIDTH
define|#
directive|define
name|PREVIEW_WIDTH
value|200
end_define

begin_define
DECL|macro|PREVIEW_HEIGHT
define|#
directive|define
name|PREVIEW_HEIGHT
value|200
end_define

begin_define
DECL|macro|WIRESIZE
define|#
directive|define
name|WIRESIZE
value|16
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon275d4c530108
block|{
DECL|member|x1
DECL|member|y1
DECL|member|x2
DECL|member|y2
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
DECL|member|linewidth
name|gint
name|linewidth
decl_stmt|;
DECL|member|linestyle
name|GdkLineStyle
name|linestyle
decl_stmt|;
DECL|typedef|line
block|}
name|line
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon275d4c530208
block|{
DECL|member|x
DECL|member|y
DECL|member|w
DECL|member|h
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
DECL|member|image
name|GdkImage
modifier|*
name|image
decl_stmt|;
DECL|typedef|BackBuffer
block|}
name|BackBuffer
typedef|;
end_typedef

begin_comment
comment|/* Externally visible variables */
end_comment

begin_comment
comment|/* ============================ */
end_comment

begin_decl_stmt
specifier|extern
name|line
name|linetab
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gdouble
name|mat
index|[
literal|3
index|]
index|[
literal|4
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|lightx
decl_stmt|,
name|lighty
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|BackBuffer
name|backbuf
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
name|void
name|compute_preview
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gint
name|pw
parameter_list|,
name|gint
name|ph
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|draw_wireframe
parameter_list|(
name|gint
name|startx
parameter_list|,
name|gint
name|starty
parameter_list|,
name|gint
name|pw
parameter_list|,
name|gint
name|ph
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|clear_wireframe
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|draw_preview_image
parameter_list|(
name|gint
name|docompute
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|draw_preview_wireframe
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|gint
name|check_light_hit
parameter_list|(
name|gint
name|xpos
parameter_list|,
name|gint
name|ypos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|update_light
parameter_list|(
name|gint
name|xpos
parameter_list|,
name|gint
name|ypos
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

