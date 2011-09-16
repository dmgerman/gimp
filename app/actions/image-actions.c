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
file|"core/gimpitemstack.h"
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
specifier|const
name|GimpActionEntry
name|image_actions
index|[]
init|=
block|{
block|{
literal|"image-menubar"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
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
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
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
literal|"image-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"_Image"
argument_list|)
block|}
block|,
block|{
literal|"image-mode-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"_Mode"
argument_list|)
block|}
block|,
block|{
literal|"image-transform-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"_Transform"
argument_list|)
block|}
block|,
block|{
literal|"image-guides-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"_Guides"
argument_list|)
block|}
block|,
block|{
literal|"colors-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"_Colors"
argument_list|)
block|}
block|,
block|{
literal|"colors-info-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"I_nfo"
argument_list|)
block|}
block|,
block|{
literal|"colors-auto-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"_Auto"
argument_list|)
block|}
block|,
block|{
literal|"colors-map-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"_Map"
argument_list|)
block|}
block|,
block|{
literal|"colors-components-menu"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"C_omponents"
argument_list|)
block|}
block|,
block|{
literal|"image-new"
block|,
name|GTK_STOCK_NEW
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"_New..."
argument_list|)
block|,
literal|"<primary>N"
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Create a new image"
argument_list|)
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
literal|"image-resize"
block|,
name|GIMP_STOCK_RESIZE
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Can_vas Size..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Adjust the image dimensions"
argument_list|)
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
literal|"image-resize-to-layers"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Fit Canvas to L_ayers"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Resize the image to enclose all layers"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|image_resize_to_layers_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_IMAGE_RESIZE_TO_LAYERS
block|}
block|,
block|{
literal|"image-resize-to-selection"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"F_it Canvas to Selection"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Resize the image to the extents of the selection"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|image_resize_to_selection_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_IMAGE_RESIZE_TO_SELECTION
block|}
block|,
block|{
literal|"image-print-size"
block|,
name|GIMP_STOCK_PRINT_RESOLUTION
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"_Print Size..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Adjust the print resolution"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|image_print_size_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_IMAGE_PRINT_SIZE
block|}
block|,
block|{
literal|"image-scale"
block|,
name|GIMP_STOCK_SCALE
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"_Scale Image..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Change the size of the image content"
argument_list|)
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
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"_Crop to Selection"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Crop the image to the extents of the selection"
argument_list|)
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
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"_Duplicate"
argument_list|)
block|,
literal|"<primary>D"
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Create a duplicate of this image"
argument_list|)
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
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Merge Visible _Layers..."
argument_list|)
block|,
literal|"<primary>M"
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Merge all visible layers into one layer"
argument_list|)
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
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"_Flatten Image"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Merge all layers into one and remove transparency"
argument_list|)
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
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Configure G_rid..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Configure the grid for this image"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|image_configure_grid_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_IMAGE_GRID
block|}
block|,
block|{
literal|"image-properties"
block|,
name|GTK_STOCK_INFO
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Image Pr_operties"
argument_list|)
block|,
literal|"<alt>Return"
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Display information about this image"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|image_properties_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_IMAGE_PROPERTIES
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_convert_actions
specifier|static
specifier|const
name|GimpRadioActionEntry
name|image_convert_actions
index|[]
init|=
block|{
block|{
literal|"image-convert-rgb"
block|,
name|GIMP_STOCK_CONVERT_RGB
block|,
name|NC_
argument_list|(
literal|"image-convert-action"
argument_list|,
literal|"_RGB"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-convert-action"
argument_list|,
literal|"Convert the image to the RGB colorspace"
argument_list|)
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
name|NC_
argument_list|(
literal|"image-convert-action"
argument_list|,
literal|"_Grayscale"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-convert-action"
argument_list|,
literal|"Convert the image to grayscale"
argument_list|)
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
name|NC_
argument_list|(
literal|"image-convert-action"
argument_list|,
literal|"_Indexed..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-convert-action"
argument_list|,
literal|"Convert the image to indexed colors"
argument_list|)
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
specifier|const
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
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Flip _Horizontally"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Flip image horizontally"
argument_list|)
block|,
name|GIMP_ORIENTATION_HORIZONTAL
block|,
name|FALSE
block|,
name|GIMP_HELP_IMAGE_FLIP_HORIZONTAL
block|}
block|,
block|{
literal|"image-flip-vertical"
block|,
name|GIMP_STOCK_FLIP_VERTICAL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Flip _Vertically"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Flip image vertically"
argument_list|)
block|,
name|GIMP_ORIENTATION_VERTICAL
block|,
name|FALSE
block|,
name|GIMP_HELP_IMAGE_FLIP_VERTICAL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_rotate_actions
specifier|static
specifier|const
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
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Rotate 90Â° _clockwise"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Rotate the image 90 degrees to the right"
argument_list|)
block|,
name|GIMP_ROTATE_90
block|,
name|FALSE
block|,
name|GIMP_HELP_IMAGE_ROTATE_90
block|}
block|,
block|{
literal|"image-rotate-180"
block|,
name|GIMP_STOCK_ROTATE_180
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Rotate _180Â°"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Turn the image upside-down"
argument_list|)
block|,
name|GIMP_ROTATE_180
block|,
name|FALSE
block|,
name|GIMP_HELP_IMAGE_ROTATE_180
block|}
block|,
block|{
literal|"image-rotate-270"
block|,
name|GIMP_STOCK_ROTATE_270
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Rotate 90Â° counter-clock_wise"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"image-action"
argument_list|,
literal|"Rotate the image 90 degrees to the left"
argument_list|)
block|,
name|GIMP_ROTATE_270
block|,
name|FALSE
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
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
literal|"image-action"
argument_list|,
name|image_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|image_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_radio_actions
argument_list|(
name|group
argument_list|,
literal|"image-convert-action"
argument_list|,
name|image_convert_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|image_convert_actions
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|0
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
literal|"image-action"
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
literal|"image-action"
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
literal|"image-rotate-90"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_ALWAYS_SHOW_IMAGE
argument_list|(
literal|"image-rotate-180"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_ALWAYS_SHOW_IMAGE
argument_list|(
literal|"image-rotate-270"
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
name|image
init|=
name|action_data_get_image
argument_list|(
name|data
argument_list|)
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
name|gboolean
name|groups
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|GimpContainer
modifier|*
name|layers
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|action
init|=
name|NULL
decl_stmt|;
switch|switch
condition|(
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB
case|:
name|action
operator|=
literal|"image-convert-rgb"
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY
case|:
name|action
operator|=
literal|"image-convert-grayscale"
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED
case|:
name|action
operator|=
literal|"image-convert-indexed"
expr_stmt|;
break|break;
block|}
name|gimp_action_group_set_action_active
argument_list|(
name|group
argument_list|,
name|action
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|aux
operator|=
operator|(
name|gimp_image_get_active_channel
argument_list|(
name|image
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
name|image
argument_list|)
expr_stmt|;
name|sel
operator|=
operator|!
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|layers
operator|=
name|gimp_image_get_layers
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|groups
operator|=
operator|!
name|gimp_item_stack_is_flat
argument_list|(
name|GIMP_ITEM_STACK
argument_list|(
name|layers
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
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-convert-grayscale"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-convert-indexed"
argument_list|,
name|image
operator|&&
operator|!
name|groups
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-flip-horizontal"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-flip-vertical"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-rotate-90"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-rotate-180"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-rotate-270"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-resize"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-resize-to-layers"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-resize-to-selection"
argument_list|,
name|image
operator|&&
name|sel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-print-size"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-scale"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-crop"
argument_list|,
name|image
operator|&&
name|sel
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-duplicate"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-merge-layers"
argument_list|,
name|image
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
name|image
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
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"image-properties"
argument_list|,
name|image
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

