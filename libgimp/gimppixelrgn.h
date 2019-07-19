begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppixelrgn.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
name|__GIMP_PIXEL_RGN_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PIXEL_RGN_H__
define|#
directive|define
name|__GIMP_PIXEL_RGN_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_struct
DECL|struct|_GimpPixelRgn
struct|struct
name|_GimpPixelRgn
block|{
DECL|member|data
name|guchar
modifier|*
name|data
decl_stmt|;
comment|/* pointer to region data */
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/* pointer to drawable */
DECL|member|bpp
name|gint
name|bpp
decl_stmt|;
comment|/* bytes per pixel */
DECL|member|rowstride
name|gint
name|rowstride
decl_stmt|;
comment|/* bytes per pixel row */
DECL|member|x
DECL|member|y
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/* origin */
DECL|member|w
DECL|member|h
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
comment|/* width and height of region */
DECL|member|dirty
name|guint
name|dirty
range|:
literal|1
decl_stmt|;
comment|/* will this region be dirtied? */
DECL|member|shadow
name|guint
name|shadow
range|:
literal|1
decl_stmt|;
comment|/* will this region use the shadow or normal tiles */
DECL|member|process_count
name|gint
name|process_count
decl_stmt|;
comment|/* used internally */
block|}
struct|;
end_struct

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_drawable_get_buffer
argument_list|)
end_macro

begin_function_decl
name|void
name|gimp_pixel_rgn_init
parameter_list|(
name|GimpPixelRgn
modifier|*
name|pr
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|dirty
parameter_list|,
name|gint
name|shadow
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gegl_buffer_get
argument_list|)
end_macro

begin_function_decl
name|void
name|gimp_pixel_rgn_get_row
parameter_list|(
name|GimpPixelRgn
modifier|*
name|pr
parameter_list|,
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gegl_buffer_get
argument_list|)
end_macro

begin_function_decl
name|void
name|gimp_pixel_rgn_get_rect
parameter_list|(
name|GimpPixelRgn
modifier|*
name|pr
parameter_list|,
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gegl_buffer_set
argument_list|)
end_macro

begin_function_decl
name|void
name|gimp_pixel_rgn_set_row
parameter_list|(
name|GimpPixelRgn
modifier|*
name|pr
parameter_list|,
specifier|const
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gegl_buffer_set
argument_list|)
end_macro

begin_function_decl
name|void
name|gimp_pixel_rgn_set_rect
parameter_list|(
name|GimpPixelRgn
modifier|*
name|pr
parameter_list|,
specifier|const
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gegl_buffer_iterator_new
argument_list|)
end_macro

begin_function_decl
name|gpointer
name|gimp_pixel_rgns_register
parameter_list|(
name|gint
name|nrgns
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gegl_buffer_iterator_new
argument_list|)
end_macro

begin_function_decl
name|gpointer
name|gimp_pixel_rgns_register2
parameter_list|(
name|gint
name|nrgns
parameter_list|,
name|GimpPixelRgn
modifier|*
modifier|*
name|prs
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gegl_buffer_iterator_next
argument_list|)
end_macro

begin_function_decl
name|gpointer
name|gimp_pixel_rgns_process
parameter_list|(
name|gpointer
name|pri_ptr
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
comment|/* __GIMP_PIXEL_RGN_H__ */
end_comment

end_unit

