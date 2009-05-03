begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PAINTBRUSH_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PAINTBRUSH_H__
define|#
directive|define
name|__GIMP_PAINTBRUSH_H__
end_define

begin_include
include|#
directive|include
file|"gimpbrushcore.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PAINTBRUSH
define|#
directive|define
name|GIMP_TYPE_PAINTBRUSH
value|(gimp_paintbrush_get_type ())
end_define

begin_define
DECL|macro|GIMP_PAINTBRUSH (obj)
define|#
directive|define
name|GIMP_PAINTBRUSH
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PAINTBRUSH, GimpPaintbrush))
end_define

begin_define
DECL|macro|GIMP_PAINTBRUSH_CLASS (klass)
define|#
directive|define
name|GIMP_PAINTBRUSH_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PAINTBRUSH, GimpPaintbrushClass))
end_define

begin_define
DECL|macro|GIMP_IS_PAINTBRUSH (obj)
define|#
directive|define
name|GIMP_IS_PAINTBRUSH
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PAINTBRUSH))
end_define

begin_define
DECL|macro|GIMP_IS_PAINTBRUSH_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PAINTBRUSH_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PAINTBRUSH))
end_define

begin_define
DECL|macro|GIMP_PAINTBRUSH_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PAINTBRUSH_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PAINTBRUSH, GimpPaintbrushClass))
end_define

begin_typedef
DECL|typedef|GimpPaintbrushClass
typedef|typedef
name|struct
name|_GimpPaintbrushClass
name|GimpPaintbrushClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPaintbrush
struct|struct
name|_GimpPaintbrush
block|{
DECL|member|parent_instance
name|GimpBrushCore
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPaintbrushClass
struct|struct
name|_GimpPaintbrushClass
block|{
DECL|member|parent_class
name|GimpBrushCoreClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_paintbrush_register
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
name|gimp_paintbrush_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  protected  */
end_comment

begin_function_decl
name|void
name|_gimp_paintbrush_motion
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PAINTBRUSH_H__  */
end_comment

end_unit

