begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimprectangleoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimprectangleselectoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimptooloptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_rect_select_options_rectangle_options_iface_init
parameter_list|(
name|GimpRectangleOptionsInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpRectSelectOptions,gimp_rect_select_options,GIMP_TYPE_SELECTION_OPTIONS,G_IMPLEMENT_INTERFACE (GIMP_TYPE_RECTANGLE_OPTIONS,gimp_rect_select_options_rectangle_options_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpRectSelectOptions
argument_list|,
argument|gimp_rect_select_options
argument_list|,
argument|GIMP_TYPE_SELECTION_OPTIONS
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_RECTANGLE_OPTIONS,                                                 gimp_rect_select_options_rectangle_options_iface_init)
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_rect_select_options_class_init
parameter_list|(
name|GimpRectSelectOptionsClass
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
name|gimp_rectangle_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_rectangle_options_get_property
expr_stmt|;
name|gimp_rectangle_options_install_properties
argument_list|(
name|object_class
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rect_select_options_init (GimpRectSelectOptions * options)
name|gimp_rect_select_options_init
parameter_list|(
name|GimpRectSelectOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rect_select_options_rectangle_options_iface_init (GimpRectangleOptionsInterface * iface)
name|gimp_rect_select_options_rectangle_options_iface_init
parameter_list|(
name|GimpRectangleOptionsInterface
modifier|*
name|iface
parameter_list|)
block|{ }
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_rect_select_options_gui (GimpToolOptions * tool_options)
name|gimp_rect_select_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
init|=
name|gimp_selection_options_gui
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox_rectangle
decl_stmt|;
comment|/*  rectangle options  */
name|vbox_rectangle
operator|=
name|gimp_rectangle_options_gui
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|vbox_rectangle
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
name|vbox_rectangle
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|GIMP_RECTANGLE_OPTIONS
argument_list|(
name|tool_options
argument_list|)
argument_list|,
literal|"highlight"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit

