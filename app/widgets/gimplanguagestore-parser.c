begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplanguagestore-parser.c  * Copyright (C) 2008, 2009  Sven Neumann<sven@gimp.org>  * Copyright (C) 2013  Jehan<jehan at girinstud.io>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<locale.h>
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
DECL|enum|__anon2a20ade20103
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
DECL|struct|__anon2a20ade20208
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
DECL|member|base_lang_list
name|GHashTable
modifier|*
name|base_lang_list
decl_stmt|;
DECL|typedef|IsoCodesParser
block|}
name|IsoCodesParser
typedef|;
end_typedef

begin_function_decl
specifier|static
name|gboolean
name|parse_iso_codes
parameter_list|(
name|GHashTable
modifier|*
name|base_lang_list
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_ISO_CODES
end_ifdef

begin_function_decl
specifier|static
name|void
name|iso_codes_parser_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_ISO_CODES */
end_comment

begin_comment
comment|/*  * Language lists that we want to generate only once at program startup:  * @l10n_lang_list: all available localizations self-localized;  * @all_lang_list: all known languages, in the user-selected language.  */
end_comment

begin_decl_stmt
DECL|variable|l10n_lang_list
specifier|static
name|GHashTable
modifier|*
name|l10n_lang_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|all_lang_list
specifier|static
name|GHashTable
modifier|*
name|all_lang_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/********************\  * Public Functions * \********************/
end_comment

begin_comment
comment|/*  * Initialize and run the language listing parser. This call must be  * made only once, at program initialization, but after language_init().  */
end_comment

begin_function
name|void
DECL|function|gimp_language_store_parser_init (void)
name|gimp_language_store_parser_init
parameter_list|(
name|void
parameter_list|)
block|{
name|GHashTable
modifier|*
name|base_lang_list
decl_stmt|;
name|gchar
modifier|*
name|current_env
decl_stmt|;
name|GDir
modifier|*
name|locales_dir
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|GHashTableIter
name|lang_iter
decl_stmt|;
name|gpointer
name|key
decl_stmt|;
if|if
condition|(
name|l10n_lang_list
operator|!=
name|NULL
condition|)
block|{
name|g_warning
argument_list|(
literal|"gimp_language_store_parser_init() must be run only once."
argument_list|)
expr_stmt|;
return|return;
block|}
name|current_env
operator|=
name|g_strdup
argument_list|(
name|g_getenv
argument_list|(
literal|"LANGUAGE"
argument_list|)
argument_list|)
expr_stmt|;
name|l10n_lang_list
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|all_lang_list
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|base_lang_list
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
comment|/* Check all locales we have translations for. */
name|locales_dir
operator|=
name|g_dir_open
argument_list|(
name|gimp_locale_directory
argument_list|()
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|locales_dir
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|locale
decl_stmt|;
while|while
condition|(
operator|(
name|locale
operator|=
name|g_dir_read_name
argument_list|(
name|locales_dir
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|g_build_filename
argument_list|(
name|gimp_locale_directory
argument_list|()
argument_list|,
name|locale
argument_list|,
literal|"LC_MESSAGES"
argument_list|,
name|GETTEXT_PACKAGE
literal|".mo"
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|delimiter
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|base_code
init|=
name|NULL
decl_stmt|;
name|delimiter
operator|=
name|strchr
argument_list|(
name|locale
argument_list|,
literal|'_'
argument_list|)
expr_stmt|;
if|if
condition|(
name|delimiter
condition|)
name|base_code
operator|=
name|g_strndup
argument_list|(
name|locale
argument_list|,
name|delimiter
operator|-
name|locale
argument_list|)
expr_stmt|;
else|else
name|base_code
operator|=
name|g_strdup
argument_list|(
name|locale
argument_list|)
expr_stmt|;
name|delimiter
operator|=
name|strchr
argument_list|(
name|base_code
argument_list|,
literal|'@'
argument_list|)
expr_stmt|;
if|if
condition|(
name|delimiter
condition|)
block|{
name|gchar
modifier|*
name|temp
init|=
name|base_code
decl_stmt|;
name|base_code
operator|=
name|g_strndup
argument_list|(
name|base_code
argument_list|,
name|delimiter
operator|-
name|base_code
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
block|}
comment|/* Save the full language code. */
name|g_hash_table_insert
argument_list|(
name|l10n_lang_list
argument_list|,
name|g_strdup
argument_list|(
name|locale
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Save the base language code. */
name|g_hash_table_insert
argument_list|(
name|base_lang_list
argument_list|,
name|base_code
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_dir_close
argument_list|(
name|locales_dir
argument_list|)
expr_stmt|;
block|}
comment|/* Parse ISO-639 file to get full list of language and their names. */
name|parse_iso_codes
argument_list|(
name|base_lang_list
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
comment|/* Generate the localized language names. */
name|g_hash_table_iter_init
argument_list|(
operator|&
name|lang_iter
argument_list|,
name|l10n_lang_list
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_hash_table_iter_next
argument_list|(
operator|&
name|lang_iter
argument_list|,
operator|&
name|key
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|code
init|=
operator|(
name|gchar
operator|*
operator|)
name|key
decl_stmt|;
name|gchar
modifier|*
name|localized_name
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|english_name
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|delimiter
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|base_code
init|=
name|NULL
decl_stmt|;
name|delimiter
operator|=
name|strchr
argument_list|(
name|code
argument_list|,
literal|'_'
argument_list|)
expr_stmt|;
if|if
condition|(
name|delimiter
condition|)
name|base_code
operator|=
name|g_strndup
argument_list|(
name|code
argument_list|,
name|delimiter
operator|-
name|code
argument_list|)
expr_stmt|;
else|else
name|base_code
operator|=
name|g_strdup
argument_list|(
name|code
argument_list|)
expr_stmt|;
name|delimiter
operator|=
name|strchr
argument_list|(
name|base_code
argument_list|,
literal|'@'
argument_list|)
expr_stmt|;
if|if
condition|(
name|delimiter
condition|)
block|{
name|gchar
modifier|*
name|temp
init|=
name|base_code
decl_stmt|;
name|base_code
operator|=
name|g_strndup
argument_list|(
name|base_code
argument_list|,
name|delimiter
operator|-
name|base_code
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
block|}
name|english_name
operator|=
operator|(
name|gchar
operator|*
operator|)
operator|(
name|g_hash_table_lookup
argument_list|(
name|base_lang_list
argument_list|,
name|base_code
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|english_name
condition|)
block|{
name|gchar
modifier|*
name|semicolon
decl_stmt|;
comment|/* If possible, we want to localize a language in itself.            * If it fails, gettext fallbacks to C (en_US) itself.            */
name|g_setenv
argument_list|(
literal|"LANGUAGE"
argument_list|,
name|code
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
name|localized_name
operator|=
name|g_strdup
argument_list|(
name|dgettext
argument_list|(
literal|"iso_639"
argument_list|,
name|english_name
argument_list|)
argument_list|)
expr_stmt|;
comment|/* If original and localized names are the same for other than English,            * maybe localization failed. Try now in the main dialect. */
if|if
condition|(
name|g_strcmp0
argument_list|(
name|english_name
argument_list|,
name|localized_name
argument_list|)
operator|==
literal|0
operator|&&
name|g_strcmp0
argument_list|(
name|base_code
argument_list|,
literal|"en"
argument_list|)
operator|!=
literal|0
operator|&&
name|g_strcmp0
argument_list|(
name|code
argument_list|,
name|base_code
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|g_free
argument_list|(
name|localized_name
argument_list|)
expr_stmt|;
name|g_setenv
argument_list|(
literal|"LANGUAGE"
argument_list|,
name|base_code
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
name|localized_name
operator|=
name|g_strdup
argument_list|(
name|dgettext
argument_list|(
literal|"iso_639"
argument_list|,
name|english_name
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*  there might be several language names; use the first one  */
name|semicolon
operator|=
name|strchr
argument_list|(
name|localized_name
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
name|temp
init|=
name|localized_name
decl_stmt|;
name|localized_name
operator|=
name|g_strndup
argument_list|(
name|localized_name
argument_list|,
name|semicolon
operator|-
name|localized_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
block|}
block|}
name|g_hash_table_replace
argument_list|(
name|l10n_lang_list
argument_list|,
name|g_strdup
argument_list|(
name|code
argument_list|)
argument_list|,
name|g_strdup_printf
argument_list|(
literal|"%s [%s]"
argument_list|,
name|localized_name
condition|?
name|localized_name
else|:
literal|"???"
argument_list|,
name|code
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|localized_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|base_code
argument_list|)
expr_stmt|;
block|}
comment|/*  Add special entries for system locale.    *  We want the system locale to be localized in itself. */
name|g_setenv
argument_list|(
literal|"LANGUAGE"
argument_list|,
name|setlocale
argument_list|(
name|LC_ALL
argument_list|,
name|NULL
argument_list|)
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
comment|/* g_str_hash() does not accept NULL. I give an empty code instead.    * Other solution would to create a custom hash. */
name|g_hash_table_insert
argument_list|(
name|l10n_lang_list
argument_list|,
name|g_strdup
argument_list|(
literal|""
argument_list|)
argument_list|,
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"System Language"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Go back to original localization. */
if|if
condition|(
name|current_env
condition|)
block|{
name|g_setenv
argument_list|(
literal|"LANGUAGE"
argument_list|,
name|current_env
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|current_env
argument_list|)
expr_stmt|;
block|}
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
comment|/* Add special entry for C (en_US). */
name|g_hash_table_insert
argument_list|(
name|l10n_lang_list
argument_list|,
name|g_strdup
argument_list|(
literal|"en_US"
argument_list|)
argument_list|,
name|g_strdup
argument_list|(
literal|"English [en_US]"
argument_list|)
argument_list|)
expr_stmt|;
name|g_hash_table_destroy
argument_list|(
name|base_lang_list
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_language_store_parser_clean (void)
name|gimp_language_store_parser_clean
parameter_list|(
name|void
parameter_list|)
block|{
name|g_hash_table_destroy
argument_list|(
name|l10n_lang_list
argument_list|)
expr_stmt|;
name|g_hash_table_destroy
argument_list|(
name|all_lang_list
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * Returns a Hash table of languages.  * Keys and values are respectively language codes and names from the  * ISO-639 standard code.  *  * If @localization_only is TRUE, it returns only the list of available  * GIMP localizations, and language names are translated in their own  * locale.  * If @localization_only is FALSE, the full list of ISO-639 languages  * is returned, and language names are in the user-set locale.  *  * Do not free the list or elements of the list.  */
end_comment

begin_function
name|GHashTable
modifier|*
DECL|function|gimp_language_store_parser_get_languages (gboolean localization_only)
name|gimp_language_store_parser_get_languages
parameter_list|(
name|gboolean
name|localization_only
parameter_list|)
block|{
if|if
condition|(
name|localization_only
condition|)
return|return
name|l10n_lang_list
return|;
else|else
return|return
name|all_lang_list
return|;
block|}
end_function

begin_comment
comment|/*****************************\  * Private Parsing Functions * \*****************************/
end_comment

begin_comment
comment|/*  * Parse the ISO-639 code list if available on this system, and fill  * @base_lang_list with English names of all needed base codes.  *  * It will also fill the static @all_lang_list.  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|parse_iso_codes (GHashTable * base_lang_list,GError ** error)
name|parse_iso_codes
parameter_list|(
name|GHashTable
modifier|*
name|base_lang_list
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
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
name|GFile
modifier|*
name|file
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
name|base_lang_list
operator|=
name|g_hash_table_ref
argument_list|(
name|base_lang_list
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
if|#
directive|if
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
operator|||
name|defined
argument_list|(
name|PLATFORM_OSX
argument_list|)
name|file
operator|=
name|gimp_data_directory_file
argument_list|(
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
name|file
operator|=
name|g_file_new_for_path
argument_list|(
argument|ISO_CODES_LOCATION G_DIR_SEPARATOR_S
literal|"iso_639.xml"
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|success
operator|=
name|gimp_xml_parser_parse_gfile
argument_list|(
name|xml_parser
argument_list|,
name|file
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
operator|&&
operator|*
name|error
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: error parsing '%s': %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|g_file_get_path
argument_list|(
name|file
argument_list|)
argument_list|,
operator|(
operator|*
name|error
operator|)
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|gimp_xml_parser_free
argument_list|(
name|xml_parser
argument_list|)
expr_stmt|;
name|g_hash_table_unref
argument_list|(
name|parser
operator|.
name|base_lang_list
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* HAVE_ISO_CODES */
return|return
name|success
return|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_ISO_CODES
end_ifdef

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
name|lang
operator|=
operator|*
name|values
expr_stmt|;
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
comment|/* 2-letter ISO 639-1 codes have priority.          * But some languages have no 2-letter code. Ex: Asturian (ast).          */
name|code
operator|=
operator|*
name|values
expr_stmt|;
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
name|code
operator|=
operator|*
name|values
expr_stmt|;
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
name|code
operator|=
operator|*
name|values
expr_stmt|;
name|names
operator|++
expr_stmt|;
name|values
operator|++
expr_stmt|;
block|}
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
name|gchar
modifier|*
name|semicolon
decl_stmt|;
name|gchar
modifier|*
name|localized_name
init|=
name|g_strdup
argument_list|(
name|dgettext
argument_list|(
literal|"iso_639"
argument_list|,
name|lang
argument_list|)
argument_list|)
decl_stmt|;
comment|/* If the language is in our base table, we save its standard English name. */
if|if
condition|(
name|g_hash_table_contains
argument_list|(
name|parser
operator|->
name|base_lang_list
argument_list|,
name|code
argument_list|)
condition|)
name|g_hash_table_replace
argument_list|(
name|parser
operator|->
name|base_lang_list
argument_list|,
name|g_strdup
argument_list|(
name|code
argument_list|)
argument_list|,
name|g_strdup
argument_list|(
name|lang
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  there might be several language names; use the first one  */
name|semicolon
operator|=
name|strchr
argument_list|(
name|localized_name
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
name|temp
init|=
name|localized_name
decl_stmt|;
name|localized_name
operator|=
name|g_strndup
argument_list|(
name|localized_name
argument_list|,
name|semicolon
operator|-
name|localized_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
block|}
comment|/* In any case, we save the name in user-set language for all lang. */
name|g_hash_table_insert
argument_list|(
name|all_lang_list
argument_list|,
name|g_strdup
argument_list|(
name|code
argument_list|)
argument_list|,
name|localized_name
argument_list|)
expr_stmt|;
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
name|gimp_assert
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_ISO_CODES */
end_comment

end_unit

