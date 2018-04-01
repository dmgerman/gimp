begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsymmetry.c  * Copyright (C) 2015 Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
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
file|"gimpsymmetry.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon287a019a0103
block|{
DECL|enumerator|STROKES_UPDATED
name|STROKES_UPDATED
block|,
DECL|enumerator|GUI_PARAM_CHANGED
name|GUI_PARAM_CHANGED
block|,
DECL|enumerator|ACTIVE_CHANGED
name|ACTIVE_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon287a019a0203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_IMAGE
name|PROP_IMAGE
block|,
DECL|enumerator|PROP_ACTIVE
name|PROP_ACTIVE
block|,
DECL|enumerator|PROP_VERSION
name|PROP_VERSION
block|, }
enum|;
end_enum

begin_comment
comment|/* Local function prototypes */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_symmetry_finalize
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
name|gimp_symmetry_set_property
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
name|gimp_symmetry_get_property
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
name|gimp_symmetry_real_update_strokes
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GeglNode
modifier|*
name|gimp_symmetry_real_get_op
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_symmetry_real_update_version
parameter_list|(
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpSymmetry
argument_list|,
argument|gimp_symmetry
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG, NULL)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_symmetry_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|gimp_symmetry_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_symmetry_class_init (GimpSymmetryClass * klass)
name|gimp_symmetry_class_init
parameter_list|(
name|GimpSymmetryClass
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
comment|/* This signal should likely be emitted at the end of    * update_strokes() if stroke coordinates were changed.    */
name|gimp_symmetry_signals
index|[
name|STROKES_UPDATED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"strokes-updated"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|)
expr_stmt|;
comment|/* This signal should be emitted when you request a change in the    * settings UI. For instance adding some settings (therefore having    * a dynamic UI), or changing scale min/max extremes, etc.    */
name|gimp_symmetry_signals
index|[
name|GUI_PARAM_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"gui-param-changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|)
expr_stmt|;
name|gimp_symmetry_signals
index|[
name|ACTIVE_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"active-changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpSymmetryClass
argument_list|,
name|active_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_symmetry_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_symmetry_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_symmetry_get_property
expr_stmt|;
name|klass
operator|->
name|label
operator|=
name|_
argument_list|(
literal|"None"
argument_list|)
expr_stmt|;
name|klass
operator|->
name|update_strokes
operator|=
name|gimp_symmetry_real_update_strokes
expr_stmt|;
name|klass
operator|->
name|get_operation
operator|=
name|gimp_symmetry_real_get_op
expr_stmt|;
name|klass
operator|->
name|active_changed
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|update_version
operator|=
name|gimp_symmetry_real_update_version
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_IMAGE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"image"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_ACTIVE
argument_list|,
literal|"active"
argument_list|,
name|_
argument_list|(
literal|"Active"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Activate symmetry painting"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_VERSION
argument_list|,
literal|"version"
argument_list|,
literal|"Symmetry version"
argument_list|,
literal|"Version of the symmetry object"
argument_list|,
operator|-
literal|1
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_symmetry_init (GimpSymmetry * sym)
name|gimp_symmetry_init
parameter_list|(
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_symmetry_finalize (GObject * object)
name|gimp_symmetry_finalize
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
name|g_clear_object
argument_list|(
operator|&
name|sym
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|sym
operator|->
name|origin
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
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
DECL|function|gimp_symmetry_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_symmetry_set_property
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
name|GimpSymmetry
modifier|*
name|sym
init|=
name|GIMP_SYMMETRY
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
name|PROP_IMAGE
case|:
name|sym
operator|->
name|image
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ACTIVE
case|:
name|sym
operator|->
name|active
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|sym
argument_list|,
name|gimp_symmetry_signals
index|[
name|ACTIVE_CHANGED
index|]
argument_list|,
literal|0
argument_list|,
name|sym
operator|->
name|active
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VERSION
case|:
name|sym
operator|->
name|version
operator|=
name|g_value_get_int
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
DECL|function|gimp_symmetry_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_symmetry_get_property
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
name|GimpSymmetry
modifier|*
name|sym
init|=
name|GIMP_SYMMETRY
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
name|PROP_IMAGE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|sym
operator|->
name|image
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ACTIVE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|sym
operator|->
name|active
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VERSION
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|sym
operator|->
name|version
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
DECL|function|gimp_symmetry_real_update_strokes (GimpSymmetry * sym,GimpDrawable * drawable,GimpCoords * origin)
name|gimp_symmetry_real_update_strokes
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
comment|/* The basic symmetry just uses the origin as is. */
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
name|g_memdup
argument_list|(
name|origin
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpCoords
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GeglNode
modifier|*
DECL|function|gimp_symmetry_real_get_op (GimpSymmetry * sym,gint stroke,gint paint_width,gint paint_height)
name|gimp_symmetry_real_get_op
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
comment|/* The basic symmetry just returns NULL, since no transformation of the    * brush painting happen. */
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_symmetry_real_update_version (GimpSymmetry * symmetry)
name|gimp_symmetry_real_update_version
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|)
block|{
comment|/* Currently all symmetries are at version 0. So all this check has to    * do is verify that we are at version 0.    * If one of the child symmetry bumps its version, it will have to    * override the update_version() virtual function and do any necessary    * update there (for instance new properties, modified properties, or    * whatnot).    */
name|gint
name|version
decl_stmt|;
name|g_object_get
argument_list|(
name|symmetry
argument_list|,
literal|"version"
argument_list|,
operator|&
name|version
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
operator|(
name|version
operator|==
literal|0
operator|)
return|;
block|}
end_function

begin_comment
comment|/***** Public Functions *****/
end_comment

begin_comment
comment|/**  * gimp_symmetry_set_origin:  * @sym:      the #GimpSymmetry  * @drawable: the #GimpDrawable where painting will happen  * @origin:   new base coordinates.  *  * Set the symmetry to new origin coordinates and drawable.  **/
end_comment

begin_function
name|void
DECL|function|gimp_symmetry_set_origin (GimpSymmetry * sym,GimpDrawable * drawable,GimpCoords * origin)
name|gimp_symmetry_set_origin
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SYMMETRY
argument_list|(
name|sym
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|==
name|sym
operator|->
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|!=
name|sym
operator|->
name|drawable
condition|)
block|{
if|if
condition|(
name|sym
operator|->
name|drawable
condition|)
name|g_object_unref
argument_list|(
name|sym
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|sym
operator|->
name|drawable
operator|=
name|g_object_ref
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|origin
operator|!=
name|sym
operator|->
name|origin
condition|)
block|{
name|g_free
argument_list|(
name|sym
operator|->
name|origin
argument_list|)
expr_stmt|;
name|sym
operator|->
name|origin
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
block|}
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
name|GIMP_SYMMETRY_GET_CLASS
argument_list|(
name|sym
argument_list|)
operator|->
name|update_strokes
argument_list|(
name|sym
argument_list|,
name|drawable
argument_list|,
name|origin
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_symmetry_get_origin:  * @sym: the #GimpSymmetry  *  * Returns: the origin stroke coordinates.  * The returned value is owned by the #GimpSymmetry and must not be freed.  **/
end_comment

begin_function
name|GimpCoords
modifier|*
DECL|function|gimp_symmetry_get_origin (GimpSymmetry * sym)
name|gimp_symmetry_get_origin
parameter_list|(
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_SYMMETRY
argument_list|(
name|sym
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|sym
operator|->
name|origin
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_symmetry_get_size:  * @sym: the #GimpSymmetry  *  * Returns: the total number of strokes.  **/
end_comment

begin_function
name|gint
DECL|function|gimp_symmetry_get_size (GimpSymmetry * sym)
name|gimp_symmetry_get_size
parameter_list|(
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_SYMMETRY
argument_list|(
name|sym
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|g_list_length
argument_list|(
name|sym
operator|->
name|strokes
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_symmetry_get_coords:  * @sym:    the #GimpSymmetry  * @stroke: the stroke number  *  * Returns: the coordinates of the stroke number @stroke.  * The returned value is owned by the #GimpSymmetry and must not be freed.  **/
end_comment

begin_function
name|GimpCoords
modifier|*
DECL|function|gimp_symmetry_get_coords (GimpSymmetry * sym,gint stroke)
name|gimp_symmetry_get_coords
parameter_list|(
name|GimpSymmetry
modifier|*
name|sym
parameter_list|,
name|gint
name|stroke
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_SYMMETRY
argument_list|(
name|sym
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_list_nth_data
argument_list|(
name|sym
operator|->
name|strokes
argument_list|,
name|stroke
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_symmetry_get_operation:  * @sym:          the #GimpSymmetry  * @stroke:       the stroke number  * @paint_width:  the width of the painting area  * @paint_height: the height of the painting area  *  * Returns: the operation to apply to the paint buffer for stroke number @stroke.  * NULL means to copy the original stroke as-is.  **/
end_comment

begin_function
name|GeglNode
modifier|*
DECL|function|gimp_symmetry_get_operation (GimpSymmetry * sym,gint stroke,gint paint_width,gint paint_height)
name|gimp_symmetry_get_operation
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_SYMMETRY
argument_list|(
name|sym
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_SYMMETRY_GET_CLASS
argument_list|(
name|sym
argument_list|)
operator|->
name|get_operation
argument_list|(
name|sym
argument_list|,
name|stroke
argument_list|,
name|paint_width
argument_list|,
name|paint_height
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  * gimp_symmetry_parasite_name:  * @type: the #GimpSymmetry's #GType  *  * Returns: a newly allocated string.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_symmetry_parasite_name (GType type)
name|gimp_symmetry_parasite_name
parameter_list|(
name|GType
name|type
parameter_list|)
block|{
return|return
name|g_strconcat
argument_list|(
literal|"gimp-image-symmetry:"
argument_list|,
name|g_type_name
argument_list|(
name|type
argument_list|)
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpParasite
modifier|*
DECL|function|gimp_symmetry_to_parasite (const GimpSymmetry * sym)
name|gimp_symmetry_to_parasite
parameter_list|(
specifier|const
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|gchar
modifier|*
name|parasite_name
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_SYMMETRY
argument_list|(
name|sym
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|str
operator|=
name|gimp_config_serialize_to_string
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|sym
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|str
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|parasite_name
operator|=
name|gimp_symmetry_parasite_name
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|sym
argument_list|)
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
name|parasite_name
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|str
argument_list|)
operator|+
literal|1
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|parasite_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
return|return
name|parasite
return|;
block|}
end_function

begin_function
name|GimpSymmetry
modifier|*
DECL|function|gimp_symmetry_from_parasite (const GimpParasite * parasite,GimpImage * image,GType type)
name|gimp_symmetry_from_parasite
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GType
name|type
parameter_list|)
block|{
name|GimpSymmetry
modifier|*
name|symmetry
decl_stmt|;
name|gchar
modifier|*
name|parasite_name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|str
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|parasite_name
operator|=
name|gimp_symmetry_parasite_name
argument_list|(
name|type
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parasite
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|strcmp
argument_list|(
name|gimp_parasite_name
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|parasite_name
argument_list|)
operator|==
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|str
operator|=
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|str
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|symmetry
operator|=
name|gimp_image_symmetry_new
argument_list|(
name|image
argument_list|,
name|type
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|symmetry
argument_list|,
literal|"version"
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_string
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|symmetry
argument_list|)
argument_list|,
name|str
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Failed to deserialize symmetry parasite: %s\n"
literal|"\t- parasite name: %s\n\t- parasite data: %s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|,
name|parasite_name
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|symmetry
argument_list|)
expr_stmt|;
name|symmetry
operator|=
name|NULL
expr_stmt|;
block|}
name|g_free
argument_list|(
name|parasite_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|symmetry
condition|)
block|{
name|gint
name|version
decl_stmt|;
name|g_object_get
argument_list|(
name|symmetry
argument_list|,
literal|"version"
argument_list|,
operator|&
name|version
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|version
operator|==
operator|-
literal|1
condition|)
block|{
comment|/* If version has not been updated, let's assume this parasite was            * not representing symmetry settings.            */
name|g_object_unref
argument_list|(
name|symmetry
argument_list|)
expr_stmt|;
name|symmetry
operator|=
name|NULL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_SYMMETRY_GET_CLASS
argument_list|(
name|symmetry
argument_list|)
operator|->
name|update_version
argument_list|(
name|symmetry
argument_list|)
operator|&&
operator|!
name|GIMP_SYMMETRY_GET_CLASS
argument_list|(
name|symmetry
argument_list|)
operator|->
name|update_version
argument_list|(
name|symmetry
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|symmetry
argument_list|)
expr_stmt|;
name|symmetry
operator|=
name|NULL
expr_stmt|;
block|}
block|}
return|return
name|symmetry
return|;
block|}
end_function

end_unit

