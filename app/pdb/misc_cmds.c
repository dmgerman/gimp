begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_decl_stmt
DECL|variable|version_proc
specifier|static
name|ProcRecord
name|version_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|quit_proc
specifier|static
name|ProcRecord
name|quit_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_misc_procs (Gimp * gimp)
name|register_misc_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|version_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|quit_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|version_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|version_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|version_proc
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
name|pdb_pointer
operator|=
name|g_strdup
argument_list|(
name|GIMP_VERSION
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|version_outargs
specifier|static
name|ProcArg
name|version_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"version"
block|,
literal|"The gimp version"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|version_proc
specifier|static
name|ProcRecord
name|version_proc
init|=
block|{
literal|"gimp_version"
block|,
literal|"Returns the host gimp version."
block|,
literal|"This procedure returns the version number of the currently running gimp."
block|,
literal|"Manish Singh"
block|,
literal|"Manish Singh"
block|,
literal|"1999"
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|1
block|,
name|version_outargs
block|,
block|{
block|{
name|version_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|quit_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|quit_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|force
decl_stmt|;
name|force
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|gimp_exit
argument_list|(
name|gimp
argument_list|,
name|force
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|quit_proc
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|quit_inargs
specifier|static
name|ProcArg
name|quit_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"force"
block|,
literal|"Flag specifying whether to force the gimp to or exit normally"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|quit_proc
specifier|static
name|ProcRecord
name|quit_proc
init|=
block|{
literal|"gimp_quit"
block|,
literal|"Causes the gimp to exit gracefully."
block|,
literal|"The internal procedure which can either be used to make the gimp quit. If there are unsaved images in an interactive GIMP session, the user will be asked for confirmation. If force is TRUE, the application is quit without querying the user to save any dirty images."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|quit_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|quit_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

