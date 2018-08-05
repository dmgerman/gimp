begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
comment|/*  layer opacity                     */
DECL|member|mode
name|GimpLayerMode
name|mode
decl_stmt|;
comment|/*  layer combination mode            */
DECL|member|blend_space
name|GimpLayerColorSpace
name|blend_space
decl_stmt|;
comment|/*  layer blend space                 */
DECL|member|composite_space
name|GimpLayerColorSpace
name|composite_space
decl_stmt|;
comment|/*  layer composite space             */
DECL|member|composite_mode
name|GimpLayerCompositeMode
name|composite_mode
decl_stmt|;
comment|/*  layer composite mode              */
DECL|member|effective_mode
name|GimpLayerMode
name|effective_mode
decl_stmt|;
comment|/*  layer effective combination mode  */
DECL|member|effective_blend_space
name|GimpLayerColorSpace
name|effective_blend_space
decl_stmt|;
comment|/*  layer effective blend space       */
DECL|member|effective_composite_space
name|GimpLayerColorSpace
name|effective_composite_space
decl_stmt|;
comment|/*  layer effective composite space   */
DECL|member|effective_composite_mode
name|GimpLayerCompositeMode
name|effective_composite_mode
decl_stmt|;
comment|/*  layer effective composite mode    */
DECL|member|excludes_backdrop
name|gboolean
name|excludes_backdrop
decl_stmt|;
comment|/*  layer clips backdrop              */
DECL|member|lock_alpha
name|gboolean
name|lock_alpha
decl_stmt|;
comment|/*  lock the alpha channel            */
DECL|member|mask
name|GimpLayerMask
modifier|*
name|mask
decl_stmt|;
comment|/*  possible layer mask               */
DECL|member|apply_mask
name|gboolean
name|apply_mask
decl_stmt|;
comment|/*  controls mask application         */
DECL|member|edit_mask
name|gboolean
name|edit_mask
decl_stmt|;
comment|/*  edit mask or layer?               */
DECL|member|show_mask
name|gboolean
name|show_mask
decl_stmt|;
comment|/*  show mask or layer?               */
DECL|member|move_stack
name|GSList
modifier|*
name|move_stack
decl_stmt|;
comment|/*  ancestors affected by move        */
DECL|member|layer_offset_node
name|GeglNode
modifier|*
name|layer_offset_node
decl_stmt|;
DECL|member|mask_offset_node
name|GeglNode
modifier|*
name|mask_offset_node
decl_stmt|;
comment|/*  Floating selections  */
struct|struct
DECL|struct|__anon2ab4a3220108
block|{
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/*  floating sel is attached to    */
DECL|member|boundary_known
name|gboolean
name|boundary_known
decl_stmt|;
comment|/*  is the current boundary valid  */
DECL|member|segs
name|GimpBoundSeg
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
comment|/*  signals  */
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
DECL|member|blend_space_changed
name|void
function_decl|(
modifier|*
name|blend_space_changed
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
DECL|member|composite_space_changed
name|void
function_decl|(
modifier|*
name|composite_space_changed
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
DECL|member|composite_mode_changed
name|void
function_decl|(
modifier|*
name|composite_mode_changed
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
DECL|member|effective_mode_changed
name|void
function_decl|(
modifier|*
name|effective_mode_changed
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
DECL|member|excludes_backdrop_changed
name|void
function_decl|(
modifier|*
name|excludes_backdrop_changed
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
DECL|member|apply_mask_changed
name|void
function_decl|(
modifier|*
name|apply_mask_changed
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
DECL|member|edit_mask_changed
name|void
function_decl|(
modifier|*
name|edit_mask_changed
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
DECL|member|show_mask_changed
name|void
function_decl|(
modifier|*
name|show_mask_changed
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
comment|/*  virtual functions  */
DECL|member|translate
name|void
function_decl|(
modifier|*
name|translate
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
function_decl|;
DECL|member|scale
name|void
function_decl|(
modifier|*
name|scale
function_decl|)
parameter_list|(
name|GimpLayer
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
name|new_offset_x
parameter_list|,
name|gint
name|new_offset_y
parameter_list|,
name|GimpInterpolationType
name|interpolation_type
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
DECL|member|resize
name|void
function_decl|(
modifier|*
name|resize
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpFillType
name|fill_type
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
function_decl|;
DECL|member|flip
name|void
function_decl|(
modifier|*
name|flip
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|,
name|gdouble
name|axis
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
DECL|member|rotate
name|void
function_decl|(
modifier|*
name|rotate
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpRotationType
name|rotate_type
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|,
name|gboolean
name|clip_result
parameter_list|)
function_decl|;
DECL|member|transform
name|void
function_decl|(
modifier|*
name|transform
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|GimpTransformDirection
name|direction
parameter_list|,
name|GimpInterpolationType
name|interpolation_type
parameter_list|,
name|GimpTransformResize
name|clip_result
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
DECL|member|convert_type
name|void
function_decl|(
modifier|*
name|convert_type
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
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
DECL|member|get_effective_mode
name|void
function_decl|(
modifier|*
name|get_effective_mode
function_decl|)
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerMode
modifier|*
name|mode
parameter_list|,
name|GimpLayerColorSpace
modifier|*
name|blend_space
parameter_list|,
name|GimpLayerColorSpace
modifier|*
name|composite_space
parameter_list|,
name|GimpLayerCompositeMode
modifier|*
name|composite_mode
parameter_list|)
function_decl|;
DECL|member|get_excludes_backdrop
name|gboolean
function_decl|(
modifier|*
name|get_excludes_backdrop
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
name|void
name|gimp_layer_fix_format_space
parameter_list|(
name|GimpLayer
modifier|*
name|layer
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
name|GimpLayer
modifier|*
name|gimp_layer_get_parent
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerMask
modifier|*
name|gimp_layer_get_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerMask
modifier|*
name|gimp_layer_create_mask
parameter_list|(
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
name|gimp_layer_set_apply_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|apply
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_get_apply_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_set_edit_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|edit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_get_edit_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_set_show_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|show
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_get_show_mask
parameter_list|(
name|GimpLayer
modifier|*
name|layer
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
name|gimp_layer_remove_alpha
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
parameter_list|,
name|GimpFillType
name|fill_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDrawable
modifier|*
name|gimp_layer_get_floating_sel_drawable
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_set_floating_sel_drawable
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_is_floating_sel
parameter_list|(
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
name|GimpLayerMode
name|mode
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerMode
name|gimp_layer_get_mode
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_set_blend_space
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerColorSpace
name|blend_space
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerColorSpace
name|gimp_layer_get_blend_space
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerColorSpace
name|gimp_layer_get_real_blend_space
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_set_composite_space
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerColorSpace
name|composite_space
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerColorSpace
name|gimp_layer_get_composite_space
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerColorSpace
name|gimp_layer_get_real_composite_space
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_set_composite_mode
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerCompositeMode
name|composite_mode
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerCompositeMode
name|gimp_layer_get_composite_mode
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerCompositeMode
name|gimp_layer_get_real_composite_mode
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_get_effective_mode
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerMode
modifier|*
name|mode
parameter_list|,
name|GimpLayerColorSpace
modifier|*
name|blend_space
parameter_list|,
name|GimpLayerColorSpace
modifier|*
name|composite_space
parameter_list|,
name|GimpLayerCompositeMode
modifier|*
name|composite_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_get_excludes_backdrop
parameter_list|(
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
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_can_lock_alpha
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  protected  */
end_comment

begin_function_decl
name|void
name|gimp_layer_update_effective_mode
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_update_excludes_backdrop
parameter_list|(
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

