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
file|"filters-actions.h"
end_include

begin_include
include|#
directive|include
file|"filters-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|filters_actions
specifier|static
specifier|const
name|GimpStringActionEntry
name|filters_actions
index|[]
init|=
block|{
block|{
literal|"filters-color-temperature"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Color T_emperature..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Change the color temperature of the image"
argument_list|)
block|,
literal|"gegl:color-temperature"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_COLOR_TEMPERATURE */
block|}
block|,
block|{
literal|"filters-color-to-alpha"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Color to _Alpha..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Convert a specified color to transparency"
argument_list|)
block|,
literal|"gegl:color-to-alpha"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_COLOR_TO_ALPHA */
block|}
block|,
block|{
literal|"filters-gaussian-blur"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Gaussian Blur..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Apply a gaussian blur"
argument_list|)
block|,
literal|"gegl:gaussian-blur"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_GAUSSIAN_BLUR */
block|}
block|,
block|{
literal|"filters-pixelize"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Pixelize..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Simplify image into an array of solid-colored squares"
argument_list|)
block|,
literal|"gegl:pixelize"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_PIXELIZE */
block|}
block|,
block|{
literal|"filters-polar-coordinates"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"P_olar Coordinates..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Convert image to or from polar coordinates"
argument_list|)
block|,
literal|"gegl:polar-coordinates"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_POLAR_COORDINATES */
block|}
block|,
block|{
literal|"filters-threshold-alpha"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Threshold Alpha..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Make transparency all-or-nothing"
argument_list|)
block|,
literal|"gimp:threshold-alpha"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_POLAR_COORDINATES */
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|filters_actions_setup (GimpActionGroup * group)
name|filters_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_add_string_actions
argument_list|(
name|group
argument_list|,
literal|"filters-action"
argument_list|,
name|filters_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|filters_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|filters_filter_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|filters_actions_update (GimpActionGroup * group,gpointer data)
name|filters_actions_update
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
name|writable
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|gray
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|alpha
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
name|alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gray
operator|=
name|gimp_drawable_is_gray
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
name|writable
operator|=
operator|!
name|gimp_item_is_content_locked
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
name|writable
operator|=
name|FALSE
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
name|SET_SENSITIVE
argument_list|(
literal|"filters-color-temperature"
argument_list|,
name|writable
operator|&&
operator|!
name|gray
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-color-to-alpha"
argument_list|,
name|writable
operator|&&
operator|!
name|gray
operator|&&
name|alpha
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-gaussian-blur"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-pixelize"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-polar-coordinates"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-threshold-alpha"
argument_list|,
name|writable
operator|&&
name|alpha
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

