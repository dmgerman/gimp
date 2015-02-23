begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * TWAIN Plug-in  * Copyright (C) 1999 Craig Setera  * Craig Setera<setera@home.com>  * 03/31/1999  *  * Updated for Mac OS X support  * Brion Vibber<brion@pobox.com>  * 07/22/2004  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_TW_LOCAL_H
end_ifndef

begin_define
DECL|macro|_TW_LOCAL_H
define|#
directive|define
name|_TW_LOCAL_H
end_define

begin_include
include|#
directive|include
file|"tw_func.h"
end_include

begin_comment
comment|/* Functions which the platform-independent code will call */
end_comment

begin_function_decl
name|TW_UINT16
name|callDSM
parameter_list|(
name|pTW_IDENTITY
parameter_list|,
name|pTW_IDENTITY
parameter_list|,
name|TW_UINT32
parameter_list|,
name|TW_UINT16
parameter_list|,
name|TW_UINT16
parameter_list|,
name|TW_MEMREF
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|twainIsAvailable
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|twainQuitApplication
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|twainSetupCallback
parameter_list|(
name|pTW_SESSION
name|twSession
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TW_HANDLE
name|twainAllocHandle
parameter_list|(
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TW_MEMREF
name|twainLockHandle
parameter_list|(
name|TW_HANDLE
name|handle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|twainUnlockHandle
parameter_list|(
name|TW_HANDLE
name|handle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|twainFreeHandle
parameter_list|(
name|TW_HANDLE
name|handle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|twainMain
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|scanImage
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

