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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorframe.h"
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
name|gimp_color_frame_class_init
parameter_list|(
name|GimpColorFrameClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_frame_init
parameter_list|(
name|GimpColorFrame
modifier|*
name|frame
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_frame_menu_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorFrame
modifier|*
name|frame
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_frame_update
parameter_list|(
name|GimpColorFrame
modifier|*
name|frame
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpFrameClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_color_frame_get_type (void)
name|gimp_color_frame_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|frame_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpColorFrameClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_color_frame_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpColorFrame
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_color_frame_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_FRAME
argument_list|,
literal|"GimpColorFrame"
argument_list|,
operator|&
name|frame_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_frame_class_init (GimpColorFrameClass * klass)
name|gimp_color_frame_class_init
parameter_list|(
name|GimpColorFrameClass
modifier|*
name|klass
parameter_list|)
block|{
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_frame_init (GimpColorFrame * frame)
name|gimp_color_frame_init
parameter_list|(
name|GimpColorFrame
modifier|*
name|frame
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|color_area
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GimpRGB
name|init_color
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|}
decl_stmt|;
name|frame
operator|->
name|sample_valid
operator|=
name|FALSE
expr_stmt|;
name|frame
operator|->
name|sample_type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|frame
operator|->
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|frame
operator|->
name|menu
operator|=
name|gimp_enum_combo_box_new
argument_list|(
name|GIMP_TYPE_COLOR_FRAME_MODE
argument_list|)
expr_stmt|;
name|gtk_frame_set_label_widget
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|frame
operator|->
name|menu
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
operator|->
name|menu
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|frame
operator|->
name|menu
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_frame_menu_callback
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|TRUE
argument_list|,
literal|2
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
name|color_area
operator|=
name|gimp_color_area_new
argument_list|(
operator|&
name|frame
operator|->
name|color
argument_list|,
name|GIMP_COLOR_AREA_SMALL_CHECKS
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|color_area
argument_list|,
literal|30
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|gimp_color_area_set_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|color_area
argument_list|)
argument_list|,
operator|&
name|init_color
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|color_area
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
name|color_area
argument_list|)
expr_stmt|;
name|frame
operator|->
name|color_area
operator|=
name|color_area
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|GIMP_COLOR_FRAME_ROWS
condition|;
name|i
operator|++
control|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
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
name|frame
operator|->
name|name_labels
index|[
name|i
index|]
operator|=
name|gtk_label_new
argument_list|(
literal|" "
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|frame
operator|->
name|name_labels
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|frame
operator|->
name|name_labels
index|[
name|i
index|]
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
operator|->
name|name_labels
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|frame
operator|->
name|value_labels
index|[
name|i
index|]
operator|=
name|gtk_label_new
argument_list|(
literal|" "
argument_list|)
expr_stmt|;
name|gtk_label_set_selectable
argument_list|(
name|GTK_LABEL
argument_list|(
name|frame
operator|->
name|value_labels
index|[
name|i
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|frame
operator|->
name|value_labels
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|frame
operator|->
name|value_labels
index|[
name|i
index|]
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
operator|->
name|value_labels
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_color_frame_new:  *  * Creates a new #GimpColorFrame widget.  *  * Return value: The new #GimpColorFrame widget.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_frame_new (void)
name|gimp_color_frame_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_FRAME
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_frame_set_mode:  * @frame: The #GimpColorFrame.  * @mode:  The new @mode.  *  * Sets the #GimpColorFrame's color @mode. Calling this function does  * the same as selecting the @mode from the frame's #GtkOptionMenu.  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_frame_set_mode (GimpColorFrame * frame,GimpColorFrameMode mode)
name|gimp_color_frame_set_mode
parameter_list|(
name|GimpColorFrame
modifier|*
name|frame
parameter_list|,
name|GimpColorFrameMode
name|mode
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|frame
operator|->
name|menu
argument_list|)
argument_list|,
name|mode
argument_list|)
expr_stmt|;
name|frame
operator|->
name|frame_mode
operator|=
name|mode
expr_stmt|;
name|gimp_color_frame_update
argument_list|(
name|frame
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_frame_set_color:  * @frame:       The #GimpColorFrame.  * @sample_type: The type of the #GimpDrawable or #GimpImage the @color  *               was picked from.  * @color:       The @color to set.  * @color_index: The @color's index. This value is ignored unless  *               @sample_type equals to #GIMP_INDEXED_IMAGE or  *               #GIMP_INDEXEDA_IMAGE.  *  * Sets the color sample to display in the #GimpColorFrame.  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_frame_set_color (GimpColorFrame * frame,GimpImageType sample_type,const GimpRGB * color,gint color_index)
name|gimp_color_frame_set_color
parameter_list|(
name|GimpColorFrame
modifier|*
name|frame
parameter_list|,
name|GimpImageType
name|sample_type
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|color_index
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|frame
operator|->
name|sample_valid
operator|&&
name|frame
operator|->
name|sample_type
operator|==
name|sample_type
operator|&&
name|frame
operator|->
name|color_index
operator|==
name|color_index
operator|&&
name|gimp_rgb_distance
argument_list|(
operator|&
name|frame
operator|->
name|color
argument_list|,
name|color
argument_list|)
operator|<
literal|0.0001
condition|)
block|{
name|frame
operator|->
name|color
operator|=
operator|*
name|color
expr_stmt|;
return|return;
block|}
name|frame
operator|->
name|sample_valid
operator|=
name|TRUE
expr_stmt|;
name|frame
operator|->
name|sample_type
operator|=
name|sample_type
expr_stmt|;
name|frame
operator|->
name|color
operator|=
operator|*
name|color
expr_stmt|;
name|frame
operator|->
name|color_index
operator|=
name|color_index
expr_stmt|;
name|gimp_color_frame_update
argument_list|(
name|frame
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_frame_set_invalid:  * @frame: The #GimpColorFrame.  *  * Tells the #GimpColorFrame that the current sample is invalid. All labels  * visible for the current color space will show "n/a" (not available).  *  * There is no special API for setting the frame to "valid" again because  * this happens automatically when calling gimp_color_frame_set_color().  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_frame_set_invalid (GimpColorFrame * frame)
name|gimp_color_frame_set_invalid
parameter_list|(
name|GimpColorFrame
modifier|*
name|frame
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|frame
operator|->
name|sample_valid
condition|)
return|return;
name|frame
operator|->
name|sample_valid
operator|=
name|FALSE
expr_stmt|;
name|gimp_color_frame_update
argument_list|(
name|frame
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
DECL|function|gimp_color_frame_menu_callback (GtkWidget * widget,GimpColorFrame * frame)
name|gimp_color_frame_menu_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorFrame
modifier|*
name|frame
parameter_list|)
block|{
name|gimp_int_combo_box_get_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|(
name|gint
operator|*
operator|)
operator|&
name|frame
operator|->
name|frame_mode
argument_list|)
expr_stmt|;
name|gimp_color_frame_update
argument_list|(
name|frame
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_frame_update (GimpColorFrame * frame)
name|gimp_color_frame_update
parameter_list|(
name|GimpColorFrame
modifier|*
name|frame
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|names
index|[
name|GIMP_COLOR_FRAME_ROWS
index|]
init|=
block|{
name|NULL
block|, }
decl_stmt|;
name|gchar
modifier|*
name|values
index|[
name|GIMP_COLOR_FRAME_ROWS
index|]
init|=
block|{
name|NULL
block|, }
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|gint
name|alpha_row
init|=
literal|3
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|has_alpha
operator|=
name|GIMP_IMAGE_TYPE_HAS_ALPHA
argument_list|(
name|frame
operator|->
name|sample_type
argument_list|)
expr_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
operator|&
name|frame
operator|->
name|color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|,
operator|&
name|a
argument_list|)
expr_stmt|;
name|gimp_color_area_set_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|frame
operator|->
name|color_area
argument_list|)
argument_list|,
operator|&
name|frame
operator|->
name|color
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|frame
operator|->
name|frame_mode
condition|)
block|{
case|case
name|GIMP_COLOR_FRAME_MODE_PIXEL
case|:
switch|switch
condition|(
name|GIMP_IMAGE_TYPE_BASE_TYPE
argument_list|(
name|frame
operator|->
name|sample_type
argument_list|)
condition|)
block|{
case|case
name|GIMP_INDEXED
case|:
name|names
index|[
literal|4
index|]
operator|=
name|_
argument_list|(
literal|"Index:"
argument_list|)
expr_stmt|;
name|values
index|[
literal|4
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d"
argument_list|,
name|frame
operator|->
name|color_index
argument_list|)
expr_stmt|;
case|case
name|GIMP_RGB
case|:
name|names
index|[
literal|0
index|]
operator|=
name|_
argument_list|(
literal|"Red:"
argument_list|)
expr_stmt|;
name|names
index|[
literal|1
index|]
operator|=
name|_
argument_list|(
literal|"Green:"
argument_list|)
expr_stmt|;
name|names
index|[
literal|2
index|]
operator|=
name|_
argument_list|(
literal|"Blue:"
argument_list|)
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d"
argument_list|,
name|r
argument_list|)
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d"
argument_list|,
name|g
argument_list|)
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d"
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|alpha_row
operator|=
literal|3
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY
case|:
name|names
index|[
literal|0
index|]
operator|=
name|_
argument_list|(
literal|"Value:"
argument_list|)
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d"
argument_list|,
name|r
argument_list|)
expr_stmt|;
name|alpha_row
operator|=
literal|1
expr_stmt|;
break|break;
block|}
break|break;
case|case
name|GIMP_COLOR_FRAME_MODE_RGB
case|:
name|names
index|[
literal|0
index|]
operator|=
name|_
argument_list|(
literal|"Red:"
argument_list|)
expr_stmt|;
name|names
index|[
literal|1
index|]
operator|=
name|_
argument_list|(
literal|"Green:"
argument_list|)
expr_stmt|;
name|names
index|[
literal|2
index|]
operator|=
name|_
argument_list|(
literal|"Blue:"
argument_list|)
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d %%"
argument_list|,
name|ROUND
argument_list|(
name|frame
operator|->
name|color
operator|.
name|r
operator|*
literal|100.0
argument_list|)
argument_list|)
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d %%"
argument_list|,
name|ROUND
argument_list|(
name|frame
operator|->
name|color
operator|.
name|g
operator|*
literal|100.0
argument_list|)
argument_list|)
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d %%"
argument_list|,
name|ROUND
argument_list|(
name|frame
operator|->
name|color
operator|.
name|b
operator|*
literal|100.0
argument_list|)
argument_list|)
expr_stmt|;
name|alpha_row
operator|=
literal|3
expr_stmt|;
name|names
index|[
literal|4
index|]
operator|=
name|_
argument_list|(
literal|"Hex:"
argument_list|)
expr_stmt|;
name|values
index|[
literal|4
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%.2x%.2x%.2x"
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_FRAME_MODE_HSV
case|:
block|{
name|GimpHSV
name|hsv
decl_stmt|;
name|gimp_rgb_to_hsv
argument_list|(
operator|&
name|frame
operator|->
name|color
argument_list|,
operator|&
name|hsv
argument_list|)
expr_stmt|;
name|names
index|[
literal|0
index|]
operator|=
name|_
argument_list|(
literal|"Hue:"
argument_list|)
expr_stmt|;
name|names
index|[
literal|1
index|]
operator|=
name|_
argument_list|(
literal|"Sat.:"
argument_list|)
expr_stmt|;
name|names
index|[
literal|2
index|]
operator|=
name|_
argument_list|(
literal|"Value:"
argument_list|)
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d \302\260"
argument_list|,
name|ROUND
argument_list|(
name|hsv
operator|.
name|h
operator|*
literal|360.0
argument_list|)
argument_list|)
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d %%"
argument_list|,
name|ROUND
argument_list|(
name|hsv
operator|.
name|s
operator|*
literal|100.0
argument_list|)
argument_list|)
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d %%"
argument_list|,
name|ROUND
argument_list|(
name|hsv
operator|.
name|v
operator|*
literal|100.0
argument_list|)
argument_list|)
expr_stmt|;
name|alpha_row
operator|=
literal|3
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_COLOR_FRAME_MODE_CMYK
case|:
block|{
name|GimpCMYK
name|cmyk
decl_stmt|;
name|gimp_rgb_to_cmyk
argument_list|(
operator|&
name|frame
operator|->
name|color
argument_list|,
literal|1.0
argument_list|,
operator|&
name|cmyk
argument_list|)
expr_stmt|;
name|names
index|[
literal|0
index|]
operator|=
name|_
argument_list|(
literal|"Cyan:"
argument_list|)
expr_stmt|;
name|names
index|[
literal|1
index|]
operator|=
name|_
argument_list|(
literal|"Magenta:"
argument_list|)
expr_stmt|;
name|names
index|[
literal|2
index|]
operator|=
name|_
argument_list|(
literal|"Yellow:"
argument_list|)
expr_stmt|;
name|names
index|[
literal|3
index|]
operator|=
name|_
argument_list|(
literal|"Black:"
argument_list|)
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d %%"
argument_list|,
name|ROUND
argument_list|(
name|cmyk
operator|.
name|c
operator|*
literal|100.0
argument_list|)
argument_list|)
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d %%"
argument_list|,
name|ROUND
argument_list|(
name|cmyk
operator|.
name|m
operator|*
literal|100.0
argument_list|)
argument_list|)
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d %%"
argument_list|,
name|ROUND
argument_list|(
name|cmyk
operator|.
name|y
operator|*
literal|100.0
argument_list|)
argument_list|)
expr_stmt|;
name|values
index|[
literal|3
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d %%"
argument_list|,
name|ROUND
argument_list|(
name|cmyk
operator|.
name|k
operator|*
literal|100.0
argument_list|)
argument_list|)
expr_stmt|;
name|alpha_row
operator|=
literal|4
expr_stmt|;
block|}
break|break;
block|}
if|if
condition|(
name|has_alpha
condition|)
block|{
name|names
index|[
name|alpha_row
index|]
operator|=
name|_
argument_list|(
literal|"Alpha:"
argument_list|)
expr_stmt|;
if|if
condition|(
name|frame
operator|->
name|frame_mode
operator|==
name|GIMP_COLOR_FRAME_MODE_PIXEL
condition|)
name|values
index|[
name|alpha_row
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d"
argument_list|,
name|a
argument_list|)
expr_stmt|;
else|else
name|values
index|[
name|alpha_row
index|]
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d %%"
argument_list|,
call|(
name|gint
call|)
argument_list|(
name|frame
operator|->
name|color
operator|.
name|a
operator|*
literal|100.0
argument_list|)
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|GIMP_COLOR_FRAME_ROWS
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|names
index|[
name|i
index|]
operator|&&
name|values
index|[
name|i
index|]
condition|)
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|frame
operator|->
name|name_labels
index|[
name|i
index|]
argument_list|)
argument_list|,
name|names
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|frame
operator|->
name|sample_valid
condition|)
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|frame
operator|->
name|value_labels
index|[
name|i
index|]
argument_list|)
argument_list|,
name|values
index|[
name|i
index|]
argument_list|)
expr_stmt|;
else|else
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|frame
operator|->
name|value_labels
index|[
name|i
index|]
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|frame
operator|->
name|name_labels
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|" "
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|frame
operator|->
name|value_labels
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|" "
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|values
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

