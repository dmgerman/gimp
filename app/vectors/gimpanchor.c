begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpanchor.c  * Copyright (C) 2002 Simon Budig<simon@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"glib-object.h"
end_include

begin_include
include|#
directive|include
file|"vectors-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpanchor.h"
end_include

begin_function
name|GType
DECL|function|gimp_anchor_get_type (void)
name|gimp_anchor_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|anchor_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|anchor_type
condition|)
name|anchor_type
operator|=
name|g_boxed_type_register_static
argument_list|(
literal|"GimpAnchor"
argument_list|,
operator|(
name|GBoxedCopyFunc
operator|)
name|gimp_anchor_copy
argument_list|,
operator|(
name|GBoxedFreeFunc
operator|)
name|gimp_anchor_free
argument_list|)
expr_stmt|;
return|return
name|anchor_type
return|;
block|}
end_function

begin_function
name|GimpAnchor
modifier|*
DECL|function|gimp_anchor_new (GimpAnchorType type,const GimpCoords * position)
name|gimp_anchor_new
parameter_list|(
name|GimpAnchorType
name|type
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|position
parameter_list|)
block|{
name|GimpAnchor
modifier|*
name|anchor
init|=
name|g_slice_new0
argument_list|(
name|GimpAnchor
argument_list|)
decl_stmt|;
name|anchor
operator|->
name|type
operator|=
name|type
expr_stmt|;
if|if
condition|(
name|position
condition|)
name|anchor
operator|->
name|position
operator|=
operator|*
name|position
expr_stmt|;
return|return
name|anchor
return|;
block|}
end_function

begin_function
name|GimpAnchor
modifier|*
DECL|function|gimp_anchor_copy (const GimpAnchor * anchor)
name|gimp_anchor_copy
parameter_list|(
specifier|const
name|GimpAnchor
modifier|*
name|anchor
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|anchor
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_slice_dup
argument_list|(
name|GimpAnchor
argument_list|,
name|anchor
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_anchor_free (GimpAnchor * anchor)
name|gimp_anchor_free
parameter_list|(
name|GimpAnchor
modifier|*
name|anchor
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|anchor
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpAnchor
argument_list|,
name|anchor
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

