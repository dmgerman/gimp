begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
DECL|member|type
name|GimpImageType
name|type
decl_stmt|;
comment|/* type of drawable        */
DECL|member|tiles
name|TileManager
modifier|*
name|tiles
decl_stmt|;
comment|/* tiles for drawable data */
DECL|member|shadow
name|TileManager
modifier|*
name|shadow
decl_stmt|;
comment|/* shadow buffer tiles     */
DECL|member|source_node
name|GeglNode
modifier|*
name|source_node
decl_stmt|;
DECL|member|tile_source_node
name|GeglNode
modifier|*
name|tile_source_node
decl_stmt|;
DECL|member|fs_crop_node
name|GeglNode
modifier|*
name|fs_crop_node
decl_stmt|;
DECL|member|fs_opacity_node
name|GeglNode
modifier|*
name|fs_opacity_node
decl_stmt|;
DECL|member|fs_offset_node
name|GeglNode
modifier|*
name|fs_offset_node
decl_stmt|;
DECL|member|fs_mode_node
name|GeglNode
modifier|*
name|fs_mode_node
decl_stmt|;
DECL|member|mode_node
name|GeglNode
modifier|*
name|mode_node
decl_stmt|;
DECL|member|preview_cache
name|GSList
modifier|*
name|preview_cache
decl_stmt|;
comment|/* preview caches of the channel */
DECL|member|preview_valid
name|gboolean
name|preview_valid
decl_stmt|;
comment|/* is the preview valid?         */
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

