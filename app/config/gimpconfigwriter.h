begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpConfigWriter  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONFIG_WRITER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONFIG_WRITER_H__
define|#
directive|define
name|__GIMP_CONFIG_WRITER_H__
end_define

begin_struct
DECL|struct|_GimpConfigWriter
struct|struct
name|_GimpConfigWriter
block|{
comment|/*<  private>*/
DECL|member|fd
name|gint
name|fd
decl_stmt|;
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|tmpname
name|gchar
modifier|*
name|tmpname
decl_stmt|;
DECL|member|error
name|GError
modifier|*
name|error
decl_stmt|;
DECL|member|buffer
name|GString
modifier|*
name|buffer
decl_stmt|;
DECL|member|depth
name|gint
name|depth
decl_stmt|;
DECL|member|marker
name|gint
name|marker
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GimpConfigWriter
modifier|*
name|gimp_config_writer_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|safe
parameter_list|,
specifier|const
name|gchar
modifier|*
name|header
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpConfigWriter
modifier|*
name|gimp_config_writer_new_from_fd
parameter_list|(
name|gint
name|fd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_writer_open
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_writer_print
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
name|gint
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_writer_printf
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_writer_revert
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_writer_close
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_writer_linefeed
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_writer_comment
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|comment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_config_writer_finish
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|footer
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONFIG_WRITER_H__ */
end_comment

end_unit

