begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockwindow.c  * Copyright (C) 2001-2005 Michael Natterer<mitch@gimp.org>  * Copyright (C)      2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"dialogs/dialogs.h"
end_include

begin_comment
comment|/* FIXME, we are in the widget layer */
end_comment

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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
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
file|"gimpdockbook.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockwindow.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo.h"
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
file|"gimpwindow.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|DEFAULT_DOCK_HEIGHT
define|#
directive|define
name|DEFAULT_DOCK_HEIGHT
value|300
end_define

begin_define
DECL|macro|DEFAULT_DOCK_FONT_SCALE
define|#
directive|define
name|DEFAULT_DOCK_FONT_SCALE
value|PANGO_SCALE_SMALL
end_define

begin_enum
enum|enum
DECL|enum|__anon29dc40d30103
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
DECL|enumerator|PROP_UI_MANAGER_NAME
name|PROP_UI_MANAGER_NAME
block|, }
enum|;
end_enum

begin_struct
DECL|struct|_GimpDockWindowPrivate
struct|struct
name|_GimpDockWindowPrivate
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
DECL|member|ui_manager_name
name|gchar
modifier|*
name|ui_manager_name
decl_stmt|;
DECL|member|ui_manager
name|GimpUIManager
modifier|*
name|ui_manager
decl_stmt|;
DECL|member|image_flush_handler_id
name|GQuark
name|image_flush_handler_id
decl_stmt|;
DECL|member|update_title_idle_id
name|guint
name|update_title_idle_id
decl_stmt|;
DECL|member|ID
name|gint
name|ID
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_dock_window_constructor
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
name|gimp_dock_window_dispose
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
name|gimp_dock_window_set_property
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
name|gimp_dock_window_get_property
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
name|gimp_dock_window_style_set
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
name|gimp_dock_window_delete_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventAny
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dock_window_display_changed
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dock_window_image_changed
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dock_window_image_flush
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|invalidate_preview
parameter_list|,
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dock_window_update_title
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dock_window_update_title_idle
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dock_window_dock_book_removed
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
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
DECL|function|G_DEFINE_TYPE (GimpDockWindow,gimp_dock_window,GIMP_TYPE_WINDOW)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDockWindow
argument_list|,
argument|gimp_dock_window
argument_list|,
argument|GIMP_TYPE_WINDOW
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dock_window_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_dock_window_class_init
parameter_list|(
name|GimpDockWindowClass
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
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_dock_window_constructor
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_dock_window_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_dock_window_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_dock_window_get_property
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_dock_window_style_set
expr_stmt|;
name|widget_class
operator|->
name|delete_event
operator|=
name|gimp_dock_window_delete_event
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTEXT
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"gimp-context"
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
literal|"gimp-dialog-factory"
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
name|PROP_UI_MANAGER_NAME
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"ui-manager-name"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"default-height"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1
argument_list|,
name|G_MAXINT
argument_list|,
name|DEFAULT_DOCK_HEIGHT
argument_list|,
name|GIMP_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"font-scale"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
name|G_MAXDOUBLE
argument_list|,
name|DEFAULT_DOCK_FONT_SCALE
argument_list|,
name|GIMP_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpDockWindowPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_window_init (GimpDockWindow * dock_window)
name|gimp_dock_window_init
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
block|{
specifier|static
name|gint
name|dock_ID
init|=
literal|1
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/* Initialize members */
name|dock_window
operator|->
name|p
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|dock_window
argument_list|,
name|GIMP_TYPE_DOCK_WINDOW
argument_list|,
name|GimpDockWindowPrivate
argument_list|)
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|dialog_factory
operator|=
name|NULL
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|ui_manager_name
operator|=
name|NULL
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|ui_manager
operator|=
name|NULL
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|image_flush_handler_id
operator|=
literal|0
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|ID
operator|=
name|dock_ID
operator|++
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|update_title_idle_id
operator|=
literal|0
expr_stmt|;
comment|/* Some common initialization for all dock windows */
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_window_set_focus_on_map
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* Initialize theming and style-setting stuff */
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"gimp-dock-%d"
argument_list|,
name|dock_window
operator|->
name|p
operator|->
name|ID
argument_list|)
expr_stmt|;
name|gtk_widget_set_name
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock_window
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_dock_window_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_dock_window_constructor
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
name|GimpDockWindow
modifier|*
name|dock_window
decl_stmt|;
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
name|GtkAccelGroup
modifier|*
name|accel_group
decl_stmt|;
name|GimpDock
modifier|*
name|dock
decl_stmt|;
comment|/* Init */
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
name|dock_window
operator|=
name|GIMP_DOCK_WINDOW
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|dock_window
operator|->
name|p
operator|->
name|context
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
comment|/* Setup hints */
name|gimp_window_set_hint
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|,
name|config
operator|->
name|dock_window_hint
argument_list|)
expr_stmt|;
comment|/* Make image window related keyboard shortcuts work also when a    * dock window is the focused window    */
name|dock_window
operator|->
name|p
operator|->
name|ui_manager
operator|=
name|gimp_menu_factory_manager_new
argument_list|(
name|dock_window
operator|->
name|p
operator|->
name|dialog_factory
operator|->
name|menu_factory
argument_list|,
name|dock_window
operator|->
name|p
operator|->
name|ui_manager_name
argument_list|,
name|dock_window
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
name|dock_window
operator|->
name|p
operator|->
name|ui_manager
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_add_accel_group
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|,
name|accel_group
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|dock_window
operator|->
name|p
operator|->
name|context
argument_list|,
literal|"display-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dock_window_display_changed
argument_list|)
argument_list|,
name|dock_window
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|dock_window
operator|->
name|p
operator|->
name|context
argument_list|,
literal|"image-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dock_window_image_changed
argument_list|)
argument_list|,
name|dock_window
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|image_flush_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|dock_window
operator|->
name|p
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
name|gimp_dock_window_image_flush
argument_list|)
argument_list|,
name|dock_window
argument_list|)
expr_stmt|;
comment|/* Update window title now and when docks title is invalidated */
name|gimp_dock_window_update_title
argument_list|(
name|dock_window
argument_list|)
expr_stmt|;
name|dock
operator|=
name|gimp_dock_window_get_dock
argument_list|(
name|dock_window
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|dock
argument_list|,
literal|"title-invalidated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dock_window_update_title
argument_list|)
argument_list|,
name|dock_window
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
comment|/* Some docks like the toolbox dock needs to maintain special hints    * on its container GtkWindow, allow those to do so    */
name|gimp_dock_set_host_geometry_hints
argument_list|(
name|dock
argument_list|,
name|GTK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|dock
argument_list|,
literal|"geometry-invalidated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dock_set_host_geometry_hints
argument_list|)
argument_list|,
name|dock_window
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* Destroy the dock window when the last book is removed */
name|g_signal_connect_object
argument_list|(
name|dock
argument_list|,
literal|"book-removed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dock_window_dock_book_removed
argument_list|)
argument_list|,
name|dock_window
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
comment|/* Done! */
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_window_dispose (GObject * object)
name|gimp_dock_window_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDockWindow
modifier|*
name|dock_window
init|=
name|GIMP_DOCK_WINDOW
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|dock_window
operator|->
name|p
operator|->
name|update_title_idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|dock_window
operator|->
name|p
operator|->
name|update_title_idle_id
argument_list|)
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|update_title_idle_id
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|dock_window
operator|->
name|p
operator|->
name|image_flush_handler_id
condition|)
block|{
name|gimp_container_remove_handler
argument_list|(
name|dock_window
operator|->
name|p
operator|->
name|context
operator|->
name|gimp
operator|->
name|images
argument_list|,
name|dock_window
operator|->
name|p
operator|->
name|image_flush_handler_id
argument_list|)
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|image_flush_handler_id
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|dock_window
operator|->
name|p
operator|->
name|ui_manager
condition|)
block|{
name|g_object_unref
argument_list|(
name|dock_window
operator|->
name|p
operator|->
name|ui_manager
argument_list|)
expr_stmt|;
name|dock_window
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
name|dock_window
operator|->
name|p
operator|->
name|dialog_factory
condition|)
block|{
name|g_object_unref
argument_list|(
name|dock_window
operator|->
name|p
operator|->
name|dialog_factory
argument_list|)
expr_stmt|;
name|dock_window
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
name|dock_window
operator|->
name|p
operator|->
name|context
condition|)
block|{
name|g_object_unref
argument_list|(
name|dock_window
operator|->
name|p
operator|->
name|context
argument_list|)
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|context
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
DECL|function|gimp_dock_window_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_dock_window_set_property
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
name|GimpDockWindow
modifier|*
name|dock_window
init|=
name|GIMP_DOCK_WINDOW
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
name|dock_window
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
name|dock_window
operator|->
name|p
operator|->
name|dialog_factory
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UI_MANAGER_NAME
case|:
name|g_free
argument_list|(
name|dock_window
operator|->
name|p
operator|->
name|ui_manager_name
argument_list|)
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|ui_manager_name
operator|=
name|g_value_dup_string
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
DECL|function|gimp_dock_window_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_dock_window_get_property
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
name|GimpDockWindow
modifier|*
name|dock_window
init|=
name|GIMP_DOCK_WINDOW
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
name|dock_window
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
name|dock_window
operator|->
name|p
operator|->
name|dialog_factory
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UI_MANAGER_NAME
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|dock_window
operator|->
name|p
operator|->
name|ui_manager_name
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
DECL|function|gimp_dock_window_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_dock_window_style_set
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
name|GimpDockWindow
modifier|*
name|dock_window
init|=
name|GIMP_DOCK_WINDOW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|default_height
decl_stmt|;
name|gdouble
name|font_scale
decl_stmt|;
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
literal|"default-height"
argument_list|,
operator|&
name|default_height
argument_list|,
literal|"font-scale"
argument_list|,
operator|&
name|font_scale
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_window_set_default_size
argument_list|(
name|GTK_WINDOW
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|default_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|font_scale
operator|!=
literal|1.0
condition|)
block|{
name|PangoContext
modifier|*
name|context
decl_stmt|;
name|PangoFontDescription
modifier|*
name|font_desc
decl_stmt|;
name|gint
name|font_size
decl_stmt|;
name|gchar
modifier|*
name|font_str
decl_stmt|;
name|gchar
modifier|*
name|rc_string
decl_stmt|;
name|context
operator|=
name|gtk_widget_get_pango_context
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|font_desc
operator|=
name|pango_context_get_font_description
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|font_desc
operator|=
name|pango_font_description_copy
argument_list|(
name|font_desc
argument_list|)
expr_stmt|;
name|font_size
operator|=
name|pango_font_description_get_size
argument_list|(
name|font_desc
argument_list|)
expr_stmt|;
name|font_size
operator|=
name|font_scale
operator|*
name|font_size
expr_stmt|;
name|pango_font_description_set_size
argument_list|(
name|font_desc
argument_list|,
name|font_size
argument_list|)
expr_stmt|;
name|font_str
operator|=
name|pango_font_description_to_string
argument_list|(
name|font_desc
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|font_desc
argument_list|)
expr_stmt|;
name|rc_string
operator|=
name|g_strdup_printf
argument_list|(
literal|"style \"gimp-dock-style\""
literal|"{"
literal|"  font_name = \"%s\""
literal|"}"
literal|"widget \"gimp-dock-%d.*\" style \"gimp-dock-style\""
argument_list|,
name|font_str
argument_list|,
name|dock_window
operator|->
name|p
operator|->
name|ID
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|font_str
argument_list|)
expr_stmt|;
name|gtk_rc_parse_string
argument_list|(
name|rc_string
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rc_string
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
argument_list|)
condition|)
name|gtk_widget_reset_rc_styles
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_dock_window_delete_event:  * @widget:  * @event:  *  * Makes sure that when dock windows are closed they are added to the  * list of recently closed docks so that they are easy to bring back.  **/
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dock_window_delete_event (GtkWidget * widget,GdkEventAny * event)
name|gimp_dock_window_delete_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventAny
modifier|*
name|event
parameter_list|)
block|{
name|GimpDockWindow
modifier|*
name|dock_window
init|=
name|GIMP_DOCK_WINDOW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpDock
modifier|*
name|dock
init|=
name|gimp_dock_window_get_dock
argument_list|(
name|dock_window
argument_list|)
decl_stmt|;
name|GimpSessionInfo
modifier|*
name|info
init|=
name|NULL
decl_stmt|;
comment|/* Don't add docks with just a singe dockable to the list of    * recently closed dock since those can be brought back through the    * normal Windows->Dockable Dialogs menu    */
if|if
condition|(
name|gimp_dock_get_n_dockables
argument_list|(
name|dock
argument_list|)
operator|<
literal|2
condition|)
return|return
name|FALSE
return|;
name|info
operator|=
name|gimp_session_info_new
argument_list|()
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|info
argument_list|)
argument_list|,
name|gtk_window_get_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_session_info_set_widget
argument_list|(
name|info
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_session_info_get_info
argument_list|(
name|info
argument_list|)
expr_stmt|;
name|gimp_session_info_set_widget
argument_list|(
name|info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|global_recent_docks
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_window_display_changed (GimpDockWindow * dock_window,GimpObject * display,GimpContext * context)
name|gimp_dock_window_display_changed
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|gimp_ui_manager_update
argument_list|(
name|dock_window
operator|->
name|p
operator|->
name|ui_manager
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_window_image_changed (GimpDockWindow * dock_window,GimpImage * image,GimpContext * context)
name|gimp_dock_window_image_changed
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|gimp_ui_manager_update
argument_list|(
name|dock_window
operator|->
name|p
operator|->
name|ui_manager
argument_list|,
name|gimp_context_get_display
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_window_image_flush (GimpImage * image,gboolean invalidate_preview,GimpDockWindow * dock_window)
name|gimp_dock_window_image_flush
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|invalidate_preview
parameter_list|,
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
block|{
if|if
condition|(
name|image
operator|==
name|gimp_context_get_image
argument_list|(
name|dock_window
operator|->
name|p
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
name|dock_window
operator|->
name|p
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
name|dock_window
operator|->
name|p
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
DECL|function|gimp_dock_window_update_title (GimpDockWindow * dock_window)
name|gimp_dock_window_update_title
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
block|{
if|if
condition|(
name|dock_window
operator|->
name|p
operator|->
name|update_title_idle_id
condition|)
name|g_source_remove
argument_list|(
name|dock_window
operator|->
name|p
operator|->
name|update_title_idle_id
argument_list|)
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|update_title_idle_id
operator|=
name|g_idle_add
argument_list|(
operator|(
name|GSourceFunc
operator|)
name|gimp_dock_window_update_title_idle
argument_list|,
name|dock_window
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dock_window_update_title_idle (GimpDockWindow * dock_window)
name|gimp_dock_window_update_title_idle
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
block|{
name|GimpDock
modifier|*
name|dock
init|=
name|gimp_dock_window_get_dock
argument_list|(
name|dock_window
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|title
init|=
name|gimp_dock_get_title
argument_list|(
name|dock
argument_list|)
decl_stmt|;
if|if
condition|(
name|title
condition|)
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|update_title_idle_id
operator|=
literal|0
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_window_dock_book_removed (GimpDockWindow * dock_window,GimpDockbook * dockbook,GimpDock * dock)
name|gimp_dock_window_dock_book_removed
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
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
condition|)
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock_window
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_dock_window_get_id (GimpDockWindow * dock_window)
name|gimp_dock_window_get_id
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|dock_window
operator|->
name|p
operator|->
name|ID
return|;
block|}
end_function

begin_function
name|GimpUIManager
modifier|*
DECL|function|gimp_dock_window_get_ui_manager (GimpDockWindow * dock_window)
name|gimp_dock_window_get_ui_manager
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dock_window
operator|->
name|p
operator|->
name|ui_manager
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_dock_window_from_dock:  * @dock:  *  * For convenience.  *  * Returns: If the toplevel widget for the dock is a GimpDockWindow,  * return that. Otherwise return %NULL.  **/
end_comment

begin_function
name|GimpDockWindow
modifier|*
DECL|function|gimp_dock_window_from_dock (GimpDock * dock)
name|gimp_dock_window_from_dock
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|toplevel
init|=
name|NULL
decl_stmt|;
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
name|toplevel
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_DOCK_WINDOW
argument_list|(
name|toplevel
argument_list|)
condition|)
return|return
name|GIMP_DOCK_WINDOW
argument_list|(
name|toplevel
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_dock_window_get_dock:  * @dock_window:  *  * Get the #GimpDock within the #GimpDockWindow.  *  * Returns:   **/
end_comment

begin_function
name|GimpDock
modifier|*
DECL|function|gimp_dock_window_get_dock (GimpDockWindow * dock_window)
name|gimp_dock_window_get_dock
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
block|{
comment|/* Change this to return the GimpDock *inside* the GimpDockWindow    * once GimpDock is not a subclass of GimpDockWindow any longer    */
return|return
name|GIMP_DOCK
argument_list|(
name|dock_window
argument_list|)
return|;
block|}
end_function

end_unit

