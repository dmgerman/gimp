begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BUILDMENU_H__
end_ifndef

begin_define
DECL|macro|__BUILDMENU_H__
define|#
directive|define
name|__BUILDMENU_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_define
DECL|macro|PULLDOWN
define|#
directive|define
name|PULLDOWN
value|0
end_define

begin_define
DECL|macro|POPUP
define|#
directive|define
name|POPUP
value|1
end_define

begin_define
DECL|macro|OPTION
define|#
directive|define
name|OPTION
value|2
end_define

begin_comment
comment|/* Structures */
end_comment

begin_typedef
DECL|typedef|MenuItem
typedef|typedef
name|struct
name|_MenuItem
name|MenuItem
typedef|;
end_typedef

begin_typedef
DECL|typedef|MenuItemCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|MenuItemCallback
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|_MenuItem
struct|struct
name|_MenuItem
block|{
DECL|member|label
name|gchar
modifier|*
name|label
decl_stmt|;
DECL|member|accelerator_key
name|guint
name|accelerator_key
decl_stmt|;
DECL|member|accelerator_mods
name|guint
name|accelerator_mods
decl_stmt|;
DECL|member|callback
name|MenuItemCallback
name|callback
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|member|subitems
name|MenuItem
modifier|*
name|subitems
decl_stmt|;
DECL|member|widget
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* Function declarations */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|build_menu
parameter_list|(
name|MenuItem
modifier|*
parameter_list|,
name|GtkAccelGroup
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* BUILDMENU_H */
end_comment

end_unit

