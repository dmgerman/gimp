begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_RECTANGLE_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RECTANGLE_OPTIONS_H__
define|#
directive|define
name|__GIMP_RECTANGLE_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"gimpselectionoptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_RECTANGLE_OPTIONS
define|#
directive|define
name|GIMP_TYPE_RECTANGLE_OPTIONS
value|(gimp_rectangle_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_RECTANGLE_OPTIONS (obj)
define|#
directive|define
name|GIMP_RECTANGLE_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_RECTANGLE_OPTIONS, GimpRectangleOptions))
end_define

begin_define
DECL|macro|GIMP_RECTANGLE_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_RECTANGLE_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_RECTANGLE_OPTIONS, GimpRectangleOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_RECTANGLE_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_RECTANGLE_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_RECTANGLE_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_RECTANGLE_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_RECTANGLE_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_RECTANGLE_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_RECTANGLE_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_RECTANGLE_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_RECTANGLE_OPTIONS, GimpRectangleOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpRectangleOptions
typedef|typedef
name|struct
name|_GimpRectangleOptions
name|GimpRectangleOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpRectangleOptionsClass
typedef|typedef
name|struct
name|_GimpToolOptionsClass
name|GimpRectangleOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpRectangleOptions
struct|struct
name|_GimpRectangleOptions
block|{
DECL|member|parent_instance
name|GimpSelectionOptions
name|parent_instance
decl_stmt|;
DECL|member|highlight
name|gboolean
name|highlight
decl_stmt|;
DECL|member|fixed_width
name|gboolean
name|fixed_width
decl_stmt|;
DECL|member|width
name|gdouble
name|width
decl_stmt|;
DECL|member|fixed_height
name|gboolean
name|fixed_height
decl_stmt|;
DECL|member|height
name|gdouble
name|height
decl_stmt|;
DECL|member|fixed_aspect
name|gboolean
name|fixed_aspect
decl_stmt|;
DECL|member|aspect
name|gdouble
name|aspect
decl_stmt|;
DECL|member|fixed_center
name|gboolean
name|fixed_center
decl_stmt|;
DECL|member|center_x
name|gdouble
name|center_x
decl_stmt|;
DECL|member|center_y
name|gdouble
name|center_y
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_rectangle_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_rectangle_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_SELCTION_OPTIONS_H__  */
end_comment

end_unit

