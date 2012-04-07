begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattisbvf  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_H__
define|#
directive|define
name|__GIMP_IMAGE_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_define
DECL|macro|GIMP_IMAGE_ACTIVE_PARENT
define|#
directive|define
name|GIMP_IMAGE_ACTIVE_PARENT
value|((gpointer) 1)
end_define

begin_define
DECL|macro|GIMP_TYPE_IMAGE
define|#
directive|define
name|GIMP_TYPE_IMAGE
value|(gimp_image_get_type ())
end_define

begin_define
DECL|macro|GIMP_IMAGE (obj)
define|#
directive|define
name|GIMP_IMAGE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_IMAGE, GimpImage))
end_define

begin_define
DECL|macro|GIMP_IMAGE_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_IMAGE, GimpImageClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE (obj)
define|#
directive|define
name|GIMP_IS_IMAGE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_IMAGE))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGE))
end_define

begin_define
DECL|macro|GIMP_IMAGE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_IMAGE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_IMAGE, GimpImageClass))
end_define

begin_typedef
DECL|typedef|GimpImageClass
typedef|typedef
name|struct
name|_GimpImageClass
name|GimpImageClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImage
struct|struct
name|_GimpImage
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
comment|/*  the GIMP the image belongs to  */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpImageClass
struct|struct
name|_GimpImageClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|mode_changed
name|void
function_decl|(
modifier|*
name|mode_changed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
DECL|member|alpha_changed
name|void
function_decl|(
modifier|*
name|alpha_changed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
DECL|member|floating_selection_changed
name|void
function_decl|(
modifier|*
name|floating_selection_changed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
DECL|member|active_layer_changed
name|void
function_decl|(
modifier|*
name|active_layer_changed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
DECL|member|active_channel_changed
name|void
function_decl|(
modifier|*
name|active_channel_changed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
DECL|member|active_vectors_changed
name|void
function_decl|(
modifier|*
name|active_vectors_changed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
DECL|member|component_visibility_changed
name|void
function_decl|(
modifier|*
name|component_visibility_changed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|)
function_decl|;
DECL|member|component_active_changed
name|void
function_decl|(
modifier|*
name|component_active_changed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|)
function_decl|;
DECL|member|mask_changed
name|void
function_decl|(
modifier|*
name|mask_changed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
DECL|member|resolution_changed
name|void
function_decl|(
modifier|*
name|resolution_changed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
DECL|member|size_changed_detailed
name|void
function_decl|(
modifier|*
name|size_changed_detailed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|previous_origin_x
parameter_list|,
name|gint
name|previous_origin_y
parameter_list|,
name|gint
name|previous_width
parameter_list|,
name|gint
name|previous_height
parameter_list|)
function_decl|;
DECL|member|unit_changed
name|void
function_decl|(
modifier|*
name|unit_changed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
DECL|member|quick_mask_changed
name|void
function_decl|(
modifier|*
name|quick_mask_changed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
DECL|member|selection_invalidate
name|void
function_decl|(
modifier|*
name|selection_invalidate
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
DECL|member|clean
name|void
function_decl|(
modifier|*
name|clean
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDirtyMask
name|dirty_mask
parameter_list|)
function_decl|;
DECL|member|dirty
name|void
function_decl|(
modifier|*
name|dirty
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDirtyMask
name|dirty_mask
parameter_list|)
function_decl|;
DECL|member|saved
name|void
function_decl|(
modifier|*
name|saved
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
DECL|member|exported
name|void
function_decl|(
modifier|*
name|exported
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
DECL|member|guide_added
name|void
function_decl|(
modifier|*
name|guide_added
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
DECL|member|guide_removed
name|void
function_decl|(
modifier|*
name|guide_removed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
DECL|member|guide_moved
name|void
function_decl|(
modifier|*
name|guide_moved
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
DECL|member|sample_point_added
name|void
function_decl|(
modifier|*
name|sample_point_added
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|)
function_decl|;
DECL|member|sample_point_removed
name|void
function_decl|(
modifier|*
name|sample_point_removed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|)
function_decl|;
DECL|member|sample_point_moved
name|void
function_decl|(
modifier|*
name|sample_point_moved
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|)
function_decl|;
DECL|member|parasite_attached
name|void
function_decl|(
modifier|*
name|parasite_attached
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
DECL|member|parasite_detached
name|void
function_decl|(
modifier|*
name|parasite_detached
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
DECL|member|colormap_changed
name|void
function_decl|(
modifier|*
name|colormap_changed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|color_index
parameter_list|)
function_decl|;
DECL|member|undo_event
name|void
function_decl|(
modifier|*
name|undo_event
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUndoEvent
name|event
parameter_list|,
name|GimpUndo
modifier|*
name|undo
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_image_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpImage
modifier|*
name|gimp_image_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpImageBaseType
name|base_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageBaseType
name|gimp_image_base_type
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|CombinationMode
name|gimp_image_get_combination_mode
parameter_list|(
name|GimpImageType
name|dest_type
parameter_list|,
name|gint
name|src_bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_image_get_format
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImageType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_image_get_format_with_alpha
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImageType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_image_get_format_without_alpha
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImageType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_image_get_layer_format
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|with_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_ID
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_image_get_by_ID
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_image_get_uri
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_image_get_uri_or_untitled
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_image_get_imported_uri
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_image_get_exported_uri
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_image_get_save_a_copy_uri
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_image_get_any_uri
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_uri
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_imported_uri
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_exported_uri
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_save_a_copy_uri
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_filename
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_image_get_filename
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_image_get_display_name
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_load_proc
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPlugInProcedure
modifier|*
name|gimp_image_get_load_proc
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_save_proc
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPlugInProcedure
modifier|*
name|gimp_image_get_save_proc
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_saved
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_exported
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_resolution
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|yres
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_get_resolution
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
modifier|*
name|xres
parameter_list|,
name|gdouble
modifier|*
name|yres
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_resolution_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_unit
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUnit
name|gimp_image_get_unit
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_unit_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_width
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_height
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_has_alpha
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_is_empty
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_floating_selection
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpLayer
modifier|*
name|floating_sel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_image_get_floating_selection
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_floating_selection_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_image_get_mask
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_mask_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  image components  */
end_comment

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_image_get_component_format
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_component_index
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_component_active
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|type
parameter_list|,
name|gboolean
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_get_component_active
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_get_active_array
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
modifier|*
name|components
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_component_visible
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|type
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_get_component_visible
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_get_visible_array
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
modifier|*
name|components
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  emitting image signals  */
end_comment

begin_function_decl
name|void
name|gimp_image_mode_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_alpha_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_invalidate
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|gimp_image_guide_added
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_guide_removed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_guide_moved
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_sample_point_added
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_sample_point_removed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_sample_point_moved
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_colormap_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|col
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_selection_invalidate
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_quick_mask_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_size_changed_detailed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|previous_origin_x
parameter_list|,
name|gint
name|previous_origin_y
parameter_list|,
name|gint
name|previous_width
parameter_list|,
name|gint
name|previous_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_undo_event
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUndoEvent
name|event
parameter_list|,
name|GimpUndo
modifier|*
name|undo
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  dirty counters  */
end_comment

begin_function_decl
name|gint
name|gimp_image_dirty
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDirtyMask
name|dirty_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_clean
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDirtyMask
name|dirty_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_clean_all
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_export_clean_all
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_is_dirty
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_is_export_dirty
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_dirty_time
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  flush this image's displays  */
end_comment

begin_function_decl
name|void
name|gimp_image_flush
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  display / instance counters  */
end_comment

begin_function_decl
name|gint
name|gimp_image_get_display_count
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_inc_display_count
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_dec_display_count
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_instance_count
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_inc_instance_count
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  parasites  */
end_comment

begin_function_decl
specifier|const
name|GimpParasite
modifier|*
name|gimp_image_parasite_find
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gimp_image_parasite_list
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
modifier|*
name|count
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_parasite_attach
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_parasite_detach
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  tattoos  */
end_comment

begin_function_decl
name|GimpTattoo
name|gimp_image_get_new_tattoo
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_tattoo_state
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpTattoo
name|val
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpTattoo
name|gimp_image_get_tattoo_state
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  projection  */
end_comment

begin_function_decl
name|GimpProjection
modifier|*
name|gimp_image_get_projection
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  layers / channels / vectors  */
end_comment

begin_function_decl
name|GimpItemTree
modifier|*
name|gimp_image_get_layer_tree
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItemTree
modifier|*
name|gimp_image_get_channel_tree
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItemTree
modifier|*
name|gimp_image_get_vectors_tree
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_image_get_layers
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_image_get_channels
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_image_get_vectors
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_n_layers
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_n_channels
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_n_vectors
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_image_get_layer_iter
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_image_get_channel_iter
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_image_get_vectors_iter
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_image_get_layer_list
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_image_get_channel_list
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_image_get_vectors_list
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDrawable
modifier|*
name|gimp_image_get_active_drawable
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_image_get_active_layer
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_image_get_active_channel
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVectors
modifier|*
name|gimp_image_get_active_vectors
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_image_set_active_layer
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_image_set_active_channel
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_image_unset_active_channel
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVectors
modifier|*
name|gimp_image_set_active_vectors
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_image_get_layer_by_tattoo
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpTattoo
name|tattoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_image_get_channel_by_tattoo
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpTattoo
name|tattoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVectors
modifier|*
name|gimp_image_get_vectors_by_tattoo
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpTattoo
name|tattoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_image_get_layer_by_name
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_image_get_channel_by_name
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVectors
modifier|*
name|gimp_image_get_vectors_by_name
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_reorder_item
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpItem
modifier|*
name|new_parent
parameter_list|,
name|gint
name|new_index
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_raise_item
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_raise_item_to_top
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_lower_item
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_lower_item_to_bottom
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_add_layer
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayer
modifier|*
name|parent
parameter_list|,
name|gint
name|position
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_remove_layer
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
name|GimpLayer
modifier|*
name|new_active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_add_layers
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GList
modifier|*
name|layers
parameter_list|,
name|GimpLayer
modifier|*
name|parent
parameter_list|,
name|gint
name|position
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
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_add_channel
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|GimpChannel
modifier|*
name|parent
parameter_list|,
name|gint
name|position
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_remove_channel
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
name|GimpChannel
modifier|*
name|new_active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_add_vectors
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpVectors
modifier|*
name|parent
parameter_list|,
name|gint
name|position
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_remove_vectors
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
name|GimpVectors
modifier|*
name|new_active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_coords_in_active_pickable
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gboolean
name|selected_only
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_invalidate_previews
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_image_get_string_untitled
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_H__ */
end_comment

end_unit

