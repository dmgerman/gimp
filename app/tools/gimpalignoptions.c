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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpalignoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimptooloptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a4d045c0103
block|{
DECL|enumerator|ALIGN_BUTTON_CLICKED
name|ALIGN_BUTTON_CLICKED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2a4d045c0203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ALIGN_REFERENCE
name|PROP_ALIGN_REFERENCE
block|,
DECL|enumerator|PROP_OFFSET_X
name|PROP_OFFSET_X
block|,
DECL|enumerator|PROP_OFFSET_Y
name|PROP_OFFSET_Y
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_align_options_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_align_options_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpAlignOptions
argument_list|,
argument|gimp_align_options
argument_list|,
argument|GIMP_TYPE_TOOL_OPTIONS
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_selection_options_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|align_options_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_align_options_class_init (GimpAlignOptionsClass * klass)
name|gimp_align_options_class_init
parameter_list|(
name|GimpAlignOptionsClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_align_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_align_options_get_property
expr_stmt|;
name|klass
operator|->
name|align_button_clicked
operator|=
name|NULL
expr_stmt|;
name|align_options_signals
index|[
name|ALIGN_BUTTON_CLICKED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"align-button-clicked"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpAlignOptionsClass
argument_list|,
name|align_button_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__ENUM
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_ALIGNMENT_TYPE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_ALIGN_REFERENCE
argument_list|,
literal|"align-reference"
argument_list|,
name|N_
argument_list|(
literal|"Reference image object a layer will be aligned on"
argument_list|)
argument_list|,
name|GIMP_TYPE_ALIGN_REFERENCE_TYPE
argument_list|,
name|GIMP_ALIGN_REFERENCE_FIRST
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_OFFSET_X
argument_list|,
literal|"offset-x"
argument_list|,
name|N_
argument_list|(
literal|"Horizontal offset for distribution"
argument_list|)
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_OFFSET_Y
argument_list|,
literal|"offset-y"
argument_list|,
name|N_
argument_list|(
literal|"Vertical offset for distribution"
argument_list|)
argument_list|,
operator|-
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_align_options_init (GimpAlignOptions * options)
name|gimp_align_options_init
parameter_list|(
name|GimpAlignOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_align_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_align_options_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpAlignOptions
modifier|*
name|options
init|=
name|GIMP_ALIGN_OPTIONS
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_ALIGN_REFERENCE
case|:
name|options
operator|->
name|align_reference
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OFFSET_X
case|:
name|options
operator|->
name|offset_x
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OFFSET_Y
case|:
name|options
operator|->
name|offset_y
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_align_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_align_options_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpAlignOptions
modifier|*
name|options
init|=
name|GIMP_ALIGN_OPTIONS
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_ALIGN_REFERENCE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|align_reference
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OFFSET_X
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|offset_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OFFSET_Y
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|offset_y
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_align_options_button_clicked (GtkButton * button,GimpAlignOptions * options)
name|gimp_align_options_button_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GimpAlignOptions
modifier|*
name|options
parameter_list|)
block|{
name|GimpAlignmentType
name|action
decl_stmt|;
name|action
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"align-action"
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|options
argument_list|,
name|align_options_signals
index|[
name|ALIGN_BUTTON_CLICKED
index|]
argument_list|,
literal|0
argument_list|,
name|action
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_align_options_button_new (GimpAlignOptions * options,GimpAlignmentType action,GtkWidget * parent,const gchar * tooltip)
name|gimp_align_options_button_new
parameter_list|(
name|GimpAlignOptions
modifier|*
name|options
parameter_list|,
name|GimpAlignmentType
name|action
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|stock_id
init|=
name|NULL
decl_stmt|;
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|GIMP_ALIGN_LEFT
case|:
name|stock_id
operator|=
name|GIMP_STOCK_GRAVITY_WEST
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_HCENTER
case|:
name|stock_id
operator|=
name|GIMP_STOCK_HCENTER
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_RIGHT
case|:
name|stock_id
operator|=
name|GIMP_STOCK_GRAVITY_EAST
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_TOP
case|:
name|stock_id
operator|=
name|GIMP_STOCK_GRAVITY_NORTH
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_VCENTER
case|:
name|stock_id
operator|=
name|GIMP_STOCK_VCENTER
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_BOTTOM
case|:
name|stock_id
operator|=
name|GIMP_STOCK_GRAVITY_SOUTH
expr_stmt|;
break|break;
case|case
name|GIMP_ARRANGE_LEFT
case|:
name|stock_id
operator|=
name|GIMP_STOCK_GRAVITY_WEST
expr_stmt|;
break|break;
case|case
name|GIMP_ARRANGE_HCENTER
case|:
name|stock_id
operator|=
name|GIMP_STOCK_HCENTER
expr_stmt|;
break|break;
case|case
name|GIMP_ARRANGE_RIGHT
case|:
name|stock_id
operator|=
name|GIMP_STOCK_GRAVITY_EAST
expr_stmt|;
break|break;
case|case
name|GIMP_ARRANGE_TOP
case|:
name|stock_id
operator|=
name|GIMP_STOCK_GRAVITY_NORTH
expr_stmt|;
break|break;
case|case
name|GIMP_ARRANGE_VCENTER
case|:
name|stock_id
operator|=
name|GIMP_STOCK_VCENTER
expr_stmt|;
break|break;
case|case
name|GIMP_ARRANGE_BOTTOM
case|:
name|stock_id
operator|=
name|GIMP_STOCK_GRAVITY_SOUTH
expr_stmt|;
break|break;
default|default:
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
break|break;
block|}
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|stock_id
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|parent
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
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|tooltip
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"align-action"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_align_options_button_clicked
argument_list|)
argument_list|,
name|options
argument_list|)
expr_stmt|;
return|return
name|button
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_align_options_gui (GimpToolOptions * tool_options)
name|gimp_align_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GObject
modifier|*
name|config
init|=
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GimpAlignOptions
modifier|*
name|options
init|=
name|GIMP_ALIGN_OPTIONS
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
init|=
name|gimp_tool_options_gui
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|align_vbox
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
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|gint
name|n
init|=
literal|0
decl_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Align"
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
name|align_vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|align_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|align_vbox
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
name|align_vbox
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
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Relative to:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|align_vbox
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
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"align-reference"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|combo
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|combo
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
name|align_vbox
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
name|options
operator|->
name|button
index|[
name|n
operator|++
index|]
operator|=
name|gimp_align_options_button_new
argument_list|(
name|options
argument_list|,
name|GIMP_ALIGN_LEFT
argument_list|,
name|hbox
argument_list|,
name|_
argument_list|(
literal|"Align left edge of target"
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|->
name|button
index|[
name|n
operator|++
index|]
operator|=
name|gimp_align_options_button_new
argument_list|(
name|options
argument_list|,
name|GIMP_ALIGN_HCENTER
argument_list|,
name|hbox
argument_list|,
name|_
argument_list|(
literal|"Align center of target"
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|->
name|button
index|[
name|n
operator|++
index|]
operator|=
name|gimp_align_options_button_new
argument_list|(
name|options
argument_list|,
name|GIMP_ALIGN_RIGHT
argument_list|,
name|hbox
argument_list|,
name|_
argument_list|(
literal|"Align right edge of target"
argument_list|)
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
name|align_vbox
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
name|options
operator|->
name|button
index|[
name|n
operator|++
index|]
operator|=
name|gimp_align_options_button_new
argument_list|(
name|options
argument_list|,
name|GIMP_ALIGN_TOP
argument_list|,
name|hbox
argument_list|,
name|_
argument_list|(
literal|"Align top edge of target"
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|->
name|button
index|[
name|n
operator|++
index|]
operator|=
name|gimp_align_options_button_new
argument_list|(
name|options
argument_list|,
name|GIMP_ALIGN_VCENTER
argument_list|,
name|hbox
argument_list|,
name|_
argument_list|(
literal|"Align middle of target"
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|->
name|button
index|[
name|n
operator|++
index|]
operator|=
name|gimp_align_options_button_new
argument_list|(
name|options
argument_list|,
name|GIMP_ALIGN_BOTTOM
argument_list|,
name|hbox
argument_list|,
name|_
argument_list|(
literal|"Align bottom of target"
argument_list|)
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Distribute"
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
name|align_vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|align_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|align_vbox
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
name|align_vbox
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
name|options
operator|->
name|button
index|[
name|n
operator|++
index|]
operator|=
name|gimp_align_options_button_new
argument_list|(
name|options
argument_list|,
name|GIMP_ARRANGE_LEFT
argument_list|,
name|hbox
argument_list|,
name|_
argument_list|(
literal|"Distribute left edges of targets"
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|->
name|button
index|[
name|n
operator|++
index|]
operator|=
name|gimp_align_options_button_new
argument_list|(
name|options
argument_list|,
name|GIMP_ARRANGE_HCENTER
argument_list|,
name|hbox
argument_list|,
name|_
argument_list|(
literal|"Distribute horizontal centers of targets"
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|->
name|button
index|[
name|n
operator|++
index|]
operator|=
name|gimp_align_options_button_new
argument_list|(
name|options
argument_list|,
name|GIMP_ARRANGE_RIGHT
argument_list|,
name|hbox
argument_list|,
name|_
argument_list|(
literal|"Distribute right edges of targets"
argument_list|)
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
name|align_vbox
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
name|options
operator|->
name|button
index|[
name|n
operator|++
index|]
operator|=
name|gimp_align_options_button_new
argument_list|(
name|options
argument_list|,
name|GIMP_ARRANGE_TOP
argument_list|,
name|hbox
argument_list|,
name|_
argument_list|(
literal|"Distribute top edges of targets"
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|->
name|button
index|[
name|n
operator|++
index|]
operator|=
name|gimp_align_options_button_new
argument_list|(
name|options
argument_list|,
name|GIMP_ARRANGE_VCENTER
argument_list|,
name|hbox
argument_list|,
name|_
argument_list|(
literal|"Distribute vertical centers of targets"
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|->
name|button
index|[
name|n
operator|++
index|]
operator|=
name|gimp_align_options_button_new
argument_list|(
name|options
argument_list|,
name|GIMP_ARRANGE_BOTTOM
argument_list|,
name|hbox
argument_list|,
name|_
argument_list|(
literal|"Distribute bottoms of targets"
argument_list|)
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
name|align_vbox
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
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Offset:"
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
name|spinbutton
operator|=
name|gimp_prop_spin_button_new
argument_list|(
name|config
argument_list|,
literal|"offset-x"
argument_list|,
literal|1
argument_list|,
literal|20
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|spinbutton
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
name|spinbutton
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit

