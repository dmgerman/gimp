begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TILE_ROWHINTS_H__
end_ifndef

begin_define
DECL|macro|__TILE_ROWHINTS_H__
define|#
directive|define
name|__TILE_ROWHINTS_H__
end_define

begin_comment
comment|/*  * Explicit guchar type rather than enum since gcc chooses an int  * representation but arrays of TileRowHints are quite space-critical  * in GIMP.  */
end_comment

begin_typedef
DECL|typedef|TileRowHint
typedef|typedef
name|guchar
name|TileRowHint
typedef|;
end_typedef

begin_define
DECL|macro|TILEROWHINT_UNKNOWN
define|#
directive|define
name|TILEROWHINT_UNKNOWN
value|0
end_define

begin_define
DECL|macro|TILEROWHINT_OPAQUE
define|#
directive|define
name|TILEROWHINT_OPAQUE
value|1
end_define

begin_define
DECL|macro|TILEROWHINT_TRANSPARENT
define|#
directive|define
name|TILEROWHINT_TRANSPARENT
value|2
end_define

begin_define
DECL|macro|TILEROWHINT_MIXED
define|#
directive|define
name|TILEROWHINT_MIXED
value|3
end_define

begin_define
DECL|macro|TILEROWHINT_OUTOFRANGE
define|#
directive|define
name|TILEROWHINT_OUTOFRANGE
value|4
end_define

begin_define
DECL|macro|TILEROWHINT_UNDEFINED
define|#
directive|define
name|TILEROWHINT_UNDEFINED
value|5
end_define

begin_define
DECL|macro|TILEROWHINT_BROKEN
define|#
directive|define
name|TILEROWHINT_BROKEN
value|6
end_define

begin_function_decl
name|TileRowHint
name|tile_get_rowhint
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|gint
name|yoff
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_set_rowhint
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|gint
name|yoff
parameter_list|,
name|TileRowHint
name|rowhint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_allocate_rowhints
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tile_update_rowhints
parameter_list|(
name|Tile
modifier|*
name|tile
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|rows
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TILE_ROWHINTS_H__ */
end_comment

end_unit

