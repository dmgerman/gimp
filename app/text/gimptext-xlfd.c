begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2002-2004  Sven Neumann<sven@gimp.org>  *  * Some of this code was copied from Pango (pangox-fontmap.c)  * and was originally written by Owen Taylor<otaylor@redhat.com>.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"text-types.h"
end_include

begin_include
include|#
directive|include
file|"gimptext.h"
end_include

begin_include
include|#
directive|include
file|"gimptext-xlfd.h"
end_include

begin_define
DECL|macro|XLFD_MAX_FIELD_LEN
define|#
directive|define
name|XLFD_MAX_FIELD_LEN
value|64
end_define

begin_comment
comment|/* These are the field numbers in the X Logical Font Description fontnames,    e.g. -adobe-courier-bold-o-normal--25-180-100-100-m-150-iso8859-1 */
end_comment

begin_enum
enum|enum
DECL|enum|__anon2b91c7d90103
block|{
DECL|enumerator|XLFD_FOUNDRY
name|XLFD_FOUNDRY
init|=
literal|0
block|,
DECL|enumerator|XLFD_FAMILY
name|XLFD_FAMILY
init|=
literal|1
block|,
DECL|enumerator|XLFD_WEIGHT
name|XLFD_WEIGHT
init|=
literal|2
block|,
DECL|enumerator|XLFD_SLANT
name|XLFD_SLANT
init|=
literal|3
block|,
DECL|enumerator|XLFD_SET_WIDTH
name|XLFD_SET_WIDTH
init|=
literal|4
block|,
DECL|enumerator|XLFD_ADD_STYLE
name|XLFD_ADD_STYLE
init|=
literal|5
block|,
DECL|enumerator|XLFD_PIXELS
name|XLFD_PIXELS
init|=
literal|6
block|,
DECL|enumerator|XLFD_POINTS
name|XLFD_POINTS
init|=
literal|7
block|,
DECL|enumerator|XLFD_RESOLUTION_X
name|XLFD_RESOLUTION_X
init|=
literal|8
block|,
DECL|enumerator|XLFD_RESOLUTION_Y
name|XLFD_RESOLUTION_Y
init|=
literal|9
block|,
DECL|enumerator|XLFD_SPACING
name|XLFD_SPACING
init|=
literal|10
block|,
DECL|enumerator|XLFD_AVERAGE_WIDTH
name|XLFD_AVERAGE_WIDTH
init|=
literal|11
block|,
DECL|enumerator|XLFD_CHARSET
name|XLFD_CHARSET
init|=
literal|12
block|,
DECL|enumerator|XLFD_NUM_FIELDS
name|XLFD_NUM_FIELDS
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_text_get_xlfd_field
parameter_list|(
specifier|const
name|gchar
modifier|*
name|fontname
parameter_list|,
name|gint
name|field_num
parameter_list|,
name|gchar
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|launder_font_name
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_text_font_name_from_xlfd:  * @xlfd: X Logical Font Description  *  * Attempts to extract a meaningful font name from the "family",  * "weight", "slant" and "stretch" fields of an X Logical Font  * Description.  *  * Return value: a newly allocated string.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_text_font_name_from_xlfd (const gchar * xlfd)
name|gimp_text_font_name_from_xlfd
parameter_list|(
specifier|const
name|gchar
modifier|*
name|xlfd
parameter_list|)
block|{
name|gchar
modifier|*
name|fields
index|[
literal|4
index|]
decl_stmt|;
name|gchar
name|buffers
index|[
literal|4
index|]
index|[
name|XLFD_MAX_FIELD_LEN
index|]
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
comment|/*  family  */
name|fields
index|[
name|i
index|]
operator|=
name|gimp_text_get_xlfd_field
argument_list|(
name|xlfd
argument_list|,
name|XLFD_FAMILY
argument_list|,
name|buffers
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|fields
index|[
name|i
index|]
condition|)
name|i
operator|++
expr_stmt|;
comment|/*  weight  */
name|fields
index|[
name|i
index|]
operator|=
name|gimp_text_get_xlfd_field
argument_list|(
name|xlfd
argument_list|,
name|XLFD_WEIGHT
argument_list|,
name|buffers
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|fields
index|[
name|i
index|]
operator|&&
name|strcmp
argument_list|(
name|fields
index|[
name|i
index|]
argument_list|,
literal|"medium"
argument_list|)
condition|)
name|i
operator|++
expr_stmt|;
comment|/*  slant  */
name|fields
index|[
name|i
index|]
operator|=
name|gimp_text_get_xlfd_field
argument_list|(
name|xlfd
argument_list|,
name|XLFD_SLANT
argument_list|,
name|buffers
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|fields
index|[
name|i
index|]
condition|)
block|{
switch|switch
condition|(
operator|*
name|fields
index|[
name|i
index|]
condition|)
block|{
case|case
literal|'i'
case|:
name|strcpy
argument_list|(
name|buffers
index|[
name|i
index|]
argument_list|,
literal|"italic"
argument_list|)
expr_stmt|;
name|i
operator|++
expr_stmt|;
break|break;
case|case
literal|'o'
case|:
name|strcpy
argument_list|(
name|buffers
index|[
name|i
index|]
argument_list|,
literal|"oblique"
argument_list|)
expr_stmt|;
name|i
operator|++
expr_stmt|;
break|break;
case|case
literal|'r'
case|:
break|break;
block|}
block|}
comment|/*  stretch  */
name|fields
index|[
name|i
index|]
operator|=
name|gimp_text_get_xlfd_field
argument_list|(
name|xlfd
argument_list|,
name|XLFD_SET_WIDTH
argument_list|,
name|buffers
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|fields
index|[
name|i
index|]
operator|&&
name|strcmp
argument_list|(
name|fields
index|[
name|i
index|]
argument_list|,
literal|"normal"
argument_list|)
condition|)
name|i
operator|++
expr_stmt|;
if|if
condition|(
name|i
operator|<
literal|4
condition|)
name|fields
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
return|return
name|launder_font_name
argument_list|(
name|g_strconcat
argument_list|(
name|fields
index|[
literal|0
index|]
argument_list|,
literal|" "
argument_list|,
name|fields
index|[
literal|1
index|]
argument_list|,
literal|" "
argument_list|,
name|fields
index|[
literal|2
index|]
argument_list|,
literal|" "
argument_list|,
name|fields
index|[
literal|3
index|]
argument_list|,
name|NULL
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_text_font_size_from_xlfd:  * @xlfd: X Logical Font Description  * @size: return location for the font size  * @size_unit: return location for the font size unit  *  * Attempts to extract the font size from an X Logical Font  * Description.  *  * Return value: %TRUE on success, %FALSE otherwise.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_text_font_size_from_xlfd (const gchar * xlfd,gdouble * size,GimpUnit * size_unit)
name|gimp_text_font_size_from_xlfd
parameter_list|(
specifier|const
name|gchar
modifier|*
name|xlfd
parameter_list|,
name|gdouble
modifier|*
name|size
parameter_list|,
name|GimpUnit
modifier|*
name|size_unit
parameter_list|)
block|{
name|gchar
name|buffer
index|[
name|XLFD_MAX_FIELD_LEN
index|]
decl_stmt|;
name|gchar
modifier|*
name|field
decl_stmt|;
if|if
condition|(
operator|!
name|xlfd
condition|)
return|return
name|FALSE
return|;
name|field
operator|=
name|gimp_text_get_xlfd_field
argument_list|(
name|xlfd
argument_list|,
name|XLFD_PIXELS
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|field
condition|)
block|{
operator|*
name|size
operator|=
name|atoi
argument_list|(
name|field
argument_list|)
expr_stmt|;
operator|*
name|size_unit
operator|=
name|GIMP_UNIT_PIXEL
expr_stmt|;
return|return
name|TRUE
return|;
block|}
name|field
operator|=
name|gimp_text_get_xlfd_field
argument_list|(
name|xlfd
argument_list|,
name|XLFD_POINTS
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|field
condition|)
block|{
operator|*
name|size
operator|=
name|atoi
argument_list|(
name|field
argument_list|)
operator|/
literal|10.0
expr_stmt|;
operator|*
name|size_unit
operator|=
name|GIMP_UNIT_POINT
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

begin_comment
comment|/**  * gimp_text_set_font_from_xlfd:  * @text: a #GimpText object  * @xlfd: X Logical Font Description  *  * Attempts to extract font name and font size from @xlfd and sets  * them on the #GimpText object.  **/
end_comment

begin_function
name|void
DECL|function|gimp_text_set_font_from_xlfd (GimpText * text,const gchar * xlfd)
name|gimp_text_set_font_from_xlfd
parameter_list|(
name|GimpText
modifier|*
name|text
parameter_list|,
specifier|const
name|gchar
modifier|*
name|xlfd
parameter_list|)
block|{
name|gchar
modifier|*
name|font
decl_stmt|;
name|gdouble
name|size
decl_stmt|;
name|GimpUnit
name|size_unit
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT
argument_list|(
name|text
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|xlfd
condition|)
return|return;
name|font
operator|=
name|gimp_text_font_name_from_xlfd
argument_list|(
name|xlfd
argument_list|)
expr_stmt|;
if|#
directive|if
name|GIMP_TEXT_DEBUG
name|g_printerr
argument_list|(
literal|"XLFD: %s  font: %s\n"
argument_list|,
name|xlfd
argument_list|,
name|font
condition|?
name|font
else|:
literal|"(null)"
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|gimp_text_font_size_from_xlfd
argument_list|(
name|xlfd
argument_list|,
operator|&
name|size
argument_list|,
operator|&
name|size_unit
argument_list|)
condition|)
block|{
name|g_object_set
argument_list|(
name|text
argument_list|,
literal|"font-size"
argument_list|,
name|size
argument_list|,
literal|"font-size-unit"
argument_list|,
name|size_unit
argument_list|,
name|font
condition|?
literal|"font"
else|:
name|NULL
argument_list|,
name|font
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|font
condition|)
block|{
name|g_object_set
argument_list|(
name|text
argument_list|,
literal|"font"
argument_list|,
name|font
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|font
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_text_get_xlfd_field:  * @fontname: an XLFD fontname  * @field_num: field index  * @buffer: buffer of at least XLFD_MAX_FIELD_LEN chars  *  * Fills the buffer with the specified field from the X Logical Font  * Description name, and returns it. Note: For the charset field, we  * also return the encoding, e.g. 'iso8859-1'.  *  * This function is basically copied from pangox-fontmap.c.  *  * Returns: a pointer to the filled buffer or %NULL if fontname is  * %NULL, the field is longer than XFLD_MAX_FIELD_LEN or it contains  * just an asteriks.  **/
end_comment

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_text_get_xlfd_field (const gchar * fontname,gint field_num,gchar * buffer)
name|gimp_text_get_xlfd_field
parameter_list|(
specifier|const
name|gchar
modifier|*
name|fontname
parameter_list|,
name|gint
name|field_num
parameter_list|,
name|gchar
modifier|*
name|buffer
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|t1
decl_stmt|,
modifier|*
name|t2
decl_stmt|;
name|gchar
modifier|*
name|p
decl_stmt|;
name|gint
name|countdown
decl_stmt|,
name|num_dashes
decl_stmt|;
name|gsize
name|len
decl_stmt|;
if|if
condition|(
operator|!
name|fontname
condition|)
return|return
name|NULL
return|;
comment|/* we assume this is a valid fontname...that is, it has 14 fields */
for|for
control|(
name|t1
operator|=
name|fontname
operator|,
name|countdown
operator|=
name|field_num
init|;
operator|*
name|t1
operator|&&
operator|(
name|countdown
operator|>=
literal|0
operator|)
condition|;
name|t1
operator|++
control|)
if|if
condition|(
operator|*
name|t1
operator|==
literal|'-'
condition|)
name|countdown
operator|--
expr_stmt|;
name|num_dashes
operator|=
operator|(
name|field_num
operator|==
name|XLFD_CHARSET
operator|)
condition|?
literal|2
else|:
literal|1
expr_stmt|;
for|for
control|(
name|t2
operator|=
name|t1
init|;
operator|*
name|t2
condition|;
name|t2
operator|++
control|)
block|{
if|if
condition|(
operator|*
name|t2
operator|==
literal|'-'
operator|&&
operator|--
name|num_dashes
operator|==
literal|0
condition|)
break|break;
block|}
if|if
condition|(
name|t2
operator|>
name|t1
condition|)
block|{
comment|/* Check we don't overflow the buffer */
name|len
operator|=
operator|(
name|gsize
operator|)
name|t2
operator|-
operator|(
name|gsize
operator|)
name|t1
expr_stmt|;
if|if
condition|(
name|len
operator|>
name|XLFD_MAX_FIELD_LEN
operator|-
literal|1
condition|)
return|return
name|NULL
return|;
if|if
condition|(
operator|*
name|t1
operator|==
literal|'*'
condition|)
return|return
name|NULL
return|;
name|strncpy
argument_list|(
name|buffer
argument_list|,
name|t1
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|buffer
index|[
name|len
index|]
operator|=
literal|0
expr_stmt|;
comment|/* Convert to lower case. */
for|for
control|(
name|p
operator|=
name|buffer
init|;
operator|*
name|p
condition|;
name|p
operator|++
control|)
operator|*
name|p
operator|=
name|g_ascii_tolower
argument_list|(
operator|*
name|p
argument_list|)
expr_stmt|;
block|}
else|else
block|{
return|return
name|NULL
return|;
block|}
return|return
name|buffer
return|;
block|}
end_function

begin_comment
comment|/* Guard against font names that end in numbers being interpreted as a  * font size in pango font descriptions  */
end_comment

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|launder_font_name (gchar * name)
name|launder_font_name
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|gchar
modifier|*
name|laundered_name
decl_stmt|;
name|gchar
name|last_char
decl_stmt|;
name|last_char
operator|=
name|name
index|[
name|strlen
argument_list|(
name|name
argument_list|)
operator|-
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|g_ascii_isdigit
argument_list|(
name|last_char
argument_list|)
operator|||
name|last_char
operator|==
literal|'.'
condition|)
block|{
name|laundered_name
operator|=
name|g_strconcat
argument_list|(
name|name
argument_list|,
literal|","
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
return|return
name|laundered_name
return|;
block|}
else|else
return|return
name|name
return|;
block|}
end_function

end_unit

