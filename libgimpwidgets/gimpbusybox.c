begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpbusybox.c  * Copyright (C) 2018 Ell  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpbusybox.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetsutils.h"
end_include

begin_comment
comment|/**  * SECTION: gimpbusybox  * @title: GimpBusyBox  * @short_description: A widget indicating an ongoing operation  *  * #GimpBusyBox displays a styled message, providing indication of  * an ongoing operation.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2acba3300103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_MESSAGE
name|PROP_MESSAGE
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpBusyBoxPrivate
struct|struct
name|_GimpBusyBoxPrivate
block|{
DECL|member|label
name|GtkLabel
modifier|*
name|label
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_busy_box_set_property
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
name|gimp_busy_box_get_property
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
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpBusyBox,gimp_busy_box,GTK_TYPE_BOX)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpBusyBox
argument_list|,
argument|gimp_busy_box
argument_list|,
argument|GTK_TYPE_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_busy_box_parent_class
end_define

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
name|gimp_busy_box_class_init
parameter_list|(
name|GimpBusyBoxClass
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
name|gimp_busy_box_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_busy_box_get_property
expr_stmt|;
comment|/**    * GimpBusyBox:message:    *    * Specifies the displayed message.    *    * Since: 2.10.4    **/
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_MESSAGE
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"message"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
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
DECL|function|gimp_busy_box_init (GimpBusyBox * box)
name|gimp_busy_box_init
parameter_list|(
name|GimpBusyBox
modifier|*
name|box
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|spinner
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|box
operator|->
name|priv
operator|=
name|gimp_busy_box_get_instance_private
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|gtk_widget_set_halign
argument_list|(
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
argument_list|,
name|GTK_ALIGN_CENTER
argument_list|)
expr_stmt|;
name|gtk_widget_set_valign
argument_list|(
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
argument_list|,
name|GTK_ALIGN_CENTER
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
literal|8
argument_list|)
expr_stmt|;
comment|/* the spinner */
name|spinner
operator|=
name|gtk_spinner_new
argument_list|()
expr_stmt|;
name|gtk_spinner_start
argument_list|(
name|GTK_SPINNER
argument_list|(
name|spinner
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
name|spinner
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
name|spinner
argument_list|)
expr_stmt|;
comment|/* the label */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|box
operator|->
name|priv
operator|->
name|label
operator|=
name|GTK_LABEL
argument_list|(
name|label
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
DECL|function|gimp_busy_box_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_busy_box_set_property
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
name|GimpBusyBox
modifier|*
name|box
init|=
name|GIMP_BUSY_BOX
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
name|PROP_MESSAGE
case|:
name|gtk_label_set_text
argument_list|(
name|box
operator|->
name|priv
operator|->
name|label
argument_list|,
name|g_value_get_string
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

begin_function
specifier|static
name|void
DECL|function|gimp_busy_box_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_busy_box_get_property
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
name|GimpBusyBox
modifier|*
name|box
init|=
name|GIMP_BUSY_BOX
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
name|PROP_MESSAGE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|gtk_label_get_text
argument_list|(
name|box
operator|->
name|priv
operator|->
name|label
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
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_busy_box_new:  * @message: (allow-none): the displayed message, or %NULL  *  * Creates a new #GimpBusyBox widget.  *  * Returns: A pointer to the new #GimpBusyBox widget.  *  * Since: 2.10.4  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_busy_box_new (const gchar * message)
name|gimp_busy_box_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
if|if
condition|(
name|message
operator|==
name|NULL
condition|)
name|message
operator|=
literal|""
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_BUSY_BOX
argument_list|,
literal|"message"
argument_list|,
name|message
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_busy_box_set_message:  * @box:     a #GimpBusyBox  * @message: the displayed message  *  * Sets the displayed message og @box to @message.  *  * Since: 2.10.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_busy_box_set_message (GimpBusyBox * box,const gchar * message)
name|gimp_busy_box_set_message
parameter_list|(
name|GimpBusyBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BUSY_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|message
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|box
argument_list|,
literal|"message"
argument_list|,
name|message
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_busy_box_get_message:  * @box: a #GimpBusyBox  *  * Returns the displayed message of @box.  *  * Returns: The displayed message.  *  * Since: 2.10.4  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_busy_box_get_message (GimpBusyBox * box)
name|gimp_busy_box_get_message
parameter_list|(
name|GimpBusyBox
modifier|*
name|box
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BUSY_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gtk_label_get_text
argument_list|(
name|box
operator|->
name|priv
operator|->
name|label
argument_list|)
return|;
block|}
end_function

end_unit

