begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpproceduredialog.c  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"libgimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon27563c440103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PROCEDURE
name|PROP_PROCEDURE
block|,
DECL|enumerator|PROP_CONFIG
name|PROP_CONFIG
block|,
DECL|enumerator|N_PROPS
name|N_PROPS
block|}
enum|;
end_enum

begin_define
DECL|macro|RESPONSE_RESET
define|#
directive|define
name|RESPONSE_RESET
value|1
end_define

begin_struct
DECL|struct|_GimpProcedureDialogPrivate
struct|struct
name|_GimpProcedureDialogPrivate
block|{
DECL|member|procedure
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
DECL|member|config
name|GimpProcedureConfig
modifier|*
name|config
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_procedure_dialog_dispose
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
name|gimp_procedure_dialog_set_property
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
name|gimp_procedure_dialog_get_property
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

begin_macro
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpProcedureDialog
argument_list|,
argument|gimp_procedure_dialog
argument_list|,
argument|GIMP_TYPE_DIALOG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_procedure_dialog_parent_class
end_define

begin_decl_stmt
specifier|static
name|GParamSpec
modifier|*
name|props
index|[
name|N_PROPS
index|]
init|=
block|{
name|NULL
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_procedure_dialog_class_init (GimpProcedureDialogClass * klass)
name|gimp_procedure_dialog_class_init
parameter_list|(
name|GimpProcedureDialogClass
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
name|dispose
operator|=
name|gimp_procedure_dialog_dispose
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_procedure_dialog_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_procedure_dialog_set_property
expr_stmt|;
name|props
index|[
name|PROP_PROCEDURE
index|]
operator|=
name|g_param_spec_object
argument_list|(
literal|"procedure"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_PROCEDURE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|props
index|[
name|PROP_CONFIG
index|]
operator|=
name|g_param_spec_object
argument_list|(
literal|"config"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_PROCEDURE_CONFIG
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
expr_stmt|;
name|g_object_class_install_properties
argument_list|(
name|object_class
argument_list|,
name|N_PROPS
argument_list|,
name|props
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_procedure_dialog_init (GimpProcedureDialog * dialog)
name|gimp_procedure_dialog_init
parameter_list|(
name|GimpProcedureDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|dialog
operator|->
name|priv
operator|=
name|gimp_procedure_dialog_get_instance_private
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_procedure_dialog_dispose (GObject * object)
name|gimp_procedure_dialog_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpProcedureDialog
modifier|*
name|dialog
init|=
name|GIMP_PROCEDURE_DIALOG
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|dialog
operator|->
name|priv
operator|->
name|procedure
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|dialog
operator|->
name|priv
operator|->
name|config
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
DECL|function|gimp_procedure_dialog_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_procedure_dialog_set_property
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
name|GimpProcedureDialog
modifier|*
name|dialog
init|=
name|GIMP_PROCEDURE_DIALOG
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
name|PROP_PROCEDURE
case|:
name|dialog
operator|->
name|priv
operator|->
name|procedure
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONFIG
case|:
name|dialog
operator|->
name|priv
operator|->
name|config
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
DECL|function|gimp_procedure_dialog_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_procedure_dialog_get_property
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
name|GimpProcedureDialog
modifier|*
name|dialog
init|=
name|GIMP_PROCEDURE_DIALOG
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
name|PROP_PROCEDURE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|dialog
operator|->
name|priv
operator|->
name|procedure
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CONFIG
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|dialog
operator|->
name|priv
operator|->
name|config
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
name|GtkWidget
modifier|*
DECL|function|gimp_procedure_dialog_new (GimpProcedure * procedure,GimpProcedureConfig * config,const gchar * title)
name|gimp_procedure_dialog_new
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|gchar
modifier|*
name|role
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|help_id
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|ok_label
decl_stmt|;
name|gboolean
name|use_header_bar
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_procedure_config_get_procedure
argument_list|(
name|config
argument_list|)
operator|==
name|procedure
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|role
operator|=
name|g_strdup_printf
argument_list|(
literal|"gimp-%s"
argument_list|,
name|gimp_procedure_get_name
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|help_id
operator|=
name|gimp_procedure_get_help_id
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|gtk_settings_get_default
argument_list|()
argument_list|,
literal|"gtk-dialogs-use-header"
argument_list|,
operator|&
name|use_header_bar
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PROCEDURE_DIALOG
argument_list|,
literal|"procedure"
argument_list|,
name|procedure
argument_list|,
literal|"config"
argument_list|,
name|config
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
literal|"role"
argument_list|,
name|role
argument_list|,
literal|"help-func"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"help-id"
argument_list|,
name|help_id
argument_list|,
literal|"use-header-bar"
argument_list|,
name|use_header_bar
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|role
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LOAD_PROCEDURE
argument_list|(
name|procedure
argument_list|)
condition|)
name|ok_label
operator|=
name|_
argument_list|(
literal|"_Open"
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_SAVE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
condition|)
name|ok_label
operator|=
name|_
argument_list|(
literal|"_Export"
argument_list|)
expr_stmt|;
else|else
name|ok_label
operator|=
name|_
argument_list|(
literal|"_OK"
argument_list|)
expr_stmt|;
name|gimp_dialog_add_buttons
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Reset"
argument_list|)
argument_list|,
name|RESPONSE_RESET
argument_list|,
name|_
argument_list|(
literal|"_Cancel"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|ok_label
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|RESPONSE_RESET
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_window_set_transient
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_procedure_dialog_run (GimpProcedureDialog * dialog)
name|gimp_procedure_dialog_run
parameter_list|(
name|GimpProcedureDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
while|while
condition|(
name|TRUE
condition|)
block|{
name|gint
name|response
init|=
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|response
operator|==
name|RESPONSE_RESET
condition|)
block|{
name|gimp_config_reset
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|dialog
operator|->
name|priv
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
return|return
name|response
operator|==
name|GTK_RESPONSE_OK
return|;
block|}
block|}
block|}
end_function

end_unit

