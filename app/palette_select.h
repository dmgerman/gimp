begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PALETTE_SELECT_H__
end_ifndef

begin_define
DECL|macro|__PALETTE_SELECT_H__
define|#
directive|define
name|__PALETTE_SELECT_H__
end_define

begin_define
DECL|macro|SM_PREVIEW_WIDTH
define|#
directive|define
name|SM_PREVIEW_WIDTH
value|(96 + 2)
end_define

begin_define
DECL|macro|SM_PREVIEW_HEIGHT
define|#
directive|define
name|SM_PREVIEW_HEIGHT
value|(33 + 2)
end_define

begin_typedef
DECL|typedef|PaletteSelect
DECL|typedef|PaletteSelectP
typedef|typedef
name|struct
name|_PaletteSelect
name|PaletteSelect
typedef|,
modifier|*
name|PaletteSelectP
typedef|;
end_typedef

begin_struct
DECL|struct|_PaletteSelect
struct|struct
name|_PaletteSelect
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|clist
name|GtkWidget
modifier|*
name|clist
decl_stmt|;
DECL|member|gc
name|GdkGC
modifier|*
name|gc
decl_stmt|;
DECL|member|callback_name
name|gchar
modifier|*
name|callback_name
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|PaletteSelect
modifier|*
name|palette_new_selection
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|gchar
modifier|*
name|initial_palette
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palette_select_clist_insert_all
parameter_list|(
name|PaletteEntriesP
name|p_entries
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palette_select_set_text_all
parameter_list|(
name|PaletteEntriesP
name|entries
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palette_select_refresh_all
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PALETTE_SELECT_H__ */
end_comment

end_unit

