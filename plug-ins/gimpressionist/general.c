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
file|<sys/types.h>
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

begin_define
DECL|macro|COLORBUTTONWIDTH
define|#
directive|define
name|COLORBUTTONWIDTH
value|30
end_define

begin_define
DECL|macro|COLORBUTTONHEIGHT
define|#
directive|define
name|COLORBUTTONHEIGHT
value|20
end_define

begin_decl_stmt
DECL|variable|generaldarkedgeadjust
name|GtkObject
modifier|*
name|generaldarkedgeadjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|generalpaintedges
name|GtkWidget
modifier|*
name|generalpaintedges
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|generaltileable
name|GtkWidget
modifier|*
name|generaltileable
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|generaldropshadow
name|GtkWidget
modifier|*
name|generaldropshadow
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|generalshadowadjust
name|GtkObject
modifier|*
name|generalshadowadjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|generalshadowdepth
name|GtkObject
modifier|*
name|generalshadowdepth
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|generalshadowblur
name|GtkObject
modifier|*
name|generalshadowblur
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|devthreshadjust
name|GtkObject
modifier|*
name|devthreshadjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|NUMGENERALBGRADIO
define|#
directive|define
name|NUMGENERALBGRADIO
value|4
end_define

begin_decl_stmt
DECL|variable|generalbgradio
name|GtkWidget
modifier|*
name|generalbgradio
index|[
name|NUMGENERALBGRADIO
index|]
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|generalbgchange (GtkWidget * wg,void * d,int num)
name|void
name|generalbgchange
parameter_list|(
name|GtkWidget
modifier|*
name|wg
parameter_list|,
name|void
modifier|*
name|d
parameter_list|,
name|int
name|num
parameter_list|)
block|{
name|int
name|n
decl_stmt|;
if|if
condition|(
name|wg
condition|)
block|{
name|n
operator|=
operator|(
name|long
operator|)
name|d
expr_stmt|;
if|if
condition|(
operator|!
name|img_has_alpha
operator|&&
operator|(
name|n
operator|==
literal|3
operator|)
condition|)
name|n
operator|=
literal|1
expr_stmt|;
name|pcvals
operator|.
name|generalbgtype
operator|=
name|n
expr_stmt|;
block|}
else|else
block|{
name|int
name|i
decl_stmt|;
name|n
operator|=
name|num
expr_stmt|;
if|if
condition|(
operator|!
name|img_has_alpha
operator|&&
operator|(
name|n
operator|==
literal|3
operator|)
condition|)
name|n
operator|=
literal|1
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|NUMGENERALBGRADIO
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|i
operator|!=
name|n
condition|)
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|generalbgradio
index|[
name|i
index|]
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|generalbgradio
index|[
name|n
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|drawcolor (GtkWidget * w)
name|void
name|drawcolor
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|)
block|{
specifier|static
name|GtkWidget
modifier|*
name|lastw
init|=
name|NULL
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
name|guchar
name|buf
index|[
name|COLORBUTTONWIDTH
operator|*
literal|3
index|]
decl_stmt|;
if|if
condition|(
name|w
condition|)
name|lastw
operator|=
name|w
expr_stmt|;
else|else
name|w
operator|=
name|lastw
expr_stmt|;
if|if
condition|(
operator|!
name|w
condition|)
return|return;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|COLORBUTTONWIDTH
condition|;
name|x
operator|++
control|)
name|memcpy
argument_list|(
operator|&
name|buf
index|[
name|x
operator|*
literal|3
index|]
argument_list|,
operator|&
name|pcvals
operator|.
name|color
argument_list|,
literal|3
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|COLORBUTTONHEIGHT
condition|;
name|y
operator|++
control|)
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|w
argument_list|)
argument_list|,
name|buf
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|COLORBUTTONWIDTH
argument_list|)
expr_stmt|;
name|gtk_widget_draw
argument_list|(
name|w
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|selectcolor_ok (GtkWidget * w,gpointer d)
name|void
name|selectcolor_ok
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|d
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|win
init|=
operator|(
name|GtkWidget
operator|*
operator|)
name|d
decl_stmt|;
name|gdouble
name|tmpcol
index|[
literal|3
index|]
decl_stmt|;
name|gtk_color_selection_get_color
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|win
argument_list|)
operator|->
name|colorsel
argument_list|)
argument_list|,
name|tmpcol
argument_list|)
expr_stmt|;
name|pcvals
operator|.
name|color
index|[
literal|0
index|]
operator|=
name|tmpcol
index|[
literal|0
index|]
operator|*
literal|255.0
expr_stmt|;
name|pcvals
operator|.
name|color
index|[
literal|1
index|]
operator|=
name|tmpcol
index|[
literal|1
index|]
operator|*
literal|255.0
expr_stmt|;
name|pcvals
operator|.
name|color
index|[
literal|2
index|]
operator|=
name|tmpcol
index|[
literal|2
index|]
operator|*
literal|255.0
expr_stmt|;
name|drawcolor
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|win
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|selectcolor (void)
name|void
name|selectcolor
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkWidget
modifier|*
name|window
init|=
name|NULL
decl_stmt|;
name|gdouble
name|tmpcol
index|[
literal|3
index|]
decl_stmt|;
if|if
condition|(
name|window
condition|)
block|{
name|gtk_widget_show
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|gdk_window_raise
argument_list|(
name|window
operator|->
name|window
argument_list|)
expr_stmt|;
return|return;
block|}
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|generalbgradio
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|window
operator|=
name|gtk_color_selection_dialog_new
argument_list|(
literal|"Color Selection Dialog"
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|window
argument_list|)
expr_stmt|;
name|tmpcol
index|[
literal|0
index|]
operator|=
name|pcvals
operator|.
name|color
index|[
literal|0
index|]
operator|/
literal|255.0
expr_stmt|;
name|tmpcol
index|[
literal|1
index|]
operator|=
name|pcvals
operator|.
name|color
index|[
literal|1
index|]
operator|/
literal|255.0
expr_stmt|;
name|tmpcol
index|[
literal|2
index|]
operator|=
name|pcvals
operator|.
name|color
index|[
literal|2
index|]
operator|/
literal|255.0
expr_stmt|;
name|gtk_color_selection_set_color
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|window
argument_list|)
operator|->
name|colorsel
argument_list|)
argument_list|,
name|tmpcol
argument_list|)
expr_stmt|;
comment|/*   gtk_signal_connect(GTK_OBJECT(GTK_COLOR_SELECTION_DIALOG (window)->colorsel), 		     "color_changed", 		     GTK_SIGNAL_FUNC(color_selection_changed), 		     window); 		     */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|window
argument_list|)
operator|->
name|ok_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|selectcolor_ok
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|window
argument_list|)
operator|->
name|cancel_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|window
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|create_generalpage (GtkNotebook * notebook)
name|void
name|create_generalpage
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
name|box2
decl_stmt|,
modifier|*
name|box3
decl_stmt|,
modifier|*
name|box4
decl_stmt|,
modifier|*
name|thispage
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
name|tmpw
decl_stmt|,
modifier|*
name|colbutton
decl_stmt|;
name|char
name|title
index|[
literal|100
index|]
decl_stmt|;
name|sprintf
argument_list|(
name|title
argument_list|,
literal|"General"
argument_list|)
expr_stmt|;
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
name|title
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
name|title
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
name|gtk_container_border_width
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
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
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
literal|"Edge darken:"
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
name|generaldarkedgeadjust
operator|=
name|gtk_adjustment_new
argument_list|(
name|pcvals
operator|.
name|generaldarkedge
argument_list|,
literal|0.0
argument_list|,
literal|2.0
argument_list|,
literal|0.1
argument_list|,
literal|0.1
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
name|generaldarkedgeadjust
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
literal|"How much to \"darken\" the edges of each brush stroke"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|box2
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
literal|"Background:"
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
name|box3
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
name|box2
argument_list|)
argument_list|,
name|box3
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
name|box3
argument_list|)
expr_stmt|;
name|generalbgradio
index|[
literal|1
index|]
operator|=
name|tmpw
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|NULL
argument_list|,
literal|"Keep original"
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box3
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tmpw
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|generalbgchange
argument_list|,
operator|(
name|void
operator|*
operator|)
literal|1
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
literal|"Preserve the original image as a background"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pcvals
operator|.
name|generalbgtype
operator|==
literal|1
condition|)
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|generalbgradio
index|[
literal|2
index|]
operator|=
name|tmpw
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|)
argument_list|,
literal|"From paper"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box3
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
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|FALSE
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
operator|(
name|GtkSignalFunc
operator|)
name|generalbgchange
argument_list|,
operator|(
name|void
operator|*
operator|)
literal|2
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
literal|"Copy the texture of the selected paper as a background"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pcvals
operator|.
name|generalbgtype
operator|==
literal|2
condition|)
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|box3
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
name|box2
argument_list|)
argument_list|,
name|box3
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
name|box3
argument_list|)
expr_stmt|;
name|box4
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
name|box3
argument_list|)
argument_list|,
name|box4
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
name|box4
argument_list|)
expr_stmt|;
name|generalbgradio
index|[
literal|0
index|]
operator|=
name|tmpw
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|)
argument_list|,
literal|"Solid"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box4
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
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|FALSE
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
operator|(
name|GtkSignalFunc
operator|)
name|generalbgchange
argument_list|,
operator|(
name|void
operator|*
operator|)
literal|0
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
literal|"Solid colored background"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pcvals
operator|.
name|generalbgtype
operator|==
literal|0
condition|)
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|colbutton
operator|=
name|tmpw
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box4
argument_list|)
argument_list|,
name|tmpw
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
operator|(
name|GtkSignalFunc
operator|)
name|selectcolor
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tmpw
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
name|tmpw
argument_list|)
argument_list|,
name|COLORBUTTONWIDTH
argument_list|,
name|COLORBUTTONHEIGHT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|colbutton
argument_list|)
argument_list|,
name|tmpw
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
name|drawcolor
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
name|generalbgradio
index|[
literal|3
index|]
operator|=
name|tmpw
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|generalbgradio
index|[
literal|0
index|]
argument_list|)
argument_list|)
argument_list|,
literal|"Transparent"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box3
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
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|FALSE
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
operator|(
name|GtkSignalFunc
operator|)
name|generalbgchange
argument_list|,
operator|(
name|void
operator|*
operator|)
literal|3
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
literal|"Use a transparent background; Only the strokes painted will be visible"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|img_has_alpha
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|tmpw
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|pcvals
operator|.
name|generalbgtype
operator|==
literal|3
condition|)
name|gtk_toggle_button_set_state
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
name|thispage
argument_list|)
argument_list|,
name|box1
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
name|generalpaintedges
operator|=
name|tmpw
operator|=
name|gtk_check_button_new_with_label
argument_list|(
literal|"Paint edges"
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
name|gtk_toggle_button_set_state
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
literal|"Selects if to place strokes all the way out to the edges of the image"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pcvals
operator|.
name|generalpaintedges
condition|)
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|generaltileable
operator|=
name|tmpw
operator|=
name|gtk_check_button_new_with_label
argument_list|(
literal|"Tileable"
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
name|gtk_toggle_button_set_state
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
literal|"Selects if the resulting image should be seamlessly tileable"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pcvals
operator|.
name|generaltileable
condition|)
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|box2
operator|=
name|gtk_hbox_new
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
name|generaldropshadow
operator|=
name|tmpw
operator|=
name|gtk_check_button_new_with_label
argument_list|(
literal|"Drop Shadow"
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
name|gtk_toggle_button_set_state
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
literal|"Adds a shadow effect to each brush stroke"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pcvals
operator|.
name|generaldropshadow
condition|)
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|generalshadowadjust
operator|=
name|gtk_adjustment_new
argument_list|(
name|pcvals
operator|.
name|generalshadowdarkness
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|0.1
argument_list|,
literal|0.1
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
name|generalshadowadjust
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
literal|"How much to \"darken\" the drop shadow"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|box2
operator|=
name|gtk_hbox_new
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
literal|"Shadow depth:"
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
name|generalshadowdepth
operator|=
name|gtk_adjustment_new
argument_list|(
name|pcvals
operator|.
name|generalshadowdarkness
argument_list|,
literal|0.0
argument_list|,
literal|100.0
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
name|generalshadowdepth
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
literal|0
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
literal|"The depth of the drop shadow, i.e. how far apart from the object it should be"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|box2
operator|=
name|gtk_hbox_new
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
literal|"Shadow blur:"
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
name|generalshadowblur
operator|=
name|gtk_adjustment_new
argument_list|(
name|pcvals
operator|.
name|generalshadowdarkness
argument_list|,
literal|0.0
argument_list|,
literal|100.0
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
name|generalshadowblur
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
literal|0
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
literal|"How much to blur the drop shadow"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|box2
operator|=
name|gtk_hbox_new
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
literal|"Deviation threshold:"
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
name|devthreshadjust
operator|=
name|gtk_adjustment_new
argument_list|(
name|pcvals
operator|.
name|devthresh
argument_list|,
literal|0.0
argument_list|,
literal|2.0
argument_list|,
literal|0.1
argument_list|,
literal|0.1
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
name|devthreshadjust
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
literal|"A bailout-value for adaptive selections"
argument_list|,
name|NULL
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

