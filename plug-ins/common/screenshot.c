begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*    *  ScreenShot plug-in v0.9   *  Sven Neumann, neumanns@uni-duesseldorf.de    *  1998/06/06  *  *  Any suggestions, bug-reports or patches are very welcome.  *   *  This plug-in uses the X-utility xwd to grab an image from the screen  *  and the xwd-plug-in created by Peter Kirchgessner (pkirchg@aol.com)  *  to load this image into the gimp.  *  Hence its nothing but a simple frontend to those utilities.  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* Revision history  *  (98/02/18)  v0.1   first development release   *  (98/02/19)  v0.2   small bugfix   *  (98/03/09)  v0.3   another one  *  (98/03/13)  v0.4   cosmetic changes to the dialog  *  (98/04/02)  v0.5   it works non-interactively now and registers  *                     itself correctly as extension  *  (98/04/18)  v0.6   cosmetic change to the dialog  *  (98/05/28)  v0.7   use g_message for error output  *  (98/06/04)  v0.8   added delay-time for root window shot  *  (98/06/06)  v0.9   fixed a stupid bug in the dialog  */
end_comment

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

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
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

begin_define
DECL|macro|PLUG_IN_PRINT_NAME
define|#
directive|define
name|PLUG_IN_PRINT_NAME
value|"Screen Shot"
end_define

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|"v0.9 (98/06/06)"
end_define

begin_define
DECL|macro|PLUG_IN_MENU_PATH
define|#
directive|define
name|PLUG_IN_MENU_PATH
value|"<Toolbox>/Xtns/Screen Shot"
end_define

begin_define
DECL|macro|PLUG_IN_AUTHOR
define|#
directive|define
name|PLUG_IN_AUTHOR
value|"Sven Neumann (neumanns@uni-duesseldorf.de)"
end_define

begin_define
DECL|macro|PLUG_IN_COPYRIGHT
define|#
directive|define
name|PLUG_IN_COPYRIGHT
value|"Sven Neumann"
end_define

begin_define
DECL|macro|PLUG_IN_DESCRIBTION
define|#
directive|define
name|PLUG_IN_DESCRIBTION
value|"Create a screenshot of a single window or the whole screen"
end_define

begin_define
DECL|macro|PLUG_IN_HELP
define|#
directive|define
name|PLUG_IN_HELP
value|"This extension serves as a simple frontend to the X-window utility xwd and the xwd-file-plug-in. After specifying some options, xwd is called, the user selects a window, and the resulting image is loaded into the gimp. Alternatively the whole screen can be grabbed. When called non-interactively it may grab the root window or use the window-id passed as a parameter."
end_define

begin_define
DECL|macro|NUMBER_IN_ARGS
define|#
directive|define
name|NUMBER_IN_ARGS
value|3
end_define

begin_define
DECL|macro|IN_ARGS
define|#
directive|define
name|IN_ARGS
value|{ PARAM_INT32,    "run_mode",  "Interactive, non-interactive" },\                 { PARAM_INT32,    "root",      "Root window { TRUE, FALSE }" },\                 { PARAM_STRING,   "window_id", "Window id" }
end_define

begin_define
DECL|macro|NUMBER_OUT_ARGS
define|#
directive|define
name|NUMBER_OUT_ARGS
value|1
end_define

begin_define
DECL|macro|OUT_ARGS
define|#
directive|define
name|OUT_ARGS
value|{ PARAM_IMAGE,   "image",     "Output image" }
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
DECL|struct|__anon2b5b7d440108
typedef|typedef
struct|struct
block|{
DECL|member|root
name|gint
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
name|gint
name|decor
decl_stmt|;
DECL|typedef|ScreenShotValues
block|}
name|ScreenShotValues
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b5b7d440208
typedef|typedef
struct|struct
block|{
DECL|member|decor_button
name|GtkWidget
modifier|*
name|decor_button
decl_stmt|;
DECL|member|delay_box
name|GtkWidget
modifier|*
name|delay_box
decl_stmt|;
DECL|member|delay_spinner
name|GtkWidget
modifier|*
name|delay_spinner
decl_stmt|;
DECL|member|single_button
name|GtkWidget
modifier|*
name|single_button
decl_stmt|;
DECL|member|root_button
name|GtkWidget
modifier|*
name|root_button
decl_stmt|;
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|ScreenShotInterface
block|}
name|ScreenShotInterface
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

