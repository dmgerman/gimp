begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-equalize.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-invert.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-levels.h"
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
file|"core/gimpitem-linked.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitemundo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/offset-dialog.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"drawable-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|drawable_equalize_cmd_callback (GtkAction * action,gpointer data)
name|drawable_equalize_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
argument_list|,
name|_
argument_list|(
literal|"Equalize does not operate on indexed layers."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_drawable_equalize
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|drawable_invert_cmd_callback (GtkAction * action,gpointer data)
name|drawable_invert_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
argument_list|,
name|_
argument_list|(
literal|"Invert does not operate on indexed layers."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_drawable_invert
argument_list|(
name|drawable
argument_list|,
name|GIMP_PROGRESS
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|drawable_levels_stretch_cmd_callback (GtkAction * action,gpointer data)
name|drawable_levels_stretch_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
argument_list|,
name|_
argument_list|(
literal|"White Balance operates only on RGB color layers."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_drawable_levels_stretch
argument_list|(
name|drawable
argument_list|,
name|GIMP_PROGRESS
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|drawable_offset_cmd_callback (GtkAction * action,gpointer data)
name|drawable_offset_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|offset_dialog_new
argument_list|(
name|drawable
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|widget
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|drawable_linked_cmd_callback (GtkAction * action,gpointer data)
name|drawable_linked_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gboolean
name|linked
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|linked
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
condition|)
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|gimp_layer_mask_get_layer
argument_list|(
name|GIMP_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|linked
operator|!=
name|gimp_item_get_linked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|gboolean
name|push_undo
init|=
name|TRUE
decl_stmt|;
name|undo
operator|=
name|gimp_image_undo_can_compress
argument_list|(
name|image
argument_list|,
name|GIMP_TYPE_ITEM_UNDO
argument_list|,
name|GIMP_UNDO_ITEM_LINKED
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|&&
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
operator|==
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
condition|)
name|push_undo
operator|=
name|FALSE
expr_stmt|;
name|gimp_item_set_linked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|linked
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|drawable_visible_cmd_callback (GtkAction * action,gpointer data)
name|drawable_visible_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gboolean
name|visible
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|visible
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
condition|)
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|gimp_layer_mask_get_layer
argument_list|(
name|GIMP_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|visible
operator|!=
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
name|gboolean
name|push_undo
init|=
name|TRUE
decl_stmt|;
name|undo
operator|=
name|gimp_image_undo_can_compress
argument_list|(
name|image
argument_list|,
name|GIMP_TYPE_ITEM_UNDO
argument_list|,
name|GIMP_UNDO_ITEM_VISIBILITY
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|&&
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
operator|==
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
condition|)
name|push_undo
operator|=
name|FALSE
expr_stmt|;
name|gimp_item_set_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|visible
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|drawable_lock_content_cmd_callback (GtkAction * action,gpointer data)
name|drawable_lock_content_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gboolean
name|locked
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|locked
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
condition|)
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|gimp_layer_mask_get_layer
argument_list|(
name|GIMP_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|locked
operator|!=
name|gimp_item_get_lock_content
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
if|#
directive|if
literal|0
block|GimpUndo *undo;
endif|#
directive|endif
name|gboolean
name|push_undo
init|=
name|TRUE
decl_stmt|;
if|#
directive|if
literal|0
block|undo = gimp_image_undo_can_compress (image, GIMP_TYPE_ITEM_UNDO,                                            GIMP_UNDO_ITEM_VISIBILITY);        if (undo&& GIMP_ITEM_UNDO (undo)->item == GIMP_ITEM (drawable))         push_undo = FALSE;
endif|#
directive|endif
name|gimp_item_set_lock_content
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|locked
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|drawable_flip_cmd_callback (GtkAction * action,gint value,gpointer data)
name|drawable_flip_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gdouble
name|axis
init|=
literal|0.0
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|item
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
switch|switch
condition|(
operator|(
name|GimpOrientationType
operator|)
name|value
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
name|axis
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|off_x
operator|+
operator|(
name|gdouble
operator|)
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|/
literal|2.0
operator|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|axis
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|off_y
operator|+
operator|(
name|gdouble
operator|)
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|/
literal|2.0
operator|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|gimp_item_get_linked
argument_list|(
name|item
argument_list|)
condition|)
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_TRANSFORM
argument_list|,
name|GIMP_ITEM_GET_CLASS
argument_list|(
name|item
argument_list|)
operator|->
name|flip_desc
argument_list|)
expr_stmt|;
name|gimp_item_flip
argument_list|(
name|item
argument_list|,
name|context
argument_list|,
operator|(
name|GimpOrientationType
operator|)
name|value
argument_list|,
name|axis
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_item_get_linked
argument_list|(
name|item
argument_list|)
condition|)
block|{
name|gimp_item_linked_flip
argument_list|(
name|item
argument_list|,
name|context
argument_list|,
operator|(
name|GimpOrientationType
operator|)
name|value
argument_list|,
name|axis
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|drawable_rotate_cmd_callback (GtkAction * action,gint value,gpointer data)
name|drawable_rotate_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gdouble
name|center_x
decl_stmt|,
name|center_y
decl_stmt|;
name|gboolean
name|clip_result
init|=
name|FALSE
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_context
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|item
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|center_x
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|off_x
operator|+
operator|(
name|gdouble
operator|)
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
operator|/
literal|2.0
operator|)
expr_stmt|;
name|center_y
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|off_y
operator|+
operator|(
name|gdouble
operator|)
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
operator|/
literal|2.0
operator|)
expr_stmt|;
if|if
condition|(
name|gimp_item_get_linked
argument_list|(
name|item
argument_list|)
condition|)
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_TRANSFORM
argument_list|,
name|GIMP_ITEM_GET_CLASS
argument_list|(
name|item
argument_list|)
operator|->
name|rotate_desc
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_CHANNEL
argument_list|(
name|item
argument_list|)
condition|)
name|clip_result
operator|=
name|TRUE
expr_stmt|;
name|gimp_item_rotate
argument_list|(
name|item
argument_list|,
name|context
argument_list|,
operator|(
name|GimpRotationType
operator|)
name|value
argument_list|,
name|center_x
argument_list|,
name|center_y
argument_list|,
name|clip_result
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_item_get_linked
argument_list|(
name|item
argument_list|)
condition|)
block|{
name|gimp_item_linked_rotate
argument_list|(
name|item
argument_list|,
name|context
argument_list|,
operator|(
name|GimpRotationType
operator|)
name|value
argument_list|,
name|center_x
argument_list|,
name|center_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

