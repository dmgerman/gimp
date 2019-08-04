begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimp-shm.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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

begin_if
if|#
directive|if
name|defined
argument_list|(
name|USE_SYSV_SHM
argument_list|)
end_if

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_IPC_H
end_ifdef

begin_include
include|#
directive|include
file|<sys/ipc.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_SHM_H
end_ifdef

begin_include
include|#
directive|include
file|<sys/shm.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_elif
elif|#
directive|elif
name|defined
argument_list|(
name|USE_POSIX_SHM
argument_list|)
end_elif

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
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<sys/mman.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* USE_POSIX_SHM */
end_comment

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_if
if|#
directive|if
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
operator|||
name|defined
argument_list|(
name|G_WITH_CYGWIN
argument_list|)
end_if

begin_ifdef
ifdef|#
directive|ifdef
name|STRICT
end_ifdef

begin_undef
undef|#
directive|undef
name|STRICT
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|STRICT
define|#
directive|define
name|STRICT
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|_WIN32_WINNT
end_ifdef

begin_undef
undef|#
directive|undef
name|_WIN32_WINNT
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|_WIN32_WINNT
define|#
directive|define
name|_WIN32_WINNT
value|0x0601
end_define

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_include
include|#
directive|include
file|<tlhelp32.h>
end_include

begin_undef
undef|#
directive|undef
name|RGB
end_undef

begin_define
DECL|macro|USE_WIN32_SHM
define|#
directive|define
name|USE_WIN32_SHM
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-shm.h"
end_include

begin_define
DECL|macro|TILE_MAP_SIZE
define|#
directive|define
name|TILE_MAP_SIZE
value|(_tile_width * _tile_height * 32)
end_define

begin_define
DECL|macro|ERRMSG_SHM_FAILED
define|#
directive|define
name|ERRMSG_SHM_FAILED
value|"Could not attach to gimp shared memory segment"
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|USE_WIN32_SHM
end_ifdef

begin_decl_stmt
DECL|variable|_shm_handle
specifier|static
name|HANDLE
name|_shm_handle
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|_shm_ID
specifier|static
name|gint
name|_shm_ID
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|_shm_addr
specifier|static
name|guchar
modifier|*
name|_shm_addr
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|guchar
modifier|*
DECL|function|_gimp_shm_addr (void)
name|_gimp_shm_addr
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|_shm_addr
return|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_shm_open (gint shm_ID)
name|_gimp_shm_open
parameter_list|(
name|gint
name|shm_ID
parameter_list|)
block|{
name|_shm_ID
operator|=
name|shm_ID
expr_stmt|;
if|if
condition|(
name|_shm_ID
operator|!=
operator|-
literal|1
condition|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|USE_SYSV_SHM
argument_list|)
comment|/* Use SysV shared memory mechanisms for transferring tile data. */
name|_shm_addr
operator|=
operator|(
name|guchar
operator|*
operator|)
name|shmat
argument_list|(
name|_shm_ID
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|_shm_addr
operator|==
operator|(
name|guchar
operator|*
operator|)
operator|-
literal|1
condition|)
block|{
name|g_error
argument_list|(
literal|"shmat() failed: %s\n"
name|ERRMSG_SHM_FAILED
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
elif|#
directive|elif
name|defined
argument_list|(
name|USE_WIN32_SHM
argument_list|)
comment|/* Use Win32 shared memory mechanisms for transferring tile data. */
name|gchar
name|fileMapName
index|[
literal|128
index|]
decl_stmt|;
comment|/* From the id, derive the file map name */
name|g_snprintf
argument_list|(
name|fileMapName
argument_list|,
sizeof|sizeof
argument_list|(
name|fileMapName
argument_list|)
argument_list|,
literal|"GIMP%d.SHM"
argument_list|,
name|_shm_ID
argument_list|)
expr_stmt|;
comment|/* Open the file mapping */
name|shm_handle
operator|=
name|OpenFileMapping
argument_list|(
name|FILE_MAP_ALL_ACCESS
argument_list|,
literal|0
argument_list|,
name|fileMapName
argument_list|)
expr_stmt|;
if|if
condition|(
name|shm_handle
condition|)
block|{
comment|/* Map the shared memory into our address space for use */
name|_shm_addr
operator|=
operator|(
name|guchar
operator|*
operator|)
name|MapViewOfFile
argument_list|(
name|shm_handle
argument_list|,
name|FILE_MAP_ALL_ACCESS
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|TILE_MAP_SIZE
argument_list|)
expr_stmt|;
comment|/* Verify that we mapped our view */
if|if
condition|(
operator|!
name|_shm_addr
condition|)
block|{
name|g_error
argument_list|(
literal|"MapViewOfFile error: %lu... "
name|ERRMSG_SHM_FAILED
argument_list|,
name|GetLastError
argument_list|()
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_error
argument_list|(
literal|"OpenFileMapping error: %lu... "
name|ERRMSG_SHM_FAILED
argument_list|,
name|GetLastError
argument_list|()
argument_list|)
expr_stmt|;
block|}
elif|#
directive|elif
name|defined
argument_list|(
name|USE_POSIX_SHM
argument_list|)
comment|/* Use POSIX shared memory mechanisms for transferring tile data. */
name|gchar
name|map_file
index|[
literal|32
index|]
decl_stmt|;
name|gint
name|shm_fd
decl_stmt|;
comment|/* From the id, derive the file map name */
name|g_snprintf
argument_list|(
name|map_file
argument_list|,
sizeof|sizeof
argument_list|(
name|map_file
argument_list|)
argument_list|,
literal|"/gimp-shm-%d"
argument_list|,
name|_shm_ID
argument_list|)
expr_stmt|;
comment|/* Open the file mapping */
name|shm_fd
operator|=
name|shm_open
argument_list|(
name|map_file
argument_list|,
name|O_RDWR
argument_list|,
literal|0600
argument_list|)
expr_stmt|;
if|if
condition|(
name|shm_fd
operator|!=
operator|-
literal|1
condition|)
block|{
comment|/* Map the shared memory into our address space for use */
name|_shm_addr
operator|=
operator|(
name|guchar
operator|*
operator|)
name|mmap
argument_list|(
name|NULL
argument_list|,
name|TILE_MAP_SIZE
argument_list|,
name|PROT_READ
operator||
name|PROT_WRITE
argument_list|,
name|MAP_SHARED
argument_list|,
name|shm_fd
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* Verify that we mapped our view */
if|if
condition|(
name|_shm_addr
operator|==
name|MAP_FAILED
condition|)
block|{
name|g_error
argument_list|(
literal|"mmap() failed: %s\n"
name|ERRMSG_SHM_FAILED
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|close
argument_list|(
name|shm_fd
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_error
argument_list|(
literal|"shm_open() failed: %s\n"
name|ERRMSG_SHM_FAILED
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
block|}
block|}
end_function

begin_function
name|void
DECL|function|_gimp_shm_close (void)
name|_gimp_shm_close
parameter_list|(
name|void
parameter_list|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|USE_SYSV_SHM
argument_list|)
if|if
condition|(
operator|(
name|_shm_ID
operator|!=
operator|-
literal|1
operator|)
operator|&&
name|_shm_addr
condition|)
name|shmdt
argument_list|(
operator|(
name|char
operator|*
operator|)
name|_shm_addr
argument_list|)
expr_stmt|;
elif|#
directive|elif
name|defined
argument_list|(
name|USE_WIN32_SHM
argument_list|)
if|if
condition|(
name|shm_handle
condition|)
name|CloseHandle
argument_list|(
name|shm_handle
argument_list|)
expr_stmt|;
elif|#
directive|elif
name|defined
argument_list|(
name|USE_POSIX_SHM
argument_list|)
if|if
condition|(
operator|(
name|_shm_ID
operator|!=
operator|-
literal|1
operator|)
operator|&&
operator|(
name|_shm_addr
operator|!=
name|MAP_FAILED
operator|)
condition|)
name|munmap
argument_list|(
name|_shm_addr
argument_list|,
name|TILE_MAP_SIZE
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

end_unit

