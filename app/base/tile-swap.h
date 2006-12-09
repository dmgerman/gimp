begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b0d23610103
block|{
DECL|enumerator|SWAP_IN
name|SWAP_IN
init|=
literal|1
block|,
DECL|enumerator|SWAP_OUT
name|SWAP_OUT
block|,
DECL|enumerator|SWAP_DELETE
name|SWAP_DELETE
DECL|typedef|SwapCommand
block|}
name|SwapCommand
typedef|;
end_typedef

begin_typedef
DECL|typedef|SwapFunc
typedef|typedef
name|gint
function_decl|(
modifier|*
name|SwapFunc
function_decl|)
parameter_list|(
name|gint
name|fd
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|,
name|SwapCommand
name|cmd
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|tile_swap_init
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_swap_exit
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|tile_swap_add
parameter_list|(
name|gchar
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
name|gint
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
name|gboolean
name|tile_swap_test
parameter_list|(
name|void
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

