begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_define
DECL|macro|MAZE_TITLE
define|#
directive|define
name|MAZE_TITLE
value|"Maze 0.6.1"
end_define

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_typedef
DECL|struct|__anon2b2594d20108
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

