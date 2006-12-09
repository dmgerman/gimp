begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_AIRBRUSH_H__
end_ifndef

begin_define
DECL|macro|__GIMP_AIRBRUSH_H__
define|#
directive|define
name|__GIMP_AIRBRUSH_H__
end_define

begin_include
include|#
directive|include
file|"gimppaintbrush.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_AIRBRUSH
define|#
directive|define
name|GIMP_TYPE_AIRBRUSH
value|(gimp_airbrush_get_type ())
end_define

begin_define
DECL|macro|GIMP_AIRBRUSH (obj)
define|#
directive|define
name|GIMP_AIRBRUSH
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_AIRBRUSH, GimpAirbrush))
end_define

begin_define
DECL|macro|GIMP_AIRBRUSH_CLASS (klass)
define|#
directive|define
name|GIMP_AIRBRUSH_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_AIRBRUSH, GimpAirbrushClass))
end_define

begin_define
DECL|macro|GIMP_IS_AIRBRUSH (obj)
define|#
directive|define
name|GIMP_IS_AIRBRUSH
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_AIRBRUSH))
end_define

begin_define
DECL|macro|GIMP_IS_AIRBRUSH_CLASS (klass)
define|#
directive|define
name|GIMP_IS_AIRBRUSH_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_AIRBRUSH))
end_define

begin_define
DECL|macro|GIMP_AIRBRUSH_GET_CLASS (obj)
define|#
directive|define
name|GIMP_AIRBRUSH_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_AIRBRUSH, GimpAirbrushClass))
end_define

begin_typedef
DECL|typedef|GimpAirbrush
typedef|typedef
name|struct
name|_GimpAirbrush
name|GimpAirbrush
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpAirbrushClass
typedef|typedef
name|struct
name|_GimpAirbrushClass
name|GimpAirbrushClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpAirbrush
struct|struct
name|_GimpAirbrush
block|{
DECL|member|parent_instance
name|GimpPaintbrush
name|parent_instance
decl_stmt|;
DECL|member|timeout_id
name|guint
name|timeout_id
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|paint_options
name|GimpPaintOptions
modifier|*
name|paint_options
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpAirbrushClass
struct|struct
name|_GimpAirbrushClass
block|{
DECL|member|parent_class
name|GimpPaintbrushClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_airbrush_register
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
name|gimp_airbrush_get_type
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
comment|/*  __GIMP_AIRBRUSH_H__  */
end_comment

end_unit

