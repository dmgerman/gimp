begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_LCMS_LCMS_H
end_ifdef

begin_include
include|#
directive|include
file|<lcms/lcms.h>
end_include

begin_else
else|#
directive|else
end_else

begin_include
include|#
directive|include
file|<lcms.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmodule/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_define
DECL|macro|CDISPLAY_TYPE_LCMS
define|#
directive|define
name|CDISPLAY_TYPE_LCMS
value|(cdisplay_lcms_type)
end_define

begin_define
DECL|macro|CDISPLAY_LCMS (obj)
define|#
directive|define
name|CDISPLAY_LCMS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), CDISPLAY_TYPE_LCMS, CdisplayLcms))
end_define

begin_define
DECL|macro|CDISPLAY_LCMS_CLASS (klass)
define|#
directive|define
name|CDISPLAY_LCMS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), CDISPLAY_TYPE_LCMS, CdisplayLcmsClass))
end_define

begin_define
DECL|macro|CDISPLAY_IS_LCMS (obj)
define|#
directive|define
name|CDISPLAY_IS_LCMS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CDISPLAY_TYPE_LCMS))
end_define

begin_define
DECL|macro|CDISPLAY_IS_LCMS_CLASS (klass)
define|#
directive|define
name|CDISPLAY_IS_LCMS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), CDISPLAY_TYPE_LCMS))
end_define

begin_typedef
DECL|typedef|CdisplayLcms
typedef|typedef
name|struct
name|_CdisplayLcms
name|CdisplayLcms
typedef|;
end_typedef

