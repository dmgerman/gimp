begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__HUE_SATURATION_H__
end_ifndef

begin_define
DECL|macro|__HUE_SATURATION_H__
define|#
directive|define
name|__HUE_SATURATION_H__
end_define

begin_struct
DECL|struct|_HueSaturation
struct|struct
name|_HueSaturation
block|{
DECL|member|hue
name|gdouble
name|hue
index|[
literal|7
index|]
decl_stmt|;
DECL|member|lightness
name|gdouble
name|lightness
index|[
literal|7
index|]
decl_stmt|;
DECL|member|saturation
name|gdouble
name|saturation
index|[
literal|7
index|]
decl_stmt|;
DECL|member|hue_transfer
name|gint
name|hue_transfer
index|[
literal|6
index|]
index|[
literal|256
index|]
decl_stmt|;
DECL|member|lightness_transfer
name|gint
name|lightness_transfer
index|[
literal|6
index|]
index|[
literal|256
index|]
decl_stmt|;
DECL|member|saturation_transfer
name|gint
name|saturation_transfer
index|[
literal|6
index|]
index|[
literal|256
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|hue_saturation_calculate_transfers
parameter_list|(
name|HueSaturation
modifier|*
name|hs
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|hue_saturation
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
comment|/*  __HUE_SATURATION_H__  */
end_comment

end_unit

