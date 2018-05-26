begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpasync.h  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ASYNC_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ASYNC_H__
define|#
directive|define
name|__GIMP_ASYNC_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_ASYNC
define|#
directive|define
name|GIMP_TYPE_ASYNC
value|(gimp_async_get_type ())
end_define

begin_define
DECL|macro|GIMP_ASYNC (obj)
define|#
directive|define
name|GIMP_ASYNC
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ASYNC, GimpAsync))
end_define

begin_define
DECL|macro|GIMP_ASYNC_CLASS (klass)
define|#
directive|define
name|GIMP_ASYNC_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ASYNC, GimpAsyncClass))
end_define

begin_define
DECL|macro|GIMP_IS_ASYNC (obj)
define|#
directive|define
name|GIMP_IS_ASYNC
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ASYNC))
end_define

begin_define
DECL|macro|GIMP_IS_ASYNC_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ASYNC_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ASYNC))
end_define

begin_define
DECL|macro|GIMP_ASYNC_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ASYNC_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ASYNC, GimpAsyncClass))
end_define

begin_typedef
DECL|typedef|GimpAsyncCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpAsyncCallback
function_decl|)
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpAsyncPrivate
typedef|typedef
name|struct
name|_GimpAsyncPrivate
name|GimpAsyncPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpAsyncClass
typedef|typedef
name|struct
name|_GimpAsyncClass
name|GimpAsyncClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpAsync
struct|struct
name|_GimpAsync
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpAsyncPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpAsyncClass
struct|struct
name|_GimpAsyncClass
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
name|gimp_async_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpAsync
modifier|*
name|gimp_async_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_async_is_stopped
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_async_wait
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_async_wait_until
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|,
name|gint64
name|end_time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_async_add_callback
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|,
name|GimpAsyncCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_async_remove_callback
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|,
name|GimpAsyncCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_async_finish
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|,
name|gpointer
name|result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_async_finish_full
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|,
name|gpointer
name|result
parameter_list|,
name|GDestroyNotify
name|result_destroy_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_async_is_finished
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|gimp_async_get_result
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_async_abort
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_async_cancel
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_async_is_canceled
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ASYNC_H__ */
end_comment

end_unit

