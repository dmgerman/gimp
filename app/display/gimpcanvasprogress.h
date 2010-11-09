begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvasprogress.h  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CANVAS_PROGRESS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CANVAS_PROGRESS_H__
define|#
directive|define
name|__GIMP_CANVAS_PROGRESS_H__
end_define

begin_include
include|#
directive|include
file|"gimpcanvasitem.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CANVAS_PROGRESS
define|#
directive|define
name|GIMP_TYPE_CANVAS_PROGRESS
value|(gimp_canvas_progress_get_type ())
end_define

begin_define
DECL|macro|GIMP_CANVAS_PROGRESS (obj)
define|#
directive|define
name|GIMP_CANVAS_PROGRESS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CANVAS_PROGRESS, GimpCanvasProgress))
end_define

begin_define
DECL|macro|GIMP_CANVAS_PROGRESS_CLASS (klass)
define|#
directive|define
name|GIMP_CANVAS_PROGRESS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CANVAS_PROGRESS, GimpCanvasProgressClass))
end_define

begin_define
DECL|macro|GIMP_IS_CANVAS_PROGRESS (obj)
define|#
directive|define
name|GIMP_IS_CANVAS_PROGRESS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CANVAS_PROGRESS))
end_define

begin_define
DECL|macro|GIMP_IS_CANVAS_PROGRESS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CANVAS_PROGRESS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CANVAS_PROGRESS))
end_define

begin_define
DECL|macro|GIMP_CANVAS_PROGRESS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CANVAS_PROGRESS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CANVAS_PROGRESS, GimpCanvasProgressClass))
end_define

begin_typedef
DECL|typedef|GimpCanvasProgress
typedef|typedef
name|struct
name|_GimpCanvasProgress
name|GimpCanvasProgress
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCanvasProgressClass
typedef|typedef
name|struct
name|_GimpCanvasProgressClass
name|GimpCanvasProgressClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasProgress
struct|struct
name|_GimpCanvasProgress
block|{
DECL|member|parent_instance
name|GimpCanvasItem
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCanvasProgressClass
struct|struct
name|_GimpCanvasProgressClass
block|{
DECL|member|parent_class
name|GimpCanvasItemClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_canvas_progress_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_canvas_progress_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpHandleAnchor
name|anchor
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CANVAS_PROGRESS_H__ */
end_comment

end_unit

