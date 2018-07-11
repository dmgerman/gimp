begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
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

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|gboolean
DECL|function|xcf_seek_pos (XcfInfo * info,goffset pos,GError ** error)
name|xcf_seek_pos
parameter_list|(
name|XcfInfo
modifier|*
name|info
parameter_list|,
name|goffset
name|pos
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|GError
modifier|*
name|my_error
init|=
name|NULL
decl_stmt|;
name|info
operator|->
name|cp
operator|=
name|pos
expr_stmt|;
if|if
condition|(
operator|!
name|g_seekable_seek
argument_list|(
name|info
operator|->
name|seekable
argument_list|,
name|info
operator|->
name|cp
argument_list|,
name|G_SEEK_SET
argument_list|,
name|NULL
argument_list|,
operator|&
name|my_error
argument_list|)
condition|)
block|{
name|g_propagate_prefixed_error
argument_list|(
name|error
argument_list|,
name|my_error
argument_list|,
name|_
argument_list|(
literal|"Could not seek in XCF file: "
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_assert
argument_list|(
name|info
operator|->
name|cp
operator|==
name|g_seekable_tell
argument_list|(
name|info
operator|->
name|seekable
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

