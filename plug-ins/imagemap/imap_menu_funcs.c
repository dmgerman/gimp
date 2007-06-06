begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2005 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
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
file|"imap_command.h"
end_include

begin_include
include|#
directive|include
file|"imap_menu_funcs.h"
end_include

begin_decl_stmt
DECL|variable|accelerator_group
specifier|static
name|GtkAccelGroup
modifier|*
name|accelerator_group
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|init_accel_group (GtkWidget * window)
name|init_accel_group
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|)
block|{
name|accelerator_group
operator|=
name|gtk_accel_group_new
argument_list|()
expr_stmt|;
name|gtk_window_add_accel_group
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|accelerator_group
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|add_accelerator (GtkWidget * widget,guint accelerator_key,guint8 accelerator_mods)
name|add_accelerator
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|accelerator_key
parameter_list|,
name|guint8
name|accelerator_mods
parameter_list|)
block|{
name|gtk_widget_add_accelerator
argument_list|(
name|widget
argument_list|,
literal|"activate"
argument_list|,
name|accelerator_group
argument_list|,
name|accelerator_key
argument_list|,
name|accelerator_mods
argument_list|,
name|GTK_ACCEL_VISIBLE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|insert_item_with_label (GtkWidget * parent,gint position,gchar * label,MenuCallback activate,gpointer data)
name|insert_item_with_label
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|gint
name|position
parameter_list|,
name|gchar
modifier|*
name|label
parameter_list|,
name|MenuCallback
name|activate
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|item
init|=
name|gtk_image_menu_item_new_with_mnemonic
argument_list|(
name|label
argument_list|)
decl_stmt|;
name|gtk_menu_shell_insert
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|parent
argument_list|)
argument_list|,
name|item
argument_list|,
name|position
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|item
argument_list|,
literal|"activate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|activate
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|item
argument_list|)
expr_stmt|;
return|return
name|item
return|;
block|}
end_function

end_unit

