begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"gimppencil.h"
end_include

begin_include
include|#
directive|include
file|"gimppenciloptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_macro
DECL|function|G_DEFINE_TYPE (GimpPencil,gimp_pencil,GIMP_TYPE_PAINTBRUSH)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPencil
argument_list|,
argument|gimp_pencil
argument_list|,
argument|GIMP_TYPE_PAINTBRUSH
argument_list|)
end_macro

begin_function
name|void
name|gimp_pencil_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPaintRegisterCallback
name|callback
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_PENCIL
argument_list|,
name|GIMP_TYPE_PENCIL_OPTIONS
argument_list|,
literal|"gimp-pencil"
argument_list|,
name|_
argument_list|(
literal|"Pencil"
argument_list|)
argument_list|,
literal|"gimp-tool-pencil"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pencil_class_init (GimpPencilClass * klass)
name|gimp_pencil_class_init
parameter_list|(
name|GimpPencilClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pencil_init (GimpPencil * pencil)
name|gimp_pencil_init
parameter_list|(
name|GimpPencil
modifier|*
name|pencil
parameter_list|)
block|{ }
end_function

end_unit

