begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpscanner.h  * Copyright (C) 2002  Sven Neumann<sven@gimp.org>  *                     Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_SCANNER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SCANNER_H__
define|#
directive|define
name|__GIMP_SCANNER_H__
end_define

begin_function_decl
name|GScanner
modifier|*
name|gimp_scanner_new_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GScanner
modifier|*
name|gimp_scanner_new_string
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|text_len
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scanner_destroy
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_scanner_parse_token
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GTokenType
name|token
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_scanner_parse_identifier
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_scanner_parse_string
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gchar
modifier|*
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_scanner_parse_string_no_validate
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gchar
modifier|*
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_scanner_parse_data
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|length
parameter_list|,
name|guint8
modifier|*
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_scanner_parse_int
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_scanner_parse_float
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gdouble
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_scanner_parse_color
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GimpRGB
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_scanner_parse_matrix2
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GimpMatrix2
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SCANNER_H__ */
end_comment

end_unit

