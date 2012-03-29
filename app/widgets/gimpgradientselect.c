begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpgradientselect.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpgradient.h"
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
file|"gimpcontainerbox.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradientselect.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c022d590103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SAMPLE_SIZE
name|PROP_SAMPLE_SIZE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_gradient_select_constructed
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
name|gimp_gradient_select_set_property
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
name|gimp_gradient_select_run_callback
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpGradientSelect,gimp_gradient_select,GIMP_TYPE_PDB_DIALOG)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpGradientSelect
argument_list|,
argument|gimp_gradient_select
argument_list|,
argument|GIMP_TYPE_PDB_DIALOG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_gradient_select_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_gradient_select_class_init
parameter_list|(
name|GimpGradientSelectClass
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
name|constructed
operator|=
name|gimp_gradient_select_constructed
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_gradient_select_set_property
expr_stmt|;
name|pdb_class
operator|->
name|run_callback
operator|=
name|gimp_gradient_select_run_callback
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SAMPLE_SIZE
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"sample-size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|10000
argument_list|,
literal|84
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_select_init (GimpGradientSelect * select)
name|gimp_gradient_select_init
parameter_list|(
name|GimpGradientSelect
modifier|*
name|select
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_select_constructed (GObject * object)
name|gimp_gradient_select_constructed
parameter_list|(
name|GObject
modifier|*
name|object
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
name|GtkWidget
modifier|*
name|content_area
decl_stmt|;
if|if
condition|(
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
condition|)
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
name|dialog
operator|->
name|view
operator|=
name|gimp_data_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_LIST
argument_list|,
name|dialog
operator|->
name|context
operator|->
name|gimp
operator|->
name|gradient_factory
argument_list|,
name|dialog
operator|->
name|context
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|,
literal|1
argument_list|,
name|dialog
operator|->
name|menu_factory
argument_list|,
literal|"<Gradients>"
argument_list|,
literal|"/gradients-popup"
argument_list|,
literal|"gradients"
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
literal|6
operator|*
operator|(
name|GIMP_VIEW_SIZE_MEDIUM
operator|+
literal|2
operator|)
argument_list|,
literal|6
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
name|content_area
operator|=
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|content_area
argument_list|)
argument_list|,
name|dialog
operator|->
name|view
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
name|dialog
operator|->
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_select_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_gradient_select_set_property
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
name|GimpGradientSelect
modifier|*
name|select
init|=
name|GIMP_GRADIENT_SELECT
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
name|PROP_SAMPLE_SIZE
case|:
name|select
operator|->
name|sample_size
operator|=
name|g_value_get_int
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
name|GValueArray
modifier|*
DECL|function|gimp_gradient_select_run_callback (GimpPdbDialog * dialog,GimpObject * object,gboolean closing,GError ** error)
name|gimp_gradient_select_run_callback
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpGradient
modifier|*
name|gradient
init|=
name|GIMP_GRADIENT
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpGradientSegment
modifier|*
name|seg
init|=
name|NULL
decl_stmt|;
name|gdouble
modifier|*
name|values
decl_stmt|,
modifier|*
name|pv
decl_stmt|;
name|gdouble
name|pos
decl_stmt|,
name|delta
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GimpArray
modifier|*
name|array
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
name|i
operator|=
name|GIMP_GRADIENT_SELECT
argument_list|(
name|dialog
argument_list|)
operator|->
name|sample_size
expr_stmt|;
name|pos
operator|=
literal|0.0
expr_stmt|;
name|delta
operator|=
literal|1.0
operator|/
operator|(
name|i
operator|-
literal|1
operator|)
expr_stmt|;
name|values
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
literal|4
operator|*
name|i
argument_list|)
expr_stmt|;
name|pv
operator|=
name|values
expr_stmt|;
while|while
condition|(
name|i
operator|--
condition|)
block|{
name|seg
operator|=
name|gimp_gradient_get_color_at
argument_list|(
name|gradient
argument_list|,
name|dialog
operator|->
name|caller_context
argument_list|,
name|seg
argument_list|,
name|pos
argument_list|,
name|FALSE
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|r
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|g
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|b
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|a
expr_stmt|;
name|pos
operator|+=
name|delta
expr_stmt|;
block|}
name|array
operator|=
name|gimp_array_new
argument_list|(
operator|(
name|guint8
operator|*
operator|)
name|values
argument_list|,
name|GIMP_GRADIENT_SELECT
argument_list|(
name|dialog
argument_list|)
operator|->
name|sample_size
operator|*
literal|4
operator|*
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|array
operator|->
name|static_data
operator|=
name|FALSE
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
name|error
argument_list|,
name|dialog
operator|->
name|callback_name
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|gimp_object_get_name
argument_list|(
name|object
argument_list|)
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|array
operator|->
name|length
operator|/
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|,
name|GIMP_TYPE_FLOAT_ARRAY
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

end_unit

