begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphelp.c  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_function
name|void
DECL|function|gimp_standard_help_func (gchar * help_data)
name|gimp_standard_help_func
parameter_list|(
name|gchar
modifier|*
name|help_data
parameter_list|)
block|{
name|gimp_help
argument_list|(
name|gimp_get_progname
argument_list|()
argument_list|,
name|help_data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

