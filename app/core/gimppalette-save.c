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
file|<stdlib.h>
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
file|<glib/gstdio.h>
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
DECL|function|gimp_palette_save (GimpData * data,GError ** error)
name|gimp_palette_save
parameter_list|(
name|GimpData
modifier|*
name|data
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
name|GList
modifier|*
name|list
decl_stmt|;
name|FILE
modifier|*
name|file
decl_stmt|;
name|file
operator|=
name|g_fopen
argument_list|(
name|gimp_data_get_filename
argument_list|(
name|data
argument_list|)
argument_list|,
literal|"wb"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_OPEN
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for writing: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|gimp_data_get_filename
argument_list|(
name|data
argument_list|)
argument_list|)
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
name|file
argument_list|,
literal|"GIMP Palette\n"
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"Name: %s\n"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"Columns: %d\n#\n"
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
name|fprintf
argument_list|(
name|file
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
name|file
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

