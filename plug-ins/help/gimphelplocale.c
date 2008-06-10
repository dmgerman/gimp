begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2008 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  This code is written so that it can also be compiled standalone.  *  It shouldn't depend on libgimp.  */
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
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|"gimphelp.h"
end_include

begin_include
include|#
directive|include
file|"gimphelpprogress-private.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|DISABLE_NLS
end_ifdef

begin_define
DECL|macro|_ (String)
define|#
directive|define
name|_
parameter_list|(
name|String
parameter_list|)
value|(String)
end_define

begin_else
else|#
directive|else
end_else

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|locale_set_error
parameter_list|(
name|GError
modifier|*
modifier|*
name|error
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpHelpLocale
modifier|*
DECL|function|gimp_help_locale_new (const gchar * locale_id)
name|gimp_help_locale_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|locale_id
parameter_list|)
block|{
name|GimpHelpLocale
modifier|*
name|locale
init|=
name|g_slice_new0
argument_list|(
name|GimpHelpLocale
argument_list|)
decl_stmt|;
name|locale
operator|->
name|locale_id
operator|=
name|g_strdup
argument_list|(
name|locale_id
argument_list|)
expr_stmt|;
return|return
name|locale
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_help_locale_free (GimpHelpLocale * locale)
name|gimp_help_locale_free
parameter_list|(
name|GimpHelpLocale
modifier|*
name|locale
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|locale
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|locale
operator|->
name|help_id_mapping
condition|)
name|g_hash_table_destroy
argument_list|(
name|locale
operator|->
name|help_id_mapping
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|locale
operator|->
name|locale_id
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|locale
operator|->
name|help_missing
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|locale
operator|->
name|toplevel_items
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpHelpLocale
argument_list|,
name|locale
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_help_locale_map (GimpHelpLocale * locale,const gchar * help_id)
name|gimp_help_locale_map
parameter_list|(
name|GimpHelpLocale
modifier|*
name|locale
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|locale
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|locale
operator|->
name|help_id_mapping
condition|)
block|{
name|GimpHelpItem
modifier|*
name|item
init|=
name|g_hash_table_lookup
argument_list|(
name|locale
operator|->
name|help_id_mapping
argument_list|,
name|help_id
argument_list|)
decl_stmt|;
if|if
condition|(
name|item
condition|)
return|return
name|item
operator|->
name|ref
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*  the locale mapping parser  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29c7722f0103
block|{
DECL|enumerator|LOCALE_START
name|LOCALE_START
block|,
DECL|enumerator|LOCALE_IN_HELP
name|LOCALE_IN_HELP
block|,
DECL|enumerator|LOCALE_IN_ITEM
name|LOCALE_IN_ITEM
block|,
DECL|enumerator|LOCALE_IN_MISSING
name|LOCALE_IN_MISSING
block|,
DECL|enumerator|LOCALE_IN_UNKNOWN
name|LOCALE_IN_UNKNOWN
DECL|typedef|LocaleParserState
block|}
name|LocaleParserState
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29c7722f0208
block|{
DECL|member|file
name|GFile
modifier|*
name|file
decl_stmt|;
DECL|member|state
name|LocaleParserState
name|state
decl_stmt|;
DECL|member|last_known_state
name|LocaleParserState
name|last_known_state
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
DECL|member|locale
name|GimpHelpLocale
modifier|*
name|locale
decl_stmt|;
DECL|member|help_domain
specifier|const
name|gchar
modifier|*
name|help_domain
decl_stmt|;
DECL|member|id_attr_name
name|gchar
modifier|*
name|id_attr_name
decl_stmt|;
DECL|typedef|LocaleParser
block|}
name|LocaleParser
typedef|;
end_typedef

begin_function_decl
specifier|static
name|gboolean
name|locale_parser_parse
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
name|GimpHelpProgress
modifier|*
name|progress
parameter_list|,
name|GInputStream
modifier|*
name|stream
parameter_list|,
name|goffset
name|size
parameter_list|,
name|GCancellable
modifier|*
name|cancellable
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
name|locale_parser_start_element
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
name|locale_parser_end_element
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
name|locale_parser_error
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
name|locale_parser_start_unknown
parameter_list|(
name|LocaleParser
modifier|*
name|parser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|locale_parser_end_unknown
parameter_list|(
name|LocaleParser
modifier|*
name|parser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|locale_parser_parse_namespace
parameter_list|(
name|LocaleParser
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
name|locale_parser_parse_item
parameter_list|(
name|LocaleParser
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
name|locale_parser_parse_missing
parameter_list|(
name|LocaleParser
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

begin_decl_stmt
DECL|variable|markup_parser
specifier|static
specifier|const
name|GMarkupParser
name|markup_parser
init|=
block|{
name|locale_parser_start_element
block|,
name|locale_parser_end_element
block|,
name|NULL
block|,
comment|/*  characters   */
name|NULL
block|,
comment|/*  passthrough  */
name|locale_parser_error
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|gboolean
DECL|function|gimp_help_locale_parse (GimpHelpLocale * locale,const gchar * uri,const gchar * help_domain,GimpHelpProgress * progress,GError ** error)
name|gimp_help_locale_parse
parameter_list|(
name|GimpHelpLocale
modifier|*
name|locale
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
name|GimpHelpProgress
modifier|*
name|progress
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
name|GFile
modifier|*
name|file
decl_stmt|;
name|GFileInputStream
modifier|*
name|stream
decl_stmt|;
name|GCancellable
modifier|*
name|cancellable
init|=
name|NULL
decl_stmt|;
name|LocaleParser
name|parser
init|=
block|{
name|NULL
block|, }
decl_stmt|;
name|goffset
name|size
init|=
literal|0
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|locale
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
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
if|if
condition|(
name|locale
operator|->
name|help_id_mapping
condition|)
block|{
name|g_hash_table_destroy
argument_list|(
name|locale
operator|->
name|help_id_mapping
argument_list|)
expr_stmt|;
name|locale
operator|->
name|help_id_mapping
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|locale
operator|->
name|help_missing
condition|)
block|{
name|g_free
argument_list|(
name|locale
operator|->
name|help_missing
argument_list|)
expr_stmt|;
name|locale
operator|->
name|help_missing
operator|=
name|NULL
expr_stmt|;
block|}
ifdef|#
directive|ifdef
name|GIMP_HELP_DEBUG
name|g_printerr
argument_list|(
literal|"help (%s): parsing '%s' for locale \"%s\"\n"
argument_list|,
name|locale
operator|->
name|locale_id
argument_list|,
name|uri
argument_list|,
name|help_domain
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|file
operator|=
name|g_file_new_for_uri
argument_list|(
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
block|{
name|gchar
modifier|*
name|name
init|=
name|g_file_get_parse_name
argument_list|(
name|file
argument_list|)
decl_stmt|;
name|cancellable
operator|=
name|g_cancellable_new
argument_list|()
expr_stmt|;
name|_gimp_help_progress_start
argument_list|(
name|progress
argument_list|,
name|cancellable
argument_list|,
name|_
argument_list|(
literal|"Loading index from '%s'"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|cancellable
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|progress
condition|)
block|{
name|GFileInfo
modifier|*
name|info
init|=
name|g_file_query_info
argument_list|(
name|file
argument_list|,
name|G_FILE_ATTRIBUTE_STANDARD_SIZE
argument_list|,
literal|0
argument_list|,
name|cancellable
argument_list|,
name|error
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|info
condition|)
block|{
name|locale_set_error
argument_list|(
name|error
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|size
operator|=
name|g_file_info_get_size
argument_list|(
name|info
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
name|stream
operator|=
name|g_file_read
argument_list|(
name|file
argument_list|,
name|cancellable
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|stream
condition|)
block|{
name|locale_set_error
argument_list|(
name|error
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|parser
operator|.
name|file
operator|=
name|file
expr_stmt|;
name|parser
operator|.
name|value
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|parser
operator|.
name|locale
operator|=
name|locale
expr_stmt|;
name|parser
operator|.
name|help_domain
operator|=
name|help_domain
expr_stmt|;
name|parser
operator|.
name|id_attr_name
operator|=
name|g_strdup
argument_list|(
literal|"id"
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
operator|&
name|parser
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|success
operator|=
name|locale_parser_parse
argument_list|(
name|context
argument_list|,
name|progress
argument_list|,
name|G_INPUT_STREAM
argument_list|(
name|stream
argument_list|)
argument_list|,
name|size
argument_list|,
name|cancellable
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|_gimp_help_progress_finish
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|g_markup_parse_context_free
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|stream
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|parser
operator|.
name|value
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|parser
operator|.
name|id_attr_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
name|locale_set_error
argument_list|(
name|error
argument_list|,
name|_
argument_list|(
literal|"Parse error in '%s':\n%s"
argument_list|)
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|locale_parser_parse (GMarkupParseContext * context,GimpHelpProgress * progress,GInputStream * stream,goffset size,GCancellable * cancellable,GError ** error)
name|locale_parser_parse
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
name|GimpHelpProgress
modifier|*
name|progress
parameter_list|,
name|GInputStream
modifier|*
name|stream
parameter_list|,
name|goffset
name|size
parameter_list|,
name|GCancellable
modifier|*
name|cancellable
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gssize
name|len
decl_stmt|;
name|goffset
name|done
init|=
literal|0
decl_stmt|;
name|gchar
name|buffer
index|[
literal|4096
index|]
decl_stmt|;
while|while
condition|(
operator|(
name|len
operator|=
name|g_input_stream_read
argument_list|(
name|stream
argument_list|,
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|cancellable
argument_list|,
name|error
argument_list|)
operator|)
operator|!=
operator|-
literal|1
condition|)
block|{
switch|switch
condition|(
name|len
condition|)
block|{
case|case
literal|0
case|:
return|return
name|g_markup_parse_context_end_parse
argument_list|(
name|context
argument_list|,
name|error
argument_list|)
return|;
default|default:
name|done
operator|+=
name|len
expr_stmt|;
if|if
condition|(
name|progress
condition|)
block|{
if|if
condition|(
name|size
operator|>
literal|0
condition|)
name|_gimp_help_progress_update
argument_list|(
name|progress
argument_list|,
operator|(
name|gdouble
operator|)
name|done
operator|/
name|size
argument_list|)
expr_stmt|;
else|else
name|_gimp_help_progress_pulse
argument_list|(
name|progress
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|g_markup_parse_context_parse
argument_list|(
name|context
argument_list|,
name|buffer
argument_list|,
name|len
argument_list|,
name|error
argument_list|)
condition|)
return|return
name|FALSE
return|;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|locale_parser_start_element (GMarkupParseContext * context,const gchar * element_name,const gchar ** attribute_names,const gchar ** attribute_values,gpointer user_data,GError ** error)
name|locale_parser_start_element
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
name|LocaleParser
modifier|*
name|parser
init|=
operator|(
name|LocaleParser
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
name|LOCALE_START
case|:
if|if
condition|(
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"gimp-help"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|parser
operator|->
name|state
operator|=
name|LOCALE_IN_HELP
expr_stmt|;
name|locale_parser_parse_namespace
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
name|locale_parser_start_unknown
argument_list|(
name|parser
argument_list|)
expr_stmt|;
break|break;
case|case
name|LOCALE_IN_HELP
case|:
if|if
condition|(
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"help-item"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|parser
operator|->
name|state
operator|=
name|LOCALE_IN_ITEM
expr_stmt|;
name|locale_parser_parse_item
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
literal|"help-missing"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|parser
operator|->
name|state
operator|=
name|LOCALE_IN_MISSING
expr_stmt|;
name|locale_parser_parse_missing
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
name|locale_parser_start_unknown
argument_list|(
name|parser
argument_list|)
expr_stmt|;
break|break;
case|case
name|LOCALE_IN_ITEM
case|:
case|case
name|LOCALE_IN_MISSING
case|:
case|case
name|LOCALE_IN_UNKNOWN
case|:
name|locale_parser_start_unknown
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
DECL|function|locale_parser_end_element (GMarkupParseContext * context,const gchar * element_name,gpointer user_data,GError ** error)
name|locale_parser_end_element
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
name|LocaleParser
modifier|*
name|parser
init|=
operator|(
name|LocaleParser
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
name|LOCALE_START
case|:
name|g_warning
argument_list|(
literal|"locale_parser: This shouldn't happen."
argument_list|)
expr_stmt|;
break|break;
case|case
name|LOCALE_IN_HELP
case|:
name|parser
operator|->
name|state
operator|=
name|LOCALE_START
expr_stmt|;
break|break;
case|case
name|LOCALE_IN_ITEM
case|:
case|case
name|LOCALE_IN_MISSING
case|:
name|parser
operator|->
name|state
operator|=
name|LOCALE_IN_HELP
expr_stmt|;
break|break;
case|case
name|LOCALE_IN_UNKNOWN
case|:
name|locale_parser_end_unknown
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
DECL|function|locale_parser_error (GMarkupParseContext * context,GError * error,gpointer user_data)
name|locale_parser_error
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
name|LocaleParser
modifier|*
name|parser
init|=
operator|(
name|LocaleParser
operator|*
operator|)
name|user_data
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|g_file_get_parse_name
argument_list|(
name|parser
operator|->
name|file
argument_list|)
decl_stmt|;
name|g_printerr
argument_list|(
literal|"help (parsing %s): %s"
argument_list|,
name|name
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|locale_parser_start_unknown (LocaleParser * parser)
name|locale_parser_start_unknown
parameter_list|(
name|LocaleParser
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
name|LOCALE_IN_UNKNOWN
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
DECL|function|locale_parser_end_unknown (LocaleParser * parser)
name|locale_parser_end_unknown
parameter_list|(
name|LocaleParser
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
name|LOCALE_IN_UNKNOWN
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
DECL|function|locale_parser_parse_namespace (LocaleParser * parser,const gchar ** names,const gchar ** values)
name|locale_parser_parse_namespace
parameter_list|(
name|LocaleParser
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
for|for
control|(
init|;
operator|*
name|names
operator|&&
operator|*
name|values
condition|;
name|names
operator|++
operator|,
name|values
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|strncmp
argument_list|(
operator|*
name|names
argument_list|,
literal|"xmlns:"
argument_list|,
literal|6
argument_list|)
operator|&&
operator|!
name|strcmp
argument_list|(
operator|*
name|values
argument_list|,
name|parser
operator|->
name|help_domain
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|parser
operator|->
name|id_attr_name
argument_list|)
expr_stmt|;
name|parser
operator|->
name|id_attr_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s:id"
argument_list|,
operator|*
name|names
operator|+
literal|6
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_HELP_DEBUG
name|g_printerr
argument_list|(
literal|"help (%s): id attribute name for \"%s\" is \"%s\"\n"
argument_list|,
name|parser
operator|->
name|locale
operator|->
name|locale_id
argument_list|,
name|parser
operator|->
name|help_domain
argument_list|,
name|parser
operator|->
name|id_attr_name
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|locale_parser_parse_item (LocaleParser * parser,const gchar ** names,const gchar ** values)
name|locale_parser_parse_item
parameter_list|(
name|LocaleParser
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
name|id
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|ref
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|title
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|parent
init|=
name|NULL
decl_stmt|;
for|for
control|(
init|;
operator|*
name|names
operator|&&
operator|*
name|values
condition|;
name|names
operator|++
operator|,
name|values
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
operator|*
name|names
argument_list|,
name|parser
operator|->
name|id_attr_name
argument_list|)
condition|)
name|id
operator|=
operator|*
name|values
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
operator|*
name|names
argument_list|,
literal|"ref"
argument_list|)
condition|)
name|ref
operator|=
operator|*
name|values
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
operator|*
name|names
argument_list|,
literal|"title"
argument_list|)
condition|)
name|title
operator|=
operator|*
name|values
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
operator|*
name|names
argument_list|,
literal|"parent"
argument_list|)
condition|)
name|parent
operator|=
operator|*
name|values
expr_stmt|;
block|}
if|if
condition|(
name|id
operator|&&
name|ref
condition|)
block|{
if|if
condition|(
operator|!
name|parser
operator|->
name|locale
operator|->
name|help_id_mapping
condition|)
name|parser
operator|->
name|locale
operator|->
name|help_id_mapping
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
name|g_free
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_help_item_free
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|parser
operator|->
name|locale
operator|->
name|help_id_mapping
argument_list|,
name|g_strdup
argument_list|(
name|id
argument_list|)
argument_list|,
name|gimp_help_item_new
argument_list|(
name|ref
argument_list|,
name|title
argument_list|,
name|parent
argument_list|)
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_HELP_DEBUG
name|g_printerr
argument_list|(
literal|"help (%s): added mapping \"%s\" -> \"%s\"\n"
argument_list|,
name|parser
operator|->
name|locale
operator|->
name|locale_id
argument_list|,
name|id
argument_list|,
name|ref
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|locale_parser_parse_missing (LocaleParser * parser,const gchar ** names,const gchar ** values)
name|locale_parser_parse_missing
parameter_list|(
name|LocaleParser
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
name|ref
init|=
name|NULL
decl_stmt|;
for|for
control|(
init|;
operator|*
name|names
operator|&&
operator|*
name|values
condition|;
name|names
operator|++
operator|,
name|values
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
operator|*
name|names
argument_list|,
literal|"ref"
argument_list|)
condition|)
name|ref
operator|=
operator|*
name|values
expr_stmt|;
block|}
if|if
condition|(
name|ref
operator|&&
name|parser
operator|->
name|locale
operator|->
name|help_missing
operator|==
name|NULL
condition|)
block|{
name|parser
operator|->
name|locale
operator|->
name|help_missing
operator|=
name|g_strdup
argument_list|(
name|ref
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_HELP_DEBUG
name|g_printerr
argument_list|(
literal|"help (%s): added fallback for missing help -> \"%s\"\n"
argument_list|,
name|parser
operator|->
name|locale
operator|->
name|locale_id
argument_list|,
name|ref
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|locale_set_error (GError ** error,const gchar * format,GFile * file)
name|locale_set_error
parameter_list|(
name|GError
modifier|*
modifier|*
name|error
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
block|{
if|if
condition|(
name|error
operator|&&
operator|*
name|error
condition|)
block|{
name|gchar
modifier|*
name|name
init|=
name|g_file_get_parse_name
argument_list|(
name|file
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|msg
decl_stmt|;
name|msg
operator|=
name|g_strdup_printf
argument_list|(
name|format
argument_list|,
name|name
argument_list|,
operator|(
operator|*
name|error
operator|)
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
operator|(
operator|*
name|error
operator|)
operator|->
name|message
argument_list|)
expr_stmt|;
operator|(
operator|*
name|error
operator|)
operator|->
name|message
operator|=
name|msg
expr_stmt|;
block|}
block|}
end_function

end_unit

