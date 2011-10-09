begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdynamicsfactoryview.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpdynamicsfactoryview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDynamicsFactoryView,gimp_dynamics_factory_view,GIMP_TYPE_DATA_FACTORY_VIEW)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDynamicsFactoryView
argument_list|,
argument|gimp_dynamics_factory_view
argument_list|,
argument|GIMP_TYPE_DATA_FACTORY_VIEW
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_dynamics_factory_view_class_init
parameter_list|(
name|GimpDynamicsFactoryViewClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_factory_view_init (GimpDynamicsFactoryView * view)
name|gimp_dynamics_factory_view_init
parameter_list|(
name|GimpDynamicsFactoryView
modifier|*
name|view
parameter_list|)
block|{ }
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dynamics_factory_view_new (GimpViewType view_type,GimpDataFactory * factory,GimpContext * context,gint view_size,gint view_border_width,GimpMenuFactory * menu_factory)
name|gimp_dynamics_factory_view_new
parameter_list|(
name|GimpViewType
name|view_type
parameter_list|,
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|GimpDynamicsFactoryView
modifier|*
name|factory_view
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|view_size
operator|>
literal|0
operator|&&
name|view_size
operator|<=
name|GIMP_VIEWABLE_MAX_PREVIEW_SIZE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|view_border_width
operator|>=
literal|0
operator|&&
name|view_border_width
operator|<=
name|GIMP_VIEW_MAX_BORDER_WIDTH
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|factory_view
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DYNAMICS_FACTORY_VIEW
argument_list|,
literal|"view-type"
argument_list|,
name|view_type
argument_list|,
literal|"data-factory"
argument_list|,
name|factory
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_data_factory_view_construct
argument_list|(
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|factory_view
argument_list|)
argument_list|,
name|view_size
argument_list|,
name|view_border_width
argument_list|,
name|menu_factory
argument_list|,
literal|"<Dynamics>"
argument_list|,
literal|"/dynamics-popup"
argument_list|,
literal|"dynamics"
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|factory_view
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|GTK_WIDGET
argument_list|(
name|factory_view
argument_list|)
return|;
block|}
end_function

end_unit

