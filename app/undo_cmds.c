begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"undo_cmds.h"
end_include

begin_decl_stmt
DECL|variable|int_value
specifier|static
name|int
name|int_value
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|success
specifier|static
name|int
name|success
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***************************/
end_comment

begin_comment
comment|/*  UNDO_PUSH_GROUP_START  */
end_comment

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
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
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

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|undo_push_group_start_args
name|ProcArg
name|undo_push_group_start_args
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
name|ProcRecord
name|undo_push_group_start_proc
init|=
block|{
literal|"gimp_undo_push_group_start"
block|,
literal|"Starts a group undo"
block|,
literal|"This function is used to start a group undo--necessary for logically combining two or more undo operations into a single operation.  This call must be used in conjunction with a 'gimp_undo_push_group_end' call."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|undo_push_group_start_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|undo_push_group_start_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*************************/
end_comment

begin_comment
comment|/*  UNDO_PUSH_GROUP_END  */
end_comment

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
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
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

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|undo_push_group_end_args
name|ProcArg
name|undo_push_group_end_args
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
name|ProcRecord
name|undo_push_group_end_proc
init|=
block|{
literal|"gimp_undo_push_group_end"
block|,
literal|"Finish a group undo"
block|,
literal|"This function must be called once for each undo_push_group call that is made."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|undo_push_group_end_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|undo_push_group_end_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

end_unit

