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
file|"plug-in/plug-in-progress.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in.h"
end_include

begin_decl_stmt
DECL|variable|progress_init_proc
specifier|static
name|ProcRecord
name|progress_init_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|progress_update_proc
specifier|static
name|ProcRecord
name|progress_update_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|progress_install_proc
specifier|static
name|ProcRecord
name|progress_install_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|progress_uninstall_proc
specifier|static
name|ProcRecord
name|progress_uninstall_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|progress_cancel_proc
specifier|static
name|ProcRecord
name|progress_cancel_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_progress_procs (Gimp * gimp)
name|register_progress_procs
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
name|progress_init_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|progress_update_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|progress_install_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|progress_uninstall_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|progress_cancel_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|progress_init_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|progress_init_invoker
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
name|message
decl_stmt|;
name|gint32
name|gdisplay
decl_stmt|;
name|message
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
name|message
operator|&&
operator|!
name|g_utf8_validate
argument_list|(
name|message
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
name|gdisplay
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
operator|&&
name|gimp
operator|->
name|current_plug_in
operator|->
name|open
condition|)
block|{
if|if
condition|(
operator|!
name|gimp
operator|->
name|no_interface
condition|)
name|plug_in_progress_start
argument_list|(
name|gimp
operator|->
name|current_plug_in
argument_list|,
name|message
argument_list|,
name|gdisplay
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|progress_init_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|progress_init_inargs
specifier|static
name|ProcArg
name|progress_init_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"message"
block|,
literal|"Message to use in the progress dialog"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"gdisplay"
block|,
literal|"GimpDisplay to update progressbar in, or -1 for a seperate window"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|progress_init_proc
specifier|static
name|ProcRecord
name|progress_init_proc
init|=
block|{
literal|"gimp_progress_init"
block|,
literal|"Initializes the progress bar for the current plug-in."
block|,
literal|"Initializes the progress bar for the current plug-in. It is only valid to call this procedure from a plug-in."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|progress_init_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|progress_init_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|progress_update_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|progress_update_invoker
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
name|gdouble
name|percentage
decl_stmt|;
name|percentage
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|current_plug_in
operator|&&
name|gimp
operator|->
name|current_plug_in
operator|->
name|open
condition|)
block|{
if|if
condition|(
operator|!
name|gimp
operator|->
name|no_interface
condition|)
name|plug_in_progress_update
argument_list|(
name|gimp
operator|->
name|current_plug_in
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|progress_update_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|progress_update_inargs
specifier|static
name|ProcArg
name|progress_update_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"percentage"
block|,
literal|"Percentage of progress completed which must be between 0.0 and 1.0"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|progress_update_proc
specifier|static
name|ProcRecord
name|progress_update_proc
init|=
block|{
literal|"gimp_progress_update"
block|,
literal|"Updates the progress bar for the current plug-in."
block|,
literal|"Updates the progress bar for the current plug-in. It is only valid to call this procedure from a plug-in."
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
name|progress_update_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|progress_update_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|progress_install_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|progress_install_invoker
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
name|progress_callback
decl_stmt|;
name|progress_callback
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
name|progress_callback
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|progress_callback
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
name|gimp
operator|->
name|current_plug_in
operator|&&
name|gimp
operator|->
name|current_plug_in
operator|->
name|open
condition|)
name|plug_in_progress_install
argument_list|(
name|gimp
operator|->
name|current_plug_in
argument_list|,
name|progress_callback
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|progress_install_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|progress_install_inargs
specifier|static
name|ProcArg
name|progress_install_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"progress_callback"
block|,
literal|"The callback PDB proc to call"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|progress_install_proc
specifier|static
name|ProcRecord
name|progress_install_proc
init|=
block|{
literal|"gimp_progress_install"
block|,
literal|"Installs a progress callback for the current plug-in."
block|,
literal|"This function installs a temporary PDB procedure which will handle all progress calls made by this plug-in and any procedure it calls. Calling this function multiple times simply replaces the old progress callbacks."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|progress_install_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|progress_install_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|progress_uninstall_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|progress_uninstall_invoker
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
name|progress_callback
decl_stmt|;
name|progress_callback
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
name|progress_callback
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|progress_callback
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
name|gimp
operator|->
name|current_plug_in
operator|&&
name|gimp
operator|->
name|current_plug_in
operator|->
name|open
condition|)
name|plug_in_progress_uninstall
argument_list|(
name|gimp
operator|->
name|current_plug_in
argument_list|,
name|progress_callback
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|progress_uninstall_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|progress_uninstall_inargs
specifier|static
name|ProcArg
name|progress_uninstall_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"progress_callback"
block|,
literal|"The name of the callback registered for this progress"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|progress_uninstall_proc
specifier|static
name|ProcRecord
name|progress_uninstall_proc
init|=
block|{
literal|"gimp_progress_uninstall"
block|,
literal|"Uninstalls the progress callback for the current plug-in."
block|,
literal|"This function uninstalls any progress callback installed with gimp_progress_install() before."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|progress_uninstall_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|progress_uninstall_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|progress_cancel_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|progress_cancel_invoker
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
name|progress_callback
decl_stmt|;
name|progress_callback
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
name|progress_callback
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|progress_callback
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
name|gimp
operator|->
name|current_plug_in
operator|&&
name|gimp
operator|->
name|current_plug_in
operator|->
name|open
condition|)
name|plug_in_progress_cancel
argument_list|(
name|gimp
operator|->
name|current_plug_in
argument_list|,
name|progress_callback
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|progress_cancel_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|progress_cancel_inargs
specifier|static
name|ProcArg
name|progress_cancel_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"progress_callback"
block|,
literal|"The name of the callback registered for this progress"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|progress_cancel_proc
specifier|static
name|ProcRecord
name|progress_cancel_proc
init|=
block|{
literal|"gimp_progress_cancel"
block|,
literal|"Cancels a running progress."
block|,
literal|"This function cancels the currently running progress."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|progress_cancel_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|progress_cancel_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

