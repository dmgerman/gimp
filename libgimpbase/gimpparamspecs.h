begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpparamspecs.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
name|__GIMP_PARAM_SPECS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PARAM_SPECS_H__
define|#
directive|define
name|__GIMP_PARAM_SPECS_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_comment
comment|/**  * GIMP_PARAM_NO_VALIDATE:  *  * Since 3.0  */
end_comment

begin_comment
comment|/*  * Keep in sync with libgimpconfig/gimpconfig-params.h  */
end_comment

begin_define
DECL|macro|GIMP_PARAM_NO_VALIDATE
define|#
directive|define
name|GIMP_PARAM_NO_VALIDATE
value|(1<< (6 + G_PARAM_USER_SHIFT))
end_define

begin_comment
comment|/**  * GIMP_PARAM_STATIC_STRINGS:  *  * Since: 2.4  **/
end_comment

begin_define
DECL|macro|GIMP_PARAM_STATIC_STRINGS
define|#
directive|define
name|GIMP_PARAM_STATIC_STRINGS
value|(G_PARAM_STATIC_NAME | \                                    G_PARAM_STATIC_NICK | \                                    G_PARAM_STATIC_BLURB)
end_define

begin_comment
comment|/**  * GIMP_PARAM_READABLE:  *  * Since: 2.4  **/
end_comment

begin_define
DECL|macro|GIMP_PARAM_READABLE
define|#
directive|define
name|GIMP_PARAM_READABLE
value|(G_PARAM_READABLE    | \                                    GIMP_PARAM_STATIC_STRINGS)
end_define

begin_comment
comment|/**  * GIMP_PARAM_WRITABLE:  *  * Since: 2.4  **/
end_comment

begin_define
DECL|macro|GIMP_PARAM_WRITABLE
define|#
directive|define
name|GIMP_PARAM_WRITABLE
value|(G_PARAM_WRITABLE    | \                                    GIMP_PARAM_STATIC_STRINGS)
end_define

begin_comment
comment|/**  * GIMP_PARAM_READWRITE:  *  * Since: 2.4  **/
end_comment

begin_define
DECL|macro|GIMP_PARAM_READWRITE
define|#
directive|define
name|GIMP_PARAM_READWRITE
value|(G_PARAM_READWRITE   | \                                    GIMP_PARAM_STATIC_STRINGS)
end_define

begin_comment
comment|/*  * GIMP_TYPE_ARRAY  */
end_comment

