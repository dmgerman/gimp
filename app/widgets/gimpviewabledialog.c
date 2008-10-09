begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewabledialog.c  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon27aa1ee10103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_VIEWABLE
name|PROP_VIEWABLE
block|,
DECL|enumerator|PROP_CONTEXT
name|PROP_CONTEXT
block|,
DECL|enumerator|PROP_STOCK_ID
name|PROP_STOCK_ID
block|,
DECL|enumerator|PROP_DESC
name|PROP_DESC
block|,
DECL|enumerator|PROP_PARENT
name|PROP_PARENT
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_viewable_dialog_set_property
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
name|gimp_viewable_dialog_get_property
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
name|gimp_viewable_dialog_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_viewable_dialog_name_changed
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|GimpViewableDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_viewable_dialog_close
parameter_list|(
name|GimpViewableDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpViewableDialog,gimp_viewable_dialog,GIMP_TYPE_DIALOG)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpViewableDialog
argument_list|,
argument|gimp_viewable_dialog
argument_list|,
argument|GIMP_TYPE_DIALOG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_viewable_dialog_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_viewable_dialog_class_init
parameter_list|(
name|GimpViewableDialogClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|gtk_object_class
init|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|gtk_object_class
operator|->
name|destroy
operator|=
name|gimp_viewable_dialog_destroy
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_viewable_dialog_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_viewable_dialog_set_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_VIEWABLE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"viewable"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_VIEWABLE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTEXT
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"context"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CONTEXT
argument_list|,
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
name|NULL
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_DESC
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"description"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PARENT
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"parent"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_TYPE_WIDGET
argument_list|,
name|GIMP_PARAM_WRITABLE
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
DECL|function|gimp_viewable_dialog_init (GimpViewableDialog * dialog)
name|gimp_viewable_dialog_init
parameter_list|(
name|GimpViewableDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
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
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
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
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|icon
operator|=
name|gtk_image_new
argument_list|()
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|dialog
operator|->
name|icon
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|dialog
operator|->
name|icon
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
name|dialog
operator|->
name|icon
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
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
name|hbox
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|desc_label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|dialog
operator|->
name|desc_label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|dialog
operator|->
name|desc_label
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
name|vbox
argument_list|)
argument_list|,
name|dialog
operator|->
name|desc_label
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
name|dialog
operator|->
name|desc_label
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|viewable_label
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_LABEL
argument_list|,
literal|"xalign"
argument_list|,
literal|0.0
argument_list|,
literal|"yalign"
argument_list|,
literal|0.5
argument_list|,
literal|"ellipsize"
argument_list|,
name|PANGO_ELLIPSIZE_END
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|dialog
operator|->
name|viewable_label
argument_list|)
argument_list|,
name|PANGO_ATTR_SCALE
argument_list|,
name|PANGO_SCALE_SMALL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|dialog
operator|->
name|viewable_label
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
name|dialog
operator|->
name|viewable_label
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_viewable_dialog_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_viewable_dialog_set_property
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
name|GimpViewableDialog
modifier|*
name|dialog
init|=
name|GIMP_VIEWABLE_DIALOG
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
name|PROP_VIEWABLE
case|:
name|gimp_viewable_dialog_set_viewable
argument_list|(
name|dialog
argument_list|,
name|g_value_get_object
argument_list|(
name|value
argument_list|)
argument_list|,
name|dialog
operator|->
name|context
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTEXT
case|:
name|gimp_viewable_dialog_set_viewable
argument_list|(
name|dialog
argument_list|,
name|dialog
operator|->
name|view
condition|?
name|GIMP_VIEW
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
operator|->
name|viewable
else|:
name|NULL
argument_list|,
name|g_value_get_object
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STOCK_ID
case|:
name|gtk_image_set_from_stock
argument_list|(
name|GTK_IMAGE
argument_list|(
name|dialog
operator|->
name|icon
argument_list|)
argument_list|,
name|g_value_get_string
argument_list|(
name|value
argument_list|)
argument_list|,
name|GTK_ICON_SIZE_LARGE_TOOLBAR
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DESC
case|:
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|dialog
operator|->
name|desc_label
argument_list|)
argument_list|,
name|g_value_get_string
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PARENT
case|:
block|{
name|GtkWidget
modifier|*
name|parent
init|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|parent
condition|)
block|{
if|if
condition|(
name|GTK_IS_WINDOW
argument_list|(
name|parent
argument_list|)
condition|)
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
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
DECL|function|gimp_viewable_dialog_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_viewable_dialog_get_property
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
name|GimpViewableDialog
modifier|*
name|dialog
init|=
name|GIMP_VIEWABLE_DIALOG
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
name|PROP_VIEWABLE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|dialog
operator|->
name|view
condition|?
name|GIMP_VIEW
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
operator|->
name|viewable
else|:
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONTEXT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|dialog
operator|->
name|context
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
DECL|function|gimp_viewable_dialog_destroy (GtkObject * object)
name|gimp_viewable_dialog_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpViewableDialog
modifier|*
name|dialog
init|=
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|dialog
operator|->
name|view
condition|)
name|gimp_viewable_dialog_set_viewable
argument_list|(
name|dialog
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_viewable_dialog_new (GimpViewable * viewable,GimpContext * context,const gchar * title,const gchar * role,const gchar * stock_id,const gchar * desc,GtkWidget * parent,GimpHelpFunc help_func,const gchar * help_id,...)
name|gimp_viewable_dialog_new
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GimpViewableDialog
modifier|*
name|dialog
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|viewable
operator|==
name|NULL
operator|||
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|role
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parent
operator|==
name|NULL
operator|||
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|viewable
condition|)
name|g_warning
argument_list|(
literal|"Use of GimpViewableDialog with a NULL viewable is depecrated!"
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_VIEWABLE_DIALOG
argument_list|,
literal|"viewable"
argument_list|,
name|viewable
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
literal|"role"
argument_list|,
name|role
argument_list|,
literal|"help-func"
argument_list|,
name|help_func
argument_list|,
literal|"help-id"
argument_list|,
name|help_id
argument_list|,
literal|"stock-id"
argument_list|,
name|stock_id
argument_list|,
literal|"description"
argument_list|,
name|desc
argument_list|,
literal|"parent"
argument_list|,
name|parent
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
name|gimp_dialog_add_buttons_valist
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_viewable_dialog_set_viewable (GimpViewableDialog * dialog,GimpViewable * viewable,GimpContext * context)
name|gimp_viewable_dialog_set_viewable
parameter_list|(
name|GimpViewableDialog
modifier|*
name|dialog
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|viewable
operator|==
name|NULL
operator|||
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|context
operator|=
name|context
expr_stmt|;
if|if
condition|(
name|dialog
operator|->
name|view
condition|)
block|{
name|GimpViewable
modifier|*
name|old_viewable
init|=
name|GIMP_VIEW
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
operator|->
name|viewable
decl_stmt|;
if|if
condition|(
name|viewable
operator|==
name|old_viewable
condition|)
block|{
name|gimp_view_renderer_set_context
argument_list|(
name|GIMP_VIEW
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
operator|->
name|renderer
argument_list|,
name|context
argument_list|)
expr_stmt|;
return|return;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_viewable
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|old_viewable
argument_list|,
name|gimp_viewable_dialog_name_changed
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|old_viewable
argument_list|,
name|gimp_viewable_dialog_close
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|viewable
condition|)
block|{
name|GtkWidget
modifier|*
name|box
decl_stmt|;
name|g_signal_connect_object
argument_list|(
name|viewable
argument_list|,
name|GIMP_VIEWABLE_GET_CLASS
argument_list|(
name|viewable
argument_list|)
operator|->
name|name_changed_signal
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_viewable_dialog_name_changed
argument_list|)
argument_list|,
name|dialog
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|box
operator|=
name|gtk_widget_get_parent
argument_list|(
name|dialog
operator|->
name|icon
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|view
operator|=
name|gimp_view_new
argument_list|(
name|context
argument_list|,
name|viewable
argument_list|,
literal|32
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|dialog
operator|->
name|view
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|dialog
operator|->
name|view
argument_list|)
expr_stmt|;
name|gimp_viewable_dialog_name_changed
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_ITEM
argument_list|(
name|viewable
argument_list|)
condition|)
block|{
name|g_signal_connect_object
argument_list|(
name|viewable
argument_list|,
literal|"removed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_viewable_dialog_close
argument_list|)
argument_list|,
name|dialog
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_signal_connect_object
argument_list|(
name|viewable
argument_list|,
literal|"disconnect"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_viewable_dialog_close
argument_list|)
argument_list|,
name|dialog
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_viewable_dialog_name_changed (GimpObject * object,GimpViewableDialog * dialog)
name|gimp_viewable_dialog_name_changed
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|GimpViewableDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|name
operator|=
name|gimp_viewable_get_description
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|object
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_ITEM
argument_list|(
name|object
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|tmp
decl_stmt|;
name|uri
operator|=
name|gimp_image_get_uri
argument_list|(
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|object
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|name
expr_stmt|;
name|basename
operator|=
name|file_utils_uri_display_basename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-%d (%s)"
argument_list|,
name|tmp
argument_list|,
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
argument_list|(
name|object
argument_list|)
argument_list|)
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|dialog
operator|->
name|viewable_label
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_viewable_dialog_close (GimpViewableDialog * dialog)
name|gimp_viewable_dialog_close
parameter_list|(
name|GimpViewableDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|g_signal_emit_by_name
argument_list|(
name|dialog
argument_list|,
literal|"close"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

