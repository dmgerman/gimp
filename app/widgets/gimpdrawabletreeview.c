begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdrawabletreeview.c  * Copyright (C) 2001-2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|"core/gimp.h"
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-bucket-fill.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpcellrenderertoggle.h"
end_include

begin_include
include|#
directive|include
file|"gimpchanneltreeview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimplayertreeview.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_class_init
parameter_list|(
name|GimpDrawableTreeViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_init
parameter_list|(
name|GimpDrawableTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_drawable_tree_view_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_set_container
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gpointer
name|gimp_drawable_tree_view_insert_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_set_image
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_floating_selection_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawableTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_new_pattern_dropped
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_new_color_dropped
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_visibility_changed
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpDrawableTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_tree_view_eye_toggled
parameter_list|(
name|GtkCellRendererToggle
modifier|*
name|toggle
parameter_list|,
name|gchar
modifier|*
name|path
parameter_list|,
name|GimpDrawableTreeView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpItemTreeViewClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_drawable_tree_view_get_type (void)
name|gimp_drawable_tree_view_get_type
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
name|GimpDrawableTreeViewClass
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
name|gimp_drawable_tree_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpDrawableTreeView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_drawable_tree_view_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_ITEM_TREE_VIEW
argument_list|,
literal|"GimpDrawableTreeView"
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
DECL|function|gimp_drawable_tree_view_class_init (GimpDrawableTreeViewClass * klass)
name|gimp_drawable_tree_view_class_init
parameter_list|(
name|GimpDrawableTreeViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpContainerViewClass
modifier|*
name|container_view_class
decl_stmt|;
name|GimpItemTreeViewClass
modifier|*
name|item_view_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|container_view_class
operator|=
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|item_view_class
operator|=
name|GIMP_ITEM_TREE_VIEW_CLASS
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
name|constructor
operator|=
name|gimp_drawable_tree_view_constructor
expr_stmt|;
name|container_view_class
operator|->
name|set_container
operator|=
name|gimp_drawable_tree_view_set_container
expr_stmt|;
name|container_view_class
operator|->
name|insert_item
operator|=
name|gimp_drawable_tree_view_insert_item
expr_stmt|;
name|item_view_class
operator|->
name|set_image
operator|=
name|gimp_drawable_tree_view_set_image
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_init (GimpDrawableTreeView * view)
name|gimp_drawable_tree_view_init
parameter_list|(
name|GimpDrawableTreeView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContainerTreeView
modifier|*
name|tree_view
decl_stmt|;
name|GimpItemTreeView
modifier|*
name|item_view
decl_stmt|;
name|tree_view
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|item_view
operator|=
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|view
operator|->
name|model_column_visible
operator|=
name|tree_view
operator|->
name|n_model_columns
expr_stmt|;
name|tree_view
operator|->
name|model_columns
index|[
name|tree_view
operator|->
name|n_model_columns
operator|++
index|]
operator|=
name|G_TYPE_BOOLEAN
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|item_view
operator|->
name|new_button
argument_list|,
name|GIMP_TYPE_PATTERN
argument_list|,
name|gimp_drawable_tree_view_new_pattern_dropped
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gimp_dnd_color_dest_add
argument_list|(
name|item_view
operator|->
name|new_button
argument_list|,
name|gimp_drawable_tree_view_new_color_dropped
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_drawable_tree_view_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_drawable_tree_view_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GimpContainerTreeView
modifier|*
name|tree_view
decl_stmt|;
name|GimpDrawableTreeView
modifier|*
name|drawable_view
decl_stmt|;
name|GObject
modifier|*
name|object
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|tree_view
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|drawable_view
operator|=
name|GIMP_DRAWABLE_TREE_VIEW
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|drawable_view
operator|->
name|eye_column
operator|=
name|gtk_tree_view_column_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_insert_column
argument_list|(
name|tree_view
operator|->
name|view
argument_list|,
name|drawable_view
operator|->
name|eye_column
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|drawable_view
operator|->
name|eye_cell
operator|=
name|gimp_cell_renderer_toggle_new
argument_list|(
name|GIMP_STOCK_VISIBLE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|drawable_view
operator|->
name|eye_column
argument_list|,
name|drawable_view
operator|->
name|eye_cell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_attributes
argument_list|(
name|drawable_view
operator|->
name|eye_column
argument_list|,
name|drawable_view
operator|->
name|eye_cell
argument_list|,
literal|"active"
argument_list|,
name|drawable_view
operator|->
name|model_column_visible
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tree_view
operator|->
name|toggle_columns
operator|=
name|g_list_prepend
argument_list|(
name|tree_view
operator|->
name|toggle_columns
argument_list|,
name|drawable_view
operator|->
name|eye_column
argument_list|)
expr_stmt|;
name|tree_view
operator|->
name|toggle_cells
operator|=
name|g_list_prepend
argument_list|(
name|tree_view
operator|->
name|toggle_cells
argument_list|,
name|drawable_view
operator|->
name|eye_cell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|drawable_view
operator|->
name|eye_cell
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_tree_view_eye_toggled
argument_list|)
argument_list|,
name|drawable_view
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_set_container (GimpContainerView * view,GimpContainer * container)
name|gimp_drawable_tree_view_set_container
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
name|GimpDrawableTreeView
modifier|*
name|drawable_view
decl_stmt|;
name|drawable_view
operator|=
name|GIMP_DRAWABLE_TREE_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|container
condition|)
block|{
name|gimp_container_remove_handler
argument_list|(
name|view
operator|->
name|container
argument_list|,
name|drawable_view
operator|->
name|visibility_changed_handler_id
argument_list|)
expr_stmt|;
block|}
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_container
argument_list|(
name|view
argument_list|,
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|container
condition|)
block|{
name|drawable_view
operator|->
name|visibility_changed_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|view
operator|->
name|container
argument_list|,
literal|"visibility_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_tree_view_visibility_changed
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gpointer
DECL|function|gimp_drawable_tree_view_insert_item (GimpContainerView * view,GimpViewable * viewable,gint index)
name|gimp_drawable_tree_view_insert_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|GtkTreeIter
modifier|*
name|iter
decl_stmt|;
name|iter
operator|=
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|insert_item
argument_list|(
name|view
argument_list|,
name|viewable
argument_list|,
name|index
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|model
argument_list|)
argument_list|,
name|iter
argument_list|,
name|GIMP_DRAWABLE_TREE_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|model_column_visible
argument_list|,
name|gimp_drawable_get_visible
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|iter
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_set_image (GimpItemTreeView * item_view,GimpImage * gimage)
name|gimp_drawable_tree_view_set_image
parameter_list|(
name|GimpItemTreeView
modifier|*
name|item_view
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpDrawableTreeView
modifier|*
name|view
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE_TREE_VIEW
argument_list|(
name|item_view
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|gimage
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|=
name|GIMP_DRAWABLE_TREE_VIEW
argument_list|(
name|item_view
argument_list|)
expr_stmt|;
if|if
condition|(
name|item_view
operator|->
name|gimage
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|,
name|gimp_drawable_tree_view_floating_selection_changed
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
name|GIMP_ITEM_TREE_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_image
argument_list|(
name|item_view
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|item_view
operator|->
name|gimage
condition|)
block|{
name|g_signal_connect
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|,
literal|"floating_selection_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_tree_view_floating_selection_changed
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_floating_sel
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|)
condition|)
name|gimp_drawable_tree_view_floating_selection_changed
argument_list|(
name|item_view
operator|->
name|gimage
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_floating_selection_changed (GimpImage * gimage,GimpDrawableTreeView * view)
name|gimp_drawable_tree_view_floating_selection_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawableTreeView
modifier|*
name|view
parameter_list|)
block|{
if|#
directive|if
literal|0
block|GimpViewable *floating_sel;   GList        *list;   GList        *free_list;    floating_sel = (GimpViewable *) gimp_image_floating_sel (gimage);    list = free_list = gtk_container_get_children     (GTK_CONTAINER (GIMP_CONTAINER_TREE_VIEW (view)->gtk_tree));    for (; list; list = g_list_next (list))     {       if (! (GIMP_PREVIEW (GIMP_TREE_ITEM (list->data)->preview)->viewable == 	     floating_sel)) 	{ 	  gtk_widget_set_sensitive (GTK_WIDGET (list->data), 				    floating_sel == NULL); 	}     }    g_list_free (free_list);
comment|/*  update button states  */
comment|/* gimp_drawable_tree_view_drawable_changed (gimage, view); */
endif|#
directive|endif
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_new_dropped (GimpItemTreeView * view,GimpBucketFillMode fill_mode,const GimpRGB * color,GimpPattern * pattern)
name|gimp_drawable_tree_view_new_dropped
parameter_list|(
name|GimpItemTreeView
modifier|*
name|view
parameter_list|,
name|GimpBucketFillMode
name|fill_mode
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|view
operator|->
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_PASTE
argument_list|,
name|_
argument_list|(
literal|"New Layer"
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|new_item_func
argument_list|(
name|view
operator|->
name|gimage
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|view
operator|->
name|gimage
argument_list|)
expr_stmt|;
comment|/*  Get the bucket fill context  */
name|tool_info
operator|=
operator|(
name|GimpToolInfo
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|view
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|tool_info_list
argument_list|,
literal|"gimp-bucket-fill-tool"
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|tool_info
operator|->
name|tool_options
condition|)
block|{
name|context
operator|=
name|GIMP_CONTEXT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|view
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
name|gimp_drawable_bucket_fill_full
argument_list|(
name|drawable
argument_list|,
name|fill_mode
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
argument_list|,
name|FALSE
comment|/* no seed fill */
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
comment|/* fill params */
argument_list|,
name|color
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|view
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|view
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_new_pattern_dropped (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|gimp_drawable_tree_view_new_pattern_dropped
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_drawable_tree_view_new_dropped
argument_list|(
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
argument_list|,
name|GIMP_PATTERN_BUCKET_FILL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PATTERN
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_new_color_dropped (GtkWidget * widget,const GimpRGB * color,gpointer data)
name|gimp_drawable_tree_view_new_color_dropped
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_drawable_tree_view_new_dropped
argument_list|(
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
argument_list|,
name|GIMP_FG_BUCKET_FILL
argument_list|,
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_visibility_changed (GimpDrawable * drawable,GimpDrawableTreeView * view)
name|gimp_drawable_tree_view_visibility_changed
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpDrawableTreeView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContainerView
modifier|*
name|container_view
decl_stmt|;
name|GimpContainerTreeView
modifier|*
name|tree_view
decl_stmt|;
name|GtkTreeIter
modifier|*
name|iter
decl_stmt|;
name|container_view
operator|=
name|GIMP_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|tree_view
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|iter
operator|=
name|g_hash_table_lookup
argument_list|(
name|container_view
operator|->
name|hash_table
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|iter
condition|)
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|tree_view
operator|->
name|model
argument_list|)
argument_list|,
name|iter
argument_list|,
name|view
operator|->
name|model_column_visible
argument_list|,
name|gimp_drawable_get_visible
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_tree_view_eye_toggled (GtkCellRendererToggle * toggle,gchar * path_str,GimpDrawableTreeView * view)
name|gimp_drawable_tree_view_eye_toggled
parameter_list|(
name|GtkCellRendererToggle
modifier|*
name|toggle
parameter_list|,
name|gchar
modifier|*
name|path_str
parameter_list|,
name|GimpDrawableTreeView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContainerTreeView
modifier|*
name|tree_view
decl_stmt|;
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|tree_view
operator|=
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|path
operator|=
name|gtk_tree_path_new_from_string
argument_list|(
name|path_str
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter
argument_list|(
name|tree_view
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|path
argument_list|)
condition|)
block|{
name|GimpPreviewRenderer
modifier|*
name|renderer
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|tree_view
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|tree_view
operator|->
name|model_column_renderer
argument_list|,
operator|&
name|renderer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|toggle
argument_list|,
literal|"active"
argument_list|,
operator|&
name|active
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_set_visible
argument_list|(
name|drawable
argument_list|,
operator|!
name|active
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
block|}
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

