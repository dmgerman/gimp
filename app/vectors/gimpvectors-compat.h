begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpvectors-compat.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VECTORS_COMPAT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VECTORS_COMPAT_H__
define|#
directive|define
name|__GIMP_VECTORS_COMPAT_H__
end_define

begin_typedef
DECL|typedef|GimpVectorsCompatPoint
typedef|typedef
name|struct
name|_GimpVectorsCompatPoint
name|GimpVectorsCompatPoint
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpVectorsCompatPoint
struct|struct
name|_GimpVectorsCompatPoint
block|{
DECL|member|type
name|guint32
name|type
decl_stmt|;
DECL|member|x
name|gdouble
name|x
decl_stmt|;
DECL|member|y
name|gdouble
name|y
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GimpVectors
modifier|*
name|gimp_vectors_compat_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpVectorsCompatPoint
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|gboolean
name|closed
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_compat_is_compatible
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVectorsCompatPoint
modifier|*
name|gimp_vectors_compat_get_points
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|gint32
modifier|*
name|n_points
parameter_list|,
name|gint32
modifier|*
name|closed
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_VECTORS_COMPAT_H__ */
end_comment

end_unit

