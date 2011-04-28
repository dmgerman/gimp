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
name|__GIMP_CMYK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CMYK_H__
define|#
directive|define
name|__GIMP_CMYK_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
comment|/*  * GIMP_TYPE_CMYK  */
DECL|macro|GIMP_TYPE_CMYK
define|#
directive|define
name|GIMP_TYPE_CMYK
value|(gimp_cmyk_get_type ())
name|GType
name|gimp_cmyk_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_cmyk_set
parameter_list|(
name|GimpCMYK
modifier|*
name|cmyk
parameter_list|,
name|gdouble
name|cyan
parameter_list|,
name|gdouble
name|magenta
parameter_list|,
name|gdouble
name|yellow
parameter_list|,
name|gdouble
name|black
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cmyk_set_uchar
parameter_list|(
name|GimpCMYK
modifier|*
name|cmyk
parameter_list|,
name|guchar
name|cyan
parameter_list|,
name|guchar
name|magenta
parameter_list|,
name|guchar
name|yellow
parameter_list|,
name|guchar
name|black
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cmyk_get_uchar
parameter_list|(
specifier|const
name|GimpCMYK
modifier|*
name|cmyk
parameter_list|,
name|guchar
modifier|*
name|cyan
parameter_list|,
name|guchar
modifier|*
name|magenta
parameter_list|,
name|guchar
modifier|*
name|yellow
parameter_list|,
name|guchar
modifier|*
name|black
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cmyka_set
parameter_list|(
name|GimpCMYK
modifier|*
name|cmyka
parameter_list|,
name|gdouble
name|cyan
parameter_list|,
name|gdouble
name|magenta
parameter_list|,
name|gdouble
name|yellow
parameter_list|,
name|gdouble
name|black
parameter_list|,
name|gdouble
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cmyka_set_uchar
parameter_list|(
name|GimpCMYK
modifier|*
name|cmyka
parameter_list|,
name|guchar
name|cyan
parameter_list|,
name|guchar
name|magenta
parameter_list|,
name|guchar
name|yellow
parameter_list|,
name|guchar
name|black
parameter_list|,
name|guchar
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cmyka_get_uchar
parameter_list|(
specifier|const
name|GimpCMYK
modifier|*
name|cmyka
parameter_list|,
name|guchar
modifier|*
name|cyan
parameter_list|,
name|guchar
modifier|*
name|magenta
parameter_list|,
name|guchar
modifier|*
name|yellow
parameter_list|,
name|guchar
modifier|*
name|black
parameter_list|,
name|guchar
modifier|*
name|alpha
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
comment|/* __GIMP_CMYK_H__ */
end_comment

end_unit

