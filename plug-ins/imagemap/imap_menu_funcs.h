begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2005 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_MENU_FUNCS_H
end_ifndef

begin_define
DECL|macro|_IMAP_MENU_FUNCS_H
define|#
directive|define
name|_IMAP_MENU_FUNCS_H
end_define

begin_typedef
DECL|typedef|MenuCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|MenuCallback
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|init_accel_group
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|insert_item_with_label
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|gint
name|position
parameter_list|,
name|gchar
modifier|*
name|label
parameter_list|,
name|MenuCallback
name|activate
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menu_command
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|add_accelerator
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|accelerator_key
parameter_list|,
name|guint8
name|accelerator_mods
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_MENU_FUNCS_H */
end_comment

end_unit

