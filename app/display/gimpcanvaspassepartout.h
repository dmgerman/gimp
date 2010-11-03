begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvaspassepartout.h  * Copyright (C) 2010 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CANVAS_PASSE_PARTOUT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CANVAS_PASSE_PARTOUT_H__
define|#
directive|define
name|__GIMP_CANVAS_PASSE_PARTOUT_H__
end_define

begin_include
include|#
directive|include
file|"gimpcanvasrectangle.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CANVAS_PASSE_PARTOUT
define|#
directive|define
name|GIMP_TYPE_CANVAS_PASSE_PARTOUT
value|(gimp_canvas_passe_partout_get_type ())
end_define

begin_define
DECL|macro|GIMP_CANVAS_PASSE_PARTOUT (obj)
define|#
directive|define
name|GIMP_CANVAS_PASSE_PARTOUT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CANVAS_PASSE_PARTOUT, GimpCanvasPassePartout))
end_define

begin_define
DECL|macro|GIMP_CANVAS_PASSE_PARTOUT_CLASS (klass)
define|#
directive|define
name|GIMP_CANVAS_PASSE_PARTOUT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CANVAS_PASSE_PARTOUT, GimpCanvasPassePartoutClass))
end_define

begin_define
DECL|macro|GIMP_IS_CANVAS_PASSE_PARTOUT (obj)
define|#
directive|define
name|GIMP_IS_CANVAS_PASSE_PARTOUT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CANVAS_PASSE_PARTOUT))
end_define

begin_define
DECL|macro|GIMP_IS_CANVAS_PASSE_PARTOUT_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CANVAS_PASSE_PARTOUT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CANVAS_PASSE_PARTOUT))
end_define

begin_define
DECL|macro|GIMP_CANVAS_PASSE_PARTOUT_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CANVAS_PASSE_PARTOUT_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CANVAS_PASSE_PARTOUT, GimpCanvasPassePartoutClass))
end_define

begin_typedef
DECL|typedef|GimpCanvasPassePartout
typedef|typedef
name|struct
name|_GimpCanvasPassePartout
name|GimpCanvasPassePartout
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCanvasPassePartoutClass
typedef|typedef
name|struct
name|_GimpCanvasPassePartoutClass
name|GimpCanvasPassePartoutClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasPassePartout
struct|struct
name|_GimpCanvasPassePartout
block|{
DECL|member|parent_instance
name|GimpCanvasRectangle
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCanvasPassePartoutClass
struct|struct
name|_GimpCanvasPassePartoutClass
block|{
DECL|member|parent_class
name|GimpCanvasRectangleClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_canvas_passe_partout_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_canvas_passe_partout_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CANVAS_PASSE_PARTOUT_H__ */
end_comment

end_unit

