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
file|<glib-object.h>
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
file|"base/base-types.h"
end_include

begin_include
include|#
directive|include
file|"base/brush-scale.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/scale-funcs.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush-load.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2992bd800103
block|{
DECL|enumerator|SPACING_CHANGED
name|SPACING_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2992bd800203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SPACING
name|PROP_SPACING
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_brush_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_brush_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_brush_get_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_brush_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
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
name|gchar
modifier|*
name|gimp_brush_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_brush_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpBrush
modifier|*
name|gimp_brush_real_select_brush
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
name|GimpCoords
modifier|*
name|cur_coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_brush_real_want_null_motion
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
name|GimpCoords
modifier|*
name|cur_coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_brush_scale_buf
parameter_list|(
name|TempBuf
modifier|*
name|brush_buf
parameter_list|,
name|gint
name|dest_width
parameter_list|,
name|gint
name|dest_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_real_scale_size
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gint
modifier|*
name|scaled_width
parameter_list|,
name|gint
modifier|*
name|scaled_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_brush_real_scale_mask
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_brush_real_scale_pixmap
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpBrush
argument_list|,
argument|gimp_brush
argument_list|,
argument|GIMP_TYPE_DATA
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_brush_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|brush_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_brush_class_init (GimpBrushClass * klass)
name|gimp_brush_class_init
parameter_list|(
name|GimpBrushClass
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
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
init|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpDataClass
modifier|*
name|data_class
init|=
name|GIMP_DATA_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|brush_signals
index|[
name|SPACING_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"spacing-changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpBrushClass
argument_list|,
name|spacing_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_brush_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_brush_set_property
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_brush_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_brush_get_memsize
expr_stmt|;
name|viewable_class
operator|->
name|default_stock_id
operator|=
literal|"gimp-tool-paintbrush"
expr_stmt|;
name|viewable_class
operator|->
name|get_size
operator|=
name|gimp_brush_get_size
expr_stmt|;
name|viewable_class
operator|->
name|get_new_preview
operator|=
name|gimp_brush_get_new_preview
expr_stmt|;
name|viewable_class
operator|->
name|get_description
operator|=
name|gimp_brush_get_description
expr_stmt|;
name|data_class
operator|->
name|get_extension
operator|=
name|gimp_brush_get_extension
expr_stmt|;
name|klass
operator|->
name|select_brush
operator|=
name|gimp_brush_real_select_brush
expr_stmt|;
name|klass
operator|->
name|want_null_motion
operator|=
name|gimp_brush_real_want_null_motion
expr_stmt|;
name|klass
operator|->
name|scale_size
operator|=
name|gimp_brush_real_scale_size
expr_stmt|;
name|klass
operator|->
name|scale_mask
operator|=
name|gimp_brush_real_scale_mask
expr_stmt|;
name|klass
operator|->
name|scale_pixmap
operator|=
name|gimp_brush_real_scale_pixmap
expr_stmt|;
name|klass
operator|->
name|spacing_changed
operator|=
name|NULL
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SPACING
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"spacing"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|1.0
argument_list|,
literal|5000.0
argument_list|,
literal|20.0
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_init (GimpBrush * brush)
name|gimp_brush_init
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|brush
operator|->
name|mask
operator|=
name|NULL
expr_stmt|;
name|brush
operator|->
name|pixmap
operator|=
name|NULL
expr_stmt|;
name|brush
operator|->
name|spacing
operator|=
literal|20
expr_stmt|;
name|brush
operator|->
name|x_axis
operator|.
name|x
operator|=
literal|15.0
expr_stmt|;
name|brush
operator|->
name|x_axis
operator|.
name|y
operator|=
literal|0.0
expr_stmt|;
name|brush
operator|->
name|y_axis
operator|.
name|x
operator|=
literal|0.0
expr_stmt|;
name|brush
operator|->
name|y_axis
operator|.
name|y
operator|=
literal|15.0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_brush_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
init|=
name|GIMP_BRUSH
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_SPACING
case|:
name|gimp_brush_set_spacing
argument_list|(
name|brush
argument_list|,
name|g_value_get_double
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_brush_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
init|=
name|GIMP_BRUSH
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_SPACING
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|brush
operator|->
name|spacing
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_finalize (GObject * object)
name|gimp_brush_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
init|=
name|GIMP_BRUSH
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|brush
operator|->
name|mask
condition|)
block|{
name|temp_buf_free
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
name|brush
operator|->
name|mask
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|brush
operator|->
name|pixmap
condition|)
block|{
name|temp_buf_free
argument_list|(
name|brush
operator|->
name|pixmap
argument_list|)
expr_stmt|;
name|brush
operator|->
name|pixmap
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
name|gint64
DECL|function|gimp_brush_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_brush_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
init|=
name|GIMP_BRUSH
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|brush
operator|->
name|mask
condition|)
name|memsize
operator|+=
name|temp_buf_get_memsize
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|pixmap
condition|)
name|memsize
operator|+=
name|temp_buf_get_memsize
argument_list|(
name|brush
operator|->
name|pixmap
argument_list|)
expr_stmt|;
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
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_brush_get_size (GimpViewable * viewable,gint * width,gint * height)
name|gimp_brush_get_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
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
name|GimpBrush
modifier|*
name|brush
init|=
name|GIMP_BRUSH
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
operator|*
name|width
operator|=
name|brush
operator|->
name|mask
operator|->
name|width
expr_stmt|;
operator|*
name|height
operator|=
name|brush
operator|->
name|mask
operator|->
name|height
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_brush_get_new_preview (GimpViewable * viewable,GimpContext * context,gint width,gint height)
name|gimp_brush_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
init|=
name|GIMP_BRUSH
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|gint
name|brush_width
decl_stmt|;
name|gint
name|brush_height
decl_stmt|;
name|TempBuf
modifier|*
name|mask_buf
init|=
name|NULL
decl_stmt|;
name|TempBuf
modifier|*
name|pixmap_buf
init|=
name|NULL
decl_stmt|;
name|TempBuf
modifier|*
name|return_buf
init|=
name|NULL
decl_stmt|;
name|guchar
name|transp
index|[
literal|4
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|guchar
modifier|*
name|mask
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gboolean
name|scale
init|=
name|FALSE
decl_stmt|;
name|mask_buf
operator|=
name|gimp_brush_get_mask
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|pixmap_buf
operator|=
name|gimp_brush_get_pixmap
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|brush_width
operator|=
name|mask_buf
operator|->
name|width
expr_stmt|;
name|brush_height
operator|=
name|mask_buf
operator|->
name|height
expr_stmt|;
if|if
condition|(
name|brush_width
operator|>
name|width
operator|||
name|brush_height
operator|>
name|height
condition|)
block|{
name|gdouble
name|ratio_x
init|=
operator|(
name|gdouble
operator|)
name|brush_width
operator|/
name|width
decl_stmt|;
name|gdouble
name|ratio_y
init|=
operator|(
name|gdouble
operator|)
name|brush_height
operator|/
name|height
decl_stmt|;
name|brush_width
operator|=
operator|(
name|gdouble
operator|)
name|brush_width
operator|/
name|MAX
argument_list|(
name|ratio_x
argument_list|,
name|ratio_y
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|brush_height
operator|=
operator|(
name|gdouble
operator|)
name|brush_height
operator|/
name|MAX
argument_list|(
name|ratio_x
argument_list|,
name|ratio_y
argument_list|)
operator|+
literal|0.5
expr_stmt|;
if|if
condition|(
name|brush_width
operator|<=
literal|0
condition|)
name|brush_width
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|brush_height
operator|<=
literal|0
condition|)
name|brush_height
operator|=
literal|1
expr_stmt|;
name|mask_buf
operator|=
name|brush_scale_mask
argument_list|(
name|mask_buf
argument_list|,
name|brush_width
argument_list|,
name|brush_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixmap_buf
condition|)
block|{
comment|/* TODO: the scale function should scale the pixmap and the            *  mask in one run            */
name|pixmap_buf
operator|=
name|brush_scale_pixmap
argument_list|(
name|pixmap_buf
argument_list|,
name|brush_width
argument_list|,
name|brush_height
argument_list|)
expr_stmt|;
block|}
name|scale
operator|=
name|TRUE
expr_stmt|;
block|}
name|return_buf
operator|=
name|temp_buf_new
argument_list|(
name|brush_width
argument_list|,
name|brush_height
argument_list|,
literal|4
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|transp
argument_list|)
expr_stmt|;
name|mask
operator|=
name|temp_buf_data
argument_list|(
name|mask_buf
argument_list|)
expr_stmt|;
name|buf
operator|=
name|temp_buf_data
argument_list|(
name|return_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixmap_buf
condition|)
block|{
name|guchar
modifier|*
name|pixmap
init|=
name|temp_buf_data
argument_list|(
name|pixmap_buf
argument_list|)
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|brush_height
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
name|brush_width
condition|;
name|x
operator|++
control|)
block|{
operator|*
name|buf
operator|++
operator|=
operator|*
name|pixmap
operator|++
expr_stmt|;
operator|*
name|buf
operator|++
operator|=
operator|*
name|pixmap
operator|++
expr_stmt|;
operator|*
name|buf
operator|++
operator|=
operator|*
name|pixmap
operator|++
expr_stmt|;
operator|*
name|buf
operator|++
operator|=
operator|*
name|mask
operator|++
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|brush_height
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
name|brush_width
condition|;
name|x
operator|++
control|)
block|{
operator|*
name|buf
operator|++
operator|=
literal|0
expr_stmt|;
operator|*
name|buf
operator|++
operator|=
literal|0
expr_stmt|;
operator|*
name|buf
operator|++
operator|=
literal|0
expr_stmt|;
operator|*
name|buf
operator|++
operator|=
operator|*
name|mask
operator|++
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|scale
condition|)
block|{
name|temp_buf_free
argument_list|(
name|mask_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixmap_buf
condition|)
name|temp_buf_free
argument_list|(
name|pixmap_buf
argument_list|)
expr_stmt|;
block|}
return|return
name|return_buf
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_brush_get_description (GimpViewable * viewable,gchar ** tooltip)
name|gimp_brush_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
init|=
name|GIMP_BRUSH
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
return|return
name|g_strdup_printf
argument_list|(
literal|"%s (%d Ã %d)"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|brush
argument_list|)
operator|->
name|name
argument_list|,
name|brush
operator|->
name|mask
operator|->
name|width
argument_list|,
name|brush
operator|->
name|mask
operator|->
name|height
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_brush_get_extension (GimpData * data)
name|gimp_brush_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
return|return
name|GIMP_BRUSH_FILE_EXTENSION
return|;
block|}
end_function

begin_function
specifier|static
name|GimpBrush
modifier|*
DECL|function|gimp_brush_real_select_brush (GimpBrush * brush,GimpCoords * last_coords,GimpCoords * cur_coords)
name|gimp_brush_real_select_brush
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
name|GimpCoords
modifier|*
name|cur_coords
parameter_list|)
block|{
return|return
name|brush
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_brush_real_want_null_motion (GimpBrush * brush,GimpCoords * last_coords,GimpCoords * cur_coords)
name|gimp_brush_real_want_null_motion
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
name|GimpCoords
modifier|*
name|cur_coords
parameter_list|)
block|{
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_brush_scale_buf (TempBuf * brush_buf,gint dest_width,gint dest_height)
name|gimp_brush_scale_buf
parameter_list|(
name|TempBuf
modifier|*
name|brush_buf
parameter_list|,
name|gint
name|dest_width
parameter_list|,
name|gint
name|dest_height
parameter_list|)
block|{
name|PixelRegion
name|source_region
decl_stmt|;
name|PixelRegion
name|dest_region
decl_stmt|;
name|TempBuf
modifier|*
name|dest_brush_buf
decl_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|source_region
argument_list|,
name|brush_buf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|brush_buf
operator|->
name|width
argument_list|,
name|brush_buf
operator|->
name|height
argument_list|)
expr_stmt|;
name|dest_brush_buf
operator|=
name|temp_buf_new
argument_list|(
name|dest_width
argument_list|,
name|dest_height
argument_list|,
name|brush_buf
operator|->
name|bytes
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|dest_region
argument_list|,
name|dest_brush_buf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|dest_width
argument_list|,
name|dest_height
argument_list|)
expr_stmt|;
name|scale_region
argument_list|(
operator|&
name|source_region
argument_list|,
operator|&
name|dest_region
argument_list|,
name|GIMP_INTERPOLATION_LINEAR
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dest_brush_buf
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_real_scale_size (GimpBrush * brush,gdouble scale,gint * width,gint * height)
name|gimp_brush_real_scale_size
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
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
operator|*
name|width
operator|=
call|(
name|gint
call|)
argument_list|(
name|brush
operator|->
name|mask
operator|->
name|width
operator|*
name|scale
operator|+
literal|0.5
argument_list|)
expr_stmt|;
operator|*
name|height
operator|=
call|(
name|gint
call|)
argument_list|(
name|brush
operator|->
name|mask
operator|->
name|height
operator|*
name|scale
operator|+
literal|0.5
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_brush_real_scale_mask (GimpBrush * brush,gdouble scale)
name|gimp_brush_real_scale_mask
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|)
block|{
name|gint
name|dest_width
decl_stmt|;
name|gint
name|dest_height
decl_stmt|;
name|gimp_brush_scale_size
argument_list|(
name|brush
argument_list|,
name|scale
argument_list|,
operator|&
name|dest_width
argument_list|,
operator|&
name|dest_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|dest_width
operator|<=
literal|0
operator|||
name|dest_height
operator|<=
literal|0
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|scale
operator|<=
literal|1.0
condition|)
block|{
comment|/*  Downscaling with brush_scale_mask is much faster than with        *  gimp_brush_scale_buf.        */
return|return
name|brush_scale_mask
argument_list|(
name|brush
operator|->
name|mask
argument_list|,
name|dest_width
argument_list|,
name|dest_height
argument_list|)
return|;
block|}
return|return
name|gimp_brush_scale_buf
argument_list|(
name|brush
operator|->
name|mask
argument_list|,
name|dest_width
argument_list|,
name|dest_height
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_brush_real_scale_pixmap (GimpBrush * brush,gdouble scale)
name|gimp_brush_real_scale_pixmap
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|)
block|{
name|gint
name|dest_width
decl_stmt|;
name|gint
name|dest_height
decl_stmt|;
name|gimp_brush_scale_size
argument_list|(
name|brush
argument_list|,
name|scale
argument_list|,
operator|&
name|dest_width
argument_list|,
operator|&
name|dest_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|dest_width
operator|<=
literal|0
operator|||
name|dest_height
operator|<=
literal|0
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|scale
operator|<=
literal|1.0
condition|)
block|{
comment|/*  Downscaling with brush_scale_pixmap is much faster than with        *  gimp_brush_scale_buf.        */
return|return
name|brush_scale_pixmap
argument_list|(
name|brush
operator|->
name|pixmap
argument_list|,
name|dest_width
argument_list|,
name|dest_height
argument_list|)
return|;
block|}
return|return
name|gimp_brush_scale_buf
argument_list|(
name|brush
operator|->
name|pixmap
argument_list|,
name|dest_width
argument_list|,
name|dest_height
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpData
modifier|*
DECL|function|gimp_brush_new (const gchar * name)
name|gimp_brush_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_brush_generated_new
argument_list|(
name|name
argument_list|,
name|GIMP_BRUSH_GENERATED_CIRCLE
argument_list|,
literal|5.0
argument_list|,
literal|2
argument_list|,
literal|0.5
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_brush_get_standard (void)
name|gimp_brush_get_standard
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpData
modifier|*
name|standard_brush
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|standard_brush
condition|)
block|{
name|standard_brush
operator|=
name|gimp_brush_new
argument_list|(
literal|"Standard"
argument_list|)
expr_stmt|;
name|standard_brush
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
name|gimp_data_make_internal
argument_list|(
name|standard_brush
argument_list|)
expr_stmt|;
comment|/*  set ref_count to 2 --> never swap the standard brush  */
name|g_object_ref
argument_list|(
name|standard_brush
argument_list|)
expr_stmt|;
block|}
return|return
name|standard_brush
return|;
block|}
end_function

begin_function
name|GimpBrush
modifier|*
DECL|function|gimp_brush_select_brush (GimpBrush * brush,GimpCoords * last_coords,GimpCoords * cur_coords)
name|gimp_brush_select_brush
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
name|GimpCoords
modifier|*
name|cur_coords
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|last_coords
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|cur_coords
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_BRUSH_GET_CLASS
argument_list|(
name|brush
argument_list|)
operator|->
name|select_brush
argument_list|(
name|brush
argument_list|,
name|last_coords
argument_list|,
name|cur_coords
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_brush_want_null_motion (GimpBrush * brush,GimpCoords * last_coords,GimpCoords * cur_coords)
name|gimp_brush_want_null_motion
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
name|GimpCoords
modifier|*
name|cur_coords
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|last_coords
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|cur_coords
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GIMP_BRUSH_GET_CLASS
argument_list|(
name|brush
argument_list|)
operator|->
name|want_null_motion
argument_list|(
name|brush
argument_list|,
name|last_coords
argument_list|,
name|cur_coords
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_scale_size (GimpBrush * brush,gdouble scale,gint * width,gint * height)
name|gimp_brush_scale_size
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|scale
operator|>
literal|0.0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|width
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|height
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|scale
operator|==
literal|1.0
condition|)
block|{
operator|*
name|width
operator|=
name|brush
operator|->
name|mask
operator|->
name|width
expr_stmt|;
operator|*
name|height
operator|=
name|brush
operator|->
name|mask
operator|->
name|height
expr_stmt|;
return|return;
block|}
return|return
name|GIMP_BRUSH_GET_CLASS
argument_list|(
name|brush
argument_list|)
operator|->
name|scale_size
argument_list|(
name|brush
argument_list|,
name|scale
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_brush_scale_mask (GimpBrush * brush,gdouble scale)
name|gimp_brush_scale_mask
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|scale
operator|>
literal|0.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_BRUSH_GET_CLASS
argument_list|(
name|brush
argument_list|)
operator|->
name|scale_mask
argument_list|(
name|brush
argument_list|,
name|scale
argument_list|)
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_brush_scale_pixmap (GimpBrush * brush,gdouble scale)
name|gimp_brush_scale_pixmap
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|brush
operator|->
name|pixmap
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|scale
operator|>
literal|0.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_BRUSH_GET_CLASS
argument_list|(
name|brush
argument_list|)
operator|->
name|scale_pixmap
argument_list|(
name|brush
argument_list|,
name|scale
argument_list|)
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_brush_get_mask (const GimpBrush * brush)
name|gimp_brush_get_mask
parameter_list|(
specifier|const
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|brush
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|mask
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_brush_get_pixmap (const GimpBrush * brush)
name|gimp_brush_get_pixmap
parameter_list|(
specifier|const
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|brush
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|pixmap
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_brush_get_spacing (const GimpBrush * brush)
name|gimp_brush_get_spacing
parameter_list|(
specifier|const
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|spacing
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_set_spacing (GimpBrush * brush,gint spacing)
name|gimp_brush_set_spacing
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gint
name|spacing
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|spacing
operator|!=
name|spacing
condition|)
block|{
name|brush
operator|->
name|spacing
operator|=
name|spacing
expr_stmt|;
name|gimp_brush_spacing_changed
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|,
literal|"spacing"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_spacing_changed (GimpBrush * brush)
name|gimp_brush_spacing_changed
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|brush
argument_list|,
name|brush_signals
index|[
name|SPACING_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

