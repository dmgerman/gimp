begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmemsizeentry.c  * Copyright (C) 2000-2003  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_enum
enum|enum
DECL|enum|__anon27aa2edd0103
block|{
DECL|enumerator|VALUE_CHANGED
name|VALUE_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_memsize_entry_class_init
parameter_list|(
name|GimpMemsizeEntryClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_memsize_entry_init
parameter_list|(
name|GimpMemsizeEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_memsize_entry_finalize
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

begin_decl_stmt
DECL|variable|gimp_memsize_entry_signals
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkHBoxClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_memsize_entry_get_type (void)
name|gimp_memsize_entry_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|entry_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|entry_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|entry_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpMemsizeEntryClass
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
name|gimp_memsize_entry_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpMemsizeEntry
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_memsize_entry_init
block|,       }
decl_stmt|;
name|entry_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_HBOX
argument_list|,
literal|"GimpMemsizeEntry"
argument_list|,
operator|&
name|entry_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|entry_type
return|;
block|}
end_function

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
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_memsize_entry_finalize
expr_stmt|;
name|gimp_memsize_entry_signals
index|[
name|VALUE_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"value_changed"
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
name|klass
operator|->
name|value_changed
operator|=
name|NULL
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
name|entry
operator|->
name|value
operator|=
literal|0
expr_stmt|;
name|entry
operator|->
name|lower
operator|=
literal|0
expr_stmt|;
name|entry
operator|->
name|upper
operator|=
literal|0
expr_stmt|;
name|entry
operator|->
name|shift
operator|=
literal|0
expr_stmt|;
name|entry
operator|->
name|adjustment
operator|=
name|NULL
expr_stmt|;
name|entry
operator|->
name|menu
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_memsize_entry_finalize (GObject * object)
name|gimp_memsize_entry_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpMemsizeEntry
modifier|*
name|entry
init|=
operator|(
name|GimpMemsizeEntry
operator|*
operator|)
name|object
decl_stmt|;
if|if
condition|(
name|entry
operator|->
name|adjustment
condition|)
block|{
name|g_object_unref
argument_list|(
name|entry
operator|->
name|adjustment
argument_list|)
expr_stmt|;
name|entry
operator|->
name|adjustment
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
name|guint64
name|size
init|=
name|gtk_adjustment_get_value
argument_list|(
name|adj
argument_list|)
decl_stmt|;
name|entry
operator|->
name|value
operator|=
name|size
operator|<<
name|entry
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
name|entry
operator|->
name|shift
condition|)
block|{
name|entry
operator|->
name|shift
operator|=
name|shift
expr_stmt|;
name|entry
operator|->
name|adjustment
operator|->
name|value
operator|=
name|CAST
name|entry
operator|->
name|value
operator|>>
name|shift
expr_stmt|;
name|entry
operator|->
name|adjustment
operator|->
name|lower
operator|=
name|CAST
name|entry
operator|->
name|lower
operator|>>
name|shift
expr_stmt|;
name|entry
operator|->
name|adjustment
operator|->
name|upper
operator|=
name|CAST
name|entry
operator|->
name|upper
operator|>>
name|shift
expr_stmt|;
name|gtk_adjustment_value_changed
argument_list|(
name|entry
operator|->
name|adjustment
argument_list|)
expr_stmt|;
name|gtk_adjustment_changed
argument_list|(
name|entry
operator|->
name|adjustment
argument_list|)
expr_stmt|;
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
operator|(
name|guint64
operator|)
literal|1
operator|<<
name|shift
operator|)
operator|&&
name|value
operator|%
operator|(
operator|(
name|guint64
operator|)
literal|1
operator|<<
name|shift
operator|)
operator|==
literal|0
condition|)
break|break;
block|}
name|entry
operator|->
name|value
operator|=
name|value
expr_stmt|;
name|entry
operator|->
name|lower
operator|=
name|lower
expr_stmt|;
name|entry
operator|->
name|upper
operator|=
name|upper
expr_stmt|;
name|entry
operator|->
name|shift
operator|=
name|shift
expr_stmt|;
name|entry
operator|->
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|(
name|GtkObject
operator|*
operator|*
operator|)
operator|&
name|entry
operator|->
name|adjustment
argument_list|,
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
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|CAST
name|g_object_ref
argument_list|(
name|entry
operator|->
name|adjustment
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|entry
operator|->
name|adjustment
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
operator|->
name|spinbutton
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|entry
argument_list|)
argument_list|,
name|entry
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
name|entry
operator|->
name|spinbutton
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
operator|->
name|adjustment
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_memsize_entry_adj_callback
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|entry
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
name|entry
operator|->
name|menu
argument_list|)
argument_list|,
name|shift
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
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
name|entry
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
name|entry
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
name|g_return_if_fail
argument_list|(
name|value
operator|>=
name|entry
operator|->
name|lower
operator|&&
name|value
operator|<=
name|entry
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
operator|(
name|guint64
operator|)
literal|1
operator|<<
name|shift
operator|)
operator|&&
name|value
operator|%
operator|(
operator|(
name|guint64
operator|)
literal|1
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
name|entry
operator|->
name|shift
condition|)
block|{
name|entry
operator|->
name|shift
operator|=
name|shift
expr_stmt|;
name|entry
operator|->
name|value
operator|=
name|value
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|entry
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
name|entry
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
name|entry
operator|->
name|value
return|;
block|}
end_function

end_unit

