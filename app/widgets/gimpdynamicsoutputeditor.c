begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpdynamicsoutputeditor.c  * Copyright (C) 2010 Alexia Death  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
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
file|"core/gimpcurve.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdynamicsoutput.h"
end_include

begin_include
include|#
directive|include
file|"gimpcurveview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdynamicsoutputeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|CURVE_SIZE
define|#
directive|define
name|CURVE_SIZE
value|185
end_define

begin_define
DECL|macro|CURVE_BORDER
define|#
directive|define
name|CURVE_BORDER
value|4
end_define

begin_enum
enum|enum
DECL|enum|__anon2be3cb930103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_OUTPUT
name|PROP_OUTPUT
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2be3cb930203
block|{
DECL|enumerator|INPUT_COLUMN_INDEX
name|INPUT_COLUMN_INDEX
block|,
DECL|enumerator|INPUT_COLUMN_USE_INPUT
name|INPUT_COLUMN_USE_INPUT
block|,
DECL|enumerator|INPUT_COLUMN_NAME
name|INPUT_COLUMN_NAME
block|,
DECL|enumerator|INPUT_COLUMN_COLOR
name|INPUT_COLUMN_COLOR
block|,
DECL|enumerator|INPUT_N_COLUMNS
name|INPUT_N_COLUMNS
block|}
enum|;
end_enum

