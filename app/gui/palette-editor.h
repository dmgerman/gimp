begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PALETTE_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__PALETTE_EDITOR_H__
define|#
directive|define
name|__PALETTE_EDITOR_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae17a8b0103
block|{
DECL|enumerator|GIMP_UPDATE_COLOR_STATE_NEW
name|GIMP_UPDATE_COLOR_STATE_NEW
block|,
DECL|enumerator|GIMP_UPDATE_COLOR_STATE_UPDATE_NEW
name|GIMP_UPDATE_COLOR_STATE_UPDATE_NEW
block|,
DECL|enumerator|GIMP_UPDATE_COLOR_STATE_UPDATE
name|GIMP_UPDATE_COLOR_STATE_UPDATE
DECL|typedef|GimpUpdateColorState
block|}
name|GimpUpdateColorState
typedef|;
end_typedef

begin_typedef
DECL|typedef|PaletteEditor
typedef|typedef
name|struct
name|_PaletteEditor
name|PaletteEditor
typedef|;
end_typedef

begin_function_decl
name|PaletteEditor
modifier|*
name|palette_editor_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palette_editor_set_palette
parameter_list|(
name|PaletteEditor
modifier|*
name|palette_editor
parameter_list|,
name|GimpPalette
modifier|*
name|palette
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palette_editor_free
parameter_list|(
name|PaletteEditor
modifier|*
name|palette_editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palette_editor_update_color
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpUpdateColorState
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PALETTE_EDITOR_H__ */
end_comment

end_unit

