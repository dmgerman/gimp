begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_define
DECL|macro|MAZE_TITLE
define|#
directive|define
name|MAZE_TITLE
value|"Maze 0.6.2"
end_define

begin_define
DECL|macro|MAZE_URL
define|#
directive|define
name|MAZE_URL
value|"http://www.poboxes.com/kevint/gimp/maze.html"
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

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_typedef
DECL|struct|__anon29fbe35a0108
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
name|gint
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

end_unit

