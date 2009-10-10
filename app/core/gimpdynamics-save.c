begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpdynamics.h"
end_include

begin_include
include|#
directive|include
file|"gimpdynamics-save.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_dynamics_save (GimpData * data,GError ** error)
name|gimp_dynamics_save
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DYNAMICS
argument_list|(
name|data
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|gimp_config_serialize_to_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|data
argument_list|)
argument_list|,
name|data
operator|->
name|filename
argument_list|,
literal|"GIMP dynamics file"
argument_list|,
literal|"end of GIMP dynamics file"
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

end_unit

