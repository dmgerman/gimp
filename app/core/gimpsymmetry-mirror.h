begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsymmetry-mirror.h  * Copyright (C) 2015 Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MIRROR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MIRROR_H__
define|#
directive|define
name|__GIMP_MIRROR_H__
end_define

begin_include
include|#
directive|include
file|"gimpsymmetry.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_MIRROR
define|#
directive|define
name|GIMP_TYPE_MIRROR
value|(gimp_mirror_get_type ())
end_define

begin_define
DECL|macro|GIMP_MIRROR (obj)
define|#
directive|define
name|GIMP_MIRROR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_MIRROR, GimpMirror))
end_define

begin_define
DECL|macro|GIMP_MIRROR_CLASS (klass)
define|#
directive|define
name|GIMP_MIRROR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_MIRROR, GimpMirrorClass))
end_define

begin_define
DECL|macro|GIMP_IS_MIRROR (obj)
define|#
directive|define
name|GIMP_IS_MIRROR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_MIRROR))
end_define

begin_define
DECL|macro|GIMP_IS_MIRROR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_MIRROR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_MIRROR))
end_define

begin_define
DECL|macro|GIMP_MIRROR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_MIRROR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_MIRROR, GimpMirrorClass))
end_define

begin_typedef
DECL|typedef|GimpMirrorClass
typedef|typedef
name|struct
name|_GimpMirrorClass
name|GimpMirrorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpMirror
struct|struct
name|_GimpMirror
block|{
DECL|member|parent_instance
name|GimpSymmetry
name|parent_instance
decl_stmt|;
DECL|member|horizontal_mirror
name|gboolean
name|horizontal_mirror
decl_stmt|;
DECL|member|vertical_mirror
name|gboolean
name|vertical_mirror
decl_stmt|;
DECL|member|point_symmetry
name|gboolean
name|point_symmetry
decl_stmt|;
DECL|member|disable_transformation
name|gboolean
name|disable_transformation
decl_stmt|;
DECL|member|horizontal_axis_position
name|gdouble
name|horizontal_axis_position
decl_stmt|;
DECL|member|vertical_axis_position
name|gdouble
name|vertical_axis_position
decl_stmt|;
DECL|member|horizontal_guide
name|GimpGuide
modifier|*
name|horizontal_guide
decl_stmt|;
DECL|member|vertical_guide
name|GimpGuide
modifier|*
name|vertical_guide
decl_stmt|;
comment|/* Cached data */
DECL|member|last_paint_width
name|gint
name|last_paint_width
decl_stmt|;
DECL|member|last_paint_height
name|gint
name|last_paint_height
decl_stmt|;
DECL|member|horizontal_op
name|GeglNode
modifier|*
name|horizontal_op
decl_stmt|;
DECL|member|vertical_op
name|GeglNode
modifier|*
name|vertical_op
decl_stmt|;
DECL|member|central_op
name|GeglNode
modifier|*
name|central_op
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpMirrorClass
struct|struct
name|_GimpMirrorClass
block|{
DECL|member|parent_class
name|GimpSymmetryClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_mirror_get_type
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
comment|/*  __GIMP_MIRROR_H__  */
end_comment

end_unit

