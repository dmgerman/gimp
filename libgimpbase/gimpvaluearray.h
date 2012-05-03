begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpvaluearray.h ported from GValueArray  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_VALUE_ARRAY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VALUE_ARRAY_H__
define|#
directive|define
name|__GIMP_VALUE_ARRAY_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/**  * GIMP_TYPE_VALUE_ARRAY:  *  * The type ID of the "GimpValueArray" type which is a boxed type,  * used to pass around pointers to GimpValueArrays.  *  * Since: GIMP 2.10  */
DECL|macro|GIMP_TYPE_VALUE_ARRAY
define|#
directive|define
name|GIMP_TYPE_VALUE_ARRAY
value|(gimp_value_array_get_type ())
name|GType
name|gimp_value_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpValueArray
modifier|*
name|gimp_value_array_new
parameter_list|(
name|gint
name|n_prealloced
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpValueArray
modifier|*
name|gimp_value_array_ref
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_array_unref
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_value_array_length
parameter_list|(
specifier|const
name|GimpValueArray
modifier|*
name|value_array
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GValue
modifier|*
name|gimp_value_array_index
parameter_list|(
specifier|const
name|GimpValueArray
modifier|*
name|value_array
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpValueArray
modifier|*
name|gimp_value_array_prepend
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpValueArray
modifier|*
name|gimp_value_array_append
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpValueArray
modifier|*
name|gimp_value_array_insert
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|,
name|gint
name|index
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpValueArray
modifier|*
name|gimp_value_array_remove
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_array_truncate
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|,
name|gint
name|n_values
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
comment|/* __GIMP_VALUE_ARRAY_H__ */
end_comment

end_unit

