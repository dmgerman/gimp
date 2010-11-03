begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpImageParasiteView  * Copyright (C) 2006  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_PARASITE_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_PARASITE_VIEW_H__
define|#
directive|define
name|__GIMP_IMAGE_PARASITE_VIEW_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_IMAGE_PARASITE_VIEW
define|#
directive|define
name|GIMP_TYPE_IMAGE_PARASITE_VIEW
value|(gimp_image_parasite_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_IMAGE_PARASITE_VIEW (obj)
define|#
directive|define
name|GIMP_IMAGE_PARASITE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_IMAGE_PARASITE_VIEW, GimpImageParasiteView))
end_define

begin_define
DECL|macro|GIMP_IMAGE_PARASITE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_PARASITE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_IMAGE_PARASITE_VIEW, GimpImageParasiteViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_PARASITE_VIEW (obj)
define|#
directive|define
name|GIMP_IS_IMAGE_PARASITE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_IMAGE_PARASITE_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_PARASITE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGE_PARASITE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGE_PARASITE_VIEW))
end_define

begin_define
DECL|macro|GIMP_IMAGE_PARASITE_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_IMAGE_PARASITE_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_IMAGE_PARASITE_VIEW, GimpImageParasiteViewClass))
end_define

begin_typedef
DECL|typedef|GimpImageParasiteViewClass
typedef|typedef
name|struct
name|_GimpImageParasiteViewClass
name|GimpImageParasiteViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImageParasiteView
struct|struct
name|_GimpImageParasiteView
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|parasite
name|gchar
modifier|*
name|parasite
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpImageParasiteViewClass
struct|struct
name|_GimpImageParasiteViewClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|update
name|void
function_decl|(
modifier|*
name|update
function_decl|)
parameter_list|(
name|GimpImageParasiteView
modifier|*
name|view
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_image_parasite_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_image_parasite_view_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_image_parasite_view_get_image
parameter_list|(
name|GimpImageParasiteView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpParasite
modifier|*
name|gimp_image_parasite_view_get_parasite
parameter_list|(
name|GimpImageParasiteView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_IMAGE_PARASITE_VIEW_H__  */
end_comment

end_unit

