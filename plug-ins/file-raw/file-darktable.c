begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-darktable.c -- raw file format plug-in that uses darktable  * Copyright (C) 2012 Simon Budig<simon@gimp.org>  * Copyright (C) 2016 Tobias Ellinghaus<me@houz.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_include
include|#
directive|include
file|"file-raw-formats.h"
end_include

begin_include
include|#
directive|include
file|"file-raw-utils.h"
end_include

begin_define
DECL|macro|LOAD_THUMB_PROC
define|#
directive|define
name|LOAD_THUMB_PROC
value|"file-darktable-load-thumb"
end_define

begin_define
DECL|macro|REGISTRY_KEY_BASE
define|#
directive|define
name|REGISTRY_KEY_BASE
value|"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\darktable"
end_define

begin_typedef
DECL|typedef|Darktable
typedef|typedef
name|struct
name|_Darktable
name|Darktable
typedef|;
end_typedef

begin_typedef
DECL|typedef|DarktableClass
typedef|typedef
name|struct
name|_DarktableClass
name|DarktableClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Darktable
struct|struct
name|_Darktable
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_DarktableClass
struct|struct
name|_DarktableClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|DARKTABLE_TYPE
define|#
directive|define
name|DARKTABLE_TYPE
value|(darktable_get_type ())
end_define

begin_define
DECL|macro|DARKTABLE
define|#
directive|define
name|DARKTABLE
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), DARKTABLE_TYPE, Darktable))
end_define

