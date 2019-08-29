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

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_comment
comment|/*  * GIMP_TYPE_PARAM_IMAGE  */
end_comment

begin_define
DECL|macro|GIMP_VALUE_HOLDS_IMAGE (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_IMAGE
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                          GIMP_TYPE_IMAGE))
end_define

begin_define
DECL|macro|GIMP_TYPE_PARAM_IMAGE
define|#
directive|define
name|GIMP_TYPE_PARAM_IMAGE
value|(gimp_param_image_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_IMAGE (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_IMAGE
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_IMAGE, GimpParamSpecImage))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_IMAGE (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_IMAGE
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_IMAGE))
end_define

begin_typedef
DECL|typedef|GimpParamSpecImage
typedef|typedef
name|struct
name|_GimpParamSpecImage
name|GimpParamSpecImage
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecImage
struct|struct
name|_GimpParamSpecImage
block|{
DECL|member|parent_instance
name|GParamSpecObject
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
name|gimp_param_image_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_image
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

begin_comment
comment|/*  * GIMP_TYPE_PARAM_ITEM  */
end_comment

begin_define
DECL|macro|GIMP_VALUE_HOLDS_ITEM (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_ITEM
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                         GIMP_TYPE_ITEM))
end_define

begin_define
DECL|macro|GIMP_TYPE_PARAM_ITEM
define|#
directive|define
name|GIMP_TYPE_PARAM_ITEM
value|(gimp_param_item_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_ITEM (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_ITEM
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_ITEM, GimpParamSpecItem))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_ITEM (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_ITEM
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_ITEM))
end_define

begin_typedef
DECL|typedef|GimpParamSpecItem
typedef|typedef
name|struct
name|_GimpParamSpecItem
name|GimpParamSpecItem
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecItem
struct|struct
name|_GimpParamSpecItem
block|{
DECL|member|parent_instance
name|GParamSpecObject
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
name|gimp_param_item_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_item
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

begin_comment
comment|/*  * GIMP_TYPE_PARAM_DRAWABLE  */
end_comment

begin_define
DECL|macro|GIMP_VALUE_HOLDS_DRAWABLE (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_DRAWABLE
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                             GIMP_TYPE_DRAWABLE))
end_define

begin_define
DECL|macro|GIMP_TYPE_PARAM_DRAWABLE
define|#
directive|define
name|GIMP_TYPE_PARAM_DRAWABLE
value|(gimp_param_drawable_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_DRAWABLE (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_DRAWABLE
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_DRAWABLE, GimpParamSpecDrawable))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_DRAWABLE (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_DRAWABLE
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_DRAWABLE))
end_define

begin_typedef
DECL|typedef|GimpParamSpecDrawable
typedef|typedef
name|struct
name|_GimpParamSpecDrawable
name|GimpParamSpecDrawable
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecDrawable
struct|struct
name|_GimpParamSpecDrawable
block|{
DECL|member|parent_instance
name|GimpParamSpecItem
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_drawable_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_drawable
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

begin_comment
comment|/*  * GIMP_TYPE_PARAM_LAYER  */
end_comment

begin_define
DECL|macro|GIMP_VALUE_HOLDS_LAYER (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_LAYER
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                          GIMP_TYPE_LAYER))
end_define

begin_define
DECL|macro|GIMP_TYPE_PARAM_LAYER
define|#
directive|define
name|GIMP_TYPE_PARAM_LAYER
value|(gimp_param_layer_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_LAYER (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_LAYER
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_LAYER, GimpParamSpecLayer))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_LAYER (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_LAYER
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_LAYER))
end_define

begin_typedef
DECL|typedef|GimpParamSpecLayer
typedef|typedef
name|struct
name|_GimpParamSpecLayer
name|GimpParamSpecLayer
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecLayer
struct|struct
name|_GimpParamSpecLayer
block|{
DECL|member|parent_instance
name|GimpParamSpecDrawable
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_layer_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_layer
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

begin_comment
comment|/*  * GIMP_TYPE_PARAM_CHANNEL  */
end_comment

begin_define
DECL|macro|GIMP_VALUE_HOLDS_CHANNEL (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_CHANNEL
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                            GIMP_TYPE_CHANNEL))
end_define

begin_define
DECL|macro|GIMP_TYPE_PARAM_CHANNEL
define|#
directive|define
name|GIMP_TYPE_PARAM_CHANNEL
value|(gimp_param_channel_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_CHANNEL (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_CHANNEL
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_CHANNEL, GimpParamSpecChannel))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_CHANNEL (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_CHANNEL
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_CHANNEL))
end_define

