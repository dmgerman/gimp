begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"vectors-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"gimpanchor.h"
end_include

begin_include
include|#
directive|include
file|"gimpstroke.h"
end_include

begin_include
include|#
directive|include
file|"gimpbezierstroke.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectors-export.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|GString
modifier|*
name|gimp_vectors_export
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_export_image_size
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GString
modifier|*
name|str
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_export_path
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GString
modifier|*
name|str
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_vectors_export_path_data
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_vectors_export_file:  * @image: the #GimpImage from which to export vectors  * @vectors: a #GimpVectors object or %NULL to export all vectors in @image  * @filename: the name of the file to write  * @error: return location for errors  *  * Exports one or more vectors to a SVG file.  *  * Return value: %TRUE on success,  *               %FALSE if there was an error writing the file  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_vectors_export_file (const GimpImage * image,const GimpVectors * vectors,const gchar * filename,GError ** error)
name|gimp_vectors_export_file
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpVectors
modifier|*
name|vectors
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
name|GString
modifier|*
name|str
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|vectors
operator|==
name|NULL
operator|||
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
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
literal|"w"
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
literal|0
argument_list|,
literal|0
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
name|str
operator|=
name|gimp_vectors_export
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"%s"
argument_list|,
name|str
operator|->
name|str
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|str
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|fclose
argument_list|(
name|file
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Error while writing '%s': %s"
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
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_export_string:  * @image: the #GimpImage from which to export vectors  * @vectors: a #GimpVectors object or %NULL to export all vectors in @image  *  * Exports one or more vectors to a SVG string.  *  * Return value: a %NUL-terminated string that holds a complete XML document  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_vectors_export_string (const GimpImage * image,const GimpVectors * vectors)
name|gimp_vectors_export_string
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|vectors
operator|==
name|NULL
operator|||
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_string_free
argument_list|(
name|gimp_vectors_export
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|)
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GString
modifier|*
DECL|function|gimp_vectors_export (const GimpImage * image,const GimpVectors * vectors)
name|gimp_vectors_export
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
block|{
name|GString
modifier|*
name|str
init|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
literal|"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 20010904//EN\"\n"
literal|"              \"http://www.w3.org/TR/2001/REC-SVG-20010904/DTD/svg10.dtd\">\n"
literal|"\n"
literal|"<svg xmlns=\"http://www.w3.org/2000/svg\"\n"
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|"     "
argument_list|)
expr_stmt|;
name|gimp_vectors_export_image_size
argument_list|(
name|image
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_string_append_c
argument_list|(
name|str
argument_list|,
literal|'\n'
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|"     viewBox=\"0 0 %d %d\">\n"
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|vectors
condition|)
block|{
name|gimp_vectors_export_path
argument_list|(
name|vectors
argument_list|,
name|str
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|image
operator|->
name|vectors
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
name|gimp_vectors_export_path
argument_list|(
name|GIMP_VECTORS
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|,
name|str
argument_list|)
expr_stmt|;
block|}
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|"</svg>\n"
argument_list|)
expr_stmt|;
return|return
name|str
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_export_image_size (const GimpImage * image,GString * str)
name|gimp_vectors_export_image_size
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GString
modifier|*
name|str
parameter_list|)
block|{
name|GimpUnit
name|unit
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|abbrev
decl_stmt|;
name|gchar
name|wbuf
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|gchar
name|hbuf
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|gdouble
name|w
decl_stmt|,
name|h
decl_stmt|;
name|w
operator|=
operator|(
name|gdouble
operator|)
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|/
name|image
operator|->
name|xresolution
expr_stmt|;
name|h
operator|=
operator|(
name|gdouble
operator|)
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
operator|/
name|image
operator|->
name|yresolution
expr_stmt|;
comment|/*  FIXME: should probably use the display unit here  */
name|unit
operator|=
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|unit
condition|)
block|{
case|case
name|GIMP_UNIT_INCH
case|:
name|abbrev
operator|=
literal|"in"
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_MM
case|:
name|abbrev
operator|=
literal|"mm"
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_POINT
case|:
name|abbrev
operator|=
literal|"pt"
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_PICA
case|:
name|abbrev
operator|=
literal|"pc"
expr_stmt|;
break|break;
default|default:
name|abbrev
operator|=
literal|"cm"
expr_stmt|;
name|unit
operator|=
name|GIMP_UNIT_MM
expr_stmt|;
name|w
operator|/=
literal|10.0
expr_stmt|;
name|h
operator|/=
literal|10.0
expr_stmt|;
break|break;
block|}
name|g_ascii_formatd
argument_list|(
name|wbuf
argument_list|,
sizeof|sizeof
argument_list|(
name|wbuf
argument_list|)
argument_list|,
literal|"%g"
argument_list|,
name|w
operator|*
name|_gimp_unit_get_factor
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|unit
argument_list|)
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|hbuf
argument_list|,
sizeof|sizeof
argument_list|(
name|hbuf
argument_list|)
argument_list|,
literal|"%g"
argument_list|,
name|h
operator|*
name|_gimp_unit_get_factor
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|unit
argument_list|)
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|"width=\"%s%s\" height=\"%s%s\""
argument_list|,
name|wbuf
argument_list|,
name|abbrev
argument_list|,
name|hbuf
argument_list|,
name|abbrev
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_export_path (const GimpVectors * vectors,GString * str)
name|gimp_vectors_export_path
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GString
modifier|*
name|str
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|vectors
argument_list|)
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|data
init|=
name|gimp_vectors_export_path_data
argument_list|(
name|vectors
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|esc_name
decl_stmt|;
name|esc_name
operator|=
name|g_markup_escape_text
argument_list|(
name|name
argument_list|,
name|strlen
argument_list|(
name|name
argument_list|)
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|"<path id=\"%s\"\n"
literal|"        fill=\"none\" stroke=\"black\" stroke-width=\"1\"\n"
literal|"        d=\"%s\" />\n"
argument_list|,
name|esc_name
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|esc_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_define
DECL|macro|NEWLINE
define|#
directive|define
name|NEWLINE
value|"\n           "
end_define

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_vectors_export_path_data (const GimpVectors * vectors)
name|gimp_vectors_export_path_data
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
block|{
name|GString
modifier|*
name|str
decl_stmt|;
name|GList
modifier|*
name|strokes
decl_stmt|;
name|gchar
name|x_string
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|gchar
name|y_string
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|gboolean
name|closed
init|=
name|FALSE
decl_stmt|;
name|str
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|strokes
operator|=
name|vectors
operator|->
name|strokes
init|;
name|strokes
condition|;
name|strokes
operator|=
name|strokes
operator|->
name|next
control|)
block|{
name|GimpStroke
modifier|*
name|stroke
init|=
name|strokes
operator|->
name|data
decl_stmt|;
name|GArray
modifier|*
name|control_points
decl_stmt|;
name|GimpAnchor
modifier|*
name|anchor
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|closed
condition|)
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
name|NEWLINE
argument_list|)
expr_stmt|;
name|control_points
operator|=
name|gimp_stroke_control_points_get
argument_list|(
name|stroke
argument_list|,
operator|&
name|closed
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_BEZIER_STROKE
argument_list|(
name|stroke
argument_list|)
condition|)
block|{
if|if
condition|(
name|control_points
operator|->
name|len
operator|>=
literal|3
condition|)
block|{
name|anchor
operator|=
operator|&
name|g_array_index
argument_list|(
name|control_points
argument_list|,
name|GimpAnchor
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|x_string
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%.2f"
argument_list|,
name|anchor
operator|->
name|position
operator|.
name|x
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|y_string
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%.2f"
argument_list|,
name|anchor
operator|->
name|position
operator|.
name|y
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|"M %s,%s"
argument_list|,
name|x_string
argument_list|,
name|y_string
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|control_points
operator|->
name|len
operator|>
literal|3
condition|)
block|{
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
name|NEWLINE
literal|"C"
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|2
init|;
name|i
operator|<
operator|(
name|control_points
operator|->
name|len
operator|+
operator|(
name|closed
condition|?
literal|2
else|:
operator|-
literal|1
operator|)
operator|)
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|i
operator|>
literal|2
operator|&&
name|i
operator|%
literal|3
operator|==
literal|2
condition|)
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
name|NEWLINE
literal|" "
argument_list|)
expr_stmt|;
name|anchor
operator|=
operator|&
name|g_array_index
argument_list|(
name|control_points
argument_list|,
name|GimpAnchor
argument_list|,
name|i
operator|%
name|control_points
operator|->
name|len
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|x_string
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%.2f"
argument_list|,
name|anchor
operator|->
name|position
operator|.
name|x
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|y_string
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%.2f"
argument_list|,
name|anchor
operator|->
name|position
operator|.
name|y
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|" %s,%s"
argument_list|,
name|x_string
argument_list|,
name|y_string
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|closed
operator|&&
name|control_points
operator|->
name|len
operator|>
literal|3
condition|)
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|" Z"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"Unknown stroke type\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|control_points
operator|->
name|len
operator|>=
literal|1
condition|)
block|{
name|anchor
operator|=
operator|&
name|g_array_index
argument_list|(
name|control_points
argument_list|,
name|GimpAnchor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|x_string
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|".2f"
argument_list|,
name|anchor
operator|->
name|position
operator|.
name|x
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|y_string
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|".2f"
argument_list|,
name|anchor
operator|->
name|position
operator|.
name|y
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|"M %s,%s"
argument_list|,
name|x_string
argument_list|,
name|y_string
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|control_points
operator|->
name|len
operator|>
literal|1
condition|)
block|{
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
name|NEWLINE
literal|"L"
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|control_points
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|i
operator|>
literal|1
operator|&&
name|i
operator|%
literal|3
operator|==
literal|1
condition|)
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
name|NEWLINE
literal|" "
argument_list|)
expr_stmt|;
name|anchor
operator|=
operator|&
name|g_array_index
argument_list|(
name|control_points
argument_list|,
name|GimpAnchor
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|x_string
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%.2f"
argument_list|,
name|anchor
operator|->
name|position
operator|.
name|x
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|y_string
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%.2f"
argument_list|,
name|anchor
operator|->
name|position
operator|.
name|y
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|" %s,%s"
argument_list|,
name|x_string
argument_list|,
name|y_string
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|closed
operator|&&
name|control_points
operator|->
name|len
operator|>
literal|1
condition|)
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
literal|" Z"
argument_list|)
expr_stmt|;
block|}
name|g_array_free
argument_list|(
name|control_points
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
return|return
name|g_strchomp
argument_list|(
name|g_string_free
argument_list|(
name|str
argument_list|,
name|FALSE
argument_list|)
argument_list|)
return|;
block|}
end_function

end_unit

