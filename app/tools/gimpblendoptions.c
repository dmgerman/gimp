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
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpblendoptions.h"
end_include

begin_include
include|#
directive|include
file|"paint_options.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2958815d0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_OFFSET
name|PROP_OFFSET
block|,
DECL|enumerator|PROP_GRADIENT_TYPE
name|PROP_GRADIENT_TYPE
block|,
DECL|enumerator|PROP_REPEAT
name|PROP_REPEAT
block|,
DECL|enumerator|PROP_SUPERSAMPLE
name|PROP_SUPERSAMPLE
block|,
DECL|enumerator|PROP_SUPERSAMPLE_DEPTH
name|PROP_SUPERSAMPLE_DEPTH
block|,
DECL|enumerator|PROP_SUPERSAMPLE_THRESHOLD
name|PROP_SUPERSAMPLE_THRESHOLD
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_blend_options_init
parameter_list|(
name|GimpBlendOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_blend_options_class_init
parameter_list|(
name|GimpBlendOptionsClass
modifier|*
name|options_class
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_blend_options_set_property
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
name|gimp_blend_options_get_property
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

begin_function_decl
specifier|static
name|void
name|gradient_type_notify
parameter_list|(
name|GimpBlendOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GtkWidget
modifier|*
name|repeat_menu
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|blend_options_gradient_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpPaintOptionsClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_blend_options_get_type (void)
name|gimp_blend_options_get_type
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
name|info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpBlendOptionsClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_blend_options_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpBlendOptions
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_blend_options_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PAINT_OPTIONS
argument_list|,
literal|"GimpBlendOptions"
argument_list|,
operator|&
name|info
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
DECL|function|gimp_blend_options_class_init (GimpBlendOptionsClass * klass)
name|gimp_blend_options_class_init
parameter_list|(
name|GimpBlendOptionsClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_blend_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_blend_options_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_OFFSET
argument_list|,
literal|"offset"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|0.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_GRADIENT_TYPE
argument_list|,
literal|"gradient-type"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GRADIENT_TYPE
argument_list|,
name|GIMP_LINEAR
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_REPEAT
argument_list|,
literal|"repeat"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_REPEAT_MODE
argument_list|,
name|GIMP_REPEAT_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SUPERSAMPLE
argument_list|,
literal|"supersample"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_SUPERSAMPLE_DEPTH
argument_list|,
literal|"supersample-depth"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|10
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_SUPERSAMPLE_THRESHOLD
argument_list|,
literal|"supersample-threshold"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|4.0
argument_list|,
literal|0.2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blend_options_init (GimpBlendOptions * options)
name|gimp_blend_options_init
parameter_list|(
name|GimpBlendOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blend_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_blend_options_set_property
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
name|GimpBlendOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_BLEND_OPTIONS
argument_list|(
name|object
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_OFFSET
case|:
name|options
operator|->
name|offset
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_TYPE
case|:
name|options
operator|->
name|gradient_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_REPEAT
case|:
name|options
operator|->
name|repeat
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SUPERSAMPLE
case|:
name|options
operator|->
name|supersample
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SUPERSAMPLE_DEPTH
case|:
name|options
operator|->
name|supersample_depth
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SUPERSAMPLE_THRESHOLD
case|:
name|options
operator|->
name|supersample_threshold
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
DECL|function|gimp_blend_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_blend_options_get_property
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
name|GimpBlendOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_BLEND_OPTIONS
argument_list|(
name|object
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_OFFSET
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|offset
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|gradient_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_REPEAT
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|repeat
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SUPERSAMPLE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|supersample
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SUPERSAMPLE_DEPTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|supersample_depth
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SUPERSAMPLE_THRESHOLD
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|supersample_threshold
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
name|GtkWidget
modifier|*
DECL|function|gimp_blend_options_gui (GimpToolOptions * tool_options)
name|gimp_blend_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GObject
modifier|*
name|config
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|optionmenu
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|config
operator|=
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gimp_paint_options_gui
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
comment|/*  the offset scale  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|4
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
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|table
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
name|table
argument_list|)
expr_stmt|;
name|gimp_prop_scale_entry_new
argument_list|(
name|config
argument_list|,
literal|"offset"
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
literal|"Offset:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|10.0
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
comment|/*  the gradient preview  */
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|preview
operator|=
name|gimp_prop_preview_new
argument_list|(
name|config
argument_list|,
literal|"gradient"
argument_list|,
literal|32
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Gradient:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|button
argument_list|,
literal|2
argument_list|,
name|TRUE
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
name|blend_options_gradient_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  the gradient type menu  */
name|optionmenu
operator|=
name|gimp_prop_enum_option_menu_new
argument_list|(
name|config
argument_list|,
literal|"gradient-type"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"Shape:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|optionmenu
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  the repeat option  */
name|optionmenu
operator|=
name|gimp_prop_enum_option_menu_new
argument_list|(
name|config
argument_list|,
literal|"repeat"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|3
argument_list|,
name|_
argument_list|(
literal|"Repeat:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|optionmenu
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|config
argument_list|,
literal|"notify::gradient-type"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gradient_type_notify
argument_list|)
argument_list|,
name|optionmenu
argument_list|)
expr_stmt|;
comment|/*  frame for supersampling options  */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_ETCHED_IN
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
comment|/*  table for supersampling options  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
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
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|1
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
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
comment|/*  supersampling toggle  */
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"supersample"
argument_list|,
name|_
argument_list|(
literal|"Adaptive Supersampling"
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
name|gtk_widget_set_sensitive
argument_list|(
name|table
argument_list|,
name|GIMP_BLEND_OPTIONS
argument_list|(
name|config
argument_list|)
operator|->
name|supersample
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
name|table
argument_list|)
expr_stmt|;
comment|/*  max depth scale  */
name|gimp_prop_scale_entry_new
argument_list|(
name|config
argument_list|,
literal|"supersample-depth"
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
literal|"Max Depth:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
comment|/*  threshold scale  */
name|gimp_prop_scale_entry_new
argument_list|(
name|config
argument_list|,
literal|"supersample-threshold"
argument_list|,
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Threshold:"
argument_list|)
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|blend_options_gradient_clicked (GtkWidget * widget,gpointer data)
name|blend_options_gradient_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|toplevel
decl_stmt|;
name|toplevel
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_DOCK
argument_list|(
name|toplevel
argument_list|)
condition|)
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|GIMP_DOCK
argument_list|(
name|toplevel
argument_list|)
operator|->
name|dialog_factory
argument_list|,
literal|"gimp-gradient-list"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_type_notify (GimpBlendOptions * options,GParamSpec * pspec,GtkWidget * repeat_menu)
name|gradient_type_notify
parameter_list|(
name|GimpBlendOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GtkWidget
modifier|*
name|repeat_menu
parameter_list|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|repeat_menu
argument_list|,
name|options
operator|->
name|gradient_type
operator|<
literal|6
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

