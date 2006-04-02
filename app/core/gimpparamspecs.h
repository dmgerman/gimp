begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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
comment|/*  * GIMP_TYPE_PARAM_STRING  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_STRING
define|#
directive|define
name|GIMP_TYPE_PARAM_STRING
value|(gimp_param_string_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_STRING (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_STRING
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_STRING, GimpParamSpecString))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_STRING (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_STRING
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_STRING))
end_define

begin_typedef
DECL|typedef|GimpParamSpecString
typedef|typedef
name|struct
name|_GimpParamSpecString
name|GimpParamSpecString
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecString
struct|struct
name|_GimpParamSpecString
block|{
DECL|member|parent_instance
name|GParamSpecString
name|parent_instance
decl_stmt|;
DECL|member|no_validate
name|guint
name|no_validate
range|:
literal|1
decl_stmt|;
DECL|member|null_ok
name|guint
name|null_ok
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_string_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_string
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
name|gboolean
name|no_validate
parameter_list|,
name|gboolean
name|null_ok
parameter_list|,
specifier|const
name|gchar
modifier|*
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_PARAM_ENUM  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_ENUM
define|#
directive|define
name|GIMP_TYPE_PARAM_ENUM
value|(gimp_param_enum_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_ENUM (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_ENUM
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_ENUM, GimpParamSpecEnum))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_ENUM (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_ENUM
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_ENUM))
end_define

begin_typedef
DECL|typedef|GimpParamSpecEnum
typedef|typedef
name|struct
name|_GimpParamSpecEnum
name|GimpParamSpecEnum
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecEnum
struct|struct
name|_GimpParamSpecEnum
block|{
DECL|member|parent_instance
name|GParamSpecEnum
name|parent_instance
decl_stmt|;
DECL|member|excluded_values
name|GSList
modifier|*
name|excluded_values
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_enum_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_enum
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
name|GType
name|enum_type
parameter_list|,
name|gint
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_param_spec_enum_exclude_value
parameter_list|(
name|GimpParamSpecEnum
modifier|*
name|espec
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_PARAM_IMAGE_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_IMAGE_ID
define|#
directive|define
name|GIMP_TYPE_PARAM_IMAGE_ID
value|(gimp_param_image_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_IMAGE_ID (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_IMAGE_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_IMAGE_ID, GimpParamSpecImageID))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_IMAGE_ID (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_IMAGE_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_IMAGE_ID))
end_define

begin_typedef
DECL|typedef|GimpParamSpecImageID
typedef|typedef
name|struct
name|_GimpParamSpecImageID
name|GimpParamSpecImageID
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecImageID
struct|struct
name|_GimpParamSpecImageID
block|{
DECL|member|parent_instance
name|GParamSpecInt
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_image_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_image_id
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
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_value_get_image
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_image
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_PARAM_ITEM_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_ITEM_ID
define|#
directive|define
name|GIMP_TYPE_PARAM_ITEM_ID
value|(gimp_param_item_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_ITEM_ID (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_ITEM_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_ITEM_ID, GimpParamSpecItemID))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_ITEM_ID (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_ITEM_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_ITEM_ID))
end_define

begin_typedef
DECL|typedef|GimpParamSpecItemID
typedef|typedef
name|struct
name|_GimpParamSpecItemID
name|GimpParamSpecItemID
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecItemID
struct|struct
name|_GimpParamSpecItemID
block|{
DECL|member|parent_instance
name|GParamSpecInt
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|item_type
name|GType
name|item_type
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_item_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_item_id
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
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GType
name|item_type
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|gimp_value_get_item
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GType
name|item_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_item
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_PARAM_DISPLAY_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_DISPLAY_ID
define|#
directive|define
name|GIMP_TYPE_PARAM_DISPLAY_ID
value|(gimp_param_display_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_DISPLAY_ID (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_DISPLAY_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_DISPLAY_ID, GimpParamSpecDisplayID))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_DISPLAY_ID (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_DISPLAY_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_DISPLAY_ID))
end_define

begin_typedef
DECL|typedef|GimpParamSpecDisplayID
typedef|typedef
name|struct
name|_GimpParamSpecDisplayID
name|GimpParamSpecDisplayID
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecDisplayID
struct|struct
name|_GimpParamSpecDisplayID
block|{
DECL|member|parent_instance
name|GParamSpecInt
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_display_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_display_id
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
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpObject
modifier|*
name|gimp_value_get_display
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_display
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

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

begin_function_decl
specifier|const
name|guint8
modifier|*
name|gimp_value_get_int8array
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
name|gimp_value_dup_int8array
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
name|gimp_value_set_int8array
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
name|gimp_value_set_static_int8array
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
name|gimp_value_take_int8array
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

begin_function_decl
specifier|const
name|gint16
modifier|*
name|gimp_value_get_int16array
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
name|gimp_value_dup_int16array
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
name|gimp_value_set_int16array
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
name|gimp_value_set_static_int16array
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
name|gimp_value_take_int16array
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

begin_function_decl
specifier|const
name|gint32
modifier|*
name|gimp_value_get_int32array
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
name|gimp_value_dup_int32array
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
name|gimp_value_set_int32array
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
name|gimp_value_set_static_int32array
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
name|gimp_value_take_int32array
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

begin_function_decl
specifier|const
name|gdouble
modifier|*
name|gimp_value_get_floatarray
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
name|gimp_value_dup_floatarray
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
name|gimp_value_set_floatarray
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
name|gimp_value_set_static_floatarray
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
name|gimp_value_take_floatarray
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

begin_function_decl
name|GimpArray
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
name|GimpArray
modifier|*
name|gimp_string_array_copy
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
name|gimp_string_array_free
parameter_list|(
name|GimpArray
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
name|gimp_value_get_stringarray
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
name|gimp_value_dup_stringarray
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
name|gimp_value_set_stringarray
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
name|gimp_value_set_static_stringarray
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
name|gimp_value_take_stringarray
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PARAM_SPECS_H__  */
end_comment

end_unit

