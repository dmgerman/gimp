begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_RENDER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RENDER_H__
define|#
directive|define
name|__GIMP_RENDER_H__
end_define

begin_define
DECL|macro|GIMP_RENDER_BUF_WIDTH
define|#
directive|define
name|GIMP_RENDER_BUF_WIDTH
value|256
end_define

begin_define
DECL|macro|GIMP_RENDER_BUF_HEIGHT
define|#
directive|define
name|GIMP_RENDER_BUF_HEIGHT
value|256
end_define

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|gimp_render_check_buf
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|gimp_render_empty_buf
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|gimp_render_white_buf
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|gimp_render_temp_buf
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|gimp_render_blend_dark_check
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|gimp_render_blend_light_check
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|gimp_render_blend_white
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_render_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_render_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_RENDER_H__ */
end_comment

end_unit

