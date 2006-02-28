begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2003 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdarg.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"imap_statusbar.h"
end_include

begin_include
include|#
directive|include
file|"imap_stock.h"
end_include

begin_function
name|StatusBar_t
modifier|*
DECL|function|make_statusbar (GtkWidget * main_vbox,GtkWidget * window)
name|make_statusbar
parameter_list|(
name|GtkWidget
modifier|*
name|main_vbox
parameter_list|,
name|GtkWidget
modifier|*
name|window
parameter_list|)
block|{
name|StatusBar_t
modifier|*
name|statusbar
init|=
name|g_new
argument_list|(
name|StatusBar_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|,
modifier|*
name|iconw
decl_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
comment|/* Status info */
name|statusbar
operator|->
name|status
operator|=
name|gtk_statusbar_new
argument_list|()
expr_stmt|;
name|statusbar
operator|->
name|status_id
operator|=
name|gtk_statusbar_get_context_id
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|statusbar
operator|->
name|status
argument_list|)
argument_list|,
literal|"general_status"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|statusbar
operator|->
name|status
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
name|statusbar
operator|->
name|status
argument_list|)
expr_stmt|;
comment|/* (x, y) coordinate */
name|iconw
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|IMAP_STOCK_COORD
argument_list|,
name|GTK_ICON_SIZE_SMALL_TOOLBAR
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|iconw
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
name|iconw
argument_list|)
expr_stmt|;
name|statusbar
operator|->
name|xy
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|statusbar
operator|->
name|xy
argument_list|,
literal|96
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_editable_set_editable
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|statusbar
operator|->
name|xy
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|GTK_WIDGET_UNSET_FLAGS
argument_list|(
name|statusbar
operator|->
name|xy
argument_list|,
name|GTK_CAN_FOCUS
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|statusbar
operator|->
name|xy
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
name|statusbar
operator|->
name|xy
argument_list|)
expr_stmt|;
comment|/* Dimension info */
name|iconw
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|IMAP_STOCK_DIMENSION
argument_list|,
name|GTK_ICON_SIZE_SMALL_TOOLBAR
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|iconw
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
name|iconw
argument_list|)
expr_stmt|;
name|statusbar
operator|->
name|dimension
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|statusbar
operator|->
name|dimension
argument_list|,
literal|96
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_editable_set_editable
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|statusbar
operator|->
name|dimension
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|GTK_WIDGET_UNSET_FLAGS
argument_list|(
name|statusbar
operator|->
name|dimension
argument_list|,
name|GTK_CAN_FOCUS
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|statusbar
operator|->
name|dimension
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
name|statusbar
operator|->
name|dimension
argument_list|)
expr_stmt|;
comment|/* Zoom info */
name|statusbar
operator|->
name|zoom
operator|=
name|gtk_statusbar_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|statusbar
operator|->
name|zoom
argument_list|,
literal|48
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|statusbar
operator|->
name|zoom_id
operator|=
name|gtk_statusbar_get_context_id
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|statusbar
operator|->
name|zoom
argument_list|)
argument_list|,
literal|"zoom_status"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|statusbar
operator|->
name|zoom
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
name|statusbar
operator|->
name|zoom
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
return|return
name|statusbar
return|;
block|}
end_function

begin_function
name|void
DECL|function|statusbar_set_status (StatusBar_t * statusbar,const gchar * format,...)
name|statusbar_set_status
parameter_list|(
name|StatusBar_t
modifier|*
name|statusbar
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|ap
decl_stmt|;
name|char
name|scratch
index|[
literal|256
index|]
decl_stmt|;
name|va_start
argument_list|(
name|ap
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|vsprintf
argument_list|(
name|scratch
argument_list|,
name|format
argument_list|,
name|ap
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|ap
argument_list|)
expr_stmt|;
name|statusbar_clear_status
argument_list|(
name|statusbar
argument_list|)
expr_stmt|;
name|statusbar
operator|->
name|message_id
operator|=
name|gtk_statusbar_push
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|statusbar
operator|->
name|status
argument_list|)
argument_list|,
name|statusbar
operator|->
name|status_id
argument_list|,
name|scratch
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|statusbar_clear_status (StatusBar_t * statusbar)
name|statusbar_clear_status
parameter_list|(
name|StatusBar_t
modifier|*
name|statusbar
parameter_list|)
block|{
if|if
condition|(
name|statusbar
operator|->
name|message_id
condition|)
name|gtk_statusbar_remove
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|statusbar
operator|->
name|status
argument_list|)
argument_list|,
name|statusbar
operator|->
name|status_id
argument_list|,
name|statusbar
operator|->
name|message_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|statusbar_set_xy (StatusBar_t * statusbar,gint x,gint y)
name|statusbar_set_xy
parameter_list|(
name|StatusBar_t
modifier|*
name|statusbar
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|char
name|scratch
index|[
literal|16
index|]
decl_stmt|;
name|sprintf
argument_list|(
name|scratch
argument_list|,
literal|"%d, %d"
argument_list|,
operator|(
name|int
operator|)
name|x
argument_list|,
operator|(
name|int
operator|)
name|y
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|statusbar
operator|->
name|xy
argument_list|)
argument_list|,
name|scratch
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|statusbar_clear_xy (StatusBar_t * statusbar)
name|void
name|statusbar_clear_xy
parameter_list|(
name|StatusBar_t
modifier|*
name|statusbar
parameter_list|)
block|{
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|statusbar
operator|->
name|xy
argument_list|)
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|statusbar_set_dimension (StatusBar_t * statusbar,gint w,gint h)
name|statusbar_set_dimension
parameter_list|(
name|StatusBar_t
modifier|*
name|statusbar
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|gchar
name|scratch
index|[
literal|16
index|]
decl_stmt|;
name|snprintf
argument_list|(
name|scratch
argument_list|,
sizeof|sizeof
argument_list|(
name|scratch
argument_list|)
argument_list|,
literal|"%d Ã %d"
argument_list|,
operator|(
name|gint
operator|)
name|w
argument_list|,
operator|(
name|gint
operator|)
name|h
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|statusbar
operator|->
name|dimension
argument_list|)
argument_list|,
name|scratch
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|statusbar_clear_dimension (StatusBar_t * statusbar)
name|statusbar_clear_dimension
parameter_list|(
name|StatusBar_t
modifier|*
name|statusbar
parameter_list|)
block|{
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|statusbar
operator|->
name|dimension
argument_list|)
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|statusbar_set_zoom (StatusBar_t * statusbar,gint factor)
name|statusbar_set_zoom
parameter_list|(
name|StatusBar_t
modifier|*
name|statusbar
parameter_list|,
name|gint
name|factor
parameter_list|)
block|{
name|char
name|scratch
index|[
literal|16
index|]
decl_stmt|;
name|sprintf
argument_list|(
name|scratch
argument_list|,
literal|"1:%d"
argument_list|,
name|factor
argument_list|)
expr_stmt|;
name|gtk_statusbar_push
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|statusbar
operator|->
name|zoom
argument_list|)
argument_list|,
name|statusbar
operator|->
name|zoom_id
argument_list|,
name|scratch
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

