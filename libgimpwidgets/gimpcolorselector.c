begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolorselector.c  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * based on:  * Colour selector module  * Copyright (C) 1999 Austin Donnelly<austin@greenend.org.uk>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"gimpicons.h"
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
DECL|enum|__anon27df0a790103
block|{
DECL|enumerator|COLOR_CHANGED
name|COLOR_CHANGED
block|,
DECL|enumerator|CHANNEL_CHANGED
name|CHANNEL_CHANGED
block|,
DECL|enumerator|MODEL_VISIBLE_CHANGED
name|MODEL_VISIBLE_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpColorSelectorPrivate
struct|struct
name|_GimpColorSelectorPrivate
block|{
DECL|member|model_visible
name|gboolean
name|model_visible
index|[
literal|3
index|]
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
value|(((GimpColorSelector *) (obj))->priv)
end_define

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
name|_gimp_widgets_marshal_VOID__ENUM
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_COLOR_SELECTOR_CHANNEL
argument_list|)
expr_stmt|;
name|selector_signals
index|[
name|MODEL_VISIBLE_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"model-visible-changed"
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
name|model_visible_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_gimp_widgets_marshal_VOID__ENUM_BOOLEAN
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|GIMP_TYPE_COLOR_SELECTOR_MODEL
argument_list|,
name|G_TYPE_BOOLEAN
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
name|GIMP_ICON_PALETTE
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
name|set_model_visible
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
name|model_visible_changed
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|set_config
operator|=
name|NULL
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpColorSelectorPrivate
argument_list|)
argument_list|)
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
name|GimpColorSelectorPrivate
modifier|*
name|priv
decl_stmt|;
name|selector
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|selector
argument_list|,
name|GIMP_TYPE_COLOR_SELECTOR
argument_list|,
name|GimpColorSelectorPrivate
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GET_PRIVATE
argument_list|(
name|selector
argument_list|)
expr_stmt|;
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
name|GIMP_COLOR_SELECTOR_RED
expr_stmt|;
name|priv
operator|->
name|model_visible
index|[
name|GIMP_COLOR_SELECTOR_MODEL_RGB
index|]
operator|=
name|TRUE
expr_stmt|;
name|priv
operator|->
name|model_visible
index|[
name|GIMP_COLOR_SELECTOR_MODEL_LCH
index|]
operator|=
name|TRUE
expr_stmt|;
name|priv
operator|->
name|model_visible
index|[
name|GIMP_COLOR_SELECTOR_MODEL_HSV
index|]
operator|=
name|FALSE
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

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_color_selector_new:  * @selector_type: The #GType of the selector to create.  * @rgb:           The initial color to be edited.  * @hsv:           The same color in HSV.  * @channel:       The selector's initial channel.  *  * Creates a new #GimpColorSelector widget of type @selector_type.  *  * Note that this is mostly internal API to be used by other widgets.  *  * Please use gimp_color_selection_new() for the "GIMP-typical" color  * selection widget. Also see gimp_color_button_new().  *  * Retunn value: the new #GimpColorSelector widget.  **/
end_comment

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

begin_comment
comment|/**  * gimp_color_selector_set_toggles_visible:  * @selector: A #GimpColorSelector widget.  * @visible:  The new @visible setting.  *  * Sets the @visible property of the @selector's toggles.  *  * This function has no effect if this @selector instance has no  * toggles to switch channels.  **/
end_comment

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

begin_comment
comment|/**  * gimp_color_selector_get_toggles_visible:  * @selector: A #GimpColorSelector widget.  *  * Returns the @visible property of the @selector's toggles.  *  * Return value: #TRUE if the #GimpColorSelector's toggles are visible.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_color_selector_get_toggles_visible (GimpColorSelector * selector)
name|gimp_color_selector_get_toggles_visible
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|selector
operator|->
name|toggles_visible
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_selector_set_toggles_sensitive:  * @selector:  A #GimpColorSelector widget.  * @sensitive: The new @sensitive setting.  *  * Sets the @sensitive property of the @selector's toggles.  *  * This function has no effect if this @selector instance has no  * toggles to switch channels.  **/
end_comment

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

