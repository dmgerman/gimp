begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpcolortransform.h  * Copyright (C) 2014  Michael Natterer<mitch@gimp.org>  *                     Elle Stone<ellestone@ninedegreesbelow.com>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_COLOR_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COLOR_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpcolor/gimpcolor.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_TRANSFORM_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_TRANSFORM_H__
define|#
directive|define
name|__GIMP_COLOR_TRANSFORM_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b3b825c0103
block|{
DECL|enumerator|GIMP_COLOR_TRANSFORM_FLAGS_NOOPTIMIZE
name|GIMP_COLOR_TRANSFORM_FLAGS_NOOPTIMIZE
init|=
literal|0x0100
block|,
DECL|enumerator|GIMP_COLOR_TRANSFORM_FLAGS_GAMUT_CHECK
name|GIMP_COLOR_TRANSFORM_FLAGS_GAMUT_CHECK
init|=
literal|0x1000
block|,
DECL|enumerator|GIMP_COLOR_TRANSFORM_FLAGS_BLACK_POINT_COMPENSATION
name|GIMP_COLOR_TRANSFORM_FLAGS_BLACK_POINT_COMPENSATION
init|=
literal|0x2000
block|, }
DECL|typedef|GimpColorTransformFlags
name|GimpColorTransformFlags
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_COLOR_TRANSFORM
define|#
directive|define
name|GIMP_TYPE_COLOR_TRANSFORM
value|(gimp_color_transform_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_TRANSFORM (obj)
define|#
directive|define
name|GIMP_COLOR_TRANSFORM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_TRANSFORM, GimpColorTransform))
end_define

begin_define
DECL|macro|GIMP_COLOR_TRANSFORM_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_TRANSFORM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_TRANSFORM, GimpColorTransformClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_TRANSFORM (obj)
define|#
directive|define
name|GIMP_IS_COLOR_TRANSFORM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_TRANSFORM))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_TRANSFORM_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_TRANSFORM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_TRANSFORM))
end_define

begin_define
DECL|macro|GIMP_COLOR_TRANSFORM_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_TRANSFORM_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_TRANSFORM, GimpColorTransformClass))
end_define

begin_typedef
DECL|typedef|GimpColorTransformClass
typedef|typedef
name|struct
name|_GimpColorTransformClass
name|GimpColorTransformClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorTransformPrivate
typedef|typedef
name|struct
name|_GimpColorTransformPrivate
name|GimpColorTransformPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorTransform
struct|struct
name|_GimpColorTransform
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpColorTransformPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorTransformClass
struct|struct
name|_GimpColorTransformClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
comment|/* signals */
DECL|member|progress
name|void
function_decl|(
modifier|*
name|progress
function_decl|)
parameter_list|(
name|GimpColorTransform
modifier|*
name|transform
parameter_list|,
name|gdouble
name|fraction
parameter_list|)
function_decl|;
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
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_transform_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpColorTransform
modifier|*
name|gimp_color_transform_new
parameter_list|(
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
specifier|const
name|Babl
modifier|*
name|src_format
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|,
specifier|const
name|Babl
modifier|*
name|dest_format
parameter_list|,
name|GimpColorRenderingIntent
name|rendering_intent
parameter_list|,
name|GimpColorTransformFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorTransform
modifier|*
name|gimp_color_transform_new_proofing
parameter_list|(
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
specifier|const
name|Babl
modifier|*
name|src_format
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|,
specifier|const
name|Babl
modifier|*
name|dest_format
parameter_list|,
name|GimpColorProfile
modifier|*
name|proof_profile
parameter_list|,
name|GimpColorRenderingIntent
name|proof_intent
parameter_list|,
name|GimpColorRenderingIntent
name|display_intent
parameter_list|,
name|GimpColorTransformFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_transform_process_pixels
parameter_list|(
name|GimpColorTransform
modifier|*
name|transform
parameter_list|,
specifier|const
name|Babl
modifier|*
name|src_format
parameter_list|,
name|gconstpointer
name|src_pixels
parameter_list|,
specifier|const
name|Babl
modifier|*
name|dest_format
parameter_list|,
name|gpointer
name|dest_pixels
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_transform_process_buffer
parameter_list|(
name|GimpColorTransform
modifier|*
name|transform
parameter_list|,
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|src_rect
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|dest_rect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_color_transform_can_gegl_copy
parameter_list|(
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
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
comment|/* __GIMP_COLOR_TRANSFORM_H__ */
end_comment

end_unit

