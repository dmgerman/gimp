begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationpointcomposer.c  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  * Copyright (C) 2008 Martin Nordholts<martinn@svn.gnome.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationpointlayermode.h"
end_include

begin_define
DECL|macro|R
define|#
directive|define
name|R
value|RED
end_define

begin_define
DECL|macro|G
define|#
directive|define
name|G
value|GREEN
end_define

begin_define
DECL|macro|B
define|#
directive|define
name|B
value|BLUE
end_define

begin_define
DECL|macro|A
define|#
directive|define
name|A
value|ALPHA
end_define

begin_define
DECL|macro|inC
define|#
directive|define
name|inC
value|in[c]
end_define

begin_define
DECL|macro|inA
define|#
directive|define
name|inA
value|in[A]
end_define

begin_define
DECL|macro|layC
define|#
directive|define
name|layC
value|lay[c]
end_define

begin_define
DECL|macro|layA
define|#
directive|define
name|layA
value|lay[A]
end_define

begin_define
DECL|macro|outC
define|#
directive|define
name|outC
value|out[c]
end_define

begin_define
DECL|macro|outA
define|#
directive|define
name|outA
value|out[A]
end_define

begin_define
DECL|macro|BLEND (mode,expr)
define|#
directive|define
name|BLEND
parameter_list|(
name|mode
parameter_list|,
name|expr
parameter_list|)
define|\
value|case (mode):                    \           for (c = RED; c< ALPHA; c++) \             {                           \               expr;                     \             }                           \           break;
end_define

