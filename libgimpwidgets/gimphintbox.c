begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimphintbox.c  * Copyright (C) 2006 Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimpwidgets.h"
end_include

begin_comment
comment|/**  * SECTION: gimphintbox  * @title: GimpHintBox  * @short_description: Displays a wilber icon and a text.  *  * Displays a wilber icon and a text.  **/
end_comment

begin_typedef
DECL|typedef|GimpHintBoxClass
typedef|typedef
name|GtkBoxClass
name|GimpHintBoxClass
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon295aa6af0108
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|icon_name
name|gchar
modifier|*
name|icon_name
decl_stmt|;
DECL|member|stock_id
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|hint
name|gchar
modifier|*
name|hint
decl_stmt|;
DECL|typedef|GimpHintBox
block|}
name|GimpHintBox
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_HINT_BOX (obj)
define|#
directive|define
name|GIMP_HINT_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_HINT_BOX, GimpHintBox))
end_define

begin_enum
enum|enum
DECL|enum|__anon295aa6af0203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ICON_NAME
name|PROP_ICON_NAME
block|,
DECL|enumerator|PROP_STOCK_ID
name|PROP_STOCK_ID
block|,
DECL|enumerator|PROP_HINT
name|PROP_HINT
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_hint_box_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_hint_box_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_hint_box_set_property
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
name|gimp_hint_box_get_property
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
DECL|function|G_DEFINE_TYPE (GimpHintBox,gimp_hint_box,GTK_TYPE_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpHintBox
argument_list|,
argument|gimp_hint_box
argument_list|,
argument|GTK_TYPE_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_hint_box_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_hint_box_class_init
parameter_list|(
name|GimpHintBoxClass
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
name|constructed
operator|=
name|gimp_hint_box_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_hint_box_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_hint_box_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_hint_box_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ICON_NAME
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"icon-name"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_INFO
argument_list|,
name|G_PARAM_CONSTRUCT_ONLY
operator||
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_STOCK_ID
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"stock-id"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_INFO
argument_list|,
name|G_PARAM_CONSTRUCT_ONLY
operator||
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_HINT
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"hint"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_CONSTRUCT_ONLY
operator||
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_hint_box_init (GimpHintBox * box)
name|gimp_hint_box_init
parameter_list|(
name|GimpHintBox
modifier|*
name|box
parameter_list|)
block|{
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|box
argument_list|)
argument_list|,
name|GTK_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_hint_box_constructed (GObject * object)
name|gimp_hint_box_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpHintBox
modifier|*
name|box
init|=
name|GIMP_HINT_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|image
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
if|if
condition|(
name|box
operator|->
name|icon_name
condition|)
block|{
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|box
operator|->
name|icon_name
argument_list|,
name|GTK_ICON_SIZE_DIALOG
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|box
operator|->
name|stock_id
condition|)
block|{
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|box
operator|->
name|stock_id
argument_list|,
name|GTK_ICON_SIZE_DIALOG
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|image
condition|)
block|{
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|image
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
name|image
argument_list|)
expr_stmt|;
block|}
name|label
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_LABEL
argument_list|,
literal|"label"
argument_list|,
name|box
operator|->
name|hint
argument_list|,
literal|"wrap"
argument_list|,
name|TRUE
argument_list|,
literal|"justify"
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|,
literal|"xalign"
argument_list|,
literal|0.0
argument_list|,
literal|"yalign"
argument_list|,
literal|0.5
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_STYLE
argument_list|,
name|PANGO_STYLE_ITALIC
argument_list|,
operator|-
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
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_hint_box_finalize (GObject * object)
name|gimp_hint_box_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpHintBox
modifier|*
name|box
init|=
name|GIMP_HINT_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|box
operator|->
name|icon_name
condition|)
block|{
name|g_free
argument_list|(
name|box
operator|->
name|icon_name
argument_list|)
expr_stmt|;
name|box
operator|->
name|icon_name
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|box
operator|->
name|stock_id
condition|)
block|{
name|g_free
argument_list|(
name|box
operator|->
name|stock_id
argument_list|)
expr_stmt|;
name|box
operator|->
name|stock_id
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|box
operator|->
name|hint
condition|)
block|{
name|g_free
argument_list|(
name|box
operator|->
name|hint
argument_list|)
expr_stmt|;
name|box
operator|->
name|hint
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
specifier|static
name|void
DECL|function|gimp_hint_box_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_hint_box_set_property
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
name|GimpHintBox
modifier|*
name|box
init|=
name|GIMP_HINT_BOX
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
name|PROP_ICON_NAME
case|:
name|box
operator|->
name|icon_name
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STOCK_ID
case|:
name|box
operator|->
name|stock_id
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HINT
case|:
name|box
operator|->
name|hint
operator|=
name|g_value_dup_string
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
DECL|function|gimp_hint_box_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_hint_box_get_property
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
name|GimpHintBox
modifier|*
name|box
init|=
name|GIMP_HINT_BOX
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
name|PROP_ICON_NAME
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|box
operator|->
name|icon_name
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STOCK_ID
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|box
operator|->
name|stock_id
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HINT
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|box
operator|->
name|hint
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
comment|/**  * gimp_hint_box_new:  * @hint: text to display as a user hint  *  * Creates a new widget that shows a text label showing @hint,  * decorated with a GIMP_STOCK_INFO wilber icon.  *  * Return value: a new widget  *  * Since GIMP 2.4  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_hint_box_new (const gchar * hint)
name|gimp_hint_box_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|hint
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|hint
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_HINT_BOX
argument_list|,
literal|"hint"
argument_list|,
name|hint
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

