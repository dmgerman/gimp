begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"xcf-private.h"
end_include

begin_include
include|#
directive|include
file|"xcf-seek.h"
end_include

begin_function
name|void
DECL|function|xcf_seek_pos (XcfInfo * info,guint pos)
name|xcf_seek_pos
parameter_list|(
name|XcfInfo
modifier|*
name|info
parameter_list|,
name|guint
name|pos
parameter_list|)
block|{
if|if
condition|(
name|info
operator|->
name|cp
operator|!=
name|pos
condition|)
block|{
name|info
operator|->
name|cp
operator|=
name|pos
expr_stmt|;
name|fseek
argument_list|(
name|info
operator|->
name|fp
argument_list|,
name|info
operator|->
name|cp
argument_list|,
name|SEEK_SET
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|xcf_seek_end (XcfInfo * info)
name|xcf_seek_end
parameter_list|(
name|XcfInfo
modifier|*
name|info
parameter_list|)
block|{
name|fseek
argument_list|(
name|info
operator|->
name|fp
argument_list|,
literal|0
argument_list|,
name|SEEK_END
argument_list|)
expr_stmt|;
name|info
operator|->
name|cp
operator|=
name|ftell
argument_list|(
name|info
operator|->
name|fp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

