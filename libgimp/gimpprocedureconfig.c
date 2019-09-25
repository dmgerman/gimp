begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpprocedureconfig.c  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * SECTION: gimpprocedureconfig  * @title: GimpProcedureConfig  * @short_description: Config object for procedure arguments  *  * #GimpProcedureConfig base class for #GimpProcedure-specific config  * objects and the main interface to manage aspects of  * #GimpProcedure's arguments such as persistency of the last used  * arguments across GIMP sessions.  *  * A #GimpProcedureConfig is created by a #GimpProcedure using  * gimp_procedure_create_config() and its properties match the  * procedure's arguments in number, order and type.  *  * It implements the #GimpConfig interface and therefore has all its  * serialization and deserialization features.  *  * Since: 3.0  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2a226f210103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PROCEDURE
name|PROP_PROCEDURE
block|,
DECL|enumerator|N_PROPS
name|N_PROPS
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpProcedureConfigPrivate
struct|struct
name|_GimpProcedureConfigPrivate
block|{
DECL|member|procedure
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|run_mode
name|GimpRunMode
name|run_mode
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_procedure_config_constructed
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
name|gimp_procedure_config_dispose
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
name|gimp_procedure_config_set_property
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
name|gimp_procedure_config_get_property
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
name|GFile
modifier|*
name|gimp_procedure_config_get_file
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_procedure_config_load_last
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_procedure_config_save_last
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_procedure_config_parasite_name
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|suffix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_procedure_config_load_parasite
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_procedure_config_save_parasite
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpProcedureConfig
argument_list|,
argument|gimp_procedure_config
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_procedure_config_parent_class
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
DECL|function|gimp_procedure_config_class_init (GimpProcedureConfigClass * klass)
name|gimp_procedure_config_class_init
parameter_list|(
name|GimpProcedureConfigClass
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
name|gimp_procedure_config_constructed
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_procedure_config_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_procedure_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_procedure_config_get_property
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
literal|"Procedure"
argument_list|,
literal|"The procedure this config object is used for"
argument_list|,
name|GIMP_TYPE_PROCEDURE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
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
DECL|function|gimp_procedure_config_init (GimpProcedureConfig * config)
name|gimp_procedure_config_init
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|)
block|{
name|config
operator|->
name|priv
operator|=
name|gimp_procedure_config_get_instance_private
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|config
operator|->
name|priv
operator|->
name|run_mode
operator|=
operator|-
literal|1
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_procedure_config_constructed (GObject * object)
name|gimp_procedure_config_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpProcedureConfig
modifier|*
name|config
init|=
name|GIMP_PROCEDURE_CONFIG
argument_list|(
name|object
argument_list|)
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
name|g_assert
argument_list|(
name|GIMP_IS_PROCEDURE
argument_list|(
name|config
operator|->
name|priv
operator|->
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_procedure_config_dispose (GObject * object)
name|gimp_procedure_config_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpProcedureConfig
modifier|*
name|config
init|=
name|GIMP_PROCEDURE_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|config
operator|->
name|priv
operator|->
name|procedure
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
DECL|function|gimp_procedure_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_procedure_config_set_property
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
name|GimpProcedureConfig
modifier|*
name|config
init|=
name|GIMP_PROCEDURE_CONFIG
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
name|config
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
DECL|function|gimp_procedure_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_procedure_config_get_property
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
name|GimpProcedureConfig
modifier|*
name|config
init|=
name|GIMP_PROCEDURE_CONFIG
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
name|config
operator|->
name|priv
operator|->
name|procedure
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
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_procedure_config_get_procedure:  * @config: a #GimpProcedureConfig  *  * This function returns the #GimpProcedure which created @config, see  * gimp_procedure_create_config().  *  * Returns: The #GimpProcedure which created @config.  *  * Since: 3.0  **/
end_comment

begin_function
name|GimpProcedure
modifier|*
DECL|function|gimp_procedure_config_get_procedure (GimpProcedureConfig * config)
name|gimp_procedure_config_get_procedure
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|)
block|{
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
return|return
name|config
operator|->
name|priv
operator|->
name|procedure
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_procedure_config_set_values:  * @config: a #GimpProcedureConfig  * @values: a #GimpValueArray  *  * Sets the values from @values on @config's properties.  *  * The number, order and types of values in @values must match the  * number, order and types of @config's properties.  *  * This function is meant to be used on @values which are passed as  * arguments to the run() function of the #GimpProcedure which created  * this @config. See gimp_procedure_create_config().  *  * Since: 3.0  **/
end_comment

begin_function
name|void
DECL|function|gimp_procedure_config_set_values (GimpProcedureConfig * config,const GimpValueArray * values)
name|gimp_procedure_config_set_values
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|values
parameter_list|)
block|{
name|GParamSpec
modifier|*
modifier|*
name|pspecs
decl_stmt|;
name|guint
name|n_pspecs
decl_stmt|;
name|gint
name|n_aux_args
decl_stmt|;
name|gint
name|n_values
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|pspecs
operator|=
name|g_object_class_list_properties
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|config
argument_list|)
argument_list|,
operator|&
name|n_pspecs
argument_list|)
expr_stmt|;
name|gimp_procedure_get_aux_arguments
argument_list|(
name|config
operator|->
name|priv
operator|->
name|procedure
argument_list|,
operator|&
name|n_aux_args
argument_list|)
expr_stmt|;
name|n_values
operator|=
name|gimp_value_array_length
argument_list|(
name|values
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|n_pspecs
operator|==
name|n_values
operator|+
name|n_aux_args
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
name|n_values
condition|;
name|i
operator|++
control|)
block|{
name|GParamSpec
modifier|*
name|pspec
init|=
name|pspecs
index|[
name|i
index|]
decl_stmt|;
name|GValue
modifier|*
name|value
init|=
name|gimp_value_array_index
argument_list|(
name|values
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|g_object_set_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|pspecs
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_procedure_config_get_values:  * @config: a #GimpProcedureConfig  * @values: a #GimpValueArray  *  * Gets the values from @config's properties and stores them in  * @values.  *  * See gimp_procedure_config_set_values().  *  * Since: 3.0  **/
end_comment

begin_function
name|void
DECL|function|gimp_procedure_config_get_values (GimpProcedureConfig * config,GimpValueArray * values)
name|gimp_procedure_config_get_values
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
name|GimpValueArray
modifier|*
name|values
parameter_list|)
block|{
name|GParamSpec
modifier|*
modifier|*
name|pspecs
decl_stmt|;
name|guint
name|n_pspecs
decl_stmt|;
name|gint
name|n_aux_args
decl_stmt|;
name|gint
name|n_values
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|pspecs
operator|=
name|g_object_class_list_properties
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|config
argument_list|)
argument_list|,
operator|&
name|n_pspecs
argument_list|)
expr_stmt|;
name|gimp_procedure_get_aux_arguments
argument_list|(
name|config
operator|->
name|priv
operator|->
name|procedure
argument_list|,
operator|&
name|n_aux_args
argument_list|)
expr_stmt|;
name|n_values
operator|=
name|gimp_value_array_length
argument_list|(
name|values
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|n_pspecs
operator|==
name|n_values
operator|+
name|n_aux_args
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
name|n_values
condition|;
name|i
operator|++
control|)
block|{
name|GParamSpec
modifier|*
name|pspec
init|=
name|pspecs
index|[
name|i
index|]
decl_stmt|;
name|GValue
modifier|*
name|value
init|=
name|gimp_value_array_index
argument_list|(
name|values
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|g_object_get_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|pspecs
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_procedure_config_begin_run:  * @config:   a #GimpProcedureConfig  * @image:    a #GimpImage or %NULL  * @run_mode: the #GimpRunMode passed to a #GimpProcedure's run()  * @args:     the #GimpValueArray passed to a #GimpProcedure's run()  *  * Populates @config with values for a #GimpProcedure's run(),  * depending on @run_mode.  *  * If @run_mode is %GIMP_RUN_INTERACTIVE or %GIMP_RUN_WITH_LAST_VALS,  * the saved values from the procedure's last run() are loaded and set  * on @config. If @image is not %NULL, the last used values for this  * image are tried first, and if no image-spesicic values are found  * the globally saved last used values are used. If no saved last used  * values are found, the procedure's default argument values are used.  *  * If @run_mode is %GIMP_RUN_NONINTERACTIVE, the contents of @args are  * set on @config using gimp_procedure_config_set_values().  *  * After calling this function, the @args passed to run() should be  * left alone and @config be treated as the procedure's arguments.  *  * It is possible to get @config's resulting values back into @args by  * calling gimp_procedure_config_get_values(), as long as modified  * @args are written back to @config using  * gimp_procedure_config_set_values() before the call to  * gimp_procedure_config_end_run().  *  * This function should be used at the beginning of a procedure's  * run() and be paired with a call to gimp_procedure_config_end_run()  * at the end of run().  *  * Since: 3.0  **/
end_comment

begin_function
name|void
DECL|function|gimp_procedure_config_begin_run (GimpProcedureConfig * config,GimpImage * image,GimpRunMode run_mode,const GimpValueArray * args)
name|gimp_procedure_config_begin_run
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|loaded
init|=
name|FALSE
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|image
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|args
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|config
operator|->
name|priv
operator|->
name|image
operator|=
name|image
expr_stmt|;
name|config
operator|->
name|priv
operator|->
name|run_mode
operator|=
name|run_mode
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
if|if
condition|(
name|image
condition|)
block|{
name|loaded
operator|=
name|gimp_procedure_config_load_parasite
argument_list|(
name|config
argument_list|,
name|image
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|loaded
operator|&&
name|error
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Loading last used values from parasite failed: %s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|loaded
operator|&&
operator|!
name|gimp_procedure_config_load_last
argument_list|(
name|config
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Loading last used values from disk failed: %s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
name|gimp_procedure_config_set_values
argument_list|(
name|config
argument_list|,
name|args
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_procedure_config_end_run:  * @config: a #GimpProcedureConfig  * @status: the return status of the #GimpProcedure's run()  *  * This function is the counterpart of  * gimp_procedure_conig_begin_run() and must always be called in pairs  * in a procedure's run(), before returning return values.  *  * If the @run_mode passed to gimp_procedure_config_end_run() was  * %GIMP_RUN_INTERACTIVE, @config is saved as last used values to be  * used when the procedure runs again. Additionally, the @image passed  * gimp_procedure_config_begin_run() was not %NULL, @config is  * attached to @image as last used values for this image using a  * #GimpParasite and gimp_image_attach_parasite().  *  * If @run_mode was not %GIMP_RUN_NONINTERACTIVE, this function also  * conveniently calls gimp_display_flush(), which is what most  * procedures want and doesn't do any harm if called redundantly.  *  * See gimp_procedure_config_begin_run().  *  * Since: 3.0  **/
end_comment

begin_function
name|void
DECL|function|gimp_procedure_config_end_run (GimpProcedureConfig * config,GimpPDBStatusType status)
name|gimp_procedure_config_end_run
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
name|GimpPDBStatusType
name|status
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROCEDURE_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|priv
operator|->
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
operator|&&
name|config
operator|->
name|priv
operator|->
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|config
operator|->
name|priv
operator|->
name|image
condition|)
name|gimp_procedure_config_save_parasite
argument_list|(
name|config
argument_list|,
name|config
operator|->
name|priv
operator|->
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_procedure_config_save_last
argument_list|(
name|config
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Saving last used values to disk failed: %s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
block|}
name|config
operator|->
name|priv
operator|->
name|image
operator|=
name|NULL
expr_stmt|;
name|config
operator|->
name|priv
operator|->
name|run_mode
operator|=
operator|-
literal|1
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GFile
modifier|*
DECL|function|gimp_procedure_config_get_file (GimpProcedureConfig * config,const gchar * extension)
name|gimp_procedure_config_get_file
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|)
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|basename
operator|=
name|g_strconcat
argument_list|(
name|G_OBJECT_TYPE_NAME
argument_list|(
name|config
argument_list|)
argument_list|,
name|extension
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|file
operator|=
name|gimp_directory_file
argument_list|(
literal|"plug-in-settings"
argument_list|,
name|basename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
return|return
name|file
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_procedure_config_load_last (GimpProcedureConfig * config,GError ** error)
name|gimp_procedure_config_load_last
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GFile
modifier|*
name|file
init|=
name|gimp_procedure_config_get_file
argument_list|(
name|config
argument_list|,
literal|".last"
argument_list|)
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|success
operator|=
name|gimp_config_deserialize_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|success
operator|&&
operator|(
operator|*
name|error
operator|)
operator|->
name|code
operator|==
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
condition|)
block|{
name|g_clear_error
argument_list|(
name|error
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_procedure_config_save_last (GimpProcedureConfig * config,GError ** error)
name|gimp_procedure_config_save_last
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GFile
modifier|*
name|file
init|=
name|gimp_procedure_config_get_file
argument_list|(
name|config
argument_list|,
literal|".last"
argument_list|)
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|success
operator|=
name|gimp_config_serialize_to_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|file
argument_list|,
literal|"settings"
argument_list|,
literal|"end of settings"
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_procedure_config_parasite_name (GimpProcedureConfig * config,const gchar * suffix)
name|gimp_procedure_config_parasite_name
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|suffix
parameter_list|)
block|{
return|return
name|g_strconcat
argument_list|(
name|G_OBJECT_TYPE_NAME
argument_list|(
name|config
argument_list|)
argument_list|,
name|suffix
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_procedure_config_load_parasite (GimpProcedureConfig * config,GimpImage * image,GError ** error)
name|gimp_procedure_config_load_parasite
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|name
operator|=
name|gimp_procedure_config_parasite_name
argument_list|(
name|config
argument_list|,
literal|"-last"
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_image_get_parasite
argument_list|(
name|image
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|parasite
condition|)
return|return
name|FALSE
return|;
name|success
operator|=
name|gimp_config_deserialize_parasite
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|parasite
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_procedure_config_save_parasite (GimpProcedureConfig * config,GimpImage * image)
name|gimp_procedure_config_save_parasite
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|name
operator|=
name|gimp_procedure_config_parasite_name
argument_list|(
name|config
argument_list|,
literal|"-last"
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_config_serialize_to_parasite
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|,
name|name
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|parasite
condition|)
return|return
name|FALSE
return|;
name|gimp_image_attach_parasite
argument_list|(
name|image
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

