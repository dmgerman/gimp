begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagewindow.h"
end_include

begin_include
include|#
directive|include
file|"gimpstatusbar.h"
end_include

begin_include
include|#
directive|include
file|"gimp-log.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a1fbea40103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_MENU_FACTORY
name|PROP_MENU_FACTORY
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_image_window_constructor
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
name|gimp_image_window_finalize
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
name|gimp_image_window_set_property
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
name|gimp_image_window_get_property
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
name|gimp_image_window_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_image_window_window_state
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventWindowState
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_window_style_set
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
name|void
name|gimp_image_window_show_tooltip
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_window_hide_tooltip
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_window_shell_scaled
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_window_shell_title_notify
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_window_shell_status_notify
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpImageWindow
argument_list|,
argument|gimp_image_window
argument_list|,
argument|GIMP_TYPE_WINDOW
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_image_window_parent_class
end_define

begin_decl_stmt
specifier|static
specifier|const
name|gchar
name|image_window_rc_style
index|[]
init|=
literal|"style \"fullscreen-menubar-style\"\n"
literal|"{\n"
literal|"  GtkMenuBar::shadow-type      = none\n"
literal|"  GtkMenuBar::internal-padding = 0\n"
literal|"}\n"
literal|"widget \"*.gimp-menubar-fullscreen\" style \"fullscreen-menubar-style\"\n"
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_image_window_class_init (GimpImageWindowClass * klass)
name|gimp_image_window_class_init
parameter_list|(
name|GimpImageWindowClass
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
name|gimp_image_window_constructor
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_image_window_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_image_window_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_image_window_get_property
expr_stmt|;
name|gtk_object_class
operator|->
name|destroy
operator|=
name|gimp_image_window_destroy
expr_stmt|;
name|widget_class
operator|->
name|window_state_event
operator|=
name|gimp_image_window_window_state
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_image_window_style_set
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_MENU_FACTORY
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"menu-factory"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_MENU_FACTORY
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_rc_parse_string
argument_list|(
name|image_window_rc_style
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_window_init (GimpImageWindow * window)
name|gimp_image_window_init
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_image_window_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_image_window_constructor
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
name|GimpImageWindow
modifier|*
name|window
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
name|window
operator|=
name|GIMP_IMAGE_WINDOW
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_UI_MANAGER
argument_list|(
name|window
operator|->
name|menubar_manager
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_add_accel_group
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|gtk_ui_manager_get_accel_group
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|window
operator|->
name|menubar_manager
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|window
operator|->
name|menubar_manager
argument_list|,
literal|"show-tooltip"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_window_show_tooltip
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|window
operator|->
name|menubar_manager
argument_list|,
literal|"hide-tooltip"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_window_hide_tooltip
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
name|window
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
name|window
argument_list|)
argument_list|,
name|window
operator|->
name|main_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|window
operator|->
name|main_vbox
argument_list|)
expr_stmt|;
ifndef|#
directive|ifndef
name|GDK_WINDOWING_QUARTZ
name|window
operator|->
name|menubar
operator|=
name|gtk_ui_manager_get_widget
argument_list|(
name|GTK_UI_MANAGER
argument_list|(
name|window
operator|->
name|menubar_manager
argument_list|)
argument_list|,
literal|"/image-menubar"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* !GDK_WINDOWING_QUARTZ */
if|if
condition|(
name|window
operator|->
name|menubar
condition|)
block|{
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|window
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|window
operator|->
name|menubar
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  make sure we can activate accels even if the menubar is invisible        *  (see http://bugzilla.gnome.org/show_bug.cgi?id=137151)        */
name|g_signal_connect
argument_list|(
name|window
operator|->
name|menubar
argument_list|,
literal|"can-activate-accel"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_true
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
comment|/* FIXME display shell */
name|window
operator|->
name|statusbar
operator|=
name|gimp_statusbar_new
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|window
operator|->
name|statusbar
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_IMAGE_WINDOW_STATUS_BAR
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|window
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|window
operator|->
name|statusbar
argument_list|,
name|FALSE
argument_list|,
name|FALSE
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
DECL|function|gimp_image_window_finalize (GObject * object)
name|gimp_image_window_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpImageWindow
modifier|*
name|window
init|=
name|GIMP_IMAGE_WINDOW
argument_list|(
name|object
argument_list|)
decl_stmt|;
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
DECL|function|gimp_image_window_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_image_window_set_property
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
name|GimpImageWindow
modifier|*
name|window
init|=
name|GIMP_IMAGE_WINDOW
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
name|PROP_MENU_FACTORY
case|:
block|{
name|GimpMenuFactory
modifier|*
name|factory
init|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
decl_stmt|;
name|window
operator|->
name|menubar_manager
operator|=
name|gimp_menu_factory_manager_new
argument_list|(
name|factory
argument_list|,
literal|"<Image>"
argument_list|,
name|window
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
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
DECL|function|gimp_image_window_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_image_window_get_property
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
name|GimpImageWindow
modifier|*
name|window
init|=
name|GIMP_IMAGE_WINDOW
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
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
DECL|function|gimp_image_window_destroy (GtkObject * object)
name|gimp_image_window_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpImageWindow
modifier|*
name|window
init|=
name|GIMP_IMAGE_WINDOW
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|window
operator|->
name|menubar_manager
condition|)
block|{
name|g_object_unref
argument_list|(
name|window
operator|->
name|menubar_manager
argument_list|)
expr_stmt|;
name|window
operator|->
name|menubar_manager
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
name|gboolean
DECL|function|gimp_image_window_window_state (GtkWidget * widget,GdkEventWindowState * event)
name|gimp_image_window_window_state
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventWindowState
modifier|*
name|event
parameter_list|)
block|{
name|GimpImageWindow
modifier|*
name|window
init|=
name|GIMP_IMAGE_WINDOW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
init|=
name|gimp_image_window_get_active_display
argument_list|(
name|window
argument_list|)
decl_stmt|;
name|window
operator|->
name|window_state
operator|=
name|event
operator|->
name|new_window_state
expr_stmt|;
if|if
condition|(
name|event
operator|->
name|changed_mask
operator|&
name|GDK_WINDOW_STATE_FULLSCREEN
condition|)
block|{
name|GimpActionGroup
modifier|*
name|group
decl_stmt|;
name|gboolean
name|fullscreen
decl_stmt|;
name|fullscreen
operator|=
name|gimp_image_window_get_fullscreen
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|GIMP_LOG
argument_list|(
name|WM
argument_list|,
literal|"Image window '%s' [%p] set fullscreen %s"
argument_list|,
name|gtk_window_get_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|,
name|widget
argument_list|,
name|fullscreen
condition|?
literal|"TURE"
else|:
literal|"FALSE"
argument_list|)
expr_stmt|;
if|if
condition|(
name|window
operator|->
name|menubar
condition|)
name|gtk_widget_set_name
argument_list|(
name|window
operator|->
name|menubar
argument_list|,
name|fullscreen
condition|?
literal|"gimp-menubar-fullscreen"
else|:
name|NULL
argument_list|)
expr_stmt|;
name|gtk_statusbar_set_has_resize_grip
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|window
operator|->
name|statusbar
argument_list|)
argument_list|,
operator|!
name|fullscreen
argument_list|)
expr_stmt|;
name|group
operator|=
name|gimp_ui_manager_get_action_group
argument_list|(
name|window
operator|->
name|menubar_manager
argument_list|,
literal|"view"
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_active
argument_list|(
name|group
argument_list|,
literal|"view-fullscreen"
argument_list|,
name|fullscreen
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|event
operator|->
name|changed_mask
operator|&
name|GDK_WINDOW_STATE_ICONIFIED
condition|)
block|{
name|gboolean
name|iconified
init|=
operator|(
name|event
operator|->
name|new_window_state
operator|&
name|GDK_WINDOW_STATE_ICONIFIED
operator|)
operator|!=
literal|0
decl_stmt|;
name|GIMP_LOG
argument_list|(
name|WM
argument_list|,
literal|"Image window '%s' [%p] set %s"
argument_list|,
name|gtk_window_get_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|,
name|widget
argument_list|,
name|iconified
condition|?
literal|"iconified"
else|:
literal|"uniconified"
argument_list|)
expr_stmt|;
if|if
condition|(
name|iconified
condition|)
block|{
if|if
condition|(
name|gimp_displays_get_num_visible
argument_list|(
name|display
operator|->
name|gimp
argument_list|)
operator|==
literal|0
condition|)
block|{
name|GIMP_LOG
argument_list|(
name|WM
argument_list|,
literal|"No displays visible any longer"
argument_list|)
expr_stmt|;
name|gimp_dialog_factories_hide_with_display
argument_list|()
expr_stmt|;
block|}
block|}
else|else
block|{
name|gimp_dialog_factories_show_with_display
argument_list|()
expr_stmt|;
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
DECL|function|gimp_image_window_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_image_window_style_set
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
name|GimpImageWindow
modifier|*
name|window
init|=
name|GIMP_IMAGE_WINDOW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkRequisition
name|requisition
decl_stmt|;
name|GdkGeometry
name|geometry
decl_stmt|;
name|GdkWindowHints
name|geometry_mask
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
name|gtk_widget_size_request
argument_list|(
name|window
operator|->
name|statusbar
argument_list|,
operator|&
name|requisition
argument_list|)
expr_stmt|;
name|geometry
operator|.
name|min_height
operator|=
literal|23
expr_stmt|;
name|geometry
operator|.
name|min_width
operator|=
name|requisition
operator|.
name|width
expr_stmt|;
name|geometry
operator|.
name|min_height
operator|+=
name|requisition
operator|.
name|height
expr_stmt|;
if|if
condition|(
name|window
operator|->
name|menubar
condition|)
block|{
name|gtk_widget_size_request
argument_list|(
name|window
operator|->
name|menubar
argument_list|,
operator|&
name|requisition
argument_list|)
expr_stmt|;
name|geometry
operator|.
name|min_height
operator|+=
name|requisition
operator|.
name|height
expr_stmt|;
block|}
name|geometry_mask
operator|=
name|GDK_HINT_MIN_SIZE
expr_stmt|;
comment|/*  Only set user pos on the empty display because it gets a pos    *  set by gimp. All other displays should be placed by the window    *  manager. See http://bugzilla.gnome.org/show_bug.cgi?id=559580    */
if|if
condition|(
operator|!
name|gimp_image_window_get_active_display
argument_list|(
name|window
argument_list|)
operator|->
name|image
condition|)
name|geometry_mask
operator||=
name|GDK_HINT_USER_POS
expr_stmt|;
name|gtk_window_set_geometry_hints
argument_list|(
name|GTK_WINDOW
argument_list|(
name|widget
argument_list|)
argument_list|,
name|NULL
argument_list|,
operator|&
name|geometry
argument_list|,
name|geometry_mask
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_set_has_min_size
argument_list|(
name|GTK_WINDOW
argument_list|(
name|widget
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_image_window_set_active_display (GimpImageWindow * window,GimpDisplay * display)
name|gimp_image_window_set_active_display
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|active_shell
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
comment|/* FIXME enable this when the display is a separate widget */
block|if (display == window->active_display)     return;    if (window->active_display)     {       active_shell = GIMP_DISPLAY_SHELL (window->active_display->shell);        g_signal_handlers_disconnect_by_func (active_shell,                                             gimp_image_window_shell_scaled,                                             window);       g_signal_handlers_disconnect_by_func (active_shell,                                             gimp_image_window_shell_title_notify,                                             window);       g_signal_handlers_disconnect_by_func (active_shell,                                             gimp_image_window_shell_status_notify,                                             window);     }    window->active_display = display;
endif|#
directive|endif
name|active_shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|window
operator|->
name|active_display
operator|->
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|active_shell
argument_list|,
literal|"scaled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_window_shell_scaled
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
comment|/* FIXME: "title" later */
name|g_signal_connect
argument_list|(
name|active_shell
argument_list|,
literal|"notify::gimp-title"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_window_shell_title_notify
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|active_shell
argument_list|,
literal|"notify::status"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_window_shell_status_notify
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
name|gimp_ui_manager_update
argument_list|(
name|window
operator|->
name|menubar_manager
argument_list|,
name|window
operator|->
name|active_display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpDisplay
modifier|*
DECL|function|gimp_image_window_get_active_display (GimpImageWindow * window)
name|gimp_image_window_get_active_display
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|window
operator|->
name|active_display
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_window_set_fullscreen (GimpImageWindow * window,gboolean fullscreen)
name|gimp_image_window_set_fullscreen
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|,
name|gboolean
name|fullscreen
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|fullscreen
operator|!=
name|gimp_image_window_get_fullscreen
argument_list|(
name|window
argument_list|)
condition|)
block|{
if|if
condition|(
name|fullscreen
condition|)
name|gtk_window_fullscreen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gtk_window_unfullscreen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_window_get_fullscreen (GimpImageWindow * window)
name|gimp_image_window_get_fullscreen
parameter_list|(
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
operator|(
name|window
operator|->
name|window_state
operator|&
name|GDK_WINDOW_STATE_FULLSCREEN
operator|)
operator|!=
literal|0
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_image_window_show_tooltip (GimpUIManager * manager,const gchar * tooltip,GimpImageWindow * window)
name|gimp_image_window_show_tooltip
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
block|{
name|gimp_statusbar_push
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|window
operator|->
name|statusbar
argument_list|)
argument_list|,
literal|"menu-tooltip"
argument_list|,
name|NULL
argument_list|,
literal|"%s"
argument_list|,
name|tooltip
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_window_hide_tooltip (GimpUIManager * manager,GimpImageWindow * window)
name|gimp_image_window_hide_tooltip
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
block|{
name|gimp_statusbar_pop
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|window
operator|->
name|statusbar
argument_list|)
argument_list|,
literal|"menu-tooltip"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_window_shell_scaled (GimpDisplayShell * shell,GimpImageWindow * window)
name|gimp_image_window_shell_scaled
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
block|{
comment|/* update the<Image>/View/Zoom menu */
name|gimp_ui_manager_update
argument_list|(
name|window
operator|->
name|menubar_manager
argument_list|,
name|shell
operator|->
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_window_shell_title_notify (GimpDisplayShell * shell,const GParamSpec * pspec,GimpImageWindow * window)
name|gimp_image_window_shell_title_notify
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
block|{
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|shell
operator|->
name|title
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_window_shell_status_notify (GimpDisplayShell * shell,const GParamSpec * pspec,GimpImageWindow * window)
name|gimp_image_window_shell_status_notify
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpImageWindow
modifier|*
name|window
parameter_list|)
block|{
name|gimp_statusbar_replace
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|window
operator|->
name|statusbar
argument_list|)
argument_list|,
literal|"title"
argument_list|,
name|NULL
argument_list|,
literal|"%s"
argument_list|,
name|shell
operator|->
name|status
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

