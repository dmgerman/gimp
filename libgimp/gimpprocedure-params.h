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

begin_comment
comment|/*  boolean  */
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
DECL|macro|GIMP_PROC_AUX_ARG_BOOLEAN (class,name,nick,blurb,default,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_BOOLEAN
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
define|default, flags) \   gimp_procedure_add_aux_argument (procedure,\                                    g_param_spec_boolean (name, nick, blurb,\                                    default,\                                    flags))
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
DECL|macro|GIMP_VALUES_GET_BOOLEAN (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_BOOLEAN
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_boolean (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_BOOLEAN (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_BOOLEAN
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_boolean (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  int  */
end_comment

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
DECL|macro|GIMP_PROC_AUX_ARG_INT (class,name,nick,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_INT
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
define|default, flags) \   gimp_procedure_add_aux_argument (procedure,\                                    g_param_spec_int (name, nick, blurb,\                                    min, max, default,\                                    flags))
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
DECL|macro|GIMP_VALUES_GET_INT (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_INT
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_int (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_INT (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_INT
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_int (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  uint  */
end_comment

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
DECL|macro|GIMP_PROC_AUX_ARG_UINT (class,name,nick,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_UINT
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
define|default, flags) \   gimp_procedure_add_aux_argument (procedure,\                                    g_param_spec_uint (name, nick, blurb,\                                    min, max, default,\                                    flags))
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
DECL|macro|GIMP_VALUES_GET_UINT (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_UINT
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_uint (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_UINT (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_UINT
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_uint (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/* uchar  */
end_comment

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
DECL|macro|GIMP_PROC_AUX_ARG_UCHAR (class,name,nick,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_UCHAR
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
define|default, flags) \   gimp_procedure_add_aux_argument (procedure,\                                    g_param_spec_uchar (name, nick, blurb,\                                    min, max, default,\                                    flags))
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
DECL|macro|GIMP_VALUES_GET_UCHAR (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_UCHAR
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_uchar (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_UCHAR (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_UCHAR
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_uchar (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  unit  */
end_comment

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
DECL|macro|GIMP_PROC_AUX_ARG_UNIT (class,name,nick,blurb,pixels,percent,default,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_UNIT
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
define|default, flags) \   gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_unit (name, nick, blurb,\                                    pixels, percent, default,\                                    flags))
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

begin_comment
comment|/*  double  */
end_comment

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
DECL|macro|GIMP_PROC_AUX_ARG_DOUBLE (class,name,nick,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_DOUBLE
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
define|default, flags) \   gimp_procedure_add_aux_argument (procedure,\                                    g_param_spec_double (name, nick, blurb,\                                    min, max, default,\                                    flags))
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
DECL|macro|GIMP_VALUES_GET_DOUBLE (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_DOUBLE
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_double (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_DOUBLE (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_DOUBLE
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_double (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  enum  */
end_comment

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
DECL|macro|GIMP_PROC_AUX_ARG_ENUM (class,name,nick,blurb,enum_type,default,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_ENUM
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
define|default, flags) \   gimp_procedure_add_aux_argument (procedure,\                                    g_param_spec_enum (name, nick, blurb,\                                    enum_type, default,\                                    flags))
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
DECL|macro|GIMP_VALUES_GET_ENUM (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_ENUM
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_enum (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_ENUM (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_ENUM
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_enum (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  string  */
end_comment

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
DECL|macro|GIMP_PROC_AUX_ARG_STRING (class,name,nick,blurb,default,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_STRING
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
define|default, flags) \   gimp_procedure_add_aux_argument (procedure,\                                    g_param_spec_string (name, nick, blurb,\                                    default,\                                    flags))
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
DECL|macro|GIMP_VALUES_GET_STRING (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_STRING
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_string (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_DUP_STRING (args,n)
define|#
directive|define
name|GIMP_VALUES_DUP_STRING
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_dup_string (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_STRING (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_STRING
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_string (gimp_value_array_index (args, n), value)
end_define

begin_define
DECL|macro|GIMP_VALUES_TAKE_STRING (args,n,value)
define|#
directive|define
name|GIMP_VALUES_TAKE_STRING
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_take_string (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  rgb  */
end_comment

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
DECL|macro|GIMP_PROC_AUX_ARG_RGB (class,name,nick,blurb,has_alpha,default,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_RGB
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
define|default, flags) \   gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_rgb (name, nick, blurb,\                                    has_alpha, default, \                                    flags))
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
DECL|macro|GIMP_VALUES_GET_RGB (args,n,value)
define|#
directive|define
name|GIMP_VALUES_GET_RGB
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|gimp_value_get_rgb (gimp_value_array_index (args, n), value)
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_RGB (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_RGB
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|gimp_value_set_rgb (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  parasite  */
end_comment

begin_define
DECL|macro|GIMP_PROC_ARG_PARASITE (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_ARG_PARASITE
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
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_parasite (name, nick, blurb,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_AUX_ARG_PARASITE (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_PARASITE
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_parasite (name, nick, blurb,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_PARASITE (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_VAL_PARASITE
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
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_parasite (name, nick, blurb,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_PARASITE (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_PARASITE
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_boxed (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_DUP_PARASITE (args,n)
define|#
directive|define
name|GIMP_VALUES_DUP_PARASITE
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_dup_boxed (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_PARASITE (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_PARASITE
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_boxed (gimp_value_array_index (args, n), value)
end_define

begin_define
DECL|macro|GIMP_VALUES_TAKE_PARASITE (args,n,value)
define|#
directive|define
name|GIMP_VALUES_TAKE_PARASITE
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_take_boxed (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  param  */
end_comment

begin_define
DECL|macro|GIMP_PROC_ARG_PARAM (class,name,nick,blurb,param_type,flags)
define|#
directive|define
name|GIMP_PROC_ARG_PARAM
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|param_type
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                g_param_spec_param (name, nick, blurb, param_type, \                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_AUX_ARG_PARAM (class,name,nick,blurb,param_type,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_PARAM
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|param_type
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_aux_argument (procedure,\                                    g_param_spec_param (name, nick, blurb, param_type, \                                    flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_PARAM (class,name,nick,blurb,param_type,flags)
define|#
directive|define
name|GIMP_PROC_VAL_PARAM
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|param_type
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    g_param_spec_param (name, nick, blurb, param_type, \                                    flags))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_PARAM (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_PARAM
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_param (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_DUP_PARAM (args,n)
define|#
directive|define
name|GIMP_VALUES_DUP_PARAM
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_dup_param (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_PARAM (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_PARAM
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_param (gimp_value_array_index (args, n), value)
end_define

begin_define
DECL|macro|GIMP_VALUES_TAKE_PARAM (args,n,value)
define|#
directive|define
name|GIMP_VALUES_TAKE_PARAM
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_take_param (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  uint8 array  */
end_comment

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
DECL|macro|GIMP_PROC_AUX_ARG_UINT8_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_UINT8_ARRAY
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_uint8_array (name, nick, blurb,\                                    flags))
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
DECL|macro|GIMP_VALUES_GET_UINT8_ARRAY (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_UINT8_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_value_get_uint8_array (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_DUP_UINT8_ARRAY (args,n)
define|#
directive|define
name|GIMP_VALUES_DUP_UINT8_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_value_dup_uint8_array (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_UINT8_ARRAY (args,n,value,length)
define|#
directive|define
name|GIMP_VALUES_SET_UINT8_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|,
name|length
parameter_list|)
define|\
value|gimp_value_set_uint8_array (gimp_value_array_index (args, n), value, length)
end_define

begin_define
DECL|macro|GIMP_VALUES_TAKE_UINT8_ARRAY (args,n,value,length)
define|#
directive|define
name|GIMP_VALUES_TAKE_UINT8_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|,
name|length
parameter_list|)
define|\
value|gimp_value_take_uint8_array (gimp_value_array_index (args, n), value, length)
end_define

begin_comment
comment|/*  int16 array  */
end_comment

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
DECL|macro|GIMP_PROC_AUX_ARG_INT16_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_INT16_ARRAY
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_int16_array (name, nick, blurb,\                                    flags))
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
DECL|macro|GIMP_VALUES_GET_INT16_ARRAY (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_INT16_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_value_get_int16_array (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_DUP_INT16_ARRAY (args,n)
define|#
directive|define
name|GIMP_VALUES_DUP_INT16_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_value_dup_int16_array (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_INT16_ARRAY (args,n,value,length)
define|#
directive|define
name|GIMP_VALUES_SET_INT16_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|,
name|length
parameter_list|)
define|\
value|gimp_value_set_int16_array (gimp_value_array_index (args, n), value, length)
end_define

begin_define
DECL|macro|GIMP_VALUES_TAKE_INT16_ARRAY (args,n,value,length)
define|#
directive|define
name|GIMP_VALUES_TAKE_INT16_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|,
name|length
parameter_list|)
define|\
value|gimp_value_take_int16_array (gimp_value_array_index (args, n), value, length)
end_define

begin_comment
comment|/*  int32 array  */
end_comment

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
DECL|macro|GIMP_PROC_AUX_ARG_INT32_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_INT32_ARRAY
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_int32_array (name, nick, blurb,\                                    flags))
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
DECL|macro|GIMP_VALUES_GET_INT32_ARRAY (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_INT32_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_value_get_int32_array (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_DUP_INT32_ARRAY (args,n)
define|#
directive|define
name|GIMP_VALUES_DUP_INT32_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_value_dup_int32_array (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_INT32_ARRAY (args,n,value,length)
define|#
directive|define
name|GIMP_VALUES_SET_INT32_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|,
name|length
parameter_list|)
define|\
value|gimp_value_set_int32_array (gimp_value_array_index (args, n), value, length)
end_define

begin_define
DECL|macro|GIMP_VALUES_TAKE_INT32_ARRAY (args,n,value,length)
define|#
directive|define
name|GIMP_VALUES_TAKE_INT32_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|,
name|length
parameter_list|)
define|\
value|gimp_value_take_int32_array (gimp_value_array_index (args, n), value, length)
end_define

begin_comment
comment|/*  float array  */
end_comment

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
DECL|macro|GIMP_PROC_AUX_ARG_FLOAT_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_FLOAT_ARRAY
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_float_array (name, nick, blurb,\                                    flags))
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
DECL|macro|GIMP_VALUES_GET_FLOAT_ARRAY (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_FLOAT_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_value_get_float_array (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_DUP_FLOAT_ARRAY (args,n)
define|#
directive|define
name|GIMP_VALUES_DUP_FLOAT_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_value_dup_float_array (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_FLOAT_ARRAY (args,n,value,length)
define|#
directive|define
name|GIMP_VALUES_SET_FLOAT_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|,
name|length
parameter_list|)
define|\
value|gimp_value_set_float_array (gimp_value_array_index (args, n), value, length)
end_define

begin_define
DECL|macro|GIMP_VALUES_TAKE_FLOAT_ARRAY (args,n,value,length)
define|#
directive|define
name|GIMP_VALUES_TAKE_FLOAT_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|,
name|length
parameter_list|)
define|\
value|gimp_value_take_float_array (gimp_value_array_index (args, n), value, length)
end_define

begin_comment
comment|/*  string array  */
end_comment

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
DECL|macro|GIMP_PROC_AUX_ARG_STRING_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_STRING_ARRAY
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_string_array (name, nick, blurb,\                                    flags))
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
DECL|macro|GIMP_VALUES_GET_STRING_ARRAY (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_STRING_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_value_get_string_array (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_DUP_STRING_ARRAY (args,n)
define|#
directive|define
name|GIMP_VALUES_DUP_STRING_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_value_dup_string_array (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_STRING_ARRAY (args,n,value,length)
define|#
directive|define
name|GIMP_VALUES_SET_STRING_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|,
name|length
parameter_list|)
define|\
value|gimp_value_set_string_array (gimp_value_array_index (args, n), value, length)
end_define

begin_define
DECL|macro|GIMP_VALUES_TAKE_STRING_ARRAY (args,n,value,length)
define|#
directive|define
name|GIMP_VALUES_TAKE_STRING_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|,
name|length
parameter_list|)
define|\
value|gimp_value_take_string_array (gimp_value_array_index (args, n), value, length)
end_define

begin_comment
comment|/*  rgb array  */
end_comment

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
DECL|macro|GIMP_PROC_AUX_ARG_RGB_ARRAY (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_RGB_ARRAY
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_rgb_array (name, nick, blurb,\                                    flags))
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
DECL|macro|GIMP_VALUES_GET_RGB_ARRAY (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_RGB_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_value_get_rgb_array (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_DUP_RGB_ARRAY (args,n)
define|#
directive|define
name|GIMP_VALUES_DUP_RGB_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_value_dup_rgb_array (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_RGB_ARRAY (args,n,value,length)
define|#
directive|define
name|GIMP_VALUES_SET_RGB_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|,
name|length
parameter_list|)
define|\
value|gimp_value_set_rgb_array (gimp_value_array_index (args, n), value, length)
end_define

begin_define
DECL|macro|GIMP_VALUES_TAKE_RGB_ARRAY (args,n,value,length)
define|#
directive|define
name|GIMP_VALUES_TAKE_RGB_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|,
name|length
parameter_list|)
define|\
value|gimp_value_take_rgb_array (gimp_value_array_index (args, n), value, length)
end_define

begin_comment
comment|/*  object array  */
end_comment

begin_define
DECL|macro|GIMP_PROC_ARG_OBJECT_ARRAY (class,name,nick,blurb,object_type,flags)
define|#
directive|define
name|GIMP_PROC_ARG_OBJECT_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|object_type
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_object_array (name, nick, blurb,\                                                              object_type, flags))
end_define

begin_define
DECL|macro|GIMP_PROC_AUX_ARG_OBJECT_ARRAY (class,name,nick,blurb,object_type,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_OBJECT_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|object_type
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_object_array (name, nick, blurb,\                                                                  object_type, flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_OBJECT_ARRAY (class,name,nick,blurb,object_type,flags)
define|#
directive|define
name|GIMP_PROC_VAL_OBJECT_ARRAY
parameter_list|(
name|class
parameter_list|,
name|name
parameter_list|,
name|nick
parameter_list|,
name|blurb
parameter_list|,
name|object_type
parameter_list|,
name|flags
parameter_list|)
define|\
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_object_array (name, nick, blurb,\                                                                  object_type, flags))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_OBJECT_ARRAY (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_OBJECT_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|(gpointer) gimp_value_get_object_array (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_DUP_OBJECT_ARRAY (args,n)
define|#
directive|define
name|GIMP_VALUES_DUP_OBJECT_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|(gpointer) gimp_value_dup_object_array (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_OBJECT_ARRAY (args,n,object_type,value,length)
define|#
directive|define
name|GIMP_VALUES_SET_OBJECT_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|object_type
parameter_list|,
name|value
parameter_list|,
name|length
parameter_list|)
define|\
value|gimp_value_set_object_array (gimp_value_array_index (args, n),\                                object_type, (gpointer) value, length)
end_define

begin_define
DECL|macro|GIMP_VALUES_TAKE_OBJECT_ARRAY (args,n,object_type,value,length)
define|#
directive|define
name|GIMP_VALUES_TAKE_OBJECT_ARRAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|object_type
parameter_list|,
name|value
parameter_list|,
name|length
parameter_list|)
define|\
value|gimp_value_take_object_array (gimp_value_array_index (args, n),\                                 object_type, (gpointer) value, length)
end_define

begin_comment
comment|/*  display  */
end_comment

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
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_display (name, nick, blurb,\                                none_ok,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_AUX_ARG_DISPLAY (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_DISPLAY
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_display (name, nick, blurb,\                                    none_ok,\                                    flags))
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
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_display (name, nick, blurb,\                                    none_ok,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_DISPLAY (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_DISPLAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_object (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_DISPLAY_ID (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_DISPLAY_ID
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_display_get_id (g_value_get_object (gimp_value_array_index (args, n)))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_DISPLAY (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_DISPLAY
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_object (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  image  */
end_comment

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
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_image (name, nick, blurb,\                                none_ok,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_AUX_ARG_IMAGE (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_IMAGE
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
value|gimp_procedure_add_aux_argument (procedure,\                                gimp_param_spec_image (name, nick, blurb,\                                none_ok,\                                flags))
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
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_image (name, nick, blurb,\                                    none_ok,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_IMAGE (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_IMAGE
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_object (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_IMAGE_ID (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_IMAGE_ID
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_image_get_id (g_value_get_object (gimp_value_array_index (args, n)))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_IMAGE (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_IMAGE
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_object (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  item  */
end_comment

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
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_item (name, nick, blurb,\                                none_ok,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_AUX_ARG_ITEM (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_ITEM
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_item (name, nick, blurb,\                                    none_ok,\                                    flags))
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
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_item (name, nick, blurb,\                                    none_ok,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_ITEM (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_ITEM
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_object (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_ITEM_ID (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_ITEM_ID
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_item_get_id (g_value_get_object (gimp_value_array_index (args, n)))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_ITEM (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_ITEM
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_object (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  drawable  */
end_comment

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
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_drawable (name, nick, blurb,\                                none_ok,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_AUX_ARG_DRAWABLE (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_DRAWABLE
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_drawable (name, nick, blurb,\                                    none_ok,\                                    flags))
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
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_drawable (name, nick, blurb,\                                    none_ok,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_DRAWABLE (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_DRAWABLE
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_object (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_DRAWABLE_ID (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_DRAWABLE_ID
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_item_get_id (g_value_get_object (gimp_value_array_index (args, n)))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_DRAWABLE (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_DRAWABLE
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_object (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  layer */
end_comment

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
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_layer (name, nick, blurb,\                                none_ok,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_AUX_ARG_LAYER (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_LAYER
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_layer (name, nick, blurb,\                                    none_ok,\                                    flags))
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
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_layer (name, nick, blurb,\                                    none_ok,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_LAYER (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_LAYER
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_object (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_LAYER_ID (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_LAYER_ID
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_item_get_id (g_value_get_object (gimp_value_array_index (args, n)))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_LAYER (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_LAYER
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_object (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  channel  */
end_comment

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
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_channel (name, nick, blurb,\                                none_ok,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_AUX_ARG_CHANNEL (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_CHANNEL
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_channel (name, nick, blurb,\                                    none_ok,\                                    flags))
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
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_channe (name, nick, blurb,\                                    none_ok,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_CHANNEL (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_CHANNEL
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_object (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_CHANNEL_ID (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_CHANNEL_ID
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_item_get_id (g_value_get_object (gimp_value_array_index (args, n)))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_CHANNEL (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_CHANNEL
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_object (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  layer mask  */
end_comment

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
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_layer_mask (name, nick, blurb,\                                none_ok,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_AUX_ARG_LAYER_MASK (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_LAYER_MASK
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_layer_mask (name, nick, blurb,\                                    none_ok,\                                    flags))
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
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_layer_mask (name, nick, blurb,\                                    none_ok,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_LAYER_MASK (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_LAYER_MASK
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_object (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_LAYER_MASK_ID (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_LAYER_MASK_ID
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_item_get_id (g_value_get_object (gimp_value_array_index (args, n)))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_LAYER_MASK (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_LAYER_MASK
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_object (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  selection  */
end_comment

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
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_selection (name, nick, blurb,\                                none_ok,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_AUX_ARG_SELECTION (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_SELECTION
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_selection (name, nick, blurb,\                                    none_ok,\                                    flags))
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
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_selection (name, nick, blurb,\                                    none_ok,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_SELECTION (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_SELECTION
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_object (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_SELECTION_ID (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_SELECTION_ID
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_item_get_id (g_value_get_object (gimp_value_array_index (args, n)))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_SELECTION (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_SELECTION
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_object (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  vectors  */
end_comment

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
value|gimp_procedure_add_argument (procedure,\                                gimp_param_spec_vectors (name, nick, blurb,\                                none_ok,\                                flags))
end_define

begin_define
DECL|macro|GIMP_PROC_AUX_ARG_VECTORS (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_VECTORS
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
value|gimp_procedure_add_aux_argument (procedure,\                                    gimp_param_spec_vectors (name, nick, blurb,\                                    none_ok,\                                    flags))
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
value|gimp_procedure_add_return_value (procedure,\                                    gimp_param_spec_vectors (name, nick, blurb,\                                    none_ok,\                                    flags))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_VECTORS (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_VECTORS
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_object (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_VECTORS_ID (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_VECTORS_ID
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|gimp_item_get_id (g_value_get_object (gimp_value_array_index (args, n)))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_VECTORS (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_VECTORS
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_object (gimp_value_array_index (args, n), value)
end_define

begin_comment
comment|/*  file  */
end_comment

begin_define
DECL|macro|GIMP_PROC_ARG_FILE (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_ARG_FILE
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
value|gimp_procedure_add_argument (procedure,\                                g_param_spec_object (name, nick, blurb,\                                                     G_TYPE_FILE,\                                                     flags))
end_define

begin_define
DECL|macro|GIMP_PROC_AUX_ARG_FILE (class,name,nick,blurb,flags)
define|#
directive|define
name|GIMP_PROC_AUX_ARG_FILE
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
value|gimp_procedure_add_aux_argument (procedure,\                                    g_param_spec_object (name, nick, blurb,\                                                         G_TYPE_FILE,\                                                         flags))
end_define

begin_define
DECL|macro|GIMP_PROC_VAL_FILE (class,name,nick,blurb,none_ok,flags)
define|#
directive|define
name|GIMP_PROC_VAL_FILE
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
value|gimp_procedure_add_return_value (procedure,\                                    g_param_spec_object (name, nick, blurb,\                                                         G_TYPE_FILE,\                                                         flags))
end_define

begin_define
DECL|macro|GIMP_VALUES_GET_FILE (args,n)
define|#
directive|define
name|GIMP_VALUES_GET_FILE
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_get_object (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_DUP_FILE (args,n)
define|#
directive|define
name|GIMP_VALUES_DUP_FILE
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|)
define|\
value|g_value_dup_object (gimp_value_array_index (args, n))
end_define

begin_define
DECL|macro|GIMP_VALUES_SET_FILE (args,n,value)
define|#
directive|define
name|GIMP_VALUES_SET_FILE
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_set_object (gimp_value_array_index (args, n), value)
end_define

begin_define
DECL|macro|GIMP_VALUES_TAKE_FILE (args,n,value)
define|#
directive|define
name|GIMP_VALUES_TAKE_FILE
parameter_list|(
name|args
parameter_list|,
name|n
parameter_list|,
name|value
parameter_list|)
define|\
value|g_value_take_object (gimp_value_array_index (args, n), value)
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

