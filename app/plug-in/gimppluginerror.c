begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimppluginerror.h"
end_include

begin_comment
comment|/**  * gimp_plug_in_error_quark:  *  * This function is never called directly. Use GIMP_PLUG_IN_ERROR() instead.  *  * Returns: the #GQuark that defines the GimpPlugIn error domain.  **/
end_comment

begin_function
name|GQuark
DECL|function|gimp_plug_in_error_quark (void)
name|gimp_plug_in_error_quark
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_quark_from_static_string
argument_list|(
literal|"gimp-plug-in-error-quark"
argument_list|)
return|;
block|}
end_function

end_unit

