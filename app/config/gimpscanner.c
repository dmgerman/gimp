begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpscanner.c  * Copyright (C) 2002  Sven Neumann<sven@gimp.org>  *                     Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpscanner.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_scanner_message
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|is_error
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GScanner
modifier|*
DECL|function|gimp_scanner_new (const gchar * filename,GError ** error)
name|gimp_scanner_new
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
name|gint
name|fd
decl_stmt|;
name|GScanner
modifier|*
name|scanner
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
name|fd
operator|=
name|open
argument_list|(
name|filename
argument_list|,
name|O_RDONLY
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
operator|(
name|errno
operator|==
name|ENOENT
condition|?
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
else|:
name|GIMP_CONFIG_ERROR_OPEN
operator|)
argument_list|,
name|_
argument_list|(
literal|"Failed to open file: '%s': %s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|scanner
operator|=
name|g_scanner_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|g_scanner_input_file
argument_list|(
name|scanner
argument_list|,
name|fd
argument_list|)
expr_stmt|;
name|scanner
operator|->
name|user_data
operator|=
name|error
expr_stmt|;
name|scanner
operator|->
name|msg_handler
operator|=
name|gimp_scanner_message
expr_stmt|;
name|scanner
operator|->
name|input_name
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|scanner
operator|->
name|config
operator|->
name|cset_identifier_first
operator|=
operator|(
name|G_CSET_a_2_z
name|G_CSET_A_2_Z
operator|)
expr_stmt|;
name|scanner
operator|->
name|config
operator|->
name|cset_identifier_nth
operator|=
operator|(
name|G_CSET_a_2_z
name|G_CSET_A_2_Z
literal|"-_"
operator|)
expr_stmt|;
name|scanner
operator|->
name|config
operator|->
name|scan_identifier_1char
operator|=
name|TRUE
expr_stmt|;
return|return
name|scanner
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_scanner_destroy (GScanner * scanner)
name|gimp_scanner_destroy
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|scanner
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|scanner
operator|->
name|input_fd
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|scanner
operator|->
name|input_name
argument_list|)
expr_stmt|;
name|g_scanner_destroy
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_scanner_parse_token (GScanner * scanner,GTokenType token)
name|gimp_scanner_parse_token
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GTokenType
name|token
parameter_list|)
block|{
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|token
condition|)
return|return
name|FALSE
return|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_scanner_parse_identifier (GScanner * scanner,const gchar * identifier)
name|gimp_scanner_parse_identifier
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|)
block|{
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|G_TOKEN_IDENTIFIER
condition|)
return|return
name|FALSE
return|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|,
name|identifier
argument_list|)
condition|)
return|return
name|FALSE
return|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_scanner_parse_string (GScanner * scanner,gchar ** dest)
name|gimp_scanner_parse_string
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gchar
modifier|*
modifier|*
name|dest
parameter_list|)
block|{
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|G_TOKEN_STRING
condition|)
return|return
name|FALSE
return|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|scanner
operator|->
name|value
operator|.
name|v_string
condition|)
block|{
if|if
condition|(
operator|!
name|g_utf8_validate
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_string
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|g_scanner_warn
argument_list|(
name|scanner
argument_list|,
name|_
argument_list|(
literal|"invalid UTF-8 string"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
operator|*
name|dest
operator|=
name|g_strdup
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_string
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_scanner_parse_string_no_validate (GScanner * scanner,gchar ** dest)
name|gimp_scanner_parse_string_no_validate
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gchar
modifier|*
modifier|*
name|dest
parameter_list|)
block|{
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|G_TOKEN_STRING
condition|)
return|return
name|FALSE
return|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|scanner
operator|->
name|value
operator|.
name|v_string
condition|)
operator|*
name|dest
operator|=
name|g_strdup
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_string
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_scanner_parse_int (GScanner * scanner,gint * dest)
name|gimp_scanner_parse_int
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
modifier|*
name|dest
parameter_list|)
block|{
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|G_TOKEN_INT
condition|)
return|return
name|FALSE
return|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
operator|*
name|dest
operator|=
name|scanner
operator|->
name|value
operator|.
name|v_int
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_scanner_parse_float (GScanner * scanner,gdouble * dest)
name|gimp_scanner_parse_float
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gdouble
modifier|*
name|dest
parameter_list|)
block|{
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|G_TOKEN_FLOAT
condition|)
return|return
name|FALSE
return|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
operator|*
name|dest
operator|=
name|scanner
operator|->
name|value
operator|.
name|v_float
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_enum
enum|enum
DECL|enum|__anon2c5335530103
block|{
DECL|enumerator|COLOR_RGB
name|COLOR_RGB
init|=
literal|1
block|,
DECL|enumerator|COLOR_RGBA
name|COLOR_RGBA
block|,
DECL|enumerator|COLOR_HSV
name|COLOR_HSV
block|,
DECL|enumerator|COLOR_HSVA
name|COLOR_HSVA
block|}
enum|;
end_enum

