begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimppencil.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_pencil_class_init
parameter_list|(
name|GimpPencilClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pencil_init
parameter_list|(
name|GimpPencil
modifier|*
name|pencil
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pencil_paint
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpPaintCoreState
name|paint_state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pencil_motion
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpPaintCoreClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_pencil_register (Gimp * gimp,GimpPaintRegisterCallback callback)
name|gimp_pencil_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPaintRegisterCallback
name|callback
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_PENCIL
argument_list|,
name|GIMP_TYPE_PAINT_OPTIONS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_pencil_get_type (void)
name|gimp_pencil_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpPencilClass
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
name|gimp_pencil_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpPencil
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_pencil_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PAINT_CORE
argument_list|,
literal|"GimpPencil"
argument_list|,
operator|&
name|info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pencil_class_init (GimpPencilClass * klass)
name|gimp_pencil_class_init
parameter_list|(
name|GimpPencilClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPaintCoreClass
modifier|*
name|paint_core_class
decl_stmt|;
name|paint_core_class
operator|=
name|GIMP_PAINT_CORE_CLASS
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
name|paint_core_class
operator|->
name|paint
operator|=
name|gimp_pencil_paint
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pencil_init (GimpPencil * pencil)
name|gimp_pencil_init
parameter_list|(
name|GimpPencil
modifier|*
name|pencil
parameter_list|)
block|{
name|GimpPaintCore
modifier|*
name|paint_core
decl_stmt|;
name|paint_core
operator|=
name|GIMP_PAINT_CORE
argument_list|(
name|pencil
argument_list|)
expr_stmt|;
name|paint_core
operator|->
name|flags
operator||=
name|CORE_HANDLES_CHANGING_BRUSH
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pencil_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpPaintCoreState paint_state)
name|gimp_pencil_paint
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpPaintCoreState
name|paint_state
parameter_list|)
block|{
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|MOTION_PAINT
case|:
name|gimp_pencil_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pencil_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options)
name|gimp_pencil_motion
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|)
block|{
name|GimpPressureOptions
modifier|*
name|pressure_options
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|guchar
name|col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|gdouble
name|opacity
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
name|GimpPaintApplicationMode
name|paint_appl_mode
decl_stmt|;
name|pressure_options
operator|=
name|paint_options
operator|->
name|pressure_options
expr_stmt|;
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_get_current_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|paint_appl_mode
operator|=
operator|(
name|paint_options
operator|->
name|incremental
condition|?
name|GIMP_PAINT_INCREMENTAL
else|:
name|GIMP_PAINT_CONSTANT
operator|)
expr_stmt|;
if|if
condition|(
name|pressure_options
operator|->
name|size
condition|)
name|scale
operator|=
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
expr_stmt|;
else|else
name|scale
operator|=
literal|1.0
expr_stmt|;
comment|/*  Get a region which can be used to paint to  */
if|if
condition|(
operator|!
operator|(
name|area
operator|=
name|gimp_paint_core_get_paint_area
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|scale
argument_list|)
operator|)
condition|)
return|return;
comment|/*  color the pixels  */
if|if
condition|(
name|pressure_options
operator|->
name|color
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_gradient_get_color_at
argument_list|(
name|gimp_context_get_gradient
argument_list|(
name|context
argument_list|)
argument_list|,
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|col
index|[
name|RED_PIX
index|]
argument_list|,
operator|&
name|col
index|[
name|GREEN_PIX
index|]
argument_list|,
operator|&
name|col
index|[
name|BLUE_PIX
index|]
argument_list|,
operator|&
name|col
index|[
name|ALPHA_PIX
index|]
argument_list|)
expr_stmt|;
name|paint_appl_mode
operator|=
name|GIMP_PAINT_INCREMENTAL
expr_stmt|;
name|color_pixels
argument_list|(
name|temp_buf_data
argument_list|(
name|area
argument_list|)
argument_list|,
name|col
argument_list|,
name|area
operator|->
name|width
operator|*
name|area
operator|->
name|height
argument_list|,
name|area
operator|->
name|bytes
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|paint_core
operator|->
name|brush
operator|&&
name|paint_core
operator|->
name|brush
operator|->
name|pixmap
condition|)
block|{
comment|/* if its a pixmap, do pixmap stuff */
name|gimp_paint_core_color_area_with_pixmap
argument_list|(
name|paint_core
argument_list|,
name|gimage
argument_list|,
name|drawable
argument_list|,
name|area
argument_list|,
name|scale
argument_list|,
name|GIMP_BRUSH_HARD
argument_list|)
expr_stmt|;
name|paint_appl_mode
operator|=
name|GIMP_PAINT_INCREMENTAL
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_get_foreground
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|col
argument_list|)
expr_stmt|;
name|col
index|[
name|area
operator|->
name|bytes
operator|-
literal|1
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
name|color_pixels
argument_list|(
name|temp_buf_data
argument_list|(
name|area
argument_list|)
argument_list|,
name|col
argument_list|,
name|area
operator|->
name|width
operator|*
name|area
operator|->
name|height
argument_list|,
name|area
operator|->
name|bytes
argument_list|)
expr_stmt|;
block|}
name|opacity
operator|=
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|pressure_options
operator|->
name|opacity
condition|)
name|opacity
operator|=
name|opacity
operator|*
literal|2.0
operator|*
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
expr_stmt|;
comment|/*  paste the newly painted canvas to the gimage which is being worked on  */
name|gimp_paint_core_paste_canvas
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|MIN
argument_list|(
name|opacity
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|context
argument_list|)
argument_list|,
name|GIMP_BRUSH_HARD
argument_list|,
name|scale
argument_list|,
name|paint_appl_mode
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

