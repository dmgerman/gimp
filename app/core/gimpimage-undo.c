begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"gimpundostack.h"
end_include

begin_function
name|void
DECL|function|gimp_image_undo (GimpImage * gimage)
name|gimp_image_undo
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|undo
operator|=
name|GIMP_UNDO
argument_list|(
name|gimp_undo_stack_pop
argument_list|(
name|gimage
operator|->
name|new_undo_stack
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
condition|)
name|gimp_undo_stack_push
argument_list|(
name|gimage
operator|->
name|new_redo_stack
argument_list|,
name|undo
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_redo (GimpImage * gimage)
name|gimp_image_redo
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|redo
decl_stmt|;
name|redo
operator|=
name|GIMP_UNDO
argument_list|(
name|gimp_undo_stack_pop
argument_list|(
name|gimage
operator|->
name|new_redo_stack
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|redo
condition|)
name|gimp_undo_stack_push
argument_list|(
name|gimage
operator|->
name|new_undo_stack
argument_list|,
name|redo
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

