begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|LIGHTINGPREVIEWH
end_ifndef

begin_define
DECL|macro|LIGHTINGPREVIEWH
define|#
directive|define
name|LIGHTINGPREVIEWH
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

begin_define
DECL|macro|PREVIEW_WIDTH
define|#
directive|define
name|PREVIEW_WIDTH
value|300
end_define

begin_define
DECL|macro|PREVIEW_HEIGHT
define|#
directive|define
name|PREVIEW_HEIGHT
value|300
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28e8fb930108
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

begin_decl_stmt
specifier|extern
name|gdouble
modifier|*
name|xpostab
decl_stmt|,
modifier|*
name|ypostab
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
name|draw_preview_image
parameter_list|(
name|gint
name|recompute
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

