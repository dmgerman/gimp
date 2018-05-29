begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpuncancelablewaitable.h  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_UNCANCELABLE_WAITABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UNCANCELABLE_WAITABLE_H__
define|#
directive|define
name|__GIMP_UNCANCELABLE_WAITABLE_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_UNCANCELABLE_WAITABLE
define|#
directive|define
name|GIMP_TYPE_UNCANCELABLE_WAITABLE
value|(gimp_uncancelable_waitable_get_type ())
end_define

begin_define
DECL|macro|GIMP_UNCANCELABLE_WAITABLE (obj)
define|#
directive|define
name|GIMP_UNCANCELABLE_WAITABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_UNCANCELABLE_WAITABLE, GimpUncancelableWaitable))
end_define

begin_define
DECL|macro|GIMP_UNCANCELABLE_WAITABLE_CLASS (klass)
define|#
directive|define
name|GIMP_UNCANCELABLE_WAITABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_UNCANCELABLE_WAITABLE, GimpUncancelableWaitableClass))
end_define

begin_define
DECL|macro|GIMP_IS_UNCANCELABLE_WAITABLE (obj)
define|#
directive|define
name|GIMP_IS_UNCANCELABLE_WAITABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_UNCANCELABLE_WAITABLE))
end_define

begin_define
DECL|macro|GIMP_IS_UNCANCELABLE_WAITABLE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_UNCANCELABLE_WAITABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_UNCANCELABLE_WAITABLE))
end_define

begin_define
DECL|macro|GIMP_UNCANCELABLE_WAITABLE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_UNCANCELABLE_WAITABLE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_UNCANCELABLE_WAITABLE, GimpUncancelableWaitableClass))
end_define

begin_typedef
DECL|typedef|GimpUncancelableWaitablePrivate
typedef|typedef
name|struct
name|_GimpUncancelableWaitablePrivate
name|GimpUncancelableWaitablePrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpUncancelableWaitableClass
typedef|typedef
name|struct
name|_GimpUncancelableWaitableClass
name|GimpUncancelableWaitableClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpUncancelableWaitable
struct|struct
name|_GimpUncancelableWaitable
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|waitable
name|GimpWaitable
modifier|*
name|waitable
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpUncancelableWaitableClass
struct|struct
name|_GimpUncancelableWaitableClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_uncancelable_waitable_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpWaitable
modifier|*
name|gimp_uncancelable_waitable_new
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_UNCANCELABLE_WAITABLE_H__ */
end_comment

end_unit

