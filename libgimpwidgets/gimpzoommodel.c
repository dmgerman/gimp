begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpzoommodel.c  * Copyright (C) 2005  David Odin<dindinx@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimpzoommodel.h"
end_include

begin_define
DECL|macro|ZOOM_MIN
define|#
directive|define
name|ZOOM_MIN
value|(1.0 / 256.0)
end_define

begin_define
DECL|macro|ZOOM_MAX
define|#
directive|define
name|ZOOM_MAX
value|(256.0)
end_define

begin_enum
enum|enum
DECL|enum|__anon2bc2f8c70103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_VALUE
name|PROP_VALUE
block|,
DECL|enumerator|PROP_MINIMUM
name|PROP_MINIMUM
block|,
DECL|enumerator|PROP_MAXIMUM
name|PROP_MAXIMUM
block|,
DECL|enumerator|PROP_FRACTION
name|PROP_FRACTION
block|,
DECL|enumerator|PROP_PERCENTAGE
name|PROP_PERCENTAGE
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpZoomModelPrivate
typedef|typedef
name|struct
name|_GimpZoomModelPrivate
name|GimpZoomModelPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpZoomModelPrivate
struct|struct
name|_GimpZoomModelPrivate
block|{
DECL|member|value
name|gdouble
name|value
decl_stmt|;
DECL|member|minimum
name|gdouble
name|minimum
decl_stmt|;
DECL|member|maximum
name|gdouble
name|maximum
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_ZOOM_MODEL_GET_PRIVATE (obj)
define|#
directive|define
name|GIMP_ZOOM_MODEL_GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_PRIVATE ((obj), GIMP_TYPE_ZOOM_MODEL, GimpZoomModelPrivate))
end_define

