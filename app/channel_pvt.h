begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CHANNEL_PVT_H__
end_ifndef

begin_define
DECL|macro|__CHANNEL_PVT_H__
define|#
directive|define
name|__CHANNEL_PVT_H__
end_define

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"boundary.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager.h"
end_include

begin_include
include|#
directive|include
file|"drawable_pvt.h"
end_include

begin_struct
DECL|struct|_GimpChannel
struct|struct
name|_GimpChannel
block|{
DECL|member|drawable
name|GimpDrawable
name|drawable
decl_stmt|;
DECL|member|col
name|guchar
name|col
index|[
literal|3
index|]
decl_stmt|;
comment|/*  RGB triplet for channel color  */
DECL|member|opacity
name|gint
name|opacity
decl_stmt|;
comment|/*  Channel opacity                */
DECL|member|show_masked
name|gboolean
name|show_masked
decl_stmt|;
comment|/*  Show masked areas--as          */
comment|/*  opposed to selected areas      */
comment|/*  Selection mask variables  */
DECL|member|boundary_known
name|gboolean
name|boundary_known
decl_stmt|;
comment|/*  is the current boundary valid  */
DECL|member|segs_in
name|BoundSeg
modifier|*
name|segs_in
decl_stmt|;
comment|/*  outline of selected region     */
DECL|member|segs_out
name|BoundSeg
modifier|*
name|segs_out
decl_stmt|;
comment|/*  outline of selected region     */
DECL|member|num_segs_in
name|gint
name|num_segs_in
decl_stmt|;
comment|/*  number of lines in boundary    */
DECL|member|num_segs_out
name|gint
name|num_segs_out
decl_stmt|;
comment|/*  number of lines in boundary    */
DECL|member|empty
name|gboolean
name|empty
decl_stmt|;
comment|/*  is the region empty?           */
DECL|member|bounds_known
name|gboolean
name|bounds_known
decl_stmt|;
comment|/*  recalculate the bounds?        */
DECL|member|x1
DECL|member|y1
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  coordinates for bounding box   */
DECL|member|x2
DECL|member|y2
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  lower right hand coordinate    */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpChannelClass
struct|struct
name|_GimpChannelClass
block|{
DECL|member|parent_class
name|GimpDrawableClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __CHANNEL_PVT_H__ */
end_comment

end_unit

