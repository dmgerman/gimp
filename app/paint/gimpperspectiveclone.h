begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PERSPECTIVE_CLONE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PERSPECTIVE_CLONE_H__
define|#
directive|define
name|__GIMP_PERSPECTIVE_CLONE_H__
end_define

begin_include
include|#
directive|include
file|"gimpclone.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PERSPECTIVE_CLONE
define|#
directive|define
name|GIMP_TYPE_PERSPECTIVE_CLONE
value|(gimp_perspective_clone_get_type ())
end_define

begin_define
DECL|macro|GIMP_PERSPECTIVE_CLONE (obj)
define|#
directive|define
name|GIMP_PERSPECTIVE_CLONE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PERSPECTIVE_CLONE, GimpPerspectiveClone))
end_define

begin_define
DECL|macro|GIMP_PERSPECTIVE_CLONE_CLASS (klass)
define|#
directive|define
name|GIMP_PERSPECTIVE_CLONE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PERSPECTIVE_CLONE, GimpPerspectiveCloneClass))
end_define

begin_define
DECL|macro|GIMP_IS_PERSPECTIVE_CLONE (obj)
define|#
directive|define
name|GIMP_IS_PERSPECTIVE_CLONE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PERSPECTIVE_CLONE))
end_define

begin_define
DECL|macro|GIMP_IS_PERSPECTIVE_CLONE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PERSPECTIVE_CLONE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PERSPECTIVE_CLONE))
end_define

begin_define
DECL|macro|GIMP_PERSPECTIVE_CLONE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PERSPECTIVE_CLONE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PERSPECTIVE_CLONE, GimpPerspectiveCloneClass))
end_define

begin_typedef
DECL|typedef|GimpPerspectiveCloneClass
typedef|typedef
name|struct
name|_GimpPerspectiveCloneClass
name|GimpPerspectiveCloneClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPerspectiveClone
struct|struct
name|_GimpPerspectiveClone
block|{
DECL|member|parent_instance
name|GimpClone
name|parent_instance
decl_stmt|;
DECL|member|src_x_fv
name|gdouble
name|src_x_fv
decl_stmt|;
comment|/* source coords in front_view perspective */
DECL|member|src_y_fv
name|gdouble
name|src_y_fv
decl_stmt|;
DECL|member|dest_x_fv
name|gdouble
name|dest_x_fv
decl_stmt|;
comment|/* destination coords in front_view perspective */
DECL|member|dest_y_fv
name|gdouble
name|dest_y_fv
decl_stmt|;
DECL|member|transform
name|GimpMatrix3
name|transform
decl_stmt|;
DECL|member|transform_inv
name|GimpMatrix3
name|transform_inv
decl_stmt|;
DECL|member|src_area
name|TempBuf
modifier|*
name|src_area
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPerspectiveCloneClass
struct|struct
name|_GimpPerspectiveCloneClass
block|{
DECL|member|parent_class
name|GimpCloneClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_perspective_clone_register
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
name|gimp_perspective_clone_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_perspective_clone_set_transform
parameter_list|(
name|GimpPerspectiveClone
modifier|*
name|clone
parameter_list|,
name|GimpMatrix3
modifier|*
name|transform
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_perspective_clone_get_source_point
parameter_list|(
name|GimpPerspectiveClone
modifier|*
name|clone
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|newx
parameter_list|,
name|gdouble
modifier|*
name|newy
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PERSPECTIVE_CLONE_H__  */
end_comment

end_unit

