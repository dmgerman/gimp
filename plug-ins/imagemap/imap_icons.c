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
file|"imap_icons.h"
end_include

begin_include
include|#
directive|include
file|"images/imagemap-icon-images.h"
end_include

begin_include
include|#
directive|include
file|"images/imagemap-icon-images.c"
end_include

begin_function
name|void
DECL|function|init_icons (void)
name|init_icons
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
name|GtkIconTheme
modifier|*
name|icon_theme
decl_stmt|;
if|if
condition|(
name|initialized
condition|)
return|return;
name|initialized
operator|=
name|TRUE
expr_stmt|;
name|icon_theme
operator|=
name|gtk_icon_theme_get_default
argument_list|()
expr_stmt|;
name|gtk_icon_theme_add_resource_path
argument_list|(
name|icon_theme
argument_list|,
literal|"/org/gimp/imagemap/icons"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

