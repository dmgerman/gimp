begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimppainttools_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_PAINT_TOOLS_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PAINT_TOOLS_PDB_H__
define|#
directive|define
name|__GIMP_PAINT_TOOLS_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_airbrush
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|pressure
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_airbrush_default
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_clone
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint32
name|src_drawable_ID
parameter_list|,
name|GimpCloneType
name|clone_type
parameter_list|,
name|gdouble
name|src_x
parameter_list|,
name|gdouble
name|src_y
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_clone_default
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_convolve
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|pressure
parameter_list|,
name|GimpConvolveType
name|convolve_type
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_convolve_default
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dodgeburn
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|exposure
parameter_list|,
name|GimpDodgeBurnType
name|dodgeburn_type
parameter_list|,
name|GimpTransferMode
name|dodgeburn_mode
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dodgeburn_default
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_eraser
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|,
name|GimpBrushApplicationMode
name|hardness
parameter_list|,
name|GimpPaintApplicationMode
name|method
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_eraser_default
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_heal
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint32
name|src_drawable_ID
parameter_list|,
name|gdouble
name|src_x
parameter_list|,
name|gdouble
name|src_y
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_heal_default
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_paintbrush
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|fade_out
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|,
name|GimpPaintApplicationMode
name|method
parameter_list|,
name|gdouble
name|gradient_length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_paintbrush_default
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_pencil
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_smudge
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|pressure
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_smudge_default
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|strokes
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
comment|/* __GIMP_PAINT_TOOLS_PDB_H__ */
end_comment

end_unit

