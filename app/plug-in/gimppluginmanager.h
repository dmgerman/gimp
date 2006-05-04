begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppluginmanager.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_MANAGER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_MANAGER_H__
define|#
directive|define
name|__GIMP_PLUG_IN_MANAGER_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PLUG_IN_MANAGER
define|#
directive|define
name|GIMP_TYPE_PLUG_IN_MANAGER
value|(gimp_plug_in_manager_get_type ())
end_define

begin_define
DECL|macro|GIMP_PLUG_IN_MANAGER (obj)
define|#
directive|define
name|GIMP_PLUG_IN_MANAGER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PLUG_IN_MANAGER, GimpPlugInManager))
end_define

begin_define
DECL|macro|GIMP_PLUG_IN_MANAGER_CLASS (klass)
define|#
directive|define
name|GIMP_PLUG_IN_MANAGER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PLUG_IN_MANAGER, GimpPlugInManagerClass))
end_define

begin_define
DECL|macro|GIMP_IS_PLUG_IN_MANAGER (obj)
define|#
directive|define
name|GIMP_IS_PLUG_IN_MANAGER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PLUG_IN_MANAGER))
end_define

begin_define
DECL|macro|GIMP_IS_PLUG_IN_MANAGER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PLUG_IN_MANAGER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PLUG_IN_MANAGER))
end_define

begin_typedef
DECL|typedef|GimpPlugInManagerClass
typedef|typedef
name|struct
name|_GimpPlugInManagerClass
name|GimpPlugInManagerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPlugInManager
struct|struct
name|_GimpPlugInManager
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|plug_in_defs
name|GSList
modifier|*
name|plug_in_defs
decl_stmt|;
DECL|member|write_pluginrc
name|gboolean
name|write_pluginrc
decl_stmt|;
DECL|member|plug_in_procedures
name|GSList
modifier|*
name|plug_in_procedures
decl_stmt|;
DECL|member|load_procs
name|GSList
modifier|*
name|load_procs
decl_stmt|;
DECL|member|save_procs
name|GSList
modifier|*
name|save_procs
decl_stmt|;
DECL|member|menu_branches
name|GSList
modifier|*
name|menu_branches
decl_stmt|;
DECL|member|locale_domains
name|GSList
modifier|*
name|locale_domains
decl_stmt|;
DECL|member|help_domains
name|GSList
modifier|*
name|help_domains
decl_stmt|;
DECL|member|current_plug_in
name|GimpPlugIn
modifier|*
name|current_plug_in
decl_stmt|;
DECL|member|open_plug_ins
name|GSList
modifier|*
name|open_plug_ins
decl_stmt|;
DECL|member|plug_in_stack
name|GSList
modifier|*
name|plug_in_stack
decl_stmt|;
DECL|member|last_plug_ins
name|GSList
modifier|*
name|last_plug_ins
decl_stmt|;
DECL|member|shm
name|GimpPlugInShm
modifier|*
name|shm
decl_stmt|;
DECL|member|interpreter_db
name|GimpInterpreterDB
modifier|*
name|interpreter_db
decl_stmt|;
DECL|member|environ_table
name|GimpEnvironTable
modifier|*
name|environ_table
decl_stmt|;
DECL|member|debug
name|GimpPlugInDebug
modifier|*
name|debug
decl_stmt|;
DECL|member|data_list
name|GList
modifier|*
name|data_list
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPlugInManagerClass
struct|struct
name|_GimpPlugInManagerClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|menu_branch_added
name|void
function_decl|(
modifier|*
name|menu_branch_added
function_decl|)
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_label
parameter_list|)
function_decl|;
DECL|member|last_plug_ins_changed
name|void
function_decl|(
modifier|*
name|last_plug_ins_changed
function_decl|)
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_plug_in_manager_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpPlugInManager
modifier|*
name|gimp_plug_in_manager_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_manager_initialize
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_manager_restore
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_manager_exit
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Register a plug-in. This function is public for file load-save  * handlers, which are organized around the plug-in data structure.  * This could all be done a little better, but oh well.  -josh  */
end_comment

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_manager_set_last_plug_in
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_manager_plug_in_pop
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PLUG_IN_MANAGER_H__ */
end_comment

end_unit

