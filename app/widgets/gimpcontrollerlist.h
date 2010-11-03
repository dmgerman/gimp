begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontrollerlist.h  * Copyright (C) 2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTROLLER_LIST_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTROLLER_LIST_H__
define|#
directive|define
name|__GIMP_CONTROLLER_LIST_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_CONTROLLER_LIST
define|#
directive|define
name|GIMP_TYPE_CONTROLLER_LIST
value|(gimp_controller_list_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTROLLER_LIST (obj)
define|#
directive|define
name|GIMP_CONTROLLER_LIST
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTROLLER_LIST, GimpControllerList))
end_define

begin_define
DECL|macro|GIMP_CONTROLLER_LIST_CLASS (klass)
define|#
directive|define
name|GIMP_CONTROLLER_LIST_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTROLLER_LIST, GimpControllerListClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTROLLER_LIST (obj)
define|#
directive|define
name|GIMP_IS_CONTROLLER_LIST
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTROLLER_LIST))
end_define

begin_define
DECL|macro|GIMP_IS_CONTROLLER_LIST_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTROLLER_LIST_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTROLLER_LIST))
end_define

begin_define
DECL|macro|GIMP_CONTROLLER_LIST_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTROLLER_LIST_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTROLLER_LIST, GimpControllerListClass))
end_define

begin_typedef
DECL|typedef|GimpControllerListClass
typedef|typedef
name|struct
name|_GimpControllerListClass
name|GimpControllerListClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpControllerList
struct|struct
name|_GimpControllerList
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|hbox
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
DECL|member|src
name|GtkListStore
modifier|*
name|src
decl_stmt|;
DECL|member|src_sel
name|GtkTreeSelection
modifier|*
name|src_sel
decl_stmt|;
DECL|member|src_gtype
name|GType
name|src_gtype
decl_stmt|;
DECL|member|dest
name|GtkWidget
modifier|*
name|dest
decl_stmt|;
DECL|member|dest_info
name|GimpControllerInfo
modifier|*
name|dest_info
decl_stmt|;
DECL|member|add_button
name|GtkWidget
modifier|*
name|add_button
decl_stmt|;
DECL|member|remove_button
name|GtkWidget
modifier|*
name|remove_button
decl_stmt|;
DECL|member|edit_button
name|GtkWidget
modifier|*
name|edit_button
decl_stmt|;
DECL|member|up_button
name|GtkWidget
modifier|*
name|up_button
decl_stmt|;
DECL|member|down_button
name|GtkWidget
modifier|*
name|down_button
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpControllerListClass
struct|struct
name|_GimpControllerListClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_controller_list_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_controller_list_new
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
comment|/*  __GIMP_CONTROLLER_LIST_H__  */
end_comment

end_unit

