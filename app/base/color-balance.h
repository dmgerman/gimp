begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__COLOR_BALANCE_H__
end_ifndef

begin_define
DECL|macro|__COLOR_BALANCE_H__
define|#
directive|define
name|__COLOR_BALANCE_H__
end_define

begin_struct
DECL|struct|_ColorBalance
struct|struct
name|_ColorBalance
block|{
DECL|member|preserve_luminosity
name|gboolean
name|preserve_luminosity
decl_stmt|;
DECL|member|cyan_red
name|gdouble
name|cyan_red
index|[
literal|3
index|]
decl_stmt|;
DECL|member|magenta_green
name|gdouble
name|magenta_green
index|[
literal|3
index|]
decl_stmt|;
DECL|member|yellow_blue
name|gdouble
name|yellow_blue
index|[
literal|3
index|]
decl_stmt|;
DECL|member|r_lookup
name|guchar
name|r_lookup
index|[
literal|256
index|]
decl_stmt|;
DECL|member|g_lookup
name|guchar
name|g_lookup
index|[
literal|256
index|]
decl_stmt|;
DECL|member|b_lookup
name|guchar
name|b_lookup
index|[
literal|256
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|color_balance_create_lookup_tables
parameter_list|(
name|ColorBalance
modifier|*
name|cb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_balance
parameter_list|(
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __COLOR_BALANCE_H__  */
end_comment

end_unit

