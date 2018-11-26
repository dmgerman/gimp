begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
DECL|function|gimp_gradient_save (GimpData * data,GOutputStream * output,GError ** error)
name|gimp_gradient_save
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
name|GimpGradient
modifier|*
name|gradient
init|=
name|GIMP_GRADIENT
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GString
modifier|*
name|string
decl_stmt|;
name|GimpGradientSegment
modifier|*
name|seg
decl_stmt|;
name|gint
name|num_segments
decl_stmt|;
comment|/* File format is:    *    *   GIMP Gradient    *   Name: name    *   number_of_segments    *   left middle right r0 g0 b0 a0 r1 g1 b1 a1 type coloring left_color_type    *   left middle right r0 g0 b0 a0 r1 g1 b1 a1 type coloring right_color_type    *   ...    */
name|string
operator|=
name|g_string_new
argument_list|(
literal|"GIMP Gradient\n"
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|string
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
name|g_string_append_printf
argument_list|(
name|string
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
name|g_string_append_printf
argument_list|(
name|string
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
comment|/* left color   */
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
comment|/* right color  */
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
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
block|{
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

begin_function
name|gboolean
DECL|function|gimp_gradient_save_pov (GimpGradient * gradient,GFile * file,GError ** error)
name|gimp_gradient_save_pov
parameter_list|(
name|GimpGradient
modifier|*
name|gradient
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GOutputStream
modifier|*
name|output
decl_stmt|;
name|GString
modifier|*
name|string
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
name|GError
modifier|*
name|my_error
init|=
name|NULL
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
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
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
name|output
operator|=
name|G_OUTPUT_STREAM
argument_list|(
name|g_file_replace
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|G_FILE_CREATE_NONE
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|output
condition|)
return|return
name|FALSE
return|;
name|string
operator|=
name|g_string_new
argument_list|(
literal|"/* color_map file created by GIMP */\n"
literal|"/* https://www.gimp.org/          */\n"
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
name|g_string_append_printf
argument_list|(
name|string
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
name|g_string_append_printf
argument_list|(
name|string
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
name|g_string_append_printf
argument_list|(
name|string
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
name|g_string_append_printf
argument_list|(
name|string
argument_list|,
literal|"} /* color_map */\n"
argument_list|)
expr_stmt|;
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
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|my_error
argument_list|)
condition|)
block|{
name|GCancellable
modifier|*
name|cancellable
init|=
name|g_cancellable_new
argument_list|()
decl_stmt|;
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
literal|"Writing POV file '%s' failed: %s"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
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
comment|/* Cancel the overwrite initiated by g_file_replace(). */
name|g_cancellable_cancel
argument_list|(
name|cancellable
argument_list|)
expr_stmt|;
name|g_output_stream_close
argument_list|(
name|output
argument_list|,
name|cancellable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|cancellable
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|output
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
name|g_object_unref
argument_list|(
name|output
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

