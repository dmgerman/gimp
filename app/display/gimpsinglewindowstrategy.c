begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsinglewindowstrategy.c  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
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
file|"widgets/gimpdockbook.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockcolumns.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwindowstrategy.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagewindow.h"
end_include

begin_include
include|#
directive|include
file|"gimpsinglewindowstrategy.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_single_window_strategy_window_strategy_iface_init
parameter_list|(
name|GimpWindowStrategyInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_single_window_strategy_show_dockable_dialog
parameter_list|(
name|GimpWindowStrategy
modifier|*
name|strategy
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GdkMonitor
modifier|*
name|monitor
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifiers
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpSingleWindowStrategy,gimp_single_window_strategy,GIMP_TYPE_OBJECT,G_IMPLEMENT_INTERFACE (GIMP_TYPE_WINDOW_STRATEGY,gimp_single_window_strategy_window_strategy_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpSingleWindowStrategy
argument_list|,
argument|gimp_single_window_strategy
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_WINDOW_STRATEGY,                                                 gimp_single_window_strategy_window_strategy_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_single_window_strategy_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_single_window_strategy_class_init
parameter_list|(
name|GimpSingleWindowStrategyClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_single_window_strategy_init (GimpSingleWindowStrategy * strategy)
name|gimp_single_window_strategy_init
parameter_list|(
name|GimpSingleWindowStrategy
modifier|*
name|strategy
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_single_window_strategy_window_strategy_iface_init (GimpWindowStrategyInterface * iface)
name|gimp_single_window_strategy_window_strategy_iface_init
parameter_list|(
name|GimpWindowStrategyInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|show_dockable_dialog
operator|=
name|gimp_single_window_strategy_show_dockable_dialog
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_single_window_strategy_show_dockable_dialog (GimpWindowStrategy * strategy,Gimp * gimp,GimpDialogFactory * factory,GdkMonitor * monitor,const gchar * identifiers)
name|gimp_single_window_strategy_show_dockable_dialog
parameter_list|(
name|GimpWindowStrategy
modifier|*
name|strategy
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GdkMonitor
modifier|*
name|monitor
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifiers
parameter_list|)
block|{
name|GList
modifier|*
name|windows
init|=
name|gimp_get_image_windows
argument_list|(
name|gimp
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
init|=
name|NULL
decl_stmt|;
name|GimpImageWindow
modifier|*
name|window
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|windows
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* In single-window mode, there should only be one window... */
name|window
operator|=
name|GIMP_IMAGE_WINDOW
argument_list|(
name|windows
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
literal|"gimp-toolbox"
argument_list|,
name|identifiers
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/* Only allow one toolbox... */
if|if
condition|(
operator|!
name|gimp_image_window_has_toolbox
argument_list|(
name|window
argument_list|)
condition|)
block|{
name|GimpDockColumns
modifier|*
name|columns
decl_stmt|;
name|GimpUIManager
modifier|*
name|ui_manager
init|=
name|gimp_image_window_get_ui_manager
argument_list|(
name|window
argument_list|)
decl_stmt|;
name|widget
operator|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|factory
argument_list|,
name|monitor
argument_list|,
name|ui_manager
argument_list|,
name|GTK_WIDGET
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"gimp-toolbox"
argument_list|,
operator|-
literal|1
comment|/*view_size*/
argument_list|,
name|FALSE
comment|/*present*/
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|columns
operator|=
name|gimp_image_window_get_left_docks
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|gimp_dock_columns_add_dock
argument_list|(
name|columns
argument_list|,
name|GIMP_DOCK
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|-
literal|1
comment|/*index*/
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|gimp_dialog_factory_find_widget
argument_list|(
name|factory
argument_list|,
name|identifiers
argument_list|)
condition|)
block|{
comment|/* if the dialog is already open, simply raise it */
return|return
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|factory
argument_list|,
name|monitor
argument_list|,
name|GTK_WIDGET
argument_list|(
name|window
argument_list|)
argument_list|,
name|identifiers
argument_list|,
operator|-
literal|1
argument_list|)
return|;
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|dockbook
decl_stmt|;
name|dockbook
operator|=
name|gimp_image_window_get_default_dockbook
argument_list|(
name|window
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dockbook
condition|)
block|{
name|GimpDockColumns
modifier|*
name|dock_columns
decl_stmt|;
comment|/* No dock, need to add one */
name|dock_columns
operator|=
name|gimp_image_window_get_right_docks
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|gimp_dock_columns_prepare_dockbook
argument_list|(
name|dock_columns
argument_list|,
operator|-
literal|1
comment|/*index*/
argument_list|,
operator|&
name|dockbook
argument_list|)
expr_stmt|;
block|}
name|widget
operator|=
name|gimp_dockbook_add_from_dialog_factory
argument_list|(
name|GIMP_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|identifiers
argument_list|,
operator|-
literal|1
comment|/*index*/
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|windows
argument_list|)
expr_stmt|;
return|return
name|widget
return|;
block|}
end_function

begin_function
name|GimpObject
modifier|*
DECL|function|gimp_single_window_strategy_get_singleton (void)
name|gimp_single_window_strategy_get_singleton
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpObject
modifier|*
name|singleton
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|singleton
condition|)
name|singleton
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_SINGLE_WINDOW_STRATEGY
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|singleton
return|;
block|}
end_function

end_unit

