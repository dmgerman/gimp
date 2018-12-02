begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-scratch.c  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-scratch.h"
end_include

begin_comment
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|gimp_scratch_context
name|GPrivate
name|gimp_scratch_context
init|=
name|G_PRIVATE_INIT
argument_list|(
operator|(
name|GDestroyNotify
operator|)
name|gimp_scratch_context_free
argument_list|)
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_scratch_total
specifier|static
specifier|volatile
name|guintptr
name|gimp_scratch_total
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  private functions  */
end_comment

begin_function
name|GimpScratchBlock
modifier|*
DECL|function|gimp_scratch_block_new (gsize size)
name|gimp_scratch_block_new
parameter_list|(
name|gsize
name|size
parameter_list|)
block|{
name|GimpScratchBlock
modifier|*
name|block
decl_stmt|;
name|gint
name|offset
decl_stmt|;
name|g_atomic_pointer_add
argument_list|(
operator|&
name|gimp_scratch_total
argument_list|,
operator|+
name|size
argument_list|)
expr_stmt|;
name|block
operator|=
name|g_malloc
argument_list|(
operator|(
name|GIMP_SCRATCH_ALIGNMENT
operator|-
literal|1
operator|)
operator|+
sizeof|sizeof
argument_list|(
name|GimpScratchBlock
argument_list|)
operator|+
name|size
argument_list|)
expr_stmt|;
name|offset
operator|=
name|GIMP_SCRATCH_ALIGNMENT
operator|-
operator|(
operator|(
name|guintptr
operator|)
name|block
operator|)
operator|%
name|GIMP_SCRATCH_ALIGNMENT
expr_stmt|;
name|offset
operator|%=
name|GIMP_SCRATCH_ALIGNMENT
expr_stmt|;
name|block
operator|=
operator|(
name|GimpScratchBlock
operator|*
operator|)
operator|(
operator|(
name|guint8
operator|*
operator|)
name|block
operator|+
name|offset
operator|)
expr_stmt|;
name|block
operator|->
name|size
operator|=
name|size
expr_stmt|;
name|block
operator|->
name|offset
operator|=
name|offset
expr_stmt|;
return|return
name|block
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_scratch_block_free (GimpScratchBlock * block)
name|gimp_scratch_block_free
parameter_list|(
name|GimpScratchBlock
modifier|*
name|block
parameter_list|)
block|{
name|g_atomic_pointer_add
argument_list|(
operator|&
name|gimp_scratch_total
argument_list|,
operator|-
name|block
operator|->
name|size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
operator|(
name|guint8
operator|*
operator|)
name|block
operator|-
name|block
operator|->
name|offset
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpScratchContext
modifier|*
DECL|function|gimp_scratch_context_new (void)
name|gimp_scratch_context_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_slice_new0
argument_list|(
name|GimpScratchContext
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_scratch_context_free (GimpScratchContext * context)
name|gimp_scratch_context_free
parameter_list|(
name|GimpScratchContext
modifier|*
name|context
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|context
operator|->
name|n_available_blocks
condition|;
name|i
operator|++
control|)
name|gimp_scratch_block_free
argument_list|(
name|context
operator|->
name|blocks
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|context
operator|->
name|blocks
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpScratchContext
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*   public functions (stats)  */
end_comment

begin_function
name|guint64
DECL|function|gimp_scratch_get_total (void)
name|gimp_scratch_get_total
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|gimp_scratch_total
return|;
block|}
end_function

end_unit
