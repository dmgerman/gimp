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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"text-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
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

begin_struct
DECL|struct|_GimpTextLayoutClass
struct|struct
name|_GimpTextLayoutClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

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
name|gimp_image_get_pango_context
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_text_context_quark
specifier|static
name|GQuark
name|gimp_text_context_quark
init|=
literal|0
decl_stmt|;
end_decl_stmt

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
switch|switch
condition|(
name|text
operator|->
name|font_size_unit
condition|)
block|{
case|case
name|GIMP_UNIT_PIXEL
case|:
name|size
operator|=
name|PANGO_SCALE
operator|*
name|text
operator|->
name|font_size
expr_stmt|;
break|break;
default|default:
block|{
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|gdouble
name|factor
decl_stmt|;
name|factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|text
operator|->
name|font_size_unit
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|factor
operator|>
literal|0.0
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
operator|(
name|gdouble
operator|)
name|PANGO_SCALE
operator|*
name|text
operator|->
name|font_size
operator|*
name|yres
operator|/
name|factor
expr_stmt|;
block|}
break|break;
block|}
if|if
condition|(
name|size
operator|>
literal|1
condition|)
name|pango_font_description_set_size
argument_list|(
name|font_desc
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_image_get_pango_context
argument_list|(
name|image
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
name|pango_layout_set_alignment
argument_list|(
name|layout
operator|->
name|layout
argument_list|,
name|text
operator|->
name|alignment
argument_list|)
expr_stmt|;
name|gimp_text_layout_position
argument_list|(
name|layout
argument_list|)
expr_stmt|;
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
name|TileManager
modifier|*
DECL|function|gimp_text_layout_render (GimpTextLayout * layout)
name|gimp_text_layout_render
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|)
block|{
name|TileManager
modifier|*
name|mask
decl_stmt|;
name|FT_Bitmap
name|bitmap
decl_stmt|;
name|PixelRegion
name|maskPR
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
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
name|gimp_text_layout_get_size
argument_list|(
name|layout
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|gimp_text_layout_get_offsets
argument_list|(
name|layout
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|bitmap
operator|.
name|width
operator|=
name|width
expr_stmt|;
name|bitmap
operator|.
name|rows
operator|=
name|height
expr_stmt|;
name|bitmap
operator|.
name|pitch
operator|=
name|width
expr_stmt|;
if|if
condition|(
name|bitmap
operator|.
name|pitch
operator|&
literal|3
condition|)
name|bitmap
operator|.
name|pitch
operator|+=
literal|4
operator|-
operator|(
name|bitmap
operator|.
name|pitch
operator|&
literal|3
operator|)
expr_stmt|;
name|bitmap
operator|.
name|buffer
operator|=
name|g_malloc0
argument_list|(
name|bitmap
operator|.
name|rows
operator|*
name|bitmap
operator|.
name|pitch
argument_list|)
expr_stmt|;
name|pango_ft2_render_layout
argument_list|(
operator|&
name|bitmap
argument_list|,
name|layout
operator|->
name|layout
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|mask
operator|=
name|tile_manager_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|maskPR
argument_list|,
name|mask
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|height
condition|;
name|i
operator|++
control|)
name|pixel_region_set_row
argument_list|(
operator|&
name|maskPR
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|width
argument_list|,
name|bitmap
operator|.
name|buffer
operator|+
name|i
operator|*
name|bitmap
operator|.
name|pitch
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bitmap
operator|.
name|buffer
argument_list|)
expr_stmt|;
return|return
name|mask
return|;
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
name|GimpText
modifier|*
name|text
decl_stmt|;
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
name|gboolean
name|fixed
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
name|text
operator|=
name|layout
operator|->
name|text
expr_stmt|;
name|fixed
operator|=
operator|(
name|text
operator|->
name|fixed_width
operator|>
literal|1
operator|&&
name|text
operator|->
name|fixed_height
operator|>
literal|1
operator|)
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
if|if
condition|(
operator|!
name|fixed
condition|)
block|{
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
comment|/* sanity checks for insane font sizes */
if|if
condition|(
name|ink
operator|.
name|width
operator|>
literal|8192
condition|)
name|ink
operator|.
name|width
operator|=
literal|8192
expr_stmt|;
if|if
condition|(
name|ink
operator|.
name|height
operator|>
literal|8192
condition|)
name|ink
operator|.
name|height
operator|=
literal|8192
expr_stmt|;
block|}
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
name|fixed
condition|?
name|text
operator|->
name|fixed_width
else|:
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
name|fixed
condition|?
name|text
operator|->
name|fixed_height
else|:
name|y2
operator|-
name|y1
expr_stmt|;
comment|/* border should only be used by the compatibility API;      we assume that gravity is CENTER    */
if|if
condition|(
name|text
operator|->
name|border
condition|)
block|{
name|fixed
operator|=
name|TRUE
expr_stmt|;
name|layout
operator|->
name|extents
operator|.
name|width
operator|+=
literal|2
operator|*
name|text
operator|->
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
name|text
operator|->
name|border
expr_stmt|;
block|}
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
name|y
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|fixed
condition|)
return|return;
switch|switch
condition|(
name|text
operator|->
name|gravity
condition|)
block|{
case|case
name|GIMP_GRAVITY_NORTH_WEST
case|:
case|case
name|GIMP_GRAVITY_SOUTH_WEST
case|:
case|case
name|GIMP_GRAVITY_WEST
case|:
break|break;
case|case
name|GIMP_GRAVITY_NONE
case|:
case|case
name|GIMP_GRAVITY_CENTER
case|:
case|case
name|GIMP_GRAVITY_NORTH
case|:
case|case
name|GIMP_GRAVITY_SOUTH
case|:
name|layout
operator|->
name|extents
operator|.
name|x
operator|+=
operator|(
name|layout
operator|->
name|extents
operator|.
name|width
operator|-
name|logical
operator|.
name|width
operator|)
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_GRAVITY_NORTH_EAST
case|:
case|case
name|GIMP_GRAVITY_SOUTH_EAST
case|:
case|case
name|GIMP_GRAVITY_EAST
case|:
name|layout
operator|->
name|extents
operator|.
name|x
operator|+=
operator|(
name|layout
operator|->
name|extents
operator|.
name|width
operator|-
name|logical
operator|.
name|width
operator|)
expr_stmt|;
break|break;
block|}
switch|switch
condition|(
name|text
operator|->
name|gravity
condition|)
block|{
case|case
name|GIMP_GRAVITY_NORTH
case|:
case|case
name|GIMP_GRAVITY_NORTH_WEST
case|:
case|case
name|GIMP_GRAVITY_NORTH_EAST
case|:
break|break;
case|case
name|GIMP_GRAVITY_NONE
case|:
case|case
name|GIMP_GRAVITY_CENTER
case|:
case|case
name|GIMP_GRAVITY_WEST
case|:
case|case
name|GIMP_GRAVITY_EAST
case|:
name|layout
operator|->
name|extents
operator|.
name|y
operator|+=
operator|(
name|layout
operator|->
name|extents
operator|.
name|height
operator|-
name|logical
operator|.
name|height
operator|)
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_GRAVITY_SOUTH
case|:
case|case
name|GIMP_GRAVITY_SOUTH_WEST
case|:
case|case
name|GIMP_GRAVITY_SOUTH_EAST
case|:
name|layout
operator|->
name|extents
operator|.
name|y
operator|+=
operator|(
name|layout
operator|->
name|extents
operator|.
name|height
operator|-
name|logical
operator|.
name|height
operator|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|detach_pango_context (GObject * image)
name|detach_pango_context
parameter_list|(
name|GObject
modifier|*
name|image
parameter_list|)
block|{
name|g_object_set_qdata
argument_list|(
name|image
argument_list|,
name|gimp_text_context_quark
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|PangoContext
modifier|*
DECL|function|gimp_image_get_pango_context (GimpImage * image)
name|gimp_image_get_pango_context
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|PangoContext
modifier|*
name|context
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_text_context_quark
condition|)
name|gimp_text_context_quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"pango-context"
argument_list|)
expr_stmt|;
name|context
operator|=
operator|(
name|PangoContext
operator|*
operator|)
name|g_object_get_qdata
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_text_context_quark
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|context
condition|)
block|{
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
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
name|context
operator|=
name|pango_ft2_get_context
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|image
argument_list|,
literal|"resolution_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|detach_pango_context
argument_list|)
argument_list|,
name|context
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_set_qdata_full
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_text_context_quark
argument_list|,
name|context
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
block|}
return|return
name|g_object_ref
argument_list|(
name|context
argument_list|)
return|;
block|}
end_function

end_unit

