begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppdbdialog.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimppdbdialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29c6aec30103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONTEXT
name|PROP_CONTEXT
block|,
DECL|enumerator|PROP_SELECT_TYPE
name|PROP_SELECT_TYPE
block|,
DECL|enumerator|PROP_INITIAL_OBJECT
name|PROP_INITIAL_OBJECT
block|,
DECL|enumerator|PROP_CALLBACK_NAME
name|PROP_CALLBACK_NAME
block|,
DECL|enumerator|PROP_MENU_FACTORY
name|PROP_MENU_FACTORY
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_pdb_dialog_class_init
parameter_list|(
name|GimpPdbDialogClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_dialog_init
parameter_list|(
name|GimpPdbDialog
modifier|*
name|dialog
parameter_list|,
name|GimpPdbDialogClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_pdb_dialog_constructor
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
name|gimp_pdb_dialog_dispose
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
name|gimp_pdb_dialog_set_property
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
name|gimp_pdb_dialog_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_dialog_response
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_dialog_context_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|GimpPdbDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDialogClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_pdb_dialog_get_type (void)
name|gimp_pdb_dialog_get_type
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
name|GimpPdbDialogClass
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
name|gimp_pdb_dialog_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpPdbDialog
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_pdb_dialog_init
block|,       }
decl_stmt|;
name|dialog_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DIALOG
argument_list|,
literal|"GimpPdbDialog"
argument_list|,
operator|&
name|dialog_info
argument_list|,
name|G_TYPE_FLAG_ABSTRACT
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
DECL|function|gimp_pdb_dialog_class_init (GimpPdbDialogClass * klass)
name|gimp_pdb_dialog_class_init
parameter_list|(
name|GimpPdbDialogClass
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
name|GtkObjectClass
modifier|*
name|gtk_object_class
init|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkDialogClass
modifier|*
name|dialog_class
init|=
name|GTK_DIALOG_CLASS
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
name|gimp_pdb_dialog_constructor
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_pdb_dialog_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_pdb_dialog_set_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_pdb_dialog_set_property
expr_stmt|;
name|gtk_object_class
operator|->
name|destroy
operator|=
name|gimp_pdb_dialog_destroy
expr_stmt|;
name|dialog_class
operator|->
name|response
operator|=
name|gimp_pdb_dialog_response
expr_stmt|;
name|klass
operator|->
name|run_callback
operator|=
name|NULL
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
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SELECT_TYPE
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"select-type"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_INITIAL_OBJECT
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"initial-object"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CALLBACK_NAME
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"callback-name"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_MENU_FACTORY
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"menu-factory"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_MENU_FACTORY
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
DECL|function|gimp_pdb_dialog_init (GimpPdbDialog * dialog,GimpPdbDialogClass * klass)
name|gimp_pdb_dialog_init
parameter_list|(
name|GimpPdbDialog
modifier|*
name|dialog
parameter_list|,
name|GimpPdbDialogClass
modifier|*
name|klass
parameter_list|)
block|{
name|klass
operator|->
name|dialogs
operator|=
name|g_list_prepend
argument_list|(
name|klass
operator|->
name|dialogs
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gtk_dialog_add_button
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_pdb_dialog_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_pdb_dialog_constructor
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
specifier|const
name|gchar
modifier|*
name|signal_name
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
name|g_assert
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|dialog
operator|->
name|caller_context
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|g_type_is_a
argument_list|(
name|dialog
operator|->
name|select_type
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|context
operator|=
name|gimp_context_new
argument_list|(
name|dialog
operator|->
name|caller_context
operator|->
name|gimp
argument_list|,
name|g_type_name
argument_list|(
name|type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_context_set_by_type
argument_list|(
name|dialog
operator|->
name|context
argument_list|,
name|dialog
operator|->
name|select_type
argument_list|,
name|dialog
operator|->
name|initial_object
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|initial_object
operator|=
name|NULL
expr_stmt|;
name|signal_name
operator|=
name|gimp_context_type_to_signal_name
argument_list|(
name|dialog
operator|->
name|select_type
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|dialog
operator|->
name|context
argument_list|,
name|signal_name
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_pdb_dialog_context_changed
argument_list|)
argument_list|,
name|dialog
argument_list|,
literal|0
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
DECL|function|gimp_pdb_dialog_dispose (GObject * object)
name|gimp_pdb_dialog_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPdbDialogClass
modifier|*
name|klass
init|=
name|GIMP_PDB_DIALOG_GET_CLASS
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|klass
operator|->
name|dialogs
operator|=
name|g_list_remove
argument_list|(
name|klass
operator|->
name|dialogs
argument_list|,
name|object
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_dialog_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_pdb_dialog_set_property
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
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CONTEXT
case|:
name|dialog
operator|->
name|caller_context
operator|=
name|GIMP_CONTEXT
argument_list|(
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SELECT_TYPE
case|:
name|dialog
operator|->
name|select_type
operator|=
operator|(
name|GType
operator|)
name|g_value_get_pointer
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INITIAL_OBJECT
case|:
comment|/* don't ref, see constructor */
name|dialog
operator|->
name|initial_object
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CALLBACK_NAME
case|:
if|if
condition|(
name|dialog
operator|->
name|callback_name
condition|)
name|g_free
argument_list|(
name|dialog
operator|->
name|callback_name
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|callback_name
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MENU_FACTORY
case|:
name|dialog
operator|->
name|menu_factory
operator|=
operator|(
name|GimpMenuFactory
operator|*
operator|)
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
DECL|function|gimp_pdb_dialog_destroy (GtkObject * object)
name|gimp_pdb_dialog_destroy
parameter_list|(
name|GtkObject
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
if|if
condition|(
name|dialog
operator|->
name|caller_context
condition|)
block|{
name|g_object_unref
argument_list|(
name|dialog
operator|->
name|caller_context
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|caller_context
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|dialog
operator|->
name|context
condition|)
block|{
name|g_object_unref
argument_list|(
name|dialog
operator|->
name|context
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|dialog
operator|->
name|callback_name
condition|)
block|{
name|g_free
argument_list|(
name|dialog
operator|->
name|callback_name
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|callback_name
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|dialog
operator|->
name|menu_factory
condition|)
block|{
name|g_object_unref
argument_list|(
name|dialog
operator|->
name|menu_factory
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|menu_factory
operator|=
name|NULL
expr_stmt|;
block|}
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_dialog_response (GtkDialog * gtk_dialog,gint response_id)
name|gimp_pdb_dialog_response
parameter_list|(
name|GtkDialog
modifier|*
name|gtk_dialog
parameter_list|,
name|gint
name|response_id
parameter_list|)
block|{
name|GimpPdbDialog
modifier|*
name|dialog
init|=
name|GIMP_PDB_DIALOG
argument_list|(
name|gtk_dialog
argument_list|)
decl_stmt|;
name|gimp_pdb_dialog_run_callback
argument_list|(
name|dialog
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_pdb_dialog_run_callback (GimpPdbDialog * dialog,gboolean closing)
name|gimp_pdb_dialog_run_callback
parameter_list|(
name|GimpPdbDialog
modifier|*
name|dialog
parameter_list|,
name|gboolean
name|closing
parameter_list|)
block|{
name|GimpPdbDialogClass
modifier|*
name|klass
init|=
name|GIMP_PDB_DIALOG_GET_CLASS
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
name|GimpObject
modifier|*
name|object
decl_stmt|;
name|object
operator|=
name|gimp_context_get_by_type
argument_list|(
name|dialog
operator|->
name|context
argument_list|,
name|dialog
operator|->
name|select_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|object
operator|&&
name|klass
operator|->
name|run_callback
operator|&&
name|dialog
operator|->
name|callback_name
operator|&&
operator|!
name|dialog
operator|->
name|callback_busy
condition|)
block|{
name|dialog
operator|->
name|callback_busy
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|procedural_db_lookup
argument_list|(
name|dialog
operator|->
name|caller_context
operator|->
name|gimp
argument_list|,
name|dialog
operator|->
name|callback_name
argument_list|)
condition|)
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|n_return_vals
decl_stmt|;
name|return_vals
operator|=
name|klass
operator|->
name|run_callback
argument_list|(
name|dialog
argument_list|,
name|object
argument_list|,
name|closing
argument_list|,
operator|&
name|n_return_vals
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
operator|&
name|return_vals
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
operator|!=
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Unable to run %s callback. "
literal|"The corresponding plug-in may have crashed."
argument_list|)
argument_list|,
name|g_type_name
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|procedural_db_destroy_args
argument_list|(
name|return_vals
argument_list|,
name|n_return_vals
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|dialog
operator|->
name|callback_busy
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpPdbDialog
modifier|*
DECL|function|gimp_pdb_dialog_get_by_callback (GimpPdbDialogClass * klass,const gchar * callback_name)
name|gimp_pdb_dialog_get_by_callback
parameter_list|(
name|GimpPdbDialogClass
modifier|*
name|klass
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PDB_DIALOG_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|callback_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|klass
operator|->
name|dialogs
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPdbDialog
modifier|*
name|dialog
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|dialog
operator|->
name|callback_name
operator|&&
operator|!
name|strcmp
argument_list|(
name|callback_name
argument_list|,
name|dialog
operator|->
name|callback_name
argument_list|)
condition|)
return|return
name|dialog
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_pdb_dialogs_check_callback (GimpPdbDialogClass * klass)
name|gimp_pdb_dialogs_check_callback
parameter_list|(
name|GimpPdbDialogClass
modifier|*
name|klass
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PDB_DIALOG_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|klass
operator|->
name|dialogs
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|GimpPdbDialog
modifier|*
name|dialog
init|=
name|list
operator|->
name|data
decl_stmt|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
operator|->
name|caller_context
operator|&&
name|dialog
operator|->
name|callback_name
condition|)
block|{
if|if
condition|(
operator|!
name|procedural_db_lookup
argument_list|(
name|dialog
operator|->
name|caller_context
operator|->
name|gimp
argument_list|,
name|dialog
operator|->
name|callback_name
argument_list|)
condition|)
block|{
name|gtk_dialog_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|)
expr_stmt|;
block|}
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
DECL|function|gimp_pdb_dialog_context_changed (GimpContext * context,GimpObject * object,GimpPdbDialog * dialog)
name|gimp_pdb_dialog_context_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|GimpPdbDialog
modifier|*
name|dialog
parameter_list|)
block|{
if|if
condition|(
name|object
condition|)
name|gimp_pdb_dialog_run_callback
argument_list|(
name|dialog
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

