begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__LIGHTING_MAIN_H__
end_ifndef

begin_define
DECL|macro|__LIGHTING_MAIN_H__
define|#
directive|define
name|__LIGHTING_MAIN_H__
end_define

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

begin_define
DECL|macro|NUM_LIGHTS
define|#
directive|define
name|NUM_LIGHTS
value|3
end_define

begin_comment
comment|/* Typedefs */
end_comment

begin_comment
comment|/* ======== */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon279386050103
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
enum|enum
DECL|enum|__anon279386050203
block|{
DECL|enumerator|LINEAR_MAP
name|LINEAR_MAP
block|,
DECL|enumerator|LOGARITHMIC_MAP
name|LOGARITHMIC_MAP
block|,
DECL|enumerator|SINUSOIDAL_MAP
name|SINUSOIDAL_MAP
block|,
DECL|enumerator|SPHERICAL_MAP
name|SPHERICAL_MAP
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon279386050303
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
DECL|struct|__anon279386050408
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
DECL|member|metallic
name|gboolean
name|metallic
decl_stmt|;
DECL|member|color
name|GimpRGB
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
DECL|struct|__anon279386050508
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
name|GimpRGB
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
typedef|typedef
struct|struct
DECL|struct|__anon279386050608
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
name|GimpVector3
name|viewpoint
decl_stmt|;
DECL|member|planenormal
name|GimpVector3
name|planenormal
decl_stmt|;
DECL|member|lightsource
name|LightSettings
name|lightsource
index|[
name|NUM_LIGHTS
index|]
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
DECL|member|symbols
name|gboolean
name|symbols
decl_stmt|;
DECL|member|interactive_preview
name|gboolean
name|interactive_preview
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __LIGHTING_MAIN_H__ */
end_comment

end_unit

