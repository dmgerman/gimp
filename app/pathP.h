begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Andy Thomas alt@picnic.demon.co.uk  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PATHP_H__
end_ifndef

begin_define
DECL|macro|__PATHP_H__
define|#
directive|define
name|__PATHP_H__
end_define

begin_include
include|#
directive|include
file|"gimpimageF.h"
end_include

begin_comment
comment|/* Tattoo   */
end_comment

begin_struct
DECL|struct|_PathPoint
struct|struct
name|_PathPoint
block|{
DECL|member|type
name|guint32
name|type
decl_stmt|;
DECL|member|x
name|gdouble
name|x
decl_stmt|;
DECL|member|y
name|gdouble
name|y
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_Path
struct|struct
name|_Path
block|{
DECL|member|path_details
name|GSList
modifier|*
name|path_details
decl_stmt|;
DECL|member|pathtype
name|gint
name|pathtype
decl_stmt|;
comment|/* Only beziers to start with */
DECL|member|closed
name|gboolean
name|closed
decl_stmt|;
DECL|member|state
name|guint32
name|state
decl_stmt|;
DECL|member|locked
name|guint32
name|locked
decl_stmt|;
comment|/* Only bottom bit used */
DECL|member|tattoo
name|Tattoo
name|tattoo
decl_stmt|;
comment|/* The tattoo for the path */
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|gboolean
name|path_set_path
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gchar
modifier|*
name|pname
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|path_set_path_points
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gchar
modifier|*
name|pname
parameter_list|,
name|gint
name|ptype
parameter_list|,
name|gint
name|pclosed
parameter_list|,
name|gint
name|num_pnts
parameter_list|,
name|gdouble
modifier|*
name|pnts
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|path_delete_path
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gchar
modifier|*
name|pname
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GSList
modifier|*
name|pathpoints_copy
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pathpoints_free
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
comment|/*  __PATHP_H__  */
end_comment

end_unit

