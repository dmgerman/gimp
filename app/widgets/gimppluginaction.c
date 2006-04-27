begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginaction.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimppluginprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginaction.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c64b6950103
block|{
DECL|enumerator|SELECTED
name|SELECTED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2c64b6950203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PROCEDURE
name|PROP_PROCEDURE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_plug_in_action_finalize
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
name|gimp_plug_in_action_set_property
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
name|gimp_plug_in_action_get_property
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
name|gimp_plug_in_action_activate
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_plug_in_action_connect_proxy
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

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpPlugInAction
argument_list|,
name|gimp_plug_in_action
argument_list|,
name|GIMP_TYPE_ACTION
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_plug_in_action_parent_class
end_define

begin_decl_stmt
DECL|variable|action_signals
specifier|static
name|guint
name|action_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_action_class_init (GimpPlugInActionClass * klass)
name|gimp_plug_in_action_class_init
parameter_list|(
name|GimpPlugInActionClass
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
name|object_class
operator|->
name|finalize
operator|=
name|gimp_plug_in_action_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_plug_in_action_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_plug_in_action_get_property
expr_stmt|;
name|action_class
operator|->
name|activate
operator|=
name|gimp_plug_in_action_activate
expr_stmt|;
name|action_class
operator|->
name|connect_proxy
operator|=
name|gimp_plug_in_action_connect_proxy
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PROCEDURE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"procedure"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_PLUG_IN_PROCEDURE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|action_signals
index|[
name|SELECTED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"selected"
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
name|GimpPlugInActionClass
argument_list|,
name|selected
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_action_init (GimpPlugInAction * action)
name|gimp_plug_in_action_init
parameter_list|(
name|GimpPlugInAction
modifier|*
name|action
parameter_list|)
block|{
name|action
operator|->
name|procedure
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_action_finalize (GObject * object)
name|gimp_plug_in_action_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPlugInAction
modifier|*
name|action
init|=
name|GIMP_PLUG_IN_ACTION
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|action
operator|->
name|procedure
condition|)
block|{
name|g_object_unref
argument_list|(
name|action
operator|->
name|procedure
argument_list|)
expr_stmt|;
name|action
operator|->
name|procedure
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
DECL|function|gimp_plug_in_action_get_property (GObject * object,guint prop_id,GValue * value,GParamSpec * pspec)
name|gimp_plug_in_action_get_property
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
name|GimpPlugInAction
modifier|*
name|action
init|=
name|GIMP_PLUG_IN_ACTION
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
name|PROP_PROCEDURE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|action
operator|->
name|procedure
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
DECL|function|gimp_plug_in_action_set_property (GObject * object,guint prop_id,const GValue * value,GParamSpec * pspec)
name|gimp_plug_in_action_set_property
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
name|GimpPlugInAction
modifier|*
name|action
init|=
name|GIMP_PLUG_IN_ACTION
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
name|PROP_PROCEDURE
case|:
if|if
condition|(
name|action
operator|->
name|procedure
condition|)
name|g_object_unref
argument_list|(
name|action
operator|->
name|procedure
argument_list|)
expr_stmt|;
name|action
operator|->
name|procedure
operator|=
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|g_value_dup_object
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
DECL|function|gimp_plug_in_action_activate (GtkAction * action)
name|gimp_plug_in_action_activate
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|)
block|{
name|GimpPlugInAction
modifier|*
name|plug_in_action
init|=
name|GIMP_PLUG_IN_ACTION
argument_list|(
name|action
argument_list|)
decl_stmt|;
name|gimp_plug_in_action_selected
argument_list|(
name|plug_in_action
argument_list|,
name|plug_in_action
operator|->
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_action_connect_proxy (GtkAction * action,GtkWidget * proxy)
name|gimp_plug_in_action_connect_proxy
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
name|GimpPlugInAction
modifier|*
name|plug_in_action
init|=
name|GIMP_PLUG_IN_ACTION
argument_list|(
name|action
argument_list|)
decl_stmt|;
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
if|if
condition|(
name|GTK_IS_IMAGE_MENU_ITEM
argument_list|(
name|proxy
argument_list|)
operator|&&
name|plug_in_action
operator|->
name|procedure
condition|)
block|{
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|pixbuf
operator|=
name|gimp_plug_in_procedure_get_pixbuf
argument_list|(
name|plug_in_action
operator|->
name|procedure
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
block|{
name|GtkSettings
modifier|*
name|settings
init|=
name|gtk_widget_get_settings
argument_list|(
name|proxy
argument_list|)
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
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
if|if
condition|(
name|width
operator|!=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
operator|||
name|height
operator|!=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
condition|)
block|{
name|GdkPixbuf
modifier|*
name|copy
decl_stmt|;
name|copy
operator|=
name|gdk_pixbuf_scale_simple
argument_list|(
name|pixbuf
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GDK_INTERP_BILINEAR
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|copy
expr_stmt|;
block|}
name|image
operator|=
name|gtk_image_new_from_pixbuf
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|gtk_image_menu_item_set_image
argument_list|(
name|GTK_IMAGE_MENU_ITEM
argument_list|(
name|proxy
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpPlugInAction
modifier|*
DECL|function|gimp_plug_in_action_new (const gchar * name,const gchar * label,const gchar * tooltip,const gchar * stock_id,GimpPlugInProcedure * procedure)
name|gimp_plug_in_action_new
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
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_PLUG_IN_ACTION
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
literal|"stock-id"
argument_list|,
name|stock_id
argument_list|,
literal|"procedure"
argument_list|,
name|procedure
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_action_selected (GimpPlugInAction * action,GimpPlugInProcedure * procedure)
name|gimp_plug_in_action_selected
parameter_list|(
name|GimpPlugInAction
modifier|*
name|action
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|action
argument_list|,
name|action_signals
index|[
name|SELECTED
index|]
argument_list|,
literal|0
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

