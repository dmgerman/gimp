begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpwindowstrategy.c  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpwindowstrategy.h"
end_include

begin_macro
DECL|function|G_DEFINE_INTERFACE (GimpWindowStrategy,gimp_window_strategy,G_TYPE_OBJECT)
name|G_DEFINE_INTERFACE
argument_list|(
argument|GimpWindowStrategy
argument_list|,
argument|gimp_window_strategy
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
name|gimp_window_strategy_default_init
parameter_list|(
name|GimpWindowStrategyInterface
modifier|*
name|iface
parameter_list|)
block|{ }
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_window_strategy_show_dockable_dialog (GimpWindowStrategy * strategy,Gimp * gimp,GimpDialogFactory * factory,GdkMonitor * monitor,const gchar * identifiers)
name|gimp_window_strategy_show_dockable_dialog
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
name|GimpWindowStrategyInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_WINDOW_STRATEGY
argument_list|(
name|strategy
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_WINDOW_STRATEGY_GET_IFACE
argument_list|(
name|strategy
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|show_dockable_dialog
condition|)
return|return
name|iface
operator|->
name|show_dockable_dialog
argument_list|(
name|strategy
argument_list|,
name|gimp
argument_list|,
name|factory
argument_list|,
name|monitor
argument_list|,
name|identifiers
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

