begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppatheditor.c  * Copyright (C) 1999 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpuitypes.h"
end_include

begin_include
include|#
directive|include
file|"gimppatheditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpfileselection.h"
end_include

begin_include
include|#
directive|include
file|"gimpsizeentry.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"pixmaps/new.xpm"
end_include

begin_include
include|#
directive|include
file|"pixmaps/delete.xpm"
end_include

begin_include
include|#
directive|include
file|"pixmaps/raise.xpm"
end_include

begin_include
include|#
directive|include
file|"pixmaps/lower.xpm"
end_include

begin_comment
comment|/*  forward declaration  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_path_editor_select_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_path_editor_deselect_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_path_editor_new_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_path_editor_move_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_path_editor_filesel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_path_editor_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_enum
enum|enum
DECL|enum|__anon2b7023e90103
block|{
DECL|enumerator|PATH_CHANGED
name|PATH_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_decl_stmt
DECL|variable|gimp_path_editor_signals
specifier|static
name|guint
name|gimp_path_editor_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkVBoxClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_path_editor_class_init (GimpPathEditorClass * class)
name|gimp_path_editor_class_init
parameter_list|(
name|GimpPathEditorClass
modifier|*
name|class
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|class
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|gtk_vbox_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|gimp_path_editor_signals
index|[
name|PATH_CHANGED
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"path_changed"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpPathEditorClass
argument_list|,
name|path_changed
argument_list|)
argument_list|,
name|gtk_signal_default_marshaller
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
name|gimp_path_editor_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
name|class
operator|->
name|path_changed
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_path_editor_init (GimpPathEditor * gpe)
name|gimp_path_editor_init
parameter_list|(
name|GimpPathEditor
modifier|*
name|gpe
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button_box
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_window
decl_stmt|;
name|gpe
operator|->
name|file_selection
operator|=
name|NULL
expr_stmt|;
name|gpe
operator|->
name|selected_item
operator|=
name|NULL
expr_stmt|;
name|gpe
operator|->
name|number_of_items
operator|=
literal|0
expr_stmt|;
name|gpe
operator|->
name|upper_hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gpe
argument_list|)
argument_list|,
name|gpe
operator|->
name|upper_hbox
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gpe
operator|->
name|upper_hbox
argument_list|)
expr_stmt|;
name|button_box
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gpe
operator|->
name|upper_hbox
argument_list|)
argument_list|,
name|button_box
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button_box
argument_list|)
expr_stmt|;
name|gpe
operator|->
name|new_button
operator|=
name|button
operator|=
name|gimp_pixmap_button_new
argument_list|(
name|new_xpm
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|button_box
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_path_editor_new_callback
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gpe
operator|->
name|up_button
operator|=
name|button
operator|=
name|gimp_pixmap_button_new
argument_list|(
name|raise_xpm
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|button_box
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_path_editor_move_callback
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gpe
operator|->
name|down_button
operator|=
name|button
operator|=
name|gimp_pixmap_button_new
argument_list|(
name|lower_xpm
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|button_box
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_path_editor_move_callback
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gpe
operator|->
name|delete_button
operator|=
name|button
operator|=
name|gimp_pixmap_button_new
argument_list|(
name|delete_xpm
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|button_box
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_path_editor_delete_callback
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|scrolled_window
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_ALWAYS
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gpe
argument_list|)
argument_list|,
name|scrolled_window
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scrolled_window
argument_list|)
expr_stmt|;
name|gpe
operator|->
name|dir_list
operator|=
name|gtk_list_new
argument_list|()
expr_stmt|;
name|gtk_list_set_selection_mode
argument_list|(
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
argument_list|,
name|GTK_SELECTION_SINGLE
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_add_with_viewport
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|gpe
operator|->
name|dir_list
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_path_editor_get_type (void)
name|gimp_path_editor_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|gpe_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|gpe_type
condition|)
block|{
name|GtkTypeInfo
name|gpe_info
init|=
block|{
literal|"GimpPathEditor"
block|,
sizeof|sizeof
argument_list|(
name|GimpPathEditor
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpPathEditorClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_path_editor_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_path_editor_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|gpe_type
operator|=
name|gtk_type_unique
argument_list|(
name|gtk_vbox_get_type
argument_list|()
argument_list|,
operator|&
name|gpe_info
argument_list|)
expr_stmt|;
block|}
return|return
name|gpe_type
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_editor_new:  * @filesel_title: The title of the #GtkFileSelection dialog which can be  *                 popped up by the attached #GimpFileSelection.  * @path: The initial search path.  *  * Creates a new #GimpPathEditor widget.  *  * The elements of the initial search path must be separated with the  * #G_SEARCHPATH_SEPARATOR character.  *  * Returns: A pointer to the new #GimpPathEditor widget.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_path_editor_new (const gchar * filesel_title,const gchar * path)
name|gimp_path_editor_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filesel_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|)
block|{
name|GimpPathEditor
modifier|*
name|gpe
decl_stmt|;
name|GtkWidget
modifier|*
name|list_item
decl_stmt|;
name|GList
modifier|*
name|directory_list
decl_stmt|;
name|gchar
modifier|*
name|directory
decl_stmt|;
name|gchar
modifier|*
name|mypath
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|(
name|filesel_title
operator|!=
name|NULL
operator|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|(
name|path
operator|!=
name|NULL
operator|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gpe
operator|=
name|gtk_type_new
argument_list|(
name|gimp_path_editor_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|gpe
operator|->
name|file_selection
operator|=
name|gimp_file_selection_new
argument_list|(
name|filesel_title
argument_list|,
literal|""
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|gpe
operator|->
name|file_selection
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gpe
operator|->
name|upper_hbox
argument_list|)
argument_list|,
name|gpe
operator|->
name|file_selection
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
operator|->
name|file_selection
argument_list|)
argument_list|,
literal|"filename_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_path_editor_filesel_callback
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gpe
operator|->
name|file_selection
argument_list|)
expr_stmt|;
name|directory_list
operator|=
name|NULL
expr_stmt|;
name|directory
operator|=
name|mypath
operator|=
name|g_strdup
argument_list|(
name|path
argument_list|)
expr_stmt|;
comment|/*  split up the path  */
while|while
condition|(
name|strlen
argument_list|(
name|directory
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|current_dir
decl_stmt|;
name|gchar
modifier|*
name|next_separator
decl_stmt|;
name|next_separator
operator|=
name|strchr
argument_list|(
name|directory
argument_list|,
name|G_SEARCHPATH_SEPARATOR
argument_list|)
expr_stmt|;
if|if
condition|(
name|next_separator
operator|!=
name|NULL
condition|)
operator|*
name|next_separator
operator|=
literal|'\0'
expr_stmt|;
name|current_dir
operator|=
name|g_strdup
argument_list|(
name|directory
argument_list|)
expr_stmt|;
name|list_item
operator|=
name|gtk_list_item_new_with_label
argument_list|(
name|current_dir
argument_list|)
expr_stmt|;
name|gtk_object_set_data_full
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list_item
argument_list|)
argument_list|,
literal|"gimp_path_editor"
argument_list|,
name|current_dir
argument_list|,
operator|(
name|GtkDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|directory_list
operator|=
name|g_list_append
argument_list|(
name|directory_list
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list_item
argument_list|)
argument_list|,
literal|"select"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_path_editor_select_callback
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list_item
argument_list|)
argument_list|,
literal|"deselect"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_path_editor_deselect_callback
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|list_item
argument_list|)
expr_stmt|;
name|gpe
operator|->
name|number_of_items
operator|++
expr_stmt|;
if|if
condition|(
name|next_separator
operator|!=
name|NULL
condition|)
name|directory
operator|=
name|next_separator
operator|+
literal|1
expr_stmt|;
else|else
break|break;
block|}
name|g_free
argument_list|(
name|mypath
argument_list|)
expr_stmt|;
if|if
condition|(
name|directory_list
condition|)
name|gtk_list_append_items
argument_list|(
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
argument_list|,
name|directory_list
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|gpe
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_editor_get_path:  * @gpe: The path editor you want to get the search path from.  *  * The elements of the returned search path string are separated with the  * #G_SEARCHPATH_SEPARATOR character.  *  * Note that you have to g_free() the returned string.  *  * Returns: The search path the user has selected in the path editor.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_path_editor_get_path (GimpPathEditor * gpe)
name|gimp_path_editor_get_path
parameter_list|(
name|GimpPathEditor
modifier|*
name|gpe
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|path
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gpe
operator|!=
name|NULL
argument_list|,
name|g_strdup
argument_list|(
literal|""
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PATH_EDITOR
argument_list|(
name|gpe
argument_list|)
argument_list|,
name|g_strdup
argument_list|(
literal|""
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
operator|->
name|children
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
if|if
condition|(
name|path
operator|==
name|NULL
condition|)
block|{
name|path
operator|=
name|g_strdup
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|,
literal|"gimp_path_editor"
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|newpath
decl_stmt|;
name|newpath
operator|=
name|g_strconcat
argument_list|(
name|path
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|,
literal|"gimp_path_editor"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|path
operator|=
name|newpath
expr_stmt|;
block|}
block|}
return|return
name|path
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_path_editor_select_callback (GtkWidget * widget,gpointer data)
name|gimp_path_editor_select_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPathEditor
modifier|*
name|gpe
decl_stmt|;
name|gint
name|pos
decl_stmt|;
name|gchar
modifier|*
name|directory
decl_stmt|;
name|gpe
operator|=
name|GIMP_PATH_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|directory
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp_path_editor"
argument_list|)
expr_stmt|;
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
operator|->
name|file_selection
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gimp_file_selection_set_filename
argument_list|(
name|GIMP_FILE_SELECTION
argument_list|(
name|gpe
operator|->
name|file_selection
argument_list|)
argument_list|,
name|directory
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
operator|->
name|file_selection
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gpe
operator|->
name|selected_item
operator|=
name|widget
expr_stmt|;
name|pos
operator|=
name|gtk_list_child_position
argument_list|(
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
argument_list|,
name|gpe
operator|->
name|selected_item
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|gpe
operator|->
name|delete_button
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|gpe
operator|->
name|up_button
argument_list|,
operator|(
name|pos
operator|>
literal|0
operator|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|gpe
operator|->
name|down_button
argument_list|,
operator|(
name|pos
operator|<
operator|(
name|gpe
operator|->
name|number_of_items
operator|-
literal|1
operator|)
operator|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|gpe
operator|->
name|file_selection
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  the selected directory may never be deselected except by the 'new'  *  button, so catch the "deselect" signal and reselect it  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_path_editor_deselect_callback (GtkWidget * widget,gpointer data)
name|gimp_path_editor_deselect_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPathEditor
modifier|*
name|gpe
decl_stmt|;
name|gpe
operator|=
name|GIMP_PATH_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
operator|!=
name|gpe
operator|->
name|selected_item
condition|)
return|return;
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
operator|->
name|selected_item
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gtk_list_select_child
argument_list|(
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
argument_list|,
name|gpe
operator|->
name|selected_item
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
operator|->
name|selected_item
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_path_editor_new_callback (GtkWidget * widget,gpointer data)
name|gimp_path_editor_new_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPathEditor
modifier|*
name|gpe
decl_stmt|;
name|gpe
operator|=
name|GIMP_PATH_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gpe
operator|->
name|selected_item
condition|)
block|{
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
operator|->
name|selected_item
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gtk_list_unselect_child
argument_list|(
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
argument_list|,
name|gpe
operator|->
name|selected_item
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
operator|->
name|selected_item
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
block|}
name|gpe
operator|->
name|selected_item
operator|=
name|NULL
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|gpe
operator|->
name|delete_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|gpe
operator|->
name|up_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|gpe
operator|->
name|down_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|gpe
operator|->
name|file_selection
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_editable_set_position
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|GIMP_FILE_SELECTION
argument_list|(
name|gpe
operator|->
name|file_selection
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|GTK_WIDGET
argument_list|(
name|GIMP_FILE_SELECTION
argument_list|(
name|gpe
operator|->
name|file_selection
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_path_editor_move_callback (GtkWidget * widget,gpointer data)
name|gimp_path_editor_move_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPathEditor
modifier|*
name|gpe
init|=
name|GIMP_PATH_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|move_list
init|=
name|NULL
decl_stmt|;
name|gint
name|pos
decl_stmt|;
name|gint
name|distance
decl_stmt|;
if|if
condition|(
name|gpe
operator|->
name|selected_item
operator|==
name|NULL
condition|)
return|return;
name|pos
operator|=
name|gtk_list_child_position
argument_list|(
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
argument_list|,
name|gpe
operator|->
name|selected_item
argument_list|)
expr_stmt|;
name|distance
operator|=
operator|(
name|widget
operator|==
name|gpe
operator|->
name|up_button
operator|)
condition|?
operator|-
literal|1
else|:
literal|1
expr_stmt|;
name|move_list
operator|=
name|g_list_append
argument_list|(
name|move_list
argument_list|,
name|gpe
operator|->
name|selected_item
argument_list|)
expr_stmt|;
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
operator|->
name|selected_item
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gtk_list_remove_items_no_unref
argument_list|(
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
argument_list|,
name|move_list
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
operator|->
name|selected_item
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gtk_list_insert_items
argument_list|(
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
argument_list|,
name|move_list
argument_list|,
name|pos
operator|+
name|distance
argument_list|)
expr_stmt|;
name|gtk_list_select_item
argument_list|(
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
argument_list|,
name|pos
operator|+
name|distance
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
argument_list|)
argument_list|,
name|gimp_path_editor_signals
index|[
name|PATH_CHANGED
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_path_editor_delete_callback (GtkWidget * widget,gpointer data)
name|gimp_path_editor_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPathEditor
modifier|*
name|gpe
init|=
name|GIMP_PATH_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|delete_list
init|=
name|NULL
decl_stmt|;
name|gint
name|pos
decl_stmt|;
if|if
condition|(
name|gpe
operator|->
name|selected_item
operator|==
name|NULL
condition|)
return|return;
name|pos
operator|=
name|gtk_list_child_position
argument_list|(
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
argument_list|,
name|gpe
operator|->
name|selected_item
argument_list|)
expr_stmt|;
name|delete_list
operator|=
name|g_list_append
argument_list|(
name|delete_list
argument_list|,
name|gpe
operator|->
name|selected_item
argument_list|)
expr_stmt|;
name|gtk_list_remove_items
argument_list|(
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
argument_list|,
name|delete_list
argument_list|)
expr_stmt|;
name|gpe
operator|->
name|number_of_items
operator|--
expr_stmt|;
if|if
condition|(
name|gpe
operator|->
name|number_of_items
operator|==
literal|0
condition|)
block|{
name|gpe
operator|->
name|selected_item
operator|=
name|NULL
expr_stmt|;
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
operator|->
name|file_selection
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gimp_file_selection_set_filename
argument_list|(
name|GIMP_FILE_SELECTION
argument_list|(
name|gpe
operator|->
name|file_selection
argument_list|)
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
operator|->
name|file_selection
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|gpe
operator|->
name|delete_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|gpe
operator|->
name|file_selection
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|(
name|pos
operator|==
name|gpe
operator|->
name|number_of_items
operator|)
operator|&&
operator|(
name|pos
operator|>
literal|0
operator|)
condition|)
name|pos
operator|--
expr_stmt|;
name|gtk_list_select_item
argument_list|(
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
argument_list|,
name|pos
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
argument_list|)
argument_list|,
name|gimp_path_editor_signals
index|[
name|PATH_CHANGED
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_path_editor_filesel_callback (GtkWidget * widget,gpointer data)
name|gimp_path_editor_filesel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPathEditor
modifier|*
name|gpe
init|=
name|GIMP_PATH_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|append_list
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|list_item
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|directory
decl_stmt|;
name|directory
operator|=
name|gimp_file_selection_get_filename
argument_list|(
name|GIMP_FILE_SELECTION
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|directory
argument_list|,
literal|""
argument_list|)
operator|==
literal|0
condition|)
return|return;
if|if
condition|(
name|gpe
operator|->
name|selected_item
operator|==
name|NULL
condition|)
block|{
name|list_item
operator|=
name|gtk_list_item_new_with_label
argument_list|(
name|directory
argument_list|)
expr_stmt|;
name|gtk_object_set_data_full
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list_item
argument_list|)
argument_list|,
literal|"gimp_path_editor"
argument_list|,
name|directory
argument_list|,
operator|(
name|GtkDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|append_list
operator|=
name|g_list_append
argument_list|(
name|append_list
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list_item
argument_list|)
argument_list|,
literal|"select"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_path_editor_select_callback
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list_item
argument_list|)
argument_list|,
literal|"deselect"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_path_editor_deselect_callback
argument_list|)
argument_list|,
name|gpe
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|list_item
argument_list|)
expr_stmt|;
name|gpe
operator|->
name|number_of_items
operator|++
expr_stmt|;
name|gtk_list_append_items
argument_list|(
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
argument_list|,
name|append_list
argument_list|)
expr_stmt|;
name|gtk_list_select_item
argument_list|(
name|GTK_LIST
argument_list|(
name|gpe
operator|->
name|dir_list
argument_list|)
argument_list|,
name|gpe
operator|->
name|number_of_items
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|gpe
operator|->
name|selected_item
argument_list|)
operator|->
name|child
argument_list|)
argument_list|,
name|directory
argument_list|)
expr_stmt|;
name|gtk_object_set_data_full
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
operator|->
name|selected_item
argument_list|)
argument_list|,
literal|"gimp_path_editor"
argument_list|,
name|directory
argument_list|,
operator|(
name|GtkDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
block|}
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gpe
argument_list|)
argument_list|,
name|gimp_path_editor_signals
index|[
name|PATH_CHANGED
index|]
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