begin_decl_stmt
DECL|variable|shootint
specifier|static
name|ScreenShotInterface
name|shootint
init|=
block|{
name|FALSE
comment|/* run */
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
comment|/* number of parameters passed in */
name|GParam
modifier|*
name|param
parameter_list|,
comment|/* parameters passed in */
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
comment|/* number of parameters returned */
name|GParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* parameters to be returned */
end_comment

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
name|gint
name|shoot_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|shoot_close_callback
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
name|shoot_toggle_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|radio_button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|shoot_display_image
parameter_list|(
name|gint32
name|image
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
name|gint
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
name|GPlugInInfo
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
name|GParamDef
name|args
index|[]
init|=
block|{
name|IN_ARGS
block|}
decl_stmt|;
specifier|static
name|gint
name|nargs
init|=
name|NUMBER_IN_ARGS
decl_stmt|;
specifier|static
name|GParamDef
name|return_vals
index|[]
init|=
block|{
name|OUT_ARGS
block|}
decl_stmt|;
specifier|static
name|gint
name|nreturn_vals
init|=
name|NUMBER_OUT_ARGS
decl_stmt|;
comment|/* the actual installation of the plugin */
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_NAME
argument_list|,
name|PLUG_IN_DESCRIBTION
argument_list|,
name|PLUG_IN_HELP
argument_list|,
name|PLUG_IN_AUTHOR
argument_list|,
name|PLUG_IN_COPYRIGHT
argument_list|,
name|PLUG_IN_VERSION
argument_list|,
name|PLUG_IN_MENU_PATH
argument_list|,
name|NULL
argument_list|,
name|PROC_EXTENSION
argument_list|,
name|nargs
argument_list|,
name|nreturn_vals
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
DECL|function|run (gchar * name,gint nparams,GParam * param,gint * nreturn_vals,GParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
comment|/* name of plugin */
name|gint
name|nparams
parameter_list|,
comment|/* number of in-paramters */
name|GParam
modifier|*
name|param
parameter_list|,
comment|/* in-parameters */
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
comment|/* number of out-parameters */
name|GParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
comment|/* out-parameters */
block|{
comment|/* Get the runmode from the in-parameters */
name|GRunModeType
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
comment|/* status variable, use it to check for errors in invocation usualy only       during non-interactive calling */
name|GStatusType
name|status
init|=
name|STATUS_SUCCESS
decl_stmt|;
comment|/*always return at least the status to the caller. */
specifier|static
name|GParam
name|values
index|[
literal|1
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
name|PARAM_STATUS
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
comment|/*how are we running today? */
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|RUN_INTERACTIVE
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
return|return;
break|break;
case|case
name|RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparams
operator|==
name|NUMBER_IN_ARGS
condition|)
block|{
name|shootvals
operator|.
name|root
operator|=
operator|(
name|gint
operator|)
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
name|STATUS_CALLING_ERROR
expr_stmt|;
break|break;
case|case
name|RUN_WITH_LAST_VALS
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
comment|/* switch */
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
if|if
condition|(
name|shootvals
operator|.
name|root
operator|&&
operator|(
name|shootvals
operator|.
name|delay
operator|>
literal|0
operator|)
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
block|}
name|status
operator|=
operator|(
name|image_ID
operator|!=
operator|-
literal|1
operator|)
condition|?
name|STATUS_SUCCESS
else|:
name|STATUS_EXECUTION_ERROR
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
if|if
condition|(
name|run_mode
operator|==
name|RUN_INTERACTIVE
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
name|shoot_display_image
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
name|PARAM_IMAGE
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
name|GParam
modifier|*
name|params
decl_stmt|;
name|gint
name|retvals
decl_stmt|;
name|char
modifier|*
name|tmpname
decl_stmt|;
name|char
modifier|*
name|xwdargv
index|[
literal|7
index|]
decl_stmt|;
comment|/* only need a maximum of 7 arguments to xwd */
name|gint
name|pid
decl_stmt|;
name|gint
name|status
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
comment|/* get a temp name with the right extension and save into it. */
name|params
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_temp_name"
argument_list|,
operator|&
name|retvals
argument_list|,
name|PARAM_STRING
argument_list|,
literal|"xwd"
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|tmpname
operator|=
name|params
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
comment|/* construct the xwd arguments */
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
comment|/* fork off a xwd process */
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
comment|/* What are we doing here? exec must have failed */
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
block|{
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
operator|!
name|WIFEXITED
argument_list|(
name|status
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"screenshot: xwd didn't work\n"
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
comment|/* now load the tmpfile using the xwd-plug-in */
name|params
operator|=
name|gimp_run_procedure
argument_list|(
literal|"file_xwd_load"
argument_list|,
operator|&
name|retvals
argument_list|,
name|PARAM_INT32
argument_list|,
literal|1
argument_list|,
name|PARAM_STRING
argument_list|,
name|tmpname
argument_list|,
name|PARAM_STRING
argument_list|,
name|tmpname
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
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
comment|/* get rid of the tmpfile */
name|unlink
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
return|return;
block|}
end_function

begin_comment
comment|/* ScreenShot dialog */
end_comment

begin_function
specifier|static
name|gint
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
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GSList
modifier|*
name|radio_group
init|=
name|NULL
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|gint
name|radio_pressed
index|[
literal|2
index|]
decl_stmt|;
name|gint
name|decorations
decl_stmt|;
name|guint
name|delay
decl_stmt|;
name|gint
name|argc
init|=
literal|1
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|argv
init|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|argv
index|[
literal|0
index|]
operator|=
name|g_strdup
argument_list|(
literal|"ScreenShot"
argument_list|)
expr_stmt|;
name|radio_pressed
index|[
literal|0
index|]
operator|=
operator|(
name|shootvals
operator|.
name|root
operator|==
name|FALSE
operator|)
expr_stmt|;
name|radio_pressed
index|[
literal|1
index|]
operator|=
operator|(
name|shootvals
operator|.
name|root
operator|==
name|TRUE
operator|)
expr_stmt|;
name|decorations
operator|=
name|shootvals
operator|.
name|decor
expr_stmt|;
name|delay
operator|=
name|shootvals
operator|.
name|delay
expr_stmt|;
comment|/* Init GTK  */
name|gtk_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
expr_stmt|;
name|gtk_rc_parse
argument_list|(
name|gimp_gtkrc
argument_list|()
argument_list|)
expr_stmt|;
name|gdk_set_use_xshm
argument_list|(
name|gimp_use_xshm
argument_list|()
argument_list|)
expr_stmt|;
comment|/* Main Dialog */
name|dialog
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|PLUG_IN_PRINT_NAME
argument_list|)
expr_stmt|;
name|gtk_window_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|shoot_close_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Action area  */
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|"Grab"
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|shoot_ok_callback
argument_list|,
name|dialog
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
name|action_area
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_grab_default
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|"Cancel"
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gtk_widget_destroy
argument_list|,
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
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
name|action_area
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
comment|/*  Single Window */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
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
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|4
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
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
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
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_border_width
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
name|shootint
operator|.
name|single_button
operator|=
name|gtk_radio_button_new
argument_list|(
name|radio_group
argument_list|)
expr_stmt|;
name|radio_group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|shootint
operator|.
name|single_button
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
name|shootint
operator|.
name|single_button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|shootint
operator|.
name|single_button
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|shoot_toggle_update
argument_list|,
operator|&
name|radio_pressed
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|shootint
operator|.
name|single_button
argument_list|)
argument_list|,
name|radio_pressed
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|shootint
operator|.
name|single_button
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Grab a single window"
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
comment|/* with decorations */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
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
name|shootint
operator|.
name|decor_button
operator|=
name|gtk_check_button_new_with_label
argument_list|(
literal|"Include decorations"
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|shootint
operator|.
name|decor_button
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|shoot_toggle_update
argument_list|,
operator|&
name|decorations
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|shootint
operator|.
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
name|shootint
operator|.
name|decor_button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
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
comment|/* Root Window */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
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
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|4
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
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
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
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_border_width
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
name|shootint
operator|.
name|root_button
operator|=
name|gtk_radio_button_new
argument_list|(
name|radio_group
argument_list|)
expr_stmt|;
name|radio_group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|shootint
operator|.
name|root_button
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
name|shootint
operator|.
name|root_button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|shootint
operator|.
name|root_button
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|shoot_toggle_update
argument_list|,
operator|&
name|radio_pressed
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|shootint
operator|.
name|root_button
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Grab the whole screen"
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
comment|/* with delay */
name|shootint
operator|.
name|delay_box
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|shootint
operator|.
name|delay_box
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"after "
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|shootint
operator|.
name|delay_box
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|adj
operator|=
operator|(
name|GtkAdjustment
operator|*
operator|)
name|gtk_adjustment_new
argument_list|(
operator|(
name|gfloat
operator|)
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
name|shootint
operator|.
name|delay_spinner
operator|=
name|gtk_spin_button_new
argument_list|(
name|adj
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
name|shootint
operator|.
name|delay_box
argument_list|)
argument_list|,
name|shootint
operator|.
name|delay_spinner
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|shootint
operator|.
name|delay_spinner
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|" seconds delay"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|shootint
operator|.
name|delay_box
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|shootint
operator|.
name|delay_box
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
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|shootint
operator|.
name|decor_button
argument_list|)
argument_list|,
name|decorations
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|shootint
operator|.
name|decor_button
argument_list|,
name|radio_pressed
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|shootint
operator|.
name|root_button
argument_list|)
argument_list|,
name|radio_pressed
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|shootint
operator|.
name|delay_box
argument_list|,
name|radio_pressed
index|[
literal|1
index|]
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
name|gdk_flush
argument_list|()
expr_stmt|;
name|shootvals
operator|.
name|root
operator|=
name|radio_pressed
index|[
literal|1
index|]
expr_stmt|;
name|shootvals
operator|.
name|decor
operator|=
name|decorations
expr_stmt|;
return|return
name|shootint
operator|.
name|run
return|;
block|}
end_function

begin_comment
comment|/*  ScreenShot interface functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|shoot_close_callback (GtkWidget * widget,gpointer data)
name|shoot_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
end_function

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
name|shootint
operator|.
name|run
operator|=
name|TRUE
expr_stmt|;
name|shootvals
operator|.
name|delay
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|shootint
operator|.
name|delay_spinner
argument_list|)
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|shoot_toggle_update (GtkWidget * widget,gpointer radio_button)
name|shoot_toggle_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|radio_button
parameter_list|)
block|{
name|gint
modifier|*
name|toggle_val
decl_stmt|;
name|toggle_val
operator|=
operator|(
name|gint
operator|*
operator|)
name|radio_button
expr_stmt|;
if|if
condition|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
operator|*
name|toggle_val
operator|=
name|TRUE
expr_stmt|;
else|else
operator|*
name|toggle_val
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|widget
operator|==
name|shootint
operator|.
name|single_button
condition|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|shootint
operator|.
name|decor_button
argument_list|,
operator|*
name|toggle_val
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|shootint
operator|.
name|delay_box
argument_list|,
operator|!
operator|*
name|toggle_val
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|widget
operator|==
name|shootint
operator|.
name|root_button
condition|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|shootint
operator|.
name|decor_button
argument_list|,
operator|!
operator|*
name|toggle_val
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|shootint
operator|.
name|delay_box
argument_list|,
operator|*
name|toggle_val
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* Delay functions */
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
name|gint
name|timeout
decl_stmt|;
name|timeout
operator|=
name|gtk_timeout_add
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
name|gint
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
decl_stmt|;
name|seconds_left
operator|=
operator|(
name|gint
operator|*
operator|)
name|data
expr_stmt|;
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
operator|(
operator|*
name|seconds_left
operator|)
return|;
block|}
end_function

begin_comment
comment|/* Display function */
end_comment

begin_function
name|void
DECL|function|shoot_display_image (gint32 image)
name|shoot_display_image
parameter_list|(
name|gint32
name|image
parameter_list|)
block|{
name|GParam
modifier|*
name|params
decl_stmt|;
name|gint
name|retvals
decl_stmt|;
name|params
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_display_new"
argument_list|,
operator|&
name|retvals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

