begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpImageProfileView  * Copyright (C) 2006  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_PROFILE_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_PROFILE_VIEW_H__
define|#
directive|define
name|__GIMP_IMAGE_PROFILE_VIEW_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkvbox.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_IMAGE_PROFILE_VIEW
define|#
directive|define
name|GIMP_TYPE_IMAGE_PROFILE_VIEW
value|(gimp_image_profile_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_IMAGE_PROFILE_VIEW (obj)
define|#
directive|define
name|GIMP_IMAGE_PROFILE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_IMAGE_PROFILE_VIEW, GimpImageProfileView))
end_define

begin_define
DECL|macro|GIMP_IMAGE_PROFILE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_PROFILE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_IMAGE_PROFILE_VIEW, GimpImageProfileViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_PROFILE_VIEW (obj)
define|#
directive|define
name|GIMP_IS_IMAGE_PROFILE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_IMAGE_PROFILE_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_PROFILE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGE_PROFILE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGE_PROFILE_VIEW))
end_define

begin_define
DECL|macro|GIMP_IMAGE_PROFILE_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_IMAGE_PROFILE_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_IMAGE_PROFILE_VIEW, GimpImageProfileViewClass))
end_define

begin_typedef
DECL|typedef|GimpImageProfileViewClass
typedef|typedef
name|struct
name|_GimpImageProfileViewClass
name|GimpImageProfileViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImageProfileView
struct|struct
name|_GimpImageProfileView
block|{
DECL|member|parent_instance
name|GtkVBox
name|parent_instance
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|table
name|GtkWidget
modifier|*
name|table
decl_stmt|;
DECL|member|name_label
name|GtkWidget
modifier|*
name|name_label
decl_stmt|;
DECL|member|desc_label
name|GtkWidget
modifier|*
name|desc_label
decl_stmt|;
DECL|member|info_label
name|GtkWidget
modifier|*
name|info_label
decl_stmt|;
DECL|member|message
name|GtkWidget
modifier|*
name|message
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpImageProfileViewClass
struct|struct
name|_GimpImageProfileViewClass
block|{
DECL|member|parent_class
name|GtkVBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_image_profile_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_image_profile_view_new
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
comment|/*  __GIMP_IMAGE_PROFILE_VIEW_H__  */
end_comment

end_unit

