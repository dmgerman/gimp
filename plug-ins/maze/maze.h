begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__MAZE_H__
end_ifndef

begin_define
DECL|macro|__MAZE_H__
define|#
directive|define
name|__MAZE_H__
end_define

begin_define
DECL|macro|MAZE_TITLE
define|#
directive|define
name|MAZE_TITLE
value|N_("Maze")
end_define

begin_define
DECL|macro|HELP_OPENS_NEW_WINDOW
define|#
directive|define
name|HELP_OPENS_NEW_WINDOW
value|FALSE
end_define

begin_comment
comment|/* The "divbox" really should look and act more like a spinbutton.   This flag is a small step in the direction toward the former, the   latter leaves much to be desired. */
end_comment

begin_define
DECL|macro|DIVBOX_LOOKS_LIKE_SPINBUTTON
define|#
directive|define
name|DIVBOX_LOOKS_LIKE_SPINBUTTON
value|FALSE
end_define

begin_comment
comment|/* Don't update the progress for every cell when creating a maze.    Instead, update every . . . */
end_comment

begin_define
DECL|macro|PRIMS_PROGRESS_UPDATE
define|#
directive|define
name|PRIMS_PROGRESS_UPDATE
value|256
end_define

begin_comment
comment|/* Don't draw in anything that has less than    this value in the selection channel. */
end_comment

begin_define
DECL|macro|MAZE_ALPHA_THRESHOLD
define|#
directive|define
name|MAZE_ALPHA_THRESHOLD
value|127
end_define

begin_include
include|#
directive|include
file|"glib.h"
end_include

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-maze"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"maze"
end_define

begin_typedef
DECL|enum|__anon2920f6ed0103
typedef|typedef
enum|enum
block|{
DECL|enumerator|DEPTH_FIRST
name|DEPTH_FIRST
block|,
DECL|enumerator|PRIMS_ALGORITHM
name|PRIMS_ALGORITHM
DECL|typedef|MazeAlgoType
block|}
name|MazeAlgoType
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2920f6ed0208
typedef|typedef
struct|struct
block|{
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|seed
name|guint32
name|seed
decl_stmt|;
DECL|member|tile
name|gboolean
name|tile
decl_stmt|;
DECL|member|multiple
name|gint
name|multiple
decl_stmt|;
DECL|member|offset
name|gint
name|offset
decl_stmt|;
DECL|member|algorithm
name|MazeAlgoType
name|algorithm
decl_stmt|;
DECL|member|random_seed
name|gboolean
name|random_seed
decl_stmt|;
comment|/* Interface options. */
DECL|typedef|MazeValues
block|}
name|MazeValues
typedef|;
end_typedef

begin_enum
DECL|enum|CellTypes
enum|enum
name|CellTypes
block|{
DECL|enumerator|OUT
name|OUT
block|,
DECL|enumerator|IN
name|IN
block|,
DECL|enumerator|FRONTIER
name|FRONTIER
block|,
DECL|enumerator|MASKED
name|MASKED
block|}
enum|;
end_enum

begin_function_decl
name|void
name|get_colors
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|guint8
modifier|*
name|fg
parameter_list|,
name|guint8
modifier|*
name|bg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|drawbox
parameter_list|(
name|GimpPixelRgn
modifier|*
name|dest_rgn
parameter_list|,
name|guint
name|x
parameter_list|,
name|guint
name|y
parameter_list|,
name|guint
name|w
parameter_list|,
name|guint
name|h
parameter_list|,
name|guint8
name|clr
index|[
literal|4
index|]
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __MAZE_H__ */
end_comment

end_unit

