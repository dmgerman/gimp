begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpColorConfig class  * Copyright (C) 2004  Stefan DÃ¶hla<stefan@doehla.de>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfigtypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorconfig-enums.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-iface.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-path.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_define
DECL|macro|COLOR_MANAGEMENT_MODE_BLURB
define|#
directive|define
name|COLOR_MANAGEMENT_MODE_BLURB
define|\
value|N_("Mode of operation for color management.")
end_define

begin_define
DECL|macro|DISPLAY_PROFILE_BLURB
define|#
directive|define
name|DISPLAY_PROFILE_BLURB
define|\
value|N_("The color profile of your (primary) monitor.")
end_define

begin_define
DECL|macro|DISPLAY_PROFILE_FROM_GDK_BLURB
define|#
directive|define
name|DISPLAY_PROFILE_FROM_GDK_BLURB
define|\
value|N_("When enabled, GIMP will try to use the display color profile from " \      "the windowing system.  The configured monitor profile is then only " \      "used as a fallback.")
end_define

begin_define
DECL|macro|RGB_PROFILE_BLURB
define|#
directive|define
name|RGB_PROFILE_BLURB
define|\
value|N_("The default RGB working space color profile.")
end_define

begin_define
DECL|macro|CMYK_PROFILE_BLURB
define|#
directive|define
name|CMYK_PROFILE_BLURB
define|\
value|N_("The CMYK color profile used to convert between RGB and CMYK.")
end_define

begin_define
DECL|macro|PRINTER_PROFILE_BLURB
define|#
directive|define
name|PRINTER_PROFILE_BLURB
define|\
value|N_("The color profile used for simulating a printed version (softproof).")
end_define

begin_define
DECL|macro|DISPLAY_RENDERING_INTENT_BLURB
define|#
directive|define
name|DISPLAY_RENDERING_INTENT_BLURB
define|\
value|N_("Sets how colors are mapped for your display.")
end_define

begin_define
DECL|macro|SIMULATION_RENDERING_INTENT_BLURB
define|#
directive|define
name|SIMULATION_RENDERING_INTENT_BLURB
define|\
value|N_("Sets how colors are converted from RGB working space to the " \      "print simulation device.")
end_define

begin_define
DECL|macro|SIMULATION_GAMUT_CHECK_BLURB
define|#
directive|define
name|SIMULATION_GAMUT_CHECK_BLURB
define|\
value|N_("When enabled, the print simulation will mark colors which can not be " \      "represented in the target color space.")
end_define

begin_define
DECL|macro|OUT_OF_GAMUT_COLOR_BLURB
define|#
directive|define
name|OUT_OF_GAMUT_COLOR_BLURB
define|\
value|N_("The color to use for marking colors which are out of gamut.")
end_define

