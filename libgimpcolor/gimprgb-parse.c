begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimprgb-parse.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * Some of the code in here was inspired and partly copied from pango  * and librsvg.  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"gimpcolortypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorspace.h"
end_include

begin_include
include|#
directive|include
file|"gimprgb.h"
end_include

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_rgb_parse_strip
parameter_list|(
specifier|const
name|gchar
modifier|*
name|str
parameter_list|,
name|gint
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_rgb_parse_name_internal
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_rgb_parse_hex_internal
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|hex
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_rgb_parse_css_internal
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|css
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_rgba_parse_css_internal
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|css
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_rgb_parse_name:  * @rgb:  a #GimpRGB struct used to return the parsed color  * @name: a color name (in UTF-8 encoding)  * @len:  the length of @name, in bytes. or -1 if @name is nul-terminated  *  * Attempts to parse a color name. This function accepts RGB hex  * values or<ulink url="http://www.w3.org/TR/SVG/types.html">SVG 1.0  * color keywords</ulink>.  The format of an RGB value in hexadecimal  * notation is a '#' immediately followed by either three or six  * hexadecimal characters.  *  * This funcion does not touch the alpha component of @rgb.  *  * Return value: %TRUE if @name was parsed successfully and @rgb has been  *               set, %FALSE otherwise  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_rgb_parse_name (GimpRGB * rgb,const gchar * name,gint len)
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
block|{
name|gchar
modifier|*
name|tmp
decl_stmt|;
name|gboolean
name|result
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|gimp_rgb_parse_strip
argument_list|(
name|name
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|result
operator|=
name|gimp_rgb_parse_name_internal
argument_list|(
name|rgb
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_rgb_parse_hex:  * @rgb: a #GimpRGB struct used to return the parsed color  * @hex: a string describing a color in hexadecimal notation  * @len: the length of @hex, in bytes. or -1 if @hex is nul-terminated  *  * Attempts to parse a string describing a color in RGB value in  * hexadecimal notation (optionally prefixed with a '#'.  *  * This funcion does not touch the alpha component of @rgb.  *  * Return value: %TRUE if @hex was parsed successfully and @rgb has been  *               set, %FALSE otherwise  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_rgb_parse_hex (GimpRGB * rgb,const gchar * hex,gint len)
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
block|{
name|gchar
modifier|*
name|tmp
decl_stmt|;
name|gboolean
name|result
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|hex
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|gimp_rgb_parse_strip
argument_list|(
name|hex
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|result
operator|=
name|gimp_rgb_parse_hex_internal
argument_list|(
name|rgb
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_rgb_parse_css:  * @rgb: a #GimpRGB struct used to return the parsed color  * @css: a string describing a color in CSS notation  * @len: the length of @hex, in bytes. or -1 if @hex is nul-terminated  *  * Attempts to parse a string describing a color in RGB value in CSS  * notation. This can be either a numerical representation  * (<code>rgb(255,0,0)</code> or<code>rgb(100%,0%,0%)</code>) or  * a hexadecimal notation as parsed by gimp_rgb_parse_hex()  * (<code>##ff0000</code>) or a color name as parsed by  * gimp_rgb_parse_name() (<code>red</code>).  *  * This funcion does not touch the alpha component of @rgb.  *  * Return value: %TRUE if @css was parsed successfully and @rgb has been  *               set, %FALSE otherwise  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_rgb_parse_css (GimpRGB * rgb,const gchar * css,gint len)
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
block|{
name|gchar
modifier|*
name|tmp
decl_stmt|;
name|gboolean
name|result
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|css
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|gimp_rgb_parse_strip
argument_list|(
name|css
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|result
operator|=
name|gimp_rgb_parse_css_internal
argument_list|(
name|rgb
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_rgba_parse_css:  * @rgba: a #GimpRGB struct used to return the parsed color  * @css: a string describing a color in CSS notation  * @len: the length of @hex, in bytes. or -1 if @hex is nul-terminated  *  * Similar to gimp_rgb_parse_css() but handles RGB colors with alpha  * channel in the numerical CSS notation (<code>rgba(255,0,0,255)</code>  * or<code>rgba(100%,0%,0%,1000%)</code>).  *  * It doesn't handle the hexadecimal notation or color names because  * they leave the alpha channel unspecified.  *  * Return value: %TRUE if @css was parsed successfully and @rgb has been  *               set, %FALSE otherwise  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_rgba_parse_css (GimpRGB * rgba,const gchar * css,gint len)
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
block|{
name|gchar
modifier|*
name|tmp
decl_stmt|;
name|gboolean
name|result
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rgba
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|css
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|len
operator|<
literal|0
condition|)
name|len
operator|=
name|strlen
argument_list|(
name|css
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|gimp_rgb_parse_strip
argument_list|(
name|css
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|tmp
argument_list|,
literal|"transparent"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gimp_rgba_set
argument_list|(
name|rgba
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|result
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|result
operator|=
name|gimp_rgba_parse_css_internal
argument_list|(
name|rgba
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_rgb_parse_strip (const gchar * str,gint len)
name|gimp_rgb_parse_strip
parameter_list|(
specifier|const
name|gchar
modifier|*
name|str
parameter_list|,
name|gint
name|len
parameter_list|)
block|{
name|gchar
modifier|*
name|result
decl_stmt|;
while|while
condition|(
name|len
operator|>
literal|0
operator|&&
name|g_ascii_isspace
argument_list|(
operator|*
name|str
argument_list|)
condition|)
block|{
name|str
operator|++
expr_stmt|;
name|len
operator|--
expr_stmt|;
block|}
if|if
condition|(
name|len
operator|<
literal|0
condition|)
block|{
while|while
condition|(
name|g_ascii_isspace
argument_list|(
operator|*
name|str
argument_list|)
condition|)
name|str
operator|++
expr_stmt|;
name|len
operator|=
name|strlen
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
while|while
condition|(
name|len
operator|>
literal|0
operator|&&
name|g_ascii_isspace
argument_list|(
name|str
index|[
name|len
operator|-
literal|1
index|]
argument_list|)
condition|)
name|len
operator|--
expr_stmt|;
name|result
operator|=
name|g_malloc
argument_list|(
name|len
operator|+
literal|1
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|result
argument_list|,
name|str
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|result
index|[
name|len
index|]
operator|=
literal|'\0'
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2ad790e60108
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|r
specifier|const
name|guchar
name|r
decl_stmt|;
DECL|member|g
specifier|const
name|guchar
name|g
decl_stmt|;
DECL|member|b
specifier|const
name|guchar
name|b
decl_stmt|;
DECL|typedef|ColorEntry
block|}
name|ColorEntry
typedef|;
end_typedef

begin_function
specifier|static
name|gint
DECL|function|gimp_rgb_color_entry_compare (gconstpointer a,gconstpointer b)
name|gimp_rgb_color_entry_compare
parameter_list|(
name|gconstpointer
name|a
parameter_list|,
name|gconstpointer
name|b
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
name|a
decl_stmt|;
specifier|const
name|ColorEntry
modifier|*
name|entry
init|=
name|b
decl_stmt|;
return|return
name|g_ascii_strcasecmp
argument_list|(
name|name
argument_list|,
name|entry
operator|->
name|name
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_rgb_parse_name_internal (GimpRGB * rgb,const gchar * name)
name|gimp_rgb_parse_name_internal
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
specifier|static
specifier|const
name|ColorEntry
name|colors
index|[]
init|=
block|{
block|{
literal|"aliceblue"
block|,
literal|240
block|,
literal|248
block|,
literal|255
block|}
block|,
block|{
literal|"antiquewhite"
block|,
literal|250
block|,
literal|235
block|,
literal|215
block|}
block|,
block|{
literal|"aqua"
block|,
literal|0
block|,
literal|255
block|,
literal|255
block|}
block|,
block|{
literal|"aquamarine"
block|,
literal|127
block|,
literal|255
block|,
literal|212
block|}
block|,
block|{
literal|"azure"
block|,
literal|240
block|,
literal|255
block|,
literal|255
block|}
block|,
block|{
literal|"beige"
block|,
literal|245
block|,
literal|245
block|,
literal|220
block|}
block|,
block|{
literal|"bisque"
block|,
literal|255
block|,
literal|228
block|,
literal|196
block|}
block|,
block|{
literal|"black"
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
block|,
block|{
literal|"blanchedalmond"
block|,
literal|255
block|,
literal|235
block|,
literal|205
block|}
block|,
block|{
literal|"blue"
block|,
literal|0
block|,
literal|0
block|,
literal|255
block|}
block|,
block|{
literal|"blueviolet"
block|,
literal|138
block|,
literal|43
block|,
literal|226
block|}
block|,
block|{
literal|"brown"
block|,
literal|165
block|,
literal|42
block|,
literal|42
block|}
block|,
block|{
literal|"burlywood"
block|,
literal|222
block|,
literal|184
block|,
literal|135
block|}
block|,
block|{
literal|"cadetblue"
block|,
literal|95
block|,
literal|158
block|,
literal|160
block|}
block|,
block|{
literal|"chartreuse"
block|,
literal|127
block|,
literal|255
block|,
literal|0
block|}
block|,
block|{
literal|"chocolate"
block|,
literal|210
block|,
literal|105
block|,
literal|30
block|}
block|,
block|{
literal|"coral"
block|,
literal|255
block|,
literal|127
block|,
literal|80
block|}
block|,
block|{
literal|"cornflowerblue"
block|,
literal|100
block|,
literal|149
block|,
literal|237
block|}
block|,
block|{
literal|"cornsilk"
block|,
literal|255
block|,
literal|248
block|,
literal|220
block|}
block|,
block|{
literal|"crimson"
block|,
literal|220
block|,
literal|20
block|,
literal|60
block|}
block|,
block|{
literal|"cyan"
block|,
literal|0
block|,
literal|255
block|,
literal|255
block|}
block|,
block|{
literal|"darkblue"
block|,
literal|0
block|,
literal|0
block|,
literal|139
block|}
block|,
block|{
literal|"darkcyan"
block|,
literal|0
block|,
literal|139
block|,
literal|139
block|}
block|,
block|{
literal|"darkgoldenrod"
block|,
literal|184
block|,
literal|132
block|,
literal|11
block|}
block|,
block|{
literal|"darkgray"
block|,
literal|169
block|,
literal|169
block|,
literal|169
block|}
block|,
block|{
literal|"darkgreen"
block|,
literal|0
block|,
literal|100
block|,
literal|0
block|}
block|,
block|{
literal|"darkgrey"
block|,
literal|169
block|,
literal|169
block|,
literal|169
block|}
block|,
block|{
literal|"darkkhaki"
block|,
literal|189
block|,
literal|183
block|,
literal|107
block|}
block|,
block|{
literal|"darkmagenta"
block|,
literal|139
block|,
literal|0
block|,
literal|139
block|}
block|,
block|{
literal|"darkolivegreen"
block|,
literal|85
block|,
literal|107
block|,
literal|47
block|}
block|,
block|{
literal|"darkorange"
block|,
literal|255
block|,
literal|140
block|,
literal|0
block|}
block|,
block|{
literal|"darkorchid"
block|,
literal|153
block|,
literal|50
block|,
literal|204
block|}
block|,
block|{
literal|"darkred"
block|,
literal|139
block|,
literal|0
block|,
literal|0
block|}
block|,
block|{
literal|"darksalmon"
block|,
literal|233
block|,
literal|150
block|,
literal|122
block|}
block|,
block|{
literal|"darkseagreen"
block|,
literal|143
block|,
literal|188
block|,
literal|143
block|}
block|,
block|{
literal|"darkslateblue"
block|,
literal|72
block|,
literal|61
block|,
literal|139
block|}
block|,
block|{
literal|"darkslategray"
block|,
literal|47
block|,
literal|79
block|,
literal|79
block|}
block|,
block|{
literal|"darkslategrey"
block|,
literal|47
block|,
literal|79
block|,
literal|79
block|}
block|,
block|{
literal|"darkturquoise"
block|,
literal|0
block|,
literal|206
block|,
literal|209
block|}
block|,
block|{
literal|"darkviolet"
block|,
literal|148
block|,
literal|0
block|,
literal|211
block|}
block|,
block|{
literal|"deeppink"
block|,
literal|255
block|,
literal|20
block|,
literal|147
block|}
block|,
block|{
literal|"deepskyblue"
block|,
literal|0
block|,
literal|191
block|,
literal|255
block|}
block|,
block|{
literal|"dimgray"
block|,
literal|105
block|,
literal|105
block|,
literal|105
block|}
block|,
block|{
literal|"dimgrey"
block|,
literal|105
block|,
literal|105
block|,
literal|105
block|}
block|,
block|{
literal|"dodgerblue"
block|,
literal|30
block|,
literal|144
block|,
literal|255
block|}
block|,
block|{
literal|"firebrick"
block|,
literal|178
block|,
literal|34
block|,
literal|34
block|}
block|,
block|{
literal|"floralwhite"
block|,
literal|255
block|,
literal|255
block|,
literal|240
block|}
block|,
block|{
literal|"forestgreen"
block|,
literal|34
block|,
literal|139
block|,
literal|34
block|}
block|,
block|{
literal|"fuchsia"
block|,
literal|255
block|,
literal|0
block|,
literal|255
block|}
block|,
block|{
literal|"gainsboro"
block|,
literal|220
block|,
literal|220
block|,
literal|220
block|}
block|,
block|{
literal|"ghostwhite"
block|,
literal|248
block|,
literal|248
block|,
literal|255
block|}
block|,
block|{
literal|"gold"
block|,
literal|255
block|,
literal|215
block|,
literal|0
block|}
block|,
block|{
literal|"goldenrod"
block|,
literal|218
block|,
literal|165
block|,
literal|32
block|}
block|,
block|{
literal|"gray"
block|,
literal|128
block|,
literal|128
block|,
literal|128
block|}
block|,
block|{
literal|"green"
block|,
literal|0
block|,
literal|128
block|,
literal|0
block|}
block|,
block|{
literal|"greenyellow"
block|,
literal|173
block|,
literal|255
block|,
literal|47
block|}
block|,
block|{
literal|"grey"
block|,
literal|128
block|,
literal|128
block|,
literal|128
block|}
block|,
block|{
literal|"honeydew"
block|,
literal|240
block|,
literal|255
block|,
literal|240
block|}
block|,
block|{
literal|"hotpink"
block|,
literal|255
block|,
literal|105
block|,
literal|180
block|}
block|,
block|{
literal|"indianred"
block|,
literal|205
block|,
literal|92
block|,
literal|92
block|}
block|,
block|{
literal|"indigo"
block|,
literal|75
block|,
literal|0
block|,
literal|130
block|}
block|,
block|{
literal|"ivory"
block|,
literal|255
block|,
literal|255
block|,
literal|240
block|}
block|,
block|{
literal|"khaki"
block|,
literal|240
block|,
literal|230
block|,
literal|140
block|}
block|,
block|{
literal|"lavender"
block|,
literal|230
block|,
literal|230
block|,
literal|250
block|}
block|,
block|{
literal|"lavenderblush"
block|,
literal|255
block|,
literal|240
block|,
literal|245
block|}
block|,
block|{
literal|"lawngreen"
block|,
literal|124
block|,
literal|252
block|,
literal|0
block|}
block|,
block|{
literal|"lemonchiffon"
block|,
literal|255
block|,
literal|250
block|,
literal|205
block|}
block|,
block|{
literal|"lightblue"
block|,
literal|173
block|,
literal|216
block|,
literal|230
block|}
block|,
block|{
literal|"lightcoral"
block|,
literal|240
block|,
literal|128
block|,
literal|128
block|}
block|,
block|{
literal|"lightcyan"
block|,
literal|224
block|,
literal|255
block|,
literal|255
block|}
block|,
block|{
literal|"lightgoldenrodyellow"
block|,
literal|250
block|,
literal|250
block|,
literal|210
block|}
block|,
block|{
literal|"lightgray"
block|,
literal|211
block|,
literal|211
block|,
literal|211
block|}
block|,
block|{
literal|"lightgreen"
block|,
literal|144
block|,
literal|238
block|,
literal|144
block|}
block|,
block|{
literal|"lightgrey"
block|,
literal|211
block|,
literal|211
block|,
literal|211
block|}
block|,
block|{
literal|"lightpink"
block|,
literal|255
block|,
literal|182
block|,
literal|193
block|}
block|,
block|{
literal|"lightsalmon"
block|,
literal|255
block|,
literal|160
block|,
literal|122
block|}
block|,
block|{
literal|"lightseagreen"
block|,
literal|32
block|,
literal|178
block|,
literal|170
block|}
block|,
block|{
literal|"lightskyblue"
block|,
literal|135
block|,
literal|206
block|,
literal|250
block|}
block|,
block|{
literal|"lightslategray"
block|,
literal|119
block|,
literal|136
block|,
literal|153
block|}
block|,
block|{
literal|"lightslategrey"
block|,
literal|119
block|,
literal|136
block|,
literal|153
block|}
block|,
block|{
literal|"lightsteelblue"
block|,
literal|176
block|,
literal|196
block|,
literal|222
block|}
block|,
block|{
literal|"lightyellow"
block|,
literal|255
block|,
literal|255
block|,
literal|224
block|}
block|,
block|{
literal|"lime"
block|,
literal|0
block|,
literal|255
block|,
literal|0
block|}
block|,
block|{
literal|"limegreen"
block|,
literal|50
block|,
literal|205
block|,
literal|50
block|}
block|,
block|{
literal|"linen"
block|,
literal|250
block|,
literal|240
block|,
literal|230
block|}
block|,
block|{
literal|"magenta"
block|,
literal|255
block|,
literal|0
block|,
literal|255
block|}
block|,
block|{
literal|"maroon"
block|,
literal|128
block|,
literal|0
block|,
literal|0
block|}
block|,
block|{
literal|"mediumaquamarine"
block|,
literal|102
block|,
literal|205
block|,
literal|170
block|}
block|,
block|{
literal|"mediumblue"
block|,
literal|0
block|,
literal|0
block|,
literal|205
block|}
block|,
block|{
literal|"mediumorchid"
block|,
literal|186
block|,
literal|85
block|,
literal|211
block|}
block|,
block|{
literal|"mediumpurple"
block|,
literal|147
block|,
literal|112
block|,
literal|219
block|}
block|,
block|{
literal|"mediumseagreen"
block|,
literal|60
block|,
literal|179
block|,
literal|113
block|}
block|,
block|{
literal|"mediumslateblue"
block|,
literal|123
block|,
literal|104
block|,
literal|238
block|}
block|,
block|{
literal|"mediumspringgreen"
block|,
literal|0
block|,
literal|250
block|,
literal|154
block|}
block|,
block|{
literal|"mediumturquoise"
block|,
literal|72
block|,
literal|209
block|,
literal|204
block|}
block|,
block|{
literal|"mediumvioletred"
block|,
literal|199
block|,
literal|21
block|,
literal|133
block|}
block|,
block|{
literal|"midnightblue"
block|,
literal|25
block|,
literal|25
block|,
literal|112
block|}
block|,
block|{
literal|"mintcream"
block|,
literal|245
block|,
literal|255
block|,
literal|250
block|}
block|,
block|{
literal|"mistyrose"
block|,
literal|255
block|,
literal|228
block|,
literal|225
block|}
block|,
block|{
literal|"moccasin"
block|,
literal|255
block|,
literal|228
block|,
literal|181
block|}
block|,
block|{
literal|"navajowhite"
block|,
literal|255
block|,
literal|222
block|,
literal|173
block|}
block|,
block|{
literal|"navy"
block|,
literal|0
block|,
literal|0
block|,
literal|128
block|}
block|,
block|{
literal|"oldlace"
block|,
literal|253
block|,
literal|245
block|,
literal|230
block|}
block|,
block|{
literal|"olive"
block|,
literal|128
block|,
literal|128
block|,
literal|0
block|}
block|,
block|{
literal|"olivedrab"
block|,
literal|107
block|,
literal|142
block|,
literal|35
block|}
block|,
block|{
literal|"orange"
block|,
literal|255
block|,
literal|165
block|,
literal|0
block|}
block|,
block|{
literal|"orangered"
block|,
literal|255
block|,
literal|69
block|,
literal|0
block|}
block|,
block|{
literal|"orchid"
block|,
literal|218
block|,
literal|112
block|,
literal|214
block|}
block|,
block|{
literal|"palegoldenrod"
block|,
literal|238
block|,
literal|232
block|,
literal|170
block|}
block|,
block|{
literal|"palegreen"
block|,
literal|152
block|,
literal|251
block|,
literal|152
block|}
block|,
block|{
literal|"paleturquoise"
block|,
literal|175
block|,
literal|238
block|,
literal|238
block|}
block|,
block|{
literal|"palevioletred"
block|,
literal|219
block|,
literal|112
block|,
literal|147
block|}
block|,
block|{
literal|"papayawhip"
block|,
literal|255
block|,
literal|239
block|,
literal|213
block|}
block|,
block|{
literal|"peachpuff"
block|,
literal|255
block|,
literal|218
block|,
literal|185
block|}
block|,
block|{
literal|"peru"
block|,
literal|205
block|,
literal|133
block|,
literal|63
block|}
block|,
block|{
literal|"pink"
block|,
literal|255
block|,
literal|192
block|,
literal|203
block|}
block|,
block|{
literal|"plum"
block|,
literal|221
block|,
literal|160
block|,
literal|203
block|}
block|,
block|{
literal|"powderblue"
block|,
literal|176
block|,
literal|224
block|,
literal|230
block|}
block|,
block|{
literal|"purple"
block|,
literal|128
block|,
literal|0
block|,
literal|128
block|}
block|,
block|{
literal|"red"
block|,
literal|255
block|,
literal|0
block|,
literal|0
block|}
block|,
block|{
literal|"rosybrown"
block|,
literal|188
block|,
literal|143
block|,
literal|143
block|}
block|,
block|{
literal|"royalblue"
block|,
literal|65
block|,
literal|105
block|,
literal|225
block|}
block|,
block|{
literal|"saddlebrown"
block|,
literal|139
block|,
literal|69
block|,
literal|19
block|}
block|,
block|{
literal|"salmon"
block|,
literal|250
block|,
literal|128
block|,
literal|114
block|}
block|,
block|{
literal|"sandybrown"
block|,
literal|244
block|,
literal|164
block|,
literal|96
block|}
block|,
block|{
literal|"seagreen"
block|,
literal|46
block|,
literal|139
block|,
literal|87
block|}
block|,
block|{
literal|"seashell"
block|,
literal|255
block|,
literal|245
block|,
literal|238
block|}
block|,
block|{
literal|"sienna"
block|,
literal|160
block|,
literal|82
block|,
literal|45
block|}
block|,
block|{
literal|"silver"
block|,
literal|192
block|,
literal|192
block|,
literal|192
block|}
block|,
block|{
literal|"skyblue"
block|,
literal|135
block|,
literal|206
block|,
literal|235
block|}
block|,
block|{
literal|"slateblue"
block|,
literal|106
block|,
literal|90
block|,
literal|205
block|}
block|,
block|{
literal|"slategray"
block|,
literal|119
block|,
literal|128
block|,
literal|144
block|}
block|,
block|{
literal|"slategrey"
block|,
literal|119
block|,
literal|128
block|,
literal|144
block|}
block|,
block|{
literal|"snow"
block|,
literal|255
block|,
literal|255
block|,
literal|250
block|}
block|,
block|{
literal|"springgreen"
block|,
literal|0
block|,
literal|255
block|,
literal|127
block|}
block|,
block|{
literal|"steelblue"
block|,
literal|70
block|,
literal|130
block|,
literal|180
block|}
block|,
block|{
literal|"tan"
block|,
literal|210
block|,
literal|180
block|,
literal|140
block|}
block|,
block|{
literal|"teal"
block|,
literal|0
block|,
literal|128
block|,
literal|128
block|}
block|,
block|{
literal|"thistle"
block|,
literal|216
block|,
literal|191
block|,
literal|216
block|}
block|,
block|{
literal|"tomato"
block|,
literal|255
block|,
literal|99
block|,
literal|71
block|}
block|,
block|{
literal|"turquoise"
block|,
literal|64
block|,
literal|224
block|,
literal|208
block|}
block|,
block|{
literal|"violet"
block|,
literal|238
block|,
literal|130
block|,
literal|238
block|}
block|,
block|{
literal|"wheat"
block|,
literal|245
block|,
literal|222
block|,
literal|179
block|}
block|,
block|{
literal|"white"
block|,
literal|255
block|,
literal|255
block|,
literal|255
block|}
block|,
block|{
literal|"whitesmoke"
block|,
literal|245
block|,
literal|245
block|,
literal|245
block|}
block|,
block|{
literal|"yellow"
block|,
literal|255
block|,
literal|255
block|,
literal|0
block|}
block|,
block|{
literal|"yellowgreen"
block|,
literal|154
block|,
literal|205
block|,
literal|50
block|}
block|}
decl_stmt|;
name|ColorEntry
modifier|*
name|entry
init|=
name|bsearch
argument_list|(
name|name
argument_list|,
name|colors
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|colors
argument_list|)
argument_list|,
sizeof|sizeof
argument_list|(
name|ColorEntry
argument_list|)
argument_list|,
name|gimp_rgb_color_entry_compare
argument_list|)
decl_stmt|;
if|if
condition|(
name|entry
condition|)
block|{
name|gimp_rgb_set_uchar
argument_list|(
name|rgb
argument_list|,
name|entry
operator|->
name|r
argument_list|,
name|entry
operator|->
name|g
argument_list|,
name|entry
operator|->
name|b
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_rgb_parse_hex_component (const gchar * hex,gint len,gdouble * value)
name|gimp_rgb_parse_hex_component
parameter_list|(
specifier|const
name|gchar
modifier|*
name|hex
parameter_list|,
name|gint
name|len
parameter_list|,
name|gdouble
modifier|*
name|value
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|guint
name|c
init|=
literal|0
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|len
condition|;
name|i
operator|++
operator|,
name|hex
operator|++
control|)
block|{
if|if
condition|(
operator|!
operator|*
name|hex
operator|||
operator|!
name|g_ascii_isxdigit
argument_list|(
operator|*
name|hex
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|c
operator|=
operator|(
name|c
operator|<<
literal|4
operator|)
operator||
name|g_ascii_xdigit_value
argument_list|(
operator|*
name|hex
argument_list|)
expr_stmt|;
block|}
switch|switch
condition|(
name|len
condition|)
block|{
case|case
literal|1
case|:
operator|*
name|value
operator|=
operator|(
name|gdouble
operator|)
name|c
operator|/
literal|15.0
expr_stmt|;
break|break;
case|case
literal|2
case|:
operator|*
name|value
operator|=
operator|(
name|gdouble
operator|)
name|c
operator|/
literal|255.0
expr_stmt|;
break|break;
case|case
literal|3
case|:
operator|*
name|value
operator|=
operator|(
name|gdouble
operator|)
name|c
operator|/
literal|4095.0
expr_stmt|;
break|break;
case|case
literal|4
case|:
operator|*
name|value
operator|=
operator|(
name|gdouble
operator|)
name|c
operator|/
literal|65535.0
expr_stmt|;
break|break;
default|default:
name|g_return_val_if_reached
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_rgb_parse_hex_internal (GimpRGB * rgb,const gchar * hex)
name|gimp_rgb_parse_hex_internal
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|hex
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gsize
name|len
decl_stmt|;
name|gdouble
name|val
index|[
literal|3
index|]
decl_stmt|;
if|if
condition|(
name|hex
index|[
literal|0
index|]
operator|==
literal|'#'
condition|)
name|hex
operator|++
expr_stmt|;
name|len
operator|=
name|strlen
argument_list|(
name|hex
argument_list|)
expr_stmt|;
if|if
condition|(
name|len
operator|%
literal|3
operator|||
name|len
operator|<
literal|3
operator|||
name|len
operator|>
literal|12
condition|)
return|return
name|FALSE
return|;
name|len
operator|/=
literal|3
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
operator|,
name|hex
operator|+=
name|len
control|)
block|{
if|if
condition|(
operator|!
name|gimp_rgb_parse_hex_component
argument_list|(
name|hex
argument_list|,
name|len
argument_list|,
name|val
operator|+
name|i
argument_list|)
condition|)
return|return
name|FALSE
return|;
block|}
name|gimp_rgb_set
argument_list|(
name|rgb
argument_list|,
name|val
index|[
literal|0
index|]
argument_list|,
name|val
index|[
literal|1
index|]
argument_list|,
name|val
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_rgb_parse_css_numeric (GimpRGB * rgb,const gchar * css)
name|gimp_rgb_parse_css_numeric
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|css
parameter_list|)
block|{
name|gdouble
name|values
index|[
literal|4
index|]
decl_stmt|;
name|gboolean
name|alpha
decl_stmt|;
name|gboolean
name|hsl
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|css
index|[
literal|0
index|]
operator|==
literal|'r'
operator|&&
name|css
index|[
literal|1
index|]
operator|==
literal|'g'
operator|&&
name|css
index|[
literal|2
index|]
operator|==
literal|'b'
condition|)
name|hsl
operator|=
name|FALSE
expr_stmt|;
elseif|else
if|if
condition|(
name|css
index|[
literal|0
index|]
operator|==
literal|'h'
operator|&&
name|css
index|[
literal|1
index|]
operator|==
literal|'s'
operator|&&
name|css
index|[
literal|2
index|]
operator|==
literal|'l'
condition|)
name|hsl
operator|=
name|TRUE
expr_stmt|;
else|else
return|return
name|FALSE
return|;
if|if
condition|(
name|css
index|[
literal|3
index|]
operator|==
literal|'a'
operator|&&
name|css
index|[
literal|4
index|]
operator|==
literal|'('
condition|)
name|alpha
operator|=
name|TRUE
expr_stmt|;
elseif|else
if|if
condition|(
name|css
index|[
literal|3
index|]
operator|==
literal|'('
condition|)
name|alpha
operator|=
name|FALSE
expr_stmt|;
else|else
return|return
name|FALSE
return|;
name|css
operator|+=
operator|(
name|alpha
condition|?
literal|5
else|:
literal|4
operator|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|(
name|alpha
condition|?
literal|4
else|:
literal|3
operator|)
condition|;
name|i
operator|++
control|)
block|{
specifier|const
name|gchar
modifier|*
name|end
init|=
name|css
decl_stmt|;
while|while
condition|(
operator|*
name|end
operator|&&
operator|*
name|end
operator|!=
literal|','
operator|&&
operator|*
name|end
operator|!=
literal|'%'
operator|&&
operator|*
name|end
operator|!=
literal|')'
condition|)
name|end
operator|++
expr_stmt|;
if|if
condition|(
name|i
operator|==
literal|3
operator|||
operator|*
name|end
operator|==
literal|'%'
condition|)
block|{
name|values
index|[
name|i
index|]
operator|=
name|g_ascii_strtod
argument_list|(
name|css
argument_list|,
operator|(
name|gchar
operator|*
operator|*
operator|)
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|errno
operator|==
name|ERANGE
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
operator|*
name|end
operator|==
literal|'%'
condition|)
block|{
name|end
operator|++
expr_stmt|;
name|values
index|[
name|i
index|]
operator|/=
literal|100.0
expr_stmt|;
block|}
block|}
else|else
block|{
name|glong
name|value
init|=
name|strtol
argument_list|(
name|css
argument_list|,
operator|(
name|gchar
operator|*
operator|*
operator|)
operator|&
name|end
argument_list|,
literal|10
argument_list|)
decl_stmt|;
if|if
condition|(
name|errno
operator|==
name|ERANGE
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|hsl
condition|)
name|values
index|[
name|i
index|]
operator|=
name|value
operator|/
operator|(
name|i
operator|==
literal|0
condition|?
literal|360.0
else|:
literal|100.0
operator|)
expr_stmt|;
else|else
name|values
index|[
name|i
index|]
operator|=
name|value
operator|/
literal|255.0
expr_stmt|;
block|}
while|while
condition|(
operator|*
name|end
operator|==
literal|','
operator|||
name|g_ascii_isspace
argument_list|(
operator|*
name|end
argument_list|)
condition|)
name|end
operator|++
expr_stmt|;
name|css
operator|=
name|end
expr_stmt|;
block|}
if|if
condition|(
operator|*
name|css
operator|!=
literal|')'
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|alpha
condition|)
name|gimp_rgba_set
argument_list|(
name|rgb
argument_list|,
name|values
index|[
literal|0
index|]
argument_list|,
name|values
index|[
literal|1
index|]
argument_list|,
name|values
index|[
literal|2
index|]
argument_list|,
name|values
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
else|else
name|gimp_rgb_set
argument_list|(
name|rgb
argument_list|,
name|values
index|[
literal|0
index|]
argument_list|,
name|values
index|[
literal|1
index|]
argument_list|,
name|values
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|gimp_rgb_clamp
argument_list|(
name|rgb
argument_list|)
expr_stmt|;
if|if
condition|(
name|hsl
condition|)
block|{
name|GimpHSL
name|tmp
init|=
operator|(
operator|*
operator|(
operator|(
name|GimpHSL
operator|*
operator|)
name|rgb
operator|)
operator|)
decl_stmt|;
name|gimp_hsl_to_rgb
argument_list|(
operator|&
name|tmp
argument_list|,
name|rgb
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_rgb_parse_css_internal (GimpRGB * rgb,const gchar * css)
name|gimp_rgb_parse_css_internal
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|css
parameter_list|)
block|{
if|if
condition|(
name|css
index|[
literal|0
index|]
operator|==
literal|'#'
condition|)
block|{
return|return
name|gimp_rgb_parse_hex_internal
argument_list|(
name|rgb
argument_list|,
name|css
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|strncmp
argument_list|(
name|css
argument_list|,
literal|"rgb("
argument_list|,
literal|4
argument_list|)
operator|==
literal|0
operator|||
name|strncmp
argument_list|(
name|css
argument_list|,
literal|"hsl("
argument_list|,
literal|4
argument_list|)
operator|==
literal|0
condition|)
block|{
return|return
name|gimp_rgb_parse_css_numeric
argument_list|(
name|rgb
argument_list|,
name|css
argument_list|)
return|;
block|}
else|else
block|{
return|return
name|gimp_rgb_parse_name_internal
argument_list|(
name|rgb
argument_list|,
name|css
argument_list|)
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_rgba_parse_css_internal (GimpRGB * rgba,const gchar * css)
name|gimp_rgba_parse_css_internal
parameter_list|(
name|GimpRGB
modifier|*
name|rgba
parameter_list|,
specifier|const
name|gchar
modifier|*
name|css
parameter_list|)
block|{
if|if
condition|(
name|strncmp
argument_list|(
name|css
argument_list|,
literal|"rgba("
argument_list|,
literal|5
argument_list|)
operator|!=
literal|0
operator|&&
name|strncmp
argument_list|(
name|css
argument_list|,
literal|"hsla("
argument_list|,
literal|5
argument_list|)
operator|!=
literal|0
condition|)
return|return
name|FALSE
return|;
return|return
name|gimp_rgb_parse_css_numeric
argument_list|(
name|rgba
argument_list|,
name|css
argument_list|)
return|;
block|}
end_function

end_unit

