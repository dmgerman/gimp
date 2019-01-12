begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpchunkiterator.h  * Copyright (C) 2019 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CHUNK_ITEARTOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CHUNK_ITEARTOR_H__
define|#
directive|define
name|__GIMP_CHUNK_ITEARTOR_H__
end_define

begin_function_decl
name|GimpChunkIterator
modifier|*
name|gimp_chunk_iterator_new
parameter_list|(
name|cairo_region_t
modifier|*
name|region
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_chunk_iterator_set_tile_rect
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_chunk_iterator_set_priority_rect
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_chunk_iterator_set_interval
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
name|gdouble
name|interval
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_chunk_iterator_next
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_chunk_iterator_get_rect
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|cairo_region_t
modifier|*
name|gimp_chunk_iterator_stop
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
name|gboolean
name|free_region
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CHUNK_ITEARTOR_H__  */
end_comment

end_unit

