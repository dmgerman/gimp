begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpaction-history.h  * Copyright (C) 2013  Jehan<jehan at girinstud.io>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ACTION_HISTORY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ACTION_HISTORY_H__
define|#
directive|define
name|__GIMP_ACTION_HISTORY_H__
end_define

begin_typedef
DECL|typedef|GimpActionMatchFunc
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpActionMatchFunc
function_decl|)
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|keyword
parameter_list|,
name|gint
modifier|*
name|section
parameter_list|,
name|gboolean
name|match_fuzzy
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_action_history_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_history_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_history_clear
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_action_history_search
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpActionMatchFunc
name|match_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|keyword
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_action_history_excluded_action
parameter_list|(
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_history_activate_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ACTION_HISTORY_H__ */
end_comment

end_unit

