begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__ACTIONS_H__
end_ifndef

begin_define
DECL|macro|__ACTIONS_H__
define|#
directive|define
name|__ACTIONS_H__
end_define

begin_decl_stmt
specifier|extern
name|GimpActionFactory
modifier|*
name|global_action_factory
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|actions_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|actions_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Gimp
modifier|*
name|action_data_get_gimp
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|action_data_get_image
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDisplay
modifier|*
name|action_data_get_display
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|action_data_get_widget
parameter_list|(
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
comment|/* __ACTIONS_H__ */
end_comment

end_unit

