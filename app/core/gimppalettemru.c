begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppalettemru.c  * Copyright (C) 2014 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimppalettemru.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|MAX_N_COLORS
define|#
directive|define
name|MAX_N_COLORS
value|256
end_define

begin_define
DECL|macro|RGBA_EPSILON
define|#
directive|define
name|RGBA_EPSILON
value|1e-4
end_define

begin_enum
enum|enum
DECL|enum|__anon2b26e7800103
block|{
DECL|enumerator|COLOR_HISTORY
name|COLOR_HISTORY
init|=
literal|1
block|}
enum|;
end_enum

begin_macro
DECL|function|G_DEFINE_TYPE (GimpPaletteMru,gimp_palette_mru,GIMP_TYPE_PALETTE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPaletteMru
argument_list|,
argument|gimp_palette_mru
argument_list|,
argument|GIMP_TYPE_PALETTE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_palette_mru_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_palette_mru_class_init
parameter_list|(
name|GimpPaletteMruClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_mru_init (GimpPaletteMru * palette)
name|gimp_palette_mru_init
parameter_list|(
name|GimpPaletteMru
modifier|*
name|palette
parameter_list|)
block|{ }
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpData
modifier|*
DECL|function|gimp_palette_mru_new (const gchar * name)
name|gimp_palette_mru_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpPaletteMru
modifier|*
name|palette
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|*
name|name
operator|!=
literal|'\0'
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|palette
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PALETTE_MRU
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
literal|"mime-type"
argument_list|,
literal|"application/x-gimp-palette"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_DATA
argument_list|(
name|palette
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_palette_mru_load (GimpPaletteMru * mru,GFile * file)
name|gimp_palette_mru_load
parameter_list|(
name|GimpPaletteMru
modifier|*
name|mru
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
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
name|GIMP_IS_PALETTE_MRU
argument_list|(
name|mru
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|mru
argument_list|)
expr_stmt|;
name|scanner
operator|=
name|gimp_scanner_new_file
argument_list|(
name|file
argument_list|,
name|NULL
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
name|end
goto|;
name|gimp_palette_add_entry
argument_list|(
name|palette
argument_list|,
operator|-
literal|1
argument_list|,
name|_
argument_list|(
literal|"History Color"
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_palette_get_n_colors
argument_list|(
name|palette
argument_list|)
operator|==
name|MAX_N_COLORS
condition|)
goto|goto
name|end
goto|;
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
name|end
label|:
name|gimp_scanner_unref
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_palette_mru_save (GimpPaletteMru * mru,GFile * file)
name|gimp_palette_mru_save
parameter_list|(
name|GimpPaletteMru
modifier|*
name|mru
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|GimpConfigWriter
modifier|*
name|writer
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PALETTE_MRU
argument_list|(
name|mru
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|writer
operator|=
name|gimp_config_writer_new_from_file
argument_list|(
name|file
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
if|if
condition|(
operator|!
name|writer
condition|)
return|return;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|mru
argument_list|)
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
name|list
operator|=
name|palette
operator|->
name|colors
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPaletteEntry
modifier|*
name|entry
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gchar
name|buf
index|[
literal|4
index|]
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|g_ascii_dtostr
argument_list|(
name|buf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
name|entry
operator|->
name|color
operator|.
name|r
argument_list|)
expr_stmt|;
name|g_ascii_dtostr
argument_list|(
name|buf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
name|entry
operator|->
name|color
operator|.
name|g
argument_list|)
expr_stmt|;
name|g_ascii_dtostr
argument_list|(
name|buf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
name|entry
operator|->
name|color
operator|.
name|b
argument_list|)
expr_stmt|;
name|g_ascii_dtostr
argument_list|(
name|buf
index|[
literal|3
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
name|entry
operator|->
name|color
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
DECL|function|gimp_palette_mru_add (GimpPaletteMru * mru,const GimpRGB * color)
name|gimp_palette_mru_add
parameter_list|(
name|GimpPaletteMru
modifier|*
name|mru
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PALETTE_MRU
argument_list|(
name|mru
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|mru
argument_list|)
expr_stmt|;
comment|/*  is the added color already there?  */
for|for
control|(
name|list
operator|=
name|gimp_palette_get_colors
argument_list|(
name|palette
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPaletteEntry
modifier|*
name|entry
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_rgba_distance
argument_list|(
operator|&
name|entry
operator|->
name|color
argument_list|,
name|color
argument_list|)
operator|<
name|RGBA_EPSILON
condition|)
block|{
name|gimp_palette_move_entry
argument_list|(
name|palette
argument_list|,
name|entry
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  Even though they are nearly the same color, let's make them            *  exactly equal.            */
name|gimp_palette_set_entry_color
argument_list|(
name|palette
argument_list|,
literal|0
argument_list|,
name|color
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
if|if
condition|(
name|gimp_palette_get_n_colors
argument_list|(
name|palette
argument_list|)
operator|==
name|MAX_N_COLORS
condition|)
block|{
name|gimp_palette_delete_entry
argument_list|(
name|palette
argument_list|,
name|gimp_palette_get_entry
argument_list|(
name|palette
argument_list|,
name|MAX_N_COLORS
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_palette_add_entry
argument_list|(
name|palette
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"History Color"
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

