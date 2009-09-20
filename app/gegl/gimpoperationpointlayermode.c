begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationpointlayermode.c  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  * Copyright (C) 2008 Martin Nordholts<martinn@svn.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl-plugin.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationpointlayermode.h"
end_include

begin_comment
comment|/* The size of the area of which an evenly transparent Dissolve layer  * repeats its dissolve pattern  */
end_comment

begin_define
DECL|macro|DISSOLVE_REPEAT_WIDTH
define|#
directive|define
name|DISSOLVE_REPEAT_WIDTH
value|400
end_define

begin_define
DECL|macro|DISSOLVE_REPEAT_HEIGHT
define|#
directive|define
name|DISSOLVE_REPEAT_HEIGHT
value|300
end_define

begin_define
DECL|macro|DISSOLVE_SEED
define|#
directive|define
name|DISSOLVE_SEED
value|737893334
end_define

begin_define
DECL|macro|R
define|#
directive|define
name|R
value|(RED)
end_define

begin_define
DECL|macro|G
define|#
directive|define
name|G
value|(GREEN)
end_define

begin_define
DECL|macro|B
define|#
directive|define
name|B
value|(BLUE)
end_define

begin_define
DECL|macro|A
define|#
directive|define
name|A
value|(ALPHA)
end_define

begin_define
DECL|macro|L
define|#
directive|define
name|L
value|0
end_define

begin_define
DECL|macro|C
define|#
directive|define
name|C
value|1
end_define

begin_define
DECL|macro|H
define|#
directive|define
name|H
value|2
end_define

begin_define
DECL|macro|inA
define|#
directive|define
name|inA
value|(in[A])
end_define

begin_define
DECL|macro|inCa
define|#
directive|define
name|inCa
value|(in[c])
end_define

begin_define
DECL|macro|inC
define|#
directive|define
name|inC
value|(in[A]  ? in[c]  / in[A]  : 0.0)
end_define

begin_define
DECL|macro|layA
define|#
directive|define
name|layA
value|(lay[A])
end_define

begin_define
DECL|macro|layCa
define|#
directive|define
name|layCa
value|(lay[c])
end_define

begin_define
DECL|macro|layC
define|#
directive|define
name|layC
value|(lay[A] ? lay[c] / lay[A] : 0.0)
end_define

begin_define
DECL|macro|outCa
define|#
directive|define
name|outCa
value|(out[c])
end_define

begin_define
DECL|macro|outA
define|#
directive|define
name|outA
value|(out[A])
end_define

begin_define
DECL|macro|outC
define|#
directive|define
name|outC
value|(out[A] ? out[c] / out[A] : 0.0)
end_define

begin_define
DECL|macro|newCa
define|#
directive|define
name|newCa
value|(new[c])
end_define

begin_define
DECL|macro|EACH_CHANNEL (expr)
define|#
directive|define
name|EACH_CHANNEL
parameter_list|(
name|expr
parameter_list|)
define|\
value|for (c = RED; c< ALPHA; c++) \           {                           \             expr;                     \           }
end_define

