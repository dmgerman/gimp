begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpplugin.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_H__
define|#
directive|define
name|__GIMP_PLUG_IN_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginprocframe.h"
end_include

begin_define
DECL|macro|WRITE_BUFFER_SIZE
define|#
directive|define
name|WRITE_BUFFER_SIZE
value|512
end_define

begin_define
DECL|macro|GIMP_TYPE_PLUG_IN
define|#
directive|define
name|GIMP_TYPE_PLUG_IN
value|(gimp_plug_in_get_type ())
end_define

begin_define
DECL|macro|GIMP_PLUG_IN (obj)
define|#
directive|define
name|GIMP_PLUG_IN
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PLUG_IN, GimpPlugIn))
end_define

begin_define
DECL|macro|GIMP_PLUG_IN_CLASS (klass)
define|#
directive|define
name|GIMP_PLUG_IN_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PLUG_IN, GimpPlugInClass))
end_define

begin_define
DECL|macro|GIMP_IS_PLUG_IN (obj)
define|#
directive|define
name|GIMP_IS_PLUG_IN
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PLUG_IN))
end_define

begin_define
DECL|macro|GIMP_IS_PLUG_IN_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PLUG_IN_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PLUG_IN))
end_define

begin_typedef
DECL|typedef|GimpPlugInClass
typedef|typedef
name|struct
name|_GimpPlugInClass
name|GimpPlugInClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPlugIn
struct|struct
name|_GimpPlugIn
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|manager
name|GimpPlugInManager
modifier|*
name|manager
decl_stmt|;
DECL|member|prog
name|gchar
modifier|*
name|prog
decl_stmt|;
comment|/*  Plug-in's full path name          */
DECL|member|call_mode
name|GimpPlugInCallMode
name|call_mode
decl_stmt|;
comment|/*  QUERY, INIT or RUN                */
DECL|member|open
name|guint
name|open
range|:
literal|1
decl_stmt|;
comment|/*  Is the plug-in open?              */
DECL|member|pid
name|GPid
name|pid
decl_stmt|;
comment|/*  Plug-in's process id              */
DECL|member|my_read
name|GIOChannel
modifier|*
name|my_read
decl_stmt|;
comment|/*  App's read and write channels     */
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
comment|/*  Plug-in's read and write channels */
DECL|member|his_write
name|GIOChannel
modifier|*
name|his_write
decl_stmt|;
DECL|member|input_id
name|guint
name|input_id
decl_stmt|;
comment|/*  Id of input proc                  */
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
comment|/* Buffer index       */
DECL|member|temp_procedures
name|GSList
modifier|*
name|temp_procedures
decl_stmt|;
comment|/*  Temporary procedures              */
DECL|member|ext_main_loop
name|GMainLoop
modifier|*
name|ext_main_loop
decl_stmt|;
comment|/*  for waiting for extension_ack     */
DECL|member|main_proc_frame
name|GimpPlugInProcFrame
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
comment|/*  Valid during query() and init()   */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPlugInClass
struct|struct
name|_GimpPlugInClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_plug_in_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpPlugIn
modifier|*
name|gimp_plug_in_new
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpPlugInProcedure
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
name|gboolean
name|gimp_plug_in_open
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpPlugInCallMode
name|call_mode
parameter_list|,
name|gboolean
name|synchronous
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_close
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|gboolean
name|kill_it
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPlugInProcFrame
modifier|*
name|gimp_plug_in_get_proc_frame
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPlugInProcFrame
modifier|*
name|gimp_plug_in_proc_frame_push
parameter_list|(
name|GimpPlugIn
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
name|GimpTemporaryProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_proc_frame_pop
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_main_loop
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_main_loop_quit
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_plug_in_get_undo_desc
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_plug_in_menu_register
parameter_list|(
name|GimpPlugIn
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

begin_function_decl
name|void
name|gimp_plug_in_add_temp_proc
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpTemporaryProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_remove_temp_proc
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpTemporaryProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PLUG_IN_H__ */
end_comment

end_unit

