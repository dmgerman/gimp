begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *   * gimpcage.h  * Copyright (C) 2010 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CAGE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CAGE_H__
define|#
directive|define
name|__GIMP_CAGE_H__
end_define

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_CAGE
define|#
directive|define
name|GIMP_TYPE_CAGE
value|(gimp_cage_get_type ())
end_define

begin_define
DECL|macro|GIMP_CAGE (obj)
define|#
directive|define
name|GIMP_CAGE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CAGE, GimpCage))
end_define

begin_define
DECL|macro|GIMP_CAGE_CLASS (klass)
define|#
directive|define
name|GIMP_CAGE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CAGE, GimpCageClass))
end_define

begin_define
DECL|macro|GIMP_IS_CAGE (obj)
define|#
directive|define
name|GIMP_IS_CAGE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CAGE))
end_define

begin_define
DECL|macro|GIMP_IS_CAGE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CAGE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CAGE))
end_define

begin_define
DECL|macro|GIMP_CAGE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CAGE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CAGE, GimpCageClass))
end_define

begin_typedef
DECL|typedef|GimpCageClass
typedef|typedef
name|struct
name|_GimpCageClass
name|GimpCageClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCage
struct|struct
name|_GimpCage
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|cageVerticeNumber
name|gint
name|cageVerticeNumber
decl_stmt|;
DECL|member|cageVerticeX
name|gfloat
modifier|*
name|cageVerticeX
decl_stmt|;
DECL|member|cageVerticeY
name|gfloat
modifier|*
name|cageVerticeY
decl_stmt|;
DECL|member|pointNumber
name|gint
name|pointNumber
decl_stmt|;
DECL|member|CoordsVerticeX
name|gfloat
modifier|*
modifier|*
name|CoordsVerticeX
decl_stmt|;
DECL|member|CoordsVerticeY
name|gfloat
modifier|*
modifier|*
name|CoordsVerticeY
decl_stmt|;
DECL|member|CoordsEdgeX
name|gfloat
modifier|*
modifier|*
name|CoordsEdgeX
decl_stmt|;
DECL|member|CoordsEdgeY
name|gfloat
modifier|*
modifier|*
name|CoordsEdgeY
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCageClass
struct|struct
name|_GimpCageClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_cage_get_type
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
comment|/* __GIMP_CAGE_H__ */
end_comment

end_unit

