begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* vector2d  * Copyright (C) 1998 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__VECTOR2D_H__
end_ifndef

begin_define
DECL|macro|__VECTOR2D_H__
define|#
directive|define
name|__VECTOR2D_H__
end_define

begin_typedef
DECL|struct|_vector2d
typedef|typedef
struct|struct
name|_vector2d
block|{
DECL|member|x
DECL|member|y
name|double
name|x
decl_stmt|,
name|y
decl_stmt|;
DECL|typedef|vector2d
block|}
name|vector2d
typedef|;
end_typedef

begin_function_decl
name|void
name|vector2d_set
parameter_list|(
name|vector2d
modifier|*
name|v
parameter_list|,
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|double
name|vector2d_dot_product
parameter_list|(
name|vector2d
modifier|*
name|v1
parameter_list|,
name|vector2d
modifier|*
name|v2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|double
name|vector2d_magnitude
parameter_list|(
name|vector2d
modifier|*
name|v
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __VECTOR2D_H__ */
end_comment

end_unit

