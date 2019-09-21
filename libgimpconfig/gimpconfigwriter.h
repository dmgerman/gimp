begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpConfigWriter  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_CONFIG_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_CONFIG_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpconfig/gimpconfig.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

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

begin_comment
comment|/**  * GIMP_TYPE_CONFIG_WRITER:  *  * The type ID of the "GimpConfigWriter" type which is a boxed type,  * used to write config files.  *  * Since: 3.0  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_CONFIG_WRITER
define|#
directive|define
name|GIMP_TYPE_CONFIG_WRITER
value|(gimp_config_writer_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_config_writer_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpConfigWriter
modifier|*
name|gimp_config_writer_new_from_file
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|gboolean
name|atomic
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
name|gimp_config_writer_new_from_stream
parameter_list|(
name|GOutputStream
modifier|*
name|output
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
name|GimpConfigWriter
modifier|*
name|gimp_config_writer_new_from_string
parameter_list|(
name|GString
modifier|*
name|string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpConfigWriter
modifier|*
name|gimp_config_writer_ref
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_writer_unref
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
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
name|gimp_config_writer_comment_mode
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gboolean
name|enable
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
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|2
operator|,
function_decl|3
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|void
name|gimp_config_writer_identifier
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_writer_string
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_writer_data
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gint
name|length
parameter_list|,
specifier|const
name|guint8
modifier|*
name|data
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

