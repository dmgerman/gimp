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
file|"core/gimpimage-guides.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo-push.h"
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
DECL|variable|image_add_hguide_proc
specifier|static
name|ProcRecord
name|image_add_hguide_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_add_vguide_proc
specifier|static
name|ProcRecord
name|image_add_vguide_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_delete_guide_proc
specifier|static
name|ProcRecord
name|image_delete_guide_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_find_next_guide_proc
specifier|static
name|ProcRecord
name|image_find_next_guide_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_get_guide_orientation_proc
specifier|static
name|ProcRecord
name|image_get_guide_orientation_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_get_guide_position_proc
specifier|static
name|ProcRecord
name|image_get_guide_position_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_guides_procs (Gimp * gimp)
name|register_guides_procs
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
name|image_add_hguide_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_add_vguide_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_delete_guide_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_find_next_guide_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_get_guide_orientation_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_get_guide_position_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_add_hguide_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|image_add_hguide_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
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
name|gimage
decl_stmt|;
name|gint32
name|offset
decl_stmt|;
name|gint32
name|guide_ID
init|=
literal|0
decl_stmt|;
name|GimpGuide
modifier|*
name|guide
decl_stmt|;
name|gimage
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
name|gimage
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|offset
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
name|offset
operator|<
literal|0
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
name|offset
operator|<=
name|gimage
operator|->
name|height
condition|)
block|{
name|guide
operator|=
name|gimp_image_add_hguide
argument_list|(
name|gimage
argument_list|,
name|offset
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|guide_ID
operator|=
name|guide
operator|->
name|guide_ID
expr_stmt|;
block|}
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
name|image_add_hguide_proc
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
name|guide_ID
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_add_hguide_inargs
specifier|static
name|ProcArg
name|image_add_hguide_inargs
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
literal|"yposition"
block|,
literal|"The guide's y-offset from top of image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_add_hguide_outargs
specifier|static
name|ProcArg
name|image_add_hguide_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"guide"
block|,
literal|"The new guide"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_add_hguide_proc
specifier|static
name|ProcRecord
name|image_add_hguide_proc
init|=
block|{
literal|"gimp_image_add_hguide"
block|,
literal|"Add a horizontal guide to an image."
block|,
literal|"This procedure adds a horizontal guide to an image. It takes the input image and the y-position of the new guide as parameters. It returns the guide ID of the new guide."
block|,
literal|"Adam D. Moss"
block|,
literal|"Adam D. Moss"
block|,
literal|"1998"
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|image_add_hguide_inargs
block|,
literal|1
block|,
name|image_add_hguide_outargs
block|,
block|{
block|{
name|image_add_hguide_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_add_vguide_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|image_add_vguide_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
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
name|gimage
decl_stmt|;
name|gint32
name|offset
decl_stmt|;
name|gint32
name|guide_ID
init|=
literal|0
decl_stmt|;
name|GimpGuide
modifier|*
name|guide
decl_stmt|;
name|gimage
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
name|gimage
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|offset
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
name|offset
operator|<
literal|0
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
name|offset
operator|<=
name|gimage
operator|->
name|width
condition|)
block|{
name|guide
operator|=
name|gimp_image_add_vguide
argument_list|(
name|gimage
argument_list|,
name|offset
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|guide_ID
operator|=
name|guide
operator|->
name|guide_ID
expr_stmt|;
block|}
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
name|image_add_vguide_proc
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
name|guide_ID
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_add_vguide_inargs
specifier|static
name|ProcArg
name|image_add_vguide_inargs
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
literal|"xposition"
block|,
literal|"The guide's x-offset from left of image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_add_vguide_outargs
specifier|static
name|ProcArg
name|image_add_vguide_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"guide"
block|,
literal|"The new guide"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_add_vguide_proc
specifier|static
name|ProcRecord
name|image_add_vguide_proc
init|=
block|{
literal|"gimp_image_add_vguide"
block|,
literal|"Add a vertical guide to an image."
block|,
literal|"This procedure adds a vertical guide to an image. It takes the input image and the x-position of the new guide as parameters. It returns the guide ID of the new guide."
block|,
literal|"Adam D. Moss"
block|,
literal|"Adam D. Moss"
block|,
literal|"1998"
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|image_add_vguide_inargs
block|,
literal|1
block|,
name|image_add_vguide_outargs
block|,
block|{
block|{
name|image_add_vguide_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_delete_guide_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|image_delete_guide_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
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
name|gimage
decl_stmt|;
name|gint32
name|guide
decl_stmt|;
name|GList
modifier|*
name|guides
decl_stmt|;
name|gimage
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
name|gimage
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|guide
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
name|success
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|guides
operator|=
name|gimage
operator|->
name|guides
init|;
name|guides
condition|;
name|guides
operator|=
name|g_list_next
argument_list|(
name|guides
argument_list|)
control|)
block|{
name|GimpGuide
modifier|*
name|g
init|=
operator|(
name|GimpGuide
operator|*
operator|)
name|guides
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|(
name|g
operator|->
name|guide_ID
operator|==
name|guide
operator|)
operator|&&
operator|(
name|g
operator|->
name|position
operator|>=
literal|0
operator|)
condition|)
block|{
name|gimp_image_remove_guide
argument_list|(
name|gimage
argument_list|,
name|g
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
break|break;
block|}
block|}
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|image_delete_guide_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_delete_guide_inargs
specifier|static
name|ProcArg
name|image_delete_guide_inargs
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
literal|"guide"
block|,
literal|"The ID of the guide to be removed"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_delete_guide_proc
specifier|static
name|ProcRecord
name|image_delete_guide_proc
init|=
block|{
literal|"gimp_image_delete_guide"
block|,
literal|"Deletes a guide from an image."
block|,
literal|"This procedure takes an image and a guide ID as input and removes the specified guide from the specified image."
block|,
literal|"Adam D. Moss"
block|,
literal|"Adam D. Moss"
block|,
literal|"1998"
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|image_delete_guide_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_delete_guide_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_find_next_guide_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|image_find_next_guide_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
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
name|gimage
decl_stmt|;
name|gint32
name|guide
decl_stmt|;
name|gint32
name|next_guide
init|=
literal|0
decl_stmt|;
name|GList
modifier|*
name|guides
decl_stmt|;
name|gboolean
name|guide_found
decl_stmt|;
name|gimage
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
name|gimage
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|guide
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
name|gimage
operator|->
name|guides
operator|!=
name|NULL
condition|)
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
name|guide_found
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|guides
operator|=
name|gimage
operator|->
name|guides
init|;
name|guides
condition|;
name|guides
operator|=
name|g_list_next
argument_list|(
name|guides
argument_list|)
control|)
block|{
name|GimpGuide
modifier|*
name|g
init|=
operator|(
name|GimpGuide
operator|*
operator|)
name|guides
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|g
operator|->
name|position
operator|<
literal|0
condition|)
continue|continue;
if|if
condition|(
name|guide
operator|==
literal|0
condition|)
comment|/* init - Return first guide ID in list */
block|{
name|next_guide
operator|=
name|g
operator|->
name|guide_ID
expr_stmt|;
name|guide_found
operator|=
name|TRUE
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|!
name|guide_found
condition|)
block|{
if|if
condition|(
name|g
operator|->
name|guide_ID
operator|==
name|guide
condition|)
name|guide_found
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|next_guide
operator|=
name|g
operator|->
name|guide_ID
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|guide_found
condition|)
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|image_find_next_guide_proc
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
name|next_guide
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_find_next_guide_inargs
specifier|static
name|ProcArg
name|image_find_next_guide_inargs
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
literal|"guide"
block|,
literal|"The ID of the current guide (0 if first invocation)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_find_next_guide_outargs
specifier|static
name|ProcArg
name|image_find_next_guide_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"next_guide"
block|,
literal|"The next guide's ID"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_find_next_guide_proc
specifier|static
name|ProcRecord
name|image_find_next_guide_proc
init|=
block|{
literal|"gimp_image_find_next_guide"
block|,
literal|"Find next guide on an image."
block|,
literal|"This procedure takes an image and a guide ID as input and finds the guide ID of the successor of the given guide ID in the image's guide list. If the supplied guide ID is 0, the procedure will return the first Guide. The procedure will return 0 if given the final guide ID as an argument or the image has no guides."
block|,
literal|"Adam D. Moss"
block|,
literal|"Adam D. Moss"
block|,
literal|"1998"
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|image_find_next_guide_inargs
block|,
literal|1
block|,
name|image_find_next_guide_outargs
block|,
block|{
block|{
name|image_find_next_guide_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_get_guide_orientation_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|image_get_guide_orientation_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
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
name|gimage
decl_stmt|;
name|gint32
name|guide
decl_stmt|;
name|gint32
name|orientation
init|=
literal|0
decl_stmt|;
name|GList
modifier|*
name|guides
decl_stmt|;
name|gimage
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
name|gimage
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|guide
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
name|success
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|guides
operator|=
name|gimage
operator|->
name|guides
init|;
name|guides
condition|;
name|guides
operator|=
name|g_list_next
argument_list|(
name|guides
argument_list|)
control|)
block|{
name|GimpGuide
modifier|*
name|g
init|=
operator|(
name|GimpGuide
operator|*
operator|)
name|guides
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|(
name|g
operator|->
name|guide_ID
operator|==
name|guide
operator|)
operator|&&
operator|(
name|g
operator|->
name|position
operator|>=
literal|0
operator|)
condition|)
block|{
name|orientation
operator|=
name|g
operator|->
name|orientation
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
break|break;
block|}
block|}
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|image_get_guide_orientation_proc
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
name|orientation
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_get_guide_orientation_inargs
specifier|static
name|ProcArg
name|image_get_guide_orientation_inargs
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
literal|"guide"
block|,
literal|"The guide"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_get_guide_orientation_outargs
specifier|static
name|ProcArg
name|image_get_guide_orientation_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"orientation"
block|,
literal|"The guide's orientation: { GIMP_ORIENTATION_HORIZONTAL (0), GIMP_ORIENTATION_VERTICAL (1) }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_get_guide_orientation_proc
specifier|static
name|ProcRecord
name|image_get_guide_orientation_proc
init|=
block|{
literal|"gimp_image_get_guide_orientation"
block|,
literal|"Get orientation of a guide on an image."
block|,
literal|"This procedure takes an image and a guide ID as input and returns the orientations of the guide."
block|,
literal|"Adam D. Moss"
block|,
literal|"Adam D. Moss"
block|,
literal|"1998"
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|image_get_guide_orientation_inargs
block|,
literal|1
block|,
name|image_get_guide_orientation_outargs
block|,
block|{
block|{
name|image_get_guide_orientation_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_get_guide_position_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|image_get_guide_position_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
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
name|gimage
decl_stmt|;
name|gint32
name|guide
decl_stmt|;
name|gint32
name|position
init|=
literal|0
decl_stmt|;
name|GList
modifier|*
name|guides
decl_stmt|;
name|gimage
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
name|gimage
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|guide
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
name|success
operator|=
name|FALSE
expr_stmt|;
for|for
control|(
name|guides
operator|=
name|gimage
operator|->
name|guides
init|;
name|guides
condition|;
name|guides
operator|=
name|g_list_next
argument_list|(
name|guides
argument_list|)
control|)
block|{
name|GimpGuide
modifier|*
name|g
init|=
operator|(
name|GimpGuide
operator|*
operator|)
name|guides
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|(
name|g
operator|->
name|guide_ID
operator|==
name|guide
operator|)
operator|&&
operator|(
name|g
operator|->
name|position
operator|>=
literal|0
operator|)
condition|)
block|{
name|position
operator|=
name|g
operator|->
name|position
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
break|break;
block|}
block|}
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|image_get_guide_position_proc
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
name|position
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_get_guide_position_inargs
specifier|static
name|ProcArg
name|image_get_guide_position_inargs
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
literal|"guide"
block|,
literal|"The guide"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_get_guide_position_outargs
specifier|static
name|ProcArg
name|image_get_guide_position_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"position"
block|,
literal|"The guide's position relative to top or left of image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_get_guide_position_proc
specifier|static
name|ProcRecord
name|image_get_guide_position_proc
init|=
block|{
literal|"gimp_image_get_guide_position"
block|,
literal|"Get position of a guide on an image."
block|,
literal|"This procedure takes an image and a guide ID as input and returns the position of the guide relative to the top or left of the image."
block|,
literal|"Adam D. Moss"
block|,
literal|"Adam D. Moss"
block|,
literal|"1998"
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|image_get_guide_position_inargs
block|,
literal|1
block|,
name|image_get_guide_position_outargs
block|,
block|{
block|{
name|image_get_guide_position_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

