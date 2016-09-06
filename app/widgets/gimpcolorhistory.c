begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcolorhistory.c  * Copyright (C) 2015 Jehan<jehan@girinstud.io>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-palettes.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppalettemru.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorhistory.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29e086100103
block|{
DECL|enumerator|COLOR_SELECTED
name|COLOR_SELECTED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon29e086100203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONTEXT
name|PROP_CONTEXT
block|,
DECL|enumerator|PROP_HISTORY_SIZE
name|PROP_HISTORY_SIZE
block|, }
enum|;
end_enum

begin_define
DECL|macro|DEFAULT_HISTORY_SIZE
define|#
directive|define
name|DEFAULT_HISTORY_SIZE
value|12
end_define

begin_define
DECL|macro|COLOR_AREA_SIZE
define|#
directive|define
name|COLOR_AREA_SIZE
value|20
end_define

begin_function_decl
specifier|static
name|void
name|gimp_color_history_constructed
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
name|gimp_color_history_finalize
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
name|gimp_color_history_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_history_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_history_color_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorHistory
modifier|*
name|history
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_history_palette_dirty
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|,
name|GimpColorHistory
modifier|*
name|history
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_history_color_changed
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

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpColorHistory
argument_list|,
argument|gimp_color_history
argument_list|,
argument|GTK_TYPE_TABLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_history_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|history_signals
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
DECL|function|gimp_color_history_class_init (GimpColorHistoryClass * klass)
name|gimp_color_history_class_init
parameter_list|(
name|GimpColorHistoryClass
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
name|constructed
operator|=
name|gimp_color_history_constructed
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_color_history_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_color_history_get_property
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_color_history_finalize
expr_stmt|;
name|history_signals
index|[
name|COLOR_SELECTED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"color-selected"
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
name|GimpColorHistoryClass
argument_list|,
name|color_selected
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__OBJECT_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTEXT
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"context"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CONTEXT
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_HISTORY_SIZE
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"history-size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|2
argument_list|,
name|G_MAXINT
argument_list|,
name|DEFAULT_HISTORY_SIZE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|klass
operator|->
name|color_selected
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_history_init (GimpColorHistory * history)
name|gimp_color_history_init
parameter_list|(
name|GimpColorHistory
modifier|*
name|history
parameter_list|)
block|{
name|history
operator|->
name|color_areas
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_history_constructed (GObject * object)
name|gimp_color_history_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorHistory
modifier|*
name|history
init|=
name|GIMP_COLOR_HISTORY
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpPalette
modifier|*
name|palette
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
name|palette
operator|=
name|gimp_palettes_get_color_history
argument_list|(
name|history
operator|->
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|palette
argument_list|,
literal|"dirty"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_history_palette_dirty
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|history
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_color_history_palette_dirty
argument_list|(
name|palette
argument_list|,
name|history
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_history_finalize (GObject * object)
name|gimp_color_history_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorHistory
modifier|*
name|history
init|=
name|GIMP_COLOR_HISTORY
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|history
operator|->
name|color_areas
argument_list|)
expr_stmt|;
name|history
operator|->
name|color_areas
operator|=
name|NULL
expr_stmt|;
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
DECL|function|gimp_color_history_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_color_history_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpColorHistory
modifier|*
name|history
init|=
name|GIMP_COLOR_HISTORY
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CONTEXT
case|:
name|history
operator|->
name|context
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HISTORY_SIZE
case|:
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/* Destroy previous color buttons. */
name|gtk_container_foreach
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|history
argument_list|)
argument_list|,
operator|(
name|GtkCallback
operator|)
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|history
operator|->
name|history_size
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gtk_table_resize
argument_list|(
name|GTK_TABLE
argument_list|(
name|history
argument_list|)
argument_list|,
literal|2
argument_list|,
operator|(
name|history
operator|->
name|history_size
operator|+
literal|1
operator|)
operator|/
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|history
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|history
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|history
operator|->
name|color_areas
operator|=
name|g_realloc_n
argument_list|(
name|history
operator|->
name|color_areas
argument_list|,
name|history
operator|->
name|history_size
argument_list|,
sizeof|sizeof
argument_list|(
name|GtkWidget
operator|*
argument_list|)
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
name|history
operator|->
name|history_size
condition|;
name|i
operator|++
control|)
block|{
name|GimpRGB
name|black
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|column
decl_stmt|;
name|column
operator|=
name|i
operator|%
operator|(
name|history
operator|->
name|history_size
operator|/
literal|2
operator|)
expr_stmt|;
name|row
operator|=
name|i
operator|/
operator|(
name|history
operator|->
name|history_size
operator|/
literal|2
operator|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|button
argument_list|,
name|COLOR_AREA_SIZE
argument_list|,
name|COLOR_AREA_SIZE
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|history
argument_list|)
argument_list|,
name|button
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
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|history
operator|->
name|color_areas
index|[
name|i
index|]
operator|=
name|gimp_color_area_new
argument_list|(
operator|&
name|black
argument_list|,
name|GIMP_COLOR_AREA_SMALL_CHECKS
argument_list|,
name|GDK_BUTTON2_MASK
argument_list|)
expr_stmt|;
name|gimp_color_area_set_color_config
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|history
operator|->
name|color_areas
index|[
name|i
index|]
argument_list|)
argument_list|,
name|history
operator|->
name|context
operator|->
name|gimp
operator|->
name|config
operator|->
name|color_management
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|history
operator|->
name|color_areas
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|history
operator|->
name|color_areas
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_history_color_clicked
argument_list|)
argument_list|,
name|history
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|history
operator|->
name|color_areas
index|[
name|i
index|]
argument_list|,
literal|"color-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_history_color_changed
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|i
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_history_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_color_history_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpColorHistory
modifier|*
name|history
init|=
name|GIMP_COLOR_HISTORY
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CONTEXT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|history
operator|->
name|context
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HISTORY_SIZE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|history
operator|->
name|history_size
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_comment
comment|/*  Public Functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_history_new (GimpContext * context,gint history_size)
name|gimp_color_history_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|history_size
parameter_list|)
block|{
name|GimpColorHistory
modifier|*
name|history
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|history
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_HISTORY
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
literal|"history-size"
argument_list|,
name|history_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|history
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  Color history callback.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_color_history_color_clicked (GtkWidget * widget,GimpColorHistory * history)
name|gimp_color_history_color_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorHistory
modifier|*
name|history
parameter_list|)
block|{
name|GimpColorArea
modifier|*
name|color_area
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|color_area
operator|=
name|GIMP_COLOR_AREA
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_color_area_get_color
argument_list|(
name|color_area
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|history
argument_list|,
name|history_signals
index|[
name|COLOR_SELECTED
index|]
argument_list|,
literal|0
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Color history palette callback. */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_color_history_palette_dirty (GimpPalette * palette,GimpColorHistory * history)
name|gimp_color_history_palette_dirty
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|,
name|GimpColorHistory
modifier|*
name|history
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|history
operator|->
name|history_size
condition|;
name|i
operator|++
control|)
block|{
name|GimpPaletteEntry
modifier|*
name|entry
init|=
name|gimp_palette_get_entry
argument_list|(
name|palette
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|GimpRGB
name|black
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|history
operator|->
name|color_areas
index|[
name|i
index|]
argument_list|,
name|gimp_color_history_color_changed
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|i
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_color_area_set_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|history
operator|->
name|color_areas
index|[
name|i
index|]
argument_list|)
argument_list|,
name|entry
condition|?
operator|&
name|entry
operator|->
name|color
else|:
operator|&
name|black
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|history
operator|->
name|color_areas
index|[
name|i
index|]
argument_list|,
name|gimp_color_history_color_changed
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|i
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* Color area callbacks. */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_color_history_color_changed (GtkWidget * widget,gpointer data)
name|gimp_color_history_color_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpColorHistory
modifier|*
name|history
decl_stmt|;
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|history
operator|=
name|GIMP_COLOR_HISTORY
argument_list|(
name|gtk_widget_get_ancestor
argument_list|(
name|widget
argument_list|,
name|GIMP_TYPE_COLOR_HISTORY
argument_list|)
argument_list|)
expr_stmt|;
name|palette
operator|=
name|gimp_palettes_get_color_history
argument_list|(
name|history
operator|->
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|gimp_color_area_get_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_palette_set_entry_color
argument_list|(
name|palette
argument_list|,
name|GPOINTER_TO_INT
argument_list|(
name|data
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

