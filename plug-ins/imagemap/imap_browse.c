begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|"imap_browse.h"
end_include

begin_include
include|#
directive|include
file|"open.xpm"
end_include

begin_decl_stmt
DECL|variable|target_table
specifier|static
name|GtkTargetEntry
name|target_table
index|[]
init|=
block|{
block|{
literal|"STRING"
block|,
literal|0
block|,
literal|1
block|}
block|,
block|{
literal|"text/plain"
block|,
literal|0
block|,
literal|2
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|select_cb (GtkWidget * widget,gpointer data)
name|select_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrowseWidget_t
modifier|*
name|browse
init|=
operator|(
name|BrowseWidget_t
operator|*
operator|)
name|data
decl_stmt|;
name|gchar
modifier|*
name|p
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|file
decl_stmt|;
name|file
operator|=
name|gtk_file_selection_get_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|browse
operator|->
name|file_selection
argument_list|)
argument_list|)
expr_stmt|;
name|p
operator|=
operator|(
name|browse
operator|->
name|filter
operator|)
condition|?
name|browse
operator|->
name|filter
argument_list|(
name|file
argument_list|,
name|browse
operator|->
name|filter_data
argument_list|)
else|:
operator|(
name|gchar
operator|*
operator|)
name|file
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|browse
operator|->
name|file
argument_list|)
argument_list|,
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
name|browse
operator|->
name|filter
condition|)
name|g_free
argument_list|(
name|p
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|browse
operator|->
name|file_selection
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|browse
operator|->
name|file
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|browse_cb (GtkWidget * widget,gpointer data)
name|browse_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrowseWidget_t
modifier|*
name|browse
init|=
operator|(
name|BrowseWidget_t
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
operator|!
name|browse
operator|->
name|file_selection
condition|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|browse
operator|->
name|file_selection
operator|=
name|gtk_file_selection_new
argument_list|(
name|browse
operator|->
name|name
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|dialog
argument_list|)
operator|->
name|cancel_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_widget_hide
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|dialog
argument_list|)
operator|->
name|ok_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|select_cb
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|browse
operator|->
name|file_selection
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|handle_drop (GtkWidget * widget,GdkDragContext * context,gint x,gint y,GtkSelectionData * data,guint info,guint time)
name|handle_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GtkSelectionData
modifier|*
name|data
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
block|{
name|gboolean
name|success
decl_stmt|;
if|if
condition|(
name|data
operator|->
name|length
operator|>=
literal|0
operator|&&
name|data
operator|->
name|format
operator|==
literal|8
condition|)
block|{
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
name|data
operator|->
name|data
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|gtk_drag_finish
argument_list|(
name|context
argument_list|,
name|success
argument_list|,
name|FALSE
argument_list|,
name|time
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|BrowseWidget_t
modifier|*
DECL|function|browse_widget_new (const gchar * name)
name|browse_widget_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|BrowseWidget_t
modifier|*
name|browse
init|=
name|g_new
argument_list|(
name|BrowseWidget_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|iconw
decl_stmt|;
name|GdkPixmap
modifier|*
name|icon
decl_stmt|;
name|GdkBitmap
modifier|*
name|mask
decl_stmt|;
name|GtkStyle
modifier|*
name|style
decl_stmt|;
name|browse
operator|->
name|file_selection
operator|=
name|NULL
expr_stmt|;
name|browse
operator|->
name|name
operator|=
name|name
expr_stmt|;
name|browse
operator|->
name|filter
operator|=
name|NULL
expr_stmt|;
name|browse
operator|->
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|browse
operator|->
name|hbox
argument_list|)
expr_stmt|;
name|browse
operator|->
name|file
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|browse
operator|->
name|hbox
argument_list|)
argument_list|,
name|browse
operator|->
name|file
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|browse
operator|->
name|file
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|target_table
argument_list|,
literal|2
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|browse
operator|->
name|file
argument_list|)
argument_list|,
literal|"drag_data_received"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|handle_drop
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|browse
operator|->
name|file
argument_list|)
expr_stmt|;
name|browse
operator|->
name|button
operator|=
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|style
operator|=
name|gtk_widget_get_style
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|icon
operator|=
name|gdk_pixmap_colormap_create_from_xpm_d
argument_list|(
name|button
operator|->
name|window
argument_list|,
name|gtk_widget_get_colormap
argument_list|(
name|button
argument_list|)
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
name|open_xpm
argument_list|)
expr_stmt|;
name|iconw
operator|=
name|gtk_pixmap_new
argument_list|(
name|icon
argument_list|,
name|mask
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|iconw
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|iconw
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|browse
operator|->
name|hbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|browse_cb
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|browse
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
return|return
name|browse
return|;
block|}
end_function

begin_function
name|void
DECL|function|browse_widget_set_filename (BrowseWidget_t * browse,const gchar * filename)
name|browse_widget_set_filename
parameter_list|(
name|BrowseWidget_t
modifier|*
name|browse
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|browse
operator|->
name|file
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|browse_widget_set_filter (BrowseWidget_t * browse,BrowseFilter_t filter,gpointer data)
name|browse_widget_set_filter
parameter_list|(
name|BrowseWidget_t
modifier|*
name|browse
parameter_list|,
name|BrowseFilter_t
name|filter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|browse
operator|->
name|filter
operator|=
name|filter
expr_stmt|;
name|browse
operator|->
name|filter_data
operator|=
name|data
expr_stmt|;
block|}
end_function

end_unit