begin_enum
enum|enum
DECL|enum|__anon29c659de0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_BLEND_MODE
name|PROP_BLEND_MODE
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpOperationPointLayerModeClass
struct|struct
name|_GimpOperationPointLayerModeClass
block|{
DECL|member|parent_class
name|GeglOperationPointComposerClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationPointLayerMode
struct|struct
name|_GimpOperationPointLayerMode
block|{
DECL|member|parent_instance
name|GeglOperationPointComposer
name|parent_instance
decl_stmt|;
DECL|member|blend_mode
name|GimpLayerModeEffects
name|blend_mode
decl_stmt|;
block|}
struct|;
end_struct

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
name|gint
name|c
init|=
literal|0
decl_stmt|;
while|while
condition|(
name|samples
operator|--
condition|)
block|{
switch|switch
condition|(
name|self
operator|->
name|blend_mode
condition|)
block|{
comment|/* Porter-Duff A over B */
name|BLEND
argument_list|(
name|GIMP_NORMAL_MODE
argument_list|,
name|outC
operator|=
name|layC
operator|+
name|inC
operator|*
operator|(
literal|1
operator|-
name|layA
operator|)
argument_list|)
expr_stmt|;
comment|/* Porter-Duff B over A */
name|BLEND
argument_list|(
name|GIMP_BEHIND_MODE
argument_list|,
name|outC
operator|=
name|inC
operator|+
name|layC
operator|*
operator|(
literal|1
operator|-
name|inA
operator|)
argument_list|)
expr_stmt|;
comment|/* SVG 1.2 multiply */
name|BLEND
argument_list|(
name|GIMP_MULTIPLY_MODE
argument_list|,
name|outC
operator|=
name|layC
operator|*
name|inC
operator|+
name|layC
operator|*
operator|(
literal|1
operator|-
name|inA
operator|)
operator|+
name|inC
operator|*
operator|(
literal|1
operator|-
name|layA
operator|)
argument_list|)
expr_stmt|;
comment|/* SVG 1.2 screen */
name|BLEND
argument_list|(
name|GIMP_SCREEN_MODE
argument_list|,
name|outC
operator|=
name|layC
operator|+
name|inC
operator|-
name|layC
operator|*
name|inC
argument_list|)
expr_stmt|;
comment|/* SVG 1.2 difference */
name|BLEND
argument_list|(
name|GIMP_DIFFERENCE_MODE
argument_list|,
name|outC
operator|=
name|inC
operator|+
name|layC
operator|-
literal|2
operator|*
name|MIN
argument_list|(
name|layC
operator|*
name|inA
argument_list|,
name|inC
operator|*
name|layA
argument_list|)
argument_list|)
expr_stmt|;
comment|/* SVG 1.2 darken */
name|BLEND
argument_list|(
name|GIMP_DARKEN_ONLY_MODE
argument_list|,
name|outC
operator|=
name|MIN
argument_list|(
name|layC
operator|*
name|inA
argument_list|,
name|inC
operator|*
name|layA
argument_list|)
operator|+
name|layC
operator|*
operator|(
literal|1
operator|-
name|inA
operator|)
operator|+
name|inC
operator|*
operator|(
literal|1
operator|-
name|layA
operator|)
argument_list|)
expr_stmt|;
comment|/* SVG 1.2 lighten */
name|BLEND
argument_list|(
name|GIMP_LIGHTEN_ONLY_MODE
argument_list|,
name|outC
operator|=
name|MAX
argument_list|(
name|layC
operator|*
name|inA
argument_list|,
name|inC
operator|*
name|layA
argument_list|)
operator|+
name|layC
operator|*
operator|(
literal|1
operator|-
name|inA
operator|)
operator|+
name|inC
operator|*
operator|(
literal|1
operator|-
name|layA
operator|)
argument_list|)
expr_stmt|;
comment|/* SVG 1.2 overlay */
name|BLEND
argument_list|(
argument|GIMP_OVERLAY_MODE
argument_list|,
argument|if (
literal|2
argument|* inC< inA)             outC =
literal|2
argument|* layC * inC + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA);           else             outC = layA * inA -
literal|2
argument|* (inA - inC) * (layA - layC) + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA)
argument_list|)
empty_stmt|;
comment|/* SVG 1.2 color-dodge */
name|BLEND
argument_list|(
argument|GIMP_DODGE_MODE
argument_list|,
argument|if (layC * inA + inC * layA>= layA * inA)             outC = layA * inA + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA);           else             outC = inC * layA / (
literal|1
argument|- layC / layA) + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA)
argument_list|)
empty_stmt|;
comment|/* SVG 1.2 color-burn */
name|BLEND
argument_list|(
argument|GIMP_BURN_MODE
argument_list|,
argument|if (layC * inA + inC * layA<= layA * inA)             outC = layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA);           else             outC = layA * (layC * inA + inC * layA - layA * inA) / layC + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA)
argument_list|)
empty_stmt|;
comment|/* SVG 1.2 hard-light */
name|BLEND
argument_list|(
argument|GIMP_HARDLIGHT_MODE
argument_list|,
argument|if (
literal|2
argument|* layC< layA)             outC =
literal|2
argument|* layC * inC + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA);           else             outC = layA * inA -
literal|2
argument|* (inA - inC) * (layA - layC) + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA)
argument_list|)
empty_stmt|;
comment|/* SVG 1.2 soft-light */
comment|/* XXX: Why is the result so different from legacy Soft Light? */
name|BLEND
argument_list|(
argument|GIMP_SOFTLIGHT_MODE
argument_list|,
argument|if (
literal|2
argument|* layC< layA)             outC = inC * (layA - (
literal|1
argument|- inC / inA) * (
literal|2
argument|* layC - layA)) + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA);           else if (
literal|8
argument|* inC<= inA)             outC = inC * (layA - (
literal|1
argument|- inC / inA) * (
literal|2
argument|* layC - layA) * (
literal|3
argument|-
literal|8
argument|* inC / inA)) + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA);           else             outC = (inC * layA + (sqrt (inC / inA) * inA - inC) * (
literal|2
argument|* layC - layA)) + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA)
argument_list|)
empty_stmt|;
comment|/* Custom SVG 1.2:            *            * if Dc + Sc>= 1            *   f(Sc, Dc) = 1            * otherwise            *   f(Sc, Dc) = Dc + Sc            */
name|BLEND
argument_list|(
argument|GIMP_ADDITION_MODE
argument_list|,
argument|if (layC * inA + inC * layA>= layA * inA)             outC = layA * inA + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA);           else             outC = inC + layC
argument_list|)
empty_stmt|;
comment|/* Custom SVG 1.2:            *            * if Dc - Sc<= 0            *   f(Sc, Dc) = 0            * otherwise            *   f(Sc, Dc) = Dc - Sc            */
name|BLEND
argument_list|(
argument|GIMP_SUBTRACT_MODE
argument_list|,
argument|if (inC * layA - layC * inA<=
literal|0
argument|)             outC = layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA);           else             outC = inC + layC -
literal|2
argument|* layC * inA
argument_list|)
empty_stmt|;
comment|/* Custom SVG 1.2:            *            * if Dc - Sc + 0.5>= 1            *   f(Sc, Dc) = 1            * otherwise if Dc - Sc + 0.5<= 0            *   f(Sc, Dc) = 0            * otherwise            *   f(Sc, Dc) = f(Sc, Dc) = Dc - Sc + 0.5            */
name|BLEND
argument_list|(
argument|GIMP_GRAIN_EXTRACT_MODE
argument_list|,
argument|if (inC * layA - layC * inA +
literal|0.5
argument|* layA * inA>= layA * inA)             outC = layA * inA + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA);           else if (inC * layA - layC * inA +
literal|0.5
argument|* layA * inA<=
literal|0
argument|)             outC = layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA);           else             outC = inC + layC -
literal|2
argument|* layC * inA +
literal|0.5
argument|* inA * layA
argument_list|)
empty_stmt|;
comment|/* Custom SVG 1.2:            *            * if Dc + Sc - 0.5>= 1            *   f(Sc, Dc) = 1            * otherwise if Dc + Sc - 0.5<= 0            *   f(Sc, Dc) = 0            * otherwise            *   f(Sc, Dc) = f(Sc, Dc) = Dc + Sc - 0.5            */
name|BLEND
argument_list|(
argument|GIMP_GRAIN_MERGE_MODE
argument_list|,
argument|if (inC * layA + layC * inA -
literal|0.5
argument|* layA * inA>= layA * inA)             outC = layA * inA + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA);           else if (inC * layA + layC * inA -
literal|0.5
argument|* layA * inA<=
literal|0
argument|)             outC = layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA);           else             outC = inC + layC -
literal|0.5
argument|* inA * layA
argument_list|)
empty_stmt|;
comment|/* Custom SVG 1.2:            *            * if Dc / Sc> 1            *   f(Sc, Dc) = 1            * otherwise            *   f(Sc, Dc) = Dc / Sc            */
name|BLEND
argument_list|(
argument|GIMP_DIVIDE_MODE
argument_list|,
argument|if (in[c] / lay[c]> in[A] / lay[A])             outC = layA * inA + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA);           else             outC = inC * layA * layA / layC + layC * (
literal|1
argument|- inA) + inC * (
literal|1
argument|- layA)
argument_list|)
empty_stmt|;
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
comment|/* TODO */
break|break;
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
comment|/* Icky eraser and paint modes */
break|break;
case|case
name|GIMP_DISSOLVE_MODE
case|:
comment|/* Not a point filter and cannot be implemented here */
comment|/* g_assert_not_reached (); */
break|break;
default|default:
name|g_error
argument_list|(
literal|"Unknown layer mode"
argument_list|)
expr_stmt|;
break|break;
block|}
comment|/* Alpha is treated the same */
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

