begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainerbox.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimppropwidgets.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_container_box_class_init
parameter_list|(
name|GimpContainerBoxClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_box_init
parameter_list|(
name|GimpContainerBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_box_view_iface_init
parameter_list|(
name|GimpContainerViewInterface
modifier|*
name|view_iface
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
name|docked_iface
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpEditorClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_container_box_get_type (void)
name|gimp_container_box_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|box_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpContainerBoxClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_container_box_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpContainerBox
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_container_box_init
block|,       }
decl_stmt|;
specifier|static
specifier|const
name|GInterfaceInfo
name|view_iface_info
init|=
block|{
operator|(
name|GInterfaceInitFunc
operator|)
name|gimp_container_box_view_iface_init
block|,
name|NULL
block|,
comment|/* iface_finalize */
name|NULL
comment|/* iface_data     */
block|}
decl_stmt|;
specifier|static
specifier|const
name|GInterfaceInfo
name|docked_iface_info
init|=
block|{
operator|(
name|GInterfaceInitFunc
operator|)
name|gimp_container_box_docked_iface_init
block|,
name|NULL
block|,
comment|/* iface_finalize */
name|NULL
comment|/* iface_data     */
block|}
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_EDITOR
argument_list|,
literal|"GimpContainerBox"
argument_list|,
operator|&
name|box_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|type
argument_list|,
name|GIMP_TYPE_CONTAINER_VIEW
argument_list|,
operator|&
name|view_iface_info
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|type
argument_list|,
name|GIMP_TYPE_DOCKED
argument_list|,
operator|&
name|docked_iface_info
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_box_class_init (GimpContainerBoxClass * klass)
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
name|g_object_class_override_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_CONTAINER_VIEW_PROP_CONTAINER
argument_list|,
literal|"container"
argument_list|)
expr_stmt|;
name|g_object_class_override_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_CONTAINER_VIEW_PROP_CONTEXT
argument_list|,
literal|"context"
argument_list|)
expr_stmt|;
name|g_object_class_override_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_CONTAINER_VIEW_PROP_REORDERABLE
argument_list|,
literal|"reorderable"
argument_list|)
expr_stmt|;
name|g_object_class_override_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_CONTAINER_VIEW_PROP_PREVIEW_SIZE
argument_list|,
literal|"preview-size"
argument_list|)
expr_stmt|;
name|g_object_class_override_property
argument_list|(
name|object_class
argument_list|,
name|GIMP_CONTAINER_VIEW_PROP_PREVIEW_BORDER_WIDTH
argument_list|,
literal|"preview-border-width"
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
name|GTK_WIDGET_UNSET_FLAGS
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|box
operator|->
name|scrolled_win
argument_list|)
operator|->
name|vscrollbar
argument_list|,
name|GTK_CAN_FOCUS
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
DECL|function|gimp_container_box_view_iface_init (GimpContainerViewInterface * view_iface)
name|gimp_container_box_view_iface_init
parameter_list|(
name|GimpContainerViewInterface
modifier|*
name|view_iface
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_box_docked_iface_init (GimpDockedInterface * docked_iface)
name|gimp_container_box_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|docked_iface
parameter_list|)
block|{
name|docked_iface
operator|->
name|get_preview
operator|=
name|gimp_container_box_get_preview
expr_stmt|;
name|docked_iface
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
name|GtkRequisition
name|req
decl_stmt|;
name|gint
name|preview_size
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
name|preview_size
operator|=
name|gimp_container_view_get_preview_size
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
name|preview_size
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
name|preview_size
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
literal|"scrollbar_spacing"
argument_list|,
operator|&
name|scrollbar_width
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_size_request
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|box
operator|->
name|scrolled_win
argument_list|)
operator|->
name|vscrollbar
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
name|box
operator|->
name|scrolled_win
operator|->
name|style
operator|->
name|xthickness
operator|*
literal|2
operator|+
name|scrollbar_width
expr_stmt|;
name|border_y
operator|=
name|box
operator|->
name|scrolled_win
operator|->
name|style
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
name|GdkScreen
modifier|*
name|screen
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
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_icon_size_lookup_for_settings
argument_list|(
name|gtk_settings_get_for_screen
argument_list|(
name|screen
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
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|prop_name
argument_list|,
literal|"tool"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|prop_name
argument_list|,
literal|"template"
argument_list|)
condition|)
name|border_width
operator|=
literal|0
expr_stmt|;
name|preview
operator|=
name|gimp_prop_preview_new
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
name|prop_name
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|GIMP_PREVIEW
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
name|gimp_preview_renderer_set_size_full
argument_list|(
name|GIMP_PREVIEW
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

