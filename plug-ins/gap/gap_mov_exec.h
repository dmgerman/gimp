begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_lib.h  * 1997.11.01 hof (Wolfgang Hofer)  *  * GAP ... Gimp Animation Plugins  *  * basic anim functions  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * gimp    1.1.20a; 2000/04/25  hof: support for keyframes, anim_preview  * 0.96.00; 1998/06/27   hof: added gap animation sizechange plugins  *                            (moved range_ops to seperate .h file)  * 0.94.01; 1998/04/27   hof: added flatten_mode to plugin: gap_range_to_multilayer  * 0.90.00;              hof: 1.st (pre) release  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GAP_MOV_EXEC_H
end_ifndef

begin_define
DECL|macro|_GAP_MOV_EXEC_H
define|#
directive|define
name|_GAP_MOV_EXEC_H
end_define

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"gap_mov_dialog.h"
end_include

begin_function_decl
name|int
name|gap_move
parameter_list|(
name|GimpRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|p_mov_anim_preview
parameter_list|(
name|t_mov_values
modifier|*
name|pvals_orig
parameter_list|,
name|t_anim_info
modifier|*
name|ainfo_ptr
parameter_list|,
name|gint
name|preview_frame_nr
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

