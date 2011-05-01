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

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcurve.h"
end_include

begin_include
include|#
directive|include
file|"gimpcurve-save.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_curve_save (GimpData * data,GError ** error)
name|gimp_curve_save
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
comment|/* GimpCurve *curve; */
name|FILE
modifier|*
name|file
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CURVE
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
comment|/* curve = GIMP_CURVE (data); */
name|file
operator|=
name|g_fopen
argument_list|(
name|gimp_data_get_filename
argument_list|(
name|data
argument_list|)
argument_list|,
literal|"wb"
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
literal|"Could not open '%s' for writing: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|gimp_data_get_filename
argument_list|(
name|data
argument_list|)
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/* FIXME: write curve */
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

