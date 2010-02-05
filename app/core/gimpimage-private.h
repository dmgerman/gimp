begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_PRIVATE_H__
define|#
directive|define
name|__GIMP_IMAGE_PRIVATE_H__
end_define

begin_typedef
DECL|typedef|GimpImageFlushAccumulator
typedef|typedef
name|struct
name|_GimpImageFlushAccumulator
name|GimpImageFlushAccumulator
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImageFlushAccumulator
struct|struct
name|_GimpImageFlushAccumulator
block|{
DECL|member|alpha_changed
name|gboolean
name|alpha_changed
decl_stmt|;
DECL|member|mask_changed
name|gboolean
name|mask_changed
decl_stmt|;
DECL|member|floating_selection_changed
name|gboolean
name|floating_selection_changed
decl_stmt|;
DECL|member|preview_invalidated
name|gboolean
name|preview_invalidated
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpImagePrivate
typedef|typedef
name|struct
name|_GimpImagePrivate
name|GimpImagePrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImagePrivate
struct|struct
name|_GimpImagePrivate
block|{
DECL|member|ID
name|gint
name|ID
decl_stmt|;
comment|/*  provides a unique ID         */
DECL|member|load_proc
name|GimpPlugInProcedure
modifier|*
name|load_proc
decl_stmt|;
comment|/*  procedure used for loading   */
DECL|member|save_proc
name|GimpPlugInProcedure
modifier|*
name|save_proc
decl_stmt|;
comment|/*  last save procedure used     */
DECL|member|display_name
name|gchar
modifier|*
name|display_name
decl_stmt|;
comment|/*  display basename             */
DECL|member|width
name|gint
name|width
decl_stmt|;
comment|/*  width in pixels              */
DECL|member|height
name|gint
name|height
decl_stmt|;
comment|/*  height in pixels             */
DECL|member|xresolution
name|gdouble
name|xresolution
decl_stmt|;
comment|/*  image x-res, in dpi          */
DECL|member|yresolution
name|gdouble
name|yresolution
decl_stmt|;
comment|/*  image y-res, in dpi          */
DECL|member|resolution_unit
name|GimpUnit
name|resolution_unit
decl_stmt|;
comment|/*  resolution unit              */
DECL|member|base_type
name|GimpImageBaseType
name|base_type
decl_stmt|;
comment|/*  base gimp_image type         */
DECL|member|colormap
name|guchar
modifier|*
name|colormap
decl_stmt|;
comment|/*  colormap (for indexed)       */
DECL|member|n_colors
name|gint
name|n_colors
decl_stmt|;
comment|/*  # of colors (for indexed)    */
DECL|member|dirty
name|gint
name|dirty
decl_stmt|;
comment|/*  dirty flag -- # of ops       */
DECL|member|dirty_time
name|guint
name|dirty_time
decl_stmt|;
comment|/*  time when image became dirty */
DECL|member|export_dirty
name|gint
name|export_dirty
decl_stmt|;
comment|/*  'dirty' but for export       */
DECL|member|undo_freeze_count
name|gint
name|undo_freeze_count
decl_stmt|;
comment|/*  counts the _freeze's         */
DECL|member|instance_count
name|gint
name|instance_count
decl_stmt|;
comment|/*  number of instances          */
DECL|member|disp_count
name|gint
name|disp_count
decl_stmt|;
comment|/*  number of displays           */
DECL|member|tattoo_state
name|GimpTattoo
name|tattoo_state
decl_stmt|;
comment|/*  the last used tattoo         */
DECL|member|projection
name|GimpProjection
modifier|*
name|projection
decl_stmt|;
comment|/*  projection layers& channels */
DECL|member|graph
name|GeglNode
modifier|*
name|graph
decl_stmt|;
comment|/*  GEGL projection graph        */
DECL|member|guides
name|GList
modifier|*
name|guides
decl_stmt|;
comment|/*  guides                       */
DECL|member|grid
name|GimpGrid
modifier|*
name|grid
decl_stmt|;
comment|/*  grid                         */
DECL|member|sample_points
name|GList
modifier|*
name|sample_points
decl_stmt|;
comment|/*  color sample points          */
comment|/*  Layer/Channel attributes  */
DECL|member|layers
name|GimpContainer
modifier|*
name|layers
decl_stmt|;
comment|/*  the list of layers           */
DECL|member|channels
name|GimpContainer
modifier|*
name|channels
decl_stmt|;
comment|/*  the list of masks            */
DECL|member|vectors
name|GimpContainer
modifier|*
name|vectors
decl_stmt|;
comment|/*  the list of vectors          */
DECL|member|layer_stack
name|GSList
modifier|*
name|layer_stack
decl_stmt|;
comment|/*  the layers in MRU order      */
DECL|member|layer_alpha_handler
name|GQuark
name|layer_alpha_handler
decl_stmt|;
DECL|member|channel_name_changed_handler
name|GQuark
name|channel_name_changed_handler
decl_stmt|;
DECL|member|channel_color_changed_handler
name|GQuark
name|channel_color_changed_handler
decl_stmt|;
DECL|member|active_layer
name|GimpLayer
modifier|*
name|active_layer
decl_stmt|;
comment|/*  the active layer             */
DECL|member|active_channel
name|GimpChannel
modifier|*
name|active_channel
decl_stmt|;
comment|/*  the active channel           */
DECL|member|active_vectors
name|GimpVectors
modifier|*
name|active_vectors
decl_stmt|;
comment|/*  the active vectors           */
DECL|member|floating_sel
name|GimpLayer
modifier|*
name|floating_sel
decl_stmt|;
comment|/*  the FS layer                 */
DECL|member|selection_mask
name|GimpChannel
modifier|*
name|selection_mask
decl_stmt|;
comment|/*  the selection mask channel   */
DECL|member|parasites
name|GimpParasiteList
modifier|*
name|parasites
decl_stmt|;
comment|/*  Plug-in parasite data        */
DECL|member|visible
name|gboolean
name|visible
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
comment|/*  visible channels             */
DECL|member|active
name|gboolean
name|active
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
comment|/*  active channels              */
DECL|member|quick_mask_state
name|gboolean
name|quick_mask_state
decl_stmt|;
comment|/*  TRUE if quick mask is on       */
DECL|member|quick_mask_inverted
name|gboolean
name|quick_mask_inverted
decl_stmt|;
comment|/*  TRUE if quick mask is inverted */
DECL|member|quick_mask_color
name|GimpRGB
name|quick_mask_color
decl_stmt|;
comment|/*  rgba triplet of the color      */
comment|/*  Undo apparatus  */
DECL|member|undo_stack
name|GimpUndoStack
modifier|*
name|undo_stack
decl_stmt|;
comment|/*  stack for undo operations    */
DECL|member|redo_stack
name|GimpUndoStack
modifier|*
name|redo_stack
decl_stmt|;
comment|/*  stack for redo operations    */
DECL|member|group_count
name|gint
name|group_count
decl_stmt|;
comment|/*  nested undo groups           */
DECL|member|pushing_undo_group
name|GimpUndoType
name|pushing_undo_group
decl_stmt|;
comment|/*  undo group status flag       */
comment|/*  Preview  */
DECL|member|preview
name|TempBuf
modifier|*
name|preview
decl_stmt|;
comment|/*  the projection preview       */
comment|/*  Signal emmision accumulator  */
DECL|member|flush_accum
name|GimpImageFlushAccumulator
name|flush_accum
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_IMAGE_GET_PRIVATE (image)
define|#
directive|define
name|GIMP_IMAGE_GET_PRIVATE
parameter_list|(
name|image
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (image, \                                      GIMP_TYPE_IMAGE, \                                      GimpImagePrivate)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_PRIVATE_H__ */
end_comment

end_unit

