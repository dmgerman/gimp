begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimphelp.h"
end_include

begin_decl_stmt
DECL|variable|help_proc
specifier|static
name|ProcRecord
name|help_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_gimphelp_procs (void)
name|register_gimphelp_procs
parameter_list|(
name|void
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
operator|&
name|help_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|help_invoker (Argument * args)
name|help_invoker
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
name|path
decl_stmt|;
name|path
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
name|path
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
name|gimp_help
argument_list|(
name|path
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|help_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|help_inargs
specifier|static
name|ProcArg
name|help_inargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"path"
block|,
literal|"The location of the help page"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|help_proc
specifier|static
name|ProcRecord
name|help_proc
init|=
block|{
literal|"gimp_help"
block|,
literal|"Load a help page."
block|,
literal|"This procedure loads the specified help page into the helpbrowser or what ever is configured as help viewer. The location of the jelp page is given relative to the help rootdir."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"1999"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|help_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|help_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

