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
file|<string.h>
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
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpanchor.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpbezierstroke.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors-compat.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_decl_stmt
DECL|variable|vectors_get_strokes_proc
specifier|static
name|ProcRecord
name|vectors_get_strokes_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_stroke_translate_proc
specifier|static
name|ProcRecord
name|vectors_stroke_translate_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_vectors_procs (Gimp * gimp)
name|register_vectors_procs
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
name|vectors_get_strokes_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|vectors_stroke_translate_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|vectors_get_strokes_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|vectors_get_strokes_invoker
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
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|gint32
name|num_strokes
init|=
literal|0
decl_stmt|;
name|gint32
modifier|*
name|stroke_ids
init|=
name|NULL
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
name|GimpStroke
modifier|*
name|cur_stroke
init|=
name|NULL
decl_stmt|;
name|vectors
operator|=
operator|(
name|GimpVectors
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
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
operator|&&
operator|!
name|gimp_item_is_removed
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
operator|)
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
name|num_strokes
operator|=
name|gimp_vectors_get_n_strokes
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_strokes
condition|)
block|{
name|stroke_ids
operator|=
name|g_new
argument_list|(
name|gint32
argument_list|,
name|num_strokes
argument_list|)
expr_stmt|;
for|for
control|(
name|cur_stroke
operator|=
name|gimp_vectors_stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|NULL
argument_list|)
init|;
name|cur_stroke
condition|;
name|cur_stroke
operator|=
name|gimp_vectors_stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|cur_stroke
argument_list|)
control|)
block|{
name|stroke_ids
index|[
name|i
index|]
operator|=
name|gimp_stroke_get_ID
argument_list|(
name|cur_stroke
argument_list|)
expr_stmt|;
name|i
operator|++
expr_stmt|;
block|}
block|}
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|vectors_get_strokes_proc
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
name|pdb_int
operator|=
name|num_strokes
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|stroke_ids
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|vectors_get_strokes_inargs
specifier|static
name|ProcArg
name|vectors_get_strokes_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_PATH
block|,
literal|"vectors"
block|,
literal|"The vectors object"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_get_strokes_outargs
specifier|static
name|ProcArg
name|vectors_get_strokes_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"num_strokes"
block|,
literal|"The number of strokes returned."
block|}
block|,
block|{
name|GIMP_PDB_INT32ARRAY
block|,
literal|"stroke_ids"
block|,
literal|"List of the strokes belonging to the path."
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_get_strokes_proc
specifier|static
name|ProcRecord
name|vectors_get_strokes_proc
init|=
block|{
literal|"gimp_vectors_get_strokes"
block|,
literal|"List the strokes associated with the passed path."
block|,
literal|"Returns an Array with the stroke-IDs associated with the passed path."
block|,
literal|"Simon Budig"
block|,
literal|"Simon Budig"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|vectors_get_strokes_inargs
block|,
literal|2
block|,
name|vectors_get_strokes_outargs
block|,
block|{
block|{
name|vectors_get_strokes_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|vectors_stroke_translate_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|vectors_stroke_translate_invoker
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
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|gint32
name|stroke_id
decl_stmt|;
name|gint32
name|offx
decl_stmt|;
name|gint32
name|offy
decl_stmt|;
name|GimpStroke
modifier|*
name|stroke
decl_stmt|;
name|vectors
operator|=
operator|(
name|GimpVectors
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
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
operator|&&
operator|!
name|gimp_item_is_removed
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
operator|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|stroke_id
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
name|offx
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
name|offy
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
name|success
condition|)
block|{
name|GimpImage
modifier|*
name|gimage
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
decl_stmt|;
name|stroke
operator|=
name|gimp_vectors_stroke_get_by_ID
argument_list|(
name|vectors
argument_list|,
name|stroke_id
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|stroke
condition|)
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
comment|/* need to figure out how undo is supposed to work */
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_ITEM_DISPLACE
argument_list|,
name|_
argument_list|(
literal|"Modify Path"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_vectors_freeze
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
name|gimp_stroke_translate
argument_list|(
name|stroke
argument_list|,
name|offx
argument_list|,
name|offy
argument_list|)
expr_stmt|;
name|gimp_vectors_thaw
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|vectors_stroke_translate_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|vectors_stroke_translate_inargs
specifier|static
name|ProcArg
name|vectors_stroke_translate_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_PATH
block|,
literal|"vectors"
block|,
literal|"The vectors object"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"stroke_id"
block|,
literal|"The stroke ID"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"offx"
block|,
literal|"Offset in x direction"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"offy"
block|,
literal|"Offset in y direction"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_stroke_translate_proc
specifier|static
name|ProcRecord
name|vectors_stroke_translate_proc
init|=
block|{
literal|"gimp_vectors_stroke_translate"
block|,
literal|"return coordinates along the given stroke."
block|,
literal|"Returns a lot of coordinates along the passed stroke."
block|,
literal|"Simon Budig"
block|,
literal|"Simon Budig"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|4
block|,
name|vectors_stroke_translate_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|vectors_stroke_translate_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

