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
file|"config/gimpxmlparser.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient-load.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GList
modifier|*
DECL|function|gimp_gradient_load (GimpContext * context,const gchar * filename,GError ** error)
name|gimp_gradient_load
parameter_list|(
name|GimpContext
modifier|*
name|context
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
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|GimpGradientSegment
modifier|*
name|prev
decl_stmt|;
name|gint
name|num_segments
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|FILE
modifier|*
name|file
decl_stmt|;
name|gchar
name|line
index|[
literal|1024
index|]
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
name|g_path_is_absolute
argument_list|(
name|filename
argument_list|)
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
name|g_fopen
argument_list|(
name|filename
argument_list|,
literal|"rb"
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
literal|"Could not open '%s' for reading: %s"
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
name|NULL
return|;
block|}
name|linenum
operator|=
literal|1
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|line
argument_list|,
sizeof|sizeof
argument_list|(
name|line
argument_list|)
argument_list|,
name|file
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parse error in gradient file '%s': "
literal|"Read error in line %d."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
operator|!
name|g_str_has_prefix
argument_list|(
name|line
argument_list|,
literal|"GIMP Gradient"
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parse error in gradient file '%s': "
literal|"Not a GIMP gradient file."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|gradient
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_GRADIENT
argument_list|,
literal|"mime-type"
argument_list|,
literal|"application/x-gimp-gradient"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|line
argument_list|,
sizeof|sizeof
argument_list|(
name|line
argument_list|)
argument_list|,
name|file
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parse error in gradient file '%s': "
literal|"Read error in line %d."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gradient
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|line
argument_list|,
literal|"Name: "
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|utf8
decl_stmt|;
name|utf8
operator|=
name|gimp_any_to_utf8
argument_list|(
name|g_strstrip
argument_list|(
name|line
operator|+
name|strlen
argument_list|(
literal|"Name: "
argument_list|)
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|_
argument_list|(
literal|"Invalid UTF-8 string in gradient file '%s'."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gradient
argument_list|)
argument_list|,
name|utf8
argument_list|)
expr_stmt|;
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|line
argument_list|,
sizeof|sizeof
argument_list|(
name|line
argument_list|)
argument_list|,
name|file
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parse error in gradient file '%s': "
literal|"Read error in line %d."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gradient
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
else|else
comment|/* old gradient format */
block|{
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gradient
argument_list|)
argument_list|,
name|g_filename_display_basename
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|num_segments
operator|=
name|atoi
argument_list|(
name|line
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_segments
operator|<
literal|1
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parse error in gradient file '%s': "
literal|"File is corrupt in line %d."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gradient
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|prev
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_segments
condition|;
name|i
operator|++
control|)
block|{
name|GimpGradientSegment
modifier|*
name|seg
decl_stmt|;
name|gchar
modifier|*
name|end
decl_stmt|;
name|gint
name|color
decl_stmt|;
name|gint
name|type
decl_stmt|;
name|gint
name|left_color_type
decl_stmt|;
name|gint
name|right_color_type
decl_stmt|;
name|seg
operator|=
name|gimp_gradient_segment_new
argument_list|()
expr_stmt|;
name|seg
operator|->
name|prev
operator|=
name|prev
expr_stmt|;
if|if
condition|(
name|prev
condition|)
name|prev
operator|->
name|next
operator|=
name|seg
expr_stmt|;
else|else
name|gradient
operator|->
name|segments
operator|=
name|seg
expr_stmt|;
name|linenum
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|line
argument_list|,
sizeof|sizeof
argument_list|(
name|line
argument_list|)
argument_list|,
name|file
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parse error in gradient file '%s': "
literal|"Read error in line %d."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gradient
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|seg
operator|->
name|left
operator|=
name|g_ascii_strtod
argument_list|(
name|line
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|middle
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|right
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|left_color
operator|.
name|r
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|left_color
operator|.
name|g
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|left_color
operator|.
name|b
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|left_color
operator|.
name|a
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|right_color
operator|.
name|r
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|right_color
operator|.
name|g
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|right_color
operator|.
name|b
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
name|errno
operator|!=
name|ERANGE
condition|)
name|seg
operator|->
name|right_color
operator|.
name|a
operator|=
name|g_ascii_strtod
argument_list|(
name|end
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|errno
operator|!=
name|ERANGE
condition|)
block|{
switch|switch
condition|(
name|sscanf
argument_list|(
name|end
argument_list|,
literal|"%d %d %d %d"
argument_list|,
operator|&
name|type
argument_list|,
operator|&
name|color
argument_list|,
operator|&
name|left_color_type
argument_list|,
operator|&
name|right_color_type
argument_list|)
condition|)
block|{
case|case
literal|4
case|:
name|seg
operator|->
name|left_color_type
operator|=
operator|(
name|GimpGradientColor
operator|)
name|left_color_type
expr_stmt|;
name|seg
operator|->
name|right_color_type
operator|=
operator|(
name|GimpGradientColor
operator|)
name|right_color_type
expr_stmt|;
comment|/* fall thru */
case|case
literal|2
case|:
name|seg
operator|->
name|type
operator|=
operator|(
name|GimpGradientSegmentType
operator|)
name|type
expr_stmt|;
name|seg
operator|->
name|color
operator|=
operator|(
name|GimpGradientSegmentColor
operator|)
name|color
expr_stmt|;
break|break;
default|default:
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parse error in gradient file '%s': "
literal|"Corrupt segment %d in line %d."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|i
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gradient
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
else|else
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parse error in gradient file '%s': "
literal|"Corrupt segment %d in line %d."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|i
argument_list|,
name|linenum
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gradient
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
operator|(
name|prev
operator|&&
operator|(
name|prev
operator|->
name|right
operator|<
name|seg
operator|->
name|left
operator|)
operator|)
operator|||
operator|(
operator|!
name|prev
operator|&&
operator|(
literal|0.
operator|<
name|seg
operator|->
name|left
operator|)
operator|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Gradient file '%s' is corrupt: "
literal|"Segments do not span the range 0-1."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gradient
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|prev
operator|=
name|seg
expr_stmt|;
block|}
if|if
condition|(
name|prev
operator|->
name|right
operator|<
literal|1.0
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Gradient file '%s' is corrupt: "
literal|"Segments do not span the range 0-1."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gradient
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|g_list_prepend
argument_list|(
name|NULL
argument_list|,
name|gradient
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  SVG gradient parser  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c862b910108
block|{
DECL|member|gradient
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
comment|/*  current gradient    */
DECL|member|gradients
name|GList
modifier|*
name|gradients
decl_stmt|;
comment|/*  finished gradients  */
DECL|member|stops
name|GList
modifier|*
name|stops
decl_stmt|;
DECL|typedef|SvgParser
block|}
name|SvgParser
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c862b910208
block|{
DECL|member|offset
name|gdouble
name|offset
decl_stmt|;
DECL|member|color
name|GimpRGB
name|color
decl_stmt|;
DECL|typedef|SvgStop
block|}
name|SvgStop
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|svg_parser_start_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_values
parameter_list|,
name|gpointer
name|user_data
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
name|svg_parser_end_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
name|gpointer
name|user_data
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
name|GimpGradientSegment
modifier|*
name|svg_parser_gradient_segments
parameter_list|(
name|GList
modifier|*
name|stops
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|SvgStop
modifier|*
name|svg_parse_gradient_stop
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|values
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|markup_parser
specifier|static
specifier|const
name|GMarkupParser
name|markup_parser
init|=
block|{
name|svg_parser_start_element
block|,
name|svg_parser_end_element
block|,
name|NULL
block|,
comment|/*  characters   */
name|NULL
block|,
comment|/*  passthrough  */
name|NULL
comment|/*  error        */
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|GList
modifier|*
DECL|function|gimp_gradient_load_svg (GimpContext * context,const gchar * filename,GError ** error)
name|gimp_gradient_load_svg
parameter_list|(
name|GimpContext
modifier|*
name|context
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
name|GimpXmlParser
modifier|*
name|xml_parser
decl_stmt|;
name|SvgParser
name|parser
init|=
block|{
name|NULL
block|, }
decl_stmt|;
name|gboolean
name|success
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
name|g_path_is_absolute
argument_list|(
name|filename
argument_list|)
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
name|xml_parser
operator|=
name|gimp_xml_parser_new
argument_list|(
operator|&
name|markup_parser
argument_list|,
operator|&
name|parser
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_xml_parser_parse_file
argument_list|(
name|xml_parser
argument_list|,
name|filename
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|gimp_xml_parser_free
argument_list|(
name|xml_parser
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
operator|&&
operator|!
name|parser
operator|.
name|gradients
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"No linear gradients found in '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|error
operator|&&
operator|*
name|error
condition|)
comment|/*  parser reported an error  */
block|{
name|gchar
modifier|*
name|msg
init|=
operator|(
operator|*
name|error
operator|)
operator|->
name|message
decl_stmt|;
operator|(
operator|*
name|error
operator|)
operator|->
name|message
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Failed to import gradients from '%s': %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|msg
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|msg
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|parser
operator|.
name|gradient
condition|)
name|g_object_unref
argument_list|(
name|parser
operator|.
name|gradient
argument_list|)
expr_stmt|;
if|if
condition|(
name|parser
operator|.
name|stops
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|parser
operator|.
name|stops
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
name|g_slice_free
argument_list|(
name|SvgStop
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|parser
operator|.
name|stops
argument_list|)
expr_stmt|;
block|}
return|return
name|g_list_reverse
argument_list|(
name|parser
operator|.
name|gradients
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|svg_parser_start_element (GMarkupParseContext * context,const gchar * element_name,const gchar ** attribute_names,const gchar ** attribute_values,gpointer user_data,GError ** error)
name|svg_parser_start_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_values
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|SvgParser
modifier|*
name|parser
init|=
name|user_data
decl_stmt|;
if|if
condition|(
operator|!
name|parser
operator|->
name|gradient
operator|&&
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"linearGradient"
argument_list|)
operator|==
literal|0
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
while|while
condition|(
operator|*
name|attribute_names
operator|&&
operator|*
name|attribute_values
condition|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
operator|*
name|attribute_names
argument_list|,
literal|"id"
argument_list|)
operator|==
literal|0
operator|&&
operator|*
name|attribute_values
condition|)
name|name
operator|=
operator|*
name|attribute_values
expr_stmt|;
name|attribute_names
operator|++
expr_stmt|;
name|attribute_values
operator|++
expr_stmt|;
block|}
name|parser
operator|->
name|gradient
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_GRADIENT
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
literal|"mime-type"
argument_list|,
literal|"image/svg+xml"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|parser
operator|->
name|gradient
operator|&&
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"stop"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|SvgStop
modifier|*
name|stop
init|=
name|svg_parse_gradient_stop
argument_list|(
name|attribute_names
argument_list|,
name|attribute_values
argument_list|)
decl_stmt|;
comment|/*  The spec clearly states that each gradient stop's offset        *  value is required to be equal to or greater than the        *  previous gradient stop's offset value.        */
if|if
condition|(
name|parser
operator|->
name|stops
condition|)
name|stop
operator|->
name|offset
operator|=
name|MAX
argument_list|(
name|stop
operator|->
name|offset
argument_list|,
operator|(
operator|(
name|SvgStop
operator|*
operator|)
name|parser
operator|->
name|stops
operator|->
name|data
operator|)
operator|->
name|offset
argument_list|)
expr_stmt|;
name|parser
operator|->
name|stops
operator|=
name|g_list_prepend
argument_list|(
name|parser
operator|->
name|stops
argument_list|,
name|stop
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|svg_parser_end_element (GMarkupParseContext * context,const gchar * element_name,gpointer user_data,GError ** error)
name|svg_parser_end_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|SvgParser
modifier|*
name|parser
init|=
name|user_data
decl_stmt|;
if|if
condition|(
name|parser
operator|->
name|gradient
operator|&&
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"linearGradient"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|parser
operator|->
name|gradient
operator|->
name|segments
operator|=
name|svg_parser_gradient_segments
argument_list|(
name|parser
operator|->
name|stops
argument_list|)
expr_stmt|;
if|if
condition|(
name|parser
operator|->
name|gradient
operator|->
name|segments
condition|)
name|parser
operator|->
name|gradients
operator|=
name|g_list_prepend
argument_list|(
name|parser
operator|->
name|gradients
argument_list|,
name|parser
operator|->
name|gradient
argument_list|)
expr_stmt|;
else|else
name|g_object_unref
argument_list|(
name|parser
operator|->
name|gradient
argument_list|)
expr_stmt|;
name|parser
operator|->
name|gradient
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GimpGradientSegment
modifier|*
DECL|function|svg_parser_gradient_segments (GList * stops)
name|svg_parser_gradient_segments
parameter_list|(
name|GList
modifier|*
name|stops
parameter_list|)
block|{
name|GimpGradientSegment
modifier|*
name|segment
decl_stmt|;
name|SvgStop
modifier|*
name|stop
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
operator|!
name|stops
condition|)
return|return
name|NULL
return|;
name|stop
operator|=
name|stops
operator|->
name|data
expr_stmt|;
name|segment
operator|=
name|gimp_gradient_segment_new
argument_list|()
expr_stmt|;
name|segment
operator|->
name|left_color
operator|=
name|stop
operator|->
name|color
expr_stmt|;
name|segment
operator|->
name|right_color
operator|=
name|stop
operator|->
name|color
expr_stmt|;
comment|/*  the list of offsets is sorted from largest to smallest  */
for|for
control|(
name|list
operator|=
name|g_list_next
argument_list|(
name|stops
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
name|GimpGradientSegment
modifier|*
name|next
init|=
name|segment
decl_stmt|;
name|segment
operator|->
name|left
operator|=
name|stop
operator|->
name|offset
expr_stmt|;
name|segment
operator|->
name|middle
operator|=
operator|(
name|segment
operator|->
name|left
operator|+
name|segment
operator|->
name|right
operator|)
operator|/
literal|2.0
expr_stmt|;
name|segment
operator|=
name|gimp_gradient_segment_new
argument_list|()
expr_stmt|;
name|segment
operator|->
name|next
operator|=
name|next
expr_stmt|;
name|next
operator|->
name|prev
operator|=
name|segment
expr_stmt|;
name|segment
operator|->
name|right
operator|=
name|stop
operator|->
name|offset
expr_stmt|;
name|segment
operator|->
name|right_color
operator|=
name|stop
operator|->
name|color
expr_stmt|;
name|stop
operator|=
name|list
operator|->
name|data
expr_stmt|;
name|segment
operator|->
name|left_color
operator|=
name|stop
operator|->
name|color
expr_stmt|;
block|}
name|segment
operator|->
name|middle
operator|=
operator|(
name|segment
operator|->
name|left
operator|+
name|segment
operator|->
name|right
operator|)
operator|/
literal|2.0
expr_stmt|;
if|if
condition|(
name|stop
operator|->
name|offset
operator|>
literal|0.0
condition|)
name|segment
operator|->
name|right_color
operator|=
name|stop
operator|->
name|color
expr_stmt|;
comment|/*  FIXME: remove empty segments here or add a GimpGradient API to do that    */
return|return
name|segment
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|svg_parse_gradient_stop_style_prop (SvgStop * stop,const gchar * name,const gchar * value)
name|svg_parse_gradient_stop_style_prop
parameter_list|(
name|SvgStop
modifier|*
name|stop
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"stop-color"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gimp_rgb_parse_css
argument_list|(
operator|&
name|stop
operator|->
name|color
argument_list|,
name|value
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"stop-opacity"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gdouble
name|opacity
init|=
name|g_ascii_strtod
argument_list|(
name|value
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|errno
operator|!=
name|ERANGE
condition|)
name|gimp_rgb_set_alpha
argument_list|(
operator|&
name|stop
operator|->
name|color
argument_list|,
name|CLAMP
argument_list|(
name|opacity
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  very simplistic CSS style parser  */
end_comment

begin_function
specifier|static
name|void
DECL|function|svg_parse_gradient_stop_style (SvgStop * stop,const gchar * style)
name|svg_parse_gradient_stop_style
parameter_list|(
name|SvgStop
modifier|*
name|stop
parameter_list|,
specifier|const
name|gchar
modifier|*
name|style
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|end
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|sep
decl_stmt|;
while|while
condition|(
operator|*
name|style
condition|)
block|{
while|while
condition|(
name|g_ascii_isspace
argument_list|(
operator|*
name|style
argument_list|)
condition|)
name|style
operator|++
expr_stmt|;
for|for
control|(
name|end
operator|=
name|style
init|;
operator|*
name|end
operator|&&
operator|*
name|end
operator|!=
literal|';'
condition|;
name|end
operator|++
control|)
comment|/* do nothing */
empty_stmt|;
for|for
control|(
name|sep
operator|=
name|style
init|;
name|sep
operator|<
name|end
operator|&&
operator|*
name|sep
operator|!=
literal|':'
condition|;
name|sep
operator|++
control|)
comment|/* do nothing */
empty_stmt|;
if|if
condition|(
name|end
operator|>
name|sep
operator|&&
name|sep
operator|>
name|style
condition|)
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
modifier|*
name|value
decl_stmt|;
name|name
operator|=
name|g_strndup
argument_list|(
name|style
argument_list|,
name|sep
operator|-
name|style
argument_list|)
expr_stmt|;
name|sep
operator|++
expr_stmt|;
name|value
operator|=
name|g_strndup
argument_list|(
name|sep
argument_list|,
name|end
operator|-
name|sep
operator|-
operator|(
operator|*
name|end
operator|==
literal|';'
condition|?
literal|1
else|:
literal|0
operator|)
argument_list|)
expr_stmt|;
name|svg_parse_gradient_stop_style_prop
argument_list|(
name|stop
argument_list|,
name|name
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
name|style
operator|=
name|end
expr_stmt|;
if|if
condition|(
operator|*
name|style
operator|==
literal|';'
condition|)
name|style
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|SvgStop
modifier|*
DECL|function|svg_parse_gradient_stop (const gchar ** names,const gchar ** values)
name|svg_parse_gradient_stop
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|values
parameter_list|)
block|{
name|SvgStop
modifier|*
name|stop
init|=
name|g_slice_new0
argument_list|(
name|SvgStop
argument_list|)
decl_stmt|;
name|gimp_rgb_set_alpha
argument_list|(
operator|&
name|stop
operator|->
name|color
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
while|while
condition|(
operator|*
name|names
operator|&&
operator|*
name|values
condition|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
operator|*
name|names
argument_list|,
literal|"offset"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gchar
modifier|*
name|end
decl_stmt|;
name|stop
operator|->
name|offset
operator|=
name|g_ascii_strtod
argument_list|(
operator|*
name|values
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|&&
operator|*
name|end
operator|==
literal|'%'
condition|)
name|stop
operator|->
name|offset
operator|/=
literal|100.0
expr_stmt|;
name|stop
operator|->
name|offset
operator|=
name|CLAMP
argument_list|(
name|stop
operator|->
name|offset
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
operator|*
name|names
argument_list|,
literal|"style"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|svg_parse_gradient_stop_style
argument_list|(
name|stop
argument_list|,
operator|*
name|values
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|svg_parse_gradient_stop_style_prop
argument_list|(
name|stop
argument_list|,
operator|*
name|names
argument_list|,
operator|*
name|values
argument_list|)
expr_stmt|;
block|}
name|names
operator|++
expr_stmt|;
name|values
operator|++
expr_stmt|;
block|}
return|return
name|stop
return|;
block|}
end_function

end_unit

