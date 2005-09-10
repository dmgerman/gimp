begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpbase-private.c  * Copyright (C) 2003 Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpbase-private.h"
end_include

begin_decl_stmt
DECL|variable|_gimp_unit_vtable
name|GimpUnitVtable
name|_gimp_unit_vtable
init|=
block|{
name|NULL
block|, }
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_base_init (GimpUnitVtable * vtable)
name|gimp_base_init
parameter_list|(
name|GimpUnitVtable
modifier|*
name|vtable
parameter_list|)
block|{
specifier|static
name|gboolean
name|gimp_base_initialized
init|=
name|FALSE
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|vtable
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_base_initialized
condition|)
name|g_error
argument_list|(
literal|"gimp_base_init() must only be called once!"
argument_list|)
expr_stmt|;
name|_gimp_unit_vtable
operator|=
operator|*
name|vtable
expr_stmt|;
name|gimp_base_initialized
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

end_unit

