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
file|"widgets/gimpcontainereditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
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
file|"gui/data-commands.h"
end_include

begin_include
include|#
directive|include
file|"patterns-actions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|patterns_actions
specifier|static
name|GimpActionEntry
name|patterns_actions
index|[]
init|=
block|{
block|{
literal|"patterns-edit"
block|,
name|GIMP_STOCK_EDIT
block|,
name|N_
argument_list|(
literal|"_Edit Pattern..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|data_edit_data_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATTERN_EDIT
block|}
block|,
block|{
literal|"patterns-new"
block|,
name|GTK_STOCK_NEW
block|,
name|N_
argument_list|(
literal|"_New Pattern"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|data_new_data_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATTERN_NEW
block|}
block|,
block|{
literal|"patterns-duplicate"
block|,
name|GIMP_STOCK_DUPLICATE
block|,
name|N_
argument_list|(
literal|"D_uplicate Pattern"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|data_duplicate_data_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATTERN_DUPLICATE
block|}
block|,
block|{
literal|"patterns-delete"
block|,
name|GTK_STOCK_DELETE
block|,
name|N_
argument_list|(
literal|"_Delete Pattern..."
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|data_delete_data_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATTERN_DELETE
block|}
block|,
block|{
literal|"patterns-refresh"
block|,
name|GTK_STOCK_REFRESH
block|,
name|N_
argument_list|(
literal|"_Refresh Patterns"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|data_refresh_data_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATTERN_REFRESH
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|patterns_actions_setup (GimpActionGroup * group,gpointer data)
name|patterns_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|patterns_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|patterns_actions
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|patterns_actions_update (GimpActionGroup * group,gpointer user_data)
name|patterns_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
name|GimpData
modifier|*
name|data
init|=
name|NULL
decl_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|user_data
argument_list|)
expr_stmt|;
name|pattern
operator|=
name|gimp_context_get_pattern
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|pattern
condition|)
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
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
literal|"patterns-edit"
argument_list|,
name|pattern
operator|&&
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|editor
argument_list|)
operator|->
name|data_edit_func
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"patterns-duplicate"
argument_list|,
name|pattern
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
literal|"patterns-delete"
argument_list|,
name|pattern
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

