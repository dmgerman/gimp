begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<pango/pangocairo.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"text-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimptext.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayout.h"
end_include

begin_struct
DECL|struct|_GimpTextLayout
struct|struct
name|_GimpTextLayout
block|{
DECL|member|object
name|GObject
name|object
decl_stmt|;
DECL|member|text
name|GimpText
modifier|*
name|text
decl_stmt|;
DECL|member|xres
name|gdouble
name|xres
decl_stmt|;
DECL|member|yres
name|gdouble
name|yres
decl_stmt|;
DECL|member|layout
name|PangoLayout
modifier|*
name|layout
decl_stmt|;
DECL|member|extents
name|PangoRectangle
name|extents
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_text_layout_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_layout_position
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|PangoContext
modifier|*
name|gimp_text_get_pango_context
parameter_list|(
name|GimpText
modifier|*
name|text
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|yres
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_text_layout_pixel_size
parameter_list|(
name|gdouble
name|value
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|res
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_text_layout_point_size
parameter_list|(
name|gdouble
name|value
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|res
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpTextLayout,gimp_text_layout,G_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTextLayout
argument_list|,
argument|gimp_text_layout
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_text_layout_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_text_layout_class_init
parameter_list|(
name|GimpTextLayoutClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_text_layout_finalize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_layout_init (GimpTextLayout * layout)
name|gimp_text_layout_init
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|)
block|{
name|layout
operator|->
name|text
operator|=
name|NULL
expr_stmt|;
name|layout
operator|->
name|layout
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_layout_finalize (GObject * object)
name|gimp_text_layout_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTextLayout
modifier|*
name|layout
init|=
name|GIMP_TEXT_LAYOUT
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|layout
operator|->
name|text
condition|)
block|{
name|g_object_unref
argument_list|(
name|layout
operator|->
name|text
argument_list|)
expr_stmt|;
name|layout
operator|->
name|text
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|layout
operator|->
name|layout
condition|)
block|{
name|g_object_unref
argument_list|(
name|layout
operator|->
name|layout
argument_list|)
expr_stmt|;
name|layout
operator|->
name|layout
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
name|GimpTextLayout
modifier|*
DECL|function|gimp_text_layout_new (GimpText * text,GimpImage * image)
name|gimp_text_layout_new
parameter_list|(
name|GimpText
modifier|*
name|text
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpTextLayout
modifier|*
name|layout
decl_stmt|;
name|PangoContext
modifier|*
name|context
decl_stmt|;
name|PangoFontDescription
modifier|*
name|font_desc
decl_stmt|;
name|PangoAlignment
name|alignment
init|=
name|PANGO_ALIGN_LEFT
decl_stmt|;
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|gint
name|size
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEXT
argument_list|(
name|text
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|font_desc
operator|=
name|pango_font_description_from_string
argument_list|(
name|text
operator|->
name|font
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|font_desc
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|size
operator|=
name|gimp_text_layout_point_size
argument_list|(
name|text
operator|->
name|font_size
argument_list|,
name|text
operator|->
name|unit
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|pango_font_description_set_size
argument_list|(
name|font_desc
argument_list|,
name|MAX
argument_list|(
literal|1
argument_list|,
name|size
argument_list|)
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_text_get_pango_context
argument_list|(
name|text
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|layout
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEXT_LAYOUT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|layout
operator|->
name|text
operator|=
name|g_object_ref
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|layout
operator|->
name|layout
operator|=
name|pango_layout_new
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|layout
operator|->
name|xres
operator|=
name|xres
expr_stmt|;
name|layout
operator|->
name|yres
operator|=
name|yres
expr_stmt|;
name|pango_layout_set_wrap
argument_list|(
name|layout
operator|->
name|layout
argument_list|,
name|PANGO_WRAP_WORD_CHAR
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|pango_layout_set_font_description
argument_list|(
name|layout
operator|->
name|layout
argument_list|,
name|font_desc
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|font_desc
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
operator|->
name|markup
condition|)
name|pango_layout_set_markup
argument_list|(
name|layout
operator|->
name|layout
argument_list|,
name|text
operator|->
name|markup
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|text
operator|->
name|text
condition|)
name|pango_layout_set_text
argument_list|(
name|layout
operator|->
name|layout
argument_list|,
name|text
operator|->
name|text
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
else|else
name|pango_layout_set_text
argument_list|(
name|layout
operator|->
name|layout
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|text
operator|->
name|justify
condition|)
block|{
case|case
name|GIMP_TEXT_JUSTIFY_LEFT
case|:
name|alignment
operator|=
name|PANGO_ALIGN_LEFT
expr_stmt|;
break|break;
case|case
name|GIMP_TEXT_JUSTIFY_RIGHT
case|:
name|alignment
operator|=
name|PANGO_ALIGN_RIGHT
expr_stmt|;
break|break;
case|case
name|GIMP_TEXT_JUSTIFY_CENTER
case|:
name|alignment
operator|=
name|PANGO_ALIGN_CENTER
expr_stmt|;
break|break;
case|case
name|GIMP_TEXT_JUSTIFY_FILL
case|:
name|alignment
operator|=
name|PANGO_ALIGN_LEFT
expr_stmt|;
name|pango_layout_set_justify
argument_list|(
name|layout
operator|->
name|layout
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
block|}
name|pango_layout_set_alignment
argument_list|(
name|layout
operator|->
name|layout
argument_list|,
name|alignment
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|text
operator|->
name|box_mode
condition|)
block|{
case|case
name|GIMP_TEXT_BOX_DYNAMIC
case|:
break|break;
case|case
name|GIMP_TEXT_BOX_FIXED
case|:
name|pango_layout_set_width
argument_list|(
name|layout
operator|->
name|layout
argument_list|,
name|gimp_text_layout_pixel_size
argument_list|(
name|text
operator|->
name|box_width
argument_list|,
name|text
operator|->
name|box_unit
argument_list|,
name|xres
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
name|pango_layout_set_indent
argument_list|(
name|layout
operator|->
name|layout
argument_list|,
name|gimp_text_layout_pixel_size
argument_list|(
name|text
operator|->
name|indent
argument_list|,
name|text
operator|->
name|unit
argument_list|,
name|xres
argument_list|)
argument_list|)
expr_stmt|;
name|pango_layout_set_spacing
argument_list|(
name|layout
operator|->
name|layout
argument_list|,
name|gimp_text_layout_pixel_size
argument_list|(
name|text
operator|->
name|line_spacing
argument_list|,
name|text
operator|->
name|unit
argument_list|,
name|yres
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|fabs
argument_list|(
name|text
operator|->
name|letter_spacing
argument_list|)
operator|>
literal|0.1
condition|)
block|{
name|PangoAttrList
modifier|*
name|attrs
decl_stmt|;
name|PangoAttribute
modifier|*
name|attr
decl_stmt|;
name|attrs
operator|=
name|pango_layout_get_attributes
argument_list|(
name|layout
operator|->
name|layout
argument_list|)
expr_stmt|;
if|if
condition|(
name|attrs
condition|)
name|pango_attr_list_ref
argument_list|(
name|attrs
argument_list|)
expr_stmt|;
else|else
name|attrs
operator|=
name|pango_attr_list_new
argument_list|()
expr_stmt|;
name|attr
operator|=
name|pango_attr_letter_spacing_new
argument_list|(
name|text
operator|->
name|letter_spacing
operator|*
name|PANGO_SCALE
argument_list|)
expr_stmt|;
name|attr
operator|->
name|start_index
operator|=
literal|0
expr_stmt|;
name|attr
operator|->
name|end_index
operator|=
operator|-
literal|1
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|attrs
argument_list|,
name|attr
argument_list|)
expr_stmt|;
name|pango_layout_set_attributes
argument_list|(
name|layout
operator|->
name|layout
argument_list|,
name|attrs
argument_list|)
expr_stmt|;
name|pango_attr_list_unref
argument_list|(
name|attrs
argument_list|)
expr_stmt|;
block|}
name|gimp_text_layout_position
argument_list|(
name|layout
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|text
operator|->
name|box_mode
condition|)
block|{
case|case
name|GIMP_TEXT_BOX_DYNAMIC
case|:
break|break;
case|case
name|GIMP_TEXT_BOX_FIXED
case|:
name|layout
operator|->
name|extents
operator|.
name|width
operator|=
name|PANGO_PIXELS
argument_list|(
name|gimp_text_layout_pixel_size
argument_list|(
name|text
operator|->
name|box_width
argument_list|,
name|text
operator|->
name|box_unit
argument_list|,
name|xres
argument_list|)
argument_list|)
expr_stmt|;
name|layout
operator|->
name|extents
operator|.
name|height
operator|=
name|PANGO_PIXELS
argument_list|(
name|gimp_text_layout_pixel_size
argument_list|(
name|text
operator|->
name|box_height
argument_list|,
name|text
operator|->
name|box_unit
argument_list|,
name|yres
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|layout
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_text_layout_get_size (GimpTextLayout * layout,gint * width,gint * height)
name|gimp_text_layout_get_size
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYOUT
argument_list|(
name|layout
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
condition|)
operator|*
name|width
operator|=
name|layout
operator|->
name|extents
operator|.
name|width
expr_stmt|;
if|if
condition|(
name|height
condition|)
operator|*
name|height
operator|=
name|layout
operator|->
name|extents
operator|.
name|height
expr_stmt|;
return|return
operator|(
name|layout
operator|->
name|extents
operator|.
name|width
operator|>
literal|0
operator|&&
name|layout
operator|->
name|extents
operator|.
name|height
operator|>
literal|0
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_layout_get_offsets (GimpTextLayout * layout,gint * x,gint * y)
name|gimp_text_layout_get_offsets
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYOUT
argument_list|(
name|layout
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
condition|)
operator|*
name|x
operator|=
name|layout
operator|->
name|extents
operator|.
name|x
expr_stmt|;
if|if
condition|(
name|y
condition|)
operator|*
name|y
operator|=
name|layout
operator|->
name|extents
operator|.
name|y
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_layout_get_resolution (GimpTextLayout * layout,gdouble * xres,gdouble * yres)
name|gimp_text_layout_get_resolution
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|gdouble
modifier|*
name|xres
parameter_list|,
name|gdouble
modifier|*
name|yres
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYOUT
argument_list|(
name|layout
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|xres
condition|)
operator|*
name|xres
operator|=
name|layout
operator|->
name|xres
expr_stmt|;
if|if
condition|(
name|yres
condition|)
operator|*
name|yres
operator|=
name|layout
operator|->
name|yres
expr_stmt|;
block|}
end_function

begin_function
name|GimpText
modifier|*
DECL|function|gimp_text_layout_get_text (GimpTextLayout * layout)
name|gimp_text_layout_get_text
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYOUT
argument_list|(
name|layout
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|layout
operator|->
name|text
return|;
block|}
end_function

begin_function
name|PangoLayout
modifier|*
DECL|function|gimp_text_layout_get_pango_layout (GimpTextLayout * layout)
name|gimp_text_layout_get_pango_layout
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYOUT
argument_list|(
name|layout
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|layout
operator|->
name|layout
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_layout_get_transform (GimpTextLayout * layout,cairo_matrix_t * matrix)
name|gimp_text_layout_get_transform
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|cairo_matrix_t
modifier|*
name|matrix
parameter_list|)
block|{
name|GimpText
modifier|*
name|text
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gdouble
name|norm
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYOUT
argument_list|(
name|layout
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|matrix
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|text
operator|=
name|gimp_text_layout_get_text
argument_list|(
name|layout
argument_list|)
expr_stmt|;
name|gimp_text_layout_get_resolution
argument_list|(
name|layout
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|norm
operator|=
literal|1.0
operator|/
name|yres
operator|*
name|xres
expr_stmt|;
name|matrix
operator|->
name|xx
operator|=
name|text
operator|->
name|transformation
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*
name|norm
expr_stmt|;
name|matrix
operator|->
name|xy
operator|=
name|text
operator|->
name|transformation
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
literal|1.0
expr_stmt|;
name|matrix
operator|->
name|yx
operator|=
name|text
operator|->
name|transformation
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|*
name|norm
expr_stmt|;
name|matrix
operator|->
name|yy
operator|=
name|text
operator|->
name|transformation
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|*
literal|1.0
expr_stmt|;
name|matrix
operator|->
name|x0
operator|=
literal|0
expr_stmt|;
name|matrix
operator|->
name|y0
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_layout_transform_rect (GimpTextLayout * layout,PangoRectangle * rect)
name|gimp_text_layout_transform_rect
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|PangoRectangle
modifier|*
name|rect
parameter_list|)
block|{
name|cairo_matrix_t
name|matrix
decl_stmt|;
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdouble
name|width
decl_stmt|,
name|height
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYOUT
argument_list|(
name|layout
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rect
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|x
operator|=
name|rect
operator|->
name|x
expr_stmt|;
name|y
operator|=
name|rect
operator|->
name|y
expr_stmt|;
name|width
operator|=
name|rect
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|rect
operator|->
name|height
expr_stmt|;
name|gimp_text_layout_get_transform
argument_list|(
name|layout
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
name|cairo_matrix_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|cairo_matrix_transform_distance
argument_list|(
operator|&
name|matrix
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|rect
operator|->
name|x
operator|=
name|ROUND
argument_list|(
name|x
argument_list|)
expr_stmt|;
name|rect
operator|->
name|y
operator|=
name|ROUND
argument_list|(
name|y
argument_list|)
expr_stmt|;
name|rect
operator|->
name|width
operator|=
name|ROUND
argument_list|(
name|width
argument_list|)
expr_stmt|;
name|rect
operator|->
name|height
operator|=
name|ROUND
argument_list|(
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_layout_transform_point (GimpTextLayout * layout,gdouble * x,gdouble * y)
name|gimp_text_layout_transform_point
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|)
block|{
name|cairo_matrix_t
name|matrix
decl_stmt|;
name|gdouble
name|_x
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|_y
init|=
literal|0.0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYOUT
argument_list|(
name|layout
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
condition|)
name|_x
operator|=
operator|*
name|x
expr_stmt|;
if|if
condition|(
name|y
condition|)
name|_y
operator|=
operator|*
name|y
expr_stmt|;
name|gimp_text_layout_get_transform
argument_list|(
name|layout
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
name|cairo_matrix_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
operator|&
name|_x
argument_list|,
operator|&
name|_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
condition|)
operator|*
name|x
operator|=
name|_x
expr_stmt|;
if|if
condition|(
name|y
condition|)
operator|*
name|y
operator|=
name|_y
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_layout_transform_distance (GimpTextLayout * layout,gdouble * x,gdouble * y)
name|gimp_text_layout_transform_distance
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|)
block|{
name|cairo_matrix_t
name|matrix
decl_stmt|;
name|gdouble
name|_x
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|_y
init|=
literal|0.0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYOUT
argument_list|(
name|layout
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
condition|)
name|_x
operator|=
operator|*
name|x
expr_stmt|;
if|if
condition|(
name|y
condition|)
name|_y
operator|=
operator|*
name|y
expr_stmt|;
name|gimp_text_layout_get_transform
argument_list|(
name|layout
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
name|cairo_matrix_transform_distance
argument_list|(
operator|&
name|matrix
argument_list|,
operator|&
name|_x
argument_list|,
operator|&
name|_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
condition|)
operator|*
name|x
operator|=
name|_x
expr_stmt|;
if|if
condition|(
name|y
condition|)
operator|*
name|y
operator|=
name|_y
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_layout_untransform_rect (GimpTextLayout * layout,PangoRectangle * rect)
name|gimp_text_layout_untransform_rect
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|PangoRectangle
modifier|*
name|rect
parameter_list|)
block|{
name|cairo_matrix_t
name|matrix
decl_stmt|;
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdouble
name|width
decl_stmt|,
name|height
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYOUT
argument_list|(
name|layout
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rect
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|x
operator|=
name|rect
operator|->
name|x
expr_stmt|;
name|y
operator|=
name|rect
operator|->
name|y
expr_stmt|;
name|width
operator|=
name|rect
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|rect
operator|->
name|height
expr_stmt|;
name|gimp_text_layout_get_transform
argument_list|(
name|layout
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
if|if
condition|(
name|cairo_matrix_invert
argument_list|(
operator|&
name|matrix
argument_list|)
operator|==
name|CAIRO_STATUS_SUCCESS
condition|)
block|{
name|cairo_matrix_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|cairo_matrix_transform_distance
argument_list|(
operator|&
name|matrix
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|rect
operator|->
name|x
operator|=
name|ROUND
argument_list|(
name|x
argument_list|)
expr_stmt|;
name|rect
operator|->
name|y
operator|=
name|ROUND
argument_list|(
name|y
argument_list|)
expr_stmt|;
name|rect
operator|->
name|width
operator|=
name|ROUND
argument_list|(
name|width
argument_list|)
expr_stmt|;
name|rect
operator|->
name|height
operator|=
name|ROUND
argument_list|(
name|height
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_layout_untransform_point (GimpTextLayout * layout,gdouble * x,gdouble * y)
name|gimp_text_layout_untransform_point
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|)
block|{
name|cairo_matrix_t
name|matrix
decl_stmt|;
name|gdouble
name|_x
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|_y
init|=
literal|0.0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYOUT
argument_list|(
name|layout
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
condition|)
name|_x
operator|=
operator|*
name|x
expr_stmt|;
if|if
condition|(
name|y
condition|)
name|_y
operator|=
operator|*
name|y
expr_stmt|;
name|gimp_text_layout_get_transform
argument_list|(
name|layout
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
if|if
condition|(
name|cairo_matrix_invert
argument_list|(
operator|&
name|matrix
argument_list|)
operator|==
name|CAIRO_STATUS_SUCCESS
condition|)
block|{
name|cairo_matrix_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
operator|&
name|_x
argument_list|,
operator|&
name|_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
condition|)
operator|*
name|x
operator|=
name|_x
expr_stmt|;
if|if
condition|(
name|y
condition|)
operator|*
name|y
operator|=
name|_y
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_layout_untransform_distance (GimpTextLayout * layout,gdouble * x,gdouble * y)
name|gimp_text_layout_untransform_distance
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|)
block|{
name|cairo_matrix_t
name|matrix
decl_stmt|;
name|gdouble
name|_x
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|_y
init|=
literal|0.0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYOUT
argument_list|(
name|layout
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
condition|)
name|_x
operator|=
operator|*
name|x
expr_stmt|;
if|if
condition|(
name|y
condition|)
name|_y
operator|=
operator|*
name|y
expr_stmt|;
name|gimp_text_layout_get_transform
argument_list|(
name|layout
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
if|if
condition|(
name|cairo_matrix_invert
argument_list|(
operator|&
name|matrix
argument_list|)
operator|==
name|CAIRO_STATUS_SUCCESS
condition|)
block|{
name|cairo_matrix_transform_distance
argument_list|(
operator|&
name|matrix
argument_list|,
operator|&
name|_x
argument_list|,
operator|&
name|_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
condition|)
operator|*
name|x
operator|=
name|_x
expr_stmt|;
if|if
condition|(
name|y
condition|)
operator|*
name|y
operator|=
name|_y
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_layout_position (GimpTextLayout * layout)
name|gimp_text_layout_position
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|)
block|{
name|PangoRectangle
name|ink
decl_stmt|;
name|PangoRectangle
name|logical
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|layout
operator|->
name|extents
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|layout
operator|->
name|extents
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|layout
operator|->
name|extents
operator|.
name|width
operator|=
literal|0
expr_stmt|;
name|layout
operator|->
name|extents
operator|.
name|height
operator|=
literal|0
expr_stmt|;
name|pango_layout_get_pixel_extents
argument_list|(
name|layout
operator|->
name|layout
argument_list|,
operator|&
name|ink
argument_list|,
operator|&
name|logical
argument_list|)
expr_stmt|;
name|ink
operator|.
name|width
operator|=
name|ceil
argument_list|(
operator|(
name|gdouble
operator|)
name|ink
operator|.
name|width
operator|*
name|layout
operator|->
name|xres
operator|/
name|layout
operator|->
name|yres
argument_list|)
expr_stmt|;
name|logical
operator|.
name|width
operator|=
name|ceil
argument_list|(
operator|(
name|gdouble
operator|)
name|logical
operator|.
name|width
operator|*
name|layout
operator|->
name|xres
operator|/
name|layout
operator|->
name|yres
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|VERBOSE
name|g_print
argument_list|(
literal|"ink rect: %d x %d @ %d, %d\n"
argument_list|,
name|ink
operator|.
name|width
argument_list|,
name|ink
operator|.
name|height
argument_list|,
name|ink
operator|.
name|x
argument_list|,
name|ink
operator|.
name|y
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"logical rect: %d x %d @ %d, %d\n"
argument_list|,
name|logical
operator|.
name|width
argument_list|,
name|logical
operator|.
name|height
argument_list|,
name|logical
operator|.
name|x
argument_list|,
name|logical
operator|.
name|y
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|ink
operator|.
name|width
operator|<
literal|1
operator|||
name|ink
operator|.
name|height
operator|<
literal|1
condition|)
return|return;
name|x1
operator|=
name|MIN
argument_list|(
name|ink
operator|.
name|x
argument_list|,
name|logical
operator|.
name|x
argument_list|)
expr_stmt|;
name|y1
operator|=
name|MIN
argument_list|(
name|ink
operator|.
name|y
argument_list|,
name|logical
operator|.
name|y
argument_list|)
expr_stmt|;
name|x2
operator|=
name|MAX
argument_list|(
name|ink
operator|.
name|x
operator|+
name|ink
operator|.
name|width
argument_list|,
name|logical
operator|.
name|x
operator|+
name|logical
operator|.
name|width
argument_list|)
expr_stmt|;
name|y2
operator|=
name|MAX
argument_list|(
name|ink
operator|.
name|y
operator|+
name|ink
operator|.
name|height
argument_list|,
name|logical
operator|.
name|y
operator|+
name|logical
operator|.
name|height
argument_list|)
expr_stmt|;
name|layout
operator|->
name|extents
operator|.
name|x
operator|=
operator|-
name|x1
expr_stmt|;
name|layout
operator|->
name|extents
operator|.
name|y
operator|=
operator|-
name|y1
expr_stmt|;
name|layout
operator|->
name|extents
operator|.
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|layout
operator|->
name|extents
operator|.
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
if|if
condition|(
name|layout
operator|->
name|text
operator|->
name|border
operator|>
literal|0
condition|)
block|{
name|gint
name|border
init|=
name|layout
operator|->
name|text
operator|->
name|border
decl_stmt|;
name|layout
operator|->
name|extents
operator|.
name|x
operator|+=
name|border
expr_stmt|;
name|layout
operator|->
name|extents
operator|.
name|y
operator|+=
name|border
expr_stmt|;
name|layout
operator|->
name|extents
operator|.
name|width
operator|+=
literal|2
operator|*
name|border
expr_stmt|;
name|layout
operator|->
name|extents
operator|.
name|height
operator|+=
literal|2
operator|*
name|border
expr_stmt|;
block|}
ifdef|#
directive|ifdef
name|VERBOSE
name|g_print
argument_list|(
literal|"layout extents: %d x %d @ %d, %d\n"
argument_list|,
name|layout
operator|->
name|extents
operator|.
name|width
argument_list|,
name|layout
operator|->
name|extents
operator|.
name|height
argument_list|,
name|layout
operator|->
name|extents
operator|.
name|x
argument_list|,
name|layout
operator|->
name|extents
operator|.
name|y
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_function
specifier|static
name|cairo_font_options_t
modifier|*
DECL|function|gimp_text_get_font_options (GimpText * text)
name|gimp_text_get_font_options
parameter_list|(
name|GimpText
modifier|*
name|text
parameter_list|)
block|{
name|cairo_font_options_t
modifier|*
name|options
init|=
name|cairo_font_options_create
argument_list|()
decl_stmt|;
name|cairo_font_options_set_antialias
argument_list|(
name|options
argument_list|,
operator|(
name|text
operator|->
name|antialias
condition|?
name|CAIRO_ANTIALIAS_DEFAULT
else|:
name|CAIRO_ANTIALIAS_NONE
operator|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|text
operator|->
name|hint_style
condition|)
block|{
case|case
name|GIMP_TEXT_HINT_STYLE_NONE
case|:
name|cairo_font_options_set_hint_style
argument_list|(
name|options
argument_list|,
name|CAIRO_HINT_STYLE_NONE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TEXT_HINT_STYLE_SLIGHT
case|:
name|cairo_font_options_set_hint_style
argument_list|(
name|options
argument_list|,
name|CAIRO_HINT_STYLE_SLIGHT
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TEXT_HINT_STYLE_MEDIUM
case|:
name|cairo_font_options_set_hint_style
argument_list|(
name|options
argument_list|,
name|CAIRO_HINT_STYLE_MEDIUM
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TEXT_HINT_STYLE_FULL
case|:
name|cairo_font_options_set_hint_style
argument_list|(
name|options
argument_list|,
name|CAIRO_HINT_STYLE_FULL
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|options
return|;
block|}
end_function

begin_function
specifier|static
name|PangoContext
modifier|*
DECL|function|gimp_text_get_pango_context (GimpText * text,gdouble xres,gdouble yres)
name|gimp_text_get_pango_context
parameter_list|(
name|GimpText
modifier|*
name|text
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|yres
parameter_list|)
block|{
name|PangoContext
modifier|*
name|context
decl_stmt|;
name|PangoCairoFontMap
modifier|*
name|fontmap
decl_stmt|;
name|cairo_font_options_t
modifier|*
name|options
decl_stmt|;
name|fontmap
operator|=
name|PANGO_CAIRO_FONT_MAP
argument_list|(
name|pango_cairo_font_map_new_for_font_type
argument_list|(
name|CAIRO_FONT_TYPE_FT
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|fontmap
operator|==
name|NULL
condition|)
name|g_error
argument_list|(
literal|"You are using a Pango that has been built against a cairo that lacks the Freetype font backend"
argument_list|)
expr_stmt|;
name|pango_cairo_font_map_set_resolution
argument_list|(
name|fontmap
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|context
operator|=
name|pango_cairo_font_map_create_context
argument_list|(
name|fontmap
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|fontmap
argument_list|)
expr_stmt|;
name|options
operator|=
name|gimp_text_get_font_options
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|pango_cairo_context_set_font_options
argument_list|(
name|context
argument_list|,
name|options
argument_list|)
expr_stmt|;
name|cairo_font_options_destroy
argument_list|(
name|options
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
operator|->
name|language
condition|)
name|pango_context_set_language
argument_list|(
name|context
argument_list|,
name|pango_language_from_string
argument_list|(
name|text
operator|->
name|language
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|text
operator|->
name|base_dir
condition|)
block|{
case|case
name|GIMP_TEXT_DIRECTION_LTR
case|:
name|pango_context_set_base_dir
argument_list|(
name|context
argument_list|,
name|PANGO_DIRECTION_LTR
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TEXT_DIRECTION_RTL
case|:
name|pango_context_set_base_dir
argument_list|(
name|context
argument_list|,
name|PANGO_DIRECTION_RTL
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|context
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_text_layout_pixel_size (gdouble value,GimpUnit unit,gdouble res)
name|gimp_text_layout_pixel_size
parameter_list|(
name|gdouble
name|value
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|res
parameter_list|)
block|{
name|gdouble
name|factor
decl_stmt|;
switch|switch
condition|(
name|unit
condition|)
block|{
case|case
name|GIMP_UNIT_PIXEL
case|:
return|return
name|PANGO_SCALE
operator|*
name|value
return|;
default|default:
name|factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|unit
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|factor
operator|>
literal|0.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|PANGO_SCALE
operator|*
name|value
operator|*
name|res
operator|/
name|factor
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_text_layout_point_size (gdouble value,GimpUnit unit,gdouble res)
name|gimp_text_layout_point_size
parameter_list|(
name|gdouble
name|value
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|res
parameter_list|)
block|{
name|gdouble
name|factor
decl_stmt|;
switch|switch
condition|(
name|unit
condition|)
block|{
case|case
name|GIMP_UNIT_POINT
case|:
return|return
name|PANGO_SCALE
operator|*
name|value
return|;
case|case
name|GIMP_UNIT_PIXEL
case|:
name|g_return_val_if_fail
argument_list|(
name|res
operator|>
literal|0.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
operator|(
name|PANGO_SCALE
operator|*
name|value
operator|*
name|gimp_unit_get_factor
argument_list|(
name|GIMP_UNIT_POINT
argument_list|)
operator|/
name|res
operator|)
return|;
default|default:
name|factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|unit
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|factor
operator|>
literal|0.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
operator|(
name|PANGO_SCALE
operator|*
name|value
operator|*
name|gimp_unit_get_factor
argument_list|(
name|GIMP_UNIT_POINT
argument_list|)
operator|/
name|factor
operator|)
return|;
block|}
block|}
end_function

end_unit

