begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"pmg_gtk_objects.h"
end_include

begin_function
DECL|function|pmg_button_with_label_new ()
name|PmgButtonLabel
modifier|*
name|pmg_button_with_label_new
parameter_list|()
block|{
name|PmgButtonLabel
modifier|*
name|structure
decl_stmt|;
name|structure
operator|=
name|g_new
argument_list|(
name|PmgButtonLabel
argument_list|,
literal|1
argument_list|)
expr_stmt|;
return|return
name|structure
return|;
block|}
end_function

begin_function
name|PmgButtonLabelXpm
modifier|*
DECL|function|pmg_button_label_xpm_new (GtkWidget * parent,gchar * xpm_filename,gchar * label_text,gchar * additional_label_text,gint v_or_h,GtkSignalFunc * click_function,gpointer * click_data)
name|pmg_button_label_xpm_new
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|gchar
modifier|*
name|xpm_filename
parameter_list|,
name|gchar
modifier|*
name|label_text
parameter_list|,
name|gchar
modifier|*
name|additional_label_text
parameter_list|,
name|gint
name|v_or_h
parameter_list|,
name|GtkSignalFunc
modifier|*
name|click_function
parameter_list|,
name|gpointer
modifier|*
name|click_data
parameter_list|)
block|{
name|PmgButtonLabelXpm
modifier|*
name|xpm_button
decl_stmt|;
name|GtkWidget
modifier|*
name|label_box
decl_stmt|;
name|xpm_button
operator|=
name|g_new
argument_list|(
name|PmgButtonLabelXpm
argument_list|,
literal|1
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|v_or_h
condition|)
block|{
case|case
literal|'v'
case|:
name|xpm_button
operator|->
name|box
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'h'
case|:
name|xpm_button
operator|->
name|box
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
break|break;
block|}
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|xpm_button
operator|->
name|box
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|xpm_button
operator|->
name|box
argument_list|)
expr_stmt|;
name|xpm_button
operator|->
name|parent
operator|=
name|parent
expr_stmt|;
block|{
name|label_box
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label_box
argument_list|)
expr_stmt|;
name|xpm_button
operator|->
name|label
operator|=
name|gtk_label_new
argument_list|(
name|label_text
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|xpm_button
operator|->
name|label
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|label_box
argument_list|)
argument_list|,
name|xpm_button
operator|->
name|label
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
literal|""
argument_list|,
name|additional_label_text
argument_list|)
condition|)
block|{
name|xpm_button
operator|->
name|additional_label
operator|=
name|gtk_label_new
argument_list|(
name|additional_label_text
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|xpm_button
operator|->
name|additional_label
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|label_box
argument_list|)
argument_list|,
name|xpm_button
operator|->
name|additional_label
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
name|xpm_button
operator|->
name|pixmap_id
operator|=
name|NULL
expr_stmt|;
name|pmg_set_xpm_in_button_label
argument_list|(
name|xpm_button
argument_list|,
name|xpm_filename
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|xpm_button
operator|->
name|pixmap_id
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|xpm_button
operator|->
name|box
argument_list|)
argument_list|,
name|xpm_button
operator|->
name|pixmap_id
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|xpm_button
operator|->
name|box
argument_list|)
argument_list|,
name|label_box
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|xpm_button
operator|->
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|xpm_button
operator|->
name|button
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|xpm_button
operator|->
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|click_function
argument_list|,
name|click_data
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|xpm_button
operator|->
name|button
argument_list|)
argument_list|,
name|xpm_button
operator|->
name|box
argument_list|)
expr_stmt|;
return|return
name|xpm_button
return|;
block|}
end_function

begin_function
name|void
DECL|function|pmg_set_xpm_in_button_label (PmgButtonLabelXpm * xpm_button,gchar * xpm_filename)
name|pmg_set_xpm_in_button_label
parameter_list|(
name|PmgButtonLabelXpm
modifier|*
name|xpm_button
parameter_list|,
name|gchar
modifier|*
name|xpm_filename
parameter_list|)
block|{
name|GdkPixmap
modifier|*
name|pixmap
decl_stmt|;
name|GdkBitmap
modifier|*
name|mask
decl_stmt|;
name|GtkStyle
modifier|*
name|style
decl_stmt|;
name|style
operator|=
name|gtk_widget_get_style
argument_list|(
name|xpm_button
operator|->
name|parent
argument_list|)
expr_stmt|;
name|pixmap
operator|=
name|gdk_pixmap_create_from_xpm
argument_list|(
name|xpm_button
operator|->
name|parent
operator|->
name|window
argument_list|,
operator|&
name|mask
argument_list|,
operator|&
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|xpm_filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|xpm_button
operator|->
name|pixmap_id
condition|)
name|xpm_button
operator|->
name|pixmap_id
operator|=
name|gtk_pixmap_new
argument_list|(
name|pixmap
argument_list|,
name|mask
argument_list|)
expr_stmt|;
else|else
name|gtk_pixmap_set
argument_list|(
name|GTK_PIXMAP
argument_list|(
name|xpm_button
operator|->
name|pixmap_id
argument_list|)
argument_list|,
name|pixmap
argument_list|,
name|mask
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

