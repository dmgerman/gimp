begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2004 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"domain.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_struct
DECL|struct|_HelpDomain
struct|struct
name|_HelpDomain
block|{
DECL|member|help_domain
name|gchar
modifier|*
name|help_domain
decl_stmt|;
DECL|member|help_uri
name|gchar
modifier|*
name|help_uri
decl_stmt|;
DECL|member|help_id_mapping
name|GHashTable
modifier|*
name|help_id_mapping
decl_stmt|;
DECL|member|help_missing
name|gchar
modifier|*
name|help_missing
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|HelpDomain
modifier|*
name|domain_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|domain_free
parameter_list|(
name|HelpDomain
modifier|*
name|domain
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|domain_parse
parameter_list|(
name|HelpDomain
modifier|*
name|domain
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|domain_hash
specifier|static
name|GHashTable
modifier|*
name|domain_hash
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|domain_register (const gchar * domain_name,const gchar * domain_uri)
name|domain_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_uri
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|domain_name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|domain_uri
operator|!=
name|NULL
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_HELP_DEBUG
name|g_printerr
argument_list|(
literal|"help: registering help domain \"%s\" with base uri \"%s\"\n"
argument_list|,
name|domain_name
argument_list|,
name|domain_uri
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
operator|!
name|domain_hash
condition|)
name|domain_hash
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
name|domain_free
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|domain_hash
argument_list|,
name|g_strdup
argument_list|(
name|domain_name
argument_list|)
argument_list|,
name|domain_new
argument_list|(
name|domain_name
argument_list|,
name|domain_uri
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|HelpDomain
modifier|*
DECL|function|domain_lookup (const gchar * domain_name)
name|domain_lookup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|domain_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|domain_hash
condition|)
return|return
name|g_hash_table_lookup
argument_list|(
name|domain_hash
argument_list|,
name|domain_name
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|domain_map (HelpDomain * domain,GList * help_locales,const gchar * help_id)
name|domain_map
parameter_list|(
name|HelpDomain
modifier|*
name|domain
parameter_list|,
name|GList
modifier|*
name|help_locales
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|ref
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|domain
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_locales
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
operator|!
name|domain
operator|->
name|help_id_mapping
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|domain_parse
argument_list|(
name|domain
argument_list|,
operator|&
name|error
argument_list|)
operator|||
name|error
condition|)
block|{
if|if
condition|(
operator|!
name|domain
operator|->
name|help_id_mapping
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Failed to open help files:\n%s"
argument_list|)
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
else|else
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Parse error in help domain:\n%s\n\n"
literal|"(entries appearing before the error have been added anyway)"
argument_list|)
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|domain
operator|->
name|help_id_mapping
condition|)
return|return
name|NULL
return|;
block|}
name|ref
operator|=
name|g_hash_table_lookup
argument_list|(
name|domain
operator|->
name|help_id_mapping
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|ref
condition|)
name|ref
operator|=
name|domain
operator|->
name|help_missing
expr_stmt|;
if|if
condition|(
operator|!
name|ref
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Help ID '%s' unknown"
argument_list|)
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|g_strconcat
argument_list|(
name|domain
operator|->
name|help_uri
argument_list|,
literal|"/"
argument_list|,
name|ref
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|HelpDomain
modifier|*
DECL|function|domain_new (const gchar * domain_name,const gchar * domain_uri)
name|domain_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_uri
parameter_list|)
block|{
name|HelpDomain
modifier|*
name|domain
init|=
name|g_new0
argument_list|(
name|HelpDomain
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|domain
operator|->
name|help_domain
operator|=
name|g_strdup
argument_list|(
name|domain_name
argument_list|)
expr_stmt|;
name|domain
operator|->
name|help_uri
operator|=
name|g_strdup
argument_list|(
name|domain_uri
argument_list|)
expr_stmt|;
return|return
name|domain
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|domain_free (HelpDomain * domain)
name|domain_free
parameter_list|(
name|HelpDomain
modifier|*
name|domain
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|domain
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|domain
operator|->
name|help_id_mapping
condition|)
name|g_hash_table_destroy
argument_list|(
name|domain
operator|->
name|help_id_mapping
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|domain
operator|->
name|help_domain
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|domain
operator|->
name|help_uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|domain
operator|->
name|help_missing
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|domain
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  the domain mapping parser  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b3181a40103
block|{
DECL|enumerator|DOMAIN_START
name|DOMAIN_START
block|,
DECL|enumerator|DOMAIN_IN_HELP
name|DOMAIN_IN_HELP
block|,
DECL|enumerator|DOMAIN_IN_ITEM
name|DOMAIN_IN_ITEM
block|,
DECL|enumerator|DOMAIN_IN_MISSING
name|DOMAIN_IN_MISSING
block|,
DECL|enumerator|DOMAIN_IN_UNKNOWN
name|DOMAIN_IN_UNKNOWN
DECL|typedef|DomainParserState
block|}
name|DomainParserState
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b3181a40208
block|{
DECL|member|filename
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|state
name|DomainParserState
name|state
decl_stmt|;
DECL|member|last_known_state
name|DomainParserState
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
DECL|member|domain
name|HelpDomain
modifier|*
name|domain
decl_stmt|;
DECL|member|id_attr_name
name|gchar
modifier|*
name|id_attr_name
decl_stmt|;
DECL|typedef|DomainParser
block|}
name|DomainParser
typedef|;
end_typedef

begin_function_decl
specifier|static
name|gboolean
name|domain_parser_parse
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
name|GIOChannel
modifier|*
name|io
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
name|domain_parser_start_element
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
name|domain_parser_end_element
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
name|domain_parser_error
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
name|domain_parser_start_unknown
parameter_list|(
name|DomainParser
modifier|*
name|parser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|domain_parser_end_unknown
parameter_list|(
name|DomainParser
modifier|*
name|parser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|domain_parser_parse_namespace
parameter_list|(
name|DomainParser
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
name|domain_parser_parse_item
parameter_list|(
name|DomainParser
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
name|domain_parser_parse_missing
parameter_list|(
name|DomainParser
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
name|domain_parser_start_element
block|,
name|domain_parser_end_element
block|,
name|NULL
block|,
comment|/*  characters   */
name|NULL
block|,
comment|/*  passthrough  */
name|domain_parser_error
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|gboolean
DECL|function|domain_parse (HelpDomain * domain,GError ** error)
name|domain_parse
parameter_list|(
name|HelpDomain
modifier|*
name|domain
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
name|DomainParser
modifier|*
name|parser
decl_stmt|;
name|gchar
modifier|*
name|base_dir
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GIOChannel
modifier|*
name|io
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|domain
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|domain
operator|->
name|help_id_mapping
operator|==
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
name|base_dir
operator|=
name|g_filename_from_uri
argument_list|(
name|domain
operator|->
name|help_uri
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|base_dir
argument_list|,
literal|"gimp-help.xml"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|base_dir
argument_list|)
expr_stmt|;
name|io
operator|=
name|g_io_channel_new_file
argument_list|(
name|filename
argument_list|,
literal|"r"
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|io
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|msg
decl_stmt|;
name|gchar
modifier|*
name|msg2
decl_stmt|;
if|if
condition|(
operator|!
name|error
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|domain
operator|->
name|help_domain
argument_list|,
name|GIMP_HELP_DEFAULT_DOMAIN
argument_list|)
condition|)
name|msg
operator|=
name|_
argument_list|(
literal|"The GIMP help files are not installed."
argument_list|)
expr_stmt|;
else|else
name|msg
operator|=
name|_
argument_list|(
literal|"The requested help files are not installed."
argument_list|)
expr_stmt|;
name|msg2
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
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
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"%s\n\n%s\n\n%s"
argument_list|,
name|msg
argument_list|,
name|msg2
argument_list|,
name|_
argument_list|(
literal|"Please check your installation."
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|msg2
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|parser
operator|=
name|g_new0
argument_list|(
name|DomainParser
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
name|parser
operator|->
name|id_attr_name
operator|=
name|g_strdup
argument_list|(
literal|"id"
argument_list|)
expr_stmt|;
name|parser
operator|->
name|domain
operator|=
name|domain
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
name|domain_parser_parse
argument_list|(
name|context
argument_list|,
name|io
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_markup_parse_context_free
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|g_io_channel_unref
argument_list|(
name|io
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
operator|->
name|id_attr_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|parser
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
operator|(
name|domain
operator|->
name|help_id_mapping
operator|!=
name|NULL
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|domain_parser_parse (GMarkupParseContext * context,GIOChannel * io,GError ** error)
name|domain_parser_parse
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
name|GIOChannel
modifier|*
name|io
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GIOStatus
name|status
decl_stmt|;
name|gsize
name|len
decl_stmt|;
name|gchar
name|buffer
index|[
literal|4096
index|]
decl_stmt|;
while|while
condition|(
name|TRUE
condition|)
block|{
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
name|status
operator|=
name|g_io_channel_read_chars
argument_list|(
name|io
argument_list|,
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
operator|&
name|len
argument_list|,
name|error
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|status
condition|)
block|{
case|case
name|G_IO_STATUS_ERROR
case|:
return|return
name|FALSE
return|;
case|case
name|G_IO_STATUS_EOF
case|:
return|return
name|g_markup_parse_context_end_parse
argument_list|(
name|context
argument_list|,
name|error
argument_list|)
return|;
case|case
name|G_IO_STATUS_NORMAL
case|:
case|case
name|G_IO_STATUS_AGAIN
case|:
break|break;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|domain_parser_start_element (GMarkupParseContext * context,const gchar * element_name,const gchar ** attribute_names,const gchar ** attribute_values,gpointer user_data,GError ** error)
name|domain_parser_start_element
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
name|DomainParser
modifier|*
name|parser
init|=
operator|(
name|DomainParser
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
name|DOMAIN_START
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
name|DOMAIN_IN_HELP
expr_stmt|;
name|domain_parser_parse_namespace
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
name|domain_parser_start_unknown
argument_list|(
name|parser
argument_list|)
expr_stmt|;
break|break;
case|case
name|DOMAIN_IN_HELP
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
name|DOMAIN_IN_ITEM
expr_stmt|;
name|domain_parser_parse_item
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
name|DOMAIN_IN_MISSING
expr_stmt|;
name|domain_parser_parse_missing
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
name|domain_parser_start_unknown
argument_list|(
name|parser
argument_list|)
expr_stmt|;
break|break;
case|case
name|DOMAIN_IN_ITEM
case|:
case|case
name|DOMAIN_IN_MISSING
case|:
case|case
name|DOMAIN_IN_UNKNOWN
case|:
name|domain_parser_start_unknown
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
DECL|function|domain_parser_end_element (GMarkupParseContext * context,const gchar * element_name,gpointer user_data,GError ** error)
name|domain_parser_end_element
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
name|DomainParser
modifier|*
name|parser
init|=
operator|(
name|DomainParser
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
name|DOMAIN_START
case|:
name|g_warning
argument_list|(
literal|"domain_parser: This shouldn't happen."
argument_list|)
expr_stmt|;
break|break;
case|case
name|DOMAIN_IN_HELP
case|:
name|parser
operator|->
name|state
operator|=
name|DOMAIN_START
expr_stmt|;
break|break;
case|case
name|DOMAIN_IN_ITEM
case|:
case|case
name|DOMAIN_IN_MISSING
case|:
name|parser
operator|->
name|state
operator|=
name|DOMAIN_IN_HELP
expr_stmt|;
break|break;
case|case
name|DOMAIN_IN_UNKNOWN
case|:
name|domain_parser_end_unknown
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
DECL|function|domain_parser_error (GMarkupParseContext * context,GError * error,gpointer user_data)
name|domain_parser_error
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
name|DomainParser
modifier|*
name|parser
init|=
operator|(
name|DomainParser
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
DECL|function|domain_parser_start_unknown (DomainParser * parser)
name|domain_parser_start_unknown
parameter_list|(
name|DomainParser
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
name|DOMAIN_IN_UNKNOWN
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
DECL|function|domain_parser_end_unknown (DomainParser * parser)
name|domain_parser_end_unknown
parameter_list|(
name|DomainParser
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
name|DOMAIN_IN_UNKNOWN
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
DECL|function|domain_parser_parse_namespace (DomainParser * parser,const gchar ** names,const gchar ** values)
name|domain_parser_parse_namespace
parameter_list|(
name|DomainParser
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
name|domain
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
literal|"help: id attribute name for \"%s\" is \"%s\"\n"
argument_list|,
name|parser
operator|->
name|domain
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
DECL|function|domain_parser_parse_item (DomainParser * parser,const gchar ** names,const gchar ** values)
name|domain_parser_parse_item
parameter_list|(
name|DomainParser
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
name|domain
operator|->
name|help_id_mapping
condition|)
name|parser
operator|->
name|domain
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
name|g_free
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|parser
operator|->
name|domain
operator|->
name|help_id_mapping
argument_list|,
name|g_strdup
argument_list|(
name|id
argument_list|)
argument_list|,
name|g_strdup
argument_list|(
name|ref
argument_list|)
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_HELP_DEBUG
name|g_printerr
argument_list|(
literal|"help: added mapping \"%s\" -> \"%s\"\n"
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
DECL|function|domain_parser_parse_missing (DomainParser * parser,const gchar ** names,const gchar ** values)
name|domain_parser_parse_missing
parameter_list|(
name|DomainParser
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
name|domain
operator|->
name|help_missing
operator|==
name|NULL
condition|)
block|{
name|parser
operator|->
name|domain
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
literal|"help: added fallback for missing help -> \"%s\"\n"
argument_list|,
name|ref
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
block|}
end_function

end_unit

