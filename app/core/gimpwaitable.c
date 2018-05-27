begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpwaitable.c  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpwaitable.h"
end_include

begin_macro
DECL|function|G_DEFINE_INTERFACE (GimpWaitable,gimp_waitable,G_TYPE_OBJECT)
name|G_DEFINE_INTERFACE
argument_list|(
argument|GimpWaitable
argument_list|,
argument|gimp_waitable
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
name|gimp_waitable_default_init
parameter_list|(
name|GimpWaitableInterface
modifier|*
name|iface
parameter_list|)
block|{ }
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_waitable_wait (GimpWaitable * waitable)
name|gimp_waitable_wait
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|)
block|{
name|GimpWaitableInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_WAITABLE
argument_list|(
name|waitable
argument_list|)
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_WAITABLE_GET_INTERFACE
argument_list|(
name|waitable
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|wait
condition|)
name|iface
operator|->
name|wait
argument_list|(
name|waitable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_waitable_wait_until (GimpWaitable * waitable,gint64 end_time)
name|gimp_waitable_wait_until
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|,
name|gint64
name|end_time
parameter_list|)
block|{
name|GimpWaitableInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_WAITABLE
argument_list|(
name|waitable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_WAITABLE_GET_INTERFACE
argument_list|(
name|waitable
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|wait_until
condition|)
block|{
return|return
name|iface
operator|->
name|wait_until
argument_list|(
name|waitable
argument_list|,
name|end_time
argument_list|)
return|;
block|}
else|else
block|{
name|gimp_waitable_wait
argument_list|(
name|waitable
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_waitable_wait_for (GimpWaitable * waitable,gint64 wait_duration)
name|gimp_waitable_wait_for
parameter_list|(
name|GimpWaitable
modifier|*
name|waitable
parameter_list|,
name|gint64
name|wait_duration
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_WAITABLE
argument_list|(
name|waitable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|gimp_waitable_wait_until
argument_list|(
name|waitable
argument_list|,
name|g_get_monotonic_time
argument_list|()
operator|+
name|wait_duration
argument_list|)
return|;
block|}
end_function

end_unit

