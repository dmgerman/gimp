begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpfiledialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"file-dialog-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|file_dialog_show (GtkWidget * filesel,GtkWidget * parent)
name|file_dialog_show
parameter_list|(
name|GtkWidget
modifier|*
name|filesel
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Toolbox>"
argument_list|,
literal|"/File/Open..."
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Open..."
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Save"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Save as..."
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Save a Copy..."
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesel
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|filesel
argument_list|)
operator|->
name|selection_entry
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesel
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_dialog_hide (GtkWidget * filesel)
name|file_dialog_hide
parameter_list|(
name|GtkWidget
modifier|*
name|filesel
parameter_list|)
block|{
name|gtk_widget_hide
argument_list|(
name|filesel
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Toolbox>"
argument_list|,
literal|"/File/Open..."
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Open..."
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Save"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Save as..."
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
argument_list|,
literal|"/File/Save a Copy..."
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

