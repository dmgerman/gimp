begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__LAYER_PVT_H__
end_ifndef

begin_define
DECL|macro|__LAYER_PVT_H__
define|#
directive|define
name|__LAYER_PVT_H__
end_define

begin_include
include|#
directive|include
file|"layer.h"
end_include

begin_include
include|#
directive|include
file|"boundary.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"channel.h"
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

begin_include
include|#
directive|include
file|"channel_pvt.h"
end_include

begin_struct
DECL|struct|_GimpLayer
struct|struct
name|_GimpLayer
block|{
DECL|member|drawable
name|GimpDrawable
name|drawable
decl_stmt|;
DECL|member|linked
name|int
name|linked
decl_stmt|;
comment|/* control linkage */
DECL|member|preserve_trans
name|int
name|preserve_trans
decl_stmt|;
comment|/* preserve transparency */
DECL|member|mask
name|LayerMask
modifier|*
name|mask
decl_stmt|;
comment|/*  possible layer mask          */
DECL|member|apply_mask
name|int
name|apply_mask
decl_stmt|;
comment|/*  controls mask application    */
DECL|member|edit_mask
name|int
name|edit_mask
decl_stmt|;
comment|/*  edit mask or layer?          */
DECL|member|show_mask
name|int
name|show_mask
decl_stmt|;
comment|/*  show mask or layer?          */
DECL|member|opacity
name|int
name|opacity
decl_stmt|;
comment|/*  layer opacity                */
DECL|member|mode
name|int
name|mode
decl_stmt|;
comment|/*  layer combination mode       */
comment|/*  Floating selections  */
struct|struct
DECL|struct|__anon29e0924a0108
block|{
DECL|member|backing_store
name|TileManager
modifier|*
name|backing_store
decl_stmt|;
comment|/*  for obscured regions         */
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/*  floating sel is attached to  */
DECL|member|initial
name|int
name|initial
decl_stmt|;
comment|/*  is fs composited yet?        */
DECL|member|boundary_known
name|int
name|boundary_known
decl_stmt|;
comment|/*  is the current boundary valid*/
DECL|member|segs
name|BoundSeg
modifier|*
name|segs
decl_stmt|;
comment|/*  boundary of floating sel     */
DECL|member|num_segs
name|int
name|num_segs
decl_stmt|;
comment|/*  number of segs in boundary   */
DECL|member|fs
block|}
name|fs
struct|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLayerClass
struct|struct
name|_GimpLayerClass
block|{
DECL|member|parent_class
name|GimpDrawableClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLayerMask
struct|struct
name|_GimpLayerMask
block|{
DECL|member|drawable
name|GimpChannel
name|drawable
decl_stmt|;
DECL|member|layer
name|Layer
modifier|*
name|layer
decl_stmt|;
comment|/*  ID of layer */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLayerMaskClass
struct|struct
name|_GimpLayerMaskClass
block|{
DECL|member|parent_class
name|GimpChannelClass
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
comment|/* __LAYER_PVT_H__ */
end_comment

end_unit

