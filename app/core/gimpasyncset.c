begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpasyncset.c  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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

begin_include
include|#
directive|include
file|"gimpasyncset.h"
end_include

begin_include
include|#
directive|include
file|"gimpcancelable.h"
end_include

begin_include
include|#
directive|include
file|"gimpwaitable.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2796b06c0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_EMPTY
name|PROP_EMPTY
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpAsyncSetPrivate
struct|struct
name|_GimpAsyncSetPrivate
block|{
DECL|member|asyncs
name|GHashTable
modifier|*
name|asyncs
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
name|gimp_async_set_waitable_iface_init
parameter_list|(
name|GimpWaitableInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_async_set_cancelable_iface_init
parameter_list|(
name|GimpCancelableInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_async_set_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_async_set_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_async_set_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_async_set_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_async_set_wait
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_async_set_try_wait
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_async_set_wait_until
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
specifier|static
name|void
name|gimp_async_set_cancel
parameter_list|(
name|GimpCancelable
modifier|*
name|cancelable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_async_set_async_callback
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|,
name|GimpAsyncSet
modifier|*
name|async_set
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpAsyncSet,gimp_async_set,G_TYPE_OBJECT,G_IMPLEMENT_INTERFACE (GIMP_TYPE_WAITABLE,gimp_async_set_waitable_iface_init)G_IMPLEMENT_INTERFACE (GIMP_TYPE_CANCELABLE,gimp_async_set_cancelable_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpAsyncSet
argument_list|,
argument|gimp_async_set
argument_list|,
argument|G_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_WAITABLE,                                                 gimp_async_set_waitable_iface_init)                          G_IMPLEMENT_INTERFACE (GIMP_TYPE_CANCELABLE,                                                 gimp_async_set_cancelable_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_async_set_parent_class
end_define

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
name|gimp_async_set_class_init
parameter_list|(
name|GimpAsyncSetClass
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
name|dispose
operator|=
name|gimp_async_set_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_async_set_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_async_set_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_async_set_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_EMPTY
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"empty"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpAsyncSetPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_async_set_waitable_iface_init (GimpWaitableInterface * iface)
name|gimp_async_set_waitable_iface_init
parameter_list|(
name|GimpWaitableInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|wait
operator|=
name|gimp_async_set_wait
expr_stmt|;
name|iface
operator|->
name|try_wait
operator|=
name|gimp_async_set_try_wait
expr_stmt|;
name|iface
operator|->
name|wait_until
operator|=
name|gimp_async_set_wait_until
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_async_set_cancelable_iface_init (GimpCancelableInterface * iface)
name|gimp_async_set_cancelable_iface_init
parameter_list|(
name|GimpCancelableInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|cancel
operator|=
name|gimp_async_set_cancel
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_async_set_init (GimpAsyncSet * async_set)
name|gimp_async_set_init
parameter_list|(
name|GimpAsyncSet
modifier|*
name|async_set
parameter_list|)
block|{
name|async_set
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|async_set
argument_list|,
name|GIMP_TYPE_ASYNC_SET
argument_list|,
name|GimpAsyncSetPrivate
argument_list|)
expr_stmt|;
name|async_set
operator|->
name|priv
operator|->
name|asyncs
operator|=
name|g_hash_table_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_async_set_dispose (GObject * object)
name|gimp_async_set_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpAsyncSet
modifier|*
name|async_set
init|=
name|GIMP_ASYNC_SET
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gimp_async_set_clear
argument_list|(
name|async_set
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_async_set_finalize (GObject * object)
name|gimp_async_set_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpAsyncSet
modifier|*
name|async_set
init|=
name|GIMP_ASYNC_SET
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_hash_table_unref
argument_list|(
name|async_set
operator|->
name|priv
operator|->
name|asyncs
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
name|void
DECL|function|gimp_async_set_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_async_set_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
switch|switch
condition|(
name|property_id
condition|)
block|{
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_async_set_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_async_set_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpAsyncSet
modifier|*
name|async_set
init|=
name|GIMP_ASYNC_SET
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_EMPTY
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gimp_async_set_is_empty
argument_list|(
name|async_set
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_async_set_wait (GimpWaitable * waitable)
name|gimp_async_set_wait
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|)
block|{
name|GimpAsyncSet
modifier|*
name|async_set
init|=
name|GIMP_ASYNC_SET
argument_list|(
name|waitable
argument_list|)
decl_stmt|;
while|while
condition|(
operator|!
name|gimp_async_set_is_empty
argument_list|(
name|async_set
argument_list|)
condition|)
block|{
name|GimpAsync
modifier|*
name|async
decl_stmt|;
name|GHashTableIter
name|iter
decl_stmt|;
name|g_hash_table_iter_init
argument_list|(
operator|&
name|iter
argument_list|,
name|async_set
operator|->
name|priv
operator|->
name|asyncs
argument_list|)
expr_stmt|;
name|g_hash_table_iter_next
argument_list|(
operator|&
name|iter
argument_list|,
operator|(
name|gpointer
operator|*
operator|)
operator|&
name|async
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_waitable_wait
argument_list|(
name|GIMP_WAITABLE
argument_list|(
name|async
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_async_set_try_wait (GimpWaitable * waitable)
name|gimp_async_set_try_wait
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|)
block|{
name|GimpAsyncSet
modifier|*
name|async_set
init|=
name|GIMP_ASYNC_SET
argument_list|(
name|waitable
argument_list|)
decl_stmt|;
while|while
condition|(
operator|!
name|gimp_async_set_is_empty
argument_list|(
name|async_set
argument_list|)
condition|)
block|{
name|GimpAsync
modifier|*
name|async
decl_stmt|;
name|GHashTableIter
name|iter
decl_stmt|;
name|g_hash_table_iter_init
argument_list|(
operator|&
name|iter
argument_list|,
name|async_set
operator|->
name|priv
operator|->
name|asyncs
argument_list|)
expr_stmt|;
name|g_hash_table_iter_next
argument_list|(
operator|&
name|iter
argument_list|,
operator|(
name|gpointer
operator|*
operator|)
operator|&
name|async
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_waitable_try_wait
argument_list|(
name|GIMP_WAITABLE
argument_list|(
name|async
argument_list|)
argument_list|)
condition|)
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_async_set_wait_until (GimpWaitable * waitable,gint64 end_time)
name|gimp_async_set_wait_until
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|,
name|gint64
name|end_time
parameter_list|)
block|{
name|GimpAsyncSet
modifier|*
name|async_set
init|=
name|GIMP_ASYNC_SET
argument_list|(
name|waitable
argument_list|)
decl_stmt|;
while|while
condition|(
operator|!
name|gimp_async_set_is_empty
argument_list|(
name|async_set
argument_list|)
condition|)
block|{
name|GimpAsync
modifier|*
name|async
decl_stmt|;
name|GHashTableIter
name|iter
decl_stmt|;
name|g_hash_table_iter_init
argument_list|(
operator|&
name|iter
argument_list|,
name|async_set
operator|->
name|priv
operator|->
name|asyncs
argument_list|)
expr_stmt|;
name|g_hash_table_iter_next
argument_list|(
operator|&
name|iter
argument_list|,
operator|(
name|gpointer
operator|*
operator|)
operator|&
name|async
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_waitable_wait_until
argument_list|(
name|GIMP_WAITABLE
argument_list|(
name|async
argument_list|)
argument_list|,
name|end_time
argument_list|)
condition|)
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_async_set_cancel (GimpCancelable * cancelable)
name|gimp_async_set_cancel
parameter_list|(
name|GimpCancelable
modifier|*
name|cancelable
parameter_list|)
block|{
name|GimpAsyncSet
modifier|*
name|async_set
init|=
name|GIMP_ASYNC_SET
argument_list|(
name|cancelable
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|g_hash_table_get_keys
argument_list|(
name|async_set
operator|->
name|priv
operator|->
name|asyncs
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|list
argument_list|,
operator|(
name|GFunc
operator|)
name|g_object_ref
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|list
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_cancelable_cancel
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free_full
argument_list|(
name|list
argument_list|,
name|g_object_unref
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_async_set_async_callback (GimpAsync * async,GimpAsyncSet * async_set)
name|gimp_async_set_async_callback
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|,
name|GimpAsyncSet
modifier|*
name|async_set
parameter_list|)
block|{
name|g_hash_table_remove
argument_list|(
name|async_set
operator|->
name|priv
operator|->
name|asyncs
argument_list|,
name|async
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_async_set_is_empty
argument_list|(
name|async_set
argument_list|)
condition|)
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|async_set
argument_list|)
argument_list|,
literal|"empty"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpAsyncSet
modifier|*
DECL|function|gimp_async_set_new (void)
name|gimp_async_set_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_ASYNC_SET
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_async_set_add (GimpAsyncSet * async_set,GimpAsync * async)
name|gimp_async_set_add
parameter_list|(
name|GimpAsyncSet
modifier|*
name|async_set
parameter_list|,
name|GimpAsync
modifier|*
name|async
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ASYNC_SET
argument_list|(
name|async_set
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ASYNC
argument_list|(
name|async
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_hash_table_add
argument_list|(
name|async_set
operator|->
name|priv
operator|->
name|asyncs
argument_list|,
name|async
argument_list|)
condition|)
block|{
if|if
condition|(
name|g_hash_table_size
argument_list|(
name|async_set
operator|->
name|priv
operator|->
name|asyncs
argument_list|)
operator|==
literal|1
condition|)
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|async_set
argument_list|)
argument_list|,
literal|"empty"
argument_list|)
expr_stmt|;
name|gimp_async_add_callback
argument_list|(
name|async
argument_list|,
operator|(
name|GimpAsyncCallback
operator|)
name|gimp_async_set_async_callback
argument_list|,
name|async_set
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_async_set_remove (GimpAsyncSet * async_set,GimpAsync * async)
name|gimp_async_set_remove
parameter_list|(
name|GimpAsyncSet
modifier|*
name|async_set
parameter_list|,
name|GimpAsync
modifier|*
name|async
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ASYNC_SET
argument_list|(
name|async_set
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ASYNC
argument_list|(
name|async
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_hash_table_remove
argument_list|(
name|async_set
operator|->
name|priv
operator|->
name|asyncs
argument_list|,
name|async
argument_list|)
condition|)
block|{
name|gimp_async_remove_callback
argument_list|(
name|async
argument_list|,
operator|(
name|GimpAsyncCallback
operator|)
name|gimp_async_set_async_callback
argument_list|,
name|async_set
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_hash_table_size
argument_list|(
name|async_set
operator|->
name|priv
operator|->
name|asyncs
argument_list|)
operator|==
literal|0
condition|)
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|async_set
argument_list|)
argument_list|,
literal|"empty"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_async_set_clear (GimpAsyncSet * async_set)
name|gimp_async_set_clear
parameter_list|(
name|GimpAsyncSet
modifier|*
name|async_set
parameter_list|)
block|{
name|GimpAsync
modifier|*
name|async
decl_stmt|;
name|GHashTableIter
name|iter
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ASYNC_SET
argument_list|(
name|async_set
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_async_set_is_empty
argument_list|(
name|async_set
argument_list|)
condition|)
return|return;
name|g_hash_table_iter_init
argument_list|(
operator|&
name|iter
argument_list|,
name|async_set
operator|->
name|priv
operator|->
name|asyncs
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_hash_table_iter_next
argument_list|(
operator|&
name|iter
argument_list|,
operator|(
name|gpointer
operator|*
operator|)
operator|&
name|async
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gimp_async_remove_callback
argument_list|(
name|async
argument_list|,
operator|(
name|GimpAsyncCallback
operator|)
name|gimp_async_set_async_callback
argument_list|,
name|async_set
argument_list|)
expr_stmt|;
block|}
name|g_hash_table_remove_all
argument_list|(
name|async_set
operator|->
name|priv
operator|->
name|asyncs
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|async_set
argument_list|)
argument_list|,
literal|"empty"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_async_set_is_empty (GimpAsyncSet * async_set)
name|gimp_async_set_is_empty
parameter_list|(
name|GimpAsyncSet
modifier|*
name|async_set
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ASYNC_SET
argument_list|(
name|async_set
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|g_hash_table_size
argument_list|(
name|async_set
operator|->
name|priv
operator|->
name|asyncs
argument_list|)
operator|==
literal|0
return|;
block|}
end_function

end_unit

