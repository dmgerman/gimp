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
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpparasite.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpparasite.h"
end_include

begin_decl_stmt
DECL|variable|parasite_find_proc
specifier|static
name|ProcRecord
name|parasite_find_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parasite_attach_proc
specifier|static
name|ProcRecord
name|parasite_attach_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parasite_detach_proc
specifier|static
name|ProcRecord
name|parasite_detach_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parasite_list_proc
specifier|static
name|ProcRecord
name|parasite_list_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_parasite_find_proc
specifier|static
name|ProcRecord
name|drawable_parasite_find_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_parasite_attach_proc
specifier|static
name|ProcRecord
name|drawable_parasite_attach_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_parasite_detach_proc
specifier|static
name|ProcRecord
name|drawable_parasite_detach_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_parasite_list_proc
specifier|static
name|ProcRecord
name|drawable_parasite_list_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_parasite_find_proc
specifier|static
name|ProcRecord
name|image_parasite_find_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_parasite_attach_proc
specifier|static
name|ProcRecord
name|image_parasite_attach_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_parasite_detach_proc
specifier|static
name|ProcRecord
name|image_parasite_detach_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_parasite_list_proc
specifier|static
name|ProcRecord
name|image_parasite_list_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_parasite_procs (void)
name|register_parasite_procs
parameter_list|(
name|void
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
operator|&
name|parasite_find_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|parasite_attach_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|parasite_detach_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|parasite_list_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|drawable_parasite_find_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|drawable_parasite_attach_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|drawable_parasite_detach_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|drawable_parasite_list_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|image_parasite_find_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|image_parasite_attach_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|image_parasite_detach_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|image_parasite_list_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|parasite_find_invoker (Argument * args)
name|parasite_find_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
init|=
name|NULL
decl_stmt|;
name|name
operator|=
operator|(
name|gchar
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
if|if
condition|(
name|name
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
block|{
name|parasite
operator|=
name|gimp_parasite_copy
argument_list|(
name|gimp_parasite_find
argument_list|(
name|name
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|parasite
operator|!=
name|NULL
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|parasite_find_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|parasite
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|parasite_find_inargs
specifier|static
name|ProcArg
name|parasite_find_inargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"name"
block|,
literal|"The name of the parasite to find"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parasite_find_outargs
specifier|static
name|ProcArg
name|parasite_find_outargs
index|[]
init|=
block|{
block|{
name|PDB_PARASITE
block|,
literal|"parasite"
block|,
literal|"The found parasite"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parasite_find_proc
specifier|static
name|ProcRecord
name|parasite_find_proc
init|=
block|{
literal|"gimp_parasite_find"
block|,
literal|"Finds the named parasite."
block|,
literal|"Finds and returns the named parasite that was previously attached to the gimp."
block|,
literal|"Jay Cox"
block|,
literal|"Jay Cox"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|parasite_find_inargs
block|,
literal|1
block|,
name|parasite_find_outargs
block|,
block|{
block|{
name|parasite_find_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|parasite_attach_invoker (Argument * args)
name|parasite_attach_invoker
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
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|parasite
operator|=
operator|(
name|GimpParasite
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
if|if
condition|(
name|parasite
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
name|gimp_parasite_attach
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|parasite_attach_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|parasite_attach_inargs
specifier|static
name|ProcArg
name|parasite_attach_inargs
index|[]
init|=
block|{
block|{
name|PDB_PARASITE
block|,
literal|"parasite"
block|,
literal|"The parasite to attach to the gimp"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parasite_attach_proc
specifier|static
name|ProcRecord
name|parasite_attach_proc
init|=
block|{
literal|"gimp_parasite_attach"
block|,
literal|"Add a parasite to the gimp."
block|,
literal|"This procedure attaches a parasite to the gimp. It has no return values."
block|,
literal|"Jay Cox"
block|,
literal|"Jay Cox"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|parasite_attach_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|parasite_attach_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|parasite_detach_invoker (Argument * args)
name|parasite_detach_invoker
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
name|gchar
modifier|*
name|name
decl_stmt|;
name|name
operator|=
operator|(
name|gchar
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
if|if
condition|(
name|name
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
name|gimp_parasite_detach
argument_list|(
name|name
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|parasite_detach_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|parasite_detach_inargs
specifier|static
name|ProcArg
name|parasite_detach_inargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"name"
block|,
literal|"The name of the parasite to detach from the gimp."
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parasite_detach_proc
specifier|static
name|ProcRecord
name|parasite_detach_proc
init|=
block|{
literal|"gimp_parasite_detach"
block|,
literal|"Removes a parasite from the gimp."
block|,
literal|"This procedure detaches a parasite from the gimp. It has no return values."
block|,
literal|"Jay Cox"
block|,
literal|"Jay Cox"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|parasite_detach_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|parasite_detach_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|parasite_list_invoker (Argument * args)
name|parasite_list_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gint32
name|num_parasites
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|parasites
decl_stmt|;
name|parasites
operator|=
name|gimp_parasite_list
argument_list|(
operator|&
name|num_parasites
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|parasite_list_proc
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|num_parasites
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|parasites
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|parasite_list_outargs
specifier|static
name|ProcArg
name|parasite_list_outargs
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"num_parasites"
block|,
literal|"The number of attached parasites"
block|}
block|,
block|{
name|PDB_STRINGARRAY
block|,
literal|"parasites"
block|,
literal|"The names of currently attached parasites"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parasite_list_proc
specifier|static
name|ProcRecord
name|parasite_list_proc
init|=
block|{
literal|"gimp_parasite_list"
block|,
literal|"List all parasites."
block|,
literal|"Returns a list of all currently attached parasites."
block|,
literal|"Marc Lehmann"
block|,
literal|"Marc Lehmann"
block|,
literal|"1999"
block|,
name|PDB_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|2
block|,
name|parasite_list_outargs
block|,
block|{
block|{
name|parasite_list_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_parasite_find_invoker (Argument * args)
name|drawable_parasite_find_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
init|=
name|NULL
decl_stmt|;
name|drawable
operator|=
name|gimp_drawable_get_ID
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
name|drawable
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|name
operator|=
operator|(
name|gchar
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
if|if
condition|(
name|name
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
block|{
name|parasite
operator|=
name|gimp_parasite_copy
argument_list|(
name|gimp_drawable_parasite_find
argument_list|(
name|drawable
argument_list|,
name|name
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|parasite
operator|!=
name|NULL
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_parasite_find_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|parasite
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|drawable_parasite_find_inargs
specifier|static
name|ProcArg
name|drawable_parasite_find_inargs
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The drawable"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"name"
block|,
literal|"The name of the parasite to find"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_parasite_find_outargs
specifier|static
name|ProcArg
name|drawable_parasite_find_outargs
index|[]
init|=
block|{
block|{
name|PDB_PARASITE
block|,
literal|"parasite"
block|,
literal|"The found parasite"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_parasite_find_proc
specifier|static
name|ProcRecord
name|drawable_parasite_find_proc
init|=
block|{
literal|"gimp_drawable_parasite_find"
block|,
literal|"Finds the named parasite in a drawable"
block|,
literal|"Finds and returns the named parasite that was previously attached to a drawable."
block|,
literal|"Jay Cox"
block|,
literal|"Jay Cox"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
literal|2
block|,
name|drawable_parasite_find_inargs
block|,
literal|1
block|,
name|drawable_parasite_find_outargs
block|,
block|{
block|{
name|drawable_parasite_find_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_parasite_attach_invoker (Argument * args)
name|drawable_parasite_attach_invoker
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|drawable
operator|=
name|gimp_drawable_get_ID
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
name|drawable
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|parasite
operator|=
operator|(
name|GimpParasite
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
if|if
condition|(
name|parasite
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
name|gimp_drawable_parasite_attach
argument_list|(
name|drawable
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_parasite_attach_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|drawable_parasite_attach_inargs
specifier|static
name|ProcArg
name|drawable_parasite_attach_inargs
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The drawable"
block|}
block|,
block|{
name|PDB_PARASITE
block|,
literal|"parasite"
block|,
literal|"The parasite to attach to a drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_parasite_attach_proc
specifier|static
name|ProcRecord
name|drawable_parasite_attach_proc
init|=
block|{
literal|"gimp_drawable_parasite_attach"
block|,
literal|"Add a parasite to a drawable."
block|,
literal|"This procedure attaches a parasite to a drawable. It has no return values."
block|,
literal|"Jay Cox"
block|,
literal|"Jay Cox"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
literal|2
block|,
name|drawable_parasite_attach_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|drawable_parasite_attach_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_parasite_detach_invoker (Argument * args)
name|drawable_parasite_detach_invoker
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|drawable
operator|=
name|gimp_drawable_get_ID
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
name|drawable
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|name
operator|=
operator|(
name|gchar
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
if|if
condition|(
name|name
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
name|gimp_drawable_parasite_detach
argument_list|(
name|drawable
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_parasite_detach_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|drawable_parasite_detach_inargs
specifier|static
name|ProcArg
name|drawable_parasite_detach_inargs
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The drawable"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"name"
block|,
literal|"The name of the parasite to detach from a drawable."
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_parasite_detach_proc
specifier|static
name|ProcRecord
name|drawable_parasite_detach_proc
init|=
block|{
literal|"gimp_drawable_parasite_detach"
block|,
literal|"Removes a parasite from a drawable."
block|,
literal|"This procedure detaches a parasite from a drawable. It has no return values."
block|,
literal|"Jay Cox"
block|,
literal|"Jay Cox"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
literal|2
block|,
name|drawable_parasite_detach_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|drawable_parasite_detach_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_parasite_list_invoker (Argument * args)
name|drawable_parasite_list_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint32
name|num_parasites
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|parasites
init|=
name|NULL
decl_stmt|;
name|drawable
operator|=
name|gimp_drawable_get_ID
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
name|drawable
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
name|parasites
operator|=
name|gimp_drawable_parasite_list
argument_list|(
name|drawable
argument_list|,
operator|&
name|num_parasites
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_parasite_list_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
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
name|pdb_int
operator|=
name|num_parasites
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|parasites
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|drawable_parasite_list_inargs
specifier|static
name|ProcArg
name|drawable_parasite_list_inargs
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_parasite_list_outargs
specifier|static
name|ProcArg
name|drawable_parasite_list_outargs
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"num_parasites"
block|,
literal|"The number of attached parasites"
block|}
block|,
block|{
name|PDB_STRINGARRAY
block|,
literal|"parasites"
block|,
literal|"The names of currently attached parasites"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_parasite_list_proc
specifier|static
name|ProcRecord
name|drawable_parasite_list_proc
init|=
block|{
literal|"gimp_drawable_parasite_list"
block|,
literal|"List all parasites."
block|,
literal|"Returns a list of all currently attached parasites."
block|,
literal|"Marc Lehmann"
block|,
literal|"Marc Lehmann"
block|,
literal|"1999"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|drawable_parasite_list_inargs
block|,
literal|2
block|,
name|drawable_parasite_list_outargs
block|,
block|{
block|{
name|drawable_parasite_list_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_parasite_find_invoker (Argument * args)
name|image_parasite_find_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
init|=
name|NULL
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
name|name
operator|=
operator|(
name|gchar
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
if|if
condition|(
name|name
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
block|{
name|parasite
operator|=
name|gimp_parasite_copy
argument_list|(
name|gimp_image_parasite_find
argument_list|(
name|gimage
argument_list|,
name|name
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|parasite
operator|!=
name|NULL
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|image_parasite_find_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|parasite
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_parasite_find_inargs
specifier|static
name|ProcArg
name|image_parasite_find_inargs
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"name"
block|,
literal|"The name of the parasite to find"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_parasite_find_outargs
specifier|static
name|ProcArg
name|image_parasite_find_outargs
index|[]
init|=
block|{
block|{
name|PDB_PARASITE
block|,
literal|"parasite"
block|,
literal|"The found parasite"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_parasite_find_proc
specifier|static
name|ProcRecord
name|image_parasite_find_proc
init|=
block|{
literal|"gimp_image_parasite_find"
block|,
literal|"Finds the named parasite in an image"
block|,
literal|"Finds and returns the named parasite that was previously attached to an image."
block|,
literal|"Jay Cox"
block|,
literal|"Jay Cox"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
literal|2
block|,
name|image_parasite_find_inargs
block|,
literal|1
block|,
name|image_parasite_find_outargs
block|,
block|{
block|{
name|image_parasite_find_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_parasite_attach_invoker (Argument * args)
name|image_parasite_attach_invoker
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
name|GimpParasite
modifier|*
name|parasite
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
name|parasite
operator|=
operator|(
name|GimpParasite
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
if|if
condition|(
name|parasite
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
name|gimp_image_parasite_attach
argument_list|(
name|gimage
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|image_parasite_attach_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_parasite_attach_inargs
specifier|static
name|ProcArg
name|image_parasite_attach_inargs
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|PDB_PARASITE
block|,
literal|"parasite"
block|,
literal|"The parasite to attach to an image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_parasite_attach_proc
specifier|static
name|ProcRecord
name|image_parasite_attach_proc
init|=
block|{
literal|"gimp_image_parasite_attach"
block|,
literal|"Add a parasite to an image."
block|,
literal|"This procedure attaches a parasite to an image. It has no return values."
block|,
literal|"Jay Cox"
block|,
literal|"Jay Cox"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
literal|2
block|,
name|image_parasite_attach_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_parasite_attach_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_parasite_detach_invoker (Argument * args)
name|image_parasite_detach_invoker
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
name|gchar
modifier|*
name|name
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
name|name
operator|=
operator|(
name|gchar
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
if|if
condition|(
name|name
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
name|gimp_image_parasite_detach
argument_list|(
name|gimage
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|image_parasite_detach_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_parasite_detach_inargs
specifier|static
name|ProcArg
name|image_parasite_detach_inargs
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"name"
block|,
literal|"The name of the parasite to detach from an image."
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_parasite_detach_proc
specifier|static
name|ProcRecord
name|image_parasite_detach_proc
init|=
block|{
literal|"gimp_image_parasite_detach"
block|,
literal|"Removes a parasite from an image."
block|,
literal|"This procedure detaches a parasite from an image. It has no return values."
block|,
literal|"Jay Cox"
block|,
literal|"Jay Cox"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
literal|2
block|,
name|image_parasite_detach_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_parasite_detach_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_parasite_list_invoker (Argument * args)
name|image_parasite_list_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gint32
name|num_parasites
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|parasites
init|=
name|NULL
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
name|parasites
operator|=
name|gimp_image_parasite_list
argument_list|(
name|gimage
argument_list|,
operator|&
name|num_parasites
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|image_parasite_list_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
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
name|pdb_int
operator|=
name|num_parasites
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|parasites
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_parasite_list_inargs
specifier|static
name|ProcArg
name|image_parasite_list_inargs
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_parasite_list_outargs
specifier|static
name|ProcArg
name|image_parasite_list_outargs
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"num_parasites"
block|,
literal|"The number of attached parasites"
block|}
block|,
block|{
name|PDB_STRINGARRAY
block|,
literal|"parasites"
block|,
literal|"The names of currently attached parasites"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_parasite_list_proc
specifier|static
name|ProcRecord
name|image_parasite_list_proc
init|=
block|{
literal|"gimp_image_parasite_list"
block|,
literal|"List all parasites."
block|,
literal|"Returns a list of all currently attached parasites."
block|,
literal|"Marc Lehmann"
block|,
literal|"Marc Lehmann"
block|,
literal|"1999"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|image_parasite_list_inargs
block|,
literal|2
block|,
name|image_parasite_list_outargs
block|,
block|{
block|{
name|image_parasite_list_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

