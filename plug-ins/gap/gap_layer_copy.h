begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* my_layer_copy.h  * 1997.11.06 hof (Wolfgang Hofer)  *  *  *  this procedure works similar to gimp_layer_copy(src_id);  *  ==> gimp_layer_copy works only for layers within the same image !!  *  ==> Workaround:  *      p_my_layer_copy is my 'private' version of layercopy  *      that can copy layers from another image of the same type.  *  * returns the id of the new layer  *      and the offests of the original within the source image  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * version 0.98.00 1998.11.26   hof: added channel copy  * version 0.90.00;             hof: 1.st (pre) release  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GAP_LAYER_COPY_H
end_ifndef

begin_define
DECL|macro|_GAP_LAYER_COPY_H
define|#
directive|define
name|_GAP_LAYER_COPY_H
end_define

begin_comment
comment|/* SYTEM (UNIX) includes */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

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

begin_function_decl
name|gint32
name|p_my_layer_copy
parameter_list|(
name|gint32
name|dst_image_id
parameter_list|,
name|gint32
name|src_layer_id
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
comment|/* 0.0 upto 100.0 */
name|GimpLayerModeEffects
name|mode
parameter_list|,
name|gint
modifier|*
name|src_offset_x
parameter_list|,
name|gint
modifier|*
name|src_offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|p_my_channel_copy
parameter_list|(
name|gint32
name|dst_image_id
parameter_list|,
name|gint32
name|src_channel_id
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

