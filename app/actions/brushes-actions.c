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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdata.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"brushes-actions.h"
end_include

begin_include
include|#
directive|include
file|"data-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|brushes_actions
specifier|static
name|GimpActionEntry
name|brushes_actions
index|[]
init|=
block|{
block|{
literal|"brushes-popup"
block|,
name|GIMP_STOCK_BRUSH
block|,
name|N_
argument_list|(
literal|"Brushes Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_BRUSH_DIALOG
block|}
block|,
block|{
literal|"brushes-edit"
block|,
name|GIMP_STOCK_EDIT
block|,
name|N_
argument_list|(
literal|"_Edit Brush..."
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Edit brush"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_edit_data_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BRUSH_EDIT
block|}
block|,
block|{
literal|"brushes-new"
block|,
name|GTK_STOCK_NEW
block|,
name|N_
argument_list|(
literal|"New Brush"
argument_list|)
block|,
literal|""
block|,
name|N_
argument_list|(
literal|"New brush"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_new_data_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BRUSH_NEW
block|}
block|,
block|{
literal|"brushes-duplicate"
block|,
name|GIMP_STOCK_DUPLICATE
block|,
name|N_
argument_list|(
literal|"D_uplicate Brush"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Duplicate brush"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_duplicate_data_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BRUSH_DUPLICATE
block|}
block|,
block|{
literal|"brushes-delete"
block|,
name|GTK_STOCK_DELETE
block|,
name|N_
argument_list|(
literal|"_Delete Brush"
argument_list|)
block|,
literal|""
block|,
name|N_
argument_list|(
literal|"Delete brush"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_delete_data_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BRUSH_DELETE
block|}
block|,
block|{
literal|"brushes-refresh"
block|,
name|GTK_STOCK_REFRESH
block|,
name|N_
argument_list|(
literal|"_Refresh Brushes"
argument_list|)
block|,
literal|""
block|,
name|N_
argument_list|(
literal|"Refresh brushes"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_refresh_data_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BRUSH_REFRESH
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|brushes_actions_setup (GimpActionGroup * group)
name|brushes_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|brushes_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|brushes_actions
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|brushes_actions_update (GimpActionGroup * group,gpointer user_data)
name|brushes_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpBrush
modifier|*
name|brush
init|=
name|NULL
decl_stmt|;
name|GimpData
modifier|*
name|data
init|=
name|NULL
decl_stmt|;
name|context
operator|=
name|action_data_get_context
argument_list|(
name|user_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|context
condition|)
block|{
name|brush
operator|=
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
condition|)
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
expr_stmt|;
block|}
DECL|macro|SET_SENSITIVE (action,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_sensitive (group, action, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"brushes-edit"
argument_list|,
name|brush
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"brushes-duplicate"
argument_list|,
name|brush
operator|&&
name|GIMP_DATA_GET_CLASS
argument_list|(
name|data
argument_list|)
operator|->
name|duplicate
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"brushes-delete"
argument_list|,
name|brush
operator|&&
name|data
operator|->
name|deletable
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

