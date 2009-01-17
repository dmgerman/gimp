begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimppaletteselect_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PALETTE_SELECT_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PALETTE_SELECT_PDB_H__
define|#
directive|define
name|__GIMP_PALETTE_SELECT_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_palettes_popup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|palette_callback
parameter_list|,
specifier|const
name|gchar
modifier|*
name|popup_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|initial_palette
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_palettes_close_popup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|palette_callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_palettes_set_popup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|palette_callback
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette_name
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
comment|/* __GIMP_PALETTE_SELECT_PDB_H__ */
end_comment

end_unit

