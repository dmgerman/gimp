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
file|"libgimpcolor/gimpcolor.h"
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-context.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in.h"
end_include

begin_decl_stmt
DECL|variable|context_push_proc
specifier|static
name|ProcRecord
name|context_push_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_pop_proc
specifier|static
name|ProcRecord
name|context_pop_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_get_foreground_proc
specifier|static
name|ProcRecord
name|context_get_foreground_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_set_foreground_proc
specifier|static
name|ProcRecord
name|context_set_foreground_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_get_background_proc
specifier|static
name|ProcRecord
name|context_get_background_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_set_background_proc
specifier|static
name|ProcRecord
name|context_set_background_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_set_default_colors_proc
specifier|static
name|ProcRecord
name|context_set_default_colors_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_swap_colors_proc
specifier|static
name|ProcRecord
name|context_swap_colors_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_get_opacity_proc
specifier|static
name|ProcRecord
name|context_get_opacity_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_set_opacity_proc
specifier|static
name|ProcRecord
name|context_set_opacity_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_get_paint_mode_proc
specifier|static
name|ProcRecord
name|context_get_paint_mode_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_set_paint_mode_proc
specifier|static
name|ProcRecord
name|context_set_paint_mode_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_context_procs (Gimp * gimp)
name|register_context_procs
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
name|context_push_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|context_pop_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|context_get_foreground_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|context_set_foreground_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|context_get_background_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|context_set_background_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|context_set_default_colors_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|context_swap_colors_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|context_get_opacity_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|context_set_opacity_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|context_get_paint_mode_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|context_set_paint_mode_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|context_push_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|context_push_invoker
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
name|success
operator|=
name|plug_in_context_push
argument_list|(
name|gimp
operator|->
name|current_plug_in
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
name|context_push_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|context_push_proc
specifier|static
name|ProcRecord
name|context_push_proc
init|=
block|{
literal|"gimp_context_push"
block|,
literal|"Pushes a context to the top of the plug-in's context stack."
block|,
literal|"This procedure creates a new context by copying the current context. This copy becomes the new current context for the calling plug-in until it is popped again."
block|,
literal|"Michael Natterer<mitch@gimp.org>& Sven Neumann<sven@gimp.org>"
block|,
literal|"Michael Natterer& Sven Neumann"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
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
name|context_push_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|context_pop_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|context_pop_invoker
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
name|success
operator|=
name|plug_in_context_push
argument_list|(
name|gimp
operator|->
name|current_plug_in
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
name|context_pop_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|context_pop_proc
specifier|static
name|ProcRecord
name|context_pop_proc
init|=
block|{
literal|"gimp_context_pop"
block|,
literal|"Pops the topmost context from the plug-in's context stack."
block|,
literal|"This procedure creates a new context and makes it the current context for the calling plug-in."
block|,
literal|"Michael Natterer<mitch@gimp.org>& Sven Neumann<sven@gimp.org>"
block|,
literal|"Michael Natterer& Sven Neumann"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
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
name|context_pop_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|context_get_foreground_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|context_get_foreground_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|context_get_foreground_proc
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
name|pdb_color
operator|=
name|color
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|context_get_foreground_outargs
specifier|static
name|ProcArg
name|context_get_foreground_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_COLOR
block|,
literal|"foreground"
block|,
literal|"The foreground color"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_get_foreground_proc
specifier|static
name|ProcRecord
name|context_get_foreground_proc
init|=
block|{
literal|"gimp_context_get_foreground"
block|,
literal|"Get the current GIMP foreground color."
block|,
literal|"This procedure retrieves the current GIMP foreground color. The foreground color is used in a variety of tools such as paint tools, blending, and bucket fill."
block|,
literal|"Michael Natterer<mitch@gimp.org>& Sven Neumann<sven@gimp.org>"
block|,
literal|"Michael Natterer& Sven Neumann"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|1
block|,
name|context_get_foreground_outargs
block|,
block|{
block|{
name|context_get_foreground_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|context_set_foreground_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|context_set_foreground_invoker
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
name|GimpRGB
name|color
decl_stmt|;
name|color
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_color
expr_stmt|;
name|gimp_rgb_set_alpha
argument_list|(
operator|&
name|color
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_context_set_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|context_set_foreground_proc
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|context_set_foreground_inargs
specifier|static
name|ProcArg
name|context_set_foreground_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_COLOR
block|,
literal|"foreground"
block|,
literal|"The foreground color"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_set_foreground_proc
specifier|static
name|ProcRecord
name|context_set_foreground_proc
init|=
block|{
literal|"gimp_context_set_foreground"
block|,
literal|"Set the current GIMP foreground color."
block|,
literal|"This procedure sets the current GIMP foreground color. After this is set, operations which use foreground such as paint tools, blending, and bucket fill will use the new value."
block|,
literal|"Michael Natterer<mitch@gimp.org>& Sven Neumann<sven@gimp.org>"
block|,
literal|"Michael Natterer& Sven Neumann"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|context_set_foreground_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|context_set_foreground_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|context_get_background_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|context_get_background_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gimp_context_get_background
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|context_get_background_proc
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
name|pdb_color
operator|=
name|color
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|context_get_background_outargs
specifier|static
name|ProcArg
name|context_get_background_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_COLOR
block|,
literal|"foreground"
block|,
literal|"The foreground color"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_get_background_proc
specifier|static
name|ProcRecord
name|context_get_background_proc
init|=
block|{
literal|"gimp_context_get_background"
block|,
literal|"Get the current GIMP background color."
block|,
literal|"This procedure retrieves the current GIMP background color. The background color is used in a variety of tools such as blending, erasing (with non-alpha images), and image filling."
block|,
literal|"Michael Natterer<mitch@gimp.org>& Sven Neumann<sven@gimp.org>"
block|,
literal|"Michael Natterer& Sven Neumann"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|1
block|,
name|context_get_background_outargs
block|,
block|{
block|{
name|context_get_background_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|context_set_background_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|context_set_background_invoker
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
name|GimpRGB
name|color
decl_stmt|;
name|color
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_color
expr_stmt|;
name|gimp_rgb_set_alpha
argument_list|(
operator|&
name|color
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_context_set_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|context_set_background_proc
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|context_set_background_inargs
specifier|static
name|ProcArg
name|context_set_background_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_COLOR
block|,
literal|"background"
block|,
literal|"The background color"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_set_background_proc
specifier|static
name|ProcRecord
name|context_set_background_proc
init|=
block|{
literal|"gimp_context_set_background"
block|,
literal|"Set the current GIMP background color."
block|,
literal|"This procedure sets the current GIMP background color. After this is set, operations which use background such as blending, filling images, clearing, and erasing (in non-alpha images) will use the new value."
block|,
literal|"Michael Natterer<mitch@gimp.org>& Sven Neumann<sven@gimp.org>"
block|,
literal|"Michael Natterer& Sven Neumann"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|context_set_background_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|context_set_background_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|context_set_default_colors_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|context_set_default_colors_invoker
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
name|gimp_context_set_default_colors
argument_list|(
name|context
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|context_set_default_colors_proc
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|context_set_default_colors_proc
specifier|static
name|ProcRecord
name|context_set_default_colors_proc
init|=
block|{
literal|"gimp_context_set_default_colors"
block|,
literal|"Set the current GIMP foreground and background colors to black and white."
block|,
literal|"This procedure sets the current GIMP foreground and background colors to their initial default values, black and white."
block|,
literal|"Michael Natterer<mitch@gimp.org>& Sven Neumann<sven@gimp.org>"
block|,
literal|"Michael Natterer& Sven Neumann"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
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
name|context_set_default_colors_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|context_swap_colors_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|context_swap_colors_invoker
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
name|gimp_context_swap_colors
argument_list|(
name|context
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|context_swap_colors_proc
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|context_swap_colors_proc
specifier|static
name|ProcRecord
name|context_swap_colors_proc
init|=
block|{
literal|"gimp_context_swap_colors"
block|,
literal|"Swap the current GIMP foreground and background colors."
block|,
literal|"This procedure swaps the current GIMP foreground and background colors, so that the new foreground color becomes the old background color and vice versa."
block|,
literal|"Michael Natterer<mitch@gimp.org>& Sven Neumann<sven@gimp.org>"
block|,
literal|"Michael Natterer& Sven Neumann"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
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
name|context_swap_colors_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|context_get_opacity_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|context_get_opacity_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|context_get_opacity_proc
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
name|pdb_float
operator|=
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
operator|*
literal|100.0
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|context_get_opacity_outargs
specifier|static
name|ProcArg
name|context_get_opacity_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"opacity"
block|,
literal|"The opacity: 0<= opacity<= 100"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_get_opacity_proc
specifier|static
name|ProcRecord
name|context_get_opacity_proc
init|=
block|{
literal|"gimp_context_get_opacity"
block|,
literal|"Get the opacity."
block|,
literal|"This procedure returns the opacity setting. The return value is a floating point number between 0 and 100."
block|,
literal|"Michael Natterer<mitch@gimp.org>& Sven Neumann<sven@gimp.org>"
block|,
literal|"Michael Natterer& Sven Neumann"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|1
block|,
name|context_get_opacity_outargs
block|,
block|{
block|{
name|context_get_opacity_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|context_set_opacity_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|context_set_opacity_invoker
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
name|opacity
decl_stmt|;
name|opacity
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
name|opacity
operator|<
literal|0.0
operator|||
name|opacity
operator|>
literal|100.0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|gimp_context_set_opacity
argument_list|(
name|context
argument_list|,
name|opacity
operator|/
literal|100.0
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|context_set_opacity_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|context_set_opacity_inargs
specifier|static
name|ProcArg
name|context_set_opacity_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"opacity"
block|,
literal|"The opacity: 0<= opacity<= 100"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_set_opacity_proc
specifier|static
name|ProcRecord
name|context_set_opacity_proc
init|=
block|{
literal|"gimp_context_set_opacity"
block|,
literal|"Set the opacity."
block|,
literal|"This procedure modifies the opacity setting. The value should be a floating point number between 0 and 100."
block|,
literal|"Michael Natterer<mitch@gimp.org>& Sven Neumann<sven@gimp.org>"
block|,
literal|"Michael Natterer& Sven Neumann"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|context_set_opacity_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|context_set_opacity_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|context_get_paint_mode_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|context_get_paint_mode_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|context_get_paint_mode_proc
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
name|gimp_context_get_paint_mode
argument_list|(
name|context
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|context_get_paint_mode_outargs
specifier|static
name|ProcArg
name|context_get_paint_mode_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"paint_mode"
block|,
literal|"The paint mode: { GIMP_NORMAL_MODE (0), GIMP_DISSOLVE_MODE (1), GIMP_BEHIND_MODE (2), GIMP_MULTIPLY_MODE (3), GIMP_SCREEN_MODE (4), GIMP_OVERLAY_MODE (5), GIMP_DIFFERENCE_MODE (6), GIMP_ADDITION_MODE (7), GIMP_SUBTRACT_MODE (8), GIMP_DARKEN_ONLY_MODE (9), GIMP_LIGHTEN_ONLY_MODE (10), GIMP_HUE_MODE (11), GIMP_SATURATION_MODE (12), GIMP_COLOR_MODE (13), GIMP_VALUE_MODE (14), GIMP_DIVIDE_MODE (15), GIMP_DODGE_MODE (16), GIMP_BURN_MODE (17), GIMP_HARDLIGHT_MODE (18), GIMP_SOFTLIGHT_MODE (19), GIMP_GRAIN_EXTRACT_MODE (20), GIMP_GRAIN_MERGE_MODE (21), GIMP_COLOR_ERASE_MODE (22) }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_get_paint_mode_proc
specifier|static
name|ProcRecord
name|context_get_paint_mode_proc
init|=
block|{
literal|"gimp_context_get_paint_mode"
block|,
literal|"Get the paint mode."
block|,
literal|"This procedure returns the paint-mode setting. The return value is an integer which corresponds to the values listed in the argument description."
block|,
literal|"Michael Natterer<mitch@gimp.org>& Sven Neumann<sven@gimp.org>"
block|,
literal|"Michael Natterer& Sven Neumann"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|1
block|,
name|context_get_paint_mode_outargs
block|,
block|{
block|{
name|context_get_paint_mode_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|context_set_paint_mode_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|context_set_paint_mode_invoker
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
name|gint32
name|paint_mode
decl_stmt|;
name|paint_mode
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
name|paint_mode
operator|<
name|GIMP_NORMAL_MODE
operator|||
name|paint_mode
operator|>
name|GIMP_COLOR_ERASE_MODE
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|gimp_context_set_paint_mode
argument_list|(
name|context
argument_list|,
name|paint_mode
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|context_set_paint_mode_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|context_set_paint_mode_inargs
specifier|static
name|ProcArg
name|context_set_paint_mode_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"paint_mode"
block|,
literal|"The paint mode: { GIMP_NORMAL_MODE (0), GIMP_DISSOLVE_MODE (1), GIMP_BEHIND_MODE (2), GIMP_MULTIPLY_MODE (3), GIMP_SCREEN_MODE (4), GIMP_OVERLAY_MODE (5), GIMP_DIFFERENCE_MODE (6), GIMP_ADDITION_MODE (7), GIMP_SUBTRACT_MODE (8), GIMP_DARKEN_ONLY_MODE (9), GIMP_LIGHTEN_ONLY_MODE (10), GIMP_HUE_MODE (11), GIMP_SATURATION_MODE (12), GIMP_COLOR_MODE (13), GIMP_VALUE_MODE (14), GIMP_DIVIDE_MODE (15), GIMP_DODGE_MODE (16), GIMP_BURN_MODE (17), GIMP_HARDLIGHT_MODE (18), GIMP_SOFTLIGHT_MODE (19), GIMP_GRAIN_EXTRACT_MODE (20), GIMP_GRAIN_MERGE_MODE (21), GIMP_COLOR_ERASE_MODE (22) }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_set_paint_mode_proc
specifier|static
name|ProcRecord
name|context_set_paint_mode_proc
init|=
block|{
literal|"gimp_context_set_paint_mode"
block|,
literal|"Set the paint mode."
block|,
literal|"This procedure modifies the paint_mode setting."
block|,
literal|"Michael Natterer<mitch@gimp.org>& Sven Neumann<sven@gimp.org>"
block|,
literal|"Michael Natterer& Sven Neumann"
block|,
literal|"2004"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|context_set_paint_mode_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|context_set_paint_mode_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

