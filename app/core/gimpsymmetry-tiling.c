begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsymmetry-tiling.c  * Copyright (C) 2015 Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpsymmetry-tiling.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* Using same epsilon as in GLIB. */
end_comment

begin_define
DECL|macro|G_DOUBLE_EPSILON
define|#
directive|define
name|G_DOUBLE_EPSILON
value|(1e-90)
end_define

begin_enum
enum|enum
DECL|enum|__anon299930340103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_X_INTERVAL
name|PROP_X_INTERVAL
block|,
DECL|enumerator|PROP_Y_INTERVAL
name|PROP_Y_INTERVAL
block|,
DECL|enumerator|PROP_SHIFT
name|PROP_SHIFT
block|,
DECL|enumerator|PROP_X_MAX
name|PROP_X_MAX
block|,
DECL|enumerator|PROP_Y_MAX
name|PROP_Y_MAX
block|}
enum|;
end_enum

begin_comment
comment|/* Local function prototypes */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_tiling_constructed
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
name|gimp_tiling_finalize
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
name|gimp_tiling_set_property
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
name|gimp_tiling_get_property
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
name|gimp_tiling_update_strokes
parameter_list|(
name|GimpSymmetry
modifier|*
name|tiling
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpCoords
modifier|*
name|origin
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GeglNode
modifier|*
name|gimp_tiling_get_operation
parameter_list|(
name|GimpSymmetry
modifier|*
name|tiling
parameter_list|,
name|gint
name|stroke
parameter_list|,
name|gint
name|paint_width
parameter_list|,
name|gint
name|paint_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tiling_image_size_changed_cb
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|previous_origin_x
parameter_list|,
name|gint
name|previous_origin_y
parameter_list|,
name|gint
name|previous_width
parameter_list|,
name|gint
name|previous_height
parameter_list|,
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpTiling,gimp_tiling,GIMP_TYPE_SYMMETRY)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTiling
argument_list|,
argument|gimp_tiling
argument_list|,
argument|GIMP_TYPE_SYMMETRY
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tiling_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tiling_class_init
parameter_list|(
name|GimpTilingClass
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
name|GimpSymmetryClass
modifier|*
name|symmetry_class
init|=
name|GIMP_SYMMETRY_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_tiling_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_tiling_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_tiling_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_tiling_get_property
expr_stmt|;
name|symmetry_class
operator|->
name|label
operator|=
name|_
argument_list|(
literal|"Tiling"
argument_list|)
expr_stmt|;
name|symmetry_class
operator|->
name|update_strokes
operator|=
name|gimp_tiling_update_strokes
expr_stmt|;
name|symmetry_class
operator|->
name|get_operation
operator|=
name|gimp_tiling_get_operation
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_X_INTERVAL
argument_list|,
literal|"x-interval"
argument_list|,
name|_
argument_list|(
literal|"Interval X"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Interval on the X axis (pixels)"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_SYMMETRY_PARAM_GUI
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_Y_INTERVAL
argument_list|,
literal|"y-interval"
argument_list|,
name|_
argument_list|(
literal|"Interval Y"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Interval on the Y axis (pixels)"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_SYMMETRY_PARAM_GUI
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_SHIFT
argument_list|,
literal|"shift"
argument_list|,
name|_
argument_list|(
literal|"Shift"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"X-shift between lines (pixels)"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_SYMMETRY_PARAM_GUI
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_X_MAX
argument_list|,
literal|"x-max"
argument_list|,
name|_
argument_list|(
literal|"Max strokes X"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Maximum number of strokes on the X axis"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|100
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_SYMMETRY_PARAM_GUI
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_Y_MAX
argument_list|,
literal|"y-max"
argument_list|,
name|_
argument_list|(
literal|"Max strokes Y"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Maximum number of strokes on the Y axis"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|100
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_SYMMETRY_PARAM_GUI
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tiling_init (GimpTiling * tiling)
name|gimp_tiling_init
parameter_list|(
name|GimpTiling
modifier|*
name|tiling
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tiling_constructed (GObject * object)
name|gimp_tiling_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSymmetry
modifier|*
name|sym
init|=
name|GIMP_SYMMETRY
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpTiling
modifier|*
name|tiling
init|=
name|GIMP_TILING
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gdouble
modifier|*
name|x_max
init|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|gdouble
modifier|*
name|y_max
init|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|gdouble
modifier|*
name|shift_max
init|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
literal|1
argument_list|)
decl_stmt|;
comment|/* Set property values to actual image size. */
operator|*
name|x_max
operator|=
name|gimp_image_get_width
argument_list|(
name|sym
operator|->
name|image
argument_list|)
expr_stmt|;
operator|*
name|y_max
operator|=
name|gimp_image_get_height
argument_list|(
name|sym
operator|->
name|image
argument_list|)
expr_stmt|;
operator|*
name|shift_max
operator|=
operator|*
name|x_max
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|object
argument_list|,
literal|"x-interval:max"
argument_list|,
name|x_max
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|object
argument_list|,
literal|"y-interval:max"
argument_list|,
name|y_max
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|object
argument_list|,
literal|"shift:max"
argument_list|,
name|shift_max
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|sym
operator|->
name|image
argument_list|,
literal|"size-changed-detailed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tiling_image_size_changed_cb
argument_list|)
argument_list|,
name|sym
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* Set reasonable defaults. */
name|tiling
operator|->
name|interval_x
operator|=
name|gimp_image_get_width
argument_list|(
name|sym
operator|->
name|image
argument_list|)
operator|/
literal|2
expr_stmt|;
name|tiling
operator|->
name|interval_y
operator|=
name|gimp_image_get_height
argument_list|(
name|sym
operator|->
name|image
argument_list|)
operator|/
literal|2
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tiling_finalize (GObject * object)
name|gimp_tiling_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
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
DECL|function|gimp_tiling_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_tiling_set_property
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
name|GimpTiling
modifier|*
name|tiling
init|=
name|GIMP_TILING
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpSymmetry
modifier|*
name|sym
init|=
name|GIMP_SYMMETRY
argument_list|(
name|tiling
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_X_INTERVAL
case|:
if|if
condition|(
name|sym
operator|->
name|image
condition|)
block|{
name|gdouble
name|new_x
init|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|new_x
operator|<
name|gimp_image_get_width
argument_list|(
name|sym
operator|->
name|image
argument_list|)
condition|)
block|{
name|tiling
operator|->
name|interval_x
operator|=
name|new_x
expr_stmt|;
if|if
condition|(
name|tiling
operator|->
name|interval_x
operator|<=
name|tiling
operator|->
name|shift
operator|+
name|G_DOUBLE_EPSILON
condition|)
block|{
name|GValue
name|val
init|=
name|G_VALUE_INIT
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|val
argument_list|,
name|G_TYPE_DOUBLE
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
operator|&
name|val
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|g_object_set_property
argument_list|(
name|G_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
literal|"shift"
argument_list|,
operator|&
name|val
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|sym
operator|->
name|drawable
condition|)
name|gimp_tiling_update_strokes
argument_list|(
name|sym
argument_list|,
name|sym
operator|->
name|drawable
argument_list|,
name|sym
operator|->
name|origin
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
case|case
name|PROP_Y_INTERVAL
case|:
block|{
name|gdouble
name|new_y
init|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|new_y
operator|<
name|gimp_image_get_height
argument_list|(
name|sym
operator|->
name|image
argument_list|)
condition|)
block|{
name|tiling
operator|->
name|interval_y
operator|=
name|new_y
expr_stmt|;
if|if
condition|(
name|tiling
operator|->
name|interval_y
operator|<=
name|G_DOUBLE_EPSILON
condition|)
block|{
name|GValue
name|val
init|=
name|G_VALUE_INIT
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|val
argument_list|,
name|G_TYPE_DOUBLE
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
operator|&
name|val
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|g_object_set_property
argument_list|(
name|G_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
literal|"shift"
argument_list|,
operator|&
name|val
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|sym
operator|->
name|drawable
condition|)
name|gimp_tiling_update_strokes
argument_list|(
name|sym
argument_list|,
name|sym
operator|->
name|drawable
argument_list|,
name|sym
operator|->
name|origin
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
case|case
name|PROP_SHIFT
case|:
block|{
name|gdouble
name|new_shift
init|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|new_shift
operator|==
literal|0.0
operator|||
operator|(
name|tiling
operator|->
name|interval_y
operator|!=
literal|0.0
operator|&&
name|new_shift
operator|<
name|tiling
operator|->
name|interval_x
operator|)
condition|)
block|{
name|tiling
operator|->
name|shift
operator|=
name|new_shift
expr_stmt|;
if|if
condition|(
name|sym
operator|->
name|drawable
condition|)
name|gimp_tiling_update_strokes
argument_list|(
name|sym
argument_list|,
name|sym
operator|->
name|drawable
argument_list|,
name|sym
operator|->
name|origin
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
case|case
name|PROP_X_MAX
case|:
name|tiling
operator|->
name|max_x
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|sym
operator|->
name|drawable
condition|)
name|gimp_tiling_update_strokes
argument_list|(
name|sym
argument_list|,
name|sym
operator|->
name|drawable
argument_list|,
name|sym
operator|->
name|origin
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_Y_MAX
case|:
name|tiling
operator|->
name|max_y
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|sym
operator|->
name|drawable
condition|)
name|gimp_tiling_update_strokes
argument_list|(
name|sym
argument_list|,
name|sym
operator|->
name|drawable
argument_list|,
name|sym
operator|->
name|origin
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
DECL|function|gimp_tiling_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_tiling_get_property
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
name|GimpTiling
modifier|*
name|tiling
init|=
name|GIMP_TILING
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
name|PROP_X_INTERVAL
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|tiling
operator|->
name|interval_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_Y_INTERVAL
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|tiling
operator|->
name|interval_y
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHIFT
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|tiling
operator|->
name|shift
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_X_MAX
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|tiling
operator|->
name|max_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_Y_MAX
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|tiling
operator|->
name|max_y
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
DECL|function|gimp_tiling_update_strokes (GimpSymmetry * sym,GimpDrawable * drawable,GimpCoords * origin)
name|gimp_tiling_update_strokes
parameter_list|(
name|GimpSymmetry
modifier|*
name|sym
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpCoords
modifier|*
name|origin
parameter_list|)
block|{
name|GimpTiling
modifier|*
name|tiling
init|=
name|GIMP_TILING
argument_list|(
name|sym
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|strokes
init|=
name|NULL
decl_stmt|;
name|GimpCoords
modifier|*
name|coords
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|startx
init|=
name|origin
operator|->
name|x
decl_stmt|;
name|gint
name|starty
init|=
name|origin
operator|->
name|y
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|gint
name|x_count
decl_stmt|;
name|gint
name|y_count
decl_stmt|;
name|g_list_free_full
argument_list|(
name|sym
operator|->
name|strokes
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|sym
operator|->
name|strokes
operator|=
name|NULL
expr_stmt|;
name|width
operator|=
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|origin
operator|->
name|x
operator|>
literal|0
operator|&&
name|tiling
operator|->
name|max_x
operator|==
literal|0
condition|)
name|startx
operator|=
name|origin
operator|->
name|x
operator|-
name|tiling
operator|->
name|interval_x
operator|*
call|(
name|gint
call|)
argument_list|(
name|origin
operator|->
name|x
operator|/
name|tiling
operator|->
name|interval_x
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|origin
operator|->
name|y
operator|>
literal|0
operator|&&
name|tiling
operator|->
name|max_y
operator|==
literal|0
condition|)
block|{
name|starty
operator|=
name|origin
operator|->
name|y
operator|-
name|tiling
operator|->
name|interval_y
operator|*
call|(
name|gint
call|)
argument_list|(
name|origin
operator|->
name|y
operator|/
name|tiling
operator|->
name|interval_y
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|tiling
operator|->
name|shift
operator|>
literal|0.0
condition|)
name|startx
operator|-=
name|tiling
operator|->
name|shift
operator|*
call|(
name|gint
call|)
argument_list|(
name|origin
operator|->
name|y
operator|/
name|tiling
operator|->
name|interval_y
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|y_count
operator|=
literal|0
operator|,
name|y
operator|=
name|starty
init|;
name|y
operator|<
name|height
operator|+
name|tiling
operator|->
name|interval_y
condition|;
name|y_count
operator|++
operator|,
name|y
operator|+=
name|tiling
operator|->
name|interval_y
control|)
block|{
if|if
condition|(
name|tiling
operator|->
name|max_y
operator|&&
name|y_count
operator|>=
operator|(
name|gint
operator|)
name|tiling
operator|->
name|max_y
condition|)
break|break;
for|for
control|(
name|x_count
operator|=
literal|0
operator|,
name|x
operator|=
name|startx
init|;
name|x
operator|<
name|width
operator|+
name|tiling
operator|->
name|interval_x
condition|;
name|x_count
operator|++
operator|,
name|x
operator|+=
name|tiling
operator|->
name|interval_x
control|)
block|{
if|if
condition|(
name|tiling
operator|->
name|max_x
operator|&&
name|x_count
operator|>=
operator|(
name|gint
operator|)
name|tiling
operator|->
name|max_x
condition|)
break|break;
name|coords
operator|=
name|g_memdup
argument_list|(
name|origin
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpCoords
argument_list|)
argument_list|)
expr_stmt|;
name|coords
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|coords
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|strokes
operator|=
name|g_list_prepend
argument_list|(
name|strokes
argument_list|,
name|coords
argument_list|)
expr_stmt|;
if|if
condition|(
name|tiling
operator|->
name|interval_x
operator|<
literal|1.0
condition|)
break|break;
block|}
if|if
condition|(
name|tiling
operator|->
name|max_x
operator|||
name|startx
operator|+
name|tiling
operator|->
name|shift
operator|<=
literal|0.0
condition|)
name|startx
operator|=
name|startx
operator|+
name|tiling
operator|->
name|shift
expr_stmt|;
else|else
name|startx
operator|=
name|startx
operator|-
name|tiling
operator|->
name|interval_x
operator|+
name|tiling
operator|->
name|shift
expr_stmt|;
if|if
condition|(
name|tiling
operator|->
name|interval_y
operator|<
literal|1.0
condition|)
break|break;
block|}
name|sym
operator|->
name|strokes
operator|=
name|strokes
expr_stmt|;
name|g_signal_emit_by_name
argument_list|(
name|sym
argument_list|,
literal|"strokes-updated"
argument_list|,
name|sym
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GeglNode
modifier|*
DECL|function|gimp_tiling_get_operation (GimpSymmetry * sym,gint stroke,gint paint_width,gint paint_height)
name|gimp_tiling_get_operation
parameter_list|(
name|GimpSymmetry
modifier|*
name|sym
parameter_list|,
name|gint
name|stroke
parameter_list|,
name|gint
name|paint_width
parameter_list|,
name|gint
name|paint_height
parameter_list|)
block|{
comment|/* No buffer transformation happens for tiling. */
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tiling_image_size_changed_cb (GimpImage * image,gint previous_origin_x,gint previous_origin_y,gint previous_width,gint previous_height,GimpSymmetry * sym)
name|gimp_tiling_image_size_changed_cb
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|previous_origin_x
parameter_list|,
name|gint
name|previous_origin_y
parameter_list|,
name|gint
name|previous_width
parameter_list|,
name|gint
name|previous_height
parameter_list|,
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
block|{
if|if
condition|(
name|previous_width
operator|!=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|gdouble
modifier|*
name|x_max
init|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|gdouble
modifier|*
name|shift_max
init|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
literal|1
argument_list|)
decl_stmt|;
operator|*
name|x_max
operator|=
name|gimp_image_get_width
argument_list|(
name|sym
operator|->
name|image
argument_list|)
expr_stmt|;
operator|*
name|shift_max
operator|=
operator|*
name|x_max
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|sym
argument_list|)
argument_list|,
literal|"x-interval:max"
argument_list|,
name|x_max
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|sym
argument_list|)
argument_list|,
literal|"shift:max"
argument_list|,
name|shift_max
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|previous_height
operator|!=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|gdouble
modifier|*
name|y_max
init|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
literal|1
argument_list|)
decl_stmt|;
operator|*
name|y_max
operator|=
name|gimp_image_get_height
argument_list|(
name|sym
operator|->
name|image
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|sym
argument_list|)
argument_list|,
literal|"y-interval:max"
argument_list|,
name|y_max
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|previous_width
operator|!=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|||
name|previous_height
operator|!=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
condition|)
name|g_signal_emit_by_name
argument_list|(
name|sym
argument_list|,
literal|"gui-param-changed"
argument_list|,
name|sym
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

