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
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay_cmds.h"
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

begin_decl_stmt
DECL|variable|return_args
specifier|static
name|Argument
modifier|*
name|return_args
decl_stmt|;
end_decl_stmt

begin_comment
comment|/******************/
end_comment

begin_comment
comment|/*  GDISPLAY_NEW  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gdisplay_new_invoker (Argument * args)
name|gdisplay_new_invoker
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
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|unsigned
name|int
name|scale
init|=
literal|0x101
decl_stmt|;
name|gdisp
operator|=
name|NULL
expr_stmt|;
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
comment|/*  make sure the image has layers before displaying it  */
if|if
condition|(
name|success
operator|&&
name|gimage
operator|->
name|layers
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
name|success
operator|=
operator|(
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
operator|)
expr_stmt|;
comment|/*  create the new image  */
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|gdisplay_new_proc
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

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gdisplay_new_args
name|ProcArg
name|gdisplay_new_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gdisplay_new_out_args
name|ProcArg
name|gdisplay_new_out_args
index|[]
init|=
block|{
block|{
name|PDB_DISPLAY
block|,
literal|"display"
block|,
literal|"the new display"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gdisplay_new_proc
name|ProcRecord
name|gdisplay_new_proc
init|=
block|{
literal|"gimp_display_new"
block|,
literal|"Creates a new display for the specified image"
block|,
literal|"Creates a new display for the specified image.  If the image already has a display, another is added.  Multiple displays are handled transparently by the GIMP.  The newly created display is returned and can be subsequently destroyed with a call to 'gimp_display_delete'.  This procedure only makes sense for use with the GIMP UI."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|gdisplay_new_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|gdisplay_new_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|gdisplay_new_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*********************/
end_comment

begin_comment
comment|/*  GDISPLAY_DELETE  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gdisplay_delete_invoker (Argument * args)
name|gdisplay_delete_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisplay
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
name|gdisplay
operator|=
name|gdisplay_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
condition|)
name|gtk_widget_destroy
argument_list|(
name|gdisplay
operator|->
name|shell
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gdisplay_delete_proc
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
DECL|variable|gdisplay_delete_args
name|ProcArg
name|gdisplay_delete_args
index|[]
init|=
block|{
block|{
name|PDB_DISPLAY
block|,
literal|"display"
block|,
literal|"The display"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gdisplay_delete_proc
name|ProcRecord
name|gdisplay_delete_proc
init|=
block|{
literal|"gimp_display_delete"
block|,
literal|"Delete the specified display"
block|,
literal|"This procedure removes the specified display.  If this is the last remaining display for the underlying image, then the image is deleted also."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|gdisplay_delete_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|gdisplay_delete_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*********************/
end_comment

begin_comment
comment|/*  GDISPLAYS_FLUSH  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gdisplays_flush_invoker (Argument * args)
name|gdisplays_flush_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|success
operator|=
name|TRUE
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gdisplays_flush_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gdisplays_flush_proc
name|ProcRecord
name|gdisplays_flush_proc
init|=
block|{
literal|"gimp_displays_flush"
block|,
literal|"Flush all internal changes to the user interface"
block|,
literal|"This procedure takes no arguments and returns nothing except a success status.  Its purpose is to flush all pending updates of image manipulations to the user interface.  It should be called whenever appropriate."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|gdisplays_flush_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

end_unit

