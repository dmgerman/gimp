begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2008 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*  This code is written so that it can also be compiled standalone.  *  It shouldn't depend on libgimp.  */
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
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|"gimphelptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimphelpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimphelpprogress-private.h"
end_include

begin_struct
DECL|struct|_GimpHelpProgress
struct|struct
name|_GimpHelpProgress
block|{
DECL|member|vtable
name|GimpHelpProgressVTable
name|vtable
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|member|cancellable
name|GCancellable
modifier|*
name|cancellable
decl_stmt|;
block|}
struct|;
end_struct

begin_function
name|GimpHelpProgress
modifier|*
DECL|function|gimp_help_progress_new (const GimpHelpProgressVTable * vtable,gpointer user_data)
name|gimp_help_progress_new
parameter_list|(
specifier|const
name|GimpHelpProgressVTable
modifier|*
name|vtable
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpHelpProgress
modifier|*
name|progress
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|vtable
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|progress
operator|=
name|g_slice_new0
argument_list|(
name|GimpHelpProgress
argument_list|)
expr_stmt|;
name|progress
operator|->
name|vtable
operator|.
name|start
operator|=
name|vtable
operator|->
name|start
expr_stmt|;
name|progress
operator|->
name|vtable
operator|.
name|end
operator|=
name|vtable
operator|->
name|end
expr_stmt|;
name|progress
operator|->
name|vtable
operator|.
name|set_value
operator|=
name|vtable
operator|->
name|set_value
expr_stmt|;
name|progress
operator|->
name|user_data
operator|=
name|user_data
expr_stmt|;
return|return
name|progress
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_help_progress_free (GimpHelpProgress * progress)
name|gimp_help_progress_free
parameter_list|(
name|GimpHelpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|progress
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
operator|->
name|cancellable
condition|)
block|{
name|g_object_unref
argument_list|(
name|progress
operator|->
name|cancellable
argument_list|)
expr_stmt|;
name|progress
operator|->
name|cancellable
operator|=
name|NULL
expr_stmt|;
block|}
name|g_slice_free
argument_list|(
name|GimpHelpProgress
argument_list|,
name|progress
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_help_progress_cancel (GimpHelpProgress * progress)
name|gimp_help_progress_cancel
parameter_list|(
name|GimpHelpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|progress
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
operator|->
name|cancellable
condition|)
name|g_cancellable_cancel
argument_list|(
name|progress
operator|->
name|cancellable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_help_progress_start (GimpHelpProgress * progress,GCancellable * cancellable,const gchar * format,...)
name|_gimp_help_progress_start
parameter_list|(
name|GimpHelpProgress
modifier|*
name|progress
parameter_list|,
name|GCancellable
modifier|*
name|cancellable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|gchar
modifier|*
name|message
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|progress
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|cancellable
condition|)
name|g_object_ref
argument_list|(
name|cancellable
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
operator|->
name|cancellable
condition|)
name|g_object_unref
argument_list|(
name|progress
operator|->
name|cancellable
argument_list|)
expr_stmt|;
name|progress
operator|->
name|cancellable
operator|=
name|cancellable
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|message
operator|=
name|g_strdup_vprintf
argument_list|(
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
operator|->
name|vtable
operator|.
name|start
condition|)
name|progress
operator|->
name|vtable
operator|.
name|start
argument_list|(
name|message
argument_list|,
name|cancellable
operator|!=
name|NULL
argument_list|,
name|progress
operator|->
name|user_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|message
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_help_progress_update (GimpHelpProgress * progress,gdouble percentage)
name|_gimp_help_progress_update
parameter_list|(
name|GimpHelpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|progress
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
operator|->
name|vtable
operator|.
name|set_value
condition|)
name|progress
operator|->
name|vtable
operator|.
name|set_value
argument_list|(
name|percentage
argument_list|,
name|progress
operator|->
name|user_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_help_progress_pulse (GimpHelpProgress * progress)
name|_gimp_help_progress_pulse
parameter_list|(
name|GimpHelpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|progress
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|_gimp_help_progress_update
argument_list|(
name|progress
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_help_progress_finish (GimpHelpProgress * progress)
name|_gimp_help_progress_finish
parameter_list|(
name|GimpHelpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|progress
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
operator|->
name|vtable
operator|.
name|end
condition|)
name|progress
operator|->
name|vtable
operator|.
name|end
argument_list|(
name|progress
operator|->
name|user_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
operator|->
name|cancellable
condition|)
block|{
name|g_object_unref
argument_list|(
name|progress
operator|->
name|cancellable
argument_list|)
expr_stmt|;
name|progress
operator|->
name|cancellable
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

end_unit

