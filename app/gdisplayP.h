begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GDISPLAYP_H__
end_ifndef

begin_define
DECL|macro|__GDISPLAYP_H__
define|#
directive|define
name|__GDISPLAYP_H__
end_define

begin_typedef
DECL|typedef|GimpArea
typedef|typedef
name|struct
name|_GimpArea
name|GimpArea
typedef|;
end_typedef

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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GDISPLAYP_H__  */
end_comment

end_unit

