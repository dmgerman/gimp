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
file|"infile.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
DECL|variable|preview
specifier|static
name|GtkWidget
modifier|*
name|preview
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|previewbutton
specifier|static
name|GtkWidget
modifier|*
name|previewbutton
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|preview_set_button_label (gchar * text)
name|void
name|preview_set_button_label
parameter_list|(
name|gchar
modifier|*
name|text
parameter_list|)
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|previewbutton
argument_list|)
operator|->
name|child
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|drawalpha (ppm_t * p,ppm_t * a)
specifier|static
name|void
name|drawalpha
parameter_list|(
name|ppm_t
modifier|*
name|p
parameter_list|,
name|ppm_t
modifier|*
name|a
parameter_list|)
block|{
name|int
name|x
decl_stmt|,
name|y
decl_stmt|,
name|g
decl_stmt|;
name|double
name|v
decl_stmt|;
name|int
name|gridsize
init|=
literal|16
decl_stmt|;
name|int
name|rowstride
init|=
name|p
operator|->
name|width
operator|*
literal|3
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|p
operator|->
name|height
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|p
operator|->
name|width
condition|;
name|x
operator|++
control|)
block|{
name|int
name|k
init|=
name|y
operator|*
name|rowstride
operator|+
name|x
operator|*
literal|3
decl_stmt|;
if|if
condition|(
operator|!
name|a
operator|->
name|col
index|[
name|k
index|]
condition|)
continue|continue;
name|v
operator|=
literal|1.0
operator|-
name|a
operator|->
name|col
index|[
name|k
index|]
operator|/
literal|255.0
expr_stmt|;
name|g
operator|=
operator|(
operator|(
name|x
operator|/
name|gridsize
operator|+
name|y
operator|/
name|gridsize
operator|)
operator|%
literal|2
operator|)
operator|*
literal|60
operator|+
literal|100
expr_stmt|;
name|p
operator|->
name|col
index|[
name|k
operator|+
literal|0
index|]
operator|*=
name|v
expr_stmt|;
name|p
operator|->
name|col
index|[
name|k
operator|+
literal|1
index|]
operator|*=
name|v
expr_stmt|;
name|p
operator|->
name|col
index|[
name|k
operator|+
literal|2
index|]
operator|*=
name|v
expr_stmt|;
name|v
operator|=
literal|1.0
operator|-
name|v
expr_stmt|;
name|p
operator|->
name|col
index|[
name|k
operator|+
literal|0
index|]
operator|+=
name|g
operator|*
name|v
expr_stmt|;
name|p
operator|->
name|col
index|[
name|k
operator|+
literal|1
index|]
operator|+=
name|g
operator|*
name|v
expr_stmt|;
name|p
operator|->
name|col
index|[
name|k
operator|+
literal|2
index|]
operator|+=
name|g
operator|*
name|v
expr_stmt|;
block|}
block|}
block|}
end_function

