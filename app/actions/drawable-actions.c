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
name|GimpActionEntry
name|drawable_actions
index|[]
init|=
block|{
block|{
literal|"drawable-levels-auto"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_White Balance"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|drawable_levels_auto_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_WHITE_BALANCE
block|}
block|,
block|{
literal|"drawable-desaturate"
block|,
name|GIMP_STOCK_CONVERT_GRAYSCALE
block|,
name|N_
argument_list|(
literal|"_Desaturate"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|drawable_desaturate_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_DESATURATE
block|}
block|,
block|{
literal|"drawable-equalize"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Equalize"
argument_list|)
block|,
name|NULL
block|,
name|NULL
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
literal|"drawable-invert"
block|,
name|GIMP_STOCK_INVERT
block|,
name|N_
argument_list|(
literal|"In_vert"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|drawable_invert_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_LAYER_INVERT
block|}
block|,
block|{
literal|"drawable-offset"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Offset..."
argument_list|)
block|,
literal|"<control><shift>O"
block|,
name|NULL
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
name|GimpToggleActionEntry
name|drawable_toggle_actions
index|[]
init|=
block|{
block|{
literal|"drawable-linked"
block|,
name|GIMP_STOCK_LINKED
block|,
name|N_
argument_list|(
literal|"_Linked"
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
literal|"drawable-visible"
block|,
name|GIMP_STOCK_VISIBLE
block|,
name|N_
argument_list|(
literal|"_Visible"
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_flip_actions
specifier|static
name|GimpEnumActionEntry
name|drawable_flip_actions
index|[]
init|=
block|{
block|{
literal|"drawable-flip-horizontal"
block|,
name|GIMP_STOCK_FLIP_HORIZONTAL
block|,
name|N_
argument_list|(
literal|"Flip _Horizontally"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ORIENTATION_HORIZONTAL
block|,
name|GIMP_HELP_LAYER_FLIP_HORIZONTAL
block|}
block|,
block|{
literal|"drawable-flip-vertical"
block|,
name|GIMP_STOCK_FLIP_VERTICAL
block|,
name|N_
argument_list|(
literal|"Flip _Vertically"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ORIENTATION_VERTICAL
block|,
name|GIMP_HELP_LAYER_FLIP_VERTICAL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_rotate_actions
specifier|static
name|GimpEnumActionEntry
name|drawable_rotate_actions
index|[]
init|=
block|{
block|{
literal|"drawable-rotate-90"
block|,
name|GIMP_STOCK_ROTATE_90
block|,
name|N_
argument_list|(
literal|"Rotate 90 degrees _CW"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ROTATE_90
block|,
name|GIMP_HELP_LAYER_ROTATE_90
block|}
block|,
block|{
literal|"drawable-rotate-180"
block|,
name|GIMP_STOCK_ROTATE_180
block|,
name|N_
argument_list|(
literal|"Rotate _180 degrees"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ROTATE_180
block|,
name|GIMP_HELP_LAYER_ROTATE_180
block|}
block|,
block|{
literal|"drawable-rotate-270"
block|,
name|GIMP_STOCK_ROTATE_270
block|,
name|N_
argument_list|(
literal|"Rotate 90 degrees CC_W"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ROTATE_270
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
name|gimage
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
name|is_gray
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|is_indexed
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
name|gimage
operator|=
name|action_data_get_image
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
condition|)
block|{
name|GimpImageType
name|drawable_type
init|=
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|is_rgb
operator|=
name|GIMP_IMAGE_TYPE_IS_RGB
argument_list|(
name|drawable_type
argument_list|)
expr_stmt|;
name|is_gray
operator|=
name|GIMP_IMAGE_TYPE_IS_GRAY
argument_list|(
name|drawable_type
argument_list|)
expr_stmt|;
name|is_indexed
operator|=
name|GIMP_IMAGE_TYPE_IS_INDEXED
argument_list|(
name|drawable_type
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
literal|"drawable-levels-auto"
argument_list|,
name|drawable
operator|&&
name|is_rgb
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-desaturate"
argument_list|,
name|drawable
operator|&&
name|is_rgb
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-equalize"
argument_list|,
name|drawable
operator|&&
operator|!
name|is_indexed
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-invert"
argument_list|,
name|drawable
operator|&&
operator|!
name|is_indexed
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-offset"
argument_list|,
name|drawable
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
name|SET_SENSITIVE
argument_list|(
literal|"drawable-flip-horizontal"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-flip-vertical"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-rotate-90"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-rotate-180"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"drawable-rotate-270"
argument_list|,
name|drawable
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

