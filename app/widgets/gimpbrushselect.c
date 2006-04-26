begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbrushselect.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushfactoryview.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushselect.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerbox.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-constructors.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon296c5aa00103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_OPACITY
name|PROP_OPACITY
block|,
DECL|enumerator|PROP_PAINT_MODE
name|PROP_PAINT_MODE
block|,
DECL|enumerator|PROP_SPACING
name|PROP_SPACING
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_brush_select_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_select_set_property
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
name|GValueArray
modifier|*
name|gimp_brush_select_run_callback
parameter_list|(
name|GimpPdbDialog
modifier|*
name|dialog
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gboolean
name|closing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_select_opacity_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpBrushSelect
modifier|*
name|select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_select_mode_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|,
name|GimpBrushSelect
modifier|*
name|select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_select_opacity_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpBrushSelect
modifier|*
name|select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_select_mode_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpBrushSelect
modifier|*
name|select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_select_spacing_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpBrushSelect
modifier|*
name|select
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpBrushSelect
argument_list|,
name|gimp_brush_select
argument_list|,
name|GIMP_TYPE_PDB_DIALOG
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_brush_select_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_class_init (GimpBrushSelectClass * klass)
name|gimp_brush_select_class_init
parameter_list|(
name|GimpBrushSelectClass
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
name|GimpPdbDialogClass
modifier|*
name|pdb_class
init|=
name|GIMP_PDB_DIALOG_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_brush_select_constructor
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_brush_select_set_property
expr_stmt|;
name|pdb_class
operator|->
name|run_callback
operator|=
name|gimp_brush_select_run_callback
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_OPACITY
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"opacity"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_OPACITY_TRANSPARENT
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PAINT_MODE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"paint-mode"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_LAYER_MODE_EFFECTS
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SPACING
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"spacing"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
name|G_MAXINT
argument_list|,
literal|1000
argument_list|,
operator|-
literal|1
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_init (GimpBrushSelect * select)
name|gimp_brush_select_init
parameter_list|(
name|GimpBrushSelect
modifier|*
name|select
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_brush_select_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_brush_select_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpPdbDialog
modifier|*
name|dialog
decl_stmt|;
name|GimpBrushSelect
modifier|*
name|select
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkAdjustment
modifier|*
name|spacing_adj
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|GIMP_PDB_DIALOG
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|select
operator|=
name|GIMP_BRUSH_SELECT
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|gimp_context_set_opacity
argument_list|(
name|dialog
operator|->
name|context
argument_list|,
name|select
operator|->
name|initial_opacity
argument_list|)
expr_stmt|;
name|gimp_context_set_paint_mode
argument_list|(
name|dialog
operator|->
name|context
argument_list|,
name|select
operator|->
name|initial_mode
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|context
argument_list|,
literal|"opacity-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_select_opacity_changed
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|context
argument_list|,
literal|"paint-mode-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_select_mode_changed
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|view
operator|=
name|gimp_brush_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_GRID
argument_list|,
name|dialog
operator|->
name|context
operator|->
name|gimp
operator|->
name|brush_factory
argument_list|,
name|dialog
operator|->
name|context
argument_list|,
name|FALSE
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|,
literal|1
argument_list|,
name|dialog
operator|->
name|menu_factory
argument_list|)
expr_stmt|;
name|gimp_container_box_set_size_request
argument_list|(
name|GIMP_CONTAINER_BOX
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
operator|->
name|view
argument_list|)
argument_list|,
literal|5
operator|*
operator|(
name|GIMP_VIEW_SIZE_MEDIUM
operator|+
literal|2
operator|)
argument_list|,
literal|5
operator|*
operator|(
name|GIMP_VIEW_SIZE_MEDIUM
operator|+
literal|2
operator|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|dialog
operator|->
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
expr_stmt|;
comment|/*  Create the frame and the table for the options  */
name|table
operator|=
name|GIMP_BRUSH_FACTORY_VIEW
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
operator|->
name|spacing_scale
operator|->
name|parent
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
comment|/*  Create the opacity scale widget  */
name|select
operator|->
name|opacity_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Opacity:"
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
literal|5
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|dialog
operator|->
name|context
argument_list|)
operator|*
literal|100.0
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|select
operator|->
name|opacity_data
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_select_opacity_update
argument_list|)
argument_list|,
name|select
argument_list|)
expr_stmt|;
comment|/*  Create the paint mode option menu  */
name|select
operator|->
name|paint_mode_menu
operator|=
name|gimp_paint_mode_menu_new
argument_list|(
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"Mode:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|select
operator|->
name|paint_mode_menu
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_connect
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|select
operator|->
name|paint_mode_menu
argument_list|)
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|dialog
operator|->
name|context
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_select_mode_update
argument_list|)
argument_list|,
name|select
argument_list|)
expr_stmt|;
name|spacing_adj
operator|=
name|GIMP_BRUSH_FACTORY_VIEW
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
operator|->
name|spacing_adjustment
expr_stmt|;
comment|/*  Use passed spacing instead of brushes default  */
if|if
condition|(
name|select
operator|->
name|spacing
operator|>=
literal|0
condition|)
name|gtk_adjustment_set_value
argument_list|(
name|spacing_adj
argument_list|,
name|select
operator|->
name|spacing
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|spacing_adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_select_spacing_update
argument_list|)
argument_list|,
name|select
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_brush_select_set_property
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
name|GimpPdbDialog
modifier|*
name|dialog
init|=
name|GIMP_PDB_DIALOG
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpBrushSelect
modifier|*
name|select
init|=
name|GIMP_BRUSH_SELECT
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
name|PROP_OPACITY
case|:
if|if
condition|(
name|dialog
operator|->
name|view
condition|)
name|gimp_context_set_opacity
argument_list|(
name|dialog
operator|->
name|context
argument_list|,
name|g_value_get_double
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|select
operator|->
name|initial_opacity
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PAINT_MODE
case|:
if|if
condition|(
name|dialog
operator|->
name|view
condition|)
name|gimp_context_set_paint_mode
argument_list|(
name|dialog
operator|->
name|context
argument_list|,
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|select
operator|->
name|initial_mode
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SPACING
case|:
if|if
condition|(
name|dialog
operator|->
name|view
condition|)
block|{
if|if
condition|(
name|g_value_get_int
argument_list|(
name|value
argument_list|)
operator|>=
literal|0
condition|)
name|gtk_adjustment_set_value
argument_list|(
name|GIMP_BRUSH_FACTORY_VIEW
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
operator|->
name|spacing_adjustment
argument_list|,
name|g_value_get_int
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|select
operator|->
name|spacing
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
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
name|GValueArray
modifier|*
DECL|function|gimp_brush_select_run_callback (GimpPdbDialog * dialog,GimpObject * object,gboolean closing)
name|gimp_brush_select_run_callback
parameter_list|(
name|GimpPdbDialog
modifier|*
name|dialog
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gboolean
name|closing
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
init|=
name|GIMP_BRUSH
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpArray
modifier|*
name|array
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
name|array
operator|=
name|gimp_array_new
argument_list|(
name|temp_buf_data
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
argument_list|,
name|brush
operator|->
name|mask
operator|->
name|width
operator|*
name|brush
operator|->
name|mask
operator|->
name|height
operator|*
name|brush
operator|->
name|mask
operator|->
name|bytes
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_execute_procedure_by_name
argument_list|(
name|dialog
operator|->
name|pdb
argument_list|,
name|dialog
operator|->
name|caller_context
argument_list|,
name|NULL
argument_list|,
name|dialog
operator|->
name|callback_name
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|object
operator|->
name|name
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|dialog
operator|->
name|context
argument_list|)
operator|*
literal|100.0
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|GIMP_BRUSH_SELECT
argument_list|(
name|dialog
argument_list|)
operator|->
name|spacing
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|dialog
operator|->
name|context
argument_list|)
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|brush
operator|->
name|mask
operator|->
name|width
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|brush
operator|->
name|mask
operator|->
name|height
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|array
operator|->
name|length
argument_list|,
name|GIMP_TYPE_INT8_ARRAY
argument_list|,
name|array
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|closing
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_array_free
argument_list|(
name|array
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_opacity_changed (GimpContext * context,gdouble opacity,GimpBrushSelect * select)
name|gimp_brush_select_opacity_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpBrushSelect
modifier|*
name|select
parameter_list|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|select
operator|->
name|opacity_data
argument_list|,
name|gimp_brush_select_opacity_update
argument_list|,
name|select
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|select
operator|->
name|opacity_data
argument_list|)
argument_list|,
name|opacity
operator|*
literal|100.0
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|select
operator|->
name|opacity_data
argument_list|,
name|gimp_brush_select_opacity_update
argument_list|,
name|select
argument_list|)
expr_stmt|;
name|gimp_pdb_dialog_run_callback
argument_list|(
name|GIMP_PDB_DIALOG
argument_list|(
name|select
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_mode_changed (GimpContext * context,GimpLayerModeEffects paint_mode,GimpBrushSelect * select)
name|gimp_brush_select_mode_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|,
name|GimpBrushSelect
modifier|*
name|select
parameter_list|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|select
operator|->
name|paint_mode_menu
argument_list|,
name|gimp_brush_select_mode_update
argument_list|,
name|select
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|select
operator|->
name|paint_mode_menu
argument_list|)
argument_list|,
name|paint_mode
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|select
operator|->
name|paint_mode_menu
argument_list|,
name|gimp_brush_select_mode_update
argument_list|,
name|select
argument_list|)
expr_stmt|;
name|gimp_pdb_dialog_run_callback
argument_list|(
name|GIMP_PDB_DIALOG
argument_list|(
name|select
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_opacity_update (GtkAdjustment * adjustment,GimpBrushSelect * select)
name|gimp_brush_select_opacity_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpBrushSelect
modifier|*
name|select
parameter_list|)
block|{
name|gimp_context_set_opacity
argument_list|(
name|GIMP_PDB_DIALOG
argument_list|(
name|select
argument_list|)
operator|->
name|context
argument_list|,
name|adjustment
operator|->
name|value
operator|/
literal|100.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_mode_update (GtkWidget * widget,GimpBrushSelect * select)
name|gimp_brush_select_mode_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpBrushSelect
modifier|*
name|select
parameter_list|)
block|{
name|gint
name|paint_mode
decl_stmt|;
if|if
condition|(
name|gimp_int_combo_box_get_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|paint_mode
argument_list|)
condition|)
block|{
name|gimp_context_set_paint_mode
argument_list|(
name|GIMP_PDB_DIALOG
argument_list|(
name|select
argument_list|)
operator|->
name|context
argument_list|,
operator|(
name|GimpLayerModeEffects
operator|)
name|paint_mode
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_select_spacing_update (GtkAdjustment * adjustment,GimpBrushSelect * select)
name|gimp_brush_select_spacing_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpBrushSelect
modifier|*
name|select
parameter_list|)
block|{
if|if
condition|(
name|select
operator|->
name|spacing
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|select
operator|->
name|spacing
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|gimp_pdb_dialog_run_callback
argument_list|(
name|GIMP_PDB_DIALOG
argument_list|(
name|select
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