begin_decl_stmt
name|GType
name|darktable_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|GList
modifier|*
name|darktable_init_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpProcedure
modifier|*
name|darktable_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|darktable_load
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|darktable_load_thumb
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint32
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GimpRunMode
name|run_mode
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
name|gint32
name|load_thumbnail_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint
name|thumb_size
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (Darktable,darktable,GIMP_TYPE_PLUG_IN)
name|G_DEFINE_TYPE
argument_list|(
argument|Darktable
argument_list|,
argument|darktable
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|DARKTABLE_TYPE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|darktable_class_init
parameter_list|(
name|DarktableClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPlugInClass
modifier|*
name|plug_in_class
init|=
name|GIMP_PLUG_IN_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|plug_in_class
operator|->
name|init_procedures
operator|=
name|darktable_init_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|darktable_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|darktable_init (Darktable * darktable)
name|darktable_init
parameter_list|(
name|Darktable
modifier|*
name|darktable
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|darktable_init_procedures (GimpPlugIn * plug_in)
name|darktable_init_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
comment|/* check if darktable is installed    */
name|gboolean
name|search_path
init|=
name|FALSE
decl_stmt|;
name|gchar
modifier|*
name|exec_path
init|=
name|file_raw_get_executable_path
argument_list|(
literal|"darktable"
argument_list|,
name|NULL
argument_list|,
literal|"DARKTABLE_EXECUTABLE"
argument_list|,
literal|"org.darktable"
argument_list|,
name|REGISTRY_KEY_BASE
argument_list|,
operator|&
name|search_path
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|argv
index|[]
init|=
block|{
name|exec_path
block|,
literal|"--version"
block|,
name|NULL
block|}
decl_stmt|;
name|gchar
modifier|*
name|darktable_stdout
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|darktable_stderr
init|=
name|NULL
decl_stmt|;
name|gboolean
name|have_darktable
init|=
name|FALSE
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/* allow the user to have some insight into why darktable may fail. */
name|gboolean
name|debug_prints
init|=
name|g_getenv
argument_list|(
literal|"DARKTABLE_DEBUG"
argument_list|)
operator|!=
name|NULL
decl_stmt|;
if|if
condition|(
name|debug_prints
condition|)
name|g_printf
argument_list|(
literal|"[%s] trying to call '%s'\n"
argument_list|,
name|__FILE__
argument_list|,
name|exec_path
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_spawn_sync
argument_list|(
name|NULL
argument_list|,
name|argv
argument_list|,
name|NULL
argument_list|,
operator|(
name|search_path
condition|?
name|G_SPAWN_SEARCH_PATH
else|:
literal|0
operator|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|darktable_stdout
argument_list|,
operator|&
name|darktable_stderr
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|GRegex
modifier|*
name|regex
decl_stmt|;
name|GMatchInfo
modifier|*
name|matches
decl_stmt|;
name|gint
name|major
decl_stmt|;
name|gint
name|minor
decl_stmt|;
comment|/* A default darktable would apparently output something like        * "this is darktable 2.2.5", but this version string is        * customizable. In the official Fedora package for instance, I        * encountered a "this is darktable darktable-2.2.5-4.fc27".        * Therefore make the version recognition a bit more flexible.        */
name|regex
operator|=
name|g_regex_new
argument_list|(
literal|"this is darktable [^0-9]*([0-9]+)\\.([0-9]+)\\.([0-9]+)"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_regex_match
argument_list|(
name|regex
argument_list|,
name|darktable_stdout
argument_list|,
literal|0
argument_list|,
operator|&
name|matches
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|match
decl_stmt|;
name|match
operator|=
name|g_match_info_fetch
argument_list|(
name|matches
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|major
operator|=
name|g_ascii_strtoll
argument_list|(
name|match
argument_list|,
name|NULL
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|match
argument_list|)
expr_stmt|;
name|match
operator|=
name|g_match_info_fetch
argument_list|(
name|matches
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|minor
operator|=
name|g_ascii_strtoll
argument_list|(
name|match
argument_list|,
name|NULL
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|match
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|major
operator|==
literal|1
operator|&&
name|minor
operator|>=
literal|7
operator|)
operator|||
name|major
operator|>=
literal|2
operator|)
condition|)
block|{
if|if
condition|(
name|g_strstr_len
argument_list|(
name|darktable_stdout
argument_list|,
operator|-
literal|1
argument_list|,
literal|"Lua support enabled"
argument_list|)
condition|)
block|{
name|have_darktable
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
name|g_match_info_free
argument_list|(
name|matches
argument_list|)
expr_stmt|;
name|g_regex_unref
argument_list|(
name|regex
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|debug_prints
condition|)
block|{
name|g_printf
argument_list|(
literal|"[%s] g_spawn_sync failed\n"
argument_list|,
name|__FILE__
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|debug_prints
condition|)
block|{
if|if
condition|(
name|error
condition|)
name|g_printf
argument_list|(
literal|"[%s] error: %s\n"
argument_list|,
name|__FILE__
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
if|if
condition|(
name|darktable_stdout
operator|&&
operator|*
name|darktable_stdout
condition|)
name|g_printf
argument_list|(
literal|"[%s] stdout:\n%s\n"
argument_list|,
name|__FILE__
argument_list|,
name|darktable_stdout
argument_list|)
expr_stmt|;
if|if
condition|(
name|darktable_stderr
operator|&&
operator|*
name|darktable_stderr
condition|)
name|g_printf
argument_list|(
literal|"[%s] stderr:\n%s\n"
argument_list|,
name|__FILE__
argument_list|,
name|darktable_stderr
argument_list|)
expr_stmt|;
name|g_printf
argument_list|(
literal|"[%s] have_darktable: %d\n"
argument_list|,
name|__FILE__
argument_list|,
name|have_darktable
argument_list|)
expr_stmt|;
block|}
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|darktable_stdout
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|darktable_stderr
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|exec_path
argument_list|)
expr_stmt|;
if|if
condition|(
name|have_darktable
condition|)
block|{
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|g_strdup
argument_list|(
name|LOAD_THUMB_PROC
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
name|file_formats
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
specifier|const
name|FileFormat
modifier|*
name|format
init|=
operator|&
name|file_formats
index|[
name|i
index|]
decl_stmt|;
name|gchar
modifier|*
name|load_proc
decl_stmt|;
name|load_proc
operator|=
name|g_strdup_printf
argument_list|(
name|format
operator|->
name|load_proc_format
argument_list|,
literal|"darktable"
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|load_proc
argument_list|)
expr_stmt|;
block|}
return|return
name|list
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProcedure
modifier|*
DECL|function|darktable_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|darktable_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|LOAD_THUMB_PROC
argument_list|)
condition|)
block|{
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|name
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|darktable_load_thumb
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Load thumbnail from a raw image "
literal|"via darktable"
argument_list|,
literal|"This plug-in loads a thumbnail "
literal|"from a raw image by calling "
literal|"darktable-cli."
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Tobias Ellinghaus"
argument_list|,
literal|"Tobias Ellinghaus"
argument_list|,
literal|"2016"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"filename"
argument_list|,
literal|"Filename"
argument_list|,
literal|"Name of the file "
literal|"to load"
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"thumb-size"
argument_list|,
literal|"Thumb Size"
argument_list|,
literal|"Preferred thumbnail size"
argument_list|,
literal|16
argument_list|,
literal|2014
argument_list|,
literal|256
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_VAL_IMAGE
argument_list|(
name|procedure
argument_list|,
literal|"image"
argument_list|,
literal|"Image"
argument_list|,
literal|"Thumbnail image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_VAL_INT
argument_list|(
name|procedure
argument_list|,
literal|"image-width"
argument_list|,
literal|"Image width"
argument_list|,
literal|"Width of the full-sized image"
argument_list|,
literal|1
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_VAL_INT
argument_list|(
name|procedure
argument_list|,
literal|"image-height"
argument_list|,
literal|"Image height"
argument_list|,
literal|"Height of the full-sized image"
argument_list|,
literal|1
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
expr_stmt|;
block|}
else|else
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
name|file_formats
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
specifier|const
name|FileFormat
modifier|*
name|format
init|=
operator|&
name|file_formats
index|[
name|i
index|]
decl_stmt|;
name|gchar
modifier|*
name|load_proc
decl_stmt|;
name|gchar
modifier|*
name|load_blurb
decl_stmt|;
name|gchar
modifier|*
name|load_help
decl_stmt|;
name|load_proc
operator|=
name|g_strdup_printf
argument_list|(
name|format
operator|->
name|load_proc_format
argument_list|,
literal|"darktable"
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|load_proc
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|load_proc
argument_list|)
expr_stmt|;
continue|continue;
block|}
name|load_blurb
operator|=
name|g_strdup_printf
argument_list|(
name|format
operator|->
name|load_blurb_format
argument_list|,
literal|"darktable"
argument_list|)
expr_stmt|;
name|load_help
operator|=
name|g_strdup_printf
argument_list|(
name|format
operator|->
name|load_help_format
argument_list|,
literal|"darktable"
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|gimp_load_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|name
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|darktable_load
argument_list|,
operator|(
name|gpointer
operator|)
name|format
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
name|load_blurb
argument_list|,
name|load_help
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Tobias Ellinghaus"
argument_list|,
literal|"Tobias Ellinghaus"
argument_list|,
literal|"2016"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_mime_types
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|format
operator|->
name|mime_type
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_extensions
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|format
operator|->
name|extensions
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_magics
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|format
operator|->
name|magic
argument_list|)
expr_stmt|;
name|gimp_load_procedure_set_handles_raw
argument_list|(
name|GIMP_LOAD_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_load_procedure_set_thumbnail_loader
argument_list|(
name|GIMP_LOAD_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|LOAD_THUMB_PROC
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|load_proc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|load_blurb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|load_help
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
return|return
name|procedure
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|darktable_load (GimpProcedure * procedure,GimpRunMode run_mode,GFile * file,const GimpValueArray * args,gpointer run_data)
name|darktable_load
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gint32
name|image_id
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|filename
operator|=
name|g_file_get_path
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|image_id
operator|=
name|load_image
argument_list|(
name|filename
argument_list|,
name|run_mode
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_id
operator|<
literal|1
condition|)
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_EXECUTION_ERROR
argument_list|,
name|error
argument_list|)
return|;
name|return_vals
operator|=
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_SUCCESS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|image_id
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|darktable_load_thumb (GimpProcedure * procedure,const GimpValueArray * args,gpointer run_data)
name|darktable_load_thumb
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint32
name|image_id
decl_stmt|;
name|GValue
name|value
init|=
name|G_VALUE_INIT
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|filename
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|width
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|height
operator|=
name|width
expr_stmt|;
name|image_id
operator|=
name|load_thumbnail_image
argument_list|(
name|filename
argument_list|,
name|width
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_id
operator|<
literal|1
condition|)
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_EXECUTION_ERROR
argument_list|,
name|error
argument_list|)
return|;
name|return_vals
operator|=
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_SUCCESS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|image_id
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|3
argument_list|)
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|GIMP_TYPE_IMAGE_TYPE
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
operator|&
name|value
argument_list|,
name|GIMP_RGB_IMAGE
argument_list|)
expr_stmt|;
name|gimp_value_array_append
argument_list|(
name|return_vals
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|value
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_value_array_append
argument_list|(
name|return_vals
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|load_image (const gchar * filename,GimpRunMode run_mode,GError ** error)
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
name|GFile
modifier|*
name|lua_file
init|=
name|gimp_data_directory_file
argument_list|(
literal|"file-raw"
argument_list|,
literal|"file-darktable-export-on-exit.lua"
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|lua_script
init|=
name|g_file_get_path
argument_list|(
name|lua_file
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|lua_script_escaped
init|=
name|g_strescape
argument_list|(
name|lua_script
argument_list|,
literal|""
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|lua_quoted
init|=
name|g_shell_quote
argument_list|(
name|lua_script_escaped
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|lua_cmd
init|=
name|g_strdup_printf
argument_list|(
literal|"dofile(%s)"
argument_list|,
name|lua_quoted
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|filename_out
init|=
name|gimp_temp_name
argument_list|(
literal|"exr"
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|export_filename
init|=
name|g_strdup_printf
argument_list|(
literal|"lua/export_on_exit/export_filename=%s"
argument_list|,
name|filename_out
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|darktable_stdout
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|darktable_stderr
init|=
name|NULL
decl_stmt|;
comment|/* allow the user to have some insight into why darktable may fail. */
name|gboolean
name|debug_prints
init|=
name|g_getenv
argument_list|(
literal|"DARKTABLE_DEBUG"
argument_list|)
operator|!=
name|NULL
decl_stmt|;
comment|/* linear sRGB for now as GIMP uses that internally in many places anyway */
name|gboolean
name|search_path
init|=
name|FALSE
decl_stmt|;
name|gchar
modifier|*
name|exec_path
init|=
name|file_raw_get_executable_path
argument_list|(
literal|"darktable"
argument_list|,
name|NULL
argument_list|,
literal|"DARKTABLE_EXECUTABLE"
argument_list|,
literal|"org.darktable"
argument_list|,
name|REGISTRY_KEY_BASE
argument_list|,
operator|&
name|search_path
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|argv
index|[]
init|=
block|{
name|exec_path
block|,
literal|"--library"
block|,
literal|":memory:"
block|,
literal|"--luacmd"
block|,
name|lua_cmd
block|,
literal|"--conf"
block|,
literal|"plugins/lighttable/export/icctype=3"
block|,
literal|"--conf"
block|,
name|export_filename
block|,
operator|(
name|gchar
operator|*
operator|)
name|filename
block|,
name|NULL
block|}
decl_stmt|;
name|g_object_unref
argument_list|(
name|lua_file
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lua_script
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lua_script_escaped
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lua_quoted
argument_list|)
expr_stmt|;
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Opening '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|debug_prints
condition|)
block|{
name|g_printf
argument_list|(
literal|"[%s] trying to call\n"
argument_list|,
name|__FILE__
argument_list|)
expr_stmt|;
for|for
control|(
name|gchar
modifier|*
modifier|*
name|iter
init|=
name|argv
init|;
operator|*
name|iter
condition|;
name|iter
operator|++
control|)
name|g_printf
argument_list|(
literal|"    %s\n"
argument_list|,
operator|*
name|iter
argument_list|)
expr_stmt|;
name|g_printf
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|g_spawn_sync
argument_list|(
name|NULL
argument_list|,
name|argv
argument_list|,
name|NULL
argument_list|,
comment|/*G_SPAWN_STDOUT_TO_DEV_NULL |*/
comment|/*G_SPAWN_STDERR_TO_DEV_NULL |*/
operator|(
name|search_path
condition|?
name|G_SPAWN_SEARCH_PATH
else|:
literal|0
operator|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|darktable_stdout
argument_list|,
operator|&
name|darktable_stderr
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|image_ID
operator|=
name|gimp_file_load
argument_list|(
name|run_mode
argument_list|,
name|filename_out
argument_list|,
name|filename_out
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|debug_prints
condition|)
block|{
if|if
condition|(
name|darktable_stdout
operator|&&
operator|*
name|darktable_stdout
condition|)
name|g_printf
argument_list|(
literal|"%s\n"
argument_list|,
name|darktable_stdout
argument_list|)
expr_stmt|;
if|if
condition|(
name|darktable_stderr
operator|&&
operator|*
name|darktable_stderr
condition|)
name|g_printf
argument_list|(
literal|"%s\n"
argument_list|,
name|darktable_stderr
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|darktable_stdout
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|darktable_stderr
argument_list|)
expr_stmt|;
name|g_unlink
argument_list|(
name|filename_out
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lua_cmd
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename_out
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|export_filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|exec_path
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|load_thumbnail_image (const gchar * filename,gint thumb_size,gint * width,gint * height,GError ** error)
name|load_thumbnail_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint
name|thumb_size
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
name|gchar
modifier|*
name|filename_out
init|=
name|gimp_temp_name
argument_list|(
literal|"jpg"
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|size
init|=
name|g_strdup_printf
argument_list|(
literal|"%d"
argument_list|,
name|thumb_size
argument_list|)
decl_stmt|;
name|GFile
modifier|*
name|lua_file
init|=
name|gimp_data_directory_file
argument_list|(
literal|"file-raw"
argument_list|,
literal|"file-darktable-get-size.lua"
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|lua_script
init|=
name|g_file_get_path
argument_list|(
name|lua_file
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|lua_script_escaped
init|=
name|g_strescape
argument_list|(
name|lua_script
argument_list|,
literal|""
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|lua_quoted
init|=
name|g_shell_quote
argument_list|(
name|lua_script_escaped
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|lua_cmd
init|=
name|g_strdup_printf
argument_list|(
literal|"dofile(%s)"
argument_list|,
name|lua_quoted
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|darktable_stdout
init|=
name|NULL
decl_stmt|;
name|gboolean
name|search_path
init|=
name|FALSE
decl_stmt|;
name|gchar
modifier|*
name|exec_path
init|=
name|file_raw_get_executable_path
argument_list|(
literal|"darktable"
argument_list|,
literal|"-cli"
argument_list|,
literal|"DARKTABLE_EXECUTABLE"
argument_list|,
literal|"org.darktable"
argument_list|,
name|REGISTRY_KEY_BASE
argument_list|,
operator|&
name|search_path
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|argv
index|[]
init|=
block|{
name|exec_path
block|,
operator|(
name|gchar
operator|*
operator|)
name|filename
block|,
name|filename_out
block|,
literal|"--width"
block|,
name|size
block|,
literal|"--height"
block|,
name|size
block|,
literal|"--hq"
block|,
literal|"false"
block|,
literal|"--core"
block|,
literal|"--conf"
block|,
literal|"plugins/lighttable/export/icctype=3"
block|,
literal|"--luacmd"
block|,
name|lua_cmd
block|,
name|NULL
block|}
decl_stmt|;
name|g_object_unref
argument_list|(
name|lua_file
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lua_script
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lua_script_escaped
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lua_quoted
argument_list|)
expr_stmt|;
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Opening thumbnail for '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|width
operator|=
operator|*
name|height
operator|=
name|thumb_size
expr_stmt|;
if|if
condition|(
name|g_spawn_sync
argument_list|(
name|NULL
argument_list|,
name|argv
argument_list|,
name|NULL
argument_list|,
name|G_SPAWN_STDERR_TO_DEV_NULL
operator||
operator|(
name|search_path
condition|?
name|G_SPAWN_SEARCH_PATH
else|:
literal|0
operator|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|darktable_stdout
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|gimp_progress_update
argument_list|(
literal|0.5
argument_list|)
expr_stmt|;
name|image_ID
operator|=
name|gimp_file_load
argument_list|(
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|filename_out
argument_list|,
name|filename_out
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
block|{
comment|/* the size reported by raw files isn't precise,            * but it should be close enough to get an idea.            */
name|gchar
modifier|*
name|start_of_size
init|=
name|g_strstr_len
argument_list|(
name|darktable_stdout
argument_list|,
operator|-
literal|1
argument_list|,
literal|"[dt4gimp]"
argument_list|)
decl_stmt|;
if|if
condition|(
name|start_of_size
condition|)
name|sscanf
argument_list|(
name|start_of_size
argument_list|,
literal|"[dt4gimp] %d %d"
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
comment|/* is this needed for thumbnails? */
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|g_unlink
argument_list|(
name|filename_out
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename_out
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lua_cmd
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|darktable_stdout
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|exec_path
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

end_unit

