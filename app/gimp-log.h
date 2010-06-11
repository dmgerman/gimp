begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LOG_H__
define|#
directive|define
name|__GIMP_LOG_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon278696520103
block|{
DECL|enumerator|GIMP_LOG_TOOL_EVENTS
name|GIMP_LOG_TOOL_EVENTS
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_LOG_TOOL_FOCUS
name|GIMP_LOG_TOOL_FOCUS
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_LOG_DND
name|GIMP_LOG_DND
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_LOG_HELP
name|GIMP_LOG_HELP
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_LOG_DIALOG_FACTORY
name|GIMP_LOG_DIALOG_FACTORY
init|=
literal|1
operator|<<
literal|4
block|,
DECL|enumerator|GIMP_LOG_MENUS
name|GIMP_LOG_MENUS
init|=
literal|1
operator|<<
literal|5
block|,
DECL|enumerator|GIMP_LOG_SAVE_DIALOG
name|GIMP_LOG_SAVE_DIALOG
init|=
literal|1
operator|<<
literal|6
block|,
DECL|enumerator|GIMP_LOG_IMAGE_SCALE
name|GIMP_LOG_IMAGE_SCALE
init|=
literal|1
operator|<<
literal|7
block|,
DECL|enumerator|GIMP_LOG_SHADOW_TILES
name|GIMP_LOG_SHADOW_TILES
init|=
literal|1
operator|<<
literal|8
block|,
DECL|enumerator|GIMP_LOG_SCALE
name|GIMP_LOG_SCALE
init|=
literal|1
operator|<<
literal|9
block|,
DECL|enumerator|GIMP_LOG_WM
name|GIMP_LOG_WM
init|=
literal|1
operator|<<
literal|10
block|,
DECL|enumerator|GIMP_LOG_FLOATING_SELECTION
name|GIMP_LOG_FLOATING_SELECTION
init|=
literal|1
operator|<<
literal|11
block|,
DECL|enumerator|GIMP_LOG_SHM
name|GIMP_LOG_SHM
init|=
literal|1
operator|<<
literal|12
block|,
DECL|enumerator|GIMP_LOG_TEXT_EDITING
name|GIMP_LOG_TEXT_EDITING
init|=
literal|1
operator|<<
literal|13
block|,
DECL|enumerator|GIMP_LOG_KEY_EVENTS
name|GIMP_LOG_KEY_EVENTS
init|=
literal|1
operator|<<
literal|14
block|,
DECL|enumerator|GIMP_LOG_AUTO_TAB_STYLE
name|GIMP_LOG_AUTO_TAB_STYLE
init|=
literal|1
operator|<<
literal|15
DECL|typedef|GimpLogFlags
block|}
name|GimpLogFlags
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|GimpLogFlags
name|gimp_log_flags
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_log_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_log
parameter_list|(
specifier|const
name|gchar
modifier|*
name|function
parameter_list|,
name|gint
name|line
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|4
operator|,
function_decl|5
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|void
name|gimp_logv
parameter_list|(
specifier|const
name|gchar
modifier|*
name|function
parameter_list|,
name|gint
name|line
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|G_HAVE_ISO_VARARGS
end_ifdef

begin_define
DECL|macro|GIMP_LOG (type,...)
define|#
directive|define
name|GIMP_LOG
parameter_list|(
name|type
parameter_list|,
modifier|...
parameter_list|)
define|\
value|G_STMT_START { \         if (gimp_log_flags& GIMP_LOG_##type) \           gimp_log (G_STRFUNC, __LINE__, #type, __VA_ARGS__); \         } G_STMT_END
end_define

begin_elif
elif|#
directive|elif
name|defined
argument_list|(
name|G_HAVE_GNUC_VARARGS
argument_list|)
end_elif

begin_define
DECL|macro|GIMP_LOG (type,format...)
define|#
directive|define
name|GIMP_LOG
parameter_list|(
name|type
parameter_list|,
name|format
modifier|...
parameter_list|)
define|\
value|G_STMT_START { \         if (gimp_log_flags& GIMP_LOG_##type) \           gimp_log (G_STRFUNC, __LINE__, #type, format); \         } G_STMT_END
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* no varargs macros */
end_comment

begin_comment
comment|/* need to expand all the short forms  * to make them known constants at compile time  */
end_comment

begin_define
DECL|macro|TOOL_EVENTS
define|#
directive|define
name|TOOL_EVENTS
value|GIMP_LOG_TOOL_EVENTS
end_define

begin_define
DECL|macro|TOOL_FOCUS
define|#
directive|define
name|TOOL_FOCUS
value|GIMP_LOG_TOOL_FOCUS
end_define

begin_define
DECL|macro|DND
define|#
directive|define
name|DND
value|GIMP_LOG_DND
end_define

begin_define
DECL|macro|HELP
define|#
directive|define
name|HELP
value|GIMP_LOG_HELP
end_define

begin_define
DECL|macro|DIALOG_FACTORY
define|#
directive|define
name|DIALOG_FACTORY
value|GIMP_LOG_DIALOG_FACTORY
end_define

begin_define
DECL|macro|MENUS
define|#
directive|define
name|MENUS
value|GIMP_LOG_MENUS
end_define

begin_define
DECL|macro|SAVE_DIALOG
define|#
directive|define
name|SAVE_DIALOG
value|GIMP_LOG_SAVE_DIALOG
end_define

begin_define
DECL|macro|IMAGE_SCALE
define|#
directive|define
name|IMAGE_SCALE
value|GIMP_LOG_IMAGE_SCALE
end_define

begin_define
DECL|macro|SHADOW_TILES
define|#
directive|define
name|SHADOW_TILES
value|GIMP_LOG_SHADOW_TILES
end_define

begin_define
DECL|macro|SCALE
define|#
directive|define
name|SCALE
value|GIMP_LOG_SCALE
end_define

begin_define
DECL|macro|WM
define|#
directive|define
name|WM
value|GIMP_LOG_WM
end_define

begin_define
DECL|macro|FLOATING_SELECTION
define|#
directive|define
name|FLOATING_SELECTION
value|GIMP_LOG_FLOATING_SELECTION
end_define

begin_define
DECL|macro|SHM
define|#
directive|define
name|SHM
value|GIMP_LOG_SHM
end_define

begin_define
DECL|macro|TEXT_EDITING
define|#
directive|define
name|TEXT_EDITING
value|GIMP_LOG_TEXT_EDITING
end_define

begin_define
DECL|macro|KEY_EVENTS
define|#
directive|define
name|KEY_EVENTS
value|GIMP_LOG_KEY_EVENTS
end_define

begin_define
DECL|macro|AUTO_TAB_STYLE
define|#
directive|define
name|AUTO_TAB_STYLE
value|GIMP_LOG_AUTO_TAB_STYLE
end_define

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* last resort */
end_comment

begin_define
define|#
directive|define
name|GIMP_LOG
end_define

begin_comment
comment|/* nothing => no varargs, no log */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|void
DECL|function|GIMP_LOG (GimpLogFlags flags,const gchar * format,...)
name|GIMP_LOG
parameter_list|(
name|GimpLogFlags
name|flags
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
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
name|format
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_log_flags
operator|&
name|flags
condition|)
name|gimp_logv
argument_list|(
literal|""
argument_list|,
literal|0
argument_list|,
literal|""
argument_list|,
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* !__GNUC__ */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LOG_H__ */
end_comment

end_unit

