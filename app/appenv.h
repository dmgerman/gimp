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
file|"glib.h"
end_include

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

begin_include
include|#
directive|include
file|"gimpsetF.h"
end_include

begin_include
include|#
directive|include
file|"colormap_dialog.t.h"
end_include

begin_define
DECL|macro|DISPLAY
define|#
directive|define
name|DISPLAY
value|((Display *) GDK_DISPLAY())
end_define

begin_comment
comment|/*   important macros - we reuse the ones from glib */
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
value|CLAMP(a,x,y)
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
value|MIN(x,y)
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
value|MAX(x,y)
end_define

begin_comment
comment|/* limit a (0->511) int to 255 */
end_comment

begin_define
DECL|macro|MAX255 (a)
define|#
directive|define
name|MAX255
parameter_list|(
name|a
parameter_list|)
value|(a | ((a& 256) - ((a& 256)>> 8)))
end_define

begin_comment
comment|/* clamp a>>int32<<-range int between 0 and 255 inclusive */
end_comment

begin_comment
comment|/* broken! -> #define CLAMP0255(a)  ((a& 0xFFFFFF00)? (~(a>>31)) : a) */
end_comment

begin_define
DECL|macro|CLAMP0255 (a)
define|#
directive|define
name|CLAMP0255
parameter_list|(
name|a
parameter_list|)
value|CLAMP(a,0,255)
end_define

begin_typedef
DECL|enum|__anon29483a310103
typedef|typedef
enum|enum
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
name|int
name|restore_session
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  APPENV_H  */
end_comment

end_unit

