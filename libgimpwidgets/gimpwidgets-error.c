begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpwidgets-error.c  * Copyright (C) 2008 Martin Nordholts<martinn@svn.gnome.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"gimpwidgets-error.h"
end_include

begin_comment
comment|/**  * gimp_widgets_error_quark:  *  * This function is never called directly. Use GIMP_WIDGETS_ERROR() instead.  *  * Returns: the #GQuark that defines the GIMP widgets error domain.  **/
end_comment

begin_function
name|GQuark
DECL|function|gimp_widgets_error_quark (void)
name|gimp_widgets_error_quark
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_quark_from_static_string
argument_list|(
literal|"gimp-widgets-error-quark"
argument_list|)
return|;
block|}
end_function

end_unit

