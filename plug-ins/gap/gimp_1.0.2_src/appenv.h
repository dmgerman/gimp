begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__APPENV_H__
end_ifndef

begin_define
DECL|macro|__APPENV_H__
define|#
directive|define
name|__APPENV_H__
end_define

begin_include
include|#
directive|include
file|"gdk/gdkx.h"
end_include

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_define
DECL|macro|DISPLAY
define|#
directive|define
name|DISPLAY
value|((Display *) GDK_DISPLAY())
end_define

begin_comment
comment|/*   important macros  */
end_comment

begin_define
DECL|macro|BOUNDS (a,x,y)
define|#
directive|define
name|BOUNDS
parameter_list|(
name|a
parameter_list|,
name|x
parameter_list|,
name|y
parameter_list|)
value|((a< x) ? x : ((a> y) ? y : a))
end_define

begin_define
DECL|macro|MINIMUM (x,y)
define|#
directive|define
name|MINIMUM
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|)
value|((x< y) ? x : y)
end_define

begin_define
DECL|macro|MAXIMUM (x,y)
define|#
directive|define
name|MAXIMUM
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|)
value|((x> y) ? x : y)
end_define

begin_typedef
DECL|enum|__anon2c2a1e810103
typedef|typedef
enum|enum
block|{
DECL|enumerator|MESSAGE_BOX
name|MESSAGE_BOX
block|,
DECL|enumerator|CONSOLE
name|CONSOLE
DECL|typedef|MessageHandlerType
block|}
name|MessageHandlerType
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|int
name|no_interface
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|no_splash
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|no_splash_image
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|no_data
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|be_verbose
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|use_debug_handler
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|console_messages
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|MessageHandlerType
name|message_handler
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  APPENV_H  */
end_comment

end_unit

