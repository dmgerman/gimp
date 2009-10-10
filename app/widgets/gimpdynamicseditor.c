begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_define
DECL|macro|DEFAULT_PRESSURE_OPACITY
define|#
directive|define
name|DEFAULT_PRESSURE_OPACITY
value|TRUE
end_define

begin_define
DECL|macro|DEFAULT_PRESSURE_HARDNESS
define|#
directive|define
name|DEFAULT_PRESSURE_HARDNESS
value|FALSE
end_define

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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpdynamicseditor.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdynamics.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimptooloptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimppropwidgets.h"
end_include

begin_function_decl
specifier|static
name|GObject
modifier|*
name|get_config_value
parameter_list|(
name|GimpDynamicsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_dynamics_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|face
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_dynamics_editor_constructor
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
name|gimp_dynamics_editor_set_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dynamics_editor_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dynamics_editor_notify_dynamics
parameter_list|(
name|GimpDynamics
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDynamicsEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dynamics_output_maping_row_gui
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name_part
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_label
parameter_list|,
name|GtkTable
modifier|*
name|table
parameter_list|,
name|gint
name|row
parameter_list|,
name|GtkWidget
modifier|*
name|labels
index|[]
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|dynamics_check_button_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|GtkTable
modifier|*
name|table
parameter_list|,
name|gint
name|column
parameter_list|,
name|gint
name|row
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dynamics_check_button_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|toggle
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|GtkWidget
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpDynamicsEditor
argument_list|,
argument|gimp_dynamics_editor
argument_list|,
argument|GIMP_TYPE_DATA_EDITOR
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,                                                 gimp_dynamics_editor_docked_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dynamics_editor_parent_class
end_define

begin_decl_stmt
specifier|static
name|GimpDockedInterface
modifier|*
name|parent_docked_iface
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_editor_class_init (GimpDynamicsEditorClass * klass)
name|gimp_dynamics_editor_class_init
parameter_list|(
name|GimpDynamicsEditorClass
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
name|GimpDataEditorClass
modifier|*
name|editor_class
init|=
name|GIMP_DATA_EDITOR_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_dynamics_editor_constructor
expr_stmt|;
name|editor_class
operator|->
name|set_data
operator|=
name|gimp_dynamics_editor_set_data
expr_stmt|;
name|editor_class
operator|->
name|title
operator|=
name|_
argument_list|(
literal|"Dynamics Editor"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_editor_docked_iface_init (GimpDockedInterface * iface)
name|gimp_dynamics_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
block|{
name|parent_docked_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|iface
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|parent_docked_iface
condition|)
name|parent_docked_iface
operator|=
name|g_type_default_interface_peek
argument_list|(
name|GIMP_TYPE_DOCKED
argument_list|)
expr_stmt|;
name|iface
operator|->
name|set_context
operator|=
name|gimp_dynamics_editor_set_context
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_dynamics_editor_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_dynamics_editor_constructor
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
name|gimp_docked_set_show_button_bar
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|object
argument_list|)
argument_list|,
name|FALSE
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
DECL|function|gimp_dynamics_editor_set_data (GimpDataEditor * editor,GimpData * data)
name|gimp_dynamics_editor_set_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|GimpDynamicsEditor
modifier|*
name|dynamics_editor
init|=
name|GIMP_DYNAMICS_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|data
condition|)
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|data
argument_list|,
name|gimp_dynamics_editor_notify_dynamics
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|GIMP_DATA_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_data
argument_list|(
name|editor
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|data
condition|)
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|data
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dynamics_editor_notify_dynamics
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
DECL|function|gimp_dynamics_editor_notify_dynamics (GimpDynamics * options,GParamSpec * pspec,GimpDynamicsEditor * editor)
name|gimp_dynamics_editor_notify_dynamics
parameter_list|(
name|GimpDynamics
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDynamicsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|data_editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|data_editor
operator|->
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GimpDynamics
modifier|*
name|context_dyn
init|=
name|gimp_get_user_context
argument_list|(
name|data_editor
operator|->
name|context
operator|->
name|gimp
argument_list|)
operator|->
name|dynamics
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DYNAMICS
argument_list|(
name|context_dyn
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_config_copy
argument_list|(
name|options
argument_list|,
name|context_dyn
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_editor_set_context (GimpDocked * docked,GimpContext * context)
name|gimp_dynamics_editor_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|data_editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|parent_docked_iface
operator|->
name|set_context
argument_list|(
name|docked
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dynamics_editor_new (GimpContext * context,GimpMenuFactory * menu_factory)
name|gimp_dynamics_editor_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|GimpDynamicsEditor
modifier|*
name|editor
decl_stmt|;
name|editor
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DYNAMICS_EDITOR
argument_list|,
literal|"menu-factory"
argument_list|,
name|menu_factory
argument_list|,
literal|"menu-identifier"
argument_list|,
literal|"<DynamicsEditor>"
argument_list|,
literal|"ui-path"
argument_list|,
literal|"/dynamics-editor-popup"
argument_list|,
literal|"data-factory"
argument_list|,
name|context
operator|->
name|gimp
operator|->
name|dynamics_factory
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
literal|"data"
argument_list|,
name|gimp_context_get_dynamics
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|dynamics_model
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dynamics_editor_notify_dynamics
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
return|return
name|editor
return|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|get_config_value (GimpDynamicsEditor * editor)
name|get_config_value
parameter_list|(
name|GimpDynamicsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DYNAMICS_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GObject
modifier|*
name|config
init|=
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
decl_stmt|;
return|return
name|config
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_editor_init (GimpDynamicsEditor * editor)
name|gimp_dynamics_editor_init
parameter_list|(
name|GimpDynamicsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|data_editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|editor
operator|->
name|dynamics_model
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DYNAMICS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GimpDynamics
modifier|*
name|dynamics
init|=
name|editor
operator|->
name|dynamics_model
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|box
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|gint
name|n_dynamics
init|=
literal|0
decl_stmt|;
name|GtkWidget
modifier|*
name|dynamics_labels
index|[
literal|6
index|]
decl_stmt|;
name|GObject
modifier|*
name|config
init|=
name|G_OBJECT
argument_list|(
name|dynamics
argument_list|)
decl_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|data_editor
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|dynamics_labels
index|[
name|n_dynamics
index|]
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Pressure"
argument_list|)
argument_list|)
expr_stmt|;
name|n_dynamics
operator|++
expr_stmt|;
name|dynamics_labels
index|[
name|n_dynamics
index|]
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Velocity"
argument_list|)
argument_list|)
expr_stmt|;
name|n_dynamics
operator|++
expr_stmt|;
name|dynamics_labels
index|[
name|n_dynamics
index|]
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Direction"
argument_list|)
argument_list|)
expr_stmt|;
name|n_dynamics
operator|++
expr_stmt|;
name|dynamics_labels
index|[
name|n_dynamics
index|]
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Tilt"
argument_list|)
argument_list|)
expr_stmt|;
name|n_dynamics
operator|++
expr_stmt|;
name|dynamics_labels
index|[
name|n_dynamics
index|]
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Random"
argument_list|)
argument_list|)
expr_stmt|;
name|n_dynamics
operator|++
expr_stmt|;
name|dynamics_labels
index|[
name|n_dynamics
index|]
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Fade"
argument_list|)
argument_list|)
expr_stmt|;
name|n_dynamics
operator|++
expr_stmt|;
comment|/* NB: When adding new dynamics driver, increase size of the    * dynamics_labels[] array    */
if|if
condition|(
name|n_dynamics
operator|>
literal|0
condition|)
block|{
name|GtkWidget
modifier|*
name|inner_frame
decl_stmt|;
name|GtkWidget
modifier|*
name|fixed
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gboolean
name|rtl
init|=
name|gtk_widget_get_direction
argument_list|(
name|vbox
argument_list|)
operator|==
name|GTK_TEXT_DIR_RTL
decl_stmt|;
name|inner_frame
operator|=
name|gimp_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|inner_frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|inner_frame
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|9
argument_list|,
name|n_dynamics
operator|+
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|inner_frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|dynamics_output_maping_row_gui
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|dynamics_model
argument_list|)
argument_list|,
literal|"opacity"
argument_list|,
name|_
argument_list|(
literal|"Opacity"
argument_list|)
argument_list|,
name|table
argument_list|,
literal|1
argument_list|,
name|dynamics_labels
argument_list|)
expr_stmt|;
name|dynamics_output_maping_row_gui
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|dynamics_model
argument_list|)
argument_list|,
literal|"hardness"
argument_list|,
name|_
argument_list|(
literal|"Hardness"
argument_list|)
argument_list|,
name|table
argument_list|,
literal|2
argument_list|,
name|dynamics_labels
argument_list|)
expr_stmt|;
name|dynamics_output_maping_row_gui
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|dynamics_model
argument_list|)
argument_list|,
literal|"rate"
argument_list|,
name|_
argument_list|(
literal|"Rate"
argument_list|)
argument_list|,
name|table
argument_list|,
literal|3
argument_list|,
name|dynamics_labels
argument_list|)
expr_stmt|;
name|dynamics_output_maping_row_gui
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|dynamics_model
argument_list|)
argument_list|,
literal|"size"
argument_list|,
name|_
argument_list|(
literal|"Size"
argument_list|)
argument_list|,
name|table
argument_list|,
literal|4
argument_list|,
name|dynamics_labels
argument_list|)
expr_stmt|;
name|dynamics_output_maping_row_gui
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|dynamics_model
argument_list|)
argument_list|,
literal|"aspect-ratio"
argument_list|,
name|_
argument_list|(
literal|"Aspect ratio"
argument_list|)
argument_list|,
name|table
argument_list|,
literal|5
argument_list|,
name|dynamics_labels
argument_list|)
expr_stmt|;
name|dynamics_output_maping_row_gui
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|dynamics_model
argument_list|)
argument_list|,
literal|"color"
argument_list|,
name|_
argument_list|(
literal|"Color"
argument_list|)
argument_list|,
name|table
argument_list|,
literal|6
argument_list|,
name|dynamics_labels
argument_list|)
expr_stmt|;
name|dynamics_output_maping_row_gui
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|dynamics_model
argument_list|)
argument_list|,
literal|"angle"
argument_list|,
name|_
argument_list|(
literal|"Angle"
argument_list|)
argument_list|,
name|table
argument_list|,
literal|7
argument_list|,
name|dynamics_labels
argument_list|)
expr_stmt|;
name|dynamics_output_maping_row_gui
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|dynamics_model
argument_list|)
argument_list|,
literal|"jitter"
argument_list|,
name|_
argument_list|(
literal|"Jitter"
argument_list|)
argument_list|,
name|table
argument_list|,
literal|8
argument_list|,
name|dynamics_labels
argument_list|)
expr_stmt|;
name|fixed
operator|=
name|gtk_fixed_new
argument_list|()
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|fixed
argument_list|,
literal|0
argument_list|,
name|n_dynamics
operator|+
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
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
name|fixed
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
name|n_dynamics
condition|;
name|i
operator|++
control|)
block|{
name|gtk_label_set_angle
argument_list|(
name|GTK_LABEL
argument_list|(
name|dynamics_labels
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|90
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|dynamics_labels
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_fixed_put
argument_list|(
name|GTK_FIXED
argument_list|(
name|fixed
argument_list|)
argument_list|,
name|dynamics_labels
index|[
name|i
index|]
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dynamics_labels
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|dynamics_output_maping_row_gui (GObject * config,const gchar * property_name_part,const gchar * property_label,GtkTable * table,gint row,GtkWidget * labels[])
name|dynamics_output_maping_row_gui
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name_part
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_label
parameter_list|,
name|GtkTable
modifier|*
name|table
parameter_list|,
name|gint
name|row
parameter_list|,
name|GtkWidget
modifier|*
name|labels
index|[]
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|gint
name|column
init|=
literal|1
decl_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|property_label
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|row
argument_list|,
name|row
operator|+
literal|1
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
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
name|label
argument_list|)
expr_stmt|;
comment|/*gboolean  pressure;   gboolean  velocity;   gboolean  direction;   gboolean  tilt;   gboolean  random;   gboolean  fade; */
name|button
operator|=
name|dynamics_check_button_new
argument_list|(
name|config
argument_list|,
name|g_strconcat
argument_list|(
literal|"pressure-"
argument_list|,
name|property_name_part
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|table
argument_list|,
name|column
argument_list|,
name|row
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"size-allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|dynamics_check_button_size_allocate
argument_list|)
argument_list|,
name|labels
index|[
name|column
operator|-
literal|1
index|]
argument_list|)
expr_stmt|;
name|column
operator|++
expr_stmt|;
name|button
operator|=
name|dynamics_check_button_new
argument_list|(
name|config
argument_list|,
name|g_strconcat
argument_list|(
literal|"velocity-"
argument_list|,
name|property_name_part
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|table
argument_list|,
name|column
argument_list|,
name|row
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"size-allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|dynamics_check_button_size_allocate
argument_list|)
argument_list|,
name|labels
index|[
name|column
operator|-
literal|1
index|]
argument_list|)
expr_stmt|;
name|column
operator|++
expr_stmt|;
name|button
operator|=
name|dynamics_check_button_new
argument_list|(
name|config
argument_list|,
name|g_strconcat
argument_list|(
literal|"direction-"
argument_list|,
name|property_name_part
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|table
argument_list|,
name|column
argument_list|,
name|row
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"size-allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|dynamics_check_button_size_allocate
argument_list|)
argument_list|,
name|labels
index|[
name|column
operator|-
literal|1
index|]
argument_list|)
expr_stmt|;
name|column
operator|++
expr_stmt|;
name|button
operator|=
name|dynamics_check_button_new
argument_list|(
name|config
argument_list|,
name|g_strconcat
argument_list|(
literal|"tilt-"
argument_list|,
name|property_name_part
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|table
argument_list|,
name|column
argument_list|,
name|row
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"size-allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|dynamics_check_button_size_allocate
argument_list|)
argument_list|,
name|labels
index|[
name|column
operator|-
literal|1
index|]
argument_list|)
expr_stmt|;
name|column
operator|++
expr_stmt|;
name|button
operator|=
name|dynamics_check_button_new
argument_list|(
name|config
argument_list|,
name|g_strconcat
argument_list|(
literal|"random-"
argument_list|,
name|property_name_part
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|table
argument_list|,
name|column
argument_list|,
name|row
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"size-allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|dynamics_check_button_size_allocate
argument_list|)
argument_list|,
name|labels
index|[
name|column
operator|-
literal|1
index|]
argument_list|)
expr_stmt|;
name|column
operator|++
expr_stmt|;
name|button
operator|=
name|dynamics_check_button_new
argument_list|(
name|config
argument_list|,
name|g_strconcat
argument_list|(
literal|"fading-"
argument_list|,
name|property_name_part
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|table
argument_list|,
name|column
argument_list|,
name|row
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"size-allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|dynamics_check_button_size_allocate
argument_list|)
argument_list|,
name|labels
index|[
name|column
operator|-
literal|1
index|]
argument_list|)
expr_stmt|;
name|column
operator|++
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|dynamics_check_button_new (GObject * config,const gchar * property_name,GtkTable * table,gint column,gint row)
name|dynamics_check_button_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|GtkTable
modifier|*
name|table
parameter_list|,
name|gint
name|column
parameter_list|,
name|gint
name|row
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|table
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
argument_list|,
name|GTK_SHRINK
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
return|return
name|button
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dynamics_check_button_size_allocate (GtkWidget * toggle,GtkAllocation * allocation,GtkWidget * label)
name|dynamics_check_button_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|toggle
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|GtkWidget
modifier|*
name|label
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|fixed
init|=
name|label
operator|->
name|parent
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
if|if
condition|(
name|gtk_widget_get_direction
argument_list|(
name|label
argument_list|)
operator|==
name|GTK_TEXT_DIR_LTR
condition|)
name|x
operator|=
name|allocation
operator|->
name|x
expr_stmt|;
else|else
name|x
operator|=
name|allocation
operator|->
name|x
operator|+
name|allocation
operator|->
name|width
operator|-
name|label
operator|->
name|allocation
operator|.
name|width
expr_stmt|;
name|x
operator|-=
name|fixed
operator|->
name|allocation
operator|.
name|x
expr_stmt|;
name|y
operator|=
name|fixed
operator|->
name|allocation
operator|.
name|height
operator|-
name|label
operator|->
name|allocation
operator|.
name|height
expr_stmt|;
name|gtk_fixed_move
argument_list|(
name|GTK_FIXED
argument_list|(
name|fixed
argument_list|)
argument_list|,
name|label
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