begin_comment
comment|/**  * gimp_color_selector_get_toggles_sensitive:  * @selector: A #GimpColorSelector widget.  *  * Returns the @sensitive property of the @selector's toggles.  *  * Return value: #TRUE if the #GimpColorSelector's toggles are sensitive.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_color_selector_get_toggles_sensitive (GimpColorSelector * selector)
name|gimp_color_selector_get_toggles_sensitive
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|selector
operator|->
name|toggles_sensitive
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_selector_set_show_alpha:  * @selector:   A #GimpColorSelector widget.  * @show_alpha: The new @show_alpha setting.  *  * Sets the @show_alpha property of the @selector widget.  **/
end_comment

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

begin_comment
comment|/**  * gimp_color_selector_get_show_alpha:  * @selector: A #GimpColorSelector widget.  *  * Returns the @selector's @show_alpha property.  *  * Return value: #TRUE if the #GimpColorSelector has alpha controls.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_color_selector_get_show_alpha (GimpColorSelector * selector)
name|gimp_color_selector_get_show_alpha
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|selector
operator|->
name|show_alpha
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_selector_set_color:  * @selector: A #GimpColorSelector widget.  * @rgb:      The new color.  * @hsv:      The same color in HSV.  *  * Sets the color shown in the @selector widget.  **/
end_comment

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

