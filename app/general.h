begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GENERAL_H__
end_ifndef

begin_define
DECL|macro|__GENERAL_H__
define|#
directive|define
name|__GENERAL_H__
end_define

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_define
DECL|macro|TOKEN_EOF
define|#
directive|define
name|TOKEN_EOF
value|0
end_define

begin_define
DECL|macro|TOKEN_LEFT_PAREN
define|#
directive|define
name|TOKEN_LEFT_PAREN
value|1
end_define

begin_define
DECL|macro|TOKEN_RIGHT_PAREN
define|#
directive|define
name|TOKEN_RIGHT_PAREN
value|2
end_define

begin_define
DECL|macro|TOKEN_SYMBOL
define|#
directive|define
name|TOKEN_SYMBOL
value|3
end_define

begin_define
DECL|macro|TOKEN_STRING
define|#
directive|define
name|TOKEN_STRING
value|4
end_define

begin_define
DECL|macro|TOKEN_NUMBER
define|#
directive|define
name|TOKEN_NUMBER
value|5
end_define

begin_typedef
DECL|typedef|ParseInfo
typedef|typedef
name|struct
name|_ParseInfo
name|ParseInfo
typedef|;
end_typedef

begin_struct
DECL|struct|_ParseInfo
struct|struct
name|_ParseInfo
block|{
DECL|member|fp
name|FILE
modifier|*
name|fp
decl_stmt|;
DECL|member|buffer
name|char
modifier|*
name|buffer
decl_stmt|;
DECL|member|tokenbuf
name|char
modifier|*
name|tokenbuf
decl_stmt|;
DECL|member|linenum
name|int
name|linenum
decl_stmt|;
DECL|member|charnum
name|int
name|charnum
decl_stmt|;
DECL|member|position
name|int
name|position
decl_stmt|;
DECL|member|buffer_size
name|int
name|buffer_size
decl_stmt|;
DECL|member|tokenbuf_size
name|int
name|tokenbuf_size
decl_stmt|;
DECL|member|inc_linenum
name|unsigned
name|int
name|inc_linenum
range|:
literal|1
decl_stmt|;
DECL|member|inc_charnum
name|unsigned
name|int
name|inc_charnum
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|char
modifier|*
name|search_in_path
parameter_list|(
name|char
modifier|*
parameter_list|,
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|xstrsep
parameter_list|(
name|char
modifier|*
modifier|*
name|p
parameter_list|,
name|char
modifier|*
name|delim
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|get_token
parameter_list|(
name|ParseInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|find_token
parameter_list|(
name|char
modifier|*
name|line
parameter_list|,
name|char
modifier|*
name|token_r
parameter_list|,
name|int
name|maxlen
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|iso_8601_date_format
parameter_list|(
name|char
modifier|*
name|user_buf
parameter_list|,
name|int
name|strict
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|char
modifier|*
name|token_str
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|char
modifier|*
name|token_sym
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|double
name|token_num
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|token_int
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GENERAL_H__ */
end_comment

end_unit

