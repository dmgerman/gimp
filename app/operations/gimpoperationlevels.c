begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationlevels.c  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimplevelsconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationlevels.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_levels_process
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
name|out_buf
parameter_list|,
name|glong
name|samples
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationLevels,gimp_operation_levels,GIMP_TYPE_OPERATION_POINT_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationLevels
argument_list|,
argument|gimp_operation_levels
argument_list|,
argument|GIMP_TYPE_OPERATION_POINT_FILTER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_levels_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_levels_class_init
parameter_list|(
name|GimpOperationLevelsClass
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
name|GeglOperationPointFilterClass
modifier|*
name|point_class
init|=
name|GEGL_OPERATION_POINT_FILTER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_operation_point_filter_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_point_filter_get_property
expr_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:levels"
argument_list|,
literal|"categories"
argument_list|,
literal|"color"
argument_list|,
literal|"description"
argument_list|,
name|_
argument_list|(
literal|"Adjust color levels"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_levels_process
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_OPERATION_POINT_FILTER_PROP_TRC
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"trc"
argument_list|,
literal|"Linear/Percptual"
argument_list|,
literal|"What TRC to operate on"
argument_list|,
name|GIMP_TYPE_TRC_TYPE
argument_list|,
name|GIMP_TRC_NON_LINEAR
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_OPERATION_POINT_FILTER_PROP_CONFIG
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"config"
argument_list|,
literal|"Config"
argument_list|,
literal|"The config object"
argument_list|,
name|GIMP_TYPE_LEVELS_CONFIG
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_levels_init (GimpOperationLevels * self)
name|gimp_operation_levels_init
parameter_list|(
name|GimpOperationLevels
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
specifier|inline
name|gdouble
DECL|function|gimp_operation_levels_map (gdouble value,gdouble low_input,gdouble high_input,gboolean clamp_input,gdouble inv_gamma,gdouble low_output,gdouble high_output,gboolean clamp_output)
name|gimp_operation_levels_map
parameter_list|(
name|gdouble
name|value
parameter_list|,
name|gdouble
name|low_input
parameter_list|,
name|gdouble
name|high_input
parameter_list|,
name|gboolean
name|clamp_input
parameter_list|,
name|gdouble
name|inv_gamma
parameter_list|,
name|gdouble
name|low_output
parameter_list|,
name|gdouble
name|high_output
parameter_list|,
name|gboolean
name|clamp_output
parameter_list|)
block|{
comment|/*  determine input intensity  */
if|if
condition|(
name|high_input
operator|!=
name|low_input
condition|)
name|value
operator|=
operator|(
name|value
operator|-
name|low_input
operator|)
operator|/
operator|(
name|high_input
operator|-
name|low_input
operator|)
expr_stmt|;
else|else
name|value
operator|=
operator|(
name|value
operator|-
name|low_input
operator|)
expr_stmt|;
if|if
condition|(
name|clamp_input
condition|)
name|value
operator|=
name|CLAMP
argument_list|(
name|value
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|inv_gamma
operator|!=
literal|1.0
operator|&&
name|value
operator|>
literal|0
condition|)
name|value
operator|=
name|pow
argument_list|(
name|value
argument_list|,
name|inv_gamma
argument_list|)
expr_stmt|;
comment|/*  determine the output intensity  */
if|if
condition|(
name|high_output
operator|>=
name|low_output
condition|)
name|value
operator|=
name|value
operator|*
operator|(
name|high_output
operator|-
name|low_output
operator|)
operator|+
name|low_output
expr_stmt|;
elseif|else
if|if
condition|(
name|high_output
operator|<
name|low_output
condition|)
name|value
operator|=
name|low_output
operator|-
name|value
operator|*
operator|(
name|low_output
operator|-
name|high_output
operator|)
expr_stmt|;
if|if
condition|(
name|clamp_output
condition|)
name|value
operator|=
name|CLAMP
argument_list|(
name|value
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|value
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_levels_process (GeglOperation * operation,void * in_buf,void * out_buf,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_levels_process
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
name|out_buf
parameter_list|,
name|glong
name|samples
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|gint
name|level
parameter_list|)
block|{
name|GimpOperationPointFilter
modifier|*
name|point
init|=
name|GIMP_OPERATION_POINT_FILTER
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|GimpLevelsConfig
modifier|*
name|config
init|=
name|GIMP_LEVELS_CONFIG
argument_list|(
name|point
operator|->
name|config
argument_list|)
decl_stmt|;
name|gfloat
modifier|*
name|src
init|=
name|in_buf
decl_stmt|;
name|gfloat
modifier|*
name|dest
init|=
name|out_buf
decl_stmt|;
name|gfloat
name|inv_gamma
index|[
literal|5
index|]
decl_stmt|;
name|gint
name|channel
decl_stmt|;
if|if
condition|(
operator|!
name|config
condition|)
return|return
name|FALSE
return|;
for|for
control|(
name|channel
operator|=
literal|0
init|;
name|channel
operator|<
literal|5
condition|;
name|channel
operator|++
control|)
block|{
name|g_return_val_if_fail
argument_list|(
name|config
operator|->
name|gamma
index|[
name|channel
index|]
operator|!=
literal|0.0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|inv_gamma
index|[
name|channel
index|]
operator|=
literal|1.0
operator|/
name|config
operator|->
name|gamma
index|[
name|channel
index|]
expr_stmt|;
block|}
while|while
condition|(
name|samples
operator|--
condition|)
block|{
for|for
control|(
name|channel
operator|=
literal|0
init|;
name|channel
operator|<
literal|4
condition|;
name|channel
operator|++
control|)
block|{
name|gdouble
name|value
decl_stmt|;
name|value
operator|=
name|gimp_operation_levels_map
argument_list|(
name|src
index|[
name|channel
index|]
argument_list|,
name|config
operator|->
name|low_input
index|[
name|channel
operator|+
literal|1
index|]
argument_list|,
name|config
operator|->
name|high_input
index|[
name|channel
operator|+
literal|1
index|]
argument_list|,
name|config
operator|->
name|clamp_input
argument_list|,
name|inv_gamma
index|[
name|channel
operator|+
literal|1
index|]
argument_list|,
name|config
operator|->
name|low_output
index|[
name|channel
operator|+
literal|1
index|]
argument_list|,
name|config
operator|->
name|high_output
index|[
name|channel
operator|+
literal|1
index|]
argument_list|,
name|config
operator|->
name|clamp_output
argument_list|)
expr_stmt|;
comment|/* don't apply the overall curve to the alpha channel */
if|if
condition|(
name|channel
operator|!=
name|ALPHA
condition|)
name|value
operator|=
name|gimp_operation_levels_map
argument_list|(
name|value
argument_list|,
name|config
operator|->
name|low_input
index|[
literal|0
index|]
argument_list|,
name|config
operator|->
name|high_input
index|[
literal|0
index|]
argument_list|,
name|config
operator|->
name|clamp_input
argument_list|,
name|inv_gamma
index|[
literal|0
index|]
argument_list|,
name|config
operator|->
name|low_output
index|[
literal|0
index|]
argument_list|,
name|config
operator|->
name|high_output
index|[
literal|0
index|]
argument_list|,
name|config
operator|->
name|clamp_output
argument_list|)
expr_stmt|;
name|dest
index|[
name|channel
index|]
operator|=
name|value
expr_stmt|;
block|}
name|src
operator|+=
literal|4
expr_stmt|;
name|dest
operator|+=
literal|4
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gdouble
DECL|function|gimp_operation_levels_map_input (GimpLevelsConfig * config,GimpHistogramChannel channel,gdouble value)
name|gimp_operation_levels_map_input
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
name|gdouble
name|value
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LEVELS_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
comment|/*  determine input intensity  */
if|if
condition|(
name|config
operator|->
name|high_input
index|[
name|channel
index|]
operator|!=
name|config
operator|->
name|low_input
index|[
name|channel
index|]
condition|)
name|value
operator|=
operator|(
operator|(
name|value
operator|-
name|config
operator|->
name|low_input
index|[
name|channel
index|]
operator|)
operator|/
operator|(
name|config
operator|->
name|high_input
index|[
name|channel
index|]
operator|-
name|config
operator|->
name|low_input
index|[
name|channel
index|]
operator|)
operator|)
expr_stmt|;
else|else
name|value
operator|=
operator|(
name|value
operator|-
name|config
operator|->
name|low_input
index|[
name|channel
index|]
operator|)
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|gamma
index|[
name|channel
index|]
operator|!=
literal|0.0
operator|&&
name|value
operator|>
literal|0.0
condition|)
name|value
operator|=
name|pow
argument_list|(
name|value
argument_list|,
literal|1.0
operator|/
name|config
operator|->
name|gamma
index|[
name|channel
index|]
argument_list|)
expr_stmt|;
return|return
name|value
return|;
block|}
end_function

end_unit