begin_typedef
DECL|typedef|CdisplayLcmsClass
typedef|typedef
name|struct
name|_CdisplayLcmsClass
name|CdisplayLcmsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_CdisplayLcms
struct|struct
name|_CdisplayLcms
block|{
DECL|member|parent_instance
name|GimpColorDisplay
name|parent_instance
decl_stmt|;
DECL|member|config
name|GimpColorConfig
modifier|*
name|config
decl_stmt|;
DECL|member|transform
name|cmsHTRANSFORM
name|transform
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_CdisplayLcmsClass
struct|struct
name|_CdisplayLcmsClass
block|{
DECL|member|parent_instance
name|GimpColorDisplayClass
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_enum
enum|enum
DECL|enum|__anon2a9575c40103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONFIG
name|PROP_CONFIG
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GType
name|cdisplay_lcms_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_lcms_class_init
parameter_list|(
name|CdisplayLcmsClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_lcms_init
parameter_list|(
name|CdisplayLcms
modifier|*
name|lcms
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_lcms_dispose
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
name|cdisplay_lcms_get_property
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

begin_function_decl
specifier|static
name|void
name|cdisplay_lcms_set_property
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
name|cdisplay_lcms_convert
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
name|bpl
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_lcms_changed
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_lcms_set_config
parameter_list|(
name|CdisplayLcms
modifier|*
name|lcms
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|cdisplay_lcms_info
specifier|static
specifier|const
name|GimpModuleInfo
name|cdisplay_lcms_info
init|=
block|{
name|GIMP_MODULE_ABI_VERSION
block|,
name|N_
argument_list|(
literal|"Color management display filter using ICC color profiles"
argument_list|)
block|,
literal|"Sven Neumann"
block|,
literal|"v0.1"
block|,
literal|"(c) 2005, released under the GPL"
block|,
literal|"2005"
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cdisplay_lcms_type
specifier|static
name|GType
name|cdisplay_lcms_type
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpColorDisplayClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|G_MODULE_EXPORT
specifier|const
name|GimpModuleInfo
modifier|*
DECL|function|gimp_module_query (GTypeModule * module)
name|gimp_module_query
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
return|return
operator|&
name|cdisplay_lcms_info
return|;
block|}
end_function

begin_function
name|G_MODULE_EXPORT
name|gboolean
DECL|function|gimp_module_register (GTypeModule * module)
name|gimp_module_register
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
name|cdisplay_lcms_get_type
argument_list|(
name|module
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|GType
DECL|function|cdisplay_lcms_get_type (GTypeModule * module)
name|cdisplay_lcms_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
if|if
condition|(
operator|!
name|cdisplay_lcms_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|display_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|CdisplayLcmsClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|cdisplay_lcms_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|CdisplayLcms
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|cdisplay_lcms_init
block|,       }
decl_stmt|;
name|cdisplay_lcms_type
operator|=
name|g_type_module_register_type
argument_list|(
name|module
argument_list|,
name|GIMP_TYPE_COLOR_DISPLAY
argument_list|,
literal|"CdisplayLcms"
argument_list|,
operator|&
name|display_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|cdisplay_lcms_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_class_init (CdisplayLcmsClass * klass)
name|cdisplay_lcms_class_init
parameter_list|(
name|CdisplayLcmsClass
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
name|GimpColorDisplayClass
modifier|*
name|display_class
init|=
name|GIMP_COLOR_DISPLAY_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|cdisplay_lcms_dispose
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|cdisplay_lcms_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|cdisplay_lcms_set_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_CONFIG
argument_list|,
literal|"config"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_COLOR_CONFIG
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|display_class
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Color Management"
argument_list|)
expr_stmt|;
name|display_class
operator|->
name|help_id
operator|=
literal|"gimp-colordisplay-lcms"
expr_stmt|;
name|display_class
operator|->
name|convert
operator|=
name|cdisplay_lcms_convert
expr_stmt|;
name|display_class
operator|->
name|changed
operator|=
name|cdisplay_lcms_changed
expr_stmt|;
name|cmsErrorAction
argument_list|(
name|LCMS_ERROR_IGNORE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_init (CdisplayLcms * lcms)
name|cdisplay_lcms_init
parameter_list|(
name|CdisplayLcms
modifier|*
name|lcms
parameter_list|)
block|{
name|lcms
operator|->
name|config
operator|=
name|NULL
expr_stmt|;
name|lcms
operator|->
name|transform
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_dispose (GObject * object)
name|cdisplay_lcms_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|CdisplayLcms
modifier|*
name|lcms
init|=
name|CDISPLAY_LCMS
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|cdisplay_lcms_set_config
argument_list|(
name|lcms
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|cdisplay_lcms_get_property
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
name|CdisplayLcms
modifier|*
name|lcms
init|=
name|CDISPLAY_LCMS
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
name|PROP_CONFIG
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|lcms
operator|->
name|config
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
DECL|function|cdisplay_lcms_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|cdisplay_lcms_set_property
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
name|CdisplayLcms
modifier|*
name|lcms
init|=
name|CDISPLAY_LCMS
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
name|PROP_CONFIG
case|:
name|cdisplay_lcms_set_config
argument_list|(
name|lcms
argument_list|,
name|g_value_get_object
argument_list|(
name|value
argument_list|)
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
DECL|function|cdisplay_lcms_convert (GimpColorDisplay * display,guchar * buf,gint width,gint height,gint bpp,gint bpl)
name|cdisplay_lcms_convert
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
name|bpl
parameter_list|)
block|{
name|CdisplayLcms
modifier|*
name|lcms
init|=
name|CDISPLAY_LCMS
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|gint
name|y
decl_stmt|;
if|if
condition|(
name|bpp
operator|!=
literal|3
condition|)
return|return;
if|if
condition|(
operator|!
name|lcms
operator|->
name|transform
condition|)
return|return;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
operator|,
name|buf
operator|+=
name|bpl
control|)
name|cmsDoTransform
argument_list|(
name|lcms
operator|->
name|transform
argument_list|,
name|buf
argument_list|,
name|buf
argument_list|,
name|width
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_changed (GimpColorDisplay * display)
name|cdisplay_lcms_changed
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|CdisplayLcms
modifier|*
name|lcms
init|=
name|CDISPLAY_LCMS
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GimpColorConfig
modifier|*
name|config
init|=
name|lcms
operator|->
name|config
decl_stmt|;
name|cmsHPROFILE
name|src_profile
init|=
name|NULL
decl_stmt|;
name|cmsHPROFILE
name|dest_profile
init|=
name|NULL
decl_stmt|;
name|cmsHPROFILE
name|proof_profile
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|lcms
operator|->
name|transform
condition|)
block|{
name|cmsDeleteTransform
argument_list|(
name|lcms
operator|->
name|transform
argument_list|)
expr_stmt|;
name|lcms
operator|->
name|transform
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|config
condition|)
return|return;
switch|switch
condition|(
name|config
operator|->
name|mode
condition|)
block|{
case|case
name|GIMP_COLOR_MANAGEMENT_OFF
case|:
return|return;
case|case
name|GIMP_COLOR_MANAGEMENT_SOFTPROOF
case|:
if|if
condition|(
name|config
operator|->
name|printer_profile
condition|)
name|proof_profile
operator|=
name|cmsOpenProfileFromFile
argument_list|(
name|config
operator|->
name|printer_profile
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
comment|/*  fallthru  */
case|case
name|GIMP_COLOR_MANAGEMENT_DISPLAY
case|:
comment|/*  this should be taken from the image  */
name|src_profile
operator|=
name|cmsCreate_sRGBProfile
argument_list|()
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|display_profile
condition|)
name|dest_profile
operator|=
name|cmsOpenProfileFromFile
argument_list|(
name|config
operator|->
name|display_profile
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|proof_profile
condition|)
block|{
name|lcms
operator|->
name|transform
operator|=
name|cmsCreateProofingTransform
argument_list|(
name|src_profile
argument_list|,
name|TYPE_RGB_8
argument_list|,
operator|(
name|dest_profile
condition|?
name|dest_profile
else|:
name|src_profile
operator|)
argument_list|,
name|TYPE_RGB_8
argument_list|,
name|proof_profile
argument_list|,
name|config
operator|->
name|display_intent
argument_list|,
name|config
operator|->
name|simulation_intent
argument_list|,
name|cmsFLAGS_SOFTPROOFING
argument_list|)
expr_stmt|;
name|cmsCloseProfile
argument_list|(
name|proof_profile
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|dest_profile
condition|)
block|{
name|lcms
operator|->
name|transform
operator|=
name|cmsCreateTransform
argument_list|(
name|src_profile
argument_list|,
name|TYPE_RGB_8
argument_list|,
name|dest_profile
argument_list|,
name|TYPE_RGB_8
argument_list|,
name|config
operator|->
name|display_intent
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|dest_profile
condition|)
name|cmsCloseProfile
argument_list|(
name|dest_profile
argument_list|)
expr_stmt|;
name|cmsCloseProfile
argument_list|(
name|src_profile
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_lcms_set_config (CdisplayLcms * lcms,GimpColorConfig * config)
name|cdisplay_lcms_set_config
parameter_list|(
name|CdisplayLcms
modifier|*
name|lcms
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
block|{
if|if
condition|(
name|config
operator|==
name|lcms
operator|->
name|config
condition|)
return|return;
if|if
condition|(
name|lcms
operator|->
name|config
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|lcms
operator|->
name|config
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_display_changed
argument_list|)
argument_list|,
name|lcms
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|lcms
operator|->
name|config
argument_list|)
expr_stmt|;
block|}
name|lcms
operator|->
name|config
operator|=
name|config
expr_stmt|;
if|if
condition|(
name|lcms
operator|->
name|config
condition|)
block|{
name|g_object_ref
argument_list|(
name|lcms
operator|->
name|config
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|lcms
operator|->
name|config
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_display_changed
argument_list|)
argument_list|,
name|lcms
argument_list|)
expr_stmt|;
block|}
name|gimp_color_display_changed
argument_list|(
name|GIMP_COLOR_DISPLAY
argument_list|(
name|lcms
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

