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

begin_include
include|#
directive|include
file|"plug-in/plug-in.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-ins.h"
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
DECL|function|register_help_procs (Gimp * gimp)
name|register_help_procs
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
name|help_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|help_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|help_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
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
name|help_domain
decl_stmt|;
name|gchar
modifier|*
name|help_id
decl_stmt|;
name|help_domain
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
name|help_domain
operator|&&
operator|!
name|g_utf8_validate
argument_list|(
name|help_domain
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|help_id
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
name|help_id
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|help_id
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
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
if|if
condition|(
operator|!
name|help_domain
operator|&&
name|gimp
operator|->
name|current_plug_in
condition|)
name|help_domain
operator|=
operator|(
name|gchar
operator|*
operator|)
name|plug_ins_help_domain
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|current_plug_in
operator|->
name|prog
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_help
argument_list|(
name|gimp
argument_list|,
name|help_domain
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
block|}
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
name|GIMP_PDB_STRING
block|,
literal|"help_domain"
block|,
literal|"The help domain in which help_id is registered"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"help_id"
block|,
literal|"The help page's ID"
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
literal|"This procedure loads the specified help page into the helpbrowser or what ever is configured as help viewer. The help page is identified by its domain and ID: if help_domain is NULL, we use the help_domain which was registered using the gimp-plugin-help-register procedure. If help_domain is NULL and no help domain was registered, the help domain of the main GIMP installation is used."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"2000"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|2
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

