begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"cursorutil.h"
end_include

begin_function
name|void
DECL|function|change_win_cursor (win,cursortype)
name|change_win_cursor
parameter_list|(
name|win
parameter_list|,
name|cursortype
parameter_list|)
name|GdkWindow
modifier|*
name|win
decl_stmt|;
name|GdkCursorType
name|cursortype
decl_stmt|;
block|{
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
name|cursor
operator|=
name|gdk_cursor_new
argument_list|(
name|cursortype
argument_list|)
expr_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|win
argument_list|,
name|cursor
argument_list|)
expr_stmt|;
name|gdk_cursor_destroy
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|unset_win_cursor (win)
name|unset_win_cursor
parameter_list|(
name|win
parameter_list|)
name|GdkWindow
modifier|*
name|win
decl_stmt|;
block|{
name|gdk_window_set_cursor
argument_list|(
name|win
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

