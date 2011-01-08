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
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
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
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"gimpinkoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpink.h"
end_include

begin_include
include|#
directive|include
file|"gimpink-blob.h"
end_include

begin_include
include|#
directive|include
file|"gimpinkundo.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|SUBSAMPLE
define|#
directive|define
name|SUBSAMPLE
value|8
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_ink_finalize
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
name|gimp_ink_paint
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
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpPaintState
name|paint_state
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_ink_get_paint_area
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
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpUndo
modifier|*
name|gimp_ink_push_undo
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ink_motion
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
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpBlob
modifier|*
name|ink_pen_ellipse
parameter_list|(
name|GimpInkOptions
modifier|*
name|options
parameter_list|,
name|gdouble
name|x_center
parameter_list|,
name|gdouble
name|y_center
parameter_list|,
name|gdouble
name|pressure
parameter_list|,
name|gdouble
name|xtilt
parameter_list|,
name|gdouble
name|ytilt
parameter_list|,
name|gdouble
name|velocity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|render_blob
parameter_list|(
name|GimpBlob
modifier|*
name|blob
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpInk,gimp_ink,GIMP_TYPE_PAINT_CORE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpInk
argument_list|,
argument|gimp_ink
argument_list|,
argument|GIMP_TYPE_PAINT_CORE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_ink_parent_class
end_define

begin_function
name|void
name|gimp_ink_register
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
name|GIMP_TYPE_INK
argument_list|,
name|GIMP_TYPE_INK_OPTIONS
argument_list|,
literal|"gimp-ink"
argument_list|,
name|_
argument_list|(
literal|"Ink"
argument_list|)
argument_list|,
literal|"gimp-tool-ink"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ink_class_init (GimpInkClass * klass)
name|gimp_ink_class_init
parameter_list|(
name|GimpInkClass
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
name|GimpPaintCoreClass
modifier|*
name|paint_core_class
init|=
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_ink_finalize
expr_stmt|;
name|paint_core_class
operator|->
name|paint
operator|=
name|gimp_ink_paint
expr_stmt|;
name|paint_core_class
operator|->
name|get_paint_area
operator|=
name|gimp_ink_get_paint_area
expr_stmt|;
name|paint_core_class
operator|->
name|push_undo
operator|=
name|gimp_ink_push_undo
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ink_init (GimpInk * ink)
name|gimp_ink_init
parameter_list|(
name|GimpInk
modifier|*
name|ink
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ink_finalize (GObject * object)
name|gimp_ink_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpInk
modifier|*
name|ink
init|=
name|GIMP_INK
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|ink
operator|->
name|start_blob
condition|)
block|{
name|g_free
argument_list|(
name|ink
operator|->
name|start_blob
argument_list|)
expr_stmt|;
name|ink
operator|->
name|start_blob
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|ink
operator|->
name|last_blob
condition|)
block|{
name|g_free
argument_list|(
name|ink
operator|->
name|last_blob
argument_list|)
expr_stmt|;
name|ink
operator|->
name|last_blob
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
name|void
DECL|function|gimp_ink_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,GimpPaintState paint_state,guint32 time)
name|gimp_ink_paint
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
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpPaintState
name|paint_state
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
name|GimpInk
modifier|*
name|ink
init|=
name|GIMP_INK
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|paint_state
condition|)
block|{
name|GimpCoords
name|last_coords
decl_stmt|;
case|case
name|GIMP_PAINT_STATE_INIT
case|:
name|gimp_paint_core_get_last_coords
argument_list|(
name|paint_core
argument_list|,
operator|&
name|last_coords
argument_list|)
expr_stmt|;
if|if
condition|(
name|coords
operator|->
name|x
operator|==
name|last_coords
operator|.
name|x
operator|&&
name|coords
operator|->
name|y
operator|==
name|last_coords
operator|.
name|y
condition|)
block|{
comment|/*  start with new blobs if we're not interpolating  */
if|if
condition|(
name|ink
operator|->
name|start_blob
condition|)
block|{
name|g_free
argument_list|(
name|ink
operator|->
name|start_blob
argument_list|)
expr_stmt|;
name|ink
operator|->
name|start_blob
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|ink
operator|->
name|last_blob
condition|)
block|{
name|g_free
argument_list|(
name|ink
operator|->
name|last_blob
argument_list|)
expr_stmt|;
name|ink
operator|->
name|last_blob
operator|=
name|NULL
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|ink
operator|->
name|last_blob
condition|)
block|{
comment|/*  save the start blob of the line for undo otherwise  */
if|if
condition|(
name|ink
operator|->
name|start_blob
condition|)
name|g_free
argument_list|(
name|ink
operator|->
name|start_blob
argument_list|)
expr_stmt|;
name|ink
operator|->
name|start_blob
operator|=
name|gimp_blob_duplicate
argument_list|(
name|ink
operator|->
name|last_blob
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PAINT_STATE_MOTION
case|:
name|gimp_ink_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|,
name|time
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PAINT_STATE_FINISH
case|:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_ink_get_paint_area (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords)
name|gimp_ink_get_paint_area
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
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
name|GimpInk
modifier|*
name|ink
init|=
name|GIMP_INK
argument_list|(
name|paint_core
argument_list|)
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
name|gint
name|dwidth
decl_stmt|,
name|dheight
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|bytes
operator|=
name|gimp_drawable_bytes_with_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_blob_bounds
argument_list|(
name|ink
operator|->
name|cur_blob
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|dwidth
operator|=
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|dheight
operator|=
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|x1
operator|=
name|CLAMP
argument_list|(
name|x
operator|/
name|SUBSAMPLE
operator|-
literal|1
argument_list|,
literal|0
argument_list|,
name|dwidth
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|y
operator|/
name|SUBSAMPLE
operator|-
literal|1
argument_list|,
literal|0
argument_list|,
name|dheight
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
operator|(
name|x
operator|+
name|width
operator|)
operator|/
name|SUBSAMPLE
operator|+
literal|2
argument_list|,
literal|0
argument_list|,
name|dwidth
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
operator|(
name|y
operator|+
name|height
operator|)
operator|/
name|SUBSAMPLE
operator|+
literal|2
argument_list|,
literal|0
argument_list|,
name|dheight
argument_list|)
expr_stmt|;
comment|/*  configure the canvas buffer  */
if|if
condition|(
operator|(
name|x2
operator|-
name|x1
operator|)
operator|&&
operator|(
name|y2
operator|-
name|y1
operator|)
condition|)
name|paint_core
operator|->
name|canvas_buf
operator|=
name|temp_buf_resize
argument_list|(
name|paint_core
operator|->
name|canvas_buf
argument_list|,
name|bytes
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|)
expr_stmt|;
else|else
return|return
name|NULL
return|;
return|return
name|paint_core
operator|->
name|canvas_buf
return|;
block|}
end_function

begin_function
specifier|static
name|GimpUndo
modifier|*
DECL|function|gimp_ink_push_undo (GimpPaintCore * core,GimpImage * image,const gchar * undo_desc)
name|gimp_ink_push_undo
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
block|{
return|return
name|gimp_image_undo_push
argument_list|(
name|image
argument_list|,
name|GIMP_TYPE_INK_UNDO
argument_list|,
name|GIMP_UNDO_INK
argument_list|,
name|undo_desc
argument_list|,
literal|0
argument_list|,
literal|"paint-core"
argument_list|,
name|core
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ink_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,guint32 time)
name|gimp_ink_motion
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
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
name|GimpInk
modifier|*
name|ink
init|=
name|GIMP_INK
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpInkOptions
modifier|*
name|options
init|=
name|GIMP_INK_OPTIONS
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpBlob
modifier|*
name|blob_union
init|=
name|NULL
decl_stmt|;
name|GimpBlob
modifier|*
name|blob_to_render
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
name|PixelRegion
name|blob_maskPR
decl_stmt|;
name|GimpCoords
name|modified_coords
decl_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|modified_coords
operator|=
name|gimp_paint_core_get_smoothed_coords
argument_list|(
name|paint_core
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|ink
operator|->
name|last_blob
condition|)
block|{
name|ink
operator|->
name|last_blob
operator|=
name|ink_pen_ellipse
argument_list|(
name|options
argument_list|,
name|modified_coords
operator|.
name|x
argument_list|,
name|modified_coords
operator|.
name|y
argument_list|,
name|modified_coords
operator|.
name|pressure
argument_list|,
name|modified_coords
operator|.
name|xtilt
argument_list|,
name|modified_coords
operator|.
name|ytilt
argument_list|,
literal|100
argument_list|)
expr_stmt|;
if|if
condition|(
name|ink
operator|->
name|start_blob
condition|)
name|g_free
argument_list|(
name|ink
operator|->
name|start_blob
argument_list|)
expr_stmt|;
name|ink
operator|->
name|start_blob
operator|=
name|gimp_blob_duplicate
argument_list|(
name|ink
operator|->
name|last_blob
argument_list|)
expr_stmt|;
name|blob_to_render
operator|=
name|ink
operator|->
name|last_blob
expr_stmt|;
block|}
else|else
block|{
name|GimpBlob
modifier|*
name|blob
init|=
name|ink_pen_ellipse
argument_list|(
name|options
argument_list|,
name|modified_coords
operator|.
name|x
argument_list|,
name|modified_coords
operator|.
name|y
argument_list|,
name|modified_coords
operator|.
name|pressure
argument_list|,
name|modified_coords
operator|.
name|xtilt
argument_list|,
name|modified_coords
operator|.
name|ytilt
argument_list|,
name|modified_coords
operator|.
name|velocity
operator|*
literal|100
argument_list|)
decl_stmt|;
name|blob_union
operator|=
name|gimp_blob_convex_union
argument_list|(
name|ink
operator|->
name|last_blob
argument_list|,
name|blob
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ink
operator|->
name|last_blob
argument_list|)
expr_stmt|;
name|ink
operator|->
name|last_blob
operator|=
name|blob
expr_stmt|;
name|blob_to_render
operator|=
name|blob_union
expr_stmt|;
block|}
comment|/* Get the buffer */
name|ink
operator|->
name|cur_blob
operator|=
name|blob_to_render
expr_stmt|;
name|area
operator|=
name|gimp_paint_core_get_paint_area
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|)
expr_stmt|;
name|ink
operator|->
name|cur_blob
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
operator|!
name|area
condition|)
return|return;
name|gimp_image_get_foreground
argument_list|(
name|image
argument_list|,
name|context
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|col
argument_list|)
expr_stmt|;
comment|/*  set the alpha channel  */
name|col
index|[
name|paint_core
operator|->
name|canvas_buf
operator|->
name|bytes
operator|-
literal|1
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
comment|/*  color the pixels  */
name|color_pixels
argument_list|(
name|temp_buf_get_data
argument_list|(
name|paint_core
operator|->
name|canvas_buf
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
name|gimp_paint_core_validate_canvas_tiles
argument_list|(
name|paint_core
argument_list|,
name|paint_core
operator|->
name|canvas_buf
operator|->
name|x
argument_list|,
name|paint_core
operator|->
name|canvas_buf
operator|->
name|y
argument_list|,
name|paint_core
operator|->
name|canvas_buf
operator|->
name|width
argument_list|,
name|paint_core
operator|->
name|canvas_buf
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/*  draw the blob directly to the canvas_tiles  */
name|pixel_region_init
argument_list|(
operator|&
name|blob_maskPR
argument_list|,
name|paint_core
operator|->
name|canvas_tiles
argument_list|,
name|paint_core
operator|->
name|canvas_buf
operator|->
name|x
argument_list|,
name|paint_core
operator|->
name|canvas_buf
operator|->
name|y
argument_list|,
name|paint_core
operator|->
name|canvas_buf
operator|->
name|width
argument_list|,
name|paint_core
operator|->
name|canvas_buf
operator|->
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|render_blob
argument_list|(
name|blob_to_render
argument_list|,
operator|&
name|blob_maskPR
argument_list|)
expr_stmt|;
comment|/*  draw the canvas_buf using the just rendered canvas_tiles as mask */
name|pixel_region_init
argument_list|(
operator|&
name|blob_maskPR
argument_list|,
name|paint_core
operator|->
name|canvas_tiles
argument_list|,
name|paint_core
operator|->
name|canvas_buf
operator|->
name|x
argument_list|,
name|paint_core
operator|->
name|canvas_buf
operator|->
name|y
argument_list|,
name|paint_core
operator|->
name|canvas_buf
operator|->
name|width
argument_list|,
name|paint_core
operator|->
name|canvas_buf
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_paint_core_paste
argument_list|(
name|paint_core
argument_list|,
operator|&
name|blob_maskPR
argument_list|,
name|drawable
argument_list|,
name|GIMP_OPACITY_OPAQUE
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
name|GIMP_PAINT_CONSTANT
argument_list|)
expr_stmt|;
if|if
condition|(
name|blob_union
condition|)
name|g_free
argument_list|(
name|blob_union
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpBlob
modifier|*
DECL|function|ink_pen_ellipse (GimpInkOptions * options,gdouble x_center,gdouble y_center,gdouble pressure,gdouble xtilt,gdouble ytilt,gdouble velocity)
name|ink_pen_ellipse
parameter_list|(
name|GimpInkOptions
modifier|*
name|options
parameter_list|,
name|gdouble
name|x_center
parameter_list|,
name|gdouble
name|y_center
parameter_list|,
name|gdouble
name|pressure
parameter_list|,
name|gdouble
name|xtilt
parameter_list|,
name|gdouble
name|ytilt
parameter_list|,
name|gdouble
name|velocity
parameter_list|)
block|{
name|GimpBlobFunc
name|blob_function
decl_stmt|;
name|gdouble
name|size
decl_stmt|;
name|gdouble
name|tsin
decl_stmt|,
name|tcos
decl_stmt|;
name|gdouble
name|aspect
decl_stmt|,
name|radmin
decl_stmt|;
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdouble
name|tscale
decl_stmt|;
name|gdouble
name|tscale_c
decl_stmt|;
name|gdouble
name|tscale_s
decl_stmt|;
comment|/* Adjust the size depending on pressure. */
name|size
operator|=
name|options
operator|->
name|size
operator|*
operator|(
literal|1.0
operator|+
name|options
operator|->
name|size_sensitivity
operator|*
operator|(
literal|2.0
operator|*
name|pressure
operator|-
literal|1.0
operator|)
operator|)
expr_stmt|;
comment|/* Adjust the size further depending on pointer velocity and    * velocity-sensitivity.  These 'magic constants' are 'feels    * natural' tigert-approved. --ADM    */
if|if
condition|(
name|velocity
operator|<
literal|3.0
condition|)
name|velocity
operator|=
literal|3.0
expr_stmt|;
ifdef|#
directive|ifdef
name|VERBOSE
name|g_printerr
argument_list|(
literal|"%g (%g) -> "
argument_list|,
name|size
argument_list|,
name|velocity
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|size
operator|=
operator|(
name|options
operator|->
name|vel_sensitivity
operator|*
operator|(
operator|(
literal|4.5
operator|*
name|size
operator|)
operator|/
operator|(
literal|1.0
operator|+
name|options
operator|->
name|vel_sensitivity
operator|*
operator|(
literal|2.0
operator|*
name|velocity
operator|)
operator|)
operator|)
operator|+
operator|(
literal|1.0
operator|-
name|options
operator|->
name|vel_sensitivity
operator|)
operator|*
name|size
operator|)
expr_stmt|;
ifdef|#
directive|ifdef
name|VERBOSE
name|g_printerr
argument_list|(
literal|"%g\n"
argument_list|,
operator|(
name|gfloat
operator|)
name|size
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* Clamp resulting size to sane limits */
if|if
condition|(
name|size
operator|>
name|options
operator|->
name|size
operator|*
operator|(
literal|1.0
operator|+
name|options
operator|->
name|size_sensitivity
operator|)
condition|)
name|size
operator|=
name|options
operator|->
name|size
operator|*
operator|(
literal|1.0
operator|+
name|options
operator|->
name|size_sensitivity
operator|)
expr_stmt|;
if|if
condition|(
name|size
operator|*
name|SUBSAMPLE
operator|<
literal|1.0
condition|)
name|size
operator|=
literal|1.0
operator|/
name|SUBSAMPLE
expr_stmt|;
comment|/* Add brush angle/aspect to tilt vectorially */
comment|/* I'm not happy with the way the brush widget info is combined with    * tilt info from the brush. My personal feeling is that    * representing both as affine transforms would make the most    * sense. -RLL    */
name|tscale
operator|=
name|options
operator|->
name|tilt_sensitivity
operator|*
literal|10.0
expr_stmt|;
name|tscale_c
operator|=
name|tscale
operator|*
name|cos
argument_list|(
name|gimp_deg_to_rad
argument_list|(
name|options
operator|->
name|tilt_angle
argument_list|)
argument_list|)
expr_stmt|;
name|tscale_s
operator|=
name|tscale
operator|*
name|sin
argument_list|(
name|gimp_deg_to_rad
argument_list|(
name|options
operator|->
name|tilt_angle
argument_list|)
argument_list|)
expr_stmt|;
name|x
operator|=
operator|(
name|options
operator|->
name|blob_aspect
operator|*
name|cos
argument_list|(
name|options
operator|->
name|blob_angle
argument_list|)
operator|+
name|xtilt
operator|*
name|tscale_c
operator|-
name|ytilt
operator|*
name|tscale_s
operator|)
expr_stmt|;
name|y
operator|=
operator|(
name|options
operator|->
name|blob_aspect
operator|*
name|sin
argument_list|(
name|options
operator|->
name|blob_angle
argument_list|)
operator|+
name|ytilt
operator|*
name|tscale_c
operator|+
name|xtilt
operator|*
name|tscale_s
operator|)
expr_stmt|;
ifdef|#
directive|ifdef
name|VERBOSE
name|g_printerr
argument_list|(
literal|"angle %g aspect %g; %g %g; %g %g\n"
argument_list|,
name|options
operator|->
name|blob_angle
argument_list|,
name|options
operator|->
name|blob_aspect
argument_list|,
name|tscale_c
argument_list|,
name|tscale_s
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|aspect
operator|=
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|x
argument_list|)
operator|+
name|SQR
argument_list|(
name|y
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|aspect
operator|!=
literal|0
condition|)
block|{
name|tcos
operator|=
name|x
operator|/
name|aspect
expr_stmt|;
name|tsin
operator|=
name|y
operator|/
name|aspect
expr_stmt|;
block|}
else|else
block|{
name|tsin
operator|=
name|sin
argument_list|(
name|options
operator|->
name|blob_angle
argument_list|)
expr_stmt|;
name|tcos
operator|=
name|cos
argument_list|(
name|options
operator|->
name|blob_angle
argument_list|)
expr_stmt|;
block|}
name|aspect
operator|=
name|CLAMP
argument_list|(
name|aspect
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|)
expr_stmt|;
name|radmin
operator|=
name|MAX
argument_list|(
literal|1.0
argument_list|,
name|SUBSAMPLE
operator|*
name|size
operator|/
name|aspect
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|options
operator|->
name|blob_type
condition|)
block|{
case|case
name|GIMP_INK_BLOB_TYPE_CIRCLE
case|:
name|blob_function
operator|=
name|gimp_blob_ellipse
expr_stmt|;
break|break;
case|case
name|GIMP_INK_BLOB_TYPE_SQUARE
case|:
name|blob_function
operator|=
name|gimp_blob_square
expr_stmt|;
break|break;
case|case
name|GIMP_INK_BLOB_TYPE_DIAMOND
case|:
name|blob_function
operator|=
name|gimp_blob_diamond
expr_stmt|;
break|break;
default|default:
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
call|(
modifier|*
name|blob_function
call|)
argument_list|(
name|x_center
operator|*
name|SUBSAMPLE
argument_list|,
name|y_center
operator|*
name|SUBSAMPLE
argument_list|,
name|radmin
operator|*
name|aspect
operator|*
name|tcos
argument_list|,
name|radmin
operator|*
name|aspect
operator|*
name|tsin
argument_list|,
operator|-
name|radmin
operator|*
name|tsin
argument_list|,
name|radmin
operator|*
name|tcos
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*********************************/
end_comment

begin_comment
comment|/*  Rendering functions          */
end_comment

begin_comment
comment|/*********************************/
end_comment

begin_comment
comment|/* Some of this stuff should probably be combined with the  * code it was copied from in paint_core.c; but I wanted  * to learn this stuff, so I've kept it simple.  *  * The following only supports CONSTANT mode. Incremental  * would, I think, interact strangely with the way we  * do things. But it wouldn't be hard to implement at all.  */
end_comment

begin_enum
enum|enum
DECL|enum|__anon28a40a9e0103
block|{
DECL|enumerator|ROW_START
name|ROW_START
block|,
DECL|enumerator|ROW_STOP
name|ROW_STOP
block|}
enum|;
end_enum

begin_comment
comment|/* The insertion sort here, for SUBSAMPLE = 8, tends to beat out  * qsort() by 4x with CFLAGS=-O2, 2x with CFLAGS=-g  */
end_comment

begin_function
specifier|static
name|void
DECL|function|insert_sort (gint * data,gint n)
name|insert_sort
parameter_list|(
name|gint
modifier|*
name|data
parameter_list|,
name|gint
name|n
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|2
init|;
name|i
operator|<
literal|2
operator|*
name|n
condition|;
name|i
operator|+=
literal|2
control|)
block|{
name|gint
name|tmp1
init|=
name|data
index|[
name|i
index|]
decl_stmt|;
name|gint
name|tmp2
init|=
name|data
index|[
name|i
operator|+
literal|1
index|]
decl_stmt|;
name|j
operator|=
literal|0
expr_stmt|;
while|while
condition|(
name|data
index|[
name|j
index|]
operator|<
name|tmp1
condition|)
name|j
operator|+=
literal|2
expr_stmt|;
for|for
control|(
name|k
operator|=
name|i
init|;
name|k
operator|>
name|j
condition|;
name|k
operator|-=
literal|2
control|)
block|{
name|data
index|[
name|k
index|]
operator|=
name|data
index|[
name|k
operator|-
literal|2
index|]
expr_stmt|;
name|data
index|[
name|k
operator|+
literal|1
index|]
operator|=
name|data
index|[
name|k
operator|-
literal|1
index|]
expr_stmt|;
block|}
name|data
index|[
name|j
index|]
operator|=
name|tmp1
expr_stmt|;
name|data
index|[
name|j
operator|+
literal|1
index|]
operator|=
name|tmp2
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|fill_run (guchar * dest,guchar alpha,gint w)
name|fill_run
parameter_list|(
name|guchar
modifier|*
name|dest
parameter_list|,
name|guchar
name|alpha
parameter_list|,
name|gint
name|w
parameter_list|)
block|{
if|if
condition|(
name|alpha
operator|==
literal|255
condition|)
block|{
name|memset
argument_list|(
name|dest
argument_list|,
literal|255
argument_list|,
name|w
argument_list|)
expr_stmt|;
block|}
else|else
block|{
while|while
condition|(
name|w
operator|--
condition|)
block|{
operator|*
name|dest
operator|=
name|MAX
argument_list|(
operator|*
name|dest
argument_list|,
name|alpha
argument_list|)
expr_stmt|;
name|dest
operator|++
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|render_blob_line (GimpBlob * blob,guchar * dest,gint x,gint y,gint width)
name|render_blob_line
parameter_list|(
name|GimpBlob
modifier|*
name|blob
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|)
block|{
name|gint
name|buf
index|[
literal|4
operator|*
name|SUBSAMPLE
index|]
decl_stmt|;
name|gint
modifier|*
name|data
init|=
name|buf
decl_stmt|;
name|gint
name|n
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|gint
name|current
init|=
literal|0
decl_stmt|;
comment|/* number of filled rows at this point                        * in the scan line                        */
name|gint
name|last_x
decl_stmt|;
comment|/* Sort start and ends for all lines */
name|j
operator|=
name|y
operator|*
name|SUBSAMPLE
operator|-
name|blob
operator|->
name|y
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|SUBSAMPLE
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|j
operator|>=
name|blob
operator|->
name|height
condition|)
break|break;
if|if
condition|(
operator|(
name|j
operator|>
literal|0
operator|)
operator|&&
operator|(
name|blob
operator|->
name|data
index|[
name|j
index|]
operator|.
name|left
operator|<=
name|blob
operator|->
name|data
index|[
name|j
index|]
operator|.
name|right
operator|)
condition|)
block|{
name|data
index|[
literal|2
operator|*
name|n
index|]
operator|=
name|blob
operator|->
name|data
index|[
name|j
index|]
operator|.
name|left
expr_stmt|;
name|data
index|[
literal|2
operator|*
name|n
operator|+
literal|1
index|]
operator|=
name|ROW_START
expr_stmt|;
name|data
index|[
literal|2
operator|*
name|SUBSAMPLE
operator|+
literal|2
operator|*
name|n
index|]
operator|=
name|blob
operator|->
name|data
index|[
name|j
index|]
operator|.
name|right
expr_stmt|;
name|data
index|[
literal|2
operator|*
name|SUBSAMPLE
operator|+
literal|2
operator|*
name|n
operator|+
literal|1
index|]
operator|=
name|ROW_STOP
expr_stmt|;
name|n
operator|++
expr_stmt|;
block|}
name|j
operator|++
expr_stmt|;
block|}
comment|/*   If we have less than SUBSAMPLE rows, compress */
if|if
condition|(
name|n
operator|<
name|SUBSAMPLE
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|2
operator|*
name|n
condition|;
name|i
operator|++
control|)
name|data
index|[
literal|2
operator|*
name|n
operator|+
name|i
index|]
operator|=
name|data
index|[
literal|2
operator|*
name|SUBSAMPLE
operator|+
name|i
index|]
expr_stmt|;
block|}
comment|/*   Now count start and end separately */
name|n
operator|*=
literal|2
expr_stmt|;
name|insert_sort
argument_list|(
name|data
argument_list|,
name|n
argument_list|)
expr_stmt|;
comment|/* Discard portions outside of tile */
while|while
condition|(
operator|(
name|n
operator|>
literal|0
operator|)
operator|&&
operator|(
name|data
index|[
literal|0
index|]
operator|<
name|SUBSAMPLE
operator|*
name|x
operator|)
condition|)
block|{
if|if
condition|(
name|data
index|[
literal|1
index|]
operator|==
name|ROW_START
condition|)
name|current
operator|++
expr_stmt|;
else|else
name|current
operator|--
expr_stmt|;
name|data
operator|+=
literal|2
expr_stmt|;
name|n
operator|--
expr_stmt|;
block|}
while|while
condition|(
operator|(
name|n
operator|>
literal|0
operator|)
operator|&&
operator|(
name|data
index|[
literal|2
operator|*
operator|(
name|n
operator|-
literal|1
operator|)
index|]
operator|>=
name|SUBSAMPLE
operator|*
operator|(
name|x
operator|+
name|width
operator|)
operator|)
condition|)
name|n
operator|--
expr_stmt|;
comment|/* Render the row */
name|last_x
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n
condition|;
control|)
block|{
name|gint
name|cur_x
init|=
name|data
index|[
literal|2
operator|*
name|i
index|]
operator|/
name|SUBSAMPLE
operator|-
name|x
decl_stmt|;
name|gint
name|pixel
decl_stmt|;
comment|/* Fill in portion leading up to this pixel */
if|if
condition|(
name|current
operator|&&
name|cur_x
operator|!=
name|last_x
condition|)
name|fill_run
argument_list|(
name|dest
operator|+
name|last_x
argument_list|,
operator|(
literal|255
operator|*
name|current
operator|)
operator|/
name|SUBSAMPLE
argument_list|,
name|cur_x
operator|-
name|last_x
argument_list|)
expr_stmt|;
comment|/* Compute the value for this pixel */
name|pixel
operator|=
name|current
operator|*
name|SUBSAMPLE
expr_stmt|;
while|while
condition|(
name|i
operator|<
name|n
condition|)
block|{
name|gint
name|tmp_x
init|=
name|data
index|[
literal|2
operator|*
name|i
index|]
operator|/
name|SUBSAMPLE
decl_stmt|;
if|if
condition|(
name|tmp_x
operator|-
name|x
operator|!=
name|cur_x
condition|)
break|break;
if|if
condition|(
name|data
index|[
literal|2
operator|*
name|i
operator|+
literal|1
index|]
operator|==
name|ROW_START
condition|)
block|{
name|current
operator|++
expr_stmt|;
name|pixel
operator|+=
operator|(
operator|(
name|tmp_x
operator|+
literal|1
operator|)
operator|*
name|SUBSAMPLE
operator|)
operator|-
name|data
index|[
literal|2
operator|*
name|i
index|]
expr_stmt|;
block|}
else|else
block|{
name|current
operator|--
expr_stmt|;
name|pixel
operator|-=
operator|(
operator|(
name|tmp_x
operator|+
literal|1
operator|)
operator|*
name|SUBSAMPLE
operator|)
operator|-
name|data
index|[
literal|2
operator|*
name|i
index|]
expr_stmt|;
block|}
name|i
operator|++
expr_stmt|;
block|}
name|dest
index|[
name|cur_x
index|]
operator|=
name|MAX
argument_list|(
name|dest
index|[
name|cur_x
index|]
argument_list|,
operator|(
name|pixel
operator|*
literal|255
operator|)
operator|/
operator|(
name|SUBSAMPLE
operator|*
name|SUBSAMPLE
operator|)
argument_list|)
expr_stmt|;
name|last_x
operator|=
name|cur_x
operator|+
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|current
operator|!=
literal|0
condition|)
name|fill_run
argument_list|(
name|dest
operator|+
name|last_x
argument_list|,
operator|(
literal|255
operator|*
name|current
operator|)
operator|/
name|SUBSAMPLE
argument_list|,
name|width
operator|-
name|last_x
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|render_blob (GimpBlob * blob,PixelRegion * dest)
name|render_blob
parameter_list|(
name|GimpBlob
modifier|*
name|blob
parameter_list|,
name|PixelRegion
modifier|*
name|dest
parameter_list|)
block|{
name|gpointer
name|pr
decl_stmt|;
for|for
control|(
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|1
argument_list|,
name|dest
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|pixel_regions_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|guchar
modifier|*
name|d
init|=
name|dest
operator|->
name|data
decl_stmt|;
name|gint
name|h
init|=
name|dest
operator|->
name|h
decl_stmt|;
name|gint
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|h
condition|;
name|y
operator|++
operator|,
name|d
operator|+=
name|dest
operator|->
name|rowstride
control|)
block|{
name|render_blob_line
argument_list|(
name|blob
argument_list|,
name|d
argument_list|,
name|dest
operator|->
name|x
argument_list|,
name|dest
operator|->
name|y
operator|+
name|y
argument_list|,
name|dest
operator|->
name|w
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

