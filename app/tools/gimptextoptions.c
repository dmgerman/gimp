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
file|"config/gimpconfig.h"
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"text/gimptext.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcolorpanel.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerpopup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpfontselection.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptexteditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimptextoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b54e8170103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TEXT
name|PROP_TEXT
block|, }
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_text_options_init
parameter_list|(
name|GimpTextOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_options_class_init
parameter_list|(
name|GimpTextOptionsClass
modifier|*
name|options_class
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_options_get_property
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
name|gimp_text_options_notify_font
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpText
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_notify_font
parameter_list|(
name|GimpText
modifier|*
name|text
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_options_font_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpToolOptionsClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_text_options_get_type (void)
name|gimp_text_options_get_type
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
name|GimpTextOptionsClass
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
name|gimp_text_options_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpTextOptions
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_text_options_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_TOOL_OPTIONS
argument_list|,
literal|"GimpTextOptions"
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
DECL|function|gimp_text_options_class_init (GimpTextOptionsClass * klass)
name|gimp_text_options_class_init
parameter_list|(
name|GimpTextOptionsClass
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
name|get_property
operator|=
name|gimp_text_options_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_TEXT
argument_list|,
literal|"text"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TEXT
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_options_init (GimpTextOptions * options)
name|gimp_text_options_init
parameter_list|(
name|GimpTextOptions
modifier|*
name|options
parameter_list|)
block|{
name|GObject
modifier|*
name|text
decl_stmt|;
name|text
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEXT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|options
operator|->
name|text
operator|=
name|GIMP_TEXT
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|options
operator|->
name|buffer
operator|=
name|gimp_prop_text_buffer_new
argument_list|(
name|text
argument_list|,
literal|"text"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|options
argument_list|,
literal|"notify::font"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_text_options_notify_font
argument_list|)
argument_list|,
name|text
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|text
argument_list|,
literal|"notify::font"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_text_notify_font
argument_list|)
argument_list|,
name|options
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_text_options_get_property
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
name|GimpTextOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_TEXT_OPTIONS
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
name|PROP_TEXT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|text
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
DECL|function|gimp_text_options_notify_font (GimpContext * context,GParamSpec * pspec,GimpText * text)
name|gimp_text_options_notify_font
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpText
modifier|*
name|text
parameter_list|)
block|{
name|GimpFont
modifier|*
name|font
init|=
name|gimp_context_get_font
argument_list|(
name|context
argument_list|)
decl_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|text
argument_list|,
name|gimp_text_notify_font
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|text
argument_list|,
literal|"font"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|font
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|text
argument_list|,
name|gimp_text_notify_font
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_notify_font (GimpText * text,GParamSpec * pspec,GimpContext * context)
name|gimp_text_notify_font
parameter_list|(
name|GimpText
modifier|*
name|text
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpObject
modifier|*
name|font
decl_stmt|;
name|gchar
modifier|*
name|value
decl_stmt|;
name|g_object_get
argument_list|(
name|text
argument_list|,
literal|"font"
argument_list|,
operator|&
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|font
operator|=
name|gimp_container_get_child_by_name
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|fonts
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|context
argument_list|,
name|gimp_text_options_notify_font
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|context
argument_list|,
literal|"font"
argument_list|,
name|font
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|context
argument_list|,
name|gimp_text_options_notify_font
argument_list|,
name|text
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_text_options_gui (GimpToolOptions * tool_options)
name|gimp_text_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GimpTextOptions
modifier|*
name|options
decl_stmt|;
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
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|auto_button
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|GtkWidget
modifier|*
name|font_selection
decl_stmt|;
name|GtkWidget
modifier|*
name|box
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|gint
name|digits
decl_stmt|;
name|options
operator|=
name|GIMP_TEXT_OPTIONS
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|config
operator|=
name|G_OBJECT
argument_list|(
name|options
operator|->
name|text
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gimp_tool_options_gui
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|10
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
literal|2
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
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|preview
operator|=
name|gimp_prop_preview_new
argument_list|(
name|G_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
literal|"font"
argument_list|,
literal|24
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
literal|0
argument_list|,
name|_
argument_list|(
literal|"Font:"
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
name|gimp_text_options_font_clicked
argument_list|)
argument_list|,
name|options
argument_list|)
expr_stmt|;
name|font_selection
operator|=
name|gimp_prop_font_selection_new
argument_list|(
name|config
argument_list|,
literal|"font"
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
literal|"_Font:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|font_selection
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|digits
operator|=
name|gimp_unit_get_digits
argument_list|(
name|options
operator|->
name|text
operator|->
name|font_size_unit
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gimp_prop_spin_button_new
argument_list|(
name|config
argument_list|,
literal|"font-size"
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
name|digits
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
literal|"_Size:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|spinbutton
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|menu
operator|=
name|gimp_prop_unit_menu_new
argument_list|(
name|config
argument_list|,
literal|"font-size-unit"
argument_list|,
literal|"%a"
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menu
argument_list|)
argument_list|,
literal|"set_digits"
argument_list|,
name|spinbutton
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|menu
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menu
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"hinting"
argument_list|,
name|_
argument_list|(
literal|"_Hinting"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|button
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
literal|3
argument_list|,
literal|4
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|auto_button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"autohint"
argument_list|,
name|_
argument_list|(
literal|"Force use of auto-hinter"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|auto_button
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
literal|4
argument_list|,
literal|5
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|auto_button
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|auto_button
argument_list|,
name|options
operator|->
name|text
operator|->
name|hinting
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
name|auto_button
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"antialias"
argument_list|,
name|_
argument_list|(
literal|"Antialiasing"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|button
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
literal|5
argument_list|,
literal|6
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_color_button_new
argument_list|(
name|config
argument_list|,
literal|"color"
argument_list|,
name|_
argument_list|(
literal|"Text Color"
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
literal|24
argument_list|,
name|GIMP_COLOR_AREA_FLAT
argument_list|)
expr_stmt|;
name|gimp_color_panel_set_context
argument_list|(
name|GIMP_COLOR_PANEL
argument_list|(
name|button
argument_list|)
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
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
literal|6
argument_list|,
name|_
argument_list|(
literal|"Color:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|button
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|box
operator|=
name|gimp_prop_enum_stock_box_new
argument_list|(
name|config
argument_list|,
literal|"justify"
argument_list|,
literal|"gtk-justify"
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
literal|7
argument_list|,
name|_
argument_list|(
literal|"Justify:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|box
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gimp_prop_spin_button_new
argument_list|(
name|config
argument_list|,
literal|"indent"
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
literal|5
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
literal|8
argument_list|,
name|_
argument_list|(
literal|"Indent:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|spinbutton
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gimp_prop_spin_button_new
argument_list|(
name|config
argument_list|,
literal|"line-spacing"
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gimp_table_attach_stock
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|9
argument_list|,
name|_
argument_list|(
literal|"Line\nSpacing:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
name|spinbutton
argument_list|,
literal|1
argument_list|,
name|GIMP_STOCK_LINE_SPACING
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
DECL|function|gimp_text_options_font_clicked (GtkWidget * widget,GimpContext * context)
name|gimp_text_options_font_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|toplevel
decl_stmt|;
name|GtkWidget
modifier|*
name|popup
decl_stmt|;
name|toplevel
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|popup
operator|=
name|gimp_container_popup_new
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|fonts
argument_list|,
name|context
argument_list|,
name|GIMP_DOCK
argument_list|(
name|toplevel
argument_list|)
operator|->
name|dialog_factory
argument_list|,
literal|"gimp-font-list"
argument_list|,
name|GTK_STOCK_SELECT_FONT
argument_list|,
name|_
argument_list|(
literal|"Open the font selection dialog"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_popup_show
argument_list|(
name|GIMP_CONTAINER_POPUP
argument_list|(
name|popup
argument_list|)
argument_list|,
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

