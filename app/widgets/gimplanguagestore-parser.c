begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplanguagestore-parser.c  * Copyright (C) 2008, 2009  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpxmlparser.h"
end_include

begin_include
include|#
directive|include
file|"gimplanguagestore.h"
end_include

begin_include
include|#
directive|include
file|"gimplanguagestore-parser.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29c94b3c0103
block|{
DECL|enumerator|ISO_CODES_START
name|ISO_CODES_START
block|,
DECL|enumerator|ISO_CODES_IN_ENTRIES
name|ISO_CODES_IN_ENTRIES
block|,
DECL|enumerator|ISO_CODES_IN_ENTRY
name|ISO_CODES_IN_ENTRY
block|,
DECL|enumerator|ISO_CODES_IN_UNKNOWN
name|ISO_CODES_IN_UNKNOWN
DECL|typedef|IsoCodesParserState
block|}
name|IsoCodesParserState
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29c94b3c0208
block|{
DECL|member|state
name|IsoCodesParserState
name|state
decl_stmt|;
DECL|member|last_known_state
name|IsoCodesParserState
name|last_known_state
decl_stmt|;
DECL|member|unknown_depth
name|gint
name|unknown_depth
decl_stmt|;
DECL|member|store
name|GimpLanguageStore
modifier|*
name|store
decl_stmt|;
DECL|typedef|IsoCodesParser
block|}
name|IsoCodesParser
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|iso_codes_parser_start_element
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
name|iso_codes_parser_end_element
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
name|iso_codes_parser_start_unknown
parameter_list|(
name|IsoCodesParser
modifier|*
name|parser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|iso_codes_parser_end_unknown
parameter_list|(
name|IsoCodesParser
modifier|*
name|parser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_language_store_self_l10n
parameter_list|(
name|GimpLanguageStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|lang
parameter_list|,
specifier|const
name|gchar
modifier|*
name|code
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|iso_codes_parser_init (void)
name|iso_codes_parser_init
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|initialized
condition|)
return|return;
ifdef|#
directive|ifdef
name|G_OS_WIN32
comment|/*  on Win32, assume iso-codes is installed in the same location as GIMP  */
name|bindtextdomain
argument_list|(
literal|"iso_639"
argument_list|,
name|gimp_locale_directory
argument_list|()
argument_list|)
expr_stmt|;
else|#
directive|else
name|bindtextdomain
argument_list|(
literal|"iso_639"
argument_list|,
name|ISO_CODES_LOCALEDIR
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|bind_textdomain_codeset
argument_list|(
literal|"iso_639"
argument_list|,
literal|"UTF-8"
argument_list|)
expr_stmt|;
name|initialized
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_language_store_parse_iso_codes (GimpLanguageStore * store,GError ** error)
name|gimp_language_store_parse_iso_codes
parameter_list|(
name|GimpLanguageStore
modifier|*
name|store
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|HAVE_ISO_CODES
specifier|static
specifier|const
name|GMarkupParser
name|markup_parser
init|=
block|{
name|iso_codes_parser_start_element
block|,
name|iso_codes_parser_end_element
block|,
name|NULL
block|,
comment|/*  characters   */
name|NULL
block|,
comment|/*  passthrough  */
name|NULL
comment|/*  error        */
block|}
decl_stmt|;
name|GimpXmlParser
modifier|*
name|xml_parser
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|IsoCodesParser
name|parser
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LANGUAGE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|FALSE
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
name|FALSE
argument_list|)
expr_stmt|;
name|iso_codes_parser_init
argument_list|()
expr_stmt|;
name|parser
operator|.
name|store
operator|=
name|g_object_ref
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|xml_parser
operator|=
name|gimp_xml_parser_new
argument_list|(
operator|&
name|markup_parser
argument_list|,
operator|&
name|parser
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
literal|".."
argument_list|,
literal|".."
argument_list|,
literal|"xml"
argument_list|,
literal|"iso-codes"
argument_list|,
literal|"iso_639.xml"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|#
directive|else
name|filename
operator|=
name|g_build_filename
argument_list|(
name|ISO_CODES_LOCATION
argument_list|,
literal|"iso_639.xml"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|success
operator|=
name|gimp_xml_parser_parse_file
argument_list|(
name|xml_parser
argument_list|,
name|filename
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gimp_xml_parser_free
argument_list|(
name|xml_parser
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|parser
operator|.
name|store
argument_list|)
expr_stmt|;
return|return
name|success
return|;
endif|#
directive|endif
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|iso_codes_parser_entry (IsoCodesParser * parser,const gchar ** names,const gchar ** values)
name|iso_codes_parser_entry
parameter_list|(
name|IsoCodesParser
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
specifier|const
name|gchar
modifier|*
name|lang
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|code
init|=
name|NULL
decl_stmt|;
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
literal|"name"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|lang
operator|=
operator|*
name|values
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
operator|*
name|names
argument_list|,
literal|"iso_639_2B_code"
argument_list|)
operator|==
literal|0
operator|&&
name|code
operator|==
name|NULL
condition|)
block|{
comment|/* 2-letter ISO 639-1 codes have priority.            * But some languages have no 2-letter code.            * Ex: Asturian (ast).            */
name|code
operator|=
operator|*
name|values
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
operator|*
name|names
argument_list|,
literal|"iso_639_2T_code"
argument_list|)
operator|==
literal|0
operator|&&
name|code
operator|==
name|NULL
condition|)
block|{
name|code
operator|=
operator|*
name|values
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
operator|*
name|names
argument_list|,
literal|"iso_639_1_code"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|code
operator|=
operator|*
name|values
expr_stmt|;
block|}
name|names
operator|++
expr_stmt|;
name|values
operator|++
expr_stmt|;
block|}
comment|/* This is a hack for some special exception.    * It seems localization won't work for the base language "zh". Probably because    * written locale dialect are too different. So we have to be accurate and localize    * separately each Chinese dialect we support.    *    * There was unfortunately no cleaner way to achieve this since there is no standardized    * link between regions in iso-3166 and base languages in iso-639, which would allow    * automatization for generating locale dialects codes.    */
if|if
condition|(
name|g_strcmp0
argument_list|(
name|code
argument_list|,
literal|"zh"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gimp_language_store_self_l10n
argument_list|(
name|parser
operator|->
name|store
argument_list|,
literal|"Chinese"
argument_list|,
literal|"zh_CN"
argument_list|)
expr_stmt|;
name|gimp_language_store_self_l10n
argument_list|(
name|parser
operator|->
name|store
argument_list|,
literal|"Chinese"
argument_list|,
literal|"zh_TW"
argument_list|)
expr_stmt|;
name|gimp_language_store_self_l10n
argument_list|(
name|parser
operator|->
name|store
argument_list|,
literal|"Chinese"
argument_list|,
literal|"zh_HK"
argument_list|)
expr_stmt|;
block|}
else|else
name|gimp_language_store_self_l10n
argument_list|(
name|parser
operator|->
name|store
argument_list|,
name|lang
argument_list|,
name|code
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* If possible, we want to localize a language in itself.  * If it fails, fallback to the currently selected language, then to system lang.  * Only fallback to C (en_US) as a last resort.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_language_store_self_l10n (GimpLanguageStore * store,const gchar * lang,const gchar * code)
name|gimp_language_store_self_l10n
parameter_list|(
name|GimpLanguageStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|lang
parameter_list|,
specifier|const
name|gchar
modifier|*
name|code
parameter_list|)
block|{
if|if
condition|(
name|lang
operator|&&
operator|*
name|lang
operator|&&
name|code
operator|&&
operator|*
name|code
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|semicolon
decl_stmt|;
comment|/* English does not need localization. */
if|if
condition|(
name|g_strcmp0
argument_list|(
name|code
argument_list|,
literal|"en"
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|gchar
modifier|*
name|current_lang
init|=
name|g_strdup
argument_list|(
name|g_getenv
argument_list|(
literal|"LANGUAGE"
argument_list|)
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|temp_lang
decl_stmt|;
if|if
condition|(
name|current_lang
condition|)
name|temp_lang
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s:%s:%s"
argument_list|,
name|code
argument_list|,
name|current_lang
argument_list|,
name|setlocale
argument_list|(
name|LC_ALL
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|temp_lang
operator|=
name|g_strdup
argument_list|(
name|code
argument_list|)
expr_stmt|;
comment|/* Temporarily change the localization language. */
name|g_setenv
argument_list|(
literal|"LANGUAGE"
argument_list|,
name|temp_lang
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|setlocale
argument_list|(
name|LC_ALL
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|lang
operator|=
name|dgettext
argument_list|(
literal|"iso_639"
argument_list|,
name|lang
argument_list|)
expr_stmt|;
if|if
condition|(
name|current_lang
condition|)
name|g_setenv
argument_list|(
literal|"LANGUAGE"
argument_list|,
name|current_lang
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
else|else
name|g_unsetenv
argument_list|(
literal|"LANGUAGE"
argument_list|)
expr_stmt|;
name|setlocale
argument_list|(
name|LC_ALL
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|current_lang
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp_lang
argument_list|)
expr_stmt|;
block|}
comment|/*  there might be several language names; use the first one  */
name|semicolon
operator|=
name|strchr
argument_list|(
name|lang
argument_list|,
literal|';'
argument_list|)
expr_stmt|;
if|if
condition|(
name|semicolon
condition|)
block|{
name|gchar
modifier|*
name|first
init|=
name|g_strndup
argument_list|(
name|lang
argument_list|,
name|semicolon
operator|-
name|lang
argument_list|)
decl_stmt|;
name|gimp_language_store_add
argument_list|(
name|store
argument_list|,
name|first
argument_list|,
name|code
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|first
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_language_store_add
argument_list|(
name|store
argument_list|,
name|lang
argument_list|,
name|code
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|iso_codes_parser_start_element (GMarkupParseContext * context,const gchar * element_name,const gchar ** attribute_names,const gchar ** attribute_values,gpointer user_data,GError ** error)
name|iso_codes_parser_start_element
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
name|IsoCodesParser
modifier|*
name|parser
init|=
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
name|ISO_CODES_START
case|:
if|if
condition|(
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"iso_639_entries"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|parser
operator|->
name|state
operator|=
name|ISO_CODES_IN_ENTRIES
expr_stmt|;
break|break;
block|}
case|case
name|ISO_CODES_IN_ENTRIES
case|:
if|if
condition|(
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"iso_639_entry"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|parser
operator|->
name|state
operator|=
name|ISO_CODES_IN_ENTRY
expr_stmt|;
name|iso_codes_parser_entry
argument_list|(
name|parser
argument_list|,
name|attribute_names
argument_list|,
name|attribute_values
argument_list|)
expr_stmt|;
break|break;
block|}
case|case
name|ISO_CODES_IN_ENTRY
case|:
case|case
name|ISO_CODES_IN_UNKNOWN
case|:
name|iso_codes_parser_start_unknown
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
DECL|function|iso_codes_parser_end_element (GMarkupParseContext * context,const gchar * element_name,gpointer user_data,GError ** error)
name|iso_codes_parser_end_element
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
name|IsoCodesParser
modifier|*
name|parser
init|=
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
name|ISO_CODES_START
case|:
name|g_warning
argument_list|(
literal|"%s: shouldn't get here"
argument_list|,
name|G_STRLOC
argument_list|)
expr_stmt|;
break|break;
case|case
name|ISO_CODES_IN_ENTRIES
case|:
name|parser
operator|->
name|state
operator|=
name|ISO_CODES_START
expr_stmt|;
break|break;
case|case
name|ISO_CODES_IN_ENTRY
case|:
name|parser
operator|->
name|state
operator|=
name|ISO_CODES_IN_ENTRIES
expr_stmt|;
break|break;
case|case
name|ISO_CODES_IN_UNKNOWN
case|:
name|iso_codes_parser_end_unknown
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
DECL|function|iso_codes_parser_start_unknown (IsoCodesParser * parser)
name|iso_codes_parser_start_unknown
parameter_list|(
name|IsoCodesParser
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
name|ISO_CODES_IN_UNKNOWN
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
DECL|function|iso_codes_parser_end_unknown (IsoCodesParser * parser)
name|iso_codes_parser_end_unknown
parameter_list|(
name|IsoCodesParser
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
name|ISO_CODES_IN_UNKNOWN
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

end_unit

