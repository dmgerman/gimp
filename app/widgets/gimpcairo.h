begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcairo.h  * Copyright (C) 2010  Michael Natterer<mitch@gimp.org>  *  * Some code here is based on code from librsvg that was originally  * written by Raph Levien<raph@artofcode.com> for Gill.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CAIRO_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CAIRO_H__
define|#
directive|define
name|__GIMP_CAIRO_H__
end_define

begin_function_decl
name|cairo_pattern_t
modifier|*
name|gimp_cairo_stipple_pattern_create
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|fg
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|bg
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cairo_add_arc
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|,
name|gdouble
name|radius
parameter_list|,
name|gdouble
name|start_angle
parameter_list|,
name|gdouble
name|slice_angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cairo_add_segments
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GimpSegment
modifier|*
name|segs
parameter_list|,
name|gint
name|n_segs
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cairo_draw_toolbox_wilber
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cairo_draw_drop_wilber
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CAIRO_H__ */
end_comment

end_unit

