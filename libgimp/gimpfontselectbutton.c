begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpfontselectbutton.c  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"gimpfontselectbutton.h"
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

begin_comment
comment|/**  * SECTION: gimpfontselectbutton  * @title: GimpFontSelectButton  * @short_description: A button which pops up a font selection dialog.  *  * A button which pops up a font selection dialog.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2ad462330103
block|{
DECL|enumerator|FONT_SET
name|FONT_SET
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2ad462330203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TITLE
name|PROP_TITLE
block|,
DECL|enumerator|PROP_FONT_NAME
name|PROP_FONT_NAME
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpFontSelectButtonPrivate
struct|struct
name|_GimpFontSelectButtonPrivate
block|{
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
DECL|member|font_name
name|gchar
modifier|*
name|font_name
decl_stmt|;
comment|/* local copy */
DECL|member|inside
name|GtkWidget
modifier|*
name|inside
decl_stmt|;
DECL|member|label
name|GtkWidget
modifier|*
name|label
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
value|(((GimpFontSelectButton *) (obj))->priv)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_font_select_button_finalize
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
name|gimp_font_select_button_set_property
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
name|gimp_font_select_button_get_property
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
name|gimp_font_select_button_clicked
parameter_list|(
name|GimpFontSelectButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_select_button_callback
parameter_list|(
specifier|const
name|gchar
modifier|*
name|font_name
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
name|gimp_font_select_drag_data_received
parameter_list|(
name|GimpFontSelectButton
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
name|gimp_font_select_button_create_inside
parameter_list|(
name|GimpFontSelectButton
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
literal|"application/x-gimp-font-name"
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|font_button_signals
specifier|static
name|guint
name|font_button_signals
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
DECL|function|G_DEFINE_TYPE (GimpFontSelectButton,gimp_font_select_button,GIMP_TYPE_SELECT_BUTTON)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFontSelectButton
argument_list|,
argument|gimp_font_select_button
argument_list|,
argument|GIMP_TYPE_SELECT_BUTTON
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_font_select_button_class_init
parameter_list|(
name|GimpFontSelectButtonClass
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
name|gimp_font_select_button_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_font_select_button_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_font_select_button_get_property
expr_stmt|;
name|select_button_class
operator|->
name|select_destroy
operator|=
name|gimp_font_select_destroy
expr_stmt|;
name|klass
operator|->
name|font_set
operator|=
name|NULL
expr_stmt|;
comment|/**    * GimpFontSelectButton:title:    *    * The title to be used for the font selection popup dialog.    *    * Since: 2.4    */
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
literal|"The title to be used for the font selection popup dialog"
argument_list|,
name|_
argument_list|(
literal|"Font Selection"
argument_list|)
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
comment|/**    * GimpFontSelectButton:font-name:    *    * The name of the currently selected font.    *    * Since: 2.4    */
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_FONT_NAME
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"font-name"
argument_list|,
literal|"Font name"
argument_list|,
literal|"The name of the currently selected font"
argument_list|,
literal|"Sans-serif"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
comment|/**    * GimpFontSelectButton::font-set:    * @widget: the object which received the signal.    * @font_name: the name of the currently selected font.    * @dialog_closing: whether the dialog was closed or not.    *    * The ::font-set signal is emitted when the user selects a font.    *    * Since: 2.4    */
name|font_button_signals
index|[
name|FONT_SET
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"font-set"
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
name|GimpFontSelectButtonClass
argument_list|,
name|font_set
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_gimpui_marshal_VOID__STRING_BOOLEAN
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_STRING
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
name|GimpFontSelectButtonPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_select_button_init (GimpFontSelectButton * button)
name|gimp_font_select_button_init
parameter_list|(
name|GimpFontSelectButton
modifier|*
name|button
parameter_list|)
block|{
name|GimpFontSelectButtonPrivate
modifier|*
name|priv
decl_stmt|;
name|button
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|button
argument_list|,
name|GIMP_TYPE_FONT_SELECT_BUTTON
argument_list|,
name|GimpFontSelectButtonPrivate
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GET_PRIVATE
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|priv
operator|->
name|font_name
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|inside
operator|=
name|gimp_font_select_button_create_inside
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
comment|/**  * gimp_font_select_button_new:  * @title:     Title of the dialog to use or %NULL to use the default title.  * @font_name: Initial font name.  *  * Creates a new #GtkWidget that completely controls the selection of  * a font.  This widget is suitable for placement in a table in a  * plug-in dialog.  *  * Returns: A #GtkWidget that you can use in your UI.  *  * Since: 2.4  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_font_select_button_new (const gchar * title,const gchar * font_name)
name|gimp_font_select_button_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|font_name
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
name|GIMP_TYPE_FONT_SELECT_BUTTON
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
literal|"font-name"
argument_list|,
name|font_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|button
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_FONT_SELECT_BUTTON
argument_list|,
literal|"font-name"
argument_list|,
name|font_name
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
comment|/**  * gimp_font_select_button_get_font:  * @button: A #GimpFontSelectButton  *  * Retrieves the name of currently selected font.  *  * Returns: an internal copy of the font name which must not be freed.  *  * Since: 2.4  */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_font_select_button_get_font (GimpFontSelectButton * button)
name|gimp_font_select_button_get_font
parameter_list|(
name|GimpFontSelectButton
modifier|*
name|button
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FONT_SELECT_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|button
argument_list|)
operator|->
name|font_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_font_select_button_set_font:  * @button: A #GimpFontSelectButton  * @font_name: Font name to set; %NULL means no change.  *  * Sets the current font for the font select button.  *  * Since: 2.4  */
end_comment

begin_function
name|void
DECL|function|gimp_font_select_button_set_font (GimpFontSelectButton * button,const gchar * font_name)
name|gimp_font_select_button_set_font
parameter_list|(
name|GimpFontSelectButton
modifier|*
name|button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|font_name
parameter_list|)
block|{
name|GimpSelectButton
modifier|*
name|select_button
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FONT_SELECT_BUTTON
argument_list|(
name|button
argument_list|)
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
name|gimp_fonts_set_popup
argument_list|(
name|select_button
operator|->
name|temp_callback
argument_list|,
name|font_name
argument_list|)
expr_stmt|;
else|else
name|gimp_font_select_button_callback
argument_list|(
name|font_name
argument_list|,
name|FALSE
argument_list|,
name|button
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_font_select_button_finalize (GObject * object)
name|gimp_font_select_button_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFontSelectButtonPrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|priv
operator|->
name|font_name
argument_list|)
expr_stmt|;
name|priv
operator|->
name|font_name
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
name|gimp_font_select_button_parent_class
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
DECL|function|gimp_font_select_button_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_font_select_button_set_property
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
name|GimpFontSelectButton
modifier|*
name|button
init|=
name|GIMP_FONT_SELECT_BUTTON
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpFontSelectButtonPrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|button
argument_list|)
decl_stmt|;
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
name|PROP_FONT_NAME
case|:
name|gimp_font_select_button_set_font
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
DECL|function|gimp_font_select_button_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_font_select_button_get_property
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
name|GimpFontSelectButton
modifier|*
name|button
init|=
name|GIMP_FONT_SELECT_BUTTON
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpFontSelectButtonPrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|button
argument_list|)
decl_stmt|;
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
name|PROP_FONT_NAME
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|font_name
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
DECL|function|gimp_font_select_button_callback (const gchar * font_name,gboolean dialog_closing,gpointer user_data)
name|gimp_font_select_button_callback
parameter_list|(
specifier|const
name|gchar
modifier|*
name|font_name
parameter_list|,
name|gboolean
name|dialog_closing
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpFontSelectButton
modifier|*
name|button
init|=
name|GIMP_FONT_SELECT_BUTTON
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|GimpFontSelectButtonPrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|button
argument_list|)
decl_stmt|;
name|GimpSelectButton
modifier|*
name|select_button
init|=
name|GIMP_SELECT_BUTTON
argument_list|(
name|button
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|priv
operator|->
name|font_name
argument_list|)
expr_stmt|;
name|priv
operator|->
name|font_name
operator|=
name|g_strdup
argument_list|(
name|font_name
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|priv
operator|->
name|label
argument_list|)
argument_list|,
name|font_name
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
name|font_button_signals
index|[
name|FONT_SET
index|]
argument_list|,
literal|0
argument_list|,
name|font_name
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
literal|"font-name"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_select_button_clicked (GimpFontSelectButton * button)
name|gimp_font_select_button_clicked
parameter_list|(
name|GimpFontSelectButton
modifier|*
name|button
parameter_list|)
block|{
name|GimpFontSelectButtonPrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|button
argument_list|)
decl_stmt|;
name|GimpSelectButton
modifier|*
name|select_button
init|=
name|GIMP_SELECT_BUTTON
argument_list|(
name|button
argument_list|)
decl_stmt|;
if|if
condition|(
name|select_button
operator|->
name|temp_callback
condition|)
block|{
comment|/*  calling gimp_fonts_set_popup() raises the dialog  */
name|gimp_fonts_set_popup
argument_list|(
name|select_button
operator|->
name|temp_callback
argument_list|,
name|priv
operator|->
name|font_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|select_button
operator|->
name|temp_callback
operator|=
name|gimp_font_select_new
argument_list|(
name|priv
operator|->
name|title
argument_list|,
name|priv
operator|->
name|font_name
argument_list|,
name|gimp_font_select_button_callback
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
DECL|function|gimp_font_select_drag_data_received (GimpFontSelectButton * button,GdkDragContext * context,gint x,gint y,GtkSelectionData * selection,guint info,guint time)
name|gimp_font_select_drag_data_received
parameter_list|(
name|GimpFontSelectButton
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
name|gint
name|length
init|=
name|gtk_selection_data_get_length
argument_list|(
name|selection
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
if|if
condition|(
name|gtk_selection_data_get_format
argument_list|(
name|selection
argument_list|)
operator|!=
literal|8
operator|||
name|length
operator|<
literal|1
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: received invalid font data"
argument_list|,
name|G_STRFUNC
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
name|gtk_selection_data_get_data
argument_list|(
name|selection
argument_list|)
argument_list|,
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
name|gimp_font_select_button_set_font
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
DECL|function|gimp_font_select_button_create_inside (GimpFontSelectButton * font_button)
name|gimp_font_select_button_create_inside
parameter_list|(
name|GimpFontSelectButton
modifier|*
name|font_button
parameter_list|)
block|{
name|GimpFontSelectButtonPrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|font_button
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|GIMP_ICON_FONT
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
name|priv
operator|->
name|label
operator|=
name|gtk_label_new
argument_list|(
name|priv
operator|->
name|font_name
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|priv
operator|->
name|label
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|4
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
name|gimp_font_select_button_clicked
argument_list|)
argument_list|,
name|font_button
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
name|gimp_font_select_drag_data_received
argument_list|)
argument_list|,
name|font_button
argument_list|)
expr_stmt|;
return|return
name|button
return|;
block|}
end_function

end_unit

