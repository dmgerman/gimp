begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * action-search-dialog.c  * Copyright (C) 2012-2013 Srihari Sriraman  *                         Suhas V  *                         Vidyashree K  *                         Zeeshan Ali Ansari  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__ACTION_SEARCH_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__ACTION_SEARCH_DIALOG_H__
define|#
directive|define
name|__ACTION_SEARCH_DIALOG_H__
end_define

begin_function_decl
name|GtkWidget
modifier|*
name|action_search_dialog_create
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __ACTION_SEARCH_DIALOG_H__ */
end_comment

end_unit

