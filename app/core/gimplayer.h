begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__LAYER_H__
end_ifndef

begin_define
DECL|macro|__LAYER_H__
define|#
directive|define
name|__LAYER_H__
end_define

begin_include
include|#
directive|include
file|"channel.h"
end_include

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
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_LAYER, GimpLayer))
end_define

begin_define
DECL|macro|GIMP_LAYER_CLASS (klass)
define|#
directive|define
name|GIMP_LAYER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LAYER, GimpLayerClass))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER (obj)
define|#
directive|define
name|GIMP_IS_LAYER
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_LAYER))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LAYER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LAYER))
end_define

begin_define
DECL|macro|GIMP_TYPE_LAYER_MASK
define|#
directive|define
name|GIMP_TYPE_LAYER_MASK
value|(gimp_layer_mask_get_type ())
end_define

begin_define
DECL|macro|GIMP_LAYER_MASK (obj)
define|#
directive|define
name|GIMP_LAYER_MASK
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_LAYER_MASK, GimpLayerMask))
end_define

begin_define
DECL|macro|GIMP_LAYER_MASK_CLASS (klass)
define|#
directive|define
name|GIMP_LAYER_MASK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LAYER_MASK, GimpLayerMaskClass))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_MASK (obj)
define|#
directive|define
name|GIMP_IS_LAYER_MASK
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_LAYER_MASK))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_MASK_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LAYER_MASK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LAYER_MASK))
end_define

