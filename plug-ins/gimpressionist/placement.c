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
file|"placement.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|NUMPLACERADIO
define|#
directive|define
name|NUMPLACERADIO
value|2
end_define

begin_decl_stmt
DECL|variable|placeradio
specifier|static
name|GtkWidget
modifier|*
name|placeradio
index|[
name|NUMPLACERADIO
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|placecenter
specifier|static
name|GtkWidget
modifier|*
name|placecenter
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushdensityadjust
specifier|static
name|GtkObject
modifier|*
name|brushdensityadjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|place_restore ()
name|void
name|place_restore
parameter_list|()
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|placeradio
index|[
name|pcvals
operator|.
name|placetype
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|placecenter
argument_list|)
argument_list|,
name|pcvals
operator|.
name|placecenter
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|brushdensityadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|brushdensity
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|place_store ()
name|void
name|place_store
parameter_list|()
block|{
name|pcvals
operator|.
name|placecenter
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|placecenter
argument_list|)
operator|->
name|active
expr_stmt|;
block|}
end_function

begin_function
DECL|function|create_placementpage (GtkNotebook * notebook)
name|void
name|create_placementpage
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
name|tmpw
decl_stmt|,
modifier|*
name|table
decl_stmt|,
modifier|*
name|frame
decl_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Pl_acement"
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
literal|"Placement"
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
name|placetype
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Randomly"
argument_list|)
argument_list|,
name|PLACEMENT_TYPE_RANDOM
argument_list|,
operator|&
name|placeradio
index|[
name|PLACEMENT_TYPE_RANDOM
index|]
argument_list|,
name|_
argument_list|(
literal|"Evenly distributed"
argument_list|)
argument_list|,
name|PLACEMENT_TYPE_EVEN_DIST
argument_list|,
operator|&
name|placeradio
index|[
name|PLACEMENT_TYPE_EVEN_DIST
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|placeradio
index|[
name|PLACEMENT_TYPE_RANDOM
index|]
argument_list|,
name|_
argument_list|(
literal|"Place strokes randomly around the image"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|placeradio
index|[
name|PLACEMENT_TYPE_EVEN_DIST
index|]
argument_list|,
name|_
argument_list|(
literal|"The strokes are evenly distributed across the image"
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
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|placeradio
index|[
name|pcvals
operator|.
name|placetype
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
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
name|brushdensityadjust
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
literal|"Stroke _density:"
argument_list|)
argument_list|,
literal|100
argument_list|,
operator|-
literal|1
argument_list|,
name|pcvals
operator|.
name|brushdensity
argument_list|,
literal|1.0
argument_list|,
literal|50.0
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
literal|"The relative density of the brush strokes"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|brushdensityadjust
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
name|brushdensity
argument_list|)
expr_stmt|;
name|placecenter
operator|=
name|tmpw
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Centerize"
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
name|gimp_help_set_help_data
argument_list|(
name|tmpw
argument_list|,
name|_
argument_list|(
literal|"Focus the brush strokes around the center of the image"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|pcvals
operator|.
name|placecenter
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

