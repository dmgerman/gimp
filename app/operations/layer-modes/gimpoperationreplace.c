begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationreplace.c  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<gegl-plugin.h>
end_include

begin_include
include|#
directive|include
file|"../operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-layer-modes.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationreplace.h"
end_include

begin_function_decl
specifier|static
name|GeglRectangle
name|gimp_operation_replace_get_bounding_box
parameter_list|(
name|GeglOperation
modifier|*
name|op
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_replace_parent_process
parameter_list|(
name|GeglOperation
modifier|*
name|op
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
name|gimp_operation_replace_process
parameter_list|(
name|GeglOperation
modifier|*
name|op
parameter_list|,
name|void
modifier|*
name|in
parameter_list|,
name|void
modifier|*
name|layer
parameter_list|,
name|void
modifier|*
name|mask
parameter_list|,
name|void
modifier|*
name|out
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

begin_function_decl
specifier|static
name|GimpLayerCompositeRegion
name|gimp_operation_replace_get_affected_region
parameter_list|(
name|GimpOperationLayerMode
modifier|*
name|layer_mode
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationReplace,gimp_operation_replace,GIMP_TYPE_OPERATION_LAYER_MODE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationReplace
argument_list|,
argument|gimp_operation_replace
argument_list|,
argument|GIMP_TYPE_OPERATION_LAYER_MODE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_replace_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_replace_class_init
parameter_list|(
name|GimpOperationReplaceClass
modifier|*
name|klass
parameter_list|)
block|{
name|GeglOperationClass
modifier|*
name|operation_class
init|=
name|GEGL_OPERATION_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpOperationLayerModeClass
modifier|*
name|layer_mode_class
init|=
name|GIMP_OPERATION_LAYER_MODE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:replace"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP replace mode operation"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|operation_class
operator|->
name|get_bounding_box
operator|=
name|gimp_operation_replace_get_bounding_box
expr_stmt|;
name|operation_class
operator|->
name|process
operator|=
name|gimp_operation_replace_parent_process
expr_stmt|;
name|layer_mode_class
operator|->
name|process
operator|=
name|gimp_operation_replace_process
expr_stmt|;
name|layer_mode_class
operator|->
name|get_affected_region
operator|=
name|gimp_operation_replace_get_affected_region
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_replace_init (GimpOperationReplace * self)
name|gimp_operation_replace_init
parameter_list|(
name|GimpOperationReplace
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GeglRectangle
DECL|function|gimp_operation_replace_get_bounding_box (GeglOperation * op)
name|gimp_operation_replace_get_bounding_box
parameter_list|(
name|GeglOperation
modifier|*
name|op
parameter_list|)
block|{
name|GimpOperationLayerMode
modifier|*
name|self
init|=
operator|(
name|gpointer
operator|)
name|op
decl_stmt|;
name|GeglRectangle
modifier|*
name|in_rect
decl_stmt|;
name|GeglRectangle
modifier|*
name|aux_rect
decl_stmt|;
name|GeglRectangle
modifier|*
name|aux2_rect
decl_stmt|;
name|GeglRectangle
name|src_rect
init|=
block|{}
decl_stmt|;
name|GeglRectangle
name|dst_rect
init|=
block|{}
decl_stmt|;
name|GeglRectangle
name|result
decl_stmt|;
name|GimpLayerCompositeRegion
name|included_region
decl_stmt|;
name|in_rect
operator|=
name|gegl_operation_source_get_bounding_box
argument_list|(
name|op
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|aux_rect
operator|=
name|gegl_operation_source_get_bounding_box
argument_list|(
name|op
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
name|aux2_rect
operator|=
name|gegl_operation_source_get_bounding_box
argument_list|(
name|op
argument_list|,
literal|"aux2"
argument_list|)
expr_stmt|;
if|if
condition|(
name|in_rect
condition|)
name|dst_rect
operator|=
operator|*
name|in_rect
expr_stmt|;
if|if
condition|(
name|aux_rect
condition|)
block|{
name|src_rect
operator|=
operator|*
name|aux_rect
expr_stmt|;
if|if
condition|(
name|aux2_rect
condition|)
name|gegl_rectangle_intersect
argument_list|(
operator|&
name|src_rect
argument_list|,
operator|&
name|src_rect
argument_list|,
name|aux2_rect
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|self
operator|->
name|is_last_node
condition|)
block|{
name|included_region
operator|=
name|GIMP_LAYER_COMPOSITE_REGION_SOURCE
expr_stmt|;
block|}
else|else
block|{
name|included_region
operator|=
name|gimp_layer_mode_get_included_region
argument_list|(
name|self
operator|->
name|layer_mode
argument_list|,
name|self
operator|->
name|composite_mode
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|self
operator|->
name|opacity
operator|==
literal|0.0
condition|)
name|included_region
operator|&=
operator|~
name|GIMP_LAYER_COMPOSITE_REGION_SOURCE
expr_stmt|;
elseif|else
if|if
condition|(
name|self
operator|->
name|opacity
operator|==
literal|1.0
operator|&&
operator|!
name|aux2_rect
condition|)
name|included_region
operator|&=
operator|~
name|GIMP_LAYER_COMPOSITE_REGION_DESTINATION
expr_stmt|;
name|gegl_rectangle_intersect
argument_list|(
operator|&
name|result
argument_list|,
operator|&
name|src_rect
argument_list|,
operator|&
name|dst_rect
argument_list|)
expr_stmt|;
if|if
condition|(
name|included_region
operator|&
name|GIMP_LAYER_COMPOSITE_REGION_SOURCE
condition|)
name|gegl_rectangle_bounding_box
argument_list|(
operator|&
name|result
argument_list|,
operator|&
name|result
argument_list|,
operator|&
name|src_rect
argument_list|)
expr_stmt|;
if|if
condition|(
name|included_region
operator|&
name|GIMP_LAYER_COMPOSITE_REGION_DESTINATION
condition|)
name|gegl_rectangle_bounding_box
argument_list|(
operator|&
name|result
argument_list|,
operator|&
name|result
argument_list|,
operator|&
name|dst_rect
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_replace_parent_process (GeglOperation * op,GeglOperationContext * context,const gchar * output_prop,const GeglRectangle * result,gint level)
name|gimp_operation_replace_parent_process
parameter_list|(
name|GeglOperation
modifier|*
name|op
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
name|GimpOperationLayerMode
modifier|*
name|layer_mode
init|=
operator|(
name|gpointer
operator|)
name|op
decl_stmt|;
comment|/* if the layer's opacity is 100%, it has no mask, and its composite mode    * contains "aux" (the latter should always be the case in practice,    * currently,) we can just pass "aux" directly as output.    */
if|if
condition|(
name|layer_mode
operator|->
name|opacity
operator|==
literal|1.0
operator|&&
operator|!
name|gegl_operation_context_get_object
argument_list|(
name|context
argument_list|,
literal|"aux2"
argument_list|)
operator|&&
operator|(
name|gimp_layer_mode_get_included_region
argument_list|(
name|layer_mode
operator|->
name|layer_mode
argument_list|,
name|layer_mode
operator|->
name|real_composite_mode
argument_list|)
operator|&
name|GIMP_LAYER_COMPOSITE_REGION_SOURCE
operator|)
condition|)
block|{
name|GObject
modifier|*
name|aux
decl_stmt|;
name|aux
operator|=
name|gegl_operation_context_get_object
argument_list|(
name|context
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
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
comment|/* the opposite case, where the opacity is 0%, is handled by    * GimpOperationLayerMode.    */
return|return
name|GEGL_OPERATION_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|process
argument_list|(
name|op
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
DECL|function|gimp_operation_replace_process (GeglOperation * op,void * in_p,void * layer_p,void * mask_p,void * out_p,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_replace_process
parameter_list|(
name|GeglOperation
modifier|*
name|op
parameter_list|,
name|void
modifier|*
name|in_p
parameter_list|,
name|void
modifier|*
name|layer_p
parameter_list|,
name|void
modifier|*
name|mask_p
parameter_list|,
name|void
modifier|*
name|out_p
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
name|GimpOperationLayerMode
modifier|*
name|layer_mode
init|=
operator|(
name|gpointer
operator|)
name|op
decl_stmt|;
name|gfloat
modifier|*
name|in
init|=
name|in_p
decl_stmt|;
name|gfloat
modifier|*
name|out
init|=
name|out_p
decl_stmt|;
name|gfloat
modifier|*
name|layer
init|=
name|layer_p
decl_stmt|;
name|gfloat
modifier|*
name|mask
init|=
name|mask_p
decl_stmt|;
name|gfloat
name|opacity
init|=
name|layer_mode
operator|->
name|opacity
decl_stmt|;
specifier|const
name|gboolean
name|has_mask
init|=
name|mask
operator|!=
name|NULL
decl_stmt|;
switch|switch
condition|(
name|layer_mode
operator|->
name|real_composite_mode
condition|)
block|{
case|case
name|GIMP_LAYER_COMPOSITE_UNION
case|:
case|case
name|GIMP_LAYER_COMPOSITE_AUTO
case|:
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|opacity_value
init|=
name|opacity
decl_stmt|;
name|gfloat
name|new_alpha
decl_stmt|;
name|gfloat
name|ratio
decl_stmt|;
name|gint
name|b
decl_stmt|;
if|if
condition|(
name|has_mask
condition|)
name|opacity_value
operator|*=
operator|*
name|mask
expr_stmt|;
name|new_alpha
operator|=
operator|(
name|layer
index|[
name|ALPHA
index|]
operator|-
name|in
index|[
name|ALPHA
index|]
operator|)
operator|*
name|opacity_value
operator|+
name|in
index|[
name|ALPHA
index|]
expr_stmt|;
name|ratio
operator|=
name|opacity_value
expr_stmt|;
if|if
condition|(
name|new_alpha
condition|)
name|ratio
operator|*=
name|layer
index|[
name|ALPHA
index|]
operator|/
name|new_alpha
expr_stmt|;
for|for
control|(
name|b
operator|=
name|RED
init|;
name|b
operator|<
name|ALPHA
condition|;
name|b
operator|++
control|)
name|out
index|[
name|b
index|]
operator|=
operator|(
name|layer
index|[
name|b
index|]
operator|-
name|in
index|[
name|b
index|]
operator|)
operator|*
name|ratio
operator|+
name|in
index|[
name|b
index|]
expr_stmt|;
name|out
index|[
name|ALPHA
index|]
operator|=
name|new_alpha
expr_stmt|;
name|in
operator|+=
literal|4
expr_stmt|;
name|layer
operator|+=
literal|4
expr_stmt|;
name|out
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|has_mask
condition|)
name|mask
operator|++
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_LAYER_COMPOSITE_CLIP_TO_BACKDROP
case|:
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|opacity_value
init|=
name|opacity
decl_stmt|;
name|gfloat
name|new_alpha
decl_stmt|;
name|gint
name|b
decl_stmt|;
if|if
condition|(
name|has_mask
condition|)
name|opacity_value
operator|*=
operator|*
name|mask
expr_stmt|;
name|new_alpha
operator|=
name|in
index|[
name|ALPHA
index|]
operator|*
operator|(
literal|1.0f
operator|-
name|opacity_value
operator|)
expr_stmt|;
for|for
control|(
name|b
operator|=
name|RED
init|;
name|b
operator|<
name|ALPHA
condition|;
name|b
operator|++
control|)
name|out
index|[
name|b
index|]
operator|=
name|in
index|[
name|b
index|]
expr_stmt|;
name|out
index|[
name|ALPHA
index|]
operator|=
name|new_alpha
expr_stmt|;
name|in
operator|+=
literal|4
expr_stmt|;
name|out
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|has_mask
condition|)
name|mask
operator|++
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_LAYER_COMPOSITE_CLIP_TO_LAYER
case|:
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|opacity_value
init|=
name|opacity
decl_stmt|;
name|gfloat
name|new_alpha
decl_stmt|;
name|gint
name|b
decl_stmt|;
if|if
condition|(
name|has_mask
condition|)
name|opacity_value
operator|*=
operator|*
name|mask
expr_stmt|;
name|new_alpha
operator|=
name|layer
index|[
name|ALPHA
index|]
operator|*
name|opacity_value
expr_stmt|;
for|for
control|(
name|b
operator|=
name|RED
init|;
name|b
operator|<
name|ALPHA
condition|;
name|b
operator|++
control|)
name|out
index|[
name|b
index|]
operator|=
name|layer
index|[
name|b
index|]
expr_stmt|;
name|out
index|[
name|ALPHA
index|]
operator|=
name|new_alpha
expr_stmt|;
name|in
operator|+=
literal|4
expr_stmt|;
name|layer
operator|+=
literal|4
expr_stmt|;
name|out
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|has_mask
condition|)
name|mask
operator|++
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_LAYER_COMPOSITE_INTERSECTION
case|:
name|memset
argument_list|(
name|out
argument_list|,
literal|0
argument_list|,
literal|4
operator|*
name|samples
operator|*
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|GimpLayerCompositeRegion
DECL|function|gimp_operation_replace_get_affected_region (GimpOperationLayerMode * layer_mode)
name|gimp_operation_replace_get_affected_region
parameter_list|(
name|GimpOperationLayerMode
modifier|*
name|layer_mode
parameter_list|)
block|{
name|GimpLayerCompositeRegion
name|affected_region
init|=
name|GIMP_LAYER_COMPOSITE_REGION_INTERSECTION
decl_stmt|;
if|if
condition|(
name|layer_mode
operator|->
name|opacity
operator|!=
literal|0.0
condition|)
name|affected_region
operator||=
name|GIMP_LAYER_COMPOSITE_REGION_DESTINATION
expr_stmt|;
comment|/* if opacity != 1.0, or we have a mask, then we also affect SOURCE, but this    * is considered the case anyway, so no need for special handling.    */
return|return
name|affected_region
return|;
block|}
end_function

end_unit

