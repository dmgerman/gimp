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
name|__GIMP_RGB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RGB_H__
define|#
directive|define
name|__GIMP_RGB_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
comment|/*  * GIMP_TYPE_RGB  */
DECL|macro|GIMP_TYPE_RGB
define|#
directive|define
name|GIMP_TYPE_RGB
value|(gimp_rgb_get_type ())
DECL|macro|GIMP_VALUE_HOLDS_RGB (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_RGB
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_RGB))
name|GType
name|gimp_rgb_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_value_get_rgb
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_rgb
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_PARAM_RGB  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_RGB
define|#
directive|define
name|GIMP_TYPE_PARAM_RGB
value|(gimp_param_rgb_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_RGB (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_RGB
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_RGB))
end_define

begin_decl_stmt
name|GType
name|gimp_param_rgb_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_rgb
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_param_spec_rgb_has_alpha
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  RGB and RGBA color types and operations taken from LibGCK  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29d2d8900103
block|{
DECL|enumerator|GIMP_RGB_COMPOSITE_NONE
name|GIMP_RGB_COMPOSITE_NONE
init|=
literal|0
block|,
DECL|enumerator|GIMP_RGB_COMPOSITE_NORMAL
name|GIMP_RGB_COMPOSITE_NORMAL
block|,
DECL|enumerator|GIMP_RGB_COMPOSITE_BEHIND
name|GIMP_RGB_COMPOSITE_BEHIND
DECL|typedef|GimpRGBCompositeMode
block|}
name|GimpRGBCompositeMode
typedef|;
end_typedef

begin_function_decl
name|void
name|gimp_rgb_set
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|gdouble
name|red
parameter_list|,
name|gdouble
name|green
parameter_list|,
name|gdouble
name|blue
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_set_alpha
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|gdouble
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_set_uchar
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_get_uchar
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|guchar
modifier|*
name|red
parameter_list|,
name|guchar
modifier|*
name|green
parameter_list|,
name|guchar
modifier|*
name|blue
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_rgb_parse_name
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_rgb_parse_hex
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|hex
parameter_list|,
name|gint
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_rgb_parse_css
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|css
parameter_list|,
name|gint
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_add
parameter_list|(
name|GimpRGB
modifier|*
name|rgb1
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_subtract
parameter_list|(
name|GimpRGB
modifier|*
name|rgb1
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_multiply
parameter_list|(
name|GimpRGB
modifier|*
name|rgb1
parameter_list|,
name|gdouble
name|factor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_rgb_distance
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb1
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_rgb_max
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_rgb_min
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_clamp
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_gamma
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|gdouble
name|gamma
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_rgb_luminance
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
name|gimp_rgb_luminance_uchar
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

begin_function_decl
name|gdouble
name|gimp_rgb_intensity
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
name|gimp_rgb_intensity_uchar
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|void
name|gimp_rgb_composite
parameter_list|(
name|GimpRGB
modifier|*
name|color1
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color2
parameter_list|,
name|GimpRGBCompositeMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  access to the list of color names  */
end_comment

begin_function_decl
name|gint
name|gimp_rgb_list_names
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
modifier|*
name|names
parameter_list|,
name|GimpRGB
modifier|*
modifier|*
name|colors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgba_set
parameter_list|(
name|GimpRGB
modifier|*
name|rgba
parameter_list|,
name|gdouble
name|red
parameter_list|,
name|gdouble
name|green
parameter_list|,
name|gdouble
name|blue
parameter_list|,
name|gdouble
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgba_set_uchar
parameter_list|(
name|GimpRGB
modifier|*
name|rgba
parameter_list|,
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|,
name|guchar
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgba_get_uchar
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgba
parameter_list|,
name|guchar
modifier|*
name|red
parameter_list|,
name|guchar
modifier|*
name|green
parameter_list|,
name|guchar
modifier|*
name|blue
parameter_list|,
name|guchar
modifier|*
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_rgba_parse_css
parameter_list|(
name|GimpRGB
modifier|*
name|rgba
parameter_list|,
specifier|const
name|gchar
modifier|*
name|css
parameter_list|,
name|gint
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgba_add
parameter_list|(
name|GimpRGB
modifier|*
name|rgba1
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgba2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgba_subtract
parameter_list|(
name|GimpRGB
modifier|*
name|rgba1
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgba2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgba_multiply
parameter_list|(
name|GimpRGB
modifier|*
name|rgba
parameter_list|,
name|gdouble
name|factor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_rgba_distance
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgba1
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgba2
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Map RGB to intensity  */
end_comment

begin_comment
comment|/*  * The weights to compute true CIE luminance from linear red, green  * and blue, as defined by the ITU-R Recommendation BT.709, "Basic  * Parameter Values for the HDTV Standard for the Studio and for  * International Programme Exchange" (1990). Also suggested in the  * sRGB colorspace specification by the W3C.  */
end_comment

begin_define
DECL|macro|GIMP_RGB_LUMINANCE_RED
define|#
directive|define
name|GIMP_RGB_LUMINANCE_RED
value|(0.2126)
end_define

begin_define
DECL|macro|GIMP_RGB_LUMINANCE_GREEN
define|#
directive|define
name|GIMP_RGB_LUMINANCE_GREEN
value|(0.7152)
end_define

begin_define
DECL|macro|GIMP_RGB_LUMINANCE_BLUE
define|#
directive|define
name|GIMP_RGB_LUMINANCE_BLUE
value|(0.0722)
end_define

begin_define
DECL|macro|GIMP_RGB_LUMINANCE (r,g,b)
define|#
directive|define
name|GIMP_RGB_LUMINANCE
parameter_list|(
name|r
parameter_list|,
name|g
parameter_list|,
name|b
parameter_list|)
value|((r) * GIMP_RGB_LUMINANCE_RED   + \                                    (g) * GIMP_RGB_LUMINANCE_GREEN + \                                    (b) * GIMP_RGB_LUMINANCE_BLUE)
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

begin_comment
comment|/*  * The coefficients below properly computed luminance for monitors  * having phosphors that were contemporary at the introduction of NTSC  * television in 1953. They are still appropriate for computing video  * luma. However, these coefficients do not accurately compute  * luminance for contemporary monitors. The use of these definitions  * is deprecated.  */
end_comment

begin_define
DECL|macro|GIMP_RGB_INTENSITY_RED
define|#
directive|define
name|GIMP_RGB_INTENSITY_RED
value|(0.30)
end_define

begin_define
DECL|macro|GIMP_RGB_INTENSITY_GREEN
define|#
directive|define
name|GIMP_RGB_INTENSITY_GREEN
value|(0.59)
end_define

begin_define
DECL|macro|GIMP_RGB_INTENSITY_BLUE
define|#
directive|define
name|GIMP_RGB_INTENSITY_BLUE
value|(0.11)
end_define

begin_define
DECL|macro|GIMP_RGB_INTENSITY (r,g,b)
define|#
directive|define
name|GIMP_RGB_INTENSITY
parameter_list|(
name|r
parameter_list|,
name|g
parameter_list|,
name|b
parameter_list|)
value|((r) * GIMP_RGB_INTENSITY_RED   + \                                    (g) * GIMP_RGB_INTENSITY_GREEN + \                                    (b) * GIMP_RGB_INTENSITY_BLUE)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_RGB_H__ */
end_comment

end_unit

