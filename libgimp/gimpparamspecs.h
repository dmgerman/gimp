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
name|__GIMP_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimp.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__LIBGIMP_GIMP_PARAM_SPECS_H__
end_ifndef

begin_define
DECL|macro|__LIBGIMP_GIMP_PARAM_SPECS_H__
define|#
directive|define
name|__LIBGIMP_GIMP_PARAM_SPECS_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
comment|/*  * GIMP_TYPE_IMAGE_ID  */
DECL|macro|GIMP_TYPE_IMAGE_ID
define|#
directive|define
name|GIMP_TYPE_IMAGE_ID
value|(gimp_image_id_get_type ())
DECL|macro|GIMP_VALUE_HOLDS_IMAGE_ID (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_IMAGE_ID
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                           GIMP_TYPE_IMAGE_ID))
name|GType
name|gimp_image_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

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
DECL|member|none_ok
name|gboolean
name|none_ok
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
name|gboolean
name|none_ok
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_value_get_image_id
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
name|gimp_value_set_image_id
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|gint32
name|image_id
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_ITEM_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_ITEM_ID
define|#
directive|define
name|GIMP_TYPE_ITEM_ID
value|(gimp_item_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_ITEM_ID (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_ITEM_ID
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                          GIMP_TYPE_ITEM_ID))
end_define

begin_decl_stmt
name|GType
name|gimp_item_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

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
DECL|member|none_ok
name|gboolean
name|none_ok
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
name|gboolean
name|none_ok
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_value_get_item_id
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
name|gimp_value_set_item_id
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|gint32
name|item_id
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_DRAWABLE_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_DRAWABLE_ID
define|#
directive|define
name|GIMP_TYPE_DRAWABLE_ID
value|(gimp_drawable_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_DRAWABLE_ID (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_DRAWABLE_ID
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                              GIMP_TYPE_DRAWABLE_ID))
end_define

begin_decl_stmt
name|GType
name|gimp_drawable_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_DRAWABLE_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_DRAWABLE_ID
define|#
directive|define
name|GIMP_TYPE_PARAM_DRAWABLE_ID
value|(gimp_param_drawable_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_DRAWABLE_ID (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_DRAWABLE_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_DRAWABLE_ID, GimpParamSpecDrawableID))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_DRAWABLE_ID (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_DRAWABLE_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_DRAWABLE_ID))
end_define

begin_typedef
DECL|typedef|GimpParamSpecDrawableID
typedef|typedef
name|struct
name|_GimpParamSpecDrawableID
name|GimpParamSpecDrawableID
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecDrawableID
struct|struct
name|_GimpParamSpecDrawableID
block|{
DECL|member|parent_instance
name|GimpParamSpecItemID
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_drawable_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_drawable_id
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
name|none_ok
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_value_get_drawable_id
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
name|gimp_value_set_drawable_id
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|gint32
name|drawable_id
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_LAYER_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_LAYER_ID
define|#
directive|define
name|GIMP_TYPE_LAYER_ID
value|(gimp_layer_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_LAYER_ID (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_LAYER_ID
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                           GIMP_TYPE_LAYER_ID))
end_define

begin_decl_stmt
name|GType
name|gimp_layer_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_LAYER_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_LAYER_ID
define|#
directive|define
name|GIMP_TYPE_PARAM_LAYER_ID
value|(gimp_param_layer_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_LAYER_ID (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_LAYER_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_LAYER_ID, GimpParamSpecLayerID))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_LAYER_ID (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_LAYER_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_LAYER_ID))
end_define

begin_typedef
DECL|typedef|GimpParamSpecLayerID
typedef|typedef
name|struct
name|_GimpParamSpecLayerID
name|GimpParamSpecLayerID
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecLayerID
struct|struct
name|_GimpParamSpecLayerID
block|{
DECL|member|parent_instance
name|GimpParamSpecDrawableID
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_layer_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_layer_id
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
name|none_ok
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_value_get_layer_id
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
name|gimp_value_set_layer_id
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|gint32
name|layer_id
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_CHANNEL_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_CHANNEL_ID
define|#
directive|define
name|GIMP_TYPE_CHANNEL_ID
value|(gimp_channel_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_CHANNEL_ID (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_CHANNEL_ID
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                             GIMP_TYPE_CHANNEL_ID))
end_define

begin_decl_stmt
name|GType
name|gimp_channel_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_CHANNEL_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_CHANNEL_ID
define|#
directive|define
name|GIMP_TYPE_PARAM_CHANNEL_ID
value|(gimp_param_channel_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_CHANNEL_ID (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_CHANNEL_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_CHANNEL_ID, GimpParamSpecChannelID))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_CHANNEL_ID (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_CHANNEL_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_CHANNEL_ID))
end_define

