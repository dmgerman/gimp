begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LAYER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LAYER_H__
define|#
directive|define
name|__GIMP_LAYER_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_LAYER
define|#
directive|define
name|GIMP_TYPE_LAYER
value|(gimp_layer_get_type ())
end_define

begin_define
DECL|macro|GIMP_LAYER (obj)
define|#
directive|define
name|GIMP_LAYER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LAYER, GimpLayer))
end_define

begin_define
DECL|macro|GIMP_LAYER_CLASS (klass)
define|#
directive|define
name|GIMP_LAYER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LAYER, GimpLayerClass))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER (obj)
define|#
directive|define
name|GIMP_IS_LAYER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LAYER))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LAYER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LAYER))
end_define

begin_define
DECL|macro|GIMP_LAYER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_LAYER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_LAYER, GimpLayerClass))
end_define

begin_typedef
DECL|typedef|GimpLayerClass
typedef|typedef
name|struct
name|_GimpLayerClass
name|GimpLayerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpLayer
struct|struct
name|_GimpLayer
block|{
DECL|member|parent_instance
name|GimpDrawable
name|parent_instance
decl_stmt|;
DECL|member|opacity
name|gdouble
name|opacity
decl_stmt|;
comment|/*  layer opacity              */
DECL|member|mode
name|GimpLayerModeEffects
name|mode
decl_stmt|;
comment|/*  layer combination mode     */
DECL|member|lock_alpha
name|gboolean
name|lock_alpha
decl_stmt|;
comment|/*  lock the alpha channel     */
DECL|member|mask
name|GimpLayerMask
modifier|*
name|mask
decl_stmt|;
comment|/*  possible layer mask        */
comment|/*  Floating selections  */
struct|struct
DECL|struct|__anon2aea80d30108
block|{
DECL|member|backing_store
name|TileManager
modifier|*
name|backing_store
decl_stmt|;
comment|/*  for obscured regions           */
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/*  floating sel is attached to    */
DECL|member|initial
name|gboolean
name|initial
decl_stmt|;
comment|/*  is fs composited yet?          */
DECL|member|boundary_known
name|gboolean
name|boundary_known
decl_stmt|;
comment|/*  is the current boundary valid  */
DECL|member|segs
name|BoundSeg
modifier|*
name|segs
decl_stmt|;
comment|/*  boundary of floating sel       */
DECL|member|num_segs
name|gint
name|num_segs
decl_stmt|;
comment|/*  number of segs in boundary     */
DECL|member|fs
block|}
name|fs
struct|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLayerClass
struct|struct
name|_GimpLayerClass
block|{
DECL|member|parent_class
name|GimpDrawableClass
name|parent_class
decl_stmt|;
DECL|member|opacity_changed
name|void
function_decl|(
modifier|*
name|opacity_changed
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
DECL|member|mode_changed
name|void
function_decl|(
modifier|*
name|mode_changed
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
DECL|member|lock_alpha_changed
name|void
function_decl|(
modifier|*
name|lock_alpha_changed
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
DECL|member|mask_changed
name|void
function_decl|(
modifier|*
name|mask_changed
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_comment
comment|/*  function declarations  */
end_comment

begin_decl_stmt
name|GType
name|gimp_layer_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_layer_new
parameter_list|(
name|GimpImage
modifier|*
name|image
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
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_layer_new_from_tiles
parameter_list|(
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
name|GimpImageType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_layer_new_from_pixbuf
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
name|GimpImageType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_layer_new_from_region
parameter_list|(
name|PixelRegion
modifier|*
name|region
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
name|GimpImageType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerMask
modifier|*
name|gimp_layer_create_mask
parameter_list|(
specifier|const
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpAddMaskType
name|mask_type
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerMask
modifier|*
name|gimp_layer_add_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerMask
modifier|*
name|mask
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_apply_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpMaskApplyMode
name|mode
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_add_alpha
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_flatten
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_resize_to_image
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|BoundSeg
modifier|*
name|gimp_layer_boundary
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gint
modifier|*
name|num_segs
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerMask
modifier|*
name|gimp_layer_get_mask
parameter_list|(
specifier|const
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_is_floating_sel
parameter_list|(
specifier|const
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_set_opacity
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_layer_get_opacity
parameter_list|(
specifier|const
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_set_mode
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerModeEffects
name|mode
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerModeEffects
name|gimp_layer_get_mode
parameter_list|(
specifier|const
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_set_lock_alpha
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|lock_alpha
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_get_lock_alpha
parameter_list|(
specifier|const
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LAYER_H__ */
end_comment

end_unit

