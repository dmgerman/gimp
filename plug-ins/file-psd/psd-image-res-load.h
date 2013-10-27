begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GIMP PSD Plug-in  * Copyright 2007 by John Marshall  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PSD_IMAGE_RES_LOAD_H__
end_ifndef

begin_define
DECL|macro|__PSD_IMAGE_RES_LOAD_H__
define|#
directive|define
name|__PSD_IMAGE_RES_LOAD_H__
end_define

begin_function_decl
name|gint
name|get_image_resource_header
parameter_list|(
name|PSDimageres
modifier|*
name|res_a
parameter_list|,
name|FILE
modifier|*
name|f
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|load_image_resource
parameter_list|(
name|PSDimageres
modifier|*
name|res_a
parameter_list|,
specifier|const
name|gint32
name|image_id
parameter_list|,
name|PSDimage
modifier|*
name|img_a
parameter_list|,
name|FILE
modifier|*
name|f
parameter_list|,
name|gboolean
modifier|*
name|resolution_loaded
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|load_thumbnail_resource
parameter_list|(
name|PSDimageres
modifier|*
name|res_a
parameter_list|,
specifier|const
name|gint32
name|image_id
parameter_list|,
name|FILE
modifier|*
name|f
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PSD_IMAGE_RES_LOAD_H__ */
end_comment

end_unit

