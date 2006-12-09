begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets/gimpdataeditor.h"
end_include

begin_include
include|#
directive|include
file|"data-editor-commands.h"
end_include

begin_comment
comment|/*  public functionss */
end_comment

begin_function
name|void
DECL|function|data_editor_edit_active_cmd_callback (GtkAction * action,gpointer data)
name|data_editor_edit_active_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gboolean
name|edit_active
decl_stmt|;
name|edit_active
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_data_editor_set_edit_active
argument_list|(
name|editor
argument_list|,
name|edit_active
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

