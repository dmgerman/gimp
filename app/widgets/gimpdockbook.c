begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockbook.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockbook.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_define
DECL|macro|DEFAULT_TAB_BORDER
define|#
directive|define
name|DEFAULT_TAB_BORDER
value|0
end_define

begin_define
DECL|macro|DEFAULT_TAB_ICON_SIZE
define|#
directive|define
name|DEFAULT_TAB_ICON_SIZE
value|GTK_ICON_SIZE_BUTTON
end_define

begin_define
DECL|macro|DND_WIDGET_ICON_SIZE
define|#
directive|define
name|DND_WIDGET_ICON_SIZE
value|GTK_ICON_SIZE_DND
end_define

begin_define
DECL|macro|MENU_WIDGET_ICON_SIZE
define|#
directive|define
name|MENU_WIDGET_ICON_SIZE
value|GTK_ICON_SIZE_MENU
end_define

begin_define
DECL|macro|MENU_WIDGET_SPACING
define|#
directive|define
name|MENU_WIDGET_SPACING
value|4
end_define

begin_enum
enum|enum
DECL|enum|__anon295393230103
block|{
DECL|enumerator|DOCKABLE_ADDED
name|DOCKABLE_ADDED
block|,
DECL|enumerator|DOCKABLE_REMOVED
name|DOCKABLE_REMOVED
block|,
DECL|enumerator|DOCKABLE_REORDERED
name|DOCKABLE_REORDERED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_class_init
parameter_list|(
name|GimpDockbookClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_init
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dockbook_drag_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_dockable_added
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_dockable_removed
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_update_tabs
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|gboolean
name|added
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_tab_drag_begin
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_tab_drag_end
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dockbook_tab_drag_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|time
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockbook_help_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkNotebookClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dockbook_signals
specifier|static
name|guint
name|dockbook_signals
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
DECL|variable|dialog_target_table
specifier|static
name|GtkTargetEntry
name|dialog_target_table
index|[]
init|=
block|{
name|GIMP_TARGET_DIALOG
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_dockbook_get_type (void)
name|gimp_dockbook_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|dockbook_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|dockbook_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|dockbook_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpDockbookClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_dockbook_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpDockbook
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_dockbook_init
block|,       }
decl_stmt|;
name|dockbook_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_NOTEBOOK
argument_list|,
literal|"GimpDockbook"
argument_list|,
operator|&
name|dockbook_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|dockbook_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_class_init (GimpDockbookClass * klass)
name|gimp_dockbook_class_init
parameter_list|(
name|GimpDockbookClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|widget_class
operator|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|dockbook_signals
index|[
name|DOCKABLE_ADDED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"dockable_added"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpDockbookClass
argument_list|,
name|dockable_added
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__OBJECT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_DOCKABLE
argument_list|)
expr_stmt|;
name|dockbook_signals
index|[
name|DOCKABLE_REMOVED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"dockable_removed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpDockbookClass
argument_list|,
name|dockable_removed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__OBJECT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_DOCKABLE
argument_list|)
expr_stmt|;
name|dockbook_signals
index|[
name|DOCKABLE_REORDERED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"dockable_reordered"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpDockbookClass
argument_list|,
name|dockable_reordered
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__OBJECT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_DOCKABLE
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_dockbook_finalize
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_dockbook_style_set
expr_stmt|;
name|widget_class
operator|->
name|drag_drop
operator|=
name|gimp_dockbook_drag_drop
expr_stmt|;
name|klass
operator|->
name|dockable_added
operator|=
name|gimp_dockbook_dockable_added
expr_stmt|;
name|klass
operator|->
name|dockable_removed
operator|=
name|gimp_dockbook_dockable_removed
expr_stmt|;
name|klass
operator|->
name|dockable_reordered
operator|=
name|NULL
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"tab_border"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
name|DEFAULT_TAB_BORDER
argument_list|,
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"tab_icon_size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_TYPE_ICON_SIZE
argument_list|,
name|DEFAULT_TAB_ICON_SIZE
argument_list|,
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_init (GimpDockbook * dockbook)
name|gimp_dockbook_init
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
block|{
name|dockbook
operator|->
name|dock
operator|=
name|NULL
expr_stmt|;
name|dockbook
operator|->
name|ui_manager
operator|=
name|NULL
expr_stmt|;
name|gtk_notebook_popup_enable
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_notebook_set_scrollable
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|dialog_target_table
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dialog_target_table
argument_list|)
argument_list|,
name|GDK_ACTION_MOVE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_finalize (GObject * object)
name|gimp_dockbook_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDockbook
modifier|*
name|dockbook
init|=
name|GIMP_DOCKBOOK
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|dockbook
operator|->
name|ui_manager
condition|)
block|{
name|g_object_unref
argument_list|(
name|dockbook
operator|->
name|ui_manager
argument_list|)
expr_stmt|;
name|dockbook
operator|->
name|ui_manager
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_dockbook_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
block|{
name|GList
modifier|*
name|children
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|tab_border
decl_stmt|;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
condition|)
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
argument_list|(
name|widget
argument_list|,
name|prev_style
argument_list|)
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"tab_border"
argument_list|,
operator|&
name|tab_border
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|widget
argument_list|,
literal|"tab_border"
argument_list|,
name|tab_border
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|children
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
name|GtkWidget
modifier|*
name|tab_widget
decl_stmt|;
name|tab_widget
operator|=
name|gimp_dockbook_get_tab_widget
argument_list|(
name|GIMP_DOCKBOOK
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_DOCKABLE
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_notebook_set_tab_label
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|,
name|tab_widget
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dockbook_drag_drop (GtkWidget * widget,GdkDragContext * context,gint x,gint y,guint time)
name|gimp_dockbook_drag_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|time
parameter_list|)
block|{
return|return
name|gimp_dockbook_drop_dockable
argument_list|(
name|GIMP_DOCKBOOK
argument_list|(
name|widget
argument_list|)
argument_list|,
name|gtk_drag_get_source_widget
argument_list|(
name|context
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_dockable_added (GimpDockbook * dockbook,GimpDockable * dockable)
name|gimp_dockbook_dockable_added
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|gimp_dockbook_update_tabs
argument_list|(
name|dockbook
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_dockable_removed (GimpDockbook * dockbook,GimpDockable * dockable)
name|gimp_dockbook_dockable_removed
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|gimp_dockbook_update_tabs
argument_list|(
name|dockbook
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_update_tabs (GimpDockbook * dockbook,gboolean added)
name|gimp_dockbook_update_tabs
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|gboolean
name|added
parameter_list|)
block|{
switch|switch
condition|(
name|gtk_notebook_get_n_pages
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
condition|)
block|{
case|case
literal|1
case|:
name|gtk_notebook_set_show_tabs
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
break|break;
case|case
literal|2
case|:
if|if
condition|(
name|added
condition|)
name|gtk_notebook_set_show_tabs
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dockbook_new (GimpMenuFactory * menu_factory)
name|gimp_dockbook_new
parameter_list|(
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|GimpDockbook
modifier|*
name|dockbook
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dockbook
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DOCKBOOK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dockbook
operator|->
name|ui_manager
operator|=
name|gimp_menu_factory_manager_new
argument_list|(
name|menu_factory
argument_list|,
literal|"<Dialogs>"
argument_list|,
name|dockbook
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_help_connect
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|gimp_dockbook_help_func
argument_list|,
name|GIMP_HELP_DOCK
argument_list|,
name|dockbook
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dockbook_add (GimpDockbook * dockbook,GimpDockable * dockable,gint position)
name|gimp_dockbook_add
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|gint
name|position
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|tab_widget
decl_stmt|;
name|GtkWidget
modifier|*
name|menu_widget
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dockbook
operator|->
name|dock
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dockable
operator|->
name|dockbook
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|tab_widget
operator|=
name|gimp_dockbook_get_tab_widget
argument_list|(
name|dockbook
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|tab_widget
argument_list|)
argument_list|)
expr_stmt|;
name|menu_widget
operator|=
name|gimp_dockable_get_tab_widget
argument_list|(
name|dockable
argument_list|,
name|dockbook
operator|->
name|dock
operator|->
name|context
argument_list|,
name|GIMP_TAB_STYLE_ICON_BLURB
argument_list|,
name|MENU_WIDGET_ICON_SIZE
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|menu_widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|position
operator|==
operator|-
literal|1
condition|)
block|{
name|gtk_notebook_append_page_menu
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|tab_widget
argument_list|,
name|menu_widget
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_notebook_insert_page_menu
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|tab_widget
argument_list|,
name|menu_widget
argument_list|,
name|position
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|dockbook
operator|=
name|dockbook
expr_stmt|;
name|gimp_dockable_set_context
argument_list|(
name|dockable
argument_list|,
name|dockbook
operator|->
name|dock
operator|->
name|context
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|dockbook
argument_list|,
name|dockbook_signals
index|[
name|DOCKABLE_ADDED
index|]
argument_list|,
literal|0
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dockbook_remove (GimpDockbook * dockbook,GimpDockable * dockable)
name|gimp_dockbook_remove
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|GList
modifier|*
name|children
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dockable
operator|->
name|dockbook
operator|==
name|dockbook
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|dockbook
operator|=
name|NULL
expr_stmt|;
name|gimp_dockable_set_context
argument_list|(
name|dockable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|dockbook
argument_list|,
name|dockbook_signals
index|[
name|DOCKABLE_REMOVED
index|]
argument_list|,
literal|0
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_list_length
argument_list|(
name|children
argument_list|)
condition|)
name|gimp_dock_remove_book
argument_list|(
name|dockbook
operator|->
name|dock
argument_list|,
name|dockbook
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dockbook_get_tab_widget (GimpDockbook * dockbook,GimpDockable * dockable)
name|gimp_dockbook_get_tab_widget
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|tab_widget
decl_stmt|;
name|GtkIconSize
name|tab_size
init|=
name|DEFAULT_TAB_ICON_SIZE
decl_stmt|;
name|gtk_widget_style_get
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|,
literal|"tab_icon_size"
argument_list|,
operator|&
name|tab_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tab_widget
operator|=
name|gimp_dockable_get_tab_widget
argument_list|(
name|dockable
argument_list|,
name|dockbook
operator|->
name|dock
operator|->
name|context
argument_list|,
name|dockable
operator|->
name|tab_style
argument_list|,
name|tab_size
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GIMP_IS_PREVIEW
argument_list|(
name|tab_widget
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|event_box
decl_stmt|;
name|event_box
operator|=
name|gtk_event_box_new
argument_list|()
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|event_box
argument_list|)
argument_list|,
name|tab_widget
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tab_widget
argument_list|)
expr_stmt|;
name|tab_widget
operator|=
name|event_box
expr_stmt|;
block|}
name|gimp_help_set_help_data
argument_list|(
name|tab_widget
argument_list|,
name|dockable
operator|->
name|blurb
argument_list|,
name|dockable
operator|->
name|help_id
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|tab_widget
argument_list|)
argument_list|,
literal|"gimp-dockable"
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
comment|/*  set the drag source *before* connecting button_press because we    *  stop button_press emission by returning TRUE from the callback    */
name|gtk_drag_source_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|tab_widget
argument_list|)
argument_list|,
name|GDK_BUTTON1_MASK
operator||
name|GDK_BUTTON2_MASK
argument_list|,
name|dialog_target_table
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dialog_target_table
argument_list|)
argument_list|,
name|GDK_ACTION_MOVE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|tab_widget
argument_list|,
literal|"drag_begin"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dockbook_tab_drag_begin
argument_list|)
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|tab_widget
argument_list|,
literal|"drag_end"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dockbook_tab_drag_end
argument_list|)
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|gtk_drag_source_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|GDK_BUTTON1_MASK
operator||
name|GDK_BUTTON2_MASK
argument_list|,
name|dialog_target_table
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dialog_target_table
argument_list|)
argument_list|,
name|GDK_ACTION_MOVE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dockable
argument_list|,
literal|"drag_begin"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dockbook_tab_drag_begin
argument_list|)
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dockable
argument_list|,
literal|"drag_end"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dockbook_tab_drag_end
argument_list|)
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|tab_widget
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|dialog_target_table
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dialog_target_table
argument_list|)
argument_list|,
name|GDK_ACTION_MOVE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|tab_widget
argument_list|,
literal|"drag_drop"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dockbook_tab_drag_drop
argument_list|)
argument_list|,
name|dockbook
argument_list|)
expr_stmt|;
return|return
name|tab_widget
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_dockbook_drop_dockable (GimpDockbook * dockbook,GtkWidget * drag_source)
name|gimp_dockbook_drop_dockable
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GtkWidget
modifier|*
name|drag_source
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|drag_source
condition|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
if|if
condition|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|drag_source
argument_list|)
condition|)
name|dockable
operator|=
name|GIMP_DOCKABLE
argument_list|(
name|drag_source
argument_list|)
expr_stmt|;
else|else
name|dockable
operator|=
operator|(
name|GimpDockable
operator|*
operator|)
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|drag_source
argument_list|)
argument_list|,
literal|"gimp-dockable"
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
condition|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|,
literal|"gimp-dock-drag-widget"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
operator|->
name|dockbook
operator|!=
name|dockbook
condition|)
block|{
name|g_object_ref
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
name|gimp_dockbook_remove
argument_list|(
name|dockable
operator|->
name|dockbook
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
name|gimp_dockbook_add
argument_list|(
name|dockbook
argument_list|,
name|dockable
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_tab_drag_begin (GtkWidget * widget,GdkDragContext * context,gpointer data)
name|gimp_dockbook_tab_drag_begin
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|GtkWidget
modifier|*
name|window
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|dockable
operator|=
name|GIMP_DOCKABLE
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|window
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_POPUP
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|window
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_dockable_get_tab_widget
argument_list|(
name|dockable
argument_list|,
name|dockable
operator|->
name|context
argument_list|,
name|GIMP_TAB_STYLE_ICON_BLURB
argument_list|,
name|DND_WIDGET_ICON_SIZE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|,
literal|"gimp-dock-drag-widget"
argument_list|,
name|window
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gtk_widget_destroy
argument_list|)
expr_stmt|;
name|gtk_drag_set_icon_widget
argument_list|(
name|context
argument_list|,
name|window
argument_list|,
operator|-
literal|8
argument_list|,
operator|-
literal|8
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_tab_drag_end (GtkWidget * widget,GdkDragContext * context,gpointer data)
name|gimp_dockbook_tab_drag_end
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|GtkWidget
modifier|*
name|drag_widget
decl_stmt|;
name|dockable
operator|=
name|GIMP_DOCKABLE
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|drag_widget
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|,
literal|"gimp-dock-drag-widget"
argument_list|)
expr_stmt|;
comment|/*  finding the drag_widget means the drop was not successful, so    *  pop up a new dock and move the dockable there    */
if|if
condition|(
name|drag_widget
condition|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|,
literal|"gimp-dock-drag-widget"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dockable_detach
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dockbook_tab_drag_drop (GtkWidget * widget,GdkDragContext * context,gint x,gint y,guint time,gpointer data)
name|gimp_dockbook_tab_drag_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|time
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dest_dockable
decl_stmt|;
name|GtkWidget
modifier|*
name|source
decl_stmt|;
name|dest_dockable
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-dockable"
argument_list|)
expr_stmt|;
name|source
operator|=
name|gtk_drag_get_source_widget
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|dest_dockable
operator|&&
name|source
condition|)
block|{
name|GimpDockable
modifier|*
name|src_dockable
decl_stmt|;
if|if
condition|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|source
argument_list|)
condition|)
name|src_dockable
operator|=
name|GIMP_DOCKABLE
argument_list|(
name|source
argument_list|)
expr_stmt|;
else|else
name|src_dockable
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|source
argument_list|)
argument_list|,
literal|"gimp-dockable"
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_dockable
condition|)
block|{
name|gint
name|dest_index
decl_stmt|;
name|dest_index
operator|=
name|gtk_notebook_page_num
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dest_dockable
operator|->
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dest_dockable
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|src_dockable
argument_list|)
argument_list|,
literal|"gimp-dock-drag-widget"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_dockable
operator|->
name|dockbook
operator|!=
name|dest_dockable
operator|->
name|dockbook
condition|)
block|{
name|g_object_ref
argument_list|(
name|src_dockable
argument_list|)
expr_stmt|;
name|gimp_dockbook_remove
argument_list|(
name|src_dockable
operator|->
name|dockbook
argument_list|,
name|src_dockable
argument_list|)
expr_stmt|;
name|gimp_dockbook_add
argument_list|(
name|dest_dockable
operator|->
name|dockbook
argument_list|,
name|src_dockable
argument_list|,
name|dest_index
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|src_dockable
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
elseif|else
if|if
condition|(
name|src_dockable
operator|!=
name|dest_dockable
condition|)
block|{
name|gtk_notebook_reorder_child
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|src_dockable
operator|->
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|src_dockable
argument_list|)
argument_list|,
name|dest_index
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|src_dockable
operator|->
name|dockbook
argument_list|,
name|dockbook_signals
index|[
name|DOCKABLE_REORDERED
index|]
argument_list|,
literal|0
argument_list|,
name|src_dockable
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockbook_help_func (const gchar * help_id,gpointer help_data)
name|gimp_dockbook_help_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
block|{
name|GimpDockbook
modifier|*
name|dockbook
decl_stmt|;
name|GtkWidget
modifier|*
name|dockable
decl_stmt|;
name|gint
name|page_num
decl_stmt|;
name|dockbook
operator|=
name|GIMP_DOCKBOOK
argument_list|(
name|help_data
argument_list|)
expr_stmt|;
name|page_num
operator|=
name|gtk_notebook_get_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|dockable
operator|=
name|gtk_notebook_get_nth_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
condition|)
name|gimp_standard_help_func
argument_list|(
name|GIMP_DOCKABLE
argument_list|(
name|dockable
argument_list|)
operator|->
name|help_id
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|gimp_standard_help_func
argument_list|(
name|GIMP_HELP_DOCK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

