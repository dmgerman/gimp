begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_resi_dialog.h  * 1998.07.01 hof (Wolfgang Hofer)  *  * GAP ... Gimp Animation Plugins  *  * This Module contains the resize and scale Dialog for AnimFrames.  * (It just is a shell to call Gimp's resize / scale Dialog )  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history  * 0.96.00; 1998/07/01   hof: first release  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_RESI_DIALOG_H
end_ifndef

begin_define
DECL|macro|_RESI_DIALOG_H
define|#
directive|define
name|_RESI_DIALOG_H
end_define

begin_comment
comment|/* GIMP includes */
end_comment

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_comment
comment|/* GAP includes */
end_comment

begin_include
include|#
directive|include
file|"gap_range_ops.h"
end_include

begin_function_decl
name|gint
name|p_resi_dialog
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|t_gap_asiz
name|asiz_mode
parameter_list|,
name|char
modifier|*
name|title_text
parameter_list|,
name|long
modifier|*
name|size_x
parameter_list|,
name|long
modifier|*
name|size_y
parameter_list|,
name|long
modifier|*
name|offs_x
parameter_list|,
name|long
modifier|*
name|offs_y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

