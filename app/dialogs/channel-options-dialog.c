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
file|"dialogs-types.h"
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
file|"widgets/gimpcolorpanel.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpspinscale.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"channel-options-dialog.h"
end_include

begin_include
include|#
directive|include
file|"item-options-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|ChannelOptionsDialog
typedef|typedef
name|struct
name|_ChannelOptionsDialog
name|ChannelOptionsDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_ChannelOptionsDialog
struct|struct
name|_ChannelOptionsDialog
block|{
DECL|member|callback
name|GimpChannelOptionsCallback
name|callback
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|member|color_panel
name|GtkWidget
modifier|*
name|color_panel
decl_stmt|;
DECL|member|save_sel_toggle
name|GtkWidget
modifier|*
name|save_sel_toggle
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|channel_options_dialog_free
parameter_list|(
name|ChannelOptionsDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|channel_options_dialog_callback
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|item_name
parameter_list|,
name|gboolean
name|item_visible
parameter_list|,
name|gboolean
name|item_linked
parameter_list|,
name|GimpColorTag
name|item_color_tag
parameter_list|,
name|gboolean
name|item_lock_content
parameter_list|,
name|gboolean
name|item_lock_position
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|channel_options_opacity_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpColorButton
modifier|*
name|color_button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|channel_options_color_changed
parameter_list|(
name|GimpColorButton
modifier|*
name|color_button
parameter_list|,
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|channel_options_dialog_new (GimpImage * image,GimpChannel * channel,GimpContext * context,GtkWidget * parent,const gchar * title,const gchar * role,const gchar * icon_name,const gchar * desc,const gchar * help_id,const gchar * color_label,const gchar * opacity_label,gboolean show_from_sel,const gchar * channel_name,const GimpRGB * channel_color,gboolean channel_visible,gboolean channel_linked,GimpColorTag channel_color_tag,gboolean channel_lock_content,gboolean channel_lock_position,GimpChannelOptionsCallback callback,gpointer user_data)
name|channel_options_dialog_new
parameter_list|(
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
name|GtkWidget
modifier|*
name|parent
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|color_label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|opacity_label
parameter_list|,
name|gboolean
name|show_from_sel
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
name|GimpChannelOptionsCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|ChannelOptionsDialog
modifier|*
name|private
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkAdjustment
modifier|*
name|opacity_adj
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|channel
operator|==
name|NULL
operator|||
name|GIMP_IS_CHANNEL
argument_list|(
name|channel
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|role
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|icon_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|desc
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|channel_color
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|color_label
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|opacity_label
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|callback
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_slice_new0
argument_list|(
name|ChannelOptionsDialog
argument_list|)
expr_stmt|;
name|private
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|private
operator|->
name|user_data
operator|=
name|user_data
expr_stmt|;
name|dialog
operator|=
name|item_options_dialog_new
argument_list|(
name|image
argument_list|,
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|,
name|context
argument_list|,
name|parent
argument_list|,
name|title
argument_list|,
name|role
argument_list|,
name|icon_name
argument_list|,
name|desc
argument_list|,
name|help_id
argument_list|,
name|channel_name
condition|?
name|_
argument_list|(
literal|"Channel _name:"
argument_list|)
else|:
name|NULL
argument_list|,
name|GIMP_STOCK_TOOL_PAINTBRUSH
argument_list|,
name|_
argument_list|(
literal|"Lock _pixels"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Lock position and _size"
argument_list|)
argument_list|,
name|channel_name
argument_list|,
name|channel_visible
argument_list|,
name|channel_linked
argument_list|,
name|channel_color_tag
argument_list|,
name|channel_lock_content
argument_list|,
name|channel_lock_position
argument_list|,
name|channel_options_dialog_callback
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|channel_options_dialog_free
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|opacity_adj
operator|=
operator|(
name|GtkAdjustment
operator|*
operator|)
name|gtk_adjustment_new
argument_list|(
name|channel_color
operator|->
name|a
operator|*
literal|100.0
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gimp_spin_scale_new
argument_list|(
name|opacity_adj
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|scale
argument_list|,
literal|200
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|item_options_dialog_add_widget
argument_list|(
name|dialog
argument_list|,
name|opacity_label
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|private
operator|->
name|color_panel
operator|=
name|gimp_color_panel_new
argument_list|(
name|color_label
argument_list|,
name|channel_color
argument_list|,
name|GIMP_COLOR_AREA_LARGE_CHECKS
argument_list|,
literal|24
argument_list|,
literal|24
argument_list|)
expr_stmt|;
name|gimp_color_panel_set_context
argument_list|(
name|GIMP_COLOR_PANEL
argument_list|(
name|private
operator|->
name|color_panel
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|opacity_adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|channel_options_opacity_changed
argument_list|)
argument_list|,
name|private
operator|->
name|color_panel
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|private
operator|->
name|color_panel
argument_list|,
literal|"color-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|channel_options_color_changed
argument_list|)
argument_list|,
name|opacity_adj
argument_list|)
expr_stmt|;
name|item_options_dialog_add_widget
argument_list|(
name|dialog
argument_list|,
name|NULL
argument_list|,
name|private
operator|->
name|color_panel
argument_list|)
expr_stmt|;
if|if
condition|(
name|show_from_sel
condition|)
block|{
name|private
operator|->
name|save_sel_toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Initialize from _selection"
argument_list|)
argument_list|)
expr_stmt|;
name|item_options_dialog_add_widget
argument_list|(
name|dialog
argument_list|,
name|NULL
argument_list|,
name|private
operator|->
name|save_sel_toggle
argument_list|)
expr_stmt|;
block|}
return|return
name|dialog
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|channel_options_dialog_free (ChannelOptionsDialog * private)
name|channel_options_dialog_free
parameter_list|(
name|ChannelOptionsDialog
modifier|*
name|private
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|ChannelOptionsDialog
argument_list|,
name|private
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|channel_options_dialog_callback (GtkWidget * dialog,GimpImage * image,GimpItem * item,GimpContext * context,const gchar * item_name,gboolean item_visible,gboolean item_linked,GimpColorTag item_color_tag,gboolean item_lock_content,gboolean item_lock_position,gpointer user_data)
name|channel_options_dialog_callback
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|item_name
parameter_list|,
name|gboolean
name|item_visible
parameter_list|,
name|gboolean
name|item_linked
parameter_list|,
name|GimpColorTag
name|item_color_tag
parameter_list|,
name|gboolean
name|item_lock_content
parameter_list|,
name|gboolean
name|item_lock_position
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|ChannelOptionsDialog
modifier|*
name|private
init|=
name|user_data
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gboolean
name|save_selection
init|=
name|FALSE
decl_stmt|;
name|gimp_color_button_get_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|private
operator|->
name|color_panel
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|save_sel_toggle
condition|)
name|save_selection
operator|=
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|private
operator|->
name|save_sel_toggle
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|->
name|callback
argument_list|(
name|dialog
argument_list|,
name|image
argument_list|,
name|GIMP_CHANNEL
argument_list|(
name|item
argument_list|)
argument_list|,
name|context
argument_list|,
name|item_name
argument_list|,
operator|&
name|color
argument_list|,
name|save_selection
argument_list|,
name|item_visible
argument_list|,
name|item_linked
argument_list|,
name|item_color_tag
argument_list|,
name|item_lock_content
argument_list|,
name|item_lock_position
argument_list|,
name|private
operator|->
name|user_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|channel_options_opacity_changed (GtkAdjustment * adjustment,GimpColorButton * color_button)
name|channel_options_opacity_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpColorButton
modifier|*
name|color_button
parameter_list|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_color_button_get_color
argument_list|(
name|color_button
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_rgb_set_alpha
argument_list|(
operator|&
name|color
argument_list|,
name|gtk_adjustment_get_value
argument_list|(
name|adjustment
argument_list|)
operator|/
literal|100.0
argument_list|)
expr_stmt|;
name|gimp_color_button_set_color
argument_list|(
name|color_button
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|channel_options_color_changed (GimpColorButton * button,GtkAdjustment * adjustment)
name|channel_options_color_changed
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|,
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_color_button_get_color
argument_list|(
name|button
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|adjustment
argument_list|,
name|color
operator|.
name|a
operator|*
literal|100.0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

