begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TRANSFORM_CORE_H__
end_ifndef

begin_define
DECL|macro|__TRANSFORM_CORE_H__
define|#
directive|define
name|__TRANSFORM_CORE_H__
end_define

begin_include
include|#
directive|include
file|"info_dialog.h"
end_include

begin_include
include|#
directive|include
file|"draw_core.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_comment
comment|/* possible scaling functions */
end_comment

begin_define
DECL|macro|CREATING
define|#
directive|define
name|CREATING
value|0
end_define

begin_define
DECL|macro|HANDLE_1
define|#
directive|define
name|HANDLE_1
value|1
end_define

begin_define
DECL|macro|HANDLE_2
define|#
directive|define
name|HANDLE_2
value|2
end_define

begin_define
DECL|macro|HANDLE_3
define|#
directive|define
name|HANDLE_3
value|3
end_define

begin_define
DECL|macro|HANDLE_4
define|#
directive|define
name|HANDLE_4
value|4
end_define

begin_comment
comment|/* the different states that the transformation function can be called with  */
end_comment

begin_define
DECL|macro|INIT
define|#
directive|define
name|INIT
value|0
end_define

begin_define
DECL|macro|MOTION
define|#
directive|define
name|MOTION
value|1
end_define

begin_define
DECL|macro|RECALC
define|#
directive|define
name|RECALC
value|2
end_define

begin_define
DECL|macro|FINISH
define|#
directive|define
name|FINISH
value|3
end_define

begin_comment
comment|/* buffer sizes for scaling information strings (for the info dialog) */
end_comment

begin_define
DECL|macro|MAX_INFO_BUF
define|#
directive|define
name|MAX_INFO_BUF
value|12
end_define

begin_define
DECL|macro|TRAN_INFO_SIZE
define|#
directive|define
name|TRAN_INFO_SIZE
value|8
end_define

begin_comment
comment|/* control whether the transform tool draws a bounding box */
end_comment

begin_define
DECL|macro|NON_INTERACTIVE
define|#
directive|define
name|NON_INTERACTIVE
value|0
end_define

begin_define
DECL|macro|INTERACTIVE
define|#
directive|define
name|INTERACTIVE
value|1
end_define

begin_typedef
DECL|typedef|Vector
typedef|typedef
name|double
name|Vector
index|[
literal|3
index|]
typedef|;
end_typedef

begin_typedef
DECL|typedef|Matrix
typedef|typedef
name|Vector
name|Matrix
index|[
literal|3
index|]
typedef|;
end_typedef

begin_typedef
DECL|typedef|TranInfo
typedef|typedef
name|double
name|TranInfo
index|[
name|TRAN_INFO_SIZE
index|]
typedef|;
end_typedef

begin_typedef
DECL|typedef|TransformFunc
typedef|typedef
name|void
modifier|*
function_decl|(
modifier|*
name|TransformFunc
function_decl|)
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|TransformCore
typedef|typedef
name|struct
name|_transform_core
name|TransformCore
typedef|;
end_typedef

