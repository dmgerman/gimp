begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DIALOGS_ACTIONS_H__
end_ifndef

begin_define
DECL|macro|__DIALOGS_ACTIONS_H__
define|#
directive|define
name|__DIALOGS_ACTIONS_H__
end_define

begin_comment
comment|/*  this check is needed for the extern declaration below to be correct  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ACTION_GROUP_H__
end_ifndef

begin_error
error|#
directive|error
literal|"widgets/gimpactiongroup.h must be included prior to dialog-actions.h"
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
specifier|extern
name|GimpStringActionEntry
name|dialogs_dockable_actions
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|n_dialogs_dockable_actions
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|dialogs_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|dialogs_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
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
comment|/* __DIALOGS_ACTIONS_H__ */
end_comment

end_unit

