begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PALETTE_ENTRIES_H__
end_ifndef

begin_define
DECL|macro|__PALETTE_ENTRIES_H__
define|#
directive|define
name|__PALETTE_ENTRIES_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_typedef
DECL|typedef|PaletteEntries
DECL|typedef|PaletteEntriesP
typedef|typedef
name|struct
name|_PaletteEntries
name|PaletteEntries
typedef|,
modifier|*
name|PaletteEntriesP
typedef|;
end_typedef

begin_struct
DECL|struct|_PaletteEntries
struct|struct
name|_PaletteEntries
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|colors
name|GSList
modifier|*
name|colors
decl_stmt|;
DECL|member|n_colors
name|gint
name|n_colors
decl_stmt|;
DECL|member|changed
name|gboolean
name|changed
decl_stmt|;
DECL|member|pixmap
name|GdkPixmap
modifier|*
name|pixmap
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|PaletteEntry
DECL|typedef|PaletteEntryP
typedef|typedef
name|struct
name|_PaletteEntry
name|PaletteEntry
typedef|,
modifier|*
name|PaletteEntryP
typedef|;
end_typedef

begin_struct
DECL|struct|_PaletteEntry
struct|struct
name|_PaletteEntry
block|{
DECL|member|color
name|guchar
name|color
index|[
literal|3
index|]
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|position
name|gint
name|position
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|palette_entries_list
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PALETTE_ENTRIES_H__ */
end_comment

end_unit

