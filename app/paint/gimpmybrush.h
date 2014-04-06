begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MYBRUSH_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MYBRUSH_H__
define|#
directive|define
name|__GIMP_MYBRUSH_H__
end_define

begin_include
include|#
directive|include
file|"gimppaintcore.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_MYBRUSH
define|#
directive|define
name|GIMP_TYPE_MYBRUSH
value|(gimp_mybrush_get_type ())
end_define

begin_define
DECL|macro|GIMP_MYBRUSH (obj)
define|#
directive|define
name|GIMP_MYBRUSH
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_MYBRUSH, GimpMybrush))
end_define

begin_define
DECL|macro|GIMP_MYBRUSH_CLASS (klass)
define|#
directive|define
name|GIMP_MYBRUSH_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_MYBRUSH, GimpMybrushClass))
end_define

begin_define
DECL|macro|GIMP_IS_MYBRUSH (obj)
define|#
directive|define
name|GIMP_IS_MYBRUSH
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_MYBRUSH))
end_define

begin_define
DECL|macro|GIMP_IS_MYBRUSH_CLASS (klass)
define|#
directive|define
name|GIMP_IS_MYBRUSH_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_MYBRUSH))
end_define

begin_define
DECL|macro|GIMP_MYBRUSH_GET_CLASS (obj)
define|#
directive|define
name|GIMP_MYBRUSH_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_MYBRUSH, GimpMybrushClass))
end_define

begin_typedef
DECL|typedef|GimpMybrushPrivate
typedef|typedef
name|struct
name|_GimpMybrushPrivate
name|GimpMybrushPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMybrushClass
typedef|typedef
name|struct
name|_GimpMybrushClass
name|GimpMybrushClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpMybrush
struct|struct
name|_GimpMybrush
block|{
DECL|member|parent_instance
name|GimpPaintCore
name|parent_instance
decl_stmt|;
DECL|member|private
name|GimpMybrushPrivate
modifier|*
name|private
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpMybrushClass
struct|struct
name|_GimpMybrushClass
block|{
DECL|member|parent_class
name|GimpPaintCoreClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_mybrush_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPaintRegisterCallback
name|callback
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_mybrush_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_MYBRUSH_H__  */
end_comment

end_unit

