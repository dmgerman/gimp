begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpgrid_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimp.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GRID_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GRID_PDB_H__
define|#
directive|define
name|__GIMP_GRID_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_image_grid_get_spacing
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gdouble
modifier|*
name|xspacing
parameter_list|,
name|gdouble
modifier|*
name|yspacing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_grid_set_spacing
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gdouble
name|xspacing
parameter_list|,
name|gdouble
name|yspacing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_grid_get_offset
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gdouble
modifier|*
name|xoffset
parameter_list|,
name|gdouble
modifier|*
name|yoffset
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_grid_set_offset
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gdouble
name|xoffset
parameter_list|,
name|gdouble
name|yoffset
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_grid_get_foreground_color
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpRGB
modifier|*
name|fgcolor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_grid_set_foreground_color
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|fgcolor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_grid_get_background_color
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpRGB
modifier|*
name|bgcolor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_grid_set_background_color
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|bgcolor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpGridStyle
name|gimp_image_grid_get_style
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_grid_set_style
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpGridStyle
name|style
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GRID_PDB_H__ */
end_comment

end_unit