begin_comment
comment|/**  * gimp_color_selector_get_color:  * @selector: A #GimpColorSelector widget.  * @rgb:      Return location for the color.  * @hsv:      Return location for the same same color in HSV.  *  * Retrieves the color shown in the @selector widget.  *  * Since: 2.10  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_selector_get_color (GimpColorSelector * selector,GimpRGB * rgb,GimpHSV * hsv)
name|gimp_color_selector_get_color
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|GimpHSV
modifier|*
name|hsv
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
operator|*
name|rgb
operator|=
name|selector
operator|->
name|rgb
expr_stmt|;
operator|*
name|hsv
operator|=
name|selector
operator|->
name|hsv
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_selector_set_channel:  * @selector: A #GimpColorSelector widget.  * @channel:  The new @channel setting.  *  * Sets the @channel property of the @selector widget.  *  * Changes between displayed channels if this @selector instance has  * the ability to show different channels.  * This will also update the color model if needed.  **/
end_comment

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
name|GimpColorSelectorModel
name|model
init|=
operator|-
literal|1
decl_stmt|;
name|selector
operator|->
name|channel
operator|=
name|channel
expr_stmt|;
switch|switch
condition|(
name|channel
condition|)
block|{
case|case
name|GIMP_COLOR_SELECTOR_RED
case|:
case|case
name|GIMP_COLOR_SELECTOR_GREEN
case|:
case|case
name|GIMP_COLOR_SELECTOR_BLUE
case|:
name|model
operator|=
name|GIMP_COLOR_SELECTOR_MODEL_RGB
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_SELECTOR_HUE
case|:
case|case
name|GIMP_COLOR_SELECTOR_SATURATION
case|:
case|case
name|GIMP_COLOR_SELECTOR_VALUE
case|:
name|model
operator|=
name|GIMP_COLOR_SELECTOR_MODEL_HSV
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_SELECTOR_LCH_LIGHTNESS
case|:
case|case
name|GIMP_COLOR_SELECTOR_LCH_CHROMA
case|:
case|case
name|GIMP_COLOR_SELECTOR_LCH_HUE
case|:
name|model
operator|=
name|GIMP_COLOR_SELECTOR_MODEL_LCH
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_SELECTOR_ALPHA
case|:
comment|/* Alpha channel does not change the color model. */
break|break;
default|default:
comment|/* Should not happen. */
name|g_return_if_reached
argument_list|()
expr_stmt|;
break|break;
block|}
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
if|if
condition|(
name|model
operator|!=
operator|-
literal|1
condition|)
block|{
comment|/*  make visibility of LCH and HSV mutuallky exclusive  */
if|if
condition|(
name|model
operator|==
name|GIMP_COLOR_SELECTOR_MODEL_HSV
condition|)
block|{
name|gimp_color_selector_set_model_visible
argument_list|(
name|selector
argument_list|,
name|GIMP_COLOR_SELECTOR_MODEL_LCH
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|model
operator|==
name|GIMP_COLOR_SELECTOR_MODEL_LCH
condition|)
block|{
name|gimp_color_selector_set_model_visible
argument_list|(
name|selector
argument_list|,
name|GIMP_COLOR_SELECTOR_MODEL_HSV
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|gimp_color_selector_set_model_visible
argument_list|(
name|selector
argument_list|,
name|model
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_color_selector_get_channel:  * @selector: A #GimpColorSelector widget.  *  * Returns the @selector's current channel.  *  * Return value: The #GimpColorSelectorChannel currently shown by the  * @selector.  *  * Since: 2.10  **/
end_comment

begin_function
name|GimpColorSelectorChannel
DECL|function|gimp_color_selector_get_channel (GimpColorSelector * selector)
name|gimp_color_selector_get_channel
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|,
name|GIMP_COLOR_SELECTOR_RED
argument_list|)
expr_stmt|;
return|return
name|selector
operator|->
name|channel
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_selector_set_model_visible:  * @selector: A #GimpColorSelector widget.  * @model:    The affected #GimpColorSelectorModel.  * @visible:  The new visible setting.  *  * Sets the @model visible/invisible on the @selector widget.  *  * Toggles visibility of displayed models if this @selector instance  * has the ability to show different color models.  *  * Since: 2.10  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_selector_set_model_visible (GimpColorSelector * selector,GimpColorSelectorModel model,gboolean visible)
name|gimp_color_selector_set_model_visible
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorSelectorModel
name|model
parameter_list|,
name|gboolean
name|visible
parameter_list|)
block|{
name|GimpColorSelectorPrivate
modifier|*
name|priv
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GET_PRIVATE
argument_list|(
name|selector
argument_list|)
expr_stmt|;
name|visible
operator|=
name|visible
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
if|if
condition|(
name|visible
operator|!=
name|priv
operator|->
name|model_visible
index|[
name|model
index|]
condition|)
block|{
name|GimpColorSelectorClass
modifier|*
name|selector_class
decl_stmt|;
name|priv
operator|->
name|model_visible
index|[
name|model
index|]
operator|=
name|visible
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
name|set_model_visible
condition|)
name|selector_class
operator|->
name|set_model_visible
argument_list|(
name|selector
argument_list|,
name|model
argument_list|,
name|visible
argument_list|)
expr_stmt|;
name|gimp_color_selector_model_visible_changed
argument_list|(
name|selector
argument_list|,
name|model
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_color_selector_get_model_visible:  * @selector: A #GimpColorSelector widget.  * @model:    The #GimpColorSelectorModel.  *  * Return value: whether @model is visible in @selector.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_color_selector_get_model_visible (GimpColorSelector * selector,GimpColorSelectorModel model)
name|gimp_color_selector_get_model_visible
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorSelectorModel
name|model
parameter_list|)
block|{
name|GimpColorSelectorPrivate
modifier|*
name|priv
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GET_PRIVATE
argument_list|(
name|selector
argument_list|)
expr_stmt|;
return|return
name|priv
operator|->
name|model_visible
index|[
name|model
index|]
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_selector_color_changed:  * @selector: A #GimpColorSelector widget.  *  * Emits the "color-changed" signal.  **/
end_comment

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

begin_comment
comment|/**  * gimp_color_selector_channel_changed:  * @selector: A #GimpColorSelector widget.  *  * Emits the "channel-changed" signal.  **/
end_comment

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
comment|/**  * gimp_color_selector_model_visible_changed:  * @selector: A #GimpColorSelector widget.  *  * Emits the "model-visible-changed" signal.  *  * Since: 2.10  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_selector_model_visible_changed (GimpColorSelector * selector,GimpColorSelectorModel model)
name|gimp_color_selector_model_visible_changed
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorSelectorModel
name|model
parameter_list|)
block|{
name|GimpColorSelectorPrivate
modifier|*
name|priv
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_SELECTOR
argument_list|(
name|selector
argument_list|)
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GET_PRIVATE
argument_list|(
name|selector
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|selector
argument_list|,
name|selector_signals
index|[
name|MODEL_VISIBLE_CHANGED
index|]
argument_list|,
literal|0
argument_list|,
name|model
argument_list|,
name|priv
operator|->
name|model_visible
index|[
name|model
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_selector_set_config:  * @selector: a #GimpColorSelector widget.  * @config:   a #GimpColorConfig object.  *  * Sets the color management configuration to use with this color selector.  *  * Since: 2.4  */
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

