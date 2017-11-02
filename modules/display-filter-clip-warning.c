begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * Copyright (C) 2017 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
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
DECL|macro|DEFAULT_SHADOWS_COLOR
define|#
directive|define
name|DEFAULT_SHADOWS_COLOR
value|(&(GimpRGB) {0.25, 0.25, 1.00, 1.00})
end_define

begin_define
DECL|macro|DEFAULT_HIGHLIGHTS_COLOR
define|#
directive|define
name|DEFAULT_HIGHLIGHTS_COLOR
value|(&(GimpRGB) {1.00, 0.25, 0.25, 1.00})
end_define

begin_define
DECL|macro|DEFAULT_NAN_COLOR
define|#
directive|define
name|DEFAULT_NAN_COLOR
value|(&(GimpRGB) {1.00, 1.00, 0.25, 1.00})
end_define

begin_define
DECL|macro|CDISPLAY_TYPE_CLIP_WARNING
define|#
directive|define
name|CDISPLAY_TYPE_CLIP_WARNING
value|(cdisplay_clip_warning_get_type ())
end_define

begin_define
DECL|macro|CDISPLAY_CLIP_WARNING (obj)
define|#
directive|define
name|CDISPLAY_CLIP_WARNING
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), CDISPLAY_TYPE_CLIP_WARNING, CdisplayClipWarning))
end_define

begin_define
DECL|macro|CDISPLAY_CLIP_WARNING_CLASS (klass)
define|#
directive|define
name|CDISPLAY_CLIP_WARNING_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), CDISPLAY_TYPE_CLIP_WARNING, CdisplayClipWarningClass))
end_define

begin_define
DECL|macro|CDISPLAY_IS_CLIP_WARNING (obj)
define|#
directive|define
name|CDISPLAY_IS_CLIP_WARNING
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CDISPLAY_TYPE_CLIP_WARNING))
end_define

begin_define
DECL|macro|CDISPLAY_IS_CLIP_WARNING_CLASS (klass)
define|#
directive|define
name|CDISPLAY_IS_CLIP_WARNING_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), CDISPLAY_TYPE_CLIP_WARNING))
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b0e24630103
block|{
DECL|enumerator|WARNING_SHADOW
name|WARNING_SHADOW
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|WARNING_HIGHLIGHT
name|WARNING_HIGHLIGHT
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|WARNING_NAN
name|WARNING_NAN
init|=
literal|1
operator|<<
literal|2
DECL|typedef|Warning
block|}
name|Warning
typedef|;
end_typedef

begin_typedef
DECL|typedef|CdisplayClipWarning
typedef|typedef
name|struct
name|_CdisplayClipWarning
name|CdisplayClipWarning
typedef|;
end_typedef

begin_typedef
DECL|typedef|CdisplayClipWarningClass
typedef|typedef
name|struct
name|_CdisplayClipWarningClass
name|CdisplayClipWarningClass
typedef|;
end_typedef