begin_enum
enum|enum
DECL|enum|__anon2bdf18370103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_MODE
name|PROP_MODE
block|,
DECL|enumerator|PROP_RGB_PROFILE
name|PROP_RGB_PROFILE
block|,
DECL|enumerator|PROP_CMYK_PROFILE
name|PROP_CMYK_PROFILE
block|,
DECL|enumerator|PROP_DISPLAY_PROFILE
name|PROP_DISPLAY_PROFILE
block|,
DECL|enumerator|PROP_DISPLAY_PROFILE_FROM_GDK
name|PROP_DISPLAY_PROFILE_FROM_GDK
block|,
DECL|enumerator|PROP_PRINTER_PROFILE
name|PROP_PRINTER_PROFILE
block|,
DECL|enumerator|PROP_DISPLAY_RENDERING_INTENT
name|PROP_DISPLAY_RENDERING_INTENT
block|,
DECL|enumerator|PROP_SIMULATION_RENDERING_INTENT
name|PROP_SIMULATION_RENDERING_INTENT
block|,
DECL|enumerator|PROP_SIMULATION_GAMUT_CHECK
name|PROP_SIMULATION_GAMUT_CHECK
block|,
DECL|enumerator|PROP_OUT_OF_GAMUT_COLOR
name|PROP_OUT_OF_GAMUT_COLOR
block|,
DECL|enumerator|PROP_DISPLAY_MODULE
name|PROP_DISPLAY_MODULE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_color_config_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_config_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_config_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpColorConfig
argument_list|,
argument|gimp_color_config
argument_list|,
argument|G_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG, NULL)                          gimp_type_set_translation_domain (g_define_type_id,                                                            GETTEXT_PACKAGE
literal|"-libgimp"
argument|)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_config_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_color_config_class_init
parameter_list|(
name|GimpColorConfigClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
DECL|variable|color
name|GimpRGB
name|color
decl_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
literal|0x80
argument_list|,
literal|0x80
argument_list|,
literal|0x80
argument_list|,
literal|0xff
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_color_config_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_color_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_color_config_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_MODE
argument_list|,
literal|"mode"
argument_list|,
name|COLOR_MANAGEMENT_MODE_BLURB
argument_list|,
name|GIMP_TYPE_COLOR_MANAGEMENT_MODE
argument_list|,
name|GIMP_COLOR_MANAGEMENT_DISPLAY
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_RGB_PROFILE
argument_list|,
literal|"rgb-profile"
argument_list|,
name|RGB_PROFILE_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_FILE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_CMYK_PROFILE
argument_list|,
literal|"cmyk-profile"
argument_list|,
name|CMYK_PROFILE_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_FILE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_DISPLAY_PROFILE
argument_list|,
literal|"display-profile"
argument_list|,
name|DISPLAY_PROFILE_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_FILE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_DISPLAY_PROFILE_FROM_GDK
argument_list|,
literal|"display-profile-from-gdk"
argument_list|,
name|DISPLAY_PROFILE_FROM_GDK_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_PRINTER_PROFILE
argument_list|,
literal|"printer-profile"
argument_list|,
name|PRINTER_PROFILE_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_FILE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_DISPLAY_RENDERING_INTENT
argument_list|,
literal|"display-rendering-intent"
argument_list|,
name|DISPLAY_RENDERING_INTENT_BLURB
argument_list|,
name|GIMP_TYPE_COLOR_RENDERING_INTENT
argument_list|,
name|GIMP_COLOR_RENDERING_INTENT_PERCEPTUAL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_SIMULATION_RENDERING_INTENT
argument_list|,
literal|"simulation-rendering-intent"
argument_list|,
name|SIMULATION_RENDERING_INTENT_BLURB
argument_list|,
name|GIMP_TYPE_COLOR_RENDERING_INTENT
argument_list|,
name|GIMP_COLOR_RENDERING_INTENT_PERCEPTUAL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SIMULATION_GAMUT_CHECK
argument_list|,
literal|"simulation-gamut-check"
argument_list|,
name|SIMULATION_GAMUT_CHECK_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_RGB
argument_list|(
name|object_class
argument_list|,
name|PROP_OUT_OF_GAMUT_COLOR
argument_list|,
literal|"out-of-gamut-color"
argument_list|,
name|OUT_OF_GAMUT_COLOR_BLURB
argument_list|,
name|FALSE
argument_list|,
operator|&
name|color
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_DISPLAY_MODULE
argument_list|,
literal|"display-module"
argument_list|,
name|NULL
argument_list|,
literal|"CdisplayLcms"
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_config_init (GimpColorConfig * config)
name|gimp_color_config_init
parameter_list|(
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_config_finalize (GObject * object)
name|gimp_color_config_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorConfig
modifier|*
name|color_config
init|=
name|GIMP_COLOR_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|color_config
operator|->
name|rgb_profile
condition|)
name|g_free
argument_list|(
name|color_config
operator|->
name|rgb_profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|color_config
operator|->
name|cmyk_profile
condition|)
name|g_free
argument_list|(
name|color_config
operator|->
name|cmyk_profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|color_config
operator|->
name|display_profile
condition|)
name|g_free
argument_list|(
name|color_config
operator|->
name|display_profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|color_config
operator|->
name|printer_profile
condition|)
name|g_free
argument_list|(
name|color_config
operator|->
name|printer_profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|color_config
operator|->
name|display_module
condition|)
name|g_free
argument_list|(
name|color_config
operator|->
name|display_module
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_color_config_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpColorConfig
modifier|*
name|color_config
init|=
name|GIMP_COLOR_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_MODE
case|:
name|color_config
operator|->
name|mode
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RGB_PROFILE
case|:
name|g_free
argument_list|(
name|color_config
operator|->
name|rgb_profile
argument_list|)
expr_stmt|;
name|color_config
operator|->
name|rgb_profile
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CMYK_PROFILE
case|:
name|g_free
argument_list|(
name|color_config
operator|->
name|cmyk_profile
argument_list|)
expr_stmt|;
name|color_config
operator|->
name|cmyk_profile
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DISPLAY_PROFILE
case|:
name|g_free
argument_list|(
name|color_config
operator|->
name|display_profile
argument_list|)
expr_stmt|;
name|color_config
operator|->
name|display_profile
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DISPLAY_PROFILE_FROM_GDK
case|:
name|color_config
operator|->
name|display_profile_from_gdk
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRINTER_PROFILE
case|:
name|g_free
argument_list|(
name|color_config
operator|->
name|printer_profile
argument_list|)
expr_stmt|;
name|color_config
operator|->
name|printer_profile
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DISPLAY_RENDERING_INTENT
case|:
name|color_config
operator|->
name|display_intent
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SIMULATION_RENDERING_INTENT
case|:
name|color_config
operator|->
name|simulation_intent
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SIMULATION_GAMUT_CHECK
case|:
name|color_config
operator|->
name|simulation_gamut_check
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OUT_OF_GAMUT_COLOR
case|:
name|color_config
operator|->
name|out_of_gamut_color
operator|=
operator|*
operator|(
name|GimpRGB
operator|*
operator|)
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DISPLAY_MODULE
case|:
name|g_free
argument_list|(
name|color_config
operator|->
name|display_module
argument_list|)
expr_stmt|;
name|color_config
operator|->
name|display_module
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_color_config_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpColorConfig
modifier|*
name|color_config
init|=
name|GIMP_COLOR_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|color_config
operator|->
name|mode
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RGB_PROFILE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|color_config
operator|->
name|rgb_profile
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CMYK_PROFILE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|color_config
operator|->
name|cmyk_profile
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DISPLAY_PROFILE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|color_config
operator|->
name|display_profile
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DISPLAY_PROFILE_FROM_GDK
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|color_config
operator|->
name|display_profile_from_gdk
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRINTER_PROFILE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|color_config
operator|->
name|printer_profile
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DISPLAY_RENDERING_INTENT
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|color_config
operator|->
name|display_intent
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SIMULATION_RENDERING_INTENT
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|color_config
operator|->
name|simulation_intent
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SIMULATION_GAMUT_CHECK
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|color_config
operator|->
name|simulation_gamut_check
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OUT_OF_GAMUT_COLOR
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|color_config
operator|->
name|out_of_gamut_color
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DISPLAY_MODULE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|color_config
operator|->
name|display_module
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

end_unit

