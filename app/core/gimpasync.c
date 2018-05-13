begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpasync.c  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpasync.h"
end_include

begin_comment
comment|/* GimpAsync represents an asynchronous task.  Both the public and the  * protected interfaces are intentionally minimal at this point, to keep things  * simple.  They may be extended in the future as needed.  *  * Upon creation, a GimpAsync object is in the "running" state.  Once the task  * is complete (and before the object's destruction), it should be transitioned  * to the "stopped" state, using either 'gimp_async_finish()' or  * 'gimp_async_abort()'.  *  * Note that certain GimpAsync functions may be only be called during a certain  * state, or on a certain thread, as detailed for each function.  When  * referring to threads, the "main thread" is the thread running the main loop,  * and the "async thread" is the thread calling 'gimp_async_finish()' or  * 'gimp_async_abort()' (which may be the main thread).  The main thread is  * said to be "synced" with the async thread if both are the same thread, or  * after the execution of any of the callbacks added through  * 'gimp_async_add_callback()' had started, or after calling  * 'gimp_async_wait()' on the main thread.  */
end_comment

begin_typedef
DECL|typedef|GimpAsyncCallbackInfo
typedef|typedef
name|struct
name|_GimpAsyncCallbackInfo
name|GimpAsyncCallbackInfo
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpAsyncCallbackInfo
struct|struct
name|_GimpAsyncCallbackInfo
block|{
DECL|member|callback
name|GimpAsyncCallback
name|callback
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpAsyncPrivate
struct|struct
name|_GimpAsyncPrivate
block|{
DECL|member|mutex
name|GMutex
name|mutex
decl_stmt|;
DECL|member|cond
name|GCond
name|cond
decl_stmt|;
DECL|member|callbacks
name|GQueue
name|callbacks
decl_stmt|;
DECL|member|result
name|gpointer
name|result
decl_stmt|;
DECL|member|result_destroy_func
name|GDestroyNotify
name|result_destroy_func
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
DECL|member|stopped
name|gboolean
name|stopped
decl_stmt|;
DECL|member|finished
name|gboolean
name|finished
decl_stmt|;
DECL|member|canceled
name|gboolean
name|canceled
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_async_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_async_idle
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_async_stop
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpAsync,gimp_async,G_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpAsync
argument_list|,
argument|gimp_async
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_async_parent_class
end_define

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
name|gimp_async_class_init
parameter_list|(
name|GimpAsyncClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_async_finalize
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpAsyncPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_async_init (GimpAsync * async)
name|gimp_async_init
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
block|{
name|async
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|async
argument_list|,
name|GIMP_TYPE_ASYNC
argument_list|,
name|GimpAsyncPrivate
argument_list|)
expr_stmt|;
name|g_mutex_init
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|mutex
argument_list|)
expr_stmt|;
name|g_cond_init
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|cond
argument_list|)
expr_stmt|;
name|g_queue_init
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|callbacks
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_async_finalize (GObject * object)
name|gimp_async_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpAsync
modifier|*
name|async
init|=
name|GIMP_ASYNC
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_warn_if_fail
argument_list|(
name|async
operator|->
name|priv
operator|->
name|stopped
argument_list|)
expr_stmt|;
name|g_warn_if_fail
argument_list|(
name|async
operator|->
name|priv
operator|->
name|idle_id
operator|==
literal|0
argument_list|)
expr_stmt|;
name|g_warn_if_fail
argument_list|(
name|g_queue_is_empty
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|callbacks
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|async
operator|->
name|priv
operator|->
name|finished
operator|&&
name|async
operator|->
name|priv
operator|->
name|result
operator|&&
name|async
operator|->
name|priv
operator|->
name|result_destroy_func
condition|)
block|{
name|async
operator|->
name|priv
operator|->
name|result_destroy_func
argument_list|(
name|async
operator|->
name|priv
operator|->
name|result
argument_list|)
expr_stmt|;
name|async
operator|->
name|priv
operator|->
name|result
operator|=
name|NULL
expr_stmt|;
block|}
name|g_cond_clear
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|cond
argument_list|)
expr_stmt|;
name|g_mutex_clear
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|mutex
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_async_idle (GimpAsync * async)
name|gimp_async_idle
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
block|{
name|gimp_async_wait
argument_list|(
name|async
argument_list|)
expr_stmt|;
return|return
name|G_SOURCE_REMOVE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_async_stop (GimpAsync * async)
name|gimp_async_stop
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
block|{
if|if
condition|(
operator|!
name|g_queue_is_empty
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|callbacks
argument_list|)
condition|)
block|{
name|g_object_ref
argument_list|(
name|async
argument_list|)
expr_stmt|;
name|async
operator|->
name|priv
operator|->
name|idle_id
operator|=
name|g_idle_add_full
argument_list|(
name|G_PRIORITY_DEFAULT
argument_list|,
operator|(
name|GSourceFunc
operator|)
name|gimp_async_idle
argument_list|,
name|async
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|async
operator|->
name|priv
operator|->
name|stopped
operator|=
name|TRUE
expr_stmt|;
name|g_cond_broadcast
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|cond
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/* creates a new GimpAsync object, initially placed in the "running" state. */
end_comment

begin_function
name|GimpAsync
modifier|*
DECL|function|gimp_async_new (void)
name|gimp_async_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_ASYNC
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/* checks if 'async' is in the "stopped" state */
end_comment

begin_function
name|gboolean
DECL|function|gimp_async_is_stopped (GimpAsync * async)
name|gimp_async_is_stopped
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ASYNC
argument_list|(
name|async
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|async
operator|->
name|priv
operator|->
name|stopped
return|;
block|}
end_function

begin_comment
comment|/* waits for 'async' to transition to the "stopped" state.  if 'async' is  * already stopped, returns immediately.  *  * after the call, all callbacks previously added through  * 'gimp_async_add_callback()' are guaranteed to have been called.  *  * may only be called on the main thread.  */
end_comment

begin_function
name|void
DECL|function|gimp_async_wait (GimpAsync * async)
name|gimp_async_wait
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ASYNC
argument_list|(
name|async
argument_list|)
argument_list|)
expr_stmt|;
name|g_mutex_lock
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|mutex
argument_list|)
expr_stmt|;
while|while
condition|(
operator|!
name|async
operator|->
name|priv
operator|->
name|stopped
condition|)
name|g_cond_wait
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|cond
argument_list|,
operator|&
name|async
operator|->
name|priv
operator|->
name|mutex
argument_list|)
expr_stmt|;
name|g_mutex_unlock
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|mutex
argument_list|)
expr_stmt|;
if|if
condition|(
name|async
operator|->
name|priv
operator|->
name|idle_id
condition|)
block|{
name|GimpAsyncCallbackInfo
modifier|*
name|callback_info
decl_stmt|;
name|g_source_remove
argument_list|(
name|async
operator|->
name|priv
operator|->
name|idle_id
argument_list|)
expr_stmt|;
name|async
operator|->
name|priv
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
while|while
condition|(
operator|(
name|callback_info
operator|=
name|g_queue_pop_head
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|callbacks
argument_list|)
operator|)
condition|)
block|{
name|callback_info
operator|->
name|callback
argument_list|(
name|async
argument_list|,
name|callback_info
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpAsyncCallbackInfo
argument_list|,
name|callback_info
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|async
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* registers a callback to be called when 'async' transitions to the "stopped"  * state.  if 'async' is already stopped, the callback may be called directly.  *  * callbacks are called in the order in which they were added.  'async' is  * guaranteed to be kept alive, even without an external reference, between the  * point where it was stopped, and until all callbacks added while 'async' was  * externally referenced have been called.  *  * the callback is guaranteed to be called on the main thread.  *  * may only be called on the main thread.  */
end_comment

begin_function
name|void
DECL|function|gimp_async_add_callback (GimpAsync * async,GimpAsyncCallback callback,gpointer data)
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
block|{
name|GimpAsyncCallbackInfo
modifier|*
name|callback_info
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ASYNC
argument_list|(
name|async
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|callback
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_mutex_lock
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|mutex
argument_list|)
expr_stmt|;
if|if
condition|(
name|async
operator|->
name|priv
operator|->
name|stopped
operator|&&
name|g_queue_is_empty
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|callbacks
argument_list|)
condition|)
block|{
name|g_mutex_unlock
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|mutex
argument_list|)
expr_stmt|;
name|callback
argument_list|(
name|async
argument_list|,
name|data
argument_list|)
expr_stmt|;
return|return;
block|}
name|callback_info
operator|=
name|g_slice_new
argument_list|(
name|GimpAsyncCallbackInfo
argument_list|)
expr_stmt|;
name|callback_info
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|callback_info
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|g_queue_push_tail
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|callbacks
argument_list|,
name|callback_info
argument_list|)
expr_stmt|;
name|g_mutex_unlock
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|mutex
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* transitions 'async' to the "stopped" state, indicating that the task  * completed normally, possibly providing a result.  *  * 'async' shall be in the "running" state.  *  * may only be called on the async thread.  */
end_comment

