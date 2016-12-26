begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_PRIVATE_H__
define|#
directive|define
name|__GIMP_BRUSH_PRIVATE_H__
end_define

begin_struct
DECL|struct|_GimpBrushPrivate
struct|struct
name|_GimpBrushPrivate
block|{
DECL|member|mask
name|GimpTempBuf
modifier|*
name|mask
decl_stmt|;
comment|/*  the actual mask                    */
DECL|member|blured_mask
name|GimpTempBuf
modifier|*
name|blured_mask
decl_stmt|;
comment|/*  blured actual mask cached          */
DECL|member|pixmap
name|GimpTempBuf
modifier|*
name|pixmap
decl_stmt|;
comment|/*  optional pixmap data               */
DECL|member|blured_pixmap
name|GimpTempBuf
modifier|*
name|blured_pixmap
decl_stmt|;
comment|/*  optional pixmap data blured cache  */
DECL|member|blur_hardness
name|gdouble
name|blur_hardness
decl_stmt|;
DECL|member|spacing
name|gint
name|spacing
decl_stmt|;
comment|/*  brush's spacing                */
DECL|member|x_axis
name|GimpVector2
name|x_axis
decl_stmt|;
comment|/*  for calculating brush spacing  */
DECL|member|y_axis
name|GimpVector2
name|y_axis
decl_stmt|;
comment|/*  for calculating brush spacing  */
DECL|member|use_count
name|gint
name|use_count
decl_stmt|;
comment|/*  for keeping the caches alive   */
DECL|member|mask_cache
name|GimpBrushCache
modifier|*
name|mask_cache
decl_stmt|;
DECL|member|pixmap_cache
name|GimpBrushCache
modifier|*
name|pixmap_cache
decl_stmt|;
DECL|member|boundary_cache
name|GimpBrushCache
modifier|*
name|boundary_cache
decl_stmt|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_BRUSH_PRIVATE_H__ */
end_comment

end_unit

