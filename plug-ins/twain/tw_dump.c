begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * TWAIN Plug-in  * Copyright (C) 1999 Craig Setera  * Craig Setera<setera@home.com>  * 03/31/1999  *  * Updated for Mac OS X support  * Brion Vibber<brion@pobox.com>  * 07/22/2004  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  *  * Based on (at least) the following plug-ins:  * Screenshot  * GIF  * Randomize  *  * Any suggestions, bug-reports or patches are welcome.  *  * This plug-in interfaces to the TWAIN support library in order  * to capture images from TWAIN devices directly into GIMP images.  * The plug-in is capable of acquiring the following type of  * images:  * - B/W (1 bit images translated to grayscale B/W)  * - Grayscale up to 16 bits per pixel  * - RGB up to 16 bits per sample (24, 30, 36, etc.)  * - Paletted images (both Gray and RGB)  *  * Prerequisites:  * Should compile and run on both Win32 and Mac OS X 10.3 (possibly  * also on 10.2).  *  * Known problems:  * - Multiple image transfers will hang the plug-in.  The current  *   configuration compiles with a maximum of single image transfers.  * - On Mac OS X, canceling doesn't always close things out fully.  * - Epson TWAIN driver on Mac OS X crashes the plugin when scanning.  */
end_comment

begin_comment
comment|/*  * Revision history  *  (02/07/99)  v0.1   First working version (internal)  *  (02/09/99)  v0.2   First release to anyone other than myself  *  (02/15/99)  v0.3   Added image dump and read support for debugging  *  (03/31/99)  v0.5   Added support for multi-byte samples and paletted  *                     images.  *  (07/23/04)  v0.6   Added Mac OS X support.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"tw_dump.h"
end_include

begin_include
include|#
directive|include
file|"tw_func.h"
end_include

begin_include
include|#
directive|include
file|"tw_util.h"
end_include

begin_comment
comment|/* File variables */
end_comment

begin_decl_stmt
DECL|variable|outputFile
specifier|static
name|FILE
modifier|*
name|outputFile
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|pTW_SESSION
name|twSession
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * dumpPreTransferCallback  *  * This callback function is called before any images  * are transferred.  Set up the one time only stuff.  */
end_comment

