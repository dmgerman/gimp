begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpcancelable.h  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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

begin_macro
name|G_DECLARE_INTERFACE
argument_list|(
argument|GimpCancelable
argument_list|,
argument|gimp_cancelable
argument_list|,
argument|GIMP
argument_list|,
argument|CANCELABLE
argument_list|,
argument|GObject
argument_list|)
end_macro

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

