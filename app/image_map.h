begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__IMAGE_MAP_H__
end_ifndef

begin_define
DECL|macro|__IMAGE_MAP_H__
define|#
directive|define
name|__IMAGE_MAP_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawableF.h"
end_include

begin_include
include|#
directive|include
file|"pixel_region.h"
end_include

begin_comment
comment|/*  Image map apply function  */
end_comment

begin_typedef
DECL|typedef|ImageMap
typedef|typedef
name|void
modifier|*
name|ImageMap
typedef|;
end_typedef

begin_typedef
DECL|typedef|ImageMapApplyFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ImageMapApplyFunc
function_decl|)
parameter_list|(
name|PixelRegion
modifier|*
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  Image Map functions  */
end_comment

begin_comment
comment|/*  Successive image map apply functions can be called, but eventually  *   MUST be followed with an image_map_commit or an image_map_abort call  *   The image map is no longer valid after a call to commit or abort.  */
end_comment

begin_function_decl
name|ImageMap
name|image_map_create
parameter_list|(
name|void
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|image_map_apply
parameter_list|(
name|ImageMap
parameter_list|,
name|ImageMapApplyFunc
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|image_map_commit
parameter_list|(
name|ImageMap
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|image_map_clear
parameter_list|(
name|ImageMap
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|image_map_abort
parameter_list|(
name|ImageMap
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|unsigned
name|char
modifier|*
name|image_map_get_color_at
parameter_list|(
name|ImageMap
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __IMAGE_MAP_H__ */
end_comment

end_unit

