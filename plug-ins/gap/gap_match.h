begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  gap_match.h  *  * GAP ... Gimp Animation Plugins  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * version 0.97.00  1998.10.14  hof: - created module   */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GAP_MATCH_H
end_ifndef

begin_define
DECL|macro|_GAP_MATCH_H
define|#
directive|define
name|_GAP_MATCH_H
end_define

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_define
DECL|macro|MTCH_EQUAL
define|#
directive|define
name|MTCH_EQUAL
value|0
end_define

begin_define
DECL|macro|MTCH_START
define|#
directive|define
name|MTCH_START
value|1
end_define

begin_define
DECL|macro|MTCH_END
define|#
directive|define
name|MTCH_END
value|2
end_define

begin_define
DECL|macro|MTCH_ANYWHERE
define|#
directive|define
name|MTCH_ANYWHERE
value|3
end_define

begin_define
DECL|macro|MTCH_NUMBERLIST
define|#
directive|define
name|MTCH_NUMBERLIST
value|4
end_define

begin_define
DECL|macro|MTCH_INV_NUMBERLIST
define|#
directive|define
name|MTCH_INV_NUMBERLIST
value|5
end_define

begin_define
DECL|macro|MTCH_ALL_VISIBLE
define|#
directive|define
name|MTCH_ALL_VISIBLE
value|6
end_define

begin_function_decl
name|int
name|p_is_empty
parameter_list|(
name|char
modifier|*
name|str
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|p_substitute_framenr
parameter_list|(
name|char
modifier|*
name|buffer
parameter_list|,
name|int
name|buff_len
parameter_list|,
name|char
modifier|*
name|new_layername
parameter_list|,
name|long
name|curr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|str_toupper
parameter_list|(
name|char
modifier|*
name|str
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_match_number
parameter_list|(
name|gint32
name|layer_id
parameter_list|,
name|char
modifier|*
name|pattern
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_match_name
parameter_list|(
name|char
modifier|*
name|layername
parameter_list|,
name|char
modifier|*
name|pattern
parameter_list|,
name|gint32
name|mode
parameter_list|,
name|gint32
name|case_sensitive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_match_layer
parameter_list|(
name|gint32
name|layer_idx
parameter_list|,
name|char
modifier|*
name|layername
parameter_list|,
name|char
modifier|*
name|pattern
parameter_list|,
name|gint32
name|mode
parameter_list|,
name|gint32
name|case_sensitive
parameter_list|,
name|gint32
name|invert
parameter_list|,
name|gint
name|nlayers
parameter_list|,
name|gint32
name|layer_id
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

