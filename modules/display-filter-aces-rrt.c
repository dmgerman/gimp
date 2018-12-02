begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2018 Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
DECL|macro|DEFAULT_EXPOSURE
define|#
directive|define
name|DEFAULT_EXPOSURE
value|0.0
end_define

begin_define
DECL|macro|CDISPLAY_TYPE_ACES_RRT
define|#
directive|define
name|CDISPLAY_TYPE_ACES_RRT
value|(cdisplay_aces_rrt_get_type ())
end_define

begin_define
DECL|macro|CDISPLAY_ACES_RRT (obj)
define|#
directive|define
name|CDISPLAY_ACES_RRT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), CDISPLAY_TYPE_ACES_RRT, CdisplayAcesRRT))
end_define

begin_define
DECL|macro|CDISPLAY_ACES_RRT_CLASS (klass)
define|#
directive|define
name|CDISPLAY_ACES_RRT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), CDISPLAY_TYPE_ACES_RRT, CdisplayAcesRRTClass))
end_define

begin_define
DECL|macro|CDISPLAY_IS_ACES_RRT (obj)
define|#
directive|define
name|CDISPLAY_IS_ACES_RRT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CDISPLAY_TYPE_ACES_RRT))
end_define

begin_define
DECL|macro|CDISPLAY_IS_ACES_RRT_CLASS (klass)
define|#
directive|define
name|CDISPLAY_IS_ACES_RRT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), CDISPLAY_TYPE_ACES_RRT))
end_define

begin_typedef
DECL|typedef|CdisplayAcesRRT
typedef|typedef
name|struct
name|_CdisplayAcesRRT
name|CdisplayAcesRRT
typedef|;
end_typedef

begin_typedef
DECL|typedef|CdisplayAcesRRTClass
typedef|typedef
name|struct
name|_CdisplayAcesRRTClass
name|CdisplayAcesRRTClass
typedef|;
end_typedef

