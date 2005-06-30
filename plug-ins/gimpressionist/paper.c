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
DECL|variable|paper_preview
specifier|static
name|GtkWidget
modifier|*
name|paper_preview
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paper_invert
specifier|static
name|GtkWidget
modifier|*
name|paper_invert
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paper_list
specifier|static
name|GtkWidget
modifier|*
name|paper_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paper_relief_adjust
specifier|static
name|GtkObject
modifier|*
name|paper_relief_adjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paper_scale_adjust
specifier|static
name|GtkObject
modifier|*
name|paper_scale_adjust
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|paper_overlay
specifier|static
name|GtkWidget
modifier|*
name|paper_overlay
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|paper_update_preview (void)
specifier|static
name|void
name|paper_update_preview
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
modifier|*
name|buf
decl_stmt|,
modifier|*
name|paper_preview_buffer
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
name|ppm_load
argument_list|(
name|pcvals
operator|.
name|selected_paper
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
name|paper_preview_buffer
operator|=
name|g_new0
argument_list|(
name|guchar
argument_list|,
literal|100
operator|*
literal|100
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|buf
operator|=
name|paper_preview_buffer
init|;
name|i
operator|<
literal|100
condition|;
name|i
operator|++
operator|,
name|buf
operator|+=
literal|100
control|)
block|{
name|gint
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
name|paper_invert
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
block|}
name|gimp_preview_area_draw
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|paper_preview
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|100
argument_list|,
literal|100
argument_list|,
name|GIMP_GRAY_IMAGE
argument_list|,
name|paper_preview_buffer
argument_list|,
literal|100
argument_list|)
expr_stmt|;
name|ppm_kill
argument_list|(
operator|&
name|p
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|paper_preview_buffer
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|paper_preview
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|paper_select (GtkTreeSelection * selection,gpointer data)
name|paper_select
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
name|selected_paper
argument_list|,
name|fname
argument_list|,
sizeof|sizeof
argument_list|(
name|pcvals
operator|.
name|selected_paper
argument_list|)
argument_list|)
expr_stmt|;
name|paper_update_preview
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
name|void
DECL|function|paper_restore (void)
name|paper_restore
parameter_list|(
name|void
parameter_list|)
block|{
name|reselect
argument_list|(
name|paper_list
argument_list|,
name|pcvals
operator|.
name|selected_paper
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|paper_relief_adjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|paper_relief
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|paper_scale_adjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|paper_scale
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paper_invert
argument_list|)
argument_list|,
name|pcvals
operator|.
name|paper_invert
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paper_overlay
argument_list|)
argument_list|,
name|pcvals
operator|.
name|paper_overlay
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|paper_store (void)
name|paper_store
parameter_list|(
name|void
parameter_list|)
block|{
name|pcvals
operator|.
name|paper_invert
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paper_invert
argument_list|)
operator|->
name|active
expr_stmt|;
name|pcvals
operator|.
name|paper_invert
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paper_invert
argument_list|)
operator|->
name|active
expr_stmt|;
name|pcvals
operator|.
name|paper_overlay
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paper_overlay
argument_list|)
operator|->
name|active
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|create_paperpage (GtkNotebook * notebook)
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
name|GtkListStore
modifier|*
name|paper_store_list
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
name|paper_list
operator|=
name|view
operator|=
name|create_one_column_list
argument_list|(
name|box1
argument_list|,
name|paper_select
argument_list|)
expr_stmt|;
name|paper_store_list
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
name|paper_preview
operator|=
name|tmpw
operator|=
name|gimp_preview_area_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|tmpw
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
name|paper_invert
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
name|paper_select
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
name|paper_invert
argument_list|)
expr_stmt|;
name|paper_overlay
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
name|paper_overlay
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
name|paper_scale_adjust
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
name|paper_scale
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
name|paper_scale_adjust
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|pcvals
operator|.
name|paper_scale
argument_list|)
expr_stmt|;
name|paper_relief_adjust
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
name|paper_relief
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
name|paper_relief_adjust
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|pcvals
operator|.
name|paper_relief
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter_first
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|paper_store_list
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
name|paper_select
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
name|selected_paper
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

