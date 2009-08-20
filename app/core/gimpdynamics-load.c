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
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|"libgimpbase/gimpwin32-io.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

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
file|"gimpdynamics-load.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GList
modifier|*
DECL|function|gimp_dynamics_load (const gchar * filename,GError ** error)
name|gimp_dynamics_load
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|FILE
modifier|*
name|file
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_path_is_absolute
argument_list|(
name|filename
argument_list|)
argument_list|,
name|NULL
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
name|NULL
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_fopen
argument_list|(
name|filename
argument_list|,
literal|"rb"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_OPEN
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/* load dynamics */
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

