begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpdocked.h  * Copyright (C) 2003  Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DOCKED_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DOCKED_H__
define|#
directive|define
name|__GIMP_DOCKED_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_DOCKED
define|#
directive|define
name|GIMP_TYPE_DOCKED
value|(gimp_docked_interface_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_DOCKED (obj)
define|#
directive|define
name|GIMP_IS_DOCKED
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DOCKED))
end_define

begin_define
DECL|macro|GIMP_DOCKED (obj)
define|#
directive|define
name|GIMP_DOCKED
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DOCKED, GimpDocked))
end_define

begin_define
DECL|macro|GIMP_DOCKED_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_DOCKED_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_DOCKED, GimpDockedIface))
end_define

begin_struct
DECL|struct|_GimpDockedIface
struct|struct
name|_GimpDockedIface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
DECL|member|set_aux_info
name|void
function_decl|(
modifier|*
name|set_aux_info
function_decl|)
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
function_decl|;
DECL|member|get_aux_info
name|GList
modifier|*
function_decl|(
modifier|*
name|get_aux_info
function_decl|)
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
function_decl|;
DECL|member|get_preview
name|GtkWidget
modifier|*
function_decl|(
modifier|*
name|get_preview
function_decl|)
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
function_decl|;
DECL|member|set_context
name|void
function_decl|(
modifier|*
name|set_context
function_decl|)
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpContext
modifier|*
name|prev_context
parameter_list|)
function_decl|;
DECL|member|get_menu
name|GimpItemFactory
modifier|*
function_decl|(
modifier|*
name|get_menu
function_decl|)
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|gpointer
modifier|*
name|item_factory_data
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_docked_interface_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_docked_set_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_docked_get_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_docked_get_preview
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_docked_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpContext
modifier|*
name|prev_context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItemFactory
modifier|*
name|gimp_docked_get_menu
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|gpointer
modifier|*
name|item_factory_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DOCKED_H__ */
end_comment

end_unit

