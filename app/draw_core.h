begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DRAW_CORE_H__
end_ifndef

begin_define
DECL|macro|__DRAW_CORE_H__
define|#
directive|define
name|__DRAW_CORE_H__
end_define

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_comment
comment|/*  drawing states  */
end_comment

begin_define
DECL|macro|INVISIBLE
define|#
directive|define
name|INVISIBLE
value|0
end_define

begin_define
DECL|macro|VISIBLE
define|#
directive|define
name|VISIBLE
value|1
end_define

begin_comment
comment|/*  Structure definitions  */
end_comment

begin_typedef
DECL|typedef|DrawCore
typedef|typedef
name|struct
name|_draw_core
name|DrawCore
typedef|;
end_typedef

begin_typedef
DECL|typedef|DrawCoreDraw
typedef|typedef
name|void
function_decl|(
modifier|*
name|DrawCoreDraw
function_decl|)
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|_draw_core
struct|struct
name|_draw_core
block|{
DECL|member|gc
name|GdkGC
modifier|*
name|gc
decl_stmt|;
comment|/*  Grahpics context for drawing functions  */
DECL|member|win
name|GdkWindow
modifier|*
name|win
decl_stmt|;
comment|/*  Window to draw draw operation to      */
DECL|member|draw_state
name|int
name|draw_state
decl_stmt|;
comment|/*  Current state in the drawing process    */
DECL|member|line_width
name|int
name|line_width
decl_stmt|;
comment|/**/
DECL|member|line_style
name|int
name|line_style
decl_stmt|;
comment|/**/
DECL|member|cap_style
name|int
name|cap_style
decl_stmt|;
comment|/*  line attributes                         */
DECL|member|join_style
name|int
name|join_style
decl_stmt|;
comment|/**/
DECL|member|paused_count
name|int
name|paused_count
decl_stmt|;
comment|/*  count to keep track of multiple pauses  */
DECL|member|data
name|gpointer
name|data
decl_stmt|;
comment|/*  data to pass to draw_func               */
DECL|member|draw_func
name|DrawCoreDraw
name|draw_func
decl_stmt|;
comment|/*  Member function for actual drawing      */
block|}
struct|;
end_struct

begin_comment
comment|/*  draw core functions  */
end_comment

begin_function_decl
name|DrawCore
modifier|*
name|draw_core_new
parameter_list|(
name|DrawCoreDraw
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|draw_core_start
parameter_list|(
name|DrawCore
modifier|*
parameter_list|,
name|GdkWindow
modifier|*
parameter_list|,
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|draw_core_stop
parameter_list|(
name|DrawCore
modifier|*
parameter_list|,
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|draw_core_pause
parameter_list|(
name|DrawCore
modifier|*
parameter_list|,
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|draw_core_resume
parameter_list|(
name|DrawCore
modifier|*
parameter_list|,
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|draw_core_free
parameter_list|(
name|DrawCore
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __DRAW_CORE_H__  */
end_comment

end_unit

