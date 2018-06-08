begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockcolumns.c  * Copyright (C) 2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
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
file|"gimpdialogfactory.h"
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
file|"gimpdockcolumns.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenudock.h"
end_include

begin_include
include|#
directive|include
file|"gimppanedbox.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolbox.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimp-log.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon27d9587c0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONTEXT
name|PROP_CONTEXT
block|,
DECL|enumerator|PROP_DIALOG_FACTORY
name|PROP_DIALOG_FACTORY
block|,
DECL|enumerator|PROP_UI_MANAGER
name|PROP_UI_MANAGER
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon27d9587c0203
block|{
DECL|enumerator|DOCK_ADDED
name|DOCK_ADDED
block|,
DECL|enumerator|DOCK_REMOVED
name|DOCK_REMOVED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpDockColumnsPrivate
struct|struct
name|_GimpDockColumnsPrivate
block|{
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|dialog_factory
name|GimpDialogFactory
modifier|*
name|dialog_factory
decl_stmt|;
DECL|member|ui_manager
name|GimpUIManager
modifier|*
name|ui_manager
decl_stmt|;
DECL|member|docks
name|GList
modifier|*
name|docks
decl_stmt|;
DECL|member|paned_hbox
name|GtkWidget
modifier|*
name|paned_hbox
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_dock_columns_dispose
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
name|gimp_dock_columns_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dock_columns_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dock_columns_dropped_cb
parameter_list|(
name|GtkWidget
modifier|*
name|notebook
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|gint
name|insert_index
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dock_columns_real_dock_added
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dock_columns_real_dock_removed
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dock_columns_dock_book_removed
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDockColumns
argument_list|,
argument|gimp_dock_columns
argument_list|,
argument|GTK_TYPE_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dock_columns_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|dock_columns_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_dock_columns_class_init (GimpDockColumnsClass * klass)
name|gimp_dock_columns_class_init
parameter_list|(
name|GimpDockColumnsClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_dock_columns_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_dock_columns_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_dock_columns_get_property
expr_stmt|;
name|klass
operator|->
name|dock_added
operator|=
name|gimp_dock_columns_real_dock_added
expr_stmt|;
name|klass
operator|->
name|dock_removed
operator|=
name|gimp_dock_columns_real_dock_removed
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTEXT
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"context"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CONTEXT
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_DIALOG_FACTORY
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"dialog-factory"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DIALOG_FACTORY
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_UI_MANAGER
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"ui-manager"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_UI_MANAGER
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|dock_columns_signals
index|[
name|DOCK_ADDED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"dock-added"
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
name|GimpDockColumnsClass
argument_list|,
name|dock_added
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
name|GIMP_TYPE_DOCK
argument_list|)
expr_stmt|;
name|dock_columns_signals
index|[
name|DOCK_REMOVED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"dock-removed"
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
name|GimpDockColumnsClass
argument_list|,
name|dock_removed
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
name|GIMP_TYPE_DOCK
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpDockColumnsPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_columns_init (GimpDockColumns * dock_columns)
name|gimp_dock_columns_init
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|)
block|{
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|dock_columns
argument_list|)
argument_list|,
name|GTK_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
name|dock_columns
operator|->
name|p
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|dock_columns
argument_list|,
name|GIMP_TYPE_DOCK_COLUMNS
argument_list|,
name|GimpDockColumnsPrivate
argument_list|)
expr_stmt|;
name|dock_columns
operator|->
name|p
operator|->
name|paned_hbox
operator|=
name|gimp_paned_box_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|,
name|GTK_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
name|gimp_paned_box_set_dropped_cb
argument_list|(
name|GIMP_PANED_BOX
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|paned_hbox
argument_list|)
argument_list|,
name|gimp_dock_columns_dropped_cb
argument_list|,
name|dock_columns
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dock_columns
argument_list|)
argument_list|,
name|dock_columns
operator|->
name|p
operator|->
name|paned_hbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|paned_hbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_columns_dispose (GObject * object)
name|gimp_dock_columns_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDockColumns
modifier|*
name|dock_columns
init|=
name|GIMP_DOCK_COLUMNS
argument_list|(
name|object
argument_list|)
decl_stmt|;
while|while
condition|(
name|dock_columns
operator|->
name|p
operator|->
name|docks
condition|)
block|{
name|GimpDock
modifier|*
name|dock
init|=
name|dock_columns
operator|->
name|p
operator|->
name|docks
operator|->
name|data
decl_stmt|;
name|g_object_ref
argument_list|(
name|dock
argument_list|)
expr_stmt|;
name|gimp_dock_columns_remove_dock
argument_list|(
name|dock_columns
argument_list|,
name|dock
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dock
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|dock_columns
operator|->
name|p
operator|->
name|context
condition|)
block|{
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|context
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|dock_columns
operator|->
name|p
operator|->
name|context
argument_list|)
expr_stmt|;
name|dock_columns
operator|->
name|p
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|dock_columns
operator|->
name|p
operator|->
name|dialog_factory
condition|)
block|{
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|dialog_factory
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|dock_columns
operator|->
name|p
operator|->
name|dialog_factory
argument_list|)
expr_stmt|;
name|dock_columns
operator|->
name|p
operator|->
name|dialog_factory
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|dock_columns
operator|->
name|p
operator|->
name|ui_manager
condition|)
block|{
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|ui_manager
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|dock_columns
operator|->
name|p
operator|->
name|ui_manager
argument_list|)
expr_stmt|;
name|dock_columns
operator|->
name|p
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
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_columns_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_dock_columns_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpDockColumns
modifier|*
name|dock_columns
init|=
name|GIMP_DOCK_COLUMNS
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CONTEXT
case|:
if|if
condition|(
name|dock_columns
operator|->
name|p
operator|->
name|context
condition|)
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|context
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|dock_columns
operator|->
name|p
operator|->
name|context
argument_list|)
expr_stmt|;
name|dock_columns
operator|->
name|p
operator|->
name|context
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|dock_columns
operator|->
name|p
operator|->
name|context
condition|)
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|context
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|dock_columns
operator|->
name|p
operator|->
name|context
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DIALOG_FACTORY
case|:
if|if
condition|(
name|dock_columns
operator|->
name|p
operator|->
name|dialog_factory
condition|)
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|dialog_factory
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|dock_columns
operator|->
name|p
operator|->
name|dialog_factory
argument_list|)
expr_stmt|;
name|dock_columns
operator|->
name|p
operator|->
name|dialog_factory
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|dock_columns
operator|->
name|p
operator|->
name|dialog_factory
condition|)
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|dialog_factory
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|dock_columns
operator|->
name|p
operator|->
name|dialog_factory
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UI_MANAGER
case|:
if|if
condition|(
name|dock_columns
operator|->
name|p
operator|->
name|ui_manager
condition|)
name|g_object_remove_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|ui_manager
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|dock_columns
operator|->
name|p
operator|->
name|ui_manager
argument_list|)
expr_stmt|;
name|dock_columns
operator|->
name|p
operator|->
name|ui_manager
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|dock_columns
operator|->
name|p
operator|->
name|ui_manager
condition|)
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|ui_manager
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|dock_columns
operator|->
name|p
operator|->
name|ui_manager
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_columns_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_dock_columns_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpDockColumns
modifier|*
name|dock_columns
init|=
name|GIMP_DOCK_COLUMNS
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CONTEXT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|dock_columns
operator|->
name|p
operator|->
name|context
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DIALOG_FACTORY
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|dock_columns
operator|->
name|p
operator|->
name|dialog_factory
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UI_MANAGER
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|dock_columns
operator|->
name|p
operator|->
name|ui_manager
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dock_columns_dropped_cb (GtkWidget * notebook,GtkWidget * child,gint insert_index,gpointer data)
name|gimp_dock_columns_dropped_cb
parameter_list|(
name|GtkWidget
modifier|*
name|notebook
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|gint
name|insert_index
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockColumns
modifier|*
name|dock_columns
init|=
name|GIMP_DOCK_COLUMNS
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpDockable
modifier|*
name|dockable
init|=
name|GIMP_DOCKABLE
argument_list|(
name|child
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|new_dockbook
init|=
name|NULL
decl_stmt|;
comment|/* Create a new dock (including a new dockbook) */
name|gimp_dock_columns_prepare_dockbook
argument_list|(
name|dock_columns
argument_list|,
name|insert_index
argument_list|,
operator|&
name|new_dockbook
argument_list|)
expr_stmt|;
comment|/* Move the dockable to the new dockbook */
name|g_object_ref
argument_list|(
name|new_dockbook
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
name|gtk_notebook_detach_tab
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|child
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|new_dockbook
argument_list|)
argument_list|,
name|child
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|new_dockbook
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_columns_real_dock_added (GimpDockColumns * dock_columns,GimpDock * dock)
name|gimp_dock_columns_real_dock_added
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_columns_real_dock_removed (GimpDockColumns * dock_columns,GimpDock * dock)
name|gimp_dock_columns_real_dock_removed
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_columns_dock_book_removed (GimpDockColumns * dock_columns,GimpDockbook * dockbook,GimpDock * dock)
name|gimp_dock_columns_dock_book_removed
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_dock_get_dockbooks
argument_list|(
name|dock
argument_list|)
operator|==
name|NULL
operator|&&
operator|!
name|GIMP_IS_TOOLBOX
argument_list|(
name|dock
argument_list|)
operator|&&
name|gtk_widget_get_parent
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock
argument_list|)
argument_list|)
operator|!=
name|NULL
condition|)
name|gimp_dock_columns_remove_dock
argument_list|(
name|dock_columns
argument_list|,
name|dock
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_dock_columns_new:  * @context:  *  * Returns: A new #GimpDockColumns.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dock_columns_new (GimpContext * context,GimpDialogFactory * dialog_factory,GimpUIManager * ui_manager)
name|gimp_dock_columns_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpDialogFactory
modifier|*
name|dialog_factory
parameter_list|,
name|GimpUIManager
modifier|*
name|ui_manager
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DIALOG_FACTORY
argument_list|(
name|dialog_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_UI_MANAGER
argument_list|(
name|ui_manager
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_DOCK_COLUMNS
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
literal|"dialog-factory"
argument_list|,
name|dialog_factory
argument_list|,
literal|"ui-manager"
argument_list|,
name|ui_manager
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_dock_columns_add_dock:  * @dock_columns:  * @dock:  *  * Add a dock, added to a horizontal GimpPanedBox.  **/
end_comment

begin_function
name|void
DECL|function|gimp_dock_columns_add_dock (GimpDockColumns * dock_columns,GimpDock * dock,gint index)
name|gimp_dock_columns_add_dock
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK_COLUMNS
argument_list|(
name|dock_columns
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
literal|"Adding GimpDock %p to GimpDockColumns %p"
argument_list|,
name|dock
argument_list|,
name|dock_columns
argument_list|)
expr_stmt|;
name|dock_columns
operator|->
name|p
operator|->
name|docks
operator|=
name|g_list_insert
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|docks
argument_list|,
name|dock
argument_list|,
name|index
argument_list|)
expr_stmt|;
name|gimp_dock_update_with_context
argument_list|(
name|dock
argument_list|,
name|dock_columns
operator|->
name|p
operator|->
name|context
argument_list|)
expr_stmt|;
name|gimp_paned_box_add_widget
argument_list|(
name|GIMP_PANED_BOX
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|paned_hbox
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dock
argument_list|)
argument_list|,
name|index
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|dock
argument_list|,
literal|"book-removed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dock_columns_dock_book_removed
argument_list|)
argument_list|,
name|dock_columns
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|dock_columns
argument_list|,
name|dock_columns_signals
index|[
name|DOCK_ADDED
index|]
argument_list|,
literal|0
argument_list|,
name|dock
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_dock_columns_prepare_dockbook:  * @dock_columns:  * @dock_index:  * @dockbook_p:  *  * Create a new dock and add it to the dock columns with the given  * dock_index insert index, then create and add a dockbook and put it  * in the dock.  **/
end_comment

begin_function
name|void
DECL|function|gimp_dock_columns_prepare_dockbook (GimpDockColumns * dock_columns,gint dock_index,GtkWidget ** dockbook_p)
name|gimp_dock_columns_prepare_dockbook
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|gint
name|dock_index
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|dockbook_p
parameter_list|)
block|{
name|GimpMenuFactory
modifier|*
name|menu_factory
decl_stmt|;
name|GtkWidget
modifier|*
name|dock
decl_stmt|;
name|GtkWidget
modifier|*
name|dockbook
decl_stmt|;
name|dock
operator|=
name|gimp_menu_dock_new
argument_list|()
expr_stmt|;
name|gimp_dock_columns_add_dock
argument_list|(
name|dock_columns
argument_list|,
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|dock_index
argument_list|)
expr_stmt|;
name|menu_factory
operator|=
name|gimp_dialog_factory_get_menu_factory
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|dialog_factory
argument_list|)
expr_stmt|;
name|dockbook
operator|=
name|gimp_dockbook_new
argument_list|(
name|menu_factory
argument_list|)
expr_stmt|;
name|gimp_dock_add_book
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|GIMP_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockbook_p
condition|)
operator|*
name|dockbook_p
operator|=
name|dockbook
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dock_columns_remove_dock (GimpDockColumns * dock_columns,GimpDock * dock)
name|gimp_dock_columns_remove_dock
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK_COLUMNS
argument_list|(
name|dock_columns
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
literal|"Removing GimpDock %p from GimpDockColumns %p"
argument_list|,
name|dock
argument_list|,
name|dock_columns
argument_list|)
expr_stmt|;
name|dock_columns
operator|->
name|p
operator|->
name|docks
operator|=
name|g_list_remove
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|docks
argument_list|,
name|dock
argument_list|)
expr_stmt|;
name|gimp_dock_update_with_context
argument_list|(
name|dock
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|dock
argument_list|,
name|gimp_dock_columns_dock_book_removed
argument_list|,
name|dock_columns
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|dock
argument_list|)
expr_stmt|;
name|gimp_paned_box_remove_widget
argument_list|(
name|GIMP_PANED_BOX
argument_list|(
name|dock_columns
operator|->
name|p
operator|->
name|paned_hbox
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|dock_columns
argument_list|,
name|dock_columns_signals
index|[
name|DOCK_REMOVED
index|]
argument_list|,
literal|0
argument_list|,
name|dock
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dock
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_dock_columns_get_docks (GimpDockColumns * dock_columns)
name|gimp_dock_columns_get_docks
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK_COLUMNS
argument_list|(
name|dock_columns
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dock_columns
operator|->
name|p
operator|->
name|docks
return|;
block|}
end_function

begin_function
name|GimpContext
modifier|*
DECL|function|gimp_dock_columns_get_context (GimpDockColumns * dock_columns)
name|gimp_dock_columns_get_context
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK_COLUMNS
argument_list|(
name|dock_columns
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dock_columns
operator|->
name|p
operator|->
name|context
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dock_columns_set_context (GimpDockColumns * dock_columns,GimpContext * context)
name|gimp_dock_columns_set_context
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK_COLUMNS
argument_list|(
name|dock_columns
argument_list|)
argument_list|)
expr_stmt|;
name|dock_columns
operator|->
name|p
operator|->
name|context
operator|=
name|context
expr_stmt|;
block|}
end_function

begin_function
name|GimpDialogFactory
modifier|*
DECL|function|gimp_dock_columns_get_dialog_factory (GimpDockColumns * dock_columns)
name|gimp_dock_columns_get_dialog_factory
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK_COLUMNS
argument_list|(
name|dock_columns
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dock_columns
operator|->
name|p
operator|->
name|dialog_factory
return|;
block|}
end_function

begin_function
name|GimpUIManager
modifier|*
DECL|function|gimp_dock_columns_get_ui_manager (GimpDockColumns * dock_columns)
name|gimp_dock_columns_get_ui_manager
parameter_list|(
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK_COLUMNS
argument_list|(
name|dock_columns
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dock_columns
operator|->
name|p
operator|->
name|ui_manager
return|;
block|}
end_function

end_unit

