begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
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
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_define
DECL|macro|WRITE_BUFFER_SIZE
define|#
directive|define
name|WRITE_BUFFER_SIZE
value|512
end_define

begin_define
DECL|macro|RGB_IMAGE
define|#
directive|define
name|RGB_IMAGE
value|0x01
end_define

begin_define
DECL|macro|GRAY_IMAGE
define|#
directive|define
name|GRAY_IMAGE
value|0x02
end_define

begin_define
DECL|macro|INDEXED_IMAGE
define|#
directive|define
name|INDEXED_IMAGE
value|0x04
end_define

begin_define
DECL|macro|RGBA_IMAGE
define|#
directive|define
name|RGBA_IMAGE
value|0x08
end_define

begin_define
DECL|macro|GRAYA_IMAGE
define|#
directive|define
name|GRAYA_IMAGE
value|0x10
end_define

begin_define
DECL|macro|INDEXEDA_IMAGE
define|#
directive|define
name|INDEXEDA_IMAGE
value|0x20
end_define

begin_typedef
DECL|typedef|PlugIn
typedef|typedef
name|struct
name|_PlugIn
name|PlugIn
typedef|;
end_typedef

begin_typedef
DECL|typedef|PlugInDef
typedef|typedef
name|struct
name|_PlugInDef
name|PlugInDef
typedef|;
end_typedef

begin_typedef
DECL|typedef|PlugInProcDef
typedef|typedef
name|struct
name|_PlugInProcDef
name|PlugInProcDef
typedef|;
end_typedef

begin_struct
DECL|struct|_PlugIn
struct|struct
name|_PlugIn
block|{
DECL|member|open
name|unsigned
name|int
name|open
range|:
literal|1
decl_stmt|;
comment|/* Is the plug-in open */
DECL|member|destroy
name|unsigned
name|int
name|destroy
range|:
literal|1
decl_stmt|;
comment|/* Should the plug-in by destroyed */
DECL|member|query
name|unsigned
name|int
name|query
range|:
literal|1
decl_stmt|;
comment|/* Are we querying the plug-in? */
DECL|member|synchronous
name|unsigned
name|int
name|synchronous
range|:
literal|1
decl_stmt|;
comment|/* Is the plug-in running synchronously or not */
DECL|member|recurse
name|unsigned
name|int
name|recurse
range|:
literal|1
decl_stmt|;
comment|/* Have we called 'gtk_main' recursively? */
DECL|member|busy
name|unsigned
name|int
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
name|char
modifier|*
name|args
index|[
literal|7
index|]
decl_stmt|;
comment|/* Plug-ins command line arguments */
DECL|member|my_read
DECL|member|my_write
name|int
name|my_read
decl_stmt|,
name|my_write
decl_stmt|;
comment|/* Apps read and write file descriptors */
DECL|member|his_read
DECL|member|his_write
name|int
name|his_read
decl_stmt|,
name|his_write
decl_stmt|;
comment|/* Plug-ins read and write file descriptors */
DECL|member|input_id
name|guint32
name|input_id
decl_stmt|;
comment|/* Id of input proc */
DECL|member|write_buffer
name|char
name|write_buffer
index|[
name|WRITE_BUFFER_SIZE
index|]
decl_stmt|;
comment|/* Buffer for writing */
DECL|member|write_buffer_index
name|int
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
name|GtkWidget
modifier|*
name|progress
decl_stmt|;
comment|/* Progress dialog */
DECL|member|progress_label
name|GtkWidget
modifier|*
name|progress_label
decl_stmt|;
DECL|member|progress_bar
name|GtkWidget
modifier|*
name|progress_bar
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
comment|/* Handle for hanging data onto */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_PlugInDef
struct|struct
name|_PlugInDef
block|{
DECL|member|prog
name|char
modifier|*
name|prog
decl_stmt|;
DECL|member|proc_defs
name|GSList
modifier|*
name|proc_defs
decl_stmt|;
DECL|member|mtime
name|time_t
name|mtime
decl_stmt|;
DECL|member|query
name|int
name|query
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_PlugInProcDef
struct|struct
name|_PlugInProcDef
block|{
DECL|member|prog
name|char
modifier|*
name|prog
decl_stmt|;
DECL|member|menu_path
name|char
modifier|*
name|menu_path
decl_stmt|;
DECL|member|accelerator
name|char
modifier|*
name|accelerator
decl_stmt|;
DECL|member|extensions
name|char
modifier|*
name|extensions
decl_stmt|;
DECL|member|prefixes
name|char
modifier|*
name|prefixes
decl_stmt|;
DECL|member|magics
name|char
modifier|*
name|magics
decl_stmt|;
DECL|member|image_types
name|char
modifier|*
name|image_types
decl_stmt|;
DECL|member|image_types_val
name|int
name|image_types_val
decl_stmt|;
DECL|member|db_info
name|ProcRecord
name|db_info
decl_stmt|;
DECL|member|extensions_list
name|GSList
modifier|*
name|extensions_list
decl_stmt|;
DECL|member|prefixes_list
name|GSList
modifier|*
name|prefixes_list
decl_stmt|;
DECL|member|magics_list
name|GSList
modifier|*
name|magics_list
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
name|void
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
comment|/* Add a plug-in to the list of valid plug-ins  *  and query the plug-in for information if  *  necessary.  */
end_comment

begin_function_decl
name|void
name|plug_in_add
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|char
modifier|*
name|menu_path
parameter_list|,
name|char
modifier|*
name|accelerator
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Get the "image_types" the plug-in works on.  */
end_comment

begin_function_decl
name|char
modifier|*
name|plug_in_image_types
parameter_list|(
name|char
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add in the file load/save handler fields procedure.  */
end_comment

begin_function_decl
name|PlugInProcDef
modifier|*
name|plug_in_file_handler
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|char
modifier|*
name|extensions
parameter_list|,
name|char
modifier|*
name|prefixes
parameter_list|,
name|char
modifier|*
name|magics
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add a plug-in definition.  */
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
comment|/* Retrieve a plug-ins menu path  */
end_comment

begin_function_decl
name|char
modifier|*
name|plug_in_menu_path
parameter_list|(
name|char
modifier|*
name|name
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
name|char
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Destroy a plug-in structure. This will close the plug-in  *  first if necessary.  */
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
comment|/* Open a plug-in. This cause the plug-in to run. */
end_comment

begin_function_decl
name|int
name|plug_in_open
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Close a plug-in. This kills the plug-in and releases  *  its resources.  */
end_comment

begin_function_decl
name|void
name|plug_in_close
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
name|int
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
name|int
name|synchronous
parameter_list|,
name|int
name|destroy_values
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Run the last plug-in again with the same arguments. Extensions  *  are exempt from this "privelege".  */
end_comment

begin_function_decl
name|void
name|plug_in_repeat
parameter_list|(
name|int
name|with_interface
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Set the sensitivity for plug-in menu items based on the image  *  base type.  */
end_comment

begin_function_decl
name|void
name|plug_in_set_menu_sensitivity
parameter_list|(
name|int
name|base_type
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
name|char
modifier|*
name|extensions
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|plug_in_image_types_parse
parameter_list|(
name|char
modifier|*
name|image_types
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PLUG_IN_H__ */
end_comment

end_unit

