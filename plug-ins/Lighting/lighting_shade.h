begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__LIGHTING_SHADE_H__
end_ifndef

begin_define
DECL|macro|__LIGHTING_SHADE_H__
define|#
directive|define
name|__LIGHTING_SHADE_H__
end_define

begin_typedef
DECL|typedef|get_ray_func
typedef|typedef
name|GckRGB
function_decl|(
modifier|*
name|get_ray_func
function_decl|)
parameter_list|(
name|GimpVector3
modifier|*
name|vector
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|GckRGB
name|get_ray_color
parameter_list|(
name|GimpVector3
modifier|*
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GckRGB
name|get_ray_color_no_bilinear
parameter_list|(
name|GimpVector3
modifier|*
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GckRGB
name|get_ray_color_ref
parameter_list|(
name|GimpVector3
modifier|*
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GckRGB
name|get_ray_color_no_bilinear_ref
parameter_list|(
name|GimpVector3
modifier|*
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
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

begin_comment
comment|/* __LIGHTING_SHADE_H__ */
end_comment

end_unit

