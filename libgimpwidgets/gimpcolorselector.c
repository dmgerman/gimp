begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolorselector.c  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * based on:  * Colour selector module  * Copyright (C) 1999 Austin Donnelly<austin@greenend.org.uk>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU Lesser General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
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

begin_enum
enum|enum
DECL|enum|__anon2c8ab0870103
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
name|gimp_color_selector_class_init
parameter_list|(
name|GimpColorSelectorClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_selector_init
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkVBoxClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|selector_signals
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
name|GType
DECL|function|gimp_color_selector_get_type (void)
name|gimp_color_selector_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|selector_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|selector_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|selector_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpColorSelectorClass
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
name|gimp_color_selector_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpColorSelector
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_color_selector_init
block|,       }
decl_stmt|;
name|selector_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_VBOX
argument_list|,
literal|"GimpColorSelector"
argument_list|,
operator|&
name|selector_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|selector_type
return|;
block|}
end_function

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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|selector_signals
index|[
name|COLOR_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"color_changed"
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
literal|"channel_changed"
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
name|show_alpha
operator|=
name|TRUE
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
if|if
condition|(
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|selector
argument_list|)
operator|->
name|set_show_alpha
condition|)
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|selector
argument_list|)
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
if|if
condition|(
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|selector
argument_list|)
operator|->
name|set_color
condition|)
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|selector
argument_list|)
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
name|selector
operator|->
name|channel
operator|=
name|channel
expr_stmt|;
if|if
condition|(
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|selector
argument_list|)
operator|->
name|set_channel
condition|)
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|selector
argument_list|)
operator|->
name|set_channel
argument_list|(
name|selector
argument_list|,
name|channel
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
name|G_OBJECT
argument_list|(
name|selector
argument_list|)
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
name|G_OBJECT
argument_list|(
name|selector
argument_list|)
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

end_unit

