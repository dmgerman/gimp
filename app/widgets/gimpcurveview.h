begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CURVE_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CURVE_VIEW_H__
define|#
directive|define
name|__GIMP_CURVE_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimphistogramview.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CURVE_VIEW
define|#
directive|define
name|GIMP_TYPE_CURVE_VIEW
value|(gimp_curve_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_CURVE_VIEW (obj)
define|#
directive|define
name|GIMP_CURVE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CURVE_VIEW, GimpCurveView))
end_define

begin_define
DECL|macro|GIMP_CURVE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_CURVE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CURVE_VIEW, GimpCurveViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_CURVE_VIEW (obj)
define|#
directive|define
name|GIMP_IS_CURVE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CURVE_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_CURVE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CURVE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CURVE_VIEW))
end_define

begin_define
DECL|macro|GIMP_CURVE_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CURVE_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CURVE_VIEW, GimpCurveViewClass))
end_define

begin_typedef
DECL|typedef|GimpCurveViewClass
typedef|typedef
name|struct
name|_GimpCurveViewClass
name|GimpCurveViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCurveView
struct|struct
name|_GimpCurveView
block|{
DECL|member|parent_instance
name|GimpHistogramView
name|parent_instance
decl_stmt|;
DECL|member|curve
name|GimpCurve
modifier|*
name|curve
decl_stmt|;
DECL|member|draw_base_line
name|gboolean
name|draw_base_line
decl_stmt|;
DECL|member|grid_rows
name|gint
name|grid_rows
decl_stmt|;
DECL|member|grid_columns
name|gint
name|grid_columns
decl_stmt|;
DECL|member|selected
name|gint
name|selected
decl_stmt|;
DECL|member|last_x
name|gdouble
name|last_x
decl_stmt|;
DECL|member|last_y
name|gdouble
name|last_y
decl_stmt|;
DECL|member|leftmost
name|gdouble
name|leftmost
decl_stmt|;
DECL|member|rightmost
name|gdouble
name|rightmost
decl_stmt|;
DECL|member|grabbed
name|gboolean
name|grabbed
decl_stmt|;
DECL|member|cursor_type
name|GdkCursorType
name|cursor_type
decl_stmt|;
DECL|member|xpos
name|gdouble
name|xpos
decl_stmt|;
DECL|member|xpos_layout
name|PangoLayout
modifier|*
name|xpos_layout
decl_stmt|;
DECL|member|cursor_x
name|gint
name|cursor_x
decl_stmt|;
DECL|member|cursor_y
name|gint
name|cursor_y
decl_stmt|;
DECL|member|cursor_layout
name|PangoLayout
modifier|*
name|cursor_layout
decl_stmt|;
DECL|member|cursor_rect
name|PangoRectangle
name|cursor_rect
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCurveViewClass
struct|struct
name|_GimpCurveViewClass
block|{
DECL|member|parent_class
name|GimpHistogramViewClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_curve_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_curve_view_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_curve_view_set_curve
parameter_list|(
name|GimpCurveView
modifier|*
name|view
parameter_list|,
name|GimpCurve
modifier|*
name|curve
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCurve
modifier|*
name|gimp_curve_view_get_curve
parameter_list|(
name|GimpCurveView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_curve_view_set_selected
parameter_list|(
name|GimpCurveView
modifier|*
name|view
parameter_list|,
name|gint
name|selected
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_curve_view_set_xpos
parameter_list|(
name|GimpCurveView
modifier|*
name|view
parameter_list|,
name|gdouble
name|x
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CURVE_VIEW_H__ */
end_comment

end_unit

