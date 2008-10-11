begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationpointcomposer.c  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationpointcomposer.h"
end_include

begin_macro
DECL|function|G_DEFINE_ABSTRACT_TYPE (GimpOperationPointComposer,gimp_operation_point_composer,GEGL_TYPE_OPERATION_POINT_COMPOSER)
name|G_DEFINE_ABSTRACT_TYPE
argument_list|(
argument|GimpOperationPointComposer
argument_list|,
argument|gimp_operation_point_composer
argument_list|,
argument|GEGL_TYPE_OPERATION_POINT_COMPOSER
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_operation_point_composer_class_init
parameter_list|(
name|GimpOperationPointComposerClass
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
name|operation_class
operator|->
name|categories
operator|=
literal|"compositors"
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_point_composer_init (GimpOperationPointComposer * self)
name|gimp_operation_point_composer_init
parameter_list|(
name|GimpOperationPointComposer
modifier|*
name|self
parameter_list|)
block|{ }
end_function

end_unit

