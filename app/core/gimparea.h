begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_AREA_H__
end_ifndef

begin_define
DECL|macro|__GIMP_AREA_H__
define|#
directive|define
name|__GIMP_AREA_H__
end_define

begin_struct
DECL|struct|_GimpArea
struct|struct
name|_GimpArea
block|{
DECL|member|x1
DECL|member|y1
DECL|member|x2
DECL|member|y2
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  area bounds  */
block|}
struct|;
end_struct

begin_function_decl
name|GimpArea
modifier|*
name|gimp_area_new
parameter_list|(
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GSList
modifier|*
name|gimp_area_list_process
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|,
name|GimpArea
modifier|*
name|area
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GSList
modifier|*
name|gimp_area_list_free
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_AREA_H__  */
end_comment

end_unit

