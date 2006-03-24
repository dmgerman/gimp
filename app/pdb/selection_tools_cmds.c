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
file|"core/gimpchannel-select.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|by_color_select_proc
specifier|static
name|ProcRecord
name|by_color_select_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ellipse_select_proc
specifier|static
name|ProcRecord
name|ellipse_select_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|free_select_proc
specifier|static
name|ProcRecord
name|free_select_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fuzzy_select_proc
specifier|static
name|ProcRecord
name|fuzzy_select_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rect_select_proc
specifier|static
name|ProcRecord
name|rect_select_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_selection_tools_procs (Gimp * gimp)
name|register_selection_tools_procs
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
name|by_color_select_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|ellipse_select_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|free_select_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|fuzzy_select_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|rect_select_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|by_color_select_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|by_color_select_invoker
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gint32
name|threshold
decl_stmt|;
name|gint32
name|operation
decl_stmt|;
name|gboolean
name|antialias
decl_stmt|;
name|gboolean
name|feather
decl_stmt|;
name|gdouble
name|feather_radius
decl_stmt|;
name|gboolean
name|sample_merged
decl_stmt|;
name|drawable
operator|=
operator|(
name|GimpDrawable
operator|*
operator|)
name|gimp_item_get_by_ID
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
operator|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
operator|&&
operator|!
name|gimp_item_is_removed
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|color
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
name|threshold
operator|=
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|threshold
operator|<
literal|0
operator|||
name|threshold
operator|>
literal|255
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|operation
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|operation
operator|<
name|GIMP_CHANNEL_OP_ADD
operator|||
name|operation
operator|>
name|GIMP_CHANNEL_OP_INTERSECT
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|antialias
operator|=
name|args
index|[
literal|4
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
name|feather
operator|=
name|args
index|[
literal|5
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
name|feather_radius
operator|=
name|args
index|[
literal|6
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|feather_radius
operator|<
literal|0.0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|sample_merged
operator|=
name|args
index|[
literal|7
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
if|if
condition|(
name|success
condition|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_channel_select_by_color
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|sample_merged
argument_list|,
operator|&
name|color
argument_list|,
name|threshold
argument_list|,
name|FALSE
comment|/* don't select transparent */
argument_list|,
name|operation
argument_list|,
name|antialias
argument_list|,
name|feather
argument_list|,
name|feather_radius
argument_list|,
name|feather_radius
argument_list|)
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|by_color_select_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|by_color_select_inargs
specifier|static
name|ProcArg
name|by_color_select_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The affected drawable"
block|}
block|,
block|{
name|GIMP_PDB_COLOR
block|,
literal|"color"
block|,
literal|"The color to select"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"threshold"
block|,
literal|"Threshold in intensity levels (0<= threshold<= 255)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"operation"
block|,
literal|"The selection operation: { GIMP_CHANNEL_OP_ADD (0), GIMP_CHANNEL_OP_SUBTRACT (1), GIMP_CHANNEL_OP_REPLACE (2), GIMP_CHANNEL_OP_INTERSECT (3) }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"antialias"
block|,
literal|"Antialiasing (TRUE or FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"feather"
block|,
literal|"Feather option for selections"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"feather-radius"
block|,
literal|"Radius for feather operation"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"sample-merged"
block|,
literal|"Use the composite image, not the drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|by_color_select_proc
specifier|static
name|ProcRecord
name|by_color_select_proc
init|=
block|{
literal|"gimp-by-color-select"
block|,
literal|"gimp-by-color-select"
block|,
literal|"Create a selection by selecting all pixels (in the specified drawable) with the same (or similar) color to that specified."
block|,
literal|"This tool creates a selection over the specified image. A by-color selection is determined by the supplied color under the constraints of the specified threshold. Essentially, all pixels (in the drawable) that have color sufficiently close to the specified color (as determined by the threshold value) are included in the selection. The antialiasing parameter allows the final selection mask to contain intermediate values based on close misses to the threshold bar. Feathering can be enabled optionally and is controlled with the \"feather_radius\" parameter. If the sample_merged parameter is TRUE, the data of the composite image will be used instead of that for the specified drawable. This is equivalent to sampling for colors after merging all visible layers. In the case of a merged sampling, the supplied drawable is ignored."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|8
block|,
name|by_color_select_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|by_color_select_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|ellipse_select_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|ellipse_select_invoker
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
name|x
decl_stmt|;
name|gdouble
name|y
decl_stmt|;
name|gdouble
name|width
decl_stmt|;
name|gdouble
name|height
decl_stmt|;
name|gint32
name|operation
decl_stmt|;
name|gboolean
name|antialias
decl_stmt|;
name|gboolean
name|feather
decl_stmt|;
name|gdouble
name|feather_radius
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
name|x
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
name|y
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
name|width
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|width
operator|<=
literal|0.0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|height
operator|=
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|height
operator|<=
literal|0.0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|operation
operator|=
name|args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|operation
operator|<
name|GIMP_CHANNEL_OP_ADD
operator|||
name|operation
operator|>
name|GIMP_CHANNEL_OP_INTERSECT
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|antialias
operator|=
name|args
index|[
literal|6
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
name|feather
operator|=
name|args
index|[
literal|7
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
name|feather_radius
operator|=
name|args
index|[
literal|8
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|feather_radius
operator|<
literal|0.0
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
name|gimp_channel_select_ellipse
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
name|x
argument_list|,
operator|(
name|gint
operator|)
name|y
argument_list|,
operator|(
name|gint
operator|)
name|width
argument_list|,
operator|(
name|gint
operator|)
name|height
argument_list|,
name|operation
argument_list|,
name|antialias
argument_list|,
name|feather
argument_list|,
name|feather_radius
argument_list|,
name|feather_radius
argument_list|)
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|ellipse_select_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|ellipse_select_inargs
specifier|static
name|ProcArg
name|ellipse_select_inargs
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
literal|"x"
block|,
literal|"x coordinate of upper-left corner of ellipse bounding box"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y"
block|,
literal|"y coordinate of upper-left corner of ellipse bounding box"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"width"
block|,
literal|"The width of the ellipse (0< width)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"height"
block|,
literal|"The height of the ellipse (0< height)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"operation"
block|,
literal|"The selection operation: { GIMP_CHANNEL_OP_ADD (0), GIMP_CHANNEL_OP_SUBTRACT (1), GIMP_CHANNEL_OP_REPLACE (2), GIMP_CHANNEL_OP_INTERSECT (3) }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"antialias"
block|,
literal|"Antialiasing (TRUE or FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"feather"
block|,
literal|"Feather option for selections"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"feather-radius"
block|,
literal|"Radius for feather operation"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ellipse_select_proc
specifier|static
name|ProcRecord
name|ellipse_select_proc
init|=
block|{
literal|"gimp-ellipse-select"
block|,
literal|"gimp-ellipse-select"
block|,
literal|"Create an elliptical selection over the specified image."
block|,
literal|"This tool creates an elliptical selection over the specified image. The elliptical region can be either added to, subtracted from, or replace the contents of the previous selection mask. If antialiasing is turned on, the edges of the elliptical region will contain intermediate values which give the appearance of a sharper, less pixelized edge. This should be set as TRUE most of the time. If the feather option is enabled, the resulting selection is blurred before combining. The blur is a gaussian blur with the specified feather radius."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|9
block|,
name|ellipse_select_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|ellipse_select_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|free_select_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|free_select_invoker
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
name|num_segs
decl_stmt|;
name|gdouble
modifier|*
name|segs
decl_stmt|;
name|gint32
name|operation
decl_stmt|;
name|gboolean
name|antialias
decl_stmt|;
name|gboolean
name|feather
decl_stmt|;
name|gdouble
name|feather_radius
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
name|num_segs
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
name|num_segs
operator|<
literal|2
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|segs
operator|=
operator|(
name|gdouble
operator|*
operator|)
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
name|operation
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|operation
operator|<
name|GIMP_CHANNEL_OP_ADD
operator|||
name|operation
operator|>
name|GIMP_CHANNEL_OP_INTERSECT
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|antialias
operator|=
name|args
index|[
literal|4
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
name|feather
operator|=
name|args
index|[
literal|5
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
name|feather_radius
operator|=
name|args
index|[
literal|6
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|feather_radius
operator|<
literal|0.0
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
name|gimp_channel_select_polygon
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Free Select"
argument_list|)
argument_list|,
name|num_segs
operator|/
literal|2
argument_list|,
operator|(
name|GimpVector2
operator|*
operator|)
name|segs
argument_list|,
name|operation
argument_list|,
name|antialias
argument_list|,
name|feather
argument_list|,
name|feather_radius
argument_list|,
name|feather_radius
argument_list|)
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|free_select_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|free_select_inargs
specifier|static
name|ProcArg
name|free_select_inargs
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
literal|"num-segs"
block|,
literal|"Number of points (count 1 coordinate as two points)"
block|}
block|,
block|{
name|GIMP_PDB_FLOATARRAY
block|,
literal|"segs"
block|,
literal|"Array of points: { p1.x, p1.y, p2.x, p2.y, ..., pn.x, pn.y}"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"operation"
block|,
literal|"The selection operation: { GIMP_CHANNEL_OP_ADD (0), GIMP_CHANNEL_OP_SUBTRACT (1), GIMP_CHANNEL_OP_REPLACE (2), GIMP_CHANNEL_OP_INTERSECT (3) }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"antialias"
block|,
literal|"Antialiasing (TRUE or FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"feather"
block|,
literal|"Feather option for selections"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"feather-radius"
block|,
literal|"Radius for feather operation"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|free_select_proc
specifier|static
name|ProcRecord
name|free_select_proc
init|=
block|{
literal|"gimp-free-select"
block|,
literal|"gimp-free-select"
block|,
literal|"Create a polygonal selection over the specified image."
block|,
literal|"This tool creates a polygonal selection over the specified image. The polygonal region can be either added to, subtracted from, or replace the contents of the previous selection mask. The polygon is specified through an array of floating point numbers and its length. The length of array must be 2n, where n is the number of points. Each point is defined by 2 floating point values which correspond to the x and y coordinates. If the final point does not connect to the starting point, a connecting segment is automatically added. If the feather option is enabled, the resulting selection is blurred before combining. The blur is a gaussian blur with the specified feather radius."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|7
block|,
name|free_select_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|free_select_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|fuzzy_select_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|fuzzy_select_invoker
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gdouble
name|x
decl_stmt|;
name|gdouble
name|y
decl_stmt|;
name|gint32
name|threshold
decl_stmt|;
name|gint32
name|operation
decl_stmt|;
name|gboolean
name|antialias
decl_stmt|;
name|gboolean
name|feather
decl_stmt|;
name|gdouble
name|feather_radius
decl_stmt|;
name|gboolean
name|sample_merged
decl_stmt|;
name|drawable
operator|=
operator|(
name|GimpDrawable
operator|*
operator|)
name|gimp_item_get_by_ID
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
operator|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
operator|&&
operator|!
name|gimp_item_is_removed
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|x
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
name|y
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
name|threshold
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|threshold
operator|<
literal|0
operator|||
name|threshold
operator|>
literal|255
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|operation
operator|=
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|operation
operator|<
name|GIMP_CHANNEL_OP_ADD
operator|||
name|operation
operator|>
name|GIMP_CHANNEL_OP_INTERSECT
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|antialias
operator|=
name|args
index|[
literal|5
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
name|feather
operator|=
name|args
index|[
literal|6
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
name|feather_radius
operator|=
name|args
index|[
literal|7
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|feather_radius
operator|<
literal|0.0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|sample_merged
operator|=
name|args
index|[
literal|8
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
if|if
condition|(
name|success
condition|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_channel_select_fuzzy
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|sample_merged
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|threshold
argument_list|,
name|FALSE
comment|/* don't select transparent */
argument_list|,
name|operation
argument_list|,
name|antialias
argument_list|,
name|feather
argument_list|,
name|feather_radius
argument_list|,
name|feather_radius
argument_list|)
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|fuzzy_select_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|fuzzy_select_inargs
specifier|static
name|ProcArg
name|fuzzy_select_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The affected drawable"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"x"
block|,
literal|"x coordinate of initial seed fill point: (image coordinates)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y"
block|,
literal|"y coordinate of initial seed fill point: (image coordinates)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"threshold"
block|,
literal|"Threshold in intensity levels (0<= threshold<= 255)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"operation"
block|,
literal|"The selection operation: { GIMP_CHANNEL_OP_ADD (0), GIMP_CHANNEL_OP_SUBTRACT (1), GIMP_CHANNEL_OP_REPLACE (2), GIMP_CHANNEL_OP_INTERSECT (3) }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"antialias"
block|,
literal|"Antialiasing (TRUE or FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"feather"
block|,
literal|"Feather option for selections"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"feather-radius"
block|,
literal|"Radius for feather operation"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"sample-merged"
block|,
literal|"Use the composite image, not the drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fuzzy_select_proc
specifier|static
name|ProcRecord
name|fuzzy_select_proc
init|=
block|{
literal|"gimp-fuzzy-select"
block|,
literal|"gimp-fuzzy-select"
block|,
literal|"Create a fuzzy selection starting at the specified coordinates on the specified drawable."
block|,
literal|"This tool creates a fuzzy selection over the specified image. A fuzzy selection is determined by a seed fill under the constraints of the specified threshold. Essentially, the color at the specified coordinates (in the drawable) is measured and the selection expands outwards from that point to any adjacent pixels which are not significantly different (as determined by the threshold value). This process continues until no more expansion is possible. The antialiasing parameter allows the final selection mask to contain intermediate values based on close misses to the threshold bar at pixels along the seed fill boundary. Feathering can be enabled optionally and is controlled with the \"feather_radius\" paramter. If the sample_merged parameter is TRUE, the data of the composite image will be used instead of that for the specified drawable. This is equivalent to sampling for colors after merging all visible layers. In the case of a merged sampling, the supplied drawable is ignored. If"
literal|"the sample is merged, the specified coordinates are relative to the image origin; otherwise, they are relative to the drawable's origin."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|9
block|,
name|fuzzy_select_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|fuzzy_select_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|rect_select_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|rect_select_invoker
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
name|x
decl_stmt|;
name|gdouble
name|y
decl_stmt|;
name|gdouble
name|width
decl_stmt|;
name|gdouble
name|height
decl_stmt|;
name|gint32
name|operation
decl_stmt|;
name|gboolean
name|feather
decl_stmt|;
name|gdouble
name|feather_radius
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
name|x
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
name|y
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
name|width
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|width
operator|<=
literal|0.0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|height
operator|=
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|height
operator|<=
literal|0.0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|operation
operator|=
name|args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|operation
operator|<
name|GIMP_CHANNEL_OP_ADD
operator|||
name|operation
operator|>
name|GIMP_CHANNEL_OP_INTERSECT
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|feather
operator|=
name|args
index|[
literal|6
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
name|feather_radius
operator|=
name|args
index|[
literal|7
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|feather_radius
operator|<
literal|0.0
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
name|gimp_channel_select_rectangle
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
name|x
argument_list|,
operator|(
name|gint
operator|)
name|y
argument_list|,
operator|(
name|gint
operator|)
name|width
argument_list|,
operator|(
name|gint
operator|)
name|height
argument_list|,
name|operation
argument_list|,
name|feather
argument_list|,
name|feather_radius
argument_list|,
name|feather_radius
argument_list|)
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|rect_select_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|rect_select_inargs
specifier|static
name|ProcArg
name|rect_select_inargs
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
literal|"x"
block|,
literal|"x coordinate of upper-left corner of rectangle"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y"
block|,
literal|"y coordinate of upper-left corner of rectangle"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"width"
block|,
literal|"The width of the rectangle (0< width)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"height"
block|,
literal|"The height of the rectangle (0< height)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"operation"
block|,
literal|"The selection operation: { GIMP_CHANNEL_OP_ADD (0), GIMP_CHANNEL_OP_SUBTRACT (1), GIMP_CHANNEL_OP_REPLACE (2), GIMP_CHANNEL_OP_INTERSECT (3) }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"feather"
block|,
literal|"Feather option for selections"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"feather-radius"
block|,
literal|"Radius for feather operation"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rect_select_proc
specifier|static
name|ProcRecord
name|rect_select_proc
init|=
block|{
literal|"gimp-rect-select"
block|,
literal|"gimp-rect-select"
block|,
literal|"Create a rectangular selection over the specified image;"
block|,
literal|"This tool creates a rectangular selection over the specified image. The rectangular region can be either added to, subtracted from, or replace the contents of the previous selection mask. If the feather option is enabled, the resulting selection is blurred before combining. The blur is a gaussian blur with the specified feather radius."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|8
block|,
name|rect_select_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|rect_select_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

