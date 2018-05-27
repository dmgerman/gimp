begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcancelable.c  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpmarshal.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon294858860103
block|{
DECL|enumerator|CANCEL
name|CANCEL
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_macro
name|G_DEFINE_INTERFACE
argument_list|(
argument|GimpCancelable
argument_list|,
argument|gimp_cancelable
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|guint
name|cancelable_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_cancelable_default_init (GimpCancelableInterface * iface)
name|gimp_cancelable_default_init
parameter_list|(
name|GimpCancelableInterface
modifier|*
name|iface
parameter_list|)
block|{
name|cancelable_signals
index|[
name|CANCEL
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"cancel"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|iface
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpCancelableInterface
argument_list|,
name|cancel
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_cancelable_cancel (GimpCancelable * cancelable)
name|gimp_cancelable_cancel
parameter_list|(
name|GimpCancelable
modifier|*
name|cancelable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CANCELABLE
argument_list|(
name|cancelable
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|cancelable
argument_list|,
name|cancelable_signals
index|[
name|CANCEL
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

