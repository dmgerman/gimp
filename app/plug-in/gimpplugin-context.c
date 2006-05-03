begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpplugin-context.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin-context.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_plug_in_context_push (GimpPlugIn * plug_in)
name|gimp_plug_in_context_push
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|GimpContext
modifier|*
name|parent
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc_frame
operator|=
name|gimp_plug_in_get_proc_frame
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_frame
operator|->
name|context_stack
condition|)
name|parent
operator|=
name|proc_frame
operator|->
name|context_stack
operator|->
name|data
expr_stmt|;
else|else
name|parent
operator|=
name|proc_frame
operator|->
name|main_context
expr_stmt|;
name|context
operator|=
name|gimp_context_new
argument_list|(
name|plug_in
operator|->
name|manager
operator|->
name|gimp
argument_list|,
literal|"plug-in context"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_context_copy_properties
argument_list|(
name|parent
argument_list|,
name|context
argument_list|,
name|GIMP_CONTEXT_ALL_PROPS_MASK
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|context_stack
operator|=
name|g_list_prepend
argument_list|(
name|proc_frame
operator|->
name|context_stack
argument_list|,
name|context
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_context_pop (GimpPlugIn * plug_in)
name|gimp_plug_in_context_pop
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc_frame
operator|=
name|gimp_plug_in_get_proc_frame
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_frame
operator|->
name|context_stack
condition|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|proc_frame
operator|->
name|context_stack
operator|->
name|data
decl_stmt|;
name|proc_frame
operator|->
name|context_stack
operator|=
name|g_list_remove
argument_list|(
name|proc_frame
operator|->
name|context_stack
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|context
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