begin_function
name|void
DECL|function|gimp_async_finish (GimpAsync * async,gpointer result)
name|gimp_async_finish
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|,
name|gpointer
name|result
parameter_list|)
block|{
name|gimp_async_finish_full
argument_list|(
name|async
argument_list|,
name|result
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* same as 'gimp_async_finish()', taking an additional GDestroyNotify function,  * used for freeing the result when 'async' is destroyed.  */
end_comment

begin_function
name|void
DECL|function|gimp_async_finish_full (GimpAsync * async,gpointer result,GDestroyNotify result_destroy_func)
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
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ASYNC
argument_list|(
name|async
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|async
operator|->
name|priv
operator|->
name|stopped
argument_list|)
expr_stmt|;
name|g_mutex_lock
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|mutex
argument_list|)
expr_stmt|;
name|async
operator|->
name|priv
operator|->
name|finished
operator|=
name|TRUE
expr_stmt|;
name|async
operator|->
name|priv
operator|->
name|result
operator|=
name|result
expr_stmt|;
name|async
operator|->
name|priv
operator|->
name|result_destroy_func
operator|=
name|result_destroy_func
expr_stmt|;
name|gimp_async_stop
argument_list|(
name|async
argument_list|)
expr_stmt|;
name|g_mutex_unlock
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|mutex
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* checks if 'async' completed normally, using 'gimp_async_finish()' (in  * contrast to 'gimp_async_abort()').  *  * 'async' shall be in the "stopped" state.  *  * may only be called on the async thread, or on the main thread when synced  * with the async thread.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_async_is_finished (GimpAsync * async)
name|gimp_async_is_finished
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ASYNC
argument_list|(
name|async
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|async
operator|->
name|priv
operator|->
name|stopped
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|async
operator|->
name|priv
operator|->
name|finished
return|;
block|}
end_function

begin_comment
comment|/* returns the result of 'async', as passed to 'gimp_async_finish()'.  *  * 'async' shall be in the "stopped" state, and should have completed normally.  *  * may only be called on the async thread, or on the main thread when synced  * with the async thread.  */
end_comment

begin_function
name|gpointer
DECL|function|gimp_async_get_result (GimpAsync * async)
name|gimp_async_get_result
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ASYNC
argument_list|(
name|async
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|async
operator|->
name|priv
operator|->
name|stopped
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|async
operator|->
name|priv
operator|->
name|finished
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|async
operator|->
name|priv
operator|->
name|result
return|;
block|}
end_function

begin_comment
comment|/* transitions 'async' to the "stopped" state, indicating that the task  * was stopped before completion (normally, in response to a  * 'gimp_async_cancel()' call).  *  * 'async' shall be in the "running" state.  *  * may only be called on the async thread.  */
end_comment

begin_function
name|void
DECL|function|gimp_async_abort (GimpAsync * async)
name|gimp_async_abort
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ASYNC
argument_list|(
name|async
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|async
operator|->
name|priv
operator|->
name|stopped
argument_list|)
expr_stmt|;
name|g_mutex_lock
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|mutex
argument_list|)
expr_stmt|;
name|gimp_async_stop
argument_list|(
name|async
argument_list|)
expr_stmt|;
name|g_mutex_unlock
argument_list|(
operator|&
name|async
operator|->
name|priv
operator|->
name|mutex
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* requests the cancellation of the task managed by 'async'.  *  * note that 'gimp_async_cancel()' doesn't directly cause 'async' to be  * stopped, nor does it cause the main thread to become synced with the async  * thread.  furthermore, 'async' may still complete successfully even when  * cancellation has been requested.  */
end_comment

begin_function
name|void
DECL|function|gimp_async_cancel (GimpAsync * async)
name|gimp_async_cancel
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ASYNC
argument_list|(
name|async
argument_list|)
argument_list|)
expr_stmt|;
name|async
operator|->
name|priv
operator|->
name|canceled
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_comment
comment|/* checks if cancellation of 'async' has been requested.  *  * note that a return value of TRUE only indicates that 'gimp_async_cancel()'  * has been called for 'async', and not that 'async' is stopped, or, if it is  * stopped, that it was aborted.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_async_is_canceled (GimpAsync * async)
name|gimp_async_is_canceled
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ASYNC
argument_list|(
name|async
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|async
operator|->
name|priv
operator|->
name|canceled
return|;
block|}
end_function

end_unit