begin_function_decl
specifier|static
name|void
name|gimp_zoom_model_set_property
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
name|gimp_zoom_model_get_property
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

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpZoomModel
argument_list|,
name|gimp_zoom_model
argument_list|,
name|G_TYPE_OBJECT
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_zoom_model_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_zoom_model_class_init (GimpZoomModelClass * klass)
name|gimp_zoom_model_class_init
parameter_list|(
name|GimpZoomModelClass
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_zoom_model_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_zoom_model_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_VALUE
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"value"
argument_list|,
literal|"Zoom factor"
argument_list|,
name|NULL
argument_list|,
name|ZOOM_MIN
argument_list|,
name|ZOOM_MAX
argument_list|,
literal|1.0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_MINIMUM
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"minimum"
argument_list|,
literal|"Lower limit for the zoom factor"
argument_list|,
name|NULL
argument_list|,
name|ZOOM_MIN
argument_list|,
name|ZOOM_MAX
argument_list|,
name|ZOOM_MIN
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_MAXIMUM
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"maximum"
argument_list|,
literal|"Upper limit for the zoom factor"
argument_list|,
name|NULL
argument_list|,
name|ZOOM_MIN
argument_list|,
name|ZOOM_MAX
argument_list|,
name|ZOOM_MAX
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_FRACTION
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"fraction"
argument_list|,
literal|"The zoom factor expressed as a fraction"
argument_list|,
name|NULL
argument_list|,
literal|"1:1"
argument_list|,
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PERCENTAGE
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"percentage"
argument_list|,
literal|"The zoom factor expressed as a percentage"
argument_list|,
name|NULL
argument_list|,
literal|"100%"
argument_list|,
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpZoomModelPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_zoom_model_init (GimpZoomModel * model)
name|gimp_zoom_model_init
parameter_list|(
name|GimpZoomModel
modifier|*
name|model
parameter_list|)
block|{
name|GimpZoomModelPrivate
modifier|*
name|priv
init|=
name|GIMP_ZOOM_MODEL_GET_PRIVATE
argument_list|(
name|model
argument_list|)
decl_stmt|;
name|priv
operator|->
name|value
operator|=
literal|1.0
expr_stmt|;
name|priv
operator|->
name|minimum
operator|=
name|ZOOM_MIN
expr_stmt|;
name|priv
operator|->
name|maximum
operator|=
name|ZOOM_MAX
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_zoom_model_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_zoom_model_set_property
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
name|GimpZoomModelPrivate
modifier|*
name|priv
init|=
name|GIMP_ZOOM_MODEL_GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_object_freeze_notify
argument_list|(
name|object
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_VALUE
case|:
name|priv
operator|->
name|value
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"fraction"
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"percentage"
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MINIMUM
case|:
name|priv
operator|->
name|minimum
operator|=
name|MIN
argument_list|(
name|g_value_get_double
argument_list|(
name|value
argument_list|)
argument_list|,
name|priv
operator|->
name|maximum
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MAXIMUM
case|:
name|priv
operator|->
name|maximum
operator|=
name|MAX
argument_list|(
name|g_value_get_double
argument_list|(
name|value
argument_list|)
argument_list|,
name|priv
operator|->
name|minimum
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
if|if
condition|(
name|priv
operator|->
name|value
operator|>
name|priv
operator|->
name|maximum
operator|||
name|priv
operator|->
name|value
operator|<
name|priv
operator|->
name|minimum
condition|)
block|{
name|priv
operator|->
name|value
operator|=
name|CLAMP
argument_list|(
name|priv
operator|->
name|value
argument_list|,
name|priv
operator|->
name|minimum
argument_list|,
name|priv
operator|->
name|maximum
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"value"
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"fraction"
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"percentage"
argument_list|)
expr_stmt|;
block|}
name|g_object_thaw_notify
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_zoom_model_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_zoom_model_get_property
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
name|GimpZoomModelPrivate
modifier|*
name|priv
init|=
name|GIMP_ZOOM_MODEL_GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|tmp
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_VALUE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MINIMUM
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|minimum
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MAXIMUM
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|maximum
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FRACTION
case|:
block|{
name|gint
name|numerator
decl_stmt|;
name|gint
name|denominator
decl_stmt|;
name|gimp_zoom_model_get_fraction
argument_list|(
name|GIMP_ZOOM_MODEL
argument_list|(
name|object
argument_list|)
argument_list|,
operator|&
name|numerator
argument_list|,
operator|&
name|denominator
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d:%d"
argument_list|,
name|numerator
argument_list|,
name|denominator
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|PROP_PERCENTAGE
case|:
name|tmp
operator|=
name|g_strdup_printf
argument_list|(
name|priv
operator|->
name|value
operator|>=
literal|0.15
condition|?
literal|"%.0f%%"
else|:
literal|"%.2f%%"
argument_list|,
name|priv
operator|->
name|value
operator|*
literal|100.0
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
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
DECL|function|gimp_zoom_model_zoom_in (GimpZoomModel * model)
name|gimp_zoom_model_zoom_in
parameter_list|(
name|GimpZoomModel
modifier|*
name|model
parameter_list|)
block|{
name|GimpZoomModelPrivate
modifier|*
name|priv
init|=
name|GIMP_ZOOM_MODEL_GET_PRIVATE
argument_list|(
name|model
argument_list|)
decl_stmt|;
if|if
condition|(
name|priv
operator|->
name|value
operator|<
name|priv
operator|->
name|maximum
condition|)
name|gimp_zoom_model_zoom
argument_list|(
name|model
argument_list|,
name|GIMP_ZOOM_IN
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_zoom_model_zoom_out (GimpZoomModel * model)
name|gimp_zoom_model_zoom_out
parameter_list|(
name|GimpZoomModel
modifier|*
name|model
parameter_list|)
block|{
name|GimpZoomModelPrivate
modifier|*
name|priv
init|=
name|GIMP_ZOOM_MODEL_GET_PRIVATE
argument_list|(
name|model
argument_list|)
decl_stmt|;
if|if
condition|(
name|priv
operator|->
name|value
operator|>
name|priv
operator|->
name|minimum
condition|)
name|gimp_zoom_model_zoom
argument_list|(
name|model
argument_list|,
name|GIMP_ZOOM_OUT
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_zoom_model_new:  *  * Creates a new #GimpZoomModel.  *  * Return value: a new #GimpZoomModel.  *  * Since GIMP 2.4  **/
end_comment

begin_function
name|GimpZoomModel
modifier|*
DECL|function|gimp_zoom_model_new (void)
name|gimp_zoom_model_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_ZOOM_MODEL
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_zoom_model_set_range:  * @model: a #GimpZoomModel  * @min: new lower limit for zoom factor  * @max: new upper limit for zoom factor  *  * Sets the allowed range of the @model.  *  * Since GIMP 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_zoom_model_set_range (GimpZoomModel * model,gdouble min,gdouble max)
name|gimp_zoom_model_set_range
parameter_list|(
name|GimpZoomModel
modifier|*
name|model
parameter_list|,
name|gdouble
name|min
parameter_list|,
name|gdouble
name|max
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ZOOM_MODEL
argument_list|(
name|model
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|min
operator|<
name|max
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|min
operator|>=
name|ZOOM_MIN
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|max
operator|<=
name|ZOOM_MAX
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|model
argument_list|,
literal|"minimum"
argument_list|,
name|min
argument_list|,
literal|"maximum"
argument_list|,
name|max
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_zoom_model_zoom:  * @model:     a #GimpZoomModel  * @zoom_type: the #GimpZoomType  * @scale:     ignored unless @zoom_type == %GIMP_ZOOM_TO  *  * Since GIMP 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_zoom_model_zoom (GimpZoomModel * model,GimpZoomType zoom_type,gdouble scale)
name|gimp_zoom_model_zoom
parameter_list|(
name|GimpZoomModel
modifier|*
name|model
parameter_list|,
name|GimpZoomType
name|zoom_type
parameter_list|,
name|gdouble
name|scale
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ZOOM_MODEL
argument_list|(
name|model
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|zoom_type
operator|!=
name|GIMP_ZOOM_TO
condition|)
name|scale
operator|=
name|gimp_zoom_model_get_factor
argument_list|(
name|model
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|model
argument_list|,
literal|"value"
argument_list|,
name|gimp_zoom_model_zoom_step
argument_list|(
name|zoom_type
argument_list|,
name|scale
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_zoom_model_get_factor:  * @model: a #GimpZoomModel  *  * Retrieves the current zoom factor of @model.  *  * Return value: the current scale factor  *  * Since GIMP 2.4  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_zoom_model_get_factor (GimpZoomModel * model)
name|gimp_zoom_model_get_factor
parameter_list|(
name|GimpZoomModel
modifier|*
name|model
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ZOOM_MODEL
argument_list|(
name|model
argument_list|)
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|GIMP_ZOOM_MODEL_GET_PRIVATE
argument_list|(
name|model
argument_list|)
operator|->
name|value
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_zoom_model_get_fraction  * @model:       a #GimpZoomModel  * @numerator:   return location for numerator  * @denominator: return location for denominator  *  * Retrieves the current zoom factor of @model as a fraction.  *  * Since GIMP 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_zoom_model_get_fraction (GimpZoomModel * model,gint * numerator,gint * denominator)
name|gimp_zoom_model_get_fraction
parameter_list|(
name|GimpZoomModel
modifier|*
name|model
parameter_list|,
name|gint
modifier|*
name|numerator
parameter_list|,
name|gint
modifier|*
name|denominator
parameter_list|)
block|{
name|gint
name|p0
decl_stmt|,
name|p1
decl_stmt|,
name|p2
decl_stmt|;
name|gint
name|q0
decl_stmt|,
name|q1
decl_stmt|,
name|q2
decl_stmt|;
name|gdouble
name|zoom_factor
decl_stmt|;
name|gdouble
name|remainder
decl_stmt|,
name|next_cf
decl_stmt|;
name|gboolean
name|swapped
init|=
name|FALSE
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ZOOM_MODEL
argument_list|(
name|model
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|numerator
operator|!=
name|NULL
operator|&&
name|denominator
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|zoom_factor
operator|=
name|gimp_zoom_model_get_factor
argument_list|(
name|model
argument_list|)
expr_stmt|;
comment|/* make sure that zooming behaves symmetrically */
if|if
condition|(
name|zoom_factor
operator|<
literal|1.0
condition|)
block|{
name|zoom_factor
operator|=
literal|1.0
operator|/
name|zoom_factor
expr_stmt|;
name|swapped
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/* calculate the continued fraction for the desired zoom factor */
name|p0
operator|=
literal|1
expr_stmt|;
name|q0
operator|=
literal|0
expr_stmt|;
name|p1
operator|=
name|floor
argument_list|(
name|zoom_factor
argument_list|)
expr_stmt|;
name|q1
operator|=
literal|1
expr_stmt|;
name|remainder
operator|=
name|zoom_factor
operator|-
name|p1
expr_stmt|;
while|while
condition|(
name|fabs
argument_list|(
name|remainder
argument_list|)
operator|>=
literal|0.0001
operator|&&
name|fabs
argument_list|(
operator|(
operator|(
name|gdouble
operator|)
name|p1
operator|/
name|q1
operator|)
operator|-
name|zoom_factor
argument_list|)
operator|>
literal|0.0001
condition|)
block|{
name|remainder
operator|=
literal|1.0
operator|/
name|remainder
expr_stmt|;
name|next_cf
operator|=
name|floor
argument_list|(
name|remainder
argument_list|)
expr_stmt|;
name|p2
operator|=
name|next_cf
operator|*
name|p1
operator|+
name|p0
expr_stmt|;
name|q2
operator|=
name|next_cf
operator|*
name|q1
operator|+
name|q0
expr_stmt|;
comment|/* Numerator and Denominator are limited by 256 */
comment|/* also absurd ratios like 170:171 are excluded */
if|if
condition|(
name|p2
operator|>
literal|256
operator|||
name|q2
operator|>
literal|256
operator|||
operator|(
name|p2
operator|>
literal|1
operator|&&
name|q2
operator|>
literal|1
operator|&&
name|p2
operator|*
name|q2
operator|>
literal|200
operator|)
condition|)
break|break;
comment|/* remember the last two fractions */
name|p0
operator|=
name|p1
expr_stmt|;
name|p1
operator|=
name|p2
expr_stmt|;
name|q0
operator|=
name|q1
expr_stmt|;
name|q1
operator|=
name|q2
expr_stmt|;
name|remainder
operator|=
name|remainder
operator|-
name|next_cf
expr_stmt|;
block|}
name|zoom_factor
operator|=
operator|(
name|gdouble
operator|)
name|p1
operator|/
name|q1
expr_stmt|;
comment|/* hard upper and lower bounds for zoom ratio */
if|if
condition|(
name|zoom_factor
operator|>
literal|256.0
condition|)
block|{
name|p1
operator|=
literal|256
expr_stmt|;
name|q1
operator|=
literal|1
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|zoom_factor
operator|<
literal|1.0
operator|/
literal|256.0
condition|)
block|{
name|p1
operator|=
literal|1
expr_stmt|;
name|q1
operator|=
literal|256
expr_stmt|;
block|}
if|if
condition|(
name|swapped
condition|)
block|{
operator|*
name|numerator
operator|=
name|q1
expr_stmt|;
operator|*
name|denominator
operator|=
name|p1
expr_stmt|;
block|}
else|else
block|{
operator|*
name|numerator
operator|=
name|p1
expr_stmt|;
operator|*
name|denominator
operator|=
name|q1
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|zoom_button_new (const gchar * stock_id,GtkIconSize icon_size)
name|zoom_button_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
name|GtkIconSize
name|icon_size
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
if|if
condition|(
name|icon_size
operator|>
literal|0
condition|)
block|{
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|stock_id
argument_list|,
name|icon_size
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|button
operator|=
name|gtk_button_new_from_stock
argument_list|(
name|stock_id
argument_list|)
expr_stmt|;
block|}
return|return
name|button
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_zoom_button_new:  * @model:     a #GimpZoomModel  * @zoom_type:  * @icon_size: use 0 for a button with text labels  *  * Return value: a newly created GtkButton  *  * Since GIMP 2.4  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_zoom_button_new (GimpZoomModel * model,GimpZoomType zoom_type,GtkIconSize icon_size)
name|gimp_zoom_button_new
parameter_list|(
name|GimpZoomModel
modifier|*
name|model
parameter_list|,
name|GimpZoomType
name|zoom_type
parameter_list|,
name|GtkIconSize
name|icon_size
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ZOOM_MODEL
argument_list|(
name|model
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|zoom_type
condition|)
block|{
case|case
name|GIMP_ZOOM_IN
case|:
name|button
operator|=
name|zoom_button_new
argument_list|(
name|GTK_STOCK_ZOOM_IN
argument_list|,
name|icon_size
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_zoom_model_zoom_in
argument_list|)
argument_list|,
name|model
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ZOOM_OUT
case|:
name|button
operator|=
name|zoom_button_new
argument_list|(
name|GTK_STOCK_ZOOM_OUT
argument_list|,
name|icon_size
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_zoom_model_zoom_out
argument_list|)
argument_list|,
name|model
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"sorry, no button for this zoom type (%d)"
argument_list|,
name|zoom_type
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|button
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_zoom_model_zoom_step:  * @zoom_type:  * @scale:     ignored unless @zoom_type == %GIMP_ZOOM_TO  *  * Utility function to calculate a new scale factor.  *  * Return value: the new scale factor  *  * Since GIMP 2.4  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_zoom_model_zoom_step (GimpZoomType zoom_type,gdouble scale)
name|gimp_zoom_model_zoom_step
parameter_list|(
name|GimpZoomType
name|zoom_type
parameter_list|,
name|gdouble
name|scale
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|n_presets
decl_stmt|;
name|gdouble
name|new_scale
init|=
literal|1.0
decl_stmt|;
comment|/* This table is constructed to have fractions, that approximate    * sqrt(2)^k. This gives a smooth feeling regardless of the starting    * zoom level.    *    * Zooming in/out always jumps to a zoom step from the list below.    * However, we try to guarantee a certain size of the step, to    * avoid silly jumps from 101% to 100%.    *    * The factor 1.1 is chosen a bit arbitrary, but feels better    * than the geometric median of the zoom steps (2^(1/4)).    */
DECL|macro|ZOOM_MIN_STEP
define|#
directive|define
name|ZOOM_MIN_STEP
value|1.1
name|gdouble
name|presets
index|[]
init|=
block|{
literal|1.0
operator|/
literal|256
block|,
literal|1.0
operator|/
literal|180
block|,
literal|1.0
operator|/
literal|128
block|,
literal|1.0
operator|/
literal|90
block|,
literal|1.0
operator|/
literal|64
block|,
literal|1.0
operator|/
literal|45
block|,
literal|1.0
operator|/
literal|32
block|,
literal|1.0
operator|/
literal|23
block|,
literal|1.0
operator|/
literal|16
block|,
literal|1.0
operator|/
literal|11
block|,
literal|1.0
operator|/
literal|8
block|,
literal|2.0
operator|/
literal|11
block|,
literal|1.0
operator|/
literal|4
block|,
literal|1.0
operator|/
literal|3
block|,
literal|1.0
operator|/
literal|2
block|,
literal|2.0
operator|/
literal|3
block|,
literal|1.0
block|,
literal|3.0
operator|/
literal|2
block|,
literal|2.0
block|,
literal|3.0
block|,
literal|4.0
block|,
literal|11.0
operator|/
literal|2
block|,
literal|8.0
block|,
literal|11.0
block|,
literal|16.0
block|,
literal|23.0
block|,
literal|32.0
block|,
literal|45.0
block|,
literal|64.0
block|,
literal|90.0
block|,
literal|128.0
block|,
literal|180.0
block|,
literal|256.0
block|,   }
decl_stmt|;
name|n_presets
operator|=
name|G_N_ELEMENTS
argument_list|(
name|presets
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|zoom_type
condition|)
block|{
case|case
name|GIMP_ZOOM_IN
case|:
name|scale
operator|*=
name|ZOOM_MIN_STEP
expr_stmt|;
name|new_scale
operator|=
name|presets
index|[
name|n_presets
operator|-
literal|1
index|]
expr_stmt|;
for|for
control|(
name|i
operator|=
name|n_presets
operator|-
literal|1
init|;
name|i
operator|>=
literal|0
operator|&&
name|presets
index|[
name|i
index|]
operator|>
name|scale
condition|;
name|i
operator|--
control|)
name|new_scale
operator|=
name|presets
index|[
name|i
index|]
expr_stmt|;
break|break;
case|case
name|GIMP_ZOOM_OUT
case|:
name|scale
operator|/=
name|ZOOM_MIN_STEP
expr_stmt|;
name|new_scale
operator|=
name|presets
index|[
literal|0
index|]
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_presets
operator|&&
name|presets
index|[
name|i
index|]
operator|<
name|scale
condition|;
name|i
operator|++
control|)
name|new_scale
operator|=
name|presets
index|[
name|i
index|]
expr_stmt|;
break|break;
case|case
name|GIMP_ZOOM_IN_MORE
case|:
name|scale
operator|=
name|gimp_zoom_model_zoom_step
argument_list|(
name|GIMP_ZOOM_IN
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gimp_zoom_model_zoom_step
argument_list|(
name|GIMP_ZOOM_IN
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gimp_zoom_model_zoom_step
argument_list|(
name|GIMP_ZOOM_IN
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|new_scale
operator|=
name|scale
expr_stmt|;
break|break;
case|case
name|GIMP_ZOOM_OUT_MORE
case|:
name|scale
operator|=
name|gimp_zoom_model_zoom_step
argument_list|(
name|GIMP_ZOOM_OUT
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gimp_zoom_model_zoom_step
argument_list|(
name|GIMP_ZOOM_OUT
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gimp_zoom_model_zoom_step
argument_list|(
name|GIMP_ZOOM_OUT
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|new_scale
operator|=
name|scale
expr_stmt|;
break|break;
case|case
name|GIMP_ZOOM_IN_MAX
case|:
name|new_scale
operator|=
name|ZOOM_MAX
expr_stmt|;
break|break;
case|case
name|GIMP_ZOOM_OUT_MAX
case|:
name|new_scale
operator|=
name|ZOOM_MIN
expr_stmt|;
break|break;
case|case
name|GIMP_ZOOM_TO
case|:
name|new_scale
operator|=
name|scale
expr_stmt|;
break|break;
block|}
return|return
name|CLAMP
argument_list|(
name|new_scale
argument_list|,
name|ZOOM_MIN
argument_list|,
name|ZOOM_MAX
argument_list|)
return|;
undef|#
directive|undef
name|ZOOM_MIN_STEP
block|}
end_function

end_unit

