begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpinputdevicestore.h  * Copyright (C) 2007  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_INPUT_DEVICE_STORE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_INPUT_DEVICE_STORE_H__
define|#
directive|define
name|__GIMP_INPUT_DEVICE_STORE_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_INPUT_DEVICE_STORE
define|#
directive|define
name|GIMP_TYPE_INPUT_DEVICE_STORE
value|(gimp_input_device_store_get_type ())
end_define

begin_define
DECL|macro|GIMP_INPUT_DEVICE_STORE (obj)
define|#
directive|define
name|GIMP_INPUT_DEVICE_STORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_INPUT_DEVICE_STORE, GimpInputDeviceStore))
end_define

begin_define
DECL|macro|GIMP_IS_INPUT_DEVICE_STORE (obj)
define|#
directive|define
name|GIMP_IS_INPUT_DEVICE_STORE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_INPUT_DEVICE_STORE))
end_define

begin_typedef
DECL|typedef|GimpInputDeviceStore
typedef|typedef
name|struct
name|_GimpInputDeviceStore
name|GimpInputDeviceStore
typedef|;
end_typedef

begin_decl_stmt
name|GType
name|gimp_input_device_store_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkListStore
modifier|*
name|gimp_input_device_store_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_input_device_store_get_device_file
parameter_list|(
name|GimpInputDeviceStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|udi
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_INPUT_DEVICE_STORE_H__ */
end_comment

end_unit

