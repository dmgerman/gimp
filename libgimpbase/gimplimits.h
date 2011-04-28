begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1999 Peter Mattis and Spencer Kimball  *  * gimplimits.h  * Copyright (C) 1999 Michael Natterer<mitschel@cs.tu-berlin.de>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_BASE_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_BASE_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpbase/gimpbase.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LIMITS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LIMITS_H__
define|#
directive|define
name|__GIMP_LIMITS_H__
end_define

begin_expr_stmt
name|G_BEGIN_DECLS
comment|/**  * SECTION: gimplimits  * @title: gimplimits  * @short_description: Boundaries of some GIMP data types and some  *                     global constants.  *  * Boundaries of some GIMP data types and some global constants.  **/
comment|/**  * GIMP_MIN_IMAGE_SIZE:  *  * The minimum width and height of a GIMP image in pixels.  **/
DECL|macro|GIMP_MIN_IMAGE_SIZE
define|#
directive|define
name|GIMP_MIN_IMAGE_SIZE
value|1
comment|/**  * GIMP_MAX_IMAGE_SIZE:  *  * The maximum width and height of a GIMP image in pixels. This is a  * somewhat arbitray value that can be used when an upper value for  * pixel sizes is needed; for example to give a spin button an upper  * limit.  **/
DECL|macro|GIMP_MAX_IMAGE_SIZE
define|#
directive|define
name|GIMP_MAX_IMAGE_SIZE
value|262144
comment|/*  2^18  */
comment|/**  * GIMP_MIN_RESOLUTION:  *  * The minimum resolution of a GIMP image in pixels per inch. This is  * a somewhat arbitray value that can be used when a lower value for a  * resolution is needed. GIMP will not accept resolutions smaller than  * this value.  **/
DECL|macro|GIMP_MIN_RESOLUTION
define|#
directive|define
name|GIMP_MIN_RESOLUTION
value|5e-3
comment|/*  shouldn't display as 0.000  */
comment|/**  * GIMP_MAX_RESOLUTION:  *  * The maximum resolution of a GIMP image in pixels per inch. This is  * a somewhat arbitray value that can be used to when an upper value  * for a resolution is needed. GIMP will not accept resolutions larger  * than this value.  **/
DECL|macro|GIMP_MAX_RESOLUTION
define|#
directive|define
name|GIMP_MAX_RESOLUTION
value|65536.0
comment|/**  * GIMP_MAX_MEMSIZE:  *  * A large but arbitrary value that can be used when an upper limit  * for a memory size (in bytes) is needed. It is smaller than  * %G_MAXDOUBLE since the #GimpMemsizeEntry doesn't handle larger  * values.  **/
DECL|macro|GIMP_MAX_MEMSIZE
define|#
directive|define
name|GIMP_MAX_MEMSIZE
value|((guint64) 1<< 42)
comment|/*  4 terabyte;                                                   *  needs a 64bit variable                                                   *  and must be< G_MAXDOUBLE                                                   */
name|G_END_DECLS
end_expr_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LIMITS_H__ */
end_comment

end_unit

