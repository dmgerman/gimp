begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpscalecombobox.c  * Copyright (C) 2004, 2008  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"stdlib.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gdk/gdkkeysyms.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpscalecombobox.h"
end_include

begin_define
DECL|macro|MAX_ITEMS
define|#
directive|define
name|MAX_ITEMS
value|10
end_define

begin_enum
enum|enum
DECL|enum|__anon29590b140103
block|{
DECL|enumerator|COLUMN_SCALE
name|COLUMN_SCALE
block|,
DECL|enumerator|COLUMN_LABEL
name|COLUMN_LABEL
block|,
DECL|enumerator|COLUMN_PERSISTENT
name|COLUMN_PERSISTENT
block|,
DECL|enumerator|N_COLUMNS
name|N_COLUMNS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon29590b140203
block|{
DECL|enumerator|ENTRY_ACTIVATED
name|ENTRY_ACTIVATED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_scale_combo_box_finalize
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
name|gimp_scale_combo_box_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_scale_combo_box_changed
parameter_list|(
name|GimpScaleComboBox
modifier|*
name|combo_box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_scale_combo_box_entry_activate
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|GimpScaleComboBox
modifier|*
name|combo_box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_scale_combo_box_entry_key_press
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|GdkEventKey
modifier|*
name|event
parameter_list|,
name|GimpScaleComboBox
modifier|*
name|combo_box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_scale_combo_box_scale_iter_set
parameter_list|(
name|GtkListStore
modifier|*
name|store
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gboolean
name|persistent
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpScaleComboBox
argument_list|,
argument|gimp_scale_combo_box
argument_list|,
argument|GTK_TYPE_COMBO_BOX_ENTRY
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_scale_combo_box_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|scale_combo_box_signals
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
DECL|function|gimp_scale_combo_box_class_init (GimpScaleComboBoxClass * klass)
name|gimp_scale_combo_box_class_init
parameter_list|(
name|GimpScaleComboBoxClass
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
name|scale_combo_box_signals
index|[
name|ENTRY_ACTIVATED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"entry-activated"
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
name|GimpScaleComboBoxClass
argument_list|,
name|entry_activated
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_scale_combo_box_finalize
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_scale_combo_box_style_set
expr_stmt|;
name|klass
operator|->
name|entry_activated
operator|=
name|NULL
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"label-scale"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
name|G_MAXDOUBLE
argument_list|,
literal|1.0
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
DECL|function|gimp_scale_combo_box_init (GimpScaleComboBox * combo_box)
name|gimp_scale_combo_box_init
parameter_list|(
name|GimpScaleComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GtkCellLayout
modifier|*
name|layout
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|GtkBorder
name|border
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|combo_box
operator|->
name|scale
operator|=
literal|1.0
expr_stmt|;
name|combo_box
operator|->
name|last_path
operator|=
name|NULL
expr_stmt|;
name|store
operator|=
name|gtk_list_store_new
argument_list|(
name|N_COLUMNS
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
comment|/* SCALE       */
name|G_TYPE_STRING
argument_list|,
comment|/* LABEL       */
name|G_TYPE_BOOLEAN
argument_list|)
expr_stmt|;
comment|/* PERSISTENT  */
name|gtk_combo_box_set_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|gtk_combo_box_entry_set_text_column
argument_list|(
name|GTK_COMBO_BOX_ENTRY
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|COLUMN_LABEL
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|entry
argument_list|,
literal|"xalign"
argument_list|,
literal|1.0
argument_list|,
literal|"width-chars"
argument_list|,
literal|7
argument_list|,
literal|"truncate-multiline"
argument_list|,
name|TRUE
argument_list|,
literal|"inner-border"
argument_list|,
operator|&
name|border
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|layout
operator|=
name|GTK_CELL_LAYOUT
argument_list|(
name|combo_box
argument_list|)
expr_stmt|;
name|cell
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_CELL_RENDERER_TEXT
argument_list|,
literal|"xalign"
argument_list|,
literal|1.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_cell_layout_clear
argument_list|(
name|layout
argument_list|)
expr_stmt|;
name|gtk_cell_layout_pack_start
argument_list|(
name|layout
argument_list|,
name|cell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_cell_layout_set_attributes
argument_list|(
name|layout
argument_list|,
name|cell
argument_list|,
literal|"text"
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|8
init|;
name|i
operator|>
literal|0
condition|;
name|i
operator|/=
literal|2
control|)
block|{
name|gtk_list_store_append
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gimp_scale_combo_box_scale_iter_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|i
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|2
init|;
name|i
operator|<=
literal|8
condition|;
name|i
operator|*=
literal|2
control|)
block|{
name|gtk_list_store_append
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gimp_scale_combo_box_scale_iter_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
literal|1.0
operator|/
name|i
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|g_signal_connect
argument_list|(
name|combo_box
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_scale_combo_box_changed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
argument_list|,
literal|"activate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_scale_combo_box_entry_activate
argument_list|)
argument_list|,
name|combo_box
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
name|gimp_scale_combo_box_entry_key_press
argument_list|)
argument_list|,
name|combo_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_combo_box_finalize (GObject * object)
name|gimp_scale_combo_box_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpScaleComboBox
modifier|*
name|combo_box
init|=
name|GIMP_SCALE_COMBO_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|combo_box
operator|->
name|last_path
condition|)
block|{
name|gtk_tree_path_free
argument_list|(
name|combo_box
operator|->
name|last_path
argument_list|)
expr_stmt|;
name|combo_box
operator|->
name|last_path
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|combo_box
operator|->
name|mru
condition|)
block|{
name|g_list_free_full
argument_list|(
name|combo_box
operator|->
name|mru
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gtk_tree_row_reference_free
argument_list|)
expr_stmt|;
name|combo_box
operator|->
name|mru
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
DECL|function|gimp_scale_combo_box_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_scale_combo_box_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|GtkRcStyle
modifier|*
name|rc_style
decl_stmt|;
name|gint
name|font_size
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
argument_list|(
name|widget
argument_list|,
name|prev_style
argument_list|)
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"label-scale"
argument_list|,
operator|&
name|scale
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|rc_style
operator|=
name|gtk_widget_get_modifier_style
argument_list|(
name|GTK_WIDGET
argument_list|(
name|entry
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|rc_style
operator|->
name|font_desc
condition|)
block|{
name|PangoContext
modifier|*
name|context
decl_stmt|;
name|PangoFontDescription
modifier|*
name|font_desc
decl_stmt|;
name|context
operator|=
name|gtk_widget_get_pango_context
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|font_desc
operator|=
name|pango_context_get_font_description
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|rc_style
operator|->
name|font_desc
operator|=
name|pango_font_description_copy
argument_list|(
name|font_desc
argument_list|)
expr_stmt|;
block|}
name|font_size
operator|=
name|pango_font_description_get_size
argument_list|(
name|rc_style
operator|->
name|font_desc
argument_list|)
expr_stmt|;
name|pango_font_description_set_size
argument_list|(
name|rc_style
operator|->
name|font_desc
argument_list|,
name|scale
operator|*
name|font_size
argument_list|)
expr_stmt|;
name|gtk_widget_modify_style
argument_list|(
name|GTK_WIDGET
argument_list|(
name|entry
argument_list|)
argument_list|,
name|rc_style
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_combo_box_changed (GimpScaleComboBox * combo_box)
name|gimp_scale_combo_box_changed
parameter_list|(
name|GimpScaleComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
name|gtk_combo_box_get_active_iter
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_SCALE
argument_list|,
operator|&
name|scale
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|scale
operator|>
literal|0.0
condition|)
block|{
name|combo_box
operator|->
name|scale
operator|=
name|scale
expr_stmt|;
if|if
condition|(
name|combo_box
operator|->
name|last_path
condition|)
name|gtk_tree_path_free
argument_list|(
name|combo_box
operator|->
name|last_path
argument_list|)
expr_stmt|;
name|combo_box
operator|->
name|last_path
operator|=
name|gtk_tree_model_get_path
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_scale_combo_box_parse_text (const gchar * text,gdouble * scale)
name|gimp_scale_combo_box_parse_text
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gdouble
modifier|*
name|scale
parameter_list|)
block|{
name|gchar
modifier|*
name|end
decl_stmt|;
name|gdouble
name|left_number
decl_stmt|;
name|gdouble
name|right_number
decl_stmt|;
comment|/* try to parse a number */
name|left_number
operator|=
name|strtod
argument_list|(
name|text
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|==
name|text
condition|)
return|return
name|FALSE
return|;
else|else
name|text
operator|=
name|end
expr_stmt|;
comment|/* skip over whitespace */
while|while
condition|(
name|g_unichar_isspace
argument_list|(
name|g_utf8_get_char
argument_list|(
name|text
argument_list|)
argument_list|)
condition|)
name|text
operator|=
name|g_utf8_next_char
argument_list|(
name|text
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|text
operator|==
literal|'\0'
operator|||
operator|*
name|text
operator|==
literal|'%'
condition|)
block|{
operator|*
name|scale
operator|=
name|left_number
operator|/
literal|100.0
expr_stmt|;
return|return
name|TRUE
return|;
block|}
comment|/* check for a valid separator */
if|if
condition|(
operator|*
name|text
operator|!=
literal|'/'
operator|&&
operator|*
name|text
operator|!=
literal|':'
condition|)
block|{
operator|*
name|scale
operator|=
name|left_number
expr_stmt|;
return|return
name|TRUE
return|;
block|}
name|text
operator|=
name|g_utf8_next_char
argument_list|(
name|text
argument_list|)
expr_stmt|;
comment|/* skip over whitespace */
while|while
condition|(
name|g_unichar_isspace
argument_list|(
name|g_utf8_get_char
argument_list|(
name|text
argument_list|)
argument_list|)
condition|)
name|text
operator|=
name|g_utf8_next_char
argument_list|(
name|text
argument_list|)
expr_stmt|;
comment|/* try to parse another number */
name|right_number
operator|=
name|strtod
argument_list|(
name|text
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|==
name|text
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|right_number
operator|==
literal|0.0
condition|)
return|return
name|FALSE
return|;
operator|*
name|scale
operator|=
name|left_number
operator|/
name|right_number
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_combo_box_entry_activate (GtkWidget * entry,GimpScaleComboBox * combo_box)
name|gimp_scale_combo_box_entry_activate
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|GimpScaleComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|text
init|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|)
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
if|if
condition|(
name|gimp_scale_combo_box_parse_text
argument_list|(
name|text
argument_list|,
operator|&
name|scale
argument_list|)
operator|&&
name|scale
operator|>=
literal|1.0
operator|/
literal|256.0
operator|&&
name|scale
operator|<=
literal|256.0
condition|)
block|{
name|gimp_scale_combo_box_set_scale
argument_list|(
name|combo_box
argument_list|,
name|scale
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_error_bell
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|gimp_scale_combo_box_set_scale
argument_list|(
name|combo_box
argument_list|,
name|combo_box
operator|->
name|scale
argument_list|)
expr_stmt|;
block|}
name|g_signal_emit
argument_list|(
name|combo_box
argument_list|,
name|scale_combo_box_signals
index|[
name|ENTRY_ACTIVATED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_scale_combo_box_entry_key_press (GtkWidget * entry,GdkEventKey * event,GimpScaleComboBox * combo_box)
name|gimp_scale_combo_box_entry_key_press
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|GdkEventKey
modifier|*
name|event
parameter_list|,
name|GimpScaleComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
if|if
condition|(
name|event
operator|->
name|keyval
operator|==
name|GDK_Escape
condition|)
block|{
name|gimp_scale_combo_box_set_scale
argument_list|(
name|combo_box
argument_list|,
name|combo_box
operator|->
name|scale
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|combo_box
argument_list|,
name|scale_combo_box_signals
index|[
name|ENTRY_ACTIVATED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|event
operator|->
name|keyval
operator|==
name|GDK_Tab
operator|||
name|event
operator|->
name|keyval
operator|==
name|GDK_KP_Tab
operator|||
name|event
operator|->
name|keyval
operator|==
name|GDK_ISO_Left_Tab
condition|)
block|{
name|gimp_scale_combo_box_entry_activate
argument_list|(
name|entry
argument_list|,
name|combo_box
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_combo_box_scale_iter_set (GtkListStore * store,GtkTreeIter * iter,gdouble scale,gboolean persistent)
name|gimp_scale_combo_box_scale_iter_set
parameter_list|(
name|GtkListStore
modifier|*
name|store
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gboolean
name|persistent
parameter_list|)
block|{
name|gchar
name|label
index|[
literal|32
index|]
decl_stmt|;
comment|/*  use U+2009 THIN SPACE to seperate the percent sign from the number */
if|if
condition|(
name|scale
operator|>
literal|1.0
condition|)
name|g_snprintf
argument_list|(
name|label
argument_list|,
sizeof|sizeof
argument_list|(
name|label
argument_list|)
argument_list|,
literal|"%d\342\200\211%%"
argument_list|,
operator|(
name|gint
operator|)
name|ROUND
argument_list|(
literal|100.0
operator|*
name|scale
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|g_snprintf
argument_list|(
name|label
argument_list|,
sizeof|sizeof
argument_list|(
name|label
argument_list|)
argument_list|,
literal|"%.3g\342\200\211%%"
argument_list|,
literal|100.0
operator|*
name|scale
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|store
argument_list|,
name|iter
argument_list|,
name|COLUMN_SCALE
argument_list|,
name|scale
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|label
argument_list|,
name|COLUMN_PERSISTENT
argument_list|,
name|persistent
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_combo_box_mru_add (GimpScaleComboBox * combo_box,GtkTreeIter * iter)
name|gimp_scale_combo_box_mru_add
parameter_list|(
name|GimpScaleComboBox
modifier|*
name|combo_box
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
decl_stmt|;
name|GtkTreePath
modifier|*
name|path
init|=
name|gtk_tree_model_get_path
argument_list|(
name|model
argument_list|,
name|iter
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gboolean
name|found
decl_stmt|;
for|for
control|(
name|list
operator|=
name|combo_box
operator|->
name|mru
operator|,
name|found
operator|=
name|FALSE
init|;
name|list
operator|&&
operator|!
name|found
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|GtkTreePath
modifier|*
name|this
init|=
name|gtk_tree_row_reference_get_path
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|gtk_tree_path_compare
argument_list|(
name|this
argument_list|,
name|path
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|list
operator|->
name|prev
condition|)
block|{
name|combo_box
operator|->
name|mru
operator|=
name|g_list_remove_link
argument_list|(
name|combo_box
operator|->
name|mru
argument_list|,
name|list
argument_list|)
expr_stmt|;
name|combo_box
operator|->
name|mru
operator|=
name|g_list_concat
argument_list|(
name|list
argument_list|,
name|combo_box
operator|->
name|mru
argument_list|)
expr_stmt|;
block|}
name|found
operator|=
name|TRUE
expr_stmt|;
block|}
name|gtk_tree_path_free
argument_list|(
name|this
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|found
condition|)
name|combo_box
operator|->
name|mru
operator|=
name|g_list_prepend
argument_list|(
name|combo_box
operator|->
name|mru
argument_list|,
name|gtk_tree_row_reference_new
argument_list|(
name|model
argument_list|,
name|path
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_scale_combo_box_mru_remove_last (GimpScaleComboBox * combo_box)
name|gimp_scale_combo_box_mru_remove_last
parameter_list|(
name|GimpScaleComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|GList
modifier|*
name|last
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
operator|!
name|combo_box
operator|->
name|mru
condition|)
return|return;
name|model
operator|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
name|last
operator|=
name|g_list_last
argument_list|(
name|combo_box
operator|->
name|mru
argument_list|)
expr_stmt|;
name|path
operator|=
name|gtk_tree_row_reference_get_path
argument_list|(
name|last
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|path
argument_list|)
condition|)
block|{
name|gtk_list_store_remove
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_row_reference_free
argument_list|(
name|last
operator|->
name|data
argument_list|)
expr_stmt|;
name|combo_box
operator|->
name|mru
operator|=
name|g_list_delete_link
argument_list|(
name|combo_box
operator|->
name|mru
argument_list|,
name|last
argument_list|)
expr_stmt|;
block|}
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_scale_combo_box_new:  *  * Return value: a new #GimpScaleComboBox.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_scale_combo_box_new (void)
name|gimp_scale_combo_box_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_SCALE_COMBO_BOX
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_scale_combo_box_set_scale (GimpScaleComboBox * combo_box,gdouble scale)
name|gimp_scale_combo_box_set_scale
parameter_list|(
name|GimpScaleComboBox
modifier|*
name|combo_box
parameter_list|,
name|gdouble
name|scale
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
name|gboolean
name|persistent
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SCALE_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|scale
operator|>
literal|0.0
argument_list|)
expr_stmt|;
name|model
operator|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
name|store
operator|=
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
expr_stmt|;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
control|)
block|{
name|gdouble
name|this
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_SCALE
argument_list|,
operator|&
name|this
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|fabs
argument_list|(
name|this
operator|-
name|scale
argument_list|)
operator|<
literal|0.0001
condition|)
break|break;
block|}
if|if
condition|(
operator|!
name|iter_valid
condition|)
block|{
name|GtkTreeIter
name|sibling
decl_stmt|;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
operator|&
name|sibling
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
operator|&
name|sibling
argument_list|)
control|)
block|{
name|gdouble
name|this
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|sibling
argument_list|,
name|COLUMN_SCALE
argument_list|,
operator|&
name|this
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|this
operator|<
name|scale
condition|)
break|break;
block|}
name|gtk_list_store_insert_before
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|iter_valid
condition|?
operator|&
name|sibling
else|:
name|NULL
argument_list|)
expr_stmt|;
name|gimp_scale_combo_box_scale_iter_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|scale
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|gtk_combo_box_set_active_iter
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_PERSISTENT
argument_list|,
operator|&
name|persistent
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|persistent
condition|)
block|{
name|gimp_scale_combo_box_mru_add
argument_list|(
name|combo_box
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_iter_n_children
argument_list|(
name|model
argument_list|,
name|NULL
argument_list|)
operator|>
name|MAX_ITEMS
condition|)
name|gimp_scale_combo_box_mru_remove_last
argument_list|(
name|combo_box
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_scale_combo_box_get_scale (GimpScaleComboBox * combo_box)
name|gimp_scale_combo_box_get_scale
parameter_list|(
name|GimpScaleComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_SCALE_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|combo_box
operator|->
name|scale
return|;
block|}
end_function

end_unit

