begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__RECT_SELECT_H__
end_ifndef

begin_define
DECL|macro|__RECT_SELECT_H__
define|#
directive|define
name|__RECT_SELECT_H__
end_define

begin_include
include|#
directive|include
file|"gimpimageF.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"channel.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2be59a820103
block|{
DECL|enumerator|SELECTION_ADD
name|SELECTION_ADD
init|=
name|ADD
block|,
DECL|enumerator|SELECTION_SUB
name|SELECTION_SUB
init|=
name|SUB
block|,
DECL|enumerator|SELECTION_REPLACE
name|SELECTION_REPLACE
init|=
name|REPLACE
block|,
DECL|enumerator|SELECTION_INTERSECT
name|SELECTION_INTERSECT
init|=
name|INTERSECT
block|,
DECL|enumerator|SELECTION_MOVE_MASK
name|SELECTION_MOVE_MASK
block|,
DECL|enumerator|SELECTION_MOVE
name|SELECTION_MOVE
DECL|typedef|SelectOps
block|}
name|SelectOps
typedef|;
end_typedef

begin_comment
comment|/*  rect select action functions  */
end_comment

begin_function_decl
name|void
name|rect_select_button_press
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventButton
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rect_select_button_release
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventButton
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rect_select_motion
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rect_select_cursor_update
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rect_select_control
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|int
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  rect select functions  */
end_comment

begin_function_decl
name|void
name|rect_select_draw
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rect_select
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tool
modifier|*
name|tools_new_rect_select
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_free_rect_select
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __RECT_SELECT_H__  */
end_comment

end_unit

