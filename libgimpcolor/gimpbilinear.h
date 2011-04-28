begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_BILINEAR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BILINEAR_H__
define|#
directive|define
name|__GIMP_BILINEAR_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
comment|/*  bilinear interpolation functions taken from LibGCK  */
name|gdouble
name|gimp_bilinear
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
name|gimp_bilinear_8
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|guchar
modifier|*
name|values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint16
name|gimp_bilinear_16
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|guint16
modifier|*
name|values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint32
name|gimp_bilinear_32
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|guint32
modifier|*
name|values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpRGB
name|gimp_bilinear_rgb
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GimpRGB
modifier|*
name|values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpRGB
name|gimp_bilinear_rgba
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GimpRGB
modifier|*
name|values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_bilinear_pixels_8
parameter_list|(
name|guchar
modifier|*
name|dest
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|guint
name|bpp
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|guchar
modifier|*
modifier|*
name|values
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
comment|/* __GIMP_BILINEAR_H__ */
end_comment

end_unit

