begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__RECT_SELECTP_H__
end_ifndef

begin_define
DECL|macro|__RECT_SELECTP_H__
define|#
directive|define
name|__RECT_SELECTP_H__
end_define

begin_include
include|#
directive|include
file|"draw_core.h"
end_include

begin_typedef
DECL|typedef|RectSelect
DECL|typedef|EllipseSelect
typedef|typedef
name|struct
name|_RectSelect
name|RectSelect
typedef|,
name|EllipseSelect
typedef|;
end_typedef

begin_struct
DECL|struct|_RectSelect
struct|struct
name|_RectSelect
block|{
DECL|member|core
name|DrawCore
modifier|*
name|core
decl_stmt|;
comment|/*  Core select object  */
DECL|member|op
name|SelectOps
name|op
decl_stmt|;
comment|/*  selection operation (SELECTION_ADD etc.)  */
DECL|member|current_x
name|gint
name|current_x
decl_stmt|;
comment|/*  these values are updated on every motion event  */
DECL|member|current_y
name|gint
name|current_y
decl_stmt|;
comment|/*  (enables immediate cursor updating on modifier 			   *   key events).  */
DECL|member|x
DECL|member|y
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  upper left hand coordinate  */
DECL|member|w
DECL|member|h
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
comment|/*  width and height  */
DECL|member|center
name|gint
name|center
decl_stmt|;
comment|/*  is the selection being created from the 			    *  center out?  */
DECL|member|fixed_size
name|gint
name|fixed_size
decl_stmt|;
DECL|member|fixed_width
name|gdouble
name|fixed_width
decl_stmt|;
DECL|member|fixed_height
name|gdouble
name|fixed_height
decl_stmt|;
DECL|member|context_id
name|guint
name|context_id
decl_stmt|;
comment|/*  for the statusbar  */
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __RECT_SELECTP_H__  */
end_comment

end_unit

