begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"tips_dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"interface.h"
end_include

begin_include
include|#
directive|include
file|"wilber.h"
end_include

begin_define
DECL|macro|TIPS_FILE_NAME
define|#
directive|define
name|TIPS_FILE_NAME
value|"gimp_tips.txt"
end_define

begin_function_decl
specifier|static
name|int
name|tips_dialog_hide
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
name|int
name|tips_show_next
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
name|tips_toggle_update
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
name|read_tips_file
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|tips_dialog
specifier|static
name|GtkWidget
modifier|*
name|tips_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tips_label
specifier|static
name|GtkWidget
modifier|*
name|tips_label
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tips_text
specifier|static
name|char
modifier|*
modifier|*
name|tips_text
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tips_count
specifier|static
name|int
name|tips_count
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|old_show_tips
specifier|static
name|int
name|old_show_tips
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|tips_dialog_create ()
name|tips_dialog_create
parameter_list|()
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox1
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox2
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|button_close
decl_stmt|;
name|GtkWidget
modifier|*
name|button_next
decl_stmt|;
name|GtkWidget
modifier|*
name|button_prev
decl_stmt|;
name|GtkWidget
modifier|*
name|button_check
decl_stmt|;
name|guchar
modifier|*
name|temp
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|int
name|x
decl_stmt|;
name|int
name|y
decl_stmt|;
if|if
condition|(
name|tips_count
operator|==
literal|0
condition|)
block|{
name|temp
operator|=
name|g_malloc
argument_list|(
literal|512
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|temp
argument_list|,
literal|"%s/%s"
argument_list|,
name|DATADIR
argument_list|,
name|TIPS_FILE_NAME
argument_list|)
expr_stmt|;
name|read_tips_file
argument_list|(
name|temp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|last_tip
operator|>=
name|tips_count
operator|||
name|last_tip
operator|<
literal|0
condition|)
name|last_tip
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|tips_dialog
condition|)
block|{
name|tips_dialog
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_DIALOG
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
literal|"GIMP Tip of the day"
argument_list|)
expr_stmt|;
name|gtk_window_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
name|GTK_WIN_POS_CENTER
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tips_dialog
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|tips_dialog_hide
argument_list|)
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
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|tips_dialog
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
name|hbox1
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox1
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox1
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
name|hbox1
argument_list|)
expr_stmt|;
name|hbox2
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox2
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox2
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
name|hbox2
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_COLOR
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|wilber_width
argument_list|,
name|wilber_height
argument_list|)
expr_stmt|;
name|temp
operator|=
name|g_malloc
argument_list|(
name|wilber_width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|src
operator|=
name|wilber_data
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|wilber_height
condition|;
name|y
operator|++
control|)
block|{
name|dest
operator|=
name|temp
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|wilber_width
condition|;
name|x
operator|++
control|)
block|{
name|HEADER_PIXEL
argument_list|(
name|src
argument_list|,
name|dest
argument_list|)
expr_stmt|;
name|dest
operator|+=
literal|3
expr_stmt|;
block|}
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|temp
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|wilber_width
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox1
argument_list|)
argument_list|,
name|preview
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|tips_label
operator|=
name|gtk_label_new
argument_list|(
name|tips_text
index|[
name|last_tip
index|]
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|tips_label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox1
argument_list|)
argument_list|,
name|tips_label
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tips_label
argument_list|)
expr_stmt|;
name|button_close
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|"Close"
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button_close
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|tips_dialog_hide
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox2
argument_list|)
argument_list|,
name|button_close
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
name|button_close
argument_list|)
expr_stmt|;
name|button_next
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|"Next Tip"
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button_next
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|tips_show_next
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
literal|"next"
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox2
argument_list|)
argument_list|,
name|button_next
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
name|button_next
argument_list|)
expr_stmt|;
name|button_prev
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|"Prev. Tip"
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button_prev
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|tips_show_next
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
literal|"prev"
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox2
argument_list|)
argument_list|,
name|button_prev
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
name|button_prev
argument_list|)
expr_stmt|;
name|button_check
operator|=
name|gtk_check_button_new_with_label
argument_list|(
literal|"Show tip next time"
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button_check
argument_list|)
argument_list|,
name|show_tips
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button_check
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|tips_toggle_update
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|show_tips
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox2
argument_list|)
argument_list|,
name|button_check
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
name|button_check
argument_list|)
expr_stmt|;
name|old_show_tips
operator|=
name|show_tips
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|tips_dialog
argument_list|)
condition|)
block|{
name|gtk_widget_show
argument_list|(
name|tips_dialog
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdk_window_raise
argument_list|(
name|tips_dialog
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|tips_dialog_hide (GtkWidget * widget,gpointer data)
name|tips_dialog_hide
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GList
modifier|*
name|update
init|=
name|NULL
decl_stmt|;
comment|/* options that should be updated in .gimprc */
name|GList
modifier|*
name|remove
init|=
name|NULL
decl_stmt|;
comment|/* options that should be commented out */
name|gtk_widget_hide
argument_list|(
name|tips_dialog
argument_list|)
expr_stmt|;
name|update
operator|=
name|g_list_append
argument_list|(
name|update
argument_list|,
literal|"last-tip-shown"
argument_list|)
expr_stmt|;
comment|/* always save this */
if|if
condition|(
name|show_tips
operator|!=
name|old_show_tips
condition|)
block|{
name|update
operator|=
name|g_list_append
argument_list|(
name|update
argument_list|,
literal|"show-tips"
argument_list|)
expr_stmt|;
name|remove
operator|=
name|g_list_append
argument_list|(
name|remove
argument_list|,
literal|"dont-show-tips"
argument_list|)
expr_stmt|;
name|old_show_tips
operator|=
name|show_tips
expr_stmt|;
block|}
name|last_tip
operator|++
expr_stmt|;
name|save_gimprc
argument_list|(
operator|&
name|update
argument_list|,
operator|&
name|remove
argument_list|)
expr_stmt|;
name|last_tip
operator|--
expr_stmt|;
name|g_list_free
argument_list|(
name|update
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|remove
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|tips_show_next (GtkWidget * widget,gpointer data)
name|tips_show_next
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
operator|(
name|char
operator|*
operator|)
name|data
argument_list|,
literal|"prev"
argument_list|)
condition|)
block|{
name|last_tip
operator|--
expr_stmt|;
if|if
condition|(
name|last_tip
operator|<
literal|0
condition|)
name|last_tip
operator|=
name|tips_count
operator|-
literal|1
expr_stmt|;
block|}
else|else
block|{
name|last_tip
operator|++
expr_stmt|;
if|if
condition|(
name|last_tip
operator|>=
name|tips_count
condition|)
name|last_tip
operator|=
literal|0
expr_stmt|;
block|}
name|gtk_label_set
argument_list|(
name|GTK_LABEL
argument_list|(
name|tips_label
argument_list|)
argument_list|,
name|tips_text
index|[
name|last_tip
index|]
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tips_toggle_update (GtkWidget * widget,gpointer data)
name|tips_toggle_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|int
modifier|*
name|toggle_val
decl_stmt|;
name|toggle_val
operator|=
operator|(
name|int
operator|*
operator|)
name|data
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|store_tip (char * str)
name|store_tip
parameter_list|(
name|char
modifier|*
name|str
parameter_list|)
block|{
name|tips_count
operator|++
expr_stmt|;
name|tips_text
operator|=
name|g_realloc
argument_list|(
name|tips_text
argument_list|,
sizeof|sizeof
argument_list|(
name|char
operator|*
argument_list|)
operator|*
name|tips_count
argument_list|)
expr_stmt|;
name|tips_text
index|[
name|tips_count
operator|-
literal|1
index|]
operator|=
name|str
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|read_tips_file (char * filename)
name|read_tips_file
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
block|{
name|FILE
modifier|*
name|fp
decl_stmt|;
name|char
modifier|*
name|tip
init|=
name|NULL
decl_stmt|;
name|char
modifier|*
name|str
init|=
name|NULL
decl_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"rt"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fp
condition|)
block|{
name|store_tip
argument_list|(
literal|"Your GIMP tips file appears to be missing!\n"
literal|"There should be a file called "
name|TIPS_FILE_NAME
literal|" in the\n"
literal|"GIMP data directory.  Please check your installation."
argument_list|)
expr_stmt|;
return|return;
block|}
name|str
operator|=
name|g_new
argument_list|(
name|char
argument_list|,
literal|1024
argument_list|)
expr_stmt|;
while|while
condition|(
operator|!
name|feof
argument_list|(
name|fp
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|fgets
argument_list|(
name|str
argument_list|,
literal|1024
argument_list|,
name|fp
argument_list|)
condition|)
continue|continue;
if|if
condition|(
name|str
index|[
literal|0
index|]
operator|==
literal|'#'
operator|||
name|str
index|[
literal|0
index|]
operator|==
literal|'\n'
condition|)
block|{
if|if
condition|(
name|tip
operator|!=
name|NULL
condition|)
block|{
name|tip
index|[
name|strlen
argument_list|(
name|tip
argument_list|)
operator|-
literal|2
index|]
operator|=
literal|'\000'
expr_stmt|;
name|store_tip
argument_list|(
name|tip
argument_list|)
expr_stmt|;
name|tip
operator|=
name|NULL
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|tip
operator|==
name|NULL
condition|)
block|{
name|tip
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|str
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|strcpy
argument_list|(
name|tip
argument_list|,
name|str
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tip
operator|=
name|g_realloc
argument_list|(
name|tip
argument_list|,
name|strlen
argument_list|(
name|tip
argument_list|)
operator|+
name|strlen
argument_list|(
name|str
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|strcat
argument_list|(
name|tip
argument_list|,
name|str
argument_list|)
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|tip
operator|!=
name|NULL
condition|)
name|store_tip
argument_list|(
name|tip
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

