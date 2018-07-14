begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmemsizeentry.c  * Copyright (C) 2000-2003  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpmemsizeentry.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimpmemsizeentry  * @title: GimpMemSizeEntry  * @short_description: A composite widget to enter a memory size.  *  * Similar to a #GimpSizeEntry but instead of lengths, this widget is  * used to let the user enter memory sizes. A combo box allows one to  * switch between Kilobytes, Megabytes and Gigabytes. Used in the GIMP  * preferences dialog.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2a2b102f0103
block|{
DECL|enumerator|VALUE_CHANGED
name|VALUE_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpMemsizeEntryPrivate
struct|struct
name|_GimpMemsizeEntryPrivate
block|{
DECL|member|value
name|guint64
name|value
decl_stmt|;
DECL|member|lower
name|guint64
name|lower
decl_stmt|;
DECL|member|upper
name|guint64
name|upper
decl_stmt|;
DECL|member|shift
name|guint
name|shift
decl_stmt|;
comment|/* adjustment is owned by spinbutton. Do not unref() it. */
DECL|member|adjustment
name|GtkAdjustment
modifier|*
name|adjustment
decl_stmt|;
DECL|member|spinbutton
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
DECL|member|menu
name|GtkWidget
modifier|*
name|menu
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
value|(((GimpMemsizeEntry *) (obj))->priv)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_memsize_entry_adj_callback
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpMemsizeEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_memsize_entry_unit_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpMemsizeEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpMemsizeEntry
argument_list|,
argument|gimp_memsize_entry
argument_list|,
argument|GTK_TYPE_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_memsize_entry_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|gimp_memsize_entry_signals
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
DECL|function|gimp_memsize_entry_class_init (GimpMemsizeEntryClass * klass)
name|gimp_memsize_entry_class_init
parameter_list|(
name|GimpMemsizeEntryClass
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
name|klass
operator|->
name|value_changed
operator|=
name|NULL
expr_stmt|;
name|gimp_memsize_entry_signals
index|[
name|VALUE_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"value-changed"
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
name|GimpMemsizeEntryClass
argument_list|,
name|value_changed
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
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpMemsizeEntryPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_memsize_entry_init (GimpMemsizeEntry * entry)
name|gimp_memsize_entry_init
parameter_list|(
name|GimpMemsizeEntry
modifier|*
name|entry
parameter_list|)
block|{
name|entry
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|entry
argument_list|,
name|GIMP_TYPE_MEMSIZE_ENTRY
argument_list|,
name|GimpMemsizeEntryPrivate
argument_list|)
expr_stmt|;
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
name|GTK_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_memsize_entry_adj_callback (GtkAdjustment * adj,GimpMemsizeEntry * entry)
name|gimp_memsize_entry_adj_callback
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpMemsizeEntry
modifier|*
name|entry
parameter_list|)
block|{
name|GimpMemsizeEntryPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|entry
argument_list|)
decl_stmt|;
name|guint64
name|size
init|=
name|gtk_adjustment_get_value
argument_list|(
name|adj
argument_list|)
decl_stmt|;
name|private
operator|->
name|value
operator|=
name|size
operator|<<
name|private
operator|->
name|shift
expr_stmt|;
name|g_signal_emit
argument_list|(
name|entry
argument_list|,
name|gimp_memsize_entry_signals
index|[
name|VALUE_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_memsize_entry_unit_callback (GtkWidget * widget,GimpMemsizeEntry * entry)
name|gimp_memsize_entry_unit_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpMemsizeEntry
modifier|*
name|entry
parameter_list|)
block|{
name|GimpMemsizeEntryPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|entry
argument_list|)
decl_stmt|;
name|guint
name|shift
decl_stmt|;
name|gimp_int_combo_box_get_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|(
name|gint
operator|*
operator|)
operator|&
name|shift
argument_list|)
expr_stmt|;
if|#
directive|if
name|_MSC_VER
operator|<
literal|1300
DECL|macro|CAST
define|#
directive|define
name|CAST
value|(gint64)
else|#
directive|else
DECL|macro|CAST
define|#
directive|define
name|CAST
endif|#
directive|endif
if|if
condition|(
name|shift
operator|!=
name|private
operator|->
name|shift
condition|)
block|{
name|private
operator|->
name|shift
operator|=
name|shift
expr_stmt|;
name|gtk_adjustment_configure
argument_list|(
argument|private->adjustment
argument_list|,
argument|CAST private->value>> shift
argument_list|,
argument|CAST private->lower>> shift
argument_list|,
argument|CAST private->upper>> shift
argument_list|,
argument|gtk_adjustment_get_step_increment (private->adjustment)
argument_list|,
argument|gtk_adjustment_get_page_increment (private->adjustment)
argument_list|,
argument|gtk_adjustment_get_page_size (private->adjustment)
argument_list|)
empty_stmt|;
block|}
undef|#
directive|undef
name|CAST
block|}
end_function

begin_comment
comment|/**  * gimp_memsize_entry_new:  * @value: the initial value (in Bytes)  * @lower: the lower limit for the value (in Bytes)  * @upper: the upper limit for the value (in Bytes)  *  * Creates a new #GimpMemsizeEntry which is a #GtkHBox with a #GtkSpinButton  * and a #GtkOptionMenu all setup to allow the user to enter memory sizes.  *  * Returns: Pointer to the new #GimpMemsizeEntry.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_memsize_entry_new (guint64 value,guint64 lower,guint64 upper)
name|gimp_memsize_entry_new
parameter_list|(
name|guint64
name|value
parameter_list|,
name|guint64
name|lower
parameter_list|,
name|guint64
name|upper
parameter_list|)
block|{
name|GimpMemsizeEntry
modifier|*
name|entry
decl_stmt|;
name|GimpMemsizeEntryPrivate
modifier|*
name|private
decl_stmt|;
name|guint
name|shift
decl_stmt|;
if|#
directive|if
name|_MSC_VER
operator|<
literal|1300
DECL|macro|CAST
define|#
directive|define
name|CAST
value|(gint64)
else|#
directive|else
DECL|macro|CAST
define|#
directive|define
name|CAST
endif|#
directive|endif
name|g_return_val_if_fail
argument_list|(
name|value
operator|>=
name|lower
operator|&&
name|value
operator|<=
name|upper
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|entry
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_MEMSIZE_ENTRY
argument_list|,
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
for|for
control|(
name|shift
operator|=
literal|30
init|;
name|shift
operator|>
literal|10
condition|;
name|shift
operator|-=
literal|10
control|)
block|{
if|if
condition|(
name|value
operator|>
operator|(
name|G_GUINT64_CONSTANT
argument_list|(
literal|1
argument_list|)
operator|<<
name|shift
operator|)
operator|&&
name|value
operator|%
operator|(
name|G_GUINT64_CONSTANT
argument_list|(
literal|1
argument_list|)
operator|<<
name|shift
operator|)
operator|==
literal|0
condition|)
break|break;
block|}
name|private
operator|->
name|value
operator|=
name|value
expr_stmt|;
name|private
operator|->
name|lower
operator|=
name|lower
expr_stmt|;
name|private
operator|->
name|upper
operator|=
name|upper
expr_stmt|;
name|private
operator|->
name|shift
operator|=
name|shift
expr_stmt|;
name|private
operator|->
name|adjustment
operator|=
name|gtk_adjustment_new
argument_list|(
name|CAST
argument_list|(
name|value
operator|>>
name|shift
argument_list|)
argument_list|,
name|CAST
argument_list|(
name|lower
operator|>>
name|shift
argument_list|)
argument_list|,
name|CAST
argument_list|(
name|upper
operator|>>
name|shift
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|8
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|private
operator|->
name|spinbutton
operator|=
name|gtk_spin_button_new
argument_list|(
name|private
operator|->
name|adjustment
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|private
operator|->
name|spinbutton
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|CAST
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|private
operator|->
name|spinbutton
argument_list|)
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|entry
argument_list|)
argument_list|,
name|private
operator|->
name|spinbutton
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
name|private
operator|->
name|spinbutton
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|private
operator|->
name|adjustment
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_memsize_entry_adj_callback
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|private
operator|->
name|menu
operator|=
name|gimp_int_combo_box_new
argument_list|(
name|_
argument_list|(
literal|"Kilobytes"
argument_list|)
argument_list|,
literal|10
argument_list|,
name|_
argument_list|(
literal|"Megabytes"
argument_list|)
argument_list|,
literal|20
argument_list|,
name|_
argument_list|(
literal|"Gigabytes"
argument_list|)
argument_list|,
literal|30
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|private
operator|->
name|menu
argument_list|)
argument_list|,
name|shift
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|private
operator|->
name|menu
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_memsize_entry_unit_callback
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|entry
argument_list|)
argument_list|,
name|private
operator|->
name|menu
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
name|private
operator|->
name|menu
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|entry
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_memsize_entry_set_value:  * @entry: a #GimpMemsizeEntry  * @value: the new value (in Bytes)  *  * Sets the @entry's value. Please note that the #GimpMemsizeEntry rounds  * the value to full Kilobytes.  **/
end_comment

begin_function
name|void
DECL|function|gimp_memsize_entry_set_value (GimpMemsizeEntry * entry,guint64 value)
name|gimp_memsize_entry_set_value
parameter_list|(
name|GimpMemsizeEntry
modifier|*
name|entry
parameter_list|,
name|guint64
name|value
parameter_list|)
block|{
name|GimpMemsizeEntryPrivate
modifier|*
name|private
decl_stmt|;
name|guint
name|shift
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MEMSIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|value
operator|>=
name|private
operator|->
name|lower
operator|&&
name|value
operator|<=
name|private
operator|->
name|upper
argument_list|)
expr_stmt|;
for|for
control|(
name|shift
operator|=
literal|30
init|;
name|shift
operator|>
literal|10
condition|;
name|shift
operator|-=
literal|10
control|)
block|{
if|if
condition|(
name|value
operator|>
operator|(
name|G_GUINT64_CONSTANT
argument_list|(
literal|1
argument_list|)
operator|<<
name|shift
operator|)
operator|&&
name|value
operator|%
operator|(
name|G_GUINT64_CONSTANT
argument_list|(
literal|1
argument_list|)
operator|<<
name|shift
operator|)
operator|==
literal|0
condition|)
break|break;
block|}
if|if
condition|(
name|shift
operator|!=
name|private
operator|->
name|shift
condition|)
block|{
name|private
operator|->
name|shift
operator|=
name|shift
expr_stmt|;
name|private
operator|->
name|value
operator|=
name|value
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|private
operator|->
name|menu
argument_list|)
argument_list|,
name|shift
argument_list|)
expr_stmt|;
block|}
if|#
directive|if
name|_MSC_VER
operator|<
literal|1300
DECL|macro|CAST
define|#
directive|define
name|CAST
value|(gint64)
else|#
directive|else
DECL|macro|CAST
define|#
directive|define
name|CAST
endif|#
directive|endif
name|gtk_adjustment_set_value
argument_list|(
name|private
operator|->
name|adjustment
argument_list|,
name|CAST
argument_list|(
name|value
operator|>>
name|shift
argument_list|)
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|CASE
block|}
end_function

begin_comment
comment|/**  * gimp_memsize_entry_get_value:  * @entry: a #GimpMemsizeEntry  *  * Retrieves the current value from a #GimpMemsizeEntry.  *  * Returns: the current value of @entry (in Bytes).  **/
end_comment

begin_function
name|guint64
DECL|function|gimp_memsize_entry_get_value (GimpMemsizeEntry * entry)
name|gimp_memsize_entry_get_value
parameter_list|(
name|GimpMemsizeEntry
modifier|*
name|entry
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MEMSIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|entry
argument_list|)
operator|->
name|value
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_memsize_entry_get_spinbutton:  * @entry: a #GimpMemsizeEntry  *  * Returns: the entry's #GtkSpinbutton.  *  * Since: GIMP 3.0  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_memsize_entry_get_spinbutton (GimpMemsizeEntry * entry)
name|gimp_memsize_entry_get_spinbutton
parameter_list|(
name|GimpMemsizeEntry
modifier|*
name|entry
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MEMSIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|entry
argument_list|)
operator|->
name|spinbutton
return|;
block|}
end_function

end_unit

