begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|LIGHTINGMAINH
end_ifndef

begin_define
DECL|macro|LIGHTINGMAINH
define|#
directive|define
name|LIGHTINGMAINH
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
file|"lighting_preview.h"
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
DECL|enum|__anon2bc3b08d0103
typedef|typedef
enum|enum
block|{
DECL|enumerator|POINT_LIGHT
name|POINT_LIGHT
block|,
DECL|enumerator|DIRECTIONAL_LIGHT
name|DIRECTIONAL_LIGHT
block|,
DECL|enumerator|SPOT_LIGHT
name|SPOT_LIGHT
block|,
DECL|enumerator|NO_LIGHT
name|NO_LIGHT
DECL|typedef|LightType
block|}
name|LightType
typedef|;
end_typedef

begin_enum
DECL|enum|__anon2bc3b08d0203
enum|enum
block|{
DECL|enumerator|IMAGE_BUMP
name|IMAGE_BUMP
block|,
DECL|enumerator|WAVES_BUMP
name|WAVES_BUMP
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2bc3b08d0308
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
DECL|struct|__anon2bc3b08d0408
block|{
DECL|member|type
name|LightType
name|type
decl_stmt|;
DECL|member|position
name|GckVector3
name|position
decl_stmt|;
DECL|member|direction
name|GckVector3
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
DECL|struct|__anon2bc3b08d0508
typedef|typedef
struct|struct
block|{
DECL|member|drawable_id
name|gint32
name|drawable_id
decl_stmt|;
DECL|member|bumpmap_id
name|gint32
name|bumpmap_id
decl_stmt|;
DECL|member|envmap_id
name|gint32
name|envmap_id
decl_stmt|;
comment|/* Render variables */
comment|/* ================ */
DECL|member|viewpoint
name|GckVector3
name|viewpoint
decl_stmt|;
DECL|member|planenormal
name|GckVector3
name|planenormal
decl_stmt|;
DECL|member|lightsource
name|LightSettings
name|lightsource
decl_stmt|;
DECL|member|material
name|MaterialSettings
name|material
decl_stmt|;
DECL|member|ref_material
name|MaterialSettings
name|ref_material
decl_stmt|;
DECL|member|pixel_treshold
name|gdouble
name|pixel_treshold
decl_stmt|;
DECL|member|bumpmax
DECL|member|bumpmin
name|gdouble
name|bumpmax
decl_stmt|,
name|bumpmin
decl_stmt|;
comment|/*  gdouble wave_cx,wave_cy;   gdouble wave_lx,wave_ly;   gdouble wave_amp,wave_ph; */
DECL|member|max_depth
name|gint
name|max_depth
decl_stmt|;
DECL|member|bumpmaptype
name|gint
name|bumpmaptype
decl_stmt|;
comment|/*  gint    bumptype; */
comment|/* Flags */
comment|/* ===== */
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
DECL|member|tooltips_enabled
name|gint
name|tooltips_enabled
decl_stmt|;
DECL|member|bump_mapped
name|gint
name|bump_mapped
decl_stmt|;
DECL|member|env_mapped
name|gint
name|env_mapped
decl_stmt|;
DECL|member|ref_mapped
name|gint
name|ref_mapped
decl_stmt|;
DECL|member|bumpstretch
name|gint
name|bumpstretch
decl_stmt|;
DECL|member|previewquality
name|gint
name|previewquality
decl_stmt|;
comment|/* Misc */
comment|/* ==== */
DECL|member|preview_zoom_factor
name|gdouble
name|preview_zoom_factor
decl_stmt|;
DECL|typedef|LightingValues
block|}
name|LightingValues
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
name|LightingValues
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

