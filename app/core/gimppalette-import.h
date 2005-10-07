begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PALETTE_IMPORT__
end_ifndef

begin_define
DECL|macro|__GIMP_PALETTE_IMPORT__
define|#
directive|define
name|__GIMP_PALETTE_IMPORT__
end_define

begin_function_decl
name|GimpPalette
modifier|*
name|gimp_palette_import_from_gradient
parameter_list|(
name|GimpGradient
modifier|*
name|gradient
parameter_list|,
name|gboolean
name|reverse
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette_name
parameter_list|,
name|gint
name|n_colors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPalette
modifier|*
name|gimp_palette_import_from_image
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette_name
parameter_list|,
name|gint
name|n_colors
parameter_list|,
name|gint
name|treshold
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPalette
modifier|*
name|gimp_palette_import_from_indexed_image
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPalette
modifier|*
name|gimp_palette_import_from_drawable
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette_name
parameter_list|,
name|gint
name|n_colors
parameter_list|,
name|gint
name|threshold
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPalette
modifier|*
name|gimp_palette_import_from_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette_name
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PALETTE_IMPORT_H__ */
end_comment

end_unit

