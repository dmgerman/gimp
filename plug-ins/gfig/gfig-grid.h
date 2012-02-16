begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas  alt@picnic.demon.co.uk  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GFIG_GRID_H__
end_ifndef

begin_define
DECL|macro|__GFIG_GRID_H__
define|#
directive|define
name|__GFIG_GRID_H__
end_define

begin_define
DECL|macro|GFIG_NORMAL_GC
define|#
directive|define
name|GFIG_NORMAL_GC
value|-1
end_define

begin_define
DECL|macro|GFIG_BLACK_GC
define|#
directive|define
name|GFIG_BLACK_GC
value|-2
end_define

begin_define
DECL|macro|GFIG_WHITE_GC
define|#
directive|define
name|GFIG_WHITE_GC
value|-3
end_define

begin_define
DECL|macro|GFIG_GREY_GC
define|#
directive|define
name|GFIG_GREY_GC
value|-4
end_define

begin_define
DECL|macro|GFIG_DARKER_GC
define|#
directive|define
name|GFIG_DARKER_GC
value|-5
end_define

begin_define
DECL|macro|GFIG_LIGHTER_GC
define|#
directive|define
name|GFIG_LIGHTER_GC
value|-6
end_define

begin_define
DECL|macro|GFIG_VERY_DARK_GC
define|#
directive|define
name|GFIG_VERY_DARK_GC
value|-7
end_define

begin_define
DECL|macro|MIN_GRID
define|#
directive|define
name|MIN_GRID
value|10
end_define

begin_define
DECL|macro|MAX_GRID
define|#
directive|define
name|MAX_GRID
value|50
end_define

begin_decl_stmt
specifier|extern
name|gint
name|grid_gc_type
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gfig_grid_colours
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|find_grid_pos
parameter_list|(
name|GdkPoint
modifier|*
name|p
parameter_list|,
name|GdkPoint
modifier|*
name|gp
parameter_list|,
name|guint
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|draw_grid
parameter_list|(
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
comment|/* __GFIG_GRID_H__ */
end_comment

end_unit

