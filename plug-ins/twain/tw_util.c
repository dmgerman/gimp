begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*    * TWAIN Plug-in  * Copyright (C) 1999 Craig Setera  * Craig Setera<setera@home.com>  * 03/31/1999  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  *  * Based on (at least) the following plug-ins:  * Screenshot  * GIF  * Randomize  *  * Any suggestions, bug-reports or patches are welcome.  *   * This plug-in interfaces to the TWAIN support library in order  * to capture images from TWAIN devices directly into GIMP images.  * The plug-in is capable of acquiring the following type of  * images:  * - B/W (1 bit images translated to grayscale B/W)  * - Grayscale up to 16 bits per pixel  * - RGB up to 16 bits per sample (24, 30, 36, etc.)  * - Paletted images (both Gray and RGB)  *  * Prerequisites:  *  This plug-in will not compile on anything other than a Win32  *  platform.  Although the TWAIN documentation implies that there  *  is TWAIN support available on Macintosh, I neither have a   *  Macintosh nor the interest in porting this.  If anyone else  *  has an interest, consult www.twain.org for more information on  *  interfacing to TWAIN.  *  * Known problems:  * - Multiple image transfers will hang the plug-in.  The current  *   configuration compiles with a maximum of single image transfers.  */
end_comment

begin_comment
comment|/*   * Revision history  *  (02/07/99)  v0.1   First working version (internal)  *  (02/09/99)  v0.2   First release to anyone other than myself  *  (02/15/99)  v0.3   Added image dump and read support for debugging  *  (03/31/99)  v0.5   Added support for multi-byte samples and paletted   *                     images.  */
end_comment

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_comment
comment|/* Needed when compiling with gcc */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_include
include|#
directive|include
file|<stdarg.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_include
include|#
directive|include
file|"tw_util.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|_DEBUG
end_ifdef

begin_include
include|#
directive|include
file|"tw_func.h"
end_include

begin_decl_stmt
DECL|variable|logFile
name|FILE
modifier|*
name|logFile
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|_DEBUG
end_ifdef

begin_comment
comment|/*  * LogMessage  */
end_comment

