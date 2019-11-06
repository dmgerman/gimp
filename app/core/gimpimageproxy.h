begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimageproxy.h  * Copyright (C) 2019 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_PROXY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_PROXY_H__
define|#
directive|define
name|__GIMP_IMAGE_PROXY_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_IMAGE_PROXY
define|#
directive|define
name|GIMP_TYPE_IMAGE_PROXY
value|(gimp_image_proxy_get_type ())
end_define

begin_define
DECL|macro|GIMP_IMAGE_PROXY (obj)
define|#
directive|define
name|GIMP_IMAGE_PROXY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_IMAGE_PROXY, GimpImageProxy))
end_define

begin_define
DECL|macro|GIMP_IMAGE_PROXY_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_PROXY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_IMAGE_PROXY, GimpImageProxyClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_PROXY (obj)
define|#
directive|define
name|GIMP_IS_IMAGE_PROXY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_IMAGE_PROXY))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_PROXY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGE_PROXY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGE_PROXY))
end_define

begin_define
DECL|macro|GIMP_IMAGE_PROXY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_IMAGE_PROXY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_IMAGE_PROXY, GimpImageProxyClass))
end_define

begin_typedef
DECL|typedef|GimpImageProxyPrivate
typedef|typedef
name|struct
name|_GimpImageProxyPrivate
name|GimpImageProxyPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpImageProxyClass
typedef|typedef
name|struct
name|_GimpImageProxyClass
name|GimpImageProxyClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImageProxy
struct|struct
name|_GimpImageProxy
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpImageProxyPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpImageProxyClass
struct|struct
name|_GimpImageProxyClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_image_proxy_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpImageProxy
modifier|*
name|gimp_image_proxy_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_image_proxy_get_image
parameter_list|(
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_proxy_set_show_all
parameter_list|(
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|,
name|gboolean
name|show_all
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_proxy_get_show_all
parameter_list|(
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglRectangle
name|gimp_image_proxy_get_bounding_box
parameter_list|(
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_PROXY_H__ */
end_comment

end_unit
