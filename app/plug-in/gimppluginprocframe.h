begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginprocframe.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_PROC_FRAME_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_PRON_FRAME_H__
define|#
directive|define
name|__GIMP_PLUG_IN_PRON_FRAME_H__
end_define

begin_struct
DECL|struct|_GimpPlugInProcFrame
struct|struct
name|_GimpPlugInProcFrame
block|{
DECL|member|ref_count
name|gint
name|ref_count
decl_stmt|;
DECL|member|main_context
name|GimpContext
modifier|*
name|main_context
decl_stmt|;
DECL|member|context_stack
name|GList
modifier|*
name|context_stack
decl_stmt|;
DECL|member|procedure
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
DECL|member|main_loop
name|GMainLoop
modifier|*
name|main_loop
decl_stmt|;
DECL|member|return_vals
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
DECL|member|progress
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
DECL|member|progress_created
name|gboolean
name|progress_created
decl_stmt|;
DECL|member|progress_cancel_id
name|gulong
name|progress_cancel_id
decl_stmt|;
DECL|member|error_handler
name|GimpPDBErrorHandler
name|error_handler
decl_stmt|;
comment|/*  lists of things to clean up on dispose  */
DECL|member|image_cleanups
name|GList
modifier|*
name|image_cleanups
decl_stmt|;
DECL|member|item_cleanups
name|GList
modifier|*
name|item_cleanups
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GimpPlugInProcFrame
modifier|*
name|gimp_plug_in_proc_frame_new
parameter_list|(
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_proc_frame_init
parameter_list|(
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_proc_frame_dispose
parameter_list|(
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
parameter_list|,
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPlugInProcFrame
modifier|*
name|gimp_plug_in_proc_frame_ref
parameter_list|(
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_proc_frame_unref
parameter_list|(
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
parameter_list|,
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpValueArray
modifier|*
name|gimp_plug_in_proc_frame_get_return_values
parameter_list|(
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PLUG_IN_PROC_FRAME_H__ */
end_comment

end_unit

