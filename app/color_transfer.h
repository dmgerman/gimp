begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__COLOR_TRANSFER_H__
end_ifndef

begin_define
DECL|macro|__COLOR_TRANSFER_H__
define|#
directive|define
name|__COLOR_TRANSFER_H__
end_define

begin_comment
comment|/*************************/
end_comment

begin_comment
comment|/*  color transfer data  */
end_comment

begin_comment
comment|/*  for lightening  */
end_comment

begin_decl_stmt
specifier|extern
name|double
name|highlights_add
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|double
name|midtones_add
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|double
name|shadows_add
index|[]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  for darkening  */
end_comment

begin_decl_stmt
specifier|extern
name|double
name|highlights_sub
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|double
name|midtones_sub
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|double
name|shadows_sub
index|[]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  color transfer functions  */
end_comment

begin_function_decl
name|void
name|color_transfer_init
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
comment|/*  __COLOR_TRANSFER_H__  */
end_comment

end_unit

