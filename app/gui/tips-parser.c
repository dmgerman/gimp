begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * tips-parser.c -- Parse the gimp-tips.xml file.  * Copyright (C) 2002  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
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
file|"tips-parser.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c7deaa30103
block|{
DECL|enumerator|TIPS_START
name|TIPS_START
block|,
DECL|enumerator|TIPS_IN_TIPS
name|TIPS_IN_TIPS
block|,
DECL|enumerator|TIPS_IN_TIP
name|TIPS_IN_TIP
block|,
DECL|enumerator|TIPS_IN_WELCOME
name|TIPS_IN_WELCOME
block|,
DECL|enumerator|TIPS_IN_THETIP
name|TIPS_IN_THETIP
block|,
DECL|enumerator|TIPS_IN_UNKNOWN
name|TIPS_IN_UNKNOWN
DECL|typedef|TipsParserState
block|}
name|TipsParserState
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c7deaa30203
block|{
DECL|enumerator|TIPS_LOCALE_NONE
name|TIPS_LOCALE_NONE
block|,
DECL|enumerator|TIPS_LOCALE_MATCH
name|TIPS_LOCALE_MATCH
block|,
DECL|enumerator|TIPS_LOCALE_MISMATCH
name|TIPS_LOCALE_MISMATCH
block|, }
DECL|typedef|TipsParserLocaleState
name|TipsParserLocaleState
typedef|;
end_typedef

begin_typedef
DECL|typedef|TipsParser
typedef|typedef
name|struct
name|_TipsParser
name|TipsParser
typedef|;
end_typedef

