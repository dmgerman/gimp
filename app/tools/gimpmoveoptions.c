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
file|"gimpmoveoptions.h"
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
DECL|enum|__anon2c9220c20103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_MOVE_TYPE
name|PROP_MOVE_TYPE
block|,
DECL|enumerator|PROP_MOVE_CURRENT
name|PROP_MOVE_CURRENT
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_move_options_set_property
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
name|gimp_move_options_get_property
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

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpMoveOptions
argument_list|,
name|gimp_move_options
argument_list|,
name|GIMP_TYPE_TOOL_OPTIONS
argument_list|)
expr_stmt|;
end_expr_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_move_options_class_init (GimpMoveOptionsClass * klass)
name|gimp_move_options_class_init
parameter_list|(
name|GimpMoveOptionsClass
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
name|gimp_move_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_move_options_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_MOVE_TYPE
argument_list|,
literal|"move-type"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TRANSFORM_TYPE
argument_list|,
name|GIMP_TRANSFORM_TYPE_LAYER
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_MOVE_CURRENT
argument_list|,
literal|"move-current"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_options_init (GimpMoveOptions * options)
name|gimp_move_options_init
parameter_list|(
name|GimpMoveOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_move_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_move_options_set_property
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
name|GimpMoveOptions
modifier|*
name|options
init|=
name|GIMP_MOVE_OPTIONS
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
name|PROP_MOVE_TYPE
case|:
name|options
operator|->
name|move_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MOVE_CURRENT
case|:
name|options
operator|->
name|move_current
operator|=
name|g_value_get_boolean
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
DECL|function|gimp_move_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_move_options_get_property
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
name|GimpMoveOptions
modifier|*
name|options
init|=
name|GIMP_MOVE_OPTIONS
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
name|PROP_MOVE_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|move_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MOVE_CURRENT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|move_current
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
DECL|function|gimp_move_options_notify_type (GimpMoveOptions * move_options,GParamSpec * pspec,GtkWidget * frame)
name|gimp_move_options_notify_type
parameter_list|(
name|GimpMoveOptions
modifier|*
name|move_options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GtkWidget
modifier|*
name|frame
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|false_label
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|true_label
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GSList
modifier|*
name|group
decl_stmt|;
name|button
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|"radio-button"
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|move_options
operator|->
name|move_type
condition|)
block|{
case|case
name|GIMP_TRANSFORM_TYPE_LAYER
case|:
name|false_label
operator|=
name|_
argument_list|(
literal|"Pick a layer or guide"
argument_list|)
expr_stmt|;
name|true_label
operator|=
name|_
argument_list|(
literal|"Move the current layer"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_SELECTION
case|:
name|false_label
operator|=
name|true_label
operator|=
name|_
argument_list|(
literal|"Move selection"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TRANSFORM_TYPE_PATH
case|:
name|false_label
operator|=
name|_
argument_list|(
literal|"Pick a path"
argument_list|)
expr_stmt|;
name|true_label
operator|=
name|_
argument_list|(
literal|"Move the current path"
argument_list|)
expr_stmt|;
break|break;
block|}
name|group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_button_set_label
argument_list|(
name|GTK_BUTTON
argument_list|(
name|group
operator|->
name|data
argument_list|)
argument_list|,
name|true_label
argument_list|)
expr_stmt|;
name|group
operator|=
name|g_slist_next
argument_list|(
name|group
argument_list|)
expr_stmt|;
name|gtk_button_set_label
argument_list|(
name|GTK_BUTTON
argument_list|(
name|group
operator|->
name|data
argument_list|)
argument_list|,
name|false_label
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|frame
argument_list|,
name|move_options
operator|->
name|move_type
operator|!=
name|GIMP_TRANSFORM_TYPE_SELECTION
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_move_options_gui (GimpToolOptions * tool_options)
name|gimp_move_options_gui
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
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|gchar
modifier|*
name|title
decl_stmt|;
name|vbox
operator|=
name|gimp_tool_options_gui
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gimp_prop_enum_stock_box_new
argument_list|(
name|config
argument_list|,
literal|"move-type"
argument_list|,
literal|"gimp"
argument_list|,
literal|0
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
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Affect:"
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
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
comment|/*  tool toggle  */
name|title
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Tool Toggle  (%s)"
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|GDK_SHIFT_MASK
argument_list|)
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_prop_boolean_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"move-current"
argument_list|,
name|title
argument_list|,
literal|"true"
argument_list|,
literal|"false"
argument_list|)
expr_stmt|;
name|gimp_move_options_notify_type
argument_list|(
name|GIMP_MOVE_OPTIONS
argument_list|(
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|config
argument_list|,
literal|"notify::move-type"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_move_options_notify_type
argument_list|)
argument_list|,
name|frame
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
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit

