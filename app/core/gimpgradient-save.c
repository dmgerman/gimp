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
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient-save.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_gradient_save (GimpData * data,GError ** error)
name|gimp_gradient_save
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
name|GimpGradient
modifier|*
name|gradient
init|=
name|GIMP_GRADIENT
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpGradientSegment
modifier|*
name|seg
decl_stmt|;
name|gint
name|num_segments
decl_stmt|;
name|gchar
modifier|*
name|path
decl_stmt|;
name|FILE
modifier|*
name|file
decl_stmt|;
name|path
operator|=
name|g_file_get_path
argument_list|(
name|gimp_data_get_file
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_fopen
argument_list|(
name|path
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
name|path
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
comment|/* File format is:    *    *   GIMP Gradient    *   Name: name    *   number_of_segments    *   left middle right r0 g0 b0 a0 r1 g1 b1 a1 type coloring left_color_type    *   left middle right r0 g0 b0 a0 r1 g1 b1 a1 type coloring right_color_type    *   ...    */
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"GIMP Gradient\n"
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
name|gradient
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Count number of segments */
name|num_segments
operator|=
literal|0
expr_stmt|;
name|seg
operator|=
name|gradient
operator|->
name|segments
expr_stmt|;
while|while
condition|(
name|seg
condition|)
block|{
name|num_segments
operator|++
expr_stmt|;
name|seg
operator|=
name|seg
operator|->
name|next
expr_stmt|;
block|}
comment|/* Write rest of file */
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"%d\n"
argument_list|,
name|num_segments
argument_list|)
expr_stmt|;
for|for
control|(
name|seg
operator|=
name|gradient
operator|->
name|segments
init|;
name|seg
condition|;
name|seg
operator|=
name|seg
operator|->
name|next
control|)
block|{
name|gchar
name|buf
index|[
literal|11
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
name|seg
operator|->
name|left
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
name|seg
operator|->
name|middle
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
name|seg
operator|->
name|right
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
name|seg
operator|->
name|left_color
operator|.
name|r
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|4
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|left_color
operator|.
name|g
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|5
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|left_color
operator|.
name|b
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|6
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|left_color
operator|.
name|a
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|7
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|right_color
operator|.
name|r
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|8
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|right_color
operator|.
name|g
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|9
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|right_color
operator|.
name|b
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|10
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|right_color
operator|.
name|a
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"%s %s %s %s %s %s %s %s %s %s %s %d %d %d %d\n"
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
comment|/* left, middle, right */
name|buf
index|[
literal|3
index|]
argument_list|,
name|buf
index|[
literal|4
index|]
argument_list|,
name|buf
index|[
literal|5
index|]
argument_list|,
name|buf
index|[
literal|6
index|]
argument_list|,
comment|/* left color          */
name|buf
index|[
literal|7
index|]
argument_list|,
name|buf
index|[
literal|8
index|]
argument_list|,
name|buf
index|[
literal|9
index|]
argument_list|,
name|buf
index|[
literal|10
index|]
argument_list|,
comment|/* right color         */
operator|(
name|gint
operator|)
name|seg
operator|->
name|type
argument_list|,
operator|(
name|gint
operator|)
name|seg
operator|->
name|color
argument_list|,
operator|(
name|gint
operator|)
name|seg
operator|->
name|left_color_type
argument_list|,
operator|(
name|gint
operator|)
name|seg
operator|->
name|right_color_type
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

begin_function
name|gboolean
DECL|function|gimp_gradient_save_pov (GimpGradient * gradient,const gchar * filename,GError ** error)
name|gimp_gradient_save_pov
parameter_list|(
name|GimpGradient
modifier|*
name|gradient
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
name|FILE
modifier|*
name|file
decl_stmt|;
name|GimpGradientSegment
modifier|*
name|seg
decl_stmt|;
name|gchar
name|buf
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|gchar
name|color_buf
index|[
literal|4
index|]
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GRADIENT
argument_list|(
name|gradient
argument_list|)
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
name|file
operator|=
name|g_fopen
argument_list|(
name|filename
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
name|filename
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
else|else
block|{
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"/* color_map file created by GIMP */\n"
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"/* http://www.gimp.org/           */\n"
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"color_map {\n"
argument_list|)
expr_stmt|;
for|for
control|(
name|seg
operator|=
name|gradient
operator|->
name|segments
init|;
name|seg
condition|;
name|seg
operator|=
name|seg
operator|->
name|next
control|)
block|{
comment|/* Left */
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|left
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|color_buf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|left_color
operator|.
name|r
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|color_buf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|left_color
operator|.
name|g
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|color_buf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|left_color
operator|.
name|b
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|color_buf
index|[
literal|3
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
literal|1.0
operator|-
name|seg
operator|->
name|left_color
operator|.
name|a
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\t[%s color rgbt<%s, %s, %s, %s>]\n"
argument_list|,
name|buf
argument_list|,
name|color_buf
index|[
literal|0
index|]
argument_list|,
name|color_buf
index|[
literal|1
index|]
argument_list|,
name|color_buf
index|[
literal|2
index|]
argument_list|,
name|color_buf
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
comment|/* Middle */
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|middle
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|color_buf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
operator|(
name|seg
operator|->
name|left_color
operator|.
name|r
operator|+
name|seg
operator|->
name|right_color
operator|.
name|r
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|color_buf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
operator|(
name|seg
operator|->
name|left_color
operator|.
name|g
operator|+
name|seg
operator|->
name|right_color
operator|.
name|g
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|color_buf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
operator|(
name|seg
operator|->
name|left_color
operator|.
name|b
operator|+
name|seg
operator|->
name|right_color
operator|.
name|b
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|color_buf
index|[
literal|3
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
literal|1.0
operator|-
operator|(
name|seg
operator|->
name|left_color
operator|.
name|a
operator|+
name|seg
operator|->
name|right_color
operator|.
name|a
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\t[%s color rgbt<%s, %s, %s, %s>]\n"
argument_list|,
name|buf
argument_list|,
name|color_buf
index|[
literal|0
index|]
argument_list|,
name|color_buf
index|[
literal|1
index|]
argument_list|,
name|color_buf
index|[
literal|2
index|]
argument_list|,
name|color_buf
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
comment|/* Right */
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|right
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|color_buf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|right_color
operator|.
name|r
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|color_buf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|right_color
operator|.
name|g
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|color_buf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|right_color
operator|.
name|b
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|color_buf
index|[
literal|3
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
literal|1.0
operator|-
name|seg
operator|->
name|right_color
operator|.
name|a
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\t[%s color rgbt<%s, %s, %s, %s>]\n"
argument_list|,
name|buf
argument_list|,
name|color_buf
index|[
literal|0
index|]
argument_list|,
name|color_buf
index|[
literal|1
index|]
argument_list|,
name|color_buf
index|[
literal|2
index|]
argument_list|,
name|color_buf
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
block|}
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"} /* color_map */\n"
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

