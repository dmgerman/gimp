begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpscanner.c  * Copyright (C) 2002  Sven Neumann<sven@gimp.org>  *                     Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<cairo.h>
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-error.h"
end_include

begin_include
include|#
directive|include
file|"gimpscanner.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimpscanner  * @title: GimpScanner  * @short_description: A wrapper around #GScanner with some convenience API.  *  * A wrapper around #GScanner with some convenience API.  **/
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c8ea1de0108
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|file
name|GMappedFile
modifier|*
name|file
decl_stmt|;
DECL|member|error
name|GError
modifier|*
modifier|*
name|error
decl_stmt|;
DECL|typedef|GimpScannerData
block|}
name|GimpScannerData
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GScanner
modifier|*
name|gimp_scanner_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GMappedFile
modifier|*
name|file
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

begin_comment
comment|/**  * gimp_scanner_new_file:  * @filename:  * @error:  *  * Return value:  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|GScanner
modifier|*
DECL|function|gimp_scanner_new_file (const gchar * filename,GError ** error)
name|gimp_scanner_new_file
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
name|GScanner
modifier|*
name|scanner
decl_stmt|;
name|GMappedFile
modifier|*
name|file
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
name|file
operator|=
name|g_mapped_file_new
argument_list|(
name|filename
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file
condition|)
block|{
if|if
condition|(
name|error
condition|)
block|{
operator|(
operator|*
name|error
operator|)
operator|->
name|domain
operator|=
name|GIMP_CONFIG_ERROR
expr_stmt|;
operator|(
operator|*
name|error
operator|)
operator|->
name|code
operator|=
operator|(
operator|(
operator|*
name|error
operator|)
operator|->
name|code
operator|==
name|G_FILE_ERROR_NOENT
condition|?
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
else|:
name|GIMP_CONFIG_ERROR_OPEN
operator|)
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
comment|/*  gimp_scanner_new() takes a "name" for the scanner, not a filename  */
name|scanner
operator|=
name|gimp_scanner_new
argument_list|(
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|file
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_scanner_input_text
argument_list|(
name|scanner
argument_list|,
name|g_mapped_file_get_contents
argument_list|(
name|file
argument_list|)
argument_list|,
name|g_mapped_file_get_length
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|scanner
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_scanner_new_string:  * @text:  * @text_len:  * @error:  *  * Return value:  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|GScanner
modifier|*
DECL|function|gimp_scanner_new_string (const gchar * text,gint text_len,GError ** error)
name|gimp_scanner_new_string
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|text_len
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GScanner
modifier|*
name|scanner
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|text
operator|!=
name|NULL
operator|||
name|text_len
operator|==
literal|0
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
if|if
condition|(
name|text_len
operator|<
literal|0
condition|)
name|text_len
operator|=
name|strlen
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|scanner
operator|=
name|gimp_scanner_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_scanner_input_text
argument_list|(
name|scanner
argument_list|,
name|text
argument_list|,
name|text_len
argument_list|)
expr_stmt|;
return|return
name|scanner
return|;
block|}
end_function

begin_function
specifier|static
name|GScanner
modifier|*
DECL|function|gimp_scanner_new (const gchar * name,GMappedFile * file,GError ** error)
name|gimp_scanner_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GMappedFile
modifier|*
name|file
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GScanner
modifier|*
name|scanner
decl_stmt|;
name|GimpScannerData
modifier|*
name|data
decl_stmt|;
name|scanner
operator|=
name|g_scanner_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|=
name|g_slice_new0
argument_list|(
name|GimpScannerData
argument_list|)
expr_stmt|;
name|data
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|data
operator|->
name|file
operator|=
name|file
expr_stmt|;
name|data
operator|->
name|error
operator|=
name|error
expr_stmt|;
name|scanner
operator|->
name|user_data
operator|=
name|data
expr_stmt|;
name|scanner
operator|->
name|msg_handler
operator|=
name|gimp_scanner_message
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
name|G_CSET_DIGITS
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
name|scanner
operator|->
name|config
operator|->
name|store_int64
operator|=
name|TRUE
expr_stmt|;
return|return
name|scanner
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_scanner_destroy:  * @scanner:  *  * Since: GIMP 2.4  **/
end_comment

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
name|GimpScannerData
modifier|*
name|data
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|scanner
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|=
name|scanner
operator|->
name|user_data
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|file
condition|)
name|g_mapped_file_unref
argument_list|(
name|data
operator|->
name|file
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpScannerData
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_scanner_destroy
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_scanner_parse_token:  * @scanner:  * @token:  *  * Return value:  *  * Since: GIMP 2.4  **/
end_comment

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

begin_comment
comment|/**  * gimp_scanner_parse_identifier:  * @scanner:  * @identifier:  *  * Return value:  *  * Since: GIMP 2.4  **/
end_comment

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

begin_comment
comment|/**  * gimp_scanner_parse_string:  * @scanner:  * @dest:  *  * Return value:  *  * Since: GIMP 2.4  **/
end_comment

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
else|else
block|{
operator|*
name|dest
operator|=
name|NULL
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_scanner_parse_string_no_validate:  * @scanner:  * @dest:  *  * Return value:  *  * Since: GIMP 2.4  **/
end_comment

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
else|else
operator|*
name|dest
operator|=
name|NULL
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_scanner_parse_data:  * @scanner:  * @length:  * @dest:  *  * Return value:  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_scanner_parse_data (GScanner * scanner,gint length,guint8 ** dest)
name|gimp_scanner_parse_data
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|length
parameter_list|,
name|guint8
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
name|scanner
operator|->
name|value
operator|.
name|v_string
condition|)
operator|*
name|dest
operator|=
name|g_memdup
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_string
argument_list|,
name|length
argument_list|)
expr_stmt|;
else|else
operator|*
name|dest
operator|=
name|NULL
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_scanner_parse_int:  * @scanner:  * @dest:  *  * Return value:  *  * Since: GIMP 2.4  **/
end_comment

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
name|gboolean
name|negate
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
literal|'-'
condition|)
block|{
name|negate
operator|=
name|TRUE
expr_stmt|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
block|}
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
if|if
condition|(
name|negate
condition|)
operator|*
name|dest
operator|=
operator|-
name|scanner
operator|->
name|value
operator|.
name|v_int64
expr_stmt|;
else|else
operator|*
name|dest
operator|=
name|scanner
operator|->
name|value
operator|.
name|v_int64
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_scanner_parse_float:  * @scanner:  * @dest:  *  * Return value:  *  * Since: GIMP 2.4  **/
end_comment

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
DECL|enum|__anon2c8ea1de0203
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