begin_typedef
DECL|typedef|GimpParamSpecChannelID
typedef|typedef
name|struct
name|_GimpParamSpecChannelID
name|GimpParamSpecChannelID
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecChannelID
struct|struct
name|_GimpParamSpecChannelID
block|{
DECL|member|parent_instance
name|GimpParamSpecDrawableID
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_channel_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_channel_id
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
name|none_ok
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_value_get_channel_id
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
name|gimp_value_set_channel_id
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|gint32
name|channel_id
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_LAYER_MASK_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_LAYER_MASK_ID
define|#
directive|define
name|GIMP_TYPE_LAYER_MASK_ID
value|(gimp_layer_mask_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_LAYER_MASK_ID (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_LAYER_MASK_ID
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                                GIMP_TYPE_LAYER_MASK_ID))
end_define

begin_decl_stmt
name|GType
name|gimp_layer_mask_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_LAYER_MASK_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_LAYER_MASK_ID
define|#
directive|define
name|GIMP_TYPE_PARAM_LAYER_MASK_ID
value|(gimp_param_layer_mask_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_LAYER_MASK_ID (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_LAYER_MASK_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_LAYER_MASK_ID, GimpParamSpecLayerMaskID))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_LAYER_MASK_ID (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_LAYER_MASK_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_LAYER_MASK_ID))
end_define

begin_typedef
DECL|typedef|GimpParamSpecLayerMaskID
typedef|typedef
name|struct
name|_GimpParamSpecLayerMaskID
name|GimpParamSpecLayerMaskID
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecLayerMaskID
struct|struct
name|_GimpParamSpecLayerMaskID
block|{
DECL|member|parent_instance
name|GimpParamSpecChannelID
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_layer_mask_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_layer_mask_id
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
name|none_ok
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_value_get_layer_mask_id
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
name|gimp_value_set_layer_mask_id
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|gint32
name|layer_mask_id
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_SELECTION_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_SELECTION_ID
define|#
directive|define
name|GIMP_TYPE_SELECTION_ID
value|(gimp_selection_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_SELECTION_ID (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_SELECTION_ID
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                               GIMP_TYPE_SELECTION_ID))
end_define

begin_decl_stmt
name|GType
name|gimp_selection_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_SELECTION_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_SELECTION_ID
define|#
directive|define
name|GIMP_TYPE_PARAM_SELECTION_ID
value|(gimp_param_selection_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_SELECTION_ID (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_SELECTION_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_SELECTION_ID, GimpParamSpecSelectionID))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_SELECTION_ID (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_SELECTION_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_SELECTION_ID))
end_define

begin_typedef
DECL|typedef|GimpParamSpecSelectionID
typedef|typedef
name|struct
name|_GimpParamSpecSelectionID
name|GimpParamSpecSelectionID
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecSelectionID
struct|struct
name|_GimpParamSpecSelectionID
block|{
DECL|member|parent_instance
name|GimpParamSpecChannelID
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_selection_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_selection_id
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
name|none_ok
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_value_get_selection_id
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
name|gimp_value_set_selection_id
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|gint32
name|selection_id
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_VECTORS_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_VECTORS_ID
define|#
directive|define
name|GIMP_TYPE_VECTORS_ID
value|(gimp_vectors_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_VECTORS_ID (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_VECTORS_ID
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                             GIMP_TYPE_VECTORS_ID))
end_define

begin_decl_stmt
name|GType
name|gimp_vectors_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_VECTORS_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_VECTORS_ID
define|#
directive|define
name|GIMP_TYPE_PARAM_VECTORS_ID
value|(gimp_param_vectors_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_VECTORS_ID (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_VECTORS_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_VECTORS_ID, GimpParamSpecVectorsID))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_VECTORS_ID (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_VECTORS_ID
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_VECTORS_ID))
end_define

begin_typedef
DECL|typedef|GimpParamSpecVectorsID
typedef|typedef
name|struct
name|_GimpParamSpecVectorsID
name|GimpParamSpecVectorsID
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecVectorsID
struct|struct
name|_GimpParamSpecVectorsID
block|{
DECL|member|parent_instance
name|GimpParamSpecItemID
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_vectors_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_vectors_id
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
name|none_ok
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_value_get_vectors_id
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
name|gimp_value_set_vectors_id
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|gint32
name|vectors_id
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_DISPLAY_ID  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_DISPLAY_ID
define|#
directive|define
name|GIMP_TYPE_DISPLAY_ID
value|(gimp_display_id_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_DISPLAY_ID (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_DISPLAY_ID
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                             GIMP_TYPE_DISPLAY_ID))
end_define

begin_decl_stmt
name|GType
name|gimp_display_id_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

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
DECL|member|none_ok
name|gboolean
name|none_ok
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
name|gboolean
name|none_ok
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_value_get_display_id
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
name|gimp_value_set_display_id
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|,
name|gint32
name|display_id
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
comment|/*  __LIBGIMP_GIMP_PARAM_SPECS_H__  */
end_comment

end_unit

