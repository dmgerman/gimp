begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpvectorslistview.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpmath/gimpmath.h"
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

begin_warning
warning|#
directive|warning
warning|FIXME #include "display/display-types.h"
end_warning

begin_include
include|#
directive|include
file|"display/display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask-select.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectorslistview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcomponentlistitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagepreview.h"
end_include

begin_include
include|#
directive|include
file|"gimplistitem.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_vectors_list_view_class_init
parameter_list|(
name|GimpVectorsListViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_list_view_init
parameter_list|(
name|GimpVectorsListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_list_view_select_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|item
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_list_view_to_selection
parameter_list|(
name|GimpVectorsListView
modifier|*
name|view
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_list_view_toselection_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpVectorsListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_list_view_toselection_extended_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|state
parameter_list|,
name|GimpVectorsListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_list_view_stroke
parameter_list|(
name|GimpVectorsListView
modifier|*
name|view
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_list_view_stroke_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpVectorsListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpItemListViewClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_vectors_list_view_get_type (void)
name|gimp_vectors_list_view_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|view_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|view_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|view_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpVectorsListViewClass
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
name|gimp_vectors_list_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpVectorsListView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_vectors_list_view_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_ITEM_LIST_VIEW
argument_list|,
literal|"GimpVectorsListView"
argument_list|,
operator|&
name|view_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|view_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_list_view_class_init (GimpVectorsListViewClass * klass)
name|gimp_vectors_list_view_class_init
parameter_list|(
name|GimpVectorsListViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpContainerViewClass
modifier|*
name|container_view_class
decl_stmt|;
name|container_view_class
operator|=
name|GIMP_CONTAINER_VIEW_CLASS
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
name|container_view_class
operator|->
name|select_item
operator|=
name|gimp_vectors_list_view_select_item
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_list_view_init (GimpVectorsListView * view)
name|gimp_vectors_list_view_init
parameter_list|(
name|GimpVectorsListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpEditor
modifier|*
name|editor
decl_stmt|;
name|editor
operator|=
name|GIMP_EDITOR
argument_list|(
name|view
argument_list|)
expr_stmt|;
comment|/*  To Selection button  */
name|view
operator|->
name|toselection_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|editor
argument_list|,
name|GIMP_STOCK_SELECTION_REPLACE
argument_list|,
name|_
argument_list|(
literal|"Path to Selection\n"
literal|"<Shift> Add\n"
literal|"<Ctrl> Subtract\n"
literal|"<Shift><Ctrl> Intersect"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_vectors_list_view_toselection_clicked
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_vectors_list_view_toselection_extended_clicked
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|view
operator|->
name|stroke_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|editor
argument_list|,
name|GIMP_STOCK_PATH_STROKE
argument_list|,
name|_
argument_list|(
literal|"Stroke Path"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_vectors_list_view_stroke_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
operator|->
name|button_box
argument_list|)
argument_list|,
name|view
operator|->
name|toselection_button
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
operator|->
name|button_box
argument_list|)
argument_list|,
name|view
operator|->
name|stroke_button
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gimp_container_view_enable_dnd
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|toselection_button
argument_list|)
argument_list|,
name|GIMP_TYPE_VECTORS
argument_list|)
expr_stmt|;
name|gimp_container_view_enable_dnd
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|stroke_button
argument_list|)
argument_list|,
name|GIMP_TYPE_VECTORS
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|toselection_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|stroke_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  GimpContainerView methods  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_list_view_select_item (GimpContainerView * view,GimpViewable * item,gpointer insert_data)
name|gimp_vectors_list_view_select_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|item
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
block|{
name|GimpVectorsListView
modifier|*
name|list_view
decl_stmt|;
name|list_view
operator|=
name|GIMP_VECTORS_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|select_item
condition|)
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|select_item
argument_list|(
name|view
argument_list|,
name|item
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|list_view
operator|->
name|toselection_button
argument_list|,
name|item
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|list_view
operator|->
name|stroke_button
argument_list|,
name|item
operator|!=
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  "To Selection" functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_list_view_to_selection (GimpVectorsListView * view,GimpVectors * vectors,GimpChannelOps operation)
name|gimp_vectors_list_view_to_selection
parameter_list|(
name|GimpVectorsListView
modifier|*
name|view
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|)
block|{
if|if
condition|(
name|vectors
condition|)
block|{
name|gimp_image_mask_select_vectors
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
operator|->
name|gimage
argument_list|,
name|vectors
argument_list|,
name|operation
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|,
literal|0
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
DECL|function|gimp_vectors_list_view_toselection_clicked (GtkWidget * widget,GimpVectorsListView * view)
name|gimp_vectors_list_view_toselection_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpVectorsListView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_vectors_list_view_toselection_extended_clicked
argument_list|(
name|widget
argument_list|,
literal|0
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_list_view_toselection_extended_clicked (GtkWidget * widget,guint state,GimpVectorsListView * view)
name|gimp_vectors_list_view_toselection_extended_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|state
parameter_list|,
name|GimpVectorsListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpItemListView
modifier|*
name|item_view
decl_stmt|;
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
name|item_view
operator|=
name|GIMP_ITEM_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|viewable
operator|=
name|item_view
operator|->
name|get_item_func
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|viewable
condition|)
block|{
name|GimpChannelOps
name|operation
init|=
name|GIMP_CHANNEL_OP_REPLACE
decl_stmt|;
if|if
condition|(
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
name|operation
operator|=
name|GIMP_CHANNEL_OP_INTERSECT
expr_stmt|;
else|else
name|operation
operator|=
name|GIMP_CHANNEL_OP_ADD
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
name|operation
operator|=
name|GIMP_CHANNEL_OP_SUBTRACT
expr_stmt|;
block|}
name|gimp_vectors_list_view_to_selection
argument_list|(
name|view
argument_list|,
name|GIMP_VECTORS
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|operation
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_list_view_stroke (GimpVectorsListView * view,GimpVectors * vectors)
name|gimp_vectors_list_view_stroke
parameter_list|(
name|GimpVectorsListView
modifier|*
name|view
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
block|{
if|if
condition|(
name|view
operator|->
name|stroke_item_func
condition|)
block|{
name|view
operator|->
name|stroke_item_func
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_list_view_stroke_clicked (GtkWidget * widget,GimpVectorsListView * view)
name|gimp_vectors_list_view_stroke_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpVectorsListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpItemListView
modifier|*
name|item_view
decl_stmt|;
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
name|item_view
operator|=
name|GIMP_ITEM_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|viewable
operator|=
name|item_view
operator|->
name|get_item_func
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|viewable
condition|)
name|gimp_vectors_list_view_stroke
argument_list|(
name|view
argument_list|,
name|GIMP_VECTORS
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

