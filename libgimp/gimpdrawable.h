begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpdrawable.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimp.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_H__
define|#
directive|define
name|__GIMP_DRAWABLE_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_struct
DECL|struct|_GimpDrawable
struct|struct
name|_GimpDrawable
block|{
DECL|member|drawable_id
name|gint32
name|drawable_id
decl_stmt|;
comment|/* drawable ID */
DECL|member|width
name|guint
name|width
decl_stmt|;
comment|/* width of drawble */
DECL|member|height
name|guint
name|height
decl_stmt|;
comment|/* height of drawble */
DECL|member|bpp
name|guint
name|bpp
decl_stmt|;
comment|/* bytes per pixel of drawable */
DECL|member|ntile_rows
name|guint
name|ntile_rows
decl_stmt|;
comment|/* # of tile rows */
DECL|member|ntile_cols
name|guint
name|ntile_cols
decl_stmt|;
comment|/* # of tile columns */
DECL|member|tiles
name|GimpTile
modifier|*
name|tiles
decl_stmt|;
comment|/* the normal tiles */
DECL|member|shadow_tiles
name|GimpTile
modifier|*
name|shadow_tiles
decl_stmt|;
comment|/* the shadow tiles */
block|}
struct|;
end_struct

begin_function_decl
name|GeglBuffer
modifier|*
name|gimp_drawable_get_buffer
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglBuffer
modifier|*
name|gimp_drawable_get_shadow_buffer
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_drawable_get_format
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_drawable_get_buffer
argument_list|)
end_macro

begin_function_decl
name|GimpDrawable
modifier|*
name|gimp_drawable_get
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GIMP_DEPRECATED
name|void
name|gimp_drawable_detach
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gegl_buffer_flush
argument_list|)
end_macro

begin_function_decl
name|void
name|gimp_drawable_flush
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_drawable_get_buffer
argument_list|)
end_macro

begin_function_decl
name|GimpTile
modifier|*
name|gimp_drawable_get_tile
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|shadow
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|col
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_drawable_get_buffer
argument_list|)
end_macro

begin_function_decl
name|GimpTile
modifier|*
name|gimp_drawable_get_tile2
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|shadow
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GIMP_DEPRECATED
name|void
name|gimp_drawable_get_color_uchar
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|guchar
modifier|*
name|color_uchar
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_drawable_get_thumbnail_data
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|bpp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_drawable_get_sub_thumbnail_data
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
name|src_width
parameter_list|,
name|gint
name|src_height
parameter_list|,
name|gint
modifier|*
name|dest_width
parameter_list|,
name|gint
modifier|*
name|dest_height
parameter_list|,
name|gint
modifier|*
name|bpp
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DRAWABLE_H__ */
end_comment

end_unit

