begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|GTK_DISABLE_DEPRECATED
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

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
file|"ppmtool.h"
end_include

begin_include
include|#
directive|include
file|"paper.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
DECL|variable|paperprev
specifier|static
name|GtkWidget
modifier|*
name|paperprev
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paperstore
specifier|static
name|GtkListStore
modifier|*
name|paperstore
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paperinvert
specifier|static
name|GtkWidget
modifier|*
name|paperinvert
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paperlist
specifier|static
name|GtkWidget
modifier|*
name|paperlist
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paperreliefadjust
specifier|static
name|GtkObject
modifier|*
name|paperreliefadjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paperscaleadjust
specifier|static
name|GtkObject
modifier|*
name|paperscaleadjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paperoverlay
specifier|static
name|GtkWidget
modifier|*
name|paperoverlay
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|updatepaperprev (void)
specifier|static
name|void
name|updatepaperprev
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|guchar
name|buf
index|[
literal|100
index|]
decl_stmt|;
name|gdouble
name|sc
decl_stmt|;
name|ppm_t
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
name|pcvals
operator|.
name|selectedpaper
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
name|gtk_widget_queue_draw
argument_list|(
name|paperprev
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|selectpaper (GtkTreeSelection * selection,gpointer data)
specifier|static
name|void
name|selectpaper
parameter_list|(
name|GtkTreeSelection
modifier|*
name|selection
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
if|if
condition|(
name|gtk_tree_selection_get_selected
argument_list|(
name|selection
argument_list|,
operator|&
name|model
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|paper
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
literal|0
argument_list|,
operator|&
name|paper
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|paper
condition|)
block|{
name|gchar
modifier|*
name|fname
init|=
name|g_build_filename
argument_list|(
literal|"Paper"
argument_list|,
name|paper
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_strlcpy
argument_list|(
name|pcvals
operator|.
name|selectedpaper
argument_list|,
name|fname
argument_list|,
sizeof|sizeof
argument_list|(
name|pcvals
operator|.
name|selectedpaper
argument_list|)
argument_list|)
expr_stmt|;
name|updatepaperprev
argument_list|()
expr_stmt|;
name|g_free
argument_list|(
name|fname
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|paper
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
DECL|function|paper_restore (void)
name|void
name|paper_restore
parameter_list|(
name|void
parameter_list|)
block|{
name|reselect
argument_list|(
name|paperlist
argument_list|,
name|pcvals
operator|.
name|selectedpaper
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|paperreliefadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|paperrelief
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|paperscaleadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|paperscale
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paperinvert
argument_list|)
argument_list|,
name|pcvals
operator|.
name|paperinvert
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paperoverlay
argument_list|)
argument_list|,
name|pcvals
operator|.
name|paperoverlay
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|paper_store (void)
name|void
name|paper_store
parameter_list|(
name|void
parameter_list|)
block|{
name|pcvals
operator|.
name|paperinvert
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paperinvert
argument_list|)
operator|->
name|active
expr_stmt|;
name|pcvals
operator|.
name|paperinvert
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paperinvert
argument_list|)
operator|->
name|active
expr_stmt|;
name|pcvals
operator|.
name|paperoverlay
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paperoverlay
argument_list|)
operator|->
name|active
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
name|label
decl_stmt|,
modifier|*
name|tmpw
decl_stmt|,
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkTreeSelection
modifier|*
name|selection
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"P_aper"
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
name|paperlist
operator|=
name|view
operator|=
name|createonecolumnlist
argument_list|(
name|box1
argument_list|,
name|selectpaper
argument_list|)
expr_stmt|;
name|paperstore
operator|=
name|GTK_LIST_STORE
argument_list|(
name|gtk_tree_view_get_model
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|selection
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|box2
operator|=
name|gtk_vbox_new
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
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box2
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
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
name|paperinvert
operator|=
name|tmpw
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Invert"
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
name|g_signal_connect_swapped
argument_list|(
name|tmpw
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|selectpaper
argument_list|)
argument_list|,
name|selection
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
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
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|pcvals
operator|.
name|paperinvert
argument_list|)
expr_stmt|;
name|paperoverlay
operator|=
name|tmpw
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"O_verlay"
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
name|gimp_help_set_help_data
argument_list|(
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
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|tmpw
argument_list|)
argument_list|,
name|pcvals
operator|.
name|paperoverlay
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
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
name|thispage
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
name|paperscaleadjust
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
literal|"Scale:"
argument_list|)
argument_list|,
literal|150
argument_list|,
operator|-
literal|1
argument_list|,
name|pcvals
operator|.
name|paperscale
argument_list|,
literal|3.0
argument_list|,
literal|150.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Specifies the scale of the texture (in percent of original file)"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|paperscaleadjust
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
name|paperscale
argument_list|)
expr_stmt|;
name|paperreliefadjust
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
literal|"Relief:"
argument_list|)
argument_list|,
literal|150
argument_list|,
operator|-
literal|1
argument_list|,
name|pcvals
operator|.
name|paperrelief
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Specifies the amount of embossing to apply to the image (in percent)"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|paperreliefadjust
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
name|paperrelief
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter_first
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|paperstore
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
name|gtk_tree_selection_select_iter
argument_list|(
name|selection
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|selectpaper
argument_list|(
name|selection
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|readdirintolist
argument_list|(
literal|"Paper"
argument_list|,
name|view
argument_list|,
name|pcvals
operator|.
name|selectedpaper
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

