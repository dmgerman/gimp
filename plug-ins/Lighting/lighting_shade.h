begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|LIGHTINGSHADEH
end_ifndef

begin_define
DECL|macro|LIGHTINGSHADEH
define|#
directive|define
name|LIGHTINGSHADEH
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
file|<gck/gck.h>
end_include

begin_include
include|#
directive|include
file|"lighting_main.h"
end_include

begin_include
include|#
directive|include
file|"lighting_image.h"
end_include

begin_typedef
DECL|typedef|get_ray_func
typedef|typedef
name|GckRGB
function_decl|(
modifier|*
name|get_ray_func
function_decl|)
parameter_list|(
name|GckVector3
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
specifier|extern
name|GckRGB
name|get_ray_color
parameter_list|(
name|GckVector3
modifier|*
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|GckRGB
name|get_ray_color_no_bilinear
parameter_list|(
name|GckVector3
modifier|*
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|GckRGB
name|get_ray_color_ref
parameter_list|(
name|GckVector3
modifier|*
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|GckRGB
name|get_ray_color_no_bilinear_ref
parameter_list|(
name|GckVector3
modifier|*
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|precompute_init
parameter_list|(
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|precompute_normals
parameter_list|(
name|gint
name|x1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