begin_struct
struct|struct
DECL|struct|__anon2be3cb930308
block|{
DECL|member|use_property
specifier|const
name|gchar
modifier|*
name|use_property
decl_stmt|;
DECL|member|curve_property
specifier|const
name|gchar
modifier|*
name|curve_property
decl_stmt|;
DECL|member|label
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
DECL|member|color
specifier|const
name|GimpRGB
name|color
decl_stmt|;
block|}
DECL|variable|inputs
name|inputs
index|[]
init|=
block|{
block|{
literal|"use-pressure"
block|,
literal|"pressure-curve"
block|,
name|N_
argument_list|(
literal|"Pressure"
argument_list|)
block|,
block|{
literal|1.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
block|}
block|,
block|{
literal|"use-velocity"
block|,
literal|"velocity-curve"
block|,
name|N_
argument_list|(
literal|"Velocity"
argument_list|)
block|,
block|{
literal|0.0
block|,
literal|1.0
block|,
literal|0.0
block|,
literal|1.0
block|}
block|}
block|,
block|{
literal|"use-direction"
block|,
literal|"direction-curve"
block|,
name|N_
argument_list|(
literal|"Direction"
argument_list|)
block|,
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|,
literal|1.0
block|}
block|}
block|,
block|{
literal|"use-tilt"
block|,
literal|"tilt-curve"
block|,
name|N_
argument_list|(
literal|"Tilt"
argument_list|)
block|,
block|{
literal|1.0
block|,
literal|0.5
block|,
literal|0.0
block|,
literal|1.0
block|}
block|}
block|,
block|{
literal|"use-wheel"
block|,
literal|"wheel-curve"
block|,
name|N_
argument_list|(
literal|"Wheel / Rotation"
argument_list|)
block|,
block|{
literal|1.0
block|,
literal|0.0
block|,
literal|1.0
block|,
literal|1.0
block|}
block|}
block|,
block|{
literal|"use-random"
block|,
literal|"random-curve"
block|,
name|N_
argument_list|(
literal|"Random"
argument_list|)
block|,
block|{
literal|0.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|}
block|}
block|,
block|{
literal|"use-fade"
block|,
literal|"fade-curve"
block|,
name|N_
argument_list|(
literal|"Fade"
argument_list|)
block|,
block|{
literal|0.2
block|,
literal|0.2
block|,
literal|0.2
block|,
literal|1.0
block|}
block|}
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpDynamicsOutputEditorPrivate
typedef|typedef
name|struct
name|_GimpDynamicsOutputEditorPrivate
name|GimpDynamicsOutputEditorPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDynamicsOutputEditorPrivate
struct|struct
name|_GimpDynamicsOutputEditorPrivate
block|{
DECL|member|output
name|GimpDynamicsOutput
modifier|*
name|output
decl_stmt|;
DECL|member|input_list
name|GtkListStore
modifier|*
name|input_list
decl_stmt|;
DECL|member|input_iters
name|GtkTreeIter
name|input_iters
index|[
name|G_N_ELEMENTS
argument_list|(
name|inputs
argument_list|)
index|]
decl_stmt|;
DECL|member|curve_view
name|GtkWidget
modifier|*
name|curve_view
decl_stmt|;
DECL|member|input_view
name|GtkWidget
modifier|*
name|input_view
decl_stmt|;
DECL|member|active_curve
name|GimpCurve
modifier|*
name|active_curve
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (editor)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|editor
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (editor, \                                      GIMP_TYPE_DYNAMICS_OUTPUT_EDITOR, \                                      GimpDynamicsOutputEditorPrivate)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_dynamics_output_editor_constructed
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
name|gimp_dynamics_output_editor_finalize
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
name|gimp_dynamics_output_editor_set_property
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
name|gimp_dynamics_output_editor_get_property
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
name|gimp_dynamics_output_editor_curve_reset
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpDynamicsOutputEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dynamics_output_editor_input_selected
parameter_list|(
name|GtkTreeSelection
modifier|*
name|selection
parameter_list|,
name|GimpDynamicsOutputEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dynamics_output_editor_input_toggled
parameter_list|(
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|gchar
modifier|*
name|path
parameter_list|,
name|GimpDynamicsOutputEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dynamics_output_editor_activate_input
parameter_list|(
name|GimpDynamicsOutputEditor
modifier|*
name|editor
parameter_list|,
name|gint
name|input
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dynamics_output_editor_notify_output
parameter_list|(
name|GimpDynamicsOutput
modifier|*
name|output
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDynamicsOutputEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDynamicsOutputEditor,gimp_dynamics_output_editor,GTK_TYPE_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDynamicsOutputEditor
argument_list|,
argument|gimp_dynamics_output_editor
argument_list|,
argument|GTK_TYPE_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dynamics_output_editor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_dynamics_output_editor_class_init
parameter_list|(
name|GimpDynamicsOutputEditorClass
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
name|gimp_dynamics_output_editor_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_dynamics_output_editor_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_dynamics_output_editor_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_dynamics_output_editor_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_OUTPUT
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"output"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DYNAMICS_OUTPUT
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpDynamicsOutputEditorPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_output_editor_init (GimpDynamicsOutputEditor * editor)
name|gimp_dynamics_output_editor_init
parameter_list|(
name|GimpDynamicsOutputEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_output_editor_constructed (GObject * object)
name|gimp_dynamics_output_editor_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDynamicsOutputEditor
modifier|*
name|editor
decl_stmt|;
name|GimpDynamicsOutputEditorPrivate
modifier|*
name|private
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|GtkTreeSelection
modifier|*
name|tree_sel
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GimpDynamicsOutputType
name|output_type
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|type_desc
decl_stmt|;
name|editor
operator|=
name|GIMP_DYNAMICS_OUTPUT_EDITOR
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
expr_stmt|;
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
name|gimp_assert
argument_list|(
name|GIMP_IS_DYNAMICS_OUTPUT
argument_list|(
name|private
operator|->
name|output
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|->
name|curve_view
operator|=
name|gimp_curve_view_new
argument_list|()
expr_stmt|;
name|g_object_set
argument_list|(
name|private
operator|->
name|curve_view
argument_list|,
literal|"border-width"
argument_list|,
name|CURVE_BORDER
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|private
operator|->
name|output
argument_list|,
literal|"type"
argument_list|,
operator|&
name|output_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_DYNAMICS_OUTPUT_TYPE
argument_list|,
name|output_type
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|type_desc
argument_list|,
name|NULL
argument_list|)
condition|)
name|g_object_set
argument_list|(
name|private
operator|->
name|curve_view
argument_list|,
literal|"y-axis-label"
argument_list|,
name|type_desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|private
operator|->
name|curve_view
argument_list|,
name|CURVE_SIZE
operator|+
name|CURVE_BORDER
operator|*
literal|2
argument_list|,
name|CURVE_SIZE
operator|+
name|CURVE_BORDER
operator|*
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|private
operator|->
name|curve_view
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|curve_view
argument_list|)
expr_stmt|;
name|gimp_dynamics_output_editor_activate_input
argument_list|(
name|editor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Reset Curve"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|button
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
name|button
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
name|gimp_dynamics_output_editor_curve_reset
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|private
operator|->
name|input_list
operator|=
name|gtk_list_store_new
argument_list|(
name|INPUT_N_COLUMNS
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|GIMP_TYPE_RGB
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
name|G_N_ELEMENTS
argument_list|(
name|inputs
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|gboolean
name|use_input
decl_stmt|;
name|g_object_get
argument_list|(
name|private
operator|->
name|output
argument_list|,
name|inputs
index|[
name|i
index|]
operator|.
name|use_property
argument_list|,
operator|&
name|use_input
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_list_store_insert_with_values
argument_list|(
name|private
operator|->
name|input_list
argument_list|,
operator|&
name|private
operator|->
name|input_iters
index|[
name|i
index|]
argument_list|,
operator|-
literal|1
argument_list|,
name|INPUT_COLUMN_INDEX
argument_list|,
name|i
argument_list|,
name|INPUT_COLUMN_USE_INPUT
argument_list|,
name|use_input
argument_list|,
name|INPUT_COLUMN_NAME
argument_list|,
name|gettext
argument_list|(
name|inputs
index|[
name|i
index|]
operator|.
name|label
argument_list|)
argument_list|,
name|INPUT_COLUMN_COLOR
argument_list|,
operator|&
name|inputs
index|[
name|i
index|]
operator|.
name|color
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
name|view
operator|=
name|gtk_tree_view_new_with_model
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|private
operator|->
name|input_list
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|private
operator|->
name|input_list
argument_list|)
expr_stmt|;
name|gtk_tree_view_set_headers_visible
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_toggle_new
argument_list|()
expr_stmt|;
name|g_object_set
argument_list|(
name|cell
argument_list|,
literal|"mode"
argument_list|,
name|GTK_CELL_RENDERER_MODE_ACTIVATABLE
argument_list|,
literal|"activatable"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|cell
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dynamics_output_editor_input_toggled
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_tree_view_insert_column_with_attributes
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|gimp_cell_renderer_color_new
argument_list|()
argument_list|,
literal|"color"
argument_list|,
name|INPUT_COLUMN_COLOR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_insert_column_with_attributes
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|cell
argument_list|,
literal|"active"
argument_list|,
name|INPUT_COLUMN_USE_INPUT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_insert_column_with_attributes
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|gtk_cell_renderer_text_new
argument_list|()
argument_list|,
literal|"text"
argument_list|,
name|INPUT_COLUMN_NAME
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|view
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
name|view
argument_list|)
expr_stmt|;
name|private
operator|->
name|input_view
operator|=
name|view
expr_stmt|;
name|tree_sel
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_tree_selection_set_mode
argument_list|(
name|tree_sel
argument_list|,
name|GTK_SELECTION_BROWSE
argument_list|)
expr_stmt|;
name|gtk_tree_selection_select_iter
argument_list|(
name|tree_sel
argument_list|,
operator|&
name|private
operator|->
name|input_iters
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|tree_sel
argument_list|)
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dynamics_output_editor_input_selected
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|private
operator|->
name|output
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dynamics_output_editor_notify_output
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_output_editor_finalize (GObject * object)
name|gimp_dynamics_output_editor_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDynamicsOutputEditorPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|output
argument_list|)
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
DECL|function|gimp_dynamics_output_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_dynamics_output_editor_set_property
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
name|GimpDynamicsOutputEditorPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|PROP_OUTPUT
case|:
name|private
operator|->
name|output
operator|=
name|g_value_dup_object
argument_list|(
name|value
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

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_output_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_dynamics_output_editor_get_property
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
name|GimpDynamicsOutputEditorPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|PROP_OUTPUT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|output
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

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_output_editor_curve_reset (GtkWidget * button,GimpDynamicsOutputEditor * editor)
name|gimp_dynamics_output_editor_curve_reset
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GimpDynamicsOutputEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDynamicsOutputEditorPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|active_curve
condition|)
name|gimp_curve_reset
argument_list|(
name|private
operator|->
name|active_curve
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_output_editor_input_selected (GtkTreeSelection * selection,GimpDynamicsOutputEditor * editor)
name|gimp_dynamics_output_editor_input_selected
parameter_list|(
name|GtkTreeSelection
modifier|*
name|selection
parameter_list|,
name|GimpDynamicsOutputEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
name|gtk_tree_selection_get_selected
argument_list|(
name|selection
argument_list|,
operator|&
name|model
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|gint
name|input
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|INPUT_COLUMN_INDEX
argument_list|,
operator|&
name|input
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_dynamics_output_editor_activate_input
argument_list|(
name|editor
argument_list|,
name|input
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_output_editor_input_toggled (GtkCellRenderer * cell,gchar * path,GimpDynamicsOutputEditor * editor)
name|gimp_dynamics_output_editor_input_toggled
parameter_list|(
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|gchar
modifier|*
name|path
parameter_list|,
name|GimpDynamicsOutputEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDynamicsOutputEditorPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|model
operator|=
name|GTK_TREE_MODEL
argument_list|(
name|private
operator|->
name|input_list
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter_from_string
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
name|gint
name|input
decl_stmt|;
name|gboolean
name|use
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|INPUT_COLUMN_INDEX
argument_list|,
operator|&
name|input
argument_list|,
name|INPUT_COLUMN_USE_INPUT
argument_list|,
operator|&
name|use
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|private
operator|->
name|output
argument_list|,
name|inputs
index|[
name|input
index|]
operator|.
name|use_property
argument_list|,
operator|!
name|use
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_output_editor_activate_input (GimpDynamicsOutputEditor * editor,gint input)
name|gimp_dynamics_output_editor_activate_input
parameter_list|(
name|GimpDynamicsOutputEditor
modifier|*
name|editor
parameter_list|,
name|gint
name|input
parameter_list|)
block|{
name|GimpDynamicsOutputEditorPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gimp_curve_view_set_curve
argument_list|(
name|GIMP_CURVE_VIEW
argument_list|(
name|private
operator|->
name|curve_view
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_curve_view_remove_all_backgrounds
argument_list|(
name|GIMP_CURVE_VIEW
argument_list|(
name|private
operator|->
name|curve_view
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
name|G_N_ELEMENTS
argument_list|(
name|inputs
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|gboolean
name|use_input
decl_stmt|;
name|GimpCurve
modifier|*
name|input_curve
decl_stmt|;
name|g_object_get
argument_list|(
name|private
operator|->
name|output
argument_list|,
name|inputs
index|[
name|i
index|]
operator|.
name|use_property
argument_list|,
operator|&
name|use_input
argument_list|,
name|inputs
index|[
name|i
index|]
operator|.
name|curve_property
argument_list|,
operator|&
name|input_curve
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|input
operator|==
name|i
condition|)
block|{
name|gimp_curve_view_set_curve
argument_list|(
name|GIMP_CURVE_VIEW
argument_list|(
name|private
operator|->
name|curve_view
argument_list|)
argument_list|,
name|input_curve
argument_list|,
operator|&
name|inputs
index|[
name|i
index|]
operator|.
name|color
argument_list|)
expr_stmt|;
name|private
operator|->
name|active_curve
operator|=
name|input_curve
expr_stmt|;
name|gimp_curve_view_set_x_axis_label
argument_list|(
name|GIMP_CURVE_VIEW
argument_list|(
name|private
operator|->
name|curve_view
argument_list|)
argument_list|,
name|inputs
index|[
name|i
index|]
operator|.
name|label
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|use_input
condition|)
block|{
name|gimp_curve_view_add_background
argument_list|(
name|GIMP_CURVE_VIEW
argument_list|(
name|private
operator|->
name|curve_view
argument_list|)
argument_list|,
name|input_curve
argument_list|,
operator|&
name|inputs
index|[
name|i
index|]
operator|.
name|color
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|input_curve
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_output_editor_notify_output (GimpDynamicsOutput * output,const GParamSpec * pspec,GimpDynamicsOutputEditor * editor)
name|gimp_dynamics_output_editor_notify_output
parameter_list|(
name|GimpDynamicsOutput
modifier|*
name|output
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDynamicsOutputEditor
modifier|*
name|editor
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
name|G_N_ELEMENTS
argument_list|(
name|inputs
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
name|inputs
index|[
name|i
index|]
operator|.
name|use_property
argument_list|)
condition|)
block|{
name|GimpDynamicsOutputEditorPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GtkTreeSelection
modifier|*
name|sel
decl_stmt|;
name|gboolean
name|use_input
decl_stmt|;
name|GimpCurve
modifier|*
name|input_curve
decl_stmt|;
name|sel
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|private
operator|->
name|input_view
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|output
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
operator|&
name|use_input
argument_list|,
name|inputs
index|[
name|i
index|]
operator|.
name|curve_property
argument_list|,
operator|&
name|input_curve
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|private
operator|->
name|input_list
argument_list|,
operator|&
name|private
operator|->
name|input_iters
index|[
name|i
index|]
argument_list|,
name|INPUT_COLUMN_USE_INPUT
argument_list|,
name|use_input
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_tree_selection_iter_is_selected
argument_list|(
name|sel
argument_list|,
operator|&
name|private
operator|->
name|input_iters
index|[
name|i
index|]
argument_list|)
condition|)
block|{
if|if
condition|(
name|use_input
condition|)
block|{
name|gimp_curve_view_add_background
argument_list|(
name|GIMP_CURVE_VIEW
argument_list|(
name|private
operator|->
name|curve_view
argument_list|)
argument_list|,
name|input_curve
argument_list|,
operator|&
name|inputs
index|[
name|i
index|]
operator|.
name|color
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_curve_view_remove_background
argument_list|(
name|GIMP_CURVE_VIEW
argument_list|(
name|private
operator|->
name|curve_view
argument_list|)
argument_list|,
name|input_curve
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|input_curve
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dynamics_output_editor_new (GimpDynamicsOutput * output)
name|gimp_dynamics_output_editor_new
parameter_list|(
name|GimpDynamicsOutput
modifier|*
name|output
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DYNAMICS_OUTPUT
argument_list|(
name|output
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_DYNAMICS_OUTPUT_EDITOR
argument_list|,
literal|"output"
argument_list|,
name|output
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

