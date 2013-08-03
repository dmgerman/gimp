begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoverlaydialog.c  * Copyright (C) 2009-2010  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpoverlaydialog.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2746340e0103
block|{
DECL|enumerator|RESPONSE
name|RESPONSE
block|,
DECL|enumerator|CLOSE
name|CLOSE
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|ResponseData
typedef|typedef
name|struct
name|_ResponseData
name|ResponseData
typedef|;
end_typedef

begin_struct
DECL|struct|_ResponseData
struct|struct
name|_ResponseData
block|{
DECL|member|response_id
name|gint
name|response_id
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_overlay_dialog_dispose
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
name|gimp_overlay_dialog_size_request
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkRequisition
modifier|*
name|requisition
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_overlay_dialog_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_overlay_dialog_forall
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|,
name|gboolean
name|include_internals
parameter_list|,
name|GtkCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_overlay_dialog_close
parameter_list|(
name|GimpOverlayDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ResponseData
modifier|*
name|get_response_data
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|create
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOverlayDialog
argument_list|,
argument|gimp_overlay_dialog
argument_list|,
argument|GIMP_TYPE_OVERLAY_FRAME
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|guint
name|signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_overlay_dialog_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_dialog_class_init (GimpOverlayDialogClass * klass)
name|gimp_overlay_dialog_class_init
parameter_list|(
name|GimpOverlayDialogClass
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
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkContainerClass
modifier|*
name|container_class
init|=
name|GTK_CONTAINER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_overlay_dialog_dispose
expr_stmt|;
name|widget_class
operator|->
name|size_request
operator|=
name|gimp_overlay_dialog_size_request
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_overlay_dialog_size_allocate
expr_stmt|;
name|container_class
operator|->
name|forall
operator|=
name|gimp_overlay_dialog_forall
expr_stmt|;
name|klass
operator|->
name|close
operator|=
name|gimp_overlay_dialog_close
expr_stmt|;
name|signals
index|[
name|RESPONSE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"response"
argument_list|,
name|G_OBJECT_CLASS_TYPE
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpOverlayDialogClass
argument_list|,
name|response
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__INT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|signals
index|[
name|CLOSE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"close"
argument_list|,
name|G_OBJECT_CLASS_TYPE
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
operator||
name|G_SIGNAL_ACTION
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpOverlayDialogClass
argument_list|,
name|close
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|gtk_binding_set_by_class
argument_list|(
name|klass
argument_list|)
argument_list|,
name|GDK_KEY_Escape
argument_list|,
literal|0
argument_list|,
literal|"close"
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_dialog_init (GimpOverlayDialog * dialog)
name|gimp_overlay_dialog_init
parameter_list|(
name|GimpOverlayDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|dialog
operator|->
name|action_area
operator|=
name|gtk_button_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
name|gtk_button_box_set_layout
argument_list|(
name|GTK_BUTTON_BOX
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|)
argument_list|,
name|GTK_BUTTONBOX_END
argument_list|)
expr_stmt|;
name|gtk_widget_set_parent
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_dialog_dispose (GObject * object)
name|gimp_overlay_dialog_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpOverlayDialog
modifier|*
name|dialog
init|=
name|GIMP_OVERLAY_DIALOG
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|dialog
operator|->
name|action_area
condition|)
block|{
name|gtk_widget_unparent
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|action_area
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_dialog_size_request (GtkWidget * widget,GtkRequisition * requisition)
name|gimp_overlay_dialog_size_request
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkRequisition
modifier|*
name|requisition
parameter_list|)
block|{
name|GtkContainer
modifier|*
name|container
init|=
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpOverlayDialog
modifier|*
name|dialog
init|=
name|GIMP_OVERLAY_DIALOG
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|child
init|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|GtkRequisition
name|child_requisition
decl_stmt|;
name|GtkRequisition
name|action_requisition
decl_stmt|;
name|gint
name|border_width
decl_stmt|;
name|border_width
operator|=
name|gtk_container_get_border_width
argument_list|(
name|container
argument_list|)
expr_stmt|;
name|requisition
operator|->
name|width
operator|=
name|border_width
operator|*
literal|2
expr_stmt|;
name|requisition
operator|->
name|height
operator|=
name|border_width
operator|*
literal|2
expr_stmt|;
if|if
condition|(
name|child
operator|&&
name|gtk_widget_get_visible
argument_list|(
name|child
argument_list|)
condition|)
block|{
name|gtk_widget_size_request
argument_list|(
name|child
argument_list|,
operator|&
name|child_requisition
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|child_requisition
operator|.
name|width
operator|=
literal|0
expr_stmt|;
name|child_requisition
operator|.
name|height
operator|=
literal|0
expr_stmt|;
block|}
name|gtk_widget_size_request
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|,
operator|&
name|action_requisition
argument_list|)
expr_stmt|;
name|requisition
operator|->
name|width
operator|+=
name|MAX
argument_list|(
name|child_requisition
operator|.
name|width
argument_list|,
name|action_requisition
operator|.
name|width
argument_list|)
expr_stmt|;
name|requisition
operator|->
name|height
operator|+=
operator|(
name|child_requisition
operator|.
name|height
operator|+
name|border_width
operator|+
name|action_requisition
operator|.
name|height
operator|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_dialog_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gimp_overlay_dialog_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
block|{
name|GtkContainer
modifier|*
name|container
init|=
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpOverlayDialog
modifier|*
name|dialog
init|=
name|GIMP_OVERLAY_DIALOG
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|child
init|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|GtkRequisition
name|action_requisition
decl_stmt|;
name|GtkAllocation
name|child_allocation
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|GtkAllocation
name|action_allocation
decl_stmt|;
name|gint
name|border_width
decl_stmt|;
name|gtk_widget_set_allocation
argument_list|(
name|widget
argument_list|,
name|allocation
argument_list|)
expr_stmt|;
name|border_width
operator|=
name|gtk_container_get_border_width
argument_list|(
name|container
argument_list|)
expr_stmt|;
name|gtk_widget_size_request
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|,
operator|&
name|action_requisition
argument_list|)
expr_stmt|;
if|if
condition|(
name|child
operator|&&
name|gtk_widget_get_visible
argument_list|(
name|child
argument_list|)
condition|)
block|{
name|child_allocation
operator|.
name|x
operator|=
name|allocation
operator|->
name|x
operator|+
name|border_width
expr_stmt|;
name|child_allocation
operator|.
name|y
operator|=
name|allocation
operator|->
name|y
operator|+
name|border_width
expr_stmt|;
name|child_allocation
operator|.
name|width
operator|=
name|MAX
argument_list|(
name|allocation
operator|->
name|width
operator|-
literal|2
operator|*
name|border_width
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|child_allocation
operator|.
name|height
operator|=
name|MAX
argument_list|(
name|allocation
operator|->
name|height
operator|-
literal|3
operator|*
name|border_width
operator|-
name|action_requisition
operator|.
name|height
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_size_allocate
argument_list|(
name|child
argument_list|,
operator|&
name|child_allocation
argument_list|)
expr_stmt|;
block|}
name|action_allocation
operator|.
name|x
operator|=
name|allocation
operator|->
name|x
operator|+
name|border_width
expr_stmt|;
name|action_allocation
operator|.
name|y
operator|=
operator|(
name|child_allocation
operator|.
name|y
operator|+
name|child_allocation
operator|.
name|height
operator|+
name|border_width
operator|)
expr_stmt|;
name|action_allocation
operator|.
name|width
operator|=
name|MAX
argument_list|(
name|allocation
operator|->
name|width
operator|-
literal|2
operator|*
name|border_width
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|action_allocation
operator|.
name|height
operator|=
name|MAX
argument_list|(
name|action_requisition
operator|.
name|height
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_size_allocate
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|,
operator|&
name|action_allocation
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_dialog_forall (GtkContainer * container,gboolean include_internals,GtkCallback callback,gpointer callback_data)
name|gimp_overlay_dialog_forall
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|,
name|gboolean
name|include_internals
parameter_list|,
name|GtkCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GTK_CONTAINER_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|forall
argument_list|(
name|container
argument_list|,
name|include_internals
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|include_internals
condition|)
block|{
name|GimpOverlayDialog
modifier|*
name|dialog
init|=
name|GIMP_OVERLAY_DIALOG
argument_list|(
name|container
argument_list|)
decl_stmt|;
if|if
condition|(
name|dialog
operator|->
name|action_area
condition|)
call|(
modifier|*
name|callback
call|)
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_overlay_dialog_close (GimpOverlayDialog * dialog)
name|gimp_overlay_dialog_close
parameter_list|(
name|GimpOverlayDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GList
modifier|*
name|children
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|ResponseData
modifier|*
name|ad
init|=
name|NULL
decl_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|children
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
name|GtkWidget
modifier|*
name|child
init|=
name|list
operator|->
name|data
decl_stmt|;
name|ad
operator|=
name|get_response_data
argument_list|(
name|child
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|ad
operator|->
name|response_id
operator|==
name|GTK_RESPONSE_CLOSE
operator|||
name|ad
operator|->
name|response_id
operator|==
name|GTK_RESPONSE_CANCEL
condition|)
block|{
break|break;
block|}
name|ad
operator|=
name|NULL
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
if|if
condition|(
name|ad
condition|)
name|gimp_overlay_dialog_response
argument_list|(
name|dialog
argument_list|,
name|ad
operator|->
name|response_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_overlay_dialog_new (GimpToolInfo * tool_info,const gchar * desc,...)
name|gimp_overlay_dialog_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
comment|/* const gchar *stock_id; */
name|va_list
name|args
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_INFO
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* stock_id = gimp_viewable_get_stock_id (GIMP_VIEWABLE (tool_info)); */
name|dialog
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_OVERLAY_DIALOG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|gimp_overlay_dialog_add_buttons_valist
argument_list|(
name|GIMP_OVERLAY_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_dialog_response (GimpOverlayDialog * dialog,gint response_id)
name|gimp_overlay_dialog_response
parameter_list|(
name|GimpOverlayDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|dialog
argument_list|,
name|signals
index|[
name|RESPONSE
index|]
argument_list|,
literal|0
argument_list|,
name|response_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_dialog_add_buttons_valist (GimpOverlayDialog * dialog,va_list args)
name|gimp_overlay_dialog_add_buttons_valist
parameter_list|(
name|GimpOverlayDialog
modifier|*
name|dialog
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|button_text
decl_stmt|;
name|gint
name|response_id
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|button_text
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
operator|)
condition|)
block|{
name|response_id
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gint
argument_list|)
expr_stmt|;
name|gimp_overlay_dialog_add_button
argument_list|(
name|dialog
argument_list|,
name|button_text
argument_list|,
name|response_id
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|action_widget_activated (GtkWidget * widget,GimpOverlayDialog * dialog)
name|action_widget_activated
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpOverlayDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|ResponseData
modifier|*
name|ad
init|=
name|get_response_data
argument_list|(
name|widget
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
name|gimp_overlay_dialog_response
argument_list|(
name|dialog
argument_list|,
name|ad
operator|->
name|response_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_overlay_dialog_add_button (GimpOverlayDialog * dialog,const gchar * button_text,gint response_id)
name|gimp_overlay_dialog_add_button
parameter_list|(
name|GimpOverlayDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|button_text
parameter_list|,
name|gint
name|response_id
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|ResponseData
modifier|*
name|ad
decl_stmt|;
name|guint
name|signal_id
decl_stmt|;
name|GClosure
modifier|*
name|closure
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_OVERLAY_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|button_text
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_from_stock
argument_list|(
name|button_text
argument_list|)
expr_stmt|;
name|gtk_widget_set_can_default
argument_list|(
name|button
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|ad
operator|=
name|get_response_data
argument_list|(
name|button
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|ad
operator|->
name|response_id
operator|=
name|response_id
expr_stmt|;
name|signal_id
operator|=
name|g_signal_lookup
argument_list|(
literal|"clicked"
argument_list|,
name|GTK_TYPE_BUTTON
argument_list|)
expr_stmt|;
name|closure
operator|=
name|g_cclosure_new_object
argument_list|(
name|G_CALLBACK
argument_list|(
name|action_widget_activated
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_closure_by_id
argument_list|(
name|button
argument_list|,
name|signal_id
argument_list|,
literal|0
argument_list|,
name|closure
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_HELP
condition|)
name|gtk_button_box_set_child_secondary
argument_list|(
name|GTK_BUTTON_BOX
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|button
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_dialog_set_alternative_button_order (GimpOverlayDialog * overlay,gint n_ids,gint * ids)
name|gimp_overlay_dialog_set_alternative_button_order
parameter_list|(
name|GimpOverlayDialog
modifier|*
name|overlay
parameter_list|,
name|gint
name|n_ids
parameter_list|,
name|gint
modifier|*
name|ids
parameter_list|)
block|{
comment|/* TODO */
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_dialog_set_default_response (GimpOverlayDialog * overlay,gint response_id)
name|gimp_overlay_dialog_set_default_response
parameter_list|(
name|GimpOverlayDialog
modifier|*
name|overlay
parameter_list|,
name|gint
name|response_id
parameter_list|)
block|{
comment|/* TODO */
block|}
end_function

begin_function
name|void
DECL|function|gimp_overlay_dialog_set_response_sensitive (GimpOverlayDialog * overlay,gint response_id,gboolean sensitive)
name|gimp_overlay_dialog_set_response_sensitive
parameter_list|(
name|GimpOverlayDialog
modifier|*
name|overlay
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
block|{
comment|/* TODO */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|response_data_free (gpointer data)
name|response_data_free
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|ResponseData
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|ResponseData
modifier|*
DECL|function|get_response_data (GtkWidget * widget,gboolean create)
name|get_response_data
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|create
parameter_list|)
block|{
name|ResponseData
modifier|*
name|ad
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-overlay-dialog-response-data"
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|ad
operator|&&
name|create
condition|)
block|{
name|ad
operator|=
name|g_slice_new
argument_list|(
name|ResponseData
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-overlay-dialog-response-data"
argument_list|,
name|ad
argument_list|,
name|response_data_free
argument_list|)
expr_stmt|;
block|}
return|return
name|ad
return|;
block|}
end_function

end_unit

