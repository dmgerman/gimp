begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * Thumbnail handling according to the Thumbnail Managing Standard.  * http://triq.net/~pearl/thumbnail-spec/  *  * Copyright (C) 2001-2003  Sven Neumann<sven@gimp.org>  *                          Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"gimpthumb-error.h"
end_include

begin_function
name|GQuark
DECL|function|gimp_thumb_error_quark (void)
name|gimp_thumb_error_quark
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GQuark
name|q
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|q
operator|==
literal|0
condition|)
name|q
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-thumb-error-quark"
argument_list|)
expr_stmt|;
return|return
name|q
return|;
block|}
end_function

end_unit

