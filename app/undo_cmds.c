begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2000 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
end_comment

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_decl_stmt
DECL|variable|undo_push_group_start_proc
specifier|static
name|ProcRecord
name|undo_push_group_start_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|undo_push_group_end_proc
specifier|static
name|ProcRecord
name|undo_push_group_end_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_undo_procs (void)
name|register_undo_procs
parameter_list|(
name|void
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
operator|&
name|undo_push_group_start_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|undo_push_group_end_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|undo_push_group_start_invoker (Argument * args)
name|undo_push_group_start_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gimage
operator|=
name|pdb_id_to_image
argument_list|(
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|undo_push_group_start
argument_list|(
name|gimage
argument_list|,
name|MISC_UNDO
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|undo_push_group_start_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|undo_push_group_start_inargs
specifier|static
name|ProcArg
name|undo_push_group_start_inargs
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The ID of the image in which to pop an undo group"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|undo_push_group_start_proc
specifier|static
name|ProcRecord
name|undo_push_group_start_proc
init|=
block|{
literal|"gimp_undo_push_group_start"
block|,
literal|"Starts a group undo."
block|,
literal|"This function is used to start a group undo--necessary for logically combining two or more undo operations into a single operation. This call must be used in conjunction with a 'gimp-undo-push-group-end' call."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|undo_push_group_start_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|undo_push_group_start_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|undo_push_group_end_invoker (Argument * args)
name|undo_push_group_end_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gimage
operator|=
name|pdb_id_to_image
argument_list|(
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|undo_push_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|undo_push_group_end_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|undo_push_group_end_inargs
specifier|static
name|ProcArg
name|undo_push_group_end_inargs
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The ID of the image in which to pop an undo group"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|undo_push_group_end_proc
specifier|static
name|ProcRecord
name|undo_push_group_end_proc
init|=
block|{
literal|"gimp_undo_push_group_end"
block|,
literal|"Finish a group undo."
block|,
literal|"This function must be called once for each gimp-undo-push-group call that is made."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|undo_push_group_end_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|undo_push_group_end_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

