begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for the GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas  alt@picnic.demon.co.uk  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *   */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GFIG_BEZIER_H__
end_ifndef

begin_define
DECL|macro|__GFIG_BEZIER_H__
define|#
directive|define
name|__GFIG_BEZIER_H__
end_define

begin_decl_stmt
specifier|extern
name|Dobject
modifier|*
name|tmp_bezier
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|d_draw_bezier
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|d_update_bezier
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|d_bezier_start
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|,
name|gint
name|shift_down
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|d_bezier_end
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|,
name|gint
name|shift_down
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|d_bezier_object_class_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bezier_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GFIG_BEZIER_H__ */
end_comment

end_unit

