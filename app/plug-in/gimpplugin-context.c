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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"plug-in.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-context.h"
end_include

begin_function
name|gboolean
DECL|function|plug_in_context_push (PlugIn * plug_in)
name|plug_in_context_push
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|PlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|plug_in
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc_frame
operator|=
name|plug_in_get_proc_frame
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|plug_in_context_pop (PlugIn * plug_in)
name|plug_in_context_pop
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|PlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|plug_in
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc_frame
operator|=
name|plug_in_get_proc_frame
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

