begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|MAPOBJECTSHADEH
end_ifndef

begin_define
DECL|macro|MAPOBJECTSHADEH
define|#
directive|define
name|MAPOBJECTSHADEH
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
file|"mapobject_main.h"
end_include

begin_include
include|#
directive|include
file|"mapobject_image.h"
end_include

begin_typedef
DECL|typedef|get_ray_color_func
typedef|typedef
name|GckRGB
function_decl|(
modifier|*
name|get_ray_color_func
function_decl|)
parameter_list|(
name|GckVector3
modifier|*
name|pos
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
specifier|extern
name|get_ray_color_func
name|get_ray_color
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|extern
name|GckRGB
name|get_ray_color_plane
parameter_list|(
name|GckVector3
modifier|*
name|pos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|GckRGB
name|get_ray_color_sphere
parameter_list|(
name|GckVector3
modifier|*
name|pos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|compute_bounding_box
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

