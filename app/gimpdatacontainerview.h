begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DATA_CONTAINER_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DATA_CONTAINER_VIEW_H__
define|#
directive|define
name|__GIMP_DATA_CONTAINER_VIEW_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkvbox.h>
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c4736850103
block|{
DECL|enumerator|GIMP_VIEW_TYPE_GRID
name|GIMP_VIEW_TYPE_GRID
block|,
DECL|enumerator|GIMP_VIEW_TYPE_LIST
name|GIMP_VIEW_TYPE_LIST
DECL|typedef|GimpViewType
block|}
name|GimpViewType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_DATA_CONTAINER_VIEW
define|#
directive|define
name|GIMP_TYPE_DATA_CONTAINER_VIEW
value|(gimp_data_container_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_DATA_CONTAINER_VIEW (obj)
define|#
directive|define
name|GIMP_DATA_CONTAINER_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_DATA_CONTAINER_VIEW, GimpDataContainerView))
end_define

begin_define
DECL|macro|GIMP_DATA_CONTAINER_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_DATA_CONTAINER_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DATA_CONTAINER_VIEW, GimpDataContainerViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_DATA_CONTAINER_VIEW (obj)
define|#
directive|define
name|GIMP_IS_DATA_CONTAINER_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_DATA_CONTAINER_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_DATA_CONTAINER_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DATA_CONTAINER_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DATA_CONTAINER_VIEW))
end_define

begin_typedef
DECL|typedef|GimpDataContainerView
typedef|typedef
name|struct
name|_GimpDataContainerView
name|GimpDataContainerView
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDataContainerViewClass
typedef|typedef
name|struct
name|_GimpDataContainerViewClass
name|GimpDataContainerViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDataContainerView
struct|struct
name|_GimpDataContainerView
block|{
DECL|member|parent_instance
name|GtkVBox
name|parent_instance
decl_stmt|;
DECL|member|view
name|GimpContainerView
modifier|*
name|view
decl_stmt|;
DECL|member|button_box
name|GtkWidget
modifier|*
name|button_box
decl_stmt|;
DECL|member|new_button
name|GtkWidget
modifier|*
name|new_button
decl_stmt|;
DECL|member|duplicate_button
name|GtkWidget
modifier|*
name|duplicate_button
decl_stmt|;
DECL|member|edit_button
name|GtkWidget
modifier|*
name|edit_button
decl_stmt|;
DECL|member|delete_button
name|GtkWidget
modifier|*
name|delete_button
decl_stmt|;
DECL|member|refresh_button
name|GtkWidget
modifier|*
name|refresh_button
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDataContainerViewClass
struct|struct
name|_GimpDataContainerViewClass
block|{
DECL|member|parent_class
name|GtkVBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_data_container_view_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_data_container_view_new
parameter_list|(
name|GimpViewType
name|view_type
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|preview_size
parameter_list|,
name|gint
name|min_items_x
parameter_list|,
name|gint
name|min_items_y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DATA_CONTAINER_VIEW_H__  */
end_comment

end_unit

