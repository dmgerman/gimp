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
file|"config/gimpguiconfig.h"
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
file|"image-actions.h"
end_include

begin_include
include|#
directive|include
file|"image-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|image_actions
specifier|static
name|GimpActionEntry
name|image_actions
index|[]
init|=
block|{
block|{
literal|"toolbox-menubar"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Toolbox Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_TOOLBOX
block|}
block|,
block|{
literal|"image-menubar"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Image Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_IMAGE_WINDOW
block|}
block|,
block|{
literal|"image-popup"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Image Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_IMAGE_WINDOW
block|}
block|,
block|{
literal|"extensions-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Xtns"
argument_list|)
block|}
block|,
block|{
literal|"image-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Image"
argument_list|)
block|}
block|,
block|{
literal|"image-mode-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Mode"
argument_list|)
block|}
block|,
block|{
literal|"image-transform-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Transform"
argument_list|)
block|}
block|,
block|{
literal|"image-new"
block|,
name|GTK_STOCK_NEW
block|,
name|N_
argument_list|(
literal|"_New..."
argument_list|)
block|,
literal|"<control>N"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|image_new_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_NEW
block|}
block|,
block|{
literal|"image-new-from-image"
block|,
name|GTK_STOCK_NEW
block|,
name|N_
argument_list|(
literal|"_New..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|image_new_from_image_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_NEW
block|}
block|,
block|{
literal|"image-resize"
block|,
name|GIMP_STOCK_RESIZE
block|,
name|N_
argument_list|(
literal|"Can_vas Size..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|image_resize_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_IMAGE_RESIZE
block|}
block|,
block|{
literal|"image-scale"
block|,
name|GIMP_STOCK_SCALE
block|,
name|N_
argument_list|(
literal|"_Scale Image..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|image_scale_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_IMAGE_SCALE
block|}
block|,
block|{
literal|"image-crop"
block|,
name|GIMP_STOCK_TOOL_CROP
block|,
name|N_
argument_list|(
literal|"_Crop Image"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|image_crop_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_IMAGE_CROP
block|}
block|,
block|{
literal|"image-duplicate"
block|,
name|GIMP_STOCK_DUPLICATE
block|,
name|N_
argument_list|(
literal|"_Duplicate"
argument_list|)
block|,
literal|"<control>D"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|image_duplicate_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_IMAGE_DUPLICATE
block|}
block|,
block|{
literal|"image-merge-layers"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Merge Visible _Layers..."
argument_list|)
block|,
literal|"<control>M"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|image_merge_layers_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_IMAGE_MERGE_LAYERS
block|}
block|,
block|{
literal|"image-flatten"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Flatten Image"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|image_flatten_image_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_IMAGE_FLATTEN
block|}
block|,
block|{
literal|"image-configure-grid"
block|,
name|GIMP_STOCK_GRID
block|,
name|N_
argument_list|(
literal|"Configure G_rid..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|image_configure_grid_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_IMAGE_GRID
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_convert_actions
specifier|static
name|GimpEnumActionEntry
name|image_convert_actions
index|[]
init|=
block|{
block|{
literal|"image-convert-rgb"
block|,
name|GIMP_STOCK_CONVERT_RGB
block|,
name|N_
argument_list|(
literal|"_RGB"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_RGB
block|,
name|GIMP_HELP_IMAGE_CONVERT_RGB
block|}
block|,
block|{
literal|"image-convert-grayscale"
block|,
name|GIMP_STOCK_CONVERT_GRAYSCALE
block|,
name|N_
argument_list|(
literal|"_Grayscale"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_GRAY
block|,
name|GIMP_HELP_IMAGE_CONVERT_GRAYSCALE
block|}
block|,
block|{
literal|"image-convert-indexed"
block|,
name|GIMP_STOCK_CONVERT_INDEXED
block|,
name|N_
argument_list|(
literal|"_Indexed..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_INDEXED
block|,
name|GIMP_HELP_IMAGE_CONVERT_INDEXED
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_flip_actions
specifier|static
name|GimpEnumActionEntry
name|image_flip_actions
index|[]
init|=
block|{
block|{
literal|"image-flip-horizontal"
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
name|GIMP_HELP_IMAGE_FLIP_HORIZONTAL
block|}
block|,
block|{
literal|"image-flip-vertical"
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
name|GIMP_HELP_IMAGE_FLIP_VERTICAL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_rotate_actions
specifier|static
name|GimpEnumActionEntry
name|image_rotate_actions
index|[]
init|=
block|{
block|{
literal|"image-rotate-90"
block|,
name|GIMP_STOCK_ROTATE_90
block|,
comment|/*  please use the degree symbol in the translation  */
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
name|GIMP_HELP_IMAGE_ROTATE_90
block|}
block|,
block|{
literal|"image-rotate-180"
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
name|GIMP_HELP_IMAGE_ROTATE_180
block|}
block|,
block|{
literal|"image-rotate-270"
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
name|GIMP_HELP_IMAGE_ROTATE_270
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|image_actions_setup (GimpActionGroup * group)
name|image_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|image_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|image_actions
argument_list|)
argument_list|)
expr_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
literal|"image-new-from-image"
argument_list|)
expr_stmt|;
name|gtk_action_set_accel_path
argument_list|(
name|action
argument_list|,
literal|"<Actions>/image/image-new"
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: remove accel_path hack
endif|#
directive|endif
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"gimp-accel-path"
argument_list|,
literal|"<Actions>/image/image-new"
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|image_convert_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|image_convert_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|image_convert_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|image_flip_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|image_flip_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|image_flip_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|image_rotate_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|image_rotate_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|image_rotate_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_actions_update (GimpActionGroup * group,gpointer data)
name|image_actions_update
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
name|fs
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|aux
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|lp
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|sel
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
name|GimpImageBaseType
name|base_type
decl_stmt|;
name|base_type
operator|=
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|is_rgb
operator|=
operator|(
name|base_type
operator|==
name|GIMP_RGB
operator|)
expr_stmt|;
name|is_gray
operator|=
operator|(
name|base_type
operator|==
name|GIMP_GRAY
operator|)
expr_stmt|;
name|is_indexed
operator|=
operator|(
name|base_type
operator|==
name|GIMP_INDEXED
operator|)
expr_stmt|;
name|fs
operator|=
operator|(
name|gimp_image_floating_sel
argument_list|(
name|gimage
argument_list|)
operator|!=
name|NULL
operator|)
expr_stmt|;
name|aux
operator|=
operator|(
name|gimp_image_get_active_channel
argument_list|(
name|gimage
argument_list|)
operator|!=
name|NULL
operator|)
expr_stmt|;
name|lp
operator|=
operator|!
name|gimp_image_is_empty
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|sel
operator|=
operator|!
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
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
name|SET_SENSITIVE
argument_list|(
literal|"image-convert-rgb"
argument_list|,
name|gimage
operator|&&
operator|!
name|is_rgb
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-convert-grayscale"
argument_list|,
name|gimage
operator|&&
operator|!
name|is_gray
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-convert-indexed"
argument_list|,
name|gimage
operator|&&
operator|!
name|is_indexed
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-flip-horizontal"
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-flip-vertical"
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-rotate-90"
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-rotate-180"
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-rotate-270"
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-resize"
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-scale"
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-crop"
argument_list|,
name|gimage
operator|&&
name|sel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-duplicate"
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-merge-layers"
argument_list|,
name|gimage
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|aux
operator|&&
name|lp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-flatten"
argument_list|,
name|gimage
operator|&&
operator|!
name|fs
operator|&&
operator|!
name|aux
operator|&&
name|lp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-configure-grid"
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

