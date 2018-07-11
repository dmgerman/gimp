begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainerpopup.c  * Copyright (C) 2003-2014 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<gdk/gdkkeysyms.h>
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
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerbox.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainereditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerpopup.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainertreeview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpwindowstrategy.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_container_popup_finalize
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
name|gimp_container_popup_confirm
parameter_list|(
name|GimpPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_popup_create_view
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_popup_smaller_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_popup_larger_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_popup_view_type_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_container_popup_dialog_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpContainerPopup,gimp_container_popup,GIMP_TYPE_POPUP)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpContainerPopup
argument_list|,
argument|gimp_container_popup
argument_list|,
argument|GIMP_TYPE_POPUP
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_container_popup_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_container_popup_class_init
parameter_list|(
name|GimpContainerPopupClass
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
name|GimpPopupClass
modifier|*
name|popup_class
init|=
name|GIMP_POPUP_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_container_popup_finalize
expr_stmt|;
name|popup_class
operator|->
name|confirm
operator|=
name|gimp_container_popup_confirm
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_popup_init (GimpContainerPopup * popup)
name|gimp_container_popup_init
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
block|{
name|popup
operator|->
name|view_type
operator|=
name|GIMP_VIEW_TYPE_LIST
expr_stmt|;
name|popup
operator|->
name|default_view_size
operator|=
name|GIMP_VIEW_SIZE_SMALL
expr_stmt|;
name|popup
operator|->
name|view_size
operator|=
name|GIMP_VIEW_SIZE_SMALL
expr_stmt|;
name|popup
operator|->
name|view_border_width
operator|=
literal|1
expr_stmt|;
name|popup
operator|->
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|popup
operator|->
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|popup
argument_list|)
argument_list|,
name|popup
operator|->
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|popup
operator|->
name|frame
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_popup_finalize (GObject * object)
name|gimp_container_popup_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpContainerPopup
modifier|*
name|popup
init|=
name|GIMP_CONTAINER_POPUP
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|popup
operator|->
name|context
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|popup
operator|->
name|dialog_identifier
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|popup
operator|->
name|dialog_icon_name
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|popup
operator|->
name|dialog_tooltip
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
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
DECL|function|gimp_container_popup_confirm (GimpPopup * popup)
name|gimp_container_popup_confirm
parameter_list|(
name|GimpPopup
modifier|*
name|popup
parameter_list|)
block|{
name|GimpContainerPopup
modifier|*
name|c_popup
init|=
name|GIMP_CONTAINER_POPUP
argument_list|(
name|popup
argument_list|)
decl_stmt|;
name|GimpObject
modifier|*
name|object
decl_stmt|;
name|object
operator|=
name|gimp_context_get_by_type
argument_list|(
name|c_popup
operator|->
name|context
argument_list|,
name|gimp_container_get_children_type
argument_list|(
name|c_popup
operator|->
name|container
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_context_set_by_type
argument_list|(
name|c_popup
operator|->
name|orig_context
argument_list|,
name|gimp_container_get_children_type
argument_list|(
name|c_popup
operator|->
name|container
argument_list|)
argument_list|,
name|object
argument_list|)
expr_stmt|;
name|GIMP_POPUP_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|confirm
argument_list|(
name|popup
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_popup_context_changed (GimpContext * context,GimpViewable * viewable,GimpContainerPopup * popup)
name|gimp_container_popup_context_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
block|{
name|GdkEvent
modifier|*
name|current_event
decl_stmt|;
name|gboolean
name|confirm
init|=
name|FALSE
decl_stmt|;
name|current_event
operator|=
name|gtk_get_current_event
argument_list|()
expr_stmt|;
if|if
condition|(
name|current_event
condition|)
block|{
if|if
condition|(
operator|(
operator|(
name|GdkEventAny
operator|*
operator|)
name|current_event
operator|)
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
operator|||
operator|(
operator|(
name|GdkEventAny
operator|*
operator|)
name|current_event
operator|)
operator|->
name|type
operator|==
name|GDK_BUTTON_RELEASE
condition|)
name|confirm
operator|=
name|TRUE
expr_stmt|;
name|gdk_event_free
argument_list|(
name|current_event
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|confirm
condition|)
name|g_signal_emit_by_name
argument_list|(
name|popup
argument_list|,
literal|"confirm"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_container_popup_new (GimpContainer * container,GimpContext * context,GimpViewType view_type,gint default_view_size,gint view_size,gint view_border_width,GimpDialogFactory * dialog_factory,const gchar * dialog_identifier,const gchar * dialog_icon_name,const gchar * dialog_tooltip)
name|gimp_container_popup_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|,
name|gint
name|default_view_size
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|,
name|GimpDialogFactory
modifier|*
name|dialog_factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_tooltip
parameter_list|)
block|{
name|GimpContainerPopup
modifier|*
name|popup
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
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
name|default_view_size
operator|>
literal|0
operator|&&
name|default_view_size
operator|<=
name|GIMP_VIEWABLE_MAX_POPUP_SIZE
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
name|GIMP_VIEWABLE_MAX_POPUP_SIZE
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
name|g_return_val_if_fail
argument_list|(
name|dialog_factory
operator|==
name|NULL
operator|||
name|GIMP_IS_DIALOG_FACTORY
argument_list|(
name|dialog_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog_factory
condition|)
block|{
name|g_return_val_if_fail
argument_list|(
name|dialog_identifier
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dialog_icon_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dialog_tooltip
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|popup
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CONTAINER_POPUP
argument_list|,
literal|"type"
argument_list|,
name|GTK_WINDOW_POPUP
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|popup
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|popup
operator|->
name|container
operator|=
name|container
expr_stmt|;
name|popup
operator|->
name|orig_context
operator|=
name|context
expr_stmt|;
name|popup
operator|->
name|context
operator|=
name|gimp_context_new
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
literal|"popup"
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|popup
operator|->
name|view_type
operator|=
name|view_type
expr_stmt|;
name|popup
operator|->
name|default_view_size
operator|=
name|default_view_size
expr_stmt|;
name|popup
operator|->
name|view_size
operator|=
name|view_size
expr_stmt|;
name|popup
operator|->
name|view_border_width
operator|=
name|view_border_width
expr_stmt|;
name|g_signal_connect
argument_list|(
name|popup
operator|->
name|context
argument_list|,
name|gimp_context_type_to_signal_name
argument_list|(
name|gimp_container_get_children_type
argument_list|(
name|container
argument_list|)
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_popup_context_changed
argument_list|)
argument_list|,
name|popup
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog_factory
condition|)
block|{
name|popup
operator|->
name|dialog_factory
operator|=
name|dialog_factory
expr_stmt|;
name|popup
operator|->
name|dialog_identifier
operator|=
name|g_strdup
argument_list|(
name|dialog_identifier
argument_list|)
expr_stmt|;
name|popup
operator|->
name|dialog_icon_name
operator|=
name|g_strdup
argument_list|(
name|dialog_icon_name
argument_list|)
expr_stmt|;
name|popup
operator|->
name|dialog_tooltip
operator|=
name|g_strdup
argument_list|(
name|dialog_tooltip
argument_list|)
expr_stmt|;
block|}
name|gimp_container_popup_create_view
argument_list|(
name|popup
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|popup
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpViewType
DECL|function|gimp_container_popup_get_view_type (GimpContainerPopup * popup)
name|gimp_container_popup_get_view_type
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_POPUP
argument_list|(
name|popup
argument_list|)
argument_list|,
name|GIMP_VIEW_TYPE_LIST
argument_list|)
expr_stmt|;
return|return
name|popup
operator|->
name|view_type
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_popup_set_view_type (GimpContainerPopup * popup,GimpViewType view_type)
name|gimp_container_popup_set_view_type
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_POPUP
argument_list|(
name|popup
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|view_type
operator|!=
name|popup
operator|->
name|view_type
condition|)
block|{
name|popup
operator|->
name|view_type
operator|=
name|view_type
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|popup
operator|->
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_popup_create_view
argument_list|(
name|popup
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gint
DECL|function|gimp_container_popup_get_view_size (GimpContainerPopup * popup)
name|gimp_container_popup_get_view_size
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_POPUP
argument_list|(
name|popup
argument_list|)
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|)
expr_stmt|;
return|return
name|popup
operator|->
name|view_size
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_container_popup_set_view_size (GimpContainerPopup * popup,gint view_size)
name|gimp_container_popup_set_view_size
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|,
name|gint
name|view_size
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|scrolled_win
decl_stmt|;
name|GtkWidget
modifier|*
name|viewport
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_POPUP
argument_list|(
name|popup
argument_list|)
argument_list|)
expr_stmt|;
name|scrolled_win
operator|=
name|GIMP_CONTAINER_BOX
argument_list|(
name|popup
operator|->
name|editor
operator|->
name|view
argument_list|)
operator|->
name|scrolled_win
expr_stmt|;
name|viewport
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|scrolled_win
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|viewport
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|view_size
operator|=
name|CLAMP
argument_list|(
name|view_size
argument_list|,
name|GIMP_VIEW_SIZE_TINY
argument_list|,
name|MIN
argument_list|(
name|GIMP_VIEW_SIZE_GIGANTIC
argument_list|,
name|allocation
operator|.
name|width
operator|-
literal|2
operator|*
name|popup
operator|->
name|view_border_width
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|view_size
operator|!=
name|popup
operator|->
name|view_size
condition|)
block|{
name|popup
operator|->
name|view_size
operator|=
name|view_size
expr_stmt|;
name|gimp_container_view_set_view_size
argument_list|(
name|popup
operator|->
name|editor
operator|->
name|view
argument_list|,
name|popup
operator|->
name|view_size
argument_list|,
name|popup
operator|->
name|view_border_width
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_container_popup_create_view (GimpContainerPopup * popup)
name|gimp_container_popup_create_view
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|editor
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|gint
name|rows
decl_stmt|;
name|gint
name|columns
decl_stmt|;
name|popup
operator|->
name|editor
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CONTAINER_EDITOR
argument_list|,
literal|"view-type"
argument_list|,
name|popup
operator|->
name|view_type
argument_list|,
literal|"container"
argument_list|,
name|popup
operator|->
name|container
argument_list|,
literal|"context"
argument_list|,
name|popup
operator|->
name|context
argument_list|,
literal|"view-size"
argument_list|,
name|popup
operator|->
name|view_size
argument_list|,
literal|"view-border-width"
argument_list|,
name|popup
operator|->
name|view_border_width
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_view_set_reorderable
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|popup
operator|->
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|popup
operator|->
name|view_type
operator|==
name|GIMP_VIEW_TYPE_LIST
condition|)
block|{
name|GtkWidget
modifier|*
name|search_entry
decl_stmt|;
name|search_entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|popup
operator|->
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|search_entry
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_tree_view_set_search_entry
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|popup
operator|->
name|editor
operator|->
name|view
argument_list|)
argument_list|)
operator|->
name|view
argument_list|)
argument_list|,
name|GTK_ENTRY
argument_list|(
name|search_entry
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|search_entry
argument_list|)
expr_stmt|;
block|}
comment|/* lame workaround for bug #761998 */
if|if
condition|(
name|popup
operator|->
name|default_view_size
operator|>=
name|GIMP_VIEW_SIZE_LARGE
condition|)
block|{
name|rows
operator|=
literal|6
expr_stmt|;
name|columns
operator|=
literal|6
expr_stmt|;
block|}
else|else
block|{
name|rows
operator|=
literal|10
expr_stmt|;
name|columns
operator|=
literal|6
expr_stmt|;
block|}
name|gimp_container_box_set_size_request
argument_list|(
name|GIMP_CONTAINER_BOX
argument_list|(
name|popup
operator|->
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|columns
operator|*
operator|(
name|popup
operator|->
name|default_view_size
operator|+
literal|2
operator|*
name|popup
operator|->
name|view_border_width
operator|)
argument_list|,
name|rows
operator|*
operator|(
name|popup
operator|->
name|default_view_size
operator|+
literal|2
operator|*
name|popup
operator|->
name|view_border_width
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_EDITOR
argument_list|(
name|popup
operator|->
name|editor
operator|->
name|view
argument_list|)
condition|)
name|gimp_editor_set_show_name
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|popup
operator|->
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|popup
operator|->
name|frame
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|popup
operator|->
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|popup
operator|->
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|editor
operator|=
name|GIMP_EDITOR
argument_list|(
name|popup
operator|->
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|gimp_editor_add_button
argument_list|(
name|editor
argument_list|,
literal|"zoom-out"
argument_list|,
name|_
argument_list|(
literal|"Smaller Previews"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_popup_smaller_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|popup
argument_list|)
expr_stmt|;
name|gimp_editor_add_button
argument_list|(
name|editor
argument_list|,
literal|"zoom-in"
argument_list|,
name|_
argument_list|(
literal|"Larger Previews"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_popup_larger_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|popup
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_editor_add_icon_box
argument_list|(
name|editor
argument_list|,
name|GIMP_TYPE_VIEW_TYPE
argument_list|,
literal|"gimp"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_popup_view_type_toggled
argument_list|)
argument_list|,
name|popup
argument_list|)
expr_stmt|;
name|gimp_int_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|popup
operator|->
name|view_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|popup
operator|->
name|dialog_factory
condition|)
name|gimp_editor_add_button
argument_list|(
name|editor
argument_list|,
name|popup
operator|->
name|dialog_icon_name
argument_list|,
name|popup
operator|->
name|dialog_tooltip
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_container_popup_dialog_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|popup
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|GTK_WIDGET
argument_list|(
name|popup
operator|->
name|editor
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_popup_smaller_clicked (GtkWidget * button,GimpContainerPopup * popup)
name|gimp_container_popup_smaller_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
block|{
name|gint
name|view_size
decl_stmt|;
name|view_size
operator|=
name|gimp_container_view_get_view_size
argument_list|(
name|popup
operator|->
name|editor
operator|->
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_popup_set_view_size
argument_list|(
name|popup
argument_list|,
name|view_size
operator|*
literal|0.8
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_popup_larger_clicked (GtkWidget * button,GimpContainerPopup * popup)
name|gimp_container_popup_larger_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
block|{
name|gint
name|view_size
decl_stmt|;
name|view_size
operator|=
name|gimp_container_view_get_view_size
argument_list|(
name|popup
operator|->
name|editor
operator|->
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_popup_set_view_size
argument_list|(
name|popup
argument_list|,
name|view_size
operator|*
literal|1.2
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_popup_view_type_toggled (GtkWidget * button,GimpContainerPopup * popup)
name|gimp_container_popup_view_type_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
block|{
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
condition|)
block|{
name|GimpViewType
name|view_type
decl_stmt|;
name|view_type
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_popup_set_view_type
argument_list|(
name|popup
argument_list|,
name|view_type
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_container_popup_dialog_clicked (GtkWidget * button,GimpContainerPopup * popup)
name|gimp_container_popup_dialog_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
block|{
name|gimp_window_strategy_show_dockable_dialog
argument_list|(
name|GIMP_WINDOW_STRATEGY
argument_list|(
name|gimp_get_window_strategy
argument_list|(
name|popup
operator|->
name|context
operator|->
name|gimp
argument_list|)
argument_list|)
argument_list|,
name|popup
operator|->
name|context
operator|->
name|gimp
argument_list|,
name|popup
operator|->
name|dialog_factory
argument_list|,
name|gimp_widget_get_monitor
argument_list|(
name|button
argument_list|)
argument_list|,
name|popup
operator|->
name|dialog_identifier
argument_list|)
expr_stmt|;
name|g_signal_emit_by_name
argument_list|(
name|popup
argument_list|,
literal|"confirm"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

