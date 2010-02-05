begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_GUIDES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_GUIDES_H__
define|#
directive|define
name|__GIMP_IMAGE_GUIDES_H__
end_define

begin_comment
comment|/*  public guide adding API  */
end_comment

begin_function_decl
name|GimpGuide
modifier|*
name|gimp_image_add_hguide
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|GimpGuide
modifier|*
name|gimp_image_add_vguide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|position
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  internal guide adding API, does not check the guide's position and  *  is publically declared only to be used from undo  */
end_comment

begin_function_decl
name|void
name|gimp_image_add_guide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_remove_guide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_move_guide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpGuide
modifier|*
name|guide
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
name|GList
modifier|*
name|gimp_image_get_guides
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpGuide
modifier|*
name|gimp_image_get_guide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|guint32
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpGuide
modifier|*
name|gimp_image_get_next_guide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|guint32
name|id
parameter_list|,
name|gboolean
modifier|*
name|guide_found
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpGuide
modifier|*
name|gimp_image_find_guide
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|epsilon_x
parameter_list|,
name|gdouble
name|epsilon_y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_GUIDES_H__ */
end_comment

end_unit

