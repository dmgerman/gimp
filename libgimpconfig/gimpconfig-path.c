begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpconfig-path.c  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-error.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-path.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimpconfig-path  * @title: GimpConfig-path  * @short_description: File path utilities for libgimpconfig.  *  * File path utilities for libgimpconfig.  **/
end_comment

begin_comment
comment|/**  * gimp_config_path_get_type:  *  * Reveals the object type  *  * Returns: the #GType for a GimpConfigPath string property  *  * Since: 2.4  **/
end_comment

begin_function
name|GType
DECL|function|gimp_config_path_get_type (void)
name|gimp_config_path_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|path_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|path_type
condition|)
block|{
specifier|const
name|GTypeInfo
name|type_info
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|path_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_STRING
argument_list|,
literal|"GimpConfigPath"
argument_list|,
operator|&
name|type_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|path_type
return|;
block|}
end_function

begin_comment
comment|/*  * GIMP_TYPE_PARAM_CONFIG_PATH  */
end_comment

begin_define
DECL|macro|GIMP_PARAM_SPEC_CONFIG_PATH (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_CONFIG_PATH
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_CONFIG_PATH, GimpParamSpecConfigPath))
end_define

begin_typedef
DECL|typedef|GimpParamSpecConfigPath
typedef|typedef
name|struct
name|_GimpParamSpecConfigPath
name|GimpParamSpecConfigPath
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecConfigPath
struct|struct
name|_GimpParamSpecConfigPath
block|{
DECL|member|parent_instance
name|GParamSpecString
name|parent_instance
decl_stmt|;
DECL|member|type
name|GimpConfigPathType
name|type
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_param_config_path_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_param_config_path_get_type:  *  * Reveals the object type  *  * Returns: the #GType for a directory path object  *  * Since: 2.4  **/
end_comment

begin_function
name|GType
DECL|function|gimp_param_config_path_get_type (void)
name|gimp_param_config_path_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|spec_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|spec_type
condition|)
block|{
specifier|const
name|GTypeInfo
name|type_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GParamSpecClass
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_param_config_path_class_init
block|,
name|NULL
block|,
name|NULL
block|,
sizeof|sizeof
argument_list|(
name|GimpParamSpecConfigPath
argument_list|)
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
name|spec_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_PARAM_STRING
argument_list|,
literal|"GimpParamConfigPath"
argument_list|,
operator|&
name|type_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|spec_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_config_path_class_init (GParamSpecClass * class)
name|gimp_param_config_path_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
block|{
name|class
operator|->
name|value_type
operator|=
name|GIMP_TYPE_CONFIG_PATH
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_param_spec_config_path:  * @name:          Canonical name of the param  * @nick:          Nickname of the param  * @blurb:         Brief description of param.  * @type:          a #GimpConfigPathType value.  * @default_value: Value to use if none is assigned.  * @flags:         a combination of #GParamFlags  *  * Creates a param spec to hold a filename, dir name,  * or list of file or dir names.  * See g_param_spec_internal() for more information.  *  * Returns: a newly allocated #GParamSpec instance  *  * Since: 2.4  **/
end_comment

begin_function
name|GParamSpec
modifier|*
DECL|function|gimp_param_spec_config_path (const gchar * name,const gchar * nick,const gchar * blurb,GimpConfigPathType type,const gchar * default_value,GParamFlags flags)
name|gimp_param_spec_config_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|GimpConfigPathType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GParamSpecString
modifier|*
name|pspec
decl_stmt|;
name|pspec
operator|=
name|g_param_spec_internal
argument_list|(
name|GIMP_TYPE_PARAM_CONFIG_PATH
argument_list|,
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|pspec
operator|->
name|default_value
operator|=
name|g_strdup
argument_list|(
name|default_value
argument_list|)
expr_stmt|;
name|GIMP_PARAM_SPEC_CONFIG_PATH
argument_list|(
name|pspec
argument_list|)
operator|->
name|type
operator|=
name|type
expr_stmt|;
return|return
name|G_PARAM_SPEC
argument_list|(
name|pspec
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_param_spec_config_path_type:  * @pspec:         A #GParamSpec for a path param  *  * Tells whether the path param encodes a filename,  * dir name, or list of file or dir names.  *  * Returns: a #GimpConfigPathType value  *  * Since: 2.4  **/
end_comment

begin_function
name|GimpConfigPathType
DECL|function|gimp_param_spec_config_path_type (GParamSpec * pspec)
name|gimp_param_spec_config_path_type
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PARAM_SPEC_CONFIG_PATH
argument_list|(
name|pspec
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|GIMP_PARAM_SPEC_CONFIG_PATH
argument_list|(
name|pspec
argument_list|)
operator|->
name|type
return|;
block|}
end_function

begin_comment
comment|/*  * GimpConfig path utilities  */
end_comment

begin_decl_stmt
specifier|static
name|gchar
modifier|*
name|gimp_config_path_expand_only
argument_list|(
specifier|const
name|gchar
operator|*
name|path
argument_list|,
name|GError
operator|*
operator|*
name|error
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
specifier|inline
name|gchar
modifier|*
name|gimp_config_path_extract_token
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|str
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|static
name|gchar
modifier|*
name|gimp_config_path_unexpand_only
argument_list|(
specifier|const
name|gchar
operator|*
name|path
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**  * gimp_config_build_data_path:  * @name: directory name (in UTF-8 encoding)  *  * Creates a search path as it is used in the gimprc file.  The path  * returned by gimp_config_build_data_path() includes a directory  * below the user's gimp directory and one in the system-wide data  * directory.  *  * Note that you cannot use this path directly with gimp_path_parse().  * As it is in the gimprc notation, you first need to expand and  * recode it using gimp_config_path_expand().  *  * Returns: a newly allocated string  *  * Since: 2.4  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_config_build_data_path (const gchar * name)
name|gimp_config_build_data_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|g_strconcat
argument_list|(
literal|"${gimp_dir}"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|name
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|,
literal|"${gimp_data_dir}"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_build_plug_in_path:  * @name: directory name (in UTF-8 encoding)  *  * Creates a search path as it is used in the gimprc file.  The path  * returned by gimp_config_build_plug_in_path() includes a directory  * below the user's gimp directory and one in the system-wide plug-in  * directory.  *  * Note that you cannot use this path directly with gimp_path_parse().  * As it is in the gimprc notation, you first need to expand and  * recode it using gimp_config_path_expand().  *  * Returns: a newly allocated string  *  * Since: 2.4  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_config_build_plug_in_path (const gchar * name)
name|gimp_config_build_plug_in_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|g_strconcat
argument_list|(
literal|"${gimp_dir}"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|name
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|,
literal|"${gimp_plug_in_dir}"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_build_writable_path:  * @name: directory name (in UTF-8 encoding)  *  * Creates a search path as it is used in the gimprc file.  The path  * returned by gimp_config_build_writable_path() is just the writable  * parts of the search path constructed by gimp_config_build_data_path().  *  * Note that you cannot use this path directly with gimp_path_parse().  * As it is in the gimprc notation, you first need to expand and  * recode it using gimp_config_path_expand().  *  * Returns: a newly allocated string  *  * Since: 2.4  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_config_build_writable_path (const gchar * name)
name|gimp_config_build_writable_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|g_strconcat
argument_list|(
literal|"${gimp_dir}"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_path_expand:  * @path:   a NUL-terminated string in UTF-8 encoding  * @recode: whether to convert to the filesystem's encoding  * @error:  return location for errors  *  * Paths as stored in gimprc and other config files have to be treated  * special.  The string may contain special identifiers such as for  * example ${gimp_dir} that have to be substituted before use. Also  * the user's filesystem may be in a different encoding than UTF-8  * (which is what is used for the gimprc). This function does the  * variable substitution for you and can also attempt to convert to  * the filesystem encoding.  *  * To reverse the expansion, use gimp_config_path_unexpand().  *  * Return value: a newly allocated NUL-terminated string  *  * Since: 2.4  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_config_path_expand (const gchar * path,gboolean recode,GError ** error)
name|gimp_config_path_expand
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gboolean
name|recode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|path
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|recode
condition|)
block|{
name|gchar
modifier|*
name|retval
decl_stmt|;
name|gchar
modifier|*
name|expanded
init|=
name|gimp_config_path_expand_only
argument_list|(
name|path
argument_list|,
name|error
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|expanded
condition|)
return|return
name|NULL
return|;
name|retval
operator|=
name|g_filename_from_utf8
argument_list|(
name|expanded
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|expanded
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
return|return
name|gimp_config_path_expand_only
argument_list|(
name|path
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_path_expand_to_files:  * @path:  a NUL-terminated string in UTF-8 encoding  * @error: return location for errors  *  * Paths as stored in the gimprc have to be treated special. The  * string may contain special identifiers such as for example  * ${gimp_dir} that have to be substituted before use. Also the user's  * filesystem may be in a different encoding than UTF-8 (which is what  * is used for the gimprc).  *  * This function runs @path through gimp_config_path_expand() and  * gimp_path_parse(), then turns the filenames returned by  * gimp_path_parse() into GFile using g_file_new_for_path().  *  * Return value: a #GList of newly allocated #GFile objects.  *  * Since: 2.10  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_config_path_expand_to_files (const gchar * path,GError ** error)
name|gimp_config_path_expand_to_files
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GList
modifier|*
name|files
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|expanded
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|path
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|expanded
operator|=
name|gimp_config_path_expand
argument_list|(
name|path
argument_list|,
name|TRUE
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|expanded
condition|)
return|return
name|NULL
return|;
name|files
operator|=
name|gimp_path_parse
argument_list|(
name|expanded
argument_list|,
literal|256
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|expanded
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|files
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
name|gchar
modifier|*
name|dir
init|=
name|list
operator|->
name|data
decl_stmt|;
name|list
operator|->
name|data
operator|=
name|g_file_new_for_path
argument_list|(
name|dir
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dir
argument_list|)
expr_stmt|;
block|}
return|return
name|files
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_path_unexpand:  * @path:   a NUL-terminated string  * @recode: whether @path is in filesystem encoding or UTF-8  * @error:  return location for errors  *  * The inverse operation of gimp_config_path_expand()  *  * This function takes a @path and tries to substitute the first  * elements by well-known special identifiers such as for example  * ${gimp_dir}. The unexpanded path can then be stored in gimprc and  * other config files.  *  * If @recode is %TRUE then @path is in local filesystem encoding,  * if @recode is %FALSE then @path is assumed to be UTF-8.  *  * Return value: a newly allocated NUL-terminated UTF-8 string  *  * Since: 2.10  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_config_path_unexpand (const gchar * path,gboolean recode,GError ** error)
name|gimp_config_path_unexpand
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gboolean
name|recode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|path
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|recode
condition|)
block|{
name|gchar
modifier|*
name|retval
decl_stmt|;
name|gchar
modifier|*
name|utf8
init|=
name|g_filename_to_utf8
argument_list|(
name|path
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|utf8
condition|)
return|return
name|NULL
return|;
name|retval
operator|=
name|gimp_config_path_unexpand_only
argument_list|(
name|utf8
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|utf8
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
return|return
name|gimp_config_path_unexpand_only
argument_list|(
name|path
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_new_for_config_path:  * @path:   a NUL-terminated string in UTF-8 encoding  * @error:  return location for errors  *  * Expands @path using gimp_config_path_expand() and returns a #GFile  * for the expanded path.  *  * To reverse the expansion, use gimp_file_get_config_path().  *  * Return value: a newly allocated #GFile, or %NULL if the expansion failed.  *  * Since: 2.10  **/
end_comment

begin_function
name|GFile
modifier|*
DECL|function|gimp_file_new_for_config_path (const gchar * path,GError ** error)
name|gimp_file_new_for_config_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
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
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|expanded
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|path
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|expanded
operator|=
name|gimp_config_path_expand
argument_list|(
name|path
argument_list|,
name|TRUE
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|expanded
condition|)
block|{
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|expanded
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|expanded
argument_list|)
expr_stmt|;
block|}
return|return
name|file
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_get_config_path:  * @file:   a #GFile  * @error:  return location for errors  *  * Unexpands @file's path using gimp_config_path_unexpand() and  * returns the unexpanded path.  *  * The inverse operation of gimp_file_new_for_config_path().  *  * Return value: a newly allocated NUL-terminated UTF-8 string, or %NULL if  *               unexpanding failed.  *  * Since: 2.10  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_file_get_config_path (GFile * file,GError ** error)
name|gimp_file_get_config_path
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gchar
modifier|*
name|unexpanded
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|path
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|path
operator|=
name|g_file_get_path
argument_list|(
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|path
condition|)
block|{
name|unexpanded
operator|=
name|gimp_config_path_unexpand
argument_list|(
name|path
argument_list|,
name|TRUE
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"File has no path representation"
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|unexpanded
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_define
DECL|macro|SUBSTS_ALLOC
define|#
directive|define
name|SUBSTS_ALLOC
value|4
end_define

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_config_path_expand_only (const gchar * path,GError ** error)
name|gimp_config_path_expand_only
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|home
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|p
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|s
decl_stmt|;
name|gchar
modifier|*
name|n
decl_stmt|;
name|gchar
modifier|*
name|token
decl_stmt|;
name|gchar
modifier|*
name|filename
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|expanded
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|substs
init|=
name|NULL
decl_stmt|;
name|guint
name|n_substs
init|=
literal|0
decl_stmt|;
name|gint
name|length
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|home
operator|=
name|g_get_home_dir
argument_list|()
expr_stmt|;
if|if
condition|(
name|home
condition|)
name|home
operator|=
name|gimp_filename_to_utf8
argument_list|(
name|home
argument_list|)
expr_stmt|;
name|p
operator|=
name|path
expr_stmt|;
while|while
condition|(
operator|*
name|p
condition|)
block|{
if|if
condition|(
operator|*
name|p
operator|==
literal|'~'
operator|&&
name|home
condition|)
block|{
name|length
operator|+=
name|strlen
argument_list|(
name|home
argument_list|)
expr_stmt|;
name|p
operator|+=
literal|1
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|token
operator|=
name|gimp_config_path_extract_token
argument_list|(
operator|&
name|p
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_substs
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|strcmp
argument_list|(
name|substs
index|[
literal|2
operator|*
name|i
index|]
argument_list|,
name|token
argument_list|)
operator|==
literal|0
condition|)
break|break;
if|if
condition|(
name|i
operator|<
name|n_substs
condition|)
block|{
name|s
operator|=
name|substs
index|[
literal|2
operator|*
name|i
operator|+
literal|1
index|]
expr_stmt|;
block|}
else|else
block|{
name|s
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|token
argument_list|,
literal|"gimp_dir"
argument_list|)
operator|==
literal|0
condition|)
name|s
operator|=
name|gimp_directory
argument_list|()
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|token
argument_list|,
literal|"gimp_data_dir"
argument_list|)
operator|==
literal|0
condition|)
name|s
operator|=
name|gimp_data_directory
argument_list|()
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|token
argument_list|,
literal|"gimp_plug_in_dir"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|token
argument_list|,
literal|"gimp_plugin_dir"
argument_list|)
operator|==
literal|0
condition|)
name|s
operator|=
name|gimp_plug_in_directory
argument_list|()
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|token
argument_list|,
literal|"gimp_sysconf_dir"
argument_list|)
operator|==
literal|0
condition|)
name|s
operator|=
name|gimp_sysconf_directory
argument_list|()
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|token
argument_list|,
literal|"gimp_installation_dir"
argument_list|)
operator|==
literal|0
condition|)
name|s
operator|=
name|gimp_installation_directory
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|s
condition|)
name|s
operator|=
name|g_getenv
argument_list|(
name|token
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
comment|/* The default user gimprc on Windows references                * ${TEMP}, but not all Windows installations have that                * environment variable, even if it should be kinda                * standard. So special-case it.                */
if|if
condition|(
operator|!
name|s
operator|&&
name|strcmp
argument_list|(
name|token
argument_list|,
literal|"TEMP"
argument_list|)
operator|==
literal|0
condition|)
name|s
operator|=
name|g_get_tmp_dir
argument_list|()
expr_stmt|;
endif|#
directive|endif
comment|/* G_OS_WIN32 */
block|}
if|if
condition|(
operator|!
name|s
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_PARSE
argument_list|,
name|_
argument_list|(
literal|"Cannot expand ${%s}"
argument_list|)
argument_list|,
name|token
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|token
argument_list|)
expr_stmt|;
goto|goto
name|cleanup
goto|;
block|}
if|if
condition|(
name|n_substs
operator|%
name|SUBSTS_ALLOC
operator|==
literal|0
condition|)
name|substs
operator|=
name|g_renew
argument_list|(
name|gchar
operator|*
argument_list|,
name|substs
argument_list|,
literal|2
operator|*
operator|(
name|n_substs
operator|+
name|SUBSTS_ALLOC
operator|)
argument_list|)
expr_stmt|;
name|substs
index|[
literal|2
operator|*
name|n_substs
index|]
operator|=
name|token
expr_stmt|;
name|substs
index|[
literal|2
operator|*
name|n_substs
operator|+
literal|1
index|]
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gimp_filename_to_utf8
argument_list|(
name|s
argument_list|)
expr_stmt|;
name|length
operator|+=
name|strlen
argument_list|(
name|substs
index|[
literal|2
operator|*
name|n_substs
operator|+
literal|1
index|]
argument_list|)
expr_stmt|;
name|n_substs
operator|++
expr_stmt|;
block|}
else|else
block|{
name|length
operator|+=
name|g_utf8_skip
index|[
operator|(
specifier|const
name|guchar
operator|)
operator|*
name|p
index|]
expr_stmt|;
name|p
operator|=
name|g_utf8_next_char
argument_list|(
name|p
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|n_substs
operator|==
literal|0
condition|)
return|return
name|g_strdup
argument_list|(
name|path
argument_list|)
return|;
name|expanded
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|length
operator|+
literal|1
argument_list|)
expr_stmt|;
name|p
operator|=
name|path
expr_stmt|;
name|n
operator|=
name|expanded
expr_stmt|;
while|while
condition|(
operator|*
name|p
condition|)
block|{
if|if
condition|(
operator|*
name|p
operator|==
literal|'~'
operator|&&
name|home
condition|)
block|{
operator|*
name|n
operator|=
literal|'\0'
expr_stmt|;
name|strcat
argument_list|(
name|n
argument_list|,
name|home
argument_list|)
expr_stmt|;
name|n
operator|+=
name|strlen
argument_list|(
name|home
argument_list|)
expr_stmt|;
name|p
operator|+=
literal|1
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|token
operator|=
name|gimp_config_path_extract_token
argument_list|(
operator|&
name|p
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_substs
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
name|substs
index|[
literal|2
operator|*
name|i
index|]
argument_list|,
name|token
argument_list|)
operator|==
literal|0
condition|)
block|{
name|s
operator|=
name|substs
index|[
literal|2
operator|*
name|i
operator|+
literal|1
index|]
expr_stmt|;
operator|*
name|n
operator|=
literal|'\0'
expr_stmt|;
name|strcat
argument_list|(
name|n
argument_list|,
name|s
argument_list|)
expr_stmt|;
name|n
operator|+=
name|strlen
argument_list|(
name|s
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
name|g_free
argument_list|(
name|token
argument_list|)
expr_stmt|;
block|}
else|else
block|{
operator|*
name|n
operator|++
operator|=
operator|*
name|p
operator|++
expr_stmt|;
block|}
block|}
operator|*
name|n
operator|=
literal|'\0'
expr_stmt|;
name|cleanup
label|:
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_substs
condition|;
name|i
operator|++
control|)
name|g_free
argument_list|(
name|substs
index|[
literal|2
operator|*
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|substs
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|expanded
return|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|gchar
modifier|*
DECL|function|gimp_config_path_extract_token (const gchar ** str)
name|gimp_config_path_extract_token
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|str
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|p
decl_stmt|;
name|gchar
modifier|*
name|token
decl_stmt|;
if|if
condition|(
name|strncmp
argument_list|(
operator|*
name|str
argument_list|,
literal|"${"
argument_list|,
literal|2
argument_list|)
condition|)
return|return
name|NULL
return|;
name|p
operator|=
operator|*
name|str
operator|+
literal|2
expr_stmt|;
while|while
condition|(
operator|*
name|p
operator|&&
operator|(
operator|*
name|p
operator|!=
literal|'}'
operator|)
condition|)
name|p
operator|=
name|g_utf8_next_char
argument_list|(
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|*
name|p
condition|)
return|return
name|NULL
return|;
name|token
operator|=
name|g_strndup
argument_list|(
operator|*
name|str
operator|+
literal|2
argument_list|,
name|g_utf8_pointer_to_offset
argument_list|(
operator|*
name|str
operator|+
literal|2
argument_list|,
name|p
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|str
operator|=
name|p
operator|+
literal|1
expr_stmt|;
comment|/* after the closing bracket */
return|return
name|token
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_config_path_unexpand_only (const gchar * path)
name|gimp_config_path_unexpand_only
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|)
block|{
specifier|const
struct|struct
DECL|struct|__anon2b82e58b0108
block|{
DECL|member|id
specifier|const
name|gchar
modifier|*
name|id
decl_stmt|;
DECL|member|prefix
specifier|const
name|gchar
modifier|*
name|prefix
decl_stmt|;
block|}
name|identifiers
index|[]
init|=
block|{
block|{
literal|"${gimp_plug_in_dir}"
block|,
name|gimp_plug_in_directory
argument_list|()
block|}
block|,
block|{
literal|"${gimp_data_dir}"
block|,
name|gimp_data_directory
argument_list|()
block|}
block|,
block|{
literal|"${gimp_sysconf_dir}"
block|,
name|gimp_sysconf_directory
argument_list|()
block|}
block|,
block|{
literal|"${gimp_installation_dir}"
block|,
name|gimp_installation_directory
argument_list|()
block|}
block|,
block|{
literal|"${gimp_dir}"
block|,
name|gimp_directory
argument_list|()
block|}
block|}
struct|;
name|GList
modifier|*
name|files
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|unexpanded
decl_stmt|;
name|files
operator|=
name|gimp_path_parse
argument_list|(
name|path
argument_list|,
literal|256
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|files
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
name|gchar
modifier|*
name|dir
init|=
name|list
operator|->
name|data
decl_stmt|;
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
name|identifiers
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|dir
argument_list|,
name|identifiers
index|[
name|i
index|]
operator|.
name|prefix
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|tmp
init|=
name|g_strconcat
argument_list|(
name|identifiers
index|[
name|i
index|]
operator|.
name|id
argument_list|,
name|dir
operator|+
name|strlen
argument_list|(
name|identifiers
index|[
name|i
index|]
operator|.
name|prefix
argument_list|)
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|dir
argument_list|)
expr_stmt|;
name|list
operator|->
name|data
operator|=
name|tmp
expr_stmt|;
break|break;
block|}
block|}
block|}
name|unexpanded
operator|=
name|gimp_path_to_str
argument_list|(
name|files
argument_list|)
expr_stmt|;
name|gimp_path_free
argument_list|(
name|files
argument_list|)
expr_stmt|;
return|return
name|unexpanded
return|;
block|}
end_function

end_unit

