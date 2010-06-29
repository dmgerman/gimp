begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_TYPES_H__
define|#
directive|define
name|__GIMP_COLOR_TYPES_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_typedef
DECL|typedef|GimpColorManaged
typedef|typedef
name|struct
name|_GimpColorManaged
name|GimpColorManaged
typedef|;
end_typedef

begin_comment
DECL|typedef|GimpColorManaged
comment|/* dummy typedef */
end_comment

begin_comment
comment|/*  usually we don't keep the structure definitions in the types file  *  but GimpRGB appears in too many header files...  */
end_comment

begin_typedef
DECL|typedef|GimpRGB
typedef|typedef
name|struct
name|_GimpRGB
name|GimpRGB
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHSV
typedef|typedef
name|struct
name|_GimpHSV
name|GimpHSV
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHSL
typedef|typedef
name|struct
name|_GimpHSL
name|GimpHSL
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCMYK
typedef|typedef
name|struct
name|_GimpCMYK
name|GimpCMYK
typedef|;
end_typedef

begin_comment
comment|/**  * GimpRGB:  * @r: the red component  * @g: the green component  * @b: the blue component  * @a: the alpha component  *  * Used to keep RGB and RGBA colors. All components are in a range of  * [0.0..1.0].  **/
end_comment

begin_struct
DECL|struct|_GimpRGB
struct|struct
name|_GimpRGB
block|{
DECL|member|r
DECL|member|g
DECL|member|b
DECL|member|a
name|gdouble
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/**  * GimpHSV:  * @h: the hue component  * @s: the saturation component  * @v: the value component  * @a: the alpha component  *  * Used to keep HSV and HSVA colors. All components are in a range of  * [0.0..1.0].  **/
end_comment

begin_struct
DECL|struct|_GimpHSV
struct|struct
name|_GimpHSV
block|{
DECL|member|h
DECL|member|s
DECL|member|v
DECL|member|a
name|gdouble
name|h
decl_stmt|,
name|s
decl_stmt|,
name|v
decl_stmt|,
name|a
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/**  * GimpHSL:  * @h: the hue component  * @s: the saturation component  * @l: the lightness component  * @a: the alpha component  *  * Used to keep HSL and HSLA colors. All components are in a range of  * [0.0..1.0].  **/
end_comment

begin_struct
DECL|struct|_GimpHSL
struct|struct
name|_GimpHSL
block|{
DECL|member|h
DECL|member|s
DECL|member|l
DECL|member|a
name|gdouble
name|h
decl_stmt|,
name|s
decl_stmt|,
name|l
decl_stmt|,
name|a
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/**  * GimpCMYK:  * @c: the cyan component  * @m: the magenta component  * @y: the yellow component  * @k: the black component  * @a: the alpha component  *  * Used to keep CMYK and CMYKA colors. All components are in a range  * of [0.0..1.0]. An alpha value is somewhat useless in the CMYK  * colorspace, but we keep one around anyway so color conversions  * going to CMYK and back can preserve alpha.  **/
end_comment

begin_struct
DECL|struct|_GimpCMYK
struct|struct
name|_GimpCMYK
block|{
DECL|member|c
DECL|member|m
DECL|member|y
DECL|member|k
DECL|member|a
name|gdouble
name|c
decl_stmt|,
name|m
decl_stmt|,
name|y
decl_stmt|,
name|k
decl_stmt|,
name|a
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpRenderFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpRenderFunc
function_decl|)
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpPutPixelFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpPutPixelFunc
function_decl|)
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpProgressFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpProgressFunc
function_decl|)
parameter_list|(
name|gint
name|min
parameter_list|,
name|gint
name|max
parameter_list|,
name|gint
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COLOR_TYPES_H__ */
end_comment

end_unit

