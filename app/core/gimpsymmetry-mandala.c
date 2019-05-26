begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsymmetry-mandala.c  * Copyright (C) 2015 Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<cairo.h>
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
file|"libgimpmath/gimpmath.h"
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
file|"gimp-cairo.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpguide.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-guides.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-symmetry.h"
end_include

begin_include
include|#
directive|include
file|"gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpsymmetry-mandala.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28aec9d70103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CENTER_X
name|PROP_CENTER_X
block|,
DECL|enumerator|PROP_CENTER_Y
name|PROP_CENTER_Y
block|,
DECL|enumerator|PROP_SIZE
name|PROP_SIZE
block|,
DECL|enumerator|PROP_DISABLE_TRANSFORMATION
name|PROP_DISABLE_TRANSFORMATION
block|, }
enum|;
end_enum

begin_comment
comment|/* Local function prototypes */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_mandala_constructed
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
name|gimp_mandala_finalize
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
name|gimp_mandala_set_property
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
name|gimp_mandala_get_property
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
name|gimp_mandala_active_changed
parameter_list|(
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_mandala_add_guide
parameter_list|(
name|GimpMandala
modifier|*
name|mandala
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_mandala_remove_guide
parameter_list|(
name|GimpMandala
modifier|*
name|mandala
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_mandala_guide_removed_cb
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GimpMandala
modifier|*
name|mandala
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_mandala_guide_position_cb
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpMandala
modifier|*
name|mandala
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_mandala_update_strokes
parameter_list|(
name|GimpSymmetry
modifier|*
name|mandala
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
name|gimp_mandala_get_operation
parameter_list|(
name|GimpSymmetry
modifier|*
name|mandala
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
name|gimp_mandala_get_transform
parameter_list|(
name|GimpSymmetry
modifier|*
name|mandala
parameter_list|,
name|gint
name|stroke
parameter_list|,
name|gdouble
modifier|*
name|angle
parameter_list|,
name|gboolean
modifier|*
name|reflect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_mandala_image_size_changed_cb
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
DECL|function|G_DEFINE_TYPE (GimpMandala,gimp_mandala,GIMP_TYPE_SYMMETRY)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpMandala
argument_list|,
argument|gimp_mandala
argument_list|,
argument|GIMP_TYPE_SYMMETRY
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_mandala_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_mandala_class_init
parameter_list|(
name|GimpMandalaClass
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
name|GParamSpec
modifier|*
name|pspec
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_mandala_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_mandala_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_mandala_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_mandala_get_property
expr_stmt|;
name|symmetry_class
operator|->
name|label
operator|=
name|_
argument_list|(
literal|"Mandala"
argument_list|)
expr_stmt|;
name|symmetry_class
operator|->
name|update_strokes
operator|=
name|gimp_mandala_update_strokes
expr_stmt|;
name|symmetry_class
operator|->
name|get_operation
operator|=
name|gimp_mandala_get_operation
expr_stmt|;
name|symmetry_class
operator|->
name|get_transform
operator|=
name|gimp_mandala_get_transform
expr_stmt|;
name|symmetry_class
operator|->
name|active_changed
operator|=
name|gimp_mandala_active_changed
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_CENTER_X
argument_list|,
literal|"center-x"
argument_list|,
name|_
argument_list|(
literal|"Center abscissa"
argument_list|)
argument_list|,
name|NULL
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
name|pspec
operator|=
name|g_object_class_find_property
argument_list|(
name|object_class
argument_list|,
literal|"center-x"
argument_list|)
expr_stmt|;
name|gegl_param_spec_set_property_key
argument_list|(
name|pspec
argument_list|,
literal|"unit"
argument_list|,
literal|"pixel-coordinate"
argument_list|)
expr_stmt|;
name|gegl_param_spec_set_property_key
argument_list|(
name|pspec
argument_list|,
literal|"axis"
argument_list|,
literal|"x"
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_CENTER_Y
argument_list|,
literal|"center-y"
argument_list|,
name|_
argument_list|(
literal|"Center ordinate"
argument_list|)
argument_list|,
name|NULL
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
name|pspec
operator|=
name|g_object_class_find_property
argument_list|(
name|object_class
argument_list|,
literal|"center-y"
argument_list|)
expr_stmt|;
name|gegl_param_spec_set_property_key
argument_list|(
name|pspec
argument_list|,
literal|"unit"
argument_list|,
literal|"pixel-coordinate"
argument_list|)
expr_stmt|;
name|gegl_param_spec_set_property_key
argument_list|(
name|pspec
argument_list|,
literal|"axis"
argument_list|,
literal|"y"
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_SIZE
argument_list|,
literal|"size"
argument_list|,
name|_
argument_list|(
literal|"Number of points"
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
literal|100
argument_list|,
literal|6.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_SYMMETRY_PARAM_GUI
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_DISABLE_TRANSFORMATION
argument_list|,
literal|"disable-transformation"
argument_list|,
name|_
argument_list|(
literal|"Disable brush transform"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Disable brush rotation"
argument_list|)
argument_list|,
name|FALSE
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
DECL|function|gimp_mandala_init (GimpMandala * mandala)
name|gimp_mandala_init
parameter_list|(
name|GimpMandala
modifier|*
name|mandala
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mandala_constructed (GObject * object)
name|gimp_mandala_constructed
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
name|gimp_mandala_image_size_changed_cb
argument_list|)
argument_list|,
name|sym
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mandala_finalize (GObject * object)
name|gimp_mandala_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpMandala
modifier|*
name|mandala
init|=
name|GIMP_MANDALA
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|mandala
operator|->
name|horizontal_guide
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|mandala
operator|->
name|vertical_guide
argument_list|)
expr_stmt|;
if|if
condition|(
name|mandala
operator|->
name|ops
condition|)
block|{
name|GList
modifier|*
name|iter
decl_stmt|;
for|for
control|(
name|iter
operator|=
name|mandala
operator|->
name|ops
init|;
name|iter
condition|;
name|iter
operator|=
name|g_list_next
argument_list|(
name|iter
argument_list|)
control|)
block|{
if|if
condition|(
name|iter
operator|->
name|data
condition|)
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|iter
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|mandala
operator|->
name|ops
argument_list|)
expr_stmt|;
name|mandala
operator|->
name|ops
operator|=
name|NULL
expr_stmt|;
block|}
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
DECL|function|gimp_mandala_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_mandala_set_property
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
name|GimpMandala
modifier|*
name|mandala
init|=
name|GIMP_MANDALA
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_SYMMETRY
argument_list|(
name|mandala
argument_list|)
operator|->
name|image
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CENTER_X
case|:
if|if
condition|(
name|g_value_get_double
argument_list|(
name|value
argument_list|)
operator|>
literal|0.0
operator|&&
name|g_value_get_double
argument_list|(
name|value
argument_list|)
operator|<
operator|(
name|gdouble
operator|)
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|mandala
operator|->
name|center_x
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|mandala
operator|->
name|vertical_guide
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|mandala
operator|->
name|vertical_guide
argument_list|,
name|gimp_mandala_guide_position_cb
argument_list|,
name|mandala
argument_list|)
expr_stmt|;
name|gimp_image_move_guide
argument_list|(
name|image
argument_list|,
name|mandala
operator|->
name|vertical_guide
argument_list|,
name|mandala
operator|->
name|center_x
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|mandala
operator|->
name|vertical_guide
argument_list|,
name|gimp_mandala_guide_position_cb
argument_list|,
name|mandala
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
case|case
name|PROP_CENTER_Y
case|:
if|if
condition|(
name|g_value_get_double
argument_list|(
name|value
argument_list|)
operator|>
literal|0.0
operator|&&
name|g_value_get_double
argument_list|(
name|value
argument_list|)
operator|<
operator|(
name|gdouble
operator|)
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|mandala
operator|->
name|center_y
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|mandala
operator|->
name|horizontal_guide
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|mandala
operator|->
name|horizontal_guide
argument_list|,
name|gimp_mandala_guide_position_cb
argument_list|,
name|mandala
argument_list|)
expr_stmt|;
name|gimp_image_move_guide
argument_list|(
name|image
argument_list|,
name|mandala
operator|->
name|horizontal_guide
argument_list|,
name|mandala
operator|->
name|center_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|mandala
operator|->
name|horizontal_guide
argument_list|,
name|gimp_mandala_guide_position_cb
argument_list|,
name|mandala
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
case|case
name|PROP_SIZE
case|:
name|mandala
operator|->
name|size
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DISABLE_TRANSFORMATION
case|:
name|mandala
operator|->
name|disable_transformation
operator|=
name|g_value_get_boolean
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
DECL|function|gimp_mandala_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_mandala_get_property
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
name|GimpMandala
modifier|*
name|mandala
init|=
name|GIMP_MANDALA
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
name|PROP_CENTER_X
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|mandala
operator|->
name|center_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CENTER_Y
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|mandala
operator|->
name|center_y
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SIZE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|mandala
operator|->
name|size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DISABLE_TRANSFORMATION
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|mandala
operator|->
name|disable_transformation
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
DECL|function|gimp_mandala_active_changed (GimpSymmetry * sym)
name|gimp_mandala_active_changed
parameter_list|(
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
block|{
name|GimpMandala
modifier|*
name|mandala
init|=
name|GIMP_MANDALA
argument_list|(
name|sym
argument_list|)
decl_stmt|;
if|if
condition|(
name|sym
operator|->
name|active
condition|)
block|{
if|if
condition|(
operator|!
name|mandala
operator|->
name|horizontal_guide
condition|)
name|gimp_mandala_add_guide
argument_list|(
name|mandala
argument_list|,
name|GIMP_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|mandala
operator|->
name|vertical_guide
condition|)
name|gimp_mandala_add_guide
argument_list|(
name|mandala
argument_list|,
name|GIMP_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|mandala
operator|->
name|horizontal_guide
condition|)
name|gimp_mandala_remove_guide
argument_list|(
name|mandala
argument_list|,
name|GIMP_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
if|if
condition|(
name|mandala
operator|->
name|vertical_guide
condition|)
name|gimp_mandala_remove_guide
argument_list|(
name|mandala
argument_list|,
name|GIMP_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mandala_add_guide (GimpMandala * mandala,GimpOrientationType orientation)
name|gimp_mandala_add_guide
parameter_list|(
name|GimpMandala
modifier|*
name|mandala
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|)
block|{
name|GimpSymmetry
modifier|*
name|sym
init|=
name|GIMP_SYMMETRY
argument_list|(
name|mandala
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpGuide
modifier|*
name|guide
decl_stmt|;
name|gint
name|position
decl_stmt|;
name|image
operator|=
name|sym
operator|->
name|image
expr_stmt|;
name|gimp
operator|=
name|image
operator|->
name|gimp
expr_stmt|;
name|guide
operator|=
name|gimp_guide_custom_new
argument_list|(
name|orientation
argument_list|,
name|gimp
operator|->
name|next_guide_ID
operator|++
argument_list|,
name|GIMP_GUIDE_STYLE_MANDALA
argument_list|)
expr_stmt|;
if|if
condition|(
name|orientation
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
block|{
name|mandala
operator|->
name|horizontal_guide
operator|=
name|guide
expr_stmt|;
comment|/* Mandala guide position at first activation is at canvas middle. */
if|if
condition|(
name|mandala
operator|->
name|center_y
operator|<
literal|1.0
condition|)
name|mandala
operator|->
name|center_y
operator|=
operator|(
name|gdouble
operator|)
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
operator|/
literal|2.0
expr_stmt|;
name|position
operator|=
operator|(
name|gint
operator|)
name|mandala
operator|->
name|center_y
expr_stmt|;
block|}
else|else
block|{
name|mandala
operator|->
name|vertical_guide
operator|=
name|guide
expr_stmt|;
comment|/* Mandala guide position at first activation is at canvas middle. */
if|if
condition|(
name|mandala
operator|->
name|center_x
operator|<
literal|1.0
condition|)
name|mandala
operator|->
name|center_x
operator|=
operator|(
name|gdouble
operator|)
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|/
literal|2.0
expr_stmt|;
name|position
operator|=
operator|(
name|gint
operator|)
name|mandala
operator|->
name|center_x
expr_stmt|;
block|}
name|g_signal_connect
argument_list|(
name|guide
argument_list|,
literal|"removed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_mandala_guide_removed_cb
argument_list|)
argument_list|,
name|mandala
argument_list|)
expr_stmt|;
name|gimp_image_add_guide
argument_list|(
name|image
argument_list|,
name|guide
argument_list|,
name|position
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|guide
argument_list|,
literal|"notify::position"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_mandala_guide_position_cb
argument_list|)
argument_list|,
name|mandala
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mandala_remove_guide (GimpMandala * mandala,GimpOrientationType orientation)
name|gimp_mandala_remove_guide
parameter_list|(
name|GimpMandala
modifier|*
name|mandala
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|)
block|{
name|GimpSymmetry
modifier|*
name|sym
init|=
name|GIMP_SYMMETRY
argument_list|(
name|mandala
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpGuide
modifier|*
name|guide
decl_stmt|;
name|image
operator|=
name|sym
operator|->
name|image
expr_stmt|;
name|guide
operator|=
operator|(
name|orientation
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
operator|)
condition|?
name|mandala
operator|->
name|horizontal_guide
else|:
name|mandala
operator|->
name|vertical_guide
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|guide
argument_list|,
name|gimp_mandala_guide_removed_cb
argument_list|,
name|mandala
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|guide
argument_list|,
name|gimp_mandala_guide_position_cb
argument_list|,
name|mandala
argument_list|)
expr_stmt|;
name|gimp_image_remove_guide
argument_list|(
name|image
argument_list|,
name|guide
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|guide
argument_list|)
expr_stmt|;
if|if
condition|(
name|orientation
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|mandala
operator|->
name|horizontal_guide
operator|=
name|NULL
expr_stmt|;
else|else
name|mandala
operator|->
name|vertical_guide
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mandala_guide_removed_cb (GObject * object,GimpMandala * mandala)
name|gimp_mandala_guide_removed_cb
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GimpMandala
modifier|*
name|mandala
parameter_list|)
block|{
name|GimpSymmetry
modifier|*
name|sym
init|=
name|GIMP_SYMMETRY
argument_list|(
name|mandala
argument_list|)
decl_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|object
argument_list|,
name|gimp_mandala_guide_removed_cb
argument_list|,
name|mandala
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|object
argument_list|,
name|gimp_mandala_guide_position_cb
argument_list|,
name|mandala
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_GUIDE
argument_list|(
name|object
argument_list|)
operator|==
name|mandala
operator|->
name|horizontal_guide
condition|)
block|{
name|g_object_unref
argument_list|(
name|mandala
operator|->
name|horizontal_guide
argument_list|)
expr_stmt|;
name|mandala
operator|->
name|horizontal_guide
operator|=
name|NULL
expr_stmt|;
name|mandala
operator|->
name|center_y
operator|=
literal|0.0
expr_stmt|;
name|gimp_mandala_remove_guide
argument_list|(
name|mandala
argument_list|,
name|GIMP_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_GUIDE
argument_list|(
name|object
argument_list|)
operator|==
name|mandala
operator|->
name|vertical_guide
condition|)
block|{
name|g_object_unref
argument_list|(
name|mandala
operator|->
name|vertical_guide
argument_list|)
expr_stmt|;
name|mandala
operator|->
name|vertical_guide
operator|=
name|NULL
expr_stmt|;
name|mandala
operator|->
name|center_x
operator|=
literal|0.0
expr_stmt|;
name|gimp_mandala_remove_guide
argument_list|(
name|mandala
argument_list|,
name|GIMP_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
block|}
name|gimp_image_symmetry_remove
argument_list|(
name|sym
operator|->
name|image
argument_list|,
name|sym
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mandala_guide_position_cb (GObject * object,GParamSpec * pspec,GimpMandala * mandala)
name|gimp_mandala_guide_position_cb
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpMandala
modifier|*
name|mandala
parameter_list|)
block|{
name|GimpGuide
modifier|*
name|guide
init|=
name|GIMP_GUIDE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|guide
operator|==
name|mandala
operator|->
name|horizontal_guide
condition|)
block|{
name|g_object_set
argument_list|(
name|G_OBJECT
argument_list|(
name|mandala
argument_list|)
argument_list|,
literal|"center-y"
argument_list|,
operator|(
name|gdouble
operator|)
name|gimp_guide_get_position
argument_list|(
name|guide
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|guide
operator|==
name|mandala
operator|->
name|vertical_guide
condition|)
block|{
name|g_object_set
argument_list|(
name|G_OBJECT
argument_list|(
name|mandala
argument_list|)
argument_list|,
literal|"center-x"
argument_list|,
operator|(
name|gdouble
operator|)
name|gimp_guide_get_position
argument_list|(
name|guide
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mandala_update_strokes (GimpSymmetry * sym,GimpDrawable * drawable,GimpCoords * origin)
name|gimp_mandala_update_strokes
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
name|GimpMandala
modifier|*
name|mandala
init|=
name|GIMP_MANDALA
argument_list|(
name|sym
argument_list|)
decl_stmt|;
name|GimpCoords
modifier|*
name|coords
decl_stmt|;
name|GimpMatrix3
name|matrix
decl_stmt|;
name|gint
name|i
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
name|coords
operator|=
name|g_memdup
argument_list|(
name|sym
operator|->
name|origin
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpCoords
argument_list|)
argument_list|)
expr_stmt|;
name|sym
operator|->
name|strokes
operator|=
name|g_list_prepend
argument_list|(
name|sym
operator|->
name|strokes
argument_list|,
name|coords
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|mandala
operator|->
name|size
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|new_x
decl_stmt|,
name|new_y
decl_stmt|;
name|coords
operator|=
name|g_memdup
argument_list|(
name|sym
operator|->
name|origin
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpCoords
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_matrix3_identity
argument_list|(
operator|&
name|matrix
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
operator|&
name|matrix
argument_list|,
operator|-
name|mandala
operator|->
name|center_x
argument_list|,
operator|-
name|mandala
operator|->
name|center_y
argument_list|)
expr_stmt|;
name|gimp_matrix3_rotate
argument_list|(
operator|&
name|matrix
argument_list|,
operator|-
name|i
operator|*
literal|2.0
operator|*
name|G_PI
operator|/
operator|(
name|gdouble
operator|)
name|mandala
operator|->
name|size
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
operator|&
name|matrix
argument_list|,
name|mandala
operator|->
name|center_x
argument_list|,
name|mandala
operator|->
name|center_y
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
operator|&
name|matrix
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|,
operator|&
name|new_x
argument_list|,
operator|&
name|new_y
argument_list|)
expr_stmt|;
name|coords
operator|->
name|x
operator|=
name|new_x
expr_stmt|;
name|coords
operator|->
name|y
operator|=
name|new_y
expr_stmt|;
name|sym
operator|->
name|strokes
operator|=
name|g_list_prepend
argument_list|(
name|sym
operator|->
name|strokes
argument_list|,
name|coords
argument_list|)
expr_stmt|;
block|}
name|sym
operator|->
name|strokes
operator|=
name|g_list_reverse
argument_list|(
name|sym
operator|->
name|strokes
argument_list|)
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
DECL|function|gimp_mandala_get_operation (GimpSymmetry * sym,gint stroke,gint paint_width,gint paint_height)
name|gimp_mandala_get_operation
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
name|GimpMandala
modifier|*
name|mandala
init|=
name|GIMP_MANDALA
argument_list|(
name|sym
argument_list|)
decl_stmt|;
name|GeglNode
modifier|*
name|op
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
operator|!
name|mandala
operator|->
name|disable_transformation
operator|&&
name|stroke
operator|!=
literal|0
operator|&&
name|paint_width
operator|!=
literal|0
operator|&&
name|paint_height
operator|!=
literal|0
condition|)
block|{
if|if
condition|(
name|mandala
operator|->
name|size
operator|!=
name|mandala
operator|->
name|cached_size
operator|||
name|mandala
operator|->
name|cached_paint_width
operator|!=
name|paint_width
operator|||
name|mandala
operator|->
name|cached_paint_height
operator|!=
name|paint_height
condition|)
block|{
name|GList
modifier|*
name|iter
decl_stmt|;
if|if
condition|(
name|mandala
operator|->
name|ops
condition|)
block|{
for|for
control|(
name|iter
operator|=
name|mandala
operator|->
name|ops
init|;
name|iter
condition|;
name|iter
operator|=
name|g_list_next
argument_list|(
name|iter
argument_list|)
control|)
block|{
if|if
condition|(
name|iter
operator|->
name|data
condition|)
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|iter
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|mandala
operator|->
name|ops
argument_list|)
expr_stmt|;
name|mandala
operator|->
name|ops
operator|=
name|NULL
expr_stmt|;
block|}
name|mandala
operator|->
name|ops
operator|=
name|g_list_prepend
argument_list|(
name|mandala
operator|->
name|ops
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|mandala
operator|->
name|size
condition|;
name|i
operator|++
control|)
block|{
name|op
operator|=
name|gegl_node_new_child
argument_list|(
name|NULL
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:rotate"
argument_list|,
literal|"origin-x"
argument_list|,
operator|(
name|gdouble
operator|)
name|paint_width
operator|/
literal|2.0
argument_list|,
literal|"origin-y"
argument_list|,
operator|(
name|gdouble
operator|)
name|paint_height
operator|/
literal|2.0
argument_list|,
literal|"degrees"
argument_list|,
name|i
operator|*
literal|360.0
operator|/
operator|(
name|gdouble
operator|)
name|mandala
operator|->
name|size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|mandala
operator|->
name|ops
operator|=
name|g_list_prepend
argument_list|(
name|mandala
operator|->
name|ops
argument_list|,
name|op
argument_list|)
expr_stmt|;
block|}
name|mandala
operator|->
name|ops
operator|=
name|g_list_reverse
argument_list|(
name|mandala
operator|->
name|ops
argument_list|)
expr_stmt|;
name|mandala
operator|->
name|cached_size
operator|=
name|mandala
operator|->
name|size
expr_stmt|;
name|mandala
operator|->
name|cached_paint_width
operator|=
name|paint_width
expr_stmt|;
name|mandala
operator|->
name|cached_paint_height
operator|=
name|paint_height
expr_stmt|;
block|}
name|op
operator|=
name|g_list_nth_data
argument_list|(
name|mandala
operator|->
name|ops
argument_list|,
name|stroke
argument_list|)
expr_stmt|;
block|}
return|return
name|op
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mandala_get_transform (GimpSymmetry * sym,gint stroke,gdouble * angle,gboolean * reflect)
name|gimp_mandala_get_transform
parameter_list|(
name|GimpSymmetry
modifier|*
name|sym
parameter_list|,
name|gint
name|stroke
parameter_list|,
name|gdouble
modifier|*
name|angle
parameter_list|,
name|gboolean
modifier|*
name|reflect
parameter_list|)
block|{
name|GimpMandala
modifier|*
name|mandala
init|=
name|GIMP_MANDALA
argument_list|(
name|sym
argument_list|)
decl_stmt|;
if|if
condition|(
name|mandala
operator|->
name|disable_transformation
condition|)
return|return;
operator|*
name|angle
operator|=
literal|360.0
operator|*
name|stroke
operator|/
name|mandala
operator|->
name|size
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mandala_image_size_changed_cb (GimpImage * image,gint previous_origin_x,gint previous_origin_y,gint previous_width,gint previous_height,GimpSymmetry * sym)
name|gimp_mandala_image_size_changed_cb
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
operator|||
name|previous_height
operator|!=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
condition|)
block|{
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
block|}
end_function

end_unit

