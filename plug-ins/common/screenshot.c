begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  *  ScreenShot plug-in  *  Copyright 1998-2000 Sven Neumann<sven@gimp.org>  *  Copyright 2003      Henrik Brix Andersen<brix@gimp.org>  *  *  Any suggestions, bug-reports or patches are very welcome.  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_if
if|#
directive|if
name|defined
argument_list|(
name|GDK_WINDOWING_X11
argument_list|)
end_if

begin_include
include|#
directive|include
file|<gdk/gdkx.h>
end_include

begin_elif
elif|#
directive|elif
name|defined
argument_list|(
name|GDK_WINDOWING_WIN32
argument_list|)
end_elif

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
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* Defines */
end_comment

begin_define
DECL|macro|PLUG_IN_NAME
define|#
directive|define
name|PLUG_IN_NAME
value|"plug_in_screenshot"
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_NATIVE_WINDOW_POINTER
end_ifdef

begin_if
if|#
directive|if
name|GLIB_SIZEOF_VOID_P
operator|!=
literal|4
end_if

begin_warning
warning|#
directive|warning
warning|window_id does not fit in PDB_INT32
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2a360e560108
block|{
DECL|member|root
name|gboolean
name|root
decl_stmt|;
DECL|member|window_id
name|guint
name|window_id
decl_stmt|;
DECL|member|delay
name|guint
name|delay
decl_stmt|;
DECL|typedef|ScreenShotValues
block|}
name|ScreenShotValues
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|shootvals
specifier|static
name|ScreenShotValues
name|shootvals
init|=
block|{
name|FALSE
block|,
comment|/* root window */
literal|0
block|,
comment|/* window ID   */
literal|0
block|,
comment|/* delay       */
block|}
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GdkNativeWindow
name|select_window
parameter_list|(
name|GdkScreen
modifier|*
name|screen
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint32
name|create_image
parameter_list|(
specifier|const
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|shoot
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|shoot_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|shoot_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|shoot_delay
parameter_list|(
name|gint32
name|delay
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|shoot_delay_callback
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Global Variables */
end_comment

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|query
block|,
comment|/* query_proc */
name|run
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* the image that will be returned */
end_comment

begin_decl_stmt
DECL|variable|image_ID
specifier|static
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|run_flag
specifier|static
name|gboolean
name|run_flag
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* the screen on which we are running */
end_comment

begin_decl_stmt
DECL|variable|cur_screen
specifier|static
name|GdkScreen
modifier|*
name|cur_screen
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* the window the user selected */
end_comment

begin_decl_stmt
DECL|variable|selected_native
specifier|static
name|GdkNativeWindow
name|selected_native
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Functions */
end_comment

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"root"
block|,
literal|"Root window { TRUE, FALSE }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"window_id"
block|,
literal|"Window id"
block|}
block|}
decl_stmt|;
specifier|static
name|GimpParamDef
name|return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Output image"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_NAME
argument_list|,
literal|"Creates a screenshot of a single window or the whole screen"
argument_list|,
literal|"After specifying some options the user selects a window and "
literal|"a time out is started. At the end of the time out the window "
literal|"is grabbed and the image is loaded into The GIMP. Alternatively "
literal|"the whole screen can be grabbed. When called non-interactively "
literal|"it may grab the root window or use the window-id passed as a parameter."
argument_list|,
literal|"Sven Neumann<sven@gimp.org>, Henrik Brix Andersen<brix@gimp.org>"
argument_list|,
literal|"1998 - 2003"
argument_list|,
literal|"v0.9.6 (2003/08/28)"
argument_list|,
name|N_
argument_list|(
literal|"<Toolbox>/File/Acquire/_Screen Shot..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|return_vals
argument_list|)
argument_list|,
name|args
argument_list|,
name|return_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
comment|/* Get the runmode from the in-parameters */
name|GimpRunMode
name|run_mode
init|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
decl_stmt|;
comment|/* status variable, use it to check for errors in invocation usually only    * during non-interactive calling    */
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
comment|/* always return at least the status to the caller. */
specifier|static
name|GimpParam
name|values
index|[
literal|2
index|]
decl_stmt|;
comment|/* initialize the return of the status */
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/* how are we running today? */
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
comment|/* Possibly retrieve data from a previous run */
name|gimp_get_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|shootvals
argument_list|)
expr_stmt|;
name|shootvals
operator|.
name|window_id
operator|=
literal|0
expr_stmt|;
comment|/* Get information from the dialog */
if|if
condition|(
operator|!
name|shoot_dialog
argument_list|()
condition|)
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparams
operator|==
literal|3
condition|)
block|{
name|shootvals
operator|.
name|root
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|shootvals
operator|.
name|window_id
operator|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|shootvals
operator|.
name|delay
operator|=
literal|0
expr_stmt|;
block|}
else|else
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
operator|!
name|gdk_init_check
argument_list|(
literal|0
argument_list|,
name|NULL
argument_list|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/* Possibly retrieve data from a previous run */
name|gimp_get_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|shootvals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
if|if
condition|(
name|shootvals
operator|.
name|delay
operator|>
literal|0
condition|)
name|shoot_delay
argument_list|(
name|shootvals
operator|.
name|delay
argument_list|)
expr_stmt|;
comment|/* Run the main function */
name|shoot
argument_list|()
expr_stmt|;
name|status
operator|=
operator|(
name|image_ID
operator|!=
operator|-
literal|1
operator|)
condition|?
name|GIMP_PDB_SUCCESS
else|:
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
comment|/* Store variable states for next run */
name|gimp_set_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|shootvals
argument_list|,
sizeof|sizeof
argument_list|(
name|ScreenShotValues
argument_list|)
argument_list|)
expr_stmt|;
comment|/* display the image */
name|gimp_display_new
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
block|}
comment|/* set return values */
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_IMAGE
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
operator|=
name|image_ID
expr_stmt|;
block|}
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Allow the user to select a window with the mouse */
end_comment

