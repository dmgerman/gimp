begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimperrorconsole.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ERROR_CONSOLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ERROR_CONSOLE_H__
define|#
directive|define
name|__GIMP_ERROR_CONSOLE_H__
end_define

begin_include
include|#
directive|include
file|"gimpeditor.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_ERROR_CONSOLE
define|#
directive|define
name|GIMP_TYPE_ERROR_CONSOLE
value|(gimp_error_console_get_type ())
end_define

begin_define
DECL|macro|GIMP_ERROR_CONSOLE (obj)
define|#
directive|define
name|GIMP_ERROR_CONSOLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ERROR_CONSOLE, GimpErrorConsole))
end_define

begin_define
DECL|macro|GIMP_ERROR_CONSOLE_CLASS (klass)
define|#
directive|define
name|GIMP_ERROR_CONSOLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ERROR_CONSOLE, GimpErrorConsoleClass))
end_define

begin_define
DECL|macro|GIMP_IS_ERROR_CONSOLE (obj)
define|#
directive|define
name|GIMP_IS_ERROR_CONSOLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ERROR_CONSOLE))
end_define

begin_define
DECL|macro|GIMP_IS_ERROR_CONSOLE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ERROR_CONSOLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ERROR_CONSOLE))
end_define

begin_define
DECL|macro|GIMP_ERROR_CONSOLE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ERROR_CONSOLE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ERROR_CONSOLE, GimpErrorConsoleClass))
end_define

begin_typedef
DECL|typedef|GimpErrorConsoleClass
typedef|typedef
name|struct
name|_GimpErrorConsoleClass
name|GimpErrorConsoleClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpErrorConsole
struct|struct
name|_GimpErrorConsole
block|{
DECL|member|parent_instance
name|GimpEditor
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|text_buffer
name|GtkTextBuffer
modifier|*
name|text_buffer
decl_stmt|;
DECL|member|text_view
name|GtkWidget
modifier|*
name|text_view
decl_stmt|;
DECL|member|clear_button
name|GtkWidget
modifier|*
name|clear_button
decl_stmt|;
DECL|member|save_button
name|GtkWidget
modifier|*
name|save_button
decl_stmt|;
DECL|member|file_dialog
name|GtkWidget
modifier|*
name|file_dialog
decl_stmt|;
DECL|member|save_selection
name|gboolean
name|save_selection
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpErrorConsoleClass
struct|struct
name|_GimpErrorConsoleClass
block|{
DECL|member|parent_class
name|GimpEditorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_error_console_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_error_console_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_error_console_add
parameter_list|(
name|GimpErrorConsole
modifier|*
name|console
parameter_list|,
name|GimpMessageSeverity
name|severity
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_ERROR_CONSOLE_H__  */
end_comment

end_unit

