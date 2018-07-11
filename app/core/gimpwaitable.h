begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpwaitable.h  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_WAITABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_WAITABLE_H__
define|#
directive|define
name|__GIMP_WAITABLE_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_WAITABLE
define|#
directive|define
name|GIMP_TYPE_WAITABLE
value|(gimp_waitable_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_WAITABLE (obj)
define|#
directive|define
name|GIMP_IS_WAITABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_WAITABLE))
end_define

begin_define
DECL|macro|GIMP_WAITABLE (obj)
define|#
directive|define
name|GIMP_WAITABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_WAITABLE, GimpWaitable))
end_define

begin_define
DECL|macro|GIMP_WAITABLE_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_WAITABLE_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_WAITABLE, GimpWaitableInterface))
end_define

begin_typedef
DECL|typedef|GimpWaitableInterface
typedef|typedef
name|struct
name|_GimpWaitableInterface
name|GimpWaitableInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpWaitableInterface
struct|struct
name|_GimpWaitableInterface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|wait
name|void
function_decl|(
modifier|*
name|wait
function_decl|)
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|)
function_decl|;
DECL|member|try_wait
name|gboolean
function_decl|(
modifier|*
name|try_wait
function_decl|)
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|)
function_decl|;
DECL|member|wait_until
name|gboolean
function_decl|(
modifier|*
name|wait_until
function_decl|)
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|,
name|gint64
name|end_time
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_waitable_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_waitable_wait
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_waitable_try_wait
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_waitable_wait_until
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|,
name|gint64
name|end_time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_waitable_wait_for
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|,
name|gint64
name|wait_duration
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_WAITABLE_H__ */
end_comment

end_unit

