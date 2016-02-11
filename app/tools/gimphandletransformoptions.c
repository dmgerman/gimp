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
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpspinscale.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimphandletransformoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2be039640103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_HANDLE_MODE
name|PROP_HANDLE_MODE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_handle_transform_options_set_property
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
name|gimp_handle_transform_options_get_property
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
DECL|function|G_DEFINE_TYPE (GimpHandleTransformOptions,gimp_handle_transform_options,GIMP_TYPE_TRANSFORM_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpHandleTransformOptions
argument_list|,
argument|gimp_handle_transform_options
argument_list|,
argument|GIMP_TYPE_TRANSFORM_OPTIONS
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_handle_transform_options_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_handle_transform_options_class_init
parameter_list|(
name|GimpHandleTransformOptionsClass
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
name|gimp_handle_transform_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_handle_transform_options_get_property
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_HANDLE_MODE
argument_list|,
literal|"handle-mode"
argument_list|,
name|_
argument_list|(
literal|"Handle mode"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Handle mode"
argument_list|)
argument_list|,
name|GIMP_TYPE_TRANSFORM_HANDLE_MODE
argument_list|,
name|GIMP_HANDLE_MODE_ADD_TRANSFORM
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_handle_transform_options_init (GimpHandleTransformOptions * options)
name|gimp_handle_transform_options_init
parameter_list|(
name|GimpHandleTransformOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_handle_transform_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_handle_transform_options_set_property
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
name|GimpHandleTransformOptions
modifier|*
name|options
init|=
name|GIMP_HANDLE_TRANSFORM_OPTIONS
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
name|PROP_HANDLE_MODE
case|:
name|options
operator|->
name|handle_mode
operator|=
name|g_value_get_enum
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
DECL|function|gimp_handle_transform_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_handle_transform_options_get_property
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
name|GimpHandleTransformOptions
modifier|*
name|options
init|=
name|GIMP_HANDLE_TRANSFORM_OPTIONS
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
name|PROP_HANDLE_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|handle_mode
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

begin_comment
comment|/**  * gimp_handle_transform_options_gui:  * @tool_options: a #GimpToolOptions  *  * Build the Transform Tool Options.  *  * Return value: a container holding the transform tool options  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_handle_transform_options_gui (GimpToolOptions * tool_options)
name|gimp_handle_transform_options_gui
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
name|gimp_transform_options_gui
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
name|gint
name|i
decl_stmt|;
name|frame
operator|=
name|gimp_prop_enum_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"handle-mode"
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
comment|/* add modifier to name, add tooltip */
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
for|for
control|(
name|i
operator|=
name|g_slist_length
argument_list|(
name|list
argument_list|)
operator|-
literal|1
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
operator|,
name|i
operator|--
control|)
block|{
name|GdkModifierType
name|shift
init|=
name|gimp_get_extend_selection_mask
argument_list|()
decl_stmt|;
name|GdkModifierType
name|ctrl
init|=
name|gimp_get_constrain_behavior_mask
argument_list|()
decl_stmt|;
name|GdkModifierType
name|modifier
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
name|tooltip
init|=
literal|""
decl_stmt|;
name|gchar
modifier|*
name|tip
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
switch|switch
condition|(
name|i
condition|)
block|{
case|case
name|GIMP_HANDLE_MODE_ADD_TRANSFORM
case|:
name|modifier
operator|=
literal|0
expr_stmt|;
name|tooltip
operator|=
name|_
argument_list|(
literal|"Add handles and transform the image"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_MODE_MOVE
case|:
name|modifier
operator|=
name|shift
expr_stmt|;
name|tooltip
operator|=
name|_
argument_list|(
literal|"Move transform handles"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_MODE_REMOVE
case|:
name|modifier
operator|=
name|ctrl
expr_stmt|;
name|tooltip
operator|=
name|_
argument_list|(
literal|"Remove transform handles"
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|modifier
condition|)
block|{
name|label
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s (%s)"
argument_list|,
name|gtk_button_get_label
argument_list|(
name|GTK_BUTTON
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|modifier
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_button_set_label
argument_list|(
name|GTK_BUTTON
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|tip
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s  (%s)"
argument_list|,
name|tooltip
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|modifier
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|tip
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tip
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_help_set_help_data
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|tooltip
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
block|}
return|return
name|vbox
return|;
block|}
end_function

end_unit

