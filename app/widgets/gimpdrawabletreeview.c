begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdrawablelistview.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpchannellistview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawablelistview.h"
end_include

begin_include
include|#
directive|include
file|"gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimplayerlistview.h"
end_include

begin_include
include|#
directive|include
file|"gimplistitem.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_drawable_list_view_class_init
parameter_list|(
name|GimpDrawableListViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_list_view_init
parameter_list|(
name|GimpDrawableListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_list_view_set_image
parameter_list|(
name|GimpItemListView
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
name|gimp_drawable_list_view_floating_selection_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawableListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_list_view_new_pattern_dropped
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
name|gimp_drawable_list_view_new_color_dropped
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
DECL|function|gimp_drawable_list_view_get_type (void)
name|gimp_drawable_list_view_get_type
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
name|GimpDrawableListViewClass
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
name|gimp_drawable_list_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpDrawableListView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_drawable_list_view_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_ITEM_LIST_VIEW
argument_list|,
literal|"GimpDrawableListView"
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
DECL|function|gimp_drawable_list_view_class_init (GimpDrawableListViewClass * klass)
name|gimp_drawable_list_view_class_init
parameter_list|(
name|GimpDrawableListViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpItemListViewClass
modifier|*
name|item_view_class
decl_stmt|;
name|item_view_class
operator|=
name|GIMP_ITEM_LIST_VIEW_CLASS
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
name|item_view_class
operator|->
name|set_image
operator|=
name|gimp_drawable_list_view_set_image
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_list_view_init (GimpDrawableListView * view)
name|gimp_drawable_list_view_init
parameter_list|(
name|GimpDrawableListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpItemListView
modifier|*
name|item_view
decl_stmt|;
name|item_view
operator|=
name|GIMP_ITEM_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|item_view
operator|->
name|new_button
argument_list|,
name|GIMP_TYPE_PATTERN
argument_list|,
name|gimp_drawable_list_view_new_pattern_dropped
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
name|gimp_drawable_list_view_new_color_dropped
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_list_view_set_image (GimpItemListView * item_view,GimpImage * gimage)
name|gimp_drawable_list_view_set_image
parameter_list|(
name|GimpItemListView
modifier|*
name|item_view
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpDrawableListView
modifier|*
name|view
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE_LIST_VIEW
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
name|GIMP_DRAWABLE_LIST_VIEW
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
name|gimp_drawable_list_view_floating_selection_changed
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
name|GIMP_ITEM_LIST_VIEW_CLASS
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
name|gimp_drawable_list_view_floating_selection_changed
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
name|gimp_drawable_list_view_floating_selection_changed
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
DECL|function|gimp_drawable_list_view_floating_selection_changed (GimpImage * gimage,GimpDrawableListView * view)
name|gimp_drawable_list_view_floating_selection_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawableListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpViewable
modifier|*
name|floating_sel
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GList
modifier|*
name|free_list
decl_stmt|;
name|floating_sel
operator|=
operator|(
name|GimpViewable
operator|*
operator|)
name|gimp_image_floating_sel
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|list
operator|=
name|free_list
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GIMP_CONTAINER_LIST_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|gtk_list
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
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
if|if
condition|(
operator|!
operator|(
name|GIMP_PREVIEW
argument_list|(
name|GIMP_LIST_ITEM
argument_list|(
name|list
operator|->
name|data
argument_list|)
operator|->
name|preview
argument_list|)
operator|->
name|viewable
operator|==
name|floating_sel
operator|)
condition|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|,
name|floating_sel
operator|==
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
name|g_list_free
argument_list|(
name|free_list
argument_list|)
expr_stmt|;
comment|/*  update button states  */
comment|/* gimp_drawable_list_view_drawable_changed (gimage, view); */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_list_view_new_dropped (GimpItemListView * view,GimpBucketFillMode fill_mode,const GimpRGB * color,GimpPattern * pattern)
name|gimp_drawable_list_view_new_dropped
parameter_list|(
name|GimpItemListView
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
name|color
argument_list|,
name|pattern
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
DECL|function|gimp_drawable_list_view_new_pattern_dropped (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|gimp_drawable_list_view_new_pattern_dropped
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
name|gimp_drawable_list_view_new_dropped
argument_list|(
name|GIMP_ITEM_LIST_VIEW
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
DECL|function|gimp_drawable_list_view_new_color_dropped (GtkWidget * widget,const GimpRGB * color,gpointer data)
name|gimp_drawable_list_view_new_color_dropped
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
name|gimp_drawable_list_view_new_dropped
argument_list|(
name|GIMP_ITEM_LIST_VIEW
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

end_unit

