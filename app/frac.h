begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__FRAC_H__
end_ifndef

begin_define
DECL|macro|__FRAC_H__
define|#
directive|define
name|__FRAC_H__
end_define

begin_function_decl
name|void
name|xcf_compress_frac_info
parameter_list|(
name|int
name|_layer_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|xcf_save_compress_frac_init
parameter_list|(
name|int
name|_dom_density
parameter_list|,
name|double
name|quality
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|xcf_load_compress_frac_init
parameter_list|(
name|int
name|_image_scale
parameter_list|,
name|int
name|_iterations
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|xcf_load_frac_compressed_tile
parameter_list|(
name|XcfInfo
modifier|*
name|info
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|xcf_save_frac_compressed_tile
parameter_list|(
name|XcfInfo
modifier|*
name|info
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __FRAC_H__ */
end_comment

end_unit

