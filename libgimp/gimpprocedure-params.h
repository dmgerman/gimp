begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpprocedure-params.h  * Copyright (C) 2019  Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
name|__GIMP_PROCEDURE_PARAMS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROCEDURE_PARAMS_H__
define|#
directive|define
name|__GIMP_PROCEDURE_PARAMS_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_comment
comment|/**  * SECTION: gimpprocedure-params  * @title: GimpProcedure-params  * @short_description: Macros and defines to add procedure arguments  *                     and return values.  *  * Macros and defines to add procedure arguments and return values.  **/
end_comment

begin_define
DECL|macro|GIMP_PROC_ARG_BOOLEAN (class,name,nick,blurb,default,flags)
define|#
directive|define
name|GIMP_PROC_ARG_BOOLEAN
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
define|default, flags) \   gimp_procedure_add_argument (procedure,\                                g_param_spec_boolean (name, nick, blurb,\                                default,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_BOOLEAN (class,name,nick,blurb,default,flags)
define|#
directive|define
name|GIMP_PROC_VAL_BOOLEAN
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
define|default, flags) \   gimp_procedure_add_return_value (procedure,\                                    g_param_spec_boolean (name, nick, blurb,\                                    default,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_INT (class,name,nick,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_PROC_ARG_INT
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|min
parameter_list|,
name|max
parameter_list|,
define|default, flags) \   gimp_procedure_add_argument (procedure,\                                g_param_spec_int (name, nick, blurb,\                                min, max, default,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_INT (class,name,nick,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_PROC_VAL_INT
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|min
parameter_list|,
name|max
parameter_list|,
define|default, flags) \   gimp_procedure_add_return_value (procedure,\                                    g_param_spec_int (name, nick, blurb,\                                    min, max, default,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_UINT (class,name,nick,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_PROC_ARG_UINT
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|min
parameter_list|,
name|max
parameter_list|,
define|default, flags) \   gimp_procedure_add_argument (procedure,\                                g_param_spec_uint (name, nick, blurb,\                                min, max, default,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_UINT (class,name,nick,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_PROC_VAL_UINT
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|min
parameter_list|,
name|max
parameter_list|,
define|default, flags) \   gimp_procedure_add_return_value (procedure,\                                    g_param_spec_uint (name, nick, blurb,\                                    min, max, default,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_UCHAR (class,name,nick,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_PROC_ARG_UCHAR
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|min
parameter_list|,
name|max
parameter_list|,
define|default, flags) \   gimp_procedure_add_argument (procedure,\                                g_param_spec_uchar (name, nick, blurb,\                                min, max, default,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_UCHAR (class,name,nick,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_PROC_VAL_UCHAR
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|min
parameter_list|,
name|max
parameter_list|,
define|default, flags) \   gimp_procedure_add_return_value (procedure,\                                    g_param_spec_uchar (name, nick, blurb,\                                    min, max, default,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_UNIT (class,name,nick,blurb,pixels,percent,default,flags)
define|#
directive|define
name|GIMP_PROC_ARG_UNIT
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|pixels
parameter_list|,
name|percent
parameter_list|,
define|default, flags) \   gimp_procedure_add_argument (procedure,\                                gimp_param_spec_unit (name, nick, blurb,\                                pixels, percent, default,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_UNIT (class,name,nick,blurb,pixels,percent,default,flags)
define|#
directive|define
name|GIMP_PROC_VAL_UNIT
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|pixels
parameter_list|,
name|percent
parameter_list|,
define|default, flags) \   gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_unit (name, nick, blurb,\                                    pixels, percent, default,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_DOUBLE (class,name,nick,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_PROC_ARG_DOUBLE
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|min
parameter_list|,
name|max
parameter_list|,
define|default, flags) \   gimp_procedure_add_argument (procedure,\                                g_param_spec_double (name, nick, blurb,\                                min, max, default,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_DOUBLE (class,name,nick,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_PROC_VAL_DOUBLE
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|min
parameter_list|,
name|max
parameter_list|,
define|default, flags) \   gimp_procedure_add_return_value (procedure,\                                    g_param_spec_double (name, nick, blurb,\                                    min, max, default,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_ENUM (class,name,nick,blurb,enum_type,default,flags)
define|#
directive|define
name|GIMP_PROC_ARG_ENUM
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|enum_type
parameter_list|,
define|default, flags) \   gimp_procedure_add_argument (procedure,\                                g_param_spec_enum (name, nick, blurb,\                                enum_type, default,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_ENUM (class,name,nick,blurb,enum_type,default,flags)
define|#
directive|define
name|GIMP_PROC_VAL_ENUM
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|enum_type
parameter_list|,
define|default, flags) \   gimp_procedure_add_return_value (procedure,\                                    g_param_spec_enum (name, nick, blurb,\                                    enum_type, default,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_STRING (class,name,nick,blurb,default,flags)
define|#
directive|define
name|GIMP_PROC_ARG_STRING
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
define|default, flags) \   gimp_procedure_add_argument (procedure,\                                g_param_spec_string (name, nick, blurb,\                                default,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_STRING (class,name,nick,blurb,default,flags)
define|#
directive|define
name|GIMP_PROC_VAL_STRING
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
define|default, flags) \   gimp_procedure_add_return_value (procedure,\                                    g_param_spec_string (name, nick, blurb,\                                    default,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_RGB (class,name,nick,blurb,has_alpha,default,flags)
define|#
directive|define
name|GIMP_PROC_ARG_RGB
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|has_alpha
parameter_list|,
define|default, flags) \   gimp_procedure_add_argument (procedure,\                                gimp_param_spec_rgb (name, nick, blurb,\                                has_alpha, default, \                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_RGB (class,name,nick,blurb,has_alpha,default,flags)
define|#
directive|define
name|GIMP_PROC_VAL_RGB
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|has_alpha
parameter_list|,
define|default, flags) \   gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_rgb (name, nick, blurb,\                                    has_alpha, default, \                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_UINT8_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_ARG_UINT8_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_uint8_array (name, nick, blurb,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_UINT8_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_VAL_UINT8_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_uint8_array (name, nick, blurb,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_INT16_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_ARG_INT16_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_int16_array (name, nick, blurb,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_INT16_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_VAL_INT16_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_int16_array (name, nick, blurb,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_INT32_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_ARG_INT32_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_int32_array (name, nick, blurb,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_INT32_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_VAL_INT32_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_int32_array (name, nick, blurb,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_FLOAT_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_ARG_FLOAT_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_float_array (name, nick, blurb,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_FLOAT_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_VAL_FLOAT_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_float_array (name, nick, blurb,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_STRING_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_ARG_STRING_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_string_array (name, nick, blurb,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_STRING_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_VAL_STRING_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_string_array (name, nick, blurb,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_RGB_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_ARG_RGB_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_rgb_array (name, nick, blurb,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_RGB_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_VAL_RGB_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_rgb_array (name, nick, blurb,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_DISPLAY (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_ARG_DISPLAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_display_id (name, nick, blurb,\                                none_ok, \                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_DISPLAY (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_VAL_DISPLAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_display_id (name, nick, blurb,\                                    none_ok, \                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_IMAGE (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_ARG_IMAGE
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_image_id (name, nick, blurb,\                                none_ok, \                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_IMAGE (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_VAL_IMAGE
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_image_id (name, nick, blurb,\                                    none_ok, \                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_ITEM (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_ARG_ITEM
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_item_id (name, nick, blurb,\                                none_ok, \                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_ITEM (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_VAL_ITEM
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_item_id (name, nick, blurb,\                                    none_ok, \                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_DRAWABLE (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_ARG_DRAWABLE
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_drawable_id (name, nick, blurb,\                                none_ok, \                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_DRAWABLE (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_VAL_DRAWABLE
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_drawable_id (name, nick, blurb,\                                    none_ok, \                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_LAYER (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_ARG_LAYER
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_layer_id (name, nick, blurb,\                                none_ok, \                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_LAYER (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_VAL_LAYER
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_layer_id (name, nick, blurb,\                                    none_ok, \                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_CHANNEL (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_ARG_CHANNEL
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_channel_id (name, nick, blurb,\                                none_ok, \                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_CHANNEL (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_VAL_CHANNEL
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_channel_id (name, nick, blurb,\                                    none_ok, \                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_LAYER_MASK (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_ARG_LAYER_MASK
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_layer_mask_id (name, nick, blurb,\                                none_ok, \                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_LAYER_MASK (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_VAL_LAYER_MASK
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_layer_mask_id (name, nick, blurb,\                                    none_ok, \                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_SELECTION (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_ARG_SELECTION
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_selection_id (name, nick, blurb,\                                none_ok, \                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_SELECTION (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_VAL_SELECTION
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_selection_id (name, nick, blurb,\                                    none_ok, \                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_ARG_VECTORS (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_ARG_VECTORS
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_vectors_id (name, nick, blurb,\                                none_ok, \                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_VECTORS (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_VAL_VECTORS
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|none_ok
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_vectors_id (name, nick, blurb,\                                    none_ok, \                                    flags))
end_define

begin_endif
unit|G_END_DECLS
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PROCEDURE_PARAMS_H__ */
end_comment

end_unit

