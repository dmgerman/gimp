begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpgradientselect.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"pdb/procedural_db.h"
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
DECL|enum|__anon2c8879c00103
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
name|gimp_gradient_select_class_init
parameter_list|(
name|GimpGradientSelectClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_gradient_select_constructor
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
name|Argument
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
name|gint
modifier|*
name|n_return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDataSelectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_gradient_select_get_type (void)
name|gimp_gradient_select_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|dialog_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|dialog_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|dialog_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpGradientSelectClass
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
name|gimp_gradient_select_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpGradientSelect
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
name|dialog_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DATA_SELECT
argument_list|,
literal|"GimpGradientSelect"
argument_list|,
operator|&
name|dialog_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|dialog_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gradient_select_class_init (GimpGradientSelectClass * klass)
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_gradient_select_constructor
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
name|G_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_gradient_select_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_gradient_select_constructor
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
name|GIMP_DATA_SELECT
argument_list|(
name|dialog
argument_list|)
operator|->
name|edit_func
argument_list|,
name|dialog
operator|->
name|context
argument_list|,
name|GIMP_PREVIEW_SIZE_MEDIUM
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
name|GIMP_PREVIEW_SIZE_MEDIUM
operator|+
literal|2
operator|)
argument_list|,
literal|6
operator|*
operator|(
name|GIMP_PREVIEW_SIZE_MEDIUM
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
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimp_gradient_select_run_callback (GimpPdbDialog * dialog,GimpObject * object,gboolean closing,gint * n_return_vals)
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
name|gint
modifier|*
name|n_return_vals
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
name|gimp_gradient_get_color_at
argument_list|(
name|gradient
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
return|return
name|procedural_db_run_proc
argument_list|(
name|dialog
operator|->
name|context
operator|->
name|gimp
argument_list|,
name|dialog
operator|->
name|context
argument_list|,
name|NULL
argument_list|,
name|dialog
operator|->
name|callback_name
argument_list|,
name|n_return_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|gradient
argument_list|)
operator|->
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|GIMP_GRADIENT_SELECT
argument_list|(
name|dialog
argument_list|)
operator|->
name|sample_size
operator|*
literal|4
argument_list|,
name|GIMP_PDB_FLOATARRAY
argument_list|,
name|values
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|closing
argument_list|,
name|GIMP_PDB_END
argument_list|)
return|;
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

end_unit

