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
DECL|macro|GIMP_IS_PARAM_SPEC_STRING (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_STRING
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_STRING))
end_define

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
DECL|macro|GIMP_IS_PARAM_SPEC_IMAGE_ID (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_IMAGE_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_IMAGE_ID))
end_define

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
DECL|macro|GIMP_IS_PARAM_SPEC_ITEM_ID (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_ITEM_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_ITEM_ID))
end_define

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
DECL|macro|GIMP_IS_PARAM_SPEC_DISPLAY_ID (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_DISPLAY_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_DISPLAY_ID))
end_define

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
comment|/*  * GIMP_TYPE_RGB  */
end_comment

begin_function_decl
name|void
name|gimp_value_get_rgb
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_set_rgb
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_PARASITE  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARASITE
define|#
directive|define
name|GIMP_TYPE_PARASITE
value|(gimp_parasite_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_PARASITE (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_PARASITE
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_PARASITE))
end_define

begin_decl_stmt
name|GType
name|gimp_parasite_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_PARASITE  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_PARASITE
define|#
directive|define
name|GIMP_TYPE_PARAM_PARASITE
value|(gimp_param_parasite_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_PARASITE (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_PARASITE
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_PARASITE))
end_define

begin_decl_stmt
name|GType
name|gimp_param_parasite_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_parasite
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PARAM_SPECS_H__  */
end_comment

end_unit

