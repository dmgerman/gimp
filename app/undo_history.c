begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * Undo history browser by Austin Donnelly<austin@gimp.org>  */
end_comment

begin_comment
comment|/* TODO:  *  *  - previews of the image on each line (reuse the L&C previews?)  *  *  - work out which (if any) is the clean image, and mark it as such  *         (eg floppy disk icon) Currently, its a "*" and it's on the  *         wrong line.  *  *  - scroll to keep current selection visible.  Can some GTK guru  *         help out?  *  *  - window looks butt-ugly.  As usual, my (lack) of graphic design  *         skills are showing through.  Someone please prettify it!  *  *  - undo names are less than useful.  This isn't a problem with  *         undo_history.c itself, more with the rather chaotic way  *         people have of picking an undo type when pushing undos, and  *         inconsistent use of undo groups.  Maybe rather than  *         specifying an (enum) type, it should be a const char * ?  *  * BUGS:  *  - clean star in wrong place  *  - window title not updated on image title change  *  *  Initial rev 0.01, (c) 19 Sept 1999 Austin Donnelly<austin@gimp.org>  *  */
end_comment

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"actionarea.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_typedef
DECL|struct|__anon29be6abe0108
typedef|typedef
struct|struct
block|{
DECL|member|gimage
name|GImage
modifier|*
name|gimage
decl_stmt|;
comment|/* image we're tracking undo info for */
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
comment|/* dialog window */
DECL|member|clist
name|GtkWidget
modifier|*
name|clist
decl_stmt|;
comment|/* list of undo actions */
DECL|member|undo_button
name|GtkWidget
modifier|*
name|undo_button
decl_stmt|;
comment|/* button to undo an operation */
DECL|member|redo_button
name|GtkWidget
modifier|*
name|redo_button
decl_stmt|;
comment|/* button to redo an operation */
DECL|member|old_selection
name|int
name|old_selection
decl_stmt|;
comment|/* previous selection in the clist */
DECL|typedef|undo_history_st
block|}
name|undo_history_st
typedef|;
end_typedef

begin_comment
comment|/*  * Theory of operation.  *  * Keep a clist.  Each row of the clist corresponds to an image as it  * was at some time in the past, present or future.  The selected row  * is the present image.  Rows below the selected one are in the  * future - as redo operations are performed, they become the current  * image.  Rows above the selected one are in the past - undo  * operations move the highlight up.  *  * The slight fly in the ointment is that if rows are images, then how  * should they be labelled?  An undo or redo operation goes _between_  * two image states - it isn't an image state.  It's a pretty  * arbitrary decision, but I've chosen to label a row with the name of  * the action that brought the image into the state represented by  * that row.  Thus, there is a special first row without a meaningful  * label, which represents the image state before the first action has  * been done to it.  The choice is between a special first row or a  * special last row.  Since people mostly work near the leading edge,  * not often going all the way back, I've chosen to put the special  * case out of common sight.  *  * So, the undo stack contents appear above the selected row, and the  * redo stack below it.  *  * The clist is initialised by mapping over the undo and redo stack.  *  * Once initialised, the dialog listens to undo_event signals from the  * gimage.  These undo events allow us to track changes to the undo  * and redo stacks.  We follow the events, making parallel changes to  * the clist.  If we ever get out of sync, there is no mechanism to  * notice or re-sync.  A few g_return_if_fails should catch some of  * these cases.  *  * User clicks changing the selected row in the clist turn into  * multiple calls to undo_pop or undo_redo, with appropriate signals  * blocked so we don't get our own events back.  *  * The "Close" button hides the dialog, rather than destroying it.  * This may well need to be changed, since the dialog will continue to  * track updates, and if it's generating previews this might take too  * long for large images.  *  * The dialog is destroyed when the gimage it is tracking is  * destroyed.  Note that a File/Revert destroys the current gimage and  * so blows the undo/redo stacks.  *  * --austin, 19/9/1999  */
end_comment

begin_comment
comment|/**************************************************************/
end_comment

begin_comment
comment|/* Local functions */
end_comment

begin_comment
comment|/* close button clicked */
end_comment

