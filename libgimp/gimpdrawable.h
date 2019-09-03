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

begin_include
include|#
directive|include
file|<libgimp/gimpitem.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_DRAWABLE
define|#
directive|define
name|GIMP_TYPE_DRAWABLE
value|(gimp_drawable_get_type ())
end_define

begin_define
DECL|macro|GIMP_DRAWABLE (obj)
define|#
directive|define
name|GIMP_DRAWABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DRAWABLE, GimpDrawable))
end_define

begin_define
DECL|macro|GIMP_DRAWABLE_CLASS (klass)
define|#
directive|define
name|GIMP_DRAWABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DRAWABLE, GimpDrawableClass))
end_define

begin_define
DECL|macro|GIMP_IS_DRAWABLE (obj)
define|#
directive|define
name|GIMP_IS_DRAWABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DRAWABLE))
end_define

begin_define
DECL|macro|GIMP_IS_DRAWABLE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DRAWABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DRAWABLE))
end_define

begin_define
DECL|macro|GIMP_DRAWABLE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DRAWABLE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DRAWABLE, GimpDrawableClass))
end_define

begin_typedef
DECL|typedef|GimpDrawableClass
typedef|typedef
name|struct
name|_GimpDrawableClass
name|GimpDrawableClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawablePrivate
typedef|typedef
name|struct
name|_GimpDrawablePrivate
name|GimpDrawablePrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDrawable
struct|struct
name|_GimpDrawable
block|{
DECL|member|parent_instance
name|GimpItem
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpDrawablePrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDrawableClass
struct|struct
name|_GimpDrawableClass
block|{
DECL|member|parent_class
name|GimpItemClass
name|parent_class
decl_stmt|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved5
name|void
function_decl|(
modifier|*
name|_gimp_reserved5
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved6
name|void
function_decl|(
modifier|*
name|_gimp_reserved6
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved7
name|void
function_decl|(
modifier|*
name|_gimp_reserved7
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved8
name|void
function_decl|(
modifier|*
name|_gimp_reserved8
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved9
name|void
function_decl|(
modifier|*
name|_gimp_reserved9
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_drawable_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpDrawable
modifier|*
name|gimp_drawable_get_by_id
parameter_list|(
name|gint32
name|drawable_id
parameter_list|)
function_decl|;
end_function_decl

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DEPRECATED_REPLACE_NEW_API
end_ifndef

begin_function_decl
name|GeglBuffer
modifier|*
name|gimp_drawable_get_buffer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglBuffer
modifier|*
name|gimp_drawable_get_shadow_buffer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_drawable_get_format
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_drawable_get_thumbnail_format
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_drawable_get_thumbnail_data
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
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
name|GdkPixbuf
modifier|*
name|gimp_drawable_get_thumbnail
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpPixbufTransparency
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_drawable_get_sub_thumbnail_data
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
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

begin_function_decl
name|GdkPixbuf
modifier|*
name|gimp_drawable_get_sub_thumbnail
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
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
name|dest_width
parameter_list|,
name|gint
name|dest_height
parameter_list|,
name|GimpPixbufTransparency
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* GIMP_DEPRECATED_REPLACE_NEW_API */
end_comment

begin_define
DECL|macro|gimp_drawable_get_buffer
define|#
directive|define
name|gimp_drawable_get_buffer
value|gimp_drawable_get_buffer_deprecated
end_define

begin_define
DECL|macro|gimp_drawable_get_shadow_buffer
define|#
directive|define
name|gimp_drawable_get_shadow_buffer
value|gimp_drawable_get_shadow_buffer_deprecated
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DEPRECATED_REPLACE_NEW_API */
end_comment

begin_function_decl
name|GeglBuffer
modifier|*
name|gimp_drawable_get_buffer_deprecated
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglBuffer
modifier|*
name|gimp_drawable_get_shadow_buffer_deprecated
parameter_list|(
name|gint32
name|drawable_ID
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

