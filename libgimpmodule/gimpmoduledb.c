begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpmoduletypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"gimpmoduledb.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2aaae4ef0103
block|{
DECL|enumerator|ADD
name|ADD
block|,
DECL|enumerator|REMOVE
name|REMOVE
block|,
DECL|enumerator|MODULE_MODIFIED
name|MODULE_MODIFIED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_comment
comment|/*  #define DUMP_DB 1  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_module_db_finalize
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
name|gimp_module_db_module_initialize
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
name|GimpModule
modifier|*
name|gimp_module_db_module_find_by_path
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
specifier|const
name|char
modifier|*
name|fullpath
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|DUMP_DB
end_ifdef

begin_function_decl
specifier|static
name|void
name|gimp_module_db_dump_module
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
specifier|static
name|void
name|gimp_module_db_module_on_disk_func
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_module_db_module_remove_func
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_module_db_module_modified
parameter_list|(
name|GimpModule
modifier|*
name|module
parameter_list|,
name|GimpModuleDB
modifier|*
name|db
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpModuleDB
argument_list|,
argument|gimp_module_db
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_module_db_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|db_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_module_db_class_init (GimpModuleDBClass * klass)
name|gimp_module_db_class_init
parameter_list|(
name|GimpModuleDBClass
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
name|db_signals
index|[
name|ADD
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"add"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpModuleDBClass
argument_list|,
name|add
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__OBJECT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_MODULE
argument_list|)
expr_stmt|;
name|db_signals
index|[
name|REMOVE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"remove"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpModuleDBClass
argument_list|,
name|remove
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__OBJECT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_MODULE
argument_list|)
expr_stmt|;
name|db_signals
index|[
name|MODULE_MODIFIED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"module-modified"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpModuleDBClass
argument_list|,
name|module_modified
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__OBJECT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_MODULE
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_module_db_finalize
expr_stmt|;
name|klass
operator|->
name|add
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|remove
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_module_db_init (GimpModuleDB * db)
name|gimp_module_db_init
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|)
block|{
name|db
operator|->
name|modules
operator|=
name|NULL
expr_stmt|;
name|db
operator|->
name|load_inhibit
operator|=
name|NULL
expr_stmt|;
name|db
operator|->
name|verbose
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_module_db_finalize (GObject * object)
name|gimp_module_db_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpModuleDB
modifier|*
name|db
init|=
name|GIMP_MODULE_DB
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|db
operator|->
name|modules
condition|)
block|{
name|g_list_free
argument_list|(
name|db
operator|->
name|modules
argument_list|)
expr_stmt|;
name|db
operator|->
name|modules
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|db
operator|->
name|load_inhibit
condition|)
block|{
name|g_free
argument_list|(
name|db
operator|->
name|load_inhibit
argument_list|)
expr_stmt|;
name|db
operator|->
name|load_inhibit
operator|=
name|NULL
expr_stmt|;
block|}
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

begin_comment
comment|/**  * gimp_module_db_new:  * @verbose: Pass %TRUE to enable debugging output.  *  * Creates a new #GimpModuleDB instance. The @verbose parameter will be  * passed to the created #GimpModule instances using gimp_module_new().  *  * Return value: The new #GimpModuleDB instance.  **/
end_comment

begin_function
name|GimpModuleDB
modifier|*
DECL|function|gimp_module_db_new (gboolean verbose)
name|gimp_module_db_new
parameter_list|(
name|gboolean
name|verbose
parameter_list|)
block|{
name|GimpModuleDB
modifier|*
name|db
decl_stmt|;
name|db
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_MODULE_DB
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|db
operator|->
name|verbose
operator|=
name|verbose
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
return|return
name|db
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|is_in_inhibit_list (const gchar * filename,const gchar * inhibit_list)
name|is_in_inhibit_list
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|inhibit_list
parameter_list|)
block|{
name|gchar
modifier|*
name|p
decl_stmt|;
name|gint
name|pathlen
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|start
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|end
decl_stmt|;
if|if
condition|(
operator|!
name|inhibit_list
operator|||
operator|!
name|strlen
argument_list|(
name|inhibit_list
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|p
operator|=
name|strstr
argument_list|(
name|inhibit_list
argument_list|,
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|p
condition|)
return|return
name|FALSE
return|;
comment|/* we have a substring, but check for colons either side */
name|start
operator|=
name|p
expr_stmt|;
while|while
condition|(
name|start
operator|!=
name|inhibit_list
operator|&&
operator|*
name|start
operator|!=
name|G_SEARCHPATH_SEPARATOR
condition|)
name|start
operator|--
expr_stmt|;
if|if
condition|(
operator|*
name|start
operator|==
name|G_SEARCHPATH_SEPARATOR
condition|)
name|start
operator|++
expr_stmt|;
name|end
operator|=
name|strchr
argument_list|(
name|p
argument_list|,
name|G_SEARCHPATH_SEPARATOR
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|end
condition|)
name|end
operator|=
name|inhibit_list
operator|+
name|strlen
argument_list|(
name|inhibit_list
argument_list|)
expr_stmt|;
name|pathlen
operator|=
name|strlen
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|end
operator|-
name|start
operator|)
operator|==
name|pathlen
condition|)
return|return
name|TRUE
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_module_db_set_load_inhibit:  * @db:           A #GimpModuleDB.  * @load_inhibit: A #G_SEARCHPATH_SEPARATOR delimited list of module  *                filenames to exclude from auto-loading.  *  * Sets the @load_inhibit flag for all #GimpModule's which are kept  * by @db (using gimp_module_set_load_inhibit()).  **/
end_comment

begin_function
name|void
DECL|function|gimp_module_db_set_load_inhibit (GimpModuleDB * db,const gchar * load_inhibit)
name|gimp_module_db_set_load_inhibit
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
specifier|const
name|gchar
modifier|*
name|load_inhibit
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MODULE_DB
argument_list|(
name|db
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|db
operator|->
name|load_inhibit
condition|)
name|g_free
argument_list|(
name|db
operator|->
name|load_inhibit
argument_list|)
expr_stmt|;
name|db
operator|->
name|load_inhibit
operator|=
name|g_strdup
argument_list|(
name|load_inhibit
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|db
operator|->
name|modules
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
name|GimpModule
modifier|*
name|module
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_module_set_load_inhibit
argument_list|(
name|module
argument_list|,
name|is_in_inhibit_list
argument_list|(
name|module
operator|->
name|filename
argument_list|,
name|load_inhibit
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_module_db_get_load_inhibit:  * @db: A #GimpModuleDB.  *  * Return the #G_SEARCHPATH_SEPARATOR selimited list of module filenames  * which are excluded from auto-loading.  *  * Return value: the @db's @load_inhibit string.  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_module_db_get_load_inhibit (GimpModuleDB * db)
name|gimp_module_db_get_load_inhibit
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MODULE_DB
argument_list|(
name|db
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|db
operator|->
name|load_inhibit
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_module_db_load:  * @db:          A #GimpModuleDB.  * @module_path: A #G_SEARCHPATH_SEPARATOR delimited list of directories  *               to load modules from.  *  * Scans the directories contained in @module_path using  * gimp_datafiles_read_directories() and creates a #GimpModule  * instance for every loadable module contained in the directories.  **/
end_comment

begin_function
name|void
DECL|function|gimp_module_db_load (GimpModuleDB * db,const gchar * module_path)
name|gimp_module_db_load
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
specifier|const
name|gchar
modifier|*
name|module_path
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MODULE_DB
argument_list|(
name|db
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|module_path
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_module_supported
argument_list|()
condition|)
name|gimp_datafiles_read_directories
argument_list|(
name|module_path
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|,
name|gimp_module_db_module_initialize
argument_list|,
name|db
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DUMP_DB
name|g_list_foreach
argument_list|(
name|db
operator|->
name|modules
argument_list|,
name|gimp_module_db_dump_module
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_comment
comment|/**  * gimp_module_db_refresh:  * @db:          A #GimpModuleDB.  * @module_path: A #G_SEARCHPATH_SEPARATOR delimited list of directories  *               to load modules from.  *  * Does the same as gimp_module_db_load(), plus removes all #GimpModule  * instances whose modules have been deleted from disk.  *  * Note that the #GimpModule's will just be removed from the internal  * list and not freed as this is not possible with #GTypeModule  * instances which actually implement types.  **/
end_comment

begin_function
name|void
DECL|function|gimp_module_db_refresh (GimpModuleDB * db,const gchar * module_path)
name|gimp_module_db_refresh
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
specifier|const
name|gchar
modifier|*
name|module_path
parameter_list|)
block|{
name|GList
modifier|*
name|kill_list
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MODULE_DB
argument_list|(
name|db
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|module_path
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/* remove modules we don't have on disk anymore */
name|g_list_foreach
argument_list|(
name|db
operator|->
name|modules
argument_list|,
name|gimp_module_db_module_on_disk_func
argument_list|,
operator|&
name|kill_list
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|kill_list
argument_list|,
name|gimp_module_db_module_remove_func
argument_list|,
name|db
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|kill_list
argument_list|)
expr_stmt|;
comment|/* walk filesystem and add new things we find */
name|gimp_datafiles_read_directories
argument_list|(
name|module_path
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|,
name|gimp_module_db_module_initialize
argument_list|,
name|db
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_module_db_module_initialize (const GimpDatafileData * file_data,gpointer user_data)
name|gimp_module_db_module_initialize
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
name|GimpModuleDB
modifier|*
name|db
init|=
name|GIMP_MODULE_DB
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|GimpModule
modifier|*
name|module
decl_stmt|;
name|gboolean
name|load_inhibit
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_datafiles_check_extension
argument_list|(
name|file_data
operator|->
name|filename
argument_list|,
literal|"."
name|G_MODULE_SUFFIX
argument_list|)
condition|)
return|return;
comment|/* don't load if we already know about it */
if|if
condition|(
name|gimp_module_db_module_find_by_path
argument_list|(
name|db
argument_list|,
name|file_data
operator|->
name|filename
argument_list|)
condition|)
return|return;
name|load_inhibit
operator|=
name|is_in_inhibit_list
argument_list|(
name|file_data
operator|->
name|filename
argument_list|,
name|db
operator|->
name|load_inhibit
argument_list|)
expr_stmt|;
name|module
operator|=
name|gimp_module_new
argument_list|(
name|file_data
operator|->
name|filename
argument_list|,
name|load_inhibit
argument_list|,
name|db
operator|->
name|verbose
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|module
argument_list|,
literal|"modified"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_module_db_module_modified
argument_list|)
argument_list|,
name|db
argument_list|)
expr_stmt|;
name|db
operator|->
name|modules
operator|=
name|g_list_append
argument_list|(
name|db
operator|->
name|modules
argument_list|,
name|module
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|db
argument_list|,
name|db_signals
index|[
name|ADD
index|]
argument_list|,
literal|0
argument_list|,
name|module
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpModule
modifier|*
DECL|function|gimp_module_db_module_find_by_path (GimpModuleDB * db,const char * fullpath)
name|gimp_module_db_module_find_by_path
parameter_list|(
name|GimpModuleDB
modifier|*
name|db
parameter_list|,
specifier|const
name|char
modifier|*
name|fullpath
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|db
operator|->
name|modules
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
name|GimpModule
modifier|*
name|module
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|module
operator|->
name|filename
argument_list|,
name|fullpath
argument_list|)
condition|)
return|return
name|module
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|DUMP_DB
end_ifdef

begin_function
specifier|static
name|void
DECL|function|gimp_module_db_dump_module (gpointer data,gpointer user_data)
name|gimp_module_db_dump_module
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpModule
modifier|*
name|module
init|=
name|data
decl_stmt|;
name|g_print
argument_list|(
literal|"\n%s: %s\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|module
operator|->
name|filename
argument_list|)
argument_list|,
name|gimp_module_state_name
argument_list|(
name|module
operator|->
name|state
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  module: %p  lasterr: %s  query: %p register: %p\n"
argument_list|,
name|module
operator|->
name|module
argument_list|,
name|module
operator|->
name|last_module_error
condition|?
name|module
operator|->
name|last_module_error
else|:
literal|"NONE"
argument_list|,
name|module
operator|->
name|query_module
argument_list|,
name|module
operator|->
name|register_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|->
name|info
condition|)
block|{
name|g_print
argument_list|(
literal|"  purpose:   %s\n"
literal|"  author:    %s\n"
literal|"  version:   %s\n"
literal|"  copyright: %s\n"
literal|"  date:      %s\n"
argument_list|,
name|module
operator|->
name|info
operator|->
name|purpose
condition|?
name|module
operator|->
name|info
operator|->
name|purpose
else|:
literal|"NONE"
argument_list|,
name|module
operator|->
name|info
operator|->
name|author
condition|?
name|module
operator|->
name|info
operator|->
name|author
else|:
literal|"NONE"
argument_list|,
name|module
operator|->
name|info
operator|->
name|version
condition|?
name|module
operator|->
name|info
operator|->
name|version
else|:
literal|"NONE"
argument_list|,
name|module
operator|->
name|info
operator|->
name|copyright
condition|?
name|module
operator|->
name|info
operator|->
name|copyright
else|:
literal|"NONE"
argument_list|,
name|module
operator|->
name|info
operator|->
name|date
condition|?
name|module
operator|->
name|info
operator|->
name|date
else|:
literal|"NONE"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|void
DECL|function|gimp_module_db_module_on_disk_func (gpointer data,gpointer user_data)
name|gimp_module_db_module_on_disk_func
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpModule
modifier|*
name|module
init|=
name|data
decl_stmt|;
name|GList
modifier|*
modifier|*
name|kill_list
init|=
name|user_data
decl_stmt|;
name|gboolean
name|old_on_disk
decl_stmt|;
name|old_on_disk
operator|=
name|module
operator|->
name|on_disk
expr_stmt|;
name|module
operator|->
name|on_disk
operator|=
name|g_file_test
argument_list|(
name|module
operator|->
name|filename
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
expr_stmt|;
comment|/* if it's not on the disk, and it isn't in memory, mark it to be    * removed later.    */
if|if
condition|(
operator|!
name|module
operator|->
name|on_disk
operator|&&
operator|!
name|module
operator|->
name|module
condition|)
block|{
operator|*
name|kill_list
operator|=
name|g_list_append
argument_list|(
operator|*
name|kill_list
argument_list|,
name|module
argument_list|)
expr_stmt|;
name|module
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|module
operator|&&
name|module
operator|->
name|on_disk
operator|!=
name|old_on_disk
condition|)
name|gimp_module_modified
argument_list|(
name|module
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_module_db_module_remove_func (gpointer data,gpointer user_data)
name|gimp_module_db_module_remove_func
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpModule
modifier|*
name|module
init|=
name|data
decl_stmt|;
name|GimpModuleDB
modifier|*
name|db
init|=
name|user_data
decl_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|module
argument_list|,
name|gimp_module_db_module_modified
argument_list|,
name|db
argument_list|)
expr_stmt|;
name|db
operator|->
name|modules
operator|=
name|g_list_remove
argument_list|(
name|db
operator|->
name|modules
argument_list|,
name|module
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|db
argument_list|,
name|db_signals
index|[
name|REMOVE
index|]
argument_list|,
literal|0
argument_list|,
name|module
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_module_db_module_modified (GimpModule * module,GimpModuleDB * db)
name|gimp_module_db_module_modified
parameter_list|(
name|GimpModule
modifier|*
name|module
parameter_list|,
name|GimpModuleDB
modifier|*
name|db
parameter_list|)
block|{
name|g_signal_emit
argument_list|(
name|db
argument_list|,
name|db_signals
index|[
name|MODULE_MODIFIED
index|]
argument_list|,
literal|0
argument_list|,
name|module
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

