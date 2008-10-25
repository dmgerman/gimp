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
file|"libgimpmath/gimpmath.h"
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
file|"core/gimpchannel-select.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpselection.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpstrokeoptions.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/stroke-dialog.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"select-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|select_feather_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|select_border_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|select_grow_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|select_shrink_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|select_feather_radius
specifier|static
name|gdouble
name|select_feather_radius
init|=
literal|5.0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|select_grow_pixels
specifier|static
name|gint
name|select_grow_pixels
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|select_shrink_pixels
specifier|static
name|gint
name|select_shrink_pixels
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|select_shrink_edge_lock
specifier|static
name|gboolean
name|select_shrink_edge_lock
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|select_border_radius
specifier|static
name|gint
name|select_border_radius
init|=
literal|5
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|select_border_feather
specifier|static
name|gboolean
name|select_border_feather
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|select_border_edge_lock
specifier|static
name|gboolean
name|select_border_edge_lock
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|select_invert_cmd_callback (GtkAction * action,gpointer data)
name|select_invert_cmd_callback
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
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_channel_invert
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_all_cmd_callback (GtkAction * action,gpointer data)
name|select_all_cmd_callback
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
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_channel_all
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_none_cmd_callback (GtkAction * action,gpointer data)
name|select_none_cmd_callback
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
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_channel_clear
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_float_cmd_callback (GtkAction * action,gpointer data)
name|select_float_cmd_callback
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
name|GError
modifier|*
name|error
init|=
name|NULL
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
if|if
condition|(
name|gimp_selection_float
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_message
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
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
name|void
DECL|function|select_feather_cmd_callback (GtkAction * action,gpointer data)
name|select_feather_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|display
operator|->
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_query_size_box
argument_list|(
name|_
argument_list|(
literal|"Feather Selection"
argument_list|)
argument_list|,
name|display
operator|->
name|shell
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_SELECTION_FEATHER
argument_list|,
name|_
argument_list|(
literal|"Feather selection by"
argument_list|)
argument_list|,
name|select_feather_radius
argument_list|,
literal|0
argument_list|,
literal|32767
argument_list|,
literal|3
argument_list|,
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
operator|->
name|unit
argument_list|,
name|MIN
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|G_OBJECT
argument_list|(
name|display
operator|->
name|image
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|select_feather_callback
argument_list|,
name|display
operator|->
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_sharpen_cmd_callback (GtkAction * action,gpointer data)
name|select_sharpen_cmd_callback
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
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_channel_sharpen
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_shrink_cmd_callback (GtkAction * action,gpointer data)
name|select_shrink_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|display
operator|->
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_query_size_box
argument_list|(
name|_
argument_list|(
literal|"Shrink Selection"
argument_list|)
argument_list|,
name|display
operator|->
name|shell
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_SELECTION_SHRINK
argument_list|,
name|_
argument_list|(
literal|"Shrink selection by"
argument_list|)
argument_list|,
name|select_shrink_pixels
argument_list|,
literal|1
argument_list|,
literal|32767
argument_list|,
literal|0
argument_list|,
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
operator|->
name|unit
argument_list|,
name|MIN
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|G_OBJECT
argument_list|(
name|display
operator|->
name|image
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|select_shrink_callback
argument_list|,
name|display
operator|->
name|image
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Shrink from image border"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GIMP_QUERY_BOX_VBOX
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"edge-lock-toggle"
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
operator|!
name|select_shrink_edge_lock
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_grow_cmd_callback (GtkAction * action,gpointer data)
name|select_grow_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|display
operator|->
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_query_size_box
argument_list|(
name|_
argument_list|(
literal|"Grow Selection"
argument_list|)
argument_list|,
name|display
operator|->
name|shell
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_SELECTION_GROW
argument_list|,
name|_
argument_list|(
literal|"Grow selection by"
argument_list|)
argument_list|,
name|select_grow_pixels
argument_list|,
literal|1
argument_list|,
literal|32767
argument_list|,
literal|0
argument_list|,
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
operator|->
name|unit
argument_list|,
name|MIN
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|G_OBJECT
argument_list|(
name|display
operator|->
name|image
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|select_grow_callback
argument_list|,
name|display
operator|->
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_border_cmd_callback (GtkAction * action,gpointer data)
name|select_border_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|display
operator|->
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_query_size_box
argument_list|(
name|_
argument_list|(
literal|"Border Selection"
argument_list|)
argument_list|,
name|display
operator|->
name|shell
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_SELECTION_BORDER
argument_list|,
name|_
argument_list|(
literal|"Border selection by"
argument_list|)
argument_list|,
name|select_border_radius
argument_list|,
literal|1
argument_list|,
literal|32767
argument_list|,
literal|0
argument_list|,
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
operator|->
name|unit
argument_list|,
name|MIN
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|G_OBJECT
argument_list|(
name|display
operator|->
name|image
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|select_border_callback
argument_list|,
name|display
operator|->
name|image
argument_list|)
expr_stmt|;
comment|/* Feather button */
name|button
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Feather border"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GIMP_QUERY_BOX_VBOX
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"border-feather-toggle"
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|select_border_feather
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
comment|/* Edge lock button */
name|button
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Lock selection to image edges"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GIMP_QUERY_BOX_VBOX
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"edge-lock-toggle"
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|select_border_edge_lock
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_save_cmd_callback (GtkAction * action,gpointer data)
name|select_save_cmd_callback
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
name|gimp_selection_save
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dock_factory
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-channel-list"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_stroke_cmd_callback (GtkAction * action,gpointer data)
name|select_stroke_cmd_callback
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
name|GimpDrawable
modifier|*
name|drawable
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
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
block|{
name|gimp_message
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
argument_list|,
name|_
argument_list|(
literal|"There is no active layer or channel to stroke to."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|dialog
operator|=
name|stroke_dialog_new
argument_list|(
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Stroke Selection"
argument_list|)
argument_list|,
name|GIMP_STOCK_SELECTION_STROKE
argument_list|,
name|GIMP_HELP_SELECTION_STROKE
argument_list|,
name|widget
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_stroke_last_vals_cmd_callback (GtkAction * action,gpointer data)
name|select_stroke_last_vals_cmd_callback
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GimpStrokeOptions
modifier|*
name|options
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|return_if_no_image
argument_list|(
name|image
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_context
argument_list|(
name|context
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
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
block|{
name|gimp_message
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
argument_list|,
name|_
argument_list|(
literal|"There is no active layer or channel to stroke to."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|options
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
argument_list|,
literal|"saved-stroke-options"
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
condition|)
name|g_object_ref
argument_list|(
name|options
argument_list|)
expr_stmt|;
else|else
name|options
operator|=
name|gimp_stroke_options_new
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|context
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_item_stroke
argument_list|(
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|context
argument_list|,
name|options
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
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
else|else
block|{
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|options
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
DECL|function|select_feather_callback (GtkWidget * widget,gdouble size,GimpUnit unit,gpointer data)
name|select_feather_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_IMAGE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gdouble
name|radius_x
decl_stmt|;
name|gdouble
name|radius_y
decl_stmt|;
name|radius_x
operator|=
name|radius_y
operator|=
name|select_feather_radius
operator|=
name|size
expr_stmt|;
if|if
condition|(
name|unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gdouble
name|factor
decl_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|factor
operator|=
operator|(
name|MAX
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
operator|/
name|MIN
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|xres
operator|==
name|MIN
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
condition|)
name|radius_y
operator|*=
name|factor
expr_stmt|;
else|else
name|radius_x
operator|*=
name|factor
expr_stmt|;
block|}
name|gimp_channel_feather
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|radius_x
argument_list|,
name|radius_y
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_border_callback (GtkWidget * widget,gdouble size,GimpUnit unit,gpointer data)
name|select_border_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_IMAGE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|feather_button
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"border-feather-toggle"
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|edge_lock_button
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"edge-lock-toggle"
argument_list|)
decl_stmt|;
name|gdouble
name|radius_x
decl_stmt|;
name|gdouble
name|radius_y
decl_stmt|;
name|radius_x
operator|=
name|radius_y
operator|=
name|select_border_radius
operator|=
name|ROUND
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|select_border_feather
operator|=
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|feather_button
argument_list|)
argument_list|)
expr_stmt|;
name|select_border_edge_lock
operator|=
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|edge_lock_button
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gdouble
name|factor
decl_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|factor
operator|=
operator|(
name|MAX
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
operator|/
name|MIN
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|xres
operator|==
name|MIN
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
condition|)
name|radius_y
operator|*=
name|factor
expr_stmt|;
else|else
name|radius_x
operator|*=
name|factor
expr_stmt|;
block|}
name|gimp_channel_border
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|radius_x
argument_list|,
name|radius_y
argument_list|,
name|select_border_feather
argument_list|,
name|select_border_edge_lock
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_grow_callback (GtkWidget * widget,gdouble size,GimpUnit unit,gpointer data)
name|select_grow_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_IMAGE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gdouble
name|radius_x
decl_stmt|;
name|gdouble
name|radius_y
decl_stmt|;
name|radius_x
operator|=
name|radius_y
operator|=
name|select_grow_pixels
operator|=
name|ROUND
argument_list|(
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gdouble
name|factor
decl_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|factor
operator|=
operator|(
name|MAX
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
operator|/
name|MIN
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|xres
operator|==
name|MIN
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
condition|)
name|radius_y
operator|*=
name|factor
expr_stmt|;
else|else
name|radius_x
operator|*=
name|factor
expr_stmt|;
block|}
name|gimp_channel_grow
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|radius_x
argument_list|,
name|radius_y
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_shrink_callback (GtkWidget * widget,gdouble size,GimpUnit unit,gpointer data)
name|select_shrink_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_IMAGE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|button
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"edge-lock-toggle"
argument_list|)
decl_stmt|;
name|gint
name|radius_x
decl_stmt|;
name|gint
name|radius_y
decl_stmt|;
name|radius_x
operator|=
name|radius_y
operator|=
name|select_shrink_pixels
operator|=
name|ROUND
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|select_shrink_edge_lock
operator|=
operator|!
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gdouble
name|factor
decl_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|factor
operator|=
operator|(
name|MAX
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
operator|/
name|MIN
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|xres
operator|==
name|MIN
argument_list|(
name|xres
argument_list|,
name|yres
argument_list|)
condition|)
name|radius_y
operator|*=
name|factor
expr_stmt|;
else|else
name|radius_x
operator|*=
name|factor
expr_stmt|;
block|}
name|gimp_channel_shrink
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|radius_x
argument_list|,
name|radius_y
argument_list|,
name|select_shrink_edge_lock
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

