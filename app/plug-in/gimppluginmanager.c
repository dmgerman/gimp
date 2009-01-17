begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis, and others  *  * gimppluginmanager.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"gimpenvirontable.h"
end_include

begin_include
include|#
directive|include
file|"gimpinterpreterdb.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugindebug.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugindef.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager-data.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager-help-domain.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager-history.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager-locale-domain.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager-menu-branch.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginshm.h"
end_include

begin_include
include|#
directive|include
file|"gimptemporaryprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2bf69f270103
block|{
DECL|enumerator|PLUG_IN_OPENED
name|PLUG_IN_OPENED
block|,
DECL|enumerator|PLUG_IN_CLOSED
name|PLUG_IN_CLOSED
block|,
DECL|enumerator|MENU_BRANCH_ADDED
name|MENU_BRANCH_ADDED
block|,
DECL|enumerator|HISTORY_CHANGED
name|HISTORY_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_plug_in_manager_dispose
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
name|gimp_plug_in_manager_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_plug_in_manager_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPlugInManager
argument_list|,
argument|gimp_plug_in_manager
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_plug_in_manager_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|manager_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_manager_class_init (GimpPlugInManagerClass * klass)
name|gimp_plug_in_manager_class_init
parameter_list|(
name|GimpPlugInManagerClass
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
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|manager_signals
index|[
name|PLUG_IN_OPENED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"plug-in-opened"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpPlugInManagerClass
argument_list|,
name|plug_in_opened
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__OBJECT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_PLUG_IN
argument_list|)
expr_stmt|;
name|manager_signals
index|[
name|PLUG_IN_CLOSED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"plug-in-closed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpPlugInManagerClass
argument_list|,
name|plug_in_closed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__OBJECT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_PLUG_IN
argument_list|)
expr_stmt|;
name|manager_signals
index|[
name|MENU_BRANCH_ADDED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"menu-branch-added"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpPlugInManagerClass
argument_list|,
name|menu_branch_added
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__STRING_STRING_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
name|manager_signals
index|[
name|HISTORY_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"history-changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpPlugInManagerClass
argument_list|,
name|history_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_plug_in_manager_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_plug_in_manager_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_plug_in_manager_get_memsize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_manager_init (GimpPlugInManager * manager)
name|gimp_plug_in_manager_init
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|)
block|{
name|manager
operator|->
name|gimp
operator|=
name|NULL
expr_stmt|;
name|manager
operator|->
name|plug_in_defs
operator|=
name|NULL
expr_stmt|;
name|manager
operator|->
name|write_pluginrc
operator|=
name|FALSE
expr_stmt|;
name|manager
operator|->
name|plug_in_procedures
operator|=
name|NULL
expr_stmt|;
name|manager
operator|->
name|load_procs
operator|=
name|NULL
expr_stmt|;
name|manager
operator|->
name|save_procs
operator|=
name|NULL
expr_stmt|;
name|manager
operator|->
name|current_plug_in
operator|=
name|NULL
expr_stmt|;
name|manager
operator|->
name|open_plug_ins
operator|=
name|NULL
expr_stmt|;
name|manager
operator|->
name|plug_in_stack
operator|=
name|NULL
expr_stmt|;
name|manager
operator|->
name|history
operator|=
name|NULL
expr_stmt|;
name|manager
operator|->
name|shm
operator|=
name|NULL
expr_stmt|;
name|manager
operator|->
name|interpreter_db
operator|=
name|gimp_interpreter_db_new
argument_list|()
expr_stmt|;
name|manager
operator|->
name|environ_table
operator|=
name|gimp_environ_table_new
argument_list|()
expr_stmt|;
name|manager
operator|->
name|debug
operator|=
name|NULL
expr_stmt|;
name|manager
operator|->
name|data_list
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_manager_dispose (GObject * object)
name|gimp_plug_in_manager_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPlugInManager
modifier|*
name|manager
init|=
name|GIMP_PLUG_IN_MANAGER
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gimp_plug_in_manager_history_clear
argument_list|(
name|manager
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
DECL|function|gimp_plug_in_manager_finalize (GObject * object)
name|gimp_plug_in_manager_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPlugInManager
modifier|*
name|manager
init|=
name|GIMP_PLUG_IN_MANAGER
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|manager
operator|->
name|load_procs
condition|)
block|{
name|g_slist_free
argument_list|(
name|manager
operator|->
name|load_procs
argument_list|)
expr_stmt|;
name|manager
operator|->
name|load_procs
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|manager
operator|->
name|save_procs
condition|)
block|{
name|g_slist_free
argument_list|(
name|manager
operator|->
name|save_procs
argument_list|)
expr_stmt|;
name|manager
operator|->
name|save_procs
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|manager
operator|->
name|plug_in_procedures
condition|)
block|{
name|g_slist_foreach
argument_list|(
name|manager
operator|->
name|plug_in_procedures
argument_list|,
operator|(
name|GFunc
operator|)
name|g_object_unref
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|manager
operator|->
name|plug_in_procedures
argument_list|)
expr_stmt|;
name|manager
operator|->
name|plug_in_procedures
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|manager
operator|->
name|plug_in_defs
condition|)
block|{
name|g_slist_foreach
argument_list|(
name|manager
operator|->
name|plug_in_defs
argument_list|,
operator|(
name|GFunc
operator|)
name|g_object_unref
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|manager
operator|->
name|plug_in_defs
argument_list|)
expr_stmt|;
name|manager
operator|->
name|plug_in_defs
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|manager
operator|->
name|shm
condition|)
block|{
name|gimp_plug_in_shm_free
argument_list|(
name|manager
operator|->
name|shm
argument_list|)
expr_stmt|;
name|manager
operator|->
name|shm
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|manager
operator|->
name|environ_table
condition|)
block|{
name|g_object_unref
argument_list|(
name|manager
operator|->
name|environ_table
argument_list|)
expr_stmt|;
name|manager
operator|->
name|environ_table
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|manager
operator|->
name|interpreter_db
condition|)
block|{
name|g_object_unref
argument_list|(
name|manager
operator|->
name|interpreter_db
argument_list|)
expr_stmt|;
name|manager
operator|->
name|interpreter_db
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|manager
operator|->
name|debug
condition|)
block|{
name|gimp_plug_in_debug_free
argument_list|(
name|manager
operator|->
name|debug
argument_list|)
expr_stmt|;
name|manager
operator|->
name|debug
operator|=
name|NULL
expr_stmt|;
block|}
name|gimp_plug_in_manager_menu_branch_exit
argument_list|(
name|manager
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_locale_domain_exit
argument_list|(
name|manager
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_help_domain_exit
argument_list|(
name|manager
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_data_free
argument_list|(
name|manager
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
specifier|static
name|gint64
DECL|function|gimp_plug_in_manager_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_plug_in_manager_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpPlugInManager
modifier|*
name|manager
init|=
name|GIMP_PLUG_IN_MANAGER
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|memsize
operator|+=
name|gimp_g_slist_get_memsize_foreach
argument_list|(
name|manager
operator|->
name|plug_in_defs
argument_list|,
operator|(
name|GimpMemsizeFunc
operator|)
name|gimp_object_get_memsize
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_g_slist_get_memsize
argument_list|(
name|manager
operator|->
name|plug_in_procedures
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_g_slist_get_memsize
argument_list|(
name|manager
operator|->
name|load_procs
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_g_slist_get_memsize
argument_list|(
name|manager
operator|->
name|save_procs
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_g_slist_get_memsize
argument_list|(
name|manager
operator|->
name|menu_branches
argument_list|,
literal|0
comment|/* FIXME */
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_g_slist_get_memsize
argument_list|(
name|manager
operator|->
name|locale_domains
argument_list|,
literal|0
comment|/* FIXME */
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_g_slist_get_memsize
argument_list|(
name|manager
operator|->
name|help_domains
argument_list|,
literal|0
comment|/* FIXME */
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_g_slist_get_memsize_foreach
argument_list|(
name|manager
operator|->
name|open_plug_ins
argument_list|,
operator|(
name|GimpMemsizeFunc
operator|)
name|gimp_object_get_memsize
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_g_slist_get_memsize
argument_list|(
name|manager
operator|->
name|plug_in_stack
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_g_slist_get_memsize
argument_list|(
name|manager
operator|->
name|history
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|memsize
operator|+=
literal|0
expr_stmt|;
comment|/* FIXME manager->shm */
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|manager
operator|->
name|interpreter_db
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|manager
operator|->
name|environ_table
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
name|memsize
operator|+=
literal|0
expr_stmt|;
comment|/* FIXME manager->plug_in_debug */
name|memsize
operator|+=
name|gimp_g_list_get_memsize
argument_list|(
name|manager
operator|->
name|data_list
argument_list|,
literal|0
comment|/* FIXME */
argument_list|)
expr_stmt|;
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpPlugInManager
modifier|*
DECL|function|gimp_plug_in_manager_new (Gimp * gimp)
name|gimp_plug_in_manager_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpPlugInManager
modifier|*
name|manager
decl_stmt|;
name|manager
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PLUG_IN_MANAGER
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|manager
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
return|return
name|manager
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_initialize (GimpPlugInManager * manager,GimpInitStatusFunc status_callback)
name|gimp_plug_in_manager_initialize
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|)
block|{
name|gchar
modifier|*
name|path
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|status_callback
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|status_callback
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Plug-In Interpreters"
argument_list|)
argument_list|,
literal|0.8
argument_list|)
expr_stmt|;
name|path
operator|=
name|gimp_config_path_expand
argument_list|(
name|manager
operator|->
name|gimp
operator|->
name|config
operator|->
name|interpreter_path
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_interpreter_db_load
argument_list|(
name|manager
operator|->
name|interpreter_db
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|status_callback
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Plug-In Environment"
argument_list|)
argument_list|,
literal|0.9
argument_list|)
expr_stmt|;
name|path
operator|=
name|gimp_config_path_expand
argument_list|(
name|manager
operator|->
name|gimp
operator|->
name|config
operator|->
name|environ_path
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_environ_table_load
argument_list|(
name|manager
operator|->
name|environ_table
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
comment|/*  allocate a piece of shared memory for use in transporting tiles    *  to plug-ins. if we can't allocate a piece of shared memory then    *  we'll fall back on sending the data over the pipe.    */
if|if
condition|(
name|manager
operator|->
name|gimp
operator|->
name|use_shm
condition|)
name|manager
operator|->
name|shm
operator|=
name|gimp_plug_in_shm_new
argument_list|()
expr_stmt|;
name|manager
operator|->
name|debug
operator|=
name|gimp_plug_in_debug_new
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_exit (GimpPlugInManager * manager)
name|gimp_plug_in_manager_exit
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|manager
operator|->
name|open_plug_ins
condition|)
name|gimp_plug_in_close
argument_list|(
name|manager
operator|->
name|open_plug_ins
operator|->
name|data
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_add_procedure (GimpPlugInManager * manager,GimpPlugInProcedure * procedure)
name|gimp_plug_in_manager_add_procedure
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|manager
operator|->
name|plug_in_procedures
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|GimpPlugInProcedure
modifier|*
name|tmp_proc
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
operator|->
name|name
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tmp_proc
argument_list|)
operator|->
name|name
argument_list|)
operator|==
literal|0
condition|)
block|{
name|GSList
modifier|*
name|list2
decl_stmt|;
name|list
operator|->
name|data
operator|=
name|g_object_ref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"Removing duplicate PDB procedure '%s' "
literal|"registered by '%s'\n"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tmp_proc
argument_list|)
operator|->
name|name
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|tmp_proc
operator|->
name|prog
argument_list|)
argument_list|)
expr_stmt|;
comment|/* search the plugin list to see if any plugins had references to            * the tmp_proc.            */
for|for
control|(
name|list2
operator|=
name|manager
operator|->
name|plug_in_defs
init|;
name|list2
condition|;
name|list2
operator|=
name|list2
operator|->
name|next
control|)
block|{
name|GimpPlugInDef
modifier|*
name|plug_in_def
init|=
name|list2
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|g_slist_find
argument_list|(
name|plug_in_def
operator|->
name|procedures
argument_list|,
name|tmp_proc
argument_list|)
condition|)
name|gimp_plug_in_def_remove_procedure
argument_list|(
name|plug_in_def
argument_list|,
name|tmp_proc
argument_list|)
expr_stmt|;
block|}
comment|/* also remove it from the lists of load and save procs */
name|manager
operator|->
name|load_procs
operator|=
name|g_slist_remove
argument_list|(
name|manager
operator|->
name|load_procs
argument_list|,
name|tmp_proc
argument_list|)
expr_stmt|;
name|manager
operator|->
name|save_procs
operator|=
name|g_slist_remove
argument_list|(
name|manager
operator|->
name|save_procs
argument_list|,
name|tmp_proc
argument_list|)
expr_stmt|;
comment|/* and from the history */
name|gimp_plug_in_manager_history_remove
argument_list|(
name|manager
argument_list|,
name|tmp_proc
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|tmp_proc
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
name|manager
operator|->
name|plug_in_procedures
operator|=
name|g_slist_prepend
argument_list|(
name|manager
operator|->
name|plug_in_procedures
argument_list|,
name|g_object_ref
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_add_temp_proc (GimpPlugInManager * manager,GimpTemporaryProcedure * procedure)
name|gimp_plug_in_manager_add_temp_proc
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpTemporaryProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEMPORARY_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|manager
operator|->
name|gimp
operator|->
name|pdb
argument_list|,
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|manager
operator|->
name|plug_in_procedures
operator|=
name|g_slist_prepend
argument_list|(
name|manager
operator|->
name|plug_in_procedures
argument_list|,
name|g_object_ref
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_remove_temp_proc (GimpPlugInManager * manager,GimpTemporaryProcedure * procedure)
name|gimp_plug_in_manager_remove_temp_proc
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpTemporaryProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEMPORARY_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|manager
operator|->
name|plug_in_procedures
operator|=
name|g_slist_remove
argument_list|(
name|manager
operator|->
name|plug_in_procedures
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_history_remove
argument_list|(
name|manager
argument_list|,
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_unregister_procedure
argument_list|(
name|manager
operator|->
name|gimp
operator|->
name|pdb
argument_list|,
name|GIMP_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_add_open_plug_in (GimpPlugInManager * manager,GimpPlugIn * plug_in)
name|gimp_plug_in_manager_add_open_plug_in
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
name|manager
operator|->
name|open_plug_ins
operator|=
name|g_slist_prepend
argument_list|(
name|manager
operator|->
name|open_plug_ins
argument_list|,
name|g_object_ref
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|manager
argument_list|,
name|manager_signals
index|[
name|PLUG_IN_OPENED
index|]
argument_list|,
literal|0
argument_list|,
name|plug_in
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_remove_open_plug_in (GimpPlugInManager * manager,GimpPlugIn * plug_in)
name|gimp_plug_in_manager_remove_open_plug_in
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
name|manager
operator|->
name|open_plug_ins
operator|=
name|g_slist_remove
argument_list|(
name|manager
operator|->
name|open_plug_ins
argument_list|,
name|plug_in
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|manager
argument_list|,
name|manager_signals
index|[
name|PLUG_IN_CLOSED
index|]
argument_list|,
literal|0
argument_list|,
name|plug_in
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_plug_in_push (GimpPlugInManager * manager,GimpPlugIn * plug_in)
name|gimp_plug_in_manager_plug_in_push
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
name|manager
operator|->
name|current_plug_in
operator|=
name|plug_in
expr_stmt|;
name|manager
operator|->
name|plug_in_stack
operator|=
name|g_slist_prepend
argument_list|(
name|manager
operator|->
name|plug_in_stack
argument_list|,
name|manager
operator|->
name|current_plug_in
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_plug_in_pop (GimpPlugInManager * manager)
name|gimp_plug_in_manager_plug_in_pop
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|manager
operator|->
name|current_plug_in
condition|)
name|manager
operator|->
name|plug_in_stack
operator|=
name|g_slist_remove
argument_list|(
name|manager
operator|->
name|plug_in_stack
argument_list|,
name|manager
operator|->
name|plug_in_stack
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|manager
operator|->
name|plug_in_stack
condition|)
name|manager
operator|->
name|current_plug_in
operator|=
name|manager
operator|->
name|plug_in_stack
operator|->
name|data
expr_stmt|;
else|else
name|manager
operator|->
name|current_plug_in
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_history_changed (GimpPlugInManager * manager)
name|gimp_plug_in_manager_history_changed
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|manager
argument_list|,
name|manager_signals
index|[
name|HISTORY_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

