begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"menus-types.h"
end_include

begin_include
include|#
directive|include
file|"file-menu.h"
end_include

begin_include
include|#
directive|include
file|"image-menu.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-menus.h"
end_include

begin_include
include|#
directive|include
file|"window-menu.h"
end_include

begin_function
name|void
DECL|function|image_menu_setup (GimpUIManager * manager,const gchar * ui_path)
name|image_menu_setup
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|)
block|{
name|gchar
modifier|*
name|path
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|ui_path
argument_list|,
literal|"/dummy-menubar"
argument_list|)
condition|)
name|ui_path
operator|=
literal|"/dummy-menubar/image-popup"
expr_stmt|;
name|file_menu_setup
argument_list|(
name|manager
argument_list|,
name|ui_path
argument_list|)
expr_stmt|;
name|plug_in_menus_setup
argument_list|(
name|manager
argument_list|,
name|ui_path
argument_list|)
expr_stmt|;
name|path
operator|=
name|g_strconcat
argument_list|(
name|ui_path
argument_list|,
literal|"/View"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|window_menu_setup
argument_list|(
name|manager
argument_list|,
literal|"view"
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

