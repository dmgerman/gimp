begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
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
file|<errno.h>
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette.h"
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
name|gimp_palette_class_init
parameter_list|(
name|GimpPaletteClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_palette_init
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_palette_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gsize
name|gimp_palette_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_palette_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_palette_dirty
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_palette_save
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_palette_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_palette_entry_free
parameter_list|(
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDataClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_palette_get_type (void)
name|gimp_palette_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|palette_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|palette_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|palette_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpPaletteClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_palette_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpPalette
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_palette_init
block|,       }
decl_stmt|;
name|palette_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DATA
argument_list|,
literal|"GimpPalette"
argument_list|,
operator|&
name|palette_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|palette_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_class_init (GimpPaletteClass * klass)
name|gimp_palette_class_init
parameter_list|(
name|GimpPaletteClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
decl_stmt|;
name|GimpDataClass
modifier|*
name|data_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_object_class
operator|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|viewable_class
operator|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|data_class
operator|=
name|GIMP_DATA_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_palette_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_palette_get_memsize
expr_stmt|;
name|viewable_class
operator|->
name|get_new_preview
operator|=
name|gimp_palette_get_new_preview
expr_stmt|;
name|data_class
operator|->
name|dirty
operator|=
name|gimp_palette_dirty
expr_stmt|;
name|data_class
operator|->
name|save
operator|=
name|gimp_palette_save
expr_stmt|;
name|data_class
operator|->
name|get_extension
operator|=
name|gimp_palette_get_extension
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_init (GimpPalette * palette)
name|gimp_palette_init
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|)
block|{
name|palette
operator|->
name|colors
operator|=
name|NULL
expr_stmt|;
name|palette
operator|->
name|n_colors
operator|=
literal|0
expr_stmt|;
name|palette
operator|->
name|n_columns
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_finalize (GObject * object)
name|gimp_palette_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PALETTE
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|palette
operator|->
name|colors
condition|)
block|{
name|g_list_foreach
argument_list|(
name|palette
operator|->
name|colors
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_palette_entry_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|palette
operator|->
name|colors
argument_list|)
expr_stmt|;
name|palette
operator|->
name|colors
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gsize
DECL|function|gimp_palette_get_memsize (GimpObject * object)
name|gimp_palette_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
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
name|gsize
name|memsize
init|=
literal|0
decl_stmt|;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|object
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
decl_stmt|;
name|entry
operator|=
operator|(
name|GimpPaletteEntry
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|memsize
operator|+=
sizeof|sizeof
argument_list|(
name|GList
argument_list|)
operator|+
sizeof|sizeof
argument_list|(
name|GimpPaletteEntry
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
operator|->
name|name
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|entry
operator|->
name|name
argument_list|)
operator|+
literal|1
expr_stmt|;
block|}
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_palette_get_new_preview (GimpViewable * viewable,gint width,gint height)
name|gimp_palette_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|GimpPaletteEntry
modifier|*
name|entry
decl_stmt|;
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|guchar
modifier|*
name|b
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|guchar
name|white
index|[
literal|3
index|]
init|=
block|{
literal|255
block|,
literal|255
block|,
literal|255
block|}
decl_stmt|;
name|gint
name|columns
decl_stmt|;
name|gint
name|rows
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|i
decl_stmt|;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
name|temp_buf
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|white
argument_list|)
expr_stmt|;
DECL|macro|CELL_SIZE
define|#
directive|define
name|CELL_SIZE
value|4
name|columns
operator|=
name|width
operator|/
name|CELL_SIZE
expr_stmt|;
name|rows
operator|=
name|height
operator|/
name|CELL_SIZE
expr_stmt|;
name|buf
operator|=
name|temp_buf_data
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
name|b
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|b
argument_list|,
literal|255
argument_list|,
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|list
operator|=
name|palette
operator|->
name|colors
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|rows
operator|&&
name|list
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|columns
operator|&&
name|list
condition|;
name|x
operator|++
control|)
block|{
name|entry
operator|=
operator|(
name|GimpPaletteEntry
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|entry
operator|->
name|color
argument_list|,
operator|&
name|b
index|[
name|x
operator|*
name|CELL_SIZE
operator|*
literal|3
operator|+
literal|0
index|]
argument_list|,
operator|&
name|b
index|[
name|x
operator|*
name|CELL_SIZE
operator|*
literal|3
operator|+
literal|1
index|]
argument_list|,
operator|&
name|b
index|[
name|x
operator|*
name|CELL_SIZE
operator|*
literal|3
operator|+
literal|2
index|]
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|CELL_SIZE
condition|;
name|i
operator|++
control|)
block|{
name|b
index|[
operator|(
name|x
operator|*
name|CELL_SIZE
operator|+
name|i
operator|)
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|b
index|[
operator|(
name|x
operator|*
name|CELL_SIZE
operator|)
operator|*
literal|3
operator|+
literal|0
index|]
expr_stmt|;
name|b
index|[
operator|(
name|x
operator|*
name|CELL_SIZE
operator|+
name|i
operator|)
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|b
index|[
operator|(
name|x
operator|*
name|CELL_SIZE
operator|)
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
name|b
index|[
operator|(
name|x
operator|*
name|CELL_SIZE
operator|+
name|i
operator|)
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|b
index|[
operator|(
name|x
operator|*
name|CELL_SIZE
operator|)
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
block|}
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|CELL_SIZE
condition|;
name|i
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|buf
operator|+
operator|(
operator|(
name|y
operator|*
name|CELL_SIZE
operator|+
name|i
operator|)
operator|*
name|width
operator|)
operator|*
literal|3
argument_list|,
name|b
argument_list|,
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
block|}
block|}
undef|#
directive|undef
name|CELL_SIZE
name|g_free
argument_list|(
name|b
argument_list|)
expr_stmt|;
return|return
name|temp_buf
return|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_palette_new (const gchar * name)
name|gimp_palette_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
init|=
name|NULL
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
name|GIMP_PALETTE
argument_list|(
name|g_object_new
argument_list|(
name|GIMP_TYPE_PALETTE
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|palette
argument_list|)
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
name|GimpData
modifier|*
DECL|function|gimp_palette_get_standard (void)
name|gimp_palette_get_standard
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpPalette
modifier|*
name|standard_palette
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|standard_palette
condition|)
block|{
name|standard_palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|g_object_new
argument_list|(
name|GIMP_TYPE_PALETTE
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|standard_palette
argument_list|)
argument_list|,
literal|"Standard"
argument_list|)
expr_stmt|;
block|}
return|return
name|GIMP_DATA
argument_list|(
name|standard_palette
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_palette_load (const gchar * filename)
name|gimp_palette_load
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|gchar
name|str
index|[
literal|1024
index|]
decl_stmt|;
name|gchar
modifier|*
name|tok
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|gint
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gint
name|linenum
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
operator|*
name|filename
operator|!=
literal|'\0'
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|r
operator|=
name|g
operator|=
name|b
operator|=
literal|0
expr_stmt|;
comment|/*  Open the requested file  */
if|if
condition|(
operator|!
operator|(
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"r"
argument_list|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Failed to open palette file '%s': %s"
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
name|linenum
operator|=
literal|0
expr_stmt|;
name|fread
argument_list|(
name|str
argument_list|,
literal|13
argument_list|,
literal|1
argument_list|,
name|fp
argument_list|)
expr_stmt|;
name|str
index|[
literal|13
index|]
operator|=
literal|'\0'
expr_stmt|;
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|str
argument_list|,
literal|"GIMP Palette\n"
argument_list|)
condition|)
block|{
comment|/* bad magic, but maybe it has \r\n at the end of lines? */
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|str
argument_list|,
literal|"GIMP Palette\r"
argument_list|)
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Loading palette '%s':\n"
literal|"Corrupt palette: missing magic header\n"
literal|"Does this file need converting from DOS?"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
else|else
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Loading palette '%s':\n"
literal|"Corrupt palette: missing magic header"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|palette
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PALETTE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_data_set_filename
argument_list|(
name|GIMP_DATA
argument_list|(
name|palette
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|str
argument_list|,
literal|1024
argument_list|,
name|fp
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Loading palette '%s':\nRead error in line %d."
argument_list|)
argument_list|,
name|filename
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|strncmp
argument_list|(
name|str
argument_list|,
literal|"Name: "
argument_list|,
name|strlen
argument_list|(
literal|"Name: "
argument_list|)
argument_list|)
condition|)
block|{
if|if
condition|(
name|g_utf8_validate
argument_list|(
name|str
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|palette
argument_list|)
argument_list|,
name|g_strstrip
argument_list|(
operator|&
name|str
index|[
name|strlen
argument_list|(
literal|"Name: "
argument_list|)
index|]
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Invalid UTF-8 string in palette file '%s'"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|palette
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Unnamed"
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|str
argument_list|,
literal|1024
argument_list|,
name|fp
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Loading palette '%s':\nRead error in line %d."
argument_list|)
argument_list|,
name|filename
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|strncmp
argument_list|(
name|str
argument_list|,
literal|"Columns: "
argument_list|,
name|strlen
argument_list|(
literal|"Columns: "
argument_list|)
argument_list|)
condition|)
block|{
name|gint
name|columns
decl_stmt|;
name|columns
operator|=
name|atoi
argument_list|(
name|g_strstrip
argument_list|(
operator|&
name|str
index|[
name|strlen
argument_list|(
literal|"Columns: "
argument_list|)
index|]
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|columns
operator|<
literal|0
operator|||
name|columns
operator|>
literal|256
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Loading palette '%s':\n"
literal|"Invalid number of columns in line %d."
argument_list|)
argument_list|,
name|filename
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|columns
operator|=
literal|0
expr_stmt|;
block|}
name|palette
operator|->
name|n_columns
operator|=
name|columns
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|str
argument_list|,
literal|1024
argument_list|,
name|fp
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Loading palette '%s':\nRead error in line %d."
argument_list|)
argument_list|,
name|filename
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|linenum
operator|++
expr_stmt|;
block|}
block|}
else|else
comment|/* old palette format */
block|{
name|gchar
modifier|*
name|basename
decl_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|palette
argument_list|)
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
block|}
while|while
condition|(
operator|!
name|feof
argument_list|(
name|fp
argument_list|)
condition|)
block|{
if|if
condition|(
name|str
index|[
literal|0
index|]
operator|!=
literal|'#'
condition|)
block|{
name|tok
operator|=
name|strtok
argument_list|(
name|str
argument_list|,
literal|" \t"
argument_list|)
expr_stmt|;
if|if
condition|(
name|tok
condition|)
name|r
operator|=
name|atoi
argument_list|(
name|tok
argument_list|)
expr_stmt|;
else|else
comment|/* maybe we should just abort? */
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Loading palette '%s':\n"
literal|"Missing RED component in line %d."
argument_list|)
argument_list|,
name|filename
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|tok
operator|=
name|strtok
argument_list|(
name|NULL
argument_list|,
literal|" \t"
argument_list|)
expr_stmt|;
if|if
condition|(
name|tok
condition|)
name|g
operator|=
name|atoi
argument_list|(
name|tok
argument_list|)
expr_stmt|;
else|else
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Loading palette '%s':\n"
literal|"Missing GREEN component in line %d."
argument_list|)
argument_list|,
name|filename
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|tok
operator|=
name|strtok
argument_list|(
name|NULL
argument_list|,
literal|" \t"
argument_list|)
expr_stmt|;
if|if
condition|(
name|tok
condition|)
name|b
operator|=
name|atoi
argument_list|(
name|tok
argument_list|)
expr_stmt|;
else|else
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Loading palette '%s':\n"
literal|"Missing BLUE component in line %d."
argument_list|)
argument_list|,
name|filename
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
comment|/* optional name */
name|tok
operator|=
name|strtok
argument_list|(
name|NULL
argument_list|,
literal|"\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
operator|<
literal|0
operator|||
name|r
operator|>
literal|255
operator|||
name|g
operator|<
literal|0
operator|||
name|g
operator|>
literal|255
operator|||
name|b
operator|<
literal|0
operator|||
name|b
operator|>
literal|255
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Loading palette '%s':\n"
literal|"RGB value out of range in line %d."
argument_list|)
argument_list|,
name|filename
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|(
name|guchar
operator|)
name|r
argument_list|,
operator|(
name|guchar
operator|)
name|g
argument_list|,
operator|(
name|guchar
operator|)
name|b
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|gimp_palette_add_entry
argument_list|(
name|palette
argument_list|,
name|tok
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|str
argument_list|,
literal|1024
argument_list|,
name|fp
argument_list|)
condition|)
block|{
if|if
condition|(
name|feof
argument_list|(
name|fp
argument_list|)
condition|)
break|break;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Loading palette '%s':\nRead error in line %d."
argument_list|)
argument_list|,
name|filename
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|linenum
operator|++
expr_stmt|;
block|}
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|GIMP_DATA
argument_list|(
name|palette
argument_list|)
operator|->
name|dirty
operator|=
name|FALSE
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
specifier|static
name|void
DECL|function|gimp_palette_dirty (GimpData * data)
name|gimp_palette_dirty
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
if|if
condition|(
name|GIMP_DATA_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dirty
condition|)
name|GIMP_DATA_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dirty
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_palette_save (GimpData * data)
name|gimp_palette_save
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|GimpPaletteEntry
modifier|*
name|entry
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|fp
operator|=
name|fopen
argument_list|(
name|GIMP_DATA
argument_list|(
name|palette
argument_list|)
operator|->
name|filename
argument_list|,
literal|"w"
argument_list|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Cannot save palette '%s':\n%s"
argument_list|)
argument_list|,
name|GIMP_DATA
argument_list|(
name|palette
argument_list|)
operator|->
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"GIMP Palette\n"
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"Name: %s\n"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|palette
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"Columns: %d\n#\n"
argument_list|,
name|CLAMP
argument_list|(
name|palette
operator|->
name|n_columns
argument_list|,
literal|0
argument_list|,
literal|256
argument_list|)
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
name|entry
operator|=
operator|(
name|GimpPaletteEntry
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|entry
operator|->
name|color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"%3d %3d %3d\t%s\n"
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
name|entry
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_DATA_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|save
condition|)
return|return
name|GIMP_DATA_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|save
argument_list|(
name|data
argument_list|)
return|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_palette_get_extension (GimpData * data)
name|gimp_palette_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
return|return
name|GIMP_PALETTE_FILE_EXTENSION
return|;
block|}
end_function

