begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewablebutton.c  * Copyright (C) 2003-2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerpopup.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewablebutton.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon290ead400103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_POPUP_VIEW_TYPE
name|PROP_POPUP_VIEW_TYPE
block|,
DECL|enumerator|PROP_POPUP_VIEW_SIZE
name|PROP_POPUP_VIEW_SIZE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_viewable_button_finalize
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
name|gimp_viewable_button_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_viewable_button_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_viewable_button_scroll_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventScroll
modifier|*
name|sevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_viewable_button_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_viewable_button_popup_closed
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|,
name|GimpViewableButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpViewableButton,gimp_viewable_button,GIMP_TYPE_BUTTON)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpViewableButton
argument_list|,
argument|gimp_viewable_button
argument_list|,
argument|GIMP_TYPE_BUTTON
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_viewable_button_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_viewable_button_class_init
parameter_list|(
name|GimpViewableButtonClass
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
name|GtkButtonClass
modifier|*
name|button_class
init|=
name|GTK_BUTTON_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_viewable_button_finalize
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_viewable_button_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_viewable_button_set_property
expr_stmt|;
name|widget_class
operator|->
name|scroll_event
operator|=
name|gimp_viewable_button_scroll_event
expr_stmt|;
name|button_class
operator|->
name|clicked
operator|=
name|gimp_viewable_button_clicked
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_POPUP_VIEW_TYPE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"popup-view-type"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_VIEW_TYPE
argument_list|,
name|GIMP_VIEW_TYPE_LIST
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_POPUP_VIEW_SIZE
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"popup-view-size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_VIEW_SIZE_TINY
argument_list|,
name|GIMP_VIEW_SIZE_GIGANTIC
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_viewable_button_init (GimpViewableButton * button)
name|gimp_viewable_button_init
parameter_list|(
name|GimpViewableButton
modifier|*
name|button
parameter_list|)
block|{
name|button
operator|->
name|popup_view_type
operator|=
name|GIMP_VIEW_TYPE_LIST
expr_stmt|;
name|button
operator|->
name|popup_view_size
operator|=
name|GIMP_VIEW_SIZE_SMALL
expr_stmt|;
name|button
operator|->
name|button_view_size
operator|=
name|GIMP_VIEW_SIZE_SMALL
expr_stmt|;
name|button
operator|->
name|view_border_width
operator|=
literal|1
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_viewable_button_finalize (GObject * object)
name|gimp_viewable_button_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpViewableButton
modifier|*
name|button
init|=
name|GIMP_VIEWABLE_BUTTON
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|button
operator|->
name|dialog_identifier
condition|)
block|{
name|g_free
argument_list|(
name|button
operator|->
name|dialog_identifier
argument_list|)
expr_stmt|;
name|button
operator|->
name|dialog_identifier
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|button
operator|->
name|dialog_stock_id
condition|)
block|{
name|g_free
argument_list|(
name|button
operator|->
name|dialog_stock_id
argument_list|)
expr_stmt|;
name|button
operator|->
name|dialog_stock_id
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|button
operator|->
name|dialog_tooltip
condition|)
block|{
name|g_free
argument_list|(
name|button
operator|->
name|dialog_tooltip
argument_list|)
expr_stmt|;
name|button
operator|->
name|dialog_tooltip
operator|=
name|NULL
expr_stmt|;
block|}
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
DECL|function|gimp_viewable_button_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_viewable_button_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpViewableButton
modifier|*
name|button
init|=
name|GIMP_VIEWABLE_BUTTON
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_POPUP_VIEW_TYPE
case|:
name|gimp_viewable_button_set_view_type
argument_list|(
name|button
argument_list|,
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_POPUP_VIEW_SIZE
case|:
name|gimp_viewable_button_set_view_size
argument_list|(
name|button
argument_list|,
name|g_value_get_int
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_viewable_button_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_viewable_button_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpViewableButton
modifier|*
name|button
init|=
name|GIMP_VIEWABLE_BUTTON
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_POPUP_VIEW_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|button
operator|->
name|popup_view_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_POPUP_VIEW_SIZE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|button
operator|->
name|popup_view_size
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_viewable_button_scroll_event (GtkWidget * widget,GdkEventScroll * sevent)
name|gimp_viewable_button_scroll_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventScroll
modifier|*
name|sevent
parameter_list|)
block|{
name|GimpViewableButton
modifier|*
name|button
init|=
name|GIMP_VIEWABLE_BUTTON
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpObject
modifier|*
name|object
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|object
operator|=
name|gimp_context_get_by_type
argument_list|(
name|button
operator|->
name|context
argument_list|,
name|button
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
name|index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|button
operator|->
name|container
argument_list|,
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|!=
operator|-
literal|1
condition|)
block|{
name|gint
name|n_children
decl_stmt|;
name|gint
name|new_index
init|=
name|index
decl_stmt|;
name|n_children
operator|=
name|gimp_container_num_children
argument_list|(
name|button
operator|->
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|sevent
operator|->
name|direction
operator|==
name|GDK_SCROLL_UP
condition|)
block|{
if|if
condition|(
name|index
operator|>
literal|0
condition|)
name|new_index
operator|--
expr_stmt|;
else|else
name|new_index
operator|=
name|n_children
operator|-
literal|1
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|sevent
operator|->
name|direction
operator|==
name|GDK_SCROLL_DOWN
condition|)
block|{
if|if
condition|(
name|index
operator|==
operator|(
name|n_children
operator|-
literal|1
operator|)
condition|)
name|new_index
operator|=
literal|0
expr_stmt|;
else|else
name|new_index
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|new_index
operator|!=
name|index
condition|)
block|{
name|object
operator|=
name|gimp_container_get_child_by_index
argument_list|(
name|button
operator|->
name|container
argument_list|,
name|new_index
argument_list|)
expr_stmt|;
if|if
condition|(
name|object
condition|)
name|gimp_context_set_by_type
argument_list|(
name|button
operator|->
name|context
argument_list|,
name|button
operator|->
name|container
operator|->
name|children_type
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_viewable_button_clicked (GtkButton * button)
name|gimp_viewable_button_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|)
block|{
name|GimpViewableButton
modifier|*
name|viewable_button
init|=
name|GIMP_VIEWABLE_BUTTON
argument_list|(
name|button
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|popup
decl_stmt|;
name|popup
operator|=
name|gimp_container_popup_new
argument_list|(
name|viewable_button
operator|->
name|container
argument_list|,
name|viewable_button
operator|->
name|context
argument_list|,
name|viewable_button
operator|->
name|popup_view_type
argument_list|,
name|viewable_button
operator|->
name|button_view_size
argument_list|,
name|viewable_button
operator|->
name|popup_view_size
argument_list|,
name|viewable_button
operator|->
name|view_border_width
argument_list|,
name|viewable_button
operator|->
name|dialog_factory
argument_list|,
name|viewable_button
operator|->
name|dialog_identifier
argument_list|,
name|viewable_button
operator|->
name|dialog_stock_id
argument_list|,
name|viewable_button
operator|->
name|dialog_tooltip
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|popup
argument_list|,
literal|"cancel"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_viewable_button_popup_closed
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|popup
argument_list|,
literal|"confirm"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_viewable_button_popup_closed
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gimp_container_popup_show
argument_list|(
name|GIMP_CONTAINER_POPUP
argument_list|(
name|popup
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_viewable_button_popup_closed (GimpContainerPopup * popup,GimpViewableButton * button)
name|gimp_viewable_button_popup_closed
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|,
name|GimpViewableButton
modifier|*
name|button
parameter_list|)
block|{
name|gimp_viewable_button_set_view_type
argument_list|(
name|button
argument_list|,
name|gimp_container_popup_get_view_type
argument_list|(
name|popup
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_viewable_button_set_view_size
argument_list|(
name|button
argument_list|,
name|gimp_container_popup_get_view_size
argument_list|(
name|popup
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_viewable_button_new (GimpContainer * container,GimpContext * context,GimpViewType view_type,gint button_view_size,gint view_size,gint view_border_width,GimpDialogFactory * dialog_factory,const gchar * dialog_identifier,const gchar * dialog_stock_id,const gchar * dialog_tooltip)
name|gimp_viewable_button_new
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
name|button_view_size
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
name|dialog_stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_tooltip
parameter_list|)
block|{
name|GimpViewableButton
modifier|*
name|button
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|prop_name
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
name|view_size
operator|>
literal|0
operator|&&
name|view_size
operator|<=
name|GIMP_VIEWABLE_MAX_BUTTON_SIZE
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
name|dialog_stock_id
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
name|button
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_VIEWABLE_BUTTON
argument_list|,
literal|"popup-view-type"
argument_list|,
name|view_type
argument_list|,
literal|"popup-view-size"
argument_list|,
name|view_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|->
name|container
operator|=
name|container
expr_stmt|;
name|button
operator|->
name|context
operator|=
name|context
expr_stmt|;
name|button
operator|->
name|button_view_size
operator|=
name|button_view_size
expr_stmt|;
name|button
operator|->
name|view_border_width
operator|=
name|view_border_width
expr_stmt|;
if|if
condition|(
name|dialog_factory
condition|)
block|{
name|button
operator|->
name|dialog_factory
operator|=
name|dialog_factory
expr_stmt|;
name|button
operator|->
name|dialog_identifier
operator|=
name|g_strdup
argument_list|(
name|dialog_identifier
argument_list|)
expr_stmt|;
name|button
operator|->
name|dialog_stock_id
operator|=
name|g_strdup
argument_list|(
name|dialog_stock_id
argument_list|)
expr_stmt|;
name|button
operator|->
name|dialog_tooltip
operator|=
name|g_strdup
argument_list|(
name|dialog_tooltip
argument_list|)
expr_stmt|;
block|}
name|prop_name
operator|=
name|gimp_context_type_to_prop_name
argument_list|(
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
name|button
operator|->
name|view
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
name|button
operator|->
name|button_view_size
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|button
operator|->
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
operator|->
name|view
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpViewType
DECL|function|gimp_viewable_button_get_view_type (GimpViewableButton * button)
name|gimp_viewable_button_get_view_type
parameter_list|(
name|GimpViewableButton
modifier|*
name|button
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|GIMP_VIEW_TYPE_LIST
argument_list|)
expr_stmt|;
return|return
name|button
operator|->
name|popup_view_type
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_viewable_button_set_view_type (GimpViewableButton * button,GimpViewType view_type)
name|gimp_viewable_button_set_view_type
parameter_list|(
name|GimpViewableButton
modifier|*
name|button
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|view_type
operator|!=
name|button
operator|->
name|popup_view_type
condition|)
block|{
name|button
operator|->
name|popup_view_type
operator|=
name|view_type
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"popup-view-type"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gint
DECL|function|gimp_viewable_button_get_view_size (GimpViewableButton * button)
name|gimp_viewable_button_get_view_size
parameter_list|(
name|GimpViewableButton
modifier|*
name|button
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|)
expr_stmt|;
return|return
name|button
operator|->
name|popup_view_size
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_viewable_button_set_view_size (GimpViewableButton * button,gint view_size)
name|gimp_viewable_button_set_view_size
parameter_list|(
name|GimpViewableButton
modifier|*
name|button
parameter_list|,
name|gint
name|view_size
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|view_size
operator|!=
name|button
operator|->
name|popup_view_size
condition|)
block|{
name|button
operator|->
name|popup_view_size
operator|=
name|view_size
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"popup-view-size"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

