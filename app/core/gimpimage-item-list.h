begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_ITEM_LIST_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_ITEM_LIST_H__
define|#
directive|define
name|__GIMP_IMAGE_ITEM_LIST_H__
end_define

begin_function_decl
name|gboolean
name|gimp_image_item_list_bounds
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GList
modifier|*
name|list
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
name|void
name|gimp_image_item_list_translate
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GList
modifier|*
name|list
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
name|void
name|gimp_image_item_list_flip
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GList
modifier|*
name|list
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
end_function_decl

begin_function_decl
name|void
name|gimp_image_item_list_rotate
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GList
modifier|*
name|list
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
end_function_decl

begin_function_decl
name|void
name|gimp_image_item_list_transform
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GList
modifier|*
name|list
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
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_image_item_list_get_list
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpItemTypeMask
name|type
parameter_list|,
name|GimpItemSet
name|set
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_image_item_list_filter
parameter_list|(
name|GList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_ITEM_LIST_H__ */
end_comment

end_unit

