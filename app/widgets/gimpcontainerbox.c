begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainerbox.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpcontainerbox.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_container_box_view_iface_init
parameter_list|(
name|GimpContainerViewInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_box_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_container_box_get_preview
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_box_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpContainerBox,gimp_container_box,GIMP_TYPE_EDITOR,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONTAINER_VIEW,gimp_container_box_view_iface_init)G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,gimp_container_box_docked_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpContainerBox
argument_list|,
argument|gimp_container_box
argument_list|,
argument|GIMP_TYPE_EDITOR
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONTAINER_VIEW,                                                 gimp_container_box_view_iface_init)                          G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,                                                 gimp_container_box_docked_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_container_box_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_container_box_class_init
parameter_list|(
name|GimpContainerBoxClass
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
name|gimp_container_view_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_container_view_get_property
expr_stmt|;
name|gimp_container_view_install_properties
argument_list|(
name|object_class
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_box_init (GimpContainerBox * box)
name|gimp_container_box_init
parameter_list|(
name|GimpContainerBox
modifier|*
name|box
parameter_list|)
block|{
name|GimpContainerView
modifier|*
name|view
init|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|box
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|sb
decl_stmt|;
name|box
operator|->
name|scrolled_win
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|box
operator|->
name|scrolled_win
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
operator|->
name|scrolled_win
argument_list|)
expr_stmt|;
name|sb
operator|=
name|gtk_scrolled_window_get_vscrollbar
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|box
operator|->
name|scrolled_win
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_can_focus
argument_list|(
name|sb
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_container_view_set_dnd_widget
argument_list|(
name|view
argument_list|,
name|box
operator|->
name|scrolled_win
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_box_view_iface_init (GimpContainerViewInterface * iface)
name|gimp_container_box_view_iface_init
parameter_list|(
name|GimpContainerViewInterface
modifier|*
name|iface
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_box_docked_iface_init (GimpDockedInterface * iface)
name|gimp_container_box_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|get_preview
operator|=
name|gimp_container_box_get_preview
expr_stmt|;
name|iface
operator|->
name|set_context
operator|=
name|gimp_container_box_set_context
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_box_set_size_request (GimpContainerBox * box,gint width,gint height)
name|gimp_container_box_set_size_request
parameter_list|(
name|GimpContainerBox
modifier|*
name|box
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpContainerView
modifier|*
name|view
decl_stmt|;
name|GtkScrolledWindowClass
modifier|*
name|sw_class
decl_stmt|;
name|GtkStyle
modifier|*
name|sw_style
decl_stmt|;
name|GtkWidget
modifier|*
name|sb
decl_stmt|;
name|GtkRequisition
name|req
decl_stmt|;
name|gint
name|view_size
decl_stmt|;
name|gint
name|scrollbar_width
decl_stmt|;
name|gint
name|border_x
decl_stmt|;
name|gint
name|border_y
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|view_size
operator|=
name|gimp_container_view_get_view_size
argument_list|(
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|width
operator|<=
literal|0
operator|||
name|width
operator|>=
name|view_size
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|height
operator|<=
literal|0
operator|||
name|height
operator|>=
name|view_size
argument_list|)
expr_stmt|;
name|sw_class
operator|=
name|GTK_SCROLLED_WINDOW_GET_CLASS
argument_list|(
name|box
operator|->
name|scrolled_win
argument_list|)
expr_stmt|;
if|if
condition|(
name|sw_class
operator|->
name|scrollbar_spacing
operator|>=
literal|0
condition|)
name|scrollbar_width
operator|=
name|sw_class
operator|->
name|scrollbar_spacing
expr_stmt|;
else|else
name|gtk_widget_style_get
argument_list|(
name|GTK_WIDGET
argument_list|(
name|box
operator|->
name|scrolled_win
argument_list|)
argument_list|,
literal|"scrollbar-spacing"
argument_list|,
operator|&
name|scrollbar_width
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|sb
operator|=
name|gtk_scrolled_window_get_vscrollbar
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|box
operator|->
name|scrolled_win
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_size_request
argument_list|(
name|sb
argument_list|,
operator|&
name|req
argument_list|)
expr_stmt|;
name|scrollbar_width
operator|+=
name|req
operator|.
name|width
expr_stmt|;
name|border_x
operator|=
name|border_y
operator|=
name|gtk_container_get_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|sw_style
operator|=
name|gtk_widget_get_style
argument_list|(
name|box
operator|->
name|scrolled_win
argument_list|)
expr_stmt|;
name|border_x
operator|+=
name|sw_style
operator|->
name|xthickness
operator|*
literal|2
operator|+
name|scrollbar_width
expr_stmt|;
name|border_y
operator|+=
name|sw_style
operator|->
name|ythickness
operator|*
literal|2
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|box
operator|->
name|scrolled_win
argument_list|,
name|width
operator|>
literal|0
condition|?
name|width
operator|+
name|border_x
else|:
operator|-
literal|1
argument_list|,
name|height
operator|>
literal|0
condition|?
name|height
operator|+
name|border_y
else|:
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_box_set_context (GimpDocked * docked,GimpContext * context)
name|gimp_container_box_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|gimp_container_view_set_context
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|docked
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_container_box_get_preview (GimpDocked * docked,GimpContext * context,GtkIconSize size)
name|gimp_container_box_get_preview
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
block|{
name|GimpContainerBox
modifier|*
name|box
init|=
name|GIMP_CONTAINER_BOX
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|GimpContainerView
modifier|*
name|view
init|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|border_width
init|=
literal|1
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|prop_name
decl_stmt|;
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|container
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_icon_size_lookup_for_settings
argument_list|(
name|gtk_widget_get_settings
argument_list|(
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
argument_list|)
argument_list|,
name|size
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|prop_name
operator|=
name|gimp_context_type_to_prop_name
argument_list|(
name|gimp_container_get_children_type
argument_list|(
name|container
argument_list|)
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_prop_view_new
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
name|prop_name
argument_list|,
name|context
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|GIMP_VIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|renderer
operator|->
name|size
operator|=
operator|-
literal|1
expr_stmt|;
name|gimp_container_view_get_view_size
argument_list|(
name|view
argument_list|,
operator|&
name|border_width
argument_list|)
expr_stmt|;
name|border_width
operator|=
name|MIN
argument_list|(
literal|1
argument_list|,
name|border_width
argument_list|)
expr_stmt|;
name|gimp_view_renderer_set_size_full
argument_list|(
name|GIMP_VIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|renderer
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|border_width
argument_list|)
expr_stmt|;
return|return
name|preview
return|;
block|}
end_function

end_unit

