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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_warning
warning|#
directive|warning
warning|FIXME #include "display/display-types.h"
end_warning

begin_include
include|#
directive|include
file|"display/display-types.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"plug-in.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-progress.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|plug_in_progress_cancel
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|plug_in_progress_init (PlugIn * plug_in,gchar * message,gint gdisp_ID)
name|plug_in_progress_init
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
name|gchar
modifier|*
name|message
parameter_list|,
name|gint
name|gdisp_ID
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|message
condition|)
name|message
operator|=
name|plug_in
operator|->
name|args
index|[
literal|0
index|]
expr_stmt|;
if|if
condition|(
name|gdisp_ID
operator|>
literal|0
condition|)
name|gdisp
operator|=
name|gimp_display_get_by_ID
argument_list|(
name|plug_in
operator|->
name|gimp
argument_list|,
name|gdisp_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in
operator|->
name|progress
condition|)
name|plug_in
operator|->
name|progress
operator|=
name|gimp_progress_restart
argument_list|(
name|plug_in
operator|->
name|progress
argument_list|,
name|message
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_progress_cancel
argument_list|)
argument_list|,
name|plug_in
argument_list|)
expr_stmt|;
else|else
name|plug_in
operator|->
name|progress
operator|=
name|gimp_progress_start
argument_list|(
name|gdisp
argument_list|,
name|message
argument_list|,
name|TRUE
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_progress_cancel
argument_list|)
argument_list|,
name|plug_in
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|plug_in_progress_update (PlugIn * plug_in,gdouble percentage)
name|plug_in_progress_update
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
if|if
condition|(
operator|!
name|plug_in
operator|->
name|progress
condition|)
name|plug_in_progress_init
argument_list|(
name|plug_in
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
name|plug_in
operator|->
name|progress
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|plug_in_progress_end (PlugIn * plug_in)
name|plug_in_progress_end
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
if|if
condition|(
name|plug_in
operator|->
name|progress
condition|)
block|{
name|gimp_progress_end
argument_list|(
name|plug_in
operator|->
name|progress
argument_list|)
expr_stmt|;
name|plug_in
operator|->
name|progress
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|plug_in_progress_cancel (GtkWidget * widget,PlugIn * plug_in)
name|plug_in_progress_cancel
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|plug_in_destroy
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

