begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"context_manager.h"
end_include

begin_function
name|void
DECL|function|context_manager_init (void)
name|context_manager_init
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
comment|/*  Implicitly create the standard context    */
name|context
operator|=
name|gimp_context_get_standard
argument_list|()
expr_stmt|;
comment|/*  To be loaded from disk later    */
name|context
operator|=
name|gimp_context_new
argument_list|(
literal|"Default"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_context_set_default
argument_list|(
name|context
argument_list|)
expr_stmt|;
comment|/*  Finally the user context will be initialized with the default context's    *  values.    */
name|context
operator|=
name|gimp_context_new
argument_list|(
literal|"User"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_context_set_user
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|gimp_context_set_current
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|context_manager_free (void)
name|context_manager_free
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_context_set_user
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gimp_context_set_current
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Save to disk before destroying later    */
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp_context_get_default
argument_list|()
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_context_set_default
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

