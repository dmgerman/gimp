begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationnormalmode.c  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationnormalmode.h"
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

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_normal_mode_process
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
name|aux2_buf
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
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationNormalMode
argument_list|,
argument|gimp_operation_normal_mode
argument_list|,
argument|GIMP_TYPE_OPERATION_POINT_LAYER_MODE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_normal_mode_parent_class
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
literal|"<node operation='gimp:normal-mode'>"
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

begin_function
specifier|static
name|void
DECL|function|gimp_operation_normal_mode_class_init (GimpOperationNormalModeClass * klass)
name|gimp_operation_normal_mode_class_init
parameter_list|(
name|GimpOperationNormalModeClass
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
literal|"gimp:normal-mode"
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
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_normal_mode_process
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_normal_mode_init (GimpOperationNormalMode * self)
name|gimp_operation_normal_mode_init
parameter_list|(
name|GimpOperationNormalMode
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
specifier|static
name|gboolean
DECL|function|gimp_operation_normal_mode_process (GeglOperation * operation,void * in_buf,void * aux_buf,void * aux2_buf,void * out_buf,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_normal_mode_process
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
name|aux2_buf
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
name|gdouble
name|opacity
init|=
name|GIMP_OPERATION_POINT_LAYER_MODE
argument_list|(
name|operation
argument_list|)
operator|->
name|opacity
decl_stmt|;
return|return
name|gimp_operation_normal_mode_process_pixels
argument_list|(
name|in_buf
argument_list|,
name|aux_buf
argument_list|,
name|aux2_buf
argument_list|,
name|out_buf
argument_list|,
name|opacity
argument_list|,
name|samples
argument_list|,
name|roi
argument_list|,
name|level
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_operation_normal_mode_process_pixels (gfloat * in,gfloat * aux,gfloat * mask,gfloat * out,gdouble opacity,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_normal_mode_process_pixels
parameter_list|(
name|gfloat
modifier|*
name|in
parameter_list|,
name|gfloat
modifier|*
name|aux
parameter_list|,
name|gfloat
modifier|*
name|mask
parameter_list|,
name|gfloat
modifier|*
name|out
parameter_list|,
name|gdouble
name|opacity
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
name|in_weight
init|=
name|in
index|[
name|ALPHA
index|]
operator|*
operator|(
literal|1.0f
operator|-
name|aux_alpha
operator|)
decl_stmt|;
name|gfloat
name|recip_out_alpha
init|=
literal|1.0f
operator|/
name|out
index|[
name|ALPHA
index|]
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
operator|(
name|aux
index|[
name|b
index|]
operator|*
name|aux_alpha
operator|+
name|in
index|[
name|b
index|]
operator|*
name|in_weight
operator|)
operator|*
name|recip_out_alpha
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

