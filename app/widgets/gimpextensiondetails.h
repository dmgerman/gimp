begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpextensiondetails.h  * Copyright (C) 2018 Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_EXTENSION_DETAILS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_EXTENSION_DETAILS_H__
define|#
directive|define
name|__GIMP_EXTENSION_DETAILS_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_EXTENSION_DETAILS
define|#
directive|define
name|GIMP_TYPE_EXTENSION_DETAILS
value|(gimp_extension_details_get_type ())
end_define

begin_define
DECL|macro|GIMP_EXTENSION_DETAILS (obj)
define|#
directive|define
name|GIMP_EXTENSION_DETAILS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_EXTENSION_DETAILS, GimpExtensionDetails))
end_define

begin_define
DECL|macro|GIMP_EXTENSION_DETAILS_CLASS (klass)
define|#
directive|define
name|GIMP_EXTENSION_DETAILS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_EXTENSION_DETAILS, GimpExtensionDetailsClass))
end_define

begin_define
DECL|macro|GIMP_IS_EXTENSION_DETAILS (obj)
define|#
directive|define
name|GIMP_IS_EXTENSION_DETAILS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_EXTENSION_DETAILS))
end_define

begin_define
DECL|macro|GIMP_IS_EXTENSION_DETAILS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_EXTENSION_DETAILS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_EXTENSION_DETAILS))
end_define

begin_define
DECL|macro|GIMP_EXTENSION_DETAILS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_EXTENSION_DETAILS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_EXTENSION_DETAILS, GimpExtensionDetailsClass))
end_define

begin_typedef
DECL|typedef|GimpExtensionDetailsClass
typedef|typedef
name|struct
name|_GimpExtensionDetailsClass
name|GimpExtensionDetailsClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpExtensionDetailsPrivate
typedef|typedef
name|struct
name|_GimpExtensionDetailsPrivate
name|GimpExtensionDetailsPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpExtensionDetails
struct|struct
name|_GimpExtensionDetails
block|{
DECL|member|parent_instance
name|GtkFrame
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpExtensionDetailsPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpExtensionDetailsClass
struct|struct
name|_GimpExtensionDetailsClass
block|{
DECL|member|parent_class
name|GtkFrameClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_extension_details_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_extension_details_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_extension_details_set
parameter_list|(
name|GimpExtensionDetails
modifier|*
name|details
parameter_list|,
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_EXTENSION_DETAILS_H__ */
end_comment

end_unit

