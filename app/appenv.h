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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpsetF.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b1443a00103
block|{
DECL|enumerator|MESSAGE_BOX
name|MESSAGE_BOX
block|,
DECL|enumerator|CONSOLE
name|CONSOLE
block|,
DECL|enumerator|ERROR_CONSOLE
name|ERROR_CONSOLE
DECL|typedef|MessageHandlerType
block|}
name|MessageHandlerType
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|gboolean
name|no_interface
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|no_splash
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|no_splash_image
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|no_data
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|be_verbose
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|use_debug_handler
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|console_messages
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|restore_session
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|double_speed
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|we_are_exiting
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* this is used in session_get_window_info() */
end_comment

begin_decl_stmt
specifier|extern
name|GimpSet
modifier|*
name|image_context
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|MessageHandlerType
name|message_handler
decl_stmt|;
end_decl_stmt

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_function_decl
name|gchar
modifier|*
name|quote_spaces
parameter_list|(
name|gchar
modifier|*
name|string
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __APPENV_H__  */
end_comment

end_unit

