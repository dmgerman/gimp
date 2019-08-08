begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * TWAIN Plug-in  * Copyright (C) 1999 Craig Setera  * Craig Setera<setera@home.com>  * 03/31/1999  *  * Updated for Mac OS X support  * Brion Vibber<brion@pobox.com>  * 07/22/2004  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*  * Windows platform-specific code  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"tw_platform.h"
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

begin_include
include|#
directive|include
file|"tw_local.h"
end_include

begin_function_decl
name|LRESULT
name|CALLBACK
name|WndProc
parameter_list|(
name|HWND
parameter_list|,
name|UINT
parameter_list|,
name|WPARAM
parameter_list|,
name|LPARAM
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|twainMessageLoop
parameter_list|(
name|pTW_SESSION
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|TwainProcessMessage
parameter_list|(
name|LPMSG
name|lpMsg
parameter_list|,
name|pTW_SESSION
name|twSession
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|GimpPlugInInfo
name|PLUG_IN_INFO
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|extern
name|pTW_SESSION
name|initializeTwain
parameter_list|()
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|_DEBUG
end_ifdef

begin_function_decl
specifier|extern
name|void
name|setRunMode
parameter_list|(
name|char
modifier|*
name|argv
index|[]
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|APP_NAME
define|#
directive|define
name|APP_NAME
value|"TWAIN"
end_define

begin_define
DECL|macro|SHOW_WINDOW
define|#
directive|define
name|SHOW_WINDOW
value|0
end_define

begin_define
DECL|macro|WM_TRANSFER_IMAGE
define|#
directive|define
name|WM_TRANSFER_IMAGE
value|(WM_USER + 100)
end_define

begin_comment
comment|/* main bits */
end_comment

begin_decl_stmt
DECL|variable|hwnd
specifier|static
name|HWND
name|hwnd
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|hInst
specifier|static
name|HINSTANCE
name|hInst
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Storage for the DLL handle */
end_comment

begin_decl_stmt
DECL|variable|hDLL
specifier|static
name|HINSTANCE
name|hDLL
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Storage for the entry point into the DSM */
end_comment

begin_decl_stmt
DECL|variable|dsmEntryPoint
specifier|static
name|DSMENTRYPROC
name|dsmEntryPoint
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * callDSM  *  * Call the specified function on the data source manager.  */
end_comment

begin_function
name|TW_UINT16
DECL|function|callDSM (pTW_IDENTITY pOrigin,pTW_IDENTITY pDest,TW_UINT32 DG,TW_UINT16 DAT,TW_UINT16 MSG,TW_MEMREF pData)
name|callDSM
parameter_list|(
name|pTW_IDENTITY
name|pOrigin
parameter_list|,
name|pTW_IDENTITY
name|pDest
parameter_list|,
name|TW_UINT32
name|DG
parameter_list|,
name|TW_UINT16
name|DAT
parameter_list|,
name|TW_UINT16
name|MSG
parameter_list|,
name|TW_MEMREF
name|pData
parameter_list|)
block|{
comment|/* Call the function */
return|return
call|(
modifier|*
name|dsmEntryPoint
call|)
argument_list|(
name|pOrigin
argument_list|,
name|pDest
argument_list|,
name|DG
argument_list|,
name|DAT
argument_list|,
name|MSG
argument_list|,
name|pData
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  * twainIsAvailable  *  * Return boolean indicating whether TWAIN is available  */
end_comment

begin_function
name|int
DECL|function|twainIsAvailable (void)
name|twainIsAvailable
parameter_list|(
name|void
parameter_list|)
block|{
comment|/* Already loaded? */
if|if
condition|(
name|dsmEntryPoint
condition|)
block|{
return|return
name|TRUE
return|;
block|}
comment|/* Attempt to load the library */
name|hDLL
operator|=
name|LoadLibrary
argument_list|(
name|TWAIN_DLL_NAME
argument_list|)
expr_stmt|;
if|if
condition|(
name|hDLL
operator|==
name|NULL
condition|)
return|return
name|FALSE
return|;
comment|/* Look up the entry point for use */
name|dsmEntryPoint
operator|=
operator|(
name|DSMENTRYPROC
operator|)
name|GetProcAddress
argument_list|(
name|hDLL
argument_list|,
literal|"DSM_Entry"
argument_list|)
expr_stmt|;
if|if
condition|(
name|dsmEntryPoint
operator|==
name|NULL
condition|)
return|return
name|FALSE
return|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|TW_HANDLE
DECL|function|twainAllocHandle (size_t size)
name|twainAllocHandle
parameter_list|(
name|size_t
name|size
parameter_list|)
block|{
return|return
name|GlobalAlloc
argument_list|(
name|GHND
argument_list|,
name|size
argument_list|)
return|;
block|}
end_function

begin_function
name|TW_MEMREF
DECL|function|twainLockHandle (TW_HANDLE handle)
name|twainLockHandle
parameter_list|(
name|TW_HANDLE
name|handle
parameter_list|)
block|{
return|return
name|GlobalLock
argument_list|(
name|handle
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|twainUnlockHandle (TW_HANDLE handle)
name|twainUnlockHandle
parameter_list|(
name|TW_HANDLE
name|handle
parameter_list|)
block|{
name|GlobalUnlock
argument_list|(
name|handle
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|twainFreeHandle (TW_HANDLE handle)
name|twainFreeHandle
parameter_list|(
name|TW_HANDLE
name|handle
parameter_list|)
block|{
name|GlobalFree
argument_list|(
name|handle
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|twainSetupCallback (pTW_SESSION twSession)
name|twainSetupCallback
parameter_list|(
name|pTW_SESSION
name|twSession
parameter_list|)
block|{
comment|/* Callbacks go through the window messaging system */
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  * unloadTwainLibrary  *  * Unload the TWAIN dynamic link library  */
end_comment

begin_function
name|int
DECL|function|unloadTwainLibrary (pTW_SESSION twSession)
name|unloadTwainLibrary
parameter_list|(
name|pTW_SESSION
name|twSession
parameter_list|)
block|{
comment|/* Explicitly free the SM library */
if|if
condition|(
name|hDLL
condition|)
block|{
name|FreeLibrary
argument_list|(
name|hDLL
argument_list|)
expr_stmt|;
name|hDLL
operator|=
name|NULL
expr_stmt|;
block|}
comment|/* the data source id will no longer be valid after    * twain is killed.  If the id is left around the    * data source can not be found or opened 	 */
name|DS_IDENTITY
argument_list|(
name|twSession
argument_list|)
operator|->
name|Id
operator|=
literal|0
expr_stmt|;
comment|/* We are now back at state 1 */
name|twSession
operator|->
name|twainState
operator|=
literal|1
expr_stmt|;
name|LogMessage
argument_list|(
literal|"Source Manager successfully closed\n"
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  * TwainProcessMessage  *  * Returns TRUE if the application should process message as usual.  * Returns FALSE if the application should skip processing of this message  */
end_comment

begin_function
name|int
DECL|function|TwainProcessMessage (LPMSG lpMsg,pTW_SESSION twSession)
name|TwainProcessMessage
parameter_list|(
name|LPMSG
name|lpMsg
parameter_list|,
name|pTW_SESSION
name|twSession
parameter_list|)
block|{
name|TW_EVENT
name|twEvent
decl_stmt|;
name|twSession
operator|->
name|twRC
operator|=
name|TWRC_NOTDSEVENT
expr_stmt|;
comment|/* Only ask Source Manager to process event if there is a Source connected. */
if|if
condition|(
name|DSM_IS_OPEN
argument_list|(
name|twSession
argument_list|)
operator|&&
name|DS_IS_OPEN
argument_list|(
name|twSession
argument_list|)
condition|)
block|{
comment|/* 		 * A Source provides a modeless dialog box as its user interface. 		 * The following call relays Windows messages down to the Source's 		 * UI that were intended for its dialog box.  It also retrieves TWAIN 		 * messages sent from the Source to our Application. 		 */
name|twEvent
operator|.
name|pEvent
operator|=
operator|(
name|TW_MEMREF
operator|)
name|lpMsg
expr_stmt|;
name|twSession
operator|->
name|twRC
operator|=
name|callDSM
argument_list|(
name|APP_IDENTITY
argument_list|(
name|twSession
argument_list|)
argument_list|,
name|DS_IDENTITY
argument_list|(
name|twSession
argument_list|)
argument_list|,
name|DG_CONTROL
argument_list|,
name|DAT_EVENT
argument_list|,
name|MSG_PROCESSEVENT
argument_list|,
operator|(
name|TW_MEMREF
operator|)
operator|&
name|twEvent
argument_list|)
expr_stmt|;
comment|/* Check the return code */
if|if
condition|(
name|twSession
operator|->
name|twRC
operator|==
name|TWRC_NOTDSEVENT
condition|)
block|{
return|return
name|FALSE
return|;
block|}
comment|/* Process the message as necessary */
name|processTwainMessage
argument_list|(
name|twEvent
operator|.
name|TWMessage
argument_list|,
name|twSession
argument_list|)
expr_stmt|;
block|}
comment|/* tell the caller what happened */
return|return
operator|(
name|twSession
operator|->
name|twRC
operator|==
name|TWRC_DSEVENT
operator|)
return|;
block|}
end_function

begin_comment
comment|/*  * twainMessageLoop  *  * Process Win32 window messages and provide special handling  * of TWAIN specific messages.  This loop will not exit until  * the application exits.  */
end_comment

begin_function
name|int
DECL|function|twainMessageLoop (pTW_SESSION twSession)
name|twainMessageLoop
parameter_list|(
name|pTW_SESSION
name|twSession
parameter_list|)
block|{
name|MSG
name|msg
decl_stmt|;
while|while
condition|(
name|GetMessage
argument_list|(
operator|&
name|msg
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
condition|)
block|{
if|if
condition|(
name|DS_IS_CLOSED
argument_list|(
name|twSession
argument_list|)
operator|||
operator|!
name|TwainProcessMessage
argument_list|(
operator|&
name|msg
argument_list|,
name|twSession
argument_list|)
condition|)
block|{
name|TranslateMessage
argument_list|(
operator|(
name|LPMSG
operator|)
operator|&
name|msg
argument_list|)
expr_stmt|;
name|DispatchMessage
argument_list|(
operator|&
name|msg
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|msg
operator|.
name|wParam
return|;
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
DECL|function|twainQuitApplication ()
name|void
name|twainQuitApplication
parameter_list|()
block|{
name|PostQuitMessage
argument_list|(
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/******************************************************************  * Win32 entry point and setup...  ******************************************************************/
end_comment

begin_comment
comment|/*  * WinMain  *  * The standard gimp entry point won't quite cut it for  * this plug-in.  This plug-in requires creation of a  * standard Win32 window (hidden) in order to receive  * and process window messages on behalf of the TWAIN  * datasource.  */
end_comment

begin_function
name|int
name|APIENTRY
DECL|function|WinMain (HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
name|WinMain
parameter_list|(
name|HINSTANCE
name|hInstance
parameter_list|,
name|HINSTANCE
name|hPrevInstance
parameter_list|,
name|LPSTR
name|lpCmdLine
parameter_list|,
name|int
name|nCmdShow
parameter_list|)
block|{
comment|/*    * Normally, we would do all of the Windows-ish set up of    * the window classes and stuff here in WinMain.  But,    * the only time we really need the window and message    * queues is during the plug-in run.  So, all of that will    * be done during run().  This avoids all of the Windows    * setup stuff for the query().  Stash the instance handle now    * so it is available from the run() procedure.    */
name|hInst
operator|=
name|hInstance
expr_stmt|;
ifdef|#
directive|ifdef
name|_DEBUG
comment|/* When in debug version, we allow different run modes...    * make sure that it is correctly set.    */
name|setRunMode
argument_list|(
name|__argv
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* _DEBUG */
comment|/*    * Now, call gimp_main_legacy... This is what the MAIN() macro    * would usually do.    */
return|return
name|gimp_main_legacy
argument_list|(
operator|&
name|PLUG_IN_INFO
argument_list|,
name|__argc
argument_list|,
name|__argv
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  * main  *  * allow to build as console app as well  */
end_comment

begin_function
DECL|function|main (int argc,char * argv[])
name|int
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
name|argv
index|[]
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|_DEBUG
comment|/* When in debug version, we allow different run modes...    * make sure that it is correctly set.    */
name|setRunMode
argument_list|(
name|__argv
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* _DEBUG */
comment|/*    * Now, call gimp_main_legacy... This is what the MAIN() macro    * would usually do.    */
return|return
name|gimp_main_legacy
argument_list|(
operator|&
name|PLUG_IN_INFO
argument_list|,
name|__argc
argument_list|,
name|__argv
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  * InitApplication  *  * Initialize window data and register the window class  */
end_comment

begin_function
name|BOOL
DECL|function|InitApplication (HINSTANCE hInstance)
name|InitApplication
parameter_list|(
name|HINSTANCE
name|hInstance
parameter_list|)
block|{
name|WNDCLASS
name|wc
decl_stmt|;
name|BOOL
name|retValue
decl_stmt|;
comment|/*    * Fill in window class structure with parameters to describe    * the main window.    */
name|wc
operator|.
name|style
operator|=
name|CS_HREDRAW
operator||
name|CS_VREDRAW
expr_stmt|;
name|wc
operator|.
name|lpfnWndProc
operator|=
operator|(
name|WNDPROC
operator|)
name|WndProc
expr_stmt|;
name|wc
operator|.
name|cbClsExtra
operator|=
literal|0
expr_stmt|;
name|wc
operator|.
name|cbWndExtra
operator|=
literal|0
expr_stmt|;
name|wc
operator|.
name|hInstance
operator|=
name|hInstance
expr_stmt|;
name|wc
operator|.
name|hIcon
operator|=
name|LoadIcon
argument_list|(
name|NULL
argument_list|,
name|IDI_APPLICATION
argument_list|)
expr_stmt|;
name|wc
operator|.
name|hCursor
operator|=
name|LoadCursor
argument_list|(
name|NULL
argument_list|,
name|IDC_ARROW
argument_list|)
expr_stmt|;
name|wc
operator|.
name|hbrBackground
operator|=
call|(
name|HBRUSH
call|)
argument_list|(
name|COLOR_WINDOW
operator|+
literal|1
argument_list|)
expr_stmt|;
name|wc
operator|.
name|lpszClassName
operator|=
name|APP_NAME
expr_stmt|;
name|wc
operator|.
name|lpszMenuName
operator|=
name|NULL
expr_stmt|;
comment|/* Register the window class and stash success/failure code. */
name|retValue
operator|=
name|RegisterClass
argument_list|(
operator|&
name|wc
argument_list|)
expr_stmt|;
comment|/* Log error */
if|if
condition|(
operator|!
name|retValue
condition|)
name|LogLastWinError
argument_list|()
expr_stmt|;
return|return
name|retValue
return|;
block|}
end_function

begin_comment
comment|/*  * InitInstance  *  * Create the main window for the application.  Used to  * interface with the TWAIN datasource.  */
end_comment

begin_function
name|BOOL
DECL|function|InitInstance (HINSTANCE hInstance,int nCmdShow,pTW_SESSION twSession)
name|InitInstance
parameter_list|(
name|HINSTANCE
name|hInstance
parameter_list|,
name|int
name|nCmdShow
parameter_list|,
name|pTW_SESSION
name|twSession
parameter_list|)
block|{
comment|/* Create our window */
name|hwnd
operator|=
name|CreateWindow
argument_list|(
name|APP_NAME
argument_list|,
name|APP_NAME
argument_list|,
name|WS_OVERLAPPEDWINDOW
argument_list|,
name|CW_USEDEFAULT
argument_list|,
literal|0
argument_list|,
name|CW_USEDEFAULT
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|hInstance
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|hwnd
condition|)
block|{
return|return
operator|(
name|FALSE
operator|)
return|;
block|}
comment|/* Register our window handle with the TWAIN    * support.    */
name|registerWindowHandle
argument_list|(
name|twSession
argument_list|,
name|hwnd
argument_list|)
expr_stmt|;
comment|/* Schedule the image transfer by posting a message */
name|PostMessage
argument_list|(
name|hwnd
argument_list|,
name|WM_TRANSFER_IMAGE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|ShowWindow
argument_list|(
name|hwnd
argument_list|,
name|nCmdShow
argument_list|)
expr_stmt|;
name|UpdateWindow
argument_list|(
name|hwnd
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  * twainWinMain  *  * This is the function that represents the code that  * would normally reside in WinMain (see above).  This  * function will get called during run() in order to set  * up the windowing environment necessary for TWAIN to  * operate.  */
end_comment

begin_function
name|int
DECL|function|twainMain ()
name|twainMain
parameter_list|()
block|{
comment|/* Initialize the twain information */
name|pTW_SESSION
name|twSession
init|=
name|initializeTwain
argument_list|()
decl_stmt|;
comment|/* Perform instance initialization */
if|if
condition|(
operator|!
name|InitApplication
argument_list|(
name|hInst
argument_list|)
condition|)
return|return
operator|(
name|FALSE
operator|)
return|;
comment|/* Perform application initialization */
if|if
condition|(
operator|!
name|InitInstance
argument_list|(
name|hInst
argument_list|,
name|SHOW_WINDOW
argument_list|,
name|twSession
argument_list|)
condition|)
return|return
operator|(
name|FALSE
operator|)
return|;
comment|/*    * Call the main message processing loop...    * This call will not return until the application    * exits.    */
return|return
name|twainMessageLoop
argument_list|(
name|twSession
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  * WndProc  *  * Process window message for the main window.  */
end_comment

begin_function
name|LRESULT
name|CALLBACK
DECL|function|WndProc (HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
name|WndProc
parameter_list|(
name|HWND
name|hWnd
parameter_list|,
name|UINT
name|message
parameter_list|,
name|WPARAM
name|wParam
parameter_list|,
name|LPARAM
name|lParam
parameter_list|)
block|{
switch|switch
condition|(
name|message
condition|)
block|{
case|case
name|WM_TRANSFER_IMAGE
case|:
comment|/* Get an image */
name|scanImage
argument_list|()
expr_stmt|;
break|break;
case|case
name|WM_DESTROY
case|:
name|LogMessage
argument_list|(
literal|"Exiting application\n"
argument_list|)
expr_stmt|;
name|PostQuitMessage
argument_list|(
literal|0
argument_list|)
expr_stmt|;
break|break;
default|default:
return|return
operator|(
name|DefWindowProc
argument_list|(
name|hWnd
argument_list|,
name|message
argument_list|,
name|wParam
argument_list|,
name|lParam
argument_list|)
operator|)
return|;
block|}
return|return
literal|0
return|;
block|}
end_function

end_unit

