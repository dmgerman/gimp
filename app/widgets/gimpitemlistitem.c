begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpitemlistitem.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|GTK_DISABLE_DEPRECATED
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpitemlistitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpitemlistview.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_item_list_item_class_init
parameter_list|(
name|GimpItemListItemClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_list_item_init
parameter_list|(
name|GimpItemListItem
modifier|*
name|list_item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_item_list_item_drag_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpListItemClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_item_list_item_get_type (void)
name|gimp_item_list_item_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|list_item_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|list_item_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|list_item_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpItemListItemClass
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
name|gimp_item_list_item_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpItemListItem
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_item_list_item_init
block|,       }
decl_stmt|;
name|list_item_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_LIST_ITEM
argument_list|,
literal|"GimpItemListItem"
argument_list|,
operator|&
name|list_item_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|list_item_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_list_item_class_init (GimpItemListItemClass * klass)
name|gimp_item_list_item_class_init
parameter_list|(
name|GimpItemListItemClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
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
name|widget_class
operator|->
name|drag_drop
operator|=
name|gimp_item_list_item_drag_drop
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_list_item_init (GimpItemListItem * list_item)
name|gimp_item_list_item_init
parameter_list|(
name|GimpItemListItem
modifier|*
name|list_item
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_item_list_item_drag_drop (GtkWidget * widget,GdkDragContext * context,gint x,gint y,guint time)
name|gimp_item_list_item_drag_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|time
parameter_list|)
block|{
name|GimpListItem
modifier|*
name|list_item
decl_stmt|;
name|GimpViewable
modifier|*
name|src_viewable
decl_stmt|;
name|gint
name|dest_index
decl_stmt|;
name|GdkDragAction
name|drag_action
decl_stmt|;
name|GimpDropType
name|drop_type
decl_stmt|;
name|gboolean
name|return_val
decl_stmt|;
name|list_item
operator|=
name|GIMP_LIST_ITEM
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|return_val
operator|=
name|gimp_list_item_check_drag
argument_list|(
name|list_item
argument_list|,
name|context
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|src_viewable
argument_list|,
operator|&
name|dest_index
argument_list|,
operator|&
name|drag_action
argument_list|,
operator|&
name|drop_type
argument_list|)
expr_stmt|;
name|gtk_drag_finish
argument_list|(
name|context
argument_list|,
name|return_val
argument_list|,
name|FALSE
argument_list|,
name|time
argument_list|)
expr_stmt|;
name|list_item
operator|->
name|drop_type
operator|=
name|GIMP_DROP_NONE
expr_stmt|;
if|if
condition|(
name|return_val
condition|)
block|{
if|if
condition|(
name|widget
operator|->
name|parent
operator|&&
comment|/* EEK */
name|widget
operator|->
name|parent
operator|->
name|parent
operator|&&
comment|/* EEEEK */
name|widget
operator|->
name|parent
operator|->
name|parent
operator|->
name|parent
operator|&&
comment|/* EEEEEEK */
name|widget
operator|->
name|parent
operator|->
name|parent
operator|->
name|parent
operator|->
name|parent
operator|&&
comment|/* EEEEEEEEK */
name|GIMP_IS_ITEM_LIST_VIEW
argument_list|(
name|widget
operator|->
name|parent
operator|->
name|parent
operator|->
name|parent
operator|->
name|parent
argument_list|)
condition|)
block|{
name|GimpItemListView
modifier|*
name|item_view
decl_stmt|;
name|GimpItemListViewClass
modifier|*
name|item_view_class
decl_stmt|;
name|item_view
operator|=
name|GIMP_ITEM_LIST_VIEW
argument_list|(
name|widget
operator|->
name|parent
operator|->
name|parent
operator|->
name|parent
operator|->
name|parent
argument_list|)
expr_stmt|;
name|item_view_class
operator|=
name|GIMP_ITEM_LIST_VIEW_GET_CLASS
argument_list|(
name|item_view
argument_list|)
expr_stmt|;
if|if
condition|(
name|item_view
operator|->
name|gimage
operator|==
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|src_viewable
argument_list|)
argument_list|)
condition|)
block|{
name|item_view_class
operator|->
name|reorder_item
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|,
name|GIMP_ITEM
argument_list|(
name|src_viewable
argument_list|)
argument_list|,
name|dest_index
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|item_view_class
operator|->
name|convert_item
condition|)
block|{
name|GimpItem
modifier|*
name|new_item
decl_stmt|;
name|new_item
operator|=
name|item_view_class
operator|->
name|convert_item
argument_list|(
name|GIMP_ITEM
argument_list|(
name|src_viewable
argument_list|)
argument_list|,
name|item_view
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|item_view_class
operator|->
name|add_item
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|,
name|new_item
argument_list|,
name|dest_index
argument_list|)
expr_stmt|;
block|}
name|gimp_image_flush
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"%s: GimpItemListItem is not "
literal|"part of a GimpItemListView"
argument_list|,
name|G_GNUC_FUNCTION
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|return_val
return|;
block|}
end_function

end_unit

