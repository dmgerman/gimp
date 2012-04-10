begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Wilber Cairo rendering  * Copyright (C) 2008  Sven Neumann<sven@gimp.org>  *  * Some code here is based on code from librsvg that was originally  * written by Raph Levien<raph@artofcode.com> for Gill.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CAIRO_WILBER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CAIRO_WILBER_H__
define|#
directive|define
name|__GIMP_CAIRO_WILBER_H__
end_define

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

begin_function_decl
name|void
name|gimp_cairo_wilber
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cairo_wilber_get_size
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gdouble
modifier|*
name|width
parameter_list|,
name|gdouble
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CAIRO_WILBER_H__ */
end_comment

end_unit

