begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpstrokeoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpdasheditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpstrokeeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b98c8ac0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_OPTIONS
name|PROP_OPTIONS
block|,
DECL|enumerator|PROP_RESOLUTION
name|PROP_RESOLUTION
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_stroke_editor_class_init
parameter_list|(
name|GimpStrokeEditorClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_stroke_editor_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_stroke_editor_set_property
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
name|gimp_stroke_editor_get_property
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
name|gimp_stroke_editor_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_stroke_editor_paint_button
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_stroke_editor_dash_preset
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkVBoxClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_stroke_editor_get_type (void)
name|gimp_stroke_editor_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|view_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|view_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|view_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpStrokeEditorClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init      */
name|NULL
block|,
comment|/* base_finalize  */
operator|(
name|GClassInitFunc
operator|)
name|gimp_stroke_editor_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpStrokeEditor
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_VBOX
argument_list|,
literal|"GimpStrokeEditor"
argument_list|,
operator|&
name|view_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|view_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_editor_class_init (GimpStrokeEditorClass * klass)
name|gimp_stroke_editor_class_init
parameter_list|(
name|GimpStrokeEditorClass
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_stroke_editor_constructor
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_stroke_editor_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_stroke_editor_get_property
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_stroke_editor_finalize
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_OPTIONS
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"options"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_STROKE_OPTIONS
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_RESOLUTION
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"resolution"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_MIN_RESOLUTION
argument_list|,
name|GIMP_MAX_RESOLUTION
argument_list|,
literal|72.0
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_stroke_editor_set_property
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
name|GimpStrokeEditor
modifier|*
name|editor
init|=
name|GIMP_STROKE_EDITOR
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
name|PROP_OPTIONS
case|:
name|editor
operator|->
name|options
operator|=
name|GIMP_STROKE_OPTIONS
argument_list|(
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RESOLUTION
case|:
name|editor
operator|->
name|resolution
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
DECL|function|gimp_stroke_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_stroke_editor_get_property
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
name|GimpStrokeEditor
modifier|*
name|editor
init|=
name|GIMP_STROKE_EDITOR
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
name|PROP_OPTIONS
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|options
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RESOLUTION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|resolution
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
name|GObject
modifier|*
DECL|function|gimp_stroke_editor_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_stroke_editor_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GimpStrokeEditor
modifier|*
name|editor
decl_stmt|;
name|GtkWidget
modifier|*
name|box
decl_stmt|;
name|GtkWidget
modifier|*
name|size
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|expander
decl_stmt|;
name|GtkWidget
modifier|*
name|dash_editor
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GObject
modifier|*
name|object
decl_stmt|;
name|gint
name|row
init|=
literal|0
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|editor
operator|=
name|GIMP_STROKE_EDITOR
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|editor
operator|->
name|options
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|box
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
name|editor
argument_list|)
argument_list|,
name|box
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
name|box
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Line Width:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
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
name|size
operator|=
name|gimp_prop_size_entry_new
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|options
argument_list|)
argument_list|,
literal|"width"
argument_list|,
literal|"unit"
argument_list|,
literal|"%a"
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|,
name|editor
operator|->
name|resolution
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_pixel_digits
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|size
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
name|size
argument_list|)
expr_stmt|;
name|expander
operator|=
name|gtk_expander_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Line Style"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|expander
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
name|expander
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
literal|"<expander>"
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|expander
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|5
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
literal|4
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
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|4
argument_list|,
literal|4
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
name|box
operator|=
name|gimp_prop_enum_stock_box_new
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|options
argument_list|)
argument_list|,
literal|"cap-style"
argument_list|,
literal|"gimp-cap"
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
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"_Cap style:"
argument_list|)
argument_list|,
literal|0.0
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
name|box
operator|=
name|gimp_prop_enum_stock_box_new
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|options
argument_list|)
argument_list|,
literal|"join-style"
argument_list|,
literal|"gimp-join"
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
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"_Join style:"
argument_list|)
argument_list|,
literal|0.0
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
name|gimp_prop_scale_entry_new
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|options
argument_list|)
argument_list|,
literal|"miter-limit"
argument_list|,
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"_Miter limit:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
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
name|GTK_SHADOW_IN
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
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Dash pattern:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|frame
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|box
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
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
name|box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|dash_editor
operator|=
name|gimp_dash_editor_new
argument_list|(
name|editor
operator|->
name|options
argument_list|)
expr_stmt|;
name|button
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_BUTTON
argument_list|,
literal|"width-request"
argument_list|,
literal|14
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dash_editor_shift_left
argument_list|)
argument_list|,
name|dash_editor
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|button
argument_list|,
literal|"expose-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_stroke_editor_paint_button
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|dash_editor
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
name|dash_editor
argument_list|)
expr_stmt|;
name|button
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_BUTTON
argument_list|,
literal|"width-request"
argument_list|,
literal|14
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dash_editor_shift_right
argument_list|)
argument_list|,
name|dash_editor
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|button
argument_list|,
literal|"expose-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_stroke_editor_paint_button
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|box
operator|=
name|gimp_enum_combo_box_new
argument_list|(
name|GIMP_TYPE_DASH_PRESET
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|GIMP_DASH_CUSTOM
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
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Dash preset:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|box
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|box
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_stroke_editor_dash_preset
argument_list|)
argument_list|,
name|editor
operator|->
name|options
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|editor
operator|->
name|options
argument_list|,
literal|"dash_info_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_combo_box_set_active
argument_list|)
argument_list|,
name|box
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|options
argument_list|)
argument_list|,
literal|"antialias"
argument_list|,
name|_
argument_list|(
literal|"_Antialiasing"
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
literal|0
argument_list|,
literal|3
argument_list|,
name|row
argument_list|,
name|row
operator|+
literal|1
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
name|row
operator|++
expr_stmt|;
name|box
operator|=
name|gimp_prop_enum_radio_box_new
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|options
argument_list|)
argument_list|,
literal|"style"
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
name|editor
argument_list|)
argument_list|,
name|box
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
name|box
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_editor_finalize (GObject * object)
name|gimp_stroke_editor_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpStrokeEditor
modifier|*
name|editor
init|=
name|GIMP_STROKE_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|options
condition|)
block|{
name|g_object_unref
argument_list|(
name|editor
operator|->
name|options
argument_list|)
expr_stmt|;
name|editor
operator|->
name|options
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_stroke_editor_new (GimpStrokeOptions * options,gdouble resolution)
name|gimp_stroke_editor_new
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|,
name|gdouble
name|resolution
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_STROKE_EDITOR
argument_list|,
literal|"options"
argument_list|,
name|options
argument_list|,
literal|"resolution"
argument_list|,
name|resolution
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_stroke_editor_paint_button (GtkWidget * widget,GdkEventExpose * event,gpointer data)
name|gimp_stroke_editor_paint_button
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkAllocation
modifier|*
name|alloc
init|=
operator|&
name|widget
operator|->
name|allocation
decl_stmt|;
name|gint
name|w
init|=
name|MIN
argument_list|(
name|alloc
operator|->
name|width
argument_list|,
name|alloc
operator|->
name|height
argument_list|)
operator|*
literal|2
operator|/
literal|3
decl_stmt|;
name|gtk_paint_arrow
argument_list|(
name|widget
operator|->
name|style
argument_list|,
name|widget
operator|->
name|window
argument_list|,
name|widget
operator|->
name|state
argument_list|,
name|GTK_SHADOW_IN
argument_list|,
operator|&
name|event
operator|->
name|area
argument_list|,
name|widget
argument_list|,
name|NULL
argument_list|,
name|data
condition|?
name|GTK_ARROW_LEFT
else|:
name|GTK_ARROW_RIGHT
argument_list|,
name|TRUE
argument_list|,
name|alloc
operator|->
name|x
operator|+
operator|(
name|alloc
operator|->
name|width
operator|-
name|w
operator|)
operator|/
literal|2
argument_list|,
name|alloc
operator|->
name|y
operator|+
operator|(
name|alloc
operator|->
name|height
operator|-
name|w
operator|)
operator|/
literal|2
argument_list|,
name|w
argument_list|,
name|w
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_editor_dash_preset (GtkWidget * widget,GimpStrokeOptions * options)
name|gimp_stroke_editor_dash_preset
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{
name|gint
name|value
decl_stmt|;
if|if
condition|(
name|gimp_int_combo_box_get_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|value
argument_list|)
operator|&&
name|value
operator|!=
name|GIMP_DASH_CUSTOM
condition|)
block|{
name|gimp_stroke_options_set_dash_pattern
argument_list|(
name|options
argument_list|,
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

