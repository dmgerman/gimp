begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__IMAGE_RENDER_H__
end_ifndef

begin_define
DECL|macro|__IMAGE_RENDER_H__
define|#
directive|define
name|__IMAGE_RENDER_H__
end_define

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_comment
comment|/*  Transparency representation  */
end_comment

begin_define
DECL|macro|LIGHT_CHECKS
define|#
directive|define
name|LIGHT_CHECKS
value|0
end_define

begin_define
DECL|macro|GRAY_CHECKS
define|#
directive|define
name|GRAY_CHECKS
value|1
end_define

begin_define
DECL|macro|DARK_CHECKS
define|#
directive|define
name|DARK_CHECKS
value|2
end_define

begin_define
DECL|macro|WHITE_ONLY
define|#
directive|define
name|WHITE_ONLY
value|3
end_define

begin_define
DECL|macro|GRAY_ONLY
define|#
directive|define
name|GRAY_ONLY
value|4
end_define

begin_define
DECL|macro|BLACK_ONLY
define|#
directive|define
name|BLACK_ONLY
value|5
end_define

begin_define
DECL|macro|SMALL_CHECKS
define|#
directive|define
name|SMALL_CHECKS
value|0
end_define

begin_define
DECL|macro|MEDIUM_CHECKS
define|#
directive|define
name|MEDIUM_CHECKS
value|1
end_define

begin_define
DECL|macro|LARGE_CHECKS
define|#
directive|define
name|LARGE_CHECKS
value|2
end_define

begin_comment
comment|/*  Functions  */
end_comment

begin_function_decl
name|void
name|render_setup
parameter_list|(
name|int
name|check_type
parameter_list|,
name|int
name|check_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|render_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|render_image
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  *  Extern variables  */
end_comment

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|check_buf
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|empty_buf
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|temp_buf
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|blend_dark_check
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|blend_light_check
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __IMAGE_RENDER_H__  */
end_comment

end_unit

