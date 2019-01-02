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
file|"libgimpcolor/gimpcolor.h"
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
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-quick-mask.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/channel-options-dialog.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/item-options-dialog.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"quick-mask-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|RGBA_EPSILON
define|#
directive|define
name|RGBA_EPSILON
value|1e-6
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|quick_mask_configure_callback
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|channel_name
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|channel_color
parameter_list|,
name|gboolean
name|save_selection
parameter_list|,
name|gboolean
name|channel_visible
parameter_list|,
name|gboolean
name|channel_linked
parameter_list|,
name|GimpColorTag
name|channel_color_tag
parameter_list|,
name|gboolean
name|channel_lock_content
parameter_list|,
name|gboolean
name|channel_lock_position
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions */
end_comment

begin_function
name|void
DECL|function|quick_mask_toggle_cmd_callback (GtkAction * action,gpointer data)
name|quick_mask_toggle_cmd_callback
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
name|gboolean
name|active
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|active
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
name|active
operator|!=
name|gimp_image_get_quick_mask_state
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|gimp_image_set_quick_mask_state
argument_list|(
name|image
argument_list|,
name|active
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
DECL|function|quick_mask_invert_cmd_callback (GtkAction * action,GtkAction * current,gpointer data)
name|quick_mask_invert_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GtkAction
modifier|*
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gint
name|value
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|value
operator|=
name|gtk_radio_action_get_current_value
argument_list|(
name|GTK_RADIO_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|!=
name|gimp_image_get_quick_mask_inverted
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|gimp_image_quick_mask_invert
argument_list|(
name|image
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
DECL|function|quick_mask_configure_cmd_callback (GtkAction * action,gpointer data)
name|quick_mask_configure_cmd_callback
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
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
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
DECL|macro|CONFIGURE_DIALOG_KEY
define|#
directive|define
name|CONFIGURE_DIALOG_KEY
value|"gimp-image-quick-mask-configure-dialog"
name|dialog
operator|=
name|dialogs_get_dialog
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
name|CONFIGURE_DIALOG_KEY
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_image_get_quick_mask_color
argument_list|(
name|image
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|channel_options_dialog_new
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|widget
argument_list|,
name|_
argument_list|(
literal|"Quick Mask Attributes"
argument_list|)
argument_list|,
literal|"gimp-quick-mask-edit"
argument_list|,
name|GIMP_ICON_QUICK_MASK_ON
argument_list|,
name|_
argument_list|(
literal|"Edit Quick Mask Attributes"
argument_list|)
argument_list|,
name|GIMP_HELP_QUICK_MASK_EDIT
argument_list|,
name|_
argument_list|(
literal|"Edit Quick Mask Color"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Mask opacity:"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
operator|&
name|color
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GIMP_COLOR_TAG_NONE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|quick_mask_configure_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|item_options_dialog_set_switches_visible
argument_list|(
name|dialog
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dialogs_attach_dialog
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
name|CONFIGURE_DIALOG_KEY
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|quick_mask_configure_callback (GtkWidget * dialog,GimpImage * image,GimpChannel * channel,GimpContext * context,const gchar * channel_name,const GimpRGB * channel_color,gboolean save_selection,gboolean channel_visible,gboolean channel_linked,GimpColorTag channel_color_tag,gboolean channel_lock_content,gboolean channel_lock_position,gpointer user_data)
name|quick_mask_configure_callback
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|channel_name
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|channel_color
parameter_list|,
name|gboolean
name|save_selection
parameter_list|,
name|gboolean
name|channel_visible
parameter_list|,
name|gboolean
name|channel_linked
parameter_list|,
name|GimpColorTag
name|channel_color_tag
parameter_list|,
name|gboolean
name|channel_lock_content
parameter_list|,
name|gboolean
name|channel_lock_position
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpRGB
name|old_color
decl_stmt|;
name|gimp_image_get_quick_mask_color
argument_list|(
name|image
argument_list|,
operator|&
name|old_color
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_rgba_distance
argument_list|(
operator|&
name|old_color
argument_list|,
name|channel_color
argument_list|)
operator|>
name|RGBA_EPSILON
condition|)
block|{
name|gimp_image_set_quick_mask_color
argument_list|(
name|image
argument_list|,
name|channel_color
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

