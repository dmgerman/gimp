begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimputils.c  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"gimputils.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * gimp_utf8_strtrim:  * @str: an UTF-8 encoded string (or %NULL)  * @max_chars: the maximum number of characters before the string get  * trimmed  *  * Creates a (possibly trimmed) copy of @str. The string is cut if it  * exceeds @max_chars characters or on the first newline. The fact  * that the string was trimmed is indicated by appending an ellipsis.  *  * Returns: A (possibly trimmed) copy of @str which should be freed  * using g_free() when it is not needed any longer.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_utf8_strtrim (const gchar * str,gint max_chars)
name|gimp_utf8_strtrim
parameter_list|(
specifier|const
name|gchar
modifier|*
name|str
parameter_list|,
name|gint
name|max_chars
parameter_list|)
block|{
comment|/* FIXME: should we make this translatable? */
specifier|static
specifier|const
name|gchar
modifier|*
name|ellipsis
init|=
literal|"..."
decl_stmt|;
specifier|static
specifier|const
name|gint
name|e_len
init|=
literal|3
decl_stmt|;
if|if
condition|(
name|str
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|p
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|newline
init|=
name|NULL
decl_stmt|;
name|gint
name|chars
init|=
literal|0
decl_stmt|;
name|gunichar
name|unichar
decl_stmt|;
for|for
control|(
name|p
operator|=
name|str
init|;
operator|*
name|p
condition|;
name|p
operator|=
name|g_utf8_next_char
argument_list|(
name|p
argument_list|)
control|)
block|{
if|if
condition|(
operator|++
name|chars
operator|>
name|max_chars
condition|)
break|break;
name|unichar
operator|=
name|g_utf8_get_char
argument_list|(
name|p
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|g_unichar_break_type
argument_list|(
name|unichar
argument_list|)
condition|)
block|{
case|case
name|G_UNICODE_BREAK_MANDATORY
case|:
case|case
name|G_UNICODE_BREAK_LINE_FEED
case|:
name|newline
operator|=
name|p
expr_stmt|;
break|break;
default|default:
continue|continue;
block|}
break|break;
block|}
if|if
condition|(
operator|*
name|p
condition|)
block|{
name|gsize
name|len
init|=
name|p
operator|-
name|str
decl_stmt|;
name|gchar
modifier|*
name|trimmed
init|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|len
operator|+
name|e_len
operator|+
literal|2
argument_list|)
decl_stmt|;
name|memcpy
argument_list|(
name|trimmed
argument_list|,
name|str
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|newline
condition|)
name|trimmed
index|[
name|len
operator|++
index|]
operator|=
literal|' '
expr_stmt|;
name|g_strlcpy
argument_list|(
name|trimmed
operator|+
name|len
argument_list|,
name|ellipsis
argument_list|,
name|e_len
operator|+
literal|1
argument_list|)
expr_stmt|;
return|return
name|trimmed
return|;
block|}
return|return
name|g_strdup
argument_list|(
name|str
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_any_to_utf8:  * @str:            The string to be converted to UTF-8.  * @len:            The length of the string, or -1 if the string  *                  is nul-terminated.  * @warning_format: The message format for the warning message if conversion  *                  to UTF-8 fails. See the<function>printf()</function>  *                  documentation.  * @Varargs:        The parameters to insert into the format string.  *  * This function takes any string (UTF-8 or not) and always returns a valid  * UTF-8 string.  *  * If @str is valid UTF-8, a copy of the string is returned.  *  * If UTF-8 validation fails, g_locale_to_utf8() is tried and if it  * succeeds the resulting string is returned.  *  * Otherwise, the portion of @str that is UTF-8, concatenated  * with "(invalid UTF-8 string)" is returned. If not even the start  * of @str is valid UTF-8, only "(invalid UTF-8 string)" is returned.  *  * Return value: The UTF-8 string as described above.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_any_to_utf8 (const gchar * str,gssize len,const gchar * warning_format,...)
name|gimp_any_to_utf8
parameter_list|(
specifier|const
name|gchar
modifier|*
name|str
parameter_list|,
name|gssize
name|len
parameter_list|,
specifier|const
name|gchar
modifier|*
name|warning_format
parameter_list|,
modifier|...
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|start_invalid
decl_stmt|;
name|gchar
modifier|*
name|utf8
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|str
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_utf8_validate
argument_list|(
name|str
argument_list|,
name|len
argument_list|,
operator|&
name|start_invalid
argument_list|)
condition|)
name|utf8
operator|=
name|g_strdup
argument_list|(
name|str
argument_list|)
expr_stmt|;
else|else
name|utf8
operator|=
name|g_locale_to_utf8
argument_list|(
name|str
argument_list|,
name|len
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|utf8
condition|)
block|{
if|if
condition|(
name|warning_format
condition|)
block|{
name|va_list
name|warning_args
decl_stmt|;
name|va_start
argument_list|(
name|warning_args
argument_list|,
name|warning_format
argument_list|)
expr_stmt|;
name|g_logv
argument_list|(
name|G_LOG_DOMAIN
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|warning_format
argument_list|,
name|warning_args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|warning_args
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|start_invalid
operator|>
name|str
condition|)
block|{
name|gchar
modifier|*
name|tmp
decl_stmt|;
name|tmp
operator|=
name|g_strndup
argument_list|(
name|str
argument_list|,
name|start_invalid
operator|-
name|str
argument_list|)
expr_stmt|;
name|utf8
operator|=
name|g_strconcat
argument_list|(
name|tmp
argument_list|,
name|_
argument_list|(
literal|"(invalid UTF-8 string)"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|utf8
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"(invalid UTF-8 string)"
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|utf8
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_filename_to_utf8:  * @filename: The filename to be converted to UTF-8.  *  * Convert a filename in the filesystem's encoding to UTF-8  * temporarily.  The return value is a pointer to a string that is  * guaranteed to be valid only during the current iteration of the  * main loop or until the next call to gimp_filename_to_utf8().  *  * The only purpose of this function is to provide an easy way to pass  * a filename in the filesystem encoding to a function that expects an  * UTF-8 encoded filename.  *  * Return value: A temporarily valid UTF-8 representation of @filename.  *               This string must not be changed or freed.  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_filename_to_utf8 (const gchar * filename)
name|gimp_filename_to_utf8
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
comment|/* Simpleminded implementation, but at least allocates just one copy    * of each translation. Could check if already UTF-8, and if so    * return filename as is. Could perhaps (re)use a suitably large    * cyclic buffer, but then would have to verify that all calls    * really need the return value just for a "short" time.    */
specifier|static
name|GHashTable
modifier|*
name|ht
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|filename_utf8
decl_stmt|;
if|if
condition|(
operator|!
name|filename
condition|)
return|return
name|NULL
return|;
if|if
condition|(
operator|!
name|ht
condition|)
name|ht
operator|=
name|g_hash_table_new
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|)
expr_stmt|;
name|filename_utf8
operator|=
name|g_hash_table_lookup
argument_list|(
name|ht
argument_list|,
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|filename_utf8
condition|)
block|{
name|filename_utf8
operator|=
name|g_filename_to_utf8
argument_list|(
name|filename
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|ht
argument_list|,
name|g_strdup
argument_list|(
name|filename
argument_list|)
argument_list|,
name|filename_utf8
argument_list|)
expr_stmt|;
block|}
return|return
name|filename_utf8
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_strip_uline:  * @str: Underline infested string (or %NULL)  *  * This function returns a copy of @str stripped of underline  * characters. This comes in handy when needing to strip mnemonics  * from menu paths etc.  *  * Return value: A (possibly stripped) copy of @str which should be  * freed using g_free() when it is not needed any longer.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_strip_uline (const gchar * str)
name|gimp_strip_uline
parameter_list|(
specifier|const
name|gchar
modifier|*
name|str
parameter_list|)
block|{
name|gchar
modifier|*
name|escaped
decl_stmt|;
name|gchar
modifier|*
name|p
decl_stmt|;
if|if
condition|(
operator|!
name|str
condition|)
return|return
name|NULL
return|;
name|p
operator|=
name|escaped
operator|=
name|g_strdup
argument_list|(
name|str
argument_list|)
expr_stmt|;
while|while
condition|(
operator|*
name|str
condition|)
block|{
if|if
condition|(
operator|*
name|str
operator|==
literal|'_'
condition|)
block|{
comment|/*  "__" means a literal "_" in the menu path  */
if|if
condition|(
name|str
index|[
literal|1
index|]
operator|==
literal|'_'
condition|)
operator|*
name|p
operator|++
operator|=
operator|*
name|str
operator|++
expr_stmt|;
name|str
operator|++
expr_stmt|;
block|}
else|else
block|{
operator|*
name|p
operator|++
operator|=
operator|*
name|str
operator|++
expr_stmt|;
block|}
block|}
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
return|return
name|escaped
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_escape_uline:  * @str: Underline infested string (or %NULL)  *  * This function returns a copy of @str with all underline converted  * to two adjacent underlines. This comes in handy when needing to display  * strings with underlines (like filenames) in a place that would convert  * them to mnemonics.  *  * Return value: A (possibly escaped) copy of @str which should be  * freed using g_free() when it is not needed any longer.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_escape_uline (const gchar * str)
name|gimp_escape_uline
parameter_list|(
specifier|const
name|gchar
modifier|*
name|str
parameter_list|)
block|{
name|gchar
modifier|*
name|escaped
decl_stmt|;
name|gchar
modifier|*
name|p
decl_stmt|;
name|gint
name|n_ulines
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|str
condition|)
return|return
name|NULL
return|;
for|for
control|(
name|p
operator|=
operator|(
name|gchar
operator|*
operator|)
name|str
init|;
operator|*
name|p
condition|;
name|p
operator|++
control|)
if|if
condition|(
operator|*
name|p
operator|==
literal|'_'
condition|)
name|n_ulines
operator|++
expr_stmt|;
name|p
operator|=
name|escaped
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|str
argument_list|)
operator|+
name|n_ulines
operator|+
literal|1
argument_list|)
expr_stmt|;
while|while
condition|(
operator|*
name|str
condition|)
block|{
if|if
condition|(
operator|*
name|str
operator|==
literal|'_'
condition|)
operator|*
name|p
operator|++
operator|=
literal|'_'
expr_stmt|;
operator|*
name|p
operator|++
operator|=
operator|*
name|str
operator|++
expr_stmt|;
block|}
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
return|return
name|escaped
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_get_desc:  * @enum_class: a #GEnumClass  * @value:      a value from @enum_class  *  * Retrieves #GimpEnumDesc associated with the given value, or %NULL.  *  * Return value: the value's #GimpEnumDesc.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GimpEnumDesc
modifier|*
DECL|function|gimp_enum_get_desc (GEnumClass * enum_class,gint value)
name|gimp_enum_get_desc
parameter_list|(
name|GEnumClass
modifier|*
name|enum_class
parameter_list|,
name|gint
name|value
parameter_list|)
block|{
specifier|const
name|GimpEnumDesc
modifier|*
name|value_desc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_ENUM_CLASS
argument_list|(
name|enum_class
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|value_desc
operator|=
name|gimp_enum_get_value_descriptions
argument_list|(
name|G_TYPE_FROM_CLASS
argument_list|(
name|enum_class
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|value_desc
condition|)
block|{
while|while
condition|(
name|value_desc
operator|->
name|value_desc
condition|)
block|{
if|if
condition|(
name|value_desc
operator|->
name|value
operator|==
name|value
condition|)
return|return
operator|(
name|GimpEnumDesc
operator|*
operator|)
name|value_desc
return|;
name|value_desc
operator|++
expr_stmt|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_get_value:  * @enum_type:  the #GType of a registered enum  * @value:      an integer value  * @value_name: return location for the value's name (or %NULL)  * @value_nick: return location for the value's nick (or %NULL)  * @value_desc: return location for the value's translated desc (or %NULL)  * @value_help: return location for the value's translated help (or %NULL)  *  * Checks if @value is valid for the enum registered as @enum_type.  * If the value exists in that enum, its name, nick and its translated  * desc and help are returned (if @value_name, @value_nick, @value_desc  * and @value_help are not %NULL).  *  * Return value: %TRUE if @value is valid for the @enum_type,  *               %FALSE otherwise  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_enum_get_value (GType enum_type,gint value,const gchar ** value_name,const gchar ** value_nick,const gchar ** value_desc,const gchar ** value_help)
name|gimp_enum_get_value
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|value
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_nick
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_desc
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_help
parameter_list|)
block|{
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_peek
argument_list|(
name|enum_type
argument_list|)
expr_stmt|;
name|enum_value
operator|=
name|g_enum_get_value
argument_list|(
name|enum_class
argument_list|,
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|enum_value
condition|)
block|{
if|if
condition|(
name|value_name
condition|)
operator|*
name|value_name
operator|=
name|enum_value
operator|->
name|value_name
expr_stmt|;
if|if
condition|(
name|value_nick
condition|)
operator|*
name|value_nick
operator|=
name|enum_value
operator|->
name|value_nick
expr_stmt|;
if|if
condition|(
name|value_desc
operator|||
name|value_help
condition|)
block|{
name|GimpEnumDesc
modifier|*
name|enum_desc
decl_stmt|;
name|enum_desc
operator|=
name|gimp_enum_get_desc
argument_list|(
name|enum_class
argument_list|,
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|value_desc
condition|)
operator|*
name|value_desc
operator|=
operator|(
operator|(
name|enum_desc
operator|&&
name|enum_desc
operator|->
name|value_desc
operator|)
condition|?
name|dgettext
argument_list|(
name|gimp_type_get_translation_domain
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|enum_desc
operator|->
name|value_desc
argument_list|)
else|:
name|NULL
operator|)
expr_stmt|;
if|if
condition|(
name|value_help
condition|)
operator|*
name|value_help
operator|=
operator|(
operator|(
name|enum_desc
operator|&&
name|enum_desc
operator|->
name|value_desc
operator|)
condition|?
name|dgettext
argument_list|(
name|gimp_type_get_translation_domain
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|enum_desc
operator|->
name|value_help
argument_list|)
else|:
name|NULL
operator|)
expr_stmt|;
block|}
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
comment|/**  * gimp_enum_value_get_desc:  * @enum_class: a #GEnumClass  * @enum_value: a #GEnumValue from @enum_class  *  * Retrieves the translated desc for a given @enum_value.  *  * Return value: the translated desc of the enum value  *  * Since: GIMP 2.2  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_enum_value_get_desc (GEnumClass * enum_class,GEnumValue * enum_value)
name|gimp_enum_value_get_desc
parameter_list|(
name|GEnumClass
modifier|*
name|enum_class
parameter_list|,
name|GEnumValue
modifier|*
name|enum_value
parameter_list|)
block|{
name|GType
name|type
init|=
name|G_TYPE_FROM_CLASS
argument_list|(
name|enum_class
argument_list|)
decl_stmt|;
name|GimpEnumDesc
modifier|*
name|enum_desc
decl_stmt|;
name|enum_desc
operator|=
name|gimp_enum_get_desc
argument_list|(
name|enum_class
argument_list|,
name|enum_value
operator|->
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|enum_desc
operator|->
name|value_desc
condition|)
return|return
name|dgettext
argument_list|(
name|gimp_type_get_translation_domain
argument_list|(
name|type
argument_list|)
argument_list|,
name|enum_desc
operator|->
name|value_desc
argument_list|)
return|;
return|return
name|enum_value
operator|->
name|value_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_value_get_help:  * @enum_class: a #GEnumClass  * @enum_value: a #GEnumValue from @enum_class  *  * Retrieves the translated help for a given @enum_value.  *  * Return value: the translated help of the enum value  *  * Since: GIMP 2.2  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_enum_value_get_help (GEnumClass * enum_class,GEnumValue * enum_value)
name|gimp_enum_value_get_help
parameter_list|(
name|GEnumClass
modifier|*
name|enum_class
parameter_list|,
name|GEnumValue
modifier|*
name|enum_value
parameter_list|)
block|{
name|GType
name|type
init|=
name|G_TYPE_FROM_CLASS
argument_list|(
name|enum_class
argument_list|)
decl_stmt|;
name|GimpEnumDesc
modifier|*
name|enum_desc
decl_stmt|;
name|enum_desc
operator|=
name|gimp_enum_get_desc
argument_list|(
name|enum_class
argument_list|,
name|enum_value
operator|->
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|enum_desc
operator|->
name|value_help
condition|)
return|return
name|dgettext
argument_list|(
name|gimp_type_get_translation_domain
argument_list|(
name|type
argument_list|)
argument_list|,
name|enum_desc
operator|->
name|value_help
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_flags_get_first_desc:  * @flags_class: a #GFlagsClass  * @value:       a value from @flags_class  *  * Retrieves the first #GimpFlagsDesc that matches the given value, or %NULL.  *  * Return value: the value's #GimpFlagsDesc.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GimpFlagsDesc
modifier|*
DECL|function|gimp_flags_get_first_desc (GFlagsClass * flags_class,guint value)
name|gimp_flags_get_first_desc
parameter_list|(
name|GFlagsClass
modifier|*
name|flags_class
parameter_list|,
name|guint
name|value
parameter_list|)
block|{
specifier|const
name|GimpFlagsDesc
modifier|*
name|value_desc
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_FLAGS_CLASS
argument_list|(
name|flags_class
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|value_desc
operator|=
name|gimp_flags_get_value_descriptions
argument_list|(
name|G_TYPE_FROM_CLASS
argument_list|(
name|flags_class
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|value_desc
condition|)
block|{
while|while
condition|(
name|value_desc
operator|->
name|value_desc
condition|)
block|{
if|if
condition|(
operator|(
name|value_desc
operator|->
name|value
operator|&
name|value
operator|)
operator|==
name|value_desc
operator|->
name|value
condition|)
return|return
operator|(
name|GimpFlagsDesc
operator|*
operator|)
name|value_desc
return|;
name|value_desc
operator|++
expr_stmt|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_flags_get_first_value:  * @flags_type: the #GType of registered flags  * @value:      an integer value  * @value_name: return location for the value's name (or %NULL)  * @value_nick: return location for the value's nick (or %NULL)  * @value_desc: return location for the value's translated desc (or %NULL)  * @value_help: return location for the value's translated help (or %NULL)  *  * Checks if @value is valid for the flags registered as @flags_type.  * If the value exists in that flags, its name, nick and its translated  * desc and help are returned (if @value_name, @value_nick, @value_desc  * and @value_help are not %NULL).  *  * Return value: %TRUE if @value is valid for the @flags_type,  *               %FALSE otherwise  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_flags_get_first_value (GType flags_type,guint value,const gchar ** value_name,const gchar ** value_nick,const gchar ** value_desc,const gchar ** value_help)
name|gimp_flags_get_first_value
parameter_list|(
name|GType
name|flags_type
parameter_list|,
name|guint
name|value
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_nick
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_desc
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_help
parameter_list|)
block|{
name|GFlagsClass
modifier|*
name|flags_class
decl_stmt|;
name|GFlagsValue
modifier|*
name|flags_value
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_FLAGS
argument_list|(
name|flags_type
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|flags_class
operator|=
name|g_type_class_peek
argument_list|(
name|flags_type
argument_list|)
expr_stmt|;
name|flags_value
operator|=
name|g_flags_get_first_value
argument_list|(
name|flags_class
argument_list|,
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|flags_value
condition|)
block|{
if|if
condition|(
name|value_name
condition|)
operator|*
name|value_name
operator|=
name|flags_value
operator|->
name|value_name
expr_stmt|;
if|if
condition|(
name|value_nick
condition|)
operator|*
name|value_nick
operator|=
name|flags_value
operator|->
name|value_nick
expr_stmt|;
if|if
condition|(
name|value_desc
operator|||
name|value_help
condition|)
block|{
name|GimpFlagsDesc
modifier|*
name|flags_desc
decl_stmt|;
name|flags_desc
operator|=
name|gimp_flags_get_first_desc
argument_list|(
name|flags_class
argument_list|,
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|value_desc
condition|)
operator|*
name|value_desc
operator|=
operator|(
operator|(
name|flags_desc
operator|&&
name|flags_desc
operator|->
name|value_desc
operator|)
condition|?
name|dgettext
argument_list|(
name|gimp_type_get_translation_domain
argument_list|(
name|flags_type
argument_list|)
argument_list|,
name|flags_desc
operator|->
name|value_desc
argument_list|)
else|:
name|NULL
operator|)
expr_stmt|;
if|if
condition|(
name|value_help
condition|)
operator|*
name|value_help
operator|=
operator|(
operator|(
name|flags_desc
operator|&&
name|flags_desc
operator|->
name|value_desc
operator|)
condition|?
name|dgettext
argument_list|(
name|gimp_type_get_translation_domain
argument_list|(
name|flags_type
argument_list|)
argument_list|,
name|flags_desc
operator|->
name|value_help
argument_list|)
else|:
name|NULL
operator|)
expr_stmt|;
block|}
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
comment|/**  * gimp_flags_value_get_desc:  * @flags_class: a #GFlagsClass  * @flags_value: a #GFlagsValue from @flags_class  *  * Retrieves the translated desc for a given @flags_value.  *  * Return value: the translated desc of the flags value  *  * Since: GIMP 2.2  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_flags_value_get_desc (GFlagsClass * flags_class,GFlagsValue * flags_value)
name|gimp_flags_value_get_desc
parameter_list|(
name|GFlagsClass
modifier|*
name|flags_class
parameter_list|,
name|GFlagsValue
modifier|*
name|flags_value
parameter_list|)
block|{
name|GType
name|type
init|=
name|G_TYPE_FROM_CLASS
argument_list|(
name|flags_class
argument_list|)
decl_stmt|;
name|GimpFlagsDesc
modifier|*
name|flags_desc
decl_stmt|;
name|flags_desc
operator|=
name|gimp_flags_get_first_desc
argument_list|(
name|flags_class
argument_list|,
name|flags_value
operator|->
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|flags_desc
operator|->
name|value_desc
condition|)
return|return
name|dgettext
argument_list|(
name|gimp_type_get_translation_domain
argument_list|(
name|type
argument_list|)
argument_list|,
name|flags_desc
operator|->
name|value_desc
argument_list|)
return|;
return|return
name|flags_value
operator|->
name|value_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_flags_value_get_help:  * @flags_class: a #GFlagsClass  * @flags_value: a #GFlagsValue from @flags_class  *  * Retrieves the translated help for a given @flags_value.  *  * Return value: the translated help of the flags value  *  * Since: GIMP 2.2  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_flags_value_get_help (GFlagsClass * flags_class,GFlagsValue * flags_value)
name|gimp_flags_value_get_help
parameter_list|(
name|GFlagsClass
modifier|*
name|flags_class
parameter_list|,
name|GFlagsValue
modifier|*
name|flags_value
parameter_list|)
block|{
name|GType
name|type
init|=
name|G_TYPE_FROM_CLASS
argument_list|(
name|flags_class
argument_list|)
decl_stmt|;
name|GimpFlagsDesc
modifier|*
name|flags_desc
decl_stmt|;
name|flags_desc
operator|=
name|gimp_flags_get_first_desc
argument_list|(
name|flags_class
argument_list|,
name|flags_value
operator|->
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|flags_desc
operator|->
name|value_help
condition|)
return|return
name|dgettext
argument_list|(
name|gimp_type_get_translation_domain
argument_list|(
name|type
argument_list|)
argument_list|,
name|flags_desc
operator|->
name|value_help
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

