begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpuiconfigurer.c  * Copyright (C) 2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gui-types.h"
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
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockcolumns.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockwindow.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptoolbox.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-appearance.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpimagewindow.h"
end_include

begin_include
include|#
directive|include
file|"menus/menus.h"
end_include

begin_include
include|#
directive|include
file|"gimpuiconfigurer.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b434b5a0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_GIMP
name|PROP_GIMP
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpUIConfigurerPrivate
struct|struct
name|_GimpUIConfigurerPrivate
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_ui_configurer_set_property
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
name|gimp_ui_configurer_get_property
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
name|gimp_ui_configurer_move_docks_to_columns
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|,
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|gboolean
name|only_toolbox
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_configurer_move_shells
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|,
name|GimpImageWindow
modifier|*
name|source_image_window
parameter_list|,
name|GimpImageWindow
modifier|*
name|target_image_window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_configurer_separate_docks
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|,
name|GimpImageWindow
modifier|*
name|source_image_window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_configurer_move_docks_to_window
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|,
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_configurer_separate_shells
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|,
name|GimpImageWindow
modifier|*
name|source_image_window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_configurer_configure_for_single_window
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_configurer_configure_for_multi_window
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpImageWindow
modifier|*
name|gimp_ui_configurer_get_uber_window
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpUIConfigurer,gimp_ui_configurer,GIMP_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpUIConfigurer
argument_list|,
argument|gimp_ui_configurer
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_ui_configurer_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_ui_configurer_class_init
parameter_list|(
name|GimpUIConfigurerClass
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
name|set_property
operator|=
name|gimp_ui_configurer_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_ui_configurer_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GIMP
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"gimp"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GIMP
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
name|GimpUIConfigurerPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ui_configurer_init (GimpUIConfigurer * ui_configurer)
name|gimp_ui_configurer_init
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|)
block|{
name|ui_configurer
operator|->
name|p
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|ui_configurer
argument_list|,
name|GIMP_TYPE_UI_CONFIGURER
argument_list|,
name|GimpUIConfigurerPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ui_configurer_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_ui_configurer_set_property
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
name|GimpUIConfigurer
modifier|*
name|ui_configurer
init|=
name|GIMP_UI_CONFIGURER
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
name|PROP_GIMP
case|:
name|ui_configurer
operator|->
name|p
operator|->
name|gimp
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
comment|/* don't ref */
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
DECL|function|gimp_ui_configurer_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_ui_configurer_get_property
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
name|GimpUIConfigurer
modifier|*
name|ui_configurer
init|=
name|GIMP_UI_CONFIGURER
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
name|PROP_GIMP
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|ui_configurer
operator|->
name|p
operator|->
name|gimp
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
DECL|function|gimp_ui_configurer_move_docks_to_columns (GimpUIConfigurer * ui_configurer,GimpDockColumns * dock_columns,gboolean only_toolbox)
name|gimp_ui_configurer_move_docks_to_columns
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|,
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|,
name|gboolean
name|only_toolbox
parameter_list|)
block|{
name|GList
modifier|*
name|dialogs
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|dialog_iter
init|=
name|NULL
decl_stmt|;
name|dialogs
operator|=
name|g_list_copy
argument_list|(
name|gimp_dialog_factory_get_open_dialogs
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|dialog_iter
operator|=
name|dialogs
init|;
name|dialog_iter
condition|;
name|dialog_iter
operator|=
name|dialog_iter
operator|->
name|next
control|)
block|{
name|GimpDockWindow
modifier|*
name|dock_window
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|docks
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|dock_iter
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|GIMP_IS_DOCK_WINDOW
argument_list|(
name|dialog_iter
operator|->
name|data
argument_list|)
condition|)
continue|continue;
name|dock_window
operator|=
name|GIMP_DOCK_WINDOW
argument_list|(
name|dialog_iter
operator|->
name|data
argument_list|)
expr_stmt|;
name|docks
operator|=
name|g_list_copy
argument_list|(
name|gimp_dock_window_get_docks
argument_list|(
name|dock_window
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|dock_iter
operator|=
name|docks
init|;
name|dock_iter
condition|;
name|dock_iter
operator|=
name|dock_iter
operator|->
name|next
control|)
block|{
name|GimpDock
modifier|*
name|dock
init|=
name|GIMP_DOCK
argument_list|(
name|dock_iter
operator|->
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|only_toolbox
operator|&&
operator|!
name|GIMP_IS_TOOLBOX
argument_list|(
name|dock
argument_list|)
condition|)
continue|continue;
comment|/* Move the dock from the image window to the dock columns            * widget. Note that we need a ref while the dock is parentless            */
name|g_object_ref
argument_list|(
name|dock
argument_list|)
expr_stmt|;
name|gimp_dock_window_remove_dock
argument_list|(
name|dock_window
argument_list|,
name|dock
argument_list|)
expr_stmt|;
name|gimp_dock_columns_add_dock
argument_list|(
name|dock_columns
argument_list|,
name|dock
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dock
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|docks
argument_list|)
expr_stmt|;
comment|/* Kill the window if removing the dock didn't destroy it        * already. This will be the case for the toolbox dock window        */
comment|/* FIXME: We should solve this in a more elegant way, valgrind        * complains about invalid reads when the dock window already is        * destroyed        */
if|if
condition|(
name|GTK_IS_WIDGET
argument_list|(
name|dock_window
argument_list|)
operator|&&
name|g_list_length
argument_list|(
name|gimp_dock_window_get_docks
argument_list|(
name|dock_window
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gimp_dialog_factory_remove_dialog
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dock_window
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock_window
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_ui_configurer_move_shells:  * @ui_configurer:  * @source_image_window:  * @target_image_window:  *  * Move all display shells from one image window to the another.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_ui_configurer_move_shells (GimpUIConfigurer * ui_configurer,GimpImageWindow * source_image_window,GimpImageWindow * target_image_window)
name|gimp_ui_configurer_move_shells
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|,
name|GimpImageWindow
modifier|*
name|source_image_window
parameter_list|,
name|GimpImageWindow
modifier|*
name|target_image_window
parameter_list|)
block|{
while|while
condition|(
name|gimp_image_window_get_n_shells
argument_list|(
name|source_image_window
argument_list|)
operator|>
literal|0
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
name|gimp_image_window_get_shell
argument_list|(
name|source_image_window
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_image_window_remove_shell
argument_list|(
name|source_image_window
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_image_window_add_shell
argument_list|(
name|target_image_window
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_ui_configurer_separate_docks:  * @ui_configurer:  * @image_window:  *  * Move out the docks from the image window.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_ui_configurer_separate_docks (GimpUIConfigurer * ui_configurer,GimpImageWindow * image_window)
name|gimp_ui_configurer_separate_docks
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|,
name|GimpImageWindow
modifier|*
name|image_window
parameter_list|)
block|{
name|GimpDockColumns
modifier|*
name|left_docks
init|=
name|NULL
decl_stmt|;
name|GimpDockColumns
modifier|*
name|right_docks
init|=
name|NULL
decl_stmt|;
name|left_docks
operator|=
name|gimp_image_window_get_left_docks
argument_list|(
name|image_window
argument_list|)
expr_stmt|;
name|right_docks
operator|=
name|gimp_image_window_get_right_docks
argument_list|(
name|image_window
argument_list|)
expr_stmt|;
name|gimp_ui_configurer_move_docks_to_window
argument_list|(
name|ui_configurer
argument_list|,
name|left_docks
argument_list|)
expr_stmt|;
name|gimp_ui_configurer_move_docks_to_window
argument_list|(
name|ui_configurer
argument_list|,
name|right_docks
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_ui_configurer_move_docks_to_window:  * @dock_columns:  *  * Moves docks in @dock_columns into a new #GimpDockWindow.  * FIXME: Properly session manage  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_ui_configurer_move_docks_to_window (GimpUIConfigurer * ui_configurer,GimpDockColumns * dock_columns)
name|gimp_ui_configurer_move_docks_to_window
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|,
name|GimpDockColumns
modifier|*
name|dock_columns
parameter_list|)
block|{
name|GdkScreen
modifier|*
name|screen
init|=
name|gtk_widget_get_screen
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock_columns
argument_list|)
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|docks
init|=
name|g_list_copy
argument_list|(
name|gimp_dock_columns_get_docks
argument_list|(
name|dock_columns
argument_list|)
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|iter
init|=
name|NULL
decl_stmt|;
for|for
control|(
name|iter
operator|=
name|docks
init|;
name|iter
condition|;
name|iter
operator|=
name|iter
operator|->
name|next
control|)
block|{
name|GimpDock
modifier|*
name|dock
init|=
name|GIMP_DOCK
argument_list|(
name|iter
operator|->
name|data
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|dock_window
init|=
name|NULL
decl_stmt|;
comment|/* Create a dock window to put the dock in. Checking for        * GIMP_IS_TOOLBOX() is kind of ugly but not a disaster. We need        * the dock window correctly configured if we create it for the        * toolbox        */
name|dock_window
operator|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|screen
argument_list|,
name|NULL
comment|/*ui_manager*/
argument_list|,
operator|(
name|GIMP_IS_TOOLBOX
argument_list|(
name|dock
argument_list|)
condition|?
literal|"gimp-toolbox-window"
else|:
literal|"gimp-dock-window"
operator|)
argument_list|,
operator|-
literal|1
comment|/*view_size*/
argument_list|,
name|FALSE
comment|/*present*/
argument_list|)
expr_stmt|;
comment|/* Move the dock to the window */
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
name|gimp_dock_window_add_dock
argument_list|(
name|GIMP_DOCK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|,
name|dock
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dock
argument_list|)
expr_stmt|;
comment|/* Don't forget to show the window */
name|gtk_widget_show
argument_list|(
name|dock_window
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|docks
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_ui_configurer_separate_shells:  * @ui_configurer:  * @source_image_window:  *  * Create one image window per display shell and move it there.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_ui_configurer_separate_shells (GimpUIConfigurer * ui_configurer,GimpImageWindow * source_image_window)
name|gimp_ui_configurer_separate_shells
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|,
name|GimpImageWindow
modifier|*
name|source_image_window
parameter_list|)
block|{
comment|/* The last display shell remains in its window */
while|while
condition|(
name|gimp_image_window_get_n_shells
argument_list|(
name|source_image_window
argument_list|)
operator|>
literal|1
condition|)
block|{
name|GimpImageWindow
modifier|*
name|new_image_window
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
comment|/* Create a new image window */
name|new_image_window
operator|=
name|gimp_image_window_new
argument_list|(
name|ui_configurer
operator|->
name|p
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|global_menu_factory
argument_list|,
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|)
expr_stmt|;
comment|/* Move the shell there */
name|shell
operator|=
name|gimp_image_window_get_shell
argument_list|(
name|source_image_window
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_image_window_remove_shell
argument_list|(
name|source_image_window
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_image_window_add_shell
argument_list|(
name|new_image_window
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shell
argument_list|)
expr_stmt|;
comment|/* FIXME: If we don't set a size request here the window will be        * too small. Get rid of this hack and fix it the proper way        */
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|new_image_window
argument_list|)
argument_list|,
literal|640
argument_list|,
literal|480
argument_list|)
expr_stmt|;
comment|/* Show after we have added the shell */
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|new_image_window
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_ui_configurer_configure_for_single_window:  * @ui_configurer:  *  * Move docks and display shells into a single window.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_ui_configurer_configure_for_single_window (GimpUIConfigurer * ui_configurer)
name|gimp_ui_configurer_configure_for_single_window
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|ui_configurer
operator|->
name|p
operator|->
name|gimp
decl_stmt|;
name|GList
modifier|*
name|windows
init|=
name|gimp_get_image_windows
argument_list|(
name|gimp
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|iter
init|=
name|NULL
decl_stmt|;
name|GimpImageWindow
modifier|*
name|uber_image_window
init|=
name|NULL
decl_stmt|;
name|GimpDockColumns
modifier|*
name|left_docks
init|=
name|NULL
decl_stmt|;
name|GimpDockColumns
modifier|*
name|right_docks
init|=
name|NULL
decl_stmt|;
comment|/* Get and setup the window to put everything in */
name|uber_image_window
operator|=
name|gimp_ui_configurer_get_uber_window
argument_list|(
name|ui_configurer
argument_list|)
expr_stmt|;
comment|/* Get dock areas */
name|left_docks
operator|=
name|gimp_image_window_get_left_docks
argument_list|(
name|uber_image_window
argument_list|)
expr_stmt|;
name|right_docks
operator|=
name|gimp_image_window_get_right_docks
argument_list|(
name|uber_image_window
argument_list|)
expr_stmt|;
comment|/* First move the toolbox to the left side of the image    * window    */
name|gimp_ui_configurer_move_docks_to_columns
argument_list|(
name|ui_configurer
argument_list|,
name|left_docks
argument_list|,
name|TRUE
comment|/*only_toolbox*/
argument_list|)
expr_stmt|;
comment|/* Then move the other docks to the right side of the image    * window    */
name|gimp_ui_configurer_move_docks_to_columns
argument_list|(
name|ui_configurer
argument_list|,
name|right_docks
argument_list|,
name|FALSE
comment|/*only_toolbox*/
argument_list|)
expr_stmt|;
comment|/* Move stuff from other windows to the uber image window */
for|for
control|(
name|iter
operator|=
name|windows
init|;
name|iter
condition|;
name|iter
operator|=
name|g_list_next
argument_list|(
name|iter
argument_list|)
control|)
block|{
name|GimpImageWindow
modifier|*
name|image_window
init|=
name|GIMP_IMAGE_WINDOW
argument_list|(
name|iter
operator|->
name|data
argument_list|)
decl_stmt|;
comment|/* Don't move stuff to itself */
if|if
condition|(
name|image_window
operator|==
name|uber_image_window
condition|)
continue|continue;
comment|/* Put the displays in the rest of the image windows into        * the uber image window        */
name|gimp_ui_configurer_move_shells
argument_list|(
name|ui_configurer
argument_list|,
name|image_window
argument_list|,
name|uber_image_window
argument_list|)
expr_stmt|;
comment|/* Destroy the window */
name|gimp_image_window_destroy
argument_list|(
name|image_window
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|windows
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_ui_configurer_configure_for_multi_window:  * @ui_configurer:  *  * Moves all display shells into their own image window.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_ui_configurer_configure_for_multi_window (GimpUIConfigurer * ui_configurer)
name|gimp_ui_configurer_configure_for_multi_window
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|ui_configurer
operator|->
name|p
operator|->
name|gimp
decl_stmt|;
name|GList
modifier|*
name|windows
init|=
name|gimp_get_image_windows
argument_list|(
name|gimp
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|iter
init|=
name|NULL
decl_stmt|;
for|for
control|(
name|iter
operator|=
name|windows
init|;
name|iter
condition|;
name|iter
operator|=
name|g_list_next
argument_list|(
name|iter
argument_list|)
control|)
block|{
name|GimpImageWindow
modifier|*
name|image_window
init|=
name|GIMP_IMAGE_WINDOW
argument_list|(
name|iter
operator|->
name|data
argument_list|)
decl_stmt|;
name|gimp_ui_configurer_separate_docks
argument_list|(
name|ui_configurer
argument_list|,
name|image_window
argument_list|)
expr_stmt|;
name|gimp_ui_configurer_separate_shells
argument_list|(
name|ui_configurer
argument_list|,
name|image_window
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|windows
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_ui_configurer_get_uber_window:  * @ui_configurer:  *  * Returns: The window to be used as the main window for single-window  *          mode.  **/
end_comment

begin_function
specifier|static
name|GimpImageWindow
modifier|*
DECL|function|gimp_ui_configurer_get_uber_window (GimpUIConfigurer * ui_configurer)
name|gimp_ui_configurer_get_uber_window
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|ui_configurer
operator|->
name|p
operator|->
name|gimp
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
init|=
name|gimp_get_display_iter
argument_list|(
name|gimp
argument_list|)
operator|->
name|data
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GimpImageWindow
modifier|*
name|image_window
init|=
name|gimp_display_shell_get_window
argument_list|(
name|shell
argument_list|)
decl_stmt|;
return|return
name|image_window
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_ui_configurer_update_appearance:  * @ui_configurer:  *  * Updates the appearance of all shells in all image windows, so they  * do whatever they deem neccessary to fit the new UI mode mode.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_ui_configurer_update_appearance (GimpUIConfigurer * ui_configurer)
name|gimp_ui_configurer_update_appearance
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|ui_configurer
operator|->
name|p
operator|->
name|gimp
decl_stmt|;
name|GList
modifier|*
name|windows
init|=
name|gimp_get_image_windows
argument_list|(
name|gimp
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|windows
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
name|GimpImageWindow
modifier|*
name|image_window
init|=
name|GIMP_IMAGE_WINDOW
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
name|gint
name|n_shells
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|n_shells
operator|=
name|gimp_image_window_get_n_shells
argument_list|(
name|image_window
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
name|n_shells
condition|;
name|i
operator|++
control|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
name|gimp_image_window_get_shell
argument_list|(
name|image_window
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|gimp_display_shell_appearance_update
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
block|}
name|g_list_free
argument_list|(
name|windows
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_ui_configurer_configure:  * @ui_configurer:  * @single_window_mode:  *  * Configure the UI.  **/
end_comment

begin_function
name|void
DECL|function|gimp_ui_configurer_configure (GimpUIConfigurer * ui_configurer,gboolean single_window_mode)
name|gimp_ui_configurer_configure
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|,
name|gboolean
name|single_window_mode
parameter_list|)
block|{
if|if
condition|(
name|single_window_mode
condition|)
name|gimp_ui_configurer_configure_for_single_window
argument_list|(
name|ui_configurer
argument_list|)
expr_stmt|;
else|else
name|gimp_ui_configurer_configure_for_multi_window
argument_list|(
name|ui_configurer
argument_list|)
expr_stmt|;
name|gimp_ui_configurer_update_appearance
argument_list|(
name|ui_configurer
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

