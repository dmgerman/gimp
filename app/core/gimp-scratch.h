begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-scratch.h  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SCRATCH_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SCRATCH_H__
define|#
directive|define
name|__GIMP_SCRATCH_H__
end_define

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_define
DECL|macro|GIMP_SCRATCH_ALIGNMENT
define|#
directive|define
name|GIMP_SCRATCH_ALIGNMENT
value|16
end_define

begin_define
DECL|macro|GIMP_SCRATCH_MAX_BLOCK_SIZE
define|#
directive|define
name|GIMP_SCRATCH_MAX_BLOCK_SIZE
value|(1<< 20)
end_define

begin_comment
comment|/*  private types  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29c9512b0108
block|{
DECL|member|size
name|gsize
name|size
decl_stmt|;
DECL|member|offset
name|guint8
name|offset
decl_stmt|;
DECL|member|padding
name|guint8
name|padding
index|[
name|GIMP_SCRATCH_ALIGNMENT
operator|-
operator|(
sizeof|sizeof
argument_list|(
name|gsize
argument_list|)
operator|+
literal|1
operator|)
index|]
decl_stmt|;
DECL|member|data
name|guint8
name|data
index|[]
decl_stmt|;
DECL|typedef|GimpScratchBlock
block|}
name|GimpScratchBlock
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29c9512b0208
block|{
DECL|member|blocks
name|GimpScratchBlock
modifier|*
modifier|*
name|blocks
decl_stmt|;
DECL|member|n_blocks
name|gint
name|n_blocks
decl_stmt|;
DECL|member|n_available_blocks
name|gint
name|n_available_blocks
decl_stmt|;
DECL|typedef|GimpScratchContext
block|}
name|GimpScratchContext
typedef|;
end_typedef

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
specifier|extern
name|GPrivate
name|gimp_scratch_context
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  private functions  */
end_comment

begin_function_decl
name|GimpScratchBlock
modifier|*
name|gimp_scratch_block_new
parameter_list|(
name|gsize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scratch_block_free
parameter_list|(
name|GimpScratchBlock
modifier|*
name|block
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpScratchContext
modifier|*
name|gimp_scratch_context_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scratch_context_free
parameter_list|(
name|GimpScratchContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
specifier|inline
name|gpointer
DECL|function|gimp_scratch_alloc (gsize size)
name|gimp_scratch_alloc
parameter_list|(
name|gsize
name|size
parameter_list|)
block|{
name|GimpScratchContext
modifier|*
name|context
decl_stmt|;
name|GimpScratchBlock
modifier|*
name|block
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|size
argument_list|)
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
name|size
operator|>
name|GIMP_SCRATCH_MAX_BLOCK_SIZE
argument_list|)
condition|)
block|{
name|block
operator|=
name|gimp_scratch_block_new
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|block
operator|->
name|size
operator|=
literal|0
expr_stmt|;
return|return
name|block
operator|->
name|data
return|;
block|}
name|context
operator|=
name|g_private_get
argument_list|(
operator|&
name|gimp_scratch_context
argument_list|)
expr_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|context
argument_list|)
condition|)
block|{
name|context
operator|=
name|gimp_scratch_context_new
argument_list|()
expr_stmt|;
name|g_private_set
argument_list|(
operator|&
name|gimp_scratch_context
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|G_LIKELY
argument_list|(
name|context
operator|->
name|n_available_blocks
argument_list|)
condition|)
block|{
name|block
operator|=
name|context
operator|->
name|blocks
index|[
operator|--
name|context
operator|->
name|n_available_blocks
index|]
expr_stmt|;
if|if
condition|(
name|G_LIKELY
argument_list|(
name|size
operator|<=
name|block
operator|->
name|size
argument_list|)
condition|)
return|return
name|block
operator|->
name|data
return|;
name|gimp_scratch_block_free
argument_list|(
name|block
argument_list|)
expr_stmt|;
block|}
name|block
operator|=
name|gimp_scratch_block_new
argument_list|(
name|size
argument_list|)
expr_stmt|;
return|return
name|block
operator|->
name|data
return|;
block|}
end_function

begin_function
specifier|inline
name|gpointer
DECL|function|gimp_scratch_alloc0 (gsize size)
name|gimp_scratch_alloc0
parameter_list|(
name|gsize
name|size
parameter_list|)
block|{
name|gpointer
name|ptr
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|size
argument_list|)
condition|)
return|return
name|NULL
return|;
name|ptr
operator|=
name|gimp_scratch_alloc
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|ptr
argument_list|,
literal|0
argument_list|,
name|size
argument_list|)
expr_stmt|;
return|return
name|ptr
return|;
block|}
end_function

begin_function
specifier|inline
name|void
DECL|function|gimp_scratch_free (gpointer ptr)
name|gimp_scratch_free
parameter_list|(
name|gpointer
name|ptr
parameter_list|)
block|{
name|GimpScratchContext
modifier|*
name|context
decl_stmt|;
name|GimpScratchBlock
modifier|*
name|block
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|ptr
argument_list|)
condition|)
return|return;
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
name|ptr
operator|-
name|GIMP_SCRATCH_ALIGNMENT
operator|)
expr_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|block
operator|->
name|size
argument_list|)
condition|)
block|{
name|gimp_scratch_block_free
argument_list|(
name|block
argument_list|)
expr_stmt|;
return|return;
block|}
name|context
operator|=
name|g_private_get
argument_list|(
operator|&
name|gimp_scratch_context
argument_list|)
expr_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
name|context
operator|->
name|n_available_blocks
operator|==
name|context
operator|->
name|n_blocks
argument_list|)
condition|)
block|{
name|context
operator|->
name|n_blocks
operator|=
name|MAX
argument_list|(
literal|2
operator|*
name|context
operator|->
name|n_blocks
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|context
operator|->
name|blocks
operator|=
name|g_renew
argument_list|(
name|GimpScratchBlock
operator|*
argument_list|,
name|context
operator|->
name|blocks
argument_list|,
name|context
operator|->
name|n_blocks
argument_list|)
expr_stmt|;
block|}
name|context
operator|->
name|blocks
index|[
name|context
operator|->
name|n_available_blocks
operator|++
index|]
operator|=
name|block
expr_stmt|;
block|}
end_function

begin_define
DECL|macro|gimp_scratch_new (type,n)
define|#
directive|define
name|gimp_scratch_new
parameter_list|(
name|type
parameter_list|,
name|n
parameter_list|)
define|\
value|((type *) (gimp_scratch_alloc (sizeof (type) * (n))))
end_define

begin_define
DECL|macro|gimp_scratch_new0 (type,n)
define|#
directive|define
name|gimp_scratch_new0
parameter_list|(
name|type
parameter_list|,
name|n
parameter_list|)
define|\
value|((type *) (gimp_scratch_alloc0 (sizeof (type) * (n))))
end_define

begin_comment
comment|/*  stats  */
end_comment

begin_function_decl
name|guint64
name|gimp_scratch_get_total
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SCRATCH_H__ */
end_comment

end_unit
