begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_H__
define|#
directive|define
name|__GIMP_DRAWABLE_H__
end_define

begin_include
include|#
directive|include
file|"gimpitem.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DRAWABLE
define|#
directive|define
name|GIMP_TYPE_DRAWABLE
value|(gimp_drawable_get_type ())
end_define

begin_define
DECL|macro|GIMP_DRAWABLE (obj)
define|#
directive|define
name|GIMP_DRAWABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DRAWABLE, GimpDrawable))
end_define

begin_define
DECL|macro|GIMP_DRAWABLE_CLASS (klass)
define|#
directive|define
name|GIMP_DRAWABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DRAWABLE, GimpDrawableClass))
end_define

begin_define
DECL|macro|GIMP_IS_DRAWABLE (obj)
define|#
directive|define
name|GIMP_IS_DRAWABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DRAWABLE))
end_define

begin_define
DECL|macro|GIMP_IS_DRAWABLE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DRAWABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DRAWABLE))
end_define

begin_define
DECL|macro|GIMP_DRAWABLE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DRAWABLE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DRAWABLE, GimpDrawableClass))
end_define

begin_typedef
DECL|typedef|GimpDrawablePrivate
typedef|typedef
name|struct
name|_GimpDrawablePrivate
name|GimpDrawablePrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawableClass
typedef|typedef
name|struct
name|_GimpDrawableClass
name|GimpDrawableClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDrawable
struct|struct
name|_GimpDrawable
block|{
DECL|member|parent_instance
name|GimpItem
name|parent_instance
decl_stmt|;
DECL|member|private
name|GimpDrawablePrivate
modifier|*
name|private
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDrawableClass
struct|struct
name|_GimpDrawableClass
block|{
DECL|member|parent_class
name|GimpItemClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|update
name|void
function_decl|(
modifier|*
name|update
function_decl|)
parameter_list|(
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
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
DECL|member|alpha_changed
name|void
function_decl|(
modifier|*
name|alpha_changed
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
comment|/*  virtual functions  */
DECL|member|estimate_memsize
name|gint64
function_decl|(
modifier|*
name|estimate_memsize
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpComponentType
name|component_type
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
DECL|member|invalidate_boundary
name|void
function_decl|(
modifier|*
name|invalidate_boundary
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
DECL|member|get_active_components
name|void
function_decl|(
modifier|*
name|get_active_components
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
modifier|*
name|active
parameter_list|)
function_decl|;
DECL|member|get_active_mask
name|GimpComponentMask
function_decl|(
modifier|*
name|get_active_mask
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
DECL|member|convert_type
name|void
function_decl|(
modifier|*
name|convert_type
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
specifier|const
name|Babl
modifier|*
name|new_format
parameter_list|,
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|,
name|GeglDitherMethod
name|layer_dither_type
parameter_list|,
name|GeglDitherMethod
name|mask_dither_type
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
DECL|member|apply_buffer
name|void
function_decl|(
modifier|*
name|apply_buffer
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|buffer_region
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerMode
name|mode
parameter_list|,
name|GimpLayerColorSpace
name|blend_space
parameter_list|,
name|GimpLayerColorSpace
name|composite_space
parameter_list|,
name|GimpLayerCompositeMode
name|composite_mode
parameter_list|,
name|GeglBuffer
modifier|*
name|base_buffer
parameter_list|,
name|gint
name|base_x
parameter_list|,
name|gint
name|base_y
parameter_list|)
function_decl|;
DECL|member|replace_buffer
name|void
function_decl|(
modifier|*
name|replace_buffer
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|buffer_region
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GeglBuffer
modifier|*
name|mask
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|mask_region
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
DECL|member|get_buffer
name|GeglBuffer
modifier|*
function_decl|(
modifier|*
name|get_buffer
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
DECL|member|set_buffer
name|void
function_decl|(
modifier|*
name|set_buffer
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
function_decl|;
DECL|member|push_undo
name|void
function_decl|(
modifier|*
name|push_undo
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
DECL|member|swap_pixels
name|void
function_decl|(
modifier|*
name|swap_pixels
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
DECL|member|get_source_node
name|GeglNode
modifier|*
function_decl|(
modifier|*
name|get_source_node
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_drawable_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpDrawable
modifier|*
name|gimp_drawable_new
parameter_list|(
name|GType
name|type
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_drawable_estimate_memsize
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpComponentType
name|component_type
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
name|void
name|gimp_drawable_update
parameter_list|(
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
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_alpha_changed
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_invalidate_boundary
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_get_active_components
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
modifier|*
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpComponentMask
name|gimp_drawable_get_active_mask
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_convert_type
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
name|GimpImageBaseType
name|new_base_type
parameter_list|,
name|GimpPrecision
name|new_precision
parameter_list|,
name|gboolean
name|new_has_alpha
parameter_list|,
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|,
name|GeglDitherMethod
name|layer_dither_type
parameter_list|,
name|GeglDitherMethod
name|mask_dither_type
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_apply_buffer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|buffer_rect
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerMode
name|mode
parameter_list|,
name|GimpLayerColorSpace
name|blend_space
parameter_list|,
name|GimpLayerColorSpace
name|composite_space
parameter_list|,
name|GimpLayerCompositeMode
name|composite_mode
parameter_list|,
name|GeglBuffer
modifier|*
name|base_buffer
parameter_list|,
name|gint
name|base_x
parameter_list|,
name|gint
name|base_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_replace_buffer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|buffer_region
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GeglBuffer
modifier|*
name|mask
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|mask_region
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglBuffer
modifier|*
name|gimp_drawable_get_buffer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_set_buffer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_set_buffer_full
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|gboolean
name|update
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_steal_buffer
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpDrawable
modifier|*
name|src_drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_set_format
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|gboolean
name|copy_buffer
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglNode
modifier|*
name|gimp_drawable_get_source_node
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglNode
modifier|*
name|gimp_drawable_get_mode_node
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_swap_pixels
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_push_undo
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
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
specifier|const
name|Babl
modifier|*
name|gimp_drawable_get_space
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_drawable_get_format
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_drawable_get_format_with_alpha
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_drawable_get_format_without_alpha
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpTRCType
name|gimp_drawable_get_trc
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_has_alpha
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageBaseType
name|gimp_drawable_get_base_type
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpComponentType
name|gimp_drawable_get_component_type
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPrecision
name|gimp_drawable_get_precision
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_rgb
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_gray
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_indexed
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_drawable_get_component_format
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_drawable_get_component_index
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|guchar
modifier|*
name|gimp_drawable_get_colormap
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_start_paint
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_end_paint
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_flush_paint
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_painting
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DRAWABLE_H__ */
end_comment

end_unit