begin_struct
DECL|struct|_CdisplayAcesRRT
struct|struct
name|_CdisplayAcesRRT
block|{
DECL|member|parent_instance
name|GimpColorDisplay
name|parent_instance
decl_stmt|;
DECL|member|exposure
name|gdouble
name|exposure
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_CdisplayAcesRRTClass
struct|struct
name|_CdisplayAcesRRTClass
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
DECL|enum|__anon2b7c19f30103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_EXPOSURE
name|PROP_EXPOSURE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GType
name|cdisplay_aces_rrt_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_aces_rrt_set_property
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
name|cdisplay_aces_rrt_get_property
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
name|cdisplay_aces_rrt_convert_buffer
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
name|cdisplay_aces_rrt_set_exposure
parameter_list|(
name|CdisplayAcesRRT
modifier|*
name|aces_rrt
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|cdisplay_aces_rrt_info
specifier|static
specifier|const
name|GimpModuleInfo
name|cdisplay_aces_rrt_info
init|=
block|{
name|GIMP_MODULE_ABI_VERSION
block|,
name|N_
argument_list|(
literal|"ACES RRT (RRT = Reference Rendering Transform). An HDR to SDR proof color display filter, using a luminance-only approximation of the ACES RRT, a pre-defined filmic look to be used before ODT (display or output space ICC profile)"
argument_list|)
block|,
literal|"Ãyvind KolÃ¥s<pippin@gimp.org>"
block|,
literal|"v0.1"
block|,
literal|"(c) 2018, released under the LGPLv2+"
block|,
literal|"July 17, 2018"
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|G_DEFINE_DYNAMIC_TYPE (CdisplayAcesRRT,cdisplay_aces_rrt,GIMP_TYPE_COLOR_DISPLAY)
name|G_DEFINE_DYNAMIC_TYPE
argument_list|(
argument|CdisplayAcesRRT
argument_list|,
argument|cdisplay_aces_rrt
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
name|cdisplay_aces_rrt_info
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
name|cdisplay_aces_rrt_register_type
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
DECL|function|cdisplay_aces_rrt_class_init (CdisplayAcesRRTClass * klass)
name|cdisplay_aces_rrt_class_init
parameter_list|(
name|CdisplayAcesRRTClass
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
name|cdisplay_aces_rrt_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|cdisplay_aces_rrt_set_property
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_EXPOSURE
argument_list|,
literal|"exposure"
argument_list|,
name|_
argument_list|(
literal|"Pre-transform change in stops"
argument_list|)
argument_list|,
name|NULL
argument_list|,
operator|-
literal|10.0
argument_list|,
literal|10.0
argument_list|,
name|DEFAULT_EXPOSURE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|display_class
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Aces RRT"
argument_list|)
expr_stmt|;
name|display_class
operator|->
name|help_id
operator|=
literal|"gimp-colordisplay-aces-rrt"
expr_stmt|;
name|display_class
operator|->
name|icon_name
operator|=
name|GIMP_ICON_DISPLAY_FILTER_GAMMA
expr_stmt|;
name|display_class
operator|->
name|convert_buffer
operator|=
name|cdisplay_aces_rrt_convert_buffer
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_aces_rrt_class_finalize (CdisplayAcesRRTClass * klass)
name|cdisplay_aces_rrt_class_finalize
parameter_list|(
name|CdisplayAcesRRTClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_aces_rrt_init (CdisplayAcesRRT * aces_rrt)
name|cdisplay_aces_rrt_init
parameter_list|(
name|CdisplayAcesRRT
modifier|*
name|aces_rrt
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_aces_rrt_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|cdisplay_aces_rrt_get_property
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
name|CdisplayAcesRRT
modifier|*
name|aces_rrt
init|=
name|CDISPLAY_ACES_RRT
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
name|PROP_EXPOSURE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|aces_rrt
operator|->
name|exposure
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
DECL|function|cdisplay_aces_rrt_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|cdisplay_aces_rrt_set_property
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
name|CdisplayAcesRRT
modifier|*
name|aces_rrt
init|=
name|CDISPLAY_ACES_RRT
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
name|PROP_EXPOSURE
case|:
name|cdisplay_aces_rrt_set_exposure
argument_list|(
name|aces_rrt
argument_list|,
name|g_value_get_double
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
DECL|function|aces_aces_rrt (float x)
specifier|static
specifier|inline
name|float
name|aces_aces_rrt
parameter_list|(
name|float
name|x
parameter_list|)
block|{
comment|/*     Approximation of the ACES aces_rrt HDR to SDR mapping from:     https://github.com/TheRealMJP/BakingLab/blob/master/BakingLab/ACES.hlsl   */
name|float
name|a
init|=
name|x
operator|*
operator|(
name|x
operator|+
literal|0.0245786f
operator|)
operator|-
literal|0.000090537f
decl_stmt|;
name|float
name|b
init|=
name|x
operator|*
operator|(
literal|0.983729f
operator|*
name|x
operator|+
literal|0.4329510f
operator|)
operator|+
literal|0.238081f
decl_stmt|;
return|return
name|a
operator|/
name|b
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_aces_rrt_convert_buffer (GimpColorDisplay * display,GeglBuffer * buffer,GeglRectangle * area)
name|cdisplay_aces_rrt_convert_buffer
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
name|CdisplayAcesRRT
modifier|*
name|filter
init|=
name|CDISPLAY_ACES_RRT
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|float
name|gain
init|=
literal|1.0f
operator|/
name|exp2f
argument_list|(
operator|-
name|filter
operator|->
name|exposure
argument_list|)
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
literal|"RGBA float"
argument_list|)
argument_list|,
name|GEGL_ACCESS_READWRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
literal|1
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
name|items
index|[
literal|0
index|]
operator|.
name|data
decl_stmt|;
name|gint
name|count
init|=
name|iter
operator|->
name|length
decl_stmt|;
while|while
condition|(
name|count
operator|--
condition|)
block|{
operator|*
name|data
operator|=
name|aces_aces_rrt
argument_list|(
operator|*
name|data
operator|*
name|gain
argument_list|)
expr_stmt|;
name|data
operator|++
expr_stmt|;
operator|*
name|data
operator|=
name|aces_aces_rrt
argument_list|(
operator|*
name|data
operator|*
name|gain
argument_list|)
expr_stmt|;
name|data
operator|++
expr_stmt|;
operator|*
name|data
operator|=
name|aces_aces_rrt
argument_list|(
operator|*
name|data
operator|*
name|gain
argument_list|)
expr_stmt|;
name|data
operator|++
expr_stmt|;
name|data
operator|++
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_aces_rrt_set_exposure (CdisplayAcesRRT * aces_rrt,gdouble value)
name|cdisplay_aces_rrt_set_exposure
parameter_list|(
name|CdisplayAcesRRT
modifier|*
name|aces_rrt
parameter_list|,
name|gdouble
name|value
parameter_list|)
block|{
if|if
condition|(
name|value
operator|!=
name|aces_rrt
operator|->
name|exposure
condition|)
block|{
name|aces_rrt
operator|->
name|exposure
operator|=
name|value
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|aces_rrt
argument_list|)
argument_list|,
literal|"exposure"
argument_list|)
expr_stmt|;
name|gimp_color_display_changed
argument_list|(
name|GIMP_COLOR_DISPLAY
argument_list|(
name|aces_rrt
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

