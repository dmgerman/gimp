begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"images-actions.h"
end_include

begin_include
include|#
directive|include
file|"images-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|images_actions
specifier|static
specifier|const
name|GimpActionEntry
name|images_actions
index|[]
init|=
block|{
block|{
literal|"images-popup"
block|,
name|GIMP_STOCK_IMAGES
block|,
name|N_
argument_list|(
literal|"Images Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_IMAGE_DIALOG
block|}
block|,
block|{
literal|"images-raise-views"
block|,
name|GTK_STOCK_GOTO_TOP
block|,
name|N_
argument_list|(
literal|"_Raise Views"
argument_list|)
block|,
literal|""
block|,
name|N_
argument_list|(
literal|"Raise this image's displays"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|images_raise_views_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"images-new-view"
block|,
name|GTK_STOCK_NEW
block|,
name|N_
argument_list|(
literal|"_New View"
argument_list|)
block|,
literal|""
block|,
name|N_
argument_list|(
literal|"Create a new display for this image"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|images_new_view_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"images-delete"
block|,
name|GTK_STOCK_DELETE
block|,
name|N_
argument_list|(
literal|"_Delete Image"
argument_list|)
block|,
literal|""
block|,
name|N_
argument_list|(
literal|"Delete this image"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|images_delete_image_cmd_callback
argument_list|)
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|images_actions_setup (GimpActionGroup * group)
name|images_actions_setup
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
name|images_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|images_actions
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|images_actions_update (GimpActionGroup * group,gpointer data)
name|images_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|action_data_get_context
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|context
condition|)
name|image
operator|=
name|gimp_context_get_image
argument_list|(
name|context
argument_list|)
expr_stmt|;
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
literal|"images-raise-views"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"images-new-view"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"images-delete"
argument_list|,
name|image
operator|&&
name|image
operator|->
name|disp_count
operator|==
literal|0
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

