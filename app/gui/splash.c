begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"splash.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|DEFAULT_WIDTH
define|#
directive|define
name|DEFAULT_WIDTH
value|300
end_define

begin_decl_stmt
DECL|variable|win_initstatus
specifier|static
name|GtkWidget
modifier|*
name|win_initstatus
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|label1
specifier|static
name|GtkWidget
modifier|*
name|label1
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|label2
specifier|static
name|GtkWidget
modifier|*
name|label2
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|progress
specifier|static
name|GtkWidget
modifier|*
name|progress
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|splash_map
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|splash_create (gboolean show_image)
name|splash_create
parameter_list|(
name|gboolean
name|show_image
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
init|=
name|NULL
decl_stmt|;
name|win_initstatus
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_TOPLEVEL
argument_list|)
expr_stmt|;
name|gtk_window_set_type_hint
argument_list|(
name|GTK_WINDOW
argument_list|(
name|win_initstatus
argument_list|)
argument_list|,
name|GDK_WINDOW_TYPE_HINT_SPLASHSCREEN
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|win_initstatus
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"GIMP Startup"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|win_initstatus
argument_list|)
argument_list|,
literal|"gimp_startup"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|win_initstatus
argument_list|)
argument_list|,
name|GTK_WIN_POS_CENTER
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|win_initstatus
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|win_initstatus
argument_list|,
literal|"delete_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_true
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* we don't want the splash screen to send the startup notification */
name|gtk_window_set_auto_startup_notification
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|win_initstatus
argument_list|,
literal|"map"
argument_list|,
name|G_CALLBACK
argument_list|(
name|splash_map
argument_list|)
argument_list|,
name|NULL
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
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|win_initstatus
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
if|if
condition|(
name|show_image
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
literal|"images"
argument_list|,
literal|"gimp_splash.png"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gdk_pixbuf_new_from_file
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
block|{
name|GtkWidget
modifier|*
name|align
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|image
operator|=
name|gtk_image_new_from_pixbuf
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|align
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|align
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|align
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|align
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|pixbuf
condition|)
block|{
name|GtkWidget
modifier|*
name|line
decl_stmt|;
name|label1
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"The GIMP"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start_defaults
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label1
argument_list|)
expr_stmt|;
name|label2
operator|=
name|gtk_label_new
argument_list|(
name|GIMP_VERSION
argument_list|)
expr_stmt|;
name|gtk_box_pack_start_defaults
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label2
argument_list|)
expr_stmt|;
name|line
operator|=
name|gtk_hseparator_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start_defaults
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|line
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|line
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|win_initstatus
argument_list|,
name|DEFAULT_WIDTH
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
name|label1
operator|=
name|gtk_label_new
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|gtk_box_pack_start_defaults
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label1
argument_list|)
expr_stmt|;
name|label2
operator|=
name|gtk_label_new
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|gtk_box_pack_start_defaults
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label2
argument_list|)
expr_stmt|;
name|progress
operator|=
name|gtk_progress_bar_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start_defaults
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|progress
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|win_initstatus
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|splash_destroy (void)
name|splash_destroy
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|win_initstatus
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|win_initstatus
argument_list|)
expr_stmt|;
name|win_initstatus
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|splash_update (const gchar * text1,const gchar * text2,gdouble percentage)
name|splash_update
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text1
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text2
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
if|if
condition|(
operator|!
name|win_initstatus
condition|)
return|return;
if|if
condition|(
name|text1
condition|)
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label1
argument_list|)
argument_list|,
name|text1
argument_list|)
expr_stmt|;
if|if
condition|(
name|text2
condition|)
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label2
argument_list|)
argument_list|,
name|text2
argument_list|)
expr_stmt|;
name|gtk_progress_bar_set_fraction
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|progress
argument_list|)
argument_list|,
name|CLAMP
argument_list|(
name|percentage
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|gtk_events_pending
argument_list|()
condition|)
name|gtk_main_iteration
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|splash_map (void)
name|splash_map
parameter_list|(
name|void
parameter_list|)
block|{
comment|/*  Reenable startup notification after the splash has been shown    *  so that the next window that is mapped sends the notification.      */
name|gtk_window_set_auto_startup_notification
argument_list|(
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

