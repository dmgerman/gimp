begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPPROGRESS_H__
end_ifndef

begin_define
DECL|macro|__GIMPPROGRESS_H__
define|#
directive|define
name|__GIMPPROGRESS_H__
end_define

begin_include
include|#
directive|include
file|"gdisplayF.h"
end_include

begin_comment
comment|/* Progress bars for use internally by the main GIMP application. */
end_comment

begin_comment
comment|/* structures */
end_comment

begin_struct_decl
struct_decl|struct
name|gimp_progress_pvt
struct_decl|;
end_struct_decl

begin_comment
comment|/* typedefs */
end_comment

begin_typedef
DECL|typedef|gimp_progress
typedef|typedef
name|struct
name|gimp_progress_pvt
name|gimp_progress
typedef|;
end_typedef

begin_typedef
DECL|typedef|progress_func_t
typedef|typedef
name|void
function_decl|(
modifier|*
name|progress_func_t
function_decl|)
parameter_list|(
name|int
name|ymin
parameter_list|,
name|int
name|ymax
parameter_list|,
name|int
name|curr_y
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/* functions */
end_comment

begin_function_decl
name|gimp_progress
modifier|*
name|progress_start
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
specifier|const
name|char
modifier|*
parameter_list|,
name|gboolean
parameter_list|,
name|GtkSignalFunc
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gimp_progress
modifier|*
name|progress_restart
parameter_list|(
name|gimp_progress
modifier|*
parameter_list|,
specifier|const
name|char
modifier|*
parameter_list|,
name|GtkSignalFunc
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|progress_update
parameter_list|(
name|gimp_progress
modifier|*
parameter_list|,
name|float
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|progress_step
parameter_list|(
name|gimp_progress
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|progress_end
parameter_list|(
name|gimp_progress
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|progress_update_and_flush
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPPROGRESS_H__ */
end_comment

end_unit

