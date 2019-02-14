begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationpassthrough.c  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *               2017 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpoperationpassthrough.h"
end_include

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationPassThrough,gimp_operation_pass_through,GIMP_TYPE_OPERATION_REPLACE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationPassThrough
argument_list|,
argument|gimp_operation_pass_through
argument_list|,
argument|GIMP_TYPE_OPERATION_REPLACE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_operation_pass_through_class_init
parameter_list|(
name|GimpOperationPassThroughClass
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
literal|"gimp:pass-through"
argument_list|,
literal|"description"
argument_list|,
literal|"GIMP pass through mode operation"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* don't use REPLACE mode's specialized get_affected_region(); PASS_THROUGH    * behaves like an ordinary layer mode here.    */
name|layer_mode_class
operator|->
name|get_affected_region
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_pass_through_init (GimpOperationPassThrough * self)
name|gimp_operation_pass_through_init
parameter_list|(
name|GimpOperationPassThrough
modifier|*
name|self
parameter_list|)
block|{ }
end_function

end_unit

