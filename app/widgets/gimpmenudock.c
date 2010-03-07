begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmenudock.c  * Copyright (C) 2001-2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
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
file|"gimpmenudock.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|DEFAULT_MINIMAL_WIDTH
define|#
directive|define
name|DEFAULT_MINIMAL_WIDTH
value|200
end_define

begin_struct
DECL|struct|_GimpMenuDockPrivate
struct|struct
name|_GimpMenuDockPrivate
block|{
DECL|member|make_sizeof_greater_than_zero
name|gint
name|make_sizeof_greater_than_zero
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_menu_dock_style_set
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpMenuDock,gimp_menu_dock,GIMP_TYPE_DOCK)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpMenuDock
argument_list|,
argument|gimp_menu_dock
argument_list|,
argument|GIMP_TYPE_DOCK
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_menu_dock_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_menu_dock_class_init
parameter_list|(
name|GimpMenuDockClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_menu_dock_style_set
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"minimal-width"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
name|DEFAULT_MINIMAL_WIDTH
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
name|GimpMenuDockPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_menu_dock_init (GimpMenuDock * dock)
name|gimp_menu_dock_init
parameter_list|(
name|GimpMenuDock
modifier|*
name|dock
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_menu_dock_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_menu_dock_style_set
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
name|gint
name|minimal_width
init|=
operator|-
literal|1
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
literal|"minimal-width"
argument_list|,
operator|&
name|minimal_width
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|widget
argument_list|,
name|minimal_width
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_menu_dock_new (void)
name|gimp_menu_dock_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_MENU_DOCK
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