begin_typedef
DECL|typedef|GimpLayerClass
typedef|typedef
name|struct
name|_GimpLayerClass
name|GimpLayerClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerMaskClass
typedef|typedef
name|struct
name|_GimpLayerMaskClass
name|GimpLayerMaskClass
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
DECL|member|linked
name|gboolean
name|linked
decl_stmt|;
comment|/*  control linkage                */
DECL|member|preserve_trans
name|gboolean
name|preserve_trans
decl_stmt|;
comment|/*  preserve transparency          */
DECL|member|mask
name|LayerMask
modifier|*
name|mask
decl_stmt|;
comment|/*  possible layer mask            */
DECL|member|apply_mask
name|gint
name|apply_mask
decl_stmt|;
comment|/*  controls mask application      */
DECL|member|edit_mask
name|gboolean
name|edit_mask
decl_stmt|;
comment|/*  edit mask or layer?            */
DECL|member|show_mask
name|gboolean
name|show_mask
decl_stmt|;
comment|/*  show mask or layer?            */
DECL|member|opacity
name|gint
name|opacity
decl_stmt|;
comment|/*  layer opacity                  */
DECL|member|mode
name|LayerModeEffects
name|mode
decl_stmt|;
comment|/*  layer combination mode         */
comment|/*  Floating selections  */
struct|struct
DECL|struct|__anon2795c36f0108
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
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLayerMask
struct|struct
name|_GimpLayerMask
block|{
DECL|member|parent_instance
name|GimpChannel
name|parent_instance
decl_stmt|;
DECL|member|layer
name|Layer
modifier|*
name|layer
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLayerMaskClass
struct|struct
name|_GimpLayerMaskClass
block|{
DECL|member|parent_class
name|GimpChannelClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Special undo types  */
end_comment

begin_struct
DECL|struct|_layer_undo
struct|struct
name|_layer_undo
block|{
DECL|member|layer
name|Layer
modifier|*
name|layer
decl_stmt|;
comment|/*  the actual layer          */
DECL|member|prev_position
name|gint
name|prev_position
decl_stmt|;
comment|/*  former position in list   */
DECL|member|prev_layer
name|Layer
modifier|*
name|prev_layer
decl_stmt|;
comment|/*  previous active layer     */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_layer_mask_undo
struct|struct
name|_layer_mask_undo
block|{
DECL|member|layer
name|Layer
modifier|*
name|layer
decl_stmt|;
comment|/*  the layer                 */
DECL|member|apply_mask
name|gboolean
name|apply_mask
decl_stmt|;
comment|/*  apply mask?               */
DECL|member|edit_mask
name|gboolean
name|edit_mask
decl_stmt|;
comment|/*  edit mask or layer?       */
DECL|member|show_mask
name|gboolean
name|show_mask
decl_stmt|;
comment|/*  show the mask?            */
DECL|member|mask
name|LayerMask
modifier|*
name|mask
decl_stmt|;
comment|/*  the layer mask            */
DECL|member|mode
name|gint
name|mode
decl_stmt|;
comment|/*  the application mode      */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_fs_to_layer_undo
struct|struct
name|_fs_to_layer_undo
block|{
DECL|member|layer
name|Layer
modifier|*
name|layer
decl_stmt|;
comment|/*  the layer                 */
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/*  drawable of floating sel  */
block|}
struct|;
end_struct

begin_comment
comment|/*  function declarations  */
end_comment

begin_function_decl
name|GtkType
name|gimp_layer_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|layer_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|gint
name|opacity
parameter_list|,
name|LayerModeEffects
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|layer_copy
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|layer_new_from_tiles
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpImageType
name|layer_type
parameter_list|,
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|opacity
parameter_list|,
name|LayerModeEffects
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|layer_check_scaling
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|layer_create_mask
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|AddMaskType
name|add_mask_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|layer_add_mask
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|LayerMask
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_delete
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_apply_mask
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|MaskApplyMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_translate
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_add_alpha
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|layer_scale_by_factors
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|gdouble
name|w_factor
parameter_list|,
name|gdouble
name|h_factor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_scale
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gboolean
name|local_origin
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_resize
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_resize_to_image
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|BoundSeg
modifier|*
name|layer_boundary
parameter_list|(
name|Layer
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
name|void
name|layer_invalidate_boundary
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|layer_pick_correlate
parameter_list|(
name|Layer
modifier|*
name|layer
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
name|GtkType
name|gimp_layer_mask_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|layer_mask_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|layer_mask_copy
parameter_list|(
name|LayerMask
modifier|*
name|layer_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_mask_delete
parameter_list|(
name|LayerMask
modifier|*
name|layer_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|layer_mask_ref
parameter_list|(
name|LayerMask
modifier|*
name|layer_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_mask_unref
parameter_list|(
name|LayerMask
modifier|*
name|layer_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_mask_set_layer
parameter_list|(
name|LayerMask
modifier|*
name|layer_mask
parameter_list|,
name|Layer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|layer_mask_get_layer
parameter_list|(
name|LayerMask
modifier|*
name|layer_mask
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  access functions  */
end_comment

begin_function_decl
name|void
name|layer_set_name
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|layer_get_name
parameter_list|(
specifier|const
name|Layer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|layer_data
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|layer_get_mask
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|layer_has_alpha
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|layer_is_floating_sel
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|layer_linked
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|layer_preview
parameter_list|(
name|Layer
modifier|*
name|layer
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
name|TempBuf
modifier|*
name|layer_mask_preview
parameter_list|(
name|Layer
modifier|*
name|layer
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
name|layer_invalidate_previews
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tattoo
name|layer_get_tattoo
parameter_list|(
specifier|const
name|Layer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_set_tattoo
parameter_list|(
name|Layer
modifier|*
name|layer
parameter_list|,
name|Tattoo
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|gimp_drawable_layer
define|#
directive|define
name|gimp_drawable_layer
value|GIMP_IS_LAYER
end_define

begin_define
DECL|macro|gimp_drawable_layer_mask
define|#
directive|define
name|gimp_drawable_layer_mask
value|GIMP_IS_LAYER_MASK
end_define

begin_function_decl
name|void
name|channel_layer_alpha
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|Layer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  from channel.c  */
end_comment

begin_function_decl
name|void
name|channel_layer_mask
parameter_list|(
name|Channel
modifier|*
name|mask
parameter_list|,
name|Layer
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
comment|/* __LAYER_H__ */
end_comment

end_unit

