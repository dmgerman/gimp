begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolorhexentry.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|<gdk/gdkkeysyms.h>
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
file|"gimpcellrenderercolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorhexentry.h"
end_include

begin_include
include|#
directive|include
file|"gimphelpui.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimpcolorhexentry  * @title: GimpColorHexEntry  * @short_description: Widget for entering a color's hex triplet.  *  * Widget for entering a color's hex triplet.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2894b3880103
block|{
DECL|enumerator|COLOR_CHANGED
name|COLOR_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2894b3880203
block|{
DECL|enumerator|COLUMN_NAME
name|COLUMN_NAME
block|,
DECL|enumerator|COLUMN_COLOR
name|COLUMN_COLOR
block|,
DECL|enumerator|NUM_COLUMNS
name|NUM_COLUMNS
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpColorHexEntryPrivate
struct|struct
name|_GimpColorHexEntryPrivate
block|{
DECL|member|color
name|GimpRGB
name|color
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
value|(((GimpColorHexEntry *) (obj))->priv)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_color_hex_entry_constructed
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
name|gimp_color_hex_entry_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_color_hex_entry_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_color_hex_entry_matched
parameter_list|(
name|GtkEntryCompletion
modifier|*
name|completion
parameter_list|,
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GimpColorHexEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpColorHexEntry
argument_list|,
argument|gimp_color_hex_entry
argument_list|,
argument|GTK_TYPE_ENTRY
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_hex_entry_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|entry_signals
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
DECL|function|gimp_color_hex_entry_class_init (GimpColorHexEntryClass * klass)
name|gimp_color_hex_entry_class_init
parameter_list|(
name|GimpColorHexEntryClass
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
name|entry_signals
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
name|GimpColorHexEntryClass
argument_list|,
name|color_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_color_hex_entry_constructed
expr_stmt|;
name|klass
operator|->
name|color_changed
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_hex_entry_init (GimpColorHexEntry * entry)
name|gimp_color_hex_entry_init
parameter_list|(
name|GimpColorHexEntry
modifier|*
name|entry
parameter_list|)
block|{
name|GimpColorHexEntryPrivate
modifier|*
name|private
decl_stmt|;
name|GtkEntryCompletion
modifier|*
name|completion
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GimpRGB
modifier|*
name|colors
decl_stmt|;
specifier|const
name|gchar
modifier|*
modifier|*
name|names
decl_stmt|;
name|gint
name|num_colors
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|entry
operator|->
name|priv
operator|=
name|gimp_color_hex_entry_get_instance_private
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|entry
argument_list|)
expr_stmt|;
comment|/* GtkEntry's minimum size is way too large, set a reasonable one    * for our use case    */
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|GTK_WIDGET
argument_list|(
name|entry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Hexadecimal color notation as used in HTML and "
literal|"CSS.  This entry also accepts CSS color names."
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|private
operator|->
name|color
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
name|store
operator|=
name|gtk_list_store_new
argument_list|(
name|NUM_COLUMNS
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|GIMP_TYPE_RGB
argument_list|)
expr_stmt|;
name|num_colors
operator|=
name|gimp_rgb_list_names
argument_list|(
operator|&
name|names
argument_list|,
operator|&
name|colors
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_colors
condition|;
name|i
operator|++
control|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|gtk_list_store_append
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_NAME
argument_list|,
name|names
index|[
name|i
index|]
argument_list|,
name|COLUMN_COLOR
argument_list|,
name|colors
operator|+
name|i
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|colors
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|names
argument_list|)
expr_stmt|;
name|completion
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_ENTRY_COMPLETION
argument_list|,
literal|"model"
argument_list|,
name|store
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gimp_cell_renderer_color_new
argument_list|()
expr_stmt|;
name|gtk_cell_layout_pack_start
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|completion
argument_list|)
argument_list|,
name|cell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_cell_layout_set_attributes
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|completion
argument_list|)
argument_list|,
name|cell
argument_list|,
literal|"color"
argument_list|,
name|COLUMN_COLOR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_entry_completion_set_text_column
argument_list|(
name|completion
argument_list|,
name|COLUMN_NAME
argument_list|)
expr_stmt|;
name|gtk_entry_set_completion
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|completion
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|completion
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
argument_list|,
literal|"focus-out-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_hex_entry_events
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
argument_list|,
literal|"key-press-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_hex_entry_events
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|completion
argument_list|,
literal|"match-selected"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_hex_entry_matched
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_hex_entry_constructed (GObject * object)
name|gimp_color_hex_entry_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
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
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|object
argument_list|)
argument_list|,
literal|"000000"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_hex_entry_new:  *  * Return value: a new #GimpColorHexEntry widget  *  * Since: 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_hex_entry_new (void)
name|gimp_color_hex_entry_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_HEX_ENTRY
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_hex_entry_set_color:  * @entry: a #GimpColorHexEntry widget  * @color: pointer to a #GimpRGB  *  * Sets the color displayed by a #GimpColorHexEntry. If the new color  * is different to the previously set color, the "color-changed"  * signal is emitted.  *  * Since: 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_hex_entry_set_color (GimpColorHexEntry * entry,const GimpRGB * color)
name|gimp_color_hex_entry_set_color
parameter_list|(
name|GimpColorHexEntry
modifier|*
name|entry
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpColorHexEntryPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_HEX_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|entry
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_rgb_distance
argument_list|(
operator|&
name|private
operator|->
name|color
argument_list|,
name|color
argument_list|)
operator|>
literal|0.0
condition|)
block|{
name|gchar
name|buffer
index|[
literal|8
index|]
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gimp_rgb_set
argument_list|(
operator|&
name|private
operator|->
name|color
argument_list|,
name|color
operator|->
name|r
argument_list|,
name|color
operator|->
name|g
argument_list|,
name|color
operator|->
name|b
argument_list|)
expr_stmt|;
name|gimp_rgb_clamp
argument_list|(
operator|&
name|private
operator|->
name|color
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|private
operator|->
name|color
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
name|g_snprintf
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|"%.2x%.2x%.2x"
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
comment|/* move cursor to the end */
name|gtk_editable_set_position
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|entry
argument_list|,
name|entry_signals
index|[
name|COLOR_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_color_hex_entry_get_color:  * @entry: a #GimpColorHexEntry widget  * @color: (out caller-allocates): pointer to a #GimpRGB  *  * Retrieves the color value displayed by a #GimpColorHexEntry.  *  * Since: 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_hex_entry_get_color (GimpColorHexEntry * entry,GimpRGB * color)
name|gimp_color_hex_entry_get_color
parameter_list|(
name|GimpColorHexEntry
modifier|*
name|entry
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpColorHexEntryPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_HEX_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|entry
argument_list|)
expr_stmt|;
operator|*
name|color
operator|=
name|private
operator|->
name|color
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_color_hex_entry_events (GtkWidget * widget,GdkEvent * event)
name|gimp_color_hex_entry_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
block|{
name|GimpColorHexEntry
modifier|*
name|entry
init|=
name|GIMP_COLOR_HEX_ENTRY
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpColorHexEntryPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|entry
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|event
operator|->
name|type
condition|)
block|{
case|case
name|GDK_KEY_PRESS
case|:
block|{
name|GdkEventKey
modifier|*
name|kevent
init|=
operator|(
name|GdkEventKey
operator|*
operator|)
name|event
decl_stmt|;
if|if
condition|(
name|kevent
operator|->
name|keyval
operator|!=
name|GDK_KEY_Return
operator|&&
name|kevent
operator|->
name|keyval
operator|!=
name|GDK_KEY_KP_Enter
operator|&&
name|kevent
operator|->
name|keyval
operator|!=
name|GDK_KEY_ISO_Enter
condition|)
break|break;
comment|/*  else fall through  */
block|}
case|case
name|GDK_FOCUS_CHANGE
case|:
block|{
specifier|const
name|gchar
modifier|*
name|text
decl_stmt|;
name|gchar
name|buffer
index|[
literal|8
index|]
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|text
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|private
operator|->
name|color
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
name|g_snprintf
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|"%.2x%.2x%.2x"
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_ascii_strcasecmp
argument_list|(
name|buffer
argument_list|,
name|text
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gsize
name|len
init|=
name|strlen
argument_list|(
name|text
argument_list|)
decl_stmt|;
if|if
condition|(
name|len
operator|>
literal|0
operator|&&
operator|(
name|gimp_rgb_parse_hex
argument_list|(
operator|&
name|color
argument_list|,
name|text
argument_list|,
name|len
argument_list|)
operator|||
name|gimp_rgb_parse_name
argument_list|(
operator|&
name|color
argument_list|,
name|text
argument_list|,
operator|-
literal|1
argument_list|)
operator|)
condition|)
block|{
name|gimp_color_hex_entry_set_color
argument_list|(
name|entry
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
block|}
block|}
block|}
break|break;
default|default:
comment|/*  do nothing  */
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_color_hex_entry_matched (GtkEntryCompletion * completion,GtkTreeModel * model,GtkTreeIter * iter,GimpColorHexEntry * entry)
name|gimp_color_hex_entry_matched
parameter_list|(
name|GtkEntryCompletion
modifier|*
name|completion
parameter_list|,
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GimpColorHexEntry
modifier|*
name|entry
parameter_list|)
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|COLUMN_NAME
argument_list|,
operator|&
name|name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_rgb_parse_name
argument_list|(
operator|&
name|color
argument_list|,
name|name
argument_list|,
operator|-
literal|1
argument_list|)
condition|)
name|gimp_color_hex_entry_set_color
argument_list|(
name|entry
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