begin_enum
enum|enum
DECL|enum|__anon2bf43f080103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_BLEND_MODE
name|PROP_BLEND_MODE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_operation_point_layer_mode_set_property
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
name|gimp_operation_point_layer_mode_get_property
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
name|gimp_operation_point_layer_mode_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_point_layer_mode_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|void
modifier|*
name|in_buf
parameter_list|,
name|void
modifier|*
name|aux_buf
parameter_list|,
name|void
modifier|*
name|out_buf
parameter_list|,
name|glong
name|samples
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationPointLayerMode,gimp_operation_point_layer_mode,GEGL_TYPE_OPERATION_POINT_COMPOSER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationPointLayerMode
argument_list|,
argument|gimp_operation_point_layer_mode
argument_list|,
argument|GEGL_TYPE_OPERATION_POINT_COMPOSER
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|guint32
name|dissolve_lut
index|[
name|DISSOLVE_REPEAT_WIDTH
operator|*
name|DISSOLVE_REPEAT_HEIGHT
index|]
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
name|gimp_operation_point_layer_mode_class_init
parameter_list|(
name|GimpOperationPointLayerModeClass
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
name|GeglOperationClass
modifier|*
name|operation_class
init|=
name|GEGL_OPERATION_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GeglOperationPointComposerClass
modifier|*
name|point_class
init|=
name|GEGL_OPERATION_POINT_COMPOSER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GRand
modifier|*
name|rand
init|=
name|g_rand_new_with_seed
argument_list|(
name|DISSOLVE_SEED
argument_list|)
decl_stmt|;
name|int
name|i
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_operation_point_layer_mode_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_point_layer_mode_get_property
expr_stmt|;
name|operation_class
operator|->
name|name
operator|=
literal|"gimp:point-layer-mode"
expr_stmt|;
name|operation_class
operator|->
name|description
operator|=
literal|"GIMP point layer mode operation"
expr_stmt|;
name|operation_class
operator|->
name|categories
operator|=
literal|"compositors"
expr_stmt|;
name|operation_class
operator|->
name|prepare
operator|=
name|gimp_operation_point_layer_mode_prepare
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_point_layer_mode_process
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_BLEND_MODE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"blend-mode"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_LAYER_MODE_EFFECTS
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|DISSOLVE_REPEAT_WIDTH
operator|*
name|DISSOLVE_REPEAT_HEIGHT
condition|;
name|i
operator|++
control|)
name|dissolve_lut
index|[
name|i
index|]
operator|=
name|g_rand_int
argument_list|(
name|rand
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_point_layer_mode_init (GimpOperationPointLayerMode * self)
name|gimp_operation_point_layer_mode_init
parameter_list|(
name|GimpOperationPointLayerMode
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_point_layer_mode_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_point_layer_mode_set_property
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
name|GimpOperationPointLayerMode
modifier|*
name|self
init|=
name|GIMP_OPERATION_POINT_LAYER_MODE
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
name|PROP_BLEND_MODE
case|:
name|self
operator|->
name|blend_mode
operator|=
name|g_value_get_enum
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
DECL|function|gimp_operation_point_layer_mode_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_point_layer_mode_get_property
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
name|GimpOperationPointLayerMode
modifier|*
name|self
init|=
name|GIMP_OPERATION_POINT_LAYER_MODE
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
name|PROP_BLEND_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|blend_mode
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
DECL|function|gimp_operation_point_layer_mode_prepare (GeglOperation * operation)
name|gimp_operation_point_layer_mode_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
block|{
name|Babl
modifier|*
name|format
init|=
name|babl_format
argument_list|(
literal|"RaGaBaA float"
argument_list|)
decl_stmt|;
name|gegl_operation_set_format
argument_list|(
name|operation
argument_list|,
literal|"input"
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|gegl_operation_set_format
argument_list|(
name|operation
argument_list|,
literal|"output"
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|gegl_operation_set_format
argument_list|(
name|operation
argument_list|,
literal|"aux"
argument_list|,
name|format
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_point_layer_mode_get_new_color_lchab (GimpLayerModeEffects blend_mode,const gfloat * in,const gfloat * lay,gfloat * new)
name|gimp_operation_point_layer_mode_get_new_color_lchab
parameter_list|(
name|GimpLayerModeEffects
name|blend_mode
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|in
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|lay
parameter_list|,
name|gfloat
modifier|*
name|new
parameter_list|)
block|{
name|float
name|in_lchab
index|[
literal|3
index|]
decl_stmt|;
name|float
name|lay_lchab
index|[
literal|3
index|]
decl_stmt|;
name|float
name|new_lchab
index|[
literal|3
index|]
decl_stmt|;
name|Babl
modifier|*
name|ragabaa_to_lchab
init|=
name|babl_fish
argument_list|(
name|babl_format
argument_list|(
literal|"RaGaBaA float"
argument_list|)
argument_list|,
name|babl_format
argument_list|(
literal|"CIE LCH(ab) float"
argument_list|)
argument_list|)
decl_stmt|;
name|Babl
modifier|*
name|lchab_to_ragabaa
init|=
name|babl_fish
argument_list|(
name|babl_format
argument_list|(
literal|"CIE LCH(ab) float"
argument_list|)
argument_list|,
name|babl_format
argument_list|(
literal|"RaGaBaA float"
argument_list|)
argument_list|)
decl_stmt|;
name|babl_process
argument_list|(
name|ragabaa_to_lchab
argument_list|,
operator|(
name|void
operator|*
operator|)
name|in
argument_list|,
operator|(
name|void
operator|*
operator|)
name|in_lchab
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|babl_process
argument_list|(
name|ragabaa_to_lchab
argument_list|,
operator|(
name|void
operator|*
operator|)
name|lay
argument_list|,
operator|(
name|void
operator|*
operator|)
name|lay_lchab
argument_list|,
literal|1
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|blend_mode
condition|)
block|{
case|case
name|GIMP_HUE_MODE
case|:
name|new_lchab
index|[
name|L
index|]
operator|=
name|in_lchab
index|[
name|L
index|]
expr_stmt|;
name|new_lchab
index|[
name|C
index|]
operator|=
name|in_lchab
index|[
name|C
index|]
expr_stmt|;
name|new_lchab
index|[
name|H
index|]
operator|=
name|lay_lchab
index|[
name|H
index|]
expr_stmt|;
break|break;
case|case
name|GIMP_SATURATION_MODE
case|:
name|new_lchab
index|[
name|L
index|]
operator|=
name|in_lchab
index|[
name|L
index|]
expr_stmt|;
name|new_lchab
index|[
name|C
index|]
operator|=
name|lay_lchab
index|[
name|C
index|]
expr_stmt|;
name|new_lchab
index|[
name|H
index|]
operator|=
name|in_lchab
index|[
name|H
index|]
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_MODE
case|:
name|new_lchab
index|[
name|L
index|]
operator|=
name|in_lchab
index|[
name|L
index|]
expr_stmt|;
name|new_lchab
index|[
name|C
index|]
operator|=
name|lay_lchab
index|[
name|C
index|]
expr_stmt|;
name|new_lchab
index|[
name|H
index|]
operator|=
name|lay_lchab
index|[
name|H
index|]
expr_stmt|;
break|break;
case|case
name|GIMP_VALUE_MODE
case|:
comment|/* GIMP_LIGHTNESS_MODE */
name|new_lchab
index|[
name|L
index|]
operator|=
name|lay_lchab
index|[
name|L
index|]
expr_stmt|;
name|new_lchab
index|[
name|C
index|]
operator|=
name|in_lchab
index|[
name|C
index|]
expr_stmt|;
name|new_lchab
index|[
name|H
index|]
operator|=
name|in_lchab
index|[
name|H
index|]
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
break|break;
block|}
name|babl_process
argument_list|(
name|lchab_to_ragabaa
argument_list|,
name|new_lchab
argument_list|,
name|new
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_point_layer_mode_get_color_erase_color (const gfloat * in,const gfloat * lay,gfloat * out)
name|gimp_operation_point_layer_mode_get_color_erase_color
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|in
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|lay
parameter_list|,
name|gfloat
modifier|*
name|out
parameter_list|)
block|{
name|GimpRGB
name|inRGB
decl_stmt|;
name|GimpRGB
name|layRGB
decl_stmt|;
if|if
condition|(
name|inA
operator|<=
literal|0.0
condition|)
name|gimp_rgba_set
argument_list|(
operator|&
name|inRGB
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|inA
argument_list|)
expr_stmt|;
else|else
name|gimp_rgba_set
argument_list|(
operator|&
name|inRGB
argument_list|,
name|in
index|[
name|R
index|]
operator|/
name|inA
argument_list|,
name|in
index|[
name|G
index|]
operator|/
name|inA
argument_list|,
name|in
index|[
name|B
index|]
operator|/
name|inA
argument_list|,
name|inA
argument_list|)
expr_stmt|;
if|if
condition|(
name|layA
operator|<=
literal|0.0
condition|)
name|gimp_rgba_set
argument_list|(
operator|&
name|layRGB
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|layA
argument_list|)
expr_stmt|;
else|else
name|gimp_rgba_set
argument_list|(
operator|&
name|layRGB
argument_list|,
name|lay
index|[
name|R
index|]
operator|/
name|layA
argument_list|,
name|lay
index|[
name|G
index|]
operator|/
name|layA
argument_list|,
name|lay
index|[
name|B
index|]
operator|/
name|layA
argument_list|,
name|layA
argument_list|)
expr_stmt|;
name|paint_funcs_color_erase_helper
argument_list|(
operator|&
name|inRGB
argument_list|,
operator|&
name|layRGB
argument_list|)
expr_stmt|;
name|out
index|[
name|A
index|]
operator|=
name|inRGB
operator|.
name|a
expr_stmt|;
name|out
index|[
name|R
index|]
operator|=
name|inRGB
operator|.
name|r
operator|*
name|out
index|[
name|A
index|]
expr_stmt|;
name|out
index|[
name|G
index|]
operator|=
name|inRGB
operator|.
name|g
operator|*
name|out
index|[
name|A
index|]
expr_stmt|;
name|out
index|[
name|B
index|]
operator|=
name|inRGB
operator|.
name|b
operator|*
name|out
index|[
name|A
index|]
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_point_layer_mode_process (GeglOperation * operation,void * in_buf,void * aux_buf,void * out_buf,glong samples,const GeglRectangle * roi)
name|gimp_operation_point_layer_mode_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|void
modifier|*
name|in_buf
parameter_list|,
name|void
modifier|*
name|aux_buf
parameter_list|,
name|void
modifier|*
name|out_buf
parameter_list|,
name|glong
name|samples
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
block|{
name|GimpOperationPointLayerMode
modifier|*
name|self
init|=
name|GIMP_OPERATION_POINT_LAYER_MODE
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|GimpLayerModeEffects
name|blend_mode
init|=
name|self
operator|->
name|blend_mode
decl_stmt|;
name|gfloat
modifier|*
name|in
init|=
name|in_buf
decl_stmt|;
comment|/* composite of layers below */
name|gfloat
modifier|*
name|lay
init|=
name|aux_buf
decl_stmt|;
comment|/* layer */
name|gfloat
modifier|*
name|out
init|=
name|out_buf
decl_stmt|;
comment|/* resulting composite */
name|glong
name|sample
init|=
name|samples
decl_stmt|;
name|gint
name|c
init|=
literal|0
decl_stmt|;
name|gint
name|x
init|=
literal|0
decl_stmt|;
name|gint
name|y
init|=
literal|0
decl_stmt|;
name|gfloat
name|new
index|[
literal|3
index|]
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|}
decl_stmt|;
while|while
condition|(
name|sample
operator|--
condition|)
block|{
switch|switch
condition|(
name|blend_mode
condition|)
block|{
case|case
name|GIMP_ERASE_MODE
case|:
case|case
name|GIMP_ANTI_ERASE_MODE
case|:
case|case
name|GIMP_COLOR_ERASE_MODE
case|:
case|case
name|GIMP_REPLACE_MODE
case|:
case|case
name|GIMP_DISSOLVE_MODE
case|:
comment|/* These modes handle alpha themselves */
break|break;
default|default:
comment|/* Porter-Duff model for the rest */
name|outA
operator|=
name|layA
operator|+
name|inA
operator|-
name|layA
operator|*
name|inA
expr_stmt|;
block|}
switch|switch
condition|(
name|blend_mode
condition|)
block|{
case|case
name|GIMP_ERASE_MODE
case|:
comment|/* Eraser mode */
name|outA
operator|=
name|inA
operator|-
name|inA
operator|*
name|layA
expr_stmt|;
if|if
condition|(
name|inA
operator|<=
literal|0.0
condition|)
name|EACH_CHANNEL
argument_list|(
argument|outCa =
literal|0.0
argument_list|)
else|else
name|EACH_CHANNEL
argument_list|(
name|outCa
operator|=
name|inC
operator|*
name|outA
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ANTI_ERASE_MODE
case|:
comment|/* Eraser mode */
name|outA
operator|=
name|inA
operator|+
operator|(
literal|1
operator|-
name|inA
operator|)
operator|*
name|layA
expr_stmt|;
if|if
condition|(
name|inA
operator|<=
literal|0.0
condition|)
name|EACH_CHANNEL
argument_list|(
argument|outCa =
literal|0.0
argument_list|)
else|else
name|EACH_CHANNEL
argument_list|(
name|outCa
operator|=
name|inC
operator|*
name|outA
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_ERASE_MODE
case|:
comment|/* Paint mode */
name|gimp_operation_point_layer_mode_get_color_erase_color
argument_list|(
name|in
argument_list|,
name|lay
argument_list|,
name|out
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_REPLACE_MODE
case|:
comment|/* Filter fade mode */
name|outA
operator|=
name|layA
expr_stmt|;
name|EACH_CHANNEL
argument_list|(
name|outCa
operator|=
name|layCa
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_DISSOLVE_MODE
case|:
comment|/* The layer pixel has layA probability of being composited            * with 100% opacity, else not all            */
name|x
operator|=
operator|(
name|roi
operator|->
name|x
operator|+
name|sample
operator|-
operator|(
name|sample
operator|/
name|roi
operator|->
name|width
operator|)
operator|*
name|roi
operator|->
name|width
operator|)
operator|%
name|DISSOLVE_REPEAT_WIDTH
expr_stmt|;
name|y
operator|=
operator|(
name|roi
operator|->
name|y
operator|+
name|sample
operator|/
name|roi
operator|->
name|width
operator|)
operator|%
name|DISSOLVE_REPEAT_HEIGHT
expr_stmt|;
if|if
condition|(
name|layA
operator|*
name|G_MAXUINT32
operator|>=
name|dissolve_lut
index|[
name|y
operator|*
name|DISSOLVE_REPEAT_WIDTH
operator|+
name|x
index|]
condition|)
block|{
name|outA
operator|=
literal|1.0
expr_stmt|;
name|EACH_CHANNEL
argument_list|(
name|outCa
operator|=
name|layC
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|outA
operator|=
name|inA
expr_stmt|;
name|EACH_CHANNEL
argument_list|(
name|outCa
operator|=
name|inCa
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_NORMAL_MODE
case|:
comment|/* Porter-Duff A over B */
name|EACH_CHANNEL
argument_list|(
name|outCa
operator|=
name|layCa
operator|+
name|inCa
operator|*
operator|(
literal|1
operator|-
name|layA
operator|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_BEHIND_MODE
case|:
comment|/* Porter-Duff B over A */
name|EACH_CHANNEL
argument_list|(
name|outCa
operator|=
name|inCa
operator|+
name|layCa
operator|*
operator|(
literal|1
operator|-
name|inA
operator|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_MULTIPLY_MODE
case|:
comment|/* SVG 1.2 multiply */
name|EACH_CHANNEL
argument_list|(
name|outCa
operator|=
name|layCa
operator|*
name|inCa
operator|+
name|layCa
operator|*
operator|(
literal|1
operator|-
name|inA
operator|)
operator|+
name|inCa
operator|*
operator|(
literal|1
operator|-
name|layA
operator|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_SCREEN_MODE
case|:
comment|/* SVG 1.2 screen */
name|EACH_CHANNEL
argument_list|(
name|outCa
operator|=
name|layCa
operator|+
name|inCa
operator|-
name|layCa
operator|*
name|inCa
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_DIFFERENCE_MODE
case|:
comment|/* SVG 1.2 difference */
name|EACH_CHANNEL
argument_list|(
name|outCa
operator|=
name|inCa
operator|+
name|layCa
operator|-
literal|2
operator|*
name|MIN
argument_list|(
name|layCa
operator|*
name|inA
argument_list|,
name|inCa
operator|*
name|layA
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_DARKEN_ONLY_MODE
case|:
comment|/* SVG 1.2 darken */
name|EACH_CHANNEL
argument_list|(
name|outCa
operator|=
name|MIN
argument_list|(
name|layCa
operator|*
name|inA
argument_list|,
name|inCa
operator|*
name|layA
argument_list|)
operator|+
name|layCa
operator|*
operator|(
literal|1
operator|-
name|inA
operator|)
operator|+
name|inCa
operator|*
operator|(
literal|1
operator|-
name|layA
operator|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_LIGHTEN_ONLY_MODE
case|:
comment|/* SVG 1.2 lighten */
name|EACH_CHANNEL
argument_list|(
name|outCa
operator|=
name|MAX
argument_list|(
name|layCa
operator|*
name|inA
argument_list|,
name|inCa
operator|*
name|layA
argument_list|)
operator|+
name|layCa
operator|*
operator|(
literal|1
operator|-
name|inA
operator|)
operator|+
name|inCa
operator|*
operator|(
literal|1
operator|-
name|layA
operator|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_OVERLAY_MODE
case|:
comment|/* SVG 1.2 overlay */
name|EACH_CHANNEL
argument_list|(
argument|if (
literal|2
argument|* inCa< inA)             outCa =
literal|2
argument|* layCa * inCa + layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA);           else             outCa = layA * inA -
literal|2
argument|* (inA - inCa) * (layA - layCa) + layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA)
argument_list|)
empty_stmt|;
break|break;
case|case
name|GIMP_DODGE_MODE
case|:
comment|/* SVG 1.2 color-dodge */
name|EACH_CHANNEL
argument_list|(
argument|if (layCa * inA + inCa * layA>= layA * inA)             outCa = layA * inA + layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA);           else             outCa = inCa * layA / (
literal|1
argument|- layC) + layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA)
argument_list|)
empty_stmt|;
break|break;
case|case
name|GIMP_BURN_MODE
case|:
comment|/* SVG 1.2 color-burn */
name|EACH_CHANNEL
argument_list|(
argument|if (layCa * inA + inCa * layA<= layA * inA)             outCa = layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA);           else             outCa = layA * (layCa * inA + inCa * layA - layA * inA) / layCa + layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA)
argument_list|)
empty_stmt|;
break|break;
case|case
name|GIMP_HARDLIGHT_MODE
case|:
comment|/* SVG 1.2 hard-light */
name|EACH_CHANNEL
argument_list|(
argument|if (
literal|2
argument|* layCa< layA)             outCa =
literal|2
argument|* layCa * inCa + layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA);           else             outCa = layA * inA -
literal|2
argument|* (inA - inCa) * (layA - layCa) + layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA)
argument_list|)
empty_stmt|;
break|break;
case|case
name|GIMP_SOFTLIGHT_MODE
case|:
comment|/* Custom SVG 1.2:            *            * f(Sc, Dc) = Dc * (Dc + (2 * Sc * (1 - Dc)))            */
name|EACH_CHANNEL
argument_list|(
name|outCa
operator|=
name|inCa
operator|*
operator|(
name|layA
operator|*
name|inC
operator|+
operator|(
literal|2
operator|*
name|layCa
operator|*
operator|(
literal|1
operator|-
name|inC
operator|)
operator|)
operator|)
operator|+
name|layCa
operator|*
operator|(
literal|1
operator|-
name|inA
operator|)
operator|+
name|inCa
operator|*
operator|(
literal|1
operator|-
name|layA
operator|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ADDITION_MODE
case|:
comment|/* Custom SVG 1.2:            *            * if Dc + Sc>= 1            *   f(Sc, Dc) = 1            * otherwise            *   f(Sc, Dc) = Dc + Sc            */
name|EACH_CHANNEL
argument_list|(
argument|if (layCa * inA + inCa * layA>= layA * inA)             outCa = layA * inA + layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA);           else             outCa = inCa + layCa
argument_list|)
empty_stmt|;
break|break;
case|case
name|GIMP_SUBTRACT_MODE
case|:
comment|/* Custom SVG 1.2:            *            * if Dc - Sc<= 0            *   f(Sc, Dc) = 0            * otherwise            *   f(Sc, Dc) = Dc - Sc            */
name|EACH_CHANNEL
argument_list|(
argument|if (inCa * layA - layCa * inA<=
literal|0
argument|)             outCa = layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA);           else             outCa = inCa + layCa -
literal|2
argument|* layCa * inA
argument_list|)
empty_stmt|;
break|break;
case|case
name|GIMP_GRAIN_EXTRACT_MODE
case|:
comment|/* Custom SVG 1.2:            *            * if Dc - Sc + 0.5>= 1            *   f(Sc, Dc) = 1            * otherwise if Dc - Sc + 0.5<= 0            *   f(Sc, Dc) = 0            * otherwise            *   f(Sc, Dc) = f(Sc, Dc) = Dc - Sc + 0.5            */
name|EACH_CHANNEL
argument_list|(
argument|if (inCa * layA - layCa * inA +
literal|0.5
argument|* layA * inA>= layA * inA)             outCa = layA * inA + layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA);           else if (inCa * layA - layCa * inA +
literal|0.5
argument|* layA * inA<=
literal|0
argument|)             outCa = layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA);           else             outCa = inCa + layCa -
literal|2
argument|* layCa * inA +
literal|0.5
argument|* inA * layA
argument_list|)
empty_stmt|;
break|break;
case|case
name|GIMP_GRAIN_MERGE_MODE
case|:
comment|/* Custom SVG 1.2:            *            * if Dc + Sc - 0.5>= 1            *   f(Sc, Dc) = 1            * otherwise if Dc + Sc - 0.5<= 0            *   f(Sc, Dc) = 0            * otherwise            *   f(Sc, Dc) = f(Sc, Dc) = Dc + Sc - 0.5            */
name|EACH_CHANNEL
argument_list|(
argument|if (inCa * layA + layCa * inA -
literal|0.5
argument|* layA * inA>= layA * inA)             outCa = layA * inA + layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA);           else if (inCa * layA + layCa * inA -
literal|0.5
argument|* layA * inA<=
literal|0
argument|)             outCa = layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA);           else             outCa = inCa + layCa -
literal|0.5
argument|* inA * layA
argument_list|)
empty_stmt|;
break|break;
case|case
name|GIMP_DIVIDE_MODE
case|:
comment|/* Custom SVG 1.2:            *            * if Dc / Sc> 1            *   f(Sc, Dc) = 1            * otherwise            *   f(Sc, Dc) = Dc / Sc            */
name|EACH_CHANNEL
argument_list|(
argument|if (layA ==
literal|0.0
argument||| inCa / layCa> inA / layA)             outCa = layA * inA + layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA);           else             outCa = inCa * layA * layA / layCa + layCa * (
literal|1
argument|- inA) + inCa * (
literal|1
argument|- layA)
argument_list|)
empty_stmt|;
break|break;
case|case
name|GIMP_HUE_MODE
case|:
case|case
name|GIMP_SATURATION_MODE
case|:
case|case
name|GIMP_COLOR_MODE
case|:
case|case
name|GIMP_VALUE_MODE
case|:
comment|/* GIMP_LIGHTNESS_MODE */
comment|/* Custom SVG 1.2:            *            * f(Sc, Dc) = New color            */
comment|/* FIXME: Doing this call for each pixel is very slow, we            * should make conversions on larger chunks of data            */
name|gimp_operation_point_layer_mode_get_new_color_lchab
argument_list|(
name|blend_mode
argument_list|,
name|in
argument_list|,
name|lay
argument_list|,
name|new
argument_list|)
expr_stmt|;
name|EACH_CHANNEL
argument_list|(
name|outCa
operator|=
name|newCa
operator|*
name|layA
operator|*
name|inA
operator|+
name|layCa
operator|*
operator|(
literal|1
operator|-
name|inA
operator|)
operator|+
name|inCa
operator|*
operator|(
literal|1
operator|-
name|layA
operator|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_error
argument_list|(
literal|"Unknown layer mode"
argument_list|)
expr_stmt|;
break|break;
block|}
name|in
operator|+=
literal|4
expr_stmt|;
name|lay
operator|+=
literal|4
expr_stmt|;
name|out
operator|+=
literal|4
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

