begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__TILE_SWAP_H__
end_ifndef

begin_define
DECL|macro|__TILE_SWAP_H__
define|#
directive|define
name|__TILE_SWAP_H__
end_define

begin_include
include|#
directive|include
file|"tile.h"
end_include

begin_typedef
DECL|enum|__anon293333fd0103
typedef|typedef
enum|enum
block|{
DECL|enumerator|SWAP_IN
name|SWAP_IN
init|=
literal|1
block|,
DECL|enumerator|SWAP_IN_ASYNC
name|SWAP_IN_ASYNC
block|,
DECL|enumerator|SWAP_OUT
name|SWAP_OUT
block|,
DECL|enumerator|SWAP_DELETE
name|SWAP_DELETE
block|,
DECL|enumerator|SWAP_COMPRESS
name|SWAP_COMPRESS
DECL|typedef|SwapCommand
block|}
name|SwapCommand
typedef|;
end_typedef

begin_typedef
DECL|typedef|SwapFunc
typedef|typedef
name|int
function_decl|(
modifier|*
name|SwapFunc
function_decl|)
parameter_list|(
name|int
name|fd
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|,
name|int
name|cmd
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|tile_swap_exit
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|tile_swap_add
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|,
name|SwapFunc
name|swap_func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_swap_remove
parameter_list|(
name|int
name|swap_num
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_swap_in
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_swap_in_async
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_swap_out
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_swap_delete
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_swap_compress
parameter_list|(
name|int
name|swap_num
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TILE_SWAP_H__ */
end_comment

end_unit

