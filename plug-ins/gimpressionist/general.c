begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
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
file|"infile.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
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

begin_define
DECL|macro|NUMGENERALBGRADIO
define|#
directive|define
name|NUMGENERALBGRADIO
value|4
end_define

begin_decl_stmt
DECL|variable|general_bg_radio
specifier|static
name|GtkWidget
modifier|*
name|general_bg_radio
index|[
name|NUMGENERALBGRADIO
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|general_paint_edges
specifier|static
name|GtkWidget
modifier|*
name|general_paint_edges
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|general_dark_edge_adjust
specifier|static
name|GtkObject
modifier|*
name|general_dark_edge_adjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|general_tileable
specifier|static
name|GtkWidget
modifier|*
name|general_tileable
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|general_drop_shadow
specifier|static
name|GtkWidget
modifier|*
name|general_drop_shadow
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|general_color_button
specifier|static
name|GtkWidget
modifier|*
name|general_color_button
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|general_shadow_adjust
specifier|static
name|GtkObject
modifier|*
name|general_shadow_adjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|general_shadow_depth
specifier|static
name|GtkObject
modifier|*
name|general_shadow_depth
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|general_shadow_blur
specifier|static
name|GtkObject
modifier|*
name|general_shadow_blur
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dev_thresh_adjust
specifier|static
name|GtkObject
modifier|*
name|dev_thresh_adjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|int
DECL|function|normalize_bg (int n)
name|normalize_bg
parameter_list|(
name|int
name|n
parameter_list|)
block|{
return|return
operator|(
operator|!
name|img_has_alpha
operator|&&
operator|(
name|n
operator|==
literal|3
operator|)
operator|)
condition|?
literal|1
else|:
name|n
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|general_bg_callback (GtkWidget * wg,void * d)
name|general_bg_callback
parameter_list|(
name|GtkWidget
modifier|*
name|wg
parameter_list|,
name|void
modifier|*
name|d
parameter_list|)
block|{
name|pcvals
operator|.
name|general_background_type
operator|=
name|normalize_bg
argument_list|(
name|GPOINTER_TO_INT
argument_list|(
name|d
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|general_store (void)
name|general_store
parameter_list|(
name|void
parameter_list|)
block|{
name|pcvals
operator|.
name|general_paint_edges
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|general_paint_edges
argument_list|)
operator|->
name|active
expr_stmt|;
name|pcvals
operator|.
name|general_dark_edge
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|general_dark_edge_adjust
argument_list|)
operator|->
name|value
expr_stmt|;
name|pcvals
operator|.
name|general_tileable
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|general_tileable
argument_list|)
operator|->
name|active
expr_stmt|;
name|pcvals
operator|.
name|general_drop_shadow
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|general_drop_shadow
argument_list|)
operator|->
name|active
expr_stmt|;
name|pcvals
operator|.
name|general_shadow_darkness
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|general_shadow_adjust
argument_list|)
operator|->
name|value
expr_stmt|;
name|pcvals
operator|.
name|general_shadow_depth
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|general_shadow_depth
argument_list|)
operator|->
name|value
expr_stmt|;
name|pcvals
operator|.
name|general_shadow_blur
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|general_shadow_blur
argument_list|)
operator|->
name|value
expr_stmt|;
name|pcvals
operator|.
name|devthresh
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|dev_thresh_adjust
argument_list|)
operator|->
name|value
expr_stmt|;
block|}
end_function