begin_function
specifier|static
name|void
DECL|function|undo_history_close_callback (GtkWidget * w,gpointer data)
name|undo_history_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|undo_history_st
modifier|*
name|st
init|=
name|data
decl_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_WIDGET
argument_list|(
name|st
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* WM_DELETE */
end_comment

begin_function
specifier|static
name|gint
DECL|function|undo_history_delete_callback (GtkWidget * w,GdkEvent * e,gpointer data)
name|undo_history_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|GdkEvent
modifier|*
name|e
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|undo_history_close_callback
argument_list|(
name|w
argument_list|,
name|data
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|action_items
specifier|static
name|ActionAreaItem
name|action_items
index|[]
init|=
block|{
block|{
name|N_
argument_list|(
literal|"Close"
argument_list|)
block|,
name|undo_history_close_callback
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* The gimage and shell destroy callbacks are split so we can:  *   a) blow the shell when the image dissappears  *   b) disconnect from the image if the shell dissappears (we don't  *        want signals from the image to carry on using "st" once it's  *        been freed.  */
end_comment

begin_comment
comment|/* gimage destroyed */
end_comment

begin_function
specifier|static
name|void
DECL|function|undo_history_gimage_destroy_callback (GtkWidget * w,gpointer data)
name|undo_history_gimage_destroy_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|undo_history_st
modifier|*
name|st
init|=
name|data
decl_stmt|;
name|st
operator|->
name|gimage
operator|=
name|NULL
expr_stmt|;
comment|/* not allowed to use this any more */
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|st
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
comment|/* which continues in the function below: */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|undo_history_shell_destroy_callback (GtkWidget * w,gpointer data)
name|undo_history_shell_destroy_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|undo_history_st
modifier|*
name|st
init|=
name|data
decl_stmt|;
if|if
condition|(
name|st
operator|->
name|gimage
condition|)
name|gtk_signal_disconnect_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|st
operator|->
name|gimage
argument_list|)
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|st
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* undo button clicked */
end_comment

begin_function
specifier|static
name|void
DECL|function|undo_history_undo_callback (GtkWidget * widget,gpointer data)
name|undo_history_undo_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|undo_history_st
modifier|*
name|st
init|=
name|data
decl_stmt|;
name|undo_pop
argument_list|(
name|st
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* redo button clicked */
end_comment

begin_function
specifier|static
name|void
DECL|function|undo_history_redo_callback (GtkWidget * widget,gpointer data)
name|undo_history_redo_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|undo_history_st
modifier|*
name|st
init|=
name|data
decl_stmt|;
name|undo_redo
argument_list|(
name|st
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Always start clist with dummy entry for image state before  * the first action on the undo stack */
end_comment

begin_function
specifier|static
name|void
DECL|function|undo_history_append_special (GtkCList * clist)
name|undo_history_append_special
parameter_list|(
name|GtkCList
modifier|*
name|clist
parameter_list|)
block|{
name|char
modifier|*
name|name
init|=
name|_
argument_list|(
literal|"[ base image ]"
argument_list|)
decl_stmt|;
name|char
modifier|*
name|namelist
index|[]
init|=
block|{
name|NULL
block|,
name|name
block|}
decl_stmt|;
name|gtk_clist_append
argument_list|(
name|clist
argument_list|,
name|namelist
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Recalculate which of the undo and redo buttons are meant to be sensitive */
end_comment

begin_function
specifier|static
name|void
DECL|function|undo_history_set_sensitive (undo_history_st * st,int rows)
name|undo_history_set_sensitive
parameter_list|(
name|undo_history_st
modifier|*
name|st
parameter_list|,
name|int
name|rows
parameter_list|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|st
operator|->
name|undo_button
argument_list|,
operator|(
name|st
operator|->
name|old_selection
operator|!=
literal|0
operator|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|st
operator|->
name|redo_button
argument_list|,
operator|(
name|st
operator|->
name|old_selection
operator|!=
name|rows
operator|-
literal|1
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Track undo_event signals, telling us of changes to the undo and  * redo stacks. */
end_comment

begin_function
specifier|static
name|void
DECL|function|undo_history_undo_event (GtkWidget * widget,int ev,gpointer data)
name|undo_history_undo_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|int
name|ev
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|undo_history_st
modifier|*
name|st
init|=
name|data
decl_stmt|;
name|undo_event_t
name|event
init|=
name|ev
decl_stmt|;
specifier|const
name|char
modifier|*
name|name
decl_stmt|;
name|char
modifier|*
name|namelist
index|[
literal|2
index|]
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|int
name|cur_selection
decl_stmt|;
name|GtkCList
modifier|*
name|clist
decl_stmt|;
name|list
operator|=
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
operator|->
name|selection
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|list
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|cur_selection
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|clist
operator|=
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
expr_stmt|;
comment|/* block select events */
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|st
operator|->
name|clist
argument_list|)
argument_list|,
name|st
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|event
condition|)
block|{
case|case
name|UNDO_PUSHED
case|:
comment|/* clip everything after the current selection (ie, the          * actions that are from the redo stack) */
name|gtk_clist_freeze
argument_list|(
name|clist
argument_list|)
expr_stmt|;
while|while
condition|(
name|clist
operator|->
name|rows
operator|>
name|cur_selection
operator|+
literal|1
condition|)
name|gtk_clist_remove
argument_list|(
name|clist
argument_list|,
name|cur_selection
operator|+
literal|1
argument_list|)
expr_stmt|;
comment|/* find out what's new */
name|name
operator|=
name|undo_get_undo_name
argument_list|(
name|st
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|namelist
index|[
literal|0
index|]
operator|=
name|NULL
expr_stmt|;
name|namelist
index|[
literal|1
index|]
operator|=
operator|(
name|char
operator|*
operator|)
name|name
expr_stmt|;
name|gtk_clist_append
argument_list|(
name|clist
argument_list|,
name|namelist
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|clist
operator|->
name|rows
operator|==
name|cur_selection
operator|+
literal|2
argument_list|)
expr_stmt|;
comment|/* always force selection to bottom, and scroll to it */
name|gtk_clist_select_row
argument_list|(
name|clist
argument_list|,
name|clist
operator|->
name|rows
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_clist_moveto
argument_list|(
name|clist
argument_list|,
name|clist
operator|->
name|rows
operator|-
literal|1
argument_list|,
literal|0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_clist_thaw
argument_list|(
name|clist
argument_list|)
expr_stmt|;
name|cur_selection
operator|=
name|clist
operator|->
name|rows
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|UNDO_EXPIRED
case|:
comment|/* remove earliest row, but not our special first one */
name|gtk_clist_remove
argument_list|(
name|clist
argument_list|,
literal|1
argument_list|)
expr_stmt|;
break|break;
case|case
name|UNDO_POPPED
case|:
comment|/* move hilight up one */
name|g_return_if_fail
argument_list|(
name|cur_selection
operator|>=
literal|1
argument_list|)
expr_stmt|;
name|gtk_clist_select_row
argument_list|(
name|clist
argument_list|,
name|cur_selection
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|cur_selection
operator|--
expr_stmt|;
break|break;
case|case
name|UNDO_REDO
case|:
comment|/* move hilight down one */
name|g_return_if_fail
argument_list|(
name|cur_selection
operator|+
literal|1
operator|<
name|clist
operator|->
name|rows
argument_list|)
expr_stmt|;
name|gtk_clist_select_row
argument_list|(
name|clist
argument_list|,
name|cur_selection
operator|+
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|cur_selection
operator|++
expr_stmt|;
break|break;
case|case
name|UNDO_FREE
case|:
comment|/* clear all info other that the special first line */
name|gtk_clist_freeze
argument_list|(
name|clist
argument_list|)
expr_stmt|;
name|gtk_clist_clear
argument_list|(
name|clist
argument_list|)
expr_stmt|;
name|undo_history_append_special
argument_list|(
name|clist
argument_list|)
expr_stmt|;
name|gtk_clist_thaw
argument_list|(
name|clist
argument_list|)
expr_stmt|;
name|cur_selection
operator|=
literal|0
expr_stmt|;
break|break;
block|}
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|st
operator|->
name|clist
argument_list|)
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|st
operator|->
name|old_selection
operator|=
name|cur_selection
expr_stmt|;
name|undo_history_set_sensitive
argument_list|(
name|st
argument_list|,
name|clist
operator|->
name|rows
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|undo_history_select_row_callback (GtkWidget * w,gint row,gint column,gpointer event,gpointer data)
name|undo_history_select_row_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|column
parameter_list|,
name|gpointer
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|undo_history_st
modifier|*
name|st
init|=
name|data
decl_stmt|;
name|int
name|cur_selection
decl_stmt|;
name|cur_selection
operator|=
name|row
expr_stmt|;
if|if
condition|(
name|cur_selection
operator|==
name|st
operator|->
name|old_selection
condition|)
return|return;
comment|/* Disable undo_event signals while we do these multiple undo or      * redo actions. */
name|gtk_signal_handler_block_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|st
operator|->
name|gimage
argument_list|)
argument_list|,
name|undo_history_undo_event
argument_list|,
name|st
argument_list|)
expr_stmt|;
while|while
condition|(
name|cur_selection
operator|<
name|st
operator|->
name|old_selection
condition|)
block|{
name|undo_pop
argument_list|(
name|st
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|st
operator|->
name|old_selection
operator|--
expr_stmt|;
block|}
while|while
condition|(
name|cur_selection
operator|>
name|st
operator|->
name|old_selection
condition|)
block|{
name|undo_redo
argument_list|(
name|st
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|st
operator|->
name|old_selection
operator|++
expr_stmt|;
block|}
name|gtk_signal_handler_unblock_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|st
operator|->
name|gimage
argument_list|)
argument_list|,
name|undo_history_undo_event
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|undo_history_set_sensitive
argument_list|(
name|st
argument_list|,
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
operator|->
name|rows
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|undo_history_clean_callback (GtkWidget * w,gpointer data)
name|undo_history_clean_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|undo_history_st
modifier|*
name|st
init|=
name|data
decl_stmt|;
name|int
name|i
decl_stmt|;
name|int
name|nrows
decl_stmt|;
name|GtkCList
modifier|*
name|clist
decl_stmt|;
if|if
condition|(
name|st
operator|->
name|gimage
operator|->
name|dirty
operator|!=
literal|0
condition|)
return|return;
comment|/* The image is clean, so this is the version on disc.  Remove the      * clean star from all other entries, and add it to the current      * one. */
comment|/* XXX currently broken, since "clean" signal is emitted before      * UNDO_POPPED event.  I don't want to change the order of the      * signals.  So I'm a little stuck. --austin */
name|clist
operator|=
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
expr_stmt|;
name|nrows
operator|=
name|clist
operator|->
name|rows
expr_stmt|;
name|gtk_clist_freeze
argument_list|(
name|clist
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
name|nrows
condition|;
name|i
operator|++
control|)
name|gtk_clist_set_text
argument_list|(
name|clist
argument_list|,
name|i
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_clist_set_text
argument_list|(
name|clist
argument_list|,
name|st
operator|->
name|old_selection
argument_list|,
literal|0
argument_list|,
literal|"*"
argument_list|)
expr_stmt|;
name|gtk_clist_thaw
argument_list|(
name|clist
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Used to build up initial contents of clist */
end_comment

begin_function
specifier|static
name|int
DECL|function|undo_history_init_undo (const char * undoitemname,void * data)
name|undo_history_init_undo
parameter_list|(
specifier|const
name|char
modifier|*
name|undoitemname
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|undo_history_st
modifier|*
name|st
init|=
name|data
decl_stmt|;
name|char
modifier|*
name|namelist
index|[
literal|2
index|]
decl_stmt|;
name|namelist
index|[
literal|0
index|]
operator|=
name|NULL
expr_stmt|;
name|namelist
index|[
literal|1
index|]
operator|=
operator|(
name|char
operator|*
operator|)
name|undoitemname
expr_stmt|;
name|gtk_clist_append
argument_list|(
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
argument_list|,
name|namelist
argument_list|)
expr_stmt|;
comment|/* force selection to bottom */
name|gtk_clist_select_row
argument_list|(
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
argument_list|,
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
operator|->
name|rows
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|st
operator|->
name|old_selection
operator|=
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
operator|->
name|rows
operator|-
literal|1
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_comment
comment|/* Ditto, but doesn't change selection */
end_comment

begin_function
specifier|static
name|int
DECL|function|undo_history_init_redo (const char * undoitemname,void * data)
name|undo_history_init_redo
parameter_list|(
specifier|const
name|char
modifier|*
name|undoitemname
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|undo_history_st
modifier|*
name|st
init|=
name|data
decl_stmt|;
name|char
modifier|*
name|namelist
index|[
literal|2
index|]
decl_stmt|;
name|namelist
index|[
literal|0
index|]
operator|=
name|NULL
expr_stmt|;
name|namelist
index|[
literal|1
index|]
operator|=
operator|(
name|char
operator|*
operator|)
name|undoitemname
expr_stmt|;
name|gtk_clist_append
argument_list|(
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
argument_list|,
name|namelist
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_comment
comment|/*************************************************************/
end_comment

begin_comment
comment|/* Publicly exported function */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|undo_history_new (GImage * gimage)
name|undo_history_new
parameter_list|(
name|GImage
modifier|*
name|gimage
parameter_list|)
block|{
name|undo_history_st
modifier|*
name|st
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
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_win
decl_stmt|;
name|st
operator|=
name|g_new0
argument_list|(
name|undo_history_st
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|st
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
comment|/* gimage signals */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"undo_event"
argument_list|,
name|undo_history_undo_event
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|undo_history_gimage_destroy_callback
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"clean"
argument_list|,
name|undo_history_clean_callback
argument_list|,
name|st
argument_list|)
expr_stmt|;
comment|/*  The shell and main vbox  */
name|st
operator|->
name|shell
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|st
operator|->
name|shell
argument_list|)
argument_list|,
literal|"undohistory"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_policy
argument_list|(
name|GTK_WINDOW
argument_list|(
name|st
operator|->
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|{
name|char
modifier|*
name|title
init|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s: undo history"
argument_list|)
argument_list|,
name|g_basename
argument_list|(
name|gimage_filename
argument_list|(
name|gimage
argument_list|)
argument_list|)
argument_list|)
decl_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|st
operator|->
name|shell
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
block|}
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|st
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
comment|/* handle the wm close event */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|st
operator|->
name|shell
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|undo_history_delete_callback
argument_list|)
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|st
operator|->
name|shell
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|undo_history_shell_destroy_callback
argument_list|)
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|scrolled_win
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* clist of undo actions */
name|st
operator|->
name|clist
operator|=
name|gtk_clist_new
argument_list|(
literal|2
argument_list|)
expr_stmt|;
name|gtk_clist_set_shadow_type
argument_list|(
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_clist_set_selection_mode
argument_list|(
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
argument_list|,
name|GTK_SELECTION_BROWSE
argument_list|)
expr_stmt|;
name|gtk_clist_set_reorderable
argument_list|(
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_clist_set_column_width
argument_list|(
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|52
argument_list|)
expr_stmt|;
name|undo_history_append_special
argument_list|(
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
argument_list|)
expr_stmt|;
comment|/* work out the initial contents */
name|undo_map_over_undo_stack
argument_list|(
name|st
operator|->
name|gimage
argument_list|,
name|undo_history_init_undo
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|undo_map_over_redo_stack
argument_list|(
name|st
operator|->
name|gimage
argument_list|,
name|undo_history_init_redo
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|st
operator|->
name|old_selection
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
operator|->
name|selection
operator|->
name|data
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|st
operator|->
name|clist
argument_list|)
argument_list|,
literal|"select_row"
argument_list|,
name|undo_history_select_row_callback
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|st
operator|->
name|clist
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|scrolled_win
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
name|GTK_WIDGET
argument_list|(
name|scrolled_win
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|st
operator|->
name|clist
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_ALWAYS
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|0
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
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"<< Undo"
argument_list|)
argument_list|)
expr_stmt|;
name|st
operator|->
name|undo_button
operator|=
name|button
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
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
name|undo_history_undo_callback
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Redo>>"
argument_list|)
argument_list|)
expr_stmt|;
name|st
operator|->
name|redo_button
operator|=
name|button
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
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
name|undo_history_redo_callback
argument_list|,
name|st
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
name|action_items
index|[
literal|0
index|]
operator|.
name|user_data
operator|=
name|st
expr_stmt|;
name|build_action_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|st
operator|->
name|shell
argument_list|)
argument_list|,
name|action_items
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|undo_history_set_sensitive
argument_list|(
name|st
argument_list|,
name|GTK_CLIST
argument_list|(
name|st
operator|->
name|clist
argument_list|)
operator|->
name|rows
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|st
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|st
operator|->
name|shell
return|;
block|}
end_function

end_unit

