begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__MAZE_UTILS_H__
end_ifndef

begin_define
DECL|macro|__MAZE_UTILS_H__
define|#
directive|define
name|__MAZE_UTILS_H__
end_define

begin_function_decl
name|void
name|get_colors
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|guint8
modifier|*
name|fg
parameter_list|,
name|guint8
modifier|*
name|bg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|drawbox
parameter_list|(
name|GimpPixelRgn
modifier|*
name|dest_rgn
parameter_list|,
name|guint
name|x
parameter_list|,
name|guint
name|y
parameter_list|,
name|guint
name|w
parameter_list|,
name|guint
name|h
parameter_list|,
name|guint8
name|clr
index|[
literal|4
index|]
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __MAZE_UTILS_H__ */
end_comment

end_unit

