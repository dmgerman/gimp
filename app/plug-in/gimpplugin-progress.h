begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PLUG_IN_H__
end_ifndef

begin_define
DECL|macro|__PLUG_IN_H__
define|#
directive|define
name|__PLUG_IN_H__
end_define

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_comment
comment|/* pid_t  */
end_comment

begin_include
include|#
directive|include
file|"pdb/procedural_db.h"
end_include

begin_comment
comment|/* ProcRecord */
end_comment

begin_include
include|#
directive|include
file|"plug-in-proc.h"
end_include

begin_comment
comment|/* to be removed */
end_comment

begin_define
DECL|macro|WRITE_BUFFER_SIZE
define|#
directive|define
name|WRITE_BUFFER_SIZE
value|512
end_define

begin_struct
DECL|struct|_PlugIn
struct|struct
name|_PlugIn
block|{
DECL|member|open
name|guint
name|open
range|:
literal|1
decl_stmt|;
comment|/* Is the plug-in open* */
DECL|member|query
name|guint
name|query
range|:
literal|1
decl_stmt|;
comment|/* Are we querying the plug-in? */
DECL|member|init
name|guint
name|init
range|:
literal|1
decl_stmt|;
comment|/* Are we initialing the plug-in? */
DECL|member|synchronous
name|guint
name|synchronous
range|:
literal|1
decl_stmt|;
comment|/* Is the plug-in running synchronously? */
DECL|member|recurse
name|guint
name|recurse
range|:
literal|1
decl_stmt|;
comment|/* Have we called 'gtk_main' recursively? */
DECL|member|busy
name|guint
name|busy
range|:
literal|1
decl_stmt|;
comment|/* Is the plug-in busy with a temp proc? */
DECL|member|pid
name|pid_t
name|pid
decl_stmt|;
comment|/* Plug-ins process id */
DECL|member|args
name|gchar
modifier|*
name|args
index|[
literal|7
index|]
decl_stmt|;
comment|/* Plug-ins command line arguments */
DECL|member|my_read
name|GIOChannel
modifier|*
name|my_read
decl_stmt|;
comment|/* App's read and write channels */
DECL|member|my_write
name|GIOChannel
modifier|*
name|my_write
decl_stmt|;
DECL|member|his_read
name|GIOChannel
modifier|*
name|his_read
decl_stmt|;
comment|/* Plug-in's read and write channels */
DECL|member|his_write
name|GIOChannel
modifier|*
name|his_write
decl_stmt|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
DECL|member|his_thread_id
name|guint
name|his_thread_id
decl_stmt|;
comment|/* Plug-in's thread ID */
DECL|member|his_read_fd
name|gint
name|his_read_fd
decl_stmt|;
comment|/* Plug-in's read pipe fd */
endif|#
directive|endif
DECL|member|input_id
name|guint32
name|input_id
decl_stmt|;
comment|/* Id of input proc */
DECL|member|write_buffer
name|gchar
name|write_buffer
index|[
name|WRITE_BUFFER_SIZE
index|]
decl_stmt|;
comment|/* Buffer for writing */
DECL|member|write_buffer_index
name|gint
name|write_buffer_index
decl_stmt|;
comment|/* Buffer index for writing */
DECL|member|temp_proc_defs
name|GSList
modifier|*
name|temp_proc_defs
decl_stmt|;
comment|/* Temporary procedures  */
DECL|member|progress
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
comment|/* Progress dialog */
DECL|member|user_data
name|PlugInDef
modifier|*
name|user_data
decl_stmt|;
comment|/* DON'T USE!! */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_PlugInDef
struct|struct
name|_PlugInDef
block|{
DECL|member|prog
name|gchar
modifier|*
name|prog
decl_stmt|;
DECL|member|proc_defs
name|GSList
modifier|*
name|proc_defs
decl_stmt|;
DECL|member|locale_domain
name|gchar
modifier|*
name|locale_domain
decl_stmt|;
DECL|member|locale_path
name|gchar
modifier|*
name|locale_path
decl_stmt|;
DECL|member|help_path
name|gchar
modifier|*
name|help_path
decl_stmt|;
DECL|member|mtime
name|time_t
name|mtime
decl_stmt|;
DECL|member|query
name|gboolean
name|query
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* Initialize the plug-ins */
end_comment

begin_function_decl
name|void
name|plug_in_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Kill all running plug-ins */
end_comment

begin_function_decl
name|void
name|plug_in_kill
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Get the "image_types" the plug-in works on. */
end_comment

begin_function_decl
name|gchar
modifier|*
name|plug_in_image_types
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add in the file load/save handler fields procedure. */
end_comment

begin_function_decl
name|PlugInProcDef
modifier|*
name|plug_in_file_handler
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|extensions
parameter_list|,
name|gchar
modifier|*
name|prefixes
parameter_list|,
name|gchar
modifier|*
name|magics
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add a plug-in definition. */
end_comment

begin_function_decl
name|void
name|plug_in_def_add
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Allocate and free a plug-in definition. */
end_comment

begin_function_decl
name|PlugInDef
modifier|*
name|plug_in_def_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|prog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_def_free
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|gboolean
name|free_proc_defs
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_def_set_mtime
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|time_t
name|mtime
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_def_set_locale_domain_name
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_def_set_locale_domain_path
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_def_set_help_path
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_def_add_proc_def
parameter_list|(
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Retrieve a plug-ins menu path */
end_comment

begin_function_decl
name|gchar
modifier|*
name|plug_in_menu_path
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Retrieve a plug-ins help path */
end_comment

begin_function_decl
name|gchar
modifier|*
name|plug_in_help_path
parameter_list|(
name|gchar
modifier|*
name|prog_name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Create a new plug-in structure */
end_comment

begin_function_decl
name|PlugIn
modifier|*
name|plug_in_new
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Destroy a plug-in structure.  *  This will close the plug-in first if necessary.  */
end_comment

begin_function_decl
name|void
name|plug_in_destroy
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Open a plug-in. This cause the plug-in to run.  * If returns TRUE, you must destroy the plugin.  * If returns FALSE, you must not destroy the plugin.  */
end_comment

begin_function_decl
name|gboolean
name|plug_in_open
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Close a plug-in. This kills the plug-in and releases its resources. */
end_comment

begin_function_decl
name|void
name|plug_in_close
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
name|gboolean
name|kill_it
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Run a plug-in as if it were a procedure database procedure */
end_comment

begin_function_decl
name|Argument
modifier|*
name|plug_in_run
parameter_list|(
name|ProcRecord
modifier|*
name|proc_rec
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|,
name|gint
name|argc
parameter_list|,
name|gboolean
name|synchronous
parameter_list|,
name|gboolean
name|destroy_values
parameter_list|,
name|gint
name|gdisp_ID
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Run the last plug-in again with the same arguments. Extensions  *  are exempt from this "privelege".  */
end_comment

begin_function_decl
name|void
name|plug_in_repeat
parameter_list|(
name|gboolean
name|with_interface
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Set the sensitivity for plug-in menu items based on the image type. */
end_comment

begin_function_decl
name|void
name|plug_in_set_menu_sensitivity
parameter_list|(
name|GimpImageType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Register an internal plug-in.  This is for file load-save  * handlers, which are organized around the plug-in data structure.  * This could all be done a little better, but oh well.  -josh  */
end_comment

begin_function_decl
name|void
name|plug_in_add_internal
parameter_list|(
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GSList
modifier|*
name|plug_in_extensions_parse
parameter_list|(
name|gchar
modifier|*
name|extensions
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PlugInImageType
name|plug_in_image_types_parse
parameter_list|(
name|gchar
modifier|*
name|image_types
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_progress_init
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
name|gchar
modifier|*
name|message
parameter_list|,
name|gint
name|gdisp_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_progress_update
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PlugIn
modifier|*
name|current_plug_in
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|proc_defs
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PLUG_IN_H__ */
end_comment

end_unit