begin_struct
DECL|struct|_CdisplayClipWarning
struct|struct
name|_CdisplayClipWarning
block|{
DECL|member|parent_instance
name|GimpColorDisplay
name|parent_instance
decl_stmt|;
DECL|member|show_shadows
name|gboolean
name|show_shadows
decl_stmt|;
DECL|member|shadows_color
name|GimpRGB
name|shadows_color
decl_stmt|;
DECL|member|show_highlights
name|gboolean
name|show_highlights
decl_stmt|;
DECL|member|highlights_color
name|GimpRGB
name|highlights_color
decl_stmt|;
DECL|member|show_nan
name|gboolean
name|show_nan
decl_stmt|;
DECL|member|nan_color
name|GimpRGB
name|nan_color
decl_stmt|;
DECL|member|include_alpha
name|gboolean
name|include_alpha
decl_stmt|;
DECL|member|opaque
name|gboolean
name|opaque
decl_stmt|;
DECL|member|colors
name|gfloat
name|colors
index|[
literal|8
index|]
index|[
literal|2
index|]
index|[
literal|4
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_CdisplayClipWarningClass
struct|struct
name|_CdisplayClipWarningClass
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
DECL|enum|__anon2b0e24630203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SHOW_SHADOWS
name|PROP_SHOW_SHADOWS
block|,
DECL|enumerator|PROP_SHADOWS_COLOR
name|PROP_SHADOWS_COLOR
block|,
DECL|enumerator|PROP_SHOW_HIGHLIGHTS
name|PROP_SHOW_HIGHLIGHTS
block|,
DECL|enumerator|PROP_HIGHLIGHTS_COLOR
name|PROP_HIGHLIGHTS_COLOR
block|,
DECL|enumerator|PROP_SHOW_NAN
name|PROP_SHOW_NAN
block|,
DECL|enumerator|PROP_NAN_COLOR
name|PROP_NAN_COLOR
block|,
DECL|enumerator|PROP_INCLUDE_ALPHA
name|PROP_INCLUDE_ALPHA
block|,
DECL|enumerator|PROP_OPAQUE
name|PROP_OPAQUE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GType
name|cdisplay_clip_warning_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_clip_warning_set_property
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
name|cdisplay_clip_warning_get_property
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
name|cdisplay_clip_warning_convert_buffer
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GeglRectangle
modifier|*
name|area
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_clip_warning_set_member
parameter_list|(
name|CdisplayClipWarning
modifier|*
name|clip_warning
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|gpointer
name|member
parameter_list|,
name|gconstpointer
name|value
parameter_list|,
name|gsize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_clip_warning_update_colors
parameter_list|(
name|CdisplayClipWarning
modifier|*
name|clip_warning
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|cdisplay_clip_warning_info
specifier|static
specifier|const
name|GimpModuleInfo
name|cdisplay_clip_warning_info
init|=
block|{
name|GIMP_MODULE_ABI_VERSION
block|,
name|N_
argument_list|(
literal|"Clip warning color display filter"
argument_list|)
block|,
literal|"Ell"
block|,
literal|"v1.0"
block|,
literal|"(c) 2017, released under the GPL"
block|,
literal|"2017"
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|G_DEFINE_DYNAMIC_TYPE (CdisplayClipWarning,cdisplay_clip_warning,GIMP_TYPE_COLOR_DISPLAY)
name|G_DEFINE_DYNAMIC_TYPE
argument_list|(
argument|CdisplayClipWarning
argument_list|,
argument|cdisplay_clip_warning
argument_list|,
argument|GIMP_TYPE_COLOR_DISPLAY
argument_list|)
end_macro

begin_function
name|G_MODULE_EXPORT
specifier|const
name|GimpModuleInfo
modifier|*
name|gimp_module_query
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
return|return
operator|&
name|cdisplay_clip_warning_info
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
name|cdisplay_clip_warning_register_type
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
name|void
DECL|function|cdisplay_clip_warning_class_init (CdisplayClipWarningClass * klass)
name|cdisplay_clip_warning_class_init
parameter_list|(
name|CdisplayClipWarningClass
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
name|object_class
operator|->
name|get_property
operator|=
name|cdisplay_clip_warning_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|cdisplay_clip_warning_set_property
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_SHADOWS
argument_list|,
literal|"show-shadows"
argument_list|,
name|_
argument_list|(
literal|"Show shadows"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Show warning for pixels with a negative component"
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_RGB
argument_list|(
name|object_class
argument_list|,
name|PROP_SHADOWS_COLOR
argument_list|,
literal|"shadows-color"
argument_list|,
name|_
argument_list|(
literal|"Shadows color"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Shadows warning color"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|DEFAULT_SHADOWS_COLOR
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_DEFAULTS
argument_list|)
expr_stmt|;
name|gegl_param_spec_set_property_key
argument_list|(
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
literal|"shadows-color"
argument_list|)
argument_list|,
literal|"sensitive"
argument_list|,
literal|"show-shadows"
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_HIGHLIGHTS
argument_list|,
literal|"show-highlights"
argument_list|,
name|_
argument_list|(
literal|"Show highlights"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Show warning for pixels with a component greater than one"
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_RGB
argument_list|(
name|object_class
argument_list|,
name|PROP_HIGHLIGHTS_COLOR
argument_list|,
literal|"highlights-color"
argument_list|,
name|_
argument_list|(
literal|"Highlights color"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Highlights warning color"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|DEFAULT_HIGHLIGHTS_COLOR
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_DEFAULTS
argument_list|)
expr_stmt|;
name|gegl_param_spec_set_property_key
argument_list|(
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
literal|"highlights-color"
argument_list|)
argument_list|,
literal|"sensitive"
argument_list|,
literal|"show-highlights"
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_NAN
argument_list|,
literal|"show-nan"
argument_list|,
name|_
argument_list|(
literal|"Show NaN"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Show warning for pixels with a NaN component"
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_RGB
argument_list|(
name|object_class
argument_list|,
name|PROP_NAN_COLOR
argument_list|,
literal|"nan-color"
argument_list|,
name|_
argument_list|(
literal|"NaN color"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"NaN warning color"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|DEFAULT_NAN_COLOR
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_DEFAULTS
argument_list|)
expr_stmt|;
name|gegl_param_spec_set_property_key
argument_list|(
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
literal|"nan-color"
argument_list|)
argument_list|,
literal|"sensitive"
argument_list|,
literal|"show-nan"
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_INCLUDE_ALPHA
argument_list|,
literal|"include-alpha"
argument_list|,
name|_
argument_list|(
literal|"Include alpha"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Include alpha component in the warnings"
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_OPAQUE
argument_list|,
literal|"opaque"
argument_list|,
name|_
argument_list|(
literal|"Opaque"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Make warning pixels opaque"
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|display_class
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Clip Warning"
argument_list|)
expr_stmt|;
name|display_class
operator|->
name|help_id
operator|=
literal|"gimp-colordisplay-clip-warning"
expr_stmt|;
name|display_class
operator|->
name|icon_name
operator|=
literal|"gimp-warning"
expr_stmt|;
name|display_class
operator|->
name|convert_buffer
operator|=
name|cdisplay_clip_warning_convert_buffer
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_clip_warning_class_finalize (CdisplayClipWarningClass * klass)
name|cdisplay_clip_warning_class_finalize
parameter_list|(
name|CdisplayClipWarningClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_clip_warning_init (CdisplayClipWarning * clip_warning)
name|cdisplay_clip_warning_init
parameter_list|(
name|CdisplayClipWarning
modifier|*
name|clip_warning
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_clip_warning_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|cdisplay_clip_warning_get_property
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
name|CdisplayClipWarning
modifier|*
name|clip_warning
init|=
name|CDISPLAY_CLIP_WARNING
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
name|PROP_SHOW_SHADOWS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|clip_warning
operator|->
name|show_shadows
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHADOWS_COLOR
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|clip_warning
operator|->
name|shadows_color
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_HIGHLIGHTS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|clip_warning
operator|->
name|show_highlights
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HIGHLIGHTS_COLOR
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|clip_warning
operator|->
name|highlights_color
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_NAN
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|clip_warning
operator|->
name|show_nan
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_NAN_COLOR
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|clip_warning
operator|->
name|nan_color
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INCLUDE_ALPHA
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|clip_warning
operator|->
name|include_alpha
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OPAQUE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|clip_warning
operator|->
name|opaque
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
DECL|function|cdisplay_clip_warning_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|cdisplay_clip_warning_set_property
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
name|CdisplayClipWarning
modifier|*
name|clip_warning
init|=
name|CDISPLAY_CLIP_WARNING
argument_list|(
name|object
argument_list|)
decl_stmt|;
DECL|macro|SET_PTR_MEMBER (member,value)
define|#
directive|define
name|SET_PTR_MEMBER
parameter_list|(
name|member
parameter_list|,
name|value
parameter_list|)
define|\
value|cdisplay_clip_warning_set_member (clip_warning,                              \                                     pspec->name,                               \&clip_warning->member,                     \                                     (value),                                   \                                     sizeof (clip_warning->member))
DECL|macro|SET_VAL_MEMBER (member,type,value)
define|#
directive|define
name|SET_VAL_MEMBER
parameter_list|(
name|member
parameter_list|,
name|type
parameter_list|,
name|value
parameter_list|)
define|\
value|SET_PTR_MEMBER (member,&(type) {value})
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_SHOW_SHADOWS
case|:
name|SET_VAL_MEMBER
argument_list|(
name|show_shadows
argument_list|,
name|gboolean
argument_list|,
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHADOWS_COLOR
case|:
name|SET_PTR_MEMBER
argument_list|(
name|shadows_color
argument_list|,
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_HIGHLIGHTS
case|:
name|SET_VAL_MEMBER
argument_list|(
name|show_highlights
argument_list|,
name|gboolean
argument_list|,
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HIGHLIGHTS_COLOR
case|:
name|SET_PTR_MEMBER
argument_list|(
name|highlights_color
argument_list|,
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_NAN
case|:
name|SET_VAL_MEMBER
argument_list|(
name|show_nan
argument_list|,
name|gboolean
argument_list|,
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_NAN_COLOR
case|:
name|SET_PTR_MEMBER
argument_list|(
name|nan_color
argument_list|,
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INCLUDE_ALPHA
case|:
name|SET_VAL_MEMBER
argument_list|(
name|include_alpha
argument_list|,
name|gboolean
argument_list|,
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OPAQUE
case|:
name|SET_VAL_MEMBER
argument_list|(
name|opaque
argument_list|,
name|gboolean
argument_list|,
name|g_value_get_boolean
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
undef|#
directive|undef
name|SET_PTR_MEMBER
undef|#
directive|undef
name|SET_VAL_MEMBER
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_clip_warning_convert_buffer (GimpColorDisplay * display,GeglBuffer * buffer,GeglRectangle * area)
name|cdisplay_clip_warning_convert_buffer
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GeglRectangle
modifier|*
name|area
parameter_list|)
block|{
name|CdisplayClipWarning
modifier|*
name|clip_warning
init|=
name|CDISPLAY_CLIP_WARNING
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|buffer
argument_list|,
name|area
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
argument_list|,
name|GEGL_ACCESS_READWRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|gfloat
modifier|*
name|data
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|gint
name|count
init|=
name|iter
operator|->
name|length
decl_stmt|;
name|gint
name|x
init|=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|x
decl_stmt|;
name|gint
name|y
init|=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|y
decl_stmt|;
while|while
condition|(
name|count
operator|--
condition|)
block|{
name|gint
name|warning
init|=
literal|0
decl_stmt|;
name|gint
name|n_components
init|=
name|clip_warning
operator|->
name|opaque
condition|?
literal|4
else|:
literal|3
decl_stmt|;
if|if
condition|(
name|clip_warning
operator|->
name|show_shadows
condition|)
block|{
if|if
condition|(
name|clip_warning
operator|->
name|include_alpha
operator|&&
name|data
index|[
literal|3
index|]
operator|<
literal|0.0f
condition|)
block|{
name|warning
operator||=
name|WARNING_SHADOW
expr_stmt|;
name|n_components
operator|=
literal|4
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|data
index|[
literal|0
index|]
operator|<
literal|0.0f
operator|||
name|data
index|[
literal|1
index|]
operator|<
literal|0.0f
operator|||
name|data
index|[
literal|2
index|]
operator|<
literal|0.0f
condition|)
block|{
name|warning
operator||=
name|WARNING_SHADOW
expr_stmt|;
block|}
block|}
if|if
condition|(
name|clip_warning
operator|->
name|show_highlights
condition|)
block|{
if|if
condition|(
name|clip_warning
operator|->
name|include_alpha
operator|&&
name|data
index|[
literal|3
index|]
operator|>
literal|1.0f
condition|)
block|{
name|warning
operator||=
name|WARNING_HIGHLIGHT
expr_stmt|;
name|n_components
operator|=
literal|4
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|data
index|[
literal|0
index|]
operator|>
literal|1.0f
operator|||
name|data
index|[
literal|1
index|]
operator|>
literal|1.0f
operator|||
name|data
index|[
literal|2
index|]
operator|>
literal|1.0f
condition|)
block|{
name|warning
operator||=
name|WARNING_HIGHLIGHT
expr_stmt|;
block|}
block|}
if|if
condition|(
name|clip_warning
operator|->
name|show_nan
condition|)
block|{
if|if
condition|(
name|clip_warning
operator|->
name|include_alpha
operator|&&
name|isnan
argument_list|(
name|data
index|[
literal|3
index|]
argument_list|)
condition|)
block|{
name|warning
operator||=
name|WARNING_NAN
expr_stmt|;
name|n_components
operator|=
literal|4
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|isnan
argument_list|(
name|data
index|[
literal|0
index|]
argument_list|)
operator|||
name|isnan
argument_list|(
name|data
index|[
literal|1
index|]
argument_list|)
operator|||
name|isnan
argument_list|(
name|data
index|[
literal|2
index|]
argument_list|)
condition|)
block|{
name|warning
operator||=
name|WARNING_NAN
expr_stmt|;
block|}
block|}
if|if
condition|(
name|warning
condition|)
block|{
name|gboolean
name|alt
init|=
operator|(
operator|(
name|x
operator|+
name|y
operator|)
operator|>>
literal|3
operator|)
operator|&
literal|1
decl_stmt|;
name|memcpy
argument_list|(
name|data
argument_list|,
name|clip_warning
operator|->
name|colors
index|[
name|warning
index|]
index|[
name|alt
index|]
argument_list|,
name|n_components
operator|*
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|data
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
operator|++
name|x
operator|==
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|x
operator|+
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|width
condition|)
block|{
name|x
operator|=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|x
expr_stmt|;
name|y
operator|++
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_clip_warning_set_member (CdisplayClipWarning * clip_warning,const gchar * property_name,gpointer member,gconstpointer value,gsize size)
name|cdisplay_clip_warning_set_member
parameter_list|(
name|CdisplayClipWarning
modifier|*
name|clip_warning
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|gpointer
name|member
parameter_list|,
name|gconstpointer
name|value
parameter_list|,
name|gsize
name|size
parameter_list|)
block|{
if|if
condition|(
name|memcmp
argument_list|(
name|member
argument_list|,
name|value
argument_list|,
name|size
argument_list|)
condition|)
block|{
name|memcpy
argument_list|(
name|member
argument_list|,
name|value
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|cdisplay_clip_warning_update_colors
argument_list|(
name|clip_warning
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|clip_warning
argument_list|)
argument_list|,
name|property_name
argument_list|)
expr_stmt|;
name|gimp_color_display_changed
argument_list|(
name|GIMP_COLOR_DISPLAY
argument_list|(
name|clip_warning
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_clip_warning_update_colors (CdisplayClipWarning * clip_warning)
name|cdisplay_clip_warning_update_colors
parameter_list|(
name|CdisplayClipWarning
modifier|*
name|clip_warning
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gint
name|j
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|8
condition|;
name|i
operator|++
control|)
block|{
name|gfloat
modifier|*
name|color
init|=
name|clip_warning
operator|->
name|colors
index|[
name|i
index|]
index|[
literal|0
index|]
decl_stmt|;
name|gfloat
modifier|*
name|alt_color
init|=
name|clip_warning
operator|->
name|colors
index|[
name|i
index|]
index|[
literal|1
index|]
decl_stmt|;
name|gfloat
name|alt_value
decl_stmt|;
name|gint
name|n
init|=
literal|0
decl_stmt|;
name|memset
argument_list|(
name|color
argument_list|,
literal|0
argument_list|,
literal|3
operator|*
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|&
name|WARNING_SHADOW
condition|)
block|{
name|color
index|[
literal|0
index|]
operator|+=
name|clip_warning
operator|->
name|shadows_color
operator|.
name|r
expr_stmt|;
name|color
index|[
literal|1
index|]
operator|+=
name|clip_warning
operator|->
name|shadows_color
operator|.
name|g
expr_stmt|;
name|color
index|[
literal|2
index|]
operator|+=
name|clip_warning
operator|->
name|shadows_color
operator|.
name|b
expr_stmt|;
name|n
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|i
operator|&
name|WARNING_HIGHLIGHT
condition|)
block|{
name|color
index|[
literal|0
index|]
operator|+=
name|clip_warning
operator|->
name|highlights_color
operator|.
name|r
expr_stmt|;
name|color
index|[
literal|1
index|]
operator|+=
name|clip_warning
operator|->
name|highlights_color
operator|.
name|g
expr_stmt|;
name|color
index|[
literal|2
index|]
operator|+=
name|clip_warning
operator|->
name|highlights_color
operator|.
name|b
expr_stmt|;
name|n
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|i
operator|&
name|WARNING_NAN
condition|)
block|{
name|color
index|[
literal|0
index|]
operator|+=
name|clip_warning
operator|->
name|nan_color
operator|.
name|r
expr_stmt|;
name|color
index|[
literal|1
index|]
operator|+=
name|clip_warning
operator|->
name|nan_color
operator|.
name|g
expr_stmt|;
name|color
index|[
literal|2
index|]
operator|+=
name|clip_warning
operator|->
name|nan_color
operator|.
name|b
expr_stmt|;
name|n
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|n
condition|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|3
condition|;
name|j
operator|++
control|)
name|color
index|[
name|j
index|]
operator|/=
name|n
expr_stmt|;
block|}
name|color
index|[
literal|3
index|]
operator|=
literal|1.0
expr_stmt|;
if|if
condition|(
name|MAX
argument_list|(
name|color
index|[
literal|0
index|]
argument_list|,
name|MAX
argument_list|(
name|color
index|[
literal|1
index|]
argument_list|,
name|color
index|[
literal|2
index|]
argument_list|)
argument_list|)
operator|<=
literal|0.5
condition|)
name|alt_value
operator|=
literal|1.0
expr_stmt|;
else|else
name|alt_value
operator|=
literal|0.0
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|3
condition|;
name|j
operator|++
control|)
name|alt_color
index|[
name|j
index|]
operator|=
literal|0.75
operator|*
name|color
index|[
name|j
index|]
operator|+
literal|0.25
operator|*
name|alt_value
expr_stmt|;
name|alt_color
index|[
literal|3
index|]
operator|=
literal|1.0
expr_stmt|;
block|}
block|}
end_function

end_unit

