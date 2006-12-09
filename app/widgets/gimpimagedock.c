begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimagedock.c  * Copyright (C) 2001-2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
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
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagedock.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_image_dock_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_dock_destroy
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
name|gimp_image_dock_display_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|,
name|GimpImageDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_dock_image_flush
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImageDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_dock_notify_transient
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpImageDock,gimp_image_dock,GIMP_TYPE_DOCK)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpImageDock
argument_list|,
argument|gimp_image_dock
argument_list|,
argument|GIMP_TYPE_DOCK
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_image_dock_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_image_dock_class_init
parameter_list|(
name|GimpImageDockClass
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
name|object_class
operator|->
name|constructor
operator|=
name|gimp_image_dock_constructor
expr_stmt|;
name|gtk_object_class
operator|->
name|destroy
operator|=
name|gimp_image_dock_destroy
expr_stmt|;
name|klass
operator|->
name|ui_manager_name
operator|=
literal|"<Dock>"
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_dock_init (GimpImageDock * dock)
name|gimp_image_dock_init
parameter_list|(
name|GimpImageDock
modifier|*
name|dock
parameter_list|)
block|{
name|dock
operator|->
name|ui_manager
operator|=
name|NULL
expr_stmt|;
name|dock
operator|->
name|image_flush_handler_id
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_image_dock_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_image_dock_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpImageDock
modifier|*
name|dock
decl_stmt|;
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
name|GtkAccelGroup
modifier|*
name|accel_group
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|dock
operator|=
name|GIMP_IMAGE_DOCK
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
operator|->
name|context
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|dock
operator|->
name|ui_manager
operator|=
name|gimp_menu_factory_manager_new
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
operator|->
name|dialog_factory
operator|->
name|menu_factory
argument_list|,
name|GIMP_IMAGE_DOCK_GET_CLASS
argument_list|(
name|dock
argument_list|)
operator|->
name|ui_manager_name
argument_list|,
name|dock
argument_list|,
name|config
operator|->
name|tearoff_menus
argument_list|)
expr_stmt|;
name|accel_group
operator|=
name|gtk_ui_manager_get_accel_group
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|dock
operator|->
name|ui_manager
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_add_accel_group
argument_list|(
name|GTK_WINDOW
argument_list|(
name|object
argument_list|)
argument_list|,
name|accel_group
argument_list|)
expr_stmt|;
name|dock
operator|->
name|image_flush_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
operator|->
name|context
operator|->
name|gimp
operator|->
name|images
argument_list|,
literal|"flush"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_dock_image_flush
argument_list|)
argument_list|,
name|dock
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
operator|->
name|context
argument_list|,
literal|"display-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_dock_display_changed
argument_list|)
argument_list|,
name|dock
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
operator|->
name|context
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::transient-docks"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_dock_notify_transient
argument_list|)
argument_list|,
name|dock
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_dock_destroy (GtkObject * object)
name|gimp_image_dock_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpImageDock
modifier|*
name|dock
init|=
name|GIMP_IMAGE_DOCK
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|dock
operator|->
name|image_flush_handler_id
condition|)
block|{
name|gimp_container_remove_handler
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
operator|->
name|context
operator|->
name|gimp
operator|->
name|images
argument_list|,
name|dock
operator|->
name|image_flush_handler_id
argument_list|)
expr_stmt|;
name|dock
operator|->
name|image_flush_handler_id
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|dock
operator|->
name|ui_manager
condition|)
block|{
name|g_object_unref
argument_list|(
name|dock
operator|->
name|ui_manager
argument_list|)
expr_stmt|;
name|dock
operator|->
name|ui_manager
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
DECL|function|gimp_image_dock_display_changed (GimpContext * context,GimpObject * display,GimpImageDock * dock)
name|gimp_image_dock_display_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|,
name|GimpImageDock
modifier|*
name|dock
parameter_list|)
block|{
name|gimp_ui_manager_update
argument_list|(
name|dock
operator|->
name|ui_manager
argument_list|,
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_GUI_CONFIG
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|transient_docks
condition|)
block|{
name|GtkWindow
modifier|*
name|parent
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|display
condition|)
name|g_object_get
argument_list|(
name|display
argument_list|,
literal|"shell"
argument_list|,
operator|&
name|parent
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock
argument_list|)
argument_list|,
name|parent
argument_list|)
expr_stmt|;
if|if
condition|(
name|parent
condition|)
name|g_object_unref
argument_list|(
name|parent
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_dock_image_flush (GimpImage * image,GimpImageDock * dock)
name|gimp_image_dock_image_flush
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImageDock
modifier|*
name|dock
parameter_list|)
block|{
if|if
condition|(
name|image
operator|==
name|gimp_context_get_image
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
operator|->
name|context
argument_list|)
condition|)
block|{
name|GimpObject
modifier|*
name|display
init|=
name|gimp_context_get_display
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
operator|->
name|context
argument_list|)
decl_stmt|;
if|if
condition|(
name|display
condition|)
name|gimp_ui_manager_update
argument_list|(
name|dock
operator|->
name|ui_manager
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_dock_notify_transient (GimpConfig * config,GParamSpec * pspec,GimpDock * dock)
name|gimp_image_dock_notify_transient
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
if|if
condition|(
name|GIMP_GUI_CONFIG
argument_list|(
name|config
argument_list|)
operator|->
name|transient_docks
condition|)
block|{
name|gimp_image_dock_display_changed
argument_list|(
name|dock
operator|->
name|context
argument_list|,
name|gimp_context_get_display
argument_list|(
name|dock
operator|->
name|context
argument_list|)
argument_list|,
name|GIMP_IMAGE_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

