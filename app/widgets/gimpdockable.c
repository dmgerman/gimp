begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockable.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockbook.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_dockable_class_init
parameter_list|(
name|GimpDockableClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockable_init
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockable_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockable_size_request
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
name|gimp_dockable_size_allocate
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
name|gimp_dockable_style_set
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

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_dockable_real_get_tab_widget
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpTabStyle
name|tab_style
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockable_real_set_context
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
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
name|GtkBinClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_dockable_get_type (void)
name|gimp_dockable_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|dockable_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|dockable_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|dockable_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpDockableClass
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
name|gimp_dockable_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpDockable
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_dockable_init
block|,       }
decl_stmt|;
name|dockable_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_BIN
argument_list|,
literal|"GimpDockable"
argument_list|,
operator|&
name|dockable_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|dockable_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_class_init (GimpDockableClass * klass)
name|gimp_dockable_class_init
parameter_list|(
name|GimpDockableClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|object_class
operator|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|widget_class
operator|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_dockable_destroy
expr_stmt|;
name|widget_class
operator|->
name|size_request
operator|=
name|gimp_dockable_size_request
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_dockable_size_allocate
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_dockable_style_set
expr_stmt|;
name|klass
operator|->
name|get_tab_widget
operator|=
name|gimp_dockable_real_get_tab_widget
expr_stmt|;
name|klass
operator|->
name|set_context
operator|=
name|gimp_dockable_real_set_context
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"content_border"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
argument_list|,
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_init (GimpDockable * dockable)
name|gimp_dockable_init
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|dockable
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
name|dockable
operator|->
name|blurb
operator|=
name|NULL
expr_stmt|;
name|dockable
operator|->
name|stock_id
operator|=
name|NULL
expr_stmt|;
name|dockable
operator|->
name|help_id
operator|=
name|NULL
expr_stmt|;
name|dockable
operator|->
name|tab_style
operator|=
name|GIMP_TAB_STYLE_ICON
expr_stmt|;
name|dockable
operator|->
name|dockbook
operator|=
name|NULL
expr_stmt|;
name|dockable
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
name|dockable
operator|->
name|get_preview_func
operator|=
name|NULL
expr_stmt|;
name|dockable
operator|->
name|get_preview_data
operator|=
name|NULL
expr_stmt|;
name|dockable
operator|->
name|set_context_func
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_destroy (GtkObject * object)
name|gimp_dockable_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|dockable
operator|=
name|GIMP_DOCKABLE
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
operator|->
name|context
condition|)
name|gimp_dockable_set_context
argument_list|(
name|dockable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
operator|->
name|name
condition|)
block|{
name|g_free
argument_list|(
name|dockable
operator|->
name|name
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|dockable
operator|->
name|blurb
condition|)
block|{
name|g_free
argument_list|(
name|dockable
operator|->
name|blurb
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|blurb
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|dockable
operator|->
name|stock_id
condition|)
block|{
name|g_free
argument_list|(
name|dockable
operator|->
name|stock_id
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|stock_id
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|dockable
operator|->
name|help_id
condition|)
block|{
name|g_free
argument_list|(
name|dockable
operator|->
name|help_id
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|help_id
operator|=
name|NULL
expr_stmt|;
block|}
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_size_request (GtkWidget * widget,GtkRequisition * requisition)
name|gimp_dockable_size_request
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
name|GtkBin
modifier|*
name|bin
init|=
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|requisition
operator|->
name|width
operator|=
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
operator|->
name|border_width
operator|*
literal|2
expr_stmt|;
name|requisition
operator|->
name|height
operator|=
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
operator|->
name|border_width
operator|*
literal|2
expr_stmt|;
if|if
condition|(
name|bin
operator|->
name|child
operator|&&
name|GTK_WIDGET_VISIBLE
argument_list|(
name|bin
operator|->
name|child
argument_list|)
condition|)
block|{
name|GtkRequisition
name|child_requisition
decl_stmt|;
name|gtk_widget_size_request
argument_list|(
name|bin
operator|->
name|child
argument_list|,
operator|&
name|child_requisition
argument_list|)
expr_stmt|;
name|requisition
operator|->
name|width
operator|+=
name|child_requisition
operator|.
name|width
expr_stmt|;
name|requisition
operator|->
name|height
operator|+=
name|child_requisition
operator|.
name|height
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gimp_dockable_size_allocate
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
name|GtkBin
modifier|*
name|bin
init|=
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|widget
operator|->
name|allocation
operator|=
operator|*
name|allocation
expr_stmt|;
if|if
condition|(
name|bin
operator|->
name|child
condition|)
block|{
name|GtkAllocation
name|child_allocation
decl_stmt|;
name|child_allocation
operator|.
name|x
operator|=
name|allocation
operator|->
name|x
expr_stmt|;
name|child_allocation
operator|.
name|y
operator|=
name|allocation
operator|->
name|y
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
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
operator|->
name|border_width
operator|*
literal|2
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
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
operator|->
name|border_width
operator|*
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_size_allocate
argument_list|(
name|bin
operator|->
name|child
argument_list|,
operator|&
name|child_allocation
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_dockable_style_set
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
name|content_border
decl_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"content_border"
argument_list|,
operator|&
name|content_border
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
argument_list|,
name|content_border
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
condition|)
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
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dockable_new (const gchar * name,const gchar * blurb,const gchar * stock_id,const gchar * help_id,GimpDockableGetPreviewFunc get_preview_func,gpointer get_preview_data,GimpDockableSetContextFunc set_context_func)
name|gimp_dockable_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpDockableGetPreviewFunc
name|get_preview_func
parameter_list|,
name|gpointer
name|get_preview_data
parameter_list|,
name|GimpDockableSetContextFunc
name|set_context_func
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|blurb
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|stock_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dockable
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DOCKABLE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|blurb
operator|=
name|g_strdup
argument_list|(
name|blurb
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|stock_id
operator|=
name|g_strdup
argument_list|(
name|stock_id
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|help_id
operator|=
name|g_strdup
argument_list|(
name|help_id
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|get_preview_func
operator|=
name|get_preview_func
expr_stmt|;
name|dockable
operator|->
name|get_preview_data
operator|=
name|get_preview_data
expr_stmt|;
name|dockable
operator|->
name|set_context_func
operator|=
name|set_context_func
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dockable_get_tab_widget (GimpDockable * dockable,GimpContext * context,GimpTabStyle tab_style,GtkIconSize size)
name|gimp_dockable_get_tab_widget
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpTabStyle
name|tab_style
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
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
return|return
name|GIMP_DOCKABLE_GET_CLASS
argument_list|(
name|dockable
argument_list|)
operator|->
name|get_tab_widget
argument_list|(
name|dockable
argument_list|,
name|context
argument_list|,
name|tab_style
argument_list|,
name|size
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dockable_set_context (GimpDockable * dockable,GimpContext * context)
name|gimp_dockable_set_context
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|context
operator|!=
name|dockable
operator|->
name|context
condition|)
name|GIMP_DOCKABLE_GET_CLASS
argument_list|(
name|dockable
argument_list|)
operator|->
name|set_context
argument_list|(
name|dockable
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
DECL|function|gimp_dockable_real_get_tab_widget (GimpDockable * dockable,GimpContext * context,GimpTabStyle tab_style,GtkIconSize size)
name|gimp_dockable_real_get_tab_widget
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpTabStyle
name|tab_style
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|tab_widget
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|label
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|icon
init|=
name|NULL
decl_stmt|;
switch|switch
condition|(
name|tab_style
condition|)
block|{
case|case
name|GIMP_TAB_STYLE_NAME
case|:
case|case
name|GIMP_TAB_STYLE_ICON_NAME
case|:
case|case
name|GIMP_TAB_STYLE_PREVIEW_NAME
case|:
name|label
operator|=
name|gtk_label_new
argument_list|(
name|dockable
operator|->
name|name
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TAB_STYLE_BLURB
case|:
case|case
name|GIMP_TAB_STYLE_ICON_BLURB
case|:
case|case
name|GIMP_TAB_STYLE_PREVIEW_BLURB
case|:
name|label
operator|=
name|gtk_label_new
argument_list|(
name|dockable
operator|->
name|blurb
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
switch|switch
condition|(
name|tab_style
condition|)
block|{
case|case
name|GIMP_TAB_STYLE_ICON
case|:
case|case
name|GIMP_TAB_STYLE_ICON_NAME
case|:
case|case
name|GIMP_TAB_STYLE_ICON_BLURB
case|:
name|icon
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|dockable
operator|->
name|stock_id
argument_list|,
name|size
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TAB_STYLE_PREVIEW
case|:
case|case
name|GIMP_TAB_STYLE_PREVIEW_NAME
case|:
case|case
name|GIMP_TAB_STYLE_PREVIEW_BLURB
case|:
if|if
condition|(
name|dockable
operator|->
name|get_preview_func
condition|)
name|icon
operator|=
name|dockable
operator|->
name|get_preview_func
argument_list|(
name|dockable
argument_list|,
name|context
argument_list|,
name|size
argument_list|,
name|dockable
operator|->
name|get_preview_data
argument_list|)
expr_stmt|;
else|else
name|icon
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|dockable
operator|->
name|stock_id
argument_list|,
name|size
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
switch|switch
condition|(
name|tab_style
condition|)
block|{
case|case
name|GIMP_TAB_STYLE_ICON
case|:
case|case
name|GIMP_TAB_STYLE_PREVIEW
case|:
name|tab_widget
operator|=
name|icon
expr_stmt|;
break|break;
case|case
name|GIMP_TAB_STYLE_NAME
case|:
case|case
name|GIMP_TAB_STYLE_BLURB
case|:
name|tab_widget
operator|=
name|label
expr_stmt|;
break|break;
case|case
name|GIMP_TAB_STYLE_ICON_NAME
case|:
case|case
name|GIMP_TAB_STYLE_ICON_BLURB
case|:
case|case
name|GIMP_TAB_STYLE_PREVIEW_NAME
case|:
case|case
name|GIMP_TAB_STYLE_PREVIEW_BLURB
case|:
name|tab_widget
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|tab_widget
argument_list|)
argument_list|,
name|icon
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
name|icon
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|tab_widget
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|tab_widget
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_real_set_context (GimpDockable * dockable,GimpContext * context)
name|gimp_dockable_real_set_context
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
operator|->
name|set_context_func
condition|)
name|dockable
operator|->
name|set_context_func
argument_list|(
name|dockable
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|context
operator|=
name|context
expr_stmt|;
block|}
end_function

end_unit