begin_struct
DECL|struct|_transform_core
struct|struct
name|_transform_core
block|{
DECL|member|core
name|DrawCore
modifier|*
name|core
decl_stmt|;
comment|/*  Core select object          */
DECL|member|startx
name|int
name|startx
decl_stmt|;
comment|/*  starting x coord            */
DECL|member|starty
name|int
name|starty
decl_stmt|;
comment|/*  starting y coord            */
DECL|member|curx
name|int
name|curx
decl_stmt|;
comment|/*  current x coord             */
DECL|member|cury
name|int
name|cury
decl_stmt|;
comment|/*  current y coord             */
DECL|member|lastx
name|int
name|lastx
decl_stmt|;
comment|/*  last x coord                */
DECL|member|lasty
name|int
name|lasty
decl_stmt|;
comment|/*  last y coord                */
DECL|member|state
name|int
name|state
decl_stmt|;
comment|/*  state of buttons and keys   */
DECL|member|x1
DECL|member|y1
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  upper left hand coordinate  */
DECL|member|x2
DECL|member|y2
name|int
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  lower right hand coords     */
DECL|member|tx1
DECL|member|ty1
name|double
name|tx1
decl_stmt|,
name|ty1
decl_stmt|;
comment|/*  transformed coords          */
DECL|member|tx2
DECL|member|ty2
name|double
name|tx2
decl_stmt|,
name|ty2
decl_stmt|;
comment|/*                              */
DECL|member|tx3
DECL|member|ty3
name|double
name|tx3
decl_stmt|,
name|ty3
decl_stmt|;
comment|/*                              */
DECL|member|tx4
DECL|member|ty4
name|double
name|tx4
decl_stmt|,
name|ty4
decl_stmt|;
comment|/*                              */
DECL|member|sx1
DECL|member|sy1
name|int
name|sx1
decl_stmt|,
name|sy1
decl_stmt|;
comment|/*  transformed screen coords   */
DECL|member|sx2
DECL|member|sy2
name|int
name|sx2
decl_stmt|,
name|sy2
decl_stmt|;
comment|/*  position of four handles    */
DECL|member|sx3
DECL|member|sy3
name|int
name|sx3
decl_stmt|,
name|sy3
decl_stmt|;
comment|/*                              */
DECL|member|sx4
DECL|member|sy4
name|int
name|sx4
decl_stmt|,
name|sy4
decl_stmt|;
comment|/*                              */
DECL|member|transform
name|Matrix
name|transform
decl_stmt|;
comment|/*  transformation matrix       */
DECL|member|trans_info
name|TranInfo
name|trans_info
decl_stmt|;
comment|/*  transformation info         */
DECL|member|original
name|TileManager
modifier|*
name|original
decl_stmt|;
comment|/*  pointer to original tiles   */
DECL|member|trans_func
name|TransformFunc
name|trans_func
decl_stmt|;
comment|/*  transformation function     */
DECL|member|function
name|int
name|function
decl_stmt|;
comment|/*  current tool activity       */
DECL|member|interactive
name|int
name|interactive
decl_stmt|;
comment|/*  tool is interactive         */
DECL|member|bpressed
name|int
name|bpressed
decl_stmt|;
comment|/* Bug work around make sure we have  				 * a button pressed before we deal with 				 * motion events. ALT. 				 */
block|}
struct|;
end_struct

begin_comment
comment|/*  Special undo type  */
end_comment

begin_typedef
DECL|typedef|TransformUndo
typedef|typedef
name|struct
name|_transform_undo
name|TransformUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_transform_undo
struct|struct
name|_transform_undo
block|{
DECL|member|tool_ID
name|int
name|tool_ID
decl_stmt|;
DECL|member|tool_type
name|int
name|tool_type
decl_stmt|;
DECL|member|trans_info
name|TranInfo
name|trans_info
decl_stmt|;
DECL|member|first
name|int
name|first
decl_stmt|;
DECL|member|original
name|TileManager
modifier|*
name|original
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  make this variable available to all  */
end_comment

begin_decl_stmt
specifier|extern
name|InfoDialog
modifier|*
name|transform_info
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  transform tool action functions  */
end_comment

begin_function_decl
name|void
name|transform_core_button_press
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
name|transform_core_button_release
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
name|transform_core_motion
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
name|transform_core_cursor_update
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
name|transform_core_control
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
comment|/*  transform tool functions  */
end_comment

begin_function_decl
name|void
name|transform_core_draw
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|transform_core_no_draw
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tool
modifier|*
name|transform_core_new
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|transform_core_free
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|transform_core_reset
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  transform functions  */
end_comment

begin_function_decl
name|TileManager
modifier|*
name|transform_core_do
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|TileManager
modifier|*
parameter_list|,
name|int
parameter_list|,
name|Matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|transform_core_cut
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|transform_core_paste
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|TileManager
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  matrix functions  */
end_comment

begin_function_decl
name|void
name|transform_bounding_box
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|transform_point
parameter_list|(
name|Matrix
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|,
name|double
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|mult_matrix
parameter_list|(
name|Matrix
parameter_list|,
name|Matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|identity_matrix
parameter_list|(
name|Matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|translate_matrix
parameter_list|(
name|Matrix
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|scale_matrix
parameter_list|(
name|Matrix
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rotate_matrix
parameter_list|(
name|Matrix
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|xshear_matrix
parameter_list|(
name|Matrix
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|yshear_matrix
parameter_list|(
name|Matrix
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __TRANSFORM_CORE_H__  */
end_comment

end_unit

