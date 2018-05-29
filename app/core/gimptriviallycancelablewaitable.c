begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptriviallycancelablewaitable.c  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpcancelable.h"
end_include

begin_include
include|#
directive|include
file|"gimptriviallycancelablewaitable.h"
end_include

begin_include
include|#
directive|include
file|"gimpwaitable.h"
end_include

begin_struct
DECL|struct|_GimpTriviallyCancelableWaitablePrivate
struct|struct
name|_GimpTriviallyCancelableWaitablePrivate
block|{
DECL|member|waitable
name|GimpWaitable
modifier|*
name|waitable
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
name|gimp_trivially_cancelable_waitable_cancelable_iface_init
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
name|gimp_trivially_cancelable_waitable_cancel
parameter_list|(
name|GimpCancelable
modifier|*
name|cancelable
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpTriviallyCancelableWaitable,gimp_trivially_cancelable_waitable,GIMP_TYPE_UNCANCELABLE_WAITABLE,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CANCELABLE,gimp_trivially_cancelable_waitable_cancelable_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpTriviallyCancelableWaitable
argument_list|,
argument|gimp_trivially_cancelable_waitable
argument_list|,
argument|GIMP_TYPE_UNCANCELABLE_WAITABLE
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CANCELABLE,                                                 gimp_trivially_cancelable_waitable_cancelable_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_trivially_cancelable_waitable_parent_class
end_define

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
name|gimp_trivially_cancelable_waitable_class_init
parameter_list|(
name|GimpTriviallyCancelableWaitableClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_trivially_cancelable_waitable_cancelable_iface_init (GimpCancelableInterface * iface)
name|gimp_trivially_cancelable_waitable_cancelable_iface_init
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
name|gimp_trivially_cancelable_waitable_cancel
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_trivially_cancelable_waitable_init (GimpTriviallyCancelableWaitable * trivially_cancelable_waitable)
name|gimp_trivially_cancelable_waitable_init
parameter_list|(
name|GimpTriviallyCancelableWaitable
modifier|*
name|trivially_cancelable_waitable
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_trivially_cancelable_waitable_cancel (GimpCancelable * cancelable)
name|gimp_trivially_cancelable_waitable_cancel
parameter_list|(
name|GimpCancelable
modifier|*
name|cancelable
parameter_list|)
block|{
name|GimpUncancelableWaitable
modifier|*
name|uncancelable_waitable
init|=
name|GIMP_UNCANCELABLE_WAITABLE
argument_list|(
name|cancelable
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|uncancelable_waitable
operator|->
name|waitable
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpWaitable
modifier|*
DECL|function|gimp_trivially_cancelable_waitable_new (GimpWaitable * waitable)
name|gimp_trivially_cancelable_waitable_new
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|)
block|{
name|GimpUncancelableWaitable
modifier|*
name|uncancelable_waitable
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_WAITABLE
argument_list|(
name|waitable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|uncancelable_waitable
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TRIVIALLY_CANCELABLE_WAITABLE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|uncancelable_waitable
operator|->
name|waitable
operator|=
name|g_object_ref
argument_list|(
name|waitable
argument_list|)
expr_stmt|;
return|return
name|GIMP_WAITABLE
argument_list|(
name|uncancelable_waitable
argument_list|)
return|;
block|}
end_function

end_unit

