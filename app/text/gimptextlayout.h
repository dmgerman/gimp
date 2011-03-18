begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_LAYOUT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_LAYOUT_H__
define|#
directive|define
name|__GIMP_TEXT_LAYOUT_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_TEXT_LAYOUT
define|#
directive|define
name|GIMP_TYPE_TEXT_LAYOUT
value|(gimp_text_layout_get_type ())
end_define

begin_define
DECL|macro|GIMP_TEXT_LAYOUT (obj)
define|#
directive|define
name|GIMP_TEXT_LAYOUT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TEXT_LAYOUT, GimpTextLayout))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_LAYOUT (obj)
define|#
directive|define
name|GIMP_IS_TEXT_LAYOUT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TEXT_LAYOUT))
end_define

begin_typedef
DECL|typedef|GimpTextLayoutClass
typedef|typedef
name|struct
name|_GimpTextLayoutClass
name|GimpTextLayoutClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTextLayoutClass
struct|struct
name|_GimpTextLayoutClass
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
name|gimp_text_layout_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpTextLayout
modifier|*
name|gimp_text_layout_new
parameter_list|(
name|GimpText
modifier|*
name|text
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|yres
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layout_get_size
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|heigth
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_layout_get_offsets
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_layout_get_resolution
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|gdouble
modifier|*
name|xres
parameter_list|,
name|gdouble
modifier|*
name|yres
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpText
modifier|*
name|gimp_text_layout_get_text
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PangoLayout
modifier|*
name|gimp_text_layout_get_pango_layout
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_layout_get_transform
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|cairo_matrix_t
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_layout_transform_rect
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|PangoRectangle
modifier|*
name|rect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_layout_transform_point
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_layout_transform_distance
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_layout_untransform_rect
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|PangoRectangle
modifier|*
name|rect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_layout_untransform_point
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_layout_untransform_distance
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TEXT_LAYOUT_H__ */
end_comment

end_unit

