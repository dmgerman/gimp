begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdrawablelistitem.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawablelistitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawablelistview.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_drawable_list_item_class_init
parameter_list|(
name|GimpDrawableListItemClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_list_item_init
parameter_list|(
name|GimpDrawableListItem
modifier|*
name|list_item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_list_item_set_viewable
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_list_item_eye_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_list_item_visibility_changed
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gpointer
name|data
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
DECL|function|gimp_drawable_list_item_get_type (void)
name|gimp_drawable_list_item_get_type
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
name|GimpDrawableListItemClass
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
name|gimp_drawable_list_item_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpDrawableListItem
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_drawable_list_item_init
block|,       }
decl_stmt|;
name|list_item_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_ITEM_LIST_ITEM
argument_list|,
literal|"GimpDrawableListItem"
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
DECL|function|gimp_drawable_list_item_class_init (GimpDrawableListItemClass * klass)
name|gimp_drawable_list_item_class_init
parameter_list|(
name|GimpDrawableListItemClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpListItemClass
modifier|*
name|list_item_class
decl_stmt|;
name|list_item_class
operator|=
name|GIMP_LIST_ITEM_CLASS
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
name|list_item_class
operator|->
name|set_viewable
operator|=
name|gimp_drawable_list_item_set_viewable
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_list_item_init (GimpDrawableListItem * list_item)
name|gimp_drawable_list_item_init
parameter_list|(
name|GimpDrawableListItem
modifier|*
name|list_item
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|abox
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|abox
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GIMP_LIST_ITEM
argument_list|(
name|list_item
argument_list|)
operator|->
name|hbox
argument_list|)
argument_list|,
name|abox
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
name|abox
argument_list|)
expr_stmt|;
name|list_item
operator|->
name|eye_button
operator|=
name|gtk_toggle_button_new
argument_list|()
expr_stmt|;
name|gtk_button_set_relief
argument_list|(
name|GTK_BUTTON
argument_list|(
name|list_item
operator|->
name|eye_button
argument_list|)
argument_list|,
name|GTK_RELIEF_NONE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|abox
argument_list|)
argument_list|,
name|list_item
operator|->
name|eye_button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|list_item
operator|->
name|eye_button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|list_item
operator|->
name|eye_button
argument_list|)
argument_list|,
literal|"realize"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_list_item_button_realize
argument_list|)
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|list_item
operator|->
name|eye_button
argument_list|)
argument_list|,
literal|"state_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_list_item_button_state_changed
argument_list|)
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|GIMP_STOCK_VISIBLE
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|list_item
operator|->
name|eye_button
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_list_item_set_viewable (GimpListItem * list_item,GimpViewable * viewable)
name|gimp_drawable_list_item_set_viewable
parameter_list|(
name|GimpListItem
modifier|*
name|list_item
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|GimpDrawableListItem
modifier|*
name|drawable_item
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gboolean
name|visible
decl_stmt|;
if|if
condition|(
name|GIMP_LIST_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_viewable
condition|)
name|GIMP_LIST_ITEM_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_viewable
argument_list|(
name|list_item
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
name|GIMP_PREVIEW
argument_list|(
name|list_item
operator|->
name|preview
argument_list|)
operator|->
name|clickable
operator|=
name|TRUE
expr_stmt|;
name|drawable_item
operator|=
name|GIMP_DRAWABLE_LIST_ITEM
argument_list|(
name|list_item
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|list_item
operator|->
name|preview
argument_list|)
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|visible
operator|=
name|gimp_drawable_get_visible
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|visible
condition|)
block|{
name|GtkRequisition
name|requisition
decl_stmt|;
name|gtk_widget_size_request
argument_list|(
name|drawable_item
operator|->
name|eye_button
argument_list|,
operator|&
name|requisition
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|drawable_item
operator|->
name|eye_button
argument_list|,
name|requisition
operator|.
name|width
argument_list|,
name|requisition
operator|.
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_BIN
argument_list|(
name|drawable_item
operator|->
name|eye_button
argument_list|)
operator|->
name|child
argument_list|)
expr_stmt|;
block|}
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|drawable_item
operator|->
name|eye_button
argument_list|)
argument_list|,
name|visible
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|drawable_item
operator|->
name|eye_button
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_list_item_eye_toggled
argument_list|)
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|G_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|,
literal|"visibility_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_list_item_visibility_changed
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|list_item
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_list_item_eye_toggled (GtkWidget * widget,gpointer data)
name|gimp_drawable_list_item_eye_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpListItem
modifier|*
name|list_item
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gboolean
name|visible
decl_stmt|;
name|list_item
operator|=
name|GIMP_LIST_ITEM
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|list_item
operator|->
name|preview
argument_list|)
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|visible
operator|=
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|visible
operator|!=
name|gimp_drawable_get_visible
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|visible
condition|)
block|{
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|widget
argument_list|)
operator|->
name|allocation
operator|.
name|width
argument_list|,
name|GTK_WIDGET
argument_list|(
name|widget
argument_list|)
operator|->
name|allocation
operator|.
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
operator|->
name|child
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_show
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
operator|->
name|child
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
name|g_signal_handlers_block_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|gimp_drawable_list_item_visibility_changed
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
name|gimp_drawable_set_visible
argument_list|(
name|drawable
argument_list|,
name|visible
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|gimp_drawable_list_item_visibility_changed
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_list_item_visibility_changed (GimpDrawable * drawable,gpointer data)
name|gimp_drawable_list_item_visibility_changed
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpListItem
modifier|*
name|list_item
decl_stmt|;
name|GtkToggleButton
modifier|*
name|toggle
decl_stmt|;
name|gboolean
name|visible
decl_stmt|;
name|list_item
operator|=
name|GIMP_LIST_ITEM
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|GIMP_DRAWABLE_LIST_ITEM
argument_list|(
name|data
argument_list|)
operator|->
name|eye_button
argument_list|)
expr_stmt|;
name|visible
operator|=
name|gimp_drawable_get_visible
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|visible
operator|!=
name|toggle
operator|->
name|active
condition|)
block|{
if|if
condition|(
operator|!
name|visible
condition|)
block|{
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|toggle
argument_list|)
operator|->
name|allocation
operator|.
name|width
argument_list|,
name|GTK_WIDGET
argument_list|(
name|toggle
argument_list|)
operator|->
name|allocation
operator|.
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_BIN
argument_list|(
name|toggle
argument_list|)
operator|->
name|child
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_show
argument_list|(
name|GTK_BIN
argument_list|(
name|toggle
argument_list|)
operator|->
name|child
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|toggle
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
name|g_signal_handlers_block_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|gimp_drawable_list_item_eye_toggled
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|toggle
argument_list|,
name|visible
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|gimp_drawable_list_item_eye_toggled
argument_list|,
name|list_item
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

