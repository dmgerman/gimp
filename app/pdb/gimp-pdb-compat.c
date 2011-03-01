begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"gimp-pdb-compat.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GParamSpec
modifier|*
DECL|function|gimp_pdb_compat_param_spec (Gimp * gimp,GimpPDBArgType arg_type,const gchar * name,const gchar * desc)
name|gimp_pdb_compat_param_spec
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPDBArgType
name|arg_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|pspec
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|arg_type
condition|)
block|{
case|case
name|GIMP_PDB_INT32
case|:
name|pspec
operator|=
name|gimp_param_spec_int32
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT16
case|:
name|pspec
operator|=
name|gimp_param_spec_int16
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_MININT16
argument_list|,
name|G_MAXINT16
argument_list|,
literal|0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT8
case|:
name|pspec
operator|=
name|gimp_param_spec_int8
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
literal|0
argument_list|,
name|G_MAXUINT8
argument_list|,
literal|0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_FLOAT
case|:
name|pspec
operator|=
name|g_param_spec_double
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
operator|-
name|G_MAXDOUBLE
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|0.0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STRING
case|:
name|pspec
operator|=
name|gimp_param_spec_string
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT32ARRAY
case|:
name|pspec
operator|=
name|gimp_param_spec_int32_array
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT16ARRAY
case|:
name|pspec
operator|=
name|gimp_param_spec_int16_array
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_INT8ARRAY
case|:
name|pspec
operator|=
name|gimp_param_spec_int8_array
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_FLOATARRAY
case|:
name|pspec
operator|=
name|gimp_param_spec_float_array
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STRINGARRAY
case|:
name|pspec
operator|=
name|gimp_param_spec_string_array
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_COLOR
case|:
name|pspec
operator|=
name|gimp_param_spec_rgb
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_ITEM
case|:
name|pspec
operator|=
name|gimp_param_spec_item_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|TRUE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_DISPLAY
case|:
name|pspec
operator|=
name|gimp_param_spec_display_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|TRUE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_IMAGE
case|:
name|pspec
operator|=
name|gimp_param_spec_image_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|TRUE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_LAYER
case|:
name|pspec
operator|=
name|gimp_param_spec_layer_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|TRUE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_CHANNEL
case|:
name|pspec
operator|=
name|gimp_param_spec_channel_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|TRUE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_DRAWABLE
case|:
name|pspec
operator|=
name|gimp_param_spec_drawable_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|TRUE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_SELECTION
case|:
name|pspec
operator|=
name|gimp_param_spec_selection_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|TRUE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_COLORARRAY
case|:
name|pspec
operator|=
name|gimp_param_spec_color_array
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_VECTORS
case|:
name|pspec
operator|=
name|gimp_param_spec_vectors_id
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|gimp
argument_list|,
name|TRUE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_PARASITE
case|:
name|pspec
operator|=
name|gimp_param_spec_parasite
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_STATUS
case|:
name|pspec
operator|=
name|g_param_spec_enum
argument_list|(
name|name
argument_list|,
name|name
argument_list|,
name|desc
argument_list|,
name|GIMP_TYPE_PDB_STATUS_TYPE
argument_list|,
name|GIMP_PDB_EXECUTION_ERROR
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_END
case|:
break|break;
block|}
if|if
condition|(
operator|!
name|pspec
condition|)
name|g_warning
argument_list|(
literal|"%s: returning NULL for %s (%s)"
argument_list|,
name|G_STRFUNC
argument_list|,
name|name
argument_list|,
name|gimp_pdb_compat_arg_type_to_string
argument_list|(
name|arg_type
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|pspec
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_pdb_compat_arg_type_to_gtype (GimpPDBArgType type)
name|gimp_pdb_compat_arg_type_to_gtype
parameter_list|(
name|GimpPDBArgType
name|type
parameter_list|)
block|{
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_PDB_INT32
case|:
return|return
name|GIMP_TYPE_INT32
return|;
case|case
name|GIMP_PDB_INT16
case|:
return|return
name|GIMP_TYPE_INT16
return|;
case|case
name|GIMP_PDB_INT8
case|:
return|return
name|GIMP_TYPE_INT8
return|;
case|case
name|GIMP_PDB_FLOAT
case|:
return|return
name|G_TYPE_DOUBLE
return|;
case|case
name|GIMP_PDB_STRING
case|:
return|return
name|G_TYPE_STRING
return|;
case|case
name|GIMP_PDB_INT32ARRAY
case|:
return|return
name|GIMP_TYPE_INT32_ARRAY
return|;
case|case
name|GIMP_PDB_INT16ARRAY
case|:
return|return
name|GIMP_TYPE_INT16_ARRAY
return|;
case|case
name|GIMP_PDB_INT8ARRAY
case|:
return|return
name|GIMP_TYPE_INT8_ARRAY
return|;
case|case
name|GIMP_PDB_FLOATARRAY
case|:
return|return
name|GIMP_TYPE_FLOAT_ARRAY
return|;
case|case
name|GIMP_PDB_STRINGARRAY
case|:
return|return
name|GIMP_TYPE_STRING_ARRAY
return|;
case|case
name|GIMP_PDB_COLOR
case|:
return|return
name|GIMP_TYPE_RGB
return|;
case|case
name|GIMP_PDB_ITEM
case|:
return|return
name|GIMP_TYPE_ITEM_ID
return|;
case|case
name|GIMP_PDB_DISPLAY
case|:
return|return
name|GIMP_TYPE_DISPLAY_ID
return|;
case|case
name|GIMP_PDB_IMAGE
case|:
return|return
name|GIMP_TYPE_IMAGE_ID
return|;
case|case
name|GIMP_PDB_LAYER
case|:
return|return
name|GIMP_TYPE_LAYER_ID
return|;
case|case
name|GIMP_PDB_CHANNEL
case|:
return|return
name|GIMP_TYPE_CHANNEL_ID
return|;
case|case
name|GIMP_PDB_DRAWABLE
case|:
return|return
name|GIMP_TYPE_DRAWABLE_ID
return|;
case|case
name|GIMP_PDB_SELECTION
case|:
return|return
name|GIMP_TYPE_SELECTION_ID
return|;
case|case
name|GIMP_PDB_COLORARRAY
case|:
return|return
name|GIMP_TYPE_COLOR_ARRAY
return|;
case|case
name|GIMP_PDB_VECTORS
case|:
return|return
name|GIMP_TYPE_VECTORS_ID
return|;
case|case
name|GIMP_PDB_PARASITE
case|:
return|return
name|GIMP_TYPE_PARASITE
return|;
case|case
name|GIMP_PDB_STATUS
case|:
return|return
name|GIMP_TYPE_PDB_STATUS_TYPE
return|;
case|case
name|GIMP_PDB_END
case|:
break|break;
block|}
name|g_warning
argument_list|(
literal|"%s: returning G_TYPE_NONE for %d (%s)"
argument_list|,
name|G_STRFUNC
argument_list|,
name|type
argument_list|,
name|gimp_pdb_compat_arg_type_to_string
argument_list|(
name|type
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|G_TYPE_NONE
return|;
block|}
end_function

begin_function
name|GimpPDBArgType
DECL|function|gimp_pdb_compat_arg_type_from_gtype (GType type)
name|gimp_pdb_compat_arg_type_from_gtype
parameter_list|(
name|GType
name|type
parameter_list|)
block|{
specifier|static
name|GQuark
name|pdb_type_quark
init|=
literal|0
decl_stmt|;
name|GimpPDBArgType
name|pdb_type
decl_stmt|;
if|if
condition|(
operator|!
name|pdb_type_quark
condition|)
block|{
struct|struct
DECL|struct|__anon2934cdc80108
block|{
DECL|member|g_type
name|GType
name|g_type
decl_stmt|;
DECL|member|pdb_type
name|GimpPDBArgType
name|pdb_type
decl_stmt|;
block|}
name|type_mapping
index|[]
init|=
block|{
block|{
name|GIMP_TYPE_INT32
block|,
name|GIMP_PDB_INT32
block|}
block|,
block|{
name|G_TYPE_INT
block|,
name|GIMP_PDB_INT32
block|}
block|,
block|{
name|G_TYPE_UINT
block|,
name|GIMP_PDB_INT32
block|}
block|,
block|{
name|G_TYPE_ENUM
block|,
name|GIMP_PDB_INT32
block|}
block|,
block|{
name|G_TYPE_BOOLEAN
block|,
name|GIMP_PDB_INT32
block|}
block|,
block|{
name|GIMP_TYPE_INT16
block|,
name|GIMP_PDB_INT16
block|}
block|,
block|{
name|GIMP_TYPE_INT8
block|,
name|GIMP_PDB_INT8
block|}
block|,
block|{
name|G_TYPE_DOUBLE
block|,
name|GIMP_PDB_FLOAT
block|}
block|,
block|{
name|G_TYPE_STRING
block|,
name|GIMP_PDB_STRING
block|}
block|,
block|{
name|GIMP_TYPE_RGB
block|,
name|GIMP_PDB_COLOR
block|}
block|,
block|{
name|GIMP_TYPE_INT32_ARRAY
block|,
name|GIMP_PDB_INT32ARRAY
block|}
block|,
block|{
name|GIMP_TYPE_INT16_ARRAY
block|,
name|GIMP_PDB_INT16ARRAY
block|}
block|,
block|{
name|GIMP_TYPE_INT8_ARRAY
block|,
name|GIMP_PDB_INT8ARRAY
block|}
block|,
block|{
name|GIMP_TYPE_FLOAT_ARRAY
block|,
name|GIMP_PDB_FLOATARRAY
block|}
block|,
block|{
name|GIMP_TYPE_STRING_ARRAY
block|,
name|GIMP_PDB_STRINGARRAY
block|}
block|,
block|{
name|GIMP_TYPE_COLOR_ARRAY
block|,
name|GIMP_PDB_COLORARRAY
block|}
block|,
block|{
name|GIMP_TYPE_DISPLAY_ID
block|,
name|GIMP_PDB_DISPLAY
block|}
block|,
block|{
name|GIMP_TYPE_IMAGE_ID
block|,
name|GIMP_PDB_IMAGE
block|}
block|,
block|{
name|GIMP_TYPE_LAYER_ID
block|,
name|GIMP_PDB_LAYER
block|}
block|,
block|{
name|GIMP_TYPE_CHANNEL_ID
block|,
name|GIMP_PDB_CHANNEL
block|}
block|,
block|{
name|GIMP_TYPE_DRAWABLE_ID
block|,
name|GIMP_PDB_DRAWABLE
block|}
block|,
block|{
name|GIMP_TYPE_SELECTION_ID
block|,
name|GIMP_PDB_SELECTION
block|}
block|,
block|{
name|GIMP_TYPE_LAYER_MASK_ID
block|,
name|GIMP_PDB_CHANNEL
block|}
block|,
block|{
name|GIMP_TYPE_VECTORS_ID
block|,
name|GIMP_PDB_VECTORS
block|}
block|,
block|{
name|GIMP_TYPE_PARASITE
block|,
name|GIMP_PDB_PARASITE
block|}
block|,
block|{
name|GIMP_TYPE_PDB_STATUS_TYPE
block|,
name|GIMP_PDB_STATUS
block|}
block|}
struct|;
name|gint
name|i
decl_stmt|;
name|pdb_type_quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-pdb-type"
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|type_mapping
argument_list|)
condition|;
name|i
operator|++
control|)
name|g_type_set_qdata
argument_list|(
name|type_mapping
index|[
name|i
index|]
operator|.
name|g_type
argument_list|,
name|pdb_type_quark
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|type_mapping
index|[
name|i
index|]
operator|.
name|pdb_type
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|pdb_type
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_type_get_qdata
argument_list|(
name|type
argument_list|,
name|pdb_type_quark
argument_list|)
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|g_printerr ("%s: arg_type = %p (%s)  ->  %d (%s)\n",               G_STRFUNC,               (gpointer) type, g_type_name (type),               pdb_type, gimp_pdb_arg_type_to_string (pdb_type));
endif|#
directive|endif
return|return
name|pdb_type
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_pdb_compat_arg_type_to_string (GimpPDBArgType type)
name|gimp_pdb_compat_arg_type_to_string
parameter_list|(
name|GimpPDBArgType
name|type
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_PDB_ARG_TYPE
argument_list|,
name|type
argument_list|,
operator|&
name|name
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
literal|"(PDB type %d unknown)"
argument_list|,
name|type
argument_list|)
return|;
block|}
return|return
name|g_strdup
argument_list|(
name|name
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_pdb_compat_procs_register (GimpPDB * pdb,GimpPDBCompatMode compat_mode)
name|gimp_pdb_compat_procs_register
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
name|GimpPDBCompatMode
name|compat_mode
parameter_list|)
block|{
specifier|static
specifier|const
struct|struct
DECL|struct|__anon2934cdc80208
block|{
DECL|member|old_name
specifier|const
name|gchar
modifier|*
name|old_name
decl_stmt|;
DECL|member|new_name
specifier|const
name|gchar
modifier|*
name|new_name
decl_stmt|;
block|}
name|compat_procs
index|[]
init|=
block|{
block|{
literal|"gimp-blend"
block|,
literal|"gimp-edit-blend"
block|}
block|,
block|{
literal|"gimp-brushes-list"
block|,
literal|"gimp-brushes-get-list"
block|}
block|,
block|{
literal|"gimp-bucket-fill"
block|,
literal|"gimp-edit-bucket-fill"
block|}
block|,
block|{
literal|"gimp-channel-delete"
block|,
literal|"gimp-item-delete"
block|}
block|,
block|{
literal|"gimp-channel-get-name"
block|,
literal|"gimp-item-get-name"
block|}
block|,
block|{
literal|"gimp-channel-get-tattoo"
block|,
literal|"gimp-item-get-tattoo"
block|}
block|,
block|{
literal|"gimp-channel-get-visible"
block|,
literal|"gimp-item-get-visible"
block|}
block|,
block|{
literal|"gimp-channel-set-name"
block|,
literal|"gimp-item-set-name"
block|}
block|,
block|{
literal|"gimp-channel-set-tattoo"
block|,
literal|"gimp-item-set-tattoo"
block|}
block|,
block|{
literal|"gimp-channel-set-visible"
block|,
literal|"gimp-item-set-visible"
block|}
block|,
block|{
literal|"gimp-color-picker"
block|,
literal|"gimp-image-pick-color"
block|}
block|,
block|{
literal|"gimp-convert-grayscale"
block|,
literal|"gimp-image-convert-grayscale"
block|}
block|,
block|{
literal|"gimp-convert-indexed"
block|,
literal|"gimp-image-convert-indexed"
block|}
block|,
block|{
literal|"gimp-convert-rgb"
block|,
literal|"gimp-image-convert-rgb"
block|}
block|,
block|{
literal|"gimp-crop"
block|,
literal|"gimp-image-crop"
block|}
block|,
block|{
literal|"gimp-drawable-bytes"
block|,
literal|"gimp-drawable-bpp"
block|}
block|,
block|{
literal|"gimp-drawable-image"
block|,
literal|"gimp-drawable-get-image"
block|}
block|,
block|{
literal|"gimp-image-active-drawable"
block|,
literal|"gimp-image-get-active-drawable"
block|}
block|,
block|{
literal|"gimp-image-floating-selection"
block|,
literal|"gimp-image-get-floating-sel"
block|}
block|,
block|{
literal|"gimp-layer-delete"
block|,
literal|"gimp-item-delete"
block|}
block|,
block|{
literal|"gimp-layer-get-linked"
block|,
literal|"gimp-item-get-linked"
block|}
block|,
block|{
literal|"gimp-layer-get-name"
block|,
literal|"gimp-item-get-name"
block|}
block|,
block|{
literal|"gimp-layer-get-tattoo"
block|,
literal|"gimp-item-get-tattoo"
block|}
block|,
block|{
literal|"gimp-layer-get-visible"
block|,
literal|"gimp-item-get-visible"
block|}
block|,
block|{
literal|"gimp-layer-mask"
block|,
literal|"gimp-layer-get-mask"
block|}
block|,
block|{
literal|"gimp-layer-set-linked"
block|,
literal|"gimp-item-set-linked"
block|}
block|,
block|{
literal|"gimp-layer-set-name"
block|,
literal|"gimp-item-set-name"
block|}
block|,
block|{
literal|"gimp-layer-set-tattoo"
block|,
literal|"gimp-item-set-tattoo"
block|}
block|,
block|{
literal|"gimp-layer-set-visible"
block|,
literal|"gimp-item-set-visible"
block|}
block|,
block|{
literal|"gimp-palette-refresh"
block|,
literal|"gimp-palettes-refresh"
block|}
block|,
block|{
literal|"gimp-patterns-list"
block|,
literal|"gimp-patterns-get-list"
block|}
block|,
block|{
literal|"gimp-temp-PDB-name"
block|,
literal|"gimp-procedural-db-temp-name"
block|}
block|,
block|{
literal|"gimp-undo-push-group-end"
block|,
literal|"gimp-image-undo-group-end"
block|}
block|,
block|{
literal|"gimp-undo-push-group-start"
block|,
literal|"gimp-image-undo-group-start"
block|}
block|,
comment|/*  deprecations since 2.0  */
block|{
literal|"gimp-brushes-get-opacity"
block|,
literal|"gimp-context-get-opacity"
block|}
block|,
block|{
literal|"gimp-brushes-get-paint-mode"
block|,
literal|"gimp-context-get-paint-mode"
block|}
block|,
block|{
literal|"gimp-brushes-set-brush"
block|,
literal|"gimp-context-set-brush"
block|}
block|,
block|{
literal|"gimp-brushes-set-opacity"
block|,
literal|"gimp-context-set-opacity"
block|}
block|,
block|{
literal|"gimp-brushes-set-paint-mode"
block|,
literal|"gimp-context-set-paint-mode"
block|}
block|,
block|{
literal|"gimp-channel-ops-duplicate"
block|,
literal|"gimp-image-duplicate"
block|}
block|,
block|{
literal|"gimp-channel-ops-offset"
block|,
literal|"gimp-drawable-offset"
block|}
block|,
block|{
literal|"gimp-gradients-get-active"
block|,
literal|"gimp-context-get-gradient"
block|}
block|,
block|{
literal|"gimp-gradients-get-gradient"
block|,
literal|"gimp-context-get-gradient"
block|}
block|,
block|{
literal|"gimp-gradients-set-active"
block|,
literal|"gimp-context-set-gradient"
block|}
block|,
block|{
literal|"gimp-gradients-set-gradient"
block|,
literal|"gimp-context-set-gradient"
block|}
block|,
block|{
literal|"gimp-image-get-cmap"
block|,
literal|"gimp-image-get-colormap"
block|}
block|,
block|{
literal|"gimp-image-set-cmap"
block|,
literal|"gimp-image-set-colormap"
block|}
block|,
block|{
literal|"gimp-palette-get-background"
block|,
literal|"gimp-context-get-background"
block|}
block|,
block|{
literal|"gimp-palette-get-foreground"
block|,
literal|"gimp-context-get-foreground"
block|}
block|,
block|{
literal|"gimp-palette-set-background"
block|,
literal|"gimp-context-set-background"
block|}
block|,
block|{
literal|"gimp-palette-set-default-colors"
block|,
literal|"gimp-context-set-default-colors"
block|}
block|,
block|{
literal|"gimp-palette-set-foreground"
block|,
literal|"gimp-context-set-foreground"
block|}
block|,
block|{
literal|"gimp-palette-swap-colors"
block|,
literal|"gimp-context-swap-colors"
block|}
block|,
block|{
literal|"gimp-palettes-set-palette"
block|,
literal|"gimp-context-set-palette"
block|}
block|,
block|{
literal|"gimp-patterns-set-pattern"
block|,
literal|"gimp-context-set-pattern"
block|}
block|,
block|{
literal|"gimp-selection-clear"
block|,
literal|"gimp-selection-none"
block|}
block|,
comment|/*  deprecations since 2.2  */
block|{
literal|"gimp-layer-get-preserve-trans"
block|,
literal|"gimp-layer-get-lock-alpha"
block|}
block|,
block|{
literal|"gimp-layer-set-preserve-trans"
block|,
literal|"gimp-layer-set-lock-alpha"
block|}
block|,
comment|/*  deprecations since 2.6  */
block|{
literal|"gimp-drawable-is-valid"
block|,
literal|"gimp-item-is-valid"
block|}
block|,
block|{
literal|"gimp-drawable-is-layer"
block|,
literal|"gimp-item-is-layer"
block|}
block|,
block|{
literal|"gimp-drawable-is-text-layer"
block|,
literal|"gimp-item-is-text-layer"
block|}
block|,
block|{
literal|"gimp-drawable-is-layer-mask"
block|,
literal|"gimp-item-is-layer-mask"
block|}
block|,
block|{
literal|"gimp-drawable-is-channel"
block|,
literal|"gimp-item-is-channel"
block|}
block|,
block|{
literal|"gimp-drawable-delete"
block|,
literal|"gimp-item-delete"
block|}
block|,
block|{
literal|"gimp-drawable-get-image"
block|,
literal|"gimp-item-get-image"
block|}
block|,
block|{
literal|"gimp-drawable-get-name"
block|,
literal|"gimp-item-get-name"
block|}
block|,
block|{
literal|"gimp-drawable-set-name"
block|,
literal|"gimp-item-set-name"
block|}
block|,
block|{
literal|"gimp-drawable-get-visible"
block|,
literal|"gimp-item-get-visible"
block|}
block|,
block|{
literal|"gimp-drawable-set-visible"
block|,
literal|"gimp-item-set-visible"
block|}
block|,
block|{
literal|"gimp-drawable-get-linked"
block|,
literal|"gimp-item-get-linked"
block|}
block|,
block|{
literal|"gimp-drawable-set-linked"
block|,
literal|"gimp-item-set-linked"
block|}
block|,
block|{
literal|"gimp-drawable-get-tattoo"
block|,
literal|"gimp-item-get-tattoo"
block|}
block|,
block|{
literal|"gimp-drawable-set-tattoo"
block|,
literal|"gimp-item-set-tattoo"
block|}
block|,
block|{
literal|"gimp-drawable-parasite-find"
block|,
literal|"gimp-item-get-parasite"
block|}
block|,
block|{
literal|"gimp-drawable-parasite-attach"
block|,
literal|"gimp-item-attach-parasite"
block|}
block|,
block|{
literal|"gimp-drawable-parasite-detach"
block|,
literal|"gimp-item-detach-parasite"
block|}
block|,
block|{
literal|"gimp-drawable-parasite-list"
block|,
literal|"gimp-item-get-parasite-list"
block|}
block|,
block|{
literal|"gimp-image-get-layer-position"
block|,
literal|"gimp-image-get-item-position"
block|}
block|,
block|{
literal|"gimp-image-raise-layer"
block|,
literal|"gimp-image-raise-item"
block|}
block|,
block|{
literal|"gimp-image-lower-layer"
block|,
literal|"gimp-image-lower-item"
block|}
block|,
block|{
literal|"gimp-image-raise-layer-to-top"
block|,
literal|"gimp-image-raise-item-to-top"
block|}
block|,
block|{
literal|"gimp-image-lower-layer-to-bottom"
block|,
literal|"gimp-image-lower-item-to-bottom"
block|}
block|,
block|{
literal|"gimp-image-get-channel-position"
block|,
literal|"gimp-image-get-item-position"
block|}
block|,
block|{
literal|"gimp-image-raise-channel"
block|,
literal|"gimp-image-raise-item"
block|}
block|,
block|{
literal|"gimp-image-lower-channel"
block|,
literal|"gimp-image-lower-item"
block|}
block|,
block|{
literal|"gimp-image-get-vectors-position"
block|,
literal|"gimp-image-get-item-position"
block|}
block|,
block|{
literal|"gimp-image-raise-vectors"
block|,
literal|"gimp-image-raise-item"
block|}
block|,
block|{
literal|"gimp-image-lower-vectors"
block|,
literal|"gimp-image-lower-item"
block|}
block|,
block|{
literal|"gimp-image-raise-vectors-to-top"
block|,
literal|"gimp-image-raise-item-to-top"
block|}
block|,
block|{
literal|"gimp-image-lower-vectors-to-bottom"
block|,
literal|"gimp-image-lower-item-to-bottom"
block|}
block|,
block|{
literal|"gimp-vectors-is-valid"
block|,
literal|"gimp-item-is-valid"
block|}
block|,
block|{
literal|"gimp-vectors-get-image"
block|,
literal|"gimp-item-get-image"
block|}
block|,
block|{
literal|"gimp-vectors-get-name"
block|,
literal|"gimp-item-get-name"
block|}
block|,
block|{
literal|"gimp-vectors-set-name"
block|,
literal|"gimp-item-set-name"
block|}
block|,
block|{
literal|"gimp-vectors-get-visible"
block|,
literal|"gimp-item-get-visible"
block|}
block|,
block|{
literal|"gimp-vectors-set-visible"
block|,
literal|"gimp-item-set-visible"
block|}
block|,
block|{
literal|"gimp-vectors-get-linked"
block|,
literal|"gimp-item-get-linked"
block|}
block|,
block|{
literal|"gimp-vectors-set-linked"
block|,
literal|"gimp-item-set-linked"
block|}
block|,
block|{
literal|"gimp-vectors-get-tattoo"
block|,
literal|"gimp-item-get-tattoo"
block|}
block|,
block|{
literal|"gimp-vectors-set-tattoo"
block|,
literal|"gimp-item-set-tattoo"
block|}
block|,
block|{
literal|"gimp-vectors-parasite-find"
block|,
literal|"gimp-item-get-parasite"
block|}
block|,
block|{
literal|"gimp-vectors-parasite-attach"
block|,
literal|"gimp-item-attach-parasite"
block|}
block|,
block|{
literal|"gimp-vectors-parasite-detach"
block|,
literal|"gimp-item-detach-parasite"
block|}
block|,
block|{
literal|"gimp-vectors-parasite-list"
block|,
literal|"gimp-item-get-parasite-list"
block|}
block|}
struct|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PDB
argument_list|(
name|pdb
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|compat_mode
operator|!=
name|GIMP_PDB_COMPAT_OFF
condition|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|compat_procs
argument_list|)
condition|;
name|i
operator|++
control|)
name|gimp_pdb_register_compat_proc_name
argument_list|(
name|pdb
argument_list|,
name|compat_procs
index|[
name|i
index|]
operator|.
name|old_name
argument_list|,
name|compat_procs
index|[
name|i
index|]
operator|.
name|new_name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