begin_comment
comment|/**  * gimp_scanner_parse_color:  * @scanner:  * @dest:  *  * Return value:  *  * Since: GIMP 2.4  **/
end_comment

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
name|token
operator|=
name|G_TOKEN_RIGHT_PAREN
expr_stmt|;
block|}
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

begin_comment
comment|/**  * gimp_scanner_parse_matrix2:  * @scanner:  * @dest:  *  * Return value:  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_scanner_parse_matrix2 (GScanner * scanner,GimpMatrix2 * dest)
name|gimp_scanner_parse_matrix2
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GimpMatrix2
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
name|GimpMatrix2
name|matrix
decl_stmt|;
name|scope_id
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp_scanner_parse_matrix"
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
literal|"matrix"
argument_list|)
condition|)
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"matrix"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
literal|0
argument_list|)
argument_list|)
expr_stmt|;
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
name|token
operator|=
name|G_TOKEN_FLOAT
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|matrix
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
argument_list|)
condition|)
goto|goto
name|finish
goto|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|matrix
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
argument_list|)
condition|)
goto|goto
name|finish
goto|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|matrix
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
argument_list|)
condition|)
goto|goto
name|finish
goto|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|matrix
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
argument_list|)
condition|)
goto|goto
name|finish
goto|;
name|token
operator|=
name|G_TOKEN_RIGHT_PAREN
expr_stmt|;
block|}
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
name|matrix
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
name|GimpScannerData
modifier|*
name|data
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
if|if
condition|(
name|data
operator|->
name|name
condition|)
name|g_set_error
argument_list|(
name|data
operator|->
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_PARSE
argument_list|,
name|_
argument_list|(
literal|"Error while parsing '%s' in line %d: %s"
argument_list|)
argument_list|,
name|data
operator|->
name|name
argument_list|,
name|scanner
operator|->
name|line
argument_list|,
name|message
argument_list|)
expr_stmt|;
else|else
comment|/*  should never happen, thus not marked for translation  */
name|g_set_error
argument_list|(
name|data
operator|->
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_PARSE
argument_list|,
literal|"Error parsing internal buffer: %s"
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

