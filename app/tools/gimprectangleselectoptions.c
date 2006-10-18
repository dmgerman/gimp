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
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimprectangleoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimprectangleselectoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimprectangleselecttool.h"
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
DECL|enum|__anon2ae5b7f60103
block|{
DECL|enumerator|PROP_ROUND_CORNERS
name|PROP_ROUND_CORNERS
init|=
name|GIMP_RECTANGLE_OPTIONS_PROP_LAST
operator|+
literal|1
block|,
DECL|enumerator|PROP_CORNER_RADIUS
name|PROP_CORNER_RADIUS
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_rect_select_options_set_property
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
name|gimp_rect_select_options_get_property
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
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpRectSelectOptions,gimp_rect_select_options,GIMP_TYPE_SELECTION_OPTIONS,G_IMPLEMENT_INTERFACE (GIMP_TYPE_RECTANGLE_OPTIONS,NULL))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpRectSelectOptions
argument_list|,
argument|gimp_rect_select_options
argument_list|,
argument|GIMP_TYPE_SELECTION_OPTIONS
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_RECTANGLE_OPTIONS,                                                 NULL)
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_rect_select_options_class_init
parameter_list|(
name|GimpRectSelectOptionsClass
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
name|gimp_rect_select_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_rect_select_options_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_ROUND_CORNERS
argument_list|,
literal|"round-corners"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_CORNER_RADIUS
argument_list|,
literal|"corner-radius"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|5.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|gimp_rectangle_options_install_properties
argument_list|(
name|object_class
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rect_select_options_init (GimpRectSelectOptions * options)
name|gimp_rect_select_options_init
parameter_list|(
name|GimpRectSelectOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rect_select_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_rect_select_options_set_property
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
name|GimpRectSelectOptions
modifier|*
name|options
init|=
name|GIMP_RECT_SELECT_OPTIONS
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
name|PROP_ROUND_CORNERS
case|:
name|options
operator|->
name|round_corners
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CORNER_RADIUS
case|:
name|options
operator|->
name|corner_radius
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|gimp_rectangle_options_set_property
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|value
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
DECL|function|gimp_rect_select_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_rect_select_options_get_property
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
name|GimpRectSelectOptions
modifier|*
name|options
init|=
name|GIMP_RECT_SELECT_OPTIONS
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
name|PROP_ROUND_CORNERS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|round_corners
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CORNER_RADIUS
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|corner_radius
argument_list|)
expr_stmt|;
break|break;
default|default:
name|gimp_rectangle_options_get_property
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|value
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_rect_select_options_gui (GimpToolOptions * tool_options)
name|gimp_rect_select_options_gui
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
name|GtkWidget
modifier|*
name|vbox
init|=
name|gimp_selection_options_gui
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
comment|/*  the round corners frame  */
if|if
condition|(
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|==
name|GIMP_TYPE_RECT_SELECT_TOOL
condition|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|NULL
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
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"round-corners"
argument_list|,
name|_
argument_list|(
literal|"Rounded corners"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_frame_set_label_widget
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool_options
argument_list|)
operator|->
name|antialias_toggle
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool_options
argument_list|)
operator|->
name|antialias_toggle
argument_list|,
name|GIMP_RECT_SELECT_OPTIONS
argument_list|(
name|tool_options
argument_list|)
operator|->
name|round_corners
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
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
name|table
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_RECT_SELECT_OPTIONS
argument_list|(
name|tool_options
argument_list|)
operator|->
name|round_corners
condition|)
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_set_visible
argument_list|)
argument_list|,
name|table
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_prop_scale_entry_new
argument_list|(
name|config
argument_list|,
literal|"corner-radius"
argument_list|,
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Radius:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
comment|/*  the rectangle options  */
block|{
name|GtkWidget
modifier|*
name|vbox_rectangle
decl_stmt|;
name|vbox_rectangle
operator|=
name|gimp_rectangle_options_gui
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|vbox_rectangle
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
name|vbox_rectangle
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|GIMP_RECTANGLE_OPTIONS
argument_list|(
name|tool_options
argument_list|)
argument_list|,
literal|"highlight"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|vbox
return|;
block|}
end_function

end_unit

