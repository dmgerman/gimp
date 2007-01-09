begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpconvert_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONVERT_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONVERT_PDB_H__
define|#
directive|define
name|__GIMP_CONVERT_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_image_convert_rgb
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_convert_grayscale
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_convert_indexed
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpConvertDitherType
name|dither_type
parameter_list|,
name|GimpConvertPaletteType
name|palette_type
parameter_list|,
name|gint
name|num_cols
parameter_list|,
name|gboolean
name|alpha_dither
parameter_list|,
name|gboolean
name|remove_unused
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_convert_set_dither_matrix
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|matrix_length
parameter_list|,
specifier|const
name|guint8
modifier|*
name|matrix
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
comment|/* __GIMP_CONVERT_PDB_H__ */
end_comment

end_unit

