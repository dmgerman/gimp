begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageP.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"lc_dialog.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"paletteP.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"layer.h"
end_include

begin_include
include|#
directive|include
file|"layer_pvt.h"
end_include

begin_include
include|#
directive|include
file|"channel.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"gimpset.h"
end_include

begin_include
include|#
directive|include
file|"dialog_handler.h"
end_include

begin_comment
comment|/* gimage.c: Junk (ugly dependencies) from gimpimage.c on its way    to proper places. That is, the handlers should be moved to    layers_dialog, gdisplay, tools, etc.. */
end_comment

begin_function_decl
specifier|static
name|void
name|gimage_dirty_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimage_destroy_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimage_cmap_change_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|ncol
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimage_rename_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimage_resize_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimage_restructure_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimage_repaint_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GImage
modifier|*
DECL|function|gimage_new (int width,int height,GimpImageBaseType base_type)
name|gimage_new
parameter_list|(
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|,
name|GimpImageBaseType
name|base_type
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
init|=
name|gimp_image_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|base_type
argument_list|)
decl_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"dirty"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimage_dirty_handler
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimage_destroy_handler
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"rename"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimage_rename_handler
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"resize"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimage_resize_handler
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"restructure"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimage_restructure_handler
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"repaint"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimage_repaint_handler
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"colormap_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimage_cmap_change_handler
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_set_add
argument_list|(
name|image_context
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
return|return
name|gimage
return|;
block|}
end_function

