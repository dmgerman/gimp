begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationcage.c  * Copyright (C) 2010 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcage.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationcage.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_operation_cage_process
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
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOperationCage,gimp_operation_cage,GEGL_TYPE_OPERATION_FILTER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationCage
argument_list|,
argument|gimp_operation_cage
argument_list|,
argument|GEGL_TYPE_OPERATION_FILTER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_cage_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_operation_cage_class_init
parameter_list|(
name|GimpOperationCageClass
modifier|*
name|klass
parameter_list|)
block|{    }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_cage_init (GimpOperationCage * self)
name|gimp_operation_cage_init
parameter_list|(
name|GimpOperationCage
modifier|*
name|self
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_operation_cage_process (GeglOperation * operation,void * in_buf,void * out_buf,glong samples,const GeglRectangle * roi)
name|gimp_operation_cage_process
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
parameter_list|)
block|{    }
end_function

end_unit

