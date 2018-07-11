begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2005 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  *  */
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
file|"imap_about.h"
end_include

begin_include
include|#
directive|include
file|"imap_main.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function
name|void
DECL|function|do_about_dialog (void)
name|do_about_dialog
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|authors
index|[]
init|=
block|{
literal|"Maurits Rijk (m.rijk@chello.nl)"
block|,
name|NULL
block|}
decl_stmt|;
name|dialog
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_ABOUT_DIALOG
argument_list|,
literal|"transient-for"
argument_list|,
name|get_dialog
argument_list|()
argument_list|,
literal|"program-name"
argument_list|,
name|_
argument_list|(
literal|"Image Map Plug-in"
argument_list|)
argument_list|,
literal|"version"
argument_list|,
literal|"2.3"
argument_list|,
literal|"authors"
argument_list|,
name|authors
argument_list|,
literal|"copyright"
argument_list|,
name|_
argument_list|(
literal|"Copyright Â© 1999-2005 by Maurits Rijk"
argument_list|)
argument_list|,
literal|"license"
argument_list|,
name|_
argument_list|(
literal|"Released under the GNU General Public License"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|dialog
argument_list|)
expr_stmt|;
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

