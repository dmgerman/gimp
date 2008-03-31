begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__MAZE_ALGORITHMS_H__
end_ifndef

begin_define
DECL|macro|__MAZE_ALGORITHMS_H__
define|#
directive|define
name|__MAZE_ALGORITHMS_H__
end_define

begin_function_decl
name|void
name|mazegen
parameter_list|(
name|gint
name|pos
parameter_list|,
name|guchar
modifier|*
name|maz
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|rnd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|mazegen_tileable
parameter_list|(
name|gint
name|pos
parameter_list|,
name|guchar
modifier|*
name|maz
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|rnd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|prim
parameter_list|(
name|gint
name|pos
parameter_list|,
name|guchar
modifier|*
name|maz
parameter_list|,
name|guint
name|x
parameter_list|,
name|guint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|prim_tileable
parameter_list|(
name|guchar
modifier|*
name|maz
parameter_list|,
name|guint
name|x
parameter_list|,
name|guint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __MAZE_ALGORITHMS_H__ */
end_comment

end_unit

