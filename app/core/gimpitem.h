begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ITEM_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ITEM_H__
define|#
directive|define
name|__GIMP_ITEM_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_ITEM
define|#
directive|define
name|GIMP_TYPE_ITEM
value|(gimp_item_get_type ())
end_define

begin_define
DECL|macro|GIMP_ITEM (obj)
define|#
directive|define
name|GIMP_ITEM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ITEM, GimpItem))
end_define

begin_define
DECL|macro|GIMP_ITEM_CLASS (klass)
define|#
directive|define
name|GIMP_ITEM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ITEM, GimpItemClass))
end_define

begin_define
DECL|macro|GIMP_IS_ITEM (obj)
define|#
directive|define
name|GIMP_IS_ITEM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ITEM))
end_define

begin_define
DECL|macro|GIMP_IS_ITEM_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ITEM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ITEM))
end_define

begin_define
DECL|macro|GIMP_ITEM_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ITEM_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ITEM, GimpItemClass))
end_define

begin_typedef
DECL|typedef|GimpItemClass
typedef|typedef
name|struct
name|_GimpItemClass
name|GimpItemClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpItem
struct|struct
name|_GimpItem
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
DECL|member|ID
name|gint
name|ID
decl_stmt|;
comment|/*  provides a unique ID     */
DECL|member|tattoo
name|guint32
name|tattoo
decl_stmt|;
comment|/*  provides a permanent ID  */
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
comment|/*  gimage owner             */
DECL|member|parasites
name|GimpParasiteList
modifier|*
name|parasites
decl_stmt|;
comment|/*  Plug-in parasite data    */
DECL|member|width
DECL|member|height
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
comment|/*  size in pixels           */
DECL|member|offset_x
DECL|member|offset_y
name|gint
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
comment|/*  pixel offset in image    */
DECL|member|visible
name|gboolean
name|visible
decl_stmt|;
comment|/*  control visibility       */
DECL|member|linked
name|gboolean
name|linked
decl_stmt|;
comment|/*  control linkage          */
DECL|member|floating
name|gboolean
name|floating
decl_stmt|;
comment|/*  added to an image?       */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpItemClass
struct|struct
name|_GimpItemClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|removed
name|void
function_decl|(
modifier|*
name|removed
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
DECL|member|visibility_changed
name|void
function_decl|(
modifier|*
name|visibility_changed
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
DECL|member|linked_changed
name|void
function_decl|(
modifier|*
name|linked_changed
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
comment|/*  virtual functions  */
DECL|member|duplicate
name|GimpItem
modifier|*
function_decl|(
modifier|*
name|duplicate
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GType
name|new_type
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
function_decl|;
DECL|member|convert
name|GimpItem
modifier|*
function_decl|(
modifier|*
name|convert
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
name|GType
name|new_type
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
function_decl|;
DECL|member|rename
name|void
function_decl|(
modifier|*
name|rename
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
DECL|member|translate
name|void
function_decl|(
modifier|*
name|translate
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
DECL|member|scale
name|void
function_decl|(
modifier|*
name|scale
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
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
parameter_list|)
function_decl|;
DECL|member|resize
name|void
function_decl|(
modifier|*
name|resize
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
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
name|GimpItem
modifier|*
name|item
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
name|GimpItem
modifier|*
name|item
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
name|GimpItem
modifier|*
name|item
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
name|gboolean
name|clip_result
parameter_list|,
name|GimpProgressFunc
name|progress_callback
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
function_decl|;
DECL|member|stroke
name|gboolean
function_decl|(
modifier|*
name|stroke
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpObject
modifier|*
name|stroke_desc
parameter_list|,
name|gboolean
name|use_default_values
parameter_list|)
function_decl|;
DECL|member|default_name
specifier|const
name|gchar
modifier|*
name|default_name
decl_stmt|;
DECL|member|rename_desc
specifier|const
name|gchar
modifier|*
name|rename_desc
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_item_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
name|gimp_item_is_floating
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_sink
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_removed
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_configure
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpImage
modifier|*
name|gimage
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
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|gimp_item_duplicate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GType
name|new_type
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|gimp_item_convert
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
name|GType
name|new_type
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_rename
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_item_width
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_item_height
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_offsets
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
modifier|*
name|offset_x
parameter_list|,
name|gint
modifier|*
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_translate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_check_scaling
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
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
name|void
name|gimp_item_scale
parameter_list|(
name|GimpItem
modifier|*
name|item
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
name|interpolation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_scale_by_factors
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gdouble
name|w_factor
parameter_list|,
name|gdouble
name|h_factor
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_scale_by_origin
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|local_origin
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_resize
parameter_list|(
name|GimpItem
modifier|*
name|item
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
end_function_decl

begin_function_decl
name|void
name|gimp_item_resize_to_image
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_flip
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|,
name|gdouble
name|axis
parameter_list|,
name|gboolean
name|flip_result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_rotate
parameter_list|(
name|GimpItem
modifier|*
name|item
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
name|flip_result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_transform
parameter_list|(
name|GimpItem
modifier|*
name|item
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
name|gboolean
name|clip_result
parameter_list|,
name|GimpProgressFunc
name|progress_callback
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_stroke
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpObject
modifier|*
name|stroke_desc
parameter_list|,
name|gboolean
name|use_default_values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_item_get_ID
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|gimp_item_get_by_ID
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
name|GimpTattoo
name|gimp_item_get_tattoo
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_set_tattoo
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpTattoo
name|tattoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_item_get_image
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_set_image
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_parasite_attach
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_parasite_detach
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpParasite
modifier|*
name|gimp_item_parasite_find
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
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
name|gimp_item_parasite_list
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
modifier|*
name|count
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_get_visible
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_set_visible
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gboolean
name|visible
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_set_linked
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gboolean
name|linked
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_get_linked
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ITEM_H__ */
end_comment

end_unit

