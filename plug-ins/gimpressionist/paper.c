begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_CONFIG_H
end_ifdef

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|HAVE_DIRENT_H
define|#
directive|define
name|HAVE_DIRENT_H
end_define

begin_define
DECL|macro|HAVE_UNISTD_H
define|#
directive|define
name|HAVE_UNISTD_H
end_define

begin_endif
endif|#
directive|endif
end_endif

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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"gimpressionist.h"
end_include

begin_include
include|#
directive|include
file|"ppmtool.h"
end_include

begin_include
include|#
directive|include
file|<libgimp/stdplugins-intl.h>
end_include

begin_decl_stmt
DECL|variable|paperlist
name|GtkWidget
modifier|*
name|paperlist
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paperprev
name|GtkWidget
modifier|*
name|paperprev
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paperreliefadjust
name|GtkObject
modifier|*
name|paperreliefadjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paperscaleadjust
name|GtkObject
modifier|*
name|paperscaleadjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paperinvert
name|GtkWidget
modifier|*
name|paperinvert
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paperoverlay
name|GtkWidget
modifier|*
name|paperoverlay
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|updatepaperprev (char * fn)
name|void
name|updatepaperprev
parameter_list|(
name|char
modifier|*
name|fn
parameter_list|)
block|{
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
name|char
name|buf
index|[
literal|100
index|]
decl_stmt|;
if|if
condition|(
operator|!
name|fn
condition|)
block|{
name|memset
argument_list|(
name|buf
argument_list|,
literal|0
argument_list|,
literal|100
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
literal|100
condition|;
name|i
operator|++
control|)
block|{
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|paperprev
argument_list|)
argument_list|,
name|buf
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
literal|100
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|double
name|sc
decl_stmt|;
name|struct
name|ppm
name|p
init|=
block|{
literal|0
block|,
literal|0
block|,
name|NULL
block|}
decl_stmt|;
name|loadppm
argument_list|(
name|fn
argument_list|,
operator|&
name|p
argument_list|)
expr_stmt|;
name|sc
operator|=
name|p
operator|.
name|width
operator|>
name|p
operator|.
name|height
condition|?
name|p
operator|.
name|width
else|:
name|p
operator|.
name|height
expr_stmt|;
name|sc
operator|=
literal|100.0
operator|/
name|sc
expr_stmt|;
name|resize
argument_list|(
operator|&
name|p
argument_list|,
name|p
operator|.
name|width
operator|*
name|sc
argument_list|,
name|p
operator|.
name|height
operator|*
name|sc
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
literal|100
condition|;
name|i
operator|++
control|)
block|{
name|int
name|k
init|=
name|i
operator|*
name|p
operator|.
name|width
operator|*
literal|3
decl_stmt|;
name|memset
argument_list|(
name|buf
argument_list|,
literal|0
argument_list|,
literal|100
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|<
name|p
operator|.
name|height
condition|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|p
operator|.
name|width
condition|;
name|j
operator|++
control|)
name|buf
index|[
name|j
index|]
operator|=
name|p
operator|.
name|col
index|[
name|k
operator|+
name|j
operator|*
literal|3
index|]
expr_stmt|;
if|if
condition|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paperinvert
argument_list|)
operator|->
name|active
condition|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|p
operator|.
name|width
condition|;
name|j
operator|++
control|)
name|buf
index|[
name|j
index|]
operator|=
literal|255
operator|-
name|buf
index|[
name|j
index|]
expr_stmt|;
block|}
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|paperprev
argument_list|)
argument_list|,
name|buf
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
literal|100
argument_list|)
expr_stmt|;
block|}
name|killppm
argument_list|(
operator|&
name|p
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_draw
argument_list|(
name|paperprev
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|selectpaper (GtkWidget * wg,GtkWidget * p)
name|void
name|selectpaper
parameter_list|(
name|GtkWidget
modifier|*
name|wg
parameter_list|,
name|GtkWidget
modifier|*
name|p
parameter_list|)
block|{
name|GList
modifier|*
name|h
init|=
name|GTK_LIST
argument_list|(
name|p
argument_list|)
operator|->
name|selection
decl_stmt|;
name|GtkWidget
modifier|*
name|tmpw
decl_stmt|;
name|char
modifier|*
name|l
decl_stmt|;
specifier|static
name|char
name|fname
index|[
literal|200
index|]
decl_stmt|;
if|if
condition|(
operator|!
name|h
condition|)
return|return;
name|tmpw
operator|=
name|h
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|tmpw
condition|)
return|return;
name|gtk_label_get
argument_list|(
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|tmpw
argument_list|)
operator|->
name|child
argument_list|)
argument_list|,
operator|&
name|l
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|fname
argument_list|,
literal|"Paper/%s"
argument_list|,
name|l
argument_list|)
expr_stmt|;
name|strcpy
argument_list|(
name|pcvals
operator|.
name|selectedpaper
argument_list|,
name|fname
argument_list|)
expr_stmt|;
name|updatepaperprev
argument_list|(
name|fname
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|create_paperpage (GtkNotebook * notebook)
name|void
name|create_paperpage
parameter_list|(
name|GtkNotebook
modifier|*
name|notebook
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|box1
decl_stmt|,
modifier|*
name|thispage
decl_stmt|,
modifier|*
name|box2
decl_stmt|;
name|GtkWidget
modifier|*
name|labelbox
decl_stmt|,
modifier|*
name|menubox
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_win
decl_stmt|,
modifier|*
name|list
decl_stmt|;
name|GtkWidget
modifier|*
name|tmpw
decl_stmt|;
name|labelbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|tmpw
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Paper"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|labelbox
argument_list|)
argument_list|,
name|tmpw
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show_all
argument_list|(
name|labelbox
argument_list|)
expr_stmt|;
name|menubox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|tmpw
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Paper"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|menubox
argument_list|)
argument_list|,
name|tmpw
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show_all
argument_list|(
name|menubox
argument_list|)
expr_stmt|;
name|thispage
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|thispage
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|thispage
argument_list|)
expr_stmt|;
name|box1
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|thispage
argument_list|)
argument_list|,
name|box1
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
name|box1
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
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box1
argument_list|)
argument_list|,
name|scrolled_win
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
name|scrolled_win
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|scrolled_win
argument_list|,
literal|150
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|paperlist
operator|=
name|list
operator|=
name|gtk_list_new
argument_list|()
expr_stmt|;
name|gtk_list_set_selection_mode
argument_list|(
name|GTK_LIST
argument_list|(
name|list
argument_list|)
argument_list|,
name|GTK_SELECTION_BROWSE
argument_list|)
expr_stmt|;
if|#
directive|if
name|GTK_MINOR_VERSION
operator|>
literal|0
name|gtk_scrolled_window_add_with_viewport
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|list
argument_list|)
expr_stmt|;
else|#
directive|else
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|list
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gtk_widget_show
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|readdirintolist
argument_list|(
literal|"Paper"
argument_list|,
name|list
argument_list|,
name|pcvals
operator|.
name|selectedpaper
argument_list|)
expr_stmt|;
name|box2
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box1
argument_list|)
argument_list|,
name|box2
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
name|box2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|box2
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|tmpw
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Paper Preview:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box2
argument_list|)
argument_list|,
name|tmpw
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
name|tmpw
argument_list|)
expr_stmt|;
name|paperprev
operator|=
name|tmpw
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_GRAYSCALE
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|tmpw
argument_list|)
argument_list|,
literal|100
argument_list|,
literal|100
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box2
argument_list|)
argument_list|,
name|tmpw
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
comment|/* updatepaperprev(NULL); */
name|paperinvert
operator|=
name|tmpw
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Invert"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box2
argument_list|)
argument_list|,
name|tmpw
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tmpw
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|selectpaper
argument_list|)
argument_list|,
name|list
argument_list|)
expr_stmt|;
name|gtk_tooltips_set_tip
argument_list|(
name|GTK_TOOLTIPS
argument_list|(
name|tooltips
argument_list|)
argument_list|,
name|tmpw
argument_list|,
name|_
argument_list|(
literal|"Inverts the Papers texture"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pcvals
operator|.
name|paperinvert
condition|)
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|paperoverlay
operator|=
name|tmpw
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Overlay"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box2
argument_list|)
argument_list|,
name|tmpw
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
name|gtk_tooltips_set_tip
argument_list|(
name|GTK_TOOLTIPS
argument_list|(
name|tooltips
argument_list|)
argument_list|,
name|tmpw
argument_list|,
name|_
argument_list|(
literal|"Applies the paper as it is (without embossing it)"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pcvals
operator|.
name|paperoverlay
condition|)
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|box1
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|thispage
argument_list|)
argument_list|,
name|box1
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box1
argument_list|)
expr_stmt|;
name|box2
operator|=
name|gtk_vbox_new
argument_list|(
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box1
argument_list|)
argument_list|,
name|box2
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
name|box2
argument_list|)
expr_stmt|;
name|tmpw
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Scale:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box2
argument_list|)
argument_list|,
name|tmpw
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
name|tmpw
argument_list|)
expr_stmt|;
name|tmpw
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Relief:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box2
argument_list|)
argument_list|,
name|tmpw
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
name|tmpw
argument_list|)
expr_stmt|;
name|box2
operator|=
name|gtk_vbox_new
argument_list|(
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box1
argument_list|)
argument_list|,
name|box2
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box2
argument_list|)
expr_stmt|;
name|paperscaleadjust
operator|=
name|gtk_adjustment_new
argument_list|(
name|pcvals
operator|.
name|paperscale
argument_list|,
literal|3.0
argument_list|,
literal|151.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|tmpw
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|paperscaleadjust
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|GTK_WIDGET
argument_list|(
name|tmpw
argument_list|)
argument_list|,
literal|150
argument_list|,
literal|30
argument_list|)
expr_stmt|;
name|gtk_scale_set_draw_value
argument_list|(
name|GTK_SCALE
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_scale_set_digits
argument_list|(
name|GTK_SCALE
argument_list|(
name|tmpw
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box2
argument_list|)
argument_list|,
name|tmpw
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
name|tmpw
argument_list|)
expr_stmt|;
name|gtk_tooltips_set_tip
argument_list|(
name|GTK_TOOLTIPS
argument_list|(
name|tooltips
argument_list|)
argument_list|,
name|tmpw
argument_list|,
name|_
argument_list|(
literal|"Specifies the scale of the texture (in percent of original file)"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|paperreliefadjust
operator|=
name|gtk_adjustment_new
argument_list|(
name|pcvals
operator|.
name|paperrelief
argument_list|,
literal|0.0
argument_list|,
literal|101.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|tmpw
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|paperreliefadjust
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|GTK_WIDGET
argument_list|(
name|tmpw
argument_list|)
argument_list|,
literal|150
argument_list|,
literal|30
argument_list|)
expr_stmt|;
name|gtk_scale_set_draw_value
argument_list|(
name|GTK_SCALE
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_scale_set_digits
argument_list|(
name|GTK_SCALE
argument_list|(
name|tmpw
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box2
argument_list|)
argument_list|,
name|tmpw
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
name|tmpw
argument_list|)
expr_stmt|;
name|gtk_tooltips_set_tip
argument_list|(
name|GTK_TOOLTIPS
argument_list|(
name|tooltips
argument_list|)
argument_list|,
name|tmpw
argument_list|,
name|_
argument_list|(
literal|"Specifies the amount of embossing to apply to the image (in percent)"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list
argument_list|)
argument_list|,
literal|"selection_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|selectpaper
argument_list|)
argument_list|,
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_LIST
argument_list|(
name|list
argument_list|)
operator|->
name|selection
condition|)
name|gtk_list_select_item
argument_list|(
name|GTK_LIST
argument_list|(
name|list
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|selectpaper
argument_list|(
name|NULL
argument_list|,
name|list
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page_menu
argument_list|(
name|notebook
argument_list|,
name|thispage
argument_list|,
name|labelbox
argument_list|,
name|menubox
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

