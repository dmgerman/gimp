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

begin_include
include|#
directive|include
file|<libgimp/stdplugins-intl.h>
end_include

begin_decl_stmt
DECL|variable|orientnumadjust
name|GtkObject
modifier|*
name|orientnumadjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|orientfirstadjust
name|GtkObject
modifier|*
name|orientfirstadjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|orientlastadjust
name|GtkObject
modifier|*
name|orientlastadjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|NUMORIENTRADIO
define|#
directive|define
name|NUMORIENTRADIO
value|8
end_define

begin_decl_stmt
DECL|variable|orientradio
name|GtkWidget
modifier|*
name|orientradio
index|[
name|NUMORIENTRADIO
index|]
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|orientchange (GtkWidget * wg,void * d,int num)
name|void
name|orientchange
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
name|pcvals
operator|.
name|orienttype
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
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|NUMORIENTRADIO
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
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|orientradio
index|[
name|i
index|]
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|orientradio
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
DECL|function|create_orientationpage (GtkNotebook * notebook)
name|void
name|create_orientationpage
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
decl_stmt|;
name|int
name|i
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
literal|"Orientation"
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
literal|"Orientation"
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
name|_
argument_list|(
literal|"Directions:"
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
literal|"Start angle:"
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
literal|"Angle span:"
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
name|orientnumadjust
operator|=
name|gtk_adjustment_new
argument_list|(
name|pcvals
operator|.
name|orientnum
argument_list|,
literal|1.0
argument_list|,
literal|31.0
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
name|orientnumadjust
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
literal|"The number of directions (i.e. brushes) to use"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
name|orientfirstadjust
operator|=
name|gtk_adjustment_new
argument_list|(
name|pcvals
operator|.
name|orientfirst
argument_list|,
literal|0.0
argument_list|,
literal|361.0
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
name|orientfirstadjust
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
literal|"The angle of the first brush to create"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
name|orientlastadjust
operator|=
name|gtk_adjustment_new
argument_list|(
name|pcvals
operator|.
name|orientlast
argument_list|,
literal|0.0
argument_list|,
literal|361.0
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
name|orientlastadjust
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
literal|"How large an angle-span to use (360 = full circle)"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmpw
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
name|_
argument_list|(
literal|"Orientation:"
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
name|i
operator|=
name|pcvals
operator|.
name|orienttype
expr_stmt|;
name|orientradio
index|[
literal|0
index|]
operator|=
name|tmpw
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Value"
argument_list|)
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
operator|(
name|GtkSignalFunc
operator|)
name|orientchange
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
name|_
argument_list|(
literal|"Let the value (brightness) of the region determine the direction of the stroke"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|==
literal|0
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
name|orientradio
index|[
literal|1
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
name|_
argument_list|(
literal|"Radius"
argument_list|)
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
name|orientchange
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
name|_
argument_list|(
literal|"The distance from the center of the image determines the direction of the stroke"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|==
literal|1
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
name|orientradio
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
name|_
argument_list|(
literal|"Random"
argument_list|)
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
name|orientchange
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
name|_
argument_list|(
literal|"Selects a random direction of each stroke"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|==
literal|2
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
name|orientradio
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
name|tmpw
argument_list|)
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Radial"
argument_list|)
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
name|orientchange
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
name|_
argument_list|(
literal|"Let the direction from the center determine the direction of the stroke"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|==
literal|3
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
name|orientradio
index|[
literal|4
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
name|_
argument_list|(
literal|"Flowing"
argument_list|)
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
name|orientchange
argument_list|,
operator|(
name|void
operator|*
operator|)
literal|4
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
literal|"The strokes follow a \"flowing\" pattern"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|==
literal|4
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
name|orientradio
index|[
literal|5
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
name|_
argument_list|(
literal|"Hue"
argument_list|)
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
name|orientchange
argument_list|,
operator|(
name|void
operator|*
operator|)
literal|5
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
literal|"The hue of the region determines the direction of the stroke"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|==
literal|5
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
name|orientradio
index|[
literal|6
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
name|_
argument_list|(
literal|"Adaptive"
argument_list|)
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
name|orientchange
argument_list|,
operator|(
name|void
operator|*
operator|)
literal|6
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
literal|"The direction that matches the original image the closest is selected"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|==
literal|6
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
name|orientradio
index|[
literal|7
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
name|_
argument_list|(
literal|"Manual"
argument_list|)
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
name|orientchange
argument_list|,
operator|(
name|void
operator|*
operator|)
literal|7
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
literal|"Manually specify the stroke orientation"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|==
literal|7
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
name|tmpw
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Edit..."
argument_list|)
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
name|create_orientmap_dialog
argument_list|,
name|NULL
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
literal|"Opens up the Orientation Map Editor"
argument_list|)
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