begin_function
name|void
DECL|function|LogMessage (char * format,...)
name|LogMessage
parameter_list|(
name|char
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|time_t
name|time_of_day
decl_stmt|;
name|char
modifier|*
name|ctime_string
decl_stmt|;
comment|/* Open the log file as necessary */
if|if
condition|(
operator|!
name|logFile
condition|)
name|logFile
operator|=
name|fopen
argument_list|(
literal|"c:\\twain.log"
argument_list|,
literal|"w"
argument_list|)
expr_stmt|;
name|time_of_day
operator|=
name|time
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|ctime_string
operator|=
name|ctime
argument_list|(
operator|&
name|time_of_day
argument_list|)
expr_stmt|;
name|ctime_string
index|[
literal|19
index|]
operator|=
literal|'\0'
expr_stmt|;
name|fprintf
argument_list|(
name|logFile
argument_list|,
literal|"[%s] "
argument_list|,
operator|(
name|ctime_string
operator|+
literal|11
operator|)
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|vfprintf
argument_list|(
name|logFile
argument_list|,
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|fflush
argument_list|(
name|logFile
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * LogLastWinError  *  * Log the last Windows error as returned by  * GetLastError.  */
end_comment

begin_function
name|void
DECL|function|LogLastWinError (void)
name|LogLastWinError
parameter_list|(
name|void
parameter_list|)
block|{
name|LPVOID
name|lpMsgBuf
decl_stmt|;
name|FormatMessage
argument_list|(
name|FORMAT_MESSAGE_ALLOCATE_BUFFER
operator||
name|FORMAT_MESSAGE_FROM_SYSTEM
operator||
name|FORMAT_MESSAGE_IGNORE_INSERTS
argument_list|,
name|NULL
argument_list|,
name|GetLastError
argument_list|()
argument_list|,
name|MAKELANGID
argument_list|(
name|LANG_NEUTRAL
argument_list|,
name|SUBLANG_DEFAULT
argument_list|)
argument_list|,
comment|/* Default language */
operator|(
name|LPTSTR
operator|)
operator|&
name|lpMsgBuf
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"%s\n"
argument_list|,
name|lpMsgBuf
argument_list|)
expr_stmt|;
comment|/* Free the buffer. */
name|LocalFree
argument_list|(
name|lpMsgBuf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|logBegin (pTW_IMAGEINFO imageInfo,void * clientData)
name|logBegin
parameter_list|(
name|pTW_IMAGEINFO
name|imageInfo
parameter_list|,
name|void
modifier|*
name|clientData
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
name|char
name|buffer
index|[
literal|256
index|]
decl_stmt|;
name|LogMessage
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"*************************************\n"
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"Image transfer begin:\n"
argument_list|)
expr_stmt|;
comment|/*	LogMessage("\tClient data: %s\n", (char *) clientData); */
comment|/* Log the image information */
name|LogMessage
argument_list|(
literal|"Image information:\n"
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tXResolution: %f\n"
argument_list|,
name|FIX32ToFloat
argument_list|(
name|imageInfo
operator|->
name|XResolution
argument_list|)
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tYResolution: %f\n"
argument_list|,
name|FIX32ToFloat
argument_list|(
name|imageInfo
operator|->
name|YResolution
argument_list|)
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tImageWidth: %d\n"
argument_list|,
name|imageInfo
operator|->
name|ImageWidth
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tImageLength: %d\n"
argument_list|,
name|imageInfo
operator|->
name|ImageLength
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tSamplesPerPixel: %d\n"
argument_list|,
name|imageInfo
operator|->
name|SamplesPerPixel
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|buffer
argument_list|,
literal|"\tBitsPerSample: {"
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|8
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|imageInfo
operator|->
name|BitsPerSample
index|[
name|i
index|]
condition|)
name|strcat
argument_list|(
name|buffer
argument_list|,
literal|"1"
argument_list|)
expr_stmt|;
else|else
name|strcat
argument_list|(
name|buffer
argument_list|,
literal|"0"
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|!=
literal|7
condition|)
name|strcat
argument_list|(
name|buffer
argument_list|,
literal|","
argument_list|)
expr_stmt|;
block|}
name|LogMessage
argument_list|(
literal|"%s}\n"
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tBitsPerPixel: %d\n"
argument_list|,
name|imageInfo
operator|->
name|BitsPerPixel
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tPlanar: %s\n"
argument_list|,
operator|(
name|imageInfo
operator|->
name|Planar
condition|?
literal|"TRUE"
else|:
literal|"FALSE"
operator|)
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tPixelType: %d\n"
argument_list|,
name|imageInfo
operator|->
name|PixelType
argument_list|)
expr_stmt|;
comment|/* Compression */
block|}
end_function

begin_function
name|void
DECL|function|logData (pTW_IMAGEINFO imageInfo,pTW_IMAGEMEMXFER imageMemXfer,void * clientData)
name|logData
parameter_list|(
name|pTW_IMAGEINFO
name|imageInfo
parameter_list|,
name|pTW_IMAGEMEMXFER
name|imageMemXfer
parameter_list|,
name|void
modifier|*
name|clientData
parameter_list|)
block|{
name|LogMessage
argument_list|(
literal|"Image transfer callback called:\n"
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tClient data: %s\n"
argument_list|,
operator|(
name|char
operator|*
operator|)
name|clientData
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"Memory block transferred:\n"
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tBytesPerRow = %d\n"
argument_list|,
name|imageMemXfer
operator|->
name|BytesPerRow
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tColumns = %d\n"
argument_list|,
name|imageMemXfer
operator|->
name|Columns
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tRows = %d\n"
argument_list|,
name|imageMemXfer
operator|->
name|Rows
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tXOffset = %d\n"
argument_list|,
name|imageMemXfer
operator|->
name|XOffset
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tYOffset = %d\n"
argument_list|,
name|imageMemXfer
operator|->
name|YOffset
argument_list|)
expr_stmt|;
name|LogMessage
argument_list|(
literal|"\tBytesWritten = %d\n"
argument_list|,
name|imageMemXfer
operator|->
name|BytesWritten
argument_list|)
expr_stmt|;
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_comment
comment|/*  * LogMessage  */
end_comment

begin_function
name|void
DECL|function|LogMessage (char * format,...)
name|LogMessage
parameter_list|(
name|char
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{ }
end_function

begin_comment
comment|/*  * LogLastWinError  *  * Log the last Windows error as returned by  * GetLastError.  */
end_comment

begin_function
name|void
DECL|function|LogLastWinError (void)
name|LogLastWinError
parameter_list|(
name|void
parameter_list|)
block|{ }
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* DEBUG */
end_comment

end_unit

