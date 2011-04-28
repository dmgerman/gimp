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
name|__GIMP_COLOR_SPACE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_SPACE_H__
define|#
directive|define
name|__GIMP_COLOR_SPACE_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
comment|/*  Color conversion routines  */
comment|/*  GimpRGB function  */
name|void
name|gimp_rgb_to_hsv
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_to_hsl
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|GimpHSL
modifier|*
name|hsl
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_to_cmyk
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|gdouble
name|pullout
parameter_list|,
name|GimpCMYK
modifier|*
name|cmyk
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_hsv_to_rgb
parameter_list|(
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|,
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_hsl_to_rgb
parameter_list|(
specifier|const
name|GimpHSL
modifier|*
name|hsl
parameter_list|,
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cmyk_to_rgb
parameter_list|(
specifier|const
name|GimpCMYK
modifier|*
name|cmyk
parameter_list|,
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_to_hwb
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|gdouble
modifier|*
name|hue
parameter_list|,
name|gdouble
modifier|*
name|whiteness
parameter_list|,
name|gdouble
modifier|*
name|blackness
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_hwb_to_rgb
parameter_list|(
name|gdouble
name|hue
parameter_list|,
name|gdouble
name|whiteness
parameter_list|,
name|gdouble
name|blackness
parameter_list|,
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  gint functions  */
end_comment

begin_function_decl
name|void
name|gimp_rgb_to_hsv_int
parameter_list|(
name|gint
modifier|*
name|red
comment|/* returns hue        */
parameter_list|,
name|gint
modifier|*
name|green
comment|/* returns saturation */
parameter_list|,
name|gint
modifier|*
name|blue
comment|/* returns value      */
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_hsv_to_rgb_int
parameter_list|(
name|gint
modifier|*
name|hue
comment|/* returns red        */
parameter_list|,
name|gint
modifier|*
name|saturation
comment|/* returns green      */
parameter_list|,
name|gint
modifier|*
name|value
comment|/* returns blue       */
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_to_cmyk_int
parameter_list|(
name|gint
modifier|*
name|red
comment|/* returns cyan       */
parameter_list|,
name|gint
modifier|*
name|green
comment|/* returns magenta    */
parameter_list|,
name|gint
modifier|*
name|blue
comment|/* returns yellow     */
parameter_list|,
name|gint
modifier|*
name|pullout
comment|/* returns black      */
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cmyk_to_rgb_int
parameter_list|(
name|gint
modifier|*
name|cyan
comment|/* returns red        */
parameter_list|,
name|gint
modifier|*
name|magenta
comment|/* returns green      */
parameter_list|,
name|gint
modifier|*
name|yellow
comment|/* returns blue       */
parameter_list|,
name|gint
modifier|*
name|black
comment|/* not changed        */
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_to_hsl_int
parameter_list|(
name|gint
modifier|*
name|red
comment|/* returns hue        */
parameter_list|,
name|gint
modifier|*
name|green
comment|/* returns saturation */
parameter_list|,
name|gint
modifier|*
name|blue
comment|/* returns lightness  */
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_rgb_to_l_int
parameter_list|(
name|gint
name|red
parameter_list|,
name|gint
name|green
parameter_list|,
name|gint
name|blue
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_hsl_to_rgb_int
parameter_list|(
name|gint
modifier|*
name|hue
comment|/* returns red        */
parameter_list|,
name|gint
modifier|*
name|saturation
comment|/* returns green      */
parameter_list|,
name|gint
modifier|*
name|lightness
comment|/* returns blue       */
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  gdouble functions  */
end_comment

begin_function_decl
name|void
name|gimp_rgb_to_hsv4
parameter_list|(
specifier|const
name|guchar
modifier|*
name|rgb
parameter_list|,
name|gdouble
modifier|*
name|hue
parameter_list|,
name|gdouble
modifier|*
name|saturation
parameter_list|,
name|gdouble
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_hsv_to_rgb4
parameter_list|(
name|guchar
modifier|*
name|rgb
parameter_list|,
name|gdouble
name|hue
parameter_list|,
name|gdouble
name|saturation
parameter_list|,
name|gdouble
name|value
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
comment|/* __GIMP_COLOR_SPACE_H__ */
end_comment

end_unit

