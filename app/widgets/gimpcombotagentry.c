begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcombotagentry.c  * Copyright (C) 2008 Aurimas JuÅ¡ka<aurisj@svn.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptag.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptagged.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptaggedcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimptagentry.h"
end_include

begin_include
include|#
directive|include
file|"gimptagpopup.h"
end_include

begin_include
include|#
directive|include
file|"gimpcombotagentry.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_combo_tag_entry_constructed
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
name|gimp_combo_tag_entry_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_combo_tag_entry_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_combo_tag_entry_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|previous_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_combo_tag_entry_icon_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkEntryIconPosition
name|icon_pos
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_combo_tag_entry_popup_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|GimpComboTagEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_combo_tag_entry_tag_count_changed
parameter_list|(
name|GimpTaggedContainer
modifier|*
name|container
parameter_list|,
name|gint
name|tag_count
parameter_list|,
name|GimpComboTagEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpComboTagEntry
argument_list|,
name|gimp_combo_tag_entry
argument_list|,
name|GIMP_TYPE_TAG_ENTRY
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_combo_tag_entry_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_combo_tag_entry_class_init (GimpComboTagEntryClass * klass)
name|gimp_combo_tag_entry_class_init
parameter_list|(
name|GimpComboTagEntryClass
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
name|object_class
operator|->
name|constructed
operator|=
name|gimp_combo_tag_entry_constructed
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_combo_tag_entry_dispose
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_combo_tag_entry_expose
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_combo_tag_entry_style_set
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_combo_tag_entry_init (GimpComboTagEntry * entry)
name|gimp_combo_tag_entry_init
parameter_list|(
name|GimpComboTagEntry
modifier|*
name|entry
parameter_list|)
block|{
name|entry
operator|->
name|popup
operator|=
name|NULL
expr_stmt|;
name|entry
operator|->
name|normal_item_attr
operator|=
name|NULL
expr_stmt|;
name|entry
operator|->
name|selected_item_attr
operator|=
name|NULL
expr_stmt|;
name|entry
operator|->
name|insensitive_item_attr
operator|=
name|NULL
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|GTK_WIDGET
argument_list|(
name|entry
argument_list|)
argument_list|,
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_POINTER_MOTION_MASK
argument_list|)
expr_stmt|;
name|gtk_entry_set_icon_from_stock
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|GTK_ENTRY_ICON_SECONDARY
argument_list|,
name|GTK_STOCK_GO_DOWN
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
argument_list|,
literal|"icon-press"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_combo_tag_entry_icon_press
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
DECL|function|gimp_combo_tag_entry_constructed (GObject * object)
name|gimp_combo_tag_entry_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpComboTagEntry
modifier|*
name|entry
init|=
name|GIMP_COMBO_TAG_ENTRY
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|GIMP_TAG_ENTRY
argument_list|(
name|entry
argument_list|)
operator|->
name|container
argument_list|,
literal|"tag-count-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_combo_tag_entry_tag_count_changed
argument_list|)
argument_list|,
name|entry
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_combo_tag_entry_dispose (GObject * object)
name|gimp_combo_tag_entry_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpComboTagEntry
modifier|*
name|combo_entry
init|=
name|GIMP_COMBO_TAG_ENTRY
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|combo_entry
operator|->
name|arrow_pixbuf
condition|)
block|{
name|g_object_unref
argument_list|(
name|combo_entry
operator|->
name|arrow_pixbuf
argument_list|)
expr_stmt|;
name|combo_entry
operator|->
name|arrow_pixbuf
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|combo_entry
operator|->
name|normal_item_attr
condition|)
block|{
name|pango_attr_list_unref
argument_list|(
name|combo_entry
operator|->
name|normal_item_attr
argument_list|)
expr_stmt|;
name|combo_entry
operator|->
name|normal_item_attr
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|combo_entry
operator|->
name|selected_item_attr
condition|)
block|{
name|pango_attr_list_unref
argument_list|(
name|combo_entry
operator|->
name|selected_item_attr
argument_list|)
expr_stmt|;
name|combo_entry
operator|->
name|selected_item_attr
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|combo_entry
operator|->
name|insensitive_item_attr
condition|)
block|{
name|pango_attr_list_unref
argument_list|(
name|combo_entry
operator|->
name|insensitive_item_attr
argument_list|)
expr_stmt|;
name|combo_entry
operator|->
name|insensitive_item_attr
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
name|gboolean
DECL|function|gimp_combo_tag_entry_expose (GtkWidget * widget,GdkEventExpose * event)
name|gimp_combo_tag_entry_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
block|{
name|GimpComboTagEntry
modifier|*
name|entry
init|=
name|GIMP_COMBO_TAG_ENTRY
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|entry
operator|->
name|arrow_pixbuf
condition|)
block|{
name|GtkStyle
modifier|*
name|style
init|=
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GdkPixmap
modifier|*
name|pixmap
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|pixmap
operator|=
name|gdk_pixmap_new
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|8
argument_list|,
literal|8
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|pixmap
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|style
operator|->
name|base
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|gtk_paint_arrow
argument_list|(
name|style
argument_list|,
name|pixmap
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|GTK_SHADOW_NONE
argument_list|,
name|NULL
argument_list|,
name|widget
argument_list|,
name|NULL
argument_list|,
name|GTK_ARROW_DOWN
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|8
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|entry
operator|->
name|arrow_pixbuf
operator|=
name|gdk_pixbuf_get_from_drawable
argument_list|(
name|NULL
argument_list|,
name|pixmap
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|8
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixmap
argument_list|)
expr_stmt|;
name|gtk_entry_set_icon_from_pixbuf
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|GTK_ENTRY_ICON_SECONDARY
argument_list|,
name|entry
operator|->
name|arrow_pixbuf
argument_list|)
expr_stmt|;
block|}
return|return
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|expose_event
argument_list|(
name|widget
argument_list|,
name|event
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_combo_tag_entry_style_set (GtkWidget * widget,GtkStyle * previous_style)
name|gimp_combo_tag_entry_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|previous_style
parameter_list|)
block|{
name|GimpComboTagEntry
modifier|*
name|entry
init|=
name|GIMP_COMBO_TAG_ENTRY
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkStyle
modifier|*
name|style
init|=
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GdkColor
name|color
decl_stmt|;
name|PangoAttribute
modifier|*
name|attribute
decl_stmt|;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
condition|)
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
argument_list|(
name|widget
argument_list|,
name|previous_style
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
operator|->
name|normal_item_attr
condition|)
name|pango_attr_list_unref
argument_list|(
name|entry
operator|->
name|normal_item_attr
argument_list|)
expr_stmt|;
name|entry
operator|->
name|normal_item_attr
operator|=
name|pango_attr_list_new
argument_list|()
expr_stmt|;
if|if
condition|(
name|style
operator|->
name|font_desc
condition|)
block|{
name|attribute
operator|=
name|pango_attr_font_desc_new
argument_list|(
name|style
operator|->
name|font_desc
argument_list|)
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|entry
operator|->
name|normal_item_attr
argument_list|,
name|attribute
argument_list|)
expr_stmt|;
block|}
name|color
operator|=
name|style
operator|->
name|text
index|[
name|GTK_STATE_NORMAL
index|]
expr_stmt|;
name|attribute
operator|=
name|pango_attr_foreground_new
argument_list|(
name|color
operator|.
name|red
argument_list|,
name|color
operator|.
name|green
argument_list|,
name|color
operator|.
name|blue
argument_list|)
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|entry
operator|->
name|normal_item_attr
argument_list|,
name|attribute
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
operator|->
name|selected_item_attr
condition|)
name|pango_attr_list_unref
argument_list|(
name|entry
operator|->
name|selected_item_attr
argument_list|)
expr_stmt|;
name|entry
operator|->
name|selected_item_attr
operator|=
name|pango_attr_list_copy
argument_list|(
name|entry
operator|->
name|normal_item_attr
argument_list|)
expr_stmt|;
name|color
operator|=
name|style
operator|->
name|text
index|[
name|GTK_STATE_SELECTED
index|]
expr_stmt|;
name|attribute
operator|=
name|pango_attr_foreground_new
argument_list|(
name|color
operator|.
name|red
argument_list|,
name|color
operator|.
name|green
argument_list|,
name|color
operator|.
name|blue
argument_list|)
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|entry
operator|->
name|selected_item_attr
argument_list|,
name|attribute
argument_list|)
expr_stmt|;
name|color
operator|=
name|style
operator|->
name|base
index|[
name|GTK_STATE_SELECTED
index|]
expr_stmt|;
name|attribute
operator|=
name|pango_attr_background_new
argument_list|(
name|color
operator|.
name|red
argument_list|,
name|color
operator|.
name|green
argument_list|,
name|color
operator|.
name|blue
argument_list|)
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|entry
operator|->
name|selected_item_attr
argument_list|,
name|attribute
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
operator|->
name|insensitive_item_attr
condition|)
name|pango_attr_list_unref
argument_list|(
name|entry
operator|->
name|insensitive_item_attr
argument_list|)
expr_stmt|;
name|entry
operator|->
name|insensitive_item_attr
operator|=
name|pango_attr_list_copy
argument_list|(
name|entry
operator|->
name|normal_item_attr
argument_list|)
expr_stmt|;
name|color
operator|=
name|style
operator|->
name|text
index|[
name|GTK_STATE_INSENSITIVE
index|]
expr_stmt|;
name|attribute
operator|=
name|pango_attr_foreground_new
argument_list|(
name|color
operator|.
name|red
argument_list|,
name|color
operator|.
name|green
argument_list|,
name|color
operator|.
name|blue
argument_list|)
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|entry
operator|->
name|insensitive_item_attr
argument_list|,
name|attribute
argument_list|)
expr_stmt|;
name|color
operator|=
name|style
operator|->
name|base
index|[
name|GTK_STATE_INSENSITIVE
index|]
expr_stmt|;
name|attribute
operator|=
name|pango_attr_background_new
argument_list|(
name|color
operator|.
name|red
argument_list|,
name|color
operator|.
name|green
argument_list|,
name|color
operator|.
name|blue
argument_list|)
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|entry
operator|->
name|insensitive_item_attr
argument_list|,
name|attribute
argument_list|)
expr_stmt|;
name|entry
operator|->
name|selected_item_color
operator|=
name|style
operator|->
name|base
index|[
name|GTK_STATE_SELECTED
index|]
expr_stmt|;
if|if
condition|(
name|entry
operator|->
name|arrow_pixbuf
condition|)
block|{
name|g_object_unref
argument_list|(
name|entry
operator|->
name|arrow_pixbuf
argument_list|)
expr_stmt|;
name|entry
operator|->
name|arrow_pixbuf
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_combo_tag_entry_new:  * @container: a tagged container to be used.  * @mode:      tag entry mode to work in.  *  * Creates a new #GimpComboTagEntry widget which extends #GimpTagEntry by  * adding ability to pick tags using popup window (similar to combo box).  *  * Return value: a new #GimpComboTagEntry widget.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_combo_tag_entry_new (GimpTaggedContainer * container,GimpTagEntryMode mode)
name|gimp_combo_tag_entry_new
parameter_list|(
name|GimpTaggedContainer
modifier|*
name|container
parameter_list|,
name|GimpTagEntryMode
name|mode
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TAGGED_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_COMBO_TAG_ENTRY
argument_list|,
literal|"container"
argument_list|,
name|container
argument_list|,
literal|"mode"
argument_list|,
name|mode
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_combo_tag_entry_icon_press (GtkWidget * widget,GtkEntryIconPosition icon_pos,GdkEvent * event,gpointer user_data)
name|gimp_combo_tag_entry_icon_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkEntryIconPosition
name|icon_pos
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpComboTagEntry
modifier|*
name|entry
init|=
name|GIMP_COMBO_TAG_ENTRY
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|entry
operator|->
name|popup
condition|)
block|{
name|GimpTaggedContainer
modifier|*
name|container
init|=
name|GIMP_TAG_ENTRY
argument_list|(
name|entry
argument_list|)
operator|->
name|container
decl_stmt|;
name|gint
name|tag_count
decl_stmt|;
name|tag_count
operator|=
name|gimp_tagged_container_get_tag_count
argument_list|(
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|tag_count
operator|>
literal|0
operator|&&
operator|!
name|GIMP_TAG_ENTRY
argument_list|(
name|entry
argument_list|)
operator|->
name|has_invalid_tags
condition|)
block|{
name|entry
operator|->
name|popup
operator|=
name|gimp_tag_popup_new
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
operator|->
name|popup
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_combo_tag_entry_popup_destroy
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|gimp_tag_popup_show
argument_list|(
name|GIMP_TAG_POPUP
argument_list|(
name|entry
operator|->
name|popup
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gtk_widget_destroy
argument_list|(
name|entry
operator|->
name|popup
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_combo_tag_entry_popup_destroy (GtkObject * object,GimpComboTagEntry * entry)
name|gimp_combo_tag_entry_popup_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|GimpComboTagEntry
modifier|*
name|entry
parameter_list|)
block|{
name|entry
operator|->
name|popup
operator|=
name|NULL
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|GTK_WIDGET
argument_list|(
name|entry
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_combo_tag_entry_tag_count_changed (GimpTaggedContainer * container,gint tag_count,GimpComboTagEntry * entry)
name|gimp_combo_tag_entry_tag_count_changed
parameter_list|(
name|GimpTaggedContainer
modifier|*
name|container
parameter_list|,
name|gint
name|tag_count
parameter_list|,
name|GimpComboTagEntry
modifier|*
name|entry
parameter_list|)
block|{
name|gboolean
name|sensitive
decl_stmt|;
name|sensitive
operator|=
name|tag_count
operator|>
literal|0
operator|&&
operator|!
name|GIMP_TAG_ENTRY
argument_list|(
name|entry
argument_list|)
operator|->
name|has_invalid_tags
expr_stmt|;
name|gtk_entry_set_icon_sensitive
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|GTK_ENTRY_ICON_SECONDARY
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

