begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

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

begin_include
include|#
directive|include
file|<glib-object.h>
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
file|"base/tile.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-shm.h"
end_include

begin_decl_stmt
DECL|variable|shm_ID
specifier|static
name|gint
name|shm_ID
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|shm_addr
specifier|static
name|guchar
modifier|*
name|shm_addr
init|=
name|NULL
decl_stmt|;
end_decl_stmt

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

begin_decl_stmt
DECL|variable|shm_handle
specifier|static
name|HANDLE
name|shm_handle
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|void
DECL|function|plug_in_shm_init (Gimp * gimp)
name|plug_in_shm_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
comment|/* allocate a piece of shared memory for use in transporting tiles    *  to plug-ins. if we can't allocate a piece of shared memory then    *  we'll fall back on sending the data over the pipe.    */
ifdef|#
directive|ifdef
name|HAVE_SHM_H
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|shm_ID
operator|=
name|shmget
argument_list|(
name|IPC_PRIVATE
argument_list|,
name|TILE_WIDTH
operator|*
name|TILE_HEIGHT
operator|*
literal|4
argument_list|,
name|IPC_CREAT
operator||
literal|0600
argument_list|)
expr_stmt|;
if|if
condition|(
name|shm_ID
operator|==
operator|-
literal|1
condition|)
block|{
name|g_message
argument_list|(
literal|"shmget() failed: Disabling shared memory tile transport."
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|shm_addr
operator|=
operator|(
name|guchar
operator|*
operator|)
name|shmat
argument_list|(
name|shm_ID
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
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
name|g_message
argument_list|(
literal|"shmat() failed: Disabling shared memory tile transport."
argument_list|)
expr_stmt|;
name|shmctl
argument_list|(
name|shm_ID
argument_list|,
name|IPC_RMID
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
else|#
directive|else
comment|/* ! HAVE_SHM_H */
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
comment|/* Use Win32 shared memory mechanisms for    * transfering tile data.    */
name|gint
name|pid
decl_stmt|;
name|gchar
name|fileMapName
index|[
name|MAX_PATH
index|]
decl_stmt|;
name|gint
name|tileByteSize
init|=
name|TILE_WIDTH
operator|*
name|TILE_HEIGHT
operator|*
literal|4
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
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
name|shm_handle
operator|=
name|CreateFileMapping
argument_list|(
operator|(
name|HANDLE
operator|)
literal|0xFFFFFFFF
argument_list|,
name|NULL
argument_list|,
name|PAGE_READWRITE
argument_list|,
literal|0
argument_list|,
name|tileByteSize
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
name|shm_addr
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
name|tileByteSize
argument_list|)
expr_stmt|;
comment|/* Verify that we mapped our view */
if|if
condition|(
name|shm_addr
condition|)
name|shm_ID
operator|=
name|pid
expr_stmt|;
else|else
name|g_warning
argument_list|(
literal|"MapViewOfFile error: "
literal|"%d... disabling shared memory transport"
argument_list|,
name|GetLastError
argument_list|()
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"CreateFileMapping error: "
literal|"%d... disabling shared memory transport"
argument_list|,
name|GetLastError
argument_list|()
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
comment|/* G_OS_WIN32 || G_WITH_CYGWIN */
endif|#
directive|endif
comment|/* HAVE_SHM_H */
block|}
end_function

begin_function
name|void
DECL|function|plug_in_shm_exit (Gimp * gimp)
name|plug_in_shm_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
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
name|CloseHandle
argument_list|(
name|shm_handle
argument_list|)
expr_stmt|;
else|#
directive|else
comment|/* ! (G_OS_WIN32 || G_WITH_CYGWIN) */
ifdef|#
directive|ifdef
name|HAVE_SHM_H
ifndef|#
directive|ifndef
name|IPC_RMID_DEFERRED_RELEASE
if|if
condition|(
name|shm_ID
operator|!=
operator|-
literal|1
condition|)
block|{
name|shmdt
argument_list|(
name|shm_addr
argument_list|)
expr_stmt|;
name|shmctl
argument_list|(
name|shm_ID
argument_list|,
name|IPC_RMID
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|#
directive|else
comment|/* IPC_RMID_DEFERRED_RELEASE */
if|if
condition|(
name|shm_ID
operator|!=
operator|-
literal|1
condition|)
block|{
name|shmdt
argument_list|(
name|shm_addr
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
endif|#
directive|endif
comment|/* HAVE_SHM_H */
endif|#
directive|endif
comment|/* G_OS_WIN32 || G_WITH_CYGWIN */
block|}
end_function

begin_function
name|gint
DECL|function|plug_in_shm_get_ID (Gimp * gimp)
name|plug_in_shm_get_ID
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
return|return
name|shm_ID
return|;
block|}
end_function

begin_function
name|guchar
modifier|*
DECL|function|plug_in_shm_get_addr (Gimp * gimp)
name|plug_in_shm_get_addr
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
return|return
name|shm_addr
return|;
block|}
end_function

end_unit

