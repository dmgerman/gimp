begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Andy Thomas alt@picnic.demon.co.uk  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PATH_TRANSFORM_H__
end_ifndef

begin_define
DECL|macro|__PATH_TRANSFORM_H__
define|#
directive|define
name|__PATH_TRANSFORM_H__
end_define

begin_include
include|#
directive|include
file|"draw_core.h"
end_include

begin_include
include|#
directive|include
file|"gdisplayF.h"
end_include

begin_include
include|#
directive|include
file|"path.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpmatrix.h"
end_include

begin_function_decl
name|PathUndo
modifier|*
name|path_transform_start_undo
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_transform_free_undo
parameter_list|(
name|PathUndo
modifier|*
name|pundo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_transform_do_undo
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|PathUndo
modifier|*
name|pundo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_transform_current_path
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpMatrix3
name|transform
parameter_list|,
name|gboolean
name|forpreview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_transform_draw_current
parameter_list|(
name|GDisplay
modifier|*
name|gimage
parameter_list|,
name|DrawCore
modifier|*
name|core
parameter_list|,
name|GimpMatrix3
name|transform
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_transform_flip_horz
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_transform_flip_vert
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|path_transform_xy
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PATH_TRANSFORM_H__  */
end_comment

end_unit