begin_function
name|GimpPaletteEntry
modifier|*
DECL|function|gimp_palette_add_entry (GimpPalette * palette,const gchar * name,GimpRGB * color)
name|gimp_palette_add_entry
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpPaletteEntry
modifier|*
name|entry
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PALETTE
argument_list|(
name|palette
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|entry
operator|=
name|g_new0
argument_list|(
name|GimpPaletteEntry
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|entry
operator|->
name|color
operator|=
operator|*
name|color
expr_stmt|;
name|entry
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
condition|?
name|name
else|:
name|_
argument_list|(
literal|"Untitled"
argument_list|)
argument_list|)
expr_stmt|;
name|entry
operator|->
name|position
operator|=
name|palette
operator|->
name|n_colors
expr_stmt|;
name|palette
operator|->
name|colors
operator|=
name|g_list_append
argument_list|(
name|palette
operator|->
name|colors
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|palette
operator|->
name|n_colors
operator|+=
literal|1
expr_stmt|;
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|entry
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_palette_delete_entry (GimpPalette * palette,GimpPaletteEntry * entry)
name|gimp_palette_delete_entry
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|pos
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PALETTE
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|entry
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_list_find
argument_list|(
name|palette
operator|->
name|colors
argument_list|,
name|entry
argument_list|)
condition|)
block|{
name|pos
operator|=
name|entry
operator|->
name|position
expr_stmt|;
name|gimp_palette_entry_free
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|palette
operator|->
name|colors
operator|=
name|g_list_remove
argument_list|(
name|palette
operator|->
name|colors
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|palette
operator|->
name|n_colors
operator|--
expr_stmt|;
for|for
control|(
name|list
operator|=
name|g_list_nth
argument_list|(
name|palette
operator|->
name|colors
argument_list|,
name|pos
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
name|entry
operator|=
operator|(
name|GimpPaletteEntry
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|entry
operator|->
name|position
operator|=
name|pos
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|palette
operator|->
name|n_colors
operator|==
literal|0
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|gimp_palette_add_entry
argument_list|(
name|palette
argument_list|,
name|_
argument_list|(
literal|"Black"
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_entry_free (GimpPaletteEntry * entry)
name|gimp_palette_entry_free
parameter_list|(
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|entry
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|entry
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|entry
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

