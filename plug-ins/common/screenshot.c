begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*    *  ScreenShot plug-in  *  Copyright 1998-2000 Sven Neumann<sven@gimp.org>  *  *  Any suggestions, bug-reports or patches are very welcome.  *   *  This plug-in uses the X-utility xwd to grab an image from the screen  *  and the xwd-plug-in created by Peter Kirchgessner (pkirchg@aol.com)  *  to load this image into the gimp.  *  Hence its nothing but a simple frontend to those utilities.  */
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
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<sys/wait.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__EMX__
end_ifdef

begin_include
include|#
directive|include
file|<process.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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
value|"extension_screenshot"
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|XWD
end_ifndef

begin_define
DECL|macro|XWD
define|#
directive|define
name|XWD
value|"xwd"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29af0e7d0108
block|{
DECL|member|root
name|gboolean
name|root
decl_stmt|;
DECL|member|window_id
name|gchar
modifier|*
name|window_id
decl_stmt|;
DECL|member|delay
name|guint
name|delay
decl_stmt|;
DECL|member|decor
name|gboolean
name|decor
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
name|NULL
block|,
comment|/* window ID */
literal|0
block|,
comment|/* delay */
name|TRUE
block|,
comment|/* decorations */
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
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
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
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|run_flag
name|gboolean
name|run_flag
init|=
name|FALSE
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
name|GIMP_PDB_STRING
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
literal|"This extension serves as a simple frontend to the "
literal|"X-window utility xwd and the xwd-file-plug-in. "
literal|"After specifying some options, xwd is called, the "
literal|"user selects a window, and the resulting image is "
literal|"loaded into the gimp. Alternatively the whole "
literal|"screen can be grabbed. When called non-interactively "
literal|"it may grab the root window or use the window-id "
literal|"passed as a parameter."
argument_list|,
literal|"Sven Neumann<sven@gimp.org>"
argument_list|,
literal|"1998 - 2000"
argument_list|,
literal|"v0.9.5 (2000/10/29)"
argument_list|,
name|N_
argument_list|(
literal|"<Toolbox>/File/Acquire/Screen Shot..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_EXTENSION
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
DECL|function|run (gchar * name,gint nparams,GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
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
comment|/* status variable, use it to check for errors in invocation usualy only     * during non-interactive calling    */
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
name|NULL
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
operator|(
name|gchar
operator|*
operator|)
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
name|shootvals
operator|.
name|delay
operator|=
literal|0
expr_stmt|;
name|shootvals
operator|.
name|decor
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
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
name|GimpParam
modifier|*
name|params
decl_stmt|;
name|gint
name|retvals
decl_stmt|;
name|gchar
modifier|*
name|tmpname
decl_stmt|;
name|gchar
modifier|*
name|xwdargv
index|[
literal|7
index|]
decl_stmt|;
comment|/*  need a maximum of 7 arguments to xwd  */
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|gint
name|pid
decl_stmt|;
name|gint
name|wpid
decl_stmt|;
name|gint
name|status
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
comment|/*  get a temp name with the right extension  */
name|tmpname
operator|=
name|gimp_temp_name
argument_list|(
literal|"xwd"
argument_list|)
expr_stmt|;
comment|/*  construct the xwd arguments  */
name|xwdargv
index|[
name|i
operator|++
index|]
operator|=
name|XWD
expr_stmt|;
name|xwdargv
index|[
name|i
operator|++
index|]
operator|=
literal|"-out"
expr_stmt|;
name|xwdargv
index|[
name|i
operator|++
index|]
operator|=
name|tmpname
expr_stmt|;
if|if
condition|(
name|shootvals
operator|.
name|root
operator|==
name|TRUE
condition|)
name|xwdargv
index|[
name|i
operator|++
index|]
operator|=
literal|"-root"
expr_stmt|;
else|else
block|{
if|if
condition|(
name|shootvals
operator|.
name|decor
operator|==
name|TRUE
condition|)
name|xwdargv
index|[
name|i
operator|++
index|]
operator|=
literal|"-frame"
expr_stmt|;
if|if
condition|(
name|shootvals
operator|.
name|window_id
operator|!=
name|NULL
condition|)
block|{
name|xwdargv
index|[
name|i
operator|++
index|]
operator|=
literal|"-id"
expr_stmt|;
name|xwdargv
index|[
name|i
operator|++
index|]
operator|=
name|shootvals
operator|.
name|window_id
expr_stmt|;
block|}
block|}
name|xwdargv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
ifndef|#
directive|ifndef
name|__EMX__
comment|/*  fork off a xwd process  */
if|if
condition|(
operator|(
name|pid
operator|=
name|fork
argument_list|()
operator|)
operator|<
literal|0
condition|)
block|{
name|g_message
argument_list|(
literal|"screenshot: fork failed: %s\n"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
elseif|else
if|if
condition|(
name|pid
operator|==
literal|0
condition|)
block|{
name|execvp
argument_list|(
name|XWD
argument_list|,
name|xwdargv
argument_list|)
expr_stmt|;
comment|/*  What are we doing here? exec must have failed  */
name|g_message
argument_list|(
literal|"screenshot: exec failed: xwd: %s\n"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
else|else
else|#
directive|else
comment|/* __EMX__ */
name|pid
operator|=
name|spawnvp
argument_list|(
name|P_NOWAIT
argument_list|,
name|XWD
argument_list|,
name|xwdargv
argument_list|)
expr_stmt|;
if|if
condition|(
name|pid
operator|==
operator|-
literal|1
condition|)
block|{
name|g_message
argument_list|(
literal|"screenshot: spawn failed: %s\n"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
endif|#
directive|endif
block|{
name|status
operator|=
operator|-
literal|1
expr_stmt|;
name|wpid
operator|=
name|waitpid
argument_list|(
name|pid
argument_list|,
operator|&
name|status
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|wpid
operator|<
literal|0
operator|)
operator|||
operator|!
name|WIFEXITED
argument_list|(
name|status
argument_list|)
condition|)
block|{
comment|/*  the tmpfile may have been created even if xwd failed  */
name|unlink
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
literal|"screenshot: xwd didn't work\n"
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
comment|/*  now load the tmpfile using the xwd-plug-in  */
name|params
operator|=
name|gimp_run_procedure
argument_list|(
literal|"file_xwd_load"
argument_list|,
operator|&
name|retvals
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
literal|1
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|tmpname
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|tmpname
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|params
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|image_ID
operator|=
name|params
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
expr_stmt|;
block|}
name|gimp_destroy_params
argument_list|(
name|params
argument_list|,
name|retvals
argument_list|)
expr_stmt|;
comment|/*  get rid of the tmpfile  */
name|unlink
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|gchar
modifier|*
name|comment
decl_stmt|;
comment|/*  figure out the monitor resolution and set the image to it  */
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
name|image_ID
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
comment|/*  unset the image filename  */
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
literal|""
argument_list|)
expr_stmt|;
comment|/* Set the default comment parasite */
name|comment
operator|=
name|gimp_get_default_comment
argument_list|()
expr_stmt|;
if|if
condition|(
name|comment
operator|!=
name|NULL
condition|)
block|{
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
block|}
block|}
return|return;
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
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
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
name|decor_button
decl_stmt|;
name|GtkWidget
modifier|*
name|spinner
decl_stmt|;
name|GtkWidget
modifier|*
name|sep
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
literal|"_Single Window"
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
comment|/*  with decorations  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|decor_button
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"With _Decorations"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|decor_button
argument_list|)
argument_list|,
name|shootvals
operator|.
name|decor
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|decor_button
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
name|decor_button
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|decor_button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|decor_button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|shootvals
operator|.
name|decor
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|sep
operator|=
name|gtk_hseparator_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|sep
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
name|sep
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
literal|"_Whole Screen"
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
operator|(
name|gint
operator|*
operator|)
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

