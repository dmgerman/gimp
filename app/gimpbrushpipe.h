begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1999 Adrian Likins and Tor Lillqvist  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_PIPE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_PIPE_H__
define|#
directive|define
name|__GIMP_BRUSH_PIPE_H__
end_define

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"paint_core.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_typedef
DECL|typedef|GimpBrushPipe
typedef|typedef
name|struct
name|_GimpBrushPipe
name|GimpBrushPipe
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_BRUSH_PIPE
define|#
directive|define
name|GIMP_TYPE_BRUSH_PIPE
value|(gimp_brush_pipe_get_type ())
end_define

begin_define
DECL|macro|GIMP_BRUSH_PIPE (obj)
define|#
directive|define
name|GIMP_BRUSH_PIPE
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_BRUSH_PIPE, GimpBrushPipe))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_PIPE (obj)
define|#
directive|define
name|GIMP_IS_BRUSH_PIPE
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_BRUSH_PIPE))
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b1e7fc30103
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

begin_struct
DECL|struct|_GimpBrushPipe
struct|struct
name|_GimpBrushPipe
block|{
DECL|member|gbrush
name|GimpBrush
name|gbrush
decl_stmt|;
comment|/* Also itself a brush */
DECL|member|dimension
name|gint
name|dimension
decl_stmt|;
DECL|member|rank
name|gint
modifier|*
name|rank
decl_stmt|;
comment|/* Size in each dimension */
DECL|member|stride
name|gint
modifier|*
name|stride
decl_stmt|;
comment|/* Aux for indexing */
DECL|member|select
name|PipeSelectModes
modifier|*
name|select
decl_stmt|;
comment|/* One mode per dimension */
DECL|member|index
name|gint
modifier|*
name|index
decl_stmt|;
comment|/* Current index for incremental dimensions */
DECL|member|nbrushes
name|gint
name|nbrushes
decl_stmt|;
comment|/* Might be less than the product of the 				 * ranks in some odd special case */
DECL|member|brushes
name|GimpBrush
modifier|*
modifier|*
name|brushes
decl_stmt|;
DECL|member|current
name|GimpBrush
modifier|*
name|current
decl_stmt|;
comment|/* Currently selected brush */
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpBrushPipeClass
typedef|typedef
name|struct
name|_GimpBrushPipeClass
name|GimpBrushPipeClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBrushPipeClass
struct|struct
name|_GimpBrushPipeClass
block|{
DECL|member|parent_class
name|GimpBrushClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_brush_pixmap_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_brush_pipe_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrush
modifier|*
name|gimp_brush_pipe_load
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_BRUSH_PIPE_H__ */
end_comment

end_unit

