begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<signal.h>
end_include

begin_include
include|#
directive|include
file|<stdarg.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<sys/time.h>
end_include

begin_include
include|#
directive|include
file|<sys/times.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"interface.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_decl_stmt
specifier|extern
name|char
modifier|*
name|prog_name
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|use_debug_handler
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|message_console_func (char * str)
name|message_console_func
parameter_list|(
name|char
modifier|*
name|str
parameter_list|)
block|{
name|g_print
argument_list|(
literal|"%s: %s\n"
argument_list|,
name|prog_name
argument_list|,
name|str
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|message_box_func (char * str)
name|message_box_func
parameter_list|(
name|char
modifier|*
name|str
parameter_list|)
block|{
name|message_box
argument_list|(
name|str
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|fatal_error (char * fmt,...)
name|fatal_error
parameter_list|(
name|char
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|fmt
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"%s fatal error: "
argument_list|,
name|prog_name
argument_list|)
expr_stmt|;
name|vprintf
argument_list|(
name|fmt
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|g_debug
argument_list|(
name|prog_name
argument_list|)
expr_stmt|;
name|app_exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|terminate (char * fmt,...)
name|terminate
parameter_list|(
name|char
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|fmt
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"%s terminated: "
argument_list|,
name|prog_name
argument_list|)
expr_stmt|;
name|vprintf
argument_list|(
name|fmt
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|use_debug_handler
condition|)
name|g_debug
argument_list|(
name|prog_name
argument_list|)
expr_stmt|;
name|gdk_exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

