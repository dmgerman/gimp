begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* blob.h: routines for manipulating scan converted convex  *         polygons.  *    * Copyright 1998, Owen Taylor<otaylor@gtk.org>  *  *> Please contact the above author before modifying the copy<  *> of this file in the GIMP distribution. Thanks.<  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  * */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BLOB_H__
end_ifndef

begin_define
DECL|macro|__BLOB_H__
define|#
directive|define
name|__BLOB_H__
end_define

begin_typedef
DECL|typedef|BlobSpan
typedef|typedef
name|struct
name|_BlobSpan
name|BlobSpan
typedef|;
end_typedef

begin_typedef
DECL|typedef|Blob
typedef|typedef
name|struct
name|_Blob
name|Blob
typedef|;
end_typedef

begin_struct
DECL|struct|_BlobSpan
struct|struct
name|_BlobSpan
block|{
DECL|member|left
name|int
name|left
decl_stmt|;
DECL|member|right
name|int
name|right
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_Blob
struct|struct
name|_Blob
block|{
DECL|member|y
name|int
name|y
decl_stmt|;
DECL|member|height
name|int
name|height
decl_stmt|;
DECL|member|data
name|BlobSpan
name|data
index|[
literal|1
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|Blob
modifier|*
name|blob_convex_union
parameter_list|(
name|Blob
modifier|*
name|b1
parameter_list|,
name|Blob
modifier|*
name|b2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Blob
modifier|*
name|blob_ellipse
parameter_list|(
name|double
name|xc
parameter_list|,
name|double
name|yc
parameter_list|,
name|double
name|xp
parameter_list|,
name|double
name|yp
parameter_list|,
name|double
name|xq
parameter_list|,
name|double
name|yq
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|blob_bounds
parameter_list|(
name|Blob
modifier|*
name|b
parameter_list|,
name|int
modifier|*
name|x
parameter_list|,
name|int
modifier|*
name|y
parameter_list|,
name|int
modifier|*
name|width
parameter_list|,
name|int
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __BLOB_H__ */
end_comment

end_unit

