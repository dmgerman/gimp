begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette-save.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_palette_save (GimpData * data,GOutputStream * output,GError ** error)
name|gimp_palette_save
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|,
name|GOutputStream
modifier|*
name|output
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
init|=
name|GIMP_PALETTE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GString
modifier|*
name|string
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gsize
name|bytes_written
decl_stmt|;
name|GError
modifier|*
name|my_error
init|=
name|NULL
decl_stmt|;
name|string
operator|=
name|g_string_new
argument_list|(
literal|"GIMP Palette\n"
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|string
argument_list|,
literal|"Name: %s\n"
literal|"Columns: %d\n#\n"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|palette
argument_list|)
argument_list|,
name|CLAMP
argument_list|(
name|gimp_palette_get_columns
argument_list|(
name|palette
argument_list|)
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
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
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
name|g_string_append_printf
argument_list|(
name|string
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
if|if
condition|(
operator|!
name|g_output_stream_write_all
argument_list|(
name|output
argument_list|,
name|string
operator|->
name|str
argument_list|,
name|string
operator|->
name|len
argument_list|,
operator|&
name|bytes_written
argument_list|,
name|NULL
argument_list|,
operator|&
name|my_error
argument_list|)
operator|||
name|bytes_written
operator|!=
name|string
operator|->
name|len
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_WRITE
argument_list|,
name|_
argument_list|(
literal|"Writing palette file '%s' failed: %s"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|gimp_data_get_file
argument_list|(
name|data
argument_list|)
argument_list|)
argument_list|,
name|my_error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|my_error
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|string
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|g_string_free
argument_list|(
name|string
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

