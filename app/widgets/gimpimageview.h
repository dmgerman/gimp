begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimageview.h  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_VIEW_H__
define|#
directive|define
name|__GIMP_IMAGE_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpcontainereditor.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_IMAGE_VIEW
define|#
directive|define
name|GIMP_TYPE_IMAGE_VIEW
value|(gimp_image_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_IMAGE_VIEW (obj)
define|#
directive|define
name|GIMP_IMAGE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_IMAGE_VIEW, GimpImageView))
end_define

begin_define
DECL|macro|GIMP_IMAGE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_IMAGE_VIEW, GimpImageViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_VIEW (obj)
define|#
directive|define
name|GIMP_IS_IMAGE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_IMAGE_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGE_VIEW))
end_define

begin_define
DECL|macro|GIMP_IMAGE_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_IMAGE_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_IMAGE_VIEW, GimpImageViewClass))
end_define

begin_typedef
DECL|typedef|GimpImageViewClass
typedef|typedef
name|struct
name|_GimpImageViewClass
name|GimpImageViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImageView
struct|struct
name|_GimpImageView
block|{
DECL|member|parent_instance
name|GimpContainerEditor
name|parent_instance
decl_stmt|;
DECL|member|raise_button
name|GtkWidget
modifier|*
name|raise_button
decl_stmt|;
DECL|member|new_button
name|GtkWidget
modifier|*
name|new_button
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
DECL|struct|_GimpImageViewClass
struct|struct
name|_GimpImageViewClass
block|{
DECL|member|parent_class
name|GimpContainerEditorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_image_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_image_view_new
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
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_IMAGE_VIEW_H__  */
end_comment

end_unit

