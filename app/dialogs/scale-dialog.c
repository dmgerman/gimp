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
file|"dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpenumcombobox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsizebox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"scale-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|RESPONSE_RESET
define|#
directive|define
name|RESPONSE_RESET
value|1
end_define

begin_typedef
DECL|typedef|ScaleDialog
typedef|typedef
name|struct
name|_ScaleDialog
name|ScaleDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_ScaleDialog
struct|struct
name|_ScaleDialog
block|{
DECL|member|viewable
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|interpolation
name|GimpInterpolationType
name|interpolation
decl_stmt|;
DECL|member|box
name|GtkWidget
modifier|*
name|box
decl_stmt|;
DECL|member|combo
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
DECL|member|callback
name|GimpScaleCallback
name|callback
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|scale_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ScaleDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|scale_dialog_reset
parameter_list|(
name|ScaleDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GtkWidget
modifier|*
DECL|function|scale_dialog_new (GimpViewable * viewable,const gchar * title,const gchar * role,GtkWidget * parent,GimpHelpFunc help_func,const gchar * help_id,GimpUnit unit,GimpInterpolationType interpolation,GimpScaleCallback callback,gpointer user_data)
name|scale_dialog_new
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
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
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|GimpScaleCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
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
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|ScaleDialog
modifier|*
name|private
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|text
init|=
name|NULL
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
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
if|if
condition|(
name|GIMP_IS_IMAGE
argument_list|(
name|viewable
argument_list|)
condition|)
block|{
name|image
operator|=
name|GIMP_IMAGE
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|text
operator|=
name|_
argument_list|(
literal|"Image Size"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_ITEM
argument_list|(
name|viewable
argument_list|)
condition|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_item_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|text
operator|=
name|_
argument_list|(
literal|"Layer Size"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|viewable
argument_list|,
name|title
argument_list|,
name|role
argument_list|,
name|GIMP_STOCK_SCALE
argument_list|,
name|title
argument_list|,
name|parent
argument_list|,
name|help_func
argument_list|,
name|help_id
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|RESPONSE_RESET
argument_list|,
name|GIMP_STOCK_SCALE
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_new0
argument_list|(
name|ScaleDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|g_free
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|private
operator|->
name|viewable
operator|=
name|viewable
expr_stmt|;
name|private
operator|->
name|interpolation
operator|=
name|interpolation
expr_stmt|;
name|private
operator|->
name|unit
operator|=
name|unit
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
name|private
operator|->
name|box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_SIZE_BOX
argument_list|,
literal|"width"
argument_list|,
name|width
argument_list|,
literal|"height"
argument_list|,
name|height
argument_list|,
literal|"unit"
argument_list|,
name|unit
argument_list|,
literal|"xresolution"
argument_list|,
name|xres
argument_list|,
literal|"yresolution"
argument_list|,
name|yres
argument_list|,
literal|"resolution-unit"
argument_list|,
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
argument_list|,
literal|"keep-aspect"
argument_list|,
name|TRUE
argument_list|,
literal|"edit-resolution"
argument_list|,
name|GIMP_IS_IMAGE
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|scale_dialog_response
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|private
operator|->
name|box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|box
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Quality"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
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
literal|"I_nterpolation:"
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
name|private
operator|->
name|combo
operator|=
name|gimp_enum_combo_box_new
argument_list|(
name|GIMP_TYPE_INTERPOLATION_TYPE
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|private
operator|->
name|combo
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|private
operator|->
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
name|private
operator|->
name|combo
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|private
operator|->
name|combo
argument_list|)
argument_list|,
name|private
operator|->
name|interpolation
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
operator|==
name|GIMP_INDEXED
condition|)
block|{
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Indexed color layers are always scaled "
literal|"without interpolation. The chosen "
literal|"interpolation type will affect channels "
literal|"and masks only."
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
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
block|}
return|return
name|dialog
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|scale_dialog_response (GtkWidget * dialog,gint response_id,ScaleDialog * private)
name|scale_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ScaleDialog
modifier|*
name|private
parameter_list|)
block|{
name|GimpUnit
name|unit
init|=
name|private
operator|->
name|unit
decl_stmt|;
name|gint
name|interpolation
init|=
name|private
operator|->
name|interpolation
decl_stmt|;
name|GimpUnit
name|resolution_unit
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|GTK_RESPONSE_CANCEL
case|:
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
break|break;
case|case
name|RESPONSE_RESET
case|:
name|scale_dialog_reset
argument_list|(
name|private
argument_list|)
expr_stmt|;
break|break;
case|case
name|GTK_RESPONSE_OK
case|:
name|g_object_get
argument_list|(
name|private
operator|->
name|box
argument_list|,
literal|"width"
argument_list|,
operator|&
name|width
argument_list|,
literal|"height"
argument_list|,
operator|&
name|height
argument_list|,
literal|"unit"
argument_list|,
operator|&
name|unit
argument_list|,
literal|"xresolution"
argument_list|,
operator|&
name|xres
argument_list|,
literal|"yresolution"
argument_list|,
operator|&
name|yres
argument_list|,
literal|"resolution-unit"
argument_list|,
operator|&
name|resolution_unit
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_get_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|private
operator|->
name|combo
argument_list|)
argument_list|,
operator|&
name|interpolation
argument_list|)
expr_stmt|;
name|private
operator|->
name|callback
argument_list|(
name|dialog
argument_list|,
name|private
operator|->
name|viewable
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|unit
argument_list|,
name|interpolation
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|,
name|resolution_unit
argument_list|,
name|private
operator|->
name|user_data
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|scale_dialog_reset (ScaleDialog * private)
name|scale_dialog_reset
parameter_list|(
name|ScaleDialog
modifier|*
name|private
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
if|if
condition|(
name|GIMP_IS_IMAGE
argument_list|(
name|private
operator|->
name|viewable
argument_list|)
condition|)
block|{
name|image
operator|=
name|GIMP_IMAGE
argument_list|(
name|private
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_ITEM
argument_list|(
name|private
operator|->
name|viewable
argument_list|)
condition|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|private
operator|->
name|viewable
argument_list|)
decl_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_item_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_return_if_reached
argument_list|()
expr_stmt|;
block|}
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
name|g_object_set
argument_list|(
name|private
operator|->
name|box
argument_list|,
literal|"width"
argument_list|,
name|width
argument_list|,
literal|"height"
argument_list|,
name|height
argument_list|,
literal|"unit"
argument_list|,
name|private
operator|->
name|unit
argument_list|,
literal|"keep-aspect"
argument_list|,
name|TRUE
argument_list|,
literal|"xresolution"
argument_list|,
name|xres
argument_list|,
literal|"yresolution"
argument_list|,
name|yres
argument_list|,
literal|"resolution-unit"
argument_list|,
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|private
operator|->
name|combo
argument_list|)
argument_list|,
name|private
operator|->
name|interpolation
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

