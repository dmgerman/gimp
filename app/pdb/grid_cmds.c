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
file|"libgimpbase/gimpbaseenums.h"
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
file|"core/gimpgrid.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-grid.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_decl_stmt
DECL|variable|image_grid_get_spacing_proc
specifier|static
name|ProcRecord
name|image_grid_get_spacing_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_set_spacing_proc
specifier|static
name|ProcRecord
name|image_grid_set_spacing_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_get_offset_proc
specifier|static
name|ProcRecord
name|image_grid_get_offset_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_set_offset_proc
specifier|static
name|ProcRecord
name|image_grid_set_offset_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_get_foreground_color_proc
specifier|static
name|ProcRecord
name|image_grid_get_foreground_color_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_set_foreground_color_proc
specifier|static
name|ProcRecord
name|image_grid_set_foreground_color_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_get_background_color_proc
specifier|static
name|ProcRecord
name|image_grid_get_background_color_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_set_background_color_proc
specifier|static
name|ProcRecord
name|image_grid_set_background_color_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_get_style_proc
specifier|static
name|ProcRecord
name|image_grid_get_style_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_set_style_proc
specifier|static
name|ProcRecord
name|image_grid_set_style_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_grid_procs (Gimp * gimp)
name|register_grid_procs
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
name|image_grid_get_spacing_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_grid_set_spacing_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_grid_get_offset_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_grid_set_offset_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_grid_get_foreground_color_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_grid_set_foreground_color_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_grid_get_background_color_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_grid_set_background_color_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_grid_get_style_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_grid_set_style_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_grid_get_spacing_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_grid_get_spacing_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gdouble
name|xspacing
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|yspacing
init|=
literal|0.0
decl_stmt|;
name|image
operator|=
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
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
operator|!
name|GIMP_IS_IMAGE
argument_list|(
name|image
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
name|GimpGrid
modifier|*
name|grid
init|=
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|grid
condition|)
name|g_object_get
argument_list|(
name|grid
argument_list|,
literal|"xspacing"
argument_list|,
operator|&
name|xspacing
argument_list|,
literal|"yspacing"
argument_list|,
operator|&
name|yspacing
argument_list|,
name|NULL
argument_list|)
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
name|image_grid_get_spacing_proc
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
name|pdb_float
operator|=
name|xspacing
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_float
operator|=
name|yspacing
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_grid_get_spacing_inargs
specifier|static
name|ProcArg
name|image_grid_get_spacing_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_get_spacing_outargs
specifier|static
name|ProcArg
name|image_grid_get_spacing_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"xspacing"
block|,
literal|"The image's grid horizontal spacing"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"yspacing"
block|,
literal|"The image's grid vertical spacing"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_get_spacing_proc
specifier|static
name|ProcRecord
name|image_grid_get_spacing_proc
init|=
block|{
literal|"gimp-image-grid-get-spacing"
block|,
literal|"gimp-image-grid-get-spacing"
block|,
literal|"Gets the spacing of an image's grid."
block|,
literal|"This procedure retrieves the horizontal and vertical spacing of an image's grid. It takes the image as parameter."
block|,
literal|"Sylvain Foret"
block|,
literal|"Sylvain Foret"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|image_grid_get_spacing_inargs
block|,
literal|2
block|,
name|image_grid_get_spacing_outargs
block|,
block|{
block|{
name|image_grid_get_spacing_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_grid_set_spacing_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_grid_set_spacing_invoker
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
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gdouble
name|xspacing
decl_stmt|;
name|gdouble
name|yspacing
decl_stmt|;
name|image
operator|=
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
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
operator|!
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|xspacing
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|yspacing
operator|=
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpGrid
modifier|*
name|grid
init|=
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|grid
condition|)
name|g_object_set
argument_list|(
name|grid
argument_list|,
literal|"xspacing"
argument_list|,
name|xspacing
argument_list|,
literal|"yspacing"
argument_list|,
name|yspacing
argument_list|,
name|NULL
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
name|image_grid_set_spacing_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_grid_set_spacing_inargs
specifier|static
name|ProcArg
name|image_grid_set_spacing_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"xspacing"
block|,
literal|"The image's grid horizontal spacing"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"yspacing"
block|,
literal|"The image's grid vertical spacing"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_set_spacing_proc
specifier|static
name|ProcRecord
name|image_grid_set_spacing_proc
init|=
block|{
literal|"gimp-image-grid-set-spacing"
block|,
literal|"gimp-image-grid-set-spacing"
block|,
literal|"Sets the spacing of an image's grid."
block|,
literal|"This procedure sets the horizontal and vertical spacing of an image's grid."
block|,
literal|"Sylvain Foret"
block|,
literal|"Sylvain Foret"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|3
block|,
name|image_grid_set_spacing_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_grid_set_spacing_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_grid_get_offset_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_grid_get_offset_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gdouble
name|xoffset
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|yoffset
init|=
literal|0.0
decl_stmt|;
name|image
operator|=
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
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
operator|!
name|GIMP_IS_IMAGE
argument_list|(
name|image
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
name|GimpGrid
modifier|*
name|grid
init|=
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|grid
condition|)
name|g_object_get
argument_list|(
name|grid
argument_list|,
literal|"xoffset"
argument_list|,
operator|&
name|xoffset
argument_list|,
literal|"yoffset"
argument_list|,
operator|&
name|yoffset
argument_list|,
name|NULL
argument_list|)
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
name|image_grid_get_offset_proc
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
name|pdb_float
operator|=
name|xoffset
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_float
operator|=
name|yoffset
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_grid_get_offset_inargs
specifier|static
name|ProcArg
name|image_grid_get_offset_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_get_offset_outargs
specifier|static
name|ProcArg
name|image_grid_get_offset_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"xoffset"
block|,
literal|"The image's grid horizontal offset"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"yoffset"
block|,
literal|"The image's grid vertical offset"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_get_offset_proc
specifier|static
name|ProcRecord
name|image_grid_get_offset_proc
init|=
block|{
literal|"gimp-image-grid-get-offset"
block|,
literal|"gimp-image-grid-get-offset"
block|,
literal|"Gets the offset of an image's grid."
block|,
literal|"This procedure retrieves the horizontal and vertical offset of an image's grid. It takes the image as parameter."
block|,
literal|"Sylvain Foret"
block|,
literal|"Sylvain Foret"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|image_grid_get_offset_inargs
block|,
literal|2
block|,
name|image_grid_get_offset_outargs
block|,
block|{
block|{
name|image_grid_get_offset_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_grid_set_offset_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_grid_set_offset_invoker
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
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gdouble
name|xoffset
decl_stmt|;
name|gdouble
name|yoffset
decl_stmt|;
name|image
operator|=
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
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
operator|!
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|xoffset
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|yoffset
operator|=
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpGrid
modifier|*
name|grid
init|=
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|grid
condition|)
name|g_object_set
argument_list|(
name|grid
argument_list|,
literal|"xoffset"
argument_list|,
name|xoffset
argument_list|,
literal|"yoffset"
argument_list|,
name|yoffset
argument_list|,
name|NULL
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
name|image_grid_set_offset_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_grid_set_offset_inargs
specifier|static
name|ProcArg
name|image_grid_set_offset_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"xoffset"
block|,
literal|"The image's grid horizontal offset"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"yoffset"
block|,
literal|"The image's grid vertical offset"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_set_offset_proc
specifier|static
name|ProcRecord
name|image_grid_set_offset_proc
init|=
block|{
literal|"gimp-image-grid-set-offset"
block|,
literal|"gimp-image-grid-set-offset"
block|,
literal|"Sets the offset of an image's grid."
block|,
literal|"This procedure sets the horizontal and vertical offset of an image's grid."
block|,
literal|"Sylvain Foret"
block|,
literal|"Sylvain Foret"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|3
block|,
name|image_grid_set_offset_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_grid_set_offset_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_grid_get_foreground_color_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_grid_get_foreground_color_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpRGB
name|fgcolor
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
name|image
operator|=
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
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
operator|!
name|GIMP_IS_IMAGE
argument_list|(
name|image
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
name|GimpGrid
modifier|*
name|grid
init|=
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|grid
condition|)
name|fgcolor
operator|=
name|grid
operator|->
name|fgcolor
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
name|image_grid_get_foreground_color_proc
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
name|pdb_color
operator|=
name|fgcolor
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_grid_get_foreground_color_inargs
specifier|static
name|ProcArg
name|image_grid_get_foreground_color_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_get_foreground_color_outargs
specifier|static
name|ProcArg
name|image_grid_get_foreground_color_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_COLOR
block|,
literal|"fgcolor"
block|,
literal|"The image's grid foreground color"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_get_foreground_color_proc
specifier|static
name|ProcRecord
name|image_grid_get_foreground_color_proc
init|=
block|{
literal|"gimp-image-grid-get-foreground-color"
block|,
literal|"gimp-image-grid-get-foreground-color"
block|,
literal|"Sets the foreground color of an image's grid."
block|,
literal|"This procedure gets the foreground color of an image's grid."
block|,
literal|"Sylvain Foret"
block|,
literal|"Sylvain Foret"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|image_grid_get_foreground_color_inargs
block|,
literal|1
block|,
name|image_grid_get_foreground_color_outargs
block|,
block|{
block|{
name|image_grid_get_foreground_color_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_grid_set_foreground_color_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_grid_set_foreground_color_invoker
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
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpRGB
name|fgcolor
decl_stmt|;
name|image
operator|=
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
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
operator|!
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|fgcolor
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_color
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpGrid
modifier|*
name|grid
init|=
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|grid
condition|)
name|g_object_set
argument_list|(
name|grid
argument_list|,
literal|"fgcolor"
argument_list|,
operator|&
name|fgcolor
argument_list|,
name|NULL
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
name|image_grid_set_foreground_color_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_grid_set_foreground_color_inargs
specifier|static
name|ProcArg
name|image_grid_set_foreground_color_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|GIMP_PDB_COLOR
block|,
literal|"fgcolor"
block|,
literal|"The new foreground color"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_set_foreground_color_proc
specifier|static
name|ProcRecord
name|image_grid_set_foreground_color_proc
init|=
block|{
literal|"gimp-image-grid-set-foreground-color"
block|,
literal|"gimp-image-grid-set-foreground-color"
block|,
literal|"Gets the foreground color of an image's grid."
block|,
literal|"This procedure sets the foreground color of an image's grid."
block|,
literal|"Sylvain Foret"
block|,
literal|"Sylvain Foret"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|image_grid_set_foreground_color_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_grid_set_foreground_color_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_grid_get_background_color_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_grid_get_background_color_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpRGB
name|bgcolor
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
name|image
operator|=
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
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
operator|!
name|GIMP_IS_IMAGE
argument_list|(
name|image
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
name|GimpGrid
modifier|*
name|grid
init|=
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|grid
condition|)
name|bgcolor
operator|=
name|grid
operator|->
name|bgcolor
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
name|image_grid_get_background_color_proc
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
name|pdb_color
operator|=
name|bgcolor
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_grid_get_background_color_inargs
specifier|static
name|ProcArg
name|image_grid_get_background_color_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_get_background_color_outargs
specifier|static
name|ProcArg
name|image_grid_get_background_color_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_COLOR
block|,
literal|"bgcolor"
block|,
literal|"The image's grid background color"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_get_background_color_proc
specifier|static
name|ProcRecord
name|image_grid_get_background_color_proc
init|=
block|{
literal|"gimp-image-grid-get-background-color"
block|,
literal|"gimp-image-grid-get-background-color"
block|,
literal|"Sets the background color of an image's grid."
block|,
literal|"This procedure gets the background color of an image's grid."
block|,
literal|"Sylvain Foret"
block|,
literal|"Sylvain Foret"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|image_grid_get_background_color_inargs
block|,
literal|1
block|,
name|image_grid_get_background_color_outargs
block|,
block|{
block|{
name|image_grid_get_background_color_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_grid_set_background_color_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_grid_set_background_color_invoker
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
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpRGB
name|bgcolor
decl_stmt|;
name|image
operator|=
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
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
operator|!
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|bgcolor
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_color
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpGrid
modifier|*
name|grid
init|=
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|grid
condition|)
name|g_object_set
argument_list|(
name|grid
argument_list|,
literal|"bgcolor"
argument_list|,
operator|&
name|bgcolor
argument_list|,
name|NULL
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
name|image_grid_set_background_color_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_grid_set_background_color_inargs
specifier|static
name|ProcArg
name|image_grid_set_background_color_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|GIMP_PDB_COLOR
block|,
literal|"bgcolor"
block|,
literal|"The new background color"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_set_background_color_proc
specifier|static
name|ProcRecord
name|image_grid_set_background_color_proc
init|=
block|{
literal|"gimp-image-grid-set-background-color"
block|,
literal|"gimp-image-grid-set-background-color"
block|,
literal|"Gets the background color of an image's grid."
block|,
literal|"This procedure sets the background color of an image's grid."
block|,
literal|"Sylvain Foret"
block|,
literal|"Sylvain Foret"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|image_grid_set_background_color_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_grid_set_background_color_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_grid_get_style_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_grid_get_style_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gint32
name|style
init|=
literal|0
decl_stmt|;
name|image
operator|=
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
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
operator|!
name|GIMP_IS_IMAGE
argument_list|(
name|image
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
name|GimpGrid
modifier|*
name|grid
init|=
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|grid
condition|)
name|g_object_get
argument_list|(
name|grid
argument_list|,
literal|"style"
argument_list|,
operator|&
name|style
argument_list|,
name|NULL
argument_list|)
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
name|image_grid_get_style_proc
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
name|style
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_grid_get_style_inargs
specifier|static
name|ProcArg
name|image_grid_get_style_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_get_style_outargs
specifier|static
name|ProcArg
name|image_grid_get_style_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"style"
block|,
literal|"The image's grid style: { GIMP_GRID_DOTS (0), GIMP_GRID_INTERSECTIONS (1), GIMP_GRID_ON_OFF_DASH (2), GIMP_GRID_DOUBLE_DASH (3), GIMP_GRID_SOLID (4) }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_get_style_proc
specifier|static
name|ProcRecord
name|image_grid_get_style_proc
init|=
block|{
literal|"gimp-image-grid-get-style"
block|,
literal|"gimp-image-grid-get-style"
block|,
literal|"Gets the style of an image's grid."
block|,
literal|"This procedure retrieves the style of an image's grid."
block|,
literal|"Sylvain Foret"
block|,
literal|"Sylvain Foret"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|image_grid_get_style_inargs
block|,
literal|1
block|,
name|image_grid_get_style_outargs
block|,
block|{
block|{
name|image_grid_get_style_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_grid_set_style_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|image_grid_set_style_invoker
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
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gint32
name|style
decl_stmt|;
name|image
operator|=
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
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
operator|!
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|style
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
name|style
operator|<
name|GIMP_GRID_DOTS
operator|||
name|style
operator|>
name|GIMP_GRID_SOLID
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
name|GimpGrid
modifier|*
name|grid
init|=
name|gimp_image_get_grid
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|grid
condition|)
name|g_object_set
argument_list|(
name|grid
argument_list|,
literal|"style"
argument_list|,
name|style
argument_list|,
name|NULL
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
name|image_grid_set_style_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_grid_set_style_inargs
specifier|static
name|ProcArg
name|image_grid_set_style_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"style"
block|,
literal|"The image's grid style: { GIMP_GRID_DOTS (0), GIMP_GRID_INTERSECTIONS (1), GIMP_GRID_ON_OFF_DASH (2), GIMP_GRID_DOUBLE_DASH (3), GIMP_GRID_SOLID (4) }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_grid_set_style_proc
specifier|static
name|ProcRecord
name|image_grid_set_style_proc
init|=
block|{
literal|"gimp-image-grid-set-style"
block|,
literal|"gimp-image-grid-set-style"
block|,
literal|"Sets the style unit of an image's grid."
block|,
literal|"This procedure sets the style of an image's grid. It takes the image and the new style as parameters."
block|,
literal|"Sylvain Foret"
block|,
literal|"Sylvain Foret"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|image_grid_set_style_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_grid_set_style_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

