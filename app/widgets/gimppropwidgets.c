begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppropwidgets.c  * Copyright (C) 2002-2004  Michael Natterer<mitch@gimp.org>  *                          Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
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
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorpanel.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpview.h"
end_include

begin_include
include|#
directive|include
file|"gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-constructors.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  utility function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|set_param_spec
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GParamSpec
modifier|*
name|get_param_spec
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GParamSpec
modifier|*
name|find_param_spec
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|strloc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GParamSpec
modifier|*
name|check_param_spec
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|GType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|strloc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|connect_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/****************/
end_comment

begin_comment
comment|/*  paint menu  */
end_comment

begin_comment
comment|/****************/
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_prop_paint_menu_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_prop_paint_menu_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GtkWidget
modifier|*
name|menu
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_prop_paint_mode_menu_new:  * @config:            #GimpConfig object to which property is attached.  * @property_name:     Name of Enum property controlled by combo box.  * @with_behind_mode:  Whether to include "Behind" mode in the menu.  *  * Creates a #GimpPaintModeMenu widget to display and set the specified  * Enum property, for which the enum must be #GimpLayerModeEffects.  *  * Return value: The newly created #GimpPaintModeMenu widget.  *  * Since GIMP 2.4  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prop_paint_mode_menu_new (GObject * config,const gchar * property_name,gboolean with_behind_mode)
name|gimp_prop_paint_mode_menu_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|gboolean
name|with_behind_mode
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|param_spec
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|gint
name|value
decl_stmt|;
name|param_spec
operator|=
name|check_param_spec
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|G_TYPE_PARAM_ENUM
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|param_spec
condition|)
return|return
name|NULL
return|;
name|g_object_get
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
operator|&
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|menu
operator|=
name|gimp_paint_mode_menu_new
argument_list|(
name|with_behind_mode
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_connect
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|menu
argument_list|)
argument_list|,
name|value
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_prop_paint_menu_callback
argument_list|)
argument_list|,
name|config
argument_list|)
expr_stmt|;
name|set_param_spec
argument_list|(
name|G_OBJECT
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menu
argument_list|,
name|param_spec
argument_list|)
expr_stmt|;
name|connect_notify
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_prop_paint_menu_notify
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
return|return
name|menu
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_prop_paint_menu_callback (GtkWidget * widget,GObject * config)
name|gimp_prop_paint_menu_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|param_spec
decl_stmt|;
name|gint
name|value
decl_stmt|;
name|param_spec
operator|=
name|get_param_spec
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|param_spec
condition|)
return|return;
if|if
condition|(
name|gimp_int_combo_box_get_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|value
argument_list|)
condition|)
block|{
name|g_object_set
argument_list|(
name|config
argument_list|,
name|param_spec
operator|->
name|name
argument_list|,
name|value
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
DECL|function|gimp_prop_paint_menu_notify (GObject * config,GParamSpec * param_spec,GtkWidget * menu)
name|gimp_prop_paint_menu_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GtkWidget
modifier|*
name|menu
parameter_list|)
block|{
name|gint
name|value
decl_stmt|;
name|g_object_get
argument_list|(
name|config
argument_list|,
name|param_spec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|menu
argument_list|,
name|gimp_prop_paint_menu_callback
argument_list|,
name|config
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|menu
argument_list|)
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|menu
argument_list|,
name|gimp_prop_paint_menu_callback
argument_list|,
name|config
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/******************/
end_comment

begin_comment
comment|/*  color button  */
end_comment

begin_comment
comment|/******************/
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_prop_color_button_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_prop_color_button_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GtkWidget
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_prop_color_button_new:  * @config:             #GimpConfig object to which property is attached.  * @property_name:      Name of RGB property.  * @title:              title of the #GimpColorPanel that is to be created  * @width:              Width of color button.  * @height:             Height of color button.  * @type:               How transparency is represented.  *  * Creates a #GimpColorPanel to set and display the value of an RGB  * property.  Pressing the button brings up a color selector dialog.  *  * Return value:  A new #GimpColorPanel widget.  *  * Since GIMP 2.4  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prop_color_button_new (GObject * config,const gchar * property_name,const gchar * title,gint width,gint height,GimpColorAreaType type)
name|gimp_prop_color_button_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpColorAreaType
name|type
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|param_spec
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GimpRGB
modifier|*
name|value
decl_stmt|;
name|param_spec
operator|=
name|check_param_spec
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|GIMP_TYPE_PARAM_RGB
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|param_spec
condition|)
return|return
name|NULL
return|;
name|g_object_get
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
operator|&
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_color_panel_new
argument_list|(
name|title
argument_list|,
name|value
argument_list|,
name|type
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|set_param_spec
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
name|button
argument_list|,
name|param_spec
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"color-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_prop_color_button_callback
argument_list|)
argument_list|,
name|config
argument_list|)
expr_stmt|;
name|connect_notify
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_prop_color_button_notify
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
return|return
name|button
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_prop_color_button_callback (GtkWidget * button,GObject * config)
name|gimp_prop_color_button_callback
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|param_spec
decl_stmt|;
name|GimpRGB
name|value
decl_stmt|;
name|param_spec
operator|=
name|get_param_spec
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|param_spec
condition|)
return|return;
name|gimp_color_button_get_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|config
argument_list|,
name|gimp_prop_color_button_notify
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|config
argument_list|,
name|param_spec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|config
argument_list|,
name|gimp_prop_color_button_notify
argument_list|,
name|button
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_prop_color_button_notify (GObject * config,GParamSpec * param_spec,GtkWidget * button)
name|gimp_prop_color_button_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GtkWidget
modifier|*
name|button
parameter_list|)
block|{
name|GimpRGB
modifier|*
name|value
decl_stmt|;
name|g_object_get
argument_list|(
name|config
argument_list|,
name|param_spec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|button
argument_list|,
name|gimp_prop_color_button_callback
argument_list|,
name|config
argument_list|)
expr_stmt|;
name|gimp_color_button_set_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|button
argument_list|,
name|gimp_prop_color_button_callback
argument_list|,
name|config
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*************/
end_comment

begin_comment
comment|/*  view  */
end_comment

begin_comment
comment|/*************/
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_prop_view_drop
parameter_list|(
name|GtkWidget
modifier|*
name|menu
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_prop_view_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GtkWidget
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_prop_view_new:  * @config:             #GimpConfig object to which property is attached.  * @property_name:      Name of Unit property.  * @size:               Width and height of preview display.  *  * Creates a widget to display the value of a Preview property.  *  * Return value:  A new #GimpView widget.  *  * Since GIMP 2.4  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prop_view_new (GObject * config,const gchar * property_name,gint size)
name|gimp_prop_view_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|param_spec
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
name|param_spec
operator|=
name|check_param_spec
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|G_TYPE_PARAM_OBJECT
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|param_spec
condition|)
return|return
name|NULL
return|;
if|if
condition|(
operator|!
name|g_type_is_a
argument_list|(
name|param_spec
operator|->
name|value_type
argument_list|,
name|GIMP_TYPE_VIEWABLE
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: property '%s' of %s is not a GimpViewable"
argument_list|,
name|G_STRFUNC
argument_list|,
name|property_name
argument_list|,
name|g_type_name
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|config
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|view
operator|=
name|gimp_view_new_by_types
argument_list|(
name|GIMP_TYPE_VIEW
argument_list|,
name|param_spec
operator|->
name|value_type
argument_list|,
name|size
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|view
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: cannot create view for type '%s'"
argument_list|,
name|G_STRFUNC
argument_list|,
name|g_type_name
argument_list|(
name|param_spec
operator|->
name|value_type
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|g_object_get
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
operator|&
name|viewable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|viewable
condition|)
block|{
name|gimp_view_set_viewable
argument_list|(
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
block|}
name|set_param_spec
argument_list|(
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|view
argument_list|,
name|param_spec
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|view
argument_list|,
name|param_spec
operator|->
name|value_type
argument_list|,
name|gimp_prop_view_drop
argument_list|,
name|config
argument_list|)
expr_stmt|;
name|connect_notify
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_prop_view_notify
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
return|return
name|view
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_prop_view_drop (GtkWidget * view,gint x,gint y,GimpViewable * viewable,gpointer data)
name|gimp_prop_view_drop
parameter_list|(
name|GtkWidget
modifier|*
name|view
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GObject
modifier|*
name|config
decl_stmt|;
name|GParamSpec
modifier|*
name|param_spec
decl_stmt|;
name|param_spec
operator|=
name|get_param_spec
argument_list|(
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|param_spec
condition|)
return|return;
name|config
operator|=
name|G_OBJECT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|config
argument_list|,
name|param_spec
operator|->
name|name
argument_list|,
name|viewable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_prop_view_notify (GObject * config,GParamSpec * param_spec,GtkWidget * view)
name|gimp_prop_view_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GtkWidget
modifier|*
name|view
parameter_list|)
block|{
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
name|g_object_get
argument_list|(
name|config
argument_list|,
name|param_spec
operator|->
name|name
argument_list|,
operator|&
name|viewable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_view_set_viewable
argument_list|(
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|viewable
condition|)
name|g_object_unref
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*******************************/
end_comment

begin_comment
comment|/*  private utility functions  */
end_comment

begin_comment
comment|/*******************************/
end_comment

begin_decl_stmt
DECL|variable|param_spec_quark
specifier|static
name|GQuark
name|param_spec_quark
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|set_param_spec (GObject * object,GtkWidget * widget,GParamSpec * param_spec)
name|set_param_spec
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|)
block|{
if|if
condition|(
name|object
condition|)
block|{
if|if
condition|(
operator|!
name|param_spec_quark
condition|)
name|param_spec_quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-config-param-spec"
argument_list|)
expr_stmt|;
name|g_object_set_qdata
argument_list|(
name|object
argument_list|,
name|param_spec_quark
argument_list|,
name|param_spec
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|widget
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|blurb
init|=
name|g_param_spec_get_blurb
argument_list|(
name|param_spec
argument_list|)
decl_stmt|;
if|if
condition|(
name|blurb
condition|)
name|gimp_help_set_help_data
argument_list|(
name|widget
argument_list|,
name|gettext
argument_list|(
name|blurb
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
name|GParamSpec
modifier|*
DECL|function|get_param_spec (GObject * object)
name|get_param_spec
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
if|if
condition|(
operator|!
name|param_spec_quark
condition|)
name|param_spec_quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-config-param-spec"
argument_list|)
expr_stmt|;
return|return
name|g_object_get_qdata
argument_list|(
name|object
argument_list|,
name|param_spec_quark
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GParamSpec
modifier|*
DECL|function|find_param_spec (GObject * object,const gchar * property_name,const gchar * strloc)
name|find_param_spec
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|strloc
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|param_spec
decl_stmt|;
name|param_spec
operator|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|object
argument_list|)
argument_list|,
name|property_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|param_spec
condition|)
name|g_warning
argument_list|(
literal|"%s: %s has no property named '%s'"
argument_list|,
name|strloc
argument_list|,
name|g_type_name
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|object
argument_list|)
argument_list|)
argument_list|,
name|property_name
argument_list|)
expr_stmt|;
return|return
name|param_spec
return|;
block|}
end_function

begin_function
specifier|static
name|GParamSpec
modifier|*
DECL|function|check_param_spec (GObject * object,const gchar * property_name,GType type,const gchar * strloc)
name|check_param_spec
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|GType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|strloc
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|param_spec
decl_stmt|;
name|param_spec
operator|=
name|find_param_spec
argument_list|(
name|object
argument_list|,
name|property_name
argument_list|,
name|strloc
argument_list|)
expr_stmt|;
if|if
condition|(
name|param_spec
operator|&&
operator|!
name|g_type_is_a
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|param_spec
argument_list|)
argument_list|,
name|type
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: property '%s' of %s is not a %s"
argument_list|,
name|strloc
argument_list|,
name|param_spec
operator|->
name|name
argument_list|,
name|g_type_name
argument_list|(
name|param_spec
operator|->
name|owner_type
argument_list|)
argument_list|,
name|g_type_name
argument_list|(
name|type
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|param_spec
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|connect_notify (GObject * config,const gchar * property_name,GCallback callback,gpointer callback_data)
name|connect_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|gchar
modifier|*
name|notify_name
decl_stmt|;
name|notify_name
operator|=
name|g_strconcat
argument_list|(
literal|"notify::"
argument_list|,
name|property_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|config
argument_list|,
name|notify_name
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|notify_name
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

