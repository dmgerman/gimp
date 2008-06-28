begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpgradientselectbutton.c  * Copyright (C) 1998 Andy Thomas  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpuitypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradientselectbutton.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimarshal.h"
end_include

begin_include
include|#
directive|include
file|"libgimp-intl.h"
end_include

begin_define
DECL|macro|CELL_HEIGHT
define|#
directive|define
name|CELL_HEIGHT
value|18
end_define

begin_define
DECL|macro|CELL_WIDTH
define|#
directive|define
name|CELL_WIDTH
value|84
end_define

begin_define
DECL|macro|GIMP_GRADIENT_SELECT_BUTTON_GET_PRIVATE (obj)
define|#
directive|define
name|GIMP_GRADIENT_SELECT_BUTTON_GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_PRIVATE ((obj), GIMP_TYPE_GRADIENT_SELECT_BUTTON, GimpGradientSelectButtonPrivate))
end_define

begin_typedef
DECL|typedef|GimpGradientSelectButtonPrivate
typedef|typedef
name|struct
name|_GimpGradientSelectButtonPrivate
name|GimpGradientSelectButtonPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpGradientSelectButtonPrivate
struct|struct
name|_GimpGradientSelectButtonPrivate
block|{
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
DECL|member|gradient_name
name|gchar
modifier|*
name|gradient_name
decl_stmt|;
comment|/* Local copy */
DECL|member|sample_size
name|gint
name|sample_size
decl_stmt|;
DECL|member|reverse
name|gboolean
name|reverse
decl_stmt|;
DECL|member|n_samples
name|gint
name|n_samples
decl_stmt|;
DECL|member|gradient_data
name|gdouble
modifier|*
name|gradient_data
decl_stmt|;
comment|/* Local copy */
DECL|member|inside
name|GtkWidget
modifier|*
name|inside
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
block|}
struct|;
end_struct

