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
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"palette.h"
end_include

begin_decl_stmt
DECL|variable|palette_get_foreground_proc
specifier|static
name|ProcRecord
name|palette_get_foreground_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|palette_get_background_proc
specifier|static
name|ProcRecord
name|palette_get_background_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|palette_set_foreground_proc
specifier|static
name|ProcRecord
name|palette_set_foreground_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|palette_set_background_proc
specifier|static
name|ProcRecord
name|palette_set_background_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|palette_set_default_colors_proc
specifier|static
name|ProcRecord
name|palette_set_default_colors_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|palette_swap_colors_proc
specifier|static
name|ProcRecord
name|palette_swap_colors_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|palette_refresh_proc
specifier|static
name|ProcRecord
name|palette_refresh_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_palette_procs (void)
name|register_palette_procs
parameter_list|(
name|void
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
operator|&
name|palette_get_foreground_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|palette_get_background_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|palette_set_foreground_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|palette_set_background_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|palette_set_default_colors_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|palette_swap_colors_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|palette_refresh_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|palette_get_foreground_invoker (Argument * args)
name|palette_get_foreground_invoker
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
name|guchar
modifier|*
name|col
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gimp_context_get_foreground
argument_list|(
name|NULL
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|col
operator|=
operator|(
name|guchar
operator|*
operator|)
name|g_new
argument_list|(
name|guchar
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|col
index|[
name|RED_PIX
index|]
operator|=
name|r
expr_stmt|;
name|col
index|[
name|GREEN_PIX
index|]
operator|=
name|g
expr_stmt|;
name|col
index|[
name|BLUE_PIX
index|]
operator|=
name|b
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|palette_get_foreground_proc
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
name|col
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|palette_get_foreground_outargs
specifier|static
name|ProcArg
name|palette_get_foreground_outargs
index|[]
init|=
block|{
block|{
name|PDB_COLOR
block|,
literal|"foreground"
block|,
literal|"The foreground color"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|palette_get_foreground_proc
specifier|static
name|ProcRecord
name|palette_get_foreground_proc
init|=
block|{
literal|"gimp_palette_get_foreground"
block|,
literal|"Get the current GIMP foreground color."
block|,
literal|"This procedure retrieves the current GIMP foreground color. The foreground color is used in a variety of tools such as paint tools, blending, and bucket fill."
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
literal|1
block|,
name|palette_get_foreground_outargs
block|,
block|{
block|{
name|palette_get_foreground_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|palette_get_background_invoker (Argument * args)
name|palette_get_background_invoker
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
name|guchar
modifier|*
name|col
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gimp_context_get_background
argument_list|(
name|NULL
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|col
operator|=
operator|(
name|guchar
operator|*
operator|)
name|g_new
argument_list|(
name|guchar
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|col
index|[
name|RED_PIX
index|]
operator|=
name|r
expr_stmt|;
name|col
index|[
name|GREEN_PIX
index|]
operator|=
name|g
expr_stmt|;
name|col
index|[
name|BLUE_PIX
index|]
operator|=
name|b
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|palette_get_background_proc
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
name|col
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|palette_get_background_outargs
specifier|static
name|ProcArg
name|palette_get_background_outargs
index|[]
init|=
block|{
block|{
name|PDB_COLOR
block|,
literal|"background"
block|,
literal|"The background color"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|palette_get_background_proc
specifier|static
name|ProcRecord
name|palette_get_background_proc
init|=
block|{
literal|"gimp_palette_get_background"
block|,
literal|"Get the current GIMP background color."
block|,
literal|"This procedure retrieves the current GIMP background color. The background color is used in a variety of tools such as blending, erasing (with non-alpha images), and image filling."
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
literal|1
block|,
name|palette_get_background_outargs
block|,
block|{
block|{
name|palette_get_background_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|palette_set_foreground_invoker (Argument * args)
name|palette_set_foreground_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|guchar
modifier|*
name|col
decl_stmt|;
name|col
operator|=
operator|(
name|guchar
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
name|gimp_context_set_foreground
argument_list|(
name|NULL
argument_list|,
name|col
index|[
name|RED_PIX
index|]
argument_list|,
name|col
index|[
name|GREEN_PIX
index|]
argument_list|,
name|col
index|[
name|BLUE_PIX
index|]
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|palette_set_foreground_proc
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|palette_set_foreground_inargs
specifier|static
name|ProcArg
name|palette_set_foreground_inargs
index|[]
init|=
block|{
block|{
name|PDB_COLOR
block|,
literal|"foreground"
block|,
literal|"The foreground color"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|palette_set_foreground_proc
specifier|static
name|ProcRecord
name|palette_set_foreground_proc
init|=
block|{
literal|"gimp_palette_set_foreground"
block|,
literal|"Set the current GIMP foreground color."
block|,
literal|"This procedure sets the current GIMP foreground color. After this is set, operations which use foreground such as paint tools, blending, and bucket fill will use the new value."
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
name|palette_set_foreground_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|palette_set_foreground_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|palette_set_background_invoker (Argument * args)
name|palette_set_background_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|guchar
modifier|*
name|col
decl_stmt|;
name|col
operator|=
operator|(
name|guchar
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
name|gimp_context_set_background
argument_list|(
name|NULL
argument_list|,
name|col
index|[
name|RED_PIX
index|]
argument_list|,
name|col
index|[
name|GREEN_PIX
index|]
argument_list|,
name|col
index|[
name|BLUE_PIX
index|]
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|palette_set_background_proc
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|palette_set_background_inargs
specifier|static
name|ProcArg
name|palette_set_background_inargs
index|[]
init|=
block|{
block|{
name|PDB_COLOR
block|,
literal|"background"
block|,
literal|"The background color"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|palette_set_background_proc
specifier|static
name|ProcRecord
name|palette_set_background_proc
init|=
block|{
literal|"gimp_palette_set_background"
block|,
literal|"Set the current GIMP background color."
block|,
literal|"This procedure sets the current GIMP background color. After this is set, operations which use background such as blending, filling images, clearing, and erasing (in non-alpha images) will use the new value."
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
name|palette_set_background_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|palette_set_background_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|palette_set_default_colors_invoker (Argument * args)
name|palette_set_default_colors_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gimp_context_set_default_colors
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|palette_set_default_colors_proc
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|palette_set_default_colors_proc
specifier|static
name|ProcRecord
name|palette_set_default_colors_proc
init|=
block|{
literal|"gimp_palette_set_default_colors"
block|,
literal|"Set the current GIMP foreground and background colors to black and white."
block|,
literal|"This procedure sets the current GIMP foreground and background colors to their initial default values, black and white."
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
name|palette_set_default_colors_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|palette_swap_colors_invoker (Argument * args)
name|palette_swap_colors_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gimp_context_swap_colors
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|palette_swap_colors_proc
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|palette_swap_colors_proc
specifier|static
name|ProcRecord
name|palette_swap_colors_proc
init|=
block|{
literal|"gimp_palette_swap_colors"
block|,
literal|"Swap the current GIMP foreground and background colors."
block|,
literal|"This procedure swaps the current GIMP foreground and background colors, so that the new foreground color becomes the old background color and vice versa."
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
name|palette_swap_colors_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|palette_refresh_invoker (Argument * args)
name|palette_refresh_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
comment|/* FIXME: I've hardcoded success to be TRUE, because brushes_init() is a     *        void function right now.  It'd be nice if it returned a value at     *        some future date, so we could tell if things blew up when reparsing    *        the list (for whatever reason).     *                       - Seth "Yes, this is a kludge" Burgess    *<sjburges@ou.edu>    *   -and shamelessly stolen by Adrian Likins for use here...    */
name|palette_free_palettes
argument_list|()
expr_stmt|;
name|palette_init_palettes
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|palette_refresh_proc
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|palette_refresh_proc
specifier|static
name|ProcRecord
name|palette_refresh_proc
init|=
block|{
literal|"gimp_palette_refresh"
block|,
literal|"Refreshes current palettes."
block|,
literal|"This procedure incorporates all palettes currently in the users palette path."
block|,
literal|"Adrian Likins<adrian@gimp.org>"
block|,
literal|"Adrian Likins"
block|,
literal|"1998"
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
name|palette_refresh_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

