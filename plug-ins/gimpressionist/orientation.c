begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
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
file|<string.h>
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
file|"gimpressionist.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
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
name|void
DECL|function|orientchange (GtkWidget * wg,void * d,int num)
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
if|if
condition|(
name|wg
condition|)
block|{
name|pcvals
operator|.
name|orienttype
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|d
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|orientradio
index|[
name|num
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
name|void
DECL|function|create_orientationpage (GtkNotebook * notebook)
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
name|label
decl_stmt|,
modifier|*
name|tmpw
decl_stmt|,
modifier|*
name|table
decl_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Or_ientation"
argument_list|)
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
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box1
argument_list|)
argument_list|,
name|table
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
name|table
argument_list|)
expr_stmt|;
name|orientnumadjust
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Directions:"
argument_list|)
argument_list|,
literal|150
argument_list|,
operator|-
literal|1
argument_list|,
name|pcvals
operator|.
name|orientnum
argument_list|,
literal|1.0
argument_list|,
literal|30.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"The number of directions (i.e. brushes) to use"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|orientnumadjust
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|pcvals
operator|.
name|orientnum
argument_list|)
expr_stmt|;
name|orientfirstadjust
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Start angle:"
argument_list|)
argument_list|,
literal|150
argument_list|,
operator|-
literal|1
argument_list|,
name|pcvals
operator|.
name|orientfirst
argument_list|,
literal|0.0
argument_list|,
literal|360.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"The starting angle of the first brush to create"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|orientfirstadjust
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|pcvals
operator|.
name|orientfirst
argument_list|)
expr_stmt|;
name|orientlastadjust
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"Angle span:"
argument_list|)
argument_list|,
literal|150
argument_list|,
operator|-
literal|1
argument_list|,
name|pcvals
operator|.
name|orientlast
argument_list|,
literal|0.0
argument_list|,
literal|360.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"The angle span of the first brush to create"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|orientlastadjust
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|pcvals
operator|.
name|orientlast
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
name|gtk_widget_show
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|tmpw
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|orientchange
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
literal|0
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
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
name|orientradio
index|[
literal|1
index|]
operator|=
name|tmpw
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|gtk_radio_button_get_group
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
name|g_signal_connect
argument_list|(
name|tmpw
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|orientchange
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
literal|1
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
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
name|orientradio
index|[
literal|2
index|]
operator|=
name|tmpw
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|gtk_radio_button_get_group
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
name|g_signal_connect
argument_list|(
name|tmpw
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|orientchange
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
literal|2
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
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
name|orientradio
index|[
literal|3
index|]
operator|=
name|tmpw
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|gtk_radio_button_get_group
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
name|g_signal_connect
argument_list|(
name|tmpw
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|orientchange
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
literal|3
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
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
name|gtk_radio_button_get_group
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
name|g_signal_connect
argument_list|(
name|tmpw
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|orientchange
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
literal|4
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
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
name|orientradio
index|[
literal|5
index|]
operator|=
name|tmpw
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|gtk_radio_button_get_group
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
name|g_signal_connect
argument_list|(
name|tmpw
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|orientchange
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
literal|5
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
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
name|orientradio
index|[
literal|6
index|]
operator|=
name|tmpw
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|gtk_radio_button_get_group
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
name|g_signal_connect
argument_list|(
name|tmpw
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|orientchange
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
literal|6
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
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
name|gtk_radio_button_get_group
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
name|g_signal_connect
argument_list|(
name|tmpw
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|orientchange
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
literal|7
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
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
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|orientradio
index|[
name|pcvals
operator|.
name|orienttype
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|tmpw
operator|=
name|gtk_button_new_from_stock
argument_list|(
name|GIMP_STOCK_EDIT
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
name|g_signal_connect
argument_list|(
name|tmpw
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|create_orientmap_dialog
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
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
name|label
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

