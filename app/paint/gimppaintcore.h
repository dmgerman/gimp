begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PAINT_CORE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PAINT_CORE_H__
define|#
directive|define
name|__GIMP_PAINT_CORE_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_comment
comment|/* the different states that the painting function can be called with  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c1bf4c50103
block|{
DECL|enumerator|INIT_PAINT
name|INIT_PAINT
block|,
comment|/* Setup PaintFunc internals */
DECL|enumerator|MOTION_PAINT
name|MOTION_PAINT
block|,
comment|/* PaintFunc performs motion-related rendering */
DECL|enumerator|FINISH_PAINT
name|FINISH_PAINT
block|,
comment|/* Cleanup and/or reset PaintFunc operation */
DECL|enumerator|PRETRACE_PAINT
name|PRETRACE_PAINT
block|,
comment|/* PaintFunc performs window tracing activity                      * prior to rendering                      */
DECL|enumerator|POSTTRACE_PAINT
name|POSTTRACE_PAINT
comment|/* PaintFunc performs window tracing activity                      * following rendering                      */
DECL|typedef|GimpPaintCoreState
block|}
name|GimpPaintCoreState
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PAINT_CORE
define|#
directive|define
name|GIMP_TYPE_PAINT_CORE
value|(gimp_paint_core_get_type ())
end_define

begin_define
DECL|macro|GIMP_PAINT_CORE (obj)
define|#
directive|define
name|GIMP_PAINT_CORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PAINT_CORE, GimpPaintCore))
end_define

begin_define
DECL|macro|GIMP_PAINT_CORE_CLASS (klass)
define|#
directive|define
name|GIMP_PAINT_CORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PAINT_CORE, GimpPaintCoreClass))
end_define

begin_define
DECL|macro|GIMP_IS_PAINT_CORE (obj)
define|#
directive|define
name|GIMP_IS_PAINT_CORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PAINT_CORE))
end_define

begin_define
DECL|macro|GIMP_IS_PAINT_CORE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PAINT_CORE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PAINT_CORE))
end_define

begin_define
DECL|macro|GIMP_PAINT_CORE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PAINT_CORE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PAINT_CORE, GimpPaintCoreClass))
end_define

begin_typedef
DECL|typedef|GimpPaintCoreClass
typedef|typedef
name|struct
name|_GimpPaintCoreClass
name|GimpPaintCoreClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPaintCore
struct|struct
name|_GimpPaintCore
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|ID
name|gint
name|ID
decl_stmt|;
comment|/*  unique instance ID               */
DECL|member|start_coords
name|GimpCoords
name|start_coords
decl_stmt|;
comment|/*  starting coords (for undo only)  */
DECL|member|cur_coords
name|GimpCoords
name|cur_coords
decl_stmt|;
comment|/*  current coords                   */
DECL|member|last_coords
name|GimpCoords
name|last_coords
decl_stmt|;
comment|/*  last coords                      */
DECL|member|last_paint
name|GimpVector2
name|last_paint
decl_stmt|;
comment|/*  last point that was painted      */
DECL|member|distance
name|gdouble
name|distance
decl_stmt|;
comment|/*  distance traveled by brush       */
DECL|member|pixel_dist
name|gdouble
name|pixel_dist
decl_stmt|;
comment|/*  distance in pixels               */
DECL|member|x1
DECL|member|y1
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  undo extents in image coords     */
DECL|member|x2
DECL|member|y2
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  undo extents in image coords     */
DECL|member|use_pressure
name|gboolean
name|use_pressure
decl_stmt|;
comment|/*  look at coords->pressure         */
DECL|member|undo_tiles
name|TileManager
modifier|*
name|undo_tiles
decl_stmt|;
comment|/*  tiles which have been modified   */
DECL|member|canvas_tiles
name|TileManager
modifier|*
name|canvas_tiles
decl_stmt|;
comment|/*  the buffer to paint the mask to  */
DECL|member|orig_buf
name|TempBuf
modifier|*
name|orig_buf
decl_stmt|;
comment|/*  the unmodified drawable pixels   */
DECL|member|canvas_buf
name|TempBuf
modifier|*
name|canvas_buf
decl_stmt|;
comment|/*  the buffer to paint pixels to    */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPaintCoreClass
struct|struct
name|_GimpPaintCoreClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
comment|/*  Set for tools that perform temporary rendering directly to the    *  window. These require sequencing with gimp_display_flush().    *  See gimpclone.c for example.    */
DECL|member|traces_on_window
name|gboolean
name|traces_on_window
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|start
name|gboolean
function_decl|(
modifier|*
name|start
function_decl|)
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
DECL|member|pre_paint
name|gboolean
function_decl|(
modifier|*
name|pre_paint
function_decl|)
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
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
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
DECL|member|paint
name|void
function_decl|(
modifier|*
name|paint
function_decl|)
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
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
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
DECL|member|interpolate
name|void
function_decl|(
modifier|*
name|interpolate
function_decl|)
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
DECL|member|get_paint_area
name|TempBuf
modifier|*
function_decl|(
modifier|*
name|get_paint_area
function_decl|)
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
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
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_paint_core_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_paint_core_paint
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
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
name|state
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_paint_core_start
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_core_finish
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_core_cancel
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_core_cleanup
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_core_constrain
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_core_interpolate
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  protected functions  */
end_comment

begin_function_decl
name|TempBuf
modifier|*
name|gimp_paint_core_get_paint_area
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|gimp_paint_core_get_orig_image
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_core_paste
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|PixelRegion
modifier|*
name|paint_maskPR
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gdouble
name|paint_opacity
parameter_list|,
name|gdouble
name|image_opacity
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|,
name|GimpPaintApplicationMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_core_replace
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|PixelRegion
modifier|*
name|paint_maskPR
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gdouble
name|paint_opacity
parameter_list|,
name|gdouble
name|image_opacity
parameter_list|,
name|GimpPaintApplicationMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_core_validate_undo_tiles
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_core_validate_canvas_tiles
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PAINT_CORE_H__  */
end_comment

end_unit

