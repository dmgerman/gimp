begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationmaskcomponents.c  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationmaskcomponents.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2ba943040103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_MASK
name|PROP_MASK
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_operation_mask_components_get_property
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
name|gimp_operation_mask_components_set_property
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
name|gimp_operation_mask_components_prepare
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
name|gimp_operation_mask_components_parent_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|GeglOperationContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|output_prop
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|result
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_mask_components_process
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
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationMaskComponents,gimp_operation_mask_components,GEGL_TYPE_OPERATION_POINT_COMPOSER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationMaskComponents
argument_list|,
argument|gimp_operation_mask_components
argument_list|,
argument|GEGL_TYPE_OPERATION_POINT_COMPOSER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_mask_components_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_mask_components_class_init
parameter_list|(
name|GimpOperationMaskComponentsClass
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
name|gimp_operation_mask_components_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_operation_mask_components_get_property
expr_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:mask-components"
argument_list|,
literal|"categories"
argument_list|,
literal|"gimp"
argument_list|,
literal|"description"
argument_list|,
literal|"Selectively pick components from src or aux"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|operation_class
operator|->
name|prepare
operator|=
name|gimp_operation_mask_components_prepare
expr_stmt|;
name|operation_class
operator|->
name|process
operator|=
name|gimp_operation_mask_components_parent_process
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_mask_components_process
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_MASK
argument_list|,
name|g_param_spec_flags
argument_list|(
literal|"mask"
argument_list|,
literal|"Mask"
argument_list|,
literal|"The component mask"
argument_list|,
name|GIMP_TYPE_COMPONENT_MASK
argument_list|,
name|GIMP_COMPONENT_MASK_ALL
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
DECL|function|gimp_operation_mask_components_init (GimpOperationMaskComponents * self)
name|gimp_operation_mask_components_init
parameter_list|(
name|GimpOperationMaskComponents
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_mask_components_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_operation_mask_components_get_property
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
name|GimpOperationMaskComponents
modifier|*
name|self
init|=
name|GIMP_OPERATION_MASK_COMPONENTS
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
name|PROP_MASK
case|:
name|g_value_set_flags
argument_list|(
name|value
argument_list|,
name|self
operator|->
name|mask
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
DECL|function|gimp_operation_mask_components_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_operation_mask_components_set_property
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
name|GimpOperationMaskComponents
modifier|*
name|self
init|=
name|GIMP_OPERATION_MASK_COMPONENTS
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
name|PROP_MASK
case|:
name|self
operator|->
name|mask
operator|=
name|g_value_get_flags
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
DECL|function|gimp_operation_mask_components_prepare (GeglOperation * operation)
name|gimp_operation_mask_components_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
block|{
specifier|const
name|Babl
modifier|*
name|format
init|=
name|gegl_operation_get_source_format
argument_list|(
name|operation
argument_list|,
literal|"input"
argument_list|)
decl_stmt|;
if|if
condition|(
name|format
condition|)
block|{
specifier|const
name|Babl
modifier|*
name|model
init|=
name|babl_format_get_model
argument_list|(
name|format
argument_list|)
decl_stmt|;
if|if
condition|(
name|model
operator|==
name|babl_model
argument_list|(
literal|"R'G'B'A"
argument_list|)
condition|)
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
expr_stmt|;
else|else
name|format
operator|=
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|format
operator|=
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
expr_stmt|;
block|}
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
literal|"aux"
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
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_mask_components_parent_process (GeglOperation * operation,GeglOperationContext * context,const gchar * output_prop,const GeglRectangle * result,gint level)
name|gimp_operation_mask_components_parent_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|GeglOperationContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|output_prop
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|result
parameter_list|,
name|gint
name|level
parameter_list|)
block|{
name|GimpOperationMaskComponents
modifier|*
name|self
init|=
name|GIMP_OPERATION_MASK_COMPONENTS
argument_list|(
name|operation
argument_list|)
decl_stmt|;
if|if
condition|(
name|self
operator|->
name|mask
operator|==
literal|0
condition|)
block|{
name|GObject
modifier|*
name|input
init|=
name|gegl_operation_context_get_object
argument_list|(
name|context
argument_list|,
literal|"input"
argument_list|)
decl_stmt|;
name|gegl_operation_context_set_object
argument_list|(
name|context
argument_list|,
literal|"output"
argument_list|,
name|input
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
elseif|else
if|if
condition|(
name|self
operator|->
name|mask
operator|==
name|GIMP_COMPONENT_MASK_ALL
condition|)
block|{
name|GObject
modifier|*
name|aux
init|=
name|gegl_operation_context_get_object
argument_list|(
name|context
argument_list|,
literal|"aux"
argument_list|)
decl_stmt|;
name|gegl_operation_context_set_object
argument_list|(
name|context
argument_list|,
literal|"output"
argument_list|,
name|aux
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|GEGL_OPERATION_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|process
argument_list|(
name|operation
argument_list|,
name|context
argument_list|,
name|output_prop
argument_list|,
name|result
argument_list|,
name|level
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_mask_components_process (GeglOperation * operation,void * in_buf,void * aux_buf,void * out_buf,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_mask_components_process
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
parameter_list|,
name|gint
name|level
parameter_list|)
block|{
name|GimpOperationMaskComponents
modifier|*
name|self
init|=
name|GIMP_OPERATION_MASK_COMPONENTS
argument_list|(
name|operation
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
name|aux
init|=
name|aux_buf
decl_stmt|;
name|gfloat
modifier|*
name|dest
init|=
name|out_buf
decl_stmt|;
name|GimpComponentMask
name|mask
init|=
name|self
operator|->
name|mask
decl_stmt|;
specifier|static
specifier|const
name|gfloat
name|nothing
index|[]
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
if|if
condition|(
operator|!
name|aux
condition|)
name|aux
operator|=
operator|(
name|gfloat
operator|*
operator|)
name|nothing
expr_stmt|;
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|dest
index|[
name|RED
index|]
operator|=
operator|(
name|mask
operator|&
name|GIMP_COMPONENT_MASK_RED
operator|)
condition|?
name|aux
index|[
name|RED
index|]
else|:
name|src
index|[
name|RED
index|]
expr_stmt|;
name|dest
index|[
name|GREEN
index|]
operator|=
operator|(
name|mask
operator|&
name|GIMP_COMPONENT_MASK_GREEN
operator|)
condition|?
name|aux
index|[
name|GREEN
index|]
else|:
name|src
index|[
name|GREEN
index|]
expr_stmt|;
name|dest
index|[
name|BLUE
index|]
operator|=
operator|(
name|mask
operator|&
name|GIMP_COMPONENT_MASK_BLUE
operator|)
condition|?
name|aux
index|[
name|BLUE
index|]
else|:
name|src
index|[
name|BLUE
index|]
expr_stmt|;
name|dest
index|[
name|ALPHA
index|]
operator|=
operator|(
name|mask
operator|&
name|GIMP_COMPONENT_MASK_ALPHA
operator|)
condition|?
name|aux
index|[
name|ALPHA
index|]
else|:
name|src
index|[
name|ALPHA
index|]
expr_stmt|;
name|src
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|aux_buf
condition|)
name|aux
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

end_unit