begin_function
specifier|static
name|GdkNativeWindow
DECL|function|select_window (GdkScreen * screen)
name|select_window
parameter_list|(
name|GdkScreen
modifier|*
name|screen
parameter_list|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|GDK_WINDOWING_X11
argument_list|)
comment|/* X11 specific code */
DECL|macro|MASK
define|#
directive|define
name|MASK
value|(ButtonPressMask | ButtonReleaseMask)
name|Display
modifier|*
name|x_dpy
decl_stmt|;
name|Cursor
name|x_cursor
decl_stmt|;
name|XEvent
name|x_event
decl_stmt|;
name|Window
name|x_win
decl_stmt|;
name|Window
name|x_root
decl_stmt|;
name|gint
name|x_scr
decl_stmt|;
name|gint
name|status
decl_stmt|;
name|gint
name|buttons
decl_stmt|;
name|x_dpy
operator|=
name|GDK_SCREEN_XDISPLAY
argument_list|(
name|screen
argument_list|)
expr_stmt|;
name|x_scr
operator|=
name|GDK_SCREEN_XNUMBER
argument_list|(
name|screen
argument_list|)
expr_stmt|;
name|x_win
operator|=
name|None
expr_stmt|;
name|x_root
operator|=
name|RootWindow
argument_list|(
name|x_dpy
argument_list|,
name|x_scr
argument_list|)
expr_stmt|;
name|x_cursor
operator|=
name|XCreateFontCursor
argument_list|(
name|x_dpy
argument_list|,
name|GDK_CROSSHAIR
argument_list|)
expr_stmt|;
name|buttons
operator|=
literal|0
expr_stmt|;
name|status
operator|=
name|XGrabPointer
argument_list|(
name|x_dpy
argument_list|,
name|x_root
argument_list|,
name|False
argument_list|,
name|MASK
argument_list|,
name|GrabModeSync
argument_list|,
name|GrabModeAsync
argument_list|,
name|x_root
argument_list|,
name|x_cursor
argument_list|,
name|CurrentTime
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|!=
name|GrabSuccess
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Error grabbing the pointer"
argument_list|)
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
while|while
condition|(
operator|(
name|x_win
operator|==
name|None
operator|)
operator|||
operator|(
name|buttons
operator|!=
literal|0
operator|)
condition|)
block|{
name|XAllowEvents
argument_list|(
name|x_dpy
argument_list|,
name|SyncPointer
argument_list|,
name|CurrentTime
argument_list|)
expr_stmt|;
name|XWindowEvent
argument_list|(
name|x_dpy
argument_list|,
name|x_root
argument_list|,
name|MASK
argument_list|,
operator|&
name|x_event
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|x_event
operator|.
name|type
condition|)
block|{
case|case
name|ButtonPress
case|:
if|if
condition|(
name|x_win
operator|==
name|None
condition|)
block|{
name|x_win
operator|=
name|x_event
operator|.
name|xbutton
operator|.
name|subwindow
expr_stmt|;
if|if
condition|(
name|x_win
operator|==
name|None
condition|)
name|x_win
operator|=
name|x_root
expr_stmt|;
block|}
name|buttons
operator|++
expr_stmt|;
break|break;
case|case
name|ButtonRelease
case|:
if|if
condition|(
name|buttons
operator|>
literal|0
condition|)
name|buttons
operator|--
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
block|}
block|}
name|XUngrabPointer
argument_list|(
name|x_dpy
argument_list|,
name|CurrentTime
argument_list|)
expr_stmt|;
name|XFreeCursor
argument_list|(
name|x_dpy
argument_list|,
name|x_cursor
argument_list|)
expr_stmt|;
return|return
name|x_win
return|;
elif|#
directive|elif
name|defined
argument_list|(
name|GDK_WINDOWING_WIN32
argument_list|)
comment|/* MS Windows specific code goes here (yet to be written) */
comment|/* basically the code should grab the pointer using a crosshair      cursor, allow the user to click on a window and return the      obtained HWND (as a GdkNativeWindow) - for more details consult      the X11 specific code below */
comment|/* note to self: take a look at the winsnap plug-in for example      code */
warning|#
directive|warning
warning|Win32 screenshot window chooser not implemented yet
return|return
literal|0
return|;
else|#
directive|else
comment|/* GDK_WINDOWING_WIN32 */
warning|#
directive|warning
warning|screenshot window chooser not implemented yet for this GDK backend
return|return
literal|0
return|;
endif|#
directive|endif
block|}
end_function

