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
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|open
name|guint
name|open
range|:
literal|1
decl_stmt|;
comment|/*  Is the plug-in open*                    */
DECL|member|query
name|guint
name|query
range|:
literal|1
decl_stmt|;
comment|/*  Are we querying the plug-in?            */
DECL|member|init
name|guint
name|init
range|:
literal|1
decl_stmt|;
comment|/*  Are we initialing the plug-in?          */
DECL|member|synchronous
name|guint
name|synchronous
range|:
literal|1
decl_stmt|;
comment|/*  Is the plug-in running synchronously?   */
DECL|member|recurse
name|guint
name|recurse
range|:
literal|1
decl_stmt|;
comment|/*  Have we called 'gtk_main' recursively?  */
DECL|member|busy
name|guint
name|busy
range|:
literal|1
decl_stmt|;
comment|/*  Is the plug-in busy with a temp proc?   */
DECL|member|pid
name|pid_t
name|pid
decl_stmt|;
comment|/*  Plug-ins process id                     */
DECL|member|args
name|gchar
modifier|*
name|args
index|[
literal|7
index|]
decl_stmt|;
comment|/*  Plug-ins command line arguments         */
DECL|member|my_read
name|GIOChannel
modifier|*
name|my_read
decl_stmt|;
comment|/*  App's read and write channels           */
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
comment|/*  Plug-in's read and write channels       */
DECL|member|his_write
name|GIOChannel
modifier|*
name|his_write
decl_stmt|;
DECL|member|input_id
name|guint32
name|input_id
decl_stmt|;
comment|/*  Id of input proc                        */
DECL|member|write_buffer
name|gchar
name|write_buffer
index|[
name|WRITE_BUFFER_SIZE
index|]
decl_stmt|;
comment|/*  Buffer for writing       */
DECL|member|write_buffer_index
name|gint
name|write_buffer_index
decl_stmt|;
comment|/*  Buffer index for writing */
DECL|member|temp_proc_defs
name|GSList
modifier|*
name|temp_proc_defs
decl_stmt|;
comment|/*  Temporary procedures                    */
DECL|member|progress
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
comment|/*  Progress dialog                         */
DECL|member|plug_in_def
name|PlugInDef
modifier|*
name|plug_in_def
decl_stmt|;
comment|/*  Valid only during query() and init()    */
block|}
struct|;
end_struct

begin_function_decl
name|void
name|plug_in_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_kill
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_call_query
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_call_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Create a new plug-in structure  */
end_comment

begin_function_decl
name|PlugIn
modifier|*
name|plug_in_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
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
comment|/*  Open a plug-in. This cause the plug-in to run.  *  If returns TRUE, you must destroy the plugin.  *  If returns FALSE, you must not destroy the plugin.  */
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
comment|/*  Close a plug-in. This kills the plug-in and releases its resources.  */
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
comment|/*  Run a plug-in as if it were a procedure database procedure  */
end_comment

begin_function_decl
name|Argument
modifier|*
name|plug_in_run
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
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
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|display_ID
parameter_list|,
name|gint
name|image_ID
parameter_list|,
name|gint
name|drawable_ID
parameter_list|,
name|gboolean
name|with_interface
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
name|ProcRecord
modifier|*
name|last_plug_in
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

