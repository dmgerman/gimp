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
DECL|member|ref_count
name|gint
name|ref_count
decl_stmt|;
DECL|member|open
name|guint
name|open
range|:
literal|1
decl_stmt|;
comment|/*  Is the plug-in open?                    */
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
comment|/*  Do we have an own GMainLoop?            */
DECL|member|in_temp_proc
name|guint
name|in_temp_proc
range|:
literal|1
decl_stmt|;
comment|/*  Is the plug-in busy with a temp proc?   */
DECL|member|starting_ext
name|guint
name|starting_ext
range|:
literal|1
decl_stmt|;
comment|/*  Does the plug-in wait for extension_ack?*/
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
name|guint
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
DECL|member|main_loops
name|GList
modifier|*
name|main_loops
decl_stmt|;
comment|/*  Stack of recursive main loops           */
DECL|member|return_vals
name|Argument
modifier|*
name|return_vals
decl_stmt|;
comment|/*  The return value we wait for            */
DECL|member|n_return_vals
name|gint
name|n_return_vals
decl_stmt|;
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
name|plug_in_exit
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

begin_function_decl
name|void
name|plug_in_ref
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_unref
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

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

begin_function_decl
name|void
name|plug_in_push
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_pop
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_main_loop
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_main_loop_quit
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PLUG_IN_H__ */
end_comment

end_unit

