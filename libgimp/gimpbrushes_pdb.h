begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpbrushes_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_BRUSHES_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSHES_PDB_H__
define|#
directive|define
name|__GIMP_BRUSHES_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_brushes_refresh
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gimp_brushes_get_list
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filter
parameter_list|,
name|gint
modifier|*
name|num_brushes
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_context_get_brush
argument_list|)
end_macro

begin_function_decl
name|gchar
modifier|*
name|gimp_brushes_get_brush
parameter_list|(
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|spacing
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_brush_get_spacing
argument_list|)
end_macro

begin_function_decl
name|gint
name|gimp_brushes_get_spacing
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_brush_set_spacing
argument_list|)
end_macro

begin_function_decl
name|gboolean
name|gimp_brushes_set_spacing
parameter_list|(
name|gint
name|spacing
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_brush_get_pixels
argument_list|)
end_macro

begin_function_decl
name|gchar
modifier|*
name|gimp_brushes_get_brush_data
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
modifier|*
name|opacity
parameter_list|,
name|gint
modifier|*
name|spacing
parameter_list|,
name|GimpLayerMode
modifier|*
name|paint_mode
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|length
parameter_list|,
name|guint8
modifier|*
modifier|*
name|mask_data
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
comment|/* __GIMP_BRUSHES_PDB_H__ */
end_comment

end_unit

