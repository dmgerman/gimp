begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimppalette_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PALETTE_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PALETTE_PDB_H__
define|#
directive|define
name|__GIMP_PALETTE_PDB_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_palette_get_foreground
parameter_list|(
name|guchar
modifier|*
name|red
parameter_list|,
name|guchar
modifier|*
name|green
parameter_list|,
name|guchar
modifier|*
name|blue
parameter_list|)
function_decl|;
name|gboolean
name|gimp_palette_get_background
parameter_list|(
name|guchar
modifier|*
name|red
parameter_list|,
name|guchar
modifier|*
name|green
parameter_list|,
name|guchar
modifier|*
name|blue
parameter_list|)
function_decl|;
name|gboolean
name|gimp_palette_set_foreground
parameter_list|(
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|)
function_decl|;
name|gboolean
name|gimp_palette_set_background
parameter_list|(
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|)
function_decl|;
name|gboolean
name|gimp_palette_set_default_colors
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|gboolean
name|gimp_palette_swap_colors
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|gboolean
name|gimp_palette_refresh
parameter_list|(
name|void
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PALETTE_PDB_H__ */
end_comment

end_unit

