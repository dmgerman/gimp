begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
DECL|member|bytes
name|gint
name|bytes
decl_stmt|;
comment|/* bytes per pixel                */
DECL|member|type
name|GimpImageType
name|type
decl_stmt|;
comment|/* type of drawable               */
DECL|member|has_alpha
name|gboolean
name|has_alpha
decl_stmt|;
comment|/* drawable has alpha             */
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
specifier|const
name|GimpDrawable
modifier|*
name|drawable
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
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
modifier|*
name|active
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
name|GimpImageBaseType
name|new_base_type
parameter_list|)
function_decl|;
DECL|member|apply_region
name|void
function_decl|(
modifier|*
name|apply_region
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PixelRegion
modifier|*
name|src2PR
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
name|GimpLayerModeEffects
name|mode
parameter_list|,
name|TileManager
modifier|*
name|src1_tiles
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
DECL|member|replace_region
name|void
function_decl|(
modifier|*
name|replace_region
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PixelRegion
modifier|*
name|src2PR
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
name|PixelRegion
modifier|*
name|maskPR
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
DECL|member|project_region
name|void
function_decl|(
modifier|*
name|project_region
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
parameter_list|,
name|PixelRegion
modifier|*
name|projPR
parameter_list|,
name|gboolean
name|combine
parameter_list|)
function_decl|;
DECL|member|get_tiles
name|TileManager
modifier|*
function_decl|(
modifier|*
name|get_tiles
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
DECL|member|set_tiles
name|void
function_decl|(
modifier|*
name|set_tiles
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
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|GimpImageType
name|type
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
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|gboolean
name|sparse
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
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|gboolean
name|sparse
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
name|gint64
name|gimp_drawable_estimate_memsize
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
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
name|gimp_drawable_configure
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
name|image
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
name|GimpImageType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
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
specifier|const
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_apply_region
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PixelRegion
modifier|*
name|src2PR
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
name|GimpLayerModeEffects
name|mode
parameter_list|,
name|TileManager
modifier|*
name|src1_tiles
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
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
name|gimp_drawable_replace_region
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PixelRegion
modifier|*
name|src2PR
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
name|PixelRegion
modifier|*
name|maskPR
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
name|gimp_drawable_project_region
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
parameter_list|,
name|PixelRegion
modifier|*
name|projPR
parameter_list|,
name|gboolean
name|combine
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_init_src_region
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
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
parameter_list|,
name|TileManager
modifier|*
modifier|*
name|temp_tiles
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|gimp_drawable_get_tiles
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_set_tiles
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
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|GimpImageType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_set_tiles_full
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
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|GimpImageType
name|type
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
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
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|gboolean
name|sparse
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
parameter_list|,
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|gboolean
name|sparse
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_fill
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
specifier|const
name|GimpPattern
modifier|*
name|pattern
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_fill_by_type
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpFillType
name|fill_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_mask_bounds
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_mask_intersect
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
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
name|gboolean
name|gimp_drawable_has_alpha
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_drawable_type
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_drawable_type_with_alpha
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_drawable_type_without_alpha
parameter_list|(
specifier|const
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
specifier|const
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
specifier|const
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
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_drawable_bytes
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_drawable_bytes_with_alpha
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_drawable_bytes_without_alpha
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_has_floating_sel
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|guchar
modifier|*
name|gimp_drawable_get_colormap
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_attach_floating_sel
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpLayer
modifier|*
name|floating_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_detach_floating_sel
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpLayer
modifier|*
name|floating_sel
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

