begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"config.h"
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
file|"color.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|NUMCOLORRADIO
define|#
directive|define
name|NUMCOLORRADIO
value|2
end_define

begin_decl_stmt
DECL|variable|colorradio
specifier|static
name|GtkWidget
modifier|*
name|colorradio
index|[
name|NUMCOLORRADIO
index|]
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|color_type_restore (void)
name|void
name|color_type_restore
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|colorradio
index|[
name|pcvals
operator|.
name|colortype
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|create_colorpage (GtkNotebook * notebook)
name|void
name|create_colorpage
parameter_list|(
name|GtkNotebook
modifier|*
name|notebook
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|,
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Co_lor"
argument_list|)
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_int_radio_group_new
argument_list|(
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Color"
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|pcvals
operator|.
name|colortype
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"A_verage under brush"
argument_list|)
argument_list|,
name|COLOR_TYPE_AVERAGE
argument_list|,
operator|&
name|colorradio
index|[
name|COLOR_TYPE_AVERAGE
index|]
argument_list|,
name|_
argument_list|(
literal|"C_enter of brush"
argument_list|)
argument_list|,
name|COLOR_TYPE_CENTER
argument_list|,
operator|&
name|colorradio
index|[
name|COLOR_TYPE_CENTER
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|colorradio
index|[
name|COLOR_TYPE_AVERAGE
index|]
argument_list|,
name|_
argument_list|(
literal|"Color is computed from the average of all pixels under the brush"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|colorradio
index|[
name|COLOR_TYPE_CENTER
index|]
argument_list|,
name|_
argument_list|(
literal|"Samples the color from the pixel in the center of the brush"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|color_type_restore
argument_list|()
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
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
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|colornoiseadjust
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
literal|"Color _noise:"
argument_list|)
argument_list|,
literal|100
argument_list|,
operator|-
literal|1
argument_list|,
name|pcvals
operator|.
name|colornoise
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|5.0
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
literal|"Adds random noise to the color"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|colornoiseadjust
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
name|colornoise
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page_menu
argument_list|(
name|notebook
argument_list|,
name|vbox
argument_list|,
name|label
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

