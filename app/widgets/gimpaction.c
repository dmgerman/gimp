begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpaction.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
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
file|"config/gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpaction.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b3d52830103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_COLOR
name|PROP_COLOR
block|,
DECL|enumerator|PROP_VIEWABLE
name|PROP_VIEWABLE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_action_init
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_action_class_init
parameter_list|(
name|GimpActionClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_action_finalize
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
name|gimp_action_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|gimp_action_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|gimp_action_connect_proxy
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GtkWidget
modifier|*
name|proxy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_action_set_proxy
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GtkWidget
modifier|*
name|proxy
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkActionClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_action_get_type (void)
name|gimp_action_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|type_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpActionClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_action_class_init
block|,
operator|(
name|GClassFinalizeFunc
operator|)
name|NULL
block|,
name|NULL
block|,
sizeof|sizeof
argument_list|(
name|GimpAction
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_action_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_ACTION
argument_list|,
literal|"GimpAction"
argument_list|,
operator|&
name|type_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_action_class_init (GimpActionClass * klass)
name|gimp_action_class_init
parameter_list|(
name|GimpActionClass
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
name|GtkActionClass
modifier|*
name|action_class
init|=
name|GTK_ACTION_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpRGB
name|black
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
name|finalize
operator|=
name|gimp_action_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_action_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_action_get_property
expr_stmt|;
name|action_class
operator|->
name|connect_proxy
operator|=
name|gimp_action_connect_proxy
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|black
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_COLOR
argument_list|,
name|gimp_param_spec_rgb
argument_list|(
literal|"color"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|black
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
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
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_action_init (GimpAction * action)
name|gimp_action_init
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|)
block|{
name|action
operator|->
name|color
operator|=
name|NULL
expr_stmt|;
name|action
operator|->
name|viewable
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_action_finalize (GObject * object)
name|gimp_action_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpAction
modifier|*
name|action
init|=
name|GIMP_ACTION
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|action
operator|->
name|color
condition|)
block|{
name|g_free
argument_list|(
name|action
operator|->
name|color
argument_list|)
expr_stmt|;
name|action
operator|->
name|color
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|action
operator|->
name|viewable
condition|)
block|{
name|g_object_unref
argument_list|(
name|action
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|action
operator|->
name|viewable
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
DECL|function|gimp_action_get_property (GObject * object,guint prop_id,GValue * value,GParamSpec * pspec)
name|gimp_action_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|GimpAction
modifier|*
name|action
init|=
name|GIMP_ACTION
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|prop_id
condition|)
block|{
case|case
name|PROP_COLOR
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
name|action
operator|->
name|color
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VIEWABLE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|action
operator|->
name|viewable
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|prop_id
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
DECL|function|gimp_action_set_property (GObject * object,guint prop_id,const GValue * value,GParamSpec * pspec)
name|gimp_action_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|GimpAction
modifier|*
name|action
init|=
name|GIMP_ACTION
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gboolean
name|set_proxy
init|=
name|FALSE
decl_stmt|;
switch|switch
condition|(
name|prop_id
condition|)
block|{
case|case
name|PROP_COLOR
case|:
if|if
condition|(
name|action
operator|->
name|color
condition|)
name|g_free
argument_list|(
name|action
operator|->
name|color
argument_list|)
expr_stmt|;
name|action
operator|->
name|color
operator|=
name|g_value_dup_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|set_proxy
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|PROP_VIEWABLE
case|:
if|if
condition|(
name|action
operator|->
name|viewable
condition|)
name|g_object_unref
argument_list|(
name|action
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|action
operator|->
name|viewable
operator|=
operator|(
name|GimpViewable
operator|*
operator|)
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|set_proxy
operator|=
name|TRUE
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|prop_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|set_proxy
condition|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gtk_action_get_proxies
argument_list|(
name|GTK_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|gimp_action_set_proxy
argument_list|(
name|action
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_action_connect_proxy (GtkAction * action,GtkWidget * proxy)
name|gimp_action_connect_proxy
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GtkWidget
modifier|*
name|proxy
parameter_list|)
block|{
name|GTK_ACTION_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|connect_proxy
argument_list|(
name|action
argument_list|,
name|proxy
argument_list|)
expr_stmt|;
name|gimp_action_set_proxy
argument_list|(
name|GIMP_ACTION
argument_list|(
name|action
argument_list|)
argument_list|,
name|proxy
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpAction
modifier|*
DECL|function|gimp_action_new (const gchar * name,const gchar * label,const gchar * tooltip,const gchar * stock_id)
name|gimp_action_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_ACTION
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
literal|"label"
argument_list|,
name|label
argument_list|,
literal|"tooltip"
argument_list|,
name|tooltip
argument_list|,
literal|"stock_id"
argument_list|,
name|stock_id
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_action_name_compare (GimpAction * action1,GimpAction * action2)
name|gimp_action_name_compare
parameter_list|(
name|GimpAction
modifier|*
name|action1
parameter_list|,
name|GimpAction
modifier|*
name|action2
parameter_list|)
block|{
return|return
name|strcmp
argument_list|(
name|gtk_action_get_name
argument_list|(
operator|(
name|GtkAction
operator|*
operator|)
name|action1
argument_list|)
argument_list|,
name|gtk_action_get_name
argument_list|(
operator|(
name|GtkAction
operator|*
operator|)
name|action2
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_action_set_proxy (GimpAction * action,GtkWidget * proxy)
name|gimp_action_set_proxy
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|GtkWidget
modifier|*
name|proxy
parameter_list|)
block|{
if|if
condition|(
operator|!
name|GTK_IS_IMAGE_MENU_ITEM
argument_list|(
name|proxy
argument_list|)
condition|)
return|return;
if|if
condition|(
name|action
operator|->
name|color
condition|)
block|{
name|GtkWidget
modifier|*
name|area
decl_stmt|;
name|area
operator|=
name|gtk_image_menu_item_get_image
argument_list|(
name|GTK_IMAGE_MENU_ITEM
argument_list|(
name|proxy
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|area
operator|&&
operator|!
name|GIMP_IS_COLOR_AREA
argument_list|(
name|area
argument_list|)
condition|)
block|{
name|gtk_image_menu_item_set_image
argument_list|(
name|GTK_IMAGE_MENU_ITEM
argument_list|(
name|proxy
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|area
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|area
condition|)
block|{
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|GtkSettings
modifier|*
name|settings
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|area
operator|=
name|gimp_color_area_new
argument_list|(
name|action
operator|->
name|color
argument_list|,
name|GIMP_COLOR_AREA_SMALL_CHECKS
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_color_area_set_draw_border
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|area
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|area
argument_list|)
expr_stmt|;
name|settings
operator|=
name|gtk_settings_get_for_screen
argument_list|(
name|screen
argument_list|)
expr_stmt|;
name|gtk_icon_size_lookup_for_settings
argument_list|(
name|settings
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|area
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gtk_image_menu_item_set_image
argument_list|(
name|GTK_IMAGE_MENU_ITEM
argument_list|(
name|proxy
argument_list|)
argument_list|,
name|area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|area
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_color_area_set_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|area
argument_list|)
argument_list|,
name|action
operator|->
name|color
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|action
operator|->
name|viewable
condition|)
block|{
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|preview
operator|=
name|gtk_image_menu_item_get_image
argument_list|(
name|GTK_IMAGE_MENU_ITEM
argument_list|(
name|proxy
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview
operator|&&
operator|!
name|GIMP_IS_PREVIEW
argument_list|(
name|preview
argument_list|)
condition|)
block|{
name|gtk_image_menu_item_set_image
argument_list|(
name|GTK_IMAGE_MENU_ITEM
argument_list|(
name|proxy
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|preview
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|preview
condition|)
block|{
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|proxy
argument_list|)
expr_stmt|;
name|gtk_icon_size_lookup_for_settings
argument_list|(
name|gtk_settings_get_for_screen
argument_list|(
name|screen
argument_list|)
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_preview_new_full
argument_list|(
name|action
operator|->
name|viewable
argument_list|,
name|width
operator|-
literal|2
argument_list|,
name|height
operator|-
literal|2
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_image_menu_item_set_image
argument_list|(
name|GTK_IMAGE_MENU_ITEM
argument_list|(
name|proxy
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_preview_set_viewable
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|action
operator|->
name|viewable
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|image
operator|=
name|gtk_image_menu_item_get_image
argument_list|(
name|GTK_IMAGE_MENU_ITEM
argument_list|(
name|proxy
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|&&
operator|(
name|GIMP_IS_PREVIEW
argument_list|(
name|image
argument_list|)
operator|||
name|GIMP_IS_COLOR_AREA
argument_list|(
name|image
argument_list|)
operator|)
condition|)
block|{
name|gtk_image_menu_item_set_image
argument_list|(
name|GTK_IMAGE_MENU_ITEM
argument_list|(
name|proxy
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"stock-id"
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

