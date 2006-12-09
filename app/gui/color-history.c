begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * color-history.c  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"color-history.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b2f212d0103
block|{
DECL|enumerator|COLOR_HISTORY
name|COLOR_HISTORY
init|=
literal|1
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|color_history_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_history_add_from_rc
parameter_list|(
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|color_history
specifier|static
name|GimpRGB
name|color_history
index|[
name|COLOR_HISTORY_SIZE
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_history_initialized
specifier|static
name|gboolean
name|color_history_initialized
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|color_history_save (Gimp * gimp)
name|color_history_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpConfigWriter
modifier|*
name|writer
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"colorrc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Writing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|writer
operator|=
name|gimp_config_writer_new_file
argument_list|(
name|filename
argument_list|,
name|TRUE
argument_list|,
literal|"GIMP colorrc\n\n"
literal|"This file holds a list of "
literal|"recently used colors."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|writer
condition|)
return|return;
if|if
condition|(
operator|!
name|color_history_initialized
condition|)
name|color_history_init
argument_list|()
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"color-history"
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|COLOR_HISTORY_SIZE
condition|;
name|i
operator|++
control|)
block|{
name|gchar
name|buf
index|[
literal|4
index|]
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|color_history
index|[
name|i
index|]
operator|.
name|r
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|color_history
index|[
name|i
index|]
operator|.
name|g
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|color_history
index|[
name|i
index|]
operator|.
name|b
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|3
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|color_history
index|[
name|i
index|]
operator|.
name|a
argument_list|)
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"color-rgba"
argument_list|)
expr_stmt|;
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"%s %s %s %s"
argument_list|,
name|buf
index|[
literal|0
index|]
argument_list|,
name|buf
index|[
literal|1
index|]
argument_list|,
name|buf
index|[
literal|2
index|]
argument_list|,
name|buf
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_finish
argument_list|(
name|writer
argument_list|,
literal|"end of colorrc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|color_history_restore (Gimp * gimp)
name|color_history_restore
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GScanner
modifier|*
name|scanner
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"colorrc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|scanner
operator|=
name|gimp_scanner_new_file
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|scanner
condition|)
return|return;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
literal|0
argument_list|,
literal|"color-history"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|COLOR_HISTORY
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
if|if
condition|(
name|scanner
operator|->
name|value
operator|.
name|v_symbol
operator|==
name|GINT_TO_POINTER
argument_list|(
name|COLOR_HISTORY
argument_list|)
condition|)
block|{
while|while
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|G_TOKEN_LEFT_PAREN
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_color
argument_list|(
name|scanner
argument_list|,
operator|&
name|color
argument_list|)
condition|)
goto|goto
name|error
goto|;
name|color_history_add_from_rc
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
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
break|break;
default|default:
comment|/* do nothing */
break|break;
block|}
block|}
name|error
label|:
name|gimp_scanner_destroy
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|color_history_set (gint index,const GimpRGB * rgb)
name|color_history_set
parameter_list|(
name|gint
name|index
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|index
operator|>=
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|index
operator|<
name|COLOR_HISTORY_SIZE
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|color_history_initialized
condition|)
name|color_history_init
argument_list|()
expr_stmt|;
name|color_history
index|[
name|index
index|]
operator|=
operator|*
name|rgb
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|color_history_get (gint index,GimpRGB * rgb)
name|color_history_get
parameter_list|(
name|gint
name|index
parameter_list|,
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|index
operator|>=
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|index
operator|<
name|COLOR_HISTORY_SIZE
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|color_history_initialized
condition|)
name|color_history_init
argument_list|()
expr_stmt|;
operator|*
name|rgb
operator|=
name|color_history
index|[
name|index
index|]
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|color_history_add (const GimpRGB * rgb)
name|color_history_add
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|gint
name|shift_begin
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|color_history_initialized
condition|)
name|color_history_init
argument_list|()
expr_stmt|;
comment|/*  is the added color already there?  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|COLOR_HISTORY_SIZE
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|gimp_rgba_distance
argument_list|(
operator|&
name|color_history
index|[
name|i
index|]
argument_list|,
name|rgb
argument_list|)
operator|<
literal|0.0001
condition|)
block|{
name|shift_begin
operator|=
name|i
expr_stmt|;
goto|goto
name|doit
goto|;
block|}
block|}
comment|/*  if not, are there two equal colors?  */
if|if
condition|(
name|shift_begin
operator|==
operator|-
literal|1
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|COLOR_HISTORY_SIZE
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
name|i
operator|+
literal|1
init|;
name|j
operator|<
name|COLOR_HISTORY_SIZE
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
name|gimp_rgba_distance
argument_list|(
operator|&
name|color_history
index|[
name|i
index|]
argument_list|,
operator|&
name|color_history
index|[
name|j
index|]
argument_list|)
operator|<
literal|0.0001
condition|)
block|{
name|shift_begin
operator|=
name|i
expr_stmt|;
goto|goto
name|doit
goto|;
block|}
block|}
block|}
block|}
comment|/*  if not, shift them all  */
if|if
condition|(
name|shift_begin
operator|==
operator|-
literal|1
condition|)
name|shift_begin
operator|=
name|COLOR_HISTORY_SIZE
operator|-
literal|1
expr_stmt|;
name|doit
label|:
for|for
control|(
name|i
operator|=
name|shift_begin
init|;
name|i
operator|>
literal|0
condition|;
name|i
operator|--
control|)
name|color_history
index|[
name|i
index|]
operator|=
name|color_history
index|[
name|i
operator|-
literal|1
index|]
expr_stmt|;
name|color_history
index|[
literal|0
index|]
operator|=
operator|*
name|rgb
expr_stmt|;
return|return
name|shift_begin
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|color_history_init (void)
name|color_history_init
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|COLOR_HISTORY_SIZE
condition|;
name|i
operator|++
control|)
name|gimp_rgba_set
argument_list|(
operator|&
name|color_history
index|[
name|i
index|]
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|color_history_initialized
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_history_add_from_rc (GimpRGB * color)
name|color_history_add_from_rc
parameter_list|(
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
specifier|static
name|gint
name|index
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|color_history_initialized
condition|)
name|color_history_init
argument_list|()
expr_stmt|;
if|if
condition|(
name|color
operator|&&
name|index
operator|<
name|COLOR_HISTORY_SIZE
condition|)
block|{
name|color_history
index|[
name|index
operator|++
index|]
operator|=
operator|*
name|color
expr_stmt|;
block|}
block|}
end_function

end_unit

