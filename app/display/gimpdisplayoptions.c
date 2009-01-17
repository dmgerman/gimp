begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpDisplayOptions  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpmath/gimpmath.h"
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
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"display-enums.h"
end_include

begin_include
include|#
directive|include
file|"config/gimprc-blurbs.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2afd3d160103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SHOW_MENUBAR
name|PROP_SHOW_MENUBAR
block|,
DECL|enumerator|PROP_SHOW_RULERS
name|PROP_SHOW_RULERS
block|,
DECL|enumerator|PROP_SHOW_SCROLLBARS
name|PROP_SHOW_SCROLLBARS
block|,
DECL|enumerator|PROP_SHOW_STATUSBAR
name|PROP_SHOW_STATUSBAR
block|,
DECL|enumerator|PROP_SHOW_SELECTION
name|PROP_SHOW_SELECTION
block|,
DECL|enumerator|PROP_SHOW_LAYER_BOUNDARY
name|PROP_SHOW_LAYER_BOUNDARY
block|,
DECL|enumerator|PROP_SHOW_GUIDES
name|PROP_SHOW_GUIDES
block|,
DECL|enumerator|PROP_SHOW_GRID
name|PROP_SHOW_GRID
block|,
DECL|enumerator|PROP_SHOW_SAMPLE_POINTS
name|PROP_SHOW_SAMPLE_POINTS
block|,
DECL|enumerator|PROP_PADDING_MODE
name|PROP_PADDING_MODE
block|,
DECL|enumerator|PROP_PADDING_COLOR
name|PROP_PADDING_COLOR
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_display_options_set_property
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
name|gimp_display_options_get_property
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
argument|GimpDisplayOptions
argument_list|,
argument|gimp_display_options
argument_list|,
argument|G_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG, NULL)
argument_list|)
end_macro

begin_typedef
DECL|typedef|GimpDisplayOptionsFullscreen
typedef|typedef
name|struct
name|_GimpDisplayOptions
name|GimpDisplayOptionsFullscreen
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDisplayOptionsFullscreenClass
typedef|typedef
name|struct
name|_GimpDisplayOptionsClass
name|GimpDisplayOptionsFullscreenClass
typedef|;
end_typedef

begin_define
DECL|macro|gimp_display_options_fullscreen_init
define|#
directive|define
name|gimp_display_options_fullscreen_init
value|gimp_display_options_init
end_define

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpDisplayOptionsFullscreen
argument_list|,
argument|gimp_display_options_fullscreen
argument_list|,
argument|GIMP_TYPE_DISPLAY_OPTIONS
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG, NULL)
argument_list|)
end_macro

begin_typedef
DECL|typedef|GimpDisplayOptionsNoImage
typedef|typedef
name|struct
name|_GimpDisplayOptions
name|GimpDisplayOptionsNoImage
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDisplayOptionsNoImageClass
typedef|typedef
name|struct
name|_GimpDisplayOptionsClass
name|GimpDisplayOptionsNoImageClass
typedef|;
end_typedef

