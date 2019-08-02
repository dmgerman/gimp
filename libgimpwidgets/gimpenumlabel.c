begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpenumlabel.c  * Copyright (C) 2005  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpenumlabel.h"
end_include

begin_comment
comment|/**  * SECTION: gimpenumlabel  * @title: GimpEnumLabel  * @short_description: A #GtkLabel subclass that displays an enum value.  *  * A #GtkLabel subclass that displays an enum value.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon292b10d90103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ENUM_TYPE
name|PROP_ENUM_TYPE
block|,
DECL|enumerator|PROP_ENUM_VALUE
name|PROP_ENUM_VALUE
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpEnumLabelPrivate
struct|struct
name|_GimpEnumLabelPrivate
block|{
DECL|member|enum_class
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (obj)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(((GimpEnumLabel *) (obj))->priv)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_enum_label_finalize
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
name|gimp_enum_label_get_property
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
name|gimp_enum_label_set_property
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

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpEnumLabel,gimp_enum_label,GTK_TYPE_LABEL)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpEnumLabel
argument_list|,
argument|gimp_enum_label
argument_list|,
argument|GTK_TYPE_LABEL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_enum_label_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_enum_label_class_init
parameter_list|(
name|GimpEnumLabelClass
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
name|finalize
operator|=
name|gimp_enum_label_finalize
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_enum_label_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_enum_label_set_property
expr_stmt|;
comment|/**    * GimpEnumLabel:enum-type:    *    * The #GType of the enum.    *    * Since: 2.8    **/
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ENUM_TYPE
argument_list|,
name|g_param_spec_gtype
argument_list|(
literal|"enum-type"
argument_list|,
literal|"Enum Type"
argument_list|,
literal|"The type of the displayed enum"
argument_list|,
name|G_TYPE_NONE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
comment|/**    * GimpEnumLabel:enum-value:    *    * The value to display.    *    * Since: 2.8    **/
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ENUM_VALUE
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"enum-value"
argument_list|,
literal|"Enum Value"
argument_list|,
literal|"The enum value to display"
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_label_init (GimpEnumLabel * enum_label)
name|gimp_enum_label_init
parameter_list|(
name|GimpEnumLabel
modifier|*
name|enum_label
parameter_list|)
block|{
name|enum_label
operator|->
name|priv
operator|=
name|gimp_enum_label_get_instance_private
argument_list|(
name|enum_label
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_label_finalize (GObject * object)
name|gimp_enum_label_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpEnumLabelPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|private
operator|->
name|enum_class
argument_list|,
name|g_type_class_unref
argument_list|)
expr_stmt|;
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
DECL|function|gimp_enum_label_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_enum_label_get_property
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
name|GimpEnumLabelPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|PROP_ENUM_TYPE
case|:
if|if
condition|(
name|private
operator|->
name|enum_class
condition|)
name|g_value_set_gtype
argument_list|(
name|value
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|private
operator|->
name|enum_class
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|g_value_set_gtype
argument_list|(
name|value
argument_list|,
name|G_TYPE_NONE
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
DECL|function|gimp_enum_label_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_enum_label_set_property
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
name|GimpEnumLabel
modifier|*
name|label
init|=
name|GIMP_ENUM_LABEL
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpEnumLabelPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|label
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_ENUM_TYPE
case|:
name|private
operator|->
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|g_value_get_gtype
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ENUM_VALUE
case|:
name|gimp_enum_label_set_value
argument_list|(
name|label
argument_list|,
name|g_value_get_int
argument_list|(
name|value
argument_list|)
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
comment|/**  * gimp_enum_label_new:  * @enum_type: the #GType of an enum  * @value:     an enum value  *  * Returns: a new #GimpEnumLabel.  *  * Since: 2.4  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_label_new (GType enum_type,gint value)
name|gimp_enum_label_new
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|value
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_ENUM_LABEL
argument_list|,
literal|"enum-type"
argument_list|,
name|enum_type
argument_list|,
literal|"enum-value"
argument_list|,
name|value
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_label_set_value  * @label: a #GimpEnumLabel  * @value: an enum value  *  * Since: 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_enum_label_set_value (GimpEnumLabel * label,gint value)
name|gimp_enum_label_set_value
parameter_list|(
name|GimpEnumLabel
modifier|*
name|label
parameter_list|,
name|gint
name|value
parameter_list|)
block|{
name|GimpEnumLabelPrivate
modifier|*
name|private
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|nick
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|desc
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ENUM_LABEL
argument_list|(
name|label
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_enum_get_value
argument_list|(
name|G_TYPE_FROM_CLASS
argument_list|(
name|private
operator|->
name|enum_class
argument_list|)
argument_list|,
name|value
argument_list|,
name|NULL
argument_list|,
operator|&
name|nick
argument_list|,
operator|&
name|desc
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: %d is not valid for enum of type '%s'"
argument_list|,
name|G_STRLOC
argument_list|,
name|value
argument_list|,
name|g_type_name
argument_list|(
name|G_TYPE_FROM_CLASS
argument_list|(
name|private
operator|->
name|enum_class
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|desc
condition|)
name|desc
operator|=
name|nick
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|desc
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