begin_function
name|void
DECL|function|dumpPreTransferCallback (void * clientData)
name|dumpPreTransferCallback
parameter_list|(
name|void
modifier|*
name|clientData
parameter_list|)
block|{
comment|/* Open our output file... Not settable... Always    * write to the root directory.  Simplistic, but    * gets the job done.    */
name|outputFile
operator|=
name|g_fopen
argument_list|(
name|DUMP_FILE
argument_list|,
literal|"wb"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * dumpBeginTransferCallback  *  * The following function is called at the beginning  * of each image transfer.  */
end_comment

begin_function
name|int
DECL|function|dumpBeginTransferCallback (pTW_IMAGEINFO imageInfo,void * clientData)
name|dumpBeginTransferCallback
parameter_list|(
name|pTW_IMAGEINFO
name|imageInfo
parameter_list|,
name|void
modifier|*
name|clientData
parameter_list|)
block|{
name|logBegin
argument_list|(
name|imageInfo
argument_list|,
name|clientData
argument_list|)
expr_stmt|;
comment|/* Dump the image information */
name|fwrite
argument_list|(
operator|(
name|void
operator|*
operator|)
name|imageInfo
argument_list|,
sizeof|sizeof
argument_list|(
name|TW_IMAGEINFO
argument_list|)
argument_list|,
literal|1
argument_list|,
name|outputFile
argument_list|)
expr_stmt|;
comment|/* Keep going */
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  * dumpDataTransferCallback  *  * The following function is called for each memory  * block that is transferred from the data source.  */
end_comment

begin_function
name|int
DECL|function|dumpDataTransferCallback (pTW_IMAGEINFO imageInfo,pTW_IMAGEMEMXFER imageMemXfer,void * clientData)
name|dumpDataTransferCallback
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
name|int
name|flag
init|=
literal|1
decl_stmt|;
name|logData
argument_list|(
name|imageInfo
argument_list|,
name|imageMemXfer
argument_list|,
name|clientData
argument_list|)
expr_stmt|;
comment|/* Write a flag that says that this is a data packet */
name|fwrite
argument_list|(
operator|(
name|void
operator|*
operator|)
operator|&
name|flag
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|,
literal|1
argument_list|,
name|outputFile
argument_list|)
expr_stmt|;
comment|/* Dump the memory information */
name|fwrite
argument_list|(
operator|(
name|void
operator|*
operator|)
name|imageMemXfer
argument_list|,
sizeof|sizeof
argument_list|(
name|TW_IMAGEMEMXFER
argument_list|)
argument_list|,
literal|1
argument_list|,
name|outputFile
argument_list|)
expr_stmt|;
name|fwrite
argument_list|(
operator|(
name|void
operator|*
operator|)
name|imageMemXfer
operator|->
name|Memory
operator|.
name|TheMem
argument_list|,
literal|1
argument_list|,
name|imageMemXfer
operator|->
name|BytesWritten
argument_list|,
name|outputFile
argument_list|)
expr_stmt|;
comment|/* Keep going */
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  * dumpEndTransferCallback  *  * The following function is called at the end of the  * image transfer.  The caller will be handed  * the image transfer completion state.  The  * following values (defined in twain.h) are  * possible:  *  * TWRC_XFERDONE  *  The transfer completed successfully  * TWRC_CANCEL  *  The transfer was completed by the user  * TWRC_FAILURE  *  The transfer failed.  */
end_comment

begin_function
name|int
DECL|function|dumpEndTransferCallback (int completionState,int pendingCount,void * clientData)
name|dumpEndTransferCallback
parameter_list|(
name|int
name|completionState
parameter_list|,
name|int
name|pendingCount
parameter_list|,
name|void
modifier|*
name|clientData
parameter_list|)
block|{
name|int
name|flag
init|=
literal|0
decl_stmt|;
comment|/* Write a flag that says that this is a data packet */
name|fwrite
argument_list|(
operator|(
name|void
operator|*
operator|)
operator|&
name|flag
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|,
literal|1
argument_list|,
name|outputFile
argument_list|)
expr_stmt|;
comment|/* Write the necessary data */
name|fwrite
argument_list|(
operator|&
name|completionState
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|,
literal|1
argument_list|,
name|outputFile
argument_list|)
expr_stmt|;
name|fwrite
argument_list|(
operator|&
name|pendingCount
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|,
literal|1
argument_list|,
name|outputFile
argument_list|)
expr_stmt|;
comment|/* Only ever transfer a single image */
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  * dumpPostTransferCallback  *  * This callback function will be called  * after all possible images have been  * transferred.  */
end_comment

begin_function
name|void
DECL|function|dumpPostTransferCallback (int pendingCount,void * clientData)
name|dumpPostTransferCallback
parameter_list|(
name|int
name|pendingCount
parameter_list|,
name|void
modifier|*
name|clientData
parameter_list|)
block|{
name|char
name|buffer
index|[
literal|128
index|]
decl_stmt|;
comment|/* Shut things down. */
if|if
condition|(
name|pendingCount
operator|!=
literal|0
condition|)
name|cancelPendingTransfers
argument_list|(
name|twSession
argument_list|)
expr_stmt|;
comment|/* This will close the datasource and datasource    * manager.  Then the message queue will be shut    * down and the run() procedure will finally be    * able to finish.    */
name|disableDS
argument_list|(
name|twSession
argument_list|)
expr_stmt|;
name|closeDS
argument_list|(
name|twSession
argument_list|)
expr_stmt|;
name|closeDSM
argument_list|(
name|twSession
argument_list|)
expr_stmt|;
comment|/* Close the dump file */
name|fclose
argument_list|(
name|outputFile
argument_list|)
expr_stmt|;
comment|/* Tell the user */
name|sprintf
argument_list|(
name|buffer
argument_list|,
literal|"Image dumped to file %s\n"
argument_list|,
name|DUMP_FILE
argument_list|)
expr_stmt|;
name|gimp_message
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
comment|/* Post a message to close up the application */
name|twainQuitApplication
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * readDumpedImage  *  * Get a previously dumped image.  */
end_comment

begin_function
DECL|function|readDumpedImage (pTW_SESSION twSession)
name|void
name|readDumpedImage
parameter_list|(
name|pTW_SESSION
name|twSession
parameter_list|)
block|{
name|int
name|moreData
decl_stmt|;
name|int
name|completionState
decl_stmt|;
name|int
name|pendingCount
decl_stmt|;
name|TW_IMAGEINFO
name|imageInfo
decl_stmt|;
name|TW_IMAGEMEMXFER
name|imageMemXfer
decl_stmt|;
comment|/* Open our output file... Not settable... Always    * write to the root directory.  Simplistic, but    * gets the job done.    */
name|FILE
modifier|*
name|inputFile
init|=
name|g_fopen
argument_list|(
name|DUMP_FILE
argument_list|,
literal|"rb"
argument_list|)
decl_stmt|;
comment|/*    * Inform our application that we are getting ready    * to transfer images.    */
call|(
modifier|*
name|twSession
operator|->
name|transferFunctions
operator|->
name|preTxfrCb
call|)
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
comment|/* Read the image information */
name|fread
argument_list|(
operator|(
name|void
operator|*
operator|)
operator|&
name|imageInfo
argument_list|,
sizeof|sizeof
argument_list|(
name|TW_IMAGEINFO
argument_list|)
argument_list|,
literal|1
argument_list|,
name|inputFile
argument_list|)
expr_stmt|;
comment|/* Call the begin transfer callback */
if|if
condition|(
operator|!
call|(
modifier|*
name|twSession
operator|->
name|transferFunctions
operator|->
name|txfrBeginCb
call|)
argument_list|(
operator|&
name|imageInfo
argument_list|,
name|twSession
operator|->
name|clientData
argument_list|)
condition|)
return|return;
comment|/* Read all of the data packets */
name|fread
argument_list|(
operator|(
name|void
operator|*
operator|)
operator|&
name|moreData
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|,
literal|1
argument_list|,
name|inputFile
argument_list|)
expr_stmt|;
while|while
condition|(
name|moreData
condition|)
block|{
comment|/* Read the memory information */
name|fread
argument_list|(
operator|(
name|void
operator|*
operator|)
operator|&
name|imageMemXfer
argument_list|,
sizeof|sizeof
argument_list|(
name|TW_IMAGEMEMXFER
argument_list|)
argument_list|,
literal|1
argument_list|,
name|inputFile
argument_list|)
expr_stmt|;
name|imageMemXfer
operator|.
name|Memory
operator|.
name|TheMem
operator|=
operator|(
name|TW_MEMREF
operator|)
name|g_malloc
argument_list|(
name|imageMemXfer
operator|.
name|BytesWritten
argument_list|)
expr_stmt|;
name|fread
argument_list|(
operator|(
name|void
operator|*
operator|)
name|imageMemXfer
operator|.
name|Memory
operator|.
name|TheMem
argument_list|,
literal|1
argument_list|,
name|imageMemXfer
operator|.
name|BytesWritten
argument_list|,
name|inputFile
argument_list|)
expr_stmt|;
comment|/* Call the data transfer callback function */
if|if
condition|(
operator|!
call|(
modifier|*
name|twSession
operator|->
name|transferFunctions
operator|->
name|txfrDataCb
call|)
argument_list|(
operator|&
name|imageInfo
argument_list|,
operator|&
name|imageMemXfer
argument_list|,
name|twSession
operator|->
name|clientData
argument_list|)
condition|)
return|return;
comment|/* Clean up the memory */
name|g_free
argument_list|(
name|imageMemXfer
operator|.
name|Memory
operator|.
name|TheMem
argument_list|)
expr_stmt|;
comment|/* Check for continuation */
name|fread
argument_list|(
operator|(
name|void
operator|*
operator|)
operator|&
name|moreData
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|,
literal|1
argument_list|,
name|inputFile
argument_list|)
expr_stmt|;
block|}
comment|/* Grab the final information */
name|fread
argument_list|(
operator|&
name|completionState
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|,
literal|1
argument_list|,
name|inputFile
argument_list|)
expr_stmt|;
name|fread
argument_list|(
operator|&
name|pendingCount
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|,
literal|1
argument_list|,
name|inputFile
argument_list|)
expr_stmt|;
if|if
condition|(
name|twSession
operator|->
name|transferFunctions
operator|->
name|txfrEndCb
condition|)
call|(
modifier|*
name|twSession
operator|->
name|transferFunctions
operator|->
name|txfrEndCb
call|)
argument_list|(
name|completionState
argument_list|,
literal|0
argument_list|,
name|twSession
operator|->
name|clientData
argument_list|)
expr_stmt|;
comment|/* Post a message to close up the application */
name|twainQuitApplication
argument_list|()
expr_stmt|;
block|}
end_function

end_unit

