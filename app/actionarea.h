begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__ACTIONAREA_H__
end_ifndef

begin_define
DECL|macro|__ACTIONAREA_H__
define|#
directive|define
name|__ACTIONAREA_H__
end_define

begin_typedef
DECL|typedef|ActionCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|ActionCallback
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon28c2d8b00108
typedef|typedef
struct|struct
block|{
DECL|member|label
specifier|const
name|char
modifier|*
name|label
decl_stmt|;
DECL|member|callback
name|ActionCallback
name|callback
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|member|widget
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
DECL|typedef|ActionAreaItem
block|}
name|ActionAreaItem
typedef|;
end_typedef

begin_function_decl
name|void
name|build_action_area
parameter_list|(
name|GtkDialog
modifier|*
name|dlg
parameter_list|,
name|ActionAreaItem
modifier|*
name|actions
parameter_list|,
name|int
name|num_actions
parameter_list|,
name|int
name|default_action
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __ACTIONAREA_H__ */
end_comment

end_unit

