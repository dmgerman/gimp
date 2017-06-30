begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_BASE_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_BASE_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpbase/gimpbase.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

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

begin_decl_stmt
name|G_BEGIN_DECLS
name|gchar
modifier|*
name|gimp_utf8_strtrim
argument_list|(
specifier|const
name|gchar
operator|*
name|str
argument_list|,
name|gint
name|max_chars
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gchar
modifier|*
name|gimp_any_to_utf8
argument_list|(
specifier|const
name|gchar
operator|*
name|str
argument_list|,
name|gssize
name|len
argument_list|,
specifier|const
name|gchar
operator|*
name|warning_format
argument_list|,
operator|...
argument_list|)
name|G_GNUC_PRINTF
argument_list|(
literal|3
argument_list|,
literal|4
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

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
specifier|const
name|gchar
modifier|*
name|gimp_file_get_utf8_name
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_file_has_extension
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_file_show_in_file_manager
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|gchar
modifier|*
name|gimp_strip_uline
argument_list|(
specifier|const
name|gchar
operator|*
name|str
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gchar
modifier|*
name|gimp_escape_uline
argument_list|(
specifier|const
name|gchar
operator|*
name|str
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gchar
modifier|*
name|gimp_canonicalize_identifier
argument_list|(
specifier|const
name|gchar
operator|*
name|identifier
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpEnumDesc
modifier|*
name|gimp_enum_get_desc
parameter_list|(
name|GEnumClass
modifier|*
name|enum_class
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_enum_get_value
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|value
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_nick
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_desc
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_help
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_enum_value_get_desc
parameter_list|(
name|GEnumClass
modifier|*
name|enum_class
parameter_list|,
name|GEnumValue
modifier|*
name|enum_value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_enum_value_get_help
parameter_list|(
name|GEnumClass
modifier|*
name|enum_class
parameter_list|,
name|GEnumValue
modifier|*
name|enum_value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpFlagsDesc
modifier|*
name|gimp_flags_get_first_desc
parameter_list|(
name|GFlagsClass
modifier|*
name|flags_class
parameter_list|,
name|guint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_flags_get_first_value
parameter_list|(
name|GType
name|flags_type
parameter_list|,
name|guint
name|value
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_nick
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_desc
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value_help
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_flags_value_get_desc
parameter_list|(
name|GFlagsClass
modifier|*
name|flags_class
parameter_list|,
name|GFlagsValue
modifier|*
name|flags_value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_flags_value_get_help
parameter_list|(
name|GFlagsClass
modifier|*
name|flags_class
parameter_list|,
name|GFlagsValue
modifier|*
name|flags_value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_base_compat_enum_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_UTILS_H__ */
end_comment

end_unit

