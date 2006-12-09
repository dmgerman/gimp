begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpGrid  * Copyright (C) 2003  Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GRID_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GRID_H__
define|#
directive|define
name|__GIMP_GRID_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_GRID
define|#
directive|define
name|GIMP_TYPE_GRID
value|(gimp_grid_get_type ())
end_define

begin_define
DECL|macro|GIMP_GRID (obj)
define|#
directive|define
name|GIMP_GRID
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_GRID, GimpGrid))
end_define

begin_define
DECL|macro|GIMP_GRID_CLASS (klass)
define|#
directive|define
name|GIMP_GRID_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_GRID, GimpGridClass))
end_define

begin_define
DECL|macro|GIMP_IS_GRID (obj)
define|#
directive|define
name|GIMP_IS_GRID
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_GRID))
end_define

begin_define
DECL|macro|GIMP_IS_GRID_CLASS (klass)
define|#
directive|define
name|GIMP_IS_GRID_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_GRID))
end_define

begin_define
DECL|macro|GIMP_GRID_GET_CLASS (obj)
define|#
directive|define
name|GIMP_GRID_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_GRID, GimpGridClass))
end_define

begin_typedef
DECL|typedef|GimpGridClass
typedef|typedef
name|struct
name|_GimpGridClass
name|GimpGridClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpGrid
struct|struct
name|_GimpGrid
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|style
name|GimpGridStyle
name|style
decl_stmt|;
DECL|member|fgcolor
name|GimpRGB
name|fgcolor
decl_stmt|;
DECL|member|bgcolor
name|GimpRGB
name|bgcolor
decl_stmt|;
DECL|member|xspacing
name|gdouble
name|xspacing
decl_stmt|;
DECL|member|yspacing
name|gdouble
name|yspacing
decl_stmt|;
DECL|member|spacing_unit
name|GimpUnit
name|spacing_unit
decl_stmt|;
DECL|member|xoffset
name|gdouble
name|xoffset
decl_stmt|;
DECL|member|yoffset
name|gdouble
name|yoffset
decl_stmt|;
DECL|member|offset_unit
name|GimpUnit
name|offset_unit
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpGridClass
struct|struct
name|_GimpGridClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_grid_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_grid_parasite_name
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpParasite
modifier|*
name|gimp_grid_to_parasite
parameter_list|(
specifier|const
name|GimpGrid
modifier|*
name|grid
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpGrid
modifier|*
name|gimp_grid_from_parasite
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GRID_H__ */
end_comment

end_unit

