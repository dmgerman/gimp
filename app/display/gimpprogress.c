begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpstatusbar.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_struct
DECL|struct|_GimpProgress
struct|struct
name|_GimpProgress
block|{
DECL|member|gdisp
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
comment|/* gdisp in use, or NULL*/
comment|/* next four fields are only valid if gdisp is NULL */
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
comment|/* progress dialog, NULL if using gdisp */
DECL|member|dialog_label
name|GtkWidget
modifier|*
name|dialog_label
decl_stmt|;
DECL|member|progressbar
name|GtkWidget
modifier|*
name|progressbar
decl_stmt|;
DECL|member|cancelbutton
name|GtkWidget
modifier|*
name|cancelbutton
decl_stmt|;
DECL|member|cancel_callback
name|GCallback
name|cancel_callback
decl_stmt|;
comment|/* callback to remove, or NULL */
DECL|member|cancel_data
name|gpointer
name|cancel_data
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_progress_signal_setup
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GCallback
name|cancel_callback
parameter_list|,
name|gpointer
name|cancel_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_progress_start:  * @gdisp:           The #GimpDisplay to show the progress in.  * @message:         The message.  * @important:       Setting this to #FALSE will cause the progress  *                   to silently fail if the display's statusbar  *                   is hidden.  * @cancel_callback: The callback to call if the "Cancel" button is clicked.  * @cancel_data:     The %cancel_callback's "user_data".  *   * Start a progress bar on %gdisp with reason %message.  If %gdisp  * is #NULL, the progress bar is presented in a new dialog box.  If  * %message is #NULL, then no message is used.  *  * If %cancel_callback is not %NULL, it is attached to the progress  * bar cancel button's "clicked" signal, with data %cancel_data.  The  * cancel button is only made sensitive if the callback is set.  *  * It is an error to gimp_progress_start() a bar on a %gdisp for which  * there is already a progress bar active.  *  * Progress bars with %important set to #TRUE will be shown to the  * user in any possible way.  Unimportant progress bars will not be  * shown to the user if it would mean creating a new window.  *   * Return value: The new #GimpProgress.  **/
end_comment

begin_function
name|GimpProgress
modifier|*
DECL|function|gimp_progress_start (GimpDisplay * gdisp,const gchar * message,gboolean important,GCallback cancel_callback,gpointer cancel_data)
name|gimp_progress_start
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|important
parameter_list|,
name|GCallback
name|cancel_callback
parameter_list|,
name|gpointer
name|cancel_data
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|NULL
decl_stmt|;
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gdisp
operator|==
name|NULL
operator|||
name|GIMP_IS_DISPLAY
argument_list|(
name|gdisp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
condition|)
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|progress
operator|=
name|g_new0
argument_list|(
name|GimpProgress
argument_list|,
literal|1
argument_list|)
expr_stmt|;
comment|/*  do we have a useful gdisplay and statusarea?  */
if|if
condition|(
name|gdisp
operator|&&
name|GTK_WIDGET_VISIBLE
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
condition|)
block|{
name|progress
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
if|if
condition|(
name|message
condition|)
block|{
name|gimp_statusbar_push
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|,
literal|"progress"
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
comment|/*  really need image locking to stop multiple people going at        *  the image        */
if|if
condition|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
operator|->
name|progressid
condition|)
block|{
name|g_warning
argument_list|(
literal|"gimp_progress_start(): "
literal|"%d progress bars already active for display %p"
argument_list|,
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
operator|->
name|progressid
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
operator|->
name|progressid
operator|++
expr_stmt|;
block|}
else|else
block|{
comment|/*  unimporant progress indications are occasionally failed  */
if|if
condition|(
operator|!
name|important
condition|)
block|{
name|g_free
argument_list|(
name|progress
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|progress
operator|->
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Progress"
argument_list|)
argument_list|,
literal|"progress"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_WIN_POS_NONE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|progress
operator|->
name|cancelbutton
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|NULL
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
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|progress
operator|->
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|progress
operator|->
name|dialog_label
operator|=
name|gtk_label_new
argument_list|(
name|message
condition|?
name|message
else|:
name|_
argument_list|(
literal|"Please wait..."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|progress
operator|->
name|dialog_label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|progress
operator|->
name|dialog_label
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
name|progress
operator|->
name|dialog_label
argument_list|)
expr_stmt|;
name|progress
operator|->
name|progressbar
operator|=
name|gtk_progress_bar_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|progress
operator|->
name|progressbar
argument_list|,
literal|150
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|progress
operator|->
name|progressbar
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
name|progress
operator|->
name|progressbar
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|progress
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
name|gimp_progress_signal_setup
argument_list|(
name|progress
argument_list|,
name|cancel_callback
argument_list|,
name|cancel_data
argument_list|)
expr_stmt|;
return|return
name|progress
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_progress_restart:  * @progress:        The #GimpProgress to restart.  * @message:         The new message.  * @cancel_callback: The new cancel_callback  * @cancel_data:     The new cancel_data  *   * Update the message and/or the callbacks for a progress and reset  * the bar to zero, with the minimum of disturbance to the user.  *   * Return value: The same #GimpProgress as passed in as %progress.  **/
end_comment

begin_function
name|GimpProgress
modifier|*
DECL|function|gimp_progress_restart (GimpProgress * progress,const char * message,GCallback cancel_callback,gpointer cancel_data)
name|gimp_progress_restart
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|char
modifier|*
name|message
parameter_list|,
name|GCallback
name|cancel_callback
parameter_list|,
name|gpointer
name|cancel_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|bar
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  change the message  */
if|if
condition|(
name|progress
operator|->
name|gdisp
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|progress
operator|->
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimp_statusbar_pop
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|,
literal|"progress"
argument_list|)
expr_stmt|;
if|if
condition|(
name|message
condition|)
name|gimp_statusbar_push
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|,
literal|"progress"
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|bar
operator|=
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
operator|->
name|progressbar
expr_stmt|;
block|}
else|else
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|progress
operator|->
name|dialog_label
argument_list|)
argument_list|,
name|message
condition|?
name|message
else|:
name|_
argument_list|(
literal|"Please wait..."
argument_list|)
argument_list|)
expr_stmt|;
name|bar
operator|=
name|progress
operator|->
name|progressbar
expr_stmt|;
block|}
comment|/*  reset the progress bar  */
name|gtk_progress_bar_set_fraction
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|bar
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
comment|/*  do we need to change the callbacks?  */
name|gimp_progress_signal_setup
argument_list|(
name|progress
argument_list|,
name|cancel_callback
argument_list|,
name|cancel_data
argument_list|)
expr_stmt|;
return|return
name|progress
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_progress_update (GimpProgress * progress,gdouble percentage)
name|gimp_progress_update
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|bar
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|progress
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|percentage
operator|<
literal|0.0
operator|||
name|percentage
operator|>
literal|1.0
condition|)
return|return;
comment|/*  do we have a dialog box, or are we using the statusbar?  */
if|if
condition|(
name|progress
operator|->
name|gdisp
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|progress
operator|->
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|bar
operator|=
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
operator|->
name|progressbar
expr_stmt|;
block|}
else|else
block|{
name|bar
operator|=
name|progress
operator|->
name|progressbar
expr_stmt|;
block|}
name|gtk_progress_bar_set_fraction
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|bar
argument_list|)
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
comment|/* force updates so there's feedback even when the main loop is busy */
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|bar
argument_list|)
condition|)
name|gdk_window_process_updates
argument_list|(
name|bar
operator|->
name|window
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_progress_step:  * @progress: The #GimpProgress.  *   * Step the progress bar by one percent, wrapping at 100%  **/
end_comment

begin_function
name|void
DECL|function|gimp_progress_step (GimpProgress * progress)
name|gimp_progress_step
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|bar
decl_stmt|;
name|gdouble
name|val
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|progress
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
operator|->
name|gdisp
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|progress
operator|->
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|bar
operator|=
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
operator|->
name|progressbar
expr_stmt|;
block|}
else|else
block|{
name|bar
operator|=
name|progress
operator|->
name|progressbar
expr_stmt|;
block|}
name|val
operator|=
name|gtk_progress_bar_get_fraction
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|bar
argument_list|)
argument_list|)
operator|+
literal|0.01
expr_stmt|;
if|if
condition|(
name|val
operator|>
literal|1.0
condition|)
name|val
operator|=
literal|0.0
expr_stmt|;
name|gimp_progress_update
argument_list|(
name|progress
argument_list|,
name|val
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_progress_end:  * @progress: The #GimpProgress.  *   * Finish using the progress bar.  **/
end_comment

begin_function
name|void
DECL|function|gimp_progress_end (GimpProgress * progress)
name|gimp_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|progress
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/* remove all callbacks so they don't get called while we're    * destroying widgets    */
name|gimp_progress_signal_setup
argument_list|(
name|progress
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
operator|->
name|gdisp
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GtkProgressBar
modifier|*
name|bar
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|progress
operator|->
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimp_statusbar_pop
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|,
literal|"progress"
argument_list|)
expr_stmt|;
name|bar
operator|=
name|GTK_PROGRESS_BAR
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
operator|->
name|progressbar
argument_list|)
expr_stmt|;
name|gtk_progress_bar_set_fraction
argument_list|(
name|bar
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
operator|->
name|progressid
operator|>
literal|0
condition|)
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
operator|->
name|progressid
operator|--
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_destroy
argument_list|(
name|progress
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|progress
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  This function's prototype is conveniently  *  the same as progress_func_t  */
end_comment

begin_comment
comment|/**  * gimp_progress_update_and_flush:  * @min:  The minimum, ...  * @max:  ... the maximum, ...  * @curr: ... and the current progress of your operation.  * @data: The #GimpProgress you want to update.  *   * This function's prototype is conveniently  * the same as #GimpProgressFunc from libgimpcolor.  **/
end_comment

begin_function
name|void
DECL|function|gimp_progress_update_and_flush (gint min,gint max,gint curr,gpointer data)
name|gimp_progress_update_and_flush
parameter_list|(
name|gint
name|min
parameter_list|,
name|gint
name|max
parameter_list|,
name|gint
name|curr
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_progress_update
argument_list|(
operator|(
name|GimpProgress
operator|*
operator|)
name|data
argument_list|,
call|(
name|gfloat
call|)
argument_list|(
name|curr
operator|-
name|min
argument_list|)
operator|/
call|(
name|gfloat
call|)
argument_list|(
name|max
operator|-
name|min
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|gtk_events_pending
argument_list|()
condition|)
name|gtk_main_iteration
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_comment
comment|/*  Helper function to add or remove signals  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_progress_signal_setup (GimpProgress * progress,GCallback cancel_callback,gpointer cancel_data)
name|gimp_progress_signal_setup
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GCallback
name|cancel_callback
parameter_list|,
name|gpointer
name|cancel_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
if|if
condition|(
name|progress
operator|->
name|cancel_callback
operator|==
name|cancel_callback
operator|&&
name|progress
operator|->
name|cancel_data
operator|==
name|cancel_data
condition|)
return|return;
comment|/* are we using the statusbar or a freestanding dialog? */
if|if
condition|(
name|progress
operator|->
name|gdisp
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|progress
operator|->
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|NULL
expr_stmt|;
name|button
operator|=
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
operator|->
name|cancelbutton
expr_stmt|;
block|}
else|else
block|{
name|dialog
operator|=
name|progress
operator|->
name|dialog
expr_stmt|;
name|button
operator|=
name|progress
operator|->
name|cancelbutton
expr_stmt|;
block|}
comment|/* remove any existing signal handlers */
if|if
condition|(
name|progress
operator|->
name|cancel_callback
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|button
argument_list|,
name|progress
operator|->
name|cancel_callback
argument_list|,
name|progress
operator|->
name|cancel_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
condition|)
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|dialog
argument_list|,
name|progress
operator|->
name|cancel_callback
argument_list|,
name|progress
operator|->
name|cancel_data
argument_list|)
expr_stmt|;
block|}
comment|/* add the new handlers */
if|if
condition|(
name|cancel_callback
condition|)
block|{
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|cancel_callback
argument_list|)
argument_list|,
name|cancel_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
condition|)
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|cancel_callback
argument_list|)
argument_list|,
name|cancel_data
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
argument_list|,
name|cancel_callback
condition|?
name|TRUE
else|:
name|FALSE
argument_list|)
expr_stmt|;
name|progress
operator|->
name|cancel_callback
operator|=
name|cancel_callback
expr_stmt|;
name|progress
operator|->
name|cancel_data
operator|=
name|cancel_data
expr_stmt|;
block|}
end_function

end_unit

