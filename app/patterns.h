begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PATTERNS_H__
end_ifndef

begin_define
DECL|macro|__PATTERNS_H__
define|#
directive|define
name|__PATTERNS_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_typedef
DECL|typedef|GPattern
DECL|typedef|GPatternP
typedef|typedef
name|struct
name|_GPattern
name|GPattern
typedef|,
modifier|*
name|GPatternP
typedef|;
end_typedef

begin_struct
DECL|struct|_GPattern
struct|struct
name|_GPattern
block|{
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
comment|/*  actual filename--pattern's location on disk   */
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/*  pattern's name--for pattern selection dialog  */
DECL|member|index
name|gint
name|index
decl_stmt|;
comment|/*  pattern's index...                            */
DECL|member|mask
name|TempBuf
modifier|*
name|mask
decl_stmt|;
comment|/*  the actual mask...                            */
block|}
struct|;
end_struct

begin_comment
comment|/*  function declarations  */
end_comment

begin_function_decl
name|void
name|patterns_init
parameter_list|(
name|gboolean
name|no_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|patterns_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|select_pattern
parameter_list|(
name|GPatternP
name|pattern
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GPatternP
name|get_pattern_by_index
parameter_list|(
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GPatternP
name|get_active_pattern
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GPatternP
name|pattern_list_get_pattern
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|create_pattern_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pattern_select_dialog_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  global variables  */
end_comment

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|pattern_list
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|num_patterns
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PATTERNS_H__  */
end_comment

end_unit

