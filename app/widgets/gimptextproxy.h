begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextProxy  * Copyright (C) 2009-2010  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_PROXY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_PROXY_H__
define|#
directive|define
name|__GIMP_TEXT_PROXY_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_TEXT_PROXY
define|#
directive|define
name|GIMP_TYPE_TEXT_PROXY
value|(gimp_text_proxy_get_type ())
end_define

begin_define
DECL|macro|GIMP_TEXT_PROXY (obj)
define|#
directive|define
name|GIMP_TEXT_PROXY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TEXT_PROXY, GimpTextProxy))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_PROXY (obj)
define|#
directive|define
name|GIMP_IS_TEXT_PROXY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TEXT_PROXY))
end_define

begin_define
DECL|macro|GIMP_TEXT_PROXY_CLASS (klass)
define|#
directive|define
name|GIMP_TEXT_PROXY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TEXT_PROXY, GimpTextProxyClass))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_PROXY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TEXT_PROXY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TEXT_PROXY))
end_define

begin_typedef
DECL|typedef|GimpTextProxy
typedef|typedef
name|struct
name|_GimpTextProxy
name|GimpTextProxy
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTextProxyClass
typedef|typedef
name|struct
name|_GimpTextProxyClass
name|GimpTextProxyClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTextProxy
struct|struct
name|_GimpTextProxy
block|{
DECL|member|parent_instance
name|GtkTextView
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTextProxyClass
struct|struct
name|_GimpTextProxyClass
block|{
DECL|member|parent_class
name|GtkTextViewClass
name|parent_class
decl_stmt|;
DECL|member|change_baseline
name|void
function_decl|(
modifier|*
name|change_baseline
function_decl|)
parameter_list|(
name|GimpTextProxy
modifier|*
name|proxy
parameter_list|,
name|gdouble
name|amount
parameter_list|)
function_decl|;
DECL|member|change_kerning
name|void
function_decl|(
modifier|*
name|change_kerning
function_decl|)
parameter_list|(
name|GimpTextProxy
modifier|*
name|proxy
parameter_list|,
name|gdouble
name|amount
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_text_proxy_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_text_proxy_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TEXT_PROXY_H__ */
end_comment

end_unit

