begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginhsm.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
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
file|<gegl.h>
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

begin_define
DECL|macro|STRICT
define|#
directive|define
name|STRICT
end_define

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_include
include|#
directive|include
file|<process.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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

begin_comment
comment|/* G_OS_WIN32 || G_WITH_CYGWIN */
end_comment

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginshm.h"
end_include

begin_include
include|#
directive|include
file|"gimp-log.h"
end_include

begin_define
DECL|macro|TILE_MAP_SIZE
define|#
directive|define
name|TILE_MAP_SIZE
value|(GIMP_PLUG_IN_TILE_WIDTH * GIMP_PLUG_IN_TILE_HEIGHT * 16)
end_define

begin_define
DECL|macro|ERRMSG_SHM_DISABLE
define|#
directive|define
name|ERRMSG_SHM_DISABLE
value|"Disabling shared memory tile transport"
end_define

begin_struct
DECL|struct|_GimpPlugInShm
struct|struct
name|_GimpPlugInShm
block|{
DECL|member|shm_ID
name|gint
name|shm_ID
decl_stmt|;
DECL|member|shm_addr
name|guchar
modifier|*
name|shm_addr
decl_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|USE_WIN32_SHM
argument_list|)
DECL|member|shm_handle
name|HANDLE
name|shm_handle
decl_stmt|;
endif|#
directive|endif
block|}
struct|;
end_struct

