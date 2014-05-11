begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolorselector.c  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * based on:  * Colour selector module  * Copyright (C) 1999 Austin Donnelly<austin@greenend.org.uk>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorselector.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetsmarshal.h"
end_include

begin_comment
comment|/**  * SECTION: gimpcolorselector  * @title: GimpColorSelector  * @short_description: Pluggable GIMP color selector modules.  * @see_also: #GModule, #GTypeModule, #GimpModule  *  * Functions and definitions for creating pluggable GIMP color  * selector modules.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2c5e39ec0103
block|{
DECL|enumerator|COLOR_CHANGED
name|COLOR_CHANGED
block|,
DECL|enumerator|CHANNEL_CHANGED
name|CHANNEL_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_color_selector_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpColorSelector
argument_list|,
argument|gimp_color_selector
argument_list|,
argument|GTK_TYPE_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_selector_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|selector_signals
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
DECL|function|gimp_color_selector_class_init (GimpColorSelectorClass * klass)
name|gimp_color_selector_class_init
parameter_list|(
name|GimpColorSelectorClass
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
name|dispose
operator|=
name|gimp_color_selector_dispose
expr_stmt|;
name|selector_signals
index|[
name|COLOR_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"color-changed"
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
name|GimpColorSelectorClass
argument_list|,
name|color_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_gimp_widgets_marshal_VOID__POINTER_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|selector_signals
index|[
name|CHANNEL_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"channel-changed"
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
name|GimpColorSelectorClass
argument_list|,
name|channel_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_gimp_widgets_marshal_VOID__INT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|klass
operator|->
name|name
operator|=
literal|"Unnamed"
expr_stmt|;
name|klass
operator|->
name|help_id
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|icon_name
operator|=
literal|"gtk-select-color"
expr_stmt|;
name|klass
operator|->
name|set_toggles_visible
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|set_toggles_sensitive
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|set_show_alpha
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|set_color
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|set_channel
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|color_changed
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|channel_changed
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|set_config
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_selector_init (GimpColorSelector * selector)
name|gimp_color_selector_init
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|)
block|{
name|selector
operator|->
name|toggles_visible
operator|=
name|TRUE
expr_stmt|;
name|selector
operator|->
name|toggles_sensitive
operator|=
name|TRUE
expr_stmt|;
name|selector
operator|->
name|show_alpha
operator|=
name|TRUE
expr_stmt|;
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|selector
argument_list|)
argument_list|,
name|GTK_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|selector
operator|->
name|rgb
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_rgb_to_hsv
argument_list|(
operator|&
name|selector
operator|->
name|rgb
argument_list|,
operator|&
name|selector
operator|->
name|hsv
argument_list|)
expr_stmt|;
name|selector
operator|->
name|channel
operator|=
name|GIMP_COLOR_SELECTOR_HUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_selector_dispose (GObject * object)
name|gimp_color_selector_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|gimp_color_selector_set_config
argument_list|(
name|GIMP_COLOR_SELECTOR
argument_list|(
name|object
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|GtkWidget
modifier|*
DECL|function|gimp_color_selector_new (GType selector_type,const GimpRGB * rgb,const GimpHSV * hsv,GimpColorSelectorChannel channel)
name|gimp_color_selector_new
parameter_list|(
name|GType
name|selector_type
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|)
block|{
name|GimpColorSelector
modifier|*
name|selector
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|selector_type
argument_list|,
name|GIMP_TYPE_COLOR_SELECTOR
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|hsv
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|selector
operator|=
name|g_object_new
argument_list|(
name|selector_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_color_selector_set_color
argument_list|(
name|selector
argument_list|,
name|rgb
argument_list|,
name|hsv
argument_list|)
expr_stmt|;
name|gimp_color_selector_set_channel
argument_list|(
name|selector
argument_list|,
name|channel
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|selector
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_selector_set_toggles_visible (GimpColorSelector * selector,gboolean visible)
name|gimp_color_selector_set_toggles_visible
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|visible
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|selector
operator|->
name|toggles_visible
operator|!=
name|visible
condition|)
block|{
name|GimpColorSelectorClass
modifier|*
name|selector_class
decl_stmt|;
name|selector
operator|->
name|toggles_visible
operator|=
name|visible
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|selector_class
operator|=
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|selector
argument_list|)
expr_stmt|;
if|if
condition|(
name|selector_class
operator|->
name|set_toggles_visible
condition|)
name|selector_class
operator|->
name|set_toggles_visible
argument_list|(
name|selector
argument_list|,
name|visible
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_selector_set_toggles_sensitive (GimpColorSelector * selector,gboolean sensitive)
name|gimp_color_selector_set_toggles_sensitive
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|selector
operator|->
name|toggles_sensitive
operator|!=
name|sensitive
condition|)
block|{
name|GimpColorSelectorClass
modifier|*
name|selector_class
decl_stmt|;
name|selector
operator|->
name|toggles_sensitive
operator|=
name|sensitive
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|selector_class
operator|=
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|selector
argument_list|)
expr_stmt|;
if|if
condition|(
name|selector_class
operator|->
name|set_toggles_sensitive
condition|)
name|selector_class
operator|->
name|set_toggles_sensitive
argument_list|(
name|selector
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_selector_set_show_alpha (GimpColorSelector * selector,gboolean show_alpha)
name|gimp_color_selector_set_show_alpha
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|show_alpha
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|show_alpha
operator|!=
name|selector
operator|->
name|show_alpha
condition|)
block|{
name|GimpColorSelectorClass
modifier|*
name|selector_class
decl_stmt|;
name|selector
operator|->
name|show_alpha
operator|=
name|show_alpha
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|selector_class
operator|=
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|selector
argument_list|)
expr_stmt|;
if|if
condition|(
name|selector_class
operator|->
name|set_show_alpha
condition|)
name|selector_class
operator|->
name|set_show_alpha
argument_list|(
name|selector
argument_list|,
name|show_alpha
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_selector_set_color (GimpColorSelector * selector,const GimpRGB * rgb,const GimpHSV * hsv)
name|gimp_color_selector_set_color
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
block|{
name|GimpColorSelectorClass
modifier|*
name|selector_class
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|hsv
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|selector
operator|->
name|rgb
operator|=
operator|*
name|rgb
expr_stmt|;
name|selector
operator|->
name|hsv
operator|=
operator|*
name|hsv
expr_stmt|;
name|selector_class
operator|=
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|selector
argument_list|)
expr_stmt|;
if|if
condition|(
name|selector_class
operator|->
name|set_color
condition|)
name|selector_class
operator|->
name|set_color
argument_list|(
name|selector
argument_list|,
name|rgb
argument_list|,
name|hsv
argument_list|)
expr_stmt|;
name|gimp_color_selector_color_changed
argument_list|(
name|selector
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_selector_set_channel (GimpColorSelector * selector,GimpColorSelectorChannel channel)
name|gimp_color_selector_set_channel
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|channel
operator|!=
name|selector
operator|->
name|channel
condition|)
block|{
name|GimpColorSelectorClass
modifier|*
name|selector_class
decl_stmt|;
name|selector
operator|->
name|channel
operator|=
name|channel
expr_stmt|;
name|selector_class
operator|=
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|selector
argument_list|)
expr_stmt|;
if|if
condition|(
name|selector_class
operator|->
name|set_channel
condition|)
name|selector_class
operator|->
name|set_channel
argument_list|(
name|selector
argument_list|,
name|channel
argument_list|)
expr_stmt|;
name|gimp_color_selector_channel_changed
argument_list|(
name|selector
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_selector_color_changed (GimpColorSelector * selector)
name|gimp_color_selector_color_changed
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|selector
argument_list|,
name|selector_signals
index|[
name|COLOR_CHANGED
index|]
argument_list|,
literal|0
argument_list|,
operator|&
name|selector
operator|->
name|rgb
argument_list|,
operator|&
name|selector
operator|->
name|hsv
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_selector_channel_changed (GimpColorSelector * selector)
name|gimp_color_selector_channel_changed
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|selector
argument_list|,
name|selector_signals
index|[
name|CHANNEL_CHANGED
index|]
argument_list|,
literal|0
argument_list|,
name|selector
operator|->
name|channel
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_selector_set_config:  * @selector: a #GimpColorSelector widget.  * @config:   a #GimpColorConfig object.  *  * Sets the color management configuration to use with this color selector.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|void
DECL|function|gimp_color_selector_set_config (GimpColorSelector * selector,GimpColorConfig * config)
name|gimp_color_selector_set_config
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpColorSelectorClass
modifier|*
name|selector_class
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|config
operator|==
name|NULL
operator|||
name|GIMP_IS_COLOR_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|selector_class
operator|=
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|selector
argument_list|)
expr_stmt|;
if|if
condition|(
name|selector_class
operator|->
name|set_config
condition|)
name|selector_class
operator|->
name|set_config
argument_list|(
name|selector
argument_list|,
name|config
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

