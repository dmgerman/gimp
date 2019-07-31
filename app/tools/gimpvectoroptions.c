begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpvectoroptions.c  * Copyright (C) 1999 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectoroptions.h"
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
DECL|enum|__anon2a2e6b1d0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_VECTORS_EDIT_MODE
name|PROP_VECTORS_EDIT_MODE
block|,
DECL|enumerator|PROP_VECTORS_POLYGONAL
name|PROP_VECTORS_POLYGONAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_vector_options_set_property
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
name|gimp_vector_options_get_property
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
DECL|function|G_DEFINE_TYPE (GimpVectorOptions,gimp_vector_options,GIMP_TYPE_TOOL_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpVectorOptions
argument_list|,
argument|gimp_vector_options
argument_list|,
argument|GIMP_TYPE_TOOL_OPTIONS
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_vector_options_class_init
parameter_list|(
name|GimpVectorOptionsClass
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
name|gimp_vector_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_vector_options_get_property
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_VECTORS_EDIT_MODE
argument_list|,
literal|"vectors-edit-mode"
argument_list|,
name|_
argument_list|(
literal|"Edit Mode"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_VECTOR_MODE
argument_list|,
name|GIMP_VECTOR_MODE_DESIGN
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_VECTORS_POLYGONAL
argument_list|,
literal|"vectors-polygonal"
argument_list|,
name|_
argument_list|(
literal|"Polygonal"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Restrict editing to polygons"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vector_options_init (GimpVectorOptions * options)
name|gimp_vector_options_init
parameter_list|(
name|GimpVectorOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vector_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_vector_options_set_property
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
name|GimpVectorOptions
modifier|*
name|options
init|=
name|GIMP_VECTOR_OPTIONS
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
name|PROP_VECTORS_EDIT_MODE
case|:
name|options
operator|->
name|edit_mode
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VECTORS_POLYGONAL
case|:
name|options
operator|->
name|polygonal
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
DECL|function|gimp_vector_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_vector_options_get_property
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
name|GimpVectorOptions
modifier|*
name|options
init|=
name|GIMP_VECTOR_OPTIONS
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
name|PROP_VECTORS_EDIT_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|edit_mode
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VECTORS_POLYGONAL
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|polygonal
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
DECL|function|button_append_modifier (GtkWidget * button,GdkModifierType modifiers)
name|button_append_modifier
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GdkModifierType
name|modifiers
parameter_list|)
block|{
name|gchar
modifier|*
name|str
init|=
name|g_strdup_printf
argument_list|(
literal|"%s (%s)"
argument_list|,
name|gtk_button_get_label
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|modifiers
argument_list|)
argument_list|)
decl_stmt|;
name|gtk_button_set_label
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_vector_options_gui (GimpToolOptions * tool_options)
name|gimp_vector_options_gui
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
name|GimpVectorOptions
modifier|*
name|options
init|=
name|GIMP_VECTOR_OPTIONS
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
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
comment|/*  tool toggle  */
name|frame
operator|=
name|gimp_prop_enum_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"vectors-edit-mode"
argument_list|,
name|NULL
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
if|if
condition|(
name|GTK_IS_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
condition|)
block|{
name|GSList
modifier|*
name|list
init|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
decl_stmt|;
comment|/* GIMP_VECTOR_MODE_MOVE  */
name|button_append_modifier
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|GDK_MOD1_MASK
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|next
condition|)
comment|/* GIMP_VECTOR_MODE_EDIT  */
name|button_append_modifier
argument_list|(
name|list
operator|->
name|next
operator|->
name|data
argument_list|,
name|gimp_get_toggle_behavior_mask
argument_list|()
argument_list|)
expr_stmt|;
block|}
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"vectors-polygonal"
argument_list|,
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
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Path to Selection\n"
literal|"%s  Add\n"
literal|"%s  Subtract\n"
literal|"%s  Intersect"
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|gimp_get_extend_selection_mask
argument_list|()
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|gimp_get_modify_selection_mask
argument_list|()
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|gimp_get_extend_selection_mask
argument_list|()
operator||
name|gimp_get_modify_selection_mask
argument_list|()
argument_list|)
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_button_new
argument_list|()
expr_stmt|;
comment|/*  Create a selection from the current path  */
name|gtk_button_set_label
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Selection from Path"
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
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|str
argument_list|,
name|GIMP_HELP_PATH_SELECTION_REPLACE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|options
operator|->
name|to_selection_button
operator|=
name|button
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Fill Path"
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
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_PATH_FILL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|options
operator|->
name|fill_button
operator|=
name|button
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Stroke Path"
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
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_PATH_STROKE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|options
operator|->
name|stroke_button
operator|=
name|button
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit

