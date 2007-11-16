begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_define
DECL|macro|_WIN32_WINNT
define|#
directive|define
name|_WIN32_WINNT
value|0x0500
end_define

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"base-utils.h"
end_include

begin_define
DECL|macro|NUM_PROCESSORS_DEFAULT
define|#
directive|define
name|NUM_PROCESSORS_DEFAULT
value|1
end_define

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gint
DECL|function|get_number_of_processors (void)
name|get_number_of_processors
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|retval
init|=
name|NUM_PROCESSORS_DEFAULT
decl_stmt|;
ifdef|#
directive|ifdef
name|G_OS_UNIX
if|#
directive|if
name|defined
argument_list|(
name|HAVE_UNISTD_H
argument_list|)
operator|&&
name|defined
argument_list|(
name|_SC_NPROCESSORS_ONLN
argument_list|)
name|retval
operator|=
name|sysconf
argument_list|(
name|_SC_NPROCESSORS_ONLN
argument_list|)
expr_stmt|;
endif|#
directive|endif
endif|#
directive|endif
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|SYSTEM_INFO
name|system_info
decl_stmt|;
name|GetSystemInfo
argument_list|(
operator|&
name|system_info
argument_list|)
expr_stmt|;
name|retval
operator|=
name|system_info
operator|.
name|dwNumberOfProcessors
expr_stmt|;
endif|#
directive|endif
return|return
name|retval
return|;
block|}
end_function

begin_function
name|gint
DECL|function|get_physical_memory_size_megabytes (void)
name|get_physical_memory_size_megabytes
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|retval
init|=
literal|0
decl_stmt|;
ifdef|#
directive|ifdef
name|G_OS_UNIX
comment|/* ??? */
endif|#
directive|endif
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|MEMORYSTATUSEX
name|memory_status
decl_stmt|;
name|memory_status
operator|.
name|dwLength
operator|=
sizeof|sizeof
argument_list|(
name|memory_status
argument_list|)
expr_stmt|;
if|if
condition|(
name|GlobalMemoryStatusEx
argument_list|(
operator|&
name|memory_status
argument_list|)
condition|)
name|retval
operator|=
name|memory_status
operator|.
name|ullTotalPhys
operator|/
operator|(
literal|1024
operator|*
literal|1024
operator|)
expr_stmt|;
endif|#
directive|endif
return|return
name|retval
return|;
block|}
end_function

end_unit

