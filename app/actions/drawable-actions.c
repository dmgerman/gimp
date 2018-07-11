begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"drawable-actions.h"
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

begin_decl_stmt
DECL|variable|drawable_actions
specifier|static
specifier|const
name|GimpActionEntry
name|drawable_actions
index|[]
init|=
block|{
block|{
literal|"drawable-equalize"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"_Equalize"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Automatic contrast enhancement"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|drawable_equalize_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_EQUALIZE
block|}
block|,
block|{
literal|"drawable-levels-stretch"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"_White Balance"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Automatic white balance correction"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|drawable_levels_stretch_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_WHITE_BALANCE
block|}
block|,
block|{
literal|"drawable-offset"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"_Offset..."
argument_list|)
block|,
literal|"<primary><shift>O"
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Shift the pixels, optionally wrapping them at the borders"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|drawable_offset_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_OFFSET
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_toggle_actions
specifier|static
specifier|const
name|GimpToggleActionEntry
name|drawable_toggle_actions
index|[]
init|=
block|{
block|{
literal|"drawable-visible"
block|,
name|GIMP_ICON_VISIBLE
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Toggle Drawable _Visibility"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|drawable_visible_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_VISIBLE
block|}
block|,
block|{
literal|"drawable-linked"
block|,
name|GIMP_ICON_LINKED
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Toggle Drawable _Linked State"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|drawable_linked_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_LINKED
block|}
block|,
block|{
literal|"drawable-lock-content"
block|,
name|NULL
comment|/* GIMP_ICON_LOCK */
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"L_ock Pixels of Drawable"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Keep the pixels on this drawable from being modified"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|drawable_lock_content_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_LOCK_PIXELS
block|}
block|,
block|{
literal|"drawable-lock-position"
block|,
name|GIMP_ICON_TOOL_MOVE
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"L_ock Position of Drawable"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Keep the position on this drawable from being modified"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|drawable_lock_position_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_LOCK_POSITION
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_flip_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|drawable_flip_actions
index|[]
init|=
block|{
block|{
literal|"drawable-flip-horizontal"
block|,
name|GIMP_ICON_OBJECT_FLIP_HORIZONTAL
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Flip _Horizontally"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Flip drawable horizontally"
argument_list|)
block|,
name|GIMP_ORIENTATION_HORIZONTAL
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_FLIP_HORIZONTAL
block|}
block|,
block|{
literal|"drawable-flip-vertical"
block|,
name|GIMP_ICON_OBJECT_FLIP_VERTICAL
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Flip _Vertically"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Flip drawable vertically"
argument_list|)
block|,
name|GIMP_ORIENTATION_VERTICAL
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_FLIP_VERTICAL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_rotate_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|drawable_rotate_actions
index|[]
init|=
block|{
block|{
literal|"drawable-rotate-90"
block|,
name|GIMP_ICON_OBJECT_ROTATE_90
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Rotate 90Â° _clockwise"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Rotate drawable 90 degrees to the right"
argument_list|)
block|,
name|GIMP_ROTATE_90
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_ROTATE_90
block|}
block|,
block|{
literal|"drawable-rotate-180"
block|,
name|GIMP_ICON_OBJECT_ROTATE_180
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Rotate _180Â°"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Turn drawable upside-down"
argument_list|)
block|,
name|GIMP_ROTATE_180
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_ROTATE_180
block|}
block|,
block|{
literal|"drawable-rotate-270"
block|,
name|GIMP_ICON_OBJECT_ROTATE_270
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Rotate 90Â° counter-clock_wise"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"drawable-action"
argument_list|,
literal|"Rotate drawable 90 degrees to the left"
argument_list|)
block|,
name|GIMP_ROTATE_270
block|,
name|FALSE
block|,
name|GIMP_HELP_LAYER_ROTATE_270
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|drawable_actions_setup (GimpActionGroup * group)
name|drawable_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
literal|"drawable-action"
argument_list|,
name|drawable_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|drawable_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_toggle_actions
argument_list|(
name|group
argument_list|,
literal|"drawable-action"
argument_list|,
name|drawable_toggle_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|drawable_toggle_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
literal|"drawable-action"
argument_list|,
name|drawable_flip_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|drawable_flip_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|drawable_flip_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
literal|"drawable-action"
argument_list|,
name|drawable_rotate_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|drawable_rotate_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|drawable_rotate_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
DECL|macro|SET_ALWAYS_SHOW_IMAGE (action,show)
define|#
directive|define
name|SET_ALWAYS_SHOW_IMAGE
parameter_list|(
name|action
parameter_list|,
name|show
parameter_list|)
define|\
value|gimp_action_group_set_action_always_show_image (group, action, show)
name|SET_ALWAYS_SHOW_IMAGE
argument_list|(
literal|"drawable-rotate-90"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_ALWAYS_SHOW_IMAGE
argument_list|(
literal|"drawable-rotate-180"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_ALWAYS_SHOW_IMAGE
argument_list|(
literal|"drawable-rotate-270"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_ALWAYS_SHOW_IMAGE
block|}
end_function

begin_function
name|void
DECL|function|drawable_actions_update (GimpActionGroup * group,gpointer data)
name|drawable_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
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
init|=
name|NULL
decl_stmt|;
name|gboolean
name|is_rgb
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|visible
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|linked
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|locked
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|can_lock
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|locked_pos
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|can_lock_pos
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|writable
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|movable
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|children
init|=
name|FALSE
decl_stmt|;
name|image
operator|=
name|action_data_get_image
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|is_rgb
operator|=
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
condition|)
name|item
operator|=
name|GIMP_ITEM
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
else|else
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|visible
operator|=
name|gimp_item_get_visible
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|linked
operator|=
name|gimp_item_get_linked
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|locked
operator|=
name|gimp_item_get_lock_content
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|can_lock
operator|=
name|gimp_item_can_lock_content
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|writable
operator|=
operator|!
name|gimp_item_is_content_locked
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|locked_pos
operator|=
name|gimp_item_get_lock_position
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|can_lock_pos
operator|=
name|gimp_item_can_lock_position
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|movable
operator|=
operator|!
name|gimp_item_is_position_locked
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
name|children
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
DECL|macro|SET_SENSITIVE (action,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_sensitive (group, action, (condition) != 0)
DECL|macro|SET_ACTIVE (action,condition)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_active (group, action, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"drawable-equalize"
argument_list|,
name|writable
operator|&&
operator|!
name|children
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-levels-stretch"
argument_list|,
name|writable
operator|&&
operator|!
name|children
operator|&&
name|is_rgb
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-offset"
argument_list|,
name|writable
operator|&&
operator|!
name|children
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-visible"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-linked"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-lock-content"
argument_list|,
name|can_lock
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-lock-position"
argument_list|,
name|can_lock_pos
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"drawable-visible"
argument_list|,
name|visible
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"drawable-linked"
argument_list|,
name|linked
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"drawable-lock-content"
argument_list|,
name|locked
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"drawable-lock-position"
argument_list|,
name|locked_pos
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-flip-horizontal"
argument_list|,
name|writable
operator|&&
name|movable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-flip-vertical"
argument_list|,
name|writable
operator|&&
name|movable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-rotate-90"
argument_list|,
name|writable
operator|&&
name|movable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-rotate-180"
argument_list|,
name|writable
operator|&&
name|movable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-rotate-270"
argument_list|,
name|writable
operator|&&
name|movable
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
undef|#
directive|undef
name|SET_ACTIVE
block|}
end_function

end_unit

