begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockable.c  * Copyright (C) 2001-2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockbook.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockwindow.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimppanedbox.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo-aux.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessionmanaged.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2abfa70b0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_LOCKED
name|PROP_LOCKED
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpDockablePrivate
struct|struct
name|_GimpDockablePrivate
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|blurb
name|gchar
modifier|*
name|blurb
decl_stmt|;
DECL|member|icon_name
name|gchar
modifier|*
name|icon_name
decl_stmt|;
DECL|member|help_id
name|gchar
modifier|*
name|help_id
decl_stmt|;
DECL|member|tab_style
name|GimpTabStyle
name|tab_style
decl_stmt|;
DECL|member|locked
name|gboolean
name|locked
decl_stmt|;
DECL|member|dockbook
name|GimpDockbook
modifier|*
name|dockbook
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_dockable_session_managed_iface_init
parameter_list|(
name|GimpSessionManagedInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockable_dispose
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
name|gimp_dockable_set_property
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
name|gimp_dockable_get_property
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
name|gimp_dockable_style_updated
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockable_add
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GType
name|gimp_dockable_child_type
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GList
modifier|*
name|gimp_dockable_get_aux_info
parameter_list|(
name|GimpSessionManaged
modifier|*
name|managed
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockable_set_aux_info
parameter_list|(
name|GimpSessionManaged
modifier|*
name|managed
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpDockable
argument_list|,
argument|gimp_dockable
argument_list|,
argument|GTK_TYPE_BIN
argument_list|,
argument|G_ADD_PRIVATE (GimpDockable)                          G_IMPLEMENT_INTERFACE (GIMP_TYPE_SESSION_MANAGED,                                                 gimp_dockable_session_managed_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dockable_parent_class
end_define

begin_decl_stmt
specifier|static
specifier|const
name|GtkTargetEntry
name|dialog_target_table
index|[]
init|=
block|{
name|GIMP_TARGET_NOTEBOOK_TAB
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_class_init (GimpDockableClass * klass)
name|gimp_dockable_class_init
parameter_list|(
name|GimpDockableClass
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
name|dispose
operator|=
name|gimp_dockable_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_dockable_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_dockable_get_property
expr_stmt|;
name|widget_class
operator|->
name|style_updated
operator|=
name|gimp_dockable_style_updated
expr_stmt|;
name|container_class
operator|->
name|add
operator|=
name|gimp_dockable_add
expr_stmt|;
name|container_class
operator|->
name|child_type
operator|=
name|gimp_dockable_child_type
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
name|PROP_LOCKED
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"locked"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"content-border"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_init (GimpDockable * dockable)
name|gimp_dockable_init
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|dockable
operator|->
name|p
operator|=
name|gimp_dockable_get_instance_private
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|p
operator|->
name|tab_style
operator|=
name|GIMP_TAB_STYLE_PREVIEW
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|,
literal|0
argument_list|,
name|dialog_target_table
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dialog_target_table
argument_list|)
argument_list|,
name|GDK_ACTION_MOVE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_session_managed_iface_init (GimpSessionManagedInterface * iface)
name|gimp_dockable_session_managed_iface_init
parameter_list|(
name|GimpSessionManagedInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|get_aux_info
operator|=
name|gimp_dockable_get_aux_info
expr_stmt|;
name|iface
operator|->
name|set_aux_info
operator|=
name|gimp_dockable_set_aux_info
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_dispose (GObject * object)
name|gimp_dockable_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
init|=
name|GIMP_DOCKABLE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|dockable
operator|->
name|p
operator|->
name|context
condition|)
name|gimp_dockable_set_context
argument_list|(
name|dockable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
operator|->
name|p
operator|->
name|blurb
condition|)
block|{
if|if
condition|(
name|dockable
operator|->
name|p
operator|->
name|blurb
operator|!=
name|dockable
operator|->
name|p
operator|->
name|name
condition|)
name|g_free
argument_list|(
name|dockable
operator|->
name|p
operator|->
name|blurb
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|p
operator|->
name|blurb
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|dockable
operator|->
name|p
operator|->
name|name
condition|)
block|{
name|g_free
argument_list|(
name|dockable
operator|->
name|p
operator|->
name|name
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|p
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|dockable
operator|->
name|p
operator|->
name|icon_name
condition|)
block|{
name|g_free
argument_list|(
name|dockable
operator|->
name|p
operator|->
name|icon_name
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|p
operator|->
name|icon_name
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|dockable
operator|->
name|p
operator|->
name|help_id
condition|)
block|{
name|g_free
argument_list|(
name|dockable
operator|->
name|p
operator|->
name|help_id
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|p
operator|->
name|help_id
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
DECL|function|gimp_dockable_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_dockable_set_property
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
name|GimpDockable
modifier|*
name|dockable
init|=
name|GIMP_DOCKABLE
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
name|PROP_LOCKED
case|:
name|gimp_dockable_set_locked
argument_list|(
name|dockable
argument_list|,
name|g_value_get_boolean
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
DECL|function|gimp_dockable_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_dockable_get_property
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
name|GimpDockable
modifier|*
name|dockable
init|=
name|GIMP_DOCKABLE
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
name|PROP_LOCKED
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|dockable
operator|->
name|p
operator|->
name|locked
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
DECL|function|gimp_dockable_style_updated (GtkWidget * widget)
name|gimp_dockable_style_updated
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|gint
name|content_border
decl_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_updated
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"content-border"
argument_list|,
operator|&
name|content_border
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
argument_list|,
name|content_border
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_add (GtkContainer * container,GtkWidget * widget)
name|gimp_dockable_add
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|container
argument_list|)
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|GTK_CONTAINER_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|add
argument_list|(
name|container
argument_list|,
name|widget
argument_list|)
expr_stmt|;
comment|/*  not all tab styles are supported by all children  */
name|dockable
operator|=
name|GIMP_DOCKABLE
argument_list|(
name|container
argument_list|)
expr_stmt|;
name|gimp_dockable_set_tab_style
argument_list|(
name|dockable
argument_list|,
name|dockable
operator|->
name|p
operator|->
name|tab_style
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GType
DECL|function|gimp_dockable_child_type (GtkContainer * container)
name|gimp_dockable_child_type
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|)
block|{
if|if
condition|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|container
argument_list|)
argument_list|)
condition|)
return|return
name|G_TYPE_NONE
return|;
return|return
name|GIMP_TYPE_DOCKED
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_dockable_new_tab_widget_internal (GimpDockable * dockable,GimpContext * context,GimpTabStyle tab_style,GtkIconSize size,gboolean dnd)
name|gimp_dockable_new_tab_widget_internal
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpTabStyle
name|tab_style
parameter_list|,
name|GtkIconSize
name|size
parameter_list|,
name|gboolean
name|dnd
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|tab_widget
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|label
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|icon
init|=
name|NULL
decl_stmt|;
switch|switch
condition|(
name|tab_style
condition|)
block|{
case|case
name|GIMP_TAB_STYLE_NAME
case|:
case|case
name|GIMP_TAB_STYLE_ICON_NAME
case|:
case|case
name|GIMP_TAB_STYLE_PREVIEW_NAME
case|:
name|label
operator|=
name|gtk_label_new
argument_list|(
name|dockable
operator|->
name|p
operator|->
name|name
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TAB_STYLE_BLURB
case|:
case|case
name|GIMP_TAB_STYLE_ICON_BLURB
case|:
case|case
name|GIMP_TAB_STYLE_PREVIEW_BLURB
case|:
name|label
operator|=
name|gtk_label_new
argument_list|(
name|dockable
operator|->
name|p
operator|->
name|blurb
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
switch|switch
condition|(
name|tab_style
condition|)
block|{
case|case
name|GIMP_TAB_STYLE_ICON
case|:
case|case
name|GIMP_TAB_STYLE_ICON_NAME
case|:
case|case
name|GIMP_TAB_STYLE_ICON_BLURB
case|:
name|icon
operator|=
name|gimp_dockable_get_icon
argument_list|(
name|dockable
argument_list|,
name|size
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TAB_STYLE_PREVIEW
case|:
case|case
name|GIMP_TAB_STYLE_PREVIEW_NAME
case|:
case|case
name|GIMP_TAB_STYLE_PREVIEW_BLURB
case|:
block|{
name|GtkWidget
modifier|*
name|child
init|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|child
condition|)
name|icon
operator|=
name|gimp_docked_get_preview
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|child
argument_list|)
argument_list|,
name|context
argument_list|,
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|icon
condition|)
name|icon
operator|=
name|gimp_dockable_get_icon
argument_list|(
name|dockable
argument_list|,
name|size
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|label
operator|&&
name|dnd
condition|)
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_WEIGHT
argument_list|,
name|PANGO_WEIGHT_SEMIBOLD
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|tab_style
condition|)
block|{
case|case
name|GIMP_TAB_STYLE_ICON
case|:
case|case
name|GIMP_TAB_STYLE_PREVIEW
case|:
name|tab_widget
operator|=
name|icon
expr_stmt|;
break|break;
case|case
name|GIMP_TAB_STYLE_NAME
case|:
case|case
name|GIMP_TAB_STYLE_BLURB
case|:
name|tab_widget
operator|=
name|label
expr_stmt|;
break|break;
case|case
name|GIMP_TAB_STYLE_ICON_NAME
case|:
case|case
name|GIMP_TAB_STYLE_ICON_BLURB
case|:
case|case
name|GIMP_TAB_STYLE_PREVIEW_NAME
case|:
case|case
name|GIMP_TAB_STYLE_PREVIEW_BLURB
case|:
name|tab_widget
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
name|dnd
condition|?
literal|6
else|:
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|tab_widget
argument_list|)
argument_list|,
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
name|icon
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|tab_widget
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
break|break;
block|}
return|return
name|tab_widget
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dockable_new (const gchar * name,const gchar * blurb,const gchar * icon_name,const gchar * help_id)
name|gimp_dockable_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|icon_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dockable
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DOCKABLE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|p
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|p
operator|->
name|icon_name
operator|=
name|g_strdup
argument_list|(
name|icon_name
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|p
operator|->
name|help_id
operator|=
name|g_strdup
argument_list|(
name|help_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|blurb
condition|)
name|dockable
operator|->
name|p
operator|->
name|blurb
operator|=
name|g_strdup
argument_list|(
name|blurb
argument_list|)
expr_stmt|;
else|else
name|dockable
operator|->
name|p
operator|->
name|blurb
operator|=
name|dockable
operator|->
name|p
operator|->
name|name
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dockable_set_dockbook (GimpDockable * dockable,GimpDockbook * dockbook)
name|gimp_dockable_set_dockbook
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dockbook
operator|==
name|NULL
operator|||
name|GIMP_IS_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|p
operator|->
name|dockbook
operator|=
name|dockbook
expr_stmt|;
block|}
end_function

begin_function
name|GimpDockbook
modifier|*
DECL|function|gimp_dockable_get_dockbook (GimpDockable * dockable)
name|gimp_dockable_get_dockbook
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dockable
operator|->
name|p
operator|->
name|dockbook
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dockable_set_tab_style (GimpDockable * dockable,GimpTabStyle tab_style)
name|gimp_dockable_set_tab_style
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpTabStyle
name|tab_style
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|child
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|child
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|child
operator|&&
operator|!
name|GIMP_DOCKED_GET_INTERFACE
argument_list|(
name|child
argument_list|)
operator|->
name|get_preview
condition|)
name|tab_style
operator|=
name|gimp_preview_tab_style_to_icon
argument_list|(
name|tab_style
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|p
operator|->
name|tab_style
operator|=
name|tab_style
expr_stmt|;
block|}
end_function

begin_function
name|GimpTabStyle
DECL|function|gimp_dockable_get_tab_style (GimpDockable * dockable)
name|gimp_dockable_get_tab_style
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|dockable
operator|->
name|p
operator|->
name|tab_style
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dockable_set_locked (GimpDockable * dockable,gboolean lock)
name|gimp_dockable_set_locked
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|gboolean
name|lock
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
operator|->
name|p
operator|->
name|locked
operator|!=
name|lock
condition|)
block|{
name|dockable
operator|->
name|p
operator|->
name|locked
operator|=
name|lock
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|dockable
argument_list|)
argument_list|,
literal|"locked"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_dockable_get_locked (GimpDockable * dockable)
name|gimp_dockable_get_locked
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|dockable
operator|->
name|p
operator|->
name|locked
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_dockable_get_name (GimpDockable * dockable)
name|gimp_dockable_get_name
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dockable
operator|->
name|p
operator|->
name|name
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_dockable_get_blurb (GimpDockable * dockable)
name|gimp_dockable_get_blurb
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dockable
operator|->
name|p
operator|->
name|blurb
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_dockable_get_help_id (GimpDockable * dockable)
name|gimp_dockable_get_help_id
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dockable
operator|->
name|p
operator|->
name|help_id
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_dockable_get_icon_name (GimpDockable * dockable)
name|gimp_dockable_get_icon_name
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dockable
operator|->
name|p
operator|->
name|icon_name
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dockable_get_icon (GimpDockable * dockable,GtkIconSize size)
name|gimp_dockable_get_icon
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gtk_image_new_from_icon_name
argument_list|(
name|dockable
operator|->
name|p
operator|->
name|icon_name
argument_list|,
name|size
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dockable_create_tab_widget (GimpDockable * dockable,GimpContext * context,GimpTabStyle tab_style,GtkIconSize size)
name|gimp_dockable_create_tab_widget
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpTabStyle
name|tab_style
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_dockable_new_tab_widget_internal
argument_list|(
name|dockable
argument_list|,
name|context
argument_list|,
name|tab_style
argument_list|,
name|size
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dockable_set_context (GimpDockable * dockable,GimpContext * context)
name|gimp_dockable_set_context
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
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
if|if
condition|(
name|context
operator|!=
name|dockable
operator|->
name|p
operator|->
name|context
condition|)
block|{
name|GtkWidget
modifier|*
name|child
init|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|child
condition|)
name|gimp_docked_set_context
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|child
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|p
operator|->
name|context
operator|=
name|context
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpUIManager
modifier|*
DECL|function|gimp_dockable_get_menu (GimpDockable * dockable,const gchar ** ui_path,gpointer * popup_data)
name|gimp_dockable_get_menu
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|ui_path
parameter_list|,
name|gpointer
modifier|*
name|popup_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|child
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|ui_path
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|popup_data
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|child
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|child
condition|)
return|return
name|gimp_docked_get_menu
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|child
argument_list|)
argument_list|,
name|ui_path
argument_list|,
name|popup_data
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dockable_detach (GimpDockable * dockable)
name|gimp_dockable_detach
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|GimpDialogFactory
modifier|*
name|dialog_factory
decl_stmt|;
name|GimpMenuFactory
modifier|*
name|menu_factory
decl_stmt|;
name|GimpDockWindow
modifier|*
name|src_dock_window
decl_stmt|;
name|GimpDock
modifier|*
name|src_dock
decl_stmt|;
name|GtkWidget
modifier|*
name|dock
decl_stmt|;
name|GimpDockWindow
modifier|*
name|dock_window
decl_stmt|;
name|GtkWidget
modifier|*
name|dockbook
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKBOOK
argument_list|(
name|dockable
operator|->
name|p
operator|->
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|src_dock
operator|=
name|gimp_dockbook_get_dock
argument_list|(
name|dockable
operator|->
name|p
operator|->
name|dockbook
argument_list|)
expr_stmt|;
name|src_dock_window
operator|=
name|gimp_dock_window_from_dock
argument_list|(
name|src_dock
argument_list|)
expr_stmt|;
name|dialog_factory
operator|=
name|gimp_dock_get_dialog_factory
argument_list|(
name|src_dock
argument_list|)
expr_stmt|;
name|menu_factory
operator|=
name|gimp_dialog_factory_get_menu_factory
argument_list|(
name|dialog_factory
argument_list|)
expr_stmt|;
name|dock
operator|=
name|gimp_dock_with_window_new
argument_list|(
name|dialog_factory
argument_list|,
name|gimp_widget_get_monitor
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|)
argument_list|,
name|FALSE
comment|/*toolbox*/
argument_list|)
expr_stmt|;
name|dock_window
operator|=
name|gimp_dock_window_from_dock
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_dock_window
condition|)
name|gimp_dock_window_setup
argument_list|(
name|dock_window
argument_list|,
name|src_dock_window
argument_list|)
expr_stmt|;
name|dockbook
operator|=
name|gimp_dockbook_new
argument_list|(
name|menu_factory
argument_list|)
expr_stmt|;
name|gimp_dock_add_book
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|GIMP_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dockable
operator|->
name|p
operator|->
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock_window
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dock
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GList
modifier|*
DECL|function|gimp_dockable_get_aux_info (GimpSessionManaged * session_managed)
name|gimp_dockable_get_aux_info
parameter_list|(
name|GimpSessionManaged
modifier|*
name|session_managed
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|GtkWidget
modifier|*
name|child
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|session_managed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dockable
operator|=
name|GIMP_DOCKABLE
argument_list|(
name|session_managed
argument_list|)
expr_stmt|;
name|child
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|child
condition|)
return|return
name|gimp_docked_get_aux_info
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|child
argument_list|)
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_set_aux_info (GimpSessionManaged * session_managed,GList * aux_info)
name|gimp_dockable_set_aux_info
parameter_list|(
name|GimpSessionManaged
modifier|*
name|session_managed
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|GtkWidget
modifier|*
name|child
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|session_managed
argument_list|)
argument_list|)
expr_stmt|;
name|dockable
operator|=
name|GIMP_DOCKABLE
argument_list|(
name|session_managed
argument_list|)
expr_stmt|;
name|child
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|child
condition|)
name|gimp_docked_set_aux_info
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|child
argument_list|)
argument_list|,
name|aux_info
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

