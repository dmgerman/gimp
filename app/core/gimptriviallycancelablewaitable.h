begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptriviallycancelablewaitable.h  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TRIVIALLY_CANCELABLE_WAITABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TRIVIALLY_CANCELABLE_WAITABLE_H__
define|#
directive|define
name|__GIMP_TRIVIALLY_CANCELABLE_WAITABLE_H__
end_define

begin_include
include|#
directive|include
file|"gimpuncancelablewaitable.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TRIVIALLY_CANCELABLE_WAITABLE
define|#
directive|define
name|GIMP_TYPE_TRIVIALLY_CANCELABLE_WAITABLE
value|(gimp_trivially_cancelable_waitable_get_type ())
end_define

begin_define
DECL|macro|GIMP_TRIVIALLY_CANCELABLE_WAITABLE (obj)
define|#
directive|define
name|GIMP_TRIVIALLY_CANCELABLE_WAITABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TRIVIALLY_CANCELABLE_WAITABLE, GimpTriviallyCancelableWaitable))
end_define

begin_define
DECL|macro|GIMP_TRIVIALLY_CANCELABLE_WAITABLE_CLASS (klass)
define|#
directive|define
name|GIMP_TRIVIALLY_CANCELABLE_WAITABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TRIVIALLY_CANCELABLE_WAITABLE, GimpTriviallyCancelableWaitableClass))
end_define

begin_define
DECL|macro|GIMP_IS_TRIVIALLY_CANCELABLE_WAITABLE (obj)
define|#
directive|define
name|GIMP_IS_TRIVIALLY_CANCELABLE_WAITABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TRIVIALLY_CANCELABLE_WAITABLE))
end_define

begin_define
DECL|macro|GIMP_IS_TRIVIALLY_CANCELABLE_WAITABLE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TRIVIALLY_CANCELABLE_WAITABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TRIVIALLY_CANCELABLE_WAITABLE))
end_define

begin_define
DECL|macro|GIMP_TRIVIALLY_CANCELABLE_WAITABLE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TRIVIALLY_CANCELABLE_WAITABLE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TRIVIALLY_CANCELABLE_WAITABLE, GimpTriviallyCancelableWaitableClass))
end_define

begin_typedef
DECL|typedef|GimpTriviallyCancelableWaitablePrivate
typedef|typedef
name|struct
name|_GimpTriviallyCancelableWaitablePrivate
name|GimpTriviallyCancelableWaitablePrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTriviallyCancelableWaitableClass
typedef|typedef
name|struct
name|_GimpTriviallyCancelableWaitableClass
name|GimpTriviallyCancelableWaitableClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTriviallyCancelableWaitable
struct|struct
name|_GimpTriviallyCancelableWaitable
block|{
DECL|member|parent_instance
name|GimpUncancelableWaitable
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpTriviallyCancelableWaitablePrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTriviallyCancelableWaitableClass
struct|struct
name|_GimpTriviallyCancelableWaitableClass
block|{
DECL|member|parent_class
name|GimpUncancelableWaitableClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_trivially_cancelable_waitable_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpWaitable
modifier|*
name|gimp_trivially_cancelable_waitable_new
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
comment|/* __GIMP_TRIVIALLY_CANCELABLE_WAITABLE_H__ */
end_comment

end_unit

