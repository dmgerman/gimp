begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1999 Adrian Likins and Tor Lillqvist  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPBRUSHPIPEP_H__
end_ifndef

begin_define
DECL|macro|__GIMPBRUSHPIPEP_H__
define|#
directive|define
name|__GIMPBRUSHPIPEP_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon296df63d0103
block|{
DECL|enumerator|PIPE_SELECT_CONSTANT
name|PIPE_SELECT_CONSTANT
block|,
DECL|enumerator|PIPE_SELECT_INCREMENTAL
name|PIPE_SELECT_INCREMENTAL
block|,
DECL|enumerator|PIPE_SELECT_ANGULAR
name|PIPE_SELECT_ANGULAR
block|,
DECL|enumerator|PIPE_SELECT_VELOCITY
name|PIPE_SELECT_VELOCITY
block|,
DECL|enumerator|PIPE_SELECT_RANDOM
name|PIPE_SELECT_RANDOM
block|,
DECL|enumerator|PIPE_SELECT_PRESSURE
name|PIPE_SELECT_PRESSURE
block|,
DECL|enumerator|PIPE_SELECT_TILT_X
name|PIPE_SELECT_TILT_X
block|,
DECL|enumerator|PIPE_SELECT_TILT_Y
name|PIPE_SELECT_TILT_Y
DECL|typedef|PipeSelectModes
block|}
name|PipeSelectModes
typedef|;
end_typedef

begin_comment
comment|/* A GimpBrushPixmap always exists as part in one and only one GimpBrushPipe  * It contains a back-pointer to the GimpBrushPipe so that we can select  * the next brush in the pipe with just a reference to the GimpBrushPipe.  */
end_comment

begin_struct
DECL|struct|_GimpBrushPixmap
struct|struct
name|_GimpBrushPixmap
block|{
DECL|member|gbrush
name|GimpBrush
name|gbrush
decl_stmt|;
DECL|member|pixmap_mask
name|TempBuf
modifier|*
name|pixmap_mask
decl_stmt|;
DECL|member|pipe
name|GimpBrushPipe
modifier|*
name|pipe
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBrushPipe
struct|struct
name|_GimpBrushPipe
block|{
DECL|member|pixmap
name|GimpBrushPixmap
name|pixmap
decl_stmt|;
comment|/* Also itself a pixmap brush */
DECL|member|current
name|GimpBrushPixmap
modifier|*
name|current
decl_stmt|;
comment|/* Currently selected brush */
DECL|member|dimension
name|int
name|dimension
decl_stmt|;
DECL|member|rank
name|int
modifier|*
name|rank
decl_stmt|;
comment|/* Size in each dimension */
DECL|member|stride
name|int
modifier|*
name|stride
decl_stmt|;
comment|/* Aux for indexing */
DECL|member|nbrushes
name|int
name|nbrushes
decl_stmt|;
comment|/* Might be less than the product of the 				 * ranks in some odd special case 				 */
DECL|member|brushes
name|GimpBrushPixmap
modifier|*
modifier|*
name|brushes
decl_stmt|;
DECL|member|select
name|PipeSelectModes
modifier|*
name|select
decl_stmt|;
comment|/* One mode per dimension */
DECL|member|index
name|int
modifier|*
name|index
decl_stmt|;
comment|/* Current index for incremental dimensions */
block|}
struct|;
end_struct

begin_typedef
DECL|struct|_GimpBrushPixmapClass
typedef|typedef
struct|struct
name|_GimpBrushPixmapClass
block|{
DECL|member|parent_class
name|GimpBrushClass
name|parent_class
decl_stmt|;
DECL|typedef|GimpBrushPixmapClass
block|}
name|GimpBrushPixmapClass
typedef|;
end_typedef

begin_typedef
DECL|struct|_GimpBrushPipeClass
typedef|typedef
struct|struct
name|_GimpBrushPipeClass
block|{
DECL|member|parent_class
name|GimpBrushPixmapClass
name|parent_class
decl_stmt|;
DECL|typedef|GimpBrushPipeClass
block|}
name|GimpBrushPipeClass
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPBRUSHPIPEP_H__ */
end_comment

end_unit

