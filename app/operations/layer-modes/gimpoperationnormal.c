begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationnormalmode.c  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|<gegl-plugin.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"operations/operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationnormal.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_normal_parent_process
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

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationNormal
argument_list|,
argument|gimp_operation_normal
argument_list|,
argument|GIMP_TYPE_OPERATION_POINT_LAYER_MODE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_normal_parent_class
end_define

begin_decl_stmt
specifier|static
specifier|const
name|gchar
modifier|*
name|reference_xml
init|=
literal|"<?xml version='1.0' encoding='UTF-8'?>"
literal|"<gegl>"
literal|"<node operation='gimp:normal'>"
literal|"<node operation='gegl:load'>"
literal|"<params>"
literal|"<param name='path'>blending-test-B.png</param>"
literal|"</params>"
literal|"</node>"
literal|"</node>"
literal|"<node operation='gegl:load'>"
literal|"<params>"
literal|"<param name='path'>blending-test-A.png</param>"
literal|"</params>"
literal|"</node>"
literal|"</gegl>"
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_operation_normal_process
name|GimpLayerModeFunc
name|gimp_operation_normal_process
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_operation_normal_class_init (GimpOperationNormalClass * klass)
name|gimp_operation_normal_class_init
parameter_list|(
name|GimpOperationNormalClass
modifier|*
name|klass
parameter_list|)
block|{
name|GeglOperationClass
modifier|*
name|operation_class
decl_stmt|;
name|GeglOperationPointComposer3Class
modifier|*
name|point_class
decl_stmt|;
name|operation_class
operator|=
name|GEGL_OPERATION_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|point_class
operator|=
name|GEGL_OPERATION_POINT_COMPOSER3_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gegl_operation_class_set_keys
argument_list|(
name|operation_class
argument_list|,
literal|"name"
argument_list|,
literal|"gimp:normal"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP normal mode operation"
argument_list|,
literal|"reference-image"
argument_list|,
literal|"normal-mode.png"
argument_list|,
literal|"reference-composition"
argument_list|,
name|reference_xml
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|operation_class
operator|->
name|process
operator|=
name|gimp_operation_normal_parent_process
expr_stmt|;
name|gimp_operation_normal_process
operator|=
name|gimp_operation_normal_process_core
expr_stmt|;
if|#
directive|if
name|COMPILE_SSE2_INTRINISICS
if|if
condition|(
name|gimp_cpu_accel_get_support
argument_list|()
operator|&
name|GIMP_CPU_ACCEL_X86_SSE2
condition|)
name|gimp_operation_normal_process
operator|=
name|gimp_operation_normal_process_sse2
expr_stmt|;
endif|#
directive|endif
comment|/* COMPILE_SSE2_INTRINISICS */
if|#
directive|if
name|COMPILE_SSE4_1_INTRINISICS
if|if
condition|(
name|gimp_cpu_accel_get_support
argument_list|()
operator|&
name|GIMP_CPU_ACCEL_X86_SSE4_1
condition|)
name|gimp_operation_normal_process
operator|=
name|gimp_operation_normal_process_sse4
expr_stmt|;
endif|#
directive|endif
comment|/* COMPILE_SSE4_1_INTRINISICS */
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_normal_process
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_normal_init (GimpOperationNormal * self)
name|gimp_operation_normal_init
parameter_list|(
name|GimpOperationNormal
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_normal_parent_process (GeglOperation * operation,GeglOperationContext * context,const gchar * output_prop,const GeglRectangle * result,gint level)
name|gimp_operation_normal_parent_process
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
name|GimpOperationPointLayerMode
modifier|*
name|point
decl_stmt|;
name|point
operator|=
name|GIMP_OPERATION_POINT_LAYER_MODE
argument_list|(
name|operation
argument_list|)
expr_stmt|;
if|if
condition|(
name|point
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
condition|)
block|{
specifier|const
name|GeglRectangle
modifier|*
name|in_extent
init|=
name|NULL
decl_stmt|;
specifier|const
name|GeglRectangle
modifier|*
name|aux_extent
init|=
name|NULL
decl_stmt|;
name|GObject
modifier|*
name|input
decl_stmt|;
name|GObject
modifier|*
name|aux
decl_stmt|;
comment|/* get the raw values this does not increase the reference count */
name|input
operator|=
name|gegl_operation_context_get_object
argument_list|(
name|context
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|aux
operator|=
name|gegl_operation_context_get_object
argument_list|(
name|context
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
comment|/* pass the input/aux buffers directly through if they are not        * overlapping        */
if|if
condition|(
name|input
condition|)
name|in_extent
operator|=
name|gegl_buffer_get_abyss
argument_list|(
name|GEGL_BUFFER
argument_list|(
name|input
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|input
operator|||
operator|(
name|aux
operator|&&
operator|!
name|gegl_rectangle_intersect
argument_list|(
name|NULL
argument_list|,
name|in_extent
argument_list|,
name|result
argument_list|)
operator|)
condition|)
block|{
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
if|if
condition|(
name|aux
condition|)
name|aux_extent
operator|=
name|gegl_buffer_get_abyss
argument_list|(
name|GEGL_BUFFER
argument_list|(
name|aux
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|aux
operator|||
operator|(
name|input
operator|&&
operator|!
name|gegl_rectangle_intersect
argument_list|(
name|NULL
argument_list|,
name|aux_extent
argument_list|,
name|result
argument_list|)
operator|)
condition|)
block|{
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
block|}
comment|/* chain up, which will create the needed buffers for our actual    * process function    */
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
name|gboolean
DECL|function|gimp_operation_normal_process_core (GeglOperation * operation,void * in_p,void * aux_p,void * mask_p,void * out_p,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_normal_process_core
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|void
modifier|*
name|in_p
parameter_list|,
name|void
modifier|*
name|aux_p
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
name|GimpOperationPointLayerMode
modifier|*
name|layer_mode
init|=
operator|(
name|gpointer
operator|)
name|operation
decl_stmt|;
name|gfloat
name|opacity
init|=
name|layer_mode
operator|->
name|opacity
decl_stmt|;
name|gfloat
modifier|*
name|in
init|=
name|in_p
decl_stmt|,
modifier|*
name|aux
init|=
name|aux_p
decl_stmt|,
modifier|*
name|mask
init|=
name|mask_p
decl_stmt|,
modifier|*
name|out
init|=
name|out_p
decl_stmt|;
specifier|const
name|gboolean
name|has_mask
init|=
name|mask
operator|!=
name|NULL
decl_stmt|;
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|aux_alpha
decl_stmt|;
name|aux_alpha
operator|=
name|aux
index|[
name|ALPHA
index|]
operator|*
name|opacity
expr_stmt|;
if|if
condition|(
name|has_mask
condition|)
name|aux_alpha
operator|*=
operator|*
name|mask
expr_stmt|;
name|out
index|[
name|ALPHA
index|]
operator|=
name|aux_alpha
operator|+
name|in
index|[
name|ALPHA
index|]
operator|-
name|aux_alpha
operator|*
name|in
index|[
name|ALPHA
index|]
expr_stmt|;
if|if
condition|(
name|out
index|[
name|ALPHA
index|]
condition|)
block|{
name|gfloat
name|aux_weight
init|=
name|aux_alpha
operator|/
name|out
index|[
name|ALPHA
index|]
decl_stmt|;
name|gfloat
name|in_weight
init|=
literal|1.0f
operator|-
name|aux_weight
decl_stmt|;
name|gint
name|b
decl_stmt|;
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
block|{
name|out
index|[
name|b
index|]
operator|=
name|aux
index|[
name|b
index|]
operator|*
name|aux_weight
operator|+
name|in
index|[
name|b
index|]
operator|*
name|in_weight
expr_stmt|;
block|}
block|}
else|else
block|{
name|gint
name|b
decl_stmt|;
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
block|{
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
block|}
block|}
name|in
operator|+=
literal|4
expr_stmt|;
name|aux
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
return|return
name|TRUE
return|;
block|}
end_function

end_unit

