begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__THRESHOLD_H__
end_ifndef

begin_define
DECL|macro|__THRESHOLD_H__
define|#
directive|define
name|__THRESHOLD_H__
end_define

begin_struct
DECL|struct|_Threshold
struct|struct
name|_Threshold
block|{
DECL|member|color
name|gboolean
name|color
decl_stmt|;
DECL|member|low_threshold
name|gint
name|low_threshold
decl_stmt|;
DECL|member|high_threshold
name|gint
name|high_threshold
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|threshold
parameter_list|(
name|Threshold
modifier|*
name|tr
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __THRESHOLD_H__  */
end_comment

end_unit