begin_typedef
DECL|typedef|GimpParamSpecChannel
typedef|typedef
name|struct
name|_GimpParamSpecChannel
name|GimpParamSpecChannel
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecChannel
struct|struct
name|_GimpParamSpecChannel
block|{
DECL|member|parent_instance
name|GimpParamSpecDrawable
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_channel_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_channel
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

begin_comment
comment|/*  * GIMP_TYPE_PARAM_LAYER_MASK  */
end_comment

begin_define
DECL|macro|GIMP_VALUE_HOLDS_LAYER_MASK (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_LAYER_MASK
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                               GIMP_TYPE_LAYER_MASK))
end_define

begin_define
DECL|macro|GIMP_TYPE_PARAM_LAYER_MASK
define|#
directive|define
name|GIMP_TYPE_PARAM_LAYER_MASK
value|(gimp_param_layer_mask_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_LAYER_MASK (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_LAYER_MASK
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_LAYER_MASK, GimpParamSpecLayerMask))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_LAYER_MASK (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_LAYER_MASK
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_LAYER_MASK))
end_define

begin_typedef
DECL|typedef|GimpParamSpecLayerMask
typedef|typedef
name|struct
name|_GimpParamSpecLayerMask
name|GimpParamSpecLayerMask
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecLayerMask
struct|struct
name|_GimpParamSpecLayerMask
block|{
DECL|member|parent_instance
name|GimpParamSpecChannel
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_layer_mask_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_layer_mask
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

begin_comment
comment|/*  * GIMP_TYPE_PARAM_SELECTION  */
end_comment

begin_define
DECL|macro|GIMP_VALUE_HOLDS_SELECTION (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_SELECTION
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                              GIMP_TYPE_SELECTION))
end_define

begin_define
DECL|macro|GIMP_TYPE_PARAM_SELECTION
define|#
directive|define
name|GIMP_TYPE_PARAM_SELECTION
value|(gimp_param_selection_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_SELECTION (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_SELECTION
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_SELECTION, GimpParamSpecSelection))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_SELECTION (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_SELECTION
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_SELECTION))
end_define

begin_typedef
DECL|typedef|GimpParamSpecSelection
typedef|typedef
name|struct
name|_GimpParamSpecSelection
name|GimpParamSpecSelection
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecSelection
struct|struct
name|_GimpParamSpecSelection
block|{
DECL|member|parent_instance
name|GimpParamSpecChannel
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_selection_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_selection
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

begin_comment
comment|/*  * GIMP_TYPE_PARAM_VECTORS  */
end_comment

begin_define
DECL|macro|GIMP_VALUE_HOLDS_VECTORS (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_VECTORS
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                            GIMP_TYPE_VECTORS))
end_define

begin_define
DECL|macro|GIMP_TYPE_PARAM_VECTORS
define|#
directive|define
name|GIMP_TYPE_PARAM_VECTORS
value|(gimp_param_vectors_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_VECTORS (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_VECTORS
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_VECTORS, GimpParamSpecVectors))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_VECTORS (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_VECTORS
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_VECTORS))
end_define

begin_typedef
DECL|typedef|GimpParamSpecVectors
typedef|typedef
name|struct
name|_GimpParamSpecVectors
name|GimpParamSpecVectors
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecVectors
struct|struct
name|_GimpParamSpecVectors
block|{
DECL|member|parent_instance
name|GimpParamSpecItem
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_vectors_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_vectors
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

begin_comment
comment|/*  * GIMP_TYPE_PARAM_DISPLAY  */
end_comment

begin_define
DECL|macro|GIMP_VALUE_HOLDS_DISPLAY (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_DISPLAY
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value),\                                            GIMP_TYPE_DISPLAY))
end_define

begin_define
DECL|macro|GIMP_TYPE_PARAM_DISPLAY
define|#
directive|define
name|GIMP_TYPE_PARAM_DISPLAY
value|(gimp_param_display_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_DISPLAY (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_DISPLAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_DISPLAY, GimpParamSpecDisplay))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_DISPLAY (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_DISPLAY
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_DISPLAY))
end_define

begin_typedef
DECL|typedef|GimpParamSpecDisplay
typedef|typedef
name|struct
name|_GimpParamSpecDisplay
name|GimpParamSpecDisplay
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecDisplay
struct|struct
name|_GimpParamSpecDisplay
block|{
DECL|member|parent_instance
name|GParamSpecObject
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
name|gimp_param_display_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_display
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