begin_comment
comment|/* Create a GimpImage from a GdkPixbuf */
end_comment

begin_function
specifier|static
name|gint32
DECL|function|create_image (const GdkPixbuf * pixbuf)
name|create_image
parameter_list|(
specifier|const
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|)
block|{
name|GimpPixelRgn
name|rgn
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint32
name|image
decl_stmt|;
name|gint32
name|layer
decl_stmt|;
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|gchar
modifier|*
name|comment
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|rowstride
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gboolean
name|status
decl_stmt|;
name|gchar
modifier|*
name|pixels
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|status
operator|=
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Loading Screen Shot..."
argument_list|)
argument_list|)
expr_stmt|;
name|width
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|height
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_image_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_RGB
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|_
argument_list|(
literal|"Screen Shot"
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_RGB_IMAGE
argument_list|,
literal|100
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|rowstride
operator|=
name|gdk_pixbuf_get_rowstride
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|gdk_pixbuf_get_n_channels
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|pixels
operator|=
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|bpp
operator|==
name|rgn
operator|.
name|bpp
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
argument_list|,
operator|&
name|rgn
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|src
operator|=
name|pixels
operator|+
name|rgn
operator|.
name|y
operator|*
name|rowstride
operator|+
name|rgn
operator|.
name|x
operator|*
name|bpp
expr_stmt|;
name|dest
operator|=
name|rgn
operator|.
name|data
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|rgn
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|dest
argument_list|,
name|src
argument_list|,
name|rgn
operator|.
name|w
operator|*
name|rgn
operator|.
name|bpp
argument_list|)
expr_stmt|;
name|src
operator|+=
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|rgn
operator|.
name|rowstride
expr_stmt|;
block|}
block|}
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_get_monitor_resolution
argument_list|(
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|gimp_image_set_resolution
argument_list|(
name|image
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|comment
operator|=
name|gimp_get_default_comment
argument_list|()
expr_stmt|;
if|if
condition|(
name|comment
condition|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"gimp-comment"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|g_utf8_strlen
argument_list|(
name|comment
argument_list|,
operator|-
literal|1
argument_list|)
operator|+
literal|1
argument_list|,
name|comment
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
argument_list|(
name|image_ID
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|comment
argument_list|)
expr_stmt|;
block|}
name|gimp_image_undo_enable
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|image
return|;
block|}
end_function

begin_comment
comment|/* The main ScreenShot function */
end_comment

begin_function
specifier|static
name|void
DECL|function|shoot (void)
name|shoot
parameter_list|(
name|void
parameter_list|)
block|{
name|GdkWindow
modifier|*
name|window
decl_stmt|;
name|GdkPixbuf
modifier|*
name|screenshot
decl_stmt|;
name|GdkRectangle
name|rect
decl_stmt|;
name|GdkRectangle
name|screen_rect
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/* use default screen if we are running non-interactively */
if|if
condition|(
name|cur_screen
operator|==
name|NULL
condition|)
name|cur_screen
operator|=
name|gdk_screen_get_default
argument_list|()
expr_stmt|;
name|screen_rect
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|screen_rect
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|screen_rect
operator|.
name|width
operator|=
name|gdk_screen_get_width
argument_list|(
name|cur_screen
argument_list|)
expr_stmt|;
name|screen_rect
operator|.
name|height
operator|=
name|gdk_screen_get_height
argument_list|(
name|cur_screen
argument_list|)
expr_stmt|;
if|if
condition|(
name|shootvals
operator|.
name|root
condition|)
block|{
comment|/* entire screen */
name|window
operator|=
name|gdk_screen_get_root_window
argument_list|(
name|cur_screen
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GdkDisplay
modifier|*
name|display
decl_stmt|;
name|display
operator|=
name|gdk_screen_get_display
argument_list|(
name|cur_screen
argument_list|)
expr_stmt|;
comment|/* single window */
if|if
condition|(
name|shootvals
operator|.
name|window_id
condition|)
block|{
name|window
operator|=
name|gdk_window_foreign_new_for_display
argument_list|(
name|display
argument_list|,
name|shootvals
operator|.
name|window_id
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|window
operator|=
name|gdk_window_foreign_new_for_display
argument_list|(
name|display
argument_list|,
name|selected_native
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|window
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Specified window not found"
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gdk_window_get_origin
argument_list|(
name|window
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|rect
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|rect
operator|.
name|y
operator|=
name|y
expr_stmt|;
name|gdk_drawable_get_size
argument_list|(
name|GDK_DRAWABLE
argument_list|(
name|window
argument_list|)
argument_list|,
operator|&
name|rect
operator|.
name|width
argument_list|,
operator|&
name|rect
operator|.
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gdk_rectangle_intersect
argument_list|(
operator|&
name|rect
argument_list|,
operator|&
name|screen_rect
argument_list|,
operator|&
name|rect
argument_list|)
condition|)
return|return;
name|screenshot
operator|=
name|gdk_pixbuf_get_from_drawable
argument_list|(
name|NULL
argument_list|,
name|window
argument_list|,
name|NULL
argument_list|,
name|rect
operator|.
name|x
operator|-
name|x
argument_list|,
name|rect
operator|.
name|y
operator|-
name|y
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|rect
operator|.
name|width
argument_list|,
name|rect
operator|.
name|height
argument_list|)
expr_stmt|;
name|gdk_display_beep
argument_list|(
name|gdk_screen_get_display
argument_list|(
name|cur_screen
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|screenshot
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Error obtaining Screen Shot"
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|image_ID
operator|=
name|create_image
argument_list|(
name|screenshot
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|screenshot
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  ScreenShot dialog  */
end_comment

begin_function
specifier|static
name|void
DECL|function|shoot_ok_callback (GtkWidget * widget,gpointer data)
name|shoot_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|run_flag
operator|=
name|TRUE
expr_stmt|;
comment|/* get the screen on which we are running */
name|cur_screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|shootvals
operator|.
name|root
operator|&&
operator|!
name|shootvals
operator|.
name|window_id
condition|)
name|selected_native
operator|=
name|select_window
argument_list|(
name|cur_screen
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|shoot_dialog (void)
name|shoot_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|spinner
decl_stmt|;
name|GSList
modifier|*
name|radio_group
init|=
name|NULL
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"screenshot"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  main dialog  */
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Screen Shot"
argument_list|)
argument_list|,
literal|"screenshot"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/screenshot.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|shoot_ok_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_main_quit
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
comment|/*  single window  */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Grab"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_ETCHED_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_radio_button_new_with_mnemonic
argument_list|(
name|radio_group
argument_list|,
name|_
argument_list|(
literal|"a _Single Window"
argument_list|)
argument_list|)
expr_stmt|;
name|radio_group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
operator|!
name|shootvals
operator|.
name|root
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|shootvals
operator|.
name|root
argument_list|)
expr_stmt|;
comment|/*  root window  */
name|button
operator|=
name|gtk_radio_button_new_with_mnemonic
argument_list|(
name|radio_group
argument_list|,
name|_
argument_list|(
literal|"the _Whole Screen"
argument_list|)
argument_list|)
expr_stmt|;
name|radio_group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|shootvals
operator|.
name|root
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|TRUE
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|shootvals
operator|.
name|root
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
comment|/*  with delay  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_after"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gtk_adjustment_new
argument_list|(
name|shootvals
operator|.
name|delay
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|5.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|spinner
operator|=
name|gtk_spin_button_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|spinner
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinner
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|shootvals
operator|.
name|delay
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Seconds Delay"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
return|return
name|run_flag
return|;
block|}
end_function

begin_comment
comment|/*  delay functions  */
end_comment

begin_function
name|void
DECL|function|shoot_delay (gint delay)
name|shoot_delay
parameter_list|(
name|gint
name|delay
parameter_list|)
block|{
name|g_timeout_add
argument_list|(
literal|1000
argument_list|,
name|shoot_delay_callback
argument_list|,
operator|&
name|delay
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|shoot_delay_callback (gpointer data)
name|shoot_delay_callback
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|gint
modifier|*
name|seconds_left
init|=
name|data
decl_stmt|;
operator|(
operator|*
name|seconds_left
operator|)
operator|--
expr_stmt|;
if|if
condition|(
operator|!
operator|*
name|seconds_left
condition|)
name|gtk_main_quit
argument_list|()
expr_stmt|;
return|return
operator|*
name|seconds_left
return|;
block|}
end_function

end_unit

