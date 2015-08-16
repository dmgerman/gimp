begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * color-profile-dialog.h  * Copyright (C) 2015 Michael Natterer<mitch@gimp.org>  *  * Partly based on the lcms plug-in  * Copyright (C) 2006, 2007  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
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
file|"config/gimpcoreconfig.h"
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
file|"core/gimpimage-color-profile.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"color-profile-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2936f6150108
block|{
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|main_vbox
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
DECL|member|combo
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|progress
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
DECL|member|config
name|GimpColorConfig
modifier|*
name|config
decl_stmt|;
DECL|member|convert
name|gboolean
name|convert
decl_stmt|;
DECL|member|intent
name|GimpColorRenderingIntent
name|intent
decl_stmt|;
DECL|member|bpc
name|gboolean
name|bpc
decl_stmt|;
DECL|typedef|ProfileDialog
block|}
name|ProfileDialog
typedef|;
end_typedef

begin_function_decl
specifier|static
name|ProfileDialog
modifier|*
name|color_profile_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gboolean
name|convert
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|color_profile_combo_box_new
parameter_list|(
name|ProfileDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_profile_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ProfileDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_profile_dialog_free
parameter_list|(
name|ProfileDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  defaults  */
end_comment

begin_decl_stmt
DECL|variable|saved_intent
specifier|static
name|GimpColorRenderingIntent
name|saved_intent
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|saved_bpc
specifier|static
name|gboolean
name|saved_bpc
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|color_profile_assign_dialog_new (GimpImage * image,GimpContext * context,GtkWidget * parent,GimpProgress * progress)
name|color_profile_assign_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|ProfileDialog
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|color_profile_dialog_new
argument_list|(
name|image
argument_list|,
name|context
argument_list|,
name|parent
argument_list|,
name|progress
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|dialog
condition|?
name|dialog
operator|->
name|dialog
else|:
name|NULL
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|color_profile_convert_dialog_new (GimpImage * image,GimpContext * context,GtkWidget * parent,GimpProgress * progress)
name|color_profile_convert_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|ProfileDialog
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|color_profile_dialog_new
argument_list|(
name|image
argument_list|,
name|context
argument_list|,
name|parent
argument_list|,
name|progress
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|dialog
condition|?
name|dialog
operator|->
name|dialog
else|:
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|ProfileDialog
modifier|*
DECL|function|color_profile_dialog_new (GimpImage * image,GimpContext * context,GtkWidget * parent,GimpProgress * progress,gboolean convert)
name|color_profile_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gboolean
name|convert
parameter_list|)
block|{
name|ProfileDialog
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GimpColorProfile
modifier|*
name|src_profile
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
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_slice_new0
argument_list|(
name|ProfileDialog
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|image
operator|=
name|image
expr_stmt|;
name|dialog
operator|->
name|progress
operator|=
name|progress
expr_stmt|;
name|dialog
operator|->
name|config
operator|=
name|image
operator|->
name|gimp
operator|->
name|config
operator|->
name|color_management
expr_stmt|;
name|dialog
operator|->
name|convert
operator|=
name|convert
expr_stmt|;
if|if
condition|(
name|saved_intent
operator|==
operator|-
literal|1
condition|)
block|{
name|dialog
operator|->
name|intent
operator|=
name|dialog
operator|->
name|config
operator|->
name|display_intent
expr_stmt|;
name|dialog
operator|->
name|bpc
operator|=
operator|(
name|dialog
operator|->
name|intent
operator|==
name|GIMP_COLOR_RENDERING_INTENT_RELATIVE_COLORIMETRIC
operator|)
expr_stmt|;
block|}
else|else
block|{
name|dialog
operator|->
name|intent
operator|=
name|saved_intent
expr_stmt|;
name|dialog
operator|->
name|bpc
operator|=
name|saved_bpc
expr_stmt|;
block|}
if|if
condition|(
name|convert
condition|)
block|{
name|dialog
operator|->
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image
argument_list|)
argument_list|,
name|context
argument_list|,
name|_
argument_list|(
literal|"Convert to ICC Color Profile"
argument_list|)
argument_list|,
literal|"gimp-image-color-profile-convert"
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Convert the image to a color profile"
argument_list|)
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_IMAGE_COLOR_PROFILE_CONVERT
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_CONVERT
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|dialog
operator|->
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image
argument_list|)
argument_list|,
name|context
argument_list|,
name|_
argument_list|(
literal|"Assign ICC Color Profile"
argument_list|)
argument_list|,
literal|"gimp-image-color-profile-assign"
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Assign a color profile to the image"
argument_list|)
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_IMAGE_COLOR_PROFILE_ASSIGN
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|_
argument_list|(
literal|"_Assign"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|color_profile_dialog_free
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|color_profile_dialog_response
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|main_vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dialog
operator|->
name|main_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|dialog
operator|->
name|main_vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|main_vbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Current Color Profile"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dialog
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|src_profile
operator|=
name|gimp_color_managed_get_color_profile
argument_list|(
name|GIMP_COLOR_MANAGED
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|gimp_color_profile_get_label
argument_list|(
name|src_profile
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|src_profile
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|convert
condition|?
name|_
argument_list|(
literal|"Convert to"
argument_list|)
else|:
name|_
argument_list|(
literal|"Assign"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dialog
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|combo
operator|=
name|color_profile_combo_box_new
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|dialog
operator|->
name|combo
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|combo
argument_list|)
expr_stmt|;
if|if
condition|(
name|convert
condition|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|dialog
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Rendering Intent:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_enum_combo_box_new
argument_list|(
name|GIMP_TYPE_COLOR_RENDERING_INTENT
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|combo
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|combo
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_connect
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|dialog
operator|->
name|intent
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_combo_box_get_active
argument_list|)
argument_list|,
operator|&
name|dialog
operator|->
name|intent
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|combo
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Black Point Compensation"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|dialog
operator|->
name|bpc
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|dialog
operator|->
name|bpc
argument_list|)
expr_stmt|;
block|}
return|return
name|dialog
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|color_profile_combo_box_new (ProfileDialog * dialog)
name|color_profile_combo_box_new
parameter_list|(
name|ProfileDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkWidget
modifier|*
name|chooser
decl_stmt|;
name|gchar
modifier|*
name|history
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|GFile
modifier|*
name|rgb_file
init|=
name|NULL
decl_stmt|;
name|GimpColorProfile
modifier|*
name|profile
init|=
name|NULL
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|chooser
operator|=
name|gimp_color_profile_chooser_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Select destination profile"
argument_list|)
argument_list|)
expr_stmt|;
name|history
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"profilerc"
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_color_profile_combo_box_new
argument_list|(
name|chooser
argument_list|,
name|history
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|history
argument_list|)
expr_stmt|;
name|profile
operator|=
name|gimp_color_config_get_rgb_color_profile
argument_list|(
name|dialog
operator|->
name|config
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
condition|)
block|{
name|rgb_file
operator|=
name|g_file_new_for_path
argument_list|(
name|dialog
operator|->
name|config
operator|->
name|rgb_profile
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|error
condition|)
block|{
name|gimp_message
argument_list|(
name|dialog
operator|->
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
literal|"%s"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|profile
condition|)
block|{
name|profile
operator|=
name|gimp_image_get_builtin_color_profile
argument_list|(
name|dialog
operator|->
name|image
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
name|label
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"RGB workspace (%s)"
argument_list|)
argument_list|,
name|gimp_color_profile_get_label
argument_list|(
name|profile
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
name|gimp_color_profile_combo_box_add_file
argument_list|(
name|GIMP_COLOR_PROFILE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|rgb_file
argument_list|,
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
name|rgb_file
condition|)
name|g_object_unref
argument_list|(
name|rgb_file
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gimp_color_profile_combo_box_set_active_file
argument_list|(
name|GIMP_COLOR_PROFILE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|combo
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_profile_dialog_response (GtkWidget * widget,gint response_id,ProfileDialog * dialog)
name|color_profile_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ProfileDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GimpColorProfile
modifier|*
name|dest_profile
init|=
name|NULL
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|file
operator|=
name|gimp_color_profile_combo_box_get_active_file
argument_list|(
name|GIMP_COLOR_PROFILE_COMBO_BOX
argument_list|(
name|dialog
operator|->
name|combo
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|file
condition|)
block|{
name|dest_profile
operator|=
name|gimp_color_profile_new_from_file
argument_list|(
name|file
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dest_profile
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|dest_profile
operator|=
name|gimp_color_config_get_rgb_color_profile
argument_list|(
name|dialog
operator|->
name|config
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dest_profile
condition|)
block|{
if|if
condition|(
name|error
condition|)
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|dest_profile
operator|=
name|gimp_image_get_builtin_color_profile
argument_list|(
name|dialog
operator|->
name|image
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|dest_profile
argument_list|)
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|dialog
operator|->
name|convert
condition|)
block|{
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
name|label
operator|=
name|gimp_color_profile_get_label
argument_list|(
name|dest_profile
argument_list|)
expr_stmt|;
name|progress
operator|=
name|gimp_progress_start
argument_list|(
name|dialog
operator|->
name|progress
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Converting to '%s'"
argument_list|)
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_image_convert_color_profile
argument_list|(
name|dialog
operator|->
name|image
argument_list|,
name|dest_profile
argument_list|,
name|dialog
operator|->
name|intent
argument_list|,
name|dialog
operator|->
name|bpc
argument_list|,
name|progress
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|saved_intent
operator|=
name|dialog
operator|->
name|intent
expr_stmt|;
name|saved_bpc
operator|=
name|dialog
operator|->
name|bpc
expr_stmt|;
block|}
block|}
else|else
block|{
name|gimp_image_undo_group_start
argument_list|(
name|dialog
operator|->
name|image
argument_list|,
name|GIMP_UNDO_GROUP_PARASITE_ATTACH
argument_list|,
name|_
argument_list|(
literal|"Assign color profile"
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_image_set_color_profile
argument_list|(
name|dialog
operator|->
name|image
argument_list|,
name|dest_profile
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
comment|/*  omg...  */
if|if
condition|(
name|success
condition|)
name|gimp_image_parasite_detach
argument_list|(
name|dialog
operator|->
name|image
argument_list|,
literal|"icc-profile-name"
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|dialog
operator|->
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
name|gimp_image_undo
argument_list|(
name|dialog
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|gimp_image_flush
argument_list|(
name|dialog
operator|->
name|image
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_profile
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|success
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_message
argument_list|(
name|dialog
operator|->
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
literal|"%s"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_profile_dialog_free (ProfileDialog * dialog)
name|color_profile_dialog_free
parameter_list|(
name|ProfileDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|ProfileDialog
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

