begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* parasite_cmds.c  * Copyright (C) 1998 Jay Cox<jaycox@earthlink.net>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"parasite.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_function_decl
specifier|static
name|Argument
modifier|*
name|parasite_new_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parasite_new_args
name|ProcArg
name|parasite_new_args
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"creator"
block|,
literal|"The creator ID of the parasite to create"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"type"
block|,
literal|"The type ID of the parasite to create"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"flags"
block|,
literal|"The flags ( 1 == persistance )"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"size"
block|,
literal|"The size of the data in bytes"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"data"
block|,
literal|"The data"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parasite_new_out_args
name|ProcArg
name|parasite_new_out_args
index|[]
init|=
block|{
block|{
name|PDB_PARASITE
block|,
literal|"parasite"
block|,
literal|"the new parasite"
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parasite_new_proc
name|ProcRecord
name|parasite_new_proc
init|=
block|{
literal|"parasite_new"
block|,
literal|"creates a new parasite."
block|,
literal|"creates a new parasite unatached to to any image or drawable"
block|,
literal|"Jay Cox"
block|,
literal|"Jay Cox"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|5
block|,
name|parasite_new_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|parasite_new_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|parasite_new_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|parasite_new_invoker (Argument * args)
name|parasite_new_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|char
modifier|*
name|creator
decl_stmt|,
modifier|*
name|type
decl_stmt|;
name|guint32
name|flags
decl_stmt|,
name|size
decl_stmt|;
name|void
modifier|*
name|data
decl_stmt|;
comment|/*  creator  */
if|if
condition|(
name|success
condition|)
block|{
name|creator
operator|=
operator|(
name|char
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
block|}
comment|/*  type  */
if|if
condition|(
name|success
condition|)
block|{
name|type
operator|=
operator|(
name|char
operator|*
operator|)
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
block|}
comment|/*  flags  */
if|if
condition|(
name|success
condition|)
block|{
name|flags
operator|=
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
block|}
comment|/*  size  */
if|if
condition|(
name|success
condition|)
block|{
name|size
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
block|}
comment|/*  data  */
if|if
condition|(
name|success
condition|)
block|{
name|data
operator|=
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|size
operator|>
literal|0
operator|&&
name|data
operator|==
literal|0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|parasite_new_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
comment|/*  The real work  */
if|if
condition|(
name|success
condition|)
block|{
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|parasite_new
argument_list|(
name|creator
argument_list|,
name|type
argument_list|,
name|flags
argument_list|,
name|size
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

end_unit