begin_struct
DECL|struct|_TipsParser
struct|struct
name|_TipsParser
block|{
DECL|member|filename
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|state
name|TipsParserState
name|state
decl_stmt|;
DECL|member|last_known_state
name|TipsParserState
name|last_known_state
decl_stmt|;
DECL|member|locale
specifier|const
name|gchar
modifier|*
name|locale
decl_stmt|;
DECL|member|locale_state
name|TipsParserLocaleState
name|locale_state
decl_stmt|;
DECL|member|markup_depth
name|gint
name|markup_depth
decl_stmt|;
DECL|member|unknown_depth
name|gint
name|unknown_depth
decl_stmt|;
DECL|member|value
name|GString
modifier|*
name|value
decl_stmt|;
DECL|member|current_tip
name|GimpTip
modifier|*
name|current_tip
decl_stmt|;
DECL|member|tips
name|GList
modifier|*
name|tips
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|tips_parser_start_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_values
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tips_parser_end_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tips_parser_characters
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gsize
name|text_len
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tips_parser_error
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
name|GError
modifier|*
name|error
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tips_parser_start_markup
parameter_list|(
name|TipsParser
modifier|*
name|parser
parameter_list|,
specifier|const
name|gchar
modifier|*
name|markup_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tips_parser_end_markup
parameter_list|(
name|TipsParser
modifier|*
name|parser
parameter_list|,
specifier|const
name|gchar
modifier|*
name|markup_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tips_parser_start_unknown
parameter_list|(
name|TipsParser
modifier|*
name|parser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tips_parser_end_unknown
parameter_list|(
name|TipsParser
modifier|*
name|parser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tips_parser_parse_locale
parameter_list|(
name|TipsParser
modifier|*
name|parser
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tips_parser_set_by_locale
parameter_list|(
name|TipsParser
modifier|*
name|parser
parameter_list|,
name|gchar
modifier|*
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|markup_parser
specifier|static
specifier|const
name|GMarkupParser
name|markup_parser
init|=
block|{
name|tips_parser_start_element
block|,
name|tips_parser_end_element
block|,
name|tips_parser_characters
block|,
name|NULL
block|,
comment|/*  passthrough  */
name|tips_parser_error
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|GimpTip
modifier|*
DECL|function|gimp_tip_new (const gchar * welcome,const gchar * thetip)
name|gimp_tip_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|welcome
parameter_list|,
specifier|const
name|gchar
modifier|*
name|thetip
parameter_list|)
block|{
name|GimpTip
modifier|*
name|tip
init|=
name|g_new
argument_list|(
name|GimpTip
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|tip
operator|->
name|welcome
operator|=
name|welcome
condition|?
name|g_strdup
argument_list|(
name|welcome
argument_list|)
else|:
name|NULL
expr_stmt|;
name|tip
operator|->
name|thetip
operator|=
name|thetip
condition|?
name|g_strdup
argument_list|(
name|thetip
argument_list|)
else|:
name|NULL
expr_stmt|;
return|return
name|tip
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tip_free (GimpTip * tip)
name|gimp_tip_free
parameter_list|(
name|GimpTip
modifier|*
name|tip
parameter_list|)
block|{
if|if
condition|(
operator|!
name|tip
condition|)
return|return;
name|g_free
argument_list|(
name|tip
operator|->
name|welcome
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tip
operator|->
name|thetip
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tip
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_tips_from_file:  * @filename: the name of the tips file to parse  * @error: return location for a #GError  *   * Reads a gimp-tips XML file, creates a new #GimpTip for  * each tip entry and returns a #GList of them. If a parser  * error occurs at some point, the uncompleted list is  * returned and @error is set (unless @error is %NULL).  * The message set in @error contains a detailed description  * of the problem.  *   * Return value: a #Glist of #GimpTips.  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_tips_from_file (const gchar * filename,GError ** error)
name|gimp_tips_from_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GMarkupParseContext
modifier|*
name|context
decl_stmt|;
name|TipsParser
modifier|*
name|parser
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|tips_locale
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|gsize
name|bytes
decl_stmt|;
name|gchar
name|buf
index|[
literal|4096
index|]
decl_stmt|;
name|GList
modifier|*
name|tips
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fp
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Your GIMP tips file appears to be missing! "
literal|"There should be a file called '%s'. "
literal|"Please check your installation."
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|parser
operator|=
name|g_new0
argument_list|(
name|TipsParser
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|parser
operator|->
name|filename
operator|=
name|filename
expr_stmt|;
name|parser
operator|->
name|value
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
comment|/* This is a special string to specify the language identifier to      look for in the gimp-tips.xml file. Please translate the C in it      according to the name of the po file used for gimp-tips.xml.      E.g. for the german translation, that would be "tips-locale:de".    */
name|tips_locale
operator|=
name|_
argument_list|(
literal|"tips-locale:C"
argument_list|)
expr_stmt|;
if|if
condition|(
name|strncmp
argument_list|(
name|tips_locale
argument_list|,
literal|"tips-locale:"
argument_list|,
literal|12
argument_list|)
operator|==
literal|0
condition|)
block|{
name|tips_locale
operator|+=
literal|12
expr_stmt|;
if|if
condition|(
operator|*
name|tips_locale
operator|&&
operator|*
name|tips_locale
operator|!=
literal|'C'
condition|)
name|parser
operator|->
name|locale
operator|=
name|tips_locale
expr_stmt|;
block|}
else|else
name|g_warning
argument_list|(
literal|"Wrong translation for 'tips-locale:', fix the translation!"
argument_list|)
expr_stmt|;
name|context
operator|=
name|g_markup_parse_context_new
argument_list|(
operator|&
name|markup_parser
argument_list|,
literal|0
argument_list|,
name|parser
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|bytes
operator|=
name|fread
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|gchar
argument_list|)
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|fp
argument_list|)
operator|)
operator|>
literal|0
operator|&&
name|g_markup_parse_context_parse
argument_list|(
name|context
argument_list|,
name|buf
argument_list|,
name|bytes
argument_list|,
name|error
argument_list|)
condition|)
empty_stmt|;
if|if
condition|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
condition|)
name|g_markup_parse_context_end_parse
argument_list|(
name|context
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|g_markup_parse_context_free
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|tips
operator|=
name|g_list_reverse
argument_list|(
name|parser
operator|->
name|tips
argument_list|)
expr_stmt|;
name|gimp_tip_free
argument_list|(
name|parser
operator|->
name|current_tip
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|parser
operator|->
name|value
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|parser
argument_list|)
expr_stmt|;
return|return
name|tips
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tips_free (GList * tips)
name|gimp_tips_free
parameter_list|(
name|GList
modifier|*
name|tips
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|tips
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
name|gimp_tip_free
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|tips
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_parser_start_element (GMarkupParseContext * context,const gchar * element_name,const gchar ** attribute_names,const gchar ** attribute_values,gpointer user_data,GError ** error)
name|tips_parser_start_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_values
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|TipsParser
modifier|*
name|parser
init|=
operator|(
name|TipsParser
operator|*
operator|)
name|user_data
decl_stmt|;
switch|switch
condition|(
name|parser
operator|->
name|state
condition|)
block|{
case|case
name|TIPS_START
case|:
if|if
condition|(
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"gimp-tips"
argument_list|)
operator|==
literal|0
condition|)
name|parser
operator|->
name|state
operator|=
name|TIPS_IN_TIPS
expr_stmt|;
else|else
name|tips_parser_start_unknown
argument_list|(
name|parser
argument_list|)
expr_stmt|;
break|break;
case|case
name|TIPS_IN_TIPS
case|:
if|if
condition|(
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"tip"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|parser
operator|->
name|state
operator|=
name|TIPS_IN_TIP
expr_stmt|;
name|parser
operator|->
name|current_tip
operator|=
name|g_new0
argument_list|(
name|GimpTip
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
name|tips_parser_start_unknown
argument_list|(
name|parser
argument_list|)
expr_stmt|;
break|break;
case|case
name|TIPS_IN_TIP
case|:
if|if
condition|(
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"welcome"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|parser
operator|->
name|state
operator|=
name|TIPS_IN_WELCOME
expr_stmt|;
name|tips_parser_parse_locale
argument_list|(
name|parser
argument_list|,
name|attribute_names
argument_list|,
name|attribute_values
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"thetip"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|parser
operator|->
name|state
operator|=
name|TIPS_IN_THETIP
expr_stmt|;
name|tips_parser_parse_locale
argument_list|(
name|parser
argument_list|,
name|attribute_names
argument_list|,
name|attribute_values
argument_list|)
expr_stmt|;
block|}
else|else
name|tips_parser_start_unknown
argument_list|(
name|parser
argument_list|)
expr_stmt|;
break|break;
case|case
name|TIPS_IN_WELCOME
case|:
case|case
name|TIPS_IN_THETIP
case|:
if|if
condition|(
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"b"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"big"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"tt"
argument_list|)
operator|==
literal|0
condition|)
name|tips_parser_start_markup
argument_list|(
name|parser
argument_list|,
name|element_name
argument_list|)
expr_stmt|;
else|else
name|tips_parser_start_unknown
argument_list|(
name|parser
argument_list|)
expr_stmt|;
break|break;
case|case
name|TIPS_IN_UNKNOWN
case|:
name|tips_parser_start_unknown
argument_list|(
name|parser
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_parser_end_element (GMarkupParseContext * context,const gchar * element_name,gpointer user_data,GError ** error)
name|tips_parser_end_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|TipsParser
modifier|*
name|parser
init|=
operator|(
name|TipsParser
operator|*
operator|)
name|user_data
decl_stmt|;
switch|switch
condition|(
name|parser
operator|->
name|state
condition|)
block|{
case|case
name|TIPS_START
case|:
name|g_warning
argument_list|(
literal|"tips_parser: This shouldn't happen.\n"
argument_list|)
expr_stmt|;
break|break;
case|case
name|TIPS_IN_TIPS
case|:
name|parser
operator|->
name|state
operator|=
name|TIPS_START
expr_stmt|;
break|break;
case|case
name|TIPS_IN_TIP
case|:
name|parser
operator|->
name|tips
operator|=
name|g_list_prepend
argument_list|(
name|parser
operator|->
name|tips
argument_list|,
name|parser
operator|->
name|current_tip
argument_list|)
expr_stmt|;
name|parser
operator|->
name|current_tip
operator|=
name|NULL
expr_stmt|;
name|parser
operator|->
name|state
operator|=
name|TIPS_IN_TIPS
expr_stmt|;
break|break;
case|case
name|TIPS_IN_WELCOME
case|:
if|if
condition|(
name|parser
operator|->
name|markup_depth
operator|==
literal|0
condition|)
block|{
name|tips_parser_set_by_locale
argument_list|(
name|parser
argument_list|,
operator|&
name|parser
operator|->
name|current_tip
operator|->
name|welcome
argument_list|)
expr_stmt|;
name|g_string_assign
argument_list|(
name|parser
operator|->
name|value
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|parser
operator|->
name|state
operator|=
name|TIPS_IN_TIP
expr_stmt|;
block|}
else|else
name|tips_parser_end_markup
argument_list|(
name|parser
argument_list|,
name|element_name
argument_list|)
expr_stmt|;
break|break;
case|case
name|TIPS_IN_THETIP
case|:
if|if
condition|(
name|parser
operator|->
name|markup_depth
operator|==
literal|0
condition|)
block|{
name|tips_parser_set_by_locale
argument_list|(
name|parser
argument_list|,
operator|&
name|parser
operator|->
name|current_tip
operator|->
name|thetip
argument_list|)
expr_stmt|;
name|g_string_assign
argument_list|(
name|parser
operator|->
name|value
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|parser
operator|->
name|state
operator|=
name|TIPS_IN_TIP
expr_stmt|;
block|}
else|else
name|tips_parser_end_markup
argument_list|(
name|parser
argument_list|,
name|element_name
argument_list|)
expr_stmt|;
break|break;
case|case
name|TIPS_IN_UNKNOWN
case|:
name|tips_parser_end_unknown
argument_list|(
name|parser
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_parser_characters (GMarkupParseContext * context,const gchar * text,gsize text_len,gpointer user_data,GError ** error)
name|tips_parser_characters
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gsize
name|text_len
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|TipsParser
modifier|*
name|parser
init|=
operator|(
name|TipsParser
operator|*
operator|)
name|user_data
decl_stmt|;
switch|switch
condition|(
name|parser
operator|->
name|state
condition|)
block|{
case|case
name|TIPS_IN_WELCOME
case|:
case|case
name|TIPS_IN_THETIP
case|:
if|if
condition|(
name|parser
operator|->
name|locale_state
operator|!=
name|TIPS_LOCALE_MISMATCH
condition|)
block|{
name|gint
name|i
decl_stmt|;
comment|/* strip tabs, newlines and adjacent whitespace */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|text_len
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|text
index|[
name|i
index|]
operator|!=
literal|' '
operator|&&
name|text
index|[
name|i
index|]
operator|!=
literal|'\t'
operator|&&
name|text
index|[
name|i
index|]
operator|!=
literal|'\n'
operator|&&
name|text
index|[
name|i
index|]
operator|!=
literal|'\r'
condition|)
name|g_string_append_c
argument_list|(
name|parser
operator|->
name|value
argument_list|,
name|text
index|[
name|i
index|]
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|parser
operator|->
name|value
operator|->
name|len
operator|>
literal|0
operator|&&
name|parser
operator|->
name|value
operator|->
name|str
index|[
name|parser
operator|->
name|value
operator|->
name|len
operator|-
literal|1
index|]
operator|!=
literal|' '
condition|)
name|g_string_append_c
argument_list|(
name|parser
operator|->
name|value
argument_list|,
literal|' '
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_parser_error (GMarkupParseContext * context,GError * error,gpointer user_data)
name|tips_parser_error
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
name|GError
modifier|*
name|error
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|TipsParser
modifier|*
name|parser
init|=
operator|(
name|TipsParser
operator|*
operator|)
name|user_data
decl_stmt|;
name|g_warning
argument_list|(
literal|"%s: %s"
argument_list|,
name|parser
operator|->
name|filename
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_parser_start_markup (TipsParser * parser,const gchar * markup_name)
name|tips_parser_start_markup
parameter_list|(
name|TipsParser
modifier|*
name|parser
parameter_list|,
specifier|const
name|gchar
modifier|*
name|markup_name
parameter_list|)
block|{
name|parser
operator|->
name|markup_depth
operator|++
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|parser
operator|->
name|value
argument_list|,
literal|"<%s>"
argument_list|,
name|markup_name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_parser_end_markup (TipsParser * parser,const gchar * markup_name)
name|tips_parser_end_markup
parameter_list|(
name|TipsParser
modifier|*
name|parser
parameter_list|,
specifier|const
name|gchar
modifier|*
name|markup_name
parameter_list|)
block|{
name|g_assert
argument_list|(
name|parser
operator|->
name|markup_depth
operator|>
literal|0
argument_list|)
expr_stmt|;
name|parser
operator|->
name|markup_depth
operator|--
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|parser
operator|->
name|value
argument_list|,
literal|"</%s>"
argument_list|,
name|markup_name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_parser_start_unknown (TipsParser * parser)
name|tips_parser_start_unknown
parameter_list|(
name|TipsParser
modifier|*
name|parser
parameter_list|)
block|{
if|if
condition|(
name|parser
operator|->
name|unknown_depth
operator|==
literal|0
condition|)
name|parser
operator|->
name|last_known_state
operator|=
name|parser
operator|->
name|state
expr_stmt|;
name|parser
operator|->
name|state
operator|=
name|TIPS_IN_UNKNOWN
expr_stmt|;
name|parser
operator|->
name|unknown_depth
operator|++
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_parser_end_unknown (TipsParser * parser)
name|tips_parser_end_unknown
parameter_list|(
name|TipsParser
modifier|*
name|parser
parameter_list|)
block|{
name|g_assert
argument_list|(
name|parser
operator|->
name|unknown_depth
operator|>
literal|0
operator|&&
name|parser
operator|->
name|state
operator|==
name|TIPS_IN_UNKNOWN
argument_list|)
expr_stmt|;
name|parser
operator|->
name|unknown_depth
operator|--
expr_stmt|;
if|if
condition|(
name|parser
operator|->
name|unknown_depth
operator|==
literal|0
condition|)
name|parser
operator|->
name|state
operator|=
name|parser
operator|->
name|last_known_state
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_parser_parse_locale (TipsParser * parser,const gchar ** names,const gchar ** values)
name|tips_parser_parse_locale
parameter_list|(
name|TipsParser
modifier|*
name|parser
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|values
parameter_list|)
block|{
name|parser
operator|->
name|locale_state
operator|=
name|TIPS_LOCALE_NONE
expr_stmt|;
while|while
condition|(
operator|*
name|names
operator|&&
operator|*
name|values
condition|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
operator|*
name|names
argument_list|,
literal|"xml:lang"
argument_list|)
operator|==
literal|0
operator|&&
operator|*
operator|*
name|values
condition|)
block|{
name|parser
operator|->
name|locale_state
operator|=
operator|(
name|parser
operator|->
name|locale
operator|&&
name|strcmp
argument_list|(
operator|*
name|values
argument_list|,
name|parser
operator|->
name|locale
argument_list|)
operator|==
literal|0
condition|?
name|TIPS_LOCALE_MATCH
else|:
name|TIPS_LOCALE_MISMATCH
operator|)
expr_stmt|;
block|}
name|names
operator|++
expr_stmt|;
name|values
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_parser_set_by_locale (TipsParser * parser,gchar ** dest)
name|tips_parser_set_by_locale
parameter_list|(
name|TipsParser
modifier|*
name|parser
parameter_list|,
name|gchar
modifier|*
modifier|*
name|dest
parameter_list|)
block|{
switch|switch
condition|(
name|parser
operator|->
name|locale_state
condition|)
block|{
case|case
name|TIPS_LOCALE_NONE
case|:
if|if
condition|(
operator|!
name|parser
operator|->
name|locale
condition|)
block|{
name|g_free
argument_list|(
operator|*
name|dest
argument_list|)
expr_stmt|;
operator|*
name|dest
operator|=
name|g_strdup
argument_list|(
name|parser
operator|->
name|value
operator|->
name|str
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|*
name|dest
operator|==
name|NULL
condition|)
block|{
operator|*
name|dest
operator|=
name|g_strdup
argument_list|(
name|parser
operator|->
name|value
operator|->
name|str
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|TIPS_LOCALE_MATCH
case|:
name|g_free
argument_list|(
operator|*
name|dest
argument_list|)
expr_stmt|;
operator|*
name|dest
operator|=
name|g_strdup
argument_list|(
name|parser
operator|->
name|value
operator|->
name|str
argument_list|)
expr_stmt|;
break|break;
case|case
name|TIPS_LOCALE_MISMATCH
case|:
break|break;
block|}
block|}
end_function

end_unit

