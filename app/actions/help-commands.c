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
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gui/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"help-commands.h"
end_include

begin_function
name|void
DECL|function|help_help_cmd_callback (GtkAction * action,gpointer data)
name|help_help_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_standard_help_func
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|help_context_help_cmd_callback (GtkAction * action,gpointer data)
name|help_context_help_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|GIMP_IS_GIMP
argument_list|(
name|data
argument_list|)
condition|)
name|widget
operator|=
name|dialogs_get_toolbox
argument_list|()
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_DISPLAY
argument_list|(
name|data
argument_list|)
condition|)
name|widget
operator|=
name|GIMP_DISPLAY
argument_list|(
name|data
argument_list|)
operator|->
name|shell
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_DOCK
argument_list|(
name|data
argument_list|)
condition|)
name|widget
operator|=
name|data
expr_stmt|;
if|if
condition|(
name|widget
condition|)
name|gimp_context_help
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