begin_typedef
DECL|typedef|GimpArray
typedef|typedef
name|struct
name|_GimpArray
name|GimpArray
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpArray
struct|struct
name|_GimpArray
block|{
DECL|member|data
name|guint8
modifier|*
name|data
decl_stmt|;
DECL|member|length
name|gsize
name|length
decl_stmt|;
DECL|member|static_data
name|gboolean
name|static_data
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GimpArray
modifier|*
name|gimp_array_new
parameter_list|(
specifier|const
name|guint8
modifier|*
name|data
parameter_list|,
name|gsize
name|length
parameter_list|,
name|gboolean
name|static_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpArray
modifier|*
name|gimp_array_copy
parameter_list|(
specifier|const
name|GimpArray
modifier|*
name|array
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_array_free
parameter_list|(
name|GimpArray
modifier|*
name|array
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|GIMP_TYPE_ARRAY
define|#
directive|define
name|GIMP_TYPE_ARRAY
value|(gimp_array_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_ARRAY (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_ARRAY
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_ARRAY))
end_define

begin_decl_stmt
name|GType
name|gimp_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_ARRAY  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_ARRAY
define|#
directive|define
name|GIMP_TYPE_PARAM_ARRAY
value|(gimp_param_array_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_ARRAY (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_ARRAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_ARRAY, GimpParamSpecArray))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_ARRAY (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_ARRAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_ARRAY))
end_define

begin_typedef
DECL|typedef|GimpParamSpecArray
typedef|typedef
name|struct
name|_GimpParamSpecArray
name|GimpParamSpecArray
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecArray
struct|struct
name|_GimpParamSpecArray
block|{
DECL|member|parent_instance
name|GParamSpecBoxed
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_array
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_UINT8_ARRAY  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_UINT8_ARRAY
define|#
directive|define
name|GIMP_TYPE_UINT8_ARRAY
value|(gimp_uint8_array_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_UINT8_ARRAY (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_UINT8_ARRAY
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_UINT8_ARRAY))
end_define

begin_decl_stmt
name|GType
name|gimp_uint8_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_UINT8_ARRAY  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_UINT8_ARRAY
define|#
directive|define
name|GIMP_TYPE_PARAM_UINT8_ARRAY
value|(gimp_param_uint8_array_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_UINT8_ARRAY (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_UINT8_ARRAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_UINT8_ARRAY, GimpParamSpecUInt8Array))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_UINT8_ARRAY (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_UINT8_ARRAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_UINT8_ARRAY))
end_define

begin_typedef
DECL|typedef|GimpParamSpecUInt8Array
typedef|typedef
name|struct
name|_GimpParamSpecUInt8Array
name|GimpParamSpecUInt8Array
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecUInt8Array
struct|struct
name|_GimpParamSpecUInt8Array
block|{
DECL|member|parent_instance
name|GimpParamSpecArray
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_uint8_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_uint8_array
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|guint8
modifier|*
name|gimp_value_get_uint8_array
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint8
modifier|*
name|gimp_value_dup_uint8_array
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_uint8_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
specifier|const
name|guint8
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_static_uint8_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
specifier|const
name|guint8
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_take_uint8_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|guint8
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_INT16_ARRAY  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_INT16_ARRAY
define|#
directive|define
name|GIMP_TYPE_INT16_ARRAY
value|(gimp_int16_array_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_INT16_ARRAY (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_INT16_ARRAY
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_INT16_ARRAY))
end_define

begin_decl_stmt
name|GType
name|gimp_int16_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_INT16_ARRAY  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_INT16_ARRAY
define|#
directive|define
name|GIMP_TYPE_PARAM_INT16_ARRAY
value|(gimp_param_int16_array_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_INT16_ARRAY (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_INT16_ARRAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_INT16_ARRAY, GimpParamSpecInt16Array))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_INT16_ARRAY (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_INT16_ARRAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_INT16_ARRAY))
end_define

begin_typedef
DECL|typedef|GimpParamSpecInt16Array
typedef|typedef
name|struct
name|_GimpParamSpecInt16Array
name|GimpParamSpecInt16Array
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecInt16Array
struct|struct
name|_GimpParamSpecInt16Array
block|{
DECL|member|parent_instance
name|GimpParamSpecArray
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_int16_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_int16_array
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gint16
modifier|*
name|gimp_value_get_int16_array
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint16
modifier|*
name|gimp_value_dup_int16_array
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_int16_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
specifier|const
name|gint16
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_static_int16_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
specifier|const
name|gint16
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_take_int16_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|gint16
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_INT32_ARRAY  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_INT32_ARRAY
define|#
directive|define
name|GIMP_TYPE_INT32_ARRAY
value|(gimp_int32_array_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_INT32_ARRAY (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_INT32_ARRAY
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_INT32_ARRAY))
end_define

begin_decl_stmt
name|GType
name|gimp_int32_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_INT32_ARRAY  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_INT32_ARRAY
define|#
directive|define
name|GIMP_TYPE_PARAM_INT32_ARRAY
value|(gimp_param_int32_array_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_INT32_ARRAY (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_INT32_ARRAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_INT32_ARRAY, GimpParamSpecInt32Array))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_INT32_ARRAY (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_INT32_ARRAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_INT32_ARRAY))
end_define

begin_typedef
DECL|typedef|GimpParamSpecInt32Array
typedef|typedef
name|struct
name|_GimpParamSpecInt32Array
name|GimpParamSpecInt32Array
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecInt32Array
struct|struct
name|_GimpParamSpecInt32Array
block|{
DECL|member|parent_instance
name|GimpParamSpecArray
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_int32_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_int32_array
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gint32
modifier|*
name|gimp_value_get_int32_array
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
modifier|*
name|gimp_value_dup_int32_array
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_int32_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
specifier|const
name|gint32
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_static_int32_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
specifier|const
name|gint32
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_take_int32_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|gint32
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_FLOAT_ARRAY  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_FLOAT_ARRAY
define|#
directive|define
name|GIMP_TYPE_FLOAT_ARRAY
value|(gimp_float_array_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_FLOAT_ARRAY (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_FLOAT_ARRAY
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_FLOAT_ARRAY))
end_define

begin_decl_stmt
name|GType
name|gimp_float_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_FLOAT_ARRAY  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_FLOAT_ARRAY
define|#
directive|define
name|GIMP_TYPE_PARAM_FLOAT_ARRAY
value|(gimp_param_float_array_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_FLOAT_ARRAY (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_FLOAT_ARRAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_FLOAT_ARRAY, GimpParamSpecFloatArray))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_FLOAT_ARRAY (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_FLOAT_ARRAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_FLOAT_ARRAY))
end_define

begin_typedef
DECL|typedef|GimpParamSpecFloatArray
typedef|typedef
name|struct
name|_GimpParamSpecFloatArray
name|GimpParamSpecFloatArray
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecFloatArray
struct|struct
name|_GimpParamSpecFloatArray
block|{
DECL|member|parent_instance
name|GimpParamSpecArray
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_float_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_float_array
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gdouble
modifier|*
name|gimp_value_get_float_array
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
modifier|*
name|gimp_value_dup_float_array
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_float_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_static_float_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_take_float_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|gdouble
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_STRING_ARRAY  */
end_comment

begin_typedef
DECL|typedef|GimpStringArray
typedef|typedef
name|struct
name|_GimpArray
name|GimpStringArray
typedef|;
end_typedef

begin_function_decl
name|GimpStringArray
modifier|*
name|gimp_string_array_new
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|data
parameter_list|,
name|gsize
name|length
parameter_list|,
name|gboolean
name|static_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpStringArray
modifier|*
name|gimp_string_array_copy
parameter_list|(
specifier|const
name|GimpStringArray
modifier|*
name|array
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_string_array_free
parameter_list|(
name|GimpStringArray
modifier|*
name|array
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|GIMP_TYPE_STRING_ARRAY
define|#
directive|define
name|GIMP_TYPE_STRING_ARRAY
value|(gimp_string_array_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_STRING_ARRAY (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_STRING_ARRAY
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_STRING_ARRAY))
end_define

begin_decl_stmt
name|GType
name|gimp_string_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_STRING_ARRAY  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_STRING_ARRAY
define|#
directive|define
name|GIMP_TYPE_PARAM_STRING_ARRAY
value|(gimp_param_string_array_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_STRING_ARRAY (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_STRING_ARRAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_STRING_ARRAY, GimpParamSpecStringArray))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_STRING_ARRAY (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_STRING_ARRAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_STRING_ARRAY))
end_define

begin_typedef
DECL|typedef|GimpParamSpecStringArray
typedef|typedef
name|struct
name|_GimpParamSpecStringArray
name|GimpParamSpecStringArray
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecStringArray
struct|struct
name|_GimpParamSpecStringArray
block|{
DECL|member|parent_instance
name|GParamSpecBoxed
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_string_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_string_array
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
modifier|*
name|gimp_value_get_string_array
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gimp_value_dup_string_array
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_string_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_static_string_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_take_string_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|gchar
modifier|*
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_RGB_ARRAY  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_RGB_ARRAY
define|#
directive|define
name|GIMP_TYPE_RGB_ARRAY
value|(gimp_rgb_array_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_RGB_ARRAY (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_RGB_ARRAY
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_RGB_ARRAY))
end_define

begin_decl_stmt
name|GType
name|gimp_rgb_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_RGB_ARRAY  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_RGB_ARRAY
define|#
directive|define
name|GIMP_TYPE_PARAM_RGB_ARRAY
value|(gimp_param_rgb_array_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_RGB_ARRAY (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_RGB_ARRAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_RGB_ARRAY, GimpParamSpecRGBArray))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_RGB_ARRAY (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_RGB_ARRAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_RGB_ARRAY))
end_define

begin_typedef
DECL|typedef|GimpParamSpecRGBArray
typedef|typedef
name|struct
name|_GimpParamSpecRGBArray
name|GimpParamSpecRGBArray
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecRGBArray
struct|struct
name|_GimpParamSpecRGBArray
block|{
DECL|member|parent_instance
name|GParamSpecBoxed
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_rgb_array_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_rgb_array
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpRGB
modifier|*
name|gimp_value_get_rgb_array
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpRGB
modifier|*
name|gimp_value_dup_rgb_array
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_rgb_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_static_rgb_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|array
parameter_list|,
name|gsize
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_take_rgb_array
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GimpRGB
modifier|*
name|array
parameter_list|,
name|gsize
name|length
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
comment|/*  __GIMP_PARAM_SPECS_H__  */
end_comment

end_unit

