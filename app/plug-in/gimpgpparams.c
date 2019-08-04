begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpgpparams.c  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"libgimpbase/gimpprotocol.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
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
file|"gimpgpparams.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/*  include the implementations of  *  *  _gimp_param_spec_to_gp_param_def()  *  _gimp_gp_params_to_value_array()  *  _gimp_value_array_to_gp_params()  *  *  from libgimp, they are identical.  */
end_comment

begin_include
include|#
directive|include
file|"../../libgimp/gimpgpparams-body.c"
end_include

begin_function
name|GParamSpec
modifier|*
DECL|function|_gimp_gp_param_def_to_param_spec (Gimp * gimp,GPParamDef * param_def)
name|_gimp_gp_param_def_to_param_spec
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GPParamDef
modifier|*
name|param_def
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
name|param_def
operator|->
name|name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|nick
init|=
name|param_def
operator|->
name|nick
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|blurb
init|=
name|param_def
operator|->
name|blurb
decl_stmt|;
name|GParamFlags
name|flags
init|=
name|G_PARAM_READWRITE
decl_stmt|;
switch|switch
condition|(
name|param_def
operator|->
name|param_def_type
condition|)
block|{
case|case
name|GP_PARAM_DEF_TYPE_DEFAULT
case|:
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamInt32Array"
argument_list|)
condition|)
return|return
name|gimp_param_spec_int32_array
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamInt16Array"
argument_list|)
condition|)
return|return
name|gimp_param_spec_int16_array
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamInt8Array"
argument_list|)
condition|)
return|return
name|gimp_param_spec_int8_array
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamFloatArray"
argument_list|)
condition|)
return|return
name|gimp_param_spec_float_array
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamStringArray"
argument_list|)
condition|)
return|return
name|gimp_param_spec_string_array
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamRGBArray"
argument_list|)
condition|)
return|return
name|gimp_param_spec_rgb_array
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamParasite"
argument_list|)
condition|)
return|return
name|gimp_param_spec_parasite
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
return|;
break|break;
case|case
name|GP_PARAM_DEF_TYPE_INT
case|:
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GParamInt"
argument_list|)
condition|)
return|return
name|g_param_spec_int
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|min_val
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|max_val
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|default_val
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamInt32"
argument_list|)
condition|)
return|return
name|gimp_param_spec_int32
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|min_val
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|max_val
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|default_val
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamInt16"
argument_list|)
condition|)
return|return
name|gimp_param_spec_int16
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|min_val
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|max_val
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|default_val
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamInt8"
argument_list|)
condition|)
return|return
name|gimp_param_spec_int8
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|min_val
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|max_val
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_int
operator|.
name|default_val
argument_list|,
name|flags
argument_list|)
return|;
break|break;
case|case
name|GP_PARAM_DEF_TYPE_UNIT
case|:
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamUnit"
argument_list|)
condition|)
return|return
name|gimp_param_spec_unit
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_unit
operator|.
name|allow_pixels
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_unit
operator|.
name|allow_percent
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_unit
operator|.
name|default_val
argument_list|,
name|flags
argument_list|)
return|;
break|break;
case|case
name|GP_PARAM_DEF_TYPE_ENUM
case|:
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GParamEnum"
argument_list|)
condition|)
return|return
name|g_param_spec_enum
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|g_type_from_name
argument_list|(
name|param_def
operator|->
name|meta
operator|.
name|m_enum
operator|.
name|type_name
argument_list|)
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_enum
operator|.
name|default_val
argument_list|,
name|flags
argument_list|)
return|;
break|break;
case|case
name|GP_PARAM_DEF_TYPE_BOOLEAN
case|:
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GParamBoolean"
argument_list|)
condition|)
return|return
name|g_param_spec_boolean
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_boolean
operator|.
name|default_val
argument_list|,
name|flags
argument_list|)
return|;
break|break;
case|case
name|GP_PARAM_DEF_TYPE_FLOAT
case|:
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GParamDouble"
argument_list|)
condition|)
return|return
name|g_param_spec_double
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_float
operator|.
name|min_val
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_float
operator|.
name|max_val
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_float
operator|.
name|default_val
argument_list|,
name|flags
argument_list|)
return|;
break|break;
case|case
name|GP_PARAM_DEF_TYPE_STRING
case|:
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamString"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GParamString"
argument_list|)
condition|)
return|return
name|gimp_param_spec_string
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_string
operator|.
name|allow_non_utf8
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_string
operator|.
name|null_ok
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_string
operator|.
name|non_empty
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_string
operator|.
name|default_val
argument_list|,
name|flags
argument_list|)
return|;
break|break;
case|case
name|GP_PARAM_DEF_TYPE_COLOR
case|:
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamRGB"
argument_list|)
condition|)
return|return
name|gimp_param_spec_rgb
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_color
operator|.
name|has_alpha
argument_list|,
operator|&
name|param_def
operator|->
name|meta
operator|.
name|m_color
operator|.
name|default_val
argument_list|,
name|flags
argument_list|)
return|;
case|case
name|GP_PARAM_DEF_TYPE_ID
case|:
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamDisplayID"
argument_list|)
condition|)
return|return
name|gimp_param_spec_display_id
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|gimp
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_id
operator|.
name|none_ok
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamImageID"
argument_list|)
condition|)
return|return
name|gimp_param_spec_image_id
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|gimp
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_id
operator|.
name|none_ok
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamItemID"
argument_list|)
condition|)
return|return
name|gimp_param_spec_item_id
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|gimp
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_id
operator|.
name|none_ok
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamDrawableID"
argument_list|)
condition|)
return|return
name|gimp_param_spec_drawable_id
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|gimp
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_id
operator|.
name|none_ok
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamLayerID"
argument_list|)
condition|)
return|return
name|gimp_param_spec_layer_id
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|gimp
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_id
operator|.
name|none_ok
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamChannelID"
argument_list|)
condition|)
return|return
name|gimp_param_spec_channel_id
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|gimp
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_id
operator|.
name|none_ok
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamLayerMaskID"
argument_list|)
condition|)
return|return
name|gimp_param_spec_layer_mask_id
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|gimp
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_id
operator|.
name|none_ok
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamSelectionID"
argument_list|)
condition|)
return|return
name|gimp_param_spec_selection_id
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|gimp
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_id
operator|.
name|none_ok
argument_list|,
name|flags
argument_list|)
return|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|param_def
operator|->
name|type_name
argument_list|,
literal|"GimpParamVectorsID"
argument_list|)
condition|)
return|return
name|gimp_param_spec_vectors_id
argument_list|(
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|gimp
argument_list|,
name|param_def
operator|->
name|meta
operator|.
name|m_id
operator|.
name|none_ok
argument_list|,
name|flags
argument_list|)
return|;
break|break;
block|}
name|g_printerr
argument_list|(
literal|"%s: GParamSpec type '%s' is not handled\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|param_def
operator|->
name|type_name
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

end_unit
