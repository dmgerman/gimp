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
file|"libgimpbase/gimpbase.h"
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
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"tips-dialog.h"
end_include

begin_include
include|#
directive|include
file|"tips-parser.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b0711aa0103
block|{
DECL|enumerator|RESPONSE_PREVIOUS
name|RESPONSE_PREVIOUS
init|=
literal|1
block|,
DECL|enumerator|RESPONSE_NEXT
name|RESPONSE_NEXT
init|=
literal|2
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|tips_dialog_set_tip
parameter_list|(
name|GimpTip
modifier|*
name|tip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tips_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tips_dialog_destroy
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpGuiConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|more_button_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|tips_dialog
specifier|static
name|GtkWidget
modifier|*
name|tips_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tip_label
specifier|static
name|GtkWidget
modifier|*
name|tip_label
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|more_button
specifier|static
name|GtkWidget
modifier|*
name|more_button
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tips
specifier|static
name|GList
modifier|*
name|tips
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|current_tip
specifier|static
name|GList
modifier|*
name|current_tip
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkWidget
modifier|*
DECL|function|tips_dialog_create (Gimp * gimp)
name|tips_dialog_create
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
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
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|gint
name|tips_count
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tips
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
literal|"tips"
argument_list|,
literal|"gimp-tips.xml"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tips
operator|=
name|gimp_tips_from_file
argument_list|(
name|filename
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tips
condition|)
block|{
name|GimpTip
modifier|*
name|tip
decl_stmt|;
if|if
condition|(
operator|!
name|error
condition|)
block|{
name|tip
operator|=
name|gimp_tip_new
argument_list|(
name|_
argument_list|(
literal|"The GIMP tips file is empty!"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|error
operator|->
name|code
operator|==
name|G_FILE_ERROR_NOENT
condition|)
block|{
name|tip
operator|=
name|gimp_tip_new
argument_list|(
name|_
argument_list|(
literal|"The GIMP tips file appears to be "
literal|"missing!"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"There should be a file called '%s'. "
literal|"Please check your installation."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tip
operator|=
name|gimp_tip_new
argument_list|(
name|_
argument_list|(
literal|"The GIMP tips file could not be parsed!"
argument_list|)
argument_list|,
literal|"%s"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
name|tips
operator|=
name|g_list_prepend
argument_list|(
name|tips
argument_list|,
name|tip
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|error
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Error while parsing '%s': %s\n"
argument_list|,
name|filename
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|tips_count
operator|=
name|g_list_length
argument_list|(
name|tips
argument_list|)
expr_stmt|;
name|config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|last_tip_shown
operator|>=
name|tips_count
operator|||
name|config
operator|->
name|last_tip_shown
operator|<
literal|0
condition|)
name|config
operator|->
name|last_tip_shown
operator|=
literal|0
expr_stmt|;
name|current_tip
operator|=
name|g_list_nth
argument_list|(
name|tips
argument_list|,
name|config
operator|->
name|last_tip_shown
argument_list|)
expr_stmt|;
if|if
condition|(
name|tips_dialog
condition|)
return|return
name|tips_dialog
return|;
name|tips_dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"GIMP Tip of the Day"
argument_list|)
argument_list|,
literal|"gimp-tip-of-the-day"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_dialog_add_button
argument_list|(
name|GTK_DIALOG
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Previous Tip"
argument_list|)
argument_list|,
name|RESPONSE_PREVIOUS
argument_list|)
expr_stmt|;
name|gtk_button_set_image
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|gtk_image_new_from_icon_name
argument_list|(
literal|"go-previous"
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_dialog_add_button
argument_list|(
name|GTK_DIALOG
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Next Tip"
argument_list|)
argument_list|,
name|RESPONSE_NEXT
argument_list|)
expr_stmt|;
name|gtk_button_set_image
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|gtk_image_new_from_icon_name
argument_list|(
literal|"go-next"
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_dialog_set_response_sensitive
argument_list|(
name|GTK_DIALOG
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
name|RESPONSE_NEXT
argument_list|,
name|tips_count
operator|>
literal|1
argument_list|)
expr_stmt|;
name|gtk_dialog_set_response_sensitive
argument_list|(
name|GTK_DIALOG
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
name|RESPONSE_PREVIOUS
argument_list|,
name|tips_count
operator|>
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|tips_dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tips_dialog_response
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|tips_dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tips_dialog_destroy
argument_list|)
argument_list|,
name|config
argument_list|)
expr_stmt|;
name|vbox
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
name|vbox
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
name|tips_dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|vbox
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
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
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
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
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
name|hbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|GIMP_STOCK_INFO
argument_list|,
name|GTK_ICON_SIZE_DIALOG
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|image
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|image
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
name|image
argument_list|)
expr_stmt|;
name|gtk_container_set_focus_chain
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tip_label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_selectable
argument_list|(
name|GTK_LABEL
argument_list|(
name|tip_label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|tip_label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|tip_label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|tip_label
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|tip_label
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
name|tip_label
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|0
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
name|more_button
operator|=
name|gtk_link_button_new_with_label
argument_list|(
literal|"http://docs.gimp.org/"
argument_list|,
comment|/*  a link to the related section in the user manual  */
name|_
argument_list|(
literal|"Learn more"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|more_button
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|more_button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|more_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|more_button_clicked
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|tips_dialog_set_tip
argument_list|(
name|current_tip
operator|->
name|data
argument_list|)
expr_stmt|;
return|return
name|tips_dialog
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_dialog_destroy (GtkWidget * widget,GimpGuiConfig * config)
name|tips_dialog_destroy
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpGuiConfig
modifier|*
name|config
parameter_list|)
block|{
comment|/* the last-shown-tip is saved in sessionrc */
name|config
operator|->
name|last_tip_shown
operator|=
name|g_list_position
argument_list|(
name|tips
argument_list|,
name|current_tip
argument_list|)
expr_stmt|;
name|tips_dialog
operator|=
name|NULL
expr_stmt|;
name|current_tip
operator|=
name|NULL
expr_stmt|;
name|gimp_tips_free
argument_list|(
name|tips
argument_list|)
expr_stmt|;
name|tips
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_dialog_response (GtkWidget * dialog,gint response)
name|tips_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response
parameter_list|)
block|{
switch|switch
condition|(
name|response
condition|)
block|{
case|case
name|RESPONSE_PREVIOUS
case|:
name|current_tip
operator|=
name|current_tip
operator|->
name|prev
condition|?
name|current_tip
operator|->
name|prev
else|:
name|g_list_last
argument_list|(
name|tips
argument_list|)
expr_stmt|;
name|tips_dialog_set_tip
argument_list|(
name|current_tip
operator|->
name|data
argument_list|)
expr_stmt|;
break|break;
case|case
name|RESPONSE_NEXT
case|:
name|current_tip
operator|=
name|current_tip
operator|->
name|next
condition|?
name|current_tip
operator|->
name|next
else|:
name|tips
expr_stmt|;
name|tips_dialog_set_tip
argument_list|(
name|current_tip
operator|->
name|data
argument_list|)
expr_stmt|;
break|break;
default|default:
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_dialog_set_tip (GimpTip * tip)
name|tips_dialog_set_tip
parameter_list|(
name|GimpTip
modifier|*
name|tip
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|tip
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_markup
argument_list|(
name|GTK_LABEL
argument_list|(
name|tip_label
argument_list|)
argument_list|,
name|tip
operator|->
name|text
argument_list|)
expr_stmt|;
comment|/*  set the URI to unset the "visited" state  */
name|gtk_link_button_set_uri
argument_list|(
name|GTK_LINK_BUTTON
argument_list|(
name|more_button
argument_list|)
argument_list|,
literal|"http://docs.gimp.org/"
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|more_button
argument_list|,
name|tip
operator|->
name|help_id
operator|!=
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|more_button_clicked (GtkWidget * button,Gimp * gimp)
name|more_button_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpTip
modifier|*
name|tip
init|=
name|current_tip
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|tip
operator|->
name|help_id
condition|)
name|gimp_help
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|tip
operator|->
name|help_id
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

