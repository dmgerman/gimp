begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcoordmath.h  * Copyright (C) 2002 Simon Budig<simon@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_function_decl
name|void
name|gimp_bezier_coords_mix
parameter_list|(
specifier|const
name|gdouble
name|amul
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|,
specifier|const
name|gdouble
name|bmul
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|b
parameter_list|,
name|GimpCoords
modifier|*
name|ret_val
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_bezier_coords_average
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|b
parameter_list|,
name|GimpCoords
modifier|*
name|ret_average
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_bezier_coords_add
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|b
parameter_list|,
name|GimpCoords
modifier|*
name|ret_add
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_bezier_coords_difference
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|b
parameter_list|,
name|GimpCoords
modifier|*
name|difference
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_bezier_coords_scale
parameter_list|(
specifier|const
name|gdouble
name|f
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|,
name|GimpCoords
modifier|*
name|ret_product
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_bezier_coords_scalarprod
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_bezier_coords_length
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_bezier_coords_length2
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|)
function_decl|;
end_function_decl

end_unit