begin_function
name|GImage
modifier|*
DECL|function|gimage_get_ID (gint ID)
name|gimage_get_ID
parameter_list|(
name|gint
name|ID
parameter_list|)
block|{
return|return
name|pdb_id_to_image
argument_list|(
name|ID
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/* Ack, GImages have their own ref counts! This is going to cause    trouble.. It should be pretty easy to convert to proper GtkObject    ref counting, though. */
end_comment

begin_comment
comment|/* This caused trouble indeed. The ref_count was only used by the    displays showing the image, so I renamed it to disp_count to     make clear that it should only be used for display references.                                                (Sven, 23.01.2000) */
end_comment

begin_function
name|void
DECL|function|gimage_delete (GImage * gimage)
name|gimage_delete
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|)
block|{
if|if
condition|(
name|gimage
operator|->
name|disp_count
operator|<=
literal|0
condition|)
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|invalidate_cb (gpointer image,gpointer user_data)
name|invalidate_cb
parameter_list|(
name|gpointer
name|image
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|gimp_image_invalidate_preview
argument_list|(
name|GIMP_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_invalidate_previews (void)
name|gimage_invalidate_previews
parameter_list|(
name|void
parameter_list|)
block|{
name|gimp_set_foreach
argument_list|(
name|image_context
argument_list|,
name|invalidate_cb
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimage_dirty_handler (GimpImage * gimage)
name|gimage_dirty_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
if|if
condition|(
name|active_tool
operator|&&
operator|!
name|active_tool
operator|->
name|preserve
condition|)
block|{
name|GDisplay
modifier|*
name|gdisp
init|=
name|active_tool
operator|->
name|gdisp_ptr
decl_stmt|;
if|if
condition|(
name|gdisp
condition|)
block|{
if|if
condition|(
name|gdisp
operator|->
name|gimage
operator|==
name|gimage
condition|)
name|tools_initialize
argument_list|(
name|active_tool
operator|->
name|type
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
else|else
name|tools_initialize
argument_list|(
name|active_tool
operator|->
name|type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimlist_cb (gpointer im,gpointer data)
name|gimlist_cb
parameter_list|(
name|gpointer
name|im
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GSList
modifier|*
modifier|*
name|l
init|=
operator|(
name|GSList
operator|*
operator|*
operator|)
name|data
decl_stmt|;
operator|*
name|l
operator|=
name|g_slist_prepend
argument_list|(
operator|*
name|l
argument_list|,
name|im
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimage_image_count (void)
name|gimage_image_count
parameter_list|(
name|void
parameter_list|)
block|{
name|GSList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|gint
name|num_images
init|=
literal|0
decl_stmt|;
name|gimage_foreach
argument_list|(
name|gimlist_cb
argument_list|,
operator|&
name|list
argument_list|)
expr_stmt|;
name|num_images
operator|=
name|g_slist_length
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|list
argument_list|)
expr_stmt|;
return|return
operator|(
name|num_images
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimage_destroy_handler (GimpImage * gimage)
name|gimage_destroy_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
comment|/*  free the undo list  */
name|undo_free
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/*  free all guides  */
name|list
operator|=
name|gimage
operator|->
name|guides
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|g_free
argument_list|(
operator|(
name|Guide
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|gimage
operator|->
name|guides
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage_image_count
argument_list|()
operator|==
literal|1
condition|)
comment|/*  This is the last image  */
block|{
name|dialog_show_toolbox
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimage_cmap_change_handler (GimpImage * gimage,gint ncol,gpointer user_data)
name|gimage_cmap_change_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|ncol
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|gdisplays_update_full
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
operator|==
name|INDEXED
condition|)
name|paint_funcs_invalidate_color_hash_table
argument_list|(
name|gimage
argument_list|,
name|ncol
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimage_rename_handler (GimpImage * gimage)
name|gimage_rename_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|gdisplays_update_title
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|lc_dialog_update_image_list
argument_list|()
expr_stmt|;
name|palette_import_image_renamed
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimage_resize_handler (GimpImage * gimage)
name|gimage_resize_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|undo_push_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
comment|/*  shrink wrap and update all views  */
name|channel_invalidate_previews
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|layer_invalidate_previews
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_invalidate_preview
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gdisplays_resize_cursor_label
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gdisplays_update_full
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gdisplays_shrink_wrap
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimage_restructure_handler (GimpImage * gimage)
name|gimage_restructure_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|gdisplays_update_title
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimage_repaint_handler (GimpImage * gimage,gint x,gint y,gint w,gint h)
name|gimage_repaint_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|gdisplays_update_area
argument_list|(
name|gimage
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* These really belong in the layer class */
end_comment

begin_function
name|void
DECL|function|gimage_set_layer_mask_apply (GImage * gimage,GimpLayer * layer)
name|gimage_set_layer_mask_apply
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|)
block|{
name|int
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|layer
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|layer
operator|->
name|mask
condition|)
return|return;
name|layer
operator|->
name|apply_mask
operator|=
operator|!
name|layer
operator|->
name|apply_mask
expr_stmt|;
name|drawable_offsets
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|gdisplays_update_area
argument_list|(
name|gimage
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|drawable_width
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
name|drawable_height
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_set_layer_mask_edit (GImage * gimage,Layer * layer,gboolean edit)
name|gimage_set_layer_mask_edit
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|Layer
modifier|*
name|layer
parameter_list|,
name|gboolean
name|edit
parameter_list|)
block|{
comment|/*  find the layer  */
if|if
condition|(
operator|!
name|layer
condition|)
return|return;
if|if
condition|(
name|layer
operator|->
name|mask
condition|)
name|layer
operator|->
name|edit_mask
operator|=
name|edit
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_set_layer_mask_show (GImage * gimage,GimpLayer * layer)
name|gimage_set_layer_mask_show
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|)
block|{
name|int
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|layer
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|layer
operator|->
name|mask
condition|)
return|return;
name|layer
operator|->
name|show_mask
operator|=
operator|!
name|layer
operator|->
name|show_mask
expr_stmt|;
name|drawable_offsets
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|gdisplays_update_area
argument_list|(
name|gimage
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|drawable_width
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|,
name|drawable_height
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimage_foreach (GFunc func,gpointer user_data)
name|gimage_foreach
parameter_list|(
name|GFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|gimp_set_foreach
argument_list|(
name|image_context
argument_list|,
name|func
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

