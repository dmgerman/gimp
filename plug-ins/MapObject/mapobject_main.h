begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|MAPOBJECTMAINH
end_ifndef

begin_define
DECL|macro|MAPOBJECTMAINH
define|#
directive|define
name|MAPOBJECTMAINH
end_define

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
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
file|"libgimp/stdplugins-intl.h"
end_include

begin_include
include|#
directive|include
file|"arcball.h"
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
file|"mapobject_preview.h"
end_include

begin_comment
comment|/* Defines and stuff */
end_comment

begin_comment
comment|/* ================= */
end_comment

begin_define
DECL|macro|TILE_CACHE_SIZE
define|#
directive|define
name|TILE_CACHE_SIZE
value|16
end_define

begin_comment
comment|/* Typedefs */
end_comment

begin_comment
comment|/* ======== */
end_comment

begin_typedef
DECL|enum|__anon2b575b4c0103
typedef|typedef
enum|enum
block|{
DECL|enumerator|POINT_LIGHT
name|POINT_LIGHT
block|,
DECL|enumerator|DIRECTIONAL_LIGHT
name|DIRECTIONAL_LIGHT
block|,
DECL|enumerator|NO_LIGHT
name|NO_LIGHT
DECL|typedef|LightType
block|}
name|LightType
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon2b575b4c0203
typedef|typedef
enum|enum
block|{
DECL|enumerator|MAP_PLANE
name|MAP_PLANE
block|,
DECL|enumerator|MAP_SPHERE
name|MAP_SPHERE
block|,
DECL|enumerator|MAP_BOX
name|MAP_BOX
block|,
DECL|enumerator|MAP_CYLINDER
name|MAP_CYLINDER
DECL|typedef|MapType
block|}
name|MapType
typedef|;
end_typedef

begin_comment
comment|/* Typedefs */
end_comment

begin_comment
comment|/* ======== */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b575b4c0308
block|{
DECL|member|ambient_int
name|gdouble
name|ambient_int
decl_stmt|;
DECL|member|diffuse_int
name|gdouble
name|diffuse_int
decl_stmt|;
DECL|member|diffuse_ref
name|gdouble
name|diffuse_ref
decl_stmt|;
DECL|member|specular_ref
name|gdouble
name|specular_ref
decl_stmt|;
DECL|member|highlight
name|gdouble
name|highlight
decl_stmt|;
DECL|member|color
name|GckRGB
name|color
decl_stmt|;
DECL|typedef|MaterialSettings
block|}
name|MaterialSettings
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b575b4c0408
block|{
DECL|member|type
name|LightType
name|type
decl_stmt|;
DECL|member|position
name|GimpVector3
name|position
decl_stmt|;
DECL|member|direction
name|GimpVector3
name|direction
decl_stmt|;
DECL|member|color
name|GckRGB
name|color
decl_stmt|;
DECL|member|intensity
name|gdouble
name|intensity
decl_stmt|;
DECL|typedef|LightSettings
block|}
name|LightSettings
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b575b4c0508
typedef|typedef
struct|struct
block|{
DECL|member|viewpoint
DECL|member|firstaxis
DECL|member|secondaxis
DECL|member|normal
DECL|member|position
DECL|member|scale
name|GimpVector3
name|viewpoint
decl_stmt|,
name|firstaxis
decl_stmt|,
name|secondaxis
decl_stmt|,
name|normal
decl_stmt|,
name|position
decl_stmt|,
name|scale
decl_stmt|;
DECL|member|lightsource
name|LightSettings
name|lightsource
decl_stmt|;
DECL|member|material
name|MaterialSettings
name|material
decl_stmt|;
DECL|member|refmaterial
name|MaterialSettings
name|refmaterial
decl_stmt|;
DECL|member|maptype
name|MapType
name|maptype
decl_stmt|;
DECL|member|antialiasing
name|gint
name|antialiasing
decl_stmt|;
DECL|member|create_new_image
name|gint
name|create_new_image
decl_stmt|;
DECL|member|transparent_background
name|gint
name|transparent_background
decl_stmt|;
DECL|member|tiled
name|gint
name|tiled
decl_stmt|;
DECL|member|showgrid
name|gint
name|showgrid
decl_stmt|;
DECL|member|tooltips_enabled
name|gint
name|tooltips_enabled
decl_stmt|;
DECL|member|showcaps
name|gint
name|showcaps
decl_stmt|;
DECL|member|preview_zoom_factor
name|glong
name|preview_zoom_factor
decl_stmt|;
DECL|member|alpha
DECL|member|beta
DECL|member|gamma
name|gdouble
name|alpha
decl_stmt|,
name|beta
decl_stmt|,
name|gamma
decl_stmt|;
DECL|member|maxdepth
name|gdouble
name|maxdepth
decl_stmt|;
DECL|member|pixeltreshold
name|gdouble
name|pixeltreshold
decl_stmt|;
DECL|member|radius
name|gdouble
name|radius
decl_stmt|;
DECL|member|cylinder_radius
name|gdouble
name|cylinder_radius
decl_stmt|;
DECL|member|cylinder_length
name|gdouble
name|cylinder_length
decl_stmt|;
DECL|member|boxmap_id
name|gint32
name|boxmap_id
index|[
literal|6
index|]
decl_stmt|;
DECL|member|cylindermap_id
name|gint32
name|cylindermap_id
index|[
literal|2
index|]
decl_stmt|;
DECL|typedef|MapObjectValues
block|}
name|MapObjectValues
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
name|MapObjectValues
name|mapvals
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GckRGB
name|background
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

end_unit

