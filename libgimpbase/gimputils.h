begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_UTILS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UTILS_H__
define|#
directive|define
name|__GIMP_UTILS_H__
end_define

begin_function_decl
name|gchar
modifier|*
name|gimp_utf8_strtrim
parameter_list|(
specifier|const
name|gchar
modifier|*
name|str
parameter_list|,
name|gint
name|max_chars
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_any_to_utf8
parameter_list|(
specifier|const
name|gchar
modifier|*
name|str
parameter_list|,
name|gssize
name|len
parameter_list|,
specifier|const
name|gchar
modifier|*
name|warning_format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|3
operator|,
function_decl|4
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_filename_to_utf8
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_memsize_to_string
parameter_list|(
name|guint64
name|memsize
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_strip_uline
parameter_list|(
specifier|const
name|gchar
modifier|*
name|str
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_UTILS_H__ */
end_comment

end_unit

