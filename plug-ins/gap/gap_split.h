begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_lib.h  * 1997.11.01 hof (Wolfgang Hofer)  *  * GAP ... Gimp Animation Plugins  *  * Split Image to Anim Frames (seperate Images on disk)  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * 0.96.00; 1998/07/03   hof: 1.st releas  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GAP_SPLIT_H
end_ifndef

begin_define
DECL|macro|_GAP_SPLIT_H
define|#
directive|define
name|_GAP_SPLIT_H
end_define

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_function_decl
name|int
name|gap_split_image
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|gint32
name|inverse_order
parameter_list|,
name|gint32
name|no_alpha
parameter_list|,
name|char
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

