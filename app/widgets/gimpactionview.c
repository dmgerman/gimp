begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpactionview.c  * Copyright (C) 2004  Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpaction.h"
end_include

begin_include
include|#
directive|include
file|"gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"gimpactionview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcellrendereraccel.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon27447a830103
block|{
DECL|enumerator|COLUMN_ACTION
name|COLUMN_ACTION
block|,
DECL|enumerator|COLUMN_STOCK_ID
name|COLUMN_STOCK_ID
block|,
DECL|enumerator|COLUMN_LABEL
name|COLUMN_LABEL
block|,
DECL|enumerator|COLUMN_NAME
name|COLUMN_NAME
block|,
DECL|enumerator|COLUMN_ACCEL_KEY
name|COLUMN_ACCEL_KEY
block|,
DECL|enumerator|COLUMN_ACCEL_MASK
name|COLUMN_ACCEL_MASK
block|,
DECL|enumerator|COLUMN_MENU_ITEM
name|COLUMN_MENU_ITEM
block|,
DECL|enumerator|NUM_COLUMNS
name|NUM_COLUMNS
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_action_view_class_init
parameter_list|(
name|GimpActionViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_action_view_init
parameter_list|(
name|GimpActionView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_action_view_accel_find_func
parameter_list|(
name|GtkAccelKey
modifier|*
name|key
parameter_list|,
name|GClosure
modifier|*
name|closure
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_action_view_accel_changed
parameter_list|(
name|GtkAccelGroup
modifier|*
name|accel_group
parameter_list|,
name|guint
name|unused1
parameter_list|,
name|GdkModifierType
name|unused2
parameter_list|,
name|GClosure
modifier|*
name|accel_closure
parameter_list|,
name|GimpActionView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_action_view_accel_edited
parameter_list|(
name|GimpCellRendererAccel
modifier|*
name|accel
parameter_list|,
specifier|const
name|char
modifier|*
name|path_string
parameter_list|,
name|guint
name|accel_key
parameter_list|,
name|GdkModifierType
name|accel_mask
parameter_list|,
name|GimpActionView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_action_view_get_type (void)
name|gimp_action_view_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|view_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|view_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|view_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpActionViewClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init      */
name|NULL
block|,
comment|/* base_finalize  */
operator|(
name|GClassInitFunc
operator|)
name|gimp_action_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpActionView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_action_view_init
block|}
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_TREE_VIEW
argument_list|,
literal|"GimpActionView"
argument_list|,
operator|&
name|view_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|view_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_action_view_class_init (GimpActionViewClass * klass)
name|gimp_action_view_class_init
parameter_list|(
name|GimpActionViewClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_action_view_init (GimpActionView * view)
name|gimp_action_view_init
parameter_list|(
name|GimpActionView
modifier|*
name|view
parameter_list|)
block|{ }
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_action_view_new (GimpUIManager * manager,gboolean show_shortcuts)
name|gimp_action_view_new
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
name|gboolean
name|show_shortcuts
parameter_list|)
block|{
name|GtkTreeView
modifier|*
name|view
decl_stmt|;
name|GtkTreeViewColumn
modifier|*
name|column
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|GtkTreeStore
modifier|*
name|store
decl_stmt|;
name|GtkAccelGroup
modifier|*
name|accel_group
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|store
operator|=
name|gtk_tree_store_new
argument_list|(
name|NUM_COLUMNS
argument_list|,
name|GTK_TYPE_ACTION
argument_list|,
comment|/* COLUMN_ACTION     */
name|G_TYPE_STRING
argument_list|,
comment|/* COLUMN_STOCK_ID   */
name|G_TYPE_STRING
argument_list|,
comment|/* COLUMN_LABEL      */
name|G_TYPE_STRING
argument_list|,
comment|/* COLUMN_NAME       */
name|G_TYPE_UINT
argument_list|,
comment|/* COLUMN_ACCEL_KEY  */
name|GDK_TYPE_MODIFIER_TYPE
argument_list|,
comment|/* COLUMN_ACCEL_MASK */
name|GTK_TYPE_MENU_ITEM
argument_list|)
expr_stmt|;
comment|/* COLUMN_MENU_ITEM  */
name|accel_group
operator|=
name|gtk_ui_manager_get_accel_group
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gtk_ui_manager_get_action_groups
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpActionGroup
modifier|*
name|group
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GList
modifier|*
name|actions
decl_stmt|;
name|GList
modifier|*
name|list2
decl_stmt|;
name|GtkTreeIter
name|group_iter
decl_stmt|;
name|gtk_tree_store_append
argument_list|(
name|store
argument_list|,
operator|&
name|group_iter
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|group_iter
argument_list|,
name|COLUMN_STOCK_ID
argument_list|,
name|group
operator|->
name|stock_id
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|group
operator|->
name|label
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|actions
operator|=
name|gtk_action_group_list_actions
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
name|actions
operator|=
name|g_list_sort
argument_list|(
name|actions
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|gimp_action_name_compare
argument_list|)
expr_stmt|;
for|for
control|(
name|list2
operator|=
name|actions
init|;
name|list2
condition|;
name|list2
operator|=
name|g_list_next
argument_list|(
name|list2
argument_list|)
control|)
block|{
name|GtkAction
modifier|*
name|action
init|=
name|list2
operator|->
name|data
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
init|=
name|gtk_action_get_name
argument_list|(
name|action
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|strstr
argument_list|(
name|name
argument_list|,
literal|"-menu"
argument_list|)
operator|&&
operator|!
name|strstr
argument_list|(
name|name
argument_list|,
literal|"-popup"
argument_list|)
condition|)
block|{
name|GtkTreeIter
name|action_iter
decl_stmt|;
name|gchar
modifier|*
name|stock_id
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|gchar
modifier|*
name|stripped
decl_stmt|;
name|guint
name|accel_key
init|=
literal|0
decl_stmt|;
name|GdkModifierType
name|accel_mask
init|=
literal|0
decl_stmt|;
name|GtkWidget
modifier|*
name|menu_item
init|=
name|NULL
decl_stmt|;
name|g_object_get
argument_list|(
name|action
argument_list|,
literal|"stock-id"
argument_list|,
operator|&
name|stock_id
argument_list|,
literal|"label"
argument_list|,
operator|&
name|label
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|stripped
operator|=
name|gimp_strip_uline
argument_list|(
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
name|show_shortcuts
condition|)
block|{
name|gtk_action_set_accel_group
argument_list|(
name|action
argument_list|,
name|accel_group
argument_list|)
expr_stmt|;
name|menu_item
operator|=
name|gtk_action_create_menu_item
argument_list|(
name|action
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_MENU_ITEM
argument_list|(
name|menu_item
argument_list|)
operator|&&
name|GTK_IS_ACCEL_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|menu_item
argument_list|)
operator|->
name|child
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|accel_label
init|=
name|GTK_BIN
argument_list|(
name|menu_item
argument_list|)
operator|->
name|child
decl_stmt|;
name|GClosure
modifier|*
name|accel_closure
decl_stmt|;
name|g_object_get
argument_list|(
name|accel_label
argument_list|,
literal|"accel-closure"
argument_list|,
operator|&
name|accel_closure
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|accel_closure
condition|)
block|{
name|GtkAccelKey
modifier|*
name|key
decl_stmt|;
name|key
operator|=
name|gtk_accel_group_find
argument_list|(
name|accel_group
argument_list|,
name|gimp_action_view_accel_find_func
argument_list|,
name|accel_closure
argument_list|)
expr_stmt|;
if|if
condition|(
name|key
operator|&&
name|key
operator|->
name|accel_key
operator|&&
name|key
operator|->
name|accel_flags
operator|&
name|GTK_ACCEL_VISIBLE
condition|)
block|{
name|accel_key
operator|=
name|key
operator|->
name|accel_key
expr_stmt|;
name|accel_mask
operator|=
name|key
operator|->
name|accel_mods
expr_stmt|;
block|}
block|}
name|g_object_ref
argument_list|(
name|menu_item
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menu_item
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|menu_item
condition|)
block|{
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menu_item
argument_list|)
argument_list|)
expr_stmt|;
name|menu_item
operator|=
name|NULL
expr_stmt|;
block|}
block|}
name|gtk_tree_store_append
argument_list|(
name|store
argument_list|,
operator|&
name|action_iter
argument_list|,
operator|&
name|group_iter
argument_list|)
expr_stmt|;
name|gtk_tree_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|action_iter
argument_list|,
name|COLUMN_ACTION
argument_list|,
name|action
argument_list|,
name|COLUMN_STOCK_ID
argument_list|,
name|stock_id
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|stripped
argument_list|,
name|COLUMN_NAME
argument_list|,
name|name
argument_list|,
name|COLUMN_ACCEL_KEY
argument_list|,
name|accel_key
argument_list|,
name|COLUMN_ACCEL_MASK
argument_list|,
name|accel_mask
argument_list|,
name|COLUMN_MENU_ITEM
argument_list|,
name|menu_item
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stock_id
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stripped
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu_item
condition|)
name|g_object_unref
argument_list|(
name|menu_item
argument_list|)
expr_stmt|;
block|}
block|}
name|g_list_free
argument_list|(
name|actions
argument_list|)
expr_stmt|;
block|}
name|view
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ACTION_VIEW
argument_list|,
literal|"model"
argument_list|,
name|store
argument_list|,
literal|"rules-hint"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|column
operator|=
name|gtk_tree_view_column_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_set_title
argument_list|(
name|column
argument_list|,
name|_
argument_list|(
literal|"Action"
argument_list|)
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_pixbuf_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_attributes
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
literal|"stock-id"
argument_list|,
name|COLUMN_STOCK_ID
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_attributes
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
literal|"text"
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_append_column
argument_list|(
name|view
argument_list|,
name|column
argument_list|)
expr_stmt|;
if|if
condition|(
name|show_shortcuts
condition|)
block|{
name|g_signal_connect_object
argument_list|(
name|accel_group
argument_list|,
literal|"accel-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_action_view_accel_changed
argument_list|)
argument_list|,
name|view
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|column
operator|=
name|gtk_tree_view_column_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_set_title
argument_list|(
name|column
argument_list|,
name|_
argument_list|(
literal|"Shortcut"
argument_list|)
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gimp_cell_renderer_accel_new
argument_list|()
expr_stmt|;
name|cell
operator|->
name|mode
operator|=
name|GTK_CELL_RENDERER_MODE_EDITABLE
expr_stmt|;
name|GTK_CELL_RENDERER_TEXT
argument_list|(
name|cell
argument_list|)
operator|->
name|editable
operator|=
name|TRUE
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_attributes
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
literal|"accel-key"
argument_list|,
name|COLUMN_ACCEL_KEY
argument_list|,
literal|"accel-mask"
argument_list|,
name|COLUMN_ACCEL_MASK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|cell
argument_list|,
literal|"accel-edited"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_action_view_accel_edited
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_tree_view_append_column
argument_list|(
name|view
argument_list|,
name|column
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|column
operator|=
name|gtk_tree_view_column_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_set_title
argument_list|(
name|column
argument_list|,
name|_
argument_list|(
literal|"Name"
argument_list|)
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_attributes
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
literal|"text"
argument_list|,
name|COLUMN_NAME
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_append_column
argument_list|(
name|view
argument_list|,
name|column
argument_list|)
expr_stmt|;
block|}
return|return
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_action_view_accel_find_func (GtkAccelKey * key,GClosure * closure,gpointer data)
name|gimp_action_view_accel_find_func
parameter_list|(
name|GtkAccelKey
modifier|*
name|key
parameter_list|,
name|GClosure
modifier|*
name|closure
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
return|return
operator|(
name|GClosure
operator|*
operator|)
name|data
operator|==
name|closure
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_action_view_accel_changed (GtkAccelGroup * accel_group,guint unused1,GdkModifierType unused2,GClosure * accel_closure,GimpActionView * view)
name|gimp_action_view_accel_changed
parameter_list|(
name|GtkAccelGroup
modifier|*
name|accel_group
parameter_list|,
name|guint
name|unused1
parameter_list|,
name|GdkModifierType
name|unused2
parameter_list|,
name|GClosure
modifier|*
name|accel_closure
parameter_list|,
name|GimpActionView
modifier|*
name|view
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
name|model
operator|=
name|gtk_tree_view_get_model
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|model
condition|)
return|return;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
control|)
block|{
name|GtkTreeIter
name|child_iter
decl_stmt|;
name|gboolean
name|child_valid
decl_stmt|;
for|for
control|(
name|child_valid
operator|=
name|gtk_tree_model_iter_children
argument_list|(
name|model
argument_list|,
operator|&
name|child_iter
argument_list|,
operator|&
name|iter
argument_list|)
init|;
name|child_valid
condition|;
name|child_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
operator|&
name|child_iter
argument_list|)
control|)
block|{
name|GtkWidget
modifier|*
name|menu_item
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|child_iter
argument_list|,
name|COLUMN_MENU_ITEM
argument_list|,
operator|&
name|menu_item
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu_item
condition|)
block|{
name|GClosure
modifier|*
name|item_closure
decl_stmt|;
name|g_object_get
argument_list|(
name|GTK_BIN
argument_list|(
name|menu_item
argument_list|)
operator|->
name|child
argument_list|,
literal|"accel-closure"
argument_list|,
operator|&
name|item_closure
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|menu_item
argument_list|)
expr_stmt|;
if|if
condition|(
name|accel_closure
operator|==
name|item_closure
condition|)
block|{
name|GtkAccelKey
modifier|*
name|key
decl_stmt|;
name|guint
name|accel_key
init|=
literal|0
decl_stmt|;
name|GdkModifierType
name|accel_mask
init|=
literal|0
decl_stmt|;
name|key
operator|=
name|gtk_accel_group_find
argument_list|(
name|accel_group
argument_list|,
name|gimp_action_view_accel_find_func
argument_list|,
name|accel_closure
argument_list|)
expr_stmt|;
if|if
condition|(
name|key
operator|&&
name|key
operator|->
name|accel_key
operator|&&
name|key
operator|->
name|accel_flags
operator|&
name|GTK_ACCEL_VISIBLE
condition|)
block|{
name|accel_key
operator|=
name|key
operator|->
name|accel_key
expr_stmt|;
name|accel_mask
operator|=
name|key
operator|->
name|accel_mods
expr_stmt|;
block|}
name|gtk_tree_store_set
argument_list|(
name|GTK_TREE_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
operator|&
name|child_iter
argument_list|,
name|COLUMN_ACCEL_KEY
argument_list|,
name|accel_key
argument_list|,
name|COLUMN_ACCEL_MASK
argument_list|,
name|accel_mask
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
block|}
block|}
block|}
end_function

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27447a830208
block|{
DECL|member|accel_path
name|gchar
modifier|*
name|accel_path
decl_stmt|;
DECL|member|accel_key
name|guint
name|accel_key
decl_stmt|;
DECL|member|accel_mask
name|GdkModifierType
name|accel_mask
decl_stmt|;
DECL|typedef|ConfirmData
block|}
name|ConfirmData
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|gimp_action_view_accel_confirm (GtkWidget * query_box,gboolean value,gpointer data)
name|gimp_action_view_accel_confirm
parameter_list|(
name|GtkWidget
modifier|*
name|query_box
parameter_list|,
name|gboolean
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|value
condition|)
block|{
name|ConfirmData
modifier|*
name|confirm_data
init|=
name|data
decl_stmt|;
if|if
condition|(
operator|!
name|gtk_accel_map_change_entry
argument_list|(
name|confirm_data
operator|->
name|accel_path
argument_list|,
name|confirm_data
operator|->
name|accel_key
argument_list|,
name|confirm_data
operator|->
name|accel_mask
argument_list|,
name|TRUE
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Changing shortcut failed."
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_action_view_accel_edited (GimpCellRendererAccel * accel,const char * path_string,guint accel_key,GdkModifierType accel_mask,GimpActionView * view)
name|gimp_action_view_accel_edited
parameter_list|(
name|GimpCellRendererAccel
modifier|*
name|accel
parameter_list|,
specifier|const
name|char
modifier|*
name|path_string
parameter_list|,
name|guint
name|accel_key
parameter_list|,
name|GdkModifierType
name|accel_mask
parameter_list|,
name|GimpActionView
modifier|*
name|view
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|model
operator|=
name|gtk_tree_view_get_model
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|model
condition|)
return|return;
name|path
operator|=
name|gtk_tree_path_new_from_string
argument_list|(
name|path_string
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|path
argument_list|)
condition|)
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|GtkActionGroup
modifier|*
name|group
decl_stmt|;
name|gchar
modifier|*
name|accel_path
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_ACTION
argument_list|,
operator|&
name|action
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|action
condition|)
goto|goto
name|done
goto|;
name|g_object_get
argument_list|(
name|action
argument_list|,
literal|"action-group"
argument_list|,
operator|&
name|group
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|group
condition|)
block|{
name|g_object_unref
argument_list|(
name|action
argument_list|)
expr_stmt|;
goto|goto
name|done
goto|;
block|}
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: remove accel_path hack
endif|#
directive|endif
name|accel_path
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"gimp-accel-path"
argument_list|)
expr_stmt|;
if|if
condition|(
name|accel_path
condition|)
name|accel_path
operator|=
name|g_strdup
argument_list|(
name|accel_path
argument_list|)
expr_stmt|;
else|else
name|accel_path
operator|=
name|g_strdup_printf
argument_list|(
literal|"<Actions>/%s/%s"
argument_list|,
name|gtk_action_group_get_name
argument_list|(
name|group
argument_list|)
argument_list|,
name|gtk_action_get_name
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|accel_key
condition|)
block|{
if|if
condition|(
operator|!
name|gtk_accel_map_change_entry
argument_list|(
name|accel_path
argument_list|,
name|accel_key
argument_list|,
name|accel_mask
argument_list|,
name|FALSE
argument_list|)
condition|)
block|{
name|GtkAction
modifier|*
name|conflict_action
init|=
name|NULL
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
control|)
block|{
name|GtkTreeIter
name|child_iter
decl_stmt|;
name|gboolean
name|child_valid
decl_stmt|;
for|for
control|(
name|child_valid
operator|=
name|gtk_tree_model_iter_children
argument_list|(
name|model
argument_list|,
operator|&
name|child_iter
argument_list|,
operator|&
name|iter
argument_list|)
init|;
name|child_valid
condition|;
name|child_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
operator|&
name|child_iter
argument_list|)
control|)
block|{
name|guint
name|child_accel_key
decl_stmt|;
name|GdkModifierType
name|child_accel_mask
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|child_iter
argument_list|,
name|COLUMN_ACCEL_KEY
argument_list|,
operator|&
name|child_accel_key
argument_list|,
name|COLUMN_ACCEL_MASK
argument_list|,
operator|&
name|child_accel_mask
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|accel_key
operator|==
name|child_accel_key
operator|&&
name|accel_mask
operator|==
name|child_accel_mask
condition|)
block|{
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|child_iter
argument_list|,
name|COLUMN_ACTION
argument_list|,
operator|&
name|conflict_action
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|conflict_action
condition|)
break|break;
block|}
if|if
condition|(
name|conflict_action
condition|)
block|{
name|GimpActionGroup
modifier|*
name|conflict_group
decl_stmt|;
name|gchar
modifier|*
name|accel_string
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|gchar
modifier|*
name|stripped
decl_stmt|;
name|gchar
modifier|*
name|message
decl_stmt|;
name|ConfirmData
modifier|*
name|confirm_data
decl_stmt|;
name|GtkWidget
modifier|*
name|query_box
decl_stmt|;
name|g_object_get
argument_list|(
name|conflict_action
argument_list|,
literal|"action-group"
argument_list|,
operator|&
name|conflict_group
argument_list|,
literal|"label"
argument_list|,
operator|&
name|label
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|stripped
operator|=
name|gimp_strip_uline
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|accel_string
operator|=
name|gimp_get_accel_string
argument_list|(
name|accel_key
argument_list|,
name|accel_mask
argument_list|)
expr_stmt|;
name|message
operator|=
name|g_strdup_printf
argument_list|(
literal|"Shortcut \"%s\" is already taken by "
literal|"\"%s\" from the \"%s\" group.\n"
literal|"\n"
literal|"Click \"Delete Old Shortcut\" to "
literal|"assign the shortcut anyway, "
literal|"deleting %s's shortcut."
argument_list|,
name|accel_string
argument_list|,
name|stripped
argument_list|,
name|conflict_group
operator|->
name|label
argument_list|,
name|stripped
argument_list|)
expr_stmt|;
name|confirm_data
operator|=
name|g_new0
argument_list|(
name|ConfirmData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|confirm_data
operator|->
name|accel_path
operator|=
name|g_strdup
argument_list|(
name|accel_path
argument_list|)
expr_stmt|;
name|confirm_data
operator|->
name|accel_key
operator|=
name|accel_key
expr_stmt|;
name|confirm_data
operator|->
name|accel_mask
operator|=
name|accel_mask
expr_stmt|;
name|query_box
operator|=
name|gimp_query_boolean_box
argument_list|(
name|_
argument_list|(
literal|"Conflicting Shortcuts"
argument_list|)
argument_list|,
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_WARNING
argument_list|,
name|message
argument_list|,
name|_
argument_list|(
literal|"Delete Old Shortcut"
argument_list|)
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|gimp_action_view_accel_confirm
argument_list|,
name|confirm_data
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|query_box
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_free
argument_list|,
name|confirm_data
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|query_box
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_free
argument_list|,
name|confirm_data
operator|->
name|accel_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|message
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|accel_string
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stripped
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|conflict_group
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|conflict_action
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|query_box
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Changing shortcut failed."
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|accel_mask
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_accel_map_change_entry
argument_list|(
name|accel_path
argument_list|,
name|accel_key
argument_list|,
name|accel_mask
argument_list|,
name|FALSE
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Removing shortcut failed."
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|accel_path
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|group
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|action
argument_list|)
expr_stmt|;
block|}
name|done
label|:
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

