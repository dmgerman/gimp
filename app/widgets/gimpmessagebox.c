begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmessagebox.c  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpmessagebox.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|GIMP_MESSAGE_BOX_SPACING
define|#
directive|define
name|GIMP_MESSAGE_BOX_SPACING
value|12
end_define

begin_enum
enum|enum
DECL|enum|__anon2bf81e920103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ICON_NAME
name|PROP_ICON_NAME
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_message_box_constructed
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
name|gimp_message_box_dispose
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
name|gimp_message_box_finalize
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
name|gimp_message_box_set_property
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
name|gimp_message_box_get_property
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
name|gimp_message_box_get_preferred_width
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
modifier|*
name|minimum_width
parameter_list|,
name|gint
modifier|*
name|natural_width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_message_box_get_preferred_height
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
modifier|*
name|minimum_height
parameter_list|,
name|gint
modifier|*
name|natural_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_message_box_get_preferred_width_for_height
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
modifier|*
name|minimum_width
parameter_list|,
name|gint
modifier|*
name|natural_width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_message_box_get_preferred_height_for_width
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
modifier|*
name|minimum_height
parameter_list|,
name|gint
modifier|*
name|natural_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_message_box_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_message_box_forall
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|,
name|gboolean
name|include_internals
parameter_list|,
name|GtkCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_message_box_set_label_text
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
parameter_list|,
name|gint
name|n
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|3
operator|,
function_decl|0
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
specifier|static
name|void
name|gimp_message_box_set_label_markup
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
parameter_list|,
name|gint
name|n
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|3
operator|,
function_decl|0
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
specifier|static
name|gboolean
name|gimp_message_box_update
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpMessageBox,gimp_message_box,GTK_TYPE_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpMessageBox
argument_list|,
argument|gimp_message_box
argument_list|,
argument|GTK_TYPE_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_message_box_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_message_box_class_init
parameter_list|(
name|GimpMessageBoxClass
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
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkContainerClass
modifier|*
name|container_class
init|=
name|GTK_CONTAINER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_message_box_constructed
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_message_box_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_message_box_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_message_box_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_message_box_get_property
expr_stmt|;
name|widget_class
operator|->
name|get_preferred_width
operator|=
name|gimp_message_box_get_preferred_width
expr_stmt|;
name|widget_class
operator|->
name|get_preferred_height
operator|=
name|gimp_message_box_get_preferred_height
expr_stmt|;
name|widget_class
operator|->
name|get_preferred_width_for_height
operator|=
name|gimp_message_box_get_preferred_width_for_height
expr_stmt|;
name|widget_class
operator|->
name|get_preferred_height_for_width
operator|=
name|gimp_message_box_get_preferred_height_for_width
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_message_box_size_allocate
expr_stmt|;
name|container_class
operator|->
name|forall
operator|=
name|gimp_message_box_forall
expr_stmt|;
name|gtk_container_class_handle_border_width
argument_list|(
name|container_class
argument_list|)
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
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
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
DECL|function|gimp_message_box_init (GimpMessageBox * box)
name|gimp_message_box_init
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|box
argument_list|)
argument_list|,
name|GTK_ORIENTATION_VERTICAL
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
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|box
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
comment|/*  Unset the focus chain to keep the labels from being in the focus    *  chain.  Users of GimpMessageBox that add focusable widgets should    *  either unset the focus chain or (better) explicitly set one.    */
name|gtk_container_set_focus_chain
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|box
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|2
condition|;
name|i
operator|++
control|)
block|{
name|GtkWidget
modifier|*
name|label
init|=
name|g_object_new
argument_list|(
name|GTK_TYPE_LABEL
argument_list|,
literal|"wrap"
argument_list|,
name|TRUE
argument_list|,
literal|"wrap-mode"
argument_list|,
name|PANGO_WRAP_WORD_CHAR
argument_list|,
literal|"max-width-chars"
argument_list|,
literal|80
argument_list|,
literal|"selectable"
argument_list|,
name|TRUE
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
decl_stmt|;
if|if
condition|(
name|i
operator|==
literal|0
condition|)
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_SCALE
argument_list|,
name|PANGO_SCALE_LARGE
argument_list|,
name|PANGO_ATTR_WEIGHT
argument_list|,
name|PANGO_WEIGHT_BOLD
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
name|box
operator|->
name|label
index|[
name|i
index|]
operator|=
name|label
expr_stmt|;
block|}
name|box
operator|->
name|repeat
operator|=
literal|0
expr_stmt|;
name|box
operator|->
name|label
index|[
literal|2
index|]
operator|=
name|NULL
expr_stmt|;
name|box
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_message_box_constructed (GObject * object)
name|gimp_message_box_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpMessageBox
modifier|*
name|box
init|=
name|GIMP_MESSAGE_BOX
argument_list|(
name|object
argument_list|)
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
if|if
condition|(
name|box
operator|->
name|icon_name
condition|)
block|{
name|box
operator|->
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
name|gtk_widget_set_halign
argument_list|(
name|box
operator|->
name|image
argument_list|,
name|GTK_ALIGN_START
argument_list|)
expr_stmt|;
name|gtk_widget_set_valign
argument_list|(
name|box
operator|->
name|image
argument_list|,
name|GTK_ALIGN_START
argument_list|)
expr_stmt|;
name|gtk_widget_set_parent
argument_list|(
name|box
operator|->
name|image
argument_list|,
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_message_box_dispose (GObject * object)
name|gimp_message_box_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpMessageBox
modifier|*
name|box
init|=
name|GIMP_MESSAGE_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|box
operator|->
name|image
condition|)
block|{
name|gtk_widget_unparent
argument_list|(
name|box
operator|->
name|image
argument_list|)
expr_stmt|;
name|box
operator|->
name|image
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_message_box_finalize (GObject * object)
name|gimp_message_box_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpMessageBox
modifier|*
name|box
init|=
name|GIMP_MESSAGE_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|box
operator|->
name|idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|box
operator|->
name|idle_id
argument_list|)
expr_stmt|;
name|box
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
block|}
name|g_clear_pointer
argument_list|(
operator|&
name|box
operator|->
name|icon_name
argument_list|,
name|g_free
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
DECL|function|gimp_message_box_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_message_box_set_property
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
name|GimpMessageBox
modifier|*
name|box
init|=
name|GIMP_MESSAGE_BOX
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
DECL|function|gimp_message_box_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_message_box_get_property
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
name|GimpMessageBox
modifier|*
name|box
init|=
name|GIMP_MESSAGE_BOX
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
DECL|function|gimp_message_box_get_preferred_width (GtkWidget * widget,gint * minimum_width,gint * natural_width)
name|gimp_message_box_get_preferred_width
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
modifier|*
name|minimum_width
parameter_list|,
name|gint
modifier|*
name|natural_width
parameter_list|)
block|{
name|GimpMessageBox
modifier|*
name|box
init|=
name|GIMP_MESSAGE_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_preferred_width
argument_list|(
name|widget
argument_list|,
name|minimum_width
argument_list|,
name|natural_width
argument_list|)
expr_stmt|;
if|if
condition|(
name|box
operator|->
name|image
operator|&&
name|gtk_widget_get_visible
argument_list|(
name|box
operator|->
name|image
argument_list|)
condition|)
block|{
name|gint
name|image_minimum
decl_stmt|;
name|gint
name|image_natural
decl_stmt|;
name|gtk_widget_get_preferred_width
argument_list|(
name|box
operator|->
name|image
argument_list|,
operator|&
name|image_minimum
argument_list|,
operator|&
name|image_natural
argument_list|)
expr_stmt|;
operator|*
name|minimum_width
operator|+=
name|image_minimum
operator|+
name|GIMP_MESSAGE_BOX_SPACING
expr_stmt|;
operator|*
name|natural_width
operator|+=
name|image_natural
operator|+
name|GIMP_MESSAGE_BOX_SPACING
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_message_box_get_preferred_height (GtkWidget * widget,gint * minimum_height,gint * natural_height)
name|gimp_message_box_get_preferred_height
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
modifier|*
name|minimum_height
parameter_list|,
name|gint
modifier|*
name|natural_height
parameter_list|)
block|{
name|GimpMessageBox
modifier|*
name|box
init|=
name|GIMP_MESSAGE_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_preferred_height
argument_list|(
name|widget
argument_list|,
name|minimum_height
argument_list|,
name|natural_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|box
operator|->
name|image
operator|&&
name|gtk_widget_get_visible
argument_list|(
name|box
operator|->
name|image
argument_list|)
condition|)
block|{
name|gint
name|image_minimum
decl_stmt|;
name|gint
name|image_natural
decl_stmt|;
name|gtk_widget_get_preferred_height
argument_list|(
name|box
operator|->
name|image
argument_list|,
operator|&
name|image_minimum
argument_list|,
operator|&
name|image_natural
argument_list|)
expr_stmt|;
operator|*
name|minimum_height
operator|=
name|MAX
argument_list|(
operator|*
name|minimum_height
argument_list|,
name|image_minimum
argument_list|)
expr_stmt|;
operator|*
name|natural_height
operator|=
name|MAX
argument_list|(
operator|*
name|natural_height
argument_list|,
name|image_natural
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_message_box_get_preferred_width_for_height (GtkWidget * widget,gint height,gint * minimum_width,gint * natural_width)
name|gimp_message_box_get_preferred_width_for_height
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
modifier|*
name|minimum_width
parameter_list|,
name|gint
modifier|*
name|natural_width
parameter_list|)
block|{
name|GTK_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|get_preferred_width
argument_list|(
name|widget
argument_list|,
name|minimum_width
argument_list|,
name|natural_width
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_message_box_get_preferred_height_for_width (GtkWidget * widget,gint width,gint * minimum_height,gint * natural_height)
name|gimp_message_box_get_preferred_height_for_width
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
modifier|*
name|minimum_height
parameter_list|,
name|gint
modifier|*
name|natural_height
parameter_list|)
block|{
name|GTK_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|get_preferred_height
argument_list|(
name|widget
argument_list|,
name|minimum_height
argument_list|,
name|natural_height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_message_box_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gimp_message_box_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
block|{
name|GimpMessageBox
modifier|*
name|box
init|=
name|GIMP_MESSAGE_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|width
init|=
literal|0
decl_stmt|;
name|gboolean
name|rtl
decl_stmt|;
name|rtl
operator|=
operator|(
name|gtk_widget_get_direction
argument_list|(
name|widget
argument_list|)
operator|==
name|GTK_TEXT_DIR_RTL
operator|)
expr_stmt|;
if|if
condition|(
name|box
operator|->
name|image
operator|&&
name|gtk_widget_get_visible
argument_list|(
name|box
operator|->
name|image
argument_list|)
condition|)
block|{
name|GtkRequisition
name|child_requisition
decl_stmt|;
name|GtkAllocation
name|child_allocation
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gtk_widget_get_preferred_size
argument_list|(
name|box
operator|->
name|image
argument_list|,
operator|&
name|child_requisition
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|width
operator|=
name|MIN
argument_list|(
name|allocation
operator|->
name|width
argument_list|,
name|child_requisition
operator|.
name|width
operator|+
name|GIMP_MESSAGE_BOX_SPACING
argument_list|)
expr_stmt|;
name|width
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|height
operator|=
name|allocation
operator|->
name|height
expr_stmt|;
if|if
condition|(
name|rtl
condition|)
name|child_allocation
operator|.
name|x
operator|=
name|allocation
operator|->
name|width
operator|-
name|child_requisition
operator|.
name|width
expr_stmt|;
else|else
name|child_allocation
operator|.
name|x
operator|=
name|allocation
operator|->
name|x
expr_stmt|;
name|child_allocation
operator|.
name|y
operator|=
name|allocation
operator|->
name|y
expr_stmt|;
name|child_allocation
operator|.
name|width
operator|=
name|width
expr_stmt|;
name|child_allocation
operator|.
name|height
operator|=
name|height
expr_stmt|;
name|gtk_widget_size_allocate
argument_list|(
name|box
operator|->
name|image
argument_list|,
operator|&
name|child_allocation
argument_list|)
expr_stmt|;
block|}
name|allocation
operator|->
name|x
operator|+=
name|rtl
condition|?
literal|0
else|:
name|width
expr_stmt|;
name|allocation
operator|->
name|width
operator|-=
name|width
expr_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|size_allocate
argument_list|(
name|widget
argument_list|,
name|allocation
argument_list|)
expr_stmt|;
name|allocation
operator|->
name|x
operator|-=
name|rtl
condition|?
literal|0
else|:
name|width
expr_stmt|;
name|allocation
operator|->
name|width
operator|+=
name|width
expr_stmt|;
name|gtk_widget_set_allocation
argument_list|(
name|widget
argument_list|,
name|allocation
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_message_box_forall (GtkContainer * container,gboolean include_internals,GtkCallback callback,gpointer callback_data)
name|gimp_message_box_forall
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|,
name|gboolean
name|include_internals
parameter_list|,
name|GtkCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
if|if
condition|(
name|include_internals
condition|)
block|{
name|GimpMessageBox
modifier|*
name|box
init|=
name|GIMP_MESSAGE_BOX
argument_list|(
name|container
argument_list|)
decl_stmt|;
if|if
condition|(
name|box
operator|->
name|image
condition|)
call|(
modifier|*
name|callback
call|)
argument_list|(
name|box
operator|->
name|image
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
block|}
name|GTK_CONTAINER_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|forall
argument_list|(
name|container
argument_list|,
name|include_internals
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_message_box_set_label_text (GimpMessageBox * box,gint n,const gchar * format,va_list args)
name|gimp_message_box_set_label_text
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
parameter_list|,
name|gint
name|n
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
init|=
name|box
operator|->
name|label
index|[
name|n
index|]
decl_stmt|;
if|if
condition|(
name|format
condition|)
block|{
name|gchar
modifier|*
name|text
init|=
name|g_strdup_vprintf
argument_list|(
name|format
argument_list|,
name|args
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|utf8
init|=
name|gimp_any_to_utf8
argument_list|(
name|text
argument_list|,
operator|-
literal|1
argument_list|,
literal|"Cannot convert text to utf8."
argument_list|)
decl_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|utf8
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|utf8
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_hide
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_message_box_set_label_markup (GimpMessageBox * box,gint n,const gchar * format,va_list args)
name|gimp_message_box_set_label_markup
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
parameter_list|,
name|gint
name|n
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
init|=
name|box
operator|->
name|label
index|[
name|n
index|]
decl_stmt|;
if|if
condition|(
name|format
condition|)
block|{
name|gchar
modifier|*
name|text
init|=
name|g_markup_vprintf_escaped
argument_list|(
name|format
argument_list|,
name|args
argument_list|)
decl_stmt|;
name|gtk_label_set_markup
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_hide
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_message_box_update (gpointer data)
name|gimp_message_box_update
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpMessageBox
modifier|*
name|box
init|=
name|data
decl_stmt|;
name|gchar
modifier|*
name|message
decl_stmt|;
name|box
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
name|message
operator|=
name|g_strdup_printf
argument_list|(
name|ngettext
argument_list|(
literal|"Message repeated once."
argument_list|,
literal|"Message repeated %d times."
argument_list|,
name|box
operator|->
name|repeat
argument_list|)
argument_list|,
name|box
operator|->
name|repeat
argument_list|)
expr_stmt|;
if|if
condition|(
name|box
operator|->
name|label
index|[
literal|2
index|]
condition|)
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|box
operator|->
name|label
index|[
literal|2
index|]
argument_list|)
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|label
init|=
name|box
operator|->
name|label
index|[
literal|2
index|]
operator|=
name|gtk_label_new
argument_list|(
name|message
argument_list|)
decl_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
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
name|PANGO_STYLE_OBLIQUE
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
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
name|g_free
argument_list|(
name|message
argument_list|)
expr_stmt|;
return|return
name|G_SOURCE_REMOVE
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_message_box_new (const gchar * icon_name)
name|gimp_message_box_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_MESSAGE_BOX
argument_list|,
literal|"icon-name"
argument_list|,
name|icon_name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_message_box_set_primary_text (GimpMessageBox * box,const gchar * format,...)
name|gimp_message_box_set_primary_text
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MESSAGE_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|gimp_message_box_set_label_text
argument_list|(
name|box
argument_list|,
literal|0
argument_list|,
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_message_box_set_text (GimpMessageBox * box,const gchar * format,...)
name|gimp_message_box_set_text
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MESSAGE_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|gimp_message_box_set_label_text
argument_list|(
name|box
argument_list|,
literal|1
argument_list|,
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_message_box_set_markup (GimpMessageBox * box,const gchar * format,...)
name|gimp_message_box_set_markup
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MESSAGE_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|gimp_message_box_set_label_markup
argument_list|(
name|box
argument_list|,
literal|1
argument_list|,
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_message_box_repeat (GimpMessageBox * box)
name|gimp_message_box_repeat
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MESSAGE_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|box
operator|->
name|repeat
operator|++
expr_stmt|;
if|if
condition|(
name|box
operator|->
name|idle_id
operator|==
literal|0
condition|)
block|{
comment|/* When a same message is repeated dozens of thousands of times in        * a short span of time, updating the GUI at each increment is        * extremely slow (like really really slow, your GUI gets stuck        * for 10 minutes). So let's just delay GUI update as a low        * priority idle task.        */
name|box
operator|->
name|idle_id
operator|=
name|g_idle_add_full
argument_list|(
name|G_PRIORITY_LOW
argument_list|,
name|gimp_message_box_update
argument_list|,
name|box
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|box
operator|->
name|repeat
return|;
block|}
end_function

end_unit