begin_function
name|int
DECL|function|general_bg_type_input (int in)
name|general_bg_type_input
parameter_list|(
name|int
name|in
parameter_list|)
block|{
return|return
name|CLAMP_UP_TO
argument_list|(
name|in
argument_list|,
name|NUMGENERALBGRADIO
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|general_restore (void)
name|general_restore
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|general_bg_radio
index|[
name|normalize_bg
argument_list|(
name|pcvals
operator|.
name|general_background_type
argument_list|)
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
name|general_paint_edges
argument_list|)
argument_list|,
name|pcvals
operator|.
name|general_paint_edges
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|general_dark_edge_adjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|general_dark_edge
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|general_shadow_adjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|general_shadow_darkness
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|general_drop_shadow
argument_list|)
argument_list|,
name|pcvals
operator|.
name|general_drop_shadow
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|general_shadow_depth
argument_list|)
argument_list|,
name|pcvals
operator|.
name|general_shadow_depth
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|general_shadow_blur
argument_list|)
argument_list|,
name|pcvals
operator|.
name|general_shadow_blur
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|general_tileable
argument_list|)
argument_list|,
name|pcvals
operator|.
name|general_tileable
argument_list|)
expr_stmt|;
name|gimp_color_button_set_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|general_color_button
argument_list|)
argument_list|,
operator|&
name|pcvals
operator|.
name|color
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|dev_thresh_adjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|devthresh
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|select_color (GtkWidget * widget,gpointer data)
name|select_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|general_bg_radio
index|[
name|BG_TYPE_SOLID
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|create_general_button (GtkWidget * box,int idx,gchar * label,gchar * help_string,GSList ** radio_group)
name|create_general_button
parameter_list|(
name|GtkWidget
modifier|*
name|box
parameter_list|,
name|int
name|idx
parameter_list|,
name|gchar
modifier|*
name|label
parameter_list|,
name|gchar
modifier|*
name|help_string
parameter_list|,
name|GSList
modifier|*
modifier|*
name|radio_group
parameter_list|)
block|{
return|return
name|create_radio_button
argument_list|(
name|box
argument_list|,
name|idx
argument_list|,
name|general_bg_callback
argument_list|,
name|label
argument_list|,
name|help_string
argument_list|,
name|radio_group
argument_list|,
name|general_bg_radio
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|create_generalpage (GtkNotebook * notebook)
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
name|label
decl_stmt|,
modifier|*
name|tmpw
decl_stmt|,
modifier|*
name|frame
decl_stmt|,
modifier|*
name|table
decl_stmt|;
name|GSList
modifier|*
name|radio_group
init|=
name|NULL
decl_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_General"
argument_list|)
argument_list|)
expr_stmt|;
name|thispage
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
name|thispage
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|thispage
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|thispage
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
name|box3
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|box3
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box3
argument_list|)
expr_stmt|;
name|create_general_button
argument_list|(
name|box3
argument_list|,
name|BG_TYPE_KEEP_ORIGINAL
argument_list|,
name|_
argument_list|(
literal|"Keep original"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Preserve the original image as a background"
argument_list|)
argument_list|,
operator|&
name|radio_group
argument_list|)
expr_stmt|;
name|create_general_button
argument_list|(
name|box3
argument_list|,
name|BG_TYPE_FROM_PAPER
argument_list|,
name|_
argument_list|(
literal|"From paper"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Copy the texture of the selected paper as a background"
argument_list|)
argument_list|,
operator|&
name|radio_group
argument_list|)
expr_stmt|;
name|box4
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
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
name|create_general_button
argument_list|(
name|box4
argument_list|,
name|BG_TYPE_SOLID
argument_list|,
name|_
argument_list|(
literal|"Solid"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Solid colored background"
argument_list|)
argument_list|,
operator|&
name|radio_group
argument_list|)
expr_stmt|;
name|general_color_button
operator|=
name|gimp_color_button_new
argument_list|(
name|_
argument_list|(
literal|"Color"
argument_list|)
argument_list|,
name|COLORBUTTONWIDTH
argument_list|,
name|COLORBUTTONHEIGHT
argument_list|,
operator|&
name|pcvals
operator|.
name|color
argument_list|,
name|GIMP_COLOR_AREA_FLAT
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|general_color_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|select_color
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|general_color_button
argument_list|,
literal|"color-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_button_get_color
argument_list|)
argument_list|,
operator|&
name|pcvals
operator|.
name|color
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box4
argument_list|)
argument_list|,
name|general_color_button
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
name|general_color_button
argument_list|)
expr_stmt|;
name|tmpw
operator|=
name|create_general_button
argument_list|(
name|box3
argument_list|,
name|BG_TYPE_TRANSPARENT
argument_list|,
name|_
argument_list|(
literal|"Transparent"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Use a transparent background; Only the strokes painted will be visible"
argument_list|)
argument_list|,
operator|&
name|radio_group
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
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|general_bg_radio
index|[
name|pcvals
operator|.
name|general_background_type
index|]
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
literal|12
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
name|FALSE
argument_list|,
literal|6
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
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Paint edges"
argument_list|)
argument_list|)
expr_stmt|;
name|general_paint_edges
operator|=
name|tmpw
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
name|gimp_help_set_help_data
argument_list|(
name|tmpw
argument_list|,
name|_
argument_list|(
literal|"Selects if to place strokes all the way out to the edges of the image"
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
name|general_paint_edges
argument_list|)
expr_stmt|;
name|general_tileable
operator|=
name|tmpw
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Tileable"
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
name|gimp_help_set_help_data
argument_list|(
name|tmpw
argument_list|,
name|_
argument_list|(
literal|"Selects if the resulting image should be seamlessly tileable"
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
name|general_tileable
argument_list|)
expr_stmt|;
name|tmpw
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Drop shadow"
argument_list|)
argument_list|)
expr_stmt|;
name|general_drop_shadow
operator|=
name|tmpw
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
name|gimp_help_set_help_data
argument_list|(
name|tmpw
argument_list|,
name|_
argument_list|(
literal|"Adds a shadow effect to each brush stroke"
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
name|general_drop_shadow
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|5
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
name|gtk_table_set_row_spacings
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
name|general_dark_edge_adjust
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
literal|"Edge darken:"
argument_list|)
argument_list|,
literal|150
argument_list|,
literal|6
argument_list|,
name|pcvals
operator|.
name|general_dark_edge
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"How much to \"darken\" the edges of each brush stroke"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|general_shadow_adjust
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
literal|"Shadow darken:"
argument_list|)
argument_list|,
literal|150
argument_list|,
literal|6
argument_list|,
name|pcvals
operator|.
name|general_shadow_darkness
argument_list|,
literal|0.0
argument_list|,
literal|99.0
argument_list|,
literal|0.1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"How much to \"darken\" the drop shadow"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|general_shadow_depth
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
literal|"Shadow depth:"
argument_list|)
argument_list|,
literal|150
argument_list|,
literal|6
argument_list|,
name|pcvals
operator|.
name|general_shadow_depth
argument_list|,
literal|0
argument_list|,
literal|99
argument_list|,
literal|1
argument_list|,
literal|5
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
literal|"The depth of the drop shadow, i.e. how far apart from the object it should be"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|general_shadow_blur
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
literal|3
argument_list|,
name|_
argument_list|(
literal|"Shadow blur:"
argument_list|)
argument_list|,
literal|150
argument_list|,
literal|6
argument_list|,
name|pcvals
operator|.
name|general_shadow_blur
argument_list|,
literal|0
argument_list|,
literal|99
argument_list|,
literal|1
argument_list|,
literal|5
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
literal|"How much to blur the drop shadow"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dev_thresh_adjust
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
literal|4
argument_list|,
name|_
argument_list|(
literal|"Deviation threshold:"
argument_list|)
argument_list|,
literal|150
argument_list|,
literal|6
argument_list|,
name|pcvals
operator|.
name|devthresh
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.01
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"A bailout-value for adaptive selections"
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

