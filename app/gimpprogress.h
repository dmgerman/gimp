begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROGRESS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROGRESS_H__
define|#
directive|define
name|__GIMP_PROGRESS_H__
end_define

begin_comment
comment|/* Progress bars for use internally by the main GIMP application. */
end_comment

begin_comment
comment|/* functions */
end_comment

begin_function_decl
name|GimpProgress
modifier|*
name|progress_start
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|important
parameter_list|,
name|GCallback
name|cancel_callback
parameter_list|,
name|gpointer
name|cancel_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpProgress
modifier|*
name|progress_restart
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|GCallback
name|cancel_callback
parameter_list|,
name|gpointer
name|cancel_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|progress_update
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|progress_step
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|progress_update_and_flush
parameter_list|(
name|gint
name|ymin
parameter_list|,
name|gint
name|ymax
parameter_list|,
name|gint
name|curr_x
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PROGRESS_H__ */
end_comment

end_unit

