begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_PRIVATE_H__
define|#
directive|define
name|__GIMP_DRAWABLE_PRIVATE_H__
end_define

begin_struct
DECL|struct|_GimpDrawablePrivate
struct|struct
name|_GimpDrawablePrivate
block|{
DECL|member|buffer
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
comment|/* buffer for drawable data */
DECL|member|shadow
name|GeglBuffer
modifier|*
name|shadow
decl_stmt|;
comment|/* shadow buffer            */
DECL|member|format_profile
name|GimpColorProfile
modifier|*
name|format_profile
decl_stmt|;
DECL|member|source_node
name|GeglNode
modifier|*
name|source_node
decl_stmt|;
DECL|member|buffer_source_node
name|GeglNode
modifier|*
name|buffer_source_node
decl_stmt|;
DECL|member|filter_stack
name|GimpContainer
modifier|*
name|filter_stack
decl_stmt|;
DECL|member|floating_selection
name|GimpLayer
modifier|*
name|floating_selection
decl_stmt|;
DECL|member|fs_filter
name|GimpFilter
modifier|*
name|fs_filter
decl_stmt|;
DECL|member|fs_crop_node
name|GeglNode
modifier|*
name|fs_crop_node
decl_stmt|;
DECL|member|fs_applicator
name|GimpApplicator
modifier|*
name|fs_applicator
decl_stmt|;
DECL|member|mode_node
name|GeglNode
modifier|*
name|mode_node
decl_stmt|;
DECL|member|paint_count
name|gint
name|paint_count
decl_stmt|;
DECL|member|paint_buffer
name|GeglBuffer
modifier|*
name|paint_buffer
decl_stmt|;
DECL|member|paint_copy_region
name|cairo_region_t
modifier|*
name|paint_copy_region
decl_stmt|;
DECL|member|paint_update_region
name|cairo_region_t
modifier|*
name|paint_update_region
decl_stmt|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DRAWABLE_PRIVATE_H__ */
end_comment

end_unit

