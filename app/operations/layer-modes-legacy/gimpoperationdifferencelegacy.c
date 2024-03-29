begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationdifferencemode.c  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *               2012 Ville Sokk<ville.sokk@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"../operations-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationdifferencelegacy.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_difference_legacy_process
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationDifferenceLegacy,gimp_operation_difference_legacy,GIMP_TYPE_OPERATION_LAYER_MODE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationDifferenceLegacy
argument_list|,
argument|gimp_operation_difference_legacy
argument_list|,
argument|GIMP_TYPE_OPERATION_LAYER_MODE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_operation_difference_legacy_class_init
parameter_list|(
name|GimpOperationDifferenceLegacyClass
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
literal|"gimp:difference-legacy"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP difference mode operation"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|layer_mode_class
operator|->
name|process
operator|=
name|gimp_operation_difference_legacy_process
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_difference_legacy_init (GimpOperationDifferenceLegacy * self)
name|gimp_operation_difference_legacy_init
parameter_list|(
name|GimpOperationDifferenceLegacy
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_difference_legacy_process (GeglOperation * op,void * in_p,void * layer_p,void * mask_p,void * out_p,glong samples,const GeglRectangle * roi,gint level)
name|gimp_operation_difference_legacy_process
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
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|gfloat
name|comp_alpha
decl_stmt|,
name|new_alpha
decl_stmt|;
name|comp_alpha
operator|=
name|MIN
argument_list|(
name|in
index|[
name|ALPHA
index|]
argument_list|,
name|layer
index|[
name|ALPHA
index|]
argument_list|)
operator|*
name|opacity
expr_stmt|;
if|if
condition|(
name|mask
condition|)
name|comp_alpha
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
operator|+
operator|(
literal|1.0f
operator|-
name|in
index|[
name|ALPHA
index|]
operator|)
operator|*
name|comp_alpha
expr_stmt|;
if|if
condition|(
name|comp_alpha
operator|&&
name|new_alpha
condition|)
block|{
name|gfloat
name|ratio
init|=
name|comp_alpha
operator|/
name|new_alpha
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
name|gfloat
name|comp
init|=
name|in
index|[
name|b
index|]
operator|-
name|layer
index|[
name|b
index|]
decl_stmt|;
name|comp
operator|=
operator|(
name|comp
operator|<
literal|0.0f
operator|)
condition|?
operator|-
name|comp
else|:
name|comp
expr_stmt|;
name|out
index|[
name|b
index|]
operator|=
name|comp
operator|*
name|ratio
operator|+
name|in
index|[
name|b
index|]
operator|*
operator|(
literal|1.0f
operator|-
name|ratio
operator|)
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
name|out
index|[
name|ALPHA
index|]
operator|=
name|in
index|[
name|ALPHA
index|]
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
operator|++
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

