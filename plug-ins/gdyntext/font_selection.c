begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * GIMP Dynamic Text -- This is a plug-in for The GIMP 1.0  * Copyright (C) 1998,1999 Marco Lamberto<lm@geocities.com>  * Web page: http://www.geocities.com/Tokyo/1474/gimp/  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * $Id$  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<X11/Xlib.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdkx.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"font_selection.h"
end_include

begin_function_decl
specifier|static
name|void
name|font_selection_class_init
parameter_list|(
name|FontSelectionClass
modifier|*
name|class
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|font_selection_init
parameter_list|(
name|FontSelection
modifier|*
name|fs
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|on_font_selection_family_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|on_font_selection_value_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|MAX_FONTS
define|#
directive|define
name|MAX_FONTS
value|32767
end_define

begin_enum
DECL|enum|__anon29d9bcd30103
enum|enum
block|{
DECL|enumerator|FONT_CHANGED
name|FONT_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_decl_stmt
DECL|variable|font_selection_signals
specifier|static
name|gint
name|font_selection_signals
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
DECL|function|font_selection_get_type (void)
name|guint
name|font_selection_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|guint
name|fs_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|fs_type
condition|)
block|{
name|GtkTypeInfo
name|fs_info
init|=
block|{
literal|"FontSelection"
block|,
sizeof|sizeof
argument_list|(
name|FontSelection
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|FontSelectionClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|font_selection_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|font_selection_init
block|,
operator|(
name|GtkArgSetFunc
operator|)
name|NULL
block|,
operator|(
name|GtkArgGetFunc
operator|)
name|NULL
block|,
ifdef|#
directive|ifdef
name|GTK_HAVE_FEATURES_1_1_12
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|,
endif|#
directive|endif
block|}
decl_stmt|;
name|fs_type
operator|=
name|gtk_type_unique
argument_list|(
name|gtk_hbox_get_type
argument_list|()
argument_list|,
operator|&
name|fs_info
argument_list|)
expr_stmt|;
block|}
return|return
name|fs_type
return|;
block|}
end_function

begin_function
DECL|function|font_selection_class_init (FontSelectionClass * klass)
specifier|static
name|void
name|font_selection_class_init
parameter_list|(
name|FontSelectionClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|font_selection_signals
index|[
name|FONT_CHANGED
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"font_changed"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|FontSelectionClass
argument_list|,
name|font_changed
argument_list|)
argument_list|,
name|gtk_signal_default_marshaller
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
name|font_selection_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
name|klass
operator|->
name|font_changed
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
DECL|function|font_selection_init (FontSelection * fs)
specifier|static
name|void
name|font_selection_init
parameter_list|(
name|FontSelection
modifier|*
name|fs
parameter_list|)
block|{
name|GtkObject
modifier|*
name|font_size_adj
decl_stmt|;
name|GList
modifier|*
name|font_metric_items
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|l
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|plist
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|xfontnames
decl_stmt|,
modifier|*
name|p
decl_stmt|,
modifier|*
name|q
decl_stmt|,
modifier|*
name|fname
decl_stmt|;
name|gint
name|num_fonts
decl_stmt|,
name|i
decl_stmt|;
name|fs
operator|->
name|font
operator|=
name|GTK_WIDGET
argument_list|(
name|fs
argument_list|)
operator|->
name|style
operator|->
name|font
expr_stmt|;
comment|/* get X font list and setup font names and styles */
comment|/* #define DEBUG_SPAM */
ifndef|#
directive|ifndef
name|DEBUG_SPAM
comment|/* FIXME: not only for "-*", do also "*"!!! */
name|xfontnames
operator|=
name|XListFonts
argument_list|(
name|GDK_DISPLAY
argument_list|()
argument_list|,
literal|"-*"
argument_list|,
name|MAX_FONTS
argument_list|,
operator|&
name|num_fonts
argument_list|)
expr_stmt|;
else|#
directive|else
block|{
name|FILE
modifier|*
name|f
decl_stmt|;
name|xfontnames
operator|=
name|g_new
argument_list|(
name|char
operator|*
argument_list|,
name|MAX_FONTS
argument_list|)
expr_stmt|;
name|f
operator|=
name|fopen
argument_list|(
literal|"spam_font.list"
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
name|f
operator|==
name|NULL
condition|)
block|{
name|puts
argument_list|(
literal|"Error opening font list"
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|num_fonts
operator|=
literal|0
init|;
operator|!
name|feof
argument_list|(
name|f
argument_list|)
condition|;
name|num_fonts
operator|++
control|)
block|{
name|xfontnames
index|[
name|num_fonts
index|]
operator|=
name|g_new0
argument_list|(
name|char
argument_list|,
literal|400
argument_list|)
expr_stmt|;
name|fscanf
argument_list|(
name|f
argument_list|,
literal|"%[^\n]\n"
argument_list|,
name|xfontnames
index|[
name|num_fonts
index|]
argument_list|)
expr_stmt|;
block|}
name|fclose
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"NF: %d\n"
argument_list|,
name|num_fonts
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
ifdef|#
directive|ifdef
name|DEBUG_SPAM
name|puts
argument_list|(
literal|"FontSelection: START"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* FIXME: optimize this stuff!!! */
if|if
condition|(
name|num_fonts
operator|==
name|MAX_FONTS
condition|)
name|g_warning
argument_list|(
name|_
argument_list|(
literal|"MAX_FONTS exceeded. Some fonts may be missing."
argument_list|)
argument_list|)
expr_stmt|;
name|fs
operator|->
name|font_properties
operator|=
name|g_hash_table_new
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
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
name|num_fonts
condition|;
name|i
operator|++
control|)
block|{
name|p
operator|=
name|fname
operator|=
name|strchr
argument_list|(
name|xfontnames
index|[
name|i
index|]
operator|+
literal|1
argument_list|,
literal|'-'
argument_list|)
operator|+
literal|1
expr_stmt|;
name|q
operator|=
name|strchr
argument_list|(
name|p
argument_list|,
literal|'-'
argument_list|)
expr_stmt|;
operator|*
name|q
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|l
operator|=
name|g_list_first
argument_list|(
name|fs
operator|->
name|font_names
argument_list|)
init|;
name|l
condition|;
name|l
operator|=
name|g_list_next
argument_list|(
name|l
argument_list|)
control|)
block|{
if|if
condition|(
name|g_str_equal
argument_list|(
operator|(
name|char
operator|*
operator|)
name|l
operator|->
name|data
argument_list|,
name|p
argument_list|)
condition|)
block|{
name|p
operator|=
name|NULL
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|p
operator|!=
name|NULL
condition|)
name|fs
operator|->
name|font_names
operator|=
name|g_list_insert_sorted
argument_list|(
name|fs
operator|->
name|font_names
argument_list|,
name|g_strdup
argument_list|(
name|p
argument_list|)
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|strcmp
argument_list|)
expr_stmt|;
name|p
operator|=
name|q
operator|+
literal|1
expr_stmt|;
name|q
operator|=
name|strchr
argument_list|(
name|p
argument_list|,
literal|'-'
argument_list|)
expr_stmt|;
name|q
operator|=
name|strchr
argument_list|(
operator|++
name|q
argument_list|,
literal|'-'
argument_list|)
expr_stmt|;
name|q
operator|=
name|strchr
argument_list|(
operator|++
name|q
argument_list|,
literal|'-'
argument_list|)
expr_stmt|;
operator|*
name|q
operator|=
literal|0
expr_stmt|;
name|plist
operator|=
operator|(
name|GList
operator|*
operator|)
name|g_hash_table_lookup
argument_list|(
name|fs
operator|->
name|font_properties
argument_list|,
name|fname
argument_list|)
expr_stmt|;
for|for
control|(
name|l
operator|=
name|g_list_first
argument_list|(
name|plist
argument_list|)
init|;
name|l
condition|;
name|l
operator|=
name|g_list_next
argument_list|(
name|l
argument_list|)
control|)
block|{
if|if
condition|(
name|g_str_equal
argument_list|(
operator|(
name|char
operator|*
operator|)
name|l
operator|->
name|data
argument_list|,
name|p
argument_list|)
condition|)
block|{
name|p
operator|=
name|NULL
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|p
operator|!=
name|NULL
condition|)
block|{
name|plist
operator|=
name|g_list_insert_sorted
argument_list|(
name|plist
argument_list|,
name|p
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|strcmp
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|fs
operator|->
name|font_properties
argument_list|,
name|fname
argument_list|,
name|g_list_first
argument_list|(
name|plist
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|xfontnames
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG_SPAM
name|puts
argument_list|(
literal|"FontSelection: DONE"
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|fs
operator|->
name|font_family
operator|=
name|gtk_combo_new
argument_list|()
expr_stmt|;
name|gtk_combo_set_popdown_strings
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_family
argument_list|)
argument_list|,
name|g_list_first
argument_list|(
name|fs
operator|->
name|font_names
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_entry_set_editable
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_family
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_combo_set_value_in_list
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_family
argument_list|)
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_family
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|,
literal|"changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|on_font_selection_family_changed
argument_list|)
argument_list|,
name|fs
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|fs
argument_list|)
argument_list|,
name|fs
operator|->
name|font_family
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|fs
operator|->
name|font_family
argument_list|)
expr_stmt|;
name|fs
operator|->
name|font_style
operator|=
name|gtk_combo_new
argument_list|()
expr_stmt|;
name|gtk_combo_set_popdown_strings
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_style
argument_list|)
argument_list|,
operator|(
name|GList
operator|*
operator|)
name|g_hash_table_lookup
argument_list|(
name|fs
operator|->
name|font_properties
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_family
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_entry_set_editable
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_style
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_style
argument_list|)
operator|->
name|entry
argument_list|,
literal|120
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_combo_set_value_in_list
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_family
argument_list|)
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_style
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|,
literal|"changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|on_font_selection_value_changed
argument_list|)
argument_list|,
name|fs
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|fs
argument_list|)
argument_list|,
name|fs
operator|->
name|font_style
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|fs
operator|->
name|font_style
argument_list|)
expr_stmt|;
name|font_size_adj
operator|=
name|gtk_adjustment_new
argument_list|(
literal|50
argument_list|,
literal|1
argument_list|,
literal|1000
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|fs
operator|->
name|font_size
operator|=
name|gtk_spin_button_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|font_size_adj
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|fs
operator|->
name|font_size
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_update_policy
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|fs
operator|->
name|font_size
argument_list|)
argument_list|,
name|GTK_UPDATE_ALWAYS
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|fs
operator|->
name|font_size
argument_list|)
argument_list|,
literal|50
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|fs
operator|->
name|font_size
argument_list|)
argument_list|,
literal|"changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|on_font_selection_value_changed
argument_list|)
argument_list|,
name|fs
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|fs
argument_list|)
argument_list|,
name|fs
operator|->
name|font_size
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|fs
operator|->
name|font_size
argument_list|)
expr_stmt|;
name|fs
operator|->
name|font_metric
operator|=
name|gtk_combo_new
argument_list|()
expr_stmt|;
name|font_metric_items
operator|=
name|g_list_append
argument_list|(
name|font_metric_items
argument_list|,
name|_
argument_list|(
literal|"pixels"
argument_list|)
argument_list|)
expr_stmt|;
name|font_metric_items
operator|=
name|g_list_append
argument_list|(
name|font_metric_items
argument_list|,
name|_
argument_list|(
literal|"points"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_combo_set_popdown_strings
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_metric
argument_list|)
argument_list|,
name|font_metric_items
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|font_metric_items
argument_list|)
expr_stmt|;
name|gtk_entry_set_editable
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_metric
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_metric
argument_list|)
operator|->
name|entry
argument_list|,
literal|40
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_combo_set_value_in_list
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_metric
argument_list|)
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_metric
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|,
literal|"changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|on_font_selection_value_changed
argument_list|)
argument_list|,
name|fs
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|fs
argument_list|)
argument_list|,
name|fs
operator|->
name|font_metric
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|fs
operator|->
name|font_metric
argument_list|)
expr_stmt|;
name|on_font_selection_family_changed
argument_list|(
name|NULL
argument_list|,
name|fs
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|font_selection_new (void)
name|GtkWidget
modifier|*
name|font_selection_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|GTK_WIDGET
argument_list|(
name|gtk_type_new
argument_list|(
name|font_selection_get_type
argument_list|()
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|on_font_selection_family_changed (GtkWidget * widget,gpointer data)
name|void
name|on_font_selection_family_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|FontSelection
modifier|*
name|fs
decl_stmt|;
name|fs
operator|=
operator|(
name|FontSelection
operator|*
operator|)
name|data
expr_stmt|;
name|gtk_combo_set_popdown_strings
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_style
argument_list|)
argument_list|,
operator|(
name|GList
operator|*
operator|)
name|g_hash_table_lookup
argument_list|(
name|fs
operator|->
name|font_properties
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_family
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|on_font_selection_value_changed
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|on_font_selection_value_changed (GtkWidget * widget,gpointer data)
name|void
name|on_font_selection_value_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GdkFont
modifier|*
name|font
decl_stmt|;
name|FontSelection
modifier|*
name|fs
decl_stmt|;
name|gchar
name|fontname
index|[
literal|8192
index|]
decl_stmt|;
name|fs
operator|=
operator|(
name|FontSelection
operator|*
operator|)
name|data
expr_stmt|;
comment|/* "-*-(fn)-(wg)-(sl)-(sp)-*-(px)-(po * 10)-*-*-*-*-*-*" */
if|if
condition|(
name|strcmp
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_metric
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"pixels"
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/* pixel size */
name|snprintf
argument_list|(
name|fontname
argument_list|,
sizeof|sizeof
argument_list|(
name|fontname
argument_list|)
argument_list|,
literal|"-*-%s-%s-*-%d-*-*-*-*-*-*-*"
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_family
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|)
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_style
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|)
argument_list|,
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|fs
operator|->
name|font_size
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* point size */
name|snprintf
argument_list|(
name|fontname
argument_list|,
sizeof|sizeof
argument_list|(
name|fontname
argument_list|)
argument_list|,
literal|"-*-%s-%s-*-*-%d-*-*-*-*-*-*"
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_family
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|)
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_style
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|)
argument_list|,
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|fs
operator|->
name|font_size
argument_list|)
argument_list|)
operator|*
literal|10
argument_list|)
expr_stmt|;
block|}
name|gtk_entry_set_position
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_family
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_entry_set_position
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_style
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_entry_set_position
argument_list|(
name|GTK_ENTRY
argument_list|(
operator|&
name|GTK_SPIN_BUTTON
argument_list|(
name|fs
operator|->
name|font_size
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_entry_set_position
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_metric
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gdk_error_warnings
operator|=
literal|0
expr_stmt|;
name|gdk_error_code
operator|=
literal|0
expr_stmt|;
name|font
operator|=
name|gdk_font_load
argument_list|(
name|fontname
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|font
operator|||
operator|(
name|gdk_error_code
operator|==
operator|-
literal|1
operator|)
condition|)
return|return;
name|fs
operator|->
name|font
operator|=
name|font
expr_stmt|;
comment|/* signal emit "font_changed" */
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
name|font_selection_signals
index|[
name|FONT_CHANGED
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|font_selection_set_font_family (FontSelection * fs,gchar * family)
name|void
name|font_selection_set_font_family
parameter_list|(
name|FontSelection
modifier|*
name|fs
parameter_list|,
name|gchar
modifier|*
name|family
parameter_list|)
block|{
if|if
condition|(
name|family
operator|==
name|NULL
operator|||
name|strlen
argument_list|(
name|family
argument_list|)
operator|==
literal|0
condition|)
return|return;
if|if
condition|(
name|g_hash_table_lookup
argument_list|(
name|fs
operator|->
name|font_properties
argument_list|,
name|family
argument_list|)
operator|==
name|NULL
condition|)
block|{
name|printf
argument_list|(
name|_
argument_list|(
literal|"Unknown font family \"%s\".\n"
argument_list|)
argument_list|,
name|family
argument_list|)
expr_stmt|;
return|return;
block|}
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_family
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|,
name|family
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|font_selection_set_font_style (FontSelection * fs,const gchar * style)
name|void
name|font_selection_set_font_style
parameter_list|(
name|FontSelection
modifier|*
name|fs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|style
parameter_list|)
block|{
name|GList
modifier|*
name|l
decl_stmt|;
name|gboolean
name|exists
init|=
name|FALSE
decl_stmt|;
name|gchar
modifier|*
name|family
decl_stmt|;
if|if
condition|(
name|style
operator|==
name|NULL
operator|||
name|strlen
argument_list|(
name|style
argument_list|)
operator|==
literal|0
condition|)
return|return;
name|family
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_family
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|)
expr_stmt|;
name|l
operator|=
name|g_hash_table_lookup
argument_list|(
name|fs
operator|->
name|font_properties
argument_list|,
name|family
argument_list|)
expr_stmt|;
while|while
condition|(
name|l
operator|&&
operator|!
name|exists
condition|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
operator|(
name|char
operator|*
operator|)
name|l
operator|->
name|data
argument_list|,
name|style
argument_list|)
operator|==
literal|0
condition|)
name|exists
operator|=
name|TRUE
expr_stmt|;
name|l
operator|=
name|l
operator|->
name|next
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|exists
condition|)
block|{
name|printf
argument_list|(
name|_
argument_list|(
literal|"Unknown font style \"%s\" for family \"%s\".\n"
argument_list|)
argument_list|,
name|style
argument_list|,
name|family
argument_list|)
expr_stmt|;
return|return;
block|}
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_style
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|,
name|style
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|font_selection_set_font_size (FontSelection * fs,const gint size)
name|void
name|font_selection_set_font_size
parameter_list|(
name|FontSelection
modifier|*
name|fs
parameter_list|,
specifier|const
name|gint
name|size
parameter_list|)
block|{
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|fs
operator|->
name|font_size
argument_list|)
argument_list|,
name|size
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|font_selection_set_font_metric (FontSelection * fs,FontMetricType fm)
name|void
name|font_selection_set_font_metric
parameter_list|(
name|FontSelection
modifier|*
name|fs
parameter_list|,
name|FontMetricType
name|fm
parameter_list|)
block|{
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_metric
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|,
name|fm
operator|==
name|FONT_METRIC_PIXELS
condition|?
name|_
argument_list|(
literal|"pixels"
argument_list|)
else|:
name|_
argument_list|(
literal|"points"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|font_selection_get_font_family (FontSelection * fs)
name|gchar
modifier|*
name|font_selection_get_font_family
parameter_list|(
name|FontSelection
modifier|*
name|fs
parameter_list|)
block|{
return|return
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_family
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|font_selection_get_font_style (FontSelection * fs)
name|gchar
modifier|*
name|font_selection_get_font_style
parameter_list|(
name|FontSelection
modifier|*
name|fs
parameter_list|)
block|{
return|return
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_style
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|font_selection_get_font_size (FontSelection * fs)
name|gint
name|font_selection_get_font_size
parameter_list|(
name|FontSelection
modifier|*
name|fs
parameter_list|)
block|{
return|return
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|fs
operator|->
name|font_size
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|font_selection_get_font_metric (FontSelection * fs)
name|FontMetricType
name|font_selection_get_font_metric
parameter_list|(
name|FontSelection
modifier|*
name|fs
parameter_list|)
block|{
return|return
name|strcmp
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|GTK_COMBO
argument_list|(
name|fs
operator|->
name|font_metric
argument_list|)
operator|->
name|entry
argument_list|)
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"pixels"
argument_list|)
argument_list|)
operator|==
literal|0
condition|?
name|FONT_METRIC_PIXELS
else|:
name|FONT_METRIC_POINTS
return|;
block|}
end_function

begin_comment
comment|/* vim: set ts=2 sw=2 tw=79 ai nowrap: */
end_comment

end_unit

