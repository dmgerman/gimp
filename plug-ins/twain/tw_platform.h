begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * TWAIN Plug-in  * Copyright (C) 1999 Craig Setera  * Craig Setera<setera@home.com>  * 03/31/1999  *  * Updated for Mac OS X support  * Brion Vibber<brion@pobox.com>  * 07/22/2004  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_TW_PLATFORM_H
end_ifndef

begin_define
DECL|macro|_TW_PLATFORM_H
define|#
directive|define
name|_TW_PLATFORM_H
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__APPLE__
end_ifdef

begin_comment
comment|/* Mac OS X */
end_comment

begin_include
include|#
directive|include
file|<Carbon/Carbon.h>
end_include

begin_include
include|#
directive|include
file|<TWAIN/TWAIN.h>
end_include

begin_define
DECL|macro|DEBUG_LOGFILE
define|#
directive|define
name|DEBUG_LOGFILE
value|"/tmp/twain.log"
end_define

begin_define
DECL|macro|DUMP_FILE
define|#
directive|define
name|DUMP_FILE
value|"/tmp/twaincap.bin"
end_define

begin_define
DECL|macro|DUMP_NAME
define|#
directive|define
name|DUMP_NAME
value|"dtwain"
end_define

begin_define
DECL|macro|READDUMP_NAME
define|#
directive|define
name|READDUMP_NAME
value|"rtwain"
end_define

begin_define
DECL|macro|_stricmp
define|#
directive|define
name|_stricmp
value|strcasecmp
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* Win32 */
end_comment

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_include
include|#
directive|include
file|"twain.h"
end_include

begin_comment
comment|/* The DLL to be loaded for TWAIN support */
end_comment

begin_define
DECL|macro|TWAIN_DLL_NAME
define|#
directive|define
name|TWAIN_DLL_NAME
value|"TWAIN_32.DLL"
end_define

begin_define
DECL|macro|DEBUG_LOGFILE
define|#
directive|define
name|DEBUG_LOGFILE
value|"c:\\twain.log"
end_define

begin_define
DECL|macro|DUMP_FILE
define|#
directive|define
name|DUMP_FILE
value|"C:\\TWAINCAP.BIN"
end_define

begin_define
DECL|macro|DUMP_NAME
define|#
directive|define
name|DUMP_NAME
value|"DTWAIN.EXE"
end_define

begin_define
DECL|macro|READDUMP_NAME
define|#
directive|define
name|READDUMP_NAME
value|"RTWAIN.EXE"
end_define

begin_comment
comment|/* Windows uses separate entry point */
end_comment

begin_define
DECL|macro|TWAIN_ALTERNATE_MAIN
define|#
directive|define
name|TWAIN_ALTERNATE_MAIN
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

end_unit