begin_function
name|GimpPlugInShm
modifier|*
DECL|function|gimp_plug_in_shm_new (void)
name|gimp_plug_in_shm_new
parameter_list|(
name|void
parameter_list|)
block|{
comment|/* allocate a piece of shared memory for use in transporting tiles    *  to plug-ins. if we can't allocate a piece of shared memory then    *  we'll fall back on sending the data over the pipe.    */
name|GimpPlugInShm
modifier|*
name|shm
init|=
name|g_slice_new0
argument_list|(
name|GimpPlugInShm
argument_list|)
decl_stmt|;
name|shm
operator|->
name|shm_ID
operator|=
operator|-
literal|1
expr_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|USE_SYSV_SHM
argument_list|)
comment|/* Use SysV shared memory mechanisms for transferring tile data. */
block|{
name|shm
operator|->
name|shm_ID
operator|=
name|shmget
argument_list|(
name|IPC_PRIVATE
argument_list|,
name|TILE_MAP_SIZE
argument_list|,
name|IPC_CREAT
operator||
literal|0600
argument_list|)
expr_stmt|;
if|if
condition|(
name|shm
operator|->
name|shm_ID
operator|!=
operator|-
literal|1
condition|)
block|{
name|shm
operator|->
name|shm_addr
operator|=
operator|(
name|guchar
operator|*
operator|)
name|shmat
argument_list|(
name|shm
operator|->
name|shm_ID
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|shm
operator|->
name|shm_addr
operator|==
operator|(
name|guchar
operator|*
operator|)
operator|-
literal|1
condition|)
block|{
name|g_printerr
argument_list|(
literal|"shmat() failed: %s\n"
name|ERRMSG_SHM_DISABLE
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|shmctl
argument_list|(
name|shm
operator|->
name|shm_ID
argument_list|,
name|IPC_RMID
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|shm
operator|->
name|shm_ID
operator|=
operator|-
literal|1
expr_stmt|;
block|}
ifdef|#
directive|ifdef
name|IPC_RMID_DEFERRED_RELEASE
if|if
condition|(
name|shm
operator|->
name|shm_addr
operator|!=
operator|(
name|guchar
operator|*
operator|)
operator|-
literal|1
condition|)
name|shmctl
argument_list|(
name|shm
operator|->
name|shm_ID
argument_list|,
name|IPC_RMID
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"shmget() failed: %s\n"
name|ERRMSG_SHM_DISABLE
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
elif|#
directive|elif
name|defined
argument_list|(
name|USE_WIN32_SHM
argument_list|)
comment|/* Use Win32 shared memory mechanisms for transferring tile data. */
block|{
name|gint
name|pid
decl_stmt|;
name|gchar
name|fileMapName
index|[
name|MAX_PATH
index|]
decl_stmt|;
comment|/* Our shared memory id will be our process ID */
name|pid
operator|=
name|GetCurrentProcessId
argument_list|()
expr_stmt|;
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
name|pid
argument_list|)
expr_stmt|;
comment|/* Create the file mapping into paging space */
name|shm
operator|->
name|shm_handle
operator|=
name|CreateFileMapping
argument_list|(
name|INVALID_HANDLE_VALUE
argument_list|,
name|NULL
argument_list|,
name|PAGE_READWRITE
argument_list|,
literal|0
argument_list|,
name|TILE_MAP_SIZE
argument_list|,
name|fileMapName
argument_list|)
expr_stmt|;
if|if
condition|(
name|shm
operator|->
name|shm_handle
condition|)
block|{
comment|/* Map the shared memory into our address space for use */
name|shm
operator|->
name|shm_addr
operator|=
operator|(
name|guchar
operator|*
operator|)
name|MapViewOfFile
argument_list|(
name|shm
operator|->
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
name|shm
operator|->
name|shm_addr
condition|)
block|{
name|shm
operator|->
name|shm_ID
operator|=
name|pid
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"MapViewOfFile error: %d... "
name|ERRMSG_SHM_DISABLE
argument_list|,
name|GetLastError
argument_list|()
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"CreateFileMapping error: %d... "
name|ERRMSG_SHM_DISABLE
argument_list|,
name|GetLastError
argument_list|()
argument_list|)
expr_stmt|;
block|}
block|}
elif|#
directive|elif
name|defined
argument_list|(
name|USE_POSIX_SHM
argument_list|)
comment|/* Use POSIX shared memory mechanisms for transferring tile data. */
block|{
name|gint
name|pid
decl_stmt|;
name|gchar
name|shm_handle
index|[
literal|32
index|]
decl_stmt|;
name|gint
name|shm_fd
decl_stmt|;
comment|/* Our shared memory id will be our process ID */
name|pid
operator|=
name|gimp_get_pid
argument_list|()
expr_stmt|;
comment|/* From the id, derive the file map name */
name|g_snprintf
argument_list|(
name|shm_handle
argument_list|,
sizeof|sizeof
argument_list|(
name|shm_handle
argument_list|)
argument_list|,
literal|"/gimp-shm-%d"
argument_list|,
name|pid
argument_list|)
expr_stmt|;
comment|/* Create the file mapping into paging space */
name|shm_fd
operator|=
name|shm_open
argument_list|(
name|shm_handle
argument_list|,
name|O_RDWR
operator||
name|O_CREAT
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
if|if
condition|(
name|ftruncate
argument_list|(
name|shm_fd
argument_list|,
name|TILE_MAP_SIZE
argument_list|)
operator|!=
operator|-
literal|1
condition|)
block|{
comment|/* Map the shared memory into our address space for use */
name|shm
operator|->
name|shm_addr
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
name|shm
operator|->
name|shm_addr
operator|!=
name|MAP_FAILED
condition|)
block|{
name|shm
operator|->
name|shm_ID
operator|=
name|pid
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"mmap() failed: %s\n"
name|ERRMSG_SHM_DISABLE
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|shm_unlink
argument_list|(
name|shm_handle
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"ftruncate() failed: %s\n"
name|ERRMSG_SHM_DISABLE
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|shm_unlink
argument_list|(
name|shm_handle
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
name|g_printerr
argument_list|(
literal|"shm_open() failed: %s\n"
name|ERRMSG_SHM_DISABLE
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
endif|#
directive|endif
if|if
condition|(
name|shm
operator|->
name|shm_ID
operator|==
operator|-
literal|1
condition|)
block|{
name|g_slice_free
argument_list|(
name|GimpPlugInShm
argument_list|,
name|shm
argument_list|)
expr_stmt|;
name|shm
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|GIMP_LOG
argument_list|(
name|SHM
argument_list|,
literal|"attached shared memory segment ID = %d"
argument_list|,
name|shm
operator|->
name|shm_ID
argument_list|)
expr_stmt|;
block|}
return|return
name|shm
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_shm_free (GimpPlugInShm * shm)
name|gimp_plug_in_shm_free
parameter_list|(
name|GimpPlugInShm
modifier|*
name|shm
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|shm
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|shm
operator|->
name|shm_ID
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
name|shmdt
argument_list|(
name|shm
operator|->
name|shm_addr
argument_list|)
expr_stmt|;
ifndef|#
directive|ifndef
name|IPC_RMID_DEFERRED_RELEASE
name|shmctl
argument_list|(
name|shm
operator|->
name|shm_ID
argument_list|,
name|IPC_RMID
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
endif|#
directive|endif
elif|#
directive|elif
name|defined
argument_list|(
name|USE_WIN32_SHM
argument_list|)
if|if
condition|(
name|shm
operator|->
name|shm_handle
condition|)
name|CloseHandle
argument_list|(
name|shm
operator|->
name|shm_handle
argument_list|)
expr_stmt|;
elif|#
directive|elif
name|defined
argument_list|(
name|USE_POSIX_SHM
argument_list|)
name|gchar
name|shm_handle
index|[
literal|32
index|]
decl_stmt|;
name|munmap
argument_list|(
name|shm
operator|->
name|shm_addr
argument_list|,
name|TILE_MAP_SIZE
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|shm_handle
argument_list|,
sizeof|sizeof
argument_list|(
name|shm_handle
argument_list|)
argument_list|,
literal|"/gimp-shm-%d"
argument_list|,
name|shm
operator|->
name|shm_ID
argument_list|)
expr_stmt|;
name|shm_unlink
argument_list|(
name|shm_handle
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|GIMP_LOG
argument_list|(
name|SHM
argument_list|,
literal|"detached shared memory segment ID = %d"
argument_list|,
name|shm
operator|->
name|shm_ID
argument_list|)
expr_stmt|;
block|}
name|g_slice_free
argument_list|(
name|GimpPlugInShm
argument_list|,
name|shm
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_plug_in_shm_get_ID (GimpPlugInShm * shm)
name|gimp_plug_in_shm_get_ID
parameter_list|(
name|GimpPlugInShm
modifier|*
name|shm
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|shm
operator|!=
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|shm
operator|->
name|shm_ID
return|;
block|}
end_function

begin_function
name|guchar
modifier|*
DECL|function|gimp_plug_in_shm_get_addr (GimpPlugInShm * shm)
name|gimp_plug_in_shm_get_addr
parameter_list|(
name|GimpPlugInShm
modifier|*
name|shm
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|shm
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|shm
operator|->
name|shm_addr
return|;
block|}
end_function

end_unit

