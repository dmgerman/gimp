begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmultiwindowstrategy.c  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpmultiwindowstrategy.h"
end_include

begin_include
include|#
directive|include
file|"gimpwindowstrategy.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_multi_window_strategy_window_strategy_iface_init
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
name|gimp_multi_window_strategy_create_dockable_dialog
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
name|GdkScreen
modifier|*
name|screen
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifiers
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpMultiWindowStrategy,gimp_multi_window_strategy,GIMP_TYPE_OBJECT,G_IMPLEMENT_INTERFACE (GIMP_TYPE_WINDOW_STRATEGY,gimp_multi_window_strategy_window_strategy_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpMultiWindowStrategy
argument_list|,
argument|gimp_multi_window_strategy
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_WINDOW_STRATEGY,                                                 gimp_multi_window_strategy_window_strategy_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_multi_window_strategy_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_multi_window_strategy_class_init
parameter_list|(
name|GimpMultiWindowStrategyClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_multi_window_strategy_init (GimpMultiWindowStrategy * strategy)
name|gimp_multi_window_strategy_init
parameter_list|(
name|GimpMultiWindowStrategy
modifier|*
name|strategy
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_multi_window_strategy_window_strategy_iface_init (GimpWindowStrategyInterface * iface)
name|gimp_multi_window_strategy_window_strategy_iface_init
parameter_list|(
name|GimpWindowStrategyInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|create_dockable_dialog
operator|=
name|gimp_multi_window_strategy_create_dockable_dialog
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_multi_window_strategy_create_dockable_dialog (GimpWindowStrategy * strategy,Gimp * gimp,GimpDialogFactory * factory,GdkScreen * screen,const gchar * identifiers)
name|gimp_multi_window_strategy_create_dockable_dialog
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
name|GdkScreen
modifier|*
name|screen
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifiers
parameter_list|)
block|{
return|return
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|factory
argument_list|,
name|screen
argument_list|,
name|identifiers
argument_list|,
operator|-
literal|1
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpObject
modifier|*
DECL|function|gimp_multi_window_strategy_get_singleton (void)
name|gimp_multi_window_strategy_get_singleton
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
name|GIMP_TYPE_MULTI_WINDOW_STRATEGY
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

