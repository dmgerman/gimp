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

begin_comment
comment|/*  The states for updating a color in the palette via palette_set_* calls */
end_comment

begin_define
DECL|macro|COLOR_NEW
define|#
directive|define
name|COLOR_NEW
value|0
end_define

begin_define
DECL|macro|COLOR_UPDATE_NEW
define|#
directive|define
name|COLOR_UPDATE_NEW
value|1
end_define

begin_define
DECL|macro|COLOR_UPDATE
define|#
directive|define
name|COLOR_UPDATE
value|2
end_define

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
name|palette_set_active_color
parameter_list|(
name|gint
name|r
parameter_list|,
name|gint
name|g
parameter_list|,
name|gint
name|b
parameter_list|,
name|gint
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

