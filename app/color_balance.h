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

begin_include
include|#
directive|include
file|"image_map.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2992bda10103
block|{
DECL|enumerator|SHADOWS
name|SHADOWS
block|,
DECL|enumerator|MIDTONES
name|MIDTONES
block|,
DECL|enumerator|HIGHLIGHTS
name|HIGHLIGHTS
DECL|typedef|TransferMode
block|}
name|TransferMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|ColorBalanceDialog
typedef|typedef
name|struct
name|_ColorBalanceDialog
name|ColorBalanceDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_ColorBalanceDialog
struct|struct
name|_ColorBalanceDialog
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|cyan_red_data
name|GtkAdjustment
modifier|*
name|cyan_red_data
decl_stmt|;
DECL|member|magenta_green_data
name|GtkAdjustment
modifier|*
name|magenta_green_data
decl_stmt|;
DECL|member|yellow_blue_data
name|GtkAdjustment
modifier|*
name|yellow_blue_data
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|image_map
name|ImageMap
name|image_map
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
DECL|member|preserve_luminosity
name|gboolean
name|preserve_luminosity
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|member|application_mode
name|TransferMode
name|application_mode
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|Tool
modifier|*
name|tools_new_color_balance
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_free_color_balance
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_balance_initialize
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_balance_dialog_hide
parameter_list|(
name|void
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
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_balance_create_lookup_tables
parameter_list|(
name|ColorBalanceDialog
modifier|*
name|cbd
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

