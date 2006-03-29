begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * plug-in-run.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PLUG_IN_RUN_H__
end_ifndef

begin_define
DECL|macro|__PLUG_IN_RUN_H__
define|#
directive|define
name|__PLUG_IN_RUN_H__
end_define

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
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
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
name|n_args
parameter_list|,
name|gboolean
name|synchronous
parameter_list|,
name|gboolean
name|destroy_return_vals
parameter_list|,
name|gint
name|display_ID
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Run one of the last plug-ins from the plug-in history again with  *  the same arguments. Extensions are exempt from this "privelege".  */
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
name|index
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PLUG_IN_RUN_H__ */
end_comment

end_unit

