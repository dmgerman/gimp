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
file|"gui-types.h"
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
file|"core/gimpimage-qmask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpselection.h"
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
file|"dialogs.h"
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

begin_define
DECL|macro|return_if_no_display (gdisp,data)
define|#
directive|define
name|return_if_no_display
parameter_list|(
name|gdisp
parameter_list|,
name|data
parameter_list|)
define|\
value|if (GIMP_IS_DISPLAY (data)) \     gdisp = data; \   else if (GIMP_IS_GIMP (data)) \     gdisp = gimp_context_get_display (gimp_get_user_context (GIMP (data))); \   else \     gdisp = NULL; \   if (! gdisp) \     return
end_define

begin_define
DECL|macro|return_if_no_image (gimage,data)
define|#
directive|define
name|return_if_no_image
parameter_list|(
name|gimage
parameter_list|,
name|data
parameter_list|)
define|\
value|if (GIMP_IS_DISPLAY (data)) \     gimage = ((GimpDisplay *) data)->gimage; \   else if (GIMP_IS_GIMP (data)) \     gimage = gimp_context_get_image (gimp_get_user_context (GIMP (data))); \   else \     gimage = NULL; \   if (! gimage) \     return
end_define

begin_comment
comment|/*  local functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_image_mask_feather_callback
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
name|gimp_image_mask_border_callback
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
name|gimp_image_mask_grow_callback
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
name|gimp_image_mask_shrink_callback
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
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|selection_feather_radius
specifier|static
name|gdouble
name|selection_feather_radius
init|=
literal|5.0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|selection_border_radius
specifier|static
name|gint
name|selection_border_radius
init|=
literal|5
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|selection_grow_pixels
specifier|static
name|gint
name|selection_grow_pixels
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|selection_shrink_pixels
specifier|static
name|gint
name|selection_shrink_pixels
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|selection_shrink_edge_lock
specifier|static
name|gboolean
name|selection_shrink_edge_lock
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|select_invert_cmd_callback (GtkWidget * widget,gpointer data)
name|select_invert_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_channel_invert
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_all_cmd_callback (GtkWidget * widget,gpointer data)
name|select_all_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_channel_all
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_none_cmd_callback (GtkWidget * widget,gpointer data)
name|select_none_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_channel_clear
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_float_cmd_callback (GtkWidget * widget,gpointer data)
name|select_float_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_selection_float
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_feather_cmd_callback (GtkWidget * widget,gpointer data)
name|select_feather_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GtkWidget
modifier|*
name|qbox
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|qbox
operator|=
name|gimp_query_size_box
argument_list|(
name|_
argument_list|(
literal|"Feather Selection"
argument_list|)
argument_list|,
name|gdisp
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
name|selection_feather_radius
argument_list|,
literal|0
argument_list|,
literal|32767
argument_list|,
literal|3
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|unit
argument_list|,
name|MIN
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|yresolution
argument_list|)
argument_list|,
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
operator|->
name|dot_for_dot
argument_list|,
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|gimp_image_mask_feather_callback
argument_list|,
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|qbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_sharpen_cmd_callback (GtkWidget * widget,gpointer data)
name|select_sharpen_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_channel_sharpen
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_shrink_cmd_callback (GtkWidget * widget,gpointer data)
name|select_shrink_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GtkWidget
modifier|*
name|shrink_dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|edge_lock
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shrink_dialog
operator|=
name|gimp_query_size_box
argument_list|(
name|_
argument_list|(
literal|"Shrink Selection"
argument_list|)
argument_list|,
name|gdisp
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
name|selection_shrink_pixels
argument_list|,
literal|1
argument_list|,
literal|32767
argument_list|,
literal|0
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|unit
argument_list|,
name|MIN
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|yresolution
argument_list|)
argument_list|,
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
operator|->
name|dot_for_dot
argument_list|,
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|gimp_image_mask_shrink_callback
argument_list|,
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|edge_lock
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Shrink from image border"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GIMP_QUERY_BOX_VBOX
argument_list|(
name|shrink_dialog
argument_list|)
argument_list|)
argument_list|,
name|edge_lock
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
name|shrink_dialog
argument_list|)
argument_list|,
literal|"edge_lock_toggle"
argument_list|,
name|edge_lock
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|edge_lock
argument_list|)
argument_list|,
operator|!
name|selection_shrink_edge_lock
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|edge_lock
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|shrink_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_grow_cmd_callback (GtkWidget * widget,gpointer data)
name|select_grow_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GtkWidget
modifier|*
name|qbox
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|qbox
operator|=
name|gimp_query_size_box
argument_list|(
name|_
argument_list|(
literal|"Grow Selection"
argument_list|)
argument_list|,
name|gdisp
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
name|selection_grow_pixels
argument_list|,
literal|1
argument_list|,
literal|32767
argument_list|,
literal|0
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|unit
argument_list|,
name|MIN
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|yresolution
argument_list|)
argument_list|,
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
operator|->
name|dot_for_dot
argument_list|,
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|gimp_image_mask_grow_callback
argument_list|,
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|qbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_border_cmd_callback (GtkWidget * widget,gpointer data)
name|select_border_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GtkWidget
modifier|*
name|qbox
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|qbox
operator|=
name|gimp_query_size_box
argument_list|(
name|_
argument_list|(
literal|"Border Selection"
argument_list|)
argument_list|,
name|gdisp
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
name|selection_border_radius
argument_list|,
literal|1
argument_list|,
literal|32767
argument_list|,
literal|0
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|unit
argument_list|,
name|MIN
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|yresolution
argument_list|)
argument_list|,
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
operator|->
name|dot_for_dot
argument_list|,
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|gimp_image_mask_border_callback
argument_list|,
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|qbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|select_save_cmd_callback (GtkWidget * widget,gpointer data)
name|select_save_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_selection_save
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
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
DECL|function|select_toggle_quickmask_cmd_callback (GtkWidget * widget,gpointer data)
name|select_toggle_quickmask_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_set_qmask_state
argument_list|(
name|gimage
argument_list|,
operator|!
name|gimp_image_get_qmask_state
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
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
DECL|function|gimp_image_mask_feather_callback (GtkWidget * widget,gdouble size,GimpUnit unit,gpointer data)
name|gimp_image_mask_feather_callback
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
name|gimage
decl_stmt|;
name|gdouble
name|radius_x
decl_stmt|;
name|gdouble
name|radius_y
decl_stmt|;
name|gimage
operator|=
name|GIMP_IMAGE
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|selection_feather_radius
operator|=
name|size
expr_stmt|;
name|radius_x
operator|=
name|radius_y
operator|=
name|selection_feather_radius
expr_stmt|;
if|if
condition|(
name|unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|gdouble
name|factor
decl_stmt|;
name|factor
operator|=
operator|(
name|MAX
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|)
operator|/
name|MIN
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|->
name|xresolution
operator|==
name|MIN
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
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
name|gimage
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
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_mask_border_callback (GtkWidget * widget,gdouble size,GimpUnit unit,gpointer data)
name|gimp_image_mask_border_callback
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
name|gimage
decl_stmt|;
name|gdouble
name|radius_x
decl_stmt|;
name|gdouble
name|radius_y
decl_stmt|;
name|gimage
operator|=
name|GIMP_IMAGE
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|selection_border_radius
operator|=
name|ROUND
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|radius_x
operator|=
name|radius_y
operator|=
name|selection_border_radius
expr_stmt|;
if|if
condition|(
name|unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|gdouble
name|factor
decl_stmt|;
name|factor
operator|=
operator|(
name|MAX
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|)
operator|/
name|MIN
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|->
name|xresolution
operator|==
name|MIN
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
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
name|gimage
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
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_mask_grow_callback (GtkWidget * widget,gdouble size,GimpUnit unit,gpointer data)
name|gimp_image_mask_grow_callback
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
name|gimage
decl_stmt|;
name|gdouble
name|radius_x
decl_stmt|;
name|gdouble
name|radius_y
decl_stmt|;
name|gimage
operator|=
name|GIMP_IMAGE
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|selection_grow_pixels
operator|=
name|ROUND
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|radius_x
operator|=
name|radius_y
operator|=
name|selection_grow_pixels
expr_stmt|;
if|if
condition|(
name|unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|gdouble
name|factor
decl_stmt|;
name|factor
operator|=
operator|(
name|MAX
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|)
operator|/
name|MIN
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|->
name|xresolution
operator|==
name|MIN
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
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
name|gimage
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
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_mask_shrink_callback (GtkWidget * widget,gdouble size,GimpUnit unit,gpointer data)
name|gimp_image_mask_shrink_callback
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
name|gimage
decl_stmt|;
name|gint
name|radius_x
decl_stmt|;
name|gint
name|radius_y
decl_stmt|;
name|gimage
operator|=
name|GIMP_IMAGE
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|selection_shrink_pixels
operator|=
name|ROUND
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|radius_x
operator|=
name|radius_y
operator|=
name|selection_shrink_pixels
expr_stmt|;
name|selection_shrink_edge_lock
operator|=
operator|!
name|GTK_TOGGLE_BUTTON
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"edge_lock_toggle"
argument_list|)
argument_list|)
operator|->
name|active
expr_stmt|;
if|if
condition|(
name|unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|gdouble
name|factor
decl_stmt|;
name|factor
operator|=
operator|(
name|MAX
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|)
operator|/
name|MIN
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|->
name|xresolution
operator|==
name|MIN
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
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
name|gimage
argument_list|)
argument_list|,
name|radius_x
argument_list|,
name|radius_y
argument_list|,
name|selection_shrink_edge_lock
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

