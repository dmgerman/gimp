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
file|"gdisplay.h"
end_include

begin_decl_stmt
DECL|variable|display_new_proc
specifier|static
name|ProcRecord
name|display_new_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|display_delete_proc
specifier|static
name|ProcRecord
name|display_delete_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|displays_flush_proc
specifier|static
name|ProcRecord
name|displays_flush_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_gdisplay_procs (void)
name|register_gdisplay_procs
parameter_list|(
name|void
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
operator|&
name|display_new_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|display_delete_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|displays_flush_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|display_new_invoker (Argument * args)
name|display_new_invoker
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
name|GDisplay
modifier|*
name|gdisp
init|=
name|NULL
decl_stmt|;
name|guint
name|scale
init|=
literal|0x101
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
block|{
if|if
condition|(
name|gimage
operator|->
name|layers
condition|)
name|success
operator|=
operator|(
name|gdisp
operator|=
name|gdisplay_new
argument_list|(
name|gimage
argument_list|,
name|scale
argument_list|)
operator|)
operator|!=
name|NULL
expr_stmt|;
else|else
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
name|display_new_proc
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
name|pdb_int
operator|=
name|gdisp
operator|->
name|ID
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|display_new_inargs
specifier|static
name|ProcArg
name|display_new_inargs
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
DECL|variable|display_new_outargs
specifier|static
name|ProcArg
name|display_new_outargs
index|[]
init|=
block|{
block|{
name|PDB_DISPLAY
block|,
literal|"display"
block|,
literal|"The new display"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|display_new_proc
specifier|static
name|ProcRecord
name|display_new_proc
init|=
block|{
literal|"gimp_display_new"
block|,
literal|"Create a new display for the specified image."
block|,
literal|"Creates a new display for the specified image. If the image already has a display, another is added. Multiple displays are handled transparently by the GIMP. The newly created display is returned and can be subsequently destroyed with a call to 'gimp-display-delete'. This procedure only makes sense for use with the GIMP UI."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|display_new_inargs
block|,
literal|1
block|,
name|display_new_outargs
block|,
block|{
block|{
name|display_new_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|display_delete_invoker (Argument * args)
name|display_delete_invoker
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
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|gdisplay_get_ID
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
name|gdisp
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
name|gtk_widget_destroy
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|display_delete_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|display_delete_inargs
specifier|static
name|ProcArg
name|display_delete_inargs
index|[]
init|=
block|{
block|{
name|PDB_DISPLAY
block|,
literal|"display"
block|,
literal|"The display to delete"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|display_delete_proc
specifier|static
name|ProcRecord
name|display_delete_proc
init|=
block|{
literal|"gimp_display_delete"
block|,
literal|"Delete the specified display."
block|,
literal|"This procedure removes the specified display. If this is the last remaining display for the underlying image, then the image is deleted also."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|display_delete_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|display_delete_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|displays_flush_invoker (Argument * args)
name|displays_flush_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gdisplays_flush
argument_list|()
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|displays_flush_proc
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|displays_flush_proc
specifier|static
name|ProcRecord
name|displays_flush_proc
init|=
block|{
literal|"gimp_displays_flush"
block|,
literal|"Flush all internal changes to the user interface"
block|,
literal|"This procedure takes no arguments and returns nothing except a success status. Its purpose is to flush all pending updates of image manipulations to the user interface. It should be called whenever appropriate."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|displays_flush_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

