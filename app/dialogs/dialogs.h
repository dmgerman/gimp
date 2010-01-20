begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DIALOGS_H__
end_ifndef

begin_define
DECL|macro|__DIALOGS_H__
define|#
directive|define
name|__DIALOGS_H__
end_define

begin_decl_stmt
specifier|extern
name|GimpDialogFactory
modifier|*
name|global_dialog_factory
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpDialogFactory
modifier|*
name|global_dock_factory
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpDialogFactory
modifier|*
name|global_display_factory
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpContainer
modifier|*
name|global_recent_docks
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|dialogs_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|dialogs_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|dialogs_load_recent_docks
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|dialogs_save_recent_docks
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|dialogs_get_toolbox
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DIALOGS_H__ */
end_comment

end_unit

