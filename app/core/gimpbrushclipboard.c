begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbrushclipboard.c  * Copyright (C) 2006 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpbuffer.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushclipboard.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29e8ff930103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_GIMP
name|PROP_GIMP
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_brush_clipboard_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_clipboard_set_property
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
name|gimp_brush_clipboard_get_property
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

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static GimpData * gimp_brush_clipboard_duplicate    (GimpData     *data);
endif|#
directive|endif
end_endif

begin_function_decl
specifier|static
name|void
name|gimp_brush_clipboard_buffer_changed
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpBrushClipboard,gimp_brush_clipboard,GIMP_TYPE_BRUSH)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpBrushClipboard
argument_list|,
argument|gimp_brush_clipboard
argument_list|,
argument|GIMP_TYPE_BRUSH
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_brush_clipboard_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_brush_clipboard_class_init
parameter_list|(
name|GimpBrushClipboardClass
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
if|#
directive|if
literal|0
block|GimpDataClass *data_class   = GIMP_DATA_CLASS (klass);
endif|#
directive|endif
name|object_class
operator|->
name|constructor
operator|=
name|gimp_brush_clipboard_constructor
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_brush_clipboard_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_brush_clipboard_get_property
expr_stmt|;
if|#
directive|if
literal|0
block|data_class->duplicate      = gimp_brush_clipboard_duplicate;
endif|#
directive|endif
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GIMP
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"gimp"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GIMP
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_clipboard_init (GimpBrushClipboard * brush)
name|gimp_brush_clipboard_init
parameter_list|(
name|GimpBrushClipboard
modifier|*
name|brush
parameter_list|)
block|{
name|brush
operator|->
name|gimp
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_brush_clipboard_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_brush_clipboard_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpBrushClipboard
modifier|*
name|brush
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|brush
operator|=
name|GIMP_BRUSH_CLIPBOARD
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|brush
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|brush
operator|->
name|gimp
argument_list|,
literal|"buffer-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_clipboard_buffer_changed
argument_list|)
argument_list|,
name|brush
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_brush_clipboard_buffer_changed
argument_list|(
name|brush
operator|->
name|gimp
argument_list|,
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_clipboard_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_brush_clipboard_set_property
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
name|GimpBrushClipboard
modifier|*
name|brush
init|=
name|GIMP_BRUSH_CLIPBOARD
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
name|PROP_GIMP
case|:
name|brush
operator|->
name|gimp
operator|=
name|GIMP
argument_list|(
name|g_value_get_object
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
DECL|function|gimp_brush_clipboard_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_brush_clipboard_get_property
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
name|GimpBrushClipboard
modifier|*
name|brush
init|=
name|GIMP_BRUSH_CLIPBOARD
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
name|PROP_GIMP
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|brush
operator|->
name|gimp
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

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static GimpData * gimp_brush_clipboard_duplicate (GimpData *data) {   GimpBrushClipboard *brush = GIMP_BRUSH_CLIPBOARD (data);    return gimp_brush_clipboard_new (brush->gimp); }
endif|#
directive|endif
end_endif

begin_function
name|GimpData
modifier|*
DECL|function|gimp_brush_clipboard_new (Gimp * gimp)
name|gimp_brush_clipboard_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpBrushClipboard
modifier|*
name|brush
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|brush
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_BRUSH_CLIPBOARD
argument_list|,
literal|"name"
argument_list|,
name|_
argument_list|(
literal|"Clipboard"
argument_list|)
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_brush_clipboard_buffer_changed (Gimp * gimp,GimpBrush * brush)
name|gimp_brush_clipboard_buffer_changed
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|gint
name|width
decl_stmt|;
name|gint
name|height
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
if|if
condition|(
name|gimp
operator|->
name|global_buffer
condition|)
block|{
name|TileManager
modifier|*
name|tiles
init|=
name|gimp
operator|->
name|global_buffer
operator|->
name|tiles
decl_stmt|;
name|GimpImageType
name|type
init|=
name|gimp_buffer_get_image_type
argument_list|(
name|gimp
operator|->
name|global_buffer
argument_list|)
decl_stmt|;
name|width
operator|=
name|gimp_buffer_get_width
argument_list|(
name|gimp
operator|->
name|global_buffer
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_buffer_get_height
argument_list|(
name|gimp
operator|->
name|global_buffer
argument_list|)
expr_stmt|;
name|brush
operator|->
name|mask
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|brush
operator|->
name|pixmap
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  copy the alpha channel into the brush's mask  */
if|if
condition|(
name|GIMP_IMAGE_TYPE_HAS_ALPHA
argument_list|(
name|type
argument_list|)
condition|)
block|{
name|PixelRegion
name|bufferPR
decl_stmt|;
name|PixelRegion
name|maskPR
decl_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|bufferPR
argument_list|,
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|maskPR
argument_list|,
name|brush
operator|->
name|mask
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|extract_alpha_region
argument_list|(
operator|&
name|bufferPR
argument_list|,
name|NULL
argument_list|,
operator|&
name|maskPR
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|temp_buf_data_clear
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
block|}
comment|/*  copy the color channels into the brush's pixmap  */
if|if
condition|(
name|GIMP_IMAGE_TYPE_IS_RGB
argument_list|(
name|type
argument_list|)
condition|)
block|{
name|PixelRegion
name|bufferPR
decl_stmt|;
name|PixelRegion
name|pixmapPR
decl_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|bufferPR
argument_list|,
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|pixmapPR
argument_list|,
name|brush
operator|->
name|pixmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IMAGE_TYPE_HAS_ALPHA
argument_list|(
name|type
argument_list|)
condition|)
name|copy_color
argument_list|(
operator|&
name|bufferPR
argument_list|,
operator|&
name|pixmapPR
argument_list|)
expr_stmt|;
else|else
name|copy_region
argument_list|(
operator|&
name|bufferPR
argument_list|,
operator|&
name|pixmapPR
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|PixelRegion
name|bufferPR
decl_stmt|;
name|PixelRegion
name|tempPR
decl_stmt|;
name|TempBuf
modifier|*
name|temp
init|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|bufferPR
argument_list|,
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|tempPR
argument_list|,
name|temp
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IMAGE_TYPE_HAS_ALPHA
argument_list|(
name|type
argument_list|)
condition|)
name|copy_component
argument_list|(
operator|&
name|bufferPR
argument_list|,
operator|&
name|tempPR
argument_list|,
literal|0
argument_list|)
expr_stmt|;
else|else
name|copy_region
argument_list|(
operator|&
name|bufferPR
argument_list|,
operator|&
name|tempPR
argument_list|)
expr_stmt|;
name|temp_buf_copy
argument_list|(
name|temp
argument_list|,
name|brush
operator|->
name|pixmap
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|guchar
name|color
init|=
literal|0
decl_stmt|;
name|width
operator|=
literal|17
expr_stmt|;
name|height
operator|=
literal|17
expr_stmt|;
name|brush
operator|->
name|mask
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
name|brush
operator|->
name|x_axis
operator|.
name|x
operator|=
name|width
operator|/
literal|2
expr_stmt|;
name|brush
operator|->
name|x_axis
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|brush
operator|->
name|y_axis
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|brush
operator|->
name|y_axis
operator|.
name|y
operator|=
name|height
operator|/
literal|2
expr_stmt|;
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

