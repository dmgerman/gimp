begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<pango/pangoft2.h>
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
file|"core/gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"gimptext.h"
end_include

begin_include
include|#
directive|include
file|"gimptext-private.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayout.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_text_layout_class_init
parameter_list|(
name|GimpTextLayoutClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_layout_init
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|)
function_decl|;
end_function_decl

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
name|Gimp
modifier|*
name|gimp
parameter_list|,
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
name|Gimp
modifier|*
name|gimp
parameter_list|,
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_text_layout_get_type (void)
name|gimp_text_layout_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|layout_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|layout_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|layout_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpTextLayoutClass
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
name|gimp_text_layout_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpTextLayout
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_text_layout_init
block|,       }
decl_stmt|;
name|layout_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_OBJECT
argument_list|,
literal|"GimpTextLayout"
argument_list|,
operator|&
name|layout_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|layout_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_layout_class_init (GimpTextLayoutClass * klass)
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
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
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
decl_stmt|;
name|layout
operator|=
name|GIMP_TEXT_LAYOUT
argument_list|(
name|object
argument_list|)
expr_stmt|;
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
if|if
condition|(
operator|!
name|font_desc
condition|)
return|return
name|NULL
return|;
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
name|image
operator|->
name|gimp
argument_list|,
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
comment|/* FIXME: This doesn't work since the implementation is missing          at the Pango level.        */
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
name|image
operator|->
name|gimp
argument_list|,
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
name|image
operator|->
name|gimp
argument_list|,
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
name|image
operator|->
name|gimp
argument_list|,
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
name|height
operator|=
name|PANGO_PIXELS
argument_list|(
name|gimp_text_layout_pixel_size
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
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
literal|0
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
literal|0
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
name|void
DECL|function|gimp_text_ft2_subst_func (FcPattern * pattern,gpointer data)
name|gimp_text_ft2_subst_func
parameter_list|(
name|FcPattern
modifier|*
name|pattern
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpText
modifier|*
name|text
init|=
name|GIMP_TEXT
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|FcPatternAddBool
argument_list|(
name|pattern
argument_list|,
name|FC_HINTING
argument_list|,
name|text
operator|->
name|hinting
argument_list|)
expr_stmt|;
name|FcPatternAddBool
argument_list|(
name|pattern
argument_list|,
name|FC_AUTOHINT
argument_list|,
name|text
operator|->
name|autohint
argument_list|)
expr_stmt|;
name|FcPatternAddBool
argument_list|(
name|pattern
argument_list|,
name|FC_ANTIALIAS
argument_list|,
name|text
operator|->
name|antialias
argument_list|)
expr_stmt|;
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
name|PangoFT2FontMap
modifier|*
name|fontmap
decl_stmt|;
name|fontmap
operator|=
name|PANGO_FT2_FONT_MAP
argument_list|(
name|pango_ft2_font_map_new
argument_list|()
argument_list|)
expr_stmt|;
name|pango_ft2_font_map_set_resolution
argument_list|(
name|fontmap
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|pango_ft2_font_map_set_default_substitute
argument_list|(
name|fontmap
argument_list|,
name|gimp_text_ft2_subst_func
argument_list|,
name|g_object_ref
argument_list|(
name|text
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
name|context
operator|=
name|pango_ft2_font_map_create_context
argument_list|(
name|fontmap
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|fontmap
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
DECL|function|gimp_text_layout_pixel_size (Gimp * gimp,gdouble value,GimpUnit unit,gdouble res)
name|gimp_text_layout_pixel_size
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
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
name|_gimp_unit_get_factor
argument_list|(
name|gimp
argument_list|,
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
DECL|function|gimp_text_layout_point_size (Gimp * gimp,gdouble value,GimpUnit unit,gdouble res)
name|gimp_text_layout_point_size
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
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
name|_gimp_unit_get_factor
argument_list|(
name|gimp
argument_list|,
name|GIMP_UNIT_POINT
argument_list|)
operator|/
name|res
operator|)
return|;
default|default:
name|factor
operator|=
name|_gimp_unit_get_factor
argument_list|(
name|gimp
argument_list|,
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
name|_gimp_unit_get_factor
argument_list|(
name|gimp
argument_list|,
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

