begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpcancelable.h  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CANCELABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CANCELABLE_H__
define|#
directive|define
name|__GIMP_CANCELABLE_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_CANCELABLE
define|#
directive|define
name|GIMP_TYPE_CANCELABLE
value|(gimp_cancelable_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_CANCELABLE (obj)
define|#
directive|define
name|GIMP_IS_CANCELABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CANCELABLE))
end_define

begin_define
DECL|macro|GIMP_CANCELABLE (obj)
define|#
directive|define
name|GIMP_CANCELABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CANCELABLE, GimpCancelable))
end_define

begin_define
DECL|macro|GIMP_CANCELABLE_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_CANCELABLE_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_CANCELABLE, GimpCancelableInterface))
end_define

begin_typedef
DECL|typedef|GimpCancelableInterface
typedef|typedef
name|struct
name|_GimpCancelableInterface
name|GimpCancelableInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCancelableInterface
struct|struct
name|_GimpCancelableInterface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
comment|/*  signals  */
DECL|member|cancel
name|void
function_decl|(
modifier|*
name|cancel
function_decl|)
parameter_list|(
name|GimpCancelable
modifier|*
name|cancelable
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_cancelable_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_cancelable_cancel
parameter_list|(
name|GimpCancelable
modifier|*
name|cancelable
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CANCELABLE_H__ */
end_comment

end_unit

