begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  gap_exchange_image.h  *  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * version 0.98.00; 1998/11/26  hof: 1.st release   *                             (substitute for the procedure "gimp_duplicate_into"  *                              that was never part of the GIMP core)  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GAP_EXCHANGE_IMAGE_H
end_ifndef

begin_define
DECL|macro|_GAP_EXCHANGE_IMAGE_H
define|#
directive|define
name|_GAP_EXCHANGE_IMAGE_H
end_define

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_function_decl
name|int
name|p_exchange_image
parameter_list|(
name|gint32
name|dst_image_id
parameter_list|,
name|gint32
name|src_image_id
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