begin_function
name|gboolean
DECL|function|gimp_scanner_parse_color (GScanner * scanner,GimpRGB * dest)
name|gimp_scanner_parse_color
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GimpRGB
modifier|*
name|dest
parameter_list|)
block|{
name|guint
name|scope_id
decl_stmt|;
name|guint
name|old_scope_id
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|scope_id
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp_scanner_parse_color"
argument_list|)
expr_stmt|;
name|old_scope_id
operator|=
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_scanner_scope_lookup_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"color-rgb"
argument_list|)
condition|)
block|{
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"color-rgb"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|COLOR_RGB
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"color-rgba"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|COLOR_RGBA
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"color-hsv"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|COLOR_HSV
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"color-hsva"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|COLOR_HSVA
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
while|while
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|token
condition|)
block|{
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|token
condition|)
block|{
case|case
name|G_TOKEN_LEFT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_SYMBOL
expr_stmt|;
break|break;
case|case
name|G_TOKEN_SYMBOL
case|:
block|{
name|gdouble
name|col
index|[
literal|4
index|]
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
name|gint
name|n_channels
init|=
literal|4
decl_stmt|;
name|gboolean
name|is_hsv
init|=
name|FALSE
decl_stmt|;
name|gint
name|i
decl_stmt|;
switch|switch
condition|(
name|GPOINTER_TO_INT
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_symbol
argument_list|)
condition|)
block|{
case|case
name|COLOR_RGB
case|:
name|n_channels
operator|=
literal|3
expr_stmt|;
comment|/* fallthrough */
case|case
name|COLOR_RGBA
case|:
break|break;
case|case
name|COLOR_HSV
case|:
name|n_channels
operator|=
literal|3
expr_stmt|;
comment|/* fallthrough */
case|case
name|COLOR_HSVA
case|:
name|is_hsv
operator|=
name|TRUE
expr_stmt|;
break|break;
block|}
name|token
operator|=
name|G_TOKEN_FLOAT
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_channels
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|gimp_scanner_parse_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|col
index|[
name|i
index|]
argument_list|)
condition|)
goto|goto
name|finish
goto|;
block|}
if|if
condition|(
name|is_hsv
condition|)
block|{
name|GimpHSV
name|hsv
decl_stmt|;
name|gimp_hsva_set
argument_list|(
operator|&
name|hsv
argument_list|,
name|col
index|[
literal|0
index|]
argument_list|,
name|col
index|[
literal|1
index|]
argument_list|,
name|col
index|[
literal|2
index|]
argument_list|,
name|col
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|gimp_hsv_clamp
argument_list|(
operator|&
name|hsv
argument_list|)
expr_stmt|;
name|gimp_hsv_to_rgb
argument_list|(
operator|&
name|hsv
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
name|col
index|[
literal|0
index|]
argument_list|,
name|col
index|[
literal|1
index|]
argument_list|,
name|col
index|[
literal|2
index|]
argument_list|,
name|col
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|gimp_rgb_clamp
argument_list|(
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
block|}
name|token
operator|=
name|G_TOKEN_RIGHT_PAREN
expr_stmt|;
break|break;
case|case
name|G_TOKEN_RIGHT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_NONE
expr_stmt|;
comment|/* indicates success */
goto|goto
name|finish
goto|;
default|default:
comment|/* do nothing */
break|break;
block|}
block|}
name|finish
label|:
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_NONE
condition|)
block|{
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
name|g_scanner_unexp_token
argument_list|(
name|scanner
argument_list|,
name|token
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"fatal parse error"
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
operator|*
name|dest
operator|=
name|color
expr_stmt|;
block|}
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
name|old_scope_id
argument_list|)
expr_stmt|;
return|return
operator|(
name|token
operator|==
name|G_TOKEN_NONE
operator|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_scanner_parse_string_list (GScanner * scanner,GList ** dest)
name|gimp_scanner_parse_string_list
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GList
modifier|*
modifier|*
name|dest
parameter_list|)
block|{
name|GTokenType
name|token
decl_stmt|;
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
while|while
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|token
condition|)
block|{
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|token
condition|)
block|{
case|case
name|G_TOKEN_LEFT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
break|break;
case|case
name|G_TOKEN_STRING
case|:
do|do
block|{
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|g_strdup
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_string
argument_list|)
argument_list|)
expr_stmt|;
name|token
operator|=
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|==
name|G_TOKEN_STRING
condition|)
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|token
operator|==
name|G_TOKEN_STRING
condition|)
do|;
name|token
operator|=
name|G_TOKEN_RIGHT_PAREN
expr_stmt|;
break|break;
case|case
name|G_TOKEN_RIGHT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_NONE
expr_stmt|;
comment|/* indicates success */
goto|goto
name|finish
goto|;
default|default:
comment|/* do nothing */
break|break;
block|}
block|}
name|finish
label|:
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_NONE
condition|)
block|{
name|g_list_foreach
argument_list|(
name|list
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|list
operator|=
name|NULL
expr_stmt|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
name|g_scanner_unexp_token
argument_list|(
name|scanner
argument_list|,
name|token
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"fatal parse error"
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
operator|*
name|dest
operator|=
name|list
expr_stmt|;
block|}
return|return
operator|(
name|token
operator|==
name|G_TOKEN_NONE
operator|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_scanner_message (GScanner * scanner,gchar * message,gboolean is_error)
name|gimp_scanner_message
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|is_error
parameter_list|)
block|{
name|GError
modifier|*
modifier|*
name|error
init|=
name|scanner
operator|->
name|user_data
decl_stmt|;
comment|/* we don't expect warnings */
name|g_return_if_fail
argument_list|(
name|is_error
argument_list|)
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_PARSE
argument_list|,
name|_
argument_list|(
literal|"Error while parsing '%s' in line %d:\n%s"
argument_list|)
argument_list|,
name|scanner
operator|->
name|input_name
argument_list|,
name|scanner
operator|->
name|line
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

