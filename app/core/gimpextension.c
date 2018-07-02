begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpextension.c  * Copyright (C) 2018 Jehan<jehan@girinstud.io>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<appstream-glib.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpextension.h"
end_include

begin_include
include|#
directive|include
file|"gimpextension-error.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29e621960103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PATH
name|PROP_PATH
block|,
DECL|enumerator|PROP_WRITABLE
name|PROP_WRITABLE
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpExtensionPrivate
struct|struct
name|_GimpExtensionPrivate
block|{
DECL|member|path
name|gchar
modifier|*
name|path
decl_stmt|;
DECL|member|app
name|AsApp
modifier|*
name|app
decl_stmt|;
DECL|member|writable
name|gboolean
name|writable
decl_stmt|;
comment|/* Extension metadata: directories. */
DECL|member|brush_paths
name|GList
modifier|*
name|brush_paths
decl_stmt|;
DECL|member|dynamics_paths
name|GList
modifier|*
name|dynamics_paths
decl_stmt|;
DECL|member|mypaint_brush_paths
name|GList
modifier|*
name|mypaint_brush_paths
decl_stmt|;
DECL|member|pattern_paths
name|GList
modifier|*
name|pattern_paths
decl_stmt|;
DECL|member|gradient_paths
name|GList
modifier|*
name|gradient_paths
decl_stmt|;
DECL|member|palette_paths
name|GList
modifier|*
name|palette_paths
decl_stmt|;
DECL|member|tool_preset_paths
name|GList
modifier|*
name|tool_preset_paths
decl_stmt|;
comment|/* Extension metadata: plug-in entry points. */
DECL|member|plug_in_paths
name|GList
modifier|*
name|plug_in_paths
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_extension_finalize
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
name|gimp_extension_set_property
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
name|gimp_extension_get_property
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
name|GList
modifier|*
name|gimp_extension_validate_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|,
specifier|const
name|gchar
modifier|*
name|paths
parameter_list|,
name|gboolean
name|as_directories
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpExtension,gimp_extension,GIMP_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpExtension
argument_list|,
argument|gimp_extension
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_extension_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_extension_class_init
parameter_list|(
name|GimpExtensionClass
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
name|finalize
operator|=
name|gimp_extension_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_extension_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_extension_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PATH
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"path"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_WRITABLE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"writable"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpExtensionPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_extension_init (GimpExtension * extension)
name|gimp_extension_init
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
block|{
name|extension
operator|->
name|p
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|extension
argument_list|,
name|GIMP_TYPE_EXTENSION
argument_list|,
name|GimpExtensionPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_extension_finalize (GObject * object)
name|gimp_extension_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpExtension
modifier|*
name|extension
init|=
name|GIMP_EXTENSION
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gimp_extension_stop
argument_list|(
name|extension
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|extension
operator|->
name|p
operator|->
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
name|extension
operator|->
name|p
operator|->
name|app
condition|)
name|g_object_unref
argument_list|(
name|extension
operator|->
name|p
operator|->
name|app
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_extension_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_extension_set_property
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
name|GimpExtension
modifier|*
name|extension
init|=
name|GIMP_EXTENSION
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
name|PROP_PATH
case|:
name|g_free
argument_list|(
name|extension
operator|->
name|p
operator|->
name|path
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|g_path_get_basename
argument_list|(
name|extension
operator|->
name|p
operator|->
name|path
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WRITABLE
case|:
name|extension
operator|->
name|p
operator|->
name|writable
operator|=
name|g_value_get_boolean
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
DECL|function|gimp_extension_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_extension_get_property
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
name|GimpExtension
modifier|*
name|extension
init|=
name|GIMP_EXTENSION
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
name|PROP_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|extension
operator|->
name|p
operator|->
name|path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WRITABLE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|extension
operator|->
name|p
operator|->
name|writable
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

begin_function
name|GimpExtension
modifier|*
DECL|function|gimp_extension_new (const gchar * dir,gboolean writable)
name|gimp_extension_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|dir
parameter_list|,
name|gboolean
name|writable
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|dir
operator|&&
name|g_file_test
argument_list|(
name|dir
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_EXTENSION
argument_list|,
literal|"path"
argument_list|,
name|dir
argument_list|,
literal|"writable"
argument_list|,
name|writable
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_extension_load (GimpExtension * extension,GError ** error)
name|gimp_extension_load
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|AsApp
modifier|*
name|app
decl_stmt|;
name|GPtrArray
modifier|*
name|extends
decl_stmt|;
name|GPtrArray
modifier|*
name|requires
decl_stmt|;
name|AsRelease
modifier|*
name|release
decl_stmt|;
name|gchar
modifier|*
name|appdata_name
decl_stmt|;
name|gchar
modifier|*
name|path
decl_stmt|;
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|extension
operator|->
name|p
operator|->
name|app
argument_list|)
expr_stmt|;
comment|/* Search in subdirectory if a file with the same name as    * directory and ending with ".metainfo.xml" exists.    */
name|appdata_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s.metainfo.xml"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|extension
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|path
operator|=
name|g_build_filename
argument_list|(
name|extension
operator|->
name|p
operator|->
name|path
argument_list|,
name|appdata_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|app
operator|=
name|as_app_new
argument_list|()
expr_stmt|;
name|success
operator|=
name|as_app_parse_file
argument_list|(
name|app
argument_list|,
name|path
argument_list|,
name|AS_APP_PARSE_FLAG_USE_HEURISTICS
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
operator|&&
name|as_app_get_kind
argument_list|(
name|app
argument_list|)
operator|!=
name|AS_APP_KIND_ADDON
condition|)
block|{
comment|/* Properly setting the type will allow extensions to be        * distributed appropriately through other means.        */
if|if
condition|(
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
condition|)
operator|*
name|error
operator|=
name|g_error_new
argument_list|(
name|GIMP_EXTENSION_ERROR
argument_list|,
name|GIMP_EXTENSION_BAD_APPDATA
argument_list|,
name|_
argument_list|(
literal|"Extension AppData must be of type \"addon\", found \"%s\" instead."
argument_list|)
argument_list|,
name|as_app_kind_to_string
argument_list|(
name|as_app_get_kind
argument_list|(
name|app
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|extends
operator|=
name|as_app_get_extends
argument_list|(
name|app
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
operator|&&
operator|!
name|g_ptr_array_find_with_equal_func
argument_list|(
name|extends
argument_list|,
literal|"org.gimp.GIMP"
argument_list|,
name|g_str_equal
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
comment|/* Properly setting the<extends> will allow extensions to be        * distributed appropriately through other means.        */
if|if
condition|(
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
condition|)
operator|*
name|error
operator|=
name|g_error_new
argument_list|(
name|GIMP_EXTENSION_ERROR
argument_list|,
name|GIMP_EXTENSION_BAD_APPDATA
argument_list|,
name|_
argument_list|(
literal|"Extension AppData must extend \"org.gimp.GIMP\"."
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|success
operator|&&
name|g_strcmp0
argument_list|(
name|as_app_get_id
argument_list|(
name|app
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|extension
argument_list|)
argument_list|)
operator|!=
literal|0
condition|)
block|{
comment|/* Extension IDs will be unique and we want therefore the        * installation folder to sync in order to avoid path clashes.        */
if|if
condition|(
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
condition|)
operator|*
name|error
operator|=
name|g_error_new
argument_list|(
name|GIMP_EXTENSION_ERROR
argument_list|,
name|GIMP_EXTENSION_FAILED
argument_list|,
name|_
argument_list|(
literal|"Extension AppData id (\"%s\") and directory (\"%s\") must be the same."
argument_list|)
argument_list|,
name|as_app_get_id
argument_list|(
name|app
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|extension
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|release
operator|=
name|as_app_get_release_default
argument_list|(
name|app
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
operator|&&
operator|(
operator|!
name|release
operator|||
operator|!
name|as_release_get_version
argument_list|(
name|release
argument_list|)
operator|)
condition|)
block|{
comment|/* We don't need the detail, just to know that the extension has a        * release tag with a version. This is very important since it is        * the only way we can manage updates.        */
if|if
condition|(
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
condition|)
operator|*
name|error
operator|=
name|g_error_new
argument_list|(
name|GIMP_EXTENSION_ERROR
argument_list|,
name|GIMP_EXTENSION_NO_VERSION
argument_list|,
name|_
argument_list|(
literal|"Extension AppData must advertize a version in a<release> tag."
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|requires
operator|=
name|as_app_get_requires
argument_list|(
name|app
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
operator|&&
name|requires
condition|)
block|{
name|gint
name|i
decl_stmt|;
comment|/* An extension could set requirements, in particular a range of        * supported version of GIMP, but also other extensions.        */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|requires
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|AsRequire
modifier|*
name|require
init|=
name|g_ptr_array_index
argument_list|(
name|requires
argument_list|,
name|i
argument_list|)
decl_stmt|;
if|if
condition|(
name|as_require_get_kind
argument_list|(
name|require
argument_list|)
operator|==
name|AS_REQUIRE_KIND_ID
operator|&&
name|g_strcmp0
argument_list|(
name|as_require_get_value
argument_list|(
name|require
argument_list|)
argument_list|,
literal|"org.gimp.GIMP"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
operator|!
name|as_require_version_compare
argument_list|(
name|require
argument_list|,
name|GIMP_APP_VERSION
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
block|}
elseif|else
if|if
condition|(
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
condition|)
block|{
comment|/* Right now we only support requirement relative to GIMP                * version.                */
operator|*
name|error
operator|=
name|g_error_new
argument_list|(
name|GIMP_EXTENSION_ERROR
argument_list|,
name|GIMP_EXTENSION_FAILED
argument_list|,
name|_
argument_list|(
literal|"Unsupported<requires> \"%s\" (type %s)."
argument_list|)
argument_list|,
name|as_require_get_value
argument_list|(
name|require
argument_list|)
argument_list|,
name|as_require_kind_to_string
argument_list|(
name|as_require_get_kind
argument_list|(
name|require
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
block|}
block|}
if|if
condition|(
name|success
condition|)
name|extension
operator|->
name|p
operator|->
name|app
operator|=
name|app
expr_stmt|;
else|else
name|g_object_unref
argument_list|(
name|app
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_extension_run (GimpExtension * extension,GError ** error)
name|gimp_extension_run
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GHashTable
modifier|*
name|metadata
decl_stmt|;
name|gchar
modifier|*
name|value
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|extension
operator|->
name|p
operator|->
name|app
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_extension_stop
argument_list|(
name|extension
argument_list|)
expr_stmt|;
name|metadata
operator|=
name|as_app_get_metadata
argument_list|(
name|extension
operator|->
name|p
operator|->
name|app
argument_list|)
expr_stmt|;
name|value
operator|=
name|g_hash_table_lookup
argument_list|(
name|metadata
argument_list|,
literal|"GIMP::brush-path"
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|brush_paths
operator|=
name|gimp_extension_validate_paths
argument_list|(
name|extension
argument_list|,
name|value
argument_list|,
name|TRUE
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
operator|*
name|error
operator|)
condition|)
block|{
name|value
operator|=
name|g_hash_table_lookup
argument_list|(
name|metadata
argument_list|,
literal|"GIMP::dynamics-path"
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|dynamics_paths
operator|=
name|gimp_extension_validate_paths
argument_list|(
name|extension
argument_list|,
name|value
argument_list|,
name|TRUE
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
operator|*
name|error
operator|)
condition|)
block|{
name|value
operator|=
name|g_hash_table_lookup
argument_list|(
name|metadata
argument_list|,
literal|"GIMP::mypaint-brush-path"
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|mypaint_brush_paths
operator|=
name|gimp_extension_validate_paths
argument_list|(
name|extension
argument_list|,
name|value
argument_list|,
name|TRUE
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
operator|*
name|error
operator|)
condition|)
block|{
name|value
operator|=
name|g_hash_table_lookup
argument_list|(
name|metadata
argument_list|,
literal|"GIMP::pattern-path"
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|pattern_paths
operator|=
name|gimp_extension_validate_paths
argument_list|(
name|extension
argument_list|,
name|value
argument_list|,
name|TRUE
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
operator|*
name|error
operator|)
condition|)
block|{
name|value
operator|=
name|g_hash_table_lookup
argument_list|(
name|metadata
argument_list|,
literal|"GIMP::gradient-path"
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|gradient_paths
operator|=
name|gimp_extension_validate_paths
argument_list|(
name|extension
argument_list|,
name|value
argument_list|,
name|TRUE
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
operator|*
name|error
operator|)
condition|)
block|{
name|value
operator|=
name|g_hash_table_lookup
argument_list|(
name|metadata
argument_list|,
literal|"GIMP::palette-path"
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|palette_paths
operator|=
name|gimp_extension_validate_paths
argument_list|(
name|extension
argument_list|,
name|value
argument_list|,
name|TRUE
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
operator|*
name|error
operator|)
condition|)
block|{
name|value
operator|=
name|g_hash_table_lookup
argument_list|(
name|metadata
argument_list|,
literal|"GIMP::tool-preset-path"
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|tool_preset_paths
operator|=
name|gimp_extension_validate_paths
argument_list|(
name|extension
argument_list|,
name|value
argument_list|,
name|TRUE
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
operator|*
name|error
operator|)
condition|)
block|{
name|value
operator|=
name|g_hash_table_lookup
argument_list|(
name|metadata
argument_list|,
literal|"GIMP::plug-in-path"
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|plug_in_paths
operator|=
name|gimp_extension_validate_paths
argument_list|(
name|extension
argument_list|,
name|value
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|*
name|error
condition|)
name|gimp_extension_stop
argument_list|(
name|extension
argument_list|)
expr_stmt|;
return|return
operator|(
operator|*
name|error
operator|==
name|NULL
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_extension_stop (GimpExtension * extension)
name|gimp_extension_stop
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
block|{
name|g_list_free_full
argument_list|(
name|extension
operator|->
name|p
operator|->
name|brush_paths
argument_list|,
name|g_object_unref
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|brush_paths
operator|=
name|NULL
expr_stmt|;
name|g_list_free_full
argument_list|(
name|extension
operator|->
name|p
operator|->
name|dynamics_paths
argument_list|,
name|g_object_unref
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|dynamics_paths
operator|=
name|NULL
expr_stmt|;
name|g_list_free_full
argument_list|(
name|extension
operator|->
name|p
operator|->
name|mypaint_brush_paths
argument_list|,
name|g_object_unref
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|brush_paths
operator|=
name|NULL
expr_stmt|;
name|g_list_free_full
argument_list|(
name|extension
operator|->
name|p
operator|->
name|pattern_paths
argument_list|,
name|g_object_unref
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|pattern_paths
operator|=
name|NULL
expr_stmt|;
name|g_list_free_full
argument_list|(
name|extension
operator|->
name|p
operator|->
name|gradient_paths
argument_list|,
name|g_object_unref
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|gradient_paths
operator|=
name|NULL
expr_stmt|;
name|g_list_free_full
argument_list|(
name|extension
operator|->
name|p
operator|->
name|palette_paths
argument_list|,
name|g_object_unref
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|palette_paths
operator|=
name|NULL
expr_stmt|;
name|g_list_free_full
argument_list|(
name|extension
operator|->
name|p
operator|->
name|tool_preset_paths
argument_list|,
name|g_object_unref
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|tool_preset_paths
operator|=
name|NULL
expr_stmt|;
name|g_list_free_full
argument_list|(
name|extension
operator|->
name|p
operator|->
name|plug_in_paths
argument_list|,
name|g_object_unref
argument_list|)
expr_stmt|;
name|extension
operator|->
name|p
operator|->
name|plug_in_paths
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_extension_get_brush_paths (GimpExtension * extension)
name|gimp_extension_get_brush_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
block|{
return|return
name|extension
operator|->
name|p
operator|->
name|brush_paths
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_extension_get_dynamics_paths (GimpExtension * extension)
name|gimp_extension_get_dynamics_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
block|{
return|return
name|extension
operator|->
name|p
operator|->
name|dynamics_paths
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_extension_get_mypaint_brush_paths (GimpExtension * extension)
name|gimp_extension_get_mypaint_brush_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
block|{
return|return
name|extension
operator|->
name|p
operator|->
name|mypaint_brush_paths
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_extension_get_pattern_paths (GimpExtension * extension)
name|gimp_extension_get_pattern_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
block|{
return|return
name|extension
operator|->
name|p
operator|->
name|pattern_paths
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_extension_get_gradient_paths (GimpExtension * extension)
name|gimp_extension_get_gradient_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
block|{
return|return
name|extension
operator|->
name|p
operator|->
name|gradient_paths
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_extension_get_palette_paths (GimpExtension * extension)
name|gimp_extension_get_palette_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
block|{
return|return
name|extension
operator|->
name|p
operator|->
name|palette_paths
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_extension_get_tool_preset_paths (GimpExtension * extension)
name|gimp_extension_get_tool_preset_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
block|{
return|return
name|extension
operator|->
name|p
operator|->
name|tool_preset_paths
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_extension_get_plug_in_paths (GimpExtension * extension)
name|gimp_extension_get_plug_in_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
block|{
return|return
name|extension
operator|->
name|p
operator|->
name|plug_in_paths
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_extension_validate_paths:  * @extension: the #GimpExtension  * @path:      A list of directories separated by ':'.  * @error:  *  * Very similar to gimp_path_parse() except that we don't use  * G_SEARCHPATH_SEPARATOR as path separator, because it must not be  * os-dependent.  * Also we only allow relative path which are children of the main  * extension directory (we do not allow extensions to list external  * folders).  *  * Returns: A #GList of #GFile as listed in @path.  **/
end_comment

begin_function
specifier|static
name|GList
modifier|*
DECL|function|gimp_extension_validate_paths (GimpExtension * extension,const gchar * paths,gboolean as_directories,GError ** error)
name|gimp_extension_validate_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|,
specifier|const
name|gchar
modifier|*
name|paths
parameter_list|,
name|gboolean
name|as_directories
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gchar
modifier|*
modifier|*
name|patharray
decl_stmt|;
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|paths
operator|||
operator|!
operator|(
operator|*
name|paths
operator|)
condition|)
return|return
name|NULL
return|;
name|patharray
operator|=
name|g_strsplit
argument_list|(
name|paths
argument_list|,
literal|":"
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|patharray
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
comment|/* Note: appstream-glib is supposed to return everything as UTF-8,        * so we should not have to bother about this. */
name|gchar
modifier|*
name|path
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GFile
modifier|*
name|ext_dir
decl_stmt|;
name|GFile
modifier|*
name|parent
decl_stmt|;
name|GFile
modifier|*
name|child
decl_stmt|;
name|gboolean
name|is_subpath
init|=
name|FALSE
decl_stmt|;
name|gint
name|max_depth
init|=
literal|10
decl_stmt|;
if|if
condition|(
name|g_path_is_absolute
argument_list|(
name|patharray
index|[
name|i
index|]
argument_list|)
condition|)
block|{
operator|*
name|error
operator|=
name|g_error_new
argument_list|(
name|GIMP_EXTENSION_ERROR
argument_list|,
name|GIMP_EXTENSION_BAD_PATH
argument_list|,
name|_
argument_list|(
literal|"'%s' is not a relative path."
argument_list|)
argument_list|,
name|patharray
index|[
name|i
index|]
argument_list|)
expr_stmt|;
break|break;
block|}
name|path
operator|=
name|g_build_filename
argument_list|(
name|extension
operator|->
name|p
operator|->
name|path
argument_list|,
name|patharray
index|[
name|i
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|ext_dir
operator|=
name|g_file_new_for_path
argument_list|(
name|extension
operator|->
name|p
operator|->
name|path
argument_list|)
expr_stmt|;
comment|/* Even with relative paths, it is easy to trick the system        * and leak out of the extension. So check actual kinship.        */
name|child
operator|=
name|g_object_ref
argument_list|(
name|file
argument_list|)
expr_stmt|;
while|while
condition|(
name|max_depth
operator|>
literal|0
operator|&&
operator|(
name|parent
operator|=
name|g_file_get_parent
argument_list|(
name|child
argument_list|)
operator|)
condition|)
block|{
if|if
condition|(
name|g_file_equal
argument_list|(
name|parent
argument_list|,
name|ext_dir
argument_list|)
condition|)
block|{
name|is_subpath
operator|=
name|TRUE
expr_stmt|;
name|g_object_unref
argument_list|(
name|parent
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_object_unref
argument_list|(
name|child
argument_list|)
expr_stmt|;
name|child
operator|=
name|parent
expr_stmt|;
comment|/* Avoid unfinite looping. */
name|max_depth
operator|--
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|child
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|ext_dir
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|is_subpath
condition|)
block|{
operator|*
name|error
operator|=
name|g_error_new
argument_list|(
name|GIMP_EXTENSION_ERROR
argument_list|,
name|GIMP_EXTENSION_BAD_PATH
argument_list|,
name|_
argument_list|(
literal|"'%s' is not a child of the extension."
argument_list|)
argument_list|,
name|patharray
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|as_directories
condition|)
block|{
if|if
condition|(
name|g_file_query_file_type
argument_list|(
name|file
argument_list|,
name|G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS
argument_list|,
name|NULL
argument_list|)
operator|!=
name|G_FILE_TYPE_DIRECTORY
condition|)
block|{
operator|*
name|error
operator|=
name|g_error_new
argument_list|(
name|GIMP_EXTENSION_ERROR
argument_list|,
name|GIMP_EXTENSION_BAD_PATH
argument_list|,
name|_
argument_list|(
literal|"'%s' is not a directory."
argument_list|)
argument_list|,
name|patharray
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
else|else
block|{
if|if
condition|(
name|g_file_query_file_type
argument_list|(
name|file
argument_list|,
name|G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS
argument_list|,
name|NULL
argument_list|)
operator|!=
name|G_FILE_TYPE_REGULAR
condition|)
block|{
operator|*
name|error
operator|=
name|g_error_new
argument_list|(
name|GIMP_EXTENSION_ERROR
argument_list|,
name|GIMP_EXTENSION_BAD_PATH
argument_list|,
name|_
argument_list|(
literal|"'%s' is not a valid file."
argument_list|)
argument_list|,
name|patharray
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
name|g_return_val_if_fail
argument_list|(
name|path
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_list_find_custom
argument_list|(
name|list
argument_list|,
name|file
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|g_file_equal
argument_list|)
condition|)
block|{
comment|/* Silently ignore duplicate paths. */
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
continue|continue;
block|}
name|list
operator|=
name|g_list_prepend
argument_list|(
name|list
argument_list|,
name|file
argument_list|)
expr_stmt|;
block|}
name|g_strfreev
argument_list|(
name|patharray
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_reverse
argument_list|(
name|list
argument_list|)
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

end_unit

