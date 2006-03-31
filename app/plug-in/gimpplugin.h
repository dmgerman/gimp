begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * plug-in.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"plug-in-proc-frame.h"
end_include

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
DECL|member|pid
name|GPid
name|pid
decl_stmt|;
comment|/*  Plug-in's process id                    */
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/*  Plug-in's name                          */
DECL|member|prog
name|gchar
modifier|*
name|prog
decl_stmt|;
comment|/*  Plug-in's full path name                */
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
DECL|member|ext_main_loop
name|GMainLoop
modifier|*
name|ext_main_loop
decl_stmt|;
comment|/*  for waiting for extension_ack           */
DECL|member|main_proc_frame
name|PlugInProcFrame
name|main_proc_frame
decl_stmt|;
DECL|member|temp_proc_frames
name|GList
modifier|*
name|temp_proc_frames
decl_stmt|;
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
name|GimpContext
modifier|*
name|context
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
name|GimpContext
modifier|*
name|context
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
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prog
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
name|Gimp
modifier|*
name|gimp
parameter_list|,
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
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PlugInProcFrame
modifier|*
name|plug_in_get_proc_frame
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PlugInProcFrame
modifier|*
name|plug_in_proc_frame_push
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_proc_frame_pop
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
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

begin_function_decl
name|gchar
modifier|*
name|plug_in_get_undo_desc
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|plug_in_menu_register
parameter_list|(
name|PlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
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

