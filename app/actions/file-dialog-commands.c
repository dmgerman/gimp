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
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpfiledialog.h"
end_include

begin_include
include|#
directive|include
file|"file-dialog-commands.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|file_dialog_type_cmd_callback (GtkAction * action,PlugInProcDef * proc_def,gpointer data)
name|file_dialog_type_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_file_dialog_set_file_proc
argument_list|(
name|GIMP_FILE_DIALOG
argument_list|(
name|data
argument_list|)
argument_list|,
name|proc_def
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