begin_define
DECL|macro|gimp_display_options_no_image_init
define|#
directive|define
name|gimp_display_options_no_image_init
value|gimp_display_options_init
end_define

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpDisplayOptionsNoImage,gimp_display_options_no_image,GIMP_TYPE_DISPLAY_OPTIONS,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,NULL))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpDisplayOptionsNoImage
argument_list|,
argument|gimp_display_options_no_image
argument_list|,
argument|GIMP_TYPE_DISPLAY_OPTIONS
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG, NULL)
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_display_options_class_init
parameter_list|(
name|GimpDisplayOptionsClass
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
name|GimpRGB
name|white
decl_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|white
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_display_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_display_options_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_MENUBAR
argument_list|,
literal|"show-menubar"
argument_list|,
name|SHOW_MENUBAR_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_RULERS
argument_list|,
literal|"show-rulers"
argument_list|,
name|SHOW_RULERS_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_SCROLLBARS
argument_list|,
literal|"show-scrollbars"
argument_list|,
name|SHOW_SCROLLBARS_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_STATUSBAR
argument_list|,
literal|"show-statusbar"
argument_list|,
name|SHOW_STATUSBAR_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_SELECTION
argument_list|,
literal|"show-selection"
argument_list|,
name|SHOW_SELECTION_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_LAYER_BOUNDARY
argument_list|,
literal|"show-layer-boundary"
argument_list|,
name|SHOW_LAYER_BOUNDARY_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_GUIDES
argument_list|,
literal|"show-guides"
argument_list|,
name|SHOW_GUIDES_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_GRID
argument_list|,
literal|"show-grid"
argument_list|,
name|SHOW_GRID_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_SAMPLE_POINTS
argument_list|,
literal|"show-sample-points"
argument_list|,
name|SHOW_SAMPLE_POINTS_BLURB
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_PADDING_MODE
argument_list|,
literal|"padding-mode"
argument_list|,
name|CANVAS_PADDING_MODE_BLURB
argument_list|,
name|GIMP_TYPE_CANVAS_PADDING_MODE
argument_list|,
name|GIMP_CANVAS_PADDING_MODE_DEFAULT
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_RGB
argument_list|(
name|object_class
argument_list|,
name|PROP_PADDING_COLOR
argument_list|,
literal|"padding-color"
argument_list|,
name|CANVAS_PADDING_COLOR_BLURB
argument_list|,
name|FALSE
argument_list|,
operator|&
name|white
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_options_fullscreen_class_init (GimpDisplayOptionsFullscreenClass * klass)
name|gimp_display_options_fullscreen_class_init
parameter_list|(
name|GimpDisplayOptionsFullscreenClass
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
name|GimpRGB
name|black
decl_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|black
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_display_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_display_options_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_MENUBAR
argument_list|,
literal|"show-menubar"
argument_list|,
name|SHOW_MENUBAR_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_RULERS
argument_list|,
literal|"show-rulers"
argument_list|,
name|SHOW_RULERS_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_SCROLLBARS
argument_list|,
literal|"show-scrollbars"
argument_list|,
name|SHOW_SCROLLBARS_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_STATUSBAR
argument_list|,
literal|"show-statusbar"
argument_list|,
name|SHOW_STATUSBAR_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_SELECTION
argument_list|,
literal|"show-selection"
argument_list|,
name|SHOW_SELECTION_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_LAYER_BOUNDARY
argument_list|,
literal|"show-layer-boundary"
argument_list|,
name|SHOW_LAYER_BOUNDARY_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_GUIDES
argument_list|,
literal|"show-guides"
argument_list|,
name|SHOW_GUIDES_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_GRID
argument_list|,
literal|"show-grid"
argument_list|,
name|SHOW_GRID_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_SAMPLE_POINTS
argument_list|,
literal|"show-sample-points"
argument_list|,
name|SHOW_SAMPLE_POINTS_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_PADDING_MODE
argument_list|,
literal|"padding-mode"
argument_list|,
name|CANVAS_PADDING_MODE_BLURB
argument_list|,
name|GIMP_TYPE_CANVAS_PADDING_MODE
argument_list|,
name|GIMP_CANVAS_PADDING_MODE_CUSTOM
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_RGB
argument_list|(
name|object_class
argument_list|,
name|PROP_PADDING_COLOR
argument_list|,
literal|"padding-color"
argument_list|,
name|CANVAS_PADDING_COLOR_BLURB
argument_list|,
name|FALSE
argument_list|,
operator|&
name|black
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_options_no_image_class_init (GimpDisplayOptionsNoImageClass * klass)
name|gimp_display_options_no_image_class_init
parameter_list|(
name|GimpDisplayOptionsNoImageClass
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
name|object_class
operator|->
name|set_property
operator|=
name|gimp_display_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_display_options_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_RULERS
argument_list|,
literal|"show-rulers"
argument_list|,
name|SHOW_RULERS_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_SCROLLBARS
argument_list|,
literal|"show-scrollbars"
argument_list|,
name|SHOW_SCROLLBARS_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_SELECTION
argument_list|,
literal|"show-selection"
argument_list|,
name|SHOW_SELECTION_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_LAYER_BOUNDARY
argument_list|,
literal|"show-layer-boundary"
argument_list|,
name|SHOW_LAYER_BOUNDARY_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_GUIDES
argument_list|,
literal|"show-guides"
argument_list|,
name|SHOW_GUIDES_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_GRID
argument_list|,
literal|"show-grid"
argument_list|,
name|SHOW_GRID_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_SAMPLE_POINTS
argument_list|,
literal|"show-sample-points"
argument_list|,
name|SHOW_SAMPLE_POINTS_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_options_init (GimpDisplayOptions * options)
name|gimp_display_options_init
parameter_list|(
name|GimpDisplayOptions
modifier|*
name|options
parameter_list|)
block|{
name|options
operator|->
name|padding_mode_set
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_display_options_set_property
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
name|GimpDisplayOptions
modifier|*
name|options
init|=
name|GIMP_DISPLAY_OPTIONS
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
name|PROP_SHOW_MENUBAR
case|:
name|options
operator|->
name|show_menubar
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_RULERS
case|:
name|options
operator|->
name|show_rulers
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_SCROLLBARS
case|:
name|options
operator|->
name|show_scrollbars
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_STATUSBAR
case|:
name|options
operator|->
name|show_statusbar
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_SELECTION
case|:
name|options
operator|->
name|show_selection
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_LAYER_BOUNDARY
case|:
name|options
operator|->
name|show_layer_boundary
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_GUIDES
case|:
name|options
operator|->
name|show_guides
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_GRID
case|:
name|options
operator|->
name|show_grid
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_SAMPLE_POINTS
case|:
name|options
operator|->
name|show_sample_points
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PADDING_MODE
case|:
name|options
operator|->
name|padding_mode
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PADDING_COLOR
case|:
name|options
operator|->
name|padding_color
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
DECL|function|gimp_display_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_display_options_get_property
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
name|GimpDisplayOptions
modifier|*
name|options
init|=
name|GIMP_DISPLAY_OPTIONS
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
name|PROP_SHOW_MENUBAR
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|show_menubar
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_RULERS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|show_rulers
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_SCROLLBARS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|show_scrollbars
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_STATUSBAR
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|show_statusbar
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_SELECTION
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|show_selection
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_LAYER_BOUNDARY
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|show_layer_boundary
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_GUIDES
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|show_guides
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_GRID
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|show_grid
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_SAMPLE_POINTS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|show_sample_points
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PADDING_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|padding_mode
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PADDING_COLOR
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|options
operator|->
name|padding_color
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

