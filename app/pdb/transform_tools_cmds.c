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
file|"libgimpbase/gimpbasetypes.h"
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
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-transform-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-transform.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_decl_stmt
DECL|variable|flip_proc
specifier|static
name|ProcRecord
name|flip_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|perspective_proc
specifier|static
name|ProcRecord
name|perspective_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rotate_proc
specifier|static
name|ProcRecord
name|rotate_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|scale_proc
specifier|static
name|ProcRecord
name|scale_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|shear_proc
specifier|static
name|ProcRecord
name|shear_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|transform_2d_proc
specifier|static
name|ProcRecord
name|transform_2d_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_transform_tools_procs (Gimp * gimp)
name|register_transform_tools_procs
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
name|flip_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|perspective_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|rotate_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|scale_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|shear_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|transform_2d_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|flip_invoker (Gimp * gimp,Argument * args)
name|flip_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint32
name|flip_type
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
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|flip_type
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
name|flip_type
operator|<
name|GIMP_ORIENTATION_HORIZONTAL
operator|||
name|flip_type
operator|>
name|GIMP_ORIENTATION_VERTICAL
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
name|success
operator|=
name|gimp_drawable_transform_flip
argument_list|(
name|drawable
argument_list|,
name|flip_type
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|flip_proc
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
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|flip_inargs
specifier|static
name|ProcArg
name|flip_inargs
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
name|GIMP_PDB_INT32
block|,
literal|"flip_type"
block|,
literal|"Type of flip: GIMP_ORIENTATION_HORIZONTAL (0) or GIMP_ORIENTATION_VERTICAL (1)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|flip_outargs
specifier|static
name|ProcArg
name|flip_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The flipped drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|flip_proc
specifier|static
name|ProcRecord
name|flip_proc
init|=
block|{
literal|"gimp_flip"
block|,
literal|"Flip the specified drawable about its center either vertically or horizontally."
block|,
literal|"This tool flips the specified drawable if no selection exists. If a selection exists, the portion of the drawable which lies under the selection is cut from the drawable and made into a floating selection which is then flipd by the specified amount. The return value is the ID of the flipped drawable. If there was no selection, this will be equal to the drawable ID supplied as input. Otherwise, this will be the newly created and flipped drawable. The flip type parameter indicates whether the flip will be applied horizontally or vertically."
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
name|flip_inargs
block|,
literal|1
block|,
name|flip_outargs
block|,
block|{
block|{
name|flip_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|perspective_invoker (Gimp * gimp,Argument * args)
name|perspective_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gboolean
name|interpolation
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gdouble
name|trans_info
index|[
literal|8
index|]
decl_stmt|;
name|GimpMatrix3
name|matrix
decl_stmt|;
name|GimpInterpolationType
name|interpolation_type
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
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|interpolation
operator|=
name|args
index|[
literal|1
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
name|trans_info
index|[
name|X0
index|]
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
name|trans_info
index|[
name|Y0
index|]
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
name|trans_info
index|[
name|X1
index|]
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
name|trans_info
index|[
name|Y1
index|]
operator|=
name|args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|trans_info
index|[
name|X2
index|]
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
name|trans_info
index|[
name|Y2
index|]
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
name|trans_info
index|[
name|X3
index|]
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
name|trans_info
index|[
name|Y3
index|]
operator|=
name|args
index|[
literal|9
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
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
comment|/* Assemble the transformation matrix */
name|gimp_transform_matrix_perspective
argument_list|(
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|trans_info
index|[
name|X0
index|]
argument_list|,
name|trans_info
index|[
name|Y0
index|]
argument_list|,
name|trans_info
index|[
name|X1
index|]
argument_list|,
name|trans_info
index|[
name|Y1
index|]
argument_list|,
name|trans_info
index|[
name|X2
index|]
argument_list|,
name|trans_info
index|[
name|Y2
index|]
argument_list|,
name|trans_info
index|[
name|X3
index|]
argument_list|,
name|trans_info
index|[
name|Y3
index|]
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
if|if
condition|(
name|interpolation
condition|)
name|interpolation_type
operator|=
name|gimp
operator|->
name|config
operator|->
name|interpolation_type
expr_stmt|;
else|else
name|interpolation_type
operator|=
name|GIMP_INTERPOLATION_NONE
expr_stmt|;
comment|/* Perspective the selection */
name|success
operator|=
name|gimp_drawable_transform_affine
argument_list|(
name|drawable
argument_list|,
operator|&
name|matrix
argument_list|,
name|GIMP_TRANSFORM_FORWARD
argument_list|,
name|interpolation_type
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|perspective_proc
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
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|perspective_inargs
specifier|static
name|ProcArg
name|perspective_inargs
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
name|GIMP_PDB_INT32
block|,
literal|"interpolation"
block|,
literal|"Whether to use interpolation"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"x0"
block|,
literal|"The new x coordinate of upper-left corner of original bounding box"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y0"
block|,
literal|"The new y coordinate of upper-left corner of original bounding box"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"x1"
block|,
literal|"The new x coordinate of upper-right corner of original bounding box"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y1"
block|,
literal|"The new y coordinate of upper-right corner of original bounding box"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"x2"
block|,
literal|"The new x coordinate of lower-left corner of original bounding box"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y2"
block|,
literal|"The new y coordinate of lower-left corner of original bounding box"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"x3"
block|,
literal|"The new x coordinate of lower-right corner of original bounding box"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y3"
block|,
literal|"The new y coordinate of lower-right corner of original bounding box"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|perspective_outargs
specifier|static
name|ProcArg
name|perspective_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The newly mapped drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|perspective_proc
specifier|static
name|ProcRecord
name|perspective_proc
init|=
block|{
literal|"gimp_perspective"
block|,
literal|"Perform a possibly non-affine transformation on the specified drawable."
block|,
literal|"This tool performs a possibly non-affine transformation on the specified drawable by allowing the corners of the original bounding box to be arbitrarily remapped to any values. The specified drawable is remapped if no selection exists. However, if a selection exists, the portion of the drawable which lies under the selection is cut from the drawable and made into a floating selection which is then remapped as specified. The interpolation parameter can be set to TRUE to indicate that either linear or cubic interpolation should be used to smooth the resulting remapped drawable. The return value is the ID of the remapped drawable. If there was no selection, this will be equal to the drawable ID supplied as input. Otherwise, this will be the newly created and remapped drawable. The 4 coordinates specify the new locations of each corner of the original bounding box. By specifying these values, any affine transformation (rotation, scaling, translation) can be affected. Additionally,"
literal|"these values can be specified such that the resulting transformed drawable will appear to have been projected via a perspective transform."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|10
block|,
name|perspective_inargs
block|,
literal|1
block|,
name|perspective_outargs
block|,
block|{
block|{
name|perspective_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|rotate_invoker (Gimp * gimp,Argument * args)
name|rotate_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gboolean
name|interpolation
decl_stmt|;
name|gdouble
name|angle
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|GimpMatrix3
name|matrix
decl_stmt|;
name|GimpInterpolationType
name|interpolation_type
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
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|interpolation
operator|=
name|args
index|[
literal|1
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
name|angle
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
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
comment|/* Assemble the transformation matrix */
name|gimp_transform_matrix_rotate
argument_list|(
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|angle
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
if|if
condition|(
name|interpolation
condition|)
name|interpolation_type
operator|=
name|gimp
operator|->
name|config
operator|->
name|interpolation_type
expr_stmt|;
else|else
name|interpolation_type
operator|=
name|GIMP_INTERPOLATION_NONE
expr_stmt|;
comment|/* Rotate the selection */
name|success
operator|=
name|gimp_drawable_transform_affine
argument_list|(
name|drawable
argument_list|,
operator|&
name|matrix
argument_list|,
name|GIMP_TRANSFORM_FORWARD
argument_list|,
name|interpolation_type
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|rotate_proc
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
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|rotate_inargs
specifier|static
name|ProcArg
name|rotate_inargs
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
name|GIMP_PDB_INT32
block|,
literal|"interpolation"
block|,
literal|"Whether to use interpolation"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"angle"
block|,
literal|"The angle of rotation (radians)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rotate_outargs
specifier|static
name|ProcArg
name|rotate_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The rotated drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rotate_proc
specifier|static
name|ProcRecord
name|rotate_proc
init|=
block|{
literal|"gimp_rotate"
block|,
literal|"Rotate the specified drawable about its center through the specified angle."
block|,
literal|"This tool rotates the specified drawable if no selection exists. If a selection exists, the portion of the drawable which lies under the selection is cut from the drawable and made into a floating selection which is then rotated by the specified amount. The interpolation parameter can be set to TRUE to indicate that either linear or cubic interpolation should be used to smooth the resulting rotated drawable. The return value is the ID of the rotated drawable. If there was no selection, this will be equal to the drawable ID supplied as input. Otherwise, this will be the newly created and rotated drawable."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|3
block|,
name|rotate_inargs
block|,
literal|1
block|,
name|rotate_outargs
block|,
block|{
block|{
name|rotate_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|scale_invoker (Gimp * gimp,Argument * args)
name|scale_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gboolean
name|interpolation
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gdouble
name|trans_info
index|[
literal|4
index|]
decl_stmt|;
name|GimpMatrix3
name|matrix
decl_stmt|;
name|GimpInterpolationType
name|interpolation_type
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
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|interpolation
operator|=
name|args
index|[
literal|1
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
name|trans_info
index|[
name|X0
index|]
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
name|trans_info
index|[
name|Y0
index|]
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
name|trans_info
index|[
name|X1
index|]
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
name|trans_info
index|[
name|Y1
index|]
operator|=
name|args
index|[
literal|5
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
if|if
condition|(
name|trans_info
index|[
name|X0
index|]
operator|<
name|trans_info
index|[
name|X1
index|]
operator|&&
name|trans_info
index|[
name|Y0
index|]
operator|<
name|trans_info
index|[
name|X1
index|]
condition|)
block|{
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
comment|/* Assemble the transformation matrix */
name|gimp_transform_matrix_scale
argument_list|(
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|trans_info
index|[
name|X0
index|]
argument_list|,
name|trans_info
index|[
name|Y0
index|]
argument_list|,
name|trans_info
index|[
name|X1
index|]
argument_list|,
name|trans_info
index|[
name|Y1
index|]
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
if|if
condition|(
name|interpolation
condition|)
name|interpolation_type
operator|=
name|gimp
operator|->
name|config
operator|->
name|interpolation_type
expr_stmt|;
else|else
name|interpolation_type
operator|=
name|GIMP_INTERPOLATION_NONE
expr_stmt|;
comment|/* Scale the selection */
name|success
operator|=
name|gimp_drawable_transform_affine
argument_list|(
name|drawable
argument_list|,
operator|&
name|matrix
argument_list|,
name|GIMP_TRANSFORM_FORWARD
argument_list|,
name|interpolation_type
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|scale_proc
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
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|scale_inargs
specifier|static
name|ProcArg
name|scale_inargs
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
name|GIMP_PDB_INT32
block|,
literal|"interpolation"
block|,
literal|"Whether to use interpolation"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"x0"
block|,
literal|"The new x coordinate of upper-left corner of newly scaled region"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y0"
block|,
literal|"The new y coordinate of upper-left corner of newly scaled region"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"x1"
block|,
literal|"The new x coordinate of lower-right corner of newly scaled region"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y1"
block|,
literal|"The new y coordinate of lower-right corner of newly scaled region"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|scale_outargs
specifier|static
name|ProcArg
name|scale_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The scaled drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|scale_proc
specifier|static
name|ProcRecord
name|scale_proc
init|=
block|{
literal|"gimp_scale"
block|,
literal|"Scale the specified drawable."
block|,
literal|"This tool scales the specified drawable if no selection exists. If a selection exists, the portion of the drawable which lies under the selection is cut from the drawable and made into a floating selection which is then scaled by the specified amount. The interpolation parameter can be set to TRUE to indicate that either linear or cubic interpolation should be used to smooth the resulting scaled drawable. The return value is the ID of the scaled drawable. If there was no selection, this will be equal to the drawable ID supplied as input. Otherwise, this will be the newly created and scaled drawable."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|6
block|,
name|scale_inargs
block|,
literal|1
block|,
name|scale_outargs
block|,
block|{
block|{
name|scale_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|shear_invoker (Gimp * gimp,Argument * args)
name|shear_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gboolean
name|interpolation
decl_stmt|;
name|gint32
name|shear_type
decl_stmt|;
name|gdouble
name|magnitude
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|GimpMatrix3
name|matrix
decl_stmt|;
name|GimpInterpolationType
name|interpolation_type
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
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|interpolation
operator|=
name|args
index|[
literal|1
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
name|shear_type
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
name|shear_type
operator|<
name|GIMP_ORIENTATION_HORIZONTAL
operator|||
name|shear_type
operator|>
name|GIMP_ORIENTATION_VERTICAL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|magnitude
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
name|success
condition|)
block|{
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
comment|/* Assemble the transformation matrix */
name|gimp_transform_matrix_shear
argument_list|(
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|shear_type
argument_list|,
name|magnitude
argument_list|,
operator|&
name|matrix
argument_list|)
expr_stmt|;
if|if
condition|(
name|interpolation
condition|)
name|interpolation_type
operator|=
name|gimp
operator|->
name|config
operator|->
name|interpolation_type
expr_stmt|;
else|else
name|interpolation_type
operator|=
name|GIMP_INTERPOLATION_NONE
expr_stmt|;
comment|/* Shear the selection */
name|success
operator|=
name|gimp_drawable_transform_affine
argument_list|(
name|drawable
argument_list|,
operator|&
name|matrix
argument_list|,
name|GIMP_TRANSFORM_FORWARD
argument_list|,
name|interpolation_type
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|shear_proc
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
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|shear_inargs
specifier|static
name|ProcArg
name|shear_inargs
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
name|GIMP_PDB_INT32
block|,
literal|"interpolation"
block|,
literal|"Whether to use interpolation"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"shear_type"
block|,
literal|"Type of shear: GIMP_ORIENTATION_HORIZONTAL (0) or GIMP_ORIENTATION_VERTICAL (1)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"magnitude"
block|,
literal|"The magnitude of the shear"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|shear_outargs
specifier|static
name|ProcArg
name|shear_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The sheared drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|shear_proc
specifier|static
name|ProcRecord
name|shear_proc
init|=
block|{
literal|"gimp_shear"
block|,
literal|"Shear the specified drawable about its center by the specified magnitude."
block|,
literal|"This tool shears the specified drawable if no selection exists. If a selection exists, the portion of the drawable which lies under the selection is cut from the drawable and made into a floating selection which is then sheard by the specified amount. The interpolation parameter can be set to TRUE to indicate that either linear or cubic interpolation should be used to smooth the resulting sheared drawable. The return value is the ID of the sheard drawable. If there was no selection, this will be equal to the drawable ID supplied as input. Otherwise, this will be the newly created and sheard drawable. The shear type parameter indicates whether the shear will be applied horizontally or vertically. The magnitude can be either positive or negative and indicates the extent (in pixels) to shear by."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|4
block|,
name|shear_inargs
block|,
literal|1
block|,
name|shear_outargs
block|,
block|{
block|{
name|shear_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|transform_2d_invoker (Gimp * gimp,Argument * args)
name|transform_2d_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gboolean
name|interpolation
decl_stmt|;
name|gdouble
name|source_x
decl_stmt|;
name|gdouble
name|source_y
decl_stmt|;
name|gdouble
name|scale_x
decl_stmt|;
name|gdouble
name|scale_y
decl_stmt|;
name|gdouble
name|angle
decl_stmt|;
name|gdouble
name|dest_x
decl_stmt|;
name|gdouble
name|dest_y
decl_stmt|;
name|GimpMatrix3
name|matrix
decl_stmt|;
name|GimpInterpolationType
name|interpolation_type
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
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|interpolation
operator|=
name|args
index|[
literal|1
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
name|source_x
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
name|source_y
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
name|scale_x
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
name|scale_y
operator|=
name|args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|angle
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
name|dest_x
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
name|dest_y
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
name|success
condition|)
block|{
comment|/* Assemble the transformation matrix */
name|gimp_matrix3_identity
argument_list|(
operator|&
name|matrix
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
operator|&
name|matrix
argument_list|,
operator|-
name|source_x
argument_list|,
operator|-
name|source_y
argument_list|)
expr_stmt|;
name|gimp_matrix3_scale
argument_list|(
operator|&
name|matrix
argument_list|,
name|scale_x
argument_list|,
name|scale_y
argument_list|)
expr_stmt|;
name|gimp_matrix3_rotate
argument_list|(
operator|&
name|matrix
argument_list|,
name|angle
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
operator|&
name|matrix
argument_list|,
name|dest_x
argument_list|,
name|dest_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|interpolation
condition|)
name|interpolation_type
operator|=
name|gimp
operator|->
name|config
operator|->
name|interpolation_type
expr_stmt|;
else|else
name|interpolation_type
operator|=
name|GIMP_INTERPOLATION_NONE
expr_stmt|;
comment|/* Transform the selection */
name|success
operator|=
name|gimp_drawable_transform_affine
argument_list|(
name|drawable
argument_list|,
operator|&
name|matrix
argument_list|,
name|GIMP_TRANSFORM_FORWARD
argument_list|,
name|interpolation_type
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|transform_2d_proc
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
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|transform_2d_inargs
specifier|static
name|ProcArg
name|transform_2d_inargs
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
name|GIMP_PDB_INT32
block|,
literal|"interpolation"
block|,
literal|"Whether to use interpolation"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"source_x"
block|,
literal|"X coordinate of the transformation center"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"source_y"
block|,
literal|"Y coordinate of the transformation center"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"scale_x"
block|,
literal|"Amount to scale in x direction"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"scale_y"
block|,
literal|"Amount to scale in y direction"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"angle"
block|,
literal|"The angle of rotation (radians)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"dest_x"
block|,
literal|"X coordinate of where the centre goes"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"dest_y"
block|,
literal|"Y coordinate of where the centre goes"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|transform_2d_outargs
specifier|static
name|ProcArg
name|transform_2d_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The transformed drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|transform_2d_proc
specifier|static
name|ProcRecord
name|transform_2d_proc
init|=
block|{
literal|"gimp_transform_2d"
block|,
literal|"Transform the specified drawable in 2d."
block|,
literal|"This tool transforms the specified drawable if no selection exists. If a selection exists, the portion of the drawable which lies under the selection is cut from the drawable and made into a floating selection which is then transformed. The interpolation parameter can be set to TRUE to indicate that either linear or cubic interpolation should be used to smooth the resulting drawable. The transformation is done by scaling the image by the x and y scale factors about the point (source_x, source_y), then rotating around the same point, then translating that point to the new position (dest_x, dest_y). The return value is the ID of the rotated drawable. If there was no selection, this will be equal to the drawable ID supplied as input. Otherwise, this will be the newly created and transformed drawable."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|9
block|,
name|transform_2d_inargs
block|,
literal|1
block|,
name|transform_2d_outargs
block|,
block|{
block|{
name|transform_2d_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

