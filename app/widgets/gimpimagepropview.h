begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpImagePropView  * Copyright (C) 2005  Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_PROP_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_PROP_VIEW_H__
define|#
directive|define
name|__GIMP_IMAGE_PROP_VIEW_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtktable.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_IMAGE_PROP_VIEW
define|#
directive|define
name|GIMP_TYPE_IMAGE_PROP_VIEW
value|(gimp_image_prop_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_IMAGE_PROP_VIEW (obj)
define|#
directive|define
name|GIMP_IMAGE_PROP_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_IMAGE_PROP_VIEW, GimpImagePropView))
end_define

begin_define
DECL|macro|GIMP_IMAGE_PROP_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_PROP_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_IMAGE_PROP_VIEW, GimpImagePropViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_PROP_VIEW (obj)
define|#
directive|define
name|GIMP_IS_IMAGE_PROP_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_IMAGE_PROP_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_PROP_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGE_PROP_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGE_PROP_VIEW))
end_define

begin_define
DECL|macro|GIMP_IMAGE_PROP_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_IMAGE_PROP_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_IMAGE_PROP_VIEW, GimpImagePropViewClass))
end_define

begin_typedef
DECL|typedef|GimpImagePropViewClass
typedef|typedef
name|struct
name|_GimpImagePropViewClass
name|GimpImagePropViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImagePropView
struct|struct
name|_GimpImagePropView
block|{
DECL|member|parent_instance
name|GtkTable
name|parent_instance
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|pixel_size_label
name|GtkWidget
modifier|*
name|pixel_size_label
decl_stmt|;
DECL|member|print_size_label
name|GtkWidget
modifier|*
name|print_size_label
decl_stmt|;
DECL|member|resolution_label
name|GtkWidget
modifier|*
name|resolution_label
decl_stmt|;
DECL|member|colorspace_label
name|GtkWidget
modifier|*
name|colorspace_label
decl_stmt|;
DECL|member|memsize_label
name|GtkWidget
modifier|*
name|memsize_label
decl_stmt|;
DECL|member|pixels_label
name|GtkWidget
modifier|*
name|pixels_label
decl_stmt|;
DECL|member|layers_label
name|GtkWidget
modifier|*
name|layers_label
decl_stmt|;
DECL|member|channels_label
name|GtkWidget
modifier|*
name|channels_label
decl_stmt|;
DECL|member|vectors_label
name|GtkWidget
modifier|*
name|vectors_label
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpImagePropViewClass
struct|struct
name|_GimpImagePropViewClass
block|{
DECL|member|parent_class
name|GtkTableClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_image_prop_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_image_prop_view_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_IMAGE_PROP_VIEW_H__  */
end_comment

end_unit

