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
file|"menus-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"file-menu.h"
end_include

begin_function
name|void
DECL|function|file_menu_setup (GimpUIManager * manager,const gchar * ui_path)
name|file_menu_setup
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|)
block|{
name|GtkUIManager
modifier|*
name|ui_manager
decl_stmt|;
name|gint
name|n_entries
decl_stmt|;
name|guint
name|merge_id
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|ui_path
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|ui_manager
operator|=
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
expr_stmt|;
name|n_entries
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|manager
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|last_opened_size
expr_stmt|;
name|merge_id
operator|=
name|gtk_ui_manager_new_merge_id
argument_list|(
name|ui_manager
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_entries
condition|;
name|i
operator|++
control|)
block|{
name|gchar
modifier|*
name|action_name
decl_stmt|;
name|gchar
modifier|*
name|action_path
decl_stmt|;
name|action_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"file-open-recent-%02d"
argument_list|,
name|i
operator|+
literal|1
argument_list|)
expr_stmt|;
name|action_path
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s/File/Open Recent/Files"
argument_list|,
name|ui_path
argument_list|)
expr_stmt|;
name|gtk_ui_manager_add_ui
argument_list|(
name|ui_manager
argument_list|,
name|merge_id
argument_list|,
name|action_path
argument_list|,
name|action_name
argument_list|,
name|action_name
argument_list|,
name|GTK_UI_MANAGER_MENUITEM
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|action_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|action_path
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

