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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in.h"
end_include

begin_include
include|#
directive|include
file|"commands.h"
end_include

begin_comment
comment|/*****  Help  *****/
end_comment

begin_function
name|void
DECL|function|help_help_cmd_callback (GtkWidget * widget,gpointer data)
name|help_help_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_standard_help_func
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|help_context_help_cmd_callback (GtkWidget * widget,gpointer data)
name|help_context_help_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_context_help
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/*****  Debug  *****/
end_comment

begin_function
name|void
DECL|function|debug_mem_profile_cmd_callback (GtkWidget * widget,gpointer data)
name|debug_mem_profile_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
specifier|extern
name|gboolean
name|gimp_debug_memsize
decl_stmt|;
name|gimp_debug_memsize
operator|=
name|TRUE
expr_stmt|;
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_debug_memsize
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