begin_enum
enum|enum
DECL|enum|__anon2c74430c0103
block|{
DECL|enumerator|GRADIENT_SET
name|GRADIENT_SET
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2c74430c0203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TITLE
name|PROP_TITLE
block|,
DECL|enumerator|PROP_GRADIENT_NAME
name|PROP_GRADIENT_NAME
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_gradient_select_button_finalize
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
name|gimp_gradient_select_button_set_property
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
name|gimp_gradient_select_button_get_property
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
name|gimp_gradient_select_button_clicked
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_gradient_select_button_callback
parameter_list|(
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|,
name|gint
name|n_samples
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|gradient_data
parameter_list|,
name|gboolean
name|dialog_closing
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_gradient_select_preview_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_gradient_select_preview_expose
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|,
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_gradient_select_drag_data_received
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_gradient_select_button_create_inside
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|target
specifier|static
specifier|const
name|GtkTargetEntry
name|target
init|=
block|{
literal|"application/x-gimp-gradient-name"
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradient_button_signals
specifier|static
name|guint
name|gradient_button_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|G_DEFINE_TYPE (GimpGradientSelectButton,gimp_gradient_select_button,GIMP_TYPE_SELECT_BUTTON)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpGradientSelectButton
argument_list|,
argument|gimp_gradient_select_button
argument_list|,
argument|GIMP_TYPE_SELECT_BUTTON
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_gradient_select_button_class_init
parameter_list|(
name|GimpGradientSelectButtonClass
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
name|GimpSelectButtonClass
modifier|*
name|select_button_class
init|=
name|GIMP_SELECT_BUTTON_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_gradient_select_button_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_gradient_select_button_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_gradient_select_button_get_property
expr_stmt|;
name|select_button_class
operator|->
name|select_destroy
operator|=
name|gimp_gradient_select_destroy
expr_stmt|;
name|klass
operator|->
name|gradient_set
operator|=
name|NULL
expr_stmt|;
comment|/**    * GimpGradientSelectButton:title:    *    * The title to be used for the gradient selection popup dialog.    *    * Since: GIMP 2.4    */
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_TITLE
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"title"
argument_list|,
literal|"Title"
argument_list|,
literal|"The title to be used for the gradient selection popup dialog"
argument_list|,
name|_
argument_list|(
literal|"Gradient Selection"
argument_list|)
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
comment|/**    * GimpGradientSelectButton:gradient-name:    *    * The name of the currently selected gradient.    *    * Since: GIMP 2.4    */
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GRADIENT_NAME
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"gradient-name"
argument_list|,
literal|"Gradient name"
argument_list|,
literal|"The name of the currently selected gradient"
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
comment|/**    * GimpGradientSelectButton::gradient-set:    * @widget: the object which received the signal.    * @gradient_name: the name of the currently selected gradient.    * @width: width of the gradient    * @grad_data: gradient data    * @dialog_closing: whether the dialog was closed or not.    *    * The ::gradient-set signal is emitted when the user selects a gradient.    *    * Since: GIMP 2.4    */
name|gradient_button_signals
index|[
name|GRADIENT_SET
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"gradient-set"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpGradientSelectButtonClass
argument_list|,
name|gradient_set
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_gimpui_marshal_VOID__STRING_INT_POINTER_BOOLEAN
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|4
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpGradientSelectButtonPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_select_button_init (GimpGradientSelectButton * button)
name|gimp_gradient_select_button_init
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|)
block|{
name|GimpGradientSelectButtonPrivate
modifier|*
name|priv
decl_stmt|;
name|priv
operator|=
name|GIMP_GRADIENT_SELECT_BUTTON_GET_PRIVATE
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|priv
operator|->
name|gradient_name
operator|=
name|gimp_context_get_gradient
argument_list|()
expr_stmt|;
name|priv
operator|->
name|sample_size
operator|=
name|CELL_WIDTH
expr_stmt|;
name|priv
operator|->
name|reverse
operator|=
name|FALSE
expr_stmt|;
name|priv
operator|->
name|inside
operator|=
name|gimp_gradient_select_button_create_inside
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|priv
operator|->
name|inside
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_gradient_select_button_new:  * @title:         Title of the dialog to use or %NULL to use the default title.  * @gradient_name: Initial gradient name.  *  * Creates a new #GtkWidget that completely controls the selection of  * a gradient.  This widget is suitable for placement in a table in a  * plug-in dialog.  *  * Returns: A #GtkWidget that you can use in your UI.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_gradient_select_button_new (const gchar * title,const gchar * gradient_name)
name|gimp_gradient_select_button_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
if|if
condition|(
name|title
condition|)
name|button
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_GRADIENT_SELECT_BUTTON
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
literal|"gradient-name"
argument_list|,
name|gradient_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|button
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_GRADIENT_SELECT_BUTTON
argument_list|,
literal|"gradient-name"
argument_list|,
name|gradient_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|button
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_gradient_select_button_get_gradient:  * @button: A #GimpGradientSelectButton  *  * Retrieves the name of currently selected gradient.  *  * Returns: an internal copy of the gradient name which must not be freed.  *  * Since: GIMP 2.4  */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_gradient_select_button_get_gradient (GimpGradientSelectButton * button)
name|gimp_gradient_select_button_get_gradient
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|)
block|{
name|GimpGradientSelectButtonPrivate
modifier|*
name|priv
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GRADIENT_SELECT_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GIMP_GRADIENT_SELECT_BUTTON_GET_PRIVATE
argument_list|(
name|button
argument_list|)
expr_stmt|;
return|return
name|priv
operator|->
name|gradient_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_gradient_select_button_set_gradient:  * @button: A #GimpGradientSelectButton  * @gradient_name: Gradient name to set.  *  * Sets the current gradient for the gradient select button.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|void
DECL|function|gimp_gradient_select_button_set_gradient (GimpGradientSelectButton * button,const gchar * gradient_name)
name|gimp_gradient_select_button_set_gradient
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|)
block|{
name|GimpGradientSelectButtonPrivate
modifier|*
name|priv
decl_stmt|;
name|GimpSelectButton
modifier|*
name|select_button
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GRADIENT_SELECT_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GIMP_GRADIENT_SELECT_BUTTON_GET_PRIVATE
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|select_button
operator|=
name|GIMP_SELECT_BUTTON
argument_list|(
name|button
argument_list|)
expr_stmt|;
if|if
condition|(
name|select_button
operator|->
name|temp_callback
condition|)
block|{
name|gimp_gradients_set_popup
argument_list|(
name|select_button
operator|->
name|temp_callback
argument_list|,
name|gradient_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|gdouble
modifier|*
name|samples
decl_stmt|;
name|gint
name|n_samples
decl_stmt|;
if|if
condition|(
name|gradient_name
operator|&&
operator|*
name|gradient_name
condition|)
name|name
operator|=
name|g_strdup
argument_list|(
name|gradient_name
argument_list|)
expr_stmt|;
else|else
name|name
operator|=
name|gimp_context_get_gradient
argument_list|()
expr_stmt|;
if|if
condition|(
name|gimp_gradient_get_uniform_samples
argument_list|(
name|name
argument_list|,
name|priv
operator|->
name|sample_size
argument_list|,
name|priv
operator|->
name|reverse
argument_list|,
operator|&
name|n_samples
argument_list|,
operator|&
name|samples
argument_list|)
condition|)
block|{
name|gimp_gradient_select_button_callback
argument_list|(
name|name
argument_list|,
name|n_samples
argument_list|,
name|samples
argument_list|,
name|FALSE
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|samples
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_select_button_finalize (GObject * object)
name|gimp_gradient_select_button_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpGradientSelectButtonPrivate
modifier|*
name|priv
decl_stmt|;
name|priv
operator|=
name|GIMP_GRADIENT_SELECT_BUTTON_GET_PRIVATE
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|priv
operator|->
name|gradient_name
argument_list|)
expr_stmt|;
name|priv
operator|->
name|gradient_name
operator|=
name|NULL
expr_stmt|;
name|g_free
argument_list|(
name|priv
operator|->
name|gradient_data
argument_list|)
expr_stmt|;
name|priv
operator|->
name|gradient_data
operator|=
name|NULL
expr_stmt|;
name|g_free
argument_list|(
name|priv
operator|->
name|title
argument_list|)
expr_stmt|;
name|priv
operator|->
name|title
operator|=
name|NULL
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|gimp_gradient_select_button_parent_class
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
DECL|function|gimp_gradient_select_button_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_gradient_select_button_set_property
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
name|GimpGradientSelectButton
modifier|*
name|button
decl_stmt|;
name|GimpGradientSelectButtonPrivate
modifier|*
name|priv
decl_stmt|;
name|button
operator|=
name|GIMP_GRADIENT_SELECT_BUTTON
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GIMP_GRADIENT_SELECT_BUTTON_GET_PRIVATE
argument_list|(
name|button
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_TITLE
case|:
name|priv
operator|->
name|title
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_NAME
case|:
name|gimp_gradient_select_button_set_gradient
argument_list|(
name|button
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
DECL|function|gimp_gradient_select_button_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_gradient_select_button_get_property
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
name|GimpGradientSelectButton
modifier|*
name|button
decl_stmt|;
name|GimpGradientSelectButtonPrivate
modifier|*
name|priv
decl_stmt|;
name|button
operator|=
name|GIMP_GRADIENT_SELECT_BUTTON
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GIMP_GRADIENT_SELECT_BUTTON_GET_PRIVATE
argument_list|(
name|button
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_TITLE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|title
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_NAME
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|gradient_name
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
DECL|function|gimp_gradient_select_button_callback (const gchar * gradient_name,gint n_samples,const gdouble * gradient_data,gboolean dialog_closing,gpointer user_data)
name|gimp_gradient_select_button_callback
parameter_list|(
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|,
name|gint
name|n_samples
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|gradient_data
parameter_list|,
name|gboolean
name|dialog_closing
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpGradientSelectButton
modifier|*
name|button
decl_stmt|;
name|GimpGradientSelectButtonPrivate
modifier|*
name|priv
decl_stmt|;
name|GimpSelectButton
modifier|*
name|select_button
decl_stmt|;
name|button
operator|=
name|GIMP_GRADIENT_SELECT_BUTTON
argument_list|(
name|user_data
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GIMP_GRADIENT_SELECT_BUTTON_GET_PRIVATE
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|select_button
operator|=
name|GIMP_SELECT_BUTTON
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|priv
operator|->
name|gradient_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|priv
operator|->
name|gradient_data
argument_list|)
expr_stmt|;
name|priv
operator|->
name|gradient_name
operator|=
name|g_strdup
argument_list|(
name|gradient_name
argument_list|)
expr_stmt|;
name|priv
operator|->
name|n_samples
operator|=
name|n_samples
expr_stmt|;
name|priv
operator|->
name|gradient_data
operator|=
name|g_memdup
argument_list|(
name|gradient_data
argument_list|,
name|n_samples
operator|*
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|priv
operator|->
name|preview
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog_closing
condition|)
name|select_button
operator|->
name|temp_callback
operator|=
name|NULL
expr_stmt|;
name|g_signal_emit
argument_list|(
name|button
argument_list|,
name|gradient_button_signals
index|[
name|GRADIENT_SET
index|]
argument_list|,
literal|0
argument_list|,
name|gradient_name
argument_list|,
name|n_samples
argument_list|,
name|gradient_data
argument_list|,
name|dialog_closing
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"gradient-name"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_select_button_clicked (GimpGradientSelectButton * button)
name|gimp_gradient_select_button_clicked
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|)
block|{
name|GimpGradientSelectButtonPrivate
modifier|*
name|priv
decl_stmt|;
name|GimpSelectButton
modifier|*
name|select_button
decl_stmt|;
name|priv
operator|=
name|GIMP_GRADIENT_SELECT_BUTTON_GET_PRIVATE
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|select_button
operator|=
name|GIMP_SELECT_BUTTON
argument_list|(
name|button
argument_list|)
expr_stmt|;
if|if
condition|(
name|select_button
operator|->
name|temp_callback
condition|)
block|{
comment|/*  calling gimp_gradients_set_popup() raises the dialog  */
name|gimp_gradients_set_popup
argument_list|(
name|select_button
operator|->
name|temp_callback
argument_list|,
name|priv
operator|->
name|gradient_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|select_button
operator|->
name|temp_callback
operator|=
name|gimp_gradient_select_new
argument_list|(
name|priv
operator|->
name|title
argument_list|,
name|priv
operator|->
name|gradient_name
argument_list|,
name|priv
operator|->
name|sample_size
argument_list|,
name|gimp_gradient_select_button_callback
argument_list|,
name|button
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_select_preview_size_allocate (GtkWidget * widget,GtkAllocation * allocation,GimpGradientSelectButton * button)
name|gimp_gradient_select_preview_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|)
block|{
name|gdouble
modifier|*
name|samples
decl_stmt|;
name|gint
name|n_samples
decl_stmt|;
name|GimpGradientSelectButtonPrivate
modifier|*
name|priv
decl_stmt|;
name|priv
operator|=
name|GIMP_GRADIENT_SELECT_BUTTON_GET_PRIVATE
argument_list|(
name|button
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_gradient_get_uniform_samples
argument_list|(
name|priv
operator|->
name|gradient_name
argument_list|,
name|allocation
operator|->
name|width
argument_list|,
name|priv
operator|->
name|reverse
argument_list|,
operator|&
name|n_samples
argument_list|,
operator|&
name|samples
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|priv
operator|->
name|gradient_data
argument_list|)
expr_stmt|;
name|priv
operator|->
name|sample_size
operator|=
name|allocation
operator|->
name|width
expr_stmt|;
name|priv
operator|->
name|n_samples
operator|=
name|n_samples
expr_stmt|;
name|priv
operator|->
name|gradient_data
operator|=
name|samples
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_select_preview_expose (GtkWidget * widget,GdkEventExpose * event,GimpGradientSelectButton * button)
name|gimp_gradient_select_preview_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|,
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|)
block|{
specifier|const
name|gdouble
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|p0
decl_stmt|;
name|guchar
modifier|*
name|p1
decl_stmt|;
name|guchar
modifier|*
name|even
decl_stmt|;
name|guchar
modifier|*
name|odd
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|GimpGradientSelectButtonPrivate
modifier|*
name|priv
decl_stmt|;
name|priv
operator|=
name|GIMP_GRADIENT_SELECT_BUTTON_GET_PRIVATE
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|src
operator|=
name|priv
operator|->
name|gradient_data
expr_stmt|;
if|if
condition|(
operator|!
name|src
condition|)
return|return;
name|width
operator|=
name|priv
operator|->
name|n_samples
operator|/
literal|4
expr_stmt|;
name|p0
operator|=
name|even
operator|=
name|g_malloc
argument_list|(
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|p1
operator|=
name|odd
operator|=
name|g_malloc
argument_list|(
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
control|)
block|{
name|gdouble
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
name|gdouble
name|c0
decl_stmt|,
name|c1
decl_stmt|;
name|r
operator|=
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|0
index|]
expr_stmt|;
name|g
operator|=
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|1
index|]
expr_stmt|;
name|b
operator|=
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|2
index|]
expr_stmt|;
name|a
operator|=
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|3
index|]
expr_stmt|;
if|if
condition|(
operator|(
name|x
operator|/
name|GIMP_CHECK_SIZE_SM
operator|)
operator|&
literal|1
condition|)
block|{
name|c0
operator|=
name|GIMP_CHECK_LIGHT
expr_stmt|;
name|c1
operator|=
name|GIMP_CHECK_DARK
expr_stmt|;
block|}
else|else
block|{
name|c0
operator|=
name|GIMP_CHECK_DARK
expr_stmt|;
name|c1
operator|=
name|GIMP_CHECK_LIGHT
expr_stmt|;
block|}
operator|*
name|p0
operator|++
operator|=
operator|(
name|c0
operator|+
operator|(
name|r
operator|-
name|c0
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p0
operator|++
operator|=
operator|(
name|c0
operator|+
operator|(
name|g
operator|-
name|c0
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p0
operator|++
operator|=
operator|(
name|c0
operator|+
operator|(
name|b
operator|-
name|c0
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p1
operator|++
operator|=
operator|(
name|c1
operator|+
operator|(
name|r
operator|-
name|c1
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p1
operator|++
operator|=
operator|(
name|c1
operator|+
operator|(
name|g
operator|-
name|c1
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
operator|*
name|p1
operator|++
operator|=
operator|(
name|c1
operator|+
operator|(
name|b
operator|-
name|c1
operator|)
operator|*
name|a
operator|)
operator|*
literal|255.0
expr_stmt|;
block|}
for|for
control|(
name|y
operator|=
name|event
operator|->
name|area
operator|.
name|y
init|;
name|y
operator|<
name|event
operator|->
name|area
operator|.
name|y
operator|+
name|event
operator|->
name|area
operator|.
name|height
condition|;
name|y
operator|++
control|)
block|{
name|GtkStyle
modifier|*
name|style
init|=
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|guchar
modifier|*
name|buf
init|=
operator|(
operator|(
name|y
operator|/
name|GIMP_CHECK_SIZE_SM
operator|)
operator|&
literal|1
operator|)
condition|?
name|odd
else|:
name|even
decl_stmt|;
name|gdk_draw_rgb_image_dithalign
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|style
operator|->
name|fg_gc
index|[
name|widget
operator|->
name|state
index|]
argument_list|,
name|event
operator|->
name|area
operator|.
name|x
argument_list|,
name|y
argument_list|,
name|event
operator|->
name|area
operator|.
name|width
argument_list|,
literal|1
argument_list|,
name|GDK_RGB_DITHER_MAX
argument_list|,
name|buf
operator|+
name|event
operator|->
name|area
operator|.
name|x
operator|*
literal|3
argument_list|,
name|width
operator|*
literal|3
argument_list|,
operator|-
name|event
operator|->
name|area
operator|.
name|x
argument_list|,
operator|-
name|y
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|odd
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|even
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_select_drag_data_received (GimpGradientSelectButton * button,GdkDragContext * context,gint x,gint y,GtkSelectionData * selection,guint info,guint time)
name|gimp_gradient_select_drag_data_received
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
block|{
name|gchar
modifier|*
name|str
decl_stmt|;
if|if
condition|(
operator|(
name|selection
operator|->
name|format
operator|!=
literal|8
operator|)
operator|||
operator|(
name|selection
operator|->
name|length
operator|<
literal|1
operator|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"Received invalid gradient data!"
argument_list|)
expr_stmt|;
return|return;
block|}
name|str
operator|=
name|g_strndup
argument_list|(
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|selection
operator|->
name|data
argument_list|,
name|selection
operator|->
name|length
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_utf8_validate
argument_list|(
name|str
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gint
name|pid
decl_stmt|;
name|gpointer
name|unused
decl_stmt|;
name|gint
name|name_offset
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|sscanf
argument_list|(
name|str
argument_list|,
literal|"%i:%p:%n"
argument_list|,
operator|&
name|pid
argument_list|,
operator|&
name|unused
argument_list|,
operator|&
name|name_offset
argument_list|)
operator|>=
literal|2
operator|&&
name|pid
operator|==
name|gimp_getpid
argument_list|()
operator|&&
name|name_offset
operator|>
literal|0
condition|)
block|{
name|gchar
modifier|*
name|name
init|=
name|str
operator|+
name|name_offset
decl_stmt|;
name|gimp_gradient_select_button_set_gradient
argument_list|(
name|button
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_gradient_select_button_create_inside (GimpGradientSelectButton * gradient_button)
name|gimp_gradient_select_button_create_inside
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|gradient_button
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GimpGradientSelectButtonPrivate
modifier|*
name|priv
decl_stmt|;
name|priv
operator|=
name|GIMP_GRADIENT_SELECT_BUTTON_GET_PRIVATE
argument_list|(
name|gradient_button
argument_list|)
expr_stmt|;
name|gtk_widget_push_composite_child
argument_list|()
expr_stmt|;
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|priv
operator|->
name|preview
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|priv
operator|->
name|preview
argument_list|,
name|CELL_WIDTH
argument_list|,
name|CELL_HEIGHT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|priv
operator|->
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|priv
operator|->
name|preview
argument_list|,
literal|"size-allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gradient_select_preview_size_allocate
argument_list|)
argument_list|,
name|gradient_button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|priv
operator|->
name|preview
argument_list|,
literal|"expose-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gradient_select_preview_expose
argument_list|)
argument_list|,
name|gradient_button
argument_list|)
expr_stmt|;
name|gtk_widget_show_all
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gradient_select_button_clicked
argument_list|)
argument_list|,
name|gradient_button
argument_list|)
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_HIGHLIGHT
operator||
name|GTK_DEST_DEFAULT_MOTION
operator||
name|GTK_DEST_DEFAULT_DROP
argument_list|,
operator|&
name|target
argument_list|,
literal|1
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|button
argument_list|,
literal|"drag-data-received"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gradient_select_drag_data_received
argument_list|)
argument_list|,
name|gradient_button
argument_list|)
expr_stmt|;
name|gtk_widget_pop_composite_child
argument_list|()
expr_stmt|;
return|return
name|button
return|;
block|}
end_function

end_unit

