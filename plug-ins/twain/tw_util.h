begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*    * TWAIN Plug-in  * Copyright (C) 1999 Craig Setera  * Craig Setera<setera@home.com>  * 03/31/1999  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  *  * Based on (at least) the following plug-ins:  * Screenshot  * GIF  * Randomize  *  * Any suggestions, bug-reports or patches are welcome.  *   * This plug-in interfaces to the TWAIN support library in order  * to capture images from TWAIN devices directly into GIMP images.  * The plug-in is capable of acquiring the following type of  * images:  * - B/W (1 bit images translated to grayscale B/W)  * - Grayscale up to 16 bits per pixel  * - RGB up to 16 bits per sample (24, 30, 36, etc.)  * - Paletted images (both Gray and RGB)  *  * Prerequisites:  *  This plug-in will not compile on anything other than a Win32  *  platform.  Although the TWAIN documentation implies that there  *  is TWAIN support available on Macintosh, I neither have a   *  Macintosh nor the interest in porting this.  If anyone else  *  has an interest, consult www.twain.org for more information on  *  interfacing to TWAIN.  *  * Known problems:  * - Multiple image transfers will hang the plug-in.  The current  *   configuration compiles with a maximum of single image transfers.  */
end_comment

begin_comment
comment|/*   * Revision history  *  (02/07/99)  v0.1   First working version (internal)  *  (02/09/99)  v0.2   First release to anyone other than myself  *  (02/15/99)  v0.3   Added image dump and read support for debugging  *  (03/31/99)  v0.5   Added support for multi-byte samples and paletted   *                     images.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TW_UTIL_H
end_ifndef

begin_define
DECL|macro|__TW_UTIL_H
define|#
directive|define
name|__TW_UTIL_H
end_define

begin_include
include|#
directive|include
file|"twain.h"
end_include

begin_function_decl
name|void
name|LogMessage
parameter_list|(
name|char
modifier|*
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|LogLastWinError
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|_DEBUG
end_ifdef

begin_function_decl
name|void
name|logBegin
parameter_list|(
name|pTW_IMAGEINFO
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|logData
parameter_list|(
name|pTW_IMAGEINFO
parameter_list|,
name|pTW_IMAGEMEMXFER
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TW_UTIL_H */
end_comment

end_unit

