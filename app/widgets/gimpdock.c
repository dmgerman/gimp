begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdock.c  * Copyright (C) 2001-2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpdockseparator.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c0c9fcf0103
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
DECL|enum|__anon2c0c9fcf0203
block|{
DECL|enumerator|BOOK_ADDED
name|BOOK_ADDED
block|,
DECL|enumerator|BOOK_REMOVED
name|BOOK_REMOVED
block|,
DECL|enumerator|TITLE_INVALIDATED
name|TITLE_INVALIDATED
block|,
DECL|enumerator|GEOMETRY_INVALIDATED
name|GEOMETRY_INVALIDATED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpDockPrivate
struct|struct
name|_GimpDockPrivate
block|{
DECL|member|dialog_factory
name|GimpDialogFactory
modifier|*
name|dialog_factory
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|ui_manager
name|GimpUIManager
modifier|*
name|ui_manager
decl_stmt|;
DECL|member|main_vbox
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
DECL|member|vbox
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
DECL|member|dockbooks
name|GList
modifier|*
name|dockbooks
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_dock_set_property
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
name|gimp_dock_get_property
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
name|void
name|gimp_dock_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dock_real_book_added
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dock_real_book_removed
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDock
argument_list|,
argument|gimp_dock
argument_list|,
argument|GIMP_TYPE_DOCK_WINDOW
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dock_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|dock_signals
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
DECL|function|gimp_dock_class_init (GimpDockClass * klass)
name|gimp_dock_class_init
parameter_list|(
name|GimpDockClass
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
name|GtkObjectClass
modifier|*
name|gtk_object_class
init|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|dock_signals
index|[
name|BOOK_ADDED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"book-added"
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
name|GimpDockClass
argument_list|,
name|book_added
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
name|GIMP_TYPE_DOCKBOOK
argument_list|)
expr_stmt|;
name|dock_signals
index|[
name|BOOK_REMOVED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"book-removed"
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
name|GimpDockClass
argument_list|,
name|book_removed
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
name|GIMP_TYPE_DOCKBOOK
argument_list|)
expr_stmt|;
name|dock_signals
index|[
name|TITLE_INVALIDATED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"title-invalidated"
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
name|GimpDockClass
argument_list|,
name|title_invalidated
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|dock_signals
index|[
name|GEOMETRY_INVALIDATED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"geometry-invalidated"
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
name|GimpDockClass
argument_list|,
name|geometry_invalidated
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_dock_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_dock_get_property
expr_stmt|;
name|gtk_object_class
operator|->
name|destroy
operator|=
name|gimp_dock_destroy
expr_stmt|;
name|klass
operator|->
name|setup
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|set_host_geometry_hints
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|book_added
operator|=
name|gimp_dock_real_book_added
expr_stmt|;
name|klass
operator|->
name|book_removed
operator|=
name|gimp_dock_real_book_removed
expr_stmt|;
name|klass
operator|->
name|title_invalidated
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|geometry_invalidated
operator|=
name|NULL
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
name|GIMP_PARAM_READWRITE
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
name|GIMP_PARAM_READWRITE
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
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpDockPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_init (GimpDock * dock)
name|gimp_dock_init
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|separator
decl_stmt|;
name|dock
operator|->
name|p
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|dock
argument_list|,
name|GIMP_TYPE_DOCK
argument_list|,
name|GimpDockPrivate
argument_list|)
expr_stmt|;
name|dock
operator|->
name|p
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
name|dock
operator|->
name|p
operator|->
name|dialog_factory
operator|=
name|NULL
expr_stmt|;
name|dock
operator|->
name|p
operator|->
name|dockbooks
operator|=
name|NULL
expr_stmt|;
name|dock
operator|->
name|p
operator|->
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dock
argument_list|)
argument_list|,
name|dock
operator|->
name|p
operator|->
name|main_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dock
operator|->
name|p
operator|->
name|main_vbox
argument_list|)
expr_stmt|;
name|dock
operator|->
name|p
operator|->
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dock
operator|->
name|p
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|dock
operator|->
name|p
operator|->
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dock
operator|->
name|p
operator|->
name|vbox
argument_list|)
expr_stmt|;
name|separator
operator|=
name|gimp_dock_separator_new
argument_list|(
name|dock
argument_list|,
name|GTK_ANCHOR_NORTH
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dock
operator|->
name|p
operator|->
name|vbox
argument_list|)
argument_list|,
name|separator
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|separator
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_dock_set_property
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
name|GimpDock
modifier|*
name|dock
init|=
name|GIMP_DOCK
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
name|dock
operator|->
name|p
operator|->
name|context
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DIALOG_FACTORY
case|:
name|dock
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
break|break;
case|case
name|PROP_UI_MANAGER
case|:
name|dock
operator|->
name|p
operator|->
name|ui_manager
operator|=
name|g_value_dup_object
argument_list|(
name|value
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
DECL|function|gimp_dock_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_dock_get_property
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
name|GimpDock
modifier|*
name|dock
init|=
name|GIMP_DOCK
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
name|dock
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
name|dock
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
name|dock
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
DECL|function|gimp_dock_destroy (GtkObject * object)
name|gimp_dock_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDock
modifier|*
name|dock
init|=
name|GIMP_DOCK
argument_list|(
name|object
argument_list|)
decl_stmt|;
while|while
condition|(
name|dock
operator|->
name|p
operator|->
name|dockbooks
condition|)
name|gimp_dock_remove_book
argument_list|(
name|dock
argument_list|,
name|GIMP_DOCKBOOK
argument_list|(
name|dock
operator|->
name|p
operator|->
name|dockbooks
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dock
operator|->
name|p
operator|->
name|ui_manager
condition|)
block|{
name|g_object_unref
argument_list|(
name|dock
operator|->
name|p
operator|->
name|ui_manager
argument_list|)
expr_stmt|;
name|dock
operator|->
name|p
operator|->
name|ui_manager
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|dock
operator|->
name|p
operator|->
name|context
condition|)
block|{
name|g_object_unref
argument_list|(
name|dock
operator|->
name|p
operator|->
name|context
argument_list|)
expr_stmt|;
name|dock
operator|->
name|p
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
block|}
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_real_book_added (GimpDock * dock,GimpDockbook * dockbook)
name|gimp_dock_real_book_added
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_real_book_removed (GimpDock * dock,GimpDockbook * dockbook)
name|gimp_dock_real_book_removed
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
block|{
if|if
condition|(
name|dock
operator|->
name|p
operator|->
name|dockbooks
operator|==
name|NULL
condition|)
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_dock_setup (GimpDock * dock,const GimpDock * template)
name|gimp_dock_setup
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
specifier|const
name|GimpDock
modifier|*
name|template
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_DOCK_GET_CLASS
argument_list|(
name|dock
argument_list|)
operator|->
name|setup
condition|)
name|GIMP_DOCK_GET_CLASS
argument_list|(
name|dock
argument_list|)
operator|->
name|setup
argument_list|(
name|dock
argument_list|,
name|template
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dock_set_aux_info (GimpDock * dock,GList * aux_info)
name|gimp_dock_set_aux_info
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GList
modifier|*
name|aux_info
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
name|GIMP_DOCK_GET_CLASS
argument_list|(
name|dock
argument_list|)
operator|->
name|set_aux_info
condition|)
name|GIMP_DOCK_GET_CLASS
argument_list|(
name|dock
argument_list|)
operator|->
name|set_aux_info
argument_list|(
name|dock
argument_list|,
name|aux_info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_dock_get_aux_info (GimpDock * dock)
name|gimp_dock_get_aux_info
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_DOCK_GET_CLASS
argument_list|(
name|dock
argument_list|)
operator|->
name|get_aux_info
condition|)
return|return
name|GIMP_DOCK_GET_CLASS
argument_list|(
name|dock
argument_list|)
operator|->
name|get_aux_info
argument_list|(
name|dock
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_dock_get_title (GimpDock * dock)
name|gimp_dock_get_title
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_DOCK_GET_CLASS
argument_list|(
name|dock
argument_list|)
operator|->
name|get_title
condition|)
return|return
name|GIMP_DOCK_GET_CLASS
argument_list|(
name|dock
argument_list|)
operator|->
name|get_title
argument_list|(
name|dock
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dock_invalidate_title (GimpDock * dock)
name|gimp_dock_invalidate_title
parameter_list|(
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
name|g_signal_emit
argument_list|(
name|dock
argument_list|,
name|dock_signals
index|[
name|TITLE_INVALIDATED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_dock_set_host_geometry_hints:  * @dock:   The dock  * @window: The #GtkWindow to adapt to hosting the dock  *  * Some docks have some specific needs on the #GtkWindow they are  * in. This function allows such docks to perform any such setup on  * the #GtkWindow they are in/will be put in.  **/
end_comment

begin_function
name|void
DECL|function|gimp_dock_set_host_geometry_hints (GimpDock * dock,GtkWindow * window)
name|gimp_dock_set_host_geometry_hints
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GtkWindow
modifier|*
name|window
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
name|g_return_if_fail
argument_list|(
name|GTK_IS_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_DOCK_GET_CLASS
argument_list|(
name|dock
argument_list|)
operator|->
name|set_host_geometry_hints
condition|)
name|GIMP_DOCK_GET_CLASS
argument_list|(
name|dock
argument_list|)
operator|->
name|set_host_geometry_hints
argument_list|(
name|dock
argument_list|,
name|window
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_dock_invalidate_geometry:  * @dock:  *  * Call when the dock needs to setup its host #GtkWindow with  * GtkDock::set_host_geometry_hints().  **/
end_comment

begin_function
name|void
DECL|function|gimp_dock_invalidate_geometry (GimpDock * dock)
name|gimp_dock_invalidate_geometry
parameter_list|(
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
name|g_signal_emit
argument_list|(
name|dock
argument_list|,
name|dock_signals
index|[
name|GEOMETRY_INVALIDATED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpContext
modifier|*
DECL|function|gimp_dock_get_context (GimpDock * dock)
name|gimp_dock_get_context
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dock
operator|->
name|p
operator|->
name|context
return|;
block|}
end_function

begin_function
name|GimpDialogFactory
modifier|*
DECL|function|gimp_dock_get_dialog_factory (GimpDock * dock)
name|gimp_dock_get_dialog_factory
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dock
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
DECL|function|gimp_dock_get_ui_manager (GimpDock * dock)
name|gimp_dock_get_ui_manager
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dock
operator|->
name|p
operator|->
name|ui_manager
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_dock_get_dockbooks (GimpDock * dock)
name|gimp_dock_get_dockbooks
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dock
operator|->
name|p
operator|->
name|dockbooks
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_dock_get_n_dockables (GimpDock * dock)
name|gimp_dock_get_n_dockables
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|gint
name|n
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|dock
operator|->
name|p
operator|->
name|dockbooks
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
name|n
operator|+=
name|gtk_notebook_get_n_pages
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|n
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dock_get_main_vbox (GimpDock * dock)
name|gimp_dock_get_main_vbox
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dock
operator|->
name|p
operator|->
name|main_vbox
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dock_get_vbox (GimpDock * dock)
name|gimp_dock_get_vbox
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dock
operator|->
name|p
operator|->
name|vbox
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dock_add (GimpDock * dock,GimpDockable * dockable,gint section,gint position)
name|gimp_dock_add
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|gint
name|section
parameter_list|,
name|gint
name|position
parameter_list|)
block|{
name|GimpDockbook
modifier|*
name|dockbook
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
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
name|NULL
argument_list|)
expr_stmt|;
name|dockbook
operator|=
name|GIMP_DOCKBOOK
argument_list|(
name|dock
operator|->
name|p
operator|->
name|dockbooks
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_dockbook_add
argument_list|(
name|dockbook
argument_list|,
name|dockable
argument_list|,
name|position
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dock_remove (GimpDock * dock,GimpDockable * dockable)
name|gimp_dock_remove
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockable
modifier|*
name|dockable
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
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_dockbook_get_dock
argument_list|(
name|dockable
operator|->
name|dockbook
argument_list|)
operator|==
name|dock
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
block|}
end_function

begin_function
name|void
DECL|function|gimp_dock_add_book (GimpDock * dock,GimpDockbook * dockbook,gint index)
name|gimp_dock_add_book
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|gint
name|old_length
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
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
name|gimp_dockbook_get_dock
argument_list|(
name|dockbook
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|old_length
operator|=
name|g_list_length
argument_list|(
name|dock
operator|->
name|p
operator|->
name|dockbooks
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|>=
name|old_length
operator|||
name|index
operator|<
literal|0
condition|)
name|index
operator|=
name|old_length
expr_stmt|;
name|gimp_dockbook_set_dock
argument_list|(
name|dockbook
argument_list|,
name|dock
argument_list|)
expr_stmt|;
name|dock
operator|->
name|p
operator|->
name|dockbooks
operator|=
name|g_list_insert
argument_list|(
name|dock
operator|->
name|p
operator|->
name|dockbooks
argument_list|,
name|dockbook
argument_list|,
name|index
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_length
operator|==
literal|0
condition|)
block|{
name|GtkWidget
modifier|*
name|separator
decl_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dock
operator|->
name|p
operator|->
name|vbox
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|separator
operator|=
name|gimp_dock_separator_new
argument_list|(
name|dock
argument_list|,
name|GTK_ANCHOR_SOUTH
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|dock
operator|->
name|p
operator|->
name|vbox
argument_list|)
argument_list|,
name|separator
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|separator
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|old_book
decl_stmt|;
name|GtkWidget
modifier|*
name|parent
decl_stmt|;
name|GtkWidget
modifier|*
name|paned
decl_stmt|;
if|if
condition|(
name|index
operator|==
literal|0
condition|)
name|old_book
operator|=
name|g_list_nth_data
argument_list|(
name|dock
operator|->
name|p
operator|->
name|dockbooks
argument_list|,
name|index
operator|+
literal|1
argument_list|)
expr_stmt|;
else|else
name|old_book
operator|=
name|g_list_nth_data
argument_list|(
name|dock
operator|->
name|p
operator|->
name|dockbooks
argument_list|,
name|index
operator|-
literal|1
argument_list|)
expr_stmt|;
name|parent
operator|=
name|gtk_widget_get_parent
argument_list|(
name|old_book
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|old_length
operator|>
literal|1
operator|)
operator|&&
operator|(
name|index
operator|>
literal|0
operator|)
condition|)
block|{
name|GtkWidget
modifier|*
name|grandparent
decl_stmt|;
name|grandparent
operator|=
name|gtk_widget_get_parent
argument_list|(
name|parent
argument_list|)
expr_stmt|;
name|old_book
operator|=
name|parent
expr_stmt|;
name|parent
operator|=
name|grandparent
expr_stmt|;
block|}
name|g_object_ref
argument_list|(
name|old_book
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|parent
argument_list|)
argument_list|,
name|old_book
argument_list|)
expr_stmt|;
name|paned
operator|=
name|gtk_vpaned_new
argument_list|()
expr_stmt|;
if|if
condition|(
name|GTK_IS_VPANED
argument_list|(
name|parent
argument_list|)
condition|)
name|gtk_paned_pack1
argument_list|(
name|GTK_PANED
argument_list|(
name|parent
argument_list|)
argument_list|,
name|paned
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
else|else
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|parent
argument_list|)
argument_list|,
name|paned
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
name|paned
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|==
literal|0
condition|)
block|{
name|gtk_paned_pack1
argument_list|(
name|GTK_PANED
argument_list|(
name|paned
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_paned_pack2
argument_list|(
name|GTK_PANED
argument_list|(
name|paned
argument_list|)
argument_list|,
name|old_book
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_paned_pack1
argument_list|(
name|GTK_PANED
argument_list|(
name|paned
argument_list|)
argument_list|,
name|old_book
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_paned_pack2
argument_list|(
name|GTK_PANED
argument_list|(
name|paned
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|old_book
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|dock
argument_list|,
name|dock_signals
index|[
name|BOOK_ADDED
index|]
argument_list|,
literal|0
argument_list|,
name|dockbook
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dock_remove_book (GimpDock * dock,GimpDockbook * dockbook)
name|gimp_dock_remove_book
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
block|{
name|gint
name|old_length
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
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
name|gimp_dockbook_get_dock
argument_list|(
name|dockbook
argument_list|)
operator|==
name|dock
argument_list|)
expr_stmt|;
name|old_length
operator|=
name|g_list_length
argument_list|(
name|dock
operator|->
name|p
operator|->
name|dockbooks
argument_list|)
expr_stmt|;
name|index
operator|=
name|g_list_index
argument_list|(
name|dock
operator|->
name|p
operator|->
name|dockbooks
argument_list|,
name|dockbook
argument_list|)
expr_stmt|;
name|gimp_dockbook_set_dock
argument_list|(
name|dockbook
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dock
operator|->
name|p
operator|->
name|dockbooks
operator|=
name|g_list_remove
argument_list|(
name|dock
operator|->
name|p
operator|->
name|dockbooks
argument_list|,
name|dockbook
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|dockbook
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_length
operator|==
literal|1
condition|)
block|{
name|GtkWidget
modifier|*
name|separator
decl_stmt|;
name|GList
modifier|*
name|children
decl_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dock
operator|->
name|p
operator|->
name|vbox
argument_list|)
argument_list|)
expr_stmt|;
name|separator
operator|=
name|g_list_nth_data
argument_list|(
name|children
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dock
operator|->
name|p
operator|->
name|vbox
argument_list|)
argument_list|,
name|separator
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dock
operator|->
name|p
operator|->
name|vbox
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|other_book
decl_stmt|;
name|GtkWidget
modifier|*
name|parent
decl_stmt|;
name|GtkWidget
modifier|*
name|grandparent
decl_stmt|;
name|parent
operator|=
name|gtk_widget_get_parent
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|grandparent
operator|=
name|gtk_widget_get_parent
argument_list|(
name|parent
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|==
literal|0
condition|)
name|other_book
operator|=
name|gtk_paned_get_child2
argument_list|(
name|GTK_PANED
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|other_book
operator|=
name|gtk_paned_get_child1
argument_list|(
name|GTK_PANED
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|other_book
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|parent
argument_list|)
argument_list|,
name|other_book
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|parent
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|grandparent
argument_list|)
argument_list|,
name|parent
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_VPANED
argument_list|(
name|grandparent
argument_list|)
condition|)
name|gtk_paned_pack1
argument_list|(
name|GTK_PANED
argument_list|(
name|grandparent
argument_list|)
argument_list|,
name|other_book
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
else|else
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dock
operator|->
name|p
operator|->
name|vbox
argument_list|)
argument_list|,
name|other_book
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|other_book
argument_list|)
expr_stmt|;
block|}
name|g_signal_emit
argument_list|(
name|dock
argument_list|,
name|dock_signals
index|[
name|BOOK_REMOVED
index|]
argument_list|,
literal|0
argument_list|,
name|dockbook
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dockbook
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

