begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* $Id$ */
end_comment

begin_define
DECL|macro|MAZE_TITLE
define|#
directive|define
name|MAZE_TITLE
value|"Maze 1.2.2"
end_define

begin_define
DECL|macro|MAZE_URL
define|#
directive|define
name|MAZE_URL
value|"http://gimp-plug-ins.sourceforge.net/maze/help.html"
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
comment|/* Don't draw in anything that has less than     this value in the selection channel. */
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

begin_typedef
DECL|enum|__anon2a0d68640103
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
DECL|struct|__anon2a0d68640208
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
name|guint
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
comment|/* Interface options. */
DECL|member|timeseed
name|gboolean
name|timeseed
decl_stmt|;
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

end_unit