begin_decl_stmt
DECL|variable|preview_ppm
specifier|static
name|ppm_t
name|preview_ppm
init|=
block|{
literal|0
block|,
literal|0
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|alpha_ppm
specifier|static
name|ppm_t
name|alpha_ppm
init|=
block|{
literal|0
block|,
literal|0
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|backup_ppm
specifier|static
name|ppm_t
name|backup_ppm
init|=
block|{
literal|0
block|,
literal|0
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|alpha_backup_ppm
specifier|static
name|ppm_t
name|alpha_backup_ppm
init|=
block|{
literal|0
block|,
literal|0
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|preview_free_resources (void)
name|void
name|preview_free_resources
parameter_list|(
name|void
parameter_list|)
block|{
name|ppm_kill
argument_list|(
operator|&
name|preview_ppm
argument_list|)
expr_stmt|;
name|ppm_kill
argument_list|(
operator|&
name|alpha_ppm
argument_list|)
expr_stmt|;
name|ppm_kill
argument_list|(
operator|&
name|backup_ppm
argument_list|)
expr_stmt|;
name|ppm_kill
argument_list|(
operator|&
name|alpha_backup_ppm
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|updatepreview (GtkWidget * wg,gpointer d)
name|updatepreview
parameter_list|(
name|GtkWidget
modifier|*
name|wg
parameter_list|,
name|gpointer
name|d
parameter_list|)
block|{
comment|/* This portion is remmed out because of the remming out of the    * code below.    *            -- Shlomi Fish    * */
if|#
directive|if
literal|0
block|guchar buf[PREVIEWSIZE*3];    if (!PPM_IS_INITED (&infile)&& d)     grabarea();
endif|#
directive|endif
comment|/* It seems that infile.col must be true here. (after grabarea() that is.)    * Thus, I'm removing this entire portion of the code in hope that    * it works OK afterwards.    *            -- Shlomi Fish    * */
if|#
directive|if
literal|0
block|if (!PPM_IS_INITED (&infile)&& !d) {     guchar *buffer;      buffer = g_new0 (guchar, 3*PREVIEWSIZE*PREVIEWSIZE);     gimp_preview_area_draw (GIMP_PREVIEW_AREA (preview),                             0, 0, PREVIEWSIZE, PREVIEWSIZE,                             GIMP_RGB_IMAGE,                             buffer,                             PREVIEWSIZE * 3);          g_free (buffer);   }   else
endif|#
directive|endif
block|{
if|if
condition|(
operator|!
name|PPM_IS_INITED
argument_list|(
operator|&
name|backup_ppm
argument_list|)
condition|)
block|{
name|infile_copy_to_ppm
argument_list|(
operator|&
name|backup_ppm
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|backup_ppm
operator|.
name|width
operator|!=
name|PREVIEWSIZE
operator|)
operator|||
operator|(
name|backup_ppm
operator|.
name|height
operator|!=
name|PREVIEWSIZE
operator|)
condition|)
name|resize_fast
argument_list|(
operator|&
name|backup_ppm
argument_list|,
name|PREVIEWSIZE
argument_list|,
name|PREVIEWSIZE
argument_list|)
expr_stmt|;
if|if
condition|(
name|img_has_alpha
condition|)
block|{
name|infile_copy_alpha_to_ppm
argument_list|(
operator|&
name|alpha_backup_ppm
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|alpha_backup_ppm
operator|.
name|width
operator|!=
name|PREVIEWSIZE
operator|)
operator|||
operator|(
name|alpha_backup_ppm
operator|.
name|height
operator|!=
name|PREVIEWSIZE
operator|)
condition|)
name|resize_fast
argument_list|(
operator|&
name|alpha_backup_ppm
argument_list|,
name|PREVIEWSIZE
argument_list|,
name|PREVIEWSIZE
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|PPM_IS_INITED
argument_list|(
operator|&
name|preview_ppm
argument_list|)
condition|)
block|{
name|ppm_copy
argument_list|(
operator|&
name|backup_ppm
argument_list|,
operator|&
name|preview_ppm
argument_list|)
expr_stmt|;
if|if
condition|(
name|img_has_alpha
condition|)
name|ppm_copy
argument_list|(
operator|&
name|alpha_backup_ppm
argument_list|,
operator|&
name|alpha_ppm
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|d
condition|)
block|{
name|store_values
argument_list|()
expr_stmt|;
if|if
condition|(
name|GPOINTER_TO_INT
argument_list|(
name|d
argument_list|)
operator|!=
literal|2
condition|)
name|repaint
argument_list|(
operator|&
name|preview_ppm
argument_list|,
operator|&
name|alpha_ppm
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|img_has_alpha
condition|)
name|drawalpha
argument_list|(
operator|&
name|preview_ppm
argument_list|,
operator|&
name|alpha_ppm
argument_list|)
expr_stmt|;
name|gimp_preview_area_draw
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|PREVIEWSIZE
argument_list|,
name|PREVIEWSIZE
argument_list|,
name|GIMP_RGB_IMAGE
argument_list|,
name|preview_ppm
operator|.
name|col
argument_list|,
name|PREVIEWSIZE
operator|*
literal|3
argument_list|)
expr_stmt|;
name|ppm_kill
argument_list|(
operator|&
name|preview_ppm
argument_list|)
expr_stmt|;
if|if
condition|(
name|img_has_alpha
condition|)
name|ppm_kill
argument_list|(
operator|&
name|alpha_ppm
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|preview_size_allocate (GtkWidget * preview)
name|preview_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|)
block|{
name|updatepreview
argument_list|(
name|preview
argument_list|,
name|GINT_TO_POINTER
argument_list|(
literal|0
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|create_preview (void)
name|create_preview
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
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
name|vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_preview_area_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|preview
argument_list|,
name|PREVIEWSIZE
argument_list|,
name|PREVIEWSIZE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
comment|/* This is so the preview will be displayed when the dialog is invoked. */
name|g_signal_connect
argument_list|(
name|preview
argument_list|,
literal|"size-allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|preview_size_allocate
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
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
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|previewbutton
operator|=
name|button
operator|=
name|gtk_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Update"
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|updatepreview
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|_
argument_list|(
literal|"Refresh the Preview window"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_from_stock
argument_list|(
name|GIMP_STOCK_RESET
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|updatepreview
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|_
argument_list|(
literal|"Revert to the original image"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit

