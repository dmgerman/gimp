begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PALETTE_H__
end_ifndef

begin_define
DECL|macro|__PALETTE_H__
define|#
directive|define
name|__PALETTE_H__
end_define

begin_define
DECL|macro|FOREGROUND
define|#
directive|define
name|FOREGROUND
value|0
end_define

begin_define
DECL|macro|BACKGROUND
define|#
directive|define
name|BACKGROUND
value|1
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

begin_function_decl
name|void
name|palettes_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palettes_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palette_create
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palette_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palette_get_foreground
parameter_list|(
name|unsigned
name|char
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palette_get_background
parameter_list|(
name|unsigned
name|char
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palette_set_foreground
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palette_set_background
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palette_set_active_color
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_struct
DECL|struct|_PaletteEntries
struct|struct
name|_PaletteEntries
block|{
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|filename
name|char
modifier|*
name|filename
decl_stmt|;
DECL|member|colors
name|link_ptr
name|colors
decl_stmt|;
DECL|member|n_colors
name|int
name|n_colors
decl_stmt|;
DECL|member|changed
name|int
name|changed
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|_PaletteEntries
DECL|typedef|PaletteEntriesP
typedef|typedef
name|struct
name|_PaletteEntries
name|_PaletteEntries
typedef|,
modifier|*
name|PaletteEntriesP
typedef|;
end_typedef

begin_struct
DECL|struct|_PaletteEntry
struct|struct
name|_PaletteEntry
block|{
DECL|member|color
name|unsigned
name|char
name|color
index|[
literal|3
index|]
decl_stmt|;
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|position
name|int
name|position
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|_PaletteEntry
DECL|typedef|PaletteEntryP
typedef|typedef
name|struct
name|_PaletteEntry
name|_PaletteEntry
typedef|,
modifier|*
name|PaletteEntryP
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|link_ptr
name|palette_entries_list
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|palette_init_palettes
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|palette_free_palettes
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_comment
comment|/*  Procedure definition and marshalling function  */
end_comment

begin_decl_stmt
specifier|extern
name|ProcRecord
name|palette_get_foreground_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|palette_get_background_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|palette_set_foreground_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|palette_set_background_proc
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PALETTE_H__ */
end_comment

end_unit

