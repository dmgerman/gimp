begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BASE_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BASE_TYPES_H__
define|#
directive|define
name|__GIMP_BASE_TYPES_H__
end_define

begin_include
include|#
directive|include
file|<libgimpcolor/gimpcolortypes.h>
end_include

begin_include
include|#
directive|include
file|<libgimpmath/gimpmathtypes.h>
end_include

begin_include
include|#
directive|include
file|<libgimpbase/gimpbaseenums.h>
end_include

begin_include
include|#
directive|include
file|<libgimpbase/gimpparam.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_typedef
DECL|typedef|GimpParasite
typedef|typedef
name|struct
name|_GimpParasite
name|GimpParasite
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDatafileData
typedef|typedef
name|struct
name|_GimpDatafileData
name|GimpDatafileData
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpEnumDesc
typedef|typedef
name|struct
name|_GimpEnumDesc
name|GimpEnumDesc
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFlagsDesc
typedef|typedef
name|struct
name|_GimpFlagsDesc
name|GimpFlagsDesc
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDatafileLoaderFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDatafileLoaderFunc
function_decl|)
parameter_list|(
specifier|const
name|GimpDatafileData
modifier|*
name|file_data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/**  * GimpEnumDesc:  * @value:      An enum value.  * @value_desc: The value's description.  * @value_help: The value's help text.  *  * This structure is used to register translatable descriptions and  * help texts for enum values. See gimp_enum_set_value_descriptions().  **/
end_comment

begin_struct
DECL|struct|_GimpEnumDesc
struct|struct
name|_GimpEnumDesc
block|{
DECL|member|value
name|gint
name|value
decl_stmt|;
DECL|member|value_desc
specifier|const
name|gchar
modifier|*
name|value_desc
decl_stmt|;
DECL|member|value_help
specifier|const
name|gchar
modifier|*
name|value_help
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/**  * GimpFlagsDesc:  * @value:      A flag value.  * @value_desc: The value's description.  * @value_help: The value's help text.  *  * This structure is used to register translatable descriptions and  * help texts for flag values. See gimp_flags_set_value_descriptions().  **/
end_comment

begin_struct
DECL|struct|_GimpFlagsDesc
struct|struct
name|_GimpFlagsDesc
block|{
DECL|member|value
name|guint
name|value
decl_stmt|;
DECL|member|value_desc
specifier|const
name|gchar
modifier|*
name|value_desc
decl_stmt|;
DECL|member|value_help
specifier|const
name|gchar
modifier|*
name|value_help
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_type_set_translation_domain
parameter_list|(
name|GType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_type_get_translation_domain
parameter_list|(
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_type_set_translation_context
parameter_list|(
name|GType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_type_get_translation_context
parameter_list|(
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_enum_set_value_descriptions
parameter_list|(
name|GType
name|enum_type
parameter_list|,
specifier|const
name|GimpEnumDesc
modifier|*
name|descriptions
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpEnumDesc
modifier|*
name|gimp_enum_get_value_descriptions
parameter_list|(
name|GType
name|enum_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_flags_set_value_descriptions
parameter_list|(
name|GType
name|flags_type
parameter_list|,
specifier|const
name|GimpFlagsDesc
modifier|*
name|descriptions
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpFlagsDesc
modifier|*
name|gimp_flags_get_value_descriptions
parameter_list|(
name|GType
name|flags_type
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
comment|/* __GIMP_BASE_TYPES_H__ */
end_comment

end_unit

