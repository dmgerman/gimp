begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__TILE_CACHE_H__
end_ifndef

begin_define
DECL|macro|__TILE_CACHE_H__
define|#
directive|define
name|__TILE_CACHE_H__
end_define

begin_include
include|#
directive|include
file|"tile.h"
end_include

begin_function_decl
name|void
name|tile_cache_insert
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_cache_flush
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_cache_set_size
parameter_list|(
name|unsigned
name|long
name|cache_size
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TILE_CACHE_H__ */
end_comment

end_unit

