begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpenvirontable.c  * (C) 2002 Manish Singh<yosh@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpenvirontable.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|GimpEnvironValue
typedef|typedef
name|struct
name|_GimpEnvironValue
name|GimpEnvironValue
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpEnvironValue
struct|struct
name|_GimpEnvironValue
block|{
DECL|member|value
name|gchar
modifier|*
name|value
decl_stmt|;
DECL|member|separator
name|gchar
modifier|*
name|separator
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* FIXME: check how portable this is */
end_comment

begin_decl_stmt
specifier|extern
name|char
modifier|*
modifier|*
name|environ
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|gimp_environ_table_finalize
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
name|gimp_environ_table_load_env_file
parameter_list|(
specifier|const
name|GimpDatafileData
modifier|*
name|file_data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_environ_table_legal_name
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_environ_table_populate
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_environ_table_populate_one
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpEnvironValue
modifier|*
name|val
parameter_list|,
name|GPtrArray
modifier|*
name|env_array
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_environ_table_pass_through
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
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
name|void
name|gimp_environ_table_clear_vars
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_environ_table_clear_internal
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_environ_table_clear_envp
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_environ_table_free_value
parameter_list|(
name|gpointer
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpEnvironTable,gimp_environ_table,G_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpEnvironTable
argument_list|,
argument|gimp_environ_table
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_environ_table_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_environ_table_class_init
parameter_list|(
name|GimpEnvironTableClass
modifier|*
name|class
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|class
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_environ_table_finalize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_environ_table_init (GimpEnvironTable * environ_table)
name|gimp_environ_table_init
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
block|{
name|environ_table
operator|->
name|vars
operator|=
name|NULL
expr_stmt|;
name|environ_table
operator|->
name|internal
operator|=
name|NULL
expr_stmt|;
name|environ_table
operator|->
name|envp
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_environ_table_finalize (GObject * object)
name|gimp_environ_table_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpEnvironTable
modifier|*
name|environ_table
init|=
name|GIMP_ENVIRON_TABLE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gimp_environ_table_clear_all
argument_list|(
name|environ_table
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
name|GimpEnvironTable
modifier|*
DECL|function|gimp_environ_table_new (void)
name|gimp_environ_table_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_ENVIRON_TABLE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_environ_table_load (GimpEnvironTable * environ_table,const gchar * env_path)
name|gimp_environ_table_load
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|,
specifier|const
name|gchar
modifier|*
name|env_path
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ENVIRON_TABLE
argument_list|(
name|environ_table
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_environ_table_clear
argument_list|(
name|environ_table
argument_list|)
expr_stmt|;
name|environ_table
operator|->
name|vars
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
name|g_free
argument_list|,
name|gimp_environ_table_free_value
argument_list|)
expr_stmt|;
name|gimp_datafiles_read_directories
argument_list|(
name|env_path
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|,
name|gimp_environ_table_load_env_file
argument_list|,
name|environ_table
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_environ_table_add (GimpEnvironTable * environ_table,const gchar * name,const gchar * value,const gchar * separator)
name|gimp_environ_table_add
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
specifier|const
name|gchar
modifier|*
name|separator
parameter_list|)
block|{
name|GimpEnvironValue
modifier|*
name|val
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ENVIRON_TABLE
argument_list|(
name|environ_table
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_environ_table_clear_envp
argument_list|(
name|environ_table
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|environ_table
operator|->
name|internal
condition|)
name|environ_table
operator|->
name|internal
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
name|g_free
argument_list|,
name|gimp_environ_table_free_value
argument_list|)
expr_stmt|;
name|val
operator|=
name|g_new
argument_list|(
name|GimpEnvironValue
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|val
operator|->
name|value
operator|=
name|g_strdup
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|val
operator|->
name|separator
operator|=
name|g_strdup
argument_list|(
name|separator
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|environ_table
operator|->
name|internal
argument_list|,
name|g_strdup
argument_list|(
name|name
argument_list|)
argument_list|,
name|val
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_environ_table_remove (GimpEnvironTable * environ_table,const gchar * name)
name|gimp_environ_table_remove
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ENVIRON_TABLE
argument_list|(
name|environ_table
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|environ_table
operator|->
name|internal
condition|)
return|return;
name|gimp_environ_table_clear_envp
argument_list|(
name|environ_table
argument_list|)
expr_stmt|;
name|g_hash_table_remove
argument_list|(
name|environ_table
operator|->
name|internal
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_hash_table_size
argument_list|(
name|environ_table
operator|->
name|internal
argument_list|)
operator|==
literal|0
condition|)
name|gimp_environ_table_clear_internal
argument_list|(
name|environ_table
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_environ_table_clear (GimpEnvironTable * environ_table)
name|gimp_environ_table_clear
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ENVIRON_TABLE
argument_list|(
name|environ_table
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_environ_table_clear_envp
argument_list|(
name|environ_table
argument_list|)
expr_stmt|;
name|gimp_environ_table_clear_vars
argument_list|(
name|environ_table
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_environ_table_clear_all (GimpEnvironTable * environ_table)
name|gimp_environ_table_clear_all
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ENVIRON_TABLE
argument_list|(
name|environ_table
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_environ_table_clear_envp
argument_list|(
name|environ_table
argument_list|)
expr_stmt|;
name|gimp_environ_table_clear_vars
argument_list|(
name|environ_table
argument_list|)
expr_stmt|;
name|gimp_environ_table_clear_internal
argument_list|(
name|environ_table
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gchar
modifier|*
modifier|*
DECL|function|gimp_environ_table_get_envp (GimpEnvironTable * environ_table)
name|gimp_environ_table_get_envp
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ENVIRON_TABLE
argument_list|(
name|environ_table
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Hmm.. should we return a copy here in the future? Not thread safe atm,    * but the rest of it isn't either.    */
if|if
condition|(
operator|!
name|environ_table
operator|->
name|envp
condition|)
name|gimp_environ_table_populate
argument_list|(
name|environ_table
argument_list|)
expr_stmt|;
return|return
name|environ_table
operator|->
name|envp
return|;
block|}
end_function

begin_comment
comment|/* private */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_environ_table_load_env_file (const GimpDatafileData * file_data,gpointer user_data)
name|gimp_environ_table_load_env_file
parameter_list|(
specifier|const
name|GimpDatafileData
modifier|*
name|file_data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpEnvironTable
modifier|*
name|environ_table
init|=
name|GIMP_ENVIRON_TABLE
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|FILE
modifier|*
name|env
decl_stmt|;
name|gchar
name|buffer
index|[
literal|4096
index|]
decl_stmt|;
name|gsize
name|len
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|,
modifier|*
name|value
decl_stmt|,
modifier|*
name|separator
decl_stmt|,
modifier|*
name|p
decl_stmt|,
modifier|*
name|q
decl_stmt|;
name|GimpEnvironValue
modifier|*
name|val
decl_stmt|;
name|env
operator|=
name|g_fopen
argument_list|(
name|file_data
operator|->
name|filename
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|env
condition|)
return|return;
while|while
condition|(
name|fgets
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|env
argument_list|)
condition|)
block|{
comment|/* Skip comments */
if|if
condition|(
name|buffer
index|[
literal|0
index|]
operator|==
literal|'#'
condition|)
continue|continue;
name|len
operator|=
name|strlen
argument_list|(
name|buffer
argument_list|)
operator|-
literal|1
expr_stmt|;
comment|/* Skip too long lines */
if|if
condition|(
name|buffer
index|[
name|len
index|]
operator|!=
literal|'\n'
condition|)
continue|continue;
name|buffer
index|[
name|len
index|]
operator|=
literal|'\0'
expr_stmt|;
name|p
operator|=
name|strchr
argument_list|(
name|buffer
argument_list|,
literal|'='
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|p
condition|)
continue|continue;
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
name|name
operator|=
name|buffer
expr_stmt|;
name|value
operator|=
name|p
operator|+
literal|1
expr_stmt|;
if|if
condition|(
name|name
index|[
literal|0
index|]
operator|==
literal|'\0'
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Empty variable name in environment file %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|file_data
operator|->
name|filename
argument_list|)
argument_list|)
expr_stmt|;
continue|continue;
block|}
name|separator
operator|=
name|NULL
expr_stmt|;
name|q
operator|=
name|strchr
argument_list|(
name|name
argument_list|,
literal|' '
argument_list|)
expr_stmt|;
if|if
condition|(
name|q
condition|)
block|{
operator|*
name|q
operator|=
literal|'\0'
expr_stmt|;
name|separator
operator|=
name|name
expr_stmt|;
name|name
operator|=
name|q
operator|+
literal|1
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|gimp_environ_table_legal_name
argument_list|(
name|name
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Illegal variable name in environment file %s: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|file_data
operator|->
name|filename
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
operator|!
name|g_hash_table_lookup
argument_list|(
name|environ_table
operator|->
name|vars
argument_list|,
name|name
argument_list|)
condition|)
block|{
name|val
operator|=
name|g_new
argument_list|(
name|GimpEnvironValue
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|val
operator|->
name|value
operator|=
name|gimp_config_path_expand
argument_list|(
name|value
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|val
operator|->
name|separator
operator|=
name|g_strdup
argument_list|(
name|separator
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|environ_table
operator|->
name|vars
argument_list|,
name|g_strdup
argument_list|(
name|name
argument_list|)
argument_list|,
name|val
argument_list|)
expr_stmt|;
block|}
block|}
name|fclose
argument_list|(
name|env
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_environ_table_legal_name (gchar * name)
name|gimp_environ_table_legal_name
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|gchar
modifier|*
name|s
decl_stmt|;
if|if
condition|(
operator|!
name|g_ascii_isalpha
argument_list|(
operator|*
name|name
argument_list|)
operator|&&
operator|(
operator|*
name|name
operator|!=
literal|'_'
operator|)
condition|)
return|return
name|FALSE
return|;
for|for
control|(
name|s
operator|=
name|name
operator|+
literal|1
init|;
operator|*
name|s
condition|;
name|s
operator|++
control|)
if|if
condition|(
operator|!
name|g_ascii_isalnum
argument_list|(
operator|*
name|s
argument_list|)
operator|&&
operator|(
operator|*
name|s
operator|!=
literal|'_'
operator|)
condition|)
return|return
name|FALSE
return|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_environ_table_populate (GimpEnvironTable * environ_table)
name|gimp_environ_table_populate
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
block|{
name|gchar
modifier|*
modifier|*
name|var
init|=
name|environ
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|,
modifier|*
name|p
decl_stmt|;
name|GPtrArray
modifier|*
name|env_array
decl_stmt|;
name|env_array
operator|=
name|g_ptr_array_new
argument_list|()
expr_stmt|;
while|while
condition|(
operator|*
name|var
condition|)
block|{
name|p
operator|=
name|strchr
argument_list|(
operator|*
name|var
argument_list|,
literal|'='
argument_list|)
expr_stmt|;
comment|/* shouldn't happen... but just to be safe... */
if|if
condition|(
name|p
condition|)
block|{
name|name
operator|=
name|g_strndup
argument_list|(
operator|*
name|var
argument_list|,
name|p
operator|-
operator|*
name|var
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_environ_table_pass_through
argument_list|(
name|environ_table
argument_list|,
name|name
argument_list|)
condition|)
name|g_ptr_array_add
argument_list|(
name|env_array
argument_list|,
name|g_strdup
argument_list|(
operator|*
name|var
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
name|var
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|environ_table
operator|->
name|vars
condition|)
name|g_hash_table_foreach
argument_list|(
name|environ_table
operator|->
name|vars
argument_list|,
operator|(
name|GHFunc
operator|)
name|gimp_environ_table_populate_one
argument_list|,
name|env_array
argument_list|)
expr_stmt|;
if|if
condition|(
name|environ_table
operator|->
name|internal
condition|)
name|g_hash_table_foreach
argument_list|(
name|environ_table
operator|->
name|internal
argument_list|,
operator|(
name|GHFunc
operator|)
name|gimp_environ_table_populate_one
argument_list|,
name|env_array
argument_list|)
expr_stmt|;
name|g_ptr_array_add
argument_list|(
name|env_array
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|environ_table
operator|->
name|envp
operator|=
operator|(
name|gchar
operator|*
operator|*
operator|)
name|g_ptr_array_free
argument_list|(
name|env_array
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|ENVP_DEBUG
name|var
operator|=
name|environ_table
operator|->
name|envp
expr_stmt|;
name|g_print
argument_list|(
literal|"GimpEnvironTable:\n"
argument_list|)
expr_stmt|;
while|while
condition|(
operator|*
name|var
condition|)
block|{
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
operator|*
name|var
argument_list|)
expr_stmt|;
name|var
operator|++
expr_stmt|;
block|}
endif|#
directive|endif
comment|/* ENVP_DEBUG */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_environ_table_populate_one (const gchar * name,GimpEnvironValue * val,GPtrArray * env_array)
name|gimp_environ_table_populate_one
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpEnvironValue
modifier|*
name|val
parameter_list|,
name|GPtrArray
modifier|*
name|env_array
parameter_list|)
block|{
name|gchar
modifier|*
name|old
decl_stmt|,
modifier|*
name|var
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|val
operator|->
name|separator
condition|)
block|{
name|old
operator|=
name|getenv
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|old
condition|)
name|var
operator|=
name|g_strconcat
argument_list|(
name|name
argument_list|,
literal|"="
argument_list|,
name|val
operator|->
name|value
argument_list|,
name|val
operator|->
name|separator
argument_list|,
name|old
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|var
condition|)
name|var
operator|=
name|g_strconcat
argument_list|(
name|name
argument_list|,
literal|"="
argument_list|,
name|val
operator|->
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_ptr_array_add
argument_list|(
name|env_array
argument_list|,
name|var
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_environ_table_pass_through (GimpEnvironTable * environ_table,const gchar * name)
name|gimp_environ_table_pass_through
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|gboolean
name|vars
decl_stmt|,
name|internal
decl_stmt|;
name|vars
operator|=
name|environ_table
operator|->
name|vars
operator|&&
name|g_hash_table_lookup
argument_list|(
name|environ_table
operator|->
name|vars
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|internal
operator|=
name|environ_table
operator|->
name|internal
operator|&&
name|g_hash_table_lookup
argument_list|(
name|environ_table
operator|->
name|internal
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
operator|(
operator|!
name|vars
operator|&&
operator|!
name|internal
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_environ_table_clear_vars (GimpEnvironTable * environ_table)
name|gimp_environ_table_clear_vars
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
block|{
if|if
condition|(
name|environ_table
operator|->
name|vars
condition|)
block|{
name|g_hash_table_destroy
argument_list|(
name|environ_table
operator|->
name|vars
argument_list|)
expr_stmt|;
name|environ_table
operator|->
name|vars
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_environ_table_clear_internal (GimpEnvironTable * environ_table)
name|gimp_environ_table_clear_internal
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
block|{
if|if
condition|(
name|environ_table
operator|->
name|internal
condition|)
block|{
name|g_hash_table_destroy
argument_list|(
name|environ_table
operator|->
name|internal
argument_list|)
expr_stmt|;
name|environ_table
operator|->
name|internal
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_environ_table_clear_envp (GimpEnvironTable * environ_table)
name|gimp_environ_table_clear_envp
parameter_list|(
name|GimpEnvironTable
modifier|*
name|environ_table
parameter_list|)
block|{
if|if
condition|(
name|environ_table
operator|->
name|envp
condition|)
block|{
name|g_strfreev
argument_list|(
name|environ_table
operator|->
name|envp
argument_list|)
expr_stmt|;
name|environ_table
operator|->
name|envp
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_environ_table_free_value (gpointer value)
name|gimp_environ_table_free_value
parameter_list|(
name|gpointer
name|value
parameter_list|)
block|{
name|GimpEnvironValue
modifier|*
name|val
init|=
name|value
decl_stmt|;
name|g_free
argument_list|(
name|val
operator|->
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|val
operator|->
name|separator
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|val
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

