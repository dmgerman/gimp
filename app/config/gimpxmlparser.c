begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * GimpXmlParser  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"config-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpxmlparser.h"
end_include

begin_struct
DECL|struct|_GimpXmlParser
struct|struct
name|_GimpXmlParser
block|{
DECL|member|context
name|GMarkupParseContext
modifier|*
name|context
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|gboolean
name|parse_encoding
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|text_len
parameter_list|,
name|gchar
modifier|*
modifier|*
name|encodind
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_xml_parser_new:  * @markup_parser: a #GMarkupParser  * @user_data: user data to pass to #GMarkupParser functions  *  * GimpXmlParser is a thin wrapper around GMarkupParser. This function  * creates one for you and sets up a GMarkupParseContext.  *  * Return value: a new #GimpXmlParser  **/
end_comment

begin_function
name|GimpXmlParser
modifier|*
DECL|function|gimp_xml_parser_new (const GMarkupParser * markup_parser,gpointer user_data)
name|gimp_xml_parser_new
parameter_list|(
specifier|const
name|GMarkupParser
modifier|*
name|markup_parser
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpXmlParser
modifier|*
name|parser
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|markup_parser
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|parser
operator|=
name|g_new
argument_list|(
name|GimpXmlParser
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|parser
operator|->
name|context
operator|=
name|g_markup_parse_context_new
argument_list|(
name|markup_parser
argument_list|,
literal|0
argument_list|,
name|user_data
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|parser
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_xml_parser_parse_file:  * @parser: a #GimpXmlParser  * @filename: name of a file to parse  * @error: return location for possible errors  *  * This function creates a GIOChannel for @filename and calls  * gimp_xml_parser_parse_io_channel() for you.  *  * Return value: %TRUE on success, %FALSE otherwise  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_xml_parser_parse_file (GimpXmlParser * parser,const gchar * filename,GError ** error)
name|gimp_xml_parser_parse_file
parameter_list|(
name|GimpXmlParser
modifier|*
name|parser
parameter_list|,
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
name|GIOChannel
modifier|*
name|io
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parser
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
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
return|return
name|FALSE
return|;
name|g_io_channel_set_encoding
argument_list|(
name|io
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_xml_parser_parse_io_channel
argument_list|(
name|parser
argument_list|,
name|io
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_io_channel_unref
argument_list|(
name|io
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_xml_parser_parse_io_channel:  * @parser: a #GimpXmlParser  * @io: a #GIOChannel  * @error: return location for possible errors  *  * Makes @parser read from the specified @io channel. This function  * returns when the GIOChannel becomes empty (end of file) or an  * error occurs, either reading from @io or parsing the read data.  *  * This function tries to determine the character encoding from the  * XML header and converts the content to UTF-8 for you. For this  * feature to work, the XML header with the encoding attribute must be  * contained in the first 4096 bytes read. Otherwise UTF-8 encoding  * will be assumed and parsing may break later if this assumption  * was wrong.  *  * Return value: %TRUE on success, %FALSE otherwise  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_xml_parser_parse_io_channel (GimpXmlParser * parser,GIOChannel * io,GError ** error)
name|gimp_xml_parser_parse_io_channel
parameter_list|(
name|GimpXmlParser
modifier|*
name|parser
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
name|guchar
name|buffer
index|[
literal|4096
index|]
decl_stmt|;
name|gsize
name|len
init|=
literal|0
decl_stmt|;
name|gsize
name|bytes
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|io_encoding
decl_stmt|;
name|gchar
modifier|*
name|encoding
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parser
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|io
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
name|io_encoding
operator|=
name|g_io_channel_get_encoding
argument_list|(
name|io
argument_list|)
expr_stmt|;
if|if
condition|(
name|io_encoding
condition|)
block|{
name|g_warning
argument_list|(
literal|"gimp_xml_parser_parse_io_channel():\n"
literal|"The encoding has already been set on this GIOChannel!"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/* try to determine the encoding */
while|while
condition|(
name|len
operator|<
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
condition|)
block|{
name|status
operator|=
name|g_io_channel_read_chars
argument_list|(
name|io
argument_list|,
name|buffer
operator|+
name|len
argument_list|,
literal|1
argument_list|,
operator|&
name|bytes
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|len
operator|+=
name|bytes
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|G_IO_STATUS_ERROR
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|status
operator|==
name|G_IO_STATUS_EOF
condition|)
break|break;
if|if
condition|(
name|parse_encoding
argument_list|(
name|buffer
argument_list|,
name|len
argument_list|,
operator|&
name|encoding
argument_list|)
condition|)
break|break;
block|}
if|if
condition|(
name|encoding
condition|)
block|{
if|if
condition|(
operator|!
name|g_io_channel_set_encoding
argument_list|(
name|io
argument_list|,
name|encoding
argument_list|,
name|error
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|g_free
argument_list|(
name|encoding
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_io_channel_set_encoding
argument_list|(
name|io
argument_list|,
literal|"UTF-8"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
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
name|parser
operator|->
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
name|parser
operator|->
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
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_xml_parser_parse_buffer (GimpXmlParser * parser,const gchar * buffer,gssize len,GError ** error)
name|gimp_xml_parser_parse_buffer
parameter_list|(
name|GimpXmlParser
modifier|*
name|parser
parameter_list|,
specifier|const
name|gchar
modifier|*
name|buffer
parameter_list|,
name|gssize
name|len
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gchar
modifier|*
name|encoding
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|conv
init|=
name|NULL
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parser
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|buffer
operator|!=
name|NULL
operator|||
name|len
operator|==
literal|0
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
name|len
operator|<
literal|0
condition|)
name|len
operator|=
name|strlen
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|parse_encoding
argument_list|(
name|buffer
argument_list|,
name|len
argument_list|,
operator|&
name|encoding
argument_list|)
condition|)
block|{
if|if
condition|(
name|g_ascii_strcasecmp
argument_list|(
name|encoding
argument_list|,
literal|"UTF-8"
argument_list|)
operator|&&
name|g_ascii_strcasecmp
argument_list|(
name|encoding
argument_list|,
literal|"UTF8"
argument_list|)
condition|)
block|{
name|conv
operator|=
name|g_convert
argument_list|(
name|buffer
argument_list|,
name|len
argument_list|,
literal|"UTF-8"
argument_list|,
name|encoding
argument_list|,
name|NULL
argument_list|,
operator|&
name|len
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|encoding
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|conv
condition|)
return|return
name|FALSE
return|;
block|}
block|}
name|success
operator|=
name|g_markup_parse_context_parse
argument_list|(
name|parser
operator|->
name|context
argument_list|,
name|conv
condition|?
name|conv
else|:
name|buffer
argument_list|,
name|len
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|conv
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_xml_parser_free:  * @parser: a #GimpXmlParser  *  * Frees the resources allocated for @parser. You must not access  * @parser after calling this function.  **/
end_comment

begin_function
name|void
DECL|function|gimp_xml_parser_free (GimpXmlParser * parser)
name|gimp_xml_parser_free
parameter_list|(
name|GimpXmlParser
modifier|*
name|parser
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|parser
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_markup_parse_context_free
argument_list|(
name|parser
operator|->
name|context
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|parser
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Try to determine encoding from XML header.  This function returns    FALSE when it doesn't have enough text to parse.  It returns TRUE    and sets encoding when the XML header has been parsed.  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|parse_encoding (const gchar * text,gint text_len,gchar ** encoding)
name|parse_encoding
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|text_len
parameter_list|,
name|gchar
modifier|*
modifier|*
name|encoding
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|start
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|end
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|text
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|text_len
operator|<
literal|20
condition|)
return|return
name|FALSE
return|;
name|start
operator|=
name|g_strstr_len
argument_list|(
name|text
argument_list|,
name|text_len
argument_list|,
literal|"<?xml"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|start
condition|)
return|return
name|FALSE
return|;
name|end
operator|=
name|g_strstr_len
argument_list|(
name|start
argument_list|,
name|text_len
operator|-
operator|(
name|start
operator|-
name|text
operator|)
argument_list|,
literal|"?>"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|end
condition|)
return|return
name|FALSE
return|;
operator|*
name|encoding
operator|=
name|NULL
expr_stmt|;
name|text_len
operator|=
name|end
operator|-
name|start
expr_stmt|;
if|if
condition|(
name|text_len
operator|<
literal|12
condition|)
return|return
name|TRUE
return|;
name|start
operator|=
name|g_strstr_len
argument_list|(
name|start
operator|+
literal|1
argument_list|,
name|text_len
operator|-
literal|1
argument_list|,
literal|"encoding"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|start
condition|)
return|return
name|TRUE
return|;
name|start
operator|+=
literal|8
expr_stmt|;
while|while
condition|(
name|start
operator|<
name|end
operator|&&
operator|*
name|start
operator|==
literal|' '
condition|)
name|start
operator|++
expr_stmt|;
if|if
condition|(
operator|*
name|start
operator|!=
literal|'='
condition|)
return|return
name|TRUE
return|;
name|start
operator|++
expr_stmt|;
while|while
condition|(
name|start
operator|<
name|end
operator|&&
operator|*
name|start
operator|==
literal|' '
condition|)
name|start
operator|++
expr_stmt|;
if|if
condition|(
operator|*
name|start
operator|!=
literal|'\"'
operator|&&
operator|*
name|start
operator|!=
literal|'\''
condition|)
return|return
name|TRUE
return|;
name|text_len
operator|=
name|end
operator|-
name|start
expr_stmt|;
if|if
condition|(
name|text_len
operator|<
literal|1
condition|)
return|return
name|TRUE
return|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|text_len
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|start
index|[
name|i
index|]
operator|==
name|start
index|[
literal|0
index|]
condition|)
break|break;
if|if
condition|(
name|i
operator|==
name|text_len
operator|||
name|i
operator|<
literal|3
condition|)
return|return
name|TRUE
return|;
operator|*
name|encoding
operator|=
name|g_strndup
argument_list|(
name|start
operator|+
literal|1
argument_list|,
name|i
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

