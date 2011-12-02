begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptag.c  * Copyright (C) 2008 Aurimas JuÅ¡ka<aurisj@svn.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimptag.h"
end_include

begin_define
DECL|macro|GIMP_TAG_INTERNAL_PREFIX
define|#
directive|define
name|GIMP_TAG_INTERNAL_PREFIX
value|"gimp:"
end_define

begin_macro
DECL|function|G_DEFINE_TYPE (GimpTag,gimp_tag,G_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTag
argument_list|,
argument|gimp_tag
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tag_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tag_class_init
parameter_list|(
name|GimpTagClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tag_init (GimpTag * tag)
name|gimp_tag_init
parameter_list|(
name|GimpTag
modifier|*
name|tag
parameter_list|)
block|{
name|tag
operator|->
name|tag
operator|=
literal|0
expr_stmt|;
name|tag
operator|->
name|collate_key
operator|=
literal|0
expr_stmt|;
name|tag
operator|->
name|internal
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_new:  * @tag_string: a tag name.  *  * If given tag name is not valid, an attempt will be made to fix it.  *  * Return value: a new #GimpTag object, or NULL if tag string is invalid and  * cannot be fixed.  **/
end_comment

begin_function
name|GimpTag
modifier|*
DECL|function|gimp_tag_new (const char * tag_string)
name|gimp_tag_new
parameter_list|(
specifier|const
name|char
modifier|*
name|tag_string
parameter_list|)
block|{
name|GimpTag
modifier|*
name|tag
decl_stmt|;
name|gchar
modifier|*
name|tag_name
decl_stmt|;
name|gchar
modifier|*
name|case_folded
decl_stmt|;
name|gchar
modifier|*
name|collate_key
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tag_string
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tag_name
operator|=
name|gimp_tag_string_make_valid
argument_list|(
name|tag_string
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tag_name
condition|)
return|return
name|NULL
return|;
name|tag
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TAG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tag
operator|->
name|tag
operator|=
name|g_quark_from_string
argument_list|(
name|tag_name
argument_list|)
expr_stmt|;
name|case_folded
operator|=
name|g_utf8_casefold
argument_list|(
name|tag_name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|collate_key
operator|=
name|g_utf8_collate_key
argument_list|(
name|case_folded
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|tag
operator|->
name|collate_key
operator|=
name|g_quark_from_string
argument_list|(
name|collate_key
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|collate_key
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|case_folded
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tag_name
argument_list|)
expr_stmt|;
return|return
name|tag
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_try_new:  * @tag_string: a tag name.  *  * Similar to gimp_tag_new(), but returns NULL if tag is surely not equal  * to any of currently created tags. It is useful for tag querying to avoid  * unneeded comparisons. If tag is created, however, it does not mean that  * it would necessarily match with some other tag.  *  * Return value: new #GimpTag object, or NULL if tag will not match with any  * other #GimpTag.  **/
end_comment

begin_function
name|GimpTag
modifier|*
DECL|function|gimp_tag_try_new (const char * tag_string)
name|gimp_tag_try_new
parameter_list|(
specifier|const
name|char
modifier|*
name|tag_string
parameter_list|)
block|{
name|GimpTag
modifier|*
name|tag
decl_stmt|;
name|gchar
modifier|*
name|tag_name
decl_stmt|;
name|gchar
modifier|*
name|case_folded
decl_stmt|;
name|gchar
modifier|*
name|collate_key
decl_stmt|;
name|GQuark
name|tag_quark
decl_stmt|;
name|GQuark
name|collate_key_quark
decl_stmt|;
name|tag_name
operator|=
name|gimp_tag_string_make_valid
argument_list|(
name|tag_string
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tag_name
condition|)
return|return
name|NULL
return|;
name|case_folded
operator|=
name|g_utf8_casefold
argument_list|(
name|tag_name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|collate_key
operator|=
name|g_utf8_collate_key
argument_list|(
name|case_folded
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|collate_key_quark
operator|=
name|g_quark_try_string
argument_list|(
name|collate_key
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|collate_key
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|case_folded
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|collate_key_quark
condition|)
block|{
name|g_free
argument_list|(
name|tag_name
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|tag_quark
operator|=
name|g_quark_from_string
argument_list|(
name|tag_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tag_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tag_quark
condition|)
return|return
name|NULL
return|;
name|tag
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TAG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tag
operator|->
name|tag
operator|=
name|tag_quark
expr_stmt|;
name|tag
operator|->
name|collate_key
operator|=
name|collate_key_quark
expr_stmt|;
return|return
name|tag
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_get_internal:  * @tag: a gimp tag.  *  * Retrieve internal status of the tag.  *  * Return value: internal status of tag. Internal tags are not saved.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_tag_get_internal (GimpTag * tag)
name|gimp_tag_get_internal
parameter_list|(
name|GimpTag
modifier|*
name|tag
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|tag
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|tag
operator|->
name|internal
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_set_internal:  * @tag: a gimp tag.  * @inernal: desired tag internal status  *  * Set internal status of the tag. Internal tags are usually automaticaly  * generated and will not be saved into users tag cache.  *  **/
end_comment

begin_function
name|void
DECL|function|gimp_tag_set_internal (GimpTag * tag,gboolean internal)
name|gimp_tag_set_internal
parameter_list|(
name|GimpTag
modifier|*
name|tag
parameter_list|,
name|gboolean
name|internal
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|tag
argument_list|)
argument_list|)
expr_stmt|;
name|tag
operator|->
name|internal
operator|=
name|internal
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_get_name:  * @tag: a gimp tag.  *  * Retrieve name of the tag.  *  * Return value: name of tag.  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_tag_get_name (GimpTag * tag)
name|gimp_tag_get_name
parameter_list|(
name|GimpTag
modifier|*
name|tag
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|tag
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_quark_to_string
argument_list|(
name|tag
operator|->
name|tag
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_get_hash:  * @tag: a gimp tag.  *  * Hashing function which is useful, for example, to store #GimpTag in  * a #GHashTable.  *  * Return value: hash value for tag.  **/
end_comment

begin_function
name|guint
DECL|function|gimp_tag_get_hash (GimpTag * tag)
name|gimp_tag_get_hash
parameter_list|(
name|GimpTag
modifier|*
name|tag
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|tag
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|tag
operator|->
name|collate_key
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_equals:  * @tag:   a gimp tag.  * @other: another gimp tag to compare with.  *  * Compares tags for equality according to tag comparison rules.  *  * Return value: TRUE if tags are equal, FALSE otherwise.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_tag_equals (const GimpTag * tag,const GimpTag * other)
name|gimp_tag_equals
parameter_list|(
specifier|const
name|GimpTag
modifier|*
name|tag
parameter_list|,
specifier|const
name|GimpTag
modifier|*
name|other
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|tag
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|other
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|tag
operator|->
name|collate_key
operator|==
name|other
operator|->
name|collate_key
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_compare_func:  * @p1: pointer to left-hand #GimpTag object.  * @p2: pointer to right-hand #GimpTag object.  *  * Compares tags according to tag comparison rules. Useful for sorting  * functions.  *  * Return value: meaning of return value is the same as in strcmp().  **/
end_comment

begin_function
name|int
DECL|function|gimp_tag_compare_func (const void * p1,const void * p2)
name|gimp_tag_compare_func
parameter_list|(
specifier|const
name|void
modifier|*
name|p1
parameter_list|,
specifier|const
name|void
modifier|*
name|p2
parameter_list|)
block|{
name|GimpTag
modifier|*
name|t1
init|=
name|GIMP_TAG
argument_list|(
name|p1
argument_list|)
decl_stmt|;
name|GimpTag
modifier|*
name|t2
init|=
name|GIMP_TAG
argument_list|(
name|p2
argument_list|)
decl_stmt|;
return|return
name|g_strcmp0
argument_list|(
name|g_quark_to_string
argument_list|(
name|t1
operator|->
name|collate_key
argument_list|)
argument_list|,
name|g_quark_to_string
argument_list|(
name|t2
operator|->
name|collate_key
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_compare_with_string:  * @tag:        a #GimpTag object.  * @tag_string: pointer to right-hand #GimpTag object.  *  * Compares tag and a string according to tag comparison rules. Similar to  * gimp_tag_compare_func(), but can be used without creating temporary tag  * object.  *  * Return value: meaning of return value is the same as in strcmp().  **/
end_comment

begin_function
name|gint
DECL|function|gimp_tag_compare_with_string (GimpTag * tag,const gchar * tag_string)
name|gimp_tag_compare_with_string
parameter_list|(
name|GimpTag
modifier|*
name|tag
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tag_string
parameter_list|)
block|{
name|gchar
modifier|*
name|case_folded
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|collate_key
decl_stmt|;
name|gchar
modifier|*
name|collate_key2
decl_stmt|;
name|gint
name|result
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|tag
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tag_string
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|collate_key
operator|=
name|g_quark_to_string
argument_list|(
name|tag
operator|->
name|collate_key
argument_list|)
expr_stmt|;
name|case_folded
operator|=
name|g_utf8_casefold
argument_list|(
name|tag_string
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|collate_key2
operator|=
name|g_utf8_collate_key
argument_list|(
name|case_folded
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|result
operator|=
name|g_strcmp0
argument_list|(
name|collate_key
argument_list|,
name|collate_key2
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|collate_key2
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|case_folded
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_string_make_valid:  * @tag_string: a text string.  *  * Tries to create a valid tag string from given @tag_string.  *  * Return value: a newly allocated tag string in case given @tag_string was  * valid or could be fixed, otherwise NULL. Allocated value should be freed  * using g_free().  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_tag_string_make_valid (const gchar * tag_string)
name|gimp_tag_string_make_valid
parameter_list|(
specifier|const
name|gchar
modifier|*
name|tag_string
parameter_list|)
block|{
name|gchar
modifier|*
name|tag
decl_stmt|;
name|GString
modifier|*
name|buffer
decl_stmt|;
name|gchar
modifier|*
name|tag_cursor
decl_stmt|;
name|gunichar
name|c
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tag_string
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tag
operator|=
name|g_utf8_normalize
argument_list|(
name|tag_string
argument_list|,
operator|-
literal|1
argument_list|,
name|G_NORMALIZE_ALL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tag
condition|)
return|return
name|NULL
return|;
name|tag
operator|=
name|g_strstrip
argument_list|(
name|tag
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|*
name|tag
condition|)
block|{
name|g_free
argument_list|(
name|tag
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|buffer
operator|=
name|g_string_new
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|tag_cursor
operator|=
name|tag
expr_stmt|;
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|tag_cursor
argument_list|,
name|GIMP_TAG_INTERNAL_PREFIX
argument_list|)
condition|)
block|{
name|tag_cursor
operator|+=
name|strlen
argument_list|(
name|GIMP_TAG_INTERNAL_PREFIX
argument_list|)
expr_stmt|;
block|}
do|do
block|{
name|c
operator|=
name|g_utf8_get_char
argument_list|(
name|tag_cursor
argument_list|)
expr_stmt|;
name|tag_cursor
operator|=
name|g_utf8_next_char
argument_list|(
name|tag_cursor
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_unichar_isprint
argument_list|(
name|c
argument_list|)
operator|&&
operator|!
name|gimp_tag_is_tag_separator
argument_list|(
name|c
argument_list|)
condition|)
block|{
name|g_string_append_unichar
argument_list|(
name|buffer
argument_list|,
name|c
argument_list|)
expr_stmt|;
block|}
block|}
do|while
condition|(
name|c
condition|)
do|;
name|g_free
argument_list|(
name|tag
argument_list|)
expr_stmt|;
name|tag
operator|=
name|g_string_free
argument_list|(
name|buffer
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tag
operator|=
name|g_strstrip
argument_list|(
name|tag
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|*
name|tag
condition|)
block|{
name|g_free
argument_list|(
name|tag
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|tag
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_tag_is_tag_separator:  * @c: Unicode character.  *  * Defines a set of characters that are considered tag separators. The  * tag separators are hand-picked from the set of characters with the  * Terminal_Punctuation property as specified in the version 5.1.0 of  * the Unicode Standard.  *  * Return value: %TRUE if the character is a tag separator.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_tag_is_tag_separator (gunichar c)
name|gimp_tag_is_tag_separator
parameter_list|(
name|gunichar
name|c
parameter_list|)
block|{
switch|switch
condition|(
name|c
condition|)
block|{
case|case
literal|0x002C
case|:
comment|/* COMMA */
case|case
literal|0x060C
case|:
comment|/* ARABIC COMMA */
case|case
literal|0x07F8
case|:
comment|/* NKO COMMA */
case|case
literal|0x1363
case|:
comment|/* ETHIOPIC COMMA */
case|case
literal|0x1802
case|:
comment|/* MONGOLIAN COMMA */
case|case
literal|0x1808
case|:
comment|/* MONGOLIAN MANCHU COMMA */
case|case
literal|0x3001
case|:
comment|/* IDEOGRAPHIC COMMA */
case|case
literal|0xA60D
case|:
comment|/* VAI COMMA */
case|case
literal|0xFE50
case|:
comment|/* SMALL COMMA */
case|case
literal|0xFF0C
case|:
comment|/* FULLWIDTH COMMA */
case|case
literal|0xFF64
case|:
comment|/* HALFWIDTH IDEOGRAPHIC COMMA */
return|return
name|TRUE
return|;
default|default:
return|return
name|FALSE
return|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_tag_or_null_ref:  * @tag: a #GimpTag  *  * A simple wrapper around g_object_ref() that silently accepts #NULL.  **/
end_comment

begin_function
name|void
DECL|function|gimp_tag_or_null_ref (GimpTag * tag_or_null)
name|gimp_tag_or_null_ref
parameter_list|(
name|GimpTag
modifier|*
name|tag_or_null
parameter_list|)
block|{
if|if
condition|(
name|tag_or_null
condition|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|tag_or_null
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|tag_or_null
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_tag_or_null_unref:  * @tag: a #GimpTag  *  * A simple wrapper around g_object_unref() that silently accepts #NULL.  **/
end_comment

begin_function
name|void
DECL|function|gimp_tag_or_null_unref (GimpTag * tag_or_null)
name|gimp_tag_or_null_unref
parameter_list|(
name|GimpTag
modifier|*
name|tag_or_null
parameter_list|)
block|{
if|if
condition|(
name|tag_or_null
condition|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|tag_or_null
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|tag_or_null
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

