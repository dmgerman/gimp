begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_LIST_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_LIST_VIEW_H__
define|#
directive|define
name|__GIMP_DRAWABLE_LIST_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpcontainerlistview.h"
end_include

begin_typedef
DECL|typedef|GimpGetContainerFunc
typedef|typedef
name|GimpContainer
modifier|*
function_decl|(
modifier|*
name|GimpGetContainerFunc
function_decl|)
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpGetDrawableFunc
typedef|typedef
name|GimpDrawable
modifier|*
function_decl|(
modifier|*
name|GimpGetDrawableFunc
function_decl|)
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpSetDrawableFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpSetDrawableFunc
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_DRAWABLE_LIST_VIEW
define|#
directive|define
name|GIMP_TYPE_DRAWABLE_LIST_VIEW
value|(gimp_drawable_list_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_DRAWABLE_LIST_VIEW (obj)
define|#
directive|define
name|GIMP_DRAWABLE_LIST_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_DRAWABLE_LIST_VIEW, GimpDrawableListView))
end_define

begin_define
DECL|macro|GIMP_DRAWABLE_LIST_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_DRAWABLE_LIST_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DRAWABLE_LIST_VIEW, GimpDrawableListViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_DRAWABLE_LIST_VIEW (obj)
define|#
directive|define
name|GIMP_IS_DRAWABLE_LIST_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_DRAWABLE_LIST_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_DRAWABLE_LIST_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DRAWABLE_LIST_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DRAWABLE_LIST_VIEW))
end_define

begin_typedef
DECL|typedef|GimpDrawableListViewClass
typedef|typedef
name|struct
name|_GimpDrawableListViewClass
name|GimpDrawableListViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDrawableListView
struct|struct
name|_GimpDrawableListView
block|{
DECL|member|parent_instance
name|GimpContainerListView
name|parent_instance
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
DECL|member|drawable_type
name|GtkType
name|drawable_type
decl_stmt|;
DECL|member|signal_name
name|gchar
modifier|*
name|signal_name
decl_stmt|;
DECL|member|get_container_func
name|GimpGetContainerFunc
name|get_container_func
decl_stmt|;
DECL|member|get_drawable_func
name|GimpGetDrawableFunc
name|get_drawable_func
decl_stmt|;
DECL|member|set_drawable_func
name|GimpSetDrawableFunc
name|set_drawable_func
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
DECL|member|raise_button
name|GtkWidget
modifier|*
name|raise_button
decl_stmt|;
DECL|member|lower_button
name|GtkWidget
modifier|*
name|lower_button
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
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDrawableListViewClass
struct|struct
name|_GimpDrawableListViewClass
block|{
DECL|member|parent_class
name|GimpContainerListViewClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_drawable_list_view_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_drawable_list_view_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GtkType
name|drawable_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|signal_name
parameter_list|,
name|GimpGetContainerFunc
name|get_container_func
parameter_list|,
name|GimpGetDrawableFunc
name|get_drawable_func
parameter_list|,
name|GimpSetDrawableFunc
name|set_drawable_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_list_view_set_image
parameter_list|(
name|GimpDrawableListView
modifier|*
name|view
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DRAWABLE_LIST_VIEW_H__  */
end_comment

end_unit

