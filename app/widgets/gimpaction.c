begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpaction.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimagefile.h"
end_include

begin_comment
comment|/* eek */
end_comment

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
file|"gimpaction-history.h"
end_include

begin_include
include|#
directive|include
file|"gimpview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29b3f1510103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONTEXT
name|PROP_CONTEXT
block|,
DECL|enumerator|PROP_COLOR
name|PROP_COLOR
block|,
DECL|enumerator|PROP_VIEWABLE
name|PROP_VIEWABLE
block|,
DECL|enumerator|PROP_ELLIPSIZE
name|PROP_ELLIPSIZE
block|,
DECL|enumerator|PROP_MAX_WIDTH_CHARS
name|PROP_MAX_WIDTH_CHARS
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_action_constructed
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

begin_function_decl
specifier|static
name|void
name|gimp_action_set_proxy_tooltip
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

begin_function_decl
specifier|static
name|void
name|gimp_action_tooltip_notify
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpAction,gimp_action,GTK_TYPE_ACTION)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpAction
argument_list|,
argument|gimp_action
argument_list|,
argument|GTK_TYPE_ACTION
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_action_parent_class
end_define

begin_function
specifier|static
name|void
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
name|object_class
operator|->
name|constructed
operator|=
name|gimp_action_constructed
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
name|TRUE
argument_list|,
operator|&
name|black
argument_list|,
name|GIMP_PARAM_READWRITE
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
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ELLIPSIZE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"ellipsize"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|PANGO_TYPE_ELLIPSIZE_MODE
argument_list|,
name|PANGO_ELLIPSIZE_NONE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_MAX_WIDTH_CHARS
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"max-width-chars"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1
argument_list|,
name|G_MAXINT
argument_list|,
operator|-
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
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
name|action
operator|->
name|ellipsize
operator|=
name|PANGO_ELLIPSIZE_NONE
expr_stmt|;
name|action
operator|->
name|max_width_chars
operator|=
operator|-
literal|1
expr_stmt|;
name|g_signal_connect
argument_list|(
name|action
argument_list|,
literal|"notify::tooltip"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_action_tooltip_notify
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_action_constructed (GObject * object)
name|gimp_action_constructed
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
name|g_signal_connect
argument_list|(
name|action
argument_list|,
literal|"activate"
argument_list|,
operator|(
name|GCallback
operator|)
name|gimp_action_history_activate_callback
argument_list|,
name|NULL
argument_list|)
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
name|context
condition|)
block|{
name|g_object_unref
argument_list|(
name|action
operator|->
name|context
argument_list|)
expr_stmt|;
name|action
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
block|}
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
name|PROP_CONTEXT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|action
operator|->
name|context
argument_list|)
expr_stmt|;
break|break;
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
case|case
name|PROP_ELLIPSIZE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|action
operator|->
name|ellipsize
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MAX_WIDTH_CHARS
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|action
operator|->
name|max_width_chars
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
name|PROP_CONTEXT
case|:
if|if
condition|(
name|action
operator|->
name|context
condition|)
name|g_object_unref
argument_list|(
name|action
operator|->
name|context
argument_list|)
expr_stmt|;
name|action
operator|->
name|context
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
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
case|case
name|PROP_ELLIPSIZE
case|:
name|action
operator|->
name|ellipsize
operator|=
name|g_value_get_enum
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
name|PROP_MAX_WIDTH_CHARS
case|:
name|action
operator|->
name|max_width_chars
operator|=
name|g_value_get_int
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
name|gimp_action_set_proxy_tooltip
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
DECL|function|gimp_action_new (const gchar * name,const gchar * label,const gchar * tooltip,const gchar * icon_name)
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
name|icon_name
parameter_list|)
block|{
name|GimpAction
modifier|*
name|action
decl_stmt|;
name|action
operator|=
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
literal|"icon-name"
argument_list|,
name|icon_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|action
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

begin_function
name|gboolean
DECL|function|gimp_action_is_gui_blacklisted (const gchar * action_name)
name|gimp_action_is_gui_blacklisted
parameter_list|(
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|)
block|{
specifier|static
specifier|const
name|gchar
modifier|*
name|suffixes
index|[]
init|=
block|{
literal|"-menu"
block|,
literal|"-popup"
block|}
decl_stmt|;
specifier|static
specifier|const
name|gchar
modifier|*
name|prefixes
index|[]
init|=
block|{
literal|"<"
block|,
literal|"tools-color-average-radius-"
block|,
literal|"tools-paintbrush-size-"
block|,
literal|"tools-paintbrush-aspect-ratio-"
block|,
literal|"tools-paintbrush-angle-"
block|,
literal|"tools-paintbrush-spacing-"
block|,
literal|"tools-paintbrush-hardness-"
block|,
literal|"tools-paintbrush-force-"
block|,
literal|"tools-ink-blob-size-"
block|,
literal|"tools-ink-blob-aspect-"
block|,
literal|"tools-ink-blob-angle-"
block|,
literal|"tools-mypaint-brush-radius-"
block|,
literal|"tools-mypaint-brush-hardness-"
block|,
literal|"tools-foreground-select-brush-size-"
block|,
literal|"tools-transform-preview-opacity-"
block|,
literal|"tools-warp-effect-size-"
literal|"tools-warp-effect-hardness-"
block|}
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|action_name
operator|&&
operator|*
name|action_name
operator|)
condition|)
return|return
name|TRUE
return|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|suffixes
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|g_str_has_suffix
argument_list|(
name|action_name
argument_list|,
name|suffixes
index|[
name|i
index|]
argument_list|)
condition|)
return|return
name|TRUE
return|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|prefixes
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|action_name
argument_list|,
name|prefixes
index|[
name|i
index|]
argument_list|)
condition|)
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
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
name|GIMP_IS_COLOR_AREA
argument_list|(
name|area
argument_list|)
condition|)
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
else|else
block|{
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
if|if
condition|(
name|action
operator|->
name|context
condition|)
name|gimp_color_area_set_color_config
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|area
argument_list|)
argument_list|,
name|action
operator|->
name|context
operator|->
name|gimp
operator|->
name|config
operator|->
name|color_management
argument_list|)
expr_stmt|;
name|gtk_icon_size_lookup_for_settings
argument_list|(
name|gtk_widget_get_settings
argument_list|(
name|proxy
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
name|view
decl_stmt|;
name|view
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
name|GIMP_IS_VIEW
argument_list|(
name|view
argument_list|)
operator|&&
name|g_type_is_a
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|action
operator|->
name|viewable
argument_list|)
argument_list|,
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|renderer
operator|->
name|viewable_type
argument_list|)
condition|)
block|{
name|gimp_view_set_viewable
argument_list|(
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|action
operator|->
name|viewable
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkIconSize
name|size
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|border_width
decl_stmt|;
if|if
condition|(
name|GIMP_IS_IMAGEFILE
argument_list|(
name|action
operator|->
name|viewable
argument_list|)
condition|)
block|{
name|size
operator|=
name|GTK_ICON_SIZE_LARGE_TOOLBAR
expr_stmt|;
name|border_width
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|size
operator|=
name|GTK_ICON_SIZE_MENU
expr_stmt|;
name|border_width
operator|=
literal|1
expr_stmt|;
block|}
name|gtk_icon_size_lookup_for_settings
argument_list|(
name|gtk_widget_get_settings
argument_list|(
name|proxy
argument_list|)
argument_list|,
name|size
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|view
operator|=
name|gimp_view_new_full
argument_list|(
name|action
operator|->
name|context
argument_list|,
name|action
operator|->
name|viewable
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|border_width
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
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
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
name|GIMP_IS_VIEW
argument_list|(
name|image
argument_list|)
operator|||
name|GIMP_IS_COLOR_AREA
argument_list|(
name|image
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
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|action
argument_list|)
argument_list|,
literal|"icon-name"
argument_list|)
expr_stmt|;
block|}
block|}
block|{
name|GtkWidget
modifier|*
name|child
init|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|proxy
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_IS_LABEL
argument_list|(
name|child
argument_list|)
condition|)
block|{
name|GtkLabel
modifier|*
name|label
init|=
name|GTK_LABEL
argument_list|(
name|child
argument_list|)
decl_stmt|;
name|gtk_label_set_ellipsize
argument_list|(
name|label
argument_list|,
name|action
operator|->
name|ellipsize
argument_list|)
expr_stmt|;
name|gtk_label_set_max_width_chars
argument_list|(
name|label
argument_list|,
name|action
operator|->
name|max_width_chars
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_action_set_proxy_tooltip (GimpAction * action,GtkWidget * proxy)
name|gimp_action_set_proxy_tooltip
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
specifier|const
name|gchar
modifier|*
name|tooltip
init|=
name|gtk_action_get_tooltip
argument_list|(
name|GTK_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|tooltip
condition|)
name|gimp_help_set_help_data
argument_list|(
name|proxy
argument_list|,
name|tooltip
argument_list|,
name|g_object_get_qdata
argument_list|(
name|G_OBJECT
argument_list|(
name|proxy
argument_list|)
argument_list|,
name|GIMP_HELP_ID
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_action_tooltip_notify (GimpAction * action,const GParamSpec * pspec,gpointer data)
name|gimp_action_tooltip_notify
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|gpointer
name|data
parameter_list|)
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
name|gimp_action_set_proxy_tooltip
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
end_function

end_unit

