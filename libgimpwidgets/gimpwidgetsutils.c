begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpwidgets.c  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<lcms2.h>
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

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
end_ifdef

begin_include
include|#
directive|include
file|<Carbon/Carbon.h>
end_include

begin_include
include|#
directive|include
file|<ApplicationServices/ApplicationServices.h>
end_include

begin_include
include|#
directive|include
file|<CoreServices/CoreServices.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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
file|"gimp3migration.h"
end_include

begin_include
include|#
directive|include
file|"gimpsizeentry.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetsutils.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimpwidgetsutils  * @title: GimpWidgetsUtils  * @short_description: A collection of helper functions.  *  * A collection of helper functions.  **/
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|find_mnemonic_widget (GtkWidget * widget,gint level)
name|find_mnemonic_widget
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|level
parameter_list|)
block|{
name|gboolean
name|can_focus
decl_stmt|;
name|g_object_get
argument_list|(
name|widget
argument_list|,
literal|"can-focus"
argument_list|,
operator|&
name|can_focus
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|activate_signal
operator|||
name|can_focus
operator|||
name|GTK_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|mnemonic_activate
operator|!=
name|GTK_WIDGET_CLASS
argument_list|(
name|g_type_class_peek
argument_list|(
name|GTK_TYPE_WIDGET
argument_list|)
argument_list|)
operator|->
name|mnemonic_activate
condition|)
block|{
return|return
name|widget
return|;
block|}
if|if
condition|(
name|GIMP_IS_SIZE_ENTRY
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GimpSizeEntry
modifier|*
name|entry
init|=
name|GIMP_SIZE_ENTRY
argument_list|(
name|widget
argument_list|)
decl_stmt|;
return|return
name|gimp_size_entry_get_help_widget
argument_list|(
name|entry
argument_list|,
name|entry
operator|->
name|number_of_fields
operator|-
literal|1
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|GTK_IS_CONTAINER
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|mnemonic_widget
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|children
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|children
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|mnemonic_widget
operator|=
name|find_mnemonic_widget
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|level
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|mnemonic_widget
condition|)
break|break;
block|}
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
return|return
name|mnemonic_widget
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_table_attach_aligned:  * @table:      The #GtkTable the widgets will be attached to.  * @column:     The column to start with.  * @row:        The row to attach the widgets.  * @label_text: The text for the #GtkLabel which will be attached left of  *              the widget.  * @xalign:     The horizontal alignment of the #GtkLabel.  * @yalign:     The vertival alignment of the #GtkLabel.  * @widget:     The #GtkWidget to attach right of the label.  * @colspan:    The number of columns the widget will use.  * @left_align: %TRUE if the widget should be left-aligned.  *  * Note that the @label_text can be %NULL and that the widget will be  * attached starting at (@column + 1) in this case, too.  *  * Returns: The created #GtkLabel.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_table_attach_aligned (GtkTable * table,gint column,gint row,const gchar * label_text,gfloat xalign,gfloat yalign,GtkWidget * widget,gint colspan,gboolean left_align)
name|gimp_table_attach_aligned
parameter_list|(
name|GtkTable
modifier|*
name|table
parameter_list|,
name|gint
name|column
parameter_list|,
name|gint
name|row
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label_text
parameter_list|,
name|gfloat
name|xalign
parameter_list|,
name|gfloat
name|yalign
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|colspan
parameter_list|,
name|gboolean
name|left_align
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|label_text
condition|)
block|{
name|GtkWidget
modifier|*
name|mnemonic_widget
decl_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|label_text
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
name|xalign
argument_list|,
name|yalign
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
name|column
argument_list|,
name|column
operator|+
literal|1
argument_list|,
name|row
argument_list|,
name|row
operator|+
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|mnemonic_widget
operator|=
name|find_mnemonic_widget
argument_list|(
name|widget
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|mnemonic_widget
condition|)
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|mnemonic_widget
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|left_align
condition|)
block|{
name|GtkWidget
modifier|*
name|hbox
init|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|0
argument_list|)
decl_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|widget
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
name|widget
argument_list|)
expr_stmt|;
name|widget
operator|=
name|hbox
expr_stmt|;
block|}
name|gtk_table_attach
argument_list|(
name|table
argument_list|,
name|widget
argument_list|,
name|column
operator|+
literal|1
argument_list|,
name|column
operator|+
literal|1
operator|+
name|colspan
argument_list|,
name|row
argument_list|,
name|row
operator|+
literal|1
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
return|return
name|label
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_label_set_attributes:  * @label: a #GtkLabel  * @...:   a list of PangoAttrType and value pairs terminated by -1.  *  * Sets Pango attributes on a #GtkLabel in a more convenient way than  * gtk_label_set_attributes().  *  * This function is useful if you want to change the font attributes  * of a #GtkLabel. This is an alternative to using PangoMarkup which  * is slow to parse and akward to handle in an i18n-friendly way.  *  * The attributes are set on the complete label, from start to end. If  * you need to set attributes on part of the label, you will have to  * use the PangoAttributes API directly.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_label_set_attributes (GtkLabel * label,...)
name|gimp_label_set_attributes
parameter_list|(
name|GtkLabel
modifier|*
name|label
parameter_list|,
modifier|...
parameter_list|)
block|{
name|PangoAttribute
modifier|*
name|attr
init|=
name|NULL
decl_stmt|;
name|PangoAttrList
modifier|*
name|attrs
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_LABEL
argument_list|(
name|label
argument_list|)
argument_list|)
expr_stmt|;
name|attrs
operator|=
name|pango_attr_list_new
argument_list|()
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|label
argument_list|)
expr_stmt|;
do|do
block|{
name|PangoAttrType
name|attr_type
init|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|PangoAttrType
argument_list|)
decl_stmt|;
if|if
condition|(
name|attr_type
operator|==
operator|-
literal|1
condition|)
name|attr_type
operator|=
name|PANGO_ATTR_INVALID
expr_stmt|;
switch|switch
condition|(
name|attr_type
condition|)
block|{
case|case
name|PANGO_ATTR_LANGUAGE
case|:
name|attr
operator|=
name|pango_attr_language_new
argument_list|(
name|va_arg
argument_list|(
name|args
argument_list|,
name|PangoLanguage
operator|*
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PANGO_ATTR_FAMILY
case|:
name|attr
operator|=
name|pango_attr_family_new
argument_list|(
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PANGO_ATTR_STYLE
case|:
name|attr
operator|=
name|pango_attr_style_new
argument_list|(
name|va_arg
argument_list|(
name|args
argument_list|,
name|PangoStyle
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PANGO_ATTR_WEIGHT
case|:
name|attr
operator|=
name|pango_attr_weight_new
argument_list|(
name|va_arg
argument_list|(
name|args
argument_list|,
name|PangoWeight
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PANGO_ATTR_VARIANT
case|:
name|attr
operator|=
name|pango_attr_variant_new
argument_list|(
name|va_arg
argument_list|(
name|args
argument_list|,
name|PangoVariant
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PANGO_ATTR_STRETCH
case|:
name|attr
operator|=
name|pango_attr_stretch_new
argument_list|(
name|va_arg
argument_list|(
name|args
argument_list|,
name|PangoStretch
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PANGO_ATTR_SIZE
case|:
name|attr
operator|=
name|pango_attr_size_new
argument_list|(
name|va_arg
argument_list|(
name|args
argument_list|,
name|gint
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PANGO_ATTR_FONT_DESC
case|:
name|attr
operator|=
name|pango_attr_font_desc_new
argument_list|(
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|PangoFontDescription
operator|*
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PANGO_ATTR_FOREGROUND
case|:
block|{
specifier|const
name|PangoColor
modifier|*
name|color
init|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|PangoColor
operator|*
argument_list|)
decl_stmt|;
name|attr
operator|=
name|pango_attr_foreground_new
argument_list|(
name|color
operator|->
name|red
argument_list|,
name|color
operator|->
name|green
argument_list|,
name|color
operator|->
name|blue
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|PANGO_ATTR_BACKGROUND
case|:
block|{
specifier|const
name|PangoColor
modifier|*
name|color
init|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|PangoColor
operator|*
argument_list|)
decl_stmt|;
name|attr
operator|=
name|pango_attr_background_new
argument_list|(
name|color
operator|->
name|red
argument_list|,
name|color
operator|->
name|green
argument_list|,
name|color
operator|->
name|blue
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|PANGO_ATTR_UNDERLINE
case|:
name|attr
operator|=
name|pango_attr_underline_new
argument_list|(
name|va_arg
argument_list|(
name|args
argument_list|,
name|PangoUnderline
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PANGO_ATTR_STRIKETHROUGH
case|:
name|attr
operator|=
name|pango_attr_strikethrough_new
argument_list|(
name|va_arg
argument_list|(
name|args
argument_list|,
name|gboolean
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PANGO_ATTR_RISE
case|:
name|attr
operator|=
name|pango_attr_rise_new
argument_list|(
name|va_arg
argument_list|(
name|args
argument_list|,
name|gint
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PANGO_ATTR_SCALE
case|:
name|attr
operator|=
name|pango_attr_scale_new
argument_list|(
name|va_arg
argument_list|(
name|args
argument_list|,
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"%s: invalid PangoAttribute type %d"
argument_list|,
name|G_STRFUNC
argument_list|,
name|attr_type
argument_list|)
expr_stmt|;
case|case
name|PANGO_ATTR_INVALID
case|:
name|attr
operator|=
name|NULL
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|attr
condition|)
block|{
name|attr
operator|->
name|start_index
operator|=
literal|0
expr_stmt|;
name|attr
operator|->
name|end_index
operator|=
operator|-
literal|1
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|attrs
argument_list|,
name|attr
argument_list|)
expr_stmt|;
block|}
block|}
do|while
condition|(
name|attr
condition|)
do|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|gtk_label_set_attributes
argument_list|(
name|label
argument_list|,
name|attrs
argument_list|)
expr_stmt|;
name|pango_attr_list_unref
argument_list|(
name|attrs
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_widget_get_monitor (GtkWidget * widget)
name|gimp_widget_get_monitor
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GdkWindow
modifier|*
name|window
decl_stmt|;
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|window
operator|=
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|window
condition|)
return|return
name|gimp_get_monitor_at_pointer
argument_list|(
operator|&
name|screen
argument_list|)
return|;
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gdk_window_get_origin
argument_list|(
name|window
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_widget_get_has_window
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|x
operator|+=
name|allocation
operator|.
name|x
expr_stmt|;
name|y
operator|+=
name|allocation
operator|.
name|y
expr_stmt|;
block|}
name|x
operator|+=
name|allocation
operator|.
name|width
operator|/
literal|2
expr_stmt|;
name|y
operator|+=
name|allocation
operator|.
name|height
operator|/
literal|2
expr_stmt|;
return|return
name|gdk_screen_get_monitor_at_point
argument_list|(
name|screen
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_get_monitor_at_pointer (GdkScreen ** screen)
name|gimp_get_monitor_at_pointer
parameter_list|(
name|GdkScreen
modifier|*
modifier|*
name|screen
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|screen
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gdk_display_get_pointer
argument_list|(
name|gdk_display_get_default
argument_list|()
argument_list|,
name|screen
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gdk_screen_get_monitor_at_point
argument_list|(
operator|*
name|screen
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpColorProfile
DECL|function|gimp_widget_get_color_profile (GtkWidget * widget)
name|gimp_widget_get_color_profile
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpColorProfile
name|profile
init|=
name|NULL
decl_stmt|;
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|gint
name|monitor
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|widget
operator|==
name|NULL
operator|||
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
condition|)
block|{
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|monitor
operator|=
name|gimp_widget_get_monitor
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|screen
operator|=
name|gdk_screen_get_default
argument_list|()
expr_stmt|;
name|monitor
operator|=
literal|0
expr_stmt|;
block|}
if|#
directive|if
name|defined
name|GDK_WINDOWING_X11
block|{
name|GdkAtom
name|type
init|=
name|GDK_NONE
decl_stmt|;
name|gint
name|format
init|=
literal|0
decl_stmt|;
name|gint
name|nitems
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
name|atom_name
decl_stmt|;
name|guchar
modifier|*
name|data
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|monitor
operator|>
literal|0
condition|)
name|atom_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"_ICC_PROFILE_%d"
argument_list|,
name|monitor
argument_list|)
expr_stmt|;
else|else
name|atom_name
operator|=
name|g_strdup
argument_list|(
literal|"_ICC_PROFILE"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdk_property_get
argument_list|(
name|gdk_screen_get_root_window
argument_list|(
name|screen
argument_list|)
argument_list|,
name|gdk_atom_intern
argument_list|(
name|atom_name
argument_list|,
name|FALSE
argument_list|)
argument_list|,
name|GDK_NONE
argument_list|,
literal|0
argument_list|,
literal|64
operator|*
literal|1024
operator|*
literal|1024
argument_list|,
name|FALSE
argument_list|,
operator|&
name|type
argument_list|,
operator|&
name|format
argument_list|,
operator|&
name|nitems
argument_list|,
operator|&
name|data
argument_list|)
operator|&&
name|nitems
operator|>
literal|0
condition|)
block|{
name|profile
operator|=
name|gimp_lcms_profile_open_from_data
argument_list|(
name|data
argument_list|,
name|nitems
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|atom_name
argument_list|)
expr_stmt|;
block|}
elif|#
directive|elif
name|defined
name|GDK_WINDOWING_QUARTZ
block|{
name|CMProfileRef
name|prof
init|=
name|NULL
decl_stmt|;
name|CMGetProfileByAVID
argument_list|(
name|monitor
argument_list|,
operator|&
name|prof
argument_list|)
expr_stmt|;
if|if
condition|(
name|prof
condition|)
block|{
name|CFDataRef
name|data
decl_stmt|;
name|data
operator|=
name|CMProfileCopyICCData
argument_list|(
name|NULL
argument_list|,
name|prof
argument_list|)
expr_stmt|;
name|CMCloseProfile
argument_list|(
name|prof
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
block|{
name|UInt8
modifier|*
name|buffer
init|=
name|g_malloc
argument_list|(
name|CFDataGetLength
argument_list|(
name|data
argument_list|)
argument_list|)
decl_stmt|;
comment|/* We cannot use CFDataGetBytesPtr(), because that returns              * a const pointer where cmsOpenProfileFromMem wants a              * non-const pointer.              */
name|CFDataGetBytes
argument_list|(
name|data
argument_list|,
name|CFRangeMake
argument_list|(
literal|0
argument_list|,
name|CFDataGetLength
argument_list|(
name|data
argument_list|)
argument_list|)
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|profile
operator|=
name|gimp_lcms_profile_open_from_data
argument_list|(
name|data
argument_list|,
name|CFDataGetLength
argument_list|(
name|data
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|CFRelease
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
block|}
block|}
elif|#
directive|elif
name|defined
name|G_OS_WIN32
block|{
name|HDC
name|hdc
init|=
name|GetDC
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|hdc
condition|)
block|{
name|gchar
modifier|*
name|path
decl_stmt|;
name|gint32
name|len
init|=
literal|0
decl_stmt|;
name|GetICMProfile
argument_list|(
name|hdc
argument_list|,
operator|&
name|len
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|path
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|GetICMProfile
argument_list|(
name|hdc
argument_list|,
operator|&
name|len
argument_list|,
name|path
argument_list|)
condition|)
block|{
name|GFile
modifier|*
name|file
init|=
name|g_file_new_for_path
argument_list|(
name|path
argument_list|)
decl_stmt|;
name|profile
operator|=
name|gimp_lcms_profile_open_from_file
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|ReleaseDC
argument_list|(
name|NULL
argument_list|,
name|hdc
argument_list|)
expr_stmt|;
block|}
block|}
endif|#
directive|endif
return|return
name|profile
return|;
block|}
end_function

begin_function
specifier|static
name|GimpColorProfile
DECL|function|get_display_profile (GtkWidget * widget,GimpColorConfig * config)
name|get_display_profile
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpColorProfile
name|profile
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|config
operator|->
name|display_profile_from_gdk
condition|)
name|profile
operator|=
name|gimp_widget_get_color_profile
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|profile
condition|)
name|profile
operator|=
name|gimp_color_config_get_display_profile
argument_list|(
name|config
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|profile
return|;
block|}
end_function

begin_function
name|GimpColorTransform
DECL|function|gimp_widget_get_color_transform (GtkWidget * widget,GimpColorManaged * managed,GimpColorConfig * config,const Babl ** src_format,const Babl ** dest_format)
name|gimp_widget_get_color_transform
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorManaged
modifier|*
name|managed
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|Babl
modifier|*
modifier|*
name|src_format
parameter_list|,
specifier|const
name|Babl
modifier|*
modifier|*
name|dest_format
parameter_list|)
block|{
name|GimpColorTransform
name|transform
init|=
name|NULL
decl_stmt|;
name|GimpColorProfile
name|src_profile
init|=
name|NULL
decl_stmt|;
name|GimpColorProfile
name|dest_profile
init|=
name|NULL
decl_stmt|;
name|GimpColorProfile
name|proof_profile
init|=
name|NULL
decl_stmt|;
name|cmsUInt32Number
name|lcms_src_format
decl_stmt|;
name|cmsUInt32Number
name|lcms_dest_format
decl_stmt|;
name|cmsUInt16Number
name|alarmCodes
index|[
name|cmsMAXCHANNELS
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|widget
operator|==
name|NULL
operator|||
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_MANAGED
argument_list|(
name|managed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_format
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dest_format
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|config
operator|->
name|mode
condition|)
block|{
case|case
name|GIMP_COLOR_MANAGEMENT_OFF
case|:
return|return
name|NULL
return|;
case|case
name|GIMP_COLOR_MANAGEMENT_SOFTPROOF
case|:
name|proof_profile
operator|=
name|gimp_color_config_get_printer_profile
argument_list|(
name|config
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  fallthru  */
case|case
name|GIMP_COLOR_MANAGEMENT_DISPLAY
case|:
name|src_profile
operator|=
name|gimp_color_managed_get_color_profile
argument_list|(
name|managed
argument_list|)
expr_stmt|;
name|dest_profile
operator|=
name|get_display_profile
argument_list|(
name|widget
argument_list|,
name|config
argument_list|)
expr_stmt|;
break|break;
block|}
operator|*
name|src_format
operator|=
name|gimp_lcms_get_format
argument_list|(
operator|*
name|src_format
argument_list|,
operator|&
name|lcms_src_format
argument_list|)
expr_stmt|;
operator|*
name|dest_format
operator|=
name|gimp_lcms_get_format
argument_list|(
operator|*
name|dest_format
argument_list|,
operator|&
name|lcms_dest_format
argument_list|)
expr_stmt|;
if|if
condition|(
name|proof_profile
condition|)
block|{
name|cmsUInt32Number
name|softproof_flags
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|src_profile
condition|)
name|src_profile
operator|=
name|gimp_lcms_create_srgb_profile
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|dest_profile
condition|)
name|dest_profile
operator|=
name|gimp_lcms_create_srgb_profile
argument_list|()
expr_stmt|;
name|softproof_flags
operator||=
name|cmsFLAGS_SOFTPROOFING
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|simulation_use_black_point_compensation
condition|)
block|{
name|softproof_flags
operator||=
name|cmsFLAGS_BLACKPOINTCOMPENSATION
expr_stmt|;
block|}
if|if
condition|(
name|config
operator|->
name|simulation_gamut_check
condition|)
block|{
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|softproof_flags
operator||=
name|cmsFLAGS_GAMUTCHECK
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|config
operator|->
name|out_of_gamut_color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|alarmCodes
index|[
literal|0
index|]
operator|=
operator|(
name|cmsUInt16Number
operator|)
name|r
operator|*
literal|256
expr_stmt|;
name|alarmCodes
index|[
literal|1
index|]
operator|=
operator|(
name|cmsUInt16Number
operator|)
name|g
operator|*
literal|256
expr_stmt|;
name|alarmCodes
index|[
literal|2
index|]
operator|=
operator|(
name|cmsUInt16Number
operator|)
name|b
operator|*
literal|256
expr_stmt|;
name|cmsSetAlarmCodes
argument_list|(
name|alarmCodes
argument_list|)
expr_stmt|;
block|}
name|transform
operator|=
name|cmsCreateProofingTransform
argument_list|(
name|src_profile
argument_list|,
name|lcms_src_format
argument_list|,
name|dest_profile
argument_list|,
name|lcms_dest_format
argument_list|,
name|proof_profile
argument_list|,
name|config
operator|->
name|simulation_intent
argument_list|,
name|config
operator|->
name|display_intent
argument_list|,
name|softproof_flags
argument_list|)
expr_stmt|;
name|gimp_lcms_profile_close
argument_list|(
name|proof_profile
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|src_profile
operator|||
name|dest_profile
condition|)
block|{
name|cmsUInt32Number
name|display_flags
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|src_profile
condition|)
name|src_profile
operator|=
name|gimp_lcms_create_srgb_profile
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|dest_profile
condition|)
name|dest_profile
operator|=
name|gimp_lcms_create_srgb_profile
argument_list|()
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|display_use_black_point_compensation
condition|)
block|{
name|display_flags
operator||=
name|cmsFLAGS_BLACKPOINTCOMPENSATION
expr_stmt|;
block|}
name|transform
operator|=
name|cmsCreateTransform
argument_list|(
name|src_profile
argument_list|,
name|lcms_src_format
argument_list|,
name|dest_profile
argument_list|,
name|lcms_dest_format
argument_list|,
name|config
operator|->
name|display_intent
argument_list|,
name|display_flags
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|src_profile
condition|)
name|gimp_lcms_profile_close
argument_list|(
name|src_profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|dest_profile
condition|)
name|gimp_lcms_profile_close
argument_list|(
name|dest_profile
argument_list|)
expr_stmt|;
return|return
name|transform
return|;
block|}
end_function

end_unit

