begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationerasemode.c  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *               2012 Ville Sokk<ville.sokk@gmail.com>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpoperationerasemode.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_erase_mode_process
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
DECL|function|G_DEFINE_TYPE (GimpOperationEraseMode,gimp_operation_erase_mode,GIMP_TYPE_OPERATION_POINT_LAYER_MODE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationEraseMode
argument_list|,
argument|gimp_operation_erase_mode
argument_list|,
argument|GIMP_TYPE_OPERATION_POINT_LAYER_MODE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_operation_erase_mode_class_init
parameter_list|(
name|GimpOperationEraseModeClass
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
literal|"gimp:erase-mode"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP erase mode operation"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|point_class
operator|->
name|process
operator|=
name|gimp_operation_erase_mode_process
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_erase_mode_init (GimpOperationEraseMode * self)
name|gimp_operation_erase_mode_init
parameter_list|(
name|GimpOperationEraseMode
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_erase_mode_process (GeglOperation * operation,void * in_buf,void * aux_buf,void * aux2_buf,void * out_buf,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_erase_mode_process
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
name|GimpOperationPointLayerMode
modifier|*
name|point
init|=
name|GIMP_OPERATION_POINT_LAYER_MODE
argument_list|(
name|operation
argument_list|)
decl_stmt|;
name|gfloat
name|opacity
init|=
name|point
operator|->
name|opacity
decl_stmt|;
name|gfloat
modifier|*
name|in
init|=
name|in_buf
decl_stmt|;
name|gfloat
modifier|*
name|layer
init|=
name|aux_buf
decl_stmt|;
name|gfloat
modifier|*
name|mask
init|=
name|aux2_buf
decl_stmt|;
name|gfloat
modifier|*
name|out
init|=
name|out_buf
decl_stmt|;
if|if
condition|(
name|point
operator|->
name|premultiplied
condition|)
block|{
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gint
name|b
decl_stmt|;
name|gfloat
name|value
init|=
name|opacity
decl_stmt|;
if|if
condition|(
name|mask
condition|)
name|value
operator|*=
operator|(
operator|*
name|mask
operator|)
expr_stmt|;
name|out
index|[
name|ALPHA
index|]
operator|=
name|in
index|[
name|ALPHA
index|]
operator|-
name|in
index|[
name|ALPHA
index|]
operator|*
name|layer
index|[
name|ALPHA
index|]
operator|*
name|value
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
operator|/
name|in
index|[
name|ALPHA
index|]
operator|*
name|out
index|[
name|ALPHA
index|]
expr_stmt|;
block|}
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
name|mask
condition|)
name|mask
operator|+=
literal|1
expr_stmt|;
block|}
block|}
else|else
block|{
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gint
name|b
decl_stmt|;
name|gfloat
name|value
init|=
name|opacity
decl_stmt|;
if|if
condition|(
name|mask
condition|)
name|value
operator|*=
operator|(
operator|*
name|mask
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
name|out
index|[
name|ALPHA
index|]
operator|=
name|in
index|[
name|ALPHA
index|]
operator|-
name|in
index|[
name|ALPHA
index|]
operator|*
name|layer
index|[
name|ALPHA
index|]
operator|*
name|value
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
name|mask
condition|)
name|mask
operator|+=
literal|1
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

