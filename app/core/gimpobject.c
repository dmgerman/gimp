begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_function
specifier|static
name|void
DECL|function|gimp_object_init (GimpObject * object)
name|gimp_object_init
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_object_class_init (GimpObjectClass * klass)
name|gimp_object_class_init
parameter_list|(
name|GimpObjectClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
name|GtkType
DECL|function|gimp_object_get_type (void)
name|gimp_object_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
init|=
literal|0
decl_stmt|;
name|GIMP_TYPE_INIT
argument_list|(
name|type
argument_list|,
name|GimpObject
argument_list|,
name|GimpObjectClass
argument_list|,
name|gimp_object_init
argument_list|,
name|gimp_object_class_init
argument_list|,
name|GTK_TYPE_OBJECT
argument_list|)
expr_stmt|;
return|return
name|type
return|;
block|}
end_function

end_unit

